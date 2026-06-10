/**
 * @file		Dialog_AnalogSynth_1900x1000.h
 *	@author		Nahum Budin
 *	@date		22-Dec-2025
 *	@version	1.0
 *					1. First version.
 *
 *	@brief		Used for controling the Analog Synthesizer instrument
 *				A single integrated 1900x1000 dialog version for large screen devices.
 *
 *	History:
 *			Based on the AdjModSynth project ver 1.1 16-Jan-2021
 *
 */

#pragma once

#include <QDialog>
#include <QSlider>
#include <QTHread>

#include "CustomDial.h"

#include "Defs.h"
#include "libAdjRaspi5SynthAPI.h"
#include "ControlWidgetsColorManager.h"

#include "qcustomplot.h"

namespace Ui
{
	class Dialog_AnalogSynth_1900x1000;
}

class Dialog_AnalogSynth_1900x1000 : public QDialog
{
	Q_OBJECT

  public:
	~Dialog_AnalogSynth_1900x1000();

	static Dialog_AnalogSynth_1900x1000 *get_instance(QWidget *parent = 0);

	static Ui::Dialog_AnalogSynth_1900x1000 *get_ui_instance();

	void update_all();

	// Called from callback - thread-safe, just emits signal
	void control_box_event_received(int evnt, uint16_t val);
	

	// Handle frame navigation
	void on_frame_changed(const QString &frame_name, int frame_index);

	void sketch_selected(int sketch, bool val = false);

	void osc1_set_unison_mode(int mode);

	static CustomComboBox *combo_lfo_waveform[_NUM_OF_LFOS];
	static CustomDial *dial_lfo_symmetry[_NUM_OF_LFOS];
	static CustomDial *dial_lfo_rate[_NUM_OF_LFOS];
	static QLineEdit *lineedit_lfo_rate[_NUM_OF_LFOS];
	static QLineEdit *lineedit_lfo_symmetry[_NUM_OF_LFOS];

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
	
protected:
	void timerEvent(QTimerEvent *event);

protected slots:
	void on_dialog_close();
	void on_panic_clicked();

	void on_tab_selected(int tab);

	void on_sketch1_selected();
	void on_sketch2_selected();
	void on_sketch3_selected();

	// ADSR and LFO flying frames
	void on_modulator_combo_box_mouse_entered(int val);
	void on_modulator_combo_box_mouse_exited(int val);

	void on_selected_adsr_attack_slider_changed(int val);
	void on_selected_adsr_decay_slider_changed(int val);
	void on_selected_adsr_sustain_slider_changed(int val);
	void on_selected_adsr_release_slider_changed(int val);

	void on_ADSR_frame_close_button_clicked();

	void on_selected_lfo_rate_dial_changed(int val);
	void on_selected_lfo_symmetry_dial_changed(int val);
	void on_selected_lfo_waveform_combo_changed(int val);
	
	void on_LFO_frame_close_button_clicked();

	void on_osc1_enable_changed(bool en);

	void on_osc1_waveform_symmetry_spinbox_changed(int val);
	void on_osc1_send_filter_1_spinbox_changed(int val);
	void on_osc1_send_filter_2_spinbox_changed(int val);
	void on_osc1_freq_mod_lfo_level_spinbox_changed(int val);
	void on_osc1_freq_mod_adsr_level_spinbox_changed(int val);
	void on_osc1_pwm_mod_lfo_level_spinbox_changed(int val);
	void on_osc1_pwm_mod_adsr_level_spinbox_changed(int val);
	void on_osc1_amp_mod_lfo_level_spinbox_changed(int val);
	void on_osc1_amp_mod_adsr_level_spinbox_changed(int val);

	void on_osc1_unison_level_1_spinbox_changed(int val);
	void on_osc1_unison_level_2_spinbox_changed(int val);
	void on_osc1_unison_level_3_spinbox_changed(int val);
	void on_osc1_unison_level_4_spinbox_changed(int val);
	void on_osc1_unison_level_5_spinbox_changed(int val);
	void on_osc1_unison_level_6_spinbox_changed(int val);
	void on_osc1_unison_level_7_spinbox_changed(int val);
	void on_osc1_unison_level_8_spinbox_changed(int val);
	void on_osc1_unison_level_9_spinbox_changed(int val);
	void on_osc1_unison_distortion_spinbox_changed(int val);
	void on_osc1_unison_detune_spinbox_changed(int val);

	void on_osc1_waveform_symmetry_slider_cahanged(int val);

	void on_osc1_unison_sqare_enable_changed(bool en);
	void on_osc1_unison_level_1_slider_changed(int val);
	void on_osc1_unison_level_2_slider_changed(int val);
	void on_osc1_unison_level_3_slider_changed(int val);
	void on_osc1_unison_level_4_slider_changed(int val);
	void on_osc1_unison_level_5_slider_changed(int val);
	void on_osc1_unison_level_6_slider_changed(int val);
	void on_osc1_unison_level_7_slider_changed(int val);
	void on_osc1_unison_level_8_slider_changed(int val);
	void on_osc1_unison_level_9_slider_changed(int val);
	void on_osc1_unison_distortion_slider_changed(int val);
	void on_osc1_unison_detune_slider_changed(int val);

	void on_osc1_send_filter_1_dial_changed(int val);
	void on_osc1_send_filter_2_dial_changed(int val);
	void on_osc1_freq_mod_lfo_level_dial_changed(int val);
	void on_osc1_freq_mod_adsr_level_dial_changed(int val);
	void on_osc1_pwm_mod_lfo_level_dial_changed(int val);
	void on_osc1_pwm_mod_adsr_level_dial_changed(int val);
	void on_osc1_amp_mod_lfo_level_dial_changed(int val);
	void on_osc1_amp_mod_adsr_level_dial_changed(int val);

	void on_osc1_waveform_combobox_changed(int val);
	void on_osc1_tune_octave_combobox_changed(int val);
	void on_osc1_tune_semitones_combobox_changed(int val);
	void on_osc1_tune_cents_combobox_changed(int val);
	void on_osc1_freq_mod_lfo_combobox_changed(int val);
	void on_osc1_freq_mod_adsr_combobox_changed(int val);
	void on_osc1_pwm_mod_lfo_combobox_changed(int val);
	void on_osc1_pwm_mod_adsr_combobox_changed(int val);
	void on_osc1_amp_mod_lfo_combobox_changed(int val);
	void on_osc1_amp_mod_adsr_combobox_changed(int val);
	void on_osc1_hammond_percussion_mode_combobox_changed(int val);
	void on_osc1_unison_mode_combobox_changed(int val);

	void on_osc2_enable_changed(bool en);

	void on_osc2_waveform_symmetry_spinbox_changed(int val);
	void on_osc2_send_filter_1_spinbox_changed(int val);
	void on_osc2_send_filter_2_spinbox_changed(int val);
	void on_osc2_freq_mod_lfo_level_spinbox_changed(int val);
	void on_osc2_freq_mod_adsr_level_spinbox_changed(int val);
	void on_osc2_pwm_mod_lfo_level_spinbox_changed(int val);
	void on_osc2_pwm_mod_adsr_level_spinbox_changed(int val);
	void on_osc2_amp_mod_lfo_level_spinbox_changed(int val);
	void on_osc2_amp_mod_adsr_level_spinbox_changed(int val);

	void on_osc2_send_filter_1_dial_changed(int val);
	void on_osc2_send_filter_2_dial_changed(int val);
	void on_osc2_freq_mod_lfo_level_dial_changed(int val);
	void on_osc2_freq_mod_adsr_level_dial_changed(int val);
	void on_osc2_pwm_mod_lfo_level_dial_changed(int val);
	void on_osc2_pwm_mod_adsr_level_dial_changed(int val);
	void on_osc2_amp_mod_lfo_level_dial_changed(int val);
	void on_osc2_amp_mod_adsr_level_dial_changed(int val);

	void on_osc2_waveform_symmetry_slider_cahanged(int val);

	void on_osc2_waveform_combobox_changed(int val);
	void on_osc2_tune_octave_combobox_changed(int val);
	void on_osc2_tune_semitones_combobox_changed(int val);
	void on_osc2_tune_cents_combobox_changed(int val);
	void on_osc2_freq_mod_lfo_combobox_changed(int val);
	void on_osc2_freq_mod_adsr_combobox_changed(int val);
	void on_osc2_pwm_mod_lfo_combobox_changed(int val);
	void on_osc2_pwm_mod_adsr_combobox_changed(int val);
	void on_osc2_amp_mod_lfo_combobox_changed(int val);
	void on_osc2_amp_mod_adsr_combobox_changed(int val);

	void on_osc2_sync_on_osc1_enable_changed(bool en);

	void on_noise_enable_changed(bool en);

	void on_noise_send_filter_1_spinbox_changed(int val);
	void on_noise_send_filter_2_spinbox_changed(int val);
	void on_noise_amp_mod_lfo_level_spinbox_changed(int val);
	void on_noise_amp_mod_adsr_level_spinbox_changed(int val);

	void on_noise_send_filter_1_dial_changed(int val);
	void on_noise_send_filter_2_dial_changed(int val);
	void on_noise_amp_mod_lfo_level_dial_changed(int val);
	void on_noise_amp_mod_adsr_level_dial_changed(int val);

	void on_noise_color_combobox_changed(int val);
	void on_noise_amp_mod_lfo_combobox_changed(int val);
	void on_noise_amp_mod_adsr_combobox_changed(int val);

	void on_mso_point_a_slider_moved(int val);
	void on_mso_point_b_slider_moved(int val);
	void on_mso_point_c_slider_moved(int val);
	void on_mso_point_d_slider_moved(int val);
	void on_mso_point_e_slider_moved(int val);
	void on_mso_point_f_slider_moved(int val);
	void on_mso_symetry_slider_changed(int val);

	void on_mso_detune_octave_combobox_changed(int val);
	void on_mso_detune_semitones_combobox_changed(int val);
	void on_mso_detune_cents_combobox_changed(int val);

	void on_mso_freq_mod_lfo_combobox_changed(int val);
	void on_mso_freq_mod_env_combobox_changed(int val);
	void on_mso_pwm_mod_lfo_combobox_changed(int val);
	void on_mso_pwm_mod_env_combobox_changed(int val);
	void on_mso_amp_mod_lfo_combobox_changed(int val);
	void on_mso_amp_mod_env_combobox_changed(int val);
	void on_mso_preset_combobox_changed(int val);

	void on_mso_send_filter_1_dial_changed(int val);
	void on_mso_send_filter_2_dial_changed(int val);
	void on_mso_freq_mod_lfo_level_dial_changed(int val);
	void on_mso_freq_mod_env_level_dial_changed(int val);
	void on_mso_pwm_mod_lfo_level_dial_changed(int val);
	void on_mso_pwm_mod_env_level_dial_changed(int val);
	void on_mso_amp_mod_lfo_level_dial_changed(int val);
	void on_mso_amp_mod_env_level_dial_changed(int val);

	void on_mso_enable_checkbox_changed(bool val);

	void on_karplus_excitation_waveform_combobox_changed(int val);
	void on_karplus_excitation_waveform_variations_slider_changed(int val);
	void on_karplus_string_damping_slider_changed(int val);
	void on_karplus_string_damping_variation_slider_changed(int val);
	void on_karplus_string_damping_calc_mode_combobox_hanged(int val);
	void on_karplus_pluck_damping_slider_changed(int val);
	void on_karplus_pluck_damping_variation_slider_changed(int val);
	void on_karplus_on_decay_slider_changed(int val);
	void on_karplus_off_decay_slider_changed(int val);
	void on_karplus_send_filter1_dial_changed(int val);
	void on_karplus_send_filter2_dial_changed(int val);

	void on_karplus_enable_checkbox_changed(bool val);

	void on_pad_enable_checkbox_changed(bool val);

	void on_pad_detune_octave_combobox_changed(int val);
	void on_pad_detune_semitones_combobox_changed(int val);
	void on_pad_detune_cents_combobox_changed(int val);
	void on_pad_send_filter1_dial_changed(int val);
	void on_pad_send_filter2_dial_changed(int val);
	void on_pad_freq_mod_lfo_combobox_changed(int val);
	void on_pad_freq_mod_lfo_level_dial_changed(int val);
	void on_pad_freq_mod_env_combobox_changed(int val);
	void on_pad_freq_mod_env_level_dial_changed(int val);
	void on_pad_amp_mod_lfo_combobox_changed(int val);
	void on_pad_amp_mod_lfo_level_dial_changed(int val);
	void on_pad_amp_mod_env_combobox_changed(int val);
	void on_pad_amp_mod_env_level_dial_changed(int val);

	void on_pad_quality_combobox_changed(int val);
	void on_pad_base_note_combobox_changed(int val);
	void on_pad_base_width_slider_changed(int val);
	void on_pad_shape_combobox_changed(int val);
	void on_pad_shape_cutoff_combobox_changed(int val);
	void on_pad_generate_pushbutton_clicked();

	void on_pad_harmony1_level_slider_changed(int val);
	void on_pad_harmony2_level_slider_changed(int val);
	void on_pad_harmony3_level_slider_changed(int val);
	void on_pad_harmony4_level_slider_changed(int val);
	void on_pad_harmony5_level_slider_changed(int val);
	void on_pad_harmony6_level_slider_changed(int val);
	void on_pad_harmony7_level_slider_changed(int val);
	void on_pad_harmony8_level_slider_changed(int val);
	void on_pad_harmony9_level_slider_changed(int val);
	void on_pad_harmony10_level_slider_changed(int val);

	void on_pad_harmonies_detune_slider_changed(int val);

	void on_filter1_freq_dial_changed(int val);
	void on_filter1_q_dial_changed(int val);
	void on_filter1_octave_dial_changed(int val);
	void on_filter1_kbd_track_dial_changed(int val);
	void on_filter1_band_combo_hanged(int val);
	void on_filter1_freq_mod_lfo_combo_changed(int val);
	void on_filter1_freq_mod_level_lfo_slider_changed(int val);
	void on_filter1_freq_mod_adsr_combo_changed(int val);
	void on_filter1_freq_mod_level_adsr_slider_hanged(int val);

	void on_filter2_freq_dial_changed(int val);
	void on_filter2_q_dial_changed(int val);
	void on_filter2_octave_dial_changed(int val);
	void on_filter2_kbd_track_dial_changed(int val);
	void on_filter2_band_combo_hanged(int val);
	void on_filter2_freq_mod_lfo_combo_changed(int val);
	void on_filter2_freq_mod_level_lfo_slider_changed(int val);
	void on_filter2_freq_mod_adsr_combo_changed(int val);
	void on_filter2_freq_mod_level_adsr_slider_hanged(int val);
	void on_filter2_track_filter1_checkbox_changed(bool val);

	void on_distortion1_drive_dial_changed(int val);
	void on_distortion1_range_dial_changed(int val);
	void on_distortion1_blend_dial_changed(int val);

	void on_distortion2_drive_dial_changed(int val);
	void on_distortion2_range_dial_changed(int val);
	void on_distortion2_blend_dial_changed(int val);

	void on_distortion_active_checkbox_Changed(bool val);
	void on_distortion_auto_gain_checkbox_Changed(bool val);

	void on_amp1_level_dial_hanged(int val);
	void on_amp1_pan_dial_changed(int val);
	void on_amp1_pan_mod_lfo_combo_changed(int val);
	void on_amp1_pan_mod_level_lfo_dial_changed(int val);

	void on_amp2_level_dial_hanged(int val);
	void on_amp2_pan_dial_changed(int val);
	void on_amp2_pan_mod_lfo_combo_changed(int val);
	void on_amp2_pan_mod_level_lfo_dial_changed(int val);

	void on_fixed_amp_checkbox_Changed(bool val);

	// Freeverb 3 modified
	void on_reverb_3m_enable_checkbox_hanged(bool val);
	void on_reverb_type_combobox_changed(int val);

	// Freverb
	void on_reverb_enable_checkbox_changed(bool val);
	void on_reverb_room_size_dial_changed(int val);
	void on_reverb_damp_dial_changed(int val);
	void on_reverb_wet_dial_changed(int val);
	void on_reverb_dry_dial_changed(int val);
	void on_reverb_width_dial_changed(int val);
	void on_reverb_mode_dial_changed(int val);

	void on_reverb_room_size_spinbox_changed(int val);
	void on_reverb_damp_spinbox_changed(int val);
	void on_reverb_wet_spinbox_changed(int val);
	void on_reverb_dry_spinbox_changed(int val);
	void on_reverb_width_spinbox_changed(int val);
	void on_reverb_mode_spinbox_changed(int val);

	void on_band_equilizer_band31_slider_changed(int val);
	void on_band_equilizer_band62_slider_changed(int val);
	void on_band_equilizer_band125_slider_changed(int val);
	void on_band_equilizer_band250_slider_changed(int val);
	void on_band_equilizer_band500_slider_changed(int val);
	void on_band_equilizer_band1K_slider_changed(int val);
	void on_band_equilizer_band2K_slider_changed(int val);
	void on_band_equilizer_band4K_slider_changed(int val);
	void on_band_equilizer_band8K_slider_changed(int val);
	void on_band_equilizer_band16K_slider_changed(int val);

	void on_band_equilizer_band31_spinbox_changed(int val);
	void on_band_equilizer_band62_spinbox_changed(int val);
	void on_band_equilizer_band125_spinbox_changed(int val);
	void on_band_equilizer_band250_spinbox_changed(int val);
	void on_band_equilizer_band500_spinbox_changed(int val);
	void on_band_equilizer_band1K_spinbox_changed(int val);
	void on_band_equilizer_band2K_spinbox_changed(int val);
	void on_band_equilizer_band4K_spinbox_changed(int val);
	void on_band_equilizer_band8K_spinbox_changed(int val);
	void on_band_equilizer_band16K_spinbox_changed(int val);
	
	void on_band_equilizer_band_preset_changed(int val);
	void on_band_equilizer_set_all_zero_licked(bool val);

	void on_adsr1_attack_level_slider_changed(int val);
	void on_adsr1_decay_level_slider_changed(int val);
	void on_adsr1_sustain_level_slider_changed(int val);
	void on_adsr1_release_level_slider_changed(int val);

	void on_adsr2_attack_level_slider_changed(int val);
	void on_adsr2_decay_level_slider_changed(int val);
	void on_adsr2_sustain_level_slider_changed(int val);
	void on_adsr2_release_level_slider_changed(int val);

	void on_adsr3_attack_level_slider_changed(int val);
	void on_adsr3_decay_level_slider_changed(int val);
	void on_adsr3_sustain_level_slider_changed(int val);
	void on_adsr3_release_level_slider_changed(int val);

	void on_adsr4_attack_level_slider_changed(int val);
	void on_adsr4_decay_level_slider_changed(int val);
	void on_adsr4_sustain_level_slider_changed(int val);
	void on_adsr4_release_level_slider_changed(int val);

	void on_adsr5_attack_level_slider_changed(int val);
	void on_adsr5_decay_level_slider_changed(int val);
	void on_adsr5_sustain_level_slider_changed(int val);
	void on_adsr5_release_level_slider_changed(int val);

	void on_adsr6_attack_level_slider_changed(int val);
	void on_adsr6_decay_level_slider_changed(int val);
	void on_adsr6_sustain_level_slider_changed(int val);
	void on_adsr6_release_level_slider_changed(int val);

	void on_lfo1_waveform_combo_changed(int val);
	void on_lfo1_symmetry_dial_changed(int val);
	void on_lfo1_rate_dial_changed(int val);
	
	void on_lfo2_waveform_combo_changed(int val);
	void on_lfo2_symmetry_dial_changed(int val);
	void on_lfo2_rate_dial_changed(int val);
	
	void on_lfo3_waveform_combo_changed(int val);
	void on_lfo3_symmetry_dial_changed(int val);
	void on_lfo3_rate_dial_changed(int val);
	
	void on_lfo4_waveform_combo_changed(int val);
	void on_lfo4_symmetry_dial_changed(int val);
	void on_lfo4_rate_dial_changed(int val);
	
	void on_lfo5_waveform_combo_changed(int val);
	void on_lfo5_symmetry_dial_changed(int val);
	void on_lfo5_rate_dial_changed(int val);
	
	void on_lfo6_waveform_combo_changed(int val);
	void on_lfo6_symmetry_dial_changed(int val);
	void on_lfo6_rate_dial_changed(int val);
	
	
	
	

  private:
	bool sketch1_active = true;
	bool sketch2_active = false;
	bool sketch3_active = false;
	int active_sketch = 0;

	// Used for indicating which ADSR is active and can be set.
	int active_adsr = _ENV_NONE;
	int active_adsr_attack = 0;
	int active_adsr_decay = 0;
	int active_adsr_sustain = 0;
	int active_adsr_release = 0;
	bool active_adsr_widget_showing = false;

	int active_lfo = _LFO_NONE;
	int active_lfo_waveform = _OSC_WAVEFORM_SINE;
	int active_lfo_symmetry = 50;
	int active_lfo_rate = 50;
	bool active_lfo_widget_showing = false;

	int active_tab, prev_active_tab;

	// Used for counting down ADSR/LFO frame no activity show timeout based on GUI update timer. _UPDATE_TIMER_PERIOD_MS (100ms)
	int active_adsr_frame_no_activity_counter = 0;
	int active_lfo_frame_no_activity_counter = 0;

	bool osc1_enabled = true;
	bool osc1_unison_square = false;

	int osc1_send_filter_1_level = 0;
	int osc1_send_filter_2_level = 0;

	int osc1_unison_levels[9] = {0};
	int osc_1_unison_distortion = 0;
	int osc_1_unison_detune = 0;

	int osc1_unison_mode = _OSC_UNISON_MODE_12345678;
	int osc1_hammond_percussion_mode = _HAMMOND_PERCUSION_MODE_OFF;

	int osc1_waveform = _OSC_WAVEFORM_SINE;
	int osc1_waveform_symmetry = 50;

	int osc1_tune_octave = 0;
	int osc1_tune_semitones = 0;
	int osc1_tune_cents = 0;

	int osc1_freq_mod_lfo_level = 0;
	int osc1_freq_mod_adsr_level = 0;
	int osc1_freq_mod_lfo_num = _LFO_NONE;
	int osc1_freq_mod_adsr_num = _ENV_NONE;

	int osc1_pwm_mod_lfo_level = 0;
	int osc1_pwm_mod_adsr_level = 0;
	int osc1_pwm_mod_lfo_num = _LFO_NONE;
	int osc1_pwm_mod_adsr_num = _ENV_NONE;

	int osc1_amp_mod_lfo_level = 0;
	int osc1_amp_mod_adsr_level = 0;
	int osc1_amp_mod_lfo_num = _LFO_NONE;
	int osc1_amp_mod_adsr_num = _ENV_NONE;

	bool osc2_enabled = false;

	int osc2_send_filter_1_level = 0;
	int osc2_send_filter_2_level = 0;

	int osc2_waveform = _OSC_WAVEFORM_SINE;
	int osc2_waveform_symmetry = 50;

	int osc2_tune_octave = 0;
	int osc2_tune_semitones = 0;
	int osc2_tune_cents = 0;

	int osc2_freq_mod_lfo_level = 0;
	int osc2_freq_mod_adsr_level = 0;
	int osc2_freq_mod_lfo_num = _LFO_NONE;
	int osc2_freq_mod_adsr_num = _ENV_NONE;

	int osc2_pwm_mod_lfo_level = 0;
	int osc2_pwm_mod_adsr_level = 0;
	int osc2_pwm_mod_lfo_num = _LFO_NONE;
	int osc2_pwm_mod_adsr_num = _ENV_NONE;

	int osc2_amp_mod_lfo_level = 0;
	int osc2_amp_mod_adsr_level = 0;
	int osc2_amp_mod_lfo_num = _LFO_NONE;
	int osc2_amp_mod_adsr_num = _ENV_NONE;

	bool osc_2_sync_on_osc_1 = false;

	bool noise_enabled = false;

	int noise_send_filter_1_level = 0;
	int noise_send_filter_2_level = 0;

	int noise_amp_mod_lfo_level = 0;
	int noise_amp_mod_adsr_level = 0;
	int noise_amp_mod_lfo_num = _LFO_NONE;
	int noise_amp_mod_adsr_num = _ENV_NONE;

	int noise_color = _WHITE_NOISE;

	bool mso_enabled = false;
	bool update_mso_plot = true;

	int mso_pos_a, mso_pos_b, mso_pos_c, mso_pos_d, mso_pos_e, mso_pos_f;
	int mso_symetry = 70;
	int mso_tune_octave = 0;
	int mso_tune_semitones = 0;
	int mso_tune_cents = 0;
	int mso_send_filter_1_level = 0;
	int mso_send_filter_2_level = 0;

	int mso_freq_mod_lfo_level = 0;
	int mso_freq_mod_adsr_level = 0;
	int mso_freq_mod_lfo_num = _LFO_NONE;
	int mso_freq_mod_adsr_num = _ENV_NONE;

	int mso_pwm_mod_lfo_level = 0;
	int mso_pwm_mod_adsr_level = 0;
	int mso_pwm_mod_lfo_num = _LFO_NONE;
	int mso_pwm_mod_adsr_num = _ENV_NONE;

	int mso_amp_mod_lfo_level = 0;
	int mso_amp_mod_adsr_level = 0;
	int mso_amp_mod_lfo_num = _LFO_NONE;
	int mso_amp_mod_adsr_num = _ENV_NONE;

	int mso_preset = 0;

	bool mso_replot_waveform = false;

	bool kps_enabled = false;

	int kps_excitation_waveform = _KARPLUS_STRONG_EXCITATION_WHITE_NOISE;
	int kps_string_dump_calculation_mode = _KARPLUS_STRONG_STRING_DAMPING_CALC_DIRECT;
	int kps_waveform_variations = 0;
	int kps_string_damping = 0;
	int kps_string_damping_variations = 0;
	int kps_pluck_damping = 0;
	int kps_pluck_damping_variations = 0;
	int kps_on_decay = 0;
	int kps_off_decay = 0;
	int kps_send_filter_1_level = 0;
	int kps_send_filter_2_level = 0;
	

	bool pad_enabled = false;
	bool update_profile_plot = true;
	bool update_spectrum_plot = true;

	int pad_tune_octave = 0;
	int pad_tune_semitones = 0;
	int pad_tune_cents = 0;
	int pad_send_filter_1_level = 0;
	int pad_send_filter_2_level = 0;

	int pad_freq_mod_lfo_level = 0;
	int pad_freq_mod_adsr_level = 0;
	int pad_freq_mod_lfo_num = _LFO_NONE;
	int pad_freq_mod_adsr_num = _ENV_NONE;

	int pad_amp_mod_lfo_level = 0;
	int pad_amp_mod_adsr_level = 0;
	int pad_amp_mod_lfo_num = _LFO_NONE;
	int pad_amp_mod_adsr_num = _ENV_NONE;

	int pad_quality = 0;
	int pad_base_note = 0;
	int pad_shape = 0;
	int pad_shape_cutoff = 0;

	int pad_base_width = 1;

	int pad_harmony_1_level = 100;
	int pad_harmony_2_level = 0;
	int pad_harmony_3_level = 30;
	int pad_harmony_4_level = 0;
	int pad_harmony_5_level = 0;
	int pad_harmony_6_level = 0;
	int pad_harmony_7_level = 0;
	int pad_harmony_8_level = 0;
	int pad_harmony_9_level = 0;
	int pad_harmony_10_level = 0;
	int pad_harmony_detune = 0;

	int filter1_frequency_entry = 0;
	int filter1_q_entry = 1;
	int filter1_octave_entry = 0;
	int filter1_keyboard_track = 100;
	int filter1_band = _FILTER_BAND_LPF;
	int filter1_freq_mod_lfo = 0;
	int filter1_freq_mod_lfo_level = 0;
	int filter1_freq_mod_adsr = 0;
	int filter1_freq_mod_adsr_level = 0;

	int filter2_frequency_entry = 0;
	int filter2_q_entry = 1;
	int filter2_octave_entry = 0;
	int filter2_keyboard_track = 100;
	int filter2_band = _FILTER_BAND_LPF;
	int filter2_freq_mod_lfo = 0;
	int filter2_freq_mod_lfo_level = 0;
	int filter2_freq_mod_adsr = 0;
	int filter2_freq_mod_adsr_level = 0;

	bool filter_2_follows_filter_1 = false;

	int distortion1_drive = 0;
	int distortion1_range = 0;
	int distortion1_blend = 0;

	int distortion2_drive = 0;
	int distortion2_range = 0;
	int distortion2_blend = 0;

	bool distortion_active = false;
	bool distortion_auto_gain = false;

	int amp1_level = 50;
	int amp1_pan = 50;
	int amp1_pan_mod_lfo = 0;
	int amp1_pan_mod_lfo_level = 0;

	int amp2_level = 50;
	int amp2_pan = 50;
	int amp2_pan_mod_lfo = 0;
	int amp2_pan_mod_lfo_level = 0;

	bool amp_fixed = false;

	int adsr_attack_levels[_NUM_OF_ADSRS] = { 5, 5, 5, 5, 5, 5 };
	int adsr_decay_levels[_NUM_OF_ADSRS] = { 10, 10, 10, 10, 10, 10 };
	int adsr_sustain_levels[_NUM_OF_ADSRS] = { 80, 80, 80, 80, 80, 80 };
	int adsr_release_levels[_NUM_OF_ADSRS] = { 10, 10, 10, 10, 10, 10 };

	int adsr_plot_length;

	int adsr_view_widget_attack;
	int adsr_view_widget_decay;
	int adsr_view_widget_sustain;
	int adsr_view_widget_release;

	int adsr_curve_attack_end_point;
	int adsr_curve_decay_end_point;
	int adsr_curve_sustain_end_point;
	int adsr_curve_release_end_point;

	int adsr_curve_max_attack;
	int adsr_curve_max_decay;
	int adsr_curve_max_sustain;
	int adsr_curve_max_release;

	bool update_adsr_plot[_NUM_OF_ADSRS + 1] = { false };
	int last_modified_adsr = _ENV_NONE;

	int lfo1_waveform_entry = _OSC_WAVEFORM_SINE;
	int lfo1_symmetry_entry = 50;
	int lfo1_rate_entry = 50;

	int lfo2_waveform_entry = _OSC_WAVEFORM_SINE;
	int lfo2_symmetry_entry = 50;
	int lfo2_rate_entry = 50;

	int lfo3_waveform_entry = _OSC_WAVEFORM_SINE;
	int lfo3_symmetry_entry = 50;
	int lfo3_rate_entry = 50;

	int lfo4_waveform_entry = _OSC_WAVEFORM_SINE;
	int lfo4_symmetry_entry = 50;
	int lfo4_rate_entry = 50;

	int lfo5_waveform_entry = _OSC_WAVEFORM_SINE;
	int lfo5_symmetry_entry = 50;
	int lfo5_rate_entry = 50;

	int lfo6_waveform_entry = _OSC_WAVEFORM_SINE;
	int lfo6_symmetry_entry = 50;
	int lfo6_rate_entry = 50;

	CustomVerticalSlider *vertical_sliders_adsr_attack[_NUM_OF_ADSRS];
	CustomVerticalSlider *vertical_sliders_adsr_decay[_NUM_OF_ADSRS];
	CustomVerticalSlider *vertical_sliders_adsr_sustain[_NUM_OF_ADSRS];
	CustomVerticalSlider *vertical_sliders_adsr_release[_NUM_OF_ADSRS];

	QLineEdit *lineedits_adsr_attack[_NUM_OF_ADSRS];
	QLineEdit *lineedits_adsr_decay[_NUM_OF_ADSRS];
	QLineEdit *lineedits_adsr_sustain[_NUM_OF_ADSRS];
	QLineEdit *lineedits_adsr_release[_NUM_OF_ADSRS];

	void set_analog_synth_general_signals_connections();

	void start_update_timer(int interval);
	
	int init_frame_colors(CustomFrame *frame);
	int init_dial_control_colors(CustomDial *dial);
	int init_combobox_control_colors(CustomComboBox *combobox);
	int init_horizontal_slider_control_colors(CustomHorizontalSlider *hslider);
	int init_vertical_slider_control_colors(CustomVerticalSlider *vslider);

	void set_active_adsr(int adsr);
	void set_active_adsr_attack(int attack);
	void set_active_adsr_decay(int decay);
	void set_active_adsr_sustain(int sustain);
	void set_active_adsr_release(int release);
	
	int get_active_adsr();
	int get_active_adsr_attack();
	int get_active_adsr_decay();
	int get_active_adsr_sustain();
	int get_active_adsr_release();

	void show_active_adsr_widget(bool show);

	void init_active_adsr_widget();
	void update_active_adsr_frame();

	void set_adsr_plot_widget_points(int env_id);
	void refresh_adsr_curve_view(QCustomPlot *adsr_plot);

	void init_active_lfo_widget();
	void update_active_lfo_frame();

	int init_osc1_gui();
	int init_osc2_gui();
	int init_noise_gui();
	int init_karplus_strong_gui();
	int init_mso_gui();
	int init_pad_gui();
	int init_filters_gui();
	int init_distortion_gui();
	int init_amps_gui();
	int init_reverb_gui();
	int init_equalizer_gui();
	int init_adsrs_gui();
	int init_lfos_gui();

	void set_osc1_signals_connections();

	void osc1_update();
	void osc1_set_unison_labales(QList<QString> str, uint16_t mask);
	void osc1_set_unison_labales(int mode);
	void osc1_en_dis_sliders(uint16_t mask);

	void set_osc2_signals_connections();

	void osc2_update();
	void osc2_set_unison_labales(QList<QString> str, uint16_t mask);

	void set_noise_signals_connections();
	void noise_update();

	void set_kps_signals_connections();
	void kps_update();

	void mso_update();
	void set_mso_signals_connections();
	void setup_mso_plot(QCustomPlot *custom_plot);
	void update_mso_waveform_plot();
	void mso_handle_preset_change(int newPres);
	void mso_set_preset_positions(const int pos[]);

	void set_pad_signals_connections();
	void pad_update();
	void pad_setup_profile_plot(QCustomPlot *profilePlot);
	void pad_setup_spectrum_plot(QCustomPlot *spectrumPlot);
	void pad_replot_profile();
	void pad_replot_spectrum();

	void set_filters_signals_connections();
	void filters_update();
	void copy_filter1_to_filter2();

	void set_distortion_signals_connections();
	void distortion_update();
	void init_distortion_combboxes_and_labels();

	void set_reverb_signals_connections();
	void reverb_update();
	void init_reverb_combboxes_and_labels();

	void set_equalizer_signals_connections();
	void equalizer_update();
	void init_equalizer_combboxes_and_labels();

	void set_amps_signals_connections();
	void amps_update();

	void set_adsrs_signals_connections();
	void adsrs_update();

	void set_lfos_signals_connections();
	void lfos_update();

	explicit Dialog_AnalogSynth_1900x1000(QWidget *parent = 0);

	Ui::Dialog_AnalogSynth_1900x1000 *ui;

	static Dialog_AnalogSynth_1900x1000 *dialog_analog_synth_instance;

	ControlWidgetsColorManager *control_widgets_color_manager;

	

	QList<QString> string_waveforms_list;
	QList<QString> string_adsr_values;
	QList<QString> string_lfo_values;
	QList<QString> string_unison_modes_list;
	QList<QString> string_hammond_modes_list;
	QList<QString> string_noise_colors_list;
	QList<QString> string_karplus_excitation_waveform_list;
	QList<QString> string_karplus_string_damping_calc_mode_list;
	QList<QString> string_mso_presets_list;
	QList<QString> string_pad_qualities_list;
	QList<QString> string_pad_base_notes_list;
	QList<QString> string_pad_shapes_list;
	QList<QString> string_pad_shape_cutoffs_list;

	QList<QString> string_unison_labels_hammond;
	QList<QString> string_unison_labels_octaves;
	QList<QString> string_unison_labels_c_chord;
	QList<QString> string_unison_labels_cm_chord;
	QList<QString> string_unison_labels_c7_chord;
	QList<QString> string_unison_labels_cm7_chord;

	QList<QString> string_unison_labels_harmonized;

	QList<QString> string_filters_bands;

	QSlider *unison_level_sliders[9];

	QList<QString> string_reverb_types_list;

	QList<QString> string_equalizer_presets;

	map<CustomComboBox *, int> select_adsr_combo_box_index;
};