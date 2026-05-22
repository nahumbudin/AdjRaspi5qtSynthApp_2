/**
 * @file		Dialog_PADsynthesizer.h
 *	@author		Nahum Budin
 *	@date		10-May-2026
 *	@version	1.0
 *
 *	@brief		Adj PAD Synthesizer control dialog
 *
 */

#pragma once

#include <QDialog>
#include <QLabel>
#include <QThread>

#include <qcustomplot.h>

#include "libAdjRaspi5SynthAPI.h"

namespace Ui
{
	class Dialog_PADsynthesizer;
}

class Dialog_PADsynthesizer : public QDialog
{
	Q_OBJECT

  public:
	static Dialog_PADsynthesizer *get_instance(QWidget *parent = 0);

	~Dialog_PADsynthesizer();

	// Called from callback - thread-safe, just emits signal
	void control_box_event_received(int evnt, uint16_t val);

  signals:
	// Signal emitted when control box event is received (thread-safe)
	void control_box_event_signal(int evnt, uint16_t val);

  public slots:
	void closeEvent(QCloseEvent *event);
	virtual void update_gui(); // Called by a Timer

  private slots:
	// Slot that handles the actual UI update (runs in GUI thread)
	void handle_control_box_event(int evnt, uint16_t val);

	void on_dialog_close();

	void on_preset_file_loaded(const QString &s);
	void on_preset_file_saved(const QString &s);

	void on_detune_octave_combobox_changed(int val);
	void on_detune_semitones_combobox_changed(int val);
	void on_detune_cents_combobox_changed(int val);
	void on_send_filter1_dial_changed(int val);
	void on_send_filter2_dial_changed(int val);
		
	void on_mod_lfo_level_dial_changed(int val);
	void on_mod_lfo_frequency_dial_changed(int val);
	void on_mod_lfo_symmetry_dial_changed(int val);
	void on_mod_lfo_waveform_combobox_changed(int val);

	void on_mod_env_level_dial_changed(int val);
	void on_mod_env_attack_slider_changed(int val);
	void on_mod_env_decay_slider_changed(int val);
	void on_mod_env_sustain_slider_changed(int val);
	void on_mod_env_release_slider_changed(int val);

	void on_quality_combobox_changed(int val);
	void on_base_note_combobox_changed(int val);
	void on_base_width_slider_changed(int val);
	void on_shape_combobox_changed(int val);
	void on_shape_cutoff_combobox_changed(int val);
	void on_generate_pushbutton_clicked();

	void on_harmony1_level_slider_changed(int val);
	void on_harmony2_level_slider_changed(int val);
	void on_harmony3_level_slider_changed(int val);
	void on_harmony4_level_slider_changed(int val);
	void on_harmony5_level_slider_changed(int val);
	void on_harmony6_level_slider_changed(int val);
	void on_harmony7_level_slider_changed(int val);
	void on_harmony8_level_slider_changed(int val);
	void on_harmony9_level_slider_changed(int val);
	void on_harmony10_level_slider_changed(int val);

	void on_harmonies_detune_slider_changed(int val);

  private slots:

	void on_presets_open_pushbutton_clicked();
	void on_presets_save_pushbutton_clicked();

  private:
	explicit Dialog_PADsynthesizer(QWidget *parent = 0);

	void start_update_timer(int interval);

	void init_gui_elements();

	void set_signal_slots_connections();

	void set_adsr_plot_widget_points();
	void refresh_adsr_curve_view(QCustomPlot *adsr_plot);

	void pad_setup_profile_plot(QCustomPlot *profilePlot);
	void pad_setup_spectrum_plot(QCustomPlot *spectrumPlot);

	void pad_replot_profile();
	void pad_replot_spectrum();

	Ui::Dialog_PADsynthesizer *ui;

	static Dialog_PADsynthesizer *dialog_pad_synthesizer_instance;

	int adsr_curve_max_attack;
	int adsr_curve_max_decay;
	int adsr_curve_max_sustain;
	int adsr_curve_max_release;
	int adsr_plot_length;

	int adsr_curve_attack_end_point;
	int adsr_curve_decay_end_point;
	int adsr_curve_sustain_end_point;
	int adsr_curve_release_end_point;

	int adsr_view_widget_attack;
	int adsr_view_widget_decay;
	int adsr_view_widget_sustain;
	int adsr_view_widget_release;
	
	bool update_adsr_plot = false;
	bool update_profile_plot = false;
	bool update_spectrum_plot = false;
	bool update_spectrum_params = false;

	int tune_octave = 0;
	int tune_semitones = 0;
	int tune_cents = 0;
	int send_filter_1_level = 0;
	int send_filter_2_level = 0;

	int amp_mod_lfo_level = 0;
	int amp_mod_lfo_rate = 0;
	int amp_mod_lfo_symetry = 50;
	int amp_mod_waveform = 0;
	
	int amp_mod_adsr_level = 0;
	int amp_mod_adsr_attack = 10;
	int amp_mod_adsr_decay = 10;
	int amp_mod_adsr_sustain = 90;
	int amp_mod_adsr_release = 10;
	

	int quality = 0;
	int base_note = 0;
	int shape = 0;
	int shape_cutoff = 0;

	int base_width = 1;

	int harmony_1_level = 100;
	int harmony_2_level = 0;
	int harmony_3_level = 30;
	int harmony_4_level = 0;
	int harmony_5_level = 0;
	int harmony_6_level = 0;
	int harmony_7_level = 0;
	int harmony_8_level = 0;
	int harmony_9_level = 0;
	int harmony_10_level = 0;
	int harmonies_detune = 0;

	func_ptr_void_void_t close_event_callback_ptr;

	QString last_pad_synth_preset_directory = "";
	QString last_pad_synth_preset_load_file = "";
	QString last_pad_synth_preset_save_file = "";

	QList<QString> string_pad_qualities_list;
	QList<QString> string_pad_base_notes_list;
	QList<QString> string_pad_shapes_list;
	QList<QString> string_pad_shape_cutoffs_list;
	QList<QString> string_waveforms_list;
};

class LoadPADsynthesizerPresetFileThread : public QThread
{
	Q_OBJECT
	void run();

  signals:
	void loadPresetFileDone(const QString &s);
};

class SavePADsynthesizerPresetFileThread : public QThread
{
	Q_OBJECT
	void run();

  signals:
	void savePresetFileDone(const QString &s);
};