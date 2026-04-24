/**
 * @file		Dialog_HammondOrgan.h
 *	@author		Nahum Budin
 *	@date		19-Apr-2026
 *	@version	1.0
 *
 *	@brief		Adj Hammond Organ control dialog
 *
 */

#pragma once

#include <QDialog>
#include <QLabel>

#include "libAdjRaspi5SynthAPI.h"

#include "CustomDrawbar.h"

namespace Ui
{
	class Dialog_HammondOrgan;
}

class Dialog_HammondOrgan : public QDialog
{
	Q_OBJECT

  public:
	static Dialog_HammondOrgan *get_instance(QWidget *parent = 0);

	~Dialog_HammondOrgan();

	void control_box_ui_update_callback(int evnt, uint16_t val);

  protected:
	void timerEvent(QTimerEvent *event);

  public slots:
	void closeEvent(QCloseEvent *event);
	virtual void update_gui(); // Called by a Timer

  protected slots:

	void on_dialog_close();

	void on_send_filter_1_dial_changed(int val);
	void on_send_filter_2_dial_changed(int val);

	void on_leslie_speaker_speed_dial_changed(int val);
	void on_leslie_speaker_level_dial_changed(int val);

	void on_tune_octave_combobox_changed(int val);
	void on_tune_semitones_combobox_changed(int val);
	void on_tune_cents_combobox_changed(int val);

	void on_sqare_enable_changed(bool en);
	
	void on_level_1_slider_changed(int val);
	void on_level_2_slider_changed(int val);
	void on_level_3_slider_changed(int val);
	void on_level_4_slider_changed(int val);
	void on_level_5_slider_changed(int val);
	void on_level_6_slider_changed(int val);
	void on_level_7_slider_changed(int val);
	void on_level_8_slider_changed(int val);
	void on_level_9_slider_changed(int val);

	void on_percussion_mode_combobox_changed(int val);

	void on_presets_open_pushbutton_clicked();

  private:
	explicit Dialog_HammondOrgan(QWidget *parent = 0);

	void start_update_timer(int interval);

	void init_gui_elements();

	void set_signal_slots_connections();

	Ui::Dialog_HammondOrgan *ui;

	static Dialog_HammondOrgan *dialog_hammond_organ_instance;

	func_ptr_void_void_t close_event_callback_ptr;

	QList<QString> string_unison_labels_hammond;
	QList<QString> string_hammond_modes_list;

	CustomDrawbar *bar_level_sliders[9];
	QLabel *bar_level_labels[9];

	QString last_hammond_preset_directory;
	QString last_hammond_preset_file;
};