/**
 * @file		Dialog_HTTPserver.h
 *	@author		Nahum Budin
 *	@date		14-June-2026
 *	@version	1.0
 *
 *	@brief		Control the HTTP Server used for REST Api.
 *
 */

#pragma once

#include <QDialog>

namespace Ui
{
	class Dialog_HTTPserver;
}

class Dialog_HTTPserver : public QDialog
{
	Q_OBJECT

  public:
	
	~Dialog_HTTPserver() = default;

	static Dialog_HTTPserver *get_instance(QWidget *parent = nullptr);

	void update_status_display(int mod, int sub, int param, const QVariant &val);

  private slots:
	void on_start_stop_button_clicked();
	void on_clear_button_clicked();

  private:
	explicit Dialog_HTTPserver(QWidget *parent = nullptr);
	
	Ui::Dialog_HTTPserver *ui;
	static Dialog_HTTPserver *dialog_http_server_instance;

	bool server_is_running = false;

	QString update_log;
};
