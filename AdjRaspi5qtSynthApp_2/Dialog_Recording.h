/**
 * @file		Dialog_Recording
 *	@author		Nahum Budin
 *	@date		12-Jun-2026
 *	@version	1.0
 *					1. 1st. version
 *
 *	@brief		Modular Synthesizer MP3 Files Recording Control
 *
 *	@History:
 *
 */

#pragma once

#include <QDialog>

#include "../LibAPI/audio.h"

namespace Ui
{
	class Dialog_Recording;
}

class Dialog_Recording : public QDialog
{
	Q_OBJECT

  public:
	~Dialog_Recording();
	static Dialog_Recording *get_instance(QWidget *parent = 0);

	void control_box_ui_update_callback(int evnt, uint16_t val);

  public slots:
	void closeEvent(QCloseEvent *event);

	virtual void timerEvent(); // Called by a Timer

  protected slots:
	void on_start_recording_button_clicked();
	void on_stop_recording_button_clicked();

	void on_recording_mode_combo_changed(int val);

  private:
	explicit Dialog_Recording(QWidget *parent = 0);
	Ui::Dialog_Recording *ui;
	static Dialog_Recording *dialog_recording_instance;

	void start_update_timer(int interval);
	void update_recording_time_display();

	QString last_recording_directory = "";
	QString last_recording_file_name = "";

	QList<QString> string_recording_modes_list;

	int recording_time_seconds = 0;
	int recording_mode = _RECORDING_MODE_STEREO;
};


