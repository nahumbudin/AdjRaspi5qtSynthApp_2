/**
 * @file		HttpBridgeQt.cpp
 *	@author		Nahum Budin
 *	@date		14-June-2026
 *	@version	1.0
 *
 *	@brief		HTTP Server used for REST Api.
 *
 */

#include "HttpBridgeQt.h"
#include <QDebug>
#include <QtConcurrent/QtConcurrent>

#include "HttpBridgeQt.h"
#include "utils.h"

#include <QDebug>
#include <QVariant>
#include <QtConcurrent/QtConcurrent>

HttpBridgeQt::HttpBridgeQt(QObject *parent)
	: QObject(parent), m_isRunning(false)
{
	setupRoutes();
}

HttpBridgeQt::~HttpBridgeQt()
{
	stopServer();
}

// ==========================================
//          SETTER IMPLEMENTATIONS
// ==========================================
void HttpBridgeQt::set_parm(int module_id, int sub_module_id, int param_id, int val)
{
	//set_int_parm_dispatcher(module_id, sub_module_id, param_id, val);
	emit parameterUpdated(module_id, sub_module_id, param_id, QVariant(val));
}

void HttpBridgeQt::set_parm(int module_id, int sub_module_id, int param_id, float val)
{
	//set_float_parm_dispatcher(module_id, sub_module_id, param_id, val);
	emit parameterUpdated(module_id, sub_module_id, param_id, QVariant(val));
}

void HttpBridgeQt::set_parm(int module_id, int sub_module_id, int param_id, bool val)
{
	//set_bool_parm_dispatcher(module_id, sub_module_id, param_id, val);
	emit parameterUpdated(module_id, sub_module_id, param_id, QVariant(val));
}

void HttpBridgeQt::set_parm(int module_id, int sub_module_id, int param_id, const std::string &val)
{
	//set_string_parm_dispatcher(module_id, sub_module_id, param_id, val);
	emit parameterUpdated(module_id, sub_module_id, param_id, QVariant(QString::fromStdString(val)));
}

void HttpBridgeQt::set_parm(int module_id, int sub_module_id, int param_id, const std::vector<uint8_t> &val)
{
	//set_binary_parm_dispatcher(module_id, sub_module_id, param_id, val);
	
	// Convert vector to Qt's native QByteArray container
	QByteArray qtByteArray(reinterpret_cast<const char *>(val.data()), static_cast<int>(val.size()));
	
	emit parameterUpdated(module_id, sub_module_id, param_id, QVariant(qtByteArray));
}

// ==========================================
//          GETTER IMPLEMENTATIONS
// ==========================================
void HttpBridgeQt::get_parm(int module_id, int sub_module_id, int param_id, int &val)
{
	// Your C++ lib writes into 'val' here
	val = 42; // Placeholder
}

void HttpBridgeQt::get_parm(int module_id, int sub_module_id, int param_id, float &val)
{
	// Your C++ lib writes into 'val' here
	val = 3.14f; // Placeholder
}

void HttpBridgeQt::get_parm(int module_id, int sub_module_id, int param_id, bool &val)
{
	// Your C++ lib writes into 'val' here
	val = true; // Placeholder
}

void HttpBridgeQt::get_parm(int module_id, int sub_module_id, int param_id, std::string &val)
{
	// Your C++ lib writes into 'val' here
	val = "Hello From Lib"; // Placeholder
}

void HttpBridgeQt::get_parm(int module_id, int sub_module_id, int param_id, std::vector<uint8_t> &val)
{
	// CALL YOUR PURE C++ LIBRARY HERE
	// Example: Populate the reference 'val' with data from your .a file
	// val = my_library_get_byte_function(module_id, sub_module_id, param_id);

	// Placeholder payload for testing: [0xDE, 0xAD, 0xBE, 0xEF, 0x12]
	val = {0xDE, 0xAD, 0xBE, 0xEF, 0x18};
}

// ==========================================
//          HTTP ROUTING ROUTINES
// ==========================================
void HttpBridgeQt::setupRoutes()
{
	// --- POST: /set_param ---
	m_server.Post("/set_param", [this](const httplib::Request &req, httplib::Response &res) {
		try
		{
			auto inputJson = nlohmann::json::parse(req.body);
			int mod = inputJson.at("module_id").get<int>();
			int sub = inputJson.at("sub_module_id").get<int>();
			int param = inputJson.at("param_id").get<int>();
			auto valField = inputJson.at("val");

			if (valField.is_number_integer())
			{
				set_parm(mod, sub, param, valField.get<int>());
			}
			else if (valField.is_number_float())
			{
				set_parm(mod, sub, param, valField.get<float>());
			}
			else if (valField.is_boolean())
			{
				set_parm(mod, sub, param, valField.get<bool>());
			}
			else if (valField.is_string())
			{
				std::string rawStr = valField.get<std::string>();

				// 1. Check if the string matches Base64 structural guidelines
				if (is_valid_base64(rawStr))
				{
					// Use our custom native decoder to unpack the byte stream
					std::vector<uint8_t> binaryData = decode_base64(rawStr);

					// If the decoded payload is completely empty, default treat it as plain text
					if (!binaryData.empty())
					{
						set_parm(mod, sub, param, binaryData);
					}
					else
					{
						set_parm(mod, sub, param, rawStr);
					}
				}
				else
				{
					// 2. Not a Base64 string format. Route directly as plain text.
					set_parm(mod, sub, param, rawStr);
				}
			}

			// CRITICAL FIX: Add this line to allow browser connections
			res.set_header("Access-Control-Allow-Origin", "*");

			res.status = 200;
			res.set_content(nlohmann::json{{"status", "success"}}.dump(), "application/json");
		}
		catch (const std::exception &e)
		{
			res.set_header("Access-Control-Allow-Origin", "*"); // Add here too
			res.status = 400;
			res.set_content(nlohmann::json{{"status", "error"}, {"message", e.what()}}.dump(), "application/json");
		}
	});

	// --- POST: /get_param ---
	m_server.Post("/get_param", [this](const httplib::Request &req, httplib::Response &res) {
		try
		{
			auto inputJson = nlohmann::json::parse(req.body);
			int mod = inputJson.at("module_id").get<int>();
			int sub = inputJson.at("sub_module_id").get<int>();
			int param = inputJson.at("param_id").get<int>();
			std::string requestedType = inputJson.value("type", "int");

			nlohmann::json outputJson;
			outputJson["status"] = "success";

			if (requestedType == "int")
			{
				int val;
				get_parm(mod, sub, param, val);
				outputJson["val"] = val;
			}
			else if (requestedType == "float")
			{
				float val;
				get_parm(mod, sub, param, val);
				outputJson["val"] = val;
			}
			else if (requestedType == "bool")
			{
				bool val;
				get_parm(mod, sub, param, val);
				outputJson["val"] = val;
			}
			else if (requestedType == "string")
			{
				std::string val;
				get_parm(mod, sub, param, val);
				outputJson["val"] = val;
			}
			// CRITICAL FIX: Handle the explicit byte array request configuration
			else if (requestedType == "byte[]" || requestedType == "binary")
			{
				std::vector<uint8_t> binaryVal;

				// Call your new binary getter overload
				get_parm(mod, sub, param, binaryVal);

				// Encode the raw vector into a safe string layout
				outputJson["val"] = encode_base64(binaryVal);
			}
			else
			{
				throw std::runtime_error("Unknown data type requested");
			}

			res.set_header("Access-Control-Allow-Origin", "*");
			res.status = 200;
			res.set_content(outputJson.dump(), "application/json");
		}
		catch (const std::exception &e)
		{
			res.set_header("Access-Control-Allow-Origin", "*");
			res.status = 400;
			res.set_content(nlohmann::json{{"status", "error"}, {"message", e.what()}}.dump(), "application/json");
		}
	});

	// Add this to handle browser security handshake checks automatically
	m_server.Options(R"(.*)", [](const httplib::Request &req, httplib::Response &res) {
		res.set_header("Access-Control-Allow-Origin", "*");
		res.set_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
		res.set_header("Access-Control-Allow-Headers", "Content-Type");
		res.status = 200;
	});
}

void HttpBridgeQt::startServer(const std::string &host, int port)
{
	if (m_isRunning)
		return;
	m_isRunning = true;
	QtConcurrent::run([this, host, port]() {
		if (!m_server.listen(host.c_str(), port))
		{
			m_isRunning = false;
		}
	});
}

void HttpBridgeQt::stopServer()
{
	if (m_isRunning)
	{
		m_server.stop();
		m_isRunning = false;
	}
}

//void HttpBridgeQt::set_float_parm_dispatcher(int module_id, int sub_module_id, int param_id, float val)
//{
//}

//void HttpBridgeQt::set_bool_parm_dispatcher(int module_id, int sub_module_id, int param_id, bool val)
//{
//}

//void HttpBridgeQt::set_string_parm_dispatcher(int module_id, int sub_module_id, int param_id, const std::string &val)
//{
//}
