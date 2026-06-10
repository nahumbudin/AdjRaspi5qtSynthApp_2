/**
 * @file		Dialog_MSOsynthesizer.h
 *	@author		Nahum Budin
 *	@date		29-May-2026
 *	@version	1.0
 *
 *	Note - PWM or Symmetry Modulation is not implemented in the current version.
 *
 *	@brief		Adj MSO Synthesizer control dialog
 *
 *	@History
 *
 */

#pragma once

#include <QDialog>
#include <QLabel>
#include <QThread>

#include "QCustomPlot.h"

#include "libAdjRaspi5SynthAPI.h"

namespace Ui
{
	class Dialog_MSOsynthesizer;
}

class Dialog_MSOsynthesizer : public QDialog
{
	Q_OBJECT

  public:
	static Dialog_MSOsynthesizer *get_instance(QWidget *parent = 0);

	~Dialog_MSOsynthesizer();

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
	void showEvent(QShowEvent *event);

	virtual void update_gui(); // Called by a Timer

  protected slots:

	void on_dialog_close();

	void on_send_filter_dial_changed(int val);

	void on_detune_octave_combobox_changed(int val);
	void on_detune_semitones_combobox_changed(int val);
	void on_detune_cents_combobox_changed(int val);

	void on_preset_file_loaded(const QString &s);
	void on_preset_file_saved(const QString &s);

	void on_amp_mod_env_level_dial_changed(int val);
	void on_amp_env_attack_slider_changed(int val);
	void on_amp_env_decay_slider_changed(int val);
	void on_amp_env_sustain_slider_changed(int val);
	void on_amp_env_release_slider_changed(int val);

	void on_amp_mod_lfo_level_dial_changed(int val);
	void on_amp_mod_lfo_rate_dial_changed(int val);
	void on_amp_mod_lfo_symmetry_dial_changed(int val);
	void on_amp_mod_lfo_waveform_combobox_changed(int val);

	/*
	void on_sym_mod_env_level_dial_changed(int val);
	void on_sym_env_attack_slider_changed(int val);
	void on_sym_env_decay_slider_changed(int val);
	void on_sym_env_sustain_slider_changed(int val);
	void on_sym_env_release_slider_changed(int val);

	void on_sym_mod_lfo_level_dial_changed(int val);
	void on_sym_mod_lfo_rate_dial_changed(int val);
	void on_sym_mod_lfo_symmetry_dial_changed(int val);
	void on_sym_mod_lfo_waveform_combobox_changed(int val);
	*/
	
	void on_freq_mod_env_level_dial_changed(int val);
	void on_freq_env_attack_slider_changed(int val);
	void on_freq_env_decay_slider_changed(int val);
	void on_freq_env_sustain_slider_changed(int val);
	void on_freq_env_release_slider_changed(int val);
	
	
	void on_freq_mod_lfo_level_dial_changed(int val);
	void on_freq_mod_lfo_rate_dial_changed(int val);
	void on_freq_mod_lfo_symmetry_dial_changed(int val);
	void on_freq_mod_lfo_waveform_combobox_changed(int val);

	void on_point_a_slider_moved(int val);
	void on_point_b_slider_moved(int val);
	void on_point_c_slider_moved(int val);
	void on_point_d_slider_moved(int val);
	void on_point_e_slider_moved(int val);
	void on_point_f_slider_moved(int val);
	void on_symetry_slider_changed(int val);
	void on_preset_combobox_changed(int val);


	void on_filter_freq_dial_changed(int val);
	void on_filter_q_dial_changed(int val);
	void on_filter_octave_dial_changed(int val);
	void on_filter_kbd_track_dial_changed(int val);
	void on_filter_band_combo_hanged(int val);
	
	void on_filter_freq_mod_level_lfo_dial_changed(int val);
	void on_filter_freq_mod_lfo_waveform_combo_changed(int val);
	void on_filter_freq_mod_lfo_rate_dial_changed(int val);
	void on_filter_freq_mod_lfo_symmetry_dial_changed(int val);

	void on_filter_freq_mod_env_level_dial_changed(int val);
	void on_filter_freq_mod_env_attack_slider_changed(int val);
	void on_filter_freq_mod_env_decay_slider_changed(int val);
	void on_filter_freq_mod_env_sustain_slider_changed(int val);
	void on_filter_freq_mod_env_release_slider_changed(int val);

  private slots:

	void on_presets_open_pushbutton_clicked();
	void on_presets_save_pushbutton_clicked();
	
	

  private:
	explicit Dialog_MSOsynthesizer(QWidget *parent = 0);

	void start_update_timer(int interval);

	void init_gui_elements();

	void set_signal_slots_connections();
	
	void set_preset_positions(const int pos[]);
	void handle_preset_change(int newPres);
	void setup_plot(QCustomPlot *custom_plot);
	void update_waveform_plot();

	void set_adsr_plot_widget_points(int env_id);
	void refresh_adsr_curve_view(int env_id, QCustomPlot *adsr_plot);

	Ui::Dialog_MSOsynthesizer *ui;

	static Dialog_MSOsynthesizer *dialog_msosynthesizer_instance;

	func_ptr_void_void_t close_event_callback_ptr;

	int adsr_attack[4];
	int adsr_decay[4];
	int adsr_sustain[4];
	int adsr_release[4];

	int adsr_curve_max_attack;
	int adsr_curve_max_decay;
	int adsr_curve_max_sustain;
	int adsr_curve_max_release;
	int adsr_plot_length;

	int adsr_curve_attack_end_point;
	int adsr_curve_decay_end_point;
	int adsr_curve_sustain_end_point;
	int adsr_curve_release_end_point;

	QString last_mso_synth_preset_directory = "";
	QString last_mso_synth_preset_load_file = "";
	QString last_mso_synth_preset_save_file = "";

	QList<QString> string_waveforms_list;

	QList<QString> string_presets_list;

	QList<QString> string_filters_bands;

	bool update_mso_synth_waveform_plot = true;

	std::atomic<bool> replot_waveform;


	std::atomic<bool> update_amp_mod_adsr_plot;
	std::atomic<bool> update_sym_mod_adsr_plot;
	std::atomic<bool> update_freq_mod_adsr_plot;
	std::atomic<bool> update_filter_freq_mod_adsr_plot;
};

class LoadMSOSynthesizerPresetFileThread : public QThread
{
	Q_OBJECT
	void run();

  signals:
	void loadPresetFileDone(const QString &s);
};

class SaveMSOSynthesizerPresetFileThread : public QThread
{
	Q_OBJECT
	void run();

  signals:
	void savePresetFileDone(const QString &s);
};
