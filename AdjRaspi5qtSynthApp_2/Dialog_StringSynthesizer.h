/**
 * @file		Dialog_StringSynthesizer.h
 *	@author		Nahum Budin
 *	@date		1-May-2026
 *	@version	1.0
 *
 *	@brief		Adj String Synthesizer (KPS) control dialog
 *
 */

#pragma once

#include <QDialog>
#include <QLabel>
#include <QThread>

#include "libAdjRaspi5SynthAPI.h"


namespace Ui
{
	class Dialog_StringSynthesizer;
}

class Dialog_StringSynthesizer : public QDialog
{
	Q_OBJECT

  public:
	static Dialog_StringSynthesizer *get_instance(QWidget *parent = 0);

	~Dialog_StringSynthesizer();

	void control_box_ui_update_callback(int evnt, uint16_t val);

  public slots:
	void closeEvent(QCloseEvent *event);
	virtual void update_gui(); // Called by a Timer

  protected slots:

	void on_dialog_close();

	void on_preset_file_loaded(const QString &s);
	void on_preset_file_saved(const QString &s);

	void on_karplus_excitation_waveform_combobox_changed(int val);
	void on_karplus_excitation_waveform_variations_slider_changed(int val);
	void on_karplus_string_damping_slider_changed(int val);
	void on_karplus_string_damping_variation_slider_changed(int val);
	void on_karplus_string_damping_calc_mode_combobox_hanged(int val);
	void on_karplus_pluck_damping_slider_changed(int val);
	void on_karplus_pluck_damping_variation_slider_changed(int val);
	void on_karplus_on_decay_slider_changed(int val);
	void on_karplus_off_decay_slider_changed(int val);
	void on_karplus_character_variations_slider_changed(int val);
	void on_karplus_send_filter1_dial_changed(int val);
	void on_karplus_send_filter2_dial_changed(int val);
	void on_karplus_tune_octave_combobox_changed(int val);
	void on_karplus_tune_semitones_combobox_changed(int val);

	void on_karplus_distortion_enabled_checkbox_changed(bool en);
	void on_karplus_distortion_autogain_enabled_checkbox_changed(bool en);
	
	void on_karplus_distortion_drive_dial_changed(int val);
	void on_karplus_distortion_range_dial_changed(int val);
	void on_karplus_distortion_blend_dial_changed(int val);

  private slots:

	void on_presets_open_pushbutton_clicked();
	void on_presets_save_pushbutton_clicked();

  private:
	explicit Dialog_StringSynthesizer(QWidget *parent = 0);

	void start_update_timer(int interval);

	void init_gui_elements();

	void set_signal_slots_connections();

	Ui::Dialog_StringSynthesizer *ui;

	static Dialog_StringSynthesizer *dialog_string_synthesizer_instance;

	func_ptr_void_void_t close_event_callback_ptr;

	int kps_excitation_waveform = _KARPLUS_STRONG_EXCITATION_WHITE_NOISE;
	int kps_string_dump_calculation_mode = _KARPLUS_STRONG_STRING_DAMPING_CALC_DIRECT;
	int kps_waveform_variations = 0;
	int kps_string_damping = 0;
	int kps_string_damping_variations = 0;
	int kps_pluck_damping = 0;
	int kps_pluck_damping_variations = 0;
	int kps_on_decay = 0;
	int kps_off_decay = 0;
	int kps_character_variations = 0;
	int kps_send_filter_1_level = 0;
	int kps_send_filter_2_level = 0;
	int kps_tune_octave = 0;
	int kps_tune_semitones = 0;
	int kps_distortion_level = 0;
	int kps_distortion_range = 0;
	int kps_distortion_blend = 0;
	int kps_distortion_enabled = 0;
	int kps_autogain_enabled = 0;

	QList<QString> string_karplus_excitation_waveform_list;
	QList<QString> string_karplus_string_damping_calc_mode_list;

	QString last_string_synth_preset_directory = "";
	QString last_string_synth_preset_load_file = "";
	QString last_string_synth_preset_save_file = "";
};

class LoadStringSynthesizerPresetFileThread : public QThread
{
	Q_OBJECT
	void run();

  signals:
	void loadPresetFileDone(const QString &s);
};

class SaveStringSynthesizerPresetFileThread : public QThread
{
	Q_OBJECT
	void run();

  signals:
	void savePresetFileDone(const QString &s);
};
