/**
 * @file		Dialog_KeyboardMapper.h
 *	@author		Nahum Budin
 *	@date		8-May-2026
 *	@version	1.0
 *
 *	@brief		Adj Keyboard Mapper control dialog
 *
 */

#pragma once

#include <QDialog>
#include <QThread>

#include "libAdjRaspi5SynthAPI.h"

namespace Ui
{
	class Dialog_KeyboardMapper;
}

class Dialog_KeyboardMapper : public QDialog
{
	Q_OBJECT

  public:
	static Dialog_KeyboardMapper *get_instance(QWidget *parent = 0);

	~Dialog_KeyboardMapper();

	// Called from callback - thread-safe, just emits signal
	void control_box_event_received(int evnt, uint16_t val);

  signals:
	// Signal emitted when control box event is received (thread-safe)
	void control_box_event_signal(int evnt, uint16_t val);

  private slots:
	// Slot that handles the actual UI update (runs in GUI thread)
	void handle_control_box_event(int evnt, uint16_t val);

  public slots:
	void closeEvent(QCloseEvent *event);
	virtual void update_gui(); // Called by a Timer

  protected slots:

	void on_dialog_close();

	//void on_preset_file_loaded(const QString &s);
	//void on_preset_file_saved(const QString &s);

	void on_octave_transpose_zone_1_combobox_changed(int val);
	void on_midi_channel_zone_1_combobox_changed(int val);
	void on_octave_transpose_zone_2_combobox_changed(int val);
	void on_midi_channel_zone_2_combobox_changed(int val);
	void on_split_point_note_dial_changed(int val);
	void on_bypass_on_checkbox_changed(int state);
	

  private slots:

	//void on_presets_open_pushbutton_clicked();
	//void on_presets_save_pushbutton_clicked();

  private:
	explicit Dialog_KeyboardMapper(QWidget *parent = 0);

	void start_update_timer(int interval);

	void init_gui_elements();

	void set_signal_slots_connections();

	void update_split_point_note_text();

	QString get_note_name(int midi_note);

	Ui::Dialog_KeyboardMapper *ui;

	static Dialog_KeyboardMapper *dialog_keyboard_mapper_instance;

	func_ptr_void_void_t close_event_callback_ptr;

	int zone_1_octave_offset;
	int zone_1_midi_channel;

	int zone_2_octave_offset;
	int zone_2_midi_channel;

	int split_point_note;
	bool bypass_on;
};

class LoadKeyboardMapperPresetFileThread : public QThread
{
	Q_OBJECT
	void run();

  signals:
	void loadPresetFileDone(const QString &s);
};

class SaveKeyboardMapperPresetFileThread : public QThread
{
	Q_OBJECT
	void run();

  signals:
	void savePresetFileDone(const QString &s);
};
