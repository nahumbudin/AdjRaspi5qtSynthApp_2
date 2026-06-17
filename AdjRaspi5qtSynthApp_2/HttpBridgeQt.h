/**
 * @file		HttpBridgeQt.h
 *	@author		Nahum Budin
 *	@date		14-June-2026
 *	@version	1.0
 *
 *	@brief		HTTP Server used for REST Api.
 *
 */

#pragma once

#include <QObject>
#include <QThread>

#include <vector>
#include <cstdint>

// The specific headers from your previous implementation
#include "httplib.h"
#include "json.hpp"

#include "libAdjRaspi5SynthAPI.h"

class HttpBridgeQt : public QObject
{
	Q_OBJECT

  public:
	explicit HttpBridgeQt(QObject *parent = nullptr);
	~HttpBridgeQt();

	// Starts the httplib server loop inside a separate thread
	void startServer(const std::string &host = "0.0.0.0", int port = 8080);
	void stopServer();

	void set_parm(int module_id, int sub_module_id, int param_id, int val);
	void set_parm(int module_id, int sub_module_id, int param_id, float val);
	void set_parm(int module_id, int sub_module_id, int param_id, bool val);
	void set_parm(int module_id, int sub_module_id, int param_id, const std::string &val);
	void set_parm(int module_id, int sub_module_id, int param_id, const std::vector<uint8_t> &val);

	void get_parm(int module_id, int sub_module_id, int param_id, int &val);
	void get_parm(int module_id, int sub_module_id, int param_id, float &val);
	void get_parm(int module_id, int sub_module_id, int param_id, bool &val);
	void get_parm(int module_id, int sub_module_id, int param_id, std::string &val);
	void get_parm(int module_id, int sub_module_id, int param_id, std::vector<uint8_t> &val);

  signals:
	// This signal will safely pass data back to your main Qt application loop
	void libraryUpdated(int result, const QString &statusMessage);

	void parameterUpdated(int module_id, int sub_module_id, int param_id, const QVariant &val);

  private:
	httplib::Server m_server;
	bool m_isRunning;

	// The core endpoint processing logic
	void setupRoutes();

	//void set_int_parm_dispatcher(int module_id, int sub_module_id, int param_id, int val);
	//void set_float_parm_dispatcher(int module_id, int sub_module_id, int param_id, float val);
	//void set_bool_parm_dispatcher(int module_id, int sub_module_id, int param_id, bool val);
	//void set_string_parm_dispatcher(int module_id, int sub_module_id, int param_id, const std::string &val);
	//void set_binary_parm_dispatcher(int module_id, int sub_module_id, int param_id, const std::vector<uint8_t> &val);
	
	
};


