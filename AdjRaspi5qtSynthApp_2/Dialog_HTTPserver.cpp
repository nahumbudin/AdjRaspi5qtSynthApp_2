/**
 * @file		Dialog_HTTPserver.cpp
 *	@author		Nahum Budin
 *	@date		14-June-2026
 *	@version	1.0
 *
 *	@brief		Control the HTTP Server used for REST Api.
 *
 */

#include <QTime>

#include "Dialog_HTTPserver.h".cmake/
#include "ui_Dialog_HTTPserver.h"

#include "Defs.h"
#include "utils.h"
#include "http.h"

Dialog_HTTPserver *Dialog_HTTPserver::dialog_http_server_instance = nullptr;

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdint>

void handle_incoming_parameters(int mod, int sub, int param, const char *type, const uint8_t *data, int data_len)
{
	// Ensure the visual screen dialog object instance is open and valid
	if (!Dialog_HTTPserver::get_instance())
		return;

	QString typeStr = QString::fromUtf8(type);
	QVariant parsedVariant;

	// Convert the library's raw layout fields into high-level Qt containers
	if (typeStr == "int" && data_len >= sizeof(int))
	{
		parsedVariant = QVariant(*reinterpret_cast<const int *>(data));
	}
	else if (typeStr == "float" && data_len >= sizeof(float))
	{
		parsedVariant = QVariant(*reinterpret_cast<const float *>(data));
	}
	else if (typeStr == "bool" && data_len >= sizeof(bool))
	{
		parsedVariant = QVariant(*reinterpret_cast<const bool *>(data));
	}
	else if (typeStr == "byte[]" || typeStr == "binary")
	{
		// Safe conversion to a native QByteArray container inside the QVariant
		QByteArray qtBytes(reinterpret_cast<const char *>(data), data_len);
		parsedVariant = QVariant(qtBytes);
	}
	else
	{
		QString text = QString::fromUtf8(reinterpret_cast<const char *>(data), data_len);
		parsedVariant = QVariant(text);
	}

	// Safely hop from the background server thread into your specific UI thread method
	QMetaObject::invokeMethod(Dialog_HTTPserver::get_instance(), [=]() { Dialog_HTTPserver::get_instance()->update_status_display(mod, sub, param, parsedVariant); }, Qt::QueuedConnection);
}

Dialog_HTTPserver::Dialog_HTTPserver(QWidget *parent)
	: QDialog(parent), ui(new Ui::Dialog_HTTPserver)
{
	ui->setupUi(this);
	dialog_http_server_instance = this;
	
	// Prevent dialog from being deleted when closed - only hide it
	setAttribute(Qt::WA_DeleteOnClose, false);

	// Set fixed size - prevents resizing
	setFixedSize(size());
	this->setFocus(Qt::ActiveWindowFocusReason);

	ui->pushButton_HTTPserverRunStop->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->pushButton_HTTPserverRunStop->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);

	ui->pushButton_HTTPserverClearText->setFrameColor(_CONTROLS_COLOR_GREEN);
	ui->pushButton_HTTPserverClearText->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);

	ui->checkBox_HTTPserverRunning->setLedStyle(true);
	ui->checkBox_HTTPserverRunning->setReadOnly(true);
	ui->checkBox_HTTPserverRunning->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_HTTPserverRunning->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_HTTPserverRunning->setFrameColor(_CONTROLS_COLOR_GRAY);

	ui->textEdit_HTTPserverIPaddress->setReadOnly(true);
	ui->textEdit_HTTPserverIPaddress->setAlignment(Qt::AlignmentFlag::AlignCenter);
	ui->textEdit_HTTPserverIPaddress->setText(QString::fromStdString(getEthernetIP("eth0")));

	ui->textEdit_HTTPserverPort->setReadOnly(true);
	ui->textEdit_HTTPserverPort->setAlignment(Qt::AlignmentFlag::AlignCenter);
	ui->textEdit_HTTPserverPort->setText("8080");

	connect(ui->pushButton_HTTPserverRunStop,
			SIGNAL(clicked()),
			this,
			SLOT(on_start_stop_button_clicked()));

	connect(ui->pushButton_HTTPserverClearText,
			SIGNAL(clicked()),
			this,
			SLOT(on_clear_button_clicked()));

	mod_synthesizer_http_server_register_callback(handle_incoming_parameters);

	// Catch parameter mutations from the web loop to print in our status monitor
	//connect(http_bridge, 
	//		&HttpBridgeQt::parameterUpdated, 
	//		this, 
	//		&Dialog_HTTPserver::update_status_display);
}

Dialog_HTTPserver *Dialog_HTTPserver::get_instance(QWidget *parent)
{
	if (!dialog_http_server_instance)
	{
		dialog_http_server_instance = new Dialog_HTTPserver();
	}

	return dialog_http_server_instance;
}

void Dialog_HTTPserver::on_start_stop_button_clicked()
{
	if (!server_is_running)
	{
		// Not rumnnig, start the server
		ui->pushButton_HTTPserverRunStop->setText("Stop");
		ui->checkBox_HTTPserverRunning->setChecked(true);

		mod_synthesizer_http_server_start("0.0.0.0", 8080);
		server_is_running = true;
	}
	else
	{
		// Server is running, stop the server
		ui->pushButton_HTTPserverRunStop->setText("Run");
		ui->checkBox_HTTPserverRunning->setChecked(false);

		mod_synthesizer_http_server_stop();
		server_is_running = false;
	}
}

void Dialog_HTTPserver::on_clear_button_clicked()
{
	update_log.clear();

	ui->textEdit_HTTPserverMessages->setText(update_log);
}

void Dialog_HTTPserver::update_status_display(int mod, int sub, int param, const QVariant &val)
{
	QString visualValue;

	// 1. Check if the incoming variant is holding a raw Qt byte array
	if (val.userType() == QMetaType::QByteArray)
	{
		QByteArray bytes = val.toByteArray();

		// Convert the raw binary to uppercase hex blocks separated by spaces
		visualValue = "[BINARY HEX: " + bytes.toHex(' ').toUpper() + "]";
	}
	else
	{
		// 2. Fall back to your standard plain-text string representation
		visualValue = val.toString();
	}

	// 3. Your updated accumulation line using the new visualValue variable
	update_log += ("\n") + QString("[%1] Mod:%2 Sub:%3 Param:%4 -> Val: %5")
							   .arg(QTime::currentTime().toString())
							   .arg(mod)
							   .arg(sub)
							   .arg(param)
							   .arg(visualValue); // <-- Passes the formatted string or hex block here

	// 4. Limit to last 1000 lines
	QStringList lines = update_log.split('\n');
	if (lines.size() > 1000)
	{
		lines = lines.mid(lines.size() - 1000); // Keep only last 1000 lines
		update_log = lines.join('\n');
	}

	// Force your UI element (like a QLabel or QTextEdit) to render the new log string
	ui->textEdit_HTTPserverMessages->setText(update_log);

	// 5. Auto-scroll to bottom to show the latest entry
	QTextCursor cursor = ui->textEdit_HTTPserverMessages->textCursor();
	cursor.movePosition(QTextCursor::End);
	ui->textEdit_HTTPserverMessages->setTextCursor(cursor);
	ui->textEdit_HTTPserverMessages->ensureCursorVisible();
}
