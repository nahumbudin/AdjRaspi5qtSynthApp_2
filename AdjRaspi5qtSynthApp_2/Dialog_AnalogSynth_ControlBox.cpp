/**
 * @file		Dialog_AnalogSynth_ControlBox.cpp
 *	@author		Nahum Budin
 *	@date		14-Mar-2026
 *	@version	1.0
 *
 *	@brief		Analog Synthesizer control dialog control boxs events handling
 *
 *	@History:
 *
 */

#include "Dialog_AnalogSynth_1900x1000.h"
#include "GuiNavigator.h"
#include "ui_Dialog_AnalogSynth_1900x1000.h"

#include "utils.h"

void Dialog_AnalogSynth_1900x1000::control_box_ui_update_callback(int evnt, uint16_t val)
{
	if (!this->hasFocus())
	{
		return;
	}

	GuiNavigator *nav = GuiNavigator::get_instance();
	
	int current_tab_index = nav->get_current_tab_index();
	int current_frame_index = nav->get_current_frame_index();

	int slider_level_gap = 0;

	const int send_max = 100;
	const int send_min = 0;
	const int modulation_max = 100;
	const int modulation_min = 0;
	const int tune_offset_octave_max = 12; // -6 octave offset (min) to +6 octave offset (max), with 0 octave offset centered (13 steps total starting at 0)
	const int tune_offset_octave_min = 0;
	const int tune_offset_semitone_max = 22; // -11 semitone offset (min) to +11 semitone offset (max), with 0 semitone offset centered (23 steps total starting at 0)
	const int tune_offset_semitone_min = 0;
	const int tune_offset_cents_max = 60; // -7.5 to +7.5 cents, with 0.25 cent steps (61 steps total starting at 0), with 0 cent offset centered
	const int tune_offset_cents_min = 0;
	const int lfo_max = _NUM_OF_LFOS * _NUM_OF_LFO_DELAY_OPTIONS;
	const int lfo_min = _LFO_NONE;
	const int adsr_max = _NUM_OF_ADSRS;
	const int adsr_min = _ENV_NONE;

	const int osc_waveform_symetry_max = 95;
	const int osc_waveform_symetry_min = 5;	
	const int unison_level_max = 100;
	const int unison_level_min = 0;
	const int unison_distortion_max = 100;
	const int unison_distortion_min = 0;
	const int unison_detune_max = 100;
	const int unison_detune_min = 0;	
	const int hammond_percussion_mode_max = _HAMMOND_PERCUSION_MODE_3RD_NORM_FAST;
	const int hammond_percussion_mode_min = _HAMMOND_PERCUSION_MODE_OFF;
	const int unison_mode_max = _OSC_UNISON_MODE_Cm7_CHORD;
	const int unison_mode_min = _OSC_UNISON_MODE_12345678;

	const int mso_morph_max = 95;
	const int mso_morph_min = 5;
	const int mso_preset_max = 3; // sawtooth, pulse, square, sine
	const int mso_preset_min = 0; // sine
	const int mso_segment_max = 2046;
	const int mso_segment_min = 1;
	
	const int kps_excitation_waveform_max = _KARPLUS_STRONG_EXCITATION_SQUARE_WAVE;
	const int kps_excitation_waveform_min = _KARPLUS_STRONG_EXCITATION_WHITE_NOISE;
	const int kps_damping_calculation_max = _KARPLUS_STRONG_STRING_DAMPING_CALC_MAGIC;
	const int kps_damping_calculation_min = _KARPLUS_STRONG_STRING_DAMPING_CALC_DIRECT;
	const int kps_controls_max = 95;
	const int kps_controls_min = 5;
	
	const int pad_control_max = 100;
	const int pad_control_min = 0;
	const int pad_base_width_max = 95;
	const int pad_base_width_min = 5;
	const int pad_shape_max = _PAD_SHAPE_DOUBLE_EXP;
	const int pad_shape_min = _PAD_SHAPE_RECTANGULAR;
	const int pad_shape_cutoff_max = _PAD_SHAPE_CUTOFF_LOWER;
	const int pad_shape_cutoff_min = _PAD_SHAPE_CUTOFF_FULL;
	const int pad_quality_max = _PAD_QUALITY_1024K;
	const int pad_quality_min = _PAD_QUALITY_32K;
	const int pad_base_note_max = _PAD_BASE_NOTE_G6;
	const int pad_base_note_min = _PAD_BASE_NOTE_C2;

	const int filter_frequency_max = 100;
	const int filter_frequency_min = 0;
	const int filter_modulation_octave_max = 100;
	const int filter_modulation_octave_min = 0;
	const int filter_q_max = 100;
	const int filter_q_min = 0;
	const int filter_kbd_track_max = 100;
	const int filter_kbd_track_min = 0;
	const int filter_band_max = _FILTER_BAND_PASS_ALL;
	const int filter_band_min = _FILTER_BAND_LPF;

	const int distortion_control_max = 100;
	const int distortion_control_min = 0;

	const int reverb_preset_max = _REVERB_PRESET_LONG_REVERB_2;
	const int reverb_preset_min = _REVERB_PRESET_DEFAULT;
	const int reverb_room_size_max = 98;
	const int reverb_room_size_min = 10;
	const int reverb_control_max = 100;
	const int reverb_control_min = 0;
	const int reverb_width_min = 1;
	const int reverb_mode_max = 50;

	const int eqalizer_band_max = 40;
	const int eqalizer_band_min = 0;

	const int adsr_control_max = 100;
	const int adsr_control_min = 0;

	const int lfo_control_max = 100;
	const int lfo_control_min = 0;
	const int lfo_waveform_max = _OSC_WAVEFORM_SAMPHOLD;
	const int lfo_waveform_min = _OSC_WAVEFORM_SINE;

	static bool initialized = false;

	static int osc1_symetry = 50;
	static int osc1_send_filter_1 = 0;
	static int osc1_send_filter_2 = 0;
	static int osc1_waveform = _OSC_WAVEFORM_SINE;
	static int osc1_tune_offset_octave = 7; // 0 octave offset (centered), with range of -6 to +6 octaves (13 steps total)
	static int osc1_tune_offset_semitone = 12; // 0 semitone offset (centered), with range of -11 to +11 semitones (23 steps total)
	static int osc1_tune_offset_cents = 30; // 0 cent offset (centered), with range of -7.5 to +7.5 cents (61 steps total)
	static int osc1_freq_mod_lfo = _LFO_NONE;
	static int osc1_freq_mod_lfo_level = 0;
	static int osc1_freq_mod_adsr = _ENV_NONE;
	static int osc1_freq_mod_adsr_level = 0;
	static int osc1_amp_mod_lfo = _LFO_NONE;
	static int osc1_amp_mod_lfo_level = 0;
	static int osc1_amp_mod_adsr = _ENV_NONE;
	static int osc1_amp_mod_adsr_level = 0;
	static int osc1_pwm_mod_lfo = _LFO_NONE;
	static int osc1_pwm_mod_lfo_level = 0;
	static int osc1_pwm_mod_adsr = _ENV_NONE;
	static int osc1_pwm_mod_adsr_level = 0;
	static int osc1_unison_mode = _OSC_UNISON_MODE_12345678;
	static int osc1_hammond_percussion_mode = _HAMMOND_PERCUSION_MODE_OFF;
	static int osc1_unison_level_1 = 100;
	static int osc1_unison_level_2 = 0;
	static int osc1_unison_level_3 = 0;
	static int osc1_unison_level_4 = 0;
	static int osc1_unison_level_5 = 0;
	static int osc1_unison_level_6 = 0;
	static int osc1_unison_level_7 = 0;
	static int osc1_unison_level_8 = 0;
	static int osc1_unison_level_9 = 0;
	static int osc1_unison_level_10 = 0;
	static int osc1_unison_distortion = 0;
	static int osc1_unison_detune = 0;

	static int osc2_symetry = 50;
	static int osc2_send_filter_1 = 0;
	static int osc2_send_filter_2 = 0;
	static int osc2_waveform = _OSC_WAVEFORM_SINE;
	static int osc2_tune_offset_octave = 7;	   
	static int osc2_tune_offset_semitone = 12; 
	static int osc2_tune_offset_cents = 30;	   
	static int osc2_freq_mod_lfo = _LFO_NONE;
	static int osc2_freq_mod_lfo_level = 0;
	static int osc2_freq_mod_adsr = _ENV_NONE;
	static int osc2_freq_mod_adsr_level = 0;
	static int osc2_amp_mod_lfo = _LFO_NONE;
	static int osc2_amp_mod_lfo_level = 0;
	static int osc2_amp_mod_adsr = _ENV_NONE;
	static int osc2_amp_mod_adsr_level = 0;
	static int osc2_pwm_mod_lfo = _LFO_NONE;
	static int osc2_pwm_mod_lfo_level = 0;
	static int osc2_pwm_mod_adsr = _ENV_NONE	;
	static int osc2_pwm_mod_adsr_level = 0;

	static int mso_send_filter_1 = 0;
	static int mso_send_filter_2 = 0;
	static int mso_detune_octave = 7; // 0 octave offset (centered), with range of -6 to +6 octaves (13 steps total)
	static int mso_detune_semitone = 12; // 0 semitone offset (centered), with range of -11 to +11 semitones (23 steps total)
	static int mso_detune_cents = 30;	 // 0 cent offset (centered), with range of -7.5 to +7.5 cents (61 steps total)
	static int mso_freq_mod_lfo = _LFO_NONE;
	static int mso_freq_mod_lfo_level = 0;
	static int mso_freq_mod_adsr = _ENV_NONE;
	static int mso_freq_mod_adsr_level = 0;
	static int mso_amp_mod_lfo = _LFO_NONE;
	static int mso_amp_mod_lfo_level = 0;
	static int mso_amp_mod_adsr = _ENV_NONE;
	static int mso_amp_mod_adsr_level = 0;
	static int mso_pwm_mod_lfo = _LFO_NONE;
	static int mso_pwm_mod_lfo_level = 0;
	static int mso_pwm_mod_adsr = _ENV_NONE;
	static int mso_pwm_mod_adsr_level = 0;
	static int mso_morph = 50;
	static int mso_preset = 0; // sine
	static int mso_segment_a = 512;
	static int mso_segment_b = 517;
	static int mso_segment_c = 1024;
	static int mso_segment_d = 1029;
	static int mso_segment_e = 1536;
	static int mso_segment_f = 1542;

	static int noise_send_filter_1 = 0;
	static int noise_send_filter_2 = 0;
	static int noise_color = _WHITE_NOISE;
	static int noise_amp_mod_lfo = _LFO_NONE;
	static int noise_amp_mod_lfo_level = 0;
	static int noise_amp_mod_adsr = _ENV_NONE;
	static int noise_amp_mod_adsr_level = 0;

	static int kps_excitation_waveform = _KARPLUS_STRONG_EXCITATION_WHITE_NOISE;
	static int kps_damping_calculation = _KARPLUS_STRONG_STRING_DAMPING_CALC_DIRECT;
	static int kps_send_filter_1 = 0;
	static int kps_send_filter_2 = 0;
	static int kps_waveform_variations = 50;
	static int kps_on_decay = 80;
	static int kps_off_decay = 80;
	static int kps_string_damping = 50;
	static int kps_string_damping_variation = 50;
	static int kps_pluck_damping = 50;
	static int kps_pluck_damping_variation = 50;

	static int pad_send_filter_1 = 0;
	static int pad_send_filter_2 = 0;
	static int pad_tune_offset_octave = 7; // 0 octave offset (centered), with range of -6 to +6 octaves (13 steps total)
	static int pad_tune_offset_semitone = 12; // 0 semitone offset (centered), with range of -11 to +11 semitones (23 steps total)
	static int pad_tune_offset_cents = 30;	  // 0 cent offset (centered), with range of -7.5 to +7.5 cents (61 steps total)
	static int pad_freq_mod_lfo = _LFO_NONE;
	static int pad_freq_mod_lfo_level = 0;
	static int pad_freq_mod_adsr = _ENV_NONE;
	static int pad_freq_mod_adsr_level = 0;
	static int pad_amp_mod_lfo = _LFO_NONE;
	static int pad_amp_mod_lfo_level = 0;
	static int pad_amp_mod_adsr = _ENV_NONE;
	static int pad_amp_mod_adsr_level = 0;
	static int pad_harmony_1_level = 100;
	static int pad_harmony_2_level = 0;
	static int pad_harmony_3_level = 0;
	static int pad_harmony_4_level = 0;
	static int pad_harmony_5_level = 0;
	static int pad_harmony_6_level = 0;
	static int pad_harmony_7_level = 0;
	static int pad_harmony_8_level = 0;
	static int pad_harmony_9_level = 0;
	static int pad_harmony_10_level = 0;
	static int pad_harmonies_detune = 0;
	static int pad_base_width = 30;
	static int pad_shape = _PAD_SHAPE_RECTANGULAR;
	static int pad_shape_cutoff = _PAD_SHAPE_CUTOFF_FULL;
	static int pad_quality = _PAD_QUALITY_128K;
	static int pad_base_note = _PAD_BASE_NOTE_C3;

	static int filter_1_freq = 20;
	static int filter_1_q = 0;
	static int filter_1_mod_octave = 0;
	static int filter_1_kbd_track = 100;
	static int filter_1_band = _FILTER_BAND_LPF;
	static int filter_1_frequency_modulation_lfo = _LFO_NONE;
	static int filter_1_frequency_modulation_lfo_level = 0;
	static int filter_1_frequency_modulation_adsr = _ENV_NONE;
	static int filter_1_frequency_modulation_adsr_level = 0;

	static int filter_2_freq = 20;
	static int filter_2_q = 0;
	static int filter_2_mod_octave = 0;
	static int filter_2_kbd_track = 100;
	static int filter_2_band = _FILTER_BAND_LPF;
	static int filter_2_frequency_modulation_lfo = _LFO_NONE;
	static int filter_2_frequency_modulation_lfo_level = 0;
	static int filter_2_frequency_modulation_adsr = _ENV_NONE;
	static int filter_2_frequency_modulation_adsr_level = 0;

	static int distortion_1_drive = 0;
	static int distortion_1_range = 0;
	static int distortion_1_blend = 0;

	static int distortion_2_drive = 0;
	static int distortion_2_range = 0;
	static int distortion_2_blend = 0;

	static int reverb_preset = _REVERB_PRESET_DEFAULT;
	static int reverb_room_size = 0;
	static int reverb_damping = 0;
	static int reverb_wet = 0;
	static int reverb_dry = 0;
	static int reverb_width = 0;
	static int reverb_mode = 0;

	static int eqalizer_band[10] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20};

	static int adsr_attack[_NUM_OF_ADSRS];
	static int adsr_decay[_NUM_OF_ADSRS];
	static int adsr_sustain[_NUM_OF_ADSRS];
	static int adsr_release[_NUM_OF_ADSRS];

	static int lfo_rate[_NUM_OF_LFOS];
	static int lfo_symmetry[_NUM_OF_LFOS];
	static int lfo_waveform[_NUM_OF_LFOS];

	static int prev_osc1_symetry = 50;
	static int prev_osc1_send_filter_1 = 0;
	static int prev_osc1_send_filter_2 = 0;
	static int prev_osc1_waveform = _OSC_WAVEFORM_SINE;
	static int prev_osc1_tune_offset_octave = 7;
	static int prev_osc1_tune_offset_semitone = 12;
	static int prev_osc1_tune_offset_cents = 30;
	static int prev_osc1_freq_mod_lfo = _LFO_NONE;
	static int prev_osc1_freq_mod_lfo_level = 0;
	static int prev_osc1_freq_mod_adsr = _ENV_NONE;
	static int prev_osc1_freq_mod_adsr_level = 0;
	static int prev_osc1_amp_mod_lfo = _LFO_NONE;
	static int prev_osc1_amp_mod_lfo_level = 0;
	static int prev_osc1_amp_mod_adsr = _ENV_NONE;
	static int prev_osc1_amp_mod_adsr_level = 0;
	static int prev_osc1_pwm_mod_lfo = _LFO_NONE;
	static int prev_osc1_pwm_mod_lfo_level = 0;
	static int prev_osc1_pwm_mod_adsr = _ENV_NONE;
	static int prev_osc1_pwm_mod_adsr_level = 0;
	static int prev_osc1_unison_mode = _OSC_UNISON_MODE_12345678;
	static int prev_osc1_hammond_percussion_mode = _HAMMOND_PERCUSION_MODE_OFF;
	static int prev_osc1_unison_level_1 = 100;
	static int prev_osc1_unison_level_2 = 0;
	static int prev_osc1_unison_level_3 = 0;
	static int prev_osc1_unison_level_4 = 0;
	static int prev_osc1_unison_level_5 = 0;
	static int prev_osc1_unison_level_6 = 0;
	static int prev_osc1_unison_level_7 = 0;
	static int prev_osc1_unison_level_8 = 0;
	static int prev_osc1_unison_level_9 = 0;
	static int prev_osc1_unison_level_10 = 0;
	static int prev_osc1_unison_distortion = 0;
	static int prev_osc1_unison_detune = 0;
					
	static int prev_osc2_symetry = 50;
	static int prev_osc2_send_filter_1 = 0;
	static int prev_osc2_send_filter_2 = 0;
	static int prev_osc2_waveform = _OSC_WAVEFORM_SINE;
	static int prev_osc2_tune_offset_octave = 7;
	static int prev_osc2_tune_offset_semitone = 12;
	static int prev_osc2_tune_offset_cents = 30;
	static int prev_osc2_freq_mod_lfo = _LFO_NONE;
	static int prev_osc2_freq_mod_lfo_level = 0;
	static int prev_osc2_freq_mod_adsr = _ENV_NONE;
	static int prev_osc2_freq_mod_adsr_level = 0;
	static int prev_osc2_amp_mod_lfo = _LFO_NONE;
	static int prev_osc2_amp_mod_lfo_level = 0;
	static int prev_osc2_amp_mod_adsr = _ENV_NONE;	
	static int prev_osc2_amp_mod_adsr_level = 0;
	static int prev_osc2_pwm_mod_lfo = _LFO_NONE;
	static int prev_osc2_pwm_mod_lfo_level = 0;
	static int prev_osc2_pwm_mod_adsr = _ENV_NONE;
	static int prev_osc2_pwm_mod_adsr_level = 0;

	static int prev_mso_send_filter_1 = 0;
	static int prev_mso_send_filter_2 = 0;
	static int prev_mso_detune_octave = 7;	 
	static int prev_mso_detune_semitone = 12; 
	static int prev_mso_detune_cents = 30;	 
	static int prev_mso_freq_mod_lfo = _LFO_NONE;
	static int prev_mso_freq_mod_lfo_level = 0;
	static int prev_mso_freq_mod_adsr = _ENV_NONE;
	static int prev_mso_freq_mod_adsr_level = 0;
	static int prev_mso_amp_mod_lfo = _LFO_NONE;
	static int prev_mso_amp_mod_lfo_level = 0;
	static int prev_mso_amp_mod_adsr = _ENV_NONE;
	static int prev_mso_amp_mod_adsr_level = 0;
	static int prev_mso_pwm_mod_lfo = _LFO_NONE;
	static int prev_mso_pwm_mod_lfo_level = 0;
	static int prev_mso_pwm_mod_adsr = _ENV_NONE;
	static int prev_mso_pwm_mod_adsr_level = 0;
	static int prev_mso_morph = 50;
	static int prev_mso_preset = 0; // sine
	static int prev_mso_segment_1 = 512;
	static int prev_mso_segment_2 = 517;
	static int prev_mso_segment_3 = 1024;
	static int prev_mso_segment_4 = 1029;
	static int prev_mso_segment_5 = 1536;
	static int prev_mso_segment_6 = 1542;

	static int prev_noise_send_filter_1 = 0;
	static int prev_noise_send_filter_2 = 0;
	static int prev_noise_color = _WHITE_NOISE;
	static int prev_noise_amp_mod_lfo = _LFO_NONE;
	static int prev_noise_amp_mod_lfo_level = 0;
	static int prev_noise_amp_mod_adsr = _ENV_NONE;
	static int prev_noise_amp_mod_adsr_level = 0;

	static int prev_kps_excitation_waveform = _KARPLUS_STRONG_EXCITATION_WHITE_NOISE;
	static int prev_kps_damping_calculation = _KARPLUS_STRONG_STRING_DAMPING_CALC_DIRECT;
	static int prev_kps_send_filter_1 = 0;
	static int prev_kps_send_filter_2 = 0;
	static int prev_kps_waveform_variations = 50;
	static int prev_kps_on_decay = 80;
	static int prev_kps_off_decay = 80;
	static int prev_kps_string_damping = 50;
	static int prev_kps_string_damping_variation = 50;
	static int prev_kps_pluck_damping = 50;
	static int prev_kps_pluck_damping_variation = 50;

	static int prev_pad_send_filter_1 = 0;
	static int prev_pad_send_filter_2 = 0;
	static int prev_pad_tune_offset_octave = 7;
	static int prev_pad_tune_offset_semitone = 12;
	static int prev_pad_tune_offset_cents = 30;
	static int prev_pad_freq_mod_lfo = _LFO_NONE;
	static int prev_pad_freq_mod_lfo_level = 0;
	static int prev_pad_freq_mod_adsr = _ENV_NONE;
	static int prev_pad_freq_mod_adsr_level = 0;
	static int prev_pad_amp_mod_lfo = _LFO_NONE;
	static int prev_pad_amp_mod_lfo_level = 0;
	static int prev_pad_amp_mod_adsr = _ENV_NONE;
	static int prev_pad_amp_mod_adsr_level = 0;
	static int prev_pad_harmony_1_level = 100;
	static int prev_pad_harmony_2_level = 0;
	static int prev_pad_harmony_3_level = 0;
	static int prev_pad_harmony_4_level = 0;
	static int prev_pad_harmony_5_level = 0;
	static int prev_pad_harmony_6_level = 0;
	static int prev_pad_harmony_7_level = 0;
	static int prev_pad_harmony_8_level = 0;
	static int prev_pad_harmony_9_level = 0;
	static int prev_pad_harmony_10_level = 0;
	static int prev_pad_harmonies_detune = 0;
	static int prev_pad_base_width = 30;
	static int prev_pad_shape = _PAD_SHAPE_RECTANGULAR;
	static int prev_pad_shape_cutoff = _PAD_SHAPE_CUTOFF_FULL;
	static int prev_pad_quality = _PAD_QUALITY_128K;
	static int prev_pad_base_note = _PAD_BASE_NOTE_C3;

	static int prev_filter_1_freq = 20;
	static int prev_filter_1_q = 0;
	static int prev_filter_1_mod_octave = 0;
	static int prev_filter_1_kbd_track = 100;
	static int prev_filter_1_band = _FILTER_BAND_LPF;
	static int prev_filter_1_frequency_modulation_lfo = _LFO_NONE;
	static int prev_filter_1_frequency_modulation_lfo_level = 0;
	static int prev_filter_1_frequency_modulation_adsr = _ENV_NONE;
	static int prev_filter_1_frequency_modulation_adsr_level = 0;

	static int prev_filter_2_freq = 20;
	static int prev_filter_2_q = 0;
	static int prev_filter_2_mod_octave = 0;
	static int prev_filter_2_kbd_track = 100;
	static int prev_filter_2_band = _FILTER_BAND_LPF;
	static int prev_filter_2_frequency_modulation_lfo = _LFO_NONE;
	static int prev_filter_2_frequency_modulation_lfo_level = 0;
	static int prev_filter_2_frequency_modulation_adsr = _ENV_NONE;
	static int prev_filter_2_frequency_modulation_adsr_level = 0;

	static int prev_distortion_1_drive = 0;
	static int prev_distortion_1_range = 0;
	static int prev_distortion_1_blend = 0;

	static int prev_distortion_2_drive = 0;
	static int prev_distortion_2_range = 0;
	static int prev_distortion_2_blend = 0;

	static int prev_reverb_preset = _REVERB_PRESET_DEFAULT;
	static int prev_reverb_room_size = 0;
	static int prev_reverb_damping = 0;
	static int prev_reverb_wet = 0;
	static int prev_reverb_dry = 0;
	static int prev_reverb_width = 0;
	static int prev_reverb_mode = 0;

	static int prev_eqalizer_band[10] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20};

	static int prev_adsr_attack[_NUM_OF_ADSRS] = {5};
	static int prev_adsr_decay[_NUM_OF_ADSRS] = {10};
	static int prev_adsr_sustain[_NUM_OF_ADSRS] = {80};
	static int prev_adsr_release[_NUM_OF_ADSRS] = {10};

	static int prev_lfo_rate[_NUM_OF_LFOS] = {20};
	static int prev_lfo_symmetry[_NUM_OF_LFOS] = {50};
	static int prev_lfo_waveform[_NUM_OF_LFOS] = {_OSC_WAVEFORM_SINE};
	
	if (!initialized)
	{
		initialized = true;
		
		for (int i = 0; i < _NUM_OF_LFOS; i++)
		{
			adsr_attack[i] = 5;
			adsr_decay[i] = 10;
			adsr_sustain[i] = 80;
			adsr_release[i] = 10;

			prev_adsr_attack[i] = 5;
			prev_adsr_decay[i] = 10;
			prev_adsr_sustain[i] = 80;
			prev_adsr_release[i] = 10;

			lfo_rate[i] = 20;
			lfo_symmetry[i] = 50;
			lfo_waveform[i] = _OSC_WAVEFORM_SINE;

			prev_lfo_rate[i] = 20;
			prev_lfo_symmetry[i] = 50;
			prev_lfo_waveform[i] = _OSC_WAVEFORM_SINE;
		}
	}

	if (current_tab_index == 0)
	{
		// Sources
		if (current_frame_index == 0)
		{
			// Osc1 Waveform and Tune (controls 1-8)
			if (evnt == _I2C_CONTROL_ENCODER_2)
			{
				// Gray Purple dial - Osc1 send filter1 control
				osc1_send_filter_1 = update_rotary_encoder_value(
					osc1_send_filter_1,
					val,
					&prev_osc1_send_filter_1,
					send_min,
					send_max,
					4);

				ui->dial_Osc1SendFilter1->setValue(osc1_send_filter_1);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_3)
			{
				// Gray Blue dial - Osc1 send filter2 control
				osc1_send_filter_2 = update_rotary_encoder_value(
					osc1_send_filter_2,
					val,
					&prev_osc1_send_filter_2,
					send_min,
					send_max,
					4);

				ui->dial_Osc1SendFilter2->setValue(osc1_send_filter_2);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_4)
			{
				// Gray Green combobox - Osc1 waveform control
				osc1_waveform = update_rotary_encoder_value(
					osc1_waveform,
					val,
					&prev_osc1_waveform,
					_OSC_WAVEFORM_SINE,
					_OSC_WAVEFORM_SAMPHOLD,
					1);

				ui->comboBox_Osc1Waveform->setCurrentIndex(osc1_waveform);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_5)
			{
				// Gray White combobox - Osc1 tune octave control
				osc1_tune_offset_octave = update_rotary_encoder_value(
					osc1_tune_offset_octave,
					val,
					&prev_osc1_tune_offset_octave,
					tune_offset_octave_min,
					tune_offset_octave_max,
					1);

				ui->comboBox_Osc1TuneOctave->setCurrentIndex(osc1_tune_offset_octave);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_6)
			{
				// Gray Red combobox - Osc1 tune semitones control
				osc1_tune_offset_semitone = update_rotary_encoder_value(
					osc1_tune_offset_semitone,
					val,
					&prev_osc1_tune_offset_semitone,
					tune_offset_semitone_min,
					tune_offset_semitone_max,
					1);

				ui->comboBox_Osc1TuneSemitones->setCurrentIndex(osc1_tune_offset_semitone);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_7)
			{
				// GrayYellow combobox - Osc1 Tune cents control
				osc1_tune_offset_cents = update_rotary_encoder_value(
					osc1_tune_offset_cents,
					val,
					&prev_osc1_tune_offset_cents,
					tune_offset_cents_min,
					tune_offset_cents_max,
					1);

				ui->comboBox_Osc1TuneCents->setCurrentIndex(osc1_tune_offset_cents);
			}

			// Osc1 Freq Mod and Amp Mod (controls 9-16)
			else if (evnt == _I2C_CONTROL_ENCODER_9)
			{
				// White Gray combobox - Osc1 freq mod LFO control
				osc1_freq_mod_lfo = update_rotary_encoder_value(
					osc1_freq_mod_lfo,
					val,
					&prev_osc1_freq_mod_lfo,
					lfo_min,
					lfo_max,
					1);

				ui->comboBox_Osc1FreqModLFO->setCurrentIndex(osc1_freq_mod_lfo);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_10)
			{
				// White Purple combobox - Osc1 freq mod ADSR control
				osc1_freq_mod_adsr = update_rotary_encoder_value(
					osc1_freq_mod_adsr,
					val,
					&prev_osc1_freq_mod_adsr,
					adsr_min,
					adsr_max,
					1);

				ui->comboBox_Osc1FreqModAdsr->setCurrentIndex(osc1_freq_mod_adsr);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_11)
			{
				// White Blue dial - Osc1 freq mod LFO level control
				osc1_freq_mod_lfo_level = update_rotary_encoder_value(
					osc1_freq_mod_lfo_level,
					val,
					&prev_osc1_freq_mod_lfo_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_Osc1FreqModLFOLevel->setValue(osc1_freq_mod_lfo_level);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_12)
			{
				// Whie Green dial - Osc1 freq mod ADSR level control
				osc1_freq_mod_adsr_level = update_rotary_encoder_value(
					osc1_freq_mod_adsr_level,
					val,
					&prev_osc1_pwm_mod_adsr_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_Osc1FreqModAdsrLevel->setValue(osc1_freq_mod_adsr_level);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_13)
			{
				// White White combobox - Osc1 Amp mod LFO control
				osc1_amp_mod_lfo = update_rotary_encoder_value(
					osc1_amp_mod_lfo,
					val,
					&prev_osc1_amp_mod_lfo,
					lfo_min,
					lfo_max,
					1);

				ui->comboBox_Osc1AmpModLFO->setCurrentIndex(osc1_amp_mod_lfo);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_14)
			{
				// White Yellow combobox - Osc1 Amp mod ADSR
				osc1_amp_mod_adsr = update_rotary_encoder_value(
					osc1_amp_mod_adsr,
					val,
					&prev_osc1_amp_mod_adsr,
					adsr_min,
					adsr_max,
					1);

				ui->comboBox_Osc1AmpModAdsr->setCurrentIndex(osc1_amp_mod_adsr);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_15)
			{
				// White Red dial - Osc1 Amp mod LFO level control
				osc1_amp_mod_lfo_level = update_rotary_encoder_value(
					osc1_amp_mod_lfo_level,
					val,
					&prev_osc1_amp_mod_lfo_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_Osc1AmpModLFOLevel->setValue(osc1_amp_mod_lfo_level);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_16)
			{
				// White Black dial - Osc1 Amp mod ADSR level control
				osc1_amp_mod_adsr_level = update_rotary_encoder_value(
					osc1_amp_mod_adsr_level,
					val,
					&prev_osc1_amp_mod_adsr_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_Osc1AmpModAdsrLevel->setValue(osc1_amp_mod_adsr_level);
			}
			else if (evnt == _I2C_CONTROL_SLIDER_3)
			{
				// Gray Blue slider - Osc1 symetry control
				// Get new symetry value from slider and calculate gap from current UI value
				osc1_symetry = normalize_slider_value(val / 37, osc_waveform_symetry_max, osc_waveform_symetry_min);// 0-3700
				slider_level_gap = osc1_symetry - ui->horizontalSlider_Osc1Symmetry->value(); // 5-95

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((osc_waveform_symetry_max - osc_waveform_symetry_min) / 5.0))
				{
					// Emits value changed signal.
					ui->horizontalSlider_Osc1Symmetry->setValue(osc1_symetry);
				}
			}
		}
		else if (current_frame_index == 1)
		{
			// OSC1 Drawbars 1-6 and PWM modulation (controls 1-8)
			if (evnt == _I2C_CONTROL_SLIDER_1)
			{
				// Gray Gray slider - Osc1 drawbar 1 control
				// Get new drawbar 1 value from slider and calculate gap from current UI value
				osc1_unison_level_1 = normalize_slider_value(val / 36, unison_level_max, unison_level_min); // 0-3600
				slider_level_gap = osc1_unison_level_1 - ui->verticalSlider_Osc1UnisonLevel_1->value();		// 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((unison_level_max - unison_level_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_Osc1UnisonLevel_1->setValue(osc1_unison_level_1);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_2)
			{
				// Gray Purple slider - Osc1 drawbar 2 control
				// Get new drawbar 2 value from slider and calculate gap from current UI value
				osc1_unison_level_2 = normalize_slider_value(val / 36, unison_level_max, unison_level_min); // 0-3600
				slider_level_gap = osc1_unison_level_2 - ui->verticalSlider_Osc1UnisonLevel_2->value();		// 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((unison_level_max - unison_level_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_Osc1UnisonLevel_2->setValue(osc1_unison_level_2);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_3)
			{
				// Gray Blue slider - Osc1 drawbar 3 control
				// Get new drawbar 3 value from slider and calculate gap from current UI value
				osc1_unison_level_3 = normalize_slider_value(val / 36, unison_level_max, unison_level_min); // 0-3600
				slider_level_gap = osc1_unison_level_3 - ui->verticalSlider_Osc1UnisonLevel_3->value();		// 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((unison_level_max - unison_level_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_Osc1UnisonLevel_3->setValue(osc1_unison_level_3);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_4)
			{
				// Gray Green slider - Osc1 drawbar 4 control
				// Get new drawbar 4 value from slider and calculate gap from current UI value
				osc1_unison_level_4 = normalize_slider_value(val / 36, unison_level_max, unison_level_min); // 0-3600
				slider_level_gap = osc1_unison_level_4 - ui->verticalSlider_Osc1UnisonLevel_4->value();		// 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((unison_level_max - unison_level_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_Osc1UnisonLevel_4->setValue(osc1_unison_level_4);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_5)
			{
				// Gray White slider - Osc1 drawbar 5 control
				// Get new drawbar 5 value from slider and calculate gap from current UI value
				osc1_unison_level_5 = normalize_slider_value(val / 36, unison_level_max, unison_level_min); // 0-3600
				slider_level_gap = osc1_unison_level_5 - ui->verticalSlider_Osc1UnisonLevel_5->value();		// 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((unison_level_max - unison_level_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_Osc1UnisonLevel_5->setValue(osc1_unison_level_5);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_6)
			{
				// Gray Yellow slider - Osc1 drawbar 6 control
				// Get new drawbar 6 value from slider and calculate gap from current UI value
				osc1_unison_level_6 = normalize_slider_value(val / 36, unison_level_max, unison_level_min); // 0-3600
				slider_level_gap = osc1_unison_level_6 - ui->verticalSlider_Osc1UnisonLevel_6->value();		// 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((unison_level_max - unison_level_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_Osc1UnisonLevel_6->setValue(osc1_unison_level_6);
				}
			}
			else if (evnt == _I2C_CONTROL_ENCODER_2)
			{
				// Gray Purple dial - Osc1 percussion mode control
				osc1_hammond_percussion_mode = update_rotary_encoder_value(
					osc1_hammond_percussion_mode,
					val,
					&prev_osc1_hammond_percussion_mode,
					hammond_percussion_mode_min,
					hammond_percussion_mode_max,
					1);

				ui->comboBox_Osc1HammondPercussionMode->setCurrentIndex(osc1_hammond_percussion_mode);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_3)
			{
				// Gray Blue dial - Osc1 unison mode control
				osc1_unison_mode = update_rotary_encoder_value(
					osc1_unison_mode,
					val,
					&prev_osc1_unison_mode,
					unison_mode_min,
					unison_mode_max,
					1);

				ui->comboBox_Osc1UnisonMode->setCurrentIndex(osc1_unison_mode);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_5)
			{
				// Gray White combobox - Osc1 PWM LFO control
				osc1_pwm_mod_lfo = update_rotary_encoder_value(
					osc1_pwm_mod_lfo,
					val,
					&prev_osc1_pwm_mod_lfo,
					lfo_min,
					lfo_max,
					1);

				ui->comboBox_Osc1PwmModLFO->setCurrentIndex(osc1_pwm_mod_lfo);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_6)
			{
				// Gray Yellow dial - Osc1 PWM ADSR control
				osc1_pwm_mod_adsr = update_rotary_encoder_value(
					osc1_pwm_mod_adsr,
					val,
					&prev_osc1_pwm_mod_adsr,
					adsr_min,
					adsr_max,
					1);

				ui->comboBox_Osc1PwmModAdsr->setCurrentIndex(osc1_pwm_mod_adsr);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_7)
			{
				// Gray Red dial - Osc1 PWM LFO level control
				osc1_pwm_mod_lfo_level = update_rotary_encoder_value(
					osc1_pwm_mod_lfo_level,
					val,
					&prev_osc1_pwm_mod_lfo_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_Osc1PwmModLFOLevel->setValue(osc1_pwm_mod_lfo_level);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_8)
			{
				// Gray Gray dial - Osc1 PWM ADSR level control
				osc1_pwm_mod_adsr_level = update_rotary_encoder_value(
					osc1_pwm_mod_adsr_level,
					val,
					&prev_osc1_pwm_mod_adsr_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_Osc1PwmModAdsrLevel->setValue(osc1_pwm_mod_adsr_level);
			}

			// OSC1 Drawbars 7-9 (controls 9-16)
			else if (evnt == _I2C_CONTROL_SLIDER_9)
			{
				// White Gray slider - Osc1 drawbar 7 control
				// Get new drawbar 7 value from slider and calculate gap from current UI value
				osc1_unison_level_7 = normalize_slider_value(val / 36, unison_level_max, unison_level_min); // 0-3600
				slider_level_gap = osc1_unison_level_7 - ui->verticalSlider_Osc1UnisonLevel_7->value();		// 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((unison_level_max - unison_level_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_Osc1UnisonLevel_7->setValue(osc1_unison_level_7);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_10)
			{
				// White Purple slider - Osc1 drawbar 8 control
				// Get new drawbar 8 value from slider and calculate gap from current UI value
				osc1_unison_level_8 = normalize_slider_value(val / 36, unison_level_max, unison_level_min); // 0-3600
				slider_level_gap = osc1_unison_level_8 - ui->verticalSlider_Osc1UnisonLevel_8->value();		// 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((unison_level_max - unison_level_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_Osc1UnisonLevel_8->setValue(osc1_unison_level_8);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_11)
			{
				// White Blue slider - Osc1 drawbar 9 control
				// Get new drawbar 9 value from slider and calculate gap from current UI value
				osc1_unison_level_9 = normalize_slider_value(val / 36, unison_level_max, unison_level_min); // 0-3600
				slider_level_gap = osc1_unison_level_9 - ui->verticalSlider_Osc1UnisonLevel_9->value();		// 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((unison_level_max - unison_level_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_Osc1UnisonLevel_9->setValue(osc1_unison_level_9);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_12)
			{
				// White Green slider - Osc1 unison distortion control
				// Get new distortion value from slider and calculate gap from current UI value
				osc1_unison_distortion = normalize_slider_value(val / 36, unison_distortion_max, unison_distortion_min); // 0-3600
				slider_level_gap = osc1_unison_distortion - ui->verticalSlider_Osc1HarmonyDistortLevel->value();		// 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((unison_distortion_max - unison_distortion_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_Osc1HarmonyDistortLevel->setValue(osc1_unison_distortion);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_13)
			{
				// White White slider - Osc1 unison detune control
				// Get new detune value from slider and calculate gap from current UI value
				osc1_unison_detune = normalize_slider_value(val / 36, unison_detune_max, unison_detune_min); // 0-3600
				slider_level_gap = osc1_unison_detune - ui->verticalSlider_Osc1HarmonyDetuneLevel->value();		 // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((unison_detune_max - unison_detune_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_Osc1HarmonyDetuneLevel->setValue(osc1_unison_detune);
				}
			}
		}
		else if ((current_frame_index == 2) || (current_frame_index == 3))
		{
			// OSC2 Waveform and Tune (controls 1-8) - unchanged in frame 3
			if (evnt == _I2C_CONTROL_ENCODER_2)
			{
				// Gray Purple dial - Osc2 send filter1 control
				osc2_send_filter_1 = update_rotary_encoder_value(
					osc2_send_filter_1,
					val,
					&prev_osc2_send_filter_1,
					send_min,
					send_max,
					4);

				ui->dial_Osc2SendFilter1->setValue(osc2_send_filter_1);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_3)
			{
				// Gray Blue dial - Osc2 send filter2 control
				osc2_send_filter_2 = update_rotary_encoder_value(
					osc2_send_filter_2,
					val,
					&prev_osc2_send_filter_2,
					send_min,
					send_max,
					4);

				ui->dial_Osc2SendFilter2->setValue(osc2_send_filter_2);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_4)
			{
				// Gray Green combobox - Osc2 waveform control
				osc2_waveform = update_rotary_encoder_value(
					osc2_waveform,
					val,
					&prev_osc2_waveform,
					_OSC_WAVEFORM_SINE,
					_OSC_WAVEFORM_SAMPHOLD,
					1);

				ui->comboBox_Osc2Waveform->setCurrentIndex(osc2_waveform);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_5)
			{
				// Gray White combobox - Osc2 tune octave control
				osc2_tune_offset_octave = update_rotary_encoder_value(
					osc2_tune_offset_octave,
					val,
					&prev_osc2_tune_offset_octave,
					tune_offset_octave_min,
					tune_offset_octave_max,
					1);

				ui->comboBox_Osc2TuneOctave->setCurrentIndex(osc2_tune_offset_octave);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_6)
			{
				// Gray Red combobox - Osc2 tune semitones control
				osc2_tune_offset_semitone = update_rotary_encoder_value(
					osc2_tune_offset_semitone,
					val,
					&prev_osc2_tune_offset_semitone,
					tune_offset_semitone_min,
					tune_offset_semitone_max,
					1);

				ui->comboBox_Osc2TuneSemitones->setCurrentIndex(osc2_tune_offset_semitone);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_7)
			{
				// GrayYellow combobox - Osc2 Tune cents control
				osc2_tune_offset_cents = update_rotary_encoder_value(
					osc2_tune_offset_cents,
					val,
					&prev_osc2_tune_offset_cents,
					tune_offset_cents_min,
					tune_offset_cents_max,
					1);

				ui->comboBox_Osc2TuneCents->setCurrentIndex(osc2_tune_offset_cents);
			}
			else if (evnt == _I2C_CONTROL_SLIDER_3)
			{
				// Gray Blue slider - Osc2 symetry control
				// Get new symetry value from slider and calculate gap from current UI value
				osc2_symetry = normalize_slider_value(val / 37, osc_waveform_symetry_max, osc_waveform_symetry_min); // 0-3700
				slider_level_gap = osc2_symetry - ui->horizontalSlider_Osc2Symmetry->value();						 // 5-95

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((osc_waveform_symetry_max - osc_waveform_symetry_min) / 5.0))
				{
					// Emits value changed signal.
					ui->horizontalSlider_Osc2Symmetry->setValue(osc2_symetry);
				}
			}

			// OSC2 Amp Mod (controls 13-16)
			if (evnt == _I2C_CONTROL_ENCODER_13)
			{
				// White White combobox - Osc2 Amp mod LFO control
				osc2_amp_mod_lfo = update_rotary_encoder_value(
					osc2_amp_mod_lfo,
					val,
					&prev_osc2_amp_mod_lfo,
					lfo_min,
					lfo_max,
					1);

				ui->comboBox_Osc2AmpModLFO->setCurrentIndex(osc2_amp_mod_lfo);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_14)
			{
				// White Yellow combobox - Osc2 Amp mod ADSR
				// White Yellow combobox - Osc1 Amp mod ADSR
				osc2_amp_mod_adsr = update_rotary_encoder_value(
					osc2_amp_mod_adsr,
					val,
					&prev_osc2_amp_mod_adsr,
					adsr_min,
					adsr_max,
					1);

				ui->comboBox_Osc2AmpModAdsr->setCurrentIndex(osc2_amp_mod_adsr);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_15)
			{
				// White Red dial - Osc2 Amp mod LFO level control
				osc2_amp_mod_lfo_level = update_rotary_encoder_value(
					osc2_amp_mod_lfo_level,
					val,
					&prev_osc2_amp_mod_lfo_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_Osc2AmpModLFOLevel->setValue(osc2_amp_mod_lfo_level);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_16)
			{
				// White Black dial - Osc2 Amp mod ADSR level control
				osc2_amp_mod_adsr_level = update_rotary_encoder_value(
					osc2_amp_mod_adsr_level,
					val,
					&prev_osc2_amp_mod_adsr_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_Osc2AmpModAdsrLevel->setValue(osc2_amp_mod_adsr_level);
			}
			
			if (current_frame_index == 2)
			{
				
				if (evnt == _I2C_CONTROL_ENCODER_9)
				{
					// Whiet Gray combobox - Osc2 freq mod LFO control
					osc2_freq_mod_lfo = update_rotary_encoder_value(
						osc2_freq_mod_lfo,
						val,
						&prev_osc2_freq_mod_lfo,
						lfo_min,
						lfo_max,
						1);

					ui->comboBox_Osc2FreqModLFO->setCurrentIndex(osc2_freq_mod_lfo);
				}
				else if (evnt == _I2C_CONTROL_ENCODER_10)
				{
					// White Purple combobox - Osc2 freq mod ADSR control
					osc2_freq_mod_adsr = update_rotary_encoder_value(
						osc2_freq_mod_adsr,
						val,
						&prev_osc2_freq_mod_adsr,
						adsr_min,
						adsr_max,
						1);

					ui->comboBox_Osc2FreqModAdsr->setCurrentIndex(osc2_freq_mod_adsr);
				}
				else if (evnt == _I2C_CONTROL_ENCODER_11)
				{
					// White Blue dial - Osc2 freq mod LFO level control
					osc2_freq_mod_lfo_level = update_rotary_encoder_value(
						osc2_freq_mod_lfo_level,
						val,
						&prev_osc2_freq_mod_lfo_level,
						modulation_min,
						modulation_max,
						4);

					ui->dial_Osc2FreqModLFOLevel->setValue(osc2_freq_mod_lfo_level);
				}
				else if (evnt == _I2C_CONTROL_ENCODER_12)
				{
					// White Green dial - Osc2 freq mod ADSR level control
					osc2_freq_mod_adsr_level = update_rotary_encoder_value(
						osc2_freq_mod_adsr_level,
						val,
						&prev_osc2_freq_mod_adsr_level,
						modulation_min,
						modulation_max,
						4);

					ui->dial_Osc2FreqModAdsrLevel->setValue(osc2_freq_mod_adsr_level);
				}				
			}
			else if (current_frame_index == 3)
			{
				// OSC2 PWM Mod (controls 9-12)
				if (evnt == _I2C_CONTROL_ENCODER_9)
				{
					// Whiet Gray combobox - Osc2 PWM mod LFO control
					osc2_pwm_mod_lfo = update_rotary_encoder_value(
						osc2_pwm_mod_lfo,
						val,
						&prev_osc2_pwm_mod_lfo,
						lfo_min,
						lfo_max,
						1);

					ui->comboBox_Osc2PwmModLFO->setCurrentIndex(osc2_pwm_mod_lfo);
				}
				else if (evnt == _I2C_CONTROL_ENCODER_10)
				{
					// White Purple combobox - Osc2 PWM mod ADSR control
					osc2_pwm_mod_adsr = update_rotary_encoder_value(
						osc2_pwm_mod_adsr,
						val,
						&prev_osc2_pwm_mod_adsr,
						adsr_min,
						adsr_max,
						1);

					ui->comboBox_Osc2PwmModAdsr->setCurrentIndex(osc2_pwm_mod_adsr);
				}
				else if (evnt == _I2C_CONTROL_ENCODER_11)
				{
					// White Blue dial - Osc2 PWM mod LFO level control
					osc2_pwm_mod_lfo_level = update_rotary_encoder_value(
						osc2_pwm_mod_lfo_level,
						val,
						&prev_osc2_pwm_mod_lfo_level,
						modulation_min,
						modulation_max,
						4);

					ui->dial_Osc2PwmModLFOLevel->setValue(osc2_pwm_mod_lfo_level);
				}
				else if (evnt == _I2C_CONTROL_ENCODER_12)
				{
					// White Green dial - Osc2 PWM mod ADSR level control
					osc2_pwm_mod_adsr_level = update_rotary_encoder_value(
						osc2_pwm_mod_adsr_level,
						val,
						&prev_osc2_pwm_mod_adsr_level,
						modulation_min,
						modulation_max,
						4);

					ui->dial_Osc2PwmModAdsrLevel->setValue(osc2_pwm_mod_adsr_level);
				}
			}
		}
		else if (current_frame_index == 4)
		{
			// MSO Send and Tune (controls 1-8)
			if (evnt == _I2C_CONTROL_ENCODER_2)
			{
				// Gray Purple dial - MSO send filter1 control
				mso_send_filter_1 = update_rotary_encoder_value(
					mso_send_filter_1,
					val,
					&prev_mso_send_filter_1,
					send_min,
					send_max,
					4);

				ui->dial_MsoSendFilter1->setValue(mso_send_filter_1);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_3)
			{
				// Gray Blue dial - MSO send filter2 control
				mso_send_filter_2 = update_rotary_encoder_value(
					mso_send_filter_2,
					val,
					&prev_mso_send_filter_2,
					send_min,
					send_max,
					4);

				ui->dial_MsoSendFilter2->setValue(mso_send_filter_2);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_5)
			{
				// Gray White dial - MSO tune octave control
				mso_detune_octave = update_rotary_encoder_value(
					mso_tune_octave,
					val,
					&prev_mso_detune_octave,
					tune_offset_octave_min,
					tune_offset_octave_max,
					1);

				ui->comboBox_MsoTuneOctave->setCurrentIndex(mso_detune_octave);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_6)
			{
				// Gray Yellow dial - MSO tune semitones control
				mso_detune_semitone = update_rotary_encoder_value(
					mso_detune_semitone,
					val,
					&prev_mso_detune_semitone,
					tune_offset_semitone_min,
					tune_offset_semitone_max,
					1);

				ui->comboBox_MsoTuneSemitones->setCurrentIndex(mso_detune_semitone);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_7)
			{
				// Gray Red dial - MSO Tune cents control
				mso_detune_cents = update_rotary_encoder_value(
					mso_detune_cents,
					val,
					&prev_mso_detune_cents,
					tune_offset_cents_min,
					tune_offset_cents_max,
					1);

				ui->comboBox_MsoTuneCents->setCurrentIndex(mso_detune_cents);
			}
			
			// MSO Freq  and Amp Mod (controls 9-16)
			if (evnt == _I2C_CONTROL_ENCODER_9)
			{
				// Whiet Gray combobox - MSO freq mod LFO control
				mso_freq_mod_lfo = update_rotary_encoder_value(
					mso_freq_mod_lfo,
					val,
					&prev_mso_freq_mod_lfo,
					lfo_min,
					lfo_max,
					1);

				ui->comboBox_MsoFreqModLFO->setCurrentIndex(mso_freq_mod_lfo);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_10)
			{
				// White Purple combobox - MSO freq mod ADSR control
				mso_freq_mod_adsr = update_rotary_encoder_value(
					mso_freq_mod_adsr,
					val,
					&prev_mso_freq_mod_adsr,
					adsr_min,
					adsr_max,
					1);

				ui->comboBox_MsoFreqModAdsr->setCurrentIndex(mso_freq_mod_adsr);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_11)
			{
				// White Blue dial - MSO freq mod LFO level control
				mso_freq_mod_lfo_level = update_rotary_encoder_value(
					mso_freq_mod_lfo_level,
					val,
					&prev_mso_freq_mod_lfo_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_MsoFreqModLFOLevel->setValue(mso_freq_mod_lfo_level);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_12)
			{
				// White Green dial - MSO freq mod ADSR level control
				mso_freq_mod_adsr_level = update_rotary_encoder_value(
					mso_freq_mod_adsr_level,
					val,
					&prev_mso_freq_mod_adsr_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_MsoFreqModAdsrLevel->setValue(mso_freq_mod_adsr_level);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_13)
			{
				// White White combobox - MSO Amp mod LFO control
				mso_amp_mod_lfo = update_rotary_encoder_value(
					mso_amp_mod_lfo,
					val,
					&prev_mso_amp_mod_lfo,
					lfo_min,
					lfo_max,
					1);

				ui->comboBox_MsoAmpModLFO->setCurrentIndex(mso_amp_mod_lfo);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_14)
			{
				// White Yellow combobox - MSO Amp mod ADSR
				mso_amp_mod_adsr = update_rotary_encoder_value(
					mso_amp_mod_adsr,
					val,
					&prev_mso_amp_mod_adsr,
					adsr_min,
					adsr_max,
					1);

				ui->comboBox_MsoAmpModAdsr->setCurrentIndex(mso_amp_mod_adsr);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_15)
			{
				// White Red dial - MSO Amp mod LFO level control
				mso_amp_mod_lfo_level = update_rotary_encoder_value(
					mso_amp_mod_lfo_level,
					val,
					&prev_mso_amp_mod_lfo_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_MsoAmpModLFOLevel->setValue(mso_amp_mod_lfo_level);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_16)
			{
				// White Black dial - MSO Amp mod ADSR level control
				mso_amp_mod_adsr_level = update_rotary_encoder_value(
					mso_amp_mod_adsr_level,
					val,
					&prev_mso_amp_mod_adsr_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_MsoAmpModAdsrLevel->setValue(mso_amp_mod_adsr_level);
			}
		}
		else if (current_frame_index == 5)
		{
			// MSO Amp Mod and Segments (controls 1-8)
			if (evnt == _I2C_CONTROL_ENCODER_3)
			{
				// Gray Blue combobox - MSO Preset control
				mso_preset = update_rotary_encoder_value(
					mso_preset,
					val,
					&prev_mso_preset,
					mso_preset_min,
					mso_preset_max,
					1);

				ui->comboBox_MsoPreset->setCurrentIndex(mso_preset);
			}
			if (evnt == _I2C_CONTROL_ENCODER_5)
			{
				// Gray White combobox - MSO Amp mod LFO control
				mso_amp_mod_lfo = update_rotary_encoder_value(
					mso_amp_mod_lfo,
					val,
					&prev_mso_amp_mod_lfo,
					lfo_min,
					lfo_max,
					1);

				ui->comboBox_MsoAmpModLFO->setCurrentIndex(mso_amp_mod_lfo);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_6)
			{
				// Gray Yellow combobox - MSO Amp mod ADSR control
				mso_amp_mod_adsr = update_rotary_encoder_value(
					mso_amp_mod_adsr,
					val,
					&prev_mso_amp_mod_adsr,
					adsr_min,
					adsr_max,
					1);

				ui->comboBox_MsoAmpModAdsr->setCurrentIndex(mso_amp_mod_adsr);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_7)
			{
				// Gray Red dial - MSO Amp mod LFO level control
				mso_amp_mod_lfo_level = update_rotary_encoder_value(
					mso_amp_mod_lfo_level,
					val,
					&prev_mso_amp_mod_lfo_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_MsoAmpModLFOLevel->setValue(mso_amp_mod_lfo_level);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_8)
			{
				// Gray Black dial - MSO Amp mod ADSR level control
				mso_amp_mod_adsr_level = update_rotary_encoder_value(
					mso_amp_mod_adsr_level,
					val,
					&prev_mso_amp_mod_adsr_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_MsoAmpModAdsrLevel->setValue(mso_amp_mod_adsr_level);
			}
			else if (evnt == _I2C_CONTROL_SLIDER_1)
			{
				// Gray Gray slider - MSO Segment a control
				// Get new segment a value from slider and calculate gap from current UI value
				mso_segment_a = normalize_slider_value(val / 37, mso_segment_max, mso_segment_min); // 0-3700
				slider_level_gap = mso_segment_a - ui->verticalSlider_MSO_Pos_a->value();			// 1-2046

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((mso_segment_max - mso_segment_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_MSO_Pos_a->setValue(mso_segment_a);
				}
				
			}
			else if (evnt == _I2C_CONTROL_SLIDER_2)
			{
				// Gray Purple slider - MSO Segment b control
				// Get new segment b value from slider and calculate gap from current UI value
				mso_segment_b = normalize_slider_value(val / 37, mso_segment_max, mso_segment_min); // 0-3700
				slider_level_gap = mso_segment_b - ui->verticalSlider_MSO_Pos_b->value();			// 1-2046

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((mso_segment_max - mso_segment_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_MSO_Pos_b->setValue(mso_segment_b);
				}
				
			}
			else if (evnt == _I2C_CONTROL_SLIDER_3)
			{
				// Gray Blue slider - MSO Segment c control
				// Get new segment c value from slider and calculate gap from current UI value
				mso_segment_c = normalize_slider_value(val / 37, mso_segment_max, mso_segment_min); // 0-3700
				slider_level_gap = mso_segment_c - ui->verticalSlider_MSO_Pos_c->value();			// 1-2046

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((mso_segment_max - mso_segment_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_MSO_Pos_c->setValue(mso_segment_c);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_4)
			{
				// Gray Green slider - MSO Segment 4 control
				// Get new segment d value from slider and calculate gap from current UI value
				mso_segment_d = normalize_slider_value(val / 37, mso_segment_max, mso_segment_min); // 0-3700
				slider_level_gap = mso_segment_d - ui->verticalSlider_MSO_Pos_d->value();			// 1-2046

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((mso_segment_max - mso_segment_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_MSO_Pos_d->setValue(mso_segment_d);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_5)
			{
				// Gray White slider - MSO Segment e control
				// Get new segment e value from slider and calculate gap from current UI value
				mso_segment_e = normalize_slider_value(val / 37, mso_segment_max, mso_segment_min); // 0-3700
				slider_level_gap = mso_segment_e - ui->verticalSlider_MSO_Pos_e->value();			// 1-2046

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((mso_segment_max - mso_segment_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_MSO_Pos_e->setValue(mso_segment_e);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_6)
			{
				// Gray Yellow slider - MSO Segment f control
				// Get new segment f value from slider and calculate gap from current UI value
				mso_segment_f = normalize_slider_value(val / 37, mso_segment_max, mso_segment_min); // 0-3700
				slider_level_gap = mso_segment_f - ui->verticalSlider_MSO_Pos_f->value();			// 1-2046

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((mso_segment_max - mso_segment_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_MSO_Pos_f->setValue(mso_segment_f);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_7)
			{
				// Gray Yellow slider - MSO Morph control
				// Get new morf value from slider and calculate gap from current UI value
				mso_morph = normalize_slider_value(val / 37, mso_morph_max, mso_morph_min); // 0-3700
				slider_level_gap = mso_morph - ui->horizontalSlider_MsoMorph->value();			// 5-95

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((mso_morph_max - mso_morph_min) / 5.0))
				{
					// Emits value changed signal.
					ui->horizontalSlider_MsoMorph->setValue(mso_morph);
				}
			}

			// MSO PWM modulation (controls 9-12)
			else if (evnt == _I2C_CONTROL_ENCODER_9)
			{
				// white Gray combobox - MSO PWM mod LFO control
				mso_pwm_mod_lfo = update_rotary_encoder_value(
					mso_pwm_mod_lfo,
					val,
					&prev_mso_pwm_mod_lfo,
					lfo_min,
					lfo_max,
					1);

				ui->comboBox_MsoPwmModLFO->setCurrentIndex(mso_pwm_mod_lfo);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_10)
			{
				// White Purple combobox - MSO PWM mod ADSR control
				mso_pwm_mod_adsr = update_rotary_encoder_value(
					mso_pwm_mod_adsr,
					val,
					&prev_mso_pwm_mod_adsr,
					adsr_min,
					adsr_max,
					1);

				ui->comboBox_MsoPwmModAdsr->setCurrentIndex(mso_pwm_mod_adsr);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_11)
			{
				// White Blue dial - MSO PWM mod LFO level control
				mso_pwm_mod_lfo_level = update_rotary_encoder_value(
					mso_pwm_mod_lfo_level,
					val,
					&prev_mso_pwm_mod_lfo_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_MsoPwmModLFOLevel->setValue(mso_pwm_mod_lfo_level);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_12)
			{
				// White Green dial - MSO PWM mod ADSR level control
				mso_pwm_mod_adsr_level = update_rotary_encoder_value(
					mso_pwm_mod_adsr_level,
					val,
					&prev_mso_pwm_mod_adsr_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_MsoPwmModAdsrLevel->setValue(mso_pwm_mod_adsr_level);
			}
		}
		else if (current_frame_index == 6)
		{
			// Noise (controls 1-8)
			if (evnt == _I2C_CONTROL_ENCODER_2)
			{
				// Gray Purple dial - Noise send filter1 control
				noise_send_filter_1 = update_rotary_encoder_value(
					noise_send_filter_1,
					val,
					&prev_noise_send_filter_1,
					send_min,
					send_max,
					4);

				ui->dial_NoiseSendFilter1->setValue(noise_send_filter_1);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_3)
			{
				// Gray Blue dial - Noise send filter2 control
				noise_send_filter_2 = update_rotary_encoder_value(
					noise_send_filter_2,
					val,
					&prev_noise_send_filter_2,
					send_min,
					send_max,
					4);

				ui->dial_NoiseSendFilter2->setValue(noise_send_filter_2);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_4)
			{
				// Gray Green combobox - Noise color control
				noise_color = update_rotary_encoder_value(
					noise_color,
					val,
					&prev_noise_color,
					_WHITE_NOISE,
					_BROWN_NOISE,
					1);

				ui->comboBox_NoiseColor->setCurrentIndex(noise_color);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_5)
			{
				// Gray White dial - Noise Amp mod LFO control
				noise_amp_mod_lfo = update_rotary_encoder_value(
					noise_amp_mod_lfo,
					val,
					&prev_noise_amp_mod_lfo,
					lfo_min,
					lfo_max,
					1);

				ui->comboBox_NoiseAmpModLFO->setCurrentIndex(noise_amp_mod_lfo);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_6)
			{
				// Gray Yellow dial - Noise Amp mod ADSR control
				noise_amp_mod_adsr = update_rotary_encoder_value(
					noise_amp_mod_adsr,
					val,
					&prev_noise_amp_mod_adsr,
					adsr_min,
					adsr_max,
					1);

				ui->comboBox_NoiseAmpModAdsr->setCurrentIndex(noise_amp_mod_adsr);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_7)
			{
				// Gray Red dial - Noise Amp mod LFO level control
				noise_amp_mod_lfo_level = update_rotary_encoder_value(
					noise_amp_mod_lfo_level,
					val,
					&prev_noise_amp_mod_lfo_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_NoiseAmpModLFOLevel->setValue(noise_amp_mod_lfo_level);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_8)
			{
				// Gray Black dial - Noise Amp mod ADSR level control
				noise_amp_mod_adsr_level = update_rotary_encoder_value(
					noise_amp_mod_adsr_level,
					val,
					&prev_noise_amp_mod_adsr_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_NoiseAmpModAdsrLevel->setValue(noise_amp_mod_adsr_level);
			}

			// KPS (controls 9-16)
			
			else if (evnt == _I2C_CONTROL_ENCODER_10)
			{
				// White Purple dial - KPS send filter 1
				kps_send_filter_1 = update_rotary_encoder_value(
					kps_send_filter_1,
					val,
					&prev_kps_send_filter_1,
					send_min,
					send_max,
					4);

				ui->dial_KarplusSynth_SendFilter1->setValue(kps_send_filter_1);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_11)
			{
				// White Blue dial - KPS send filter 2
				kps_send_filter_2 = update_rotary_encoder_value(
					kps_send_filter_2,
					val,
					&prev_kps_send_filter_2,
					send_min,
					send_max,
					4);

				ui->dial_KarplusSynth_SendFilter2->setValue(kps_send_filter_2);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_12)
			{
				// White Green combobox - KPS Exitation Waveform control
				kps_excitation_waveform = update_rotary_encoder_value(
					kps_excitation_waveform,
					val,
					&prev_kps_excitation_waveform,
					kps_excitation_waveform_min,
					kps_excitation_waveform_max,
					1);

				ui->comboBox_KarplusSynth_ExcitationWaveform->setCurrentIndex(kps_excitation_waveform);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_13)
			{
				// White White combobox - KPS Damping Calculation control
				kps_damping_calculation = update_rotary_encoder_value(
					kps_damping_calculation,
					val,
					&prev_kps_damping_calculation,
					kps_damping_calculation_min,
					kps_damping_calculation_max,
					1);

				ui->comboBox_KarplusSynth_CalculationMode->setCurrentIndex(kps_damping_calculation);
			}
			else if (evnt == _I2C_CONTROL_SLIDER_9)
			{
				// White Gray slider - KPS waveform variations control
				// Get new waveform variations value from slider and calculate gap from current UI value
				kps_waveform_variations = normalize_slider_value(val / 37, kps_controls_max, kps_controls_min); // 0-3700
				slider_level_gap = kps_waveform_variations - ui->horizontalSlider_KarplusSynth_WaveformVariations->value();						 // 5-95

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((kps_controls_max - kps_controls_min) / 5.0))
				{
					// Emits value changed signal.
					ui->horizontalSlider_KarplusSynth_WaveformVariations->setValue(kps_waveform_variations);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_10)
			{
				// White Purple slider - KPS On Decay control
				// Get new on decay value from slider and calculate gap from current UI value
				kps_on_decay = normalize_slider_value(val / 37, kps_controls_max, kps_controls_min);				// 0-3700
				slider_level_gap = kps_on_decay - ui->horizontalSlider_KarplusSynth_OnDecay->value(); // 5-95

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((kps_controls_max - kps_controls_min) / 5.0))
				{
					// Emits value changed signal.
					ui->horizontalSlider_KarplusSynth_OnDecay->setValue(kps_on_decay);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_11)
			{
				// White Blue slider - KPS Off Decay control
				// Get new off decay value from slider and calculate gap from current UI value
				kps_off_decay = normalize_slider_value(val / 37, kps_controls_max, kps_controls_min);  // 0-3700
				slider_level_gap = kps_off_decay - ui->horizontalSlider_KarplusSynth_OffDecay->value(); // 5-95

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((kps_controls_max - kps_controls_min) / 5.0))
				{
					// Emits value changed signal.
					ui->horizontalSlider_KarplusSynth_OffDecay->setValue(kps_off_decay);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_12)
			{
				// White Green slider - KPS String Damping control
				// Get new string damping value from slider and calculate gap from current UI value
				kps_string_damping = normalize_slider_value(val / 37, kps_controls_max, kps_controls_min);  // 0-3700
				slider_level_gap = kps_string_damping - ui->horizontalSlider_KarplusSynth_StringDamping->value(); // 5-95

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((kps_controls_max - kps_controls_min) / 5.0))
				{
					// Emits value changed signal.
					ui->horizontalSlider_KarplusSynth_StringDamping->setValue(kps_string_damping);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_13)
			{
				// White White slider - KPS String Damping Variations control
				// Get new string damping variations value from slider and calculate gap from current UI value
				kps_string_damping_variations = normalize_slider_value(val / 37, kps_controls_max, kps_controls_min);		  // 0-3700
				slider_level_gap = kps_string_damping_variations - ui->horizontalSlider_KarplusSynth_StringDampingVariations->value(); // 5-95

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((kps_controls_max - kps_controls_min) / 5.0))
				{
					// Emits value changed signal.
					ui->horizontalSlider_KarplusSynth_StringDampingVariations->setValue(kps_string_damping_variations);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_14)
			{
				// White Yellow slider - KPS Pluck Damping control
				// Get new pluck damping value from slider and calculate gap from current UI value
				kps_pluck_damping = normalize_slider_value(val / 37, kps_controls_max, kps_controls_min);		  // 0-3700
				slider_level_gap = kps_pluck_damping - ui->horizontalSlider_KarplusSynth_PluckDamping->value(); // 5-95

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((kps_controls_max - kps_controls_min) / 5.0))
				{
					// Emits value changed signal.
					ui->horizontalSlider_KarplusSynth_PluckDamping->setValue(kps_pluck_damping);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_15)
			{
				// White Red slider - KPS Pluck Damping Variations control
				// Get new pluck damping variations value from slider and calculate gap from current UI value
				kps_pluck_damping_variations = normalize_slider_value(val / 37, kps_controls_max, kps_controls_min);		// 0-3700
				slider_level_gap = kps_pluck_damping_variations - ui->horizontalSlider_KarplusSynth_PluckDampingVariations->value(); // 5-95

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((kps_controls_max - kps_controls_min) / 5.0))
				{
					// Emits value changed signal.
					ui->horizontalSlider_KarplusSynth_PluckDampingVariations->setValue(kps_pluck_damping_variations);
				}
			}
		}
		else if (current_frame_index == 7)
		{
			// Pad Send and Tune (controls 1-8)
			if (evnt == _I2C_CONTROL_ENCODER_2)
			{
				// Gray Purple dial - Pad send filter1 control
				pad_send_filter_1 = update_rotary_encoder_value(
					pad_send_filter_1,
					val,
					&prev_pad_send_filter_1,
					send_min,
					send_max,
					4);

				ui->dial_PadSendFilter1->setValue(pad_send_filter_1);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_3)
			{
				// Gray Blue dial - Pad send filter2 control
				pad_send_filter_2 = update_rotary_encoder_value(
					pad_send_filter_2,
					val,
					&prev_pad_send_filter_2,
					send_min,
					send_max,
					4);

				ui->dial_PadSendFilter2->setValue(pad_send_filter_2);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_5)
			{
				// Gray white combobox - Pad tune octave control
				pad_tune_offset_octave = update_rotary_encoder_value(
					pad_tune_offset_octave,
					val,
					&prev_pad_tune_offset_octave,
					tune_offset_octave_min,
					tune_offset_octave_max,
					1);

				ui->comboBox_PadTuneOctave->setCurrentIndex(pad_tune_offset_octave);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_6)
			{
				// Gray Yellow combobox - Pad tune semitones control
				pad_tune_offset_semitone = update_rotary_encoder_value(
					pad_tune_offset_semitone,
					val,
					&prev_pad_tune_offset_semitone,
					tune_offset_semitone_min,
					tune_offset_semitone_max,
					1);

				ui->comboBox_PadTuneSemitones->setCurrentIndex(pad_tune_offset_semitone);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_7)
			{
				// Gray Red dial - Pad Tune cents control
				pad_tune_offset_cents = update_rotary_encoder_value(
					pad_tune_offset_cents,
					val,
					&prev_pad_tune_offset_cents,
					tune_offset_cents_min,
					tune_offset_cents_max,
					1);

				ui->comboBox_PadTuneCents->setCurrentIndex(pad_tune_offset_cents);
			}

			// Pad Freq and Amp Mod (controls 9-16)
			else if (evnt == _I2C_CONTROL_ENCODER_9)
			{
				// White Gray combobox - Pad freq mod LFO control
				pad_freq_mod_lfo = update_rotary_encoder_value(
					pad_freq_mod_lfo,
					val,
					&prev_pad_freq_mod_lfo,
					lfo_min,
					lfo_max,
					1);

				ui->comboBox_PadFreqModLFO->setCurrentIndex(pad_freq_mod_lfo);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_10)
			{
				// White Purple combobox - Pad freq mod ADSR control
				pad_freq_mod_adsr = update_rotary_encoder_value(
					pad_freq_mod_adsr,
					val,
					&prev_pad_freq_mod_adsr,
					adsr_min,
					adsr_max,
					1);

				ui->comboBox_PadFreqModAdsr->setCurrentIndex(pad_freq_mod_adsr);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_11)
			{
				// White Blue dial - Pad freq mod LFO level control
				pad_freq_mod_lfo_level = update_rotary_encoder_value(
					pad_freq_mod_lfo_level,
					val,
					&prev_pad_freq_mod_lfo_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_PadFreqModLFOLevel->setValue(pad_freq_mod_lfo_level);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_12)
			{
				// White Green dial - Pad freq mod ADSR level control
				pad_freq_mod_adsr_level = update_rotary_encoder_value(
					pad_freq_mod_adsr_level,
					val,
					&prev_pad_freq_mod_adsr_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_PadFreqModAdsrLevel->setValue(pad_freq_mod_adsr_level);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_13)
			{
				// White White combobox - Pad Amp mod LFO control
				pad_amp_mod_lfo = update_rotary_encoder_value(
					pad_amp_mod_lfo,
					val,
					&prev_pad_amp_mod_lfo,
					lfo_min,
					lfo_max,
					1);

				ui->comboBox_PadAmpModLFO->setCurrentIndex(pad_amp_mod_lfo);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_14)
			{
				// White Yellow combobox - Pad Amp mod ADSR
				pad_amp_mod_adsr = update_rotary_encoder_value(
					pad_amp_mod_adsr,
					val,
					&prev_pad_amp_mod_adsr,
					adsr_min,
					adsr_max,
					1);

				ui->comboBox_PadAmpModAdsr->setCurrentIndex(pad_amp_mod_adsr);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_15)
			{
				// White Red dial - Pad Amp mod LFO level control
				pad_amp_mod_lfo_level = update_rotary_encoder_value(
					pad_amp_mod_lfo_level,
					val,
					&prev_pad_amp_mod_lfo_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_PadAmpModLFOLevel->setValue(pad_amp_mod_lfo_level);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_16)
			{
				// White Black dial - Pad Amp mod ADSR level control
				pad_amp_mod_adsr_level = update_rotary_encoder_value(
					pad_amp_mod_adsr_level,
					val,
					&prev_pad_amp_mod_adsr_level,
					modulation_min,
					modulation_max,
					4);

				ui->dial_PadAmpModAdsrLevel->setValue(pad_amp_mod_adsr_level);
			}
		}
		else if (current_frame_index == 8)
		{
			// Pad Harmonics 1-6 and Profile (controls 1-8)
			if (evnt == _I2C_CONTROL_SLIDER_1)
			{
				// Gray Gray slider - Pad Harmonic 1 control
				// Get new harmony 1 level value from slider and calculate gap from current UI value
				pad_harmony_1_level = normalize_slider_value(val / 37, pad_control_max, pad_control_min); // 0-3700
				slider_level_gap = pad_harmony_1_level - ui->verticalSlider_PadHarmony_1->value();		// 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((pad_control_max - pad_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_PadHarmony_1->setValue(pad_harmony_1_level);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_2)
			{
				// Gray Purple slider - Pad Harmonic 2 control
				// Get new harmony 2 level value from slider and calculate gap from current UI value
				pad_harmony_2_level = normalize_slider_value(val / 37, pad_control_max, pad_control_min); // 0-3700
				slider_level_gap = pad_harmony_2_level - ui->verticalSlider_PadHarmony_2->value();		  // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((pad_control_max - pad_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_PadHarmony_2->setValue(pad_harmony_2_level);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_3)
			{
				// Gray Blue slider - Pad Harmonic 3 control
				// Get new harmony 3 level value from slider and calculate gap from current UI value
				pad_harmony_3_level = normalize_slider_value(val / 37, pad_control_max, pad_control_min); // 0-3700
				slider_level_gap = pad_harmony_3_level - ui->verticalSlider_PadHarmony_3->value();		  // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((pad_control_max - pad_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_PadHarmony_3->setValue(pad_harmony_3_level);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_4)
			{
				// Gray Green slider - Pad Harmonic 4 control
				// Get new harmony 4 level value from slider and calculate gap from current UI value
				pad_harmony_4_level = normalize_slider_value(val / 37, pad_control_max, pad_control_min); // 0-3700
				slider_level_gap = pad_harmony_4_level - ui->verticalSlider_PadHarmony_4->value();		  // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((pad_control_max - pad_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_PadHarmony_4->setValue(pad_harmony_4_level);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_5)
			{
				// Gray White slider - Pad Harmonic 5 control
				// Get new harmony 5 level value from slider and calculate gap from current UI value
				pad_harmony_5_level = normalize_slider_value(val / 37, pad_control_max, pad_control_min); // 0-3700
				slider_level_gap = pad_harmony_5_level - ui->verticalSlider_PadHarmony_5->value();		  // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((pad_control_max - pad_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_PadHarmony_5->setValue(pad_harmony_5_level);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_6)
			{
				// Gray Yellow slider - Pad Harmonic 6 control
				// Get new harmony 6 level value from slider and calculate gap from current UI value
				pad_harmony_6_level = normalize_slider_value(val / 37, pad_control_max, pad_control_min); // 0-3700
				slider_level_gap = pad_harmony_6_level - ui->verticalSlider_PadHarmony_6->value();		  // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((pad_control_max - pad_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_PadHarmony_6->setValue(pad_harmony_6_level);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_7)
			{
				// Gray Red slider - Pad Profile Base Width control
				// Get new base width value from slider and calculate gap from current UI value
				pad_base_width = normalize_slider_value(val / 37, pad_base_width_max, pad_base_width_min); // 0-3700
				slider_level_gap = pad_base_width - ui->horizontalSlider_PadBaseWidth->value();		  // 5-95

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((pad_base_width_max - pad_base_width_min) / 5.0))
				{
					// Emits value changed signal.
					ui->horizontalSlider_PadBaseWidth->setValue(pad_base_width);
				}
			}
			else if (evnt == _I2C_CONTROL_ENCODER_2)
			{
				// Gray Purple combobox - Pad Quality control
				pad_quality = update_rotary_encoder_value(
					pad_quality,
					val,
					&prev_pad_quality,
					pad_quality_min,
					pad_quality_max,
					1);

				ui->comboBox_PadQuality->setCurrentIndex(pad_quality);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_3)
			{
				// Gray Blue combobox - Pad Shape control
				pad_shape = update_rotary_encoder_value(
					pad_shape,
					val,
					&prev_pad_shape,
					pad_shape_min,
					pad_shape_max,
					1);

				ui->comboBox_PadShape->setCurrentIndex(pad_shape);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_4)
			{
				// Gray Green combobox - Pad Shape Cutoff control
				pad_shape_cutoff = update_rotary_encoder_value(
					pad_shape_cutoff,
					val,
					&pad_shape_cutoff,
					pad_shape_cutoff_min,
					pad_shape_cutoff_max,
					1);

				ui->comboBox_PadShapeCutoff->setCurrentIndex(pad_shape_cutoff);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_6)
			{
				// Gray Yellow combobox - Pad Base Note control
				pad_base_note = update_rotary_encoder_value(
					pad_base_note,
					val,
					&prev_pad_base_note,
					pad_base_note_min,
					pad_base_note_max,
					1);

				ui->comboBox_PadBaseNote->setCurrentIndex(pad_base_note);
			}

			// Pad Harmonics 7-10 (controls 9-16)
			else if (evnt == _I2C_CONTROL_SLIDER_9)
			{
				// White Gray slider - Pad Harmonic 7 control
				// Get new harmony 7 level value from slider and calculate gap from current UI value
				pad_harmony_7_level = normalize_slider_value(val / 37, pad_control_max, pad_control_min); // 0-3700
				slider_level_gap = pad_harmony_7_level - ui->verticalSlider_PadHarmony_7->value();		  // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((pad_control_max - pad_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_PadHarmony_7->setValue(pad_harmony_7_level);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_10)
			{
				// White Purple slider - Pad Harmonic 8 control
				// Get new harmony 8 level value from slider and calculate gap from current UI value
				pad_harmony_8_level = normalize_slider_value(val / 37, pad_control_max, pad_control_min); // 0-3700
				slider_level_gap = pad_harmony_8_level - ui->verticalSlider_PadHarmony_8->value();		  // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((pad_control_max - pad_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_PadHarmony_8->setValue(pad_harmony_8_level);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_11)
			{
				// White Blue slider - Pad Harmonic 9 control
				// Get new harmony 9 level value from slider and calculate gap from current UI value
				pad_harmony_9_level = normalize_slider_value(val / 37, pad_control_max, pad_control_min); // 0-3700
				slider_level_gap = pad_harmony_9_level - ui->verticalSlider_PadHarmony_9->value();		  // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((pad_control_max - pad_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_PadHarmony_9->setValue(pad_harmony_9_level);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_12)
			{
				// White green slider - Pad Harmonic 10 control
				// Get new harmony 10 level value from slider and calculate gap from current UI value
				pad_harmony_10_level = normalize_slider_value(val / 37, pad_control_max, pad_control_min); // 0-3700
				slider_level_gap = pad_harmony_10_level - ui->verticalSlider_PadHarmony_10->value();		  // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((pad_control_max - pad_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_PadHarmony_10->setValue(pad_harmony_10_level);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_13)
			{
				// White White slider - Pad Harmony Detune Level control
				// Get new harmonies detune level value from slider and calculate gap from current UI value
				pad_harmonies_detune = normalize_slider_value(val / 37, pad_control_max, pad_control_min); // 0-3700
				slider_level_gap = pad_harmonies_detune - ui->verticalSlider_PadHarmonyDetune->value();		  // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((pad_control_max - pad_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_PadHarmonyDetune->setValue(pad_harmonies_detune);
				}
			}
		}
	}
	else if (current_tab_index == 1)
	{
		// Processors
		if (current_frame_index == 0)
		{
			// Filter 1 (controls 1-8)
			if (evnt == _I2C_CONTROL_ENCODER_2)
			{
				// Gray Purple dial - Filter 1 frequency control
				filter_1_freq = update_rotary_encoder_value(
					filter_1_freq,
					val,
					&prev_filter_1_freq,
					filter_frequency_min,
					filter_frequency_max,
					4);

				ui->dial_FilterFreq_1->setValue(filter_1_freq);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_3)
			{
				// Gray Blue dial - Filter 1 modulation octave control
				filter_1_mod_octave = update_rotary_encoder_value(
					filter_1_mod_octave,
					val,
					&prev_filter_1_mod_octave,
					filter_modulation_octave_min,
					filter_modulation_octave_max,
					4);

				ui->dial_FilterOctave_1->setValue(filter_1_mod_octave);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_4)
			{
				// Gray Green dial - Filter 1 Q control
				filter_1_q = update_rotary_encoder_value(
					filter_1_q,
					val,
					&prev_filter_1_q,
					filter_q_min,
					filter_q_max,
					4);

				ui->dial_FilterQ_1->setValue(filter_1_q);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_5)
			{
				// Gray White dial - Filter 1 keboard track control
				filter_1_kbd_track = update_rotary_encoder_value(
					filter_1_kbd_track,
					val,
					&prev_filter_1_kbd_track,
					filter_kbd_track_min,
					filter_kbd_track_max,
					4);

				ui->dial_FilterKbdTrack_1->setValue(filter_1_kbd_track);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_6)
			{
				// Gray Yellow combobox - Filter 1 frequency modulation LFO control
				filter_1_frequency_modulation_lfo = update_rotary_encoder_value(
					filter_1_frequency_modulation_lfo,
					val,
					&prev_filter_1_frequency_modulation_lfo,
					lfo_min,
					lfo_max,
					1);

				ui->comboBox_FilterFreqModLfo_1->setCurrentIndex(filter_1_frequency_modulation_lfo);
				
			}
			else if (evnt == _I2C_CONTROL_ENCODER_7)
			{
				// Gray Red combobox - Filter 1 frequency modulation ADSR control
				filter_1_frequency_modulation_adsr = update_rotary_encoder_value(
					filter_1_frequency_modulation_adsr,
					val,
					&prev_filter_1_frequency_modulation_adsr,
					adsr_min,
					adsr_max,
					1);

				ui->comboBox_FilterFreqModAdsr_1->setCurrentIndex(filter_1_frequency_modulation_adsr);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_1)
			{
				// Gray Gray combobox - Filter 1 band control
				filter_1_band = update_rotary_encoder_value(
					filter_1_band,
					val,
					&prev_filter_1_band,
					filter_band_min,
					filter_band_max,
					1);

				ui->comboBox_FilterBand_1->setCurrentIndex(filter_1_band);
			}
			else if (evnt == _I2C_CONTROL_SLIDER_2)
			{
				// Gray Purple slider - Filter 1 frequency modulation LFO level control
				// Get new Filter 1 frequency modulation LFO levelvalue from slider and calculate gap from current UI value
				filter_1_frequency_modulation_lfo_level = normalize_slider_value(val / 36, modulation_max, modulation_min); // 0-3600
				slider_level_gap = filter_1_frequency_modulation_lfo_level - ui->verticalSlider_FilterFreqModLfoLevel_1->value();		// 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((modulation_max - modulation_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_FilterFreqModLfoLevel_1->setValue(filter_1_frequency_modulation_lfo_level);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_3)
			{
				// Gray Blue slider - Filter 1 frequency modulation ADSR level control
				// Get new Filter 1 frequency modulation ADSR levelvalue from slider and calculate gap from current UI value
				filter_1_frequency_modulation_adsr_level = normalize_slider_value(val / 36, modulation_max, modulation_min);	  // 0-3600
				slider_level_gap = filter_1_frequency_modulation_adsr_level - ui->verticalSlider_FilterFreqModAdsrLevel_1->value(); // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((modulation_max - modulation_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_FilterFreqModAdsrLevel_1->setValue(filter_1_frequency_modulation_adsr_level);
				}
			}

			// Filter 2 (controls 9-16)
			else if (evnt == _I2C_CONTROL_ENCODER_10)
			{
				// White Purple dial - Filter 2 frequency control
				filter_2_freq = update_rotary_encoder_value(
					filter_2_freq,
					val,
					&prev_filter_2_freq,
					filter_frequency_min,
					filter_frequency_max,
					4);

				ui->dial_FilterFreq_2->setValue(filter_2_freq);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_11)
			{
				// White Blue dial - Filter 2 modulation octave control
				filter_2_mod_octave = update_rotary_encoder_value(
					filter_2_mod_octave,
					val,
					&prev_filter_2_mod_octave,
					filter_modulation_octave_min,
					filter_modulation_octave_max,
					4);

				ui->dial_FilterOctave_2->setValue(filter_2_mod_octave);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_12)
			{
				// White Green dial - Filter 2 Q control
				filter_2_q = update_rotary_encoder_value(
					filter_2_q,
					val,
					&prev_filter_2_q,
					filter_q_min,
					filter_q_max,
					4);

				ui->dial_FilterQ_2->setValue(filter_2_q);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_13)
			{
				// White White dial - Filter 2 keyboard track control
				filter_2_kbd_track = update_rotary_encoder_value(
					filter_2_kbd_track,
					val,
					&prev_filter_2_kbd_track,
					filter_kbd_track_min,
					filter_kbd_track_max,
					4);

				ui->dial_FilterKbdTrack_2->setValue(filter_2_kbd_track);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_14)
			{
				// White Yellow combobox - Filter 2 frequency modulation LFO control
				filter_2_frequency_modulation_lfo = update_rotary_encoder_value(
					filter_2_frequency_modulation_lfo,
					val,
					&prev_filter_2_frequency_modulation_lfo,
					lfo_min,
					lfo_max,
					1);

				ui->comboBox_FilterFreqModLfo_2->setCurrentIndex(filter_2_frequency_modulation_lfo);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_15)
			{
				// White Red combobox - Filter 2 frequency modulation ADSR control
				filter_2_frequency_modulation_adsr = update_rotary_encoder_value(
					filter_2_frequency_modulation_adsr,
					val,
					&prev_filter_2_frequency_modulation_adsr,
					adsr_min,
					adsr_max,
					1);

				ui->comboBox_FilterFreqModAdsr_2->setCurrentIndex(filter_2_frequency_modulation_adsr);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_16)
			{
				// White Gray combobox - Filter 2 band control
				filter_2_band = update_rotary_encoder_value(
					filter_2_band,
					val,
					&prev_filter_2_band,
					filter_band_min,
					filter_band_max,
					1);

				ui->comboBox_FilterBand_2->setCurrentIndex(filter_2_band);
			}
			else if (evnt == _I2C_CONTROL_SLIDER_10)
			{
				// White Purple slider - Filter 2 frequency modulation LFO level control
				// Get new Filter 2 frequency modulation LFO levelvalue from slider and calculate gap from current UI value
				filter_2_frequency_modulation_lfo_level = normalize_slider_value(val / 36, modulation_max, modulation_min); // 0-3600
				slider_level_gap = filter_2_frequency_modulation_lfo_level - ui->verticalSlider_FilterFreqModLfoLevel_2->value(); // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((modulation_max - modulation_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_FilterFreqModLfoLevel_2->setValue(filter_2_frequency_modulation_lfo_level);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_11)
			{
				// White Blue slider - Filter 2 frequency modulation ADSR level control
				// Get new Filter 2 frequency modulation ADSR levelvalue from slider and calculate gap from current UI value
				filter_2_frequency_modulation_adsr_level = normalize_slider_value(val / 36, modulation_max, modulation_min); // 0-3600
				slider_level_gap = filter_2_frequency_modulation_adsr_level - ui->verticalSlider_FilterFreqModAdsrLevel_2->value(); // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((modulation_max - modulation_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_FilterFreqModAdsrLevel_2->setValue(filter_2_frequency_modulation_adsr_level);
				}
			}
		}
		else if (current_frame_index == 1)
		{
			// Distortion (controls 1-8)
			if (evnt == _I2C_CONTROL_ENCODER_2)
			{
				// Gray Purple dial - Distortion 1 drive control
				distortion_1_drive = update_rotary_encoder_value(
					distortion_1_drive,
					val,
					&prev_distortion_1_drive,
					distortion_control_min,
					distortion_control_max,
					4);

				ui->dial_DistortionDrive_1->setValue(distortion_1_drive);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_3)
			{
				// Gray Blue dial - Distortion 1 range control
				distortion_1_range = update_rotary_encoder_value(
					distortion_1_range,
					val,
					&prev_distortion_1_range,
					distortion_control_min,
					distortion_control_max,
					4);

				ui->dial_DistortionRange_1->setValue(distortion_1_range);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_4)
			{
				// Gray Green dial - Distortion 1 blend control
				distortion_1_blend = update_rotary_encoder_value(
					distortion_1_blend,
					val,
					&prev_distortion_1_blend,
					distortion_control_min,
					distortion_control_max,
					4);

				ui->dial_DistortionBlend_1->setValue(distortion_1_blend);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_5)
			{
				// Gray White dial - Distortion 2 drive control
				distortion_2_drive = update_rotary_encoder_value(
					distortion_2_drive,
					val,
					&prev_distortion_2_drive,
					distortion_control_min,
					distortion_control_max,
					4);

				ui->dial_DistortionDrive_2->setValue(distortion_2_drive);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_6)
			{
				// Gray Yellow dial - Distortion 2 range control
				distortion_2_range = update_rotary_encoder_value(
					distortion_2_range,
					val,
					&prev_distortion_2_range,
					distortion_control_min,
					distortion_control_max,
					4);

				ui->dial_DistortionRange_2->setValue(distortion_2_range);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_7)
			{
				// Gray Red dial - Distortion 2 blend control
				distortion_2_blend = update_rotary_encoder_value(
					distortion_2_blend,
					val,
					&prev_distortion_2_blend,
					distortion_control_min,
					distortion_control_max,
					4);

				ui->dial_DistortionBlend_2->setValue(distortion_2_blend);
			}

			// Reverb (controls 9-16)
			else if (evnt == _I2C_CONTROL_ENCODER_10)
			{
				// White Purple combobox - Reverb 3 type control
				reverb_preset = update_rotary_encoder_value(
					reverb_preset,
					val,
					&prev_reverb_preset,
					reverb_preset_min,
					reverb_preset_max,
					1);

				ui->comboBox_ReverbType->setCurrentIndex(reverb_preset);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_11)
			{
				// White Blue dial - Reverb room size control
				reverb_room_size = update_rotary_encoder_value(
					reverb_room_size,
					val,
					&prev_reverb_room_size,
					reverb_room_size_min,
					reverb_room_size_max,
					4);

				ui->dial_ReverbRoomSize->setValue(reverb_room_size);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_12)
			{
				// White Green dial - Reverb damp control
				reverb_damping = update_rotary_encoder_value(
					reverb_damping,
					val,
					&prev_reverb_damping,
					reverb_control_min,
					reverb_control_max,
					4);

				ui->dial_ReverbDamp->setValue(reverb_damping);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_13)
			{
				// White White dial - Reverb wet control
				reverb_wet = update_rotary_encoder_value(
					reverb_wet,
					val,
					&prev_reverb_wet,
					reverb_control_min,
					reverb_control_max,
					4);

				ui->dial_ReverbWet->setValue(reverb_wet);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_14)
			{
				// White Yellow combobox - Reverb dry control
				reverb_dry = update_rotary_encoder_value(
					reverb_dry,
					val,
					&prev_reverb_dry,
					reverb_control_min,
					reverb_control_max,
					4);

				ui->dial_ReverbDry->setValue(reverb_dry);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_15)
			{
				// White Red combobox - Reverb width control
				reverb_width = update_rotary_encoder_value(
					reverb_width,
					val,
					&prev_reverb_width,
					reverb_width_min,
					reverb_control_max,
					4);

				ui->dial_ReverbWidth->setValue(reverb_width);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_16)
			{
				// White Black dial - Reverb mode control
				reverb_mode = update_rotary_encoder_value(
					reverb_mode,
					val,
					&prev_reverb_mode,
					reverb_control_min,
					reverb_mode_max,
					4);

				ui->dial_ReverbMode->setValue(reverb_mode);
			}
		}
		else if (current_frame_index == 2)
		{
			// Equalizer (controls 1-8)
			if (evnt == _I2C_CONTROL_ENCODER_3)
			{
				// Gray Blue combobox - Equalizer preset control
				// TODO:
			}
			else if (evnt == _I2C_CONTROL_SLIDER_1)
			{
				// Gray Gray slider - Equalizer 31Hz control
				// Get new equalizer band value from slider and calculate gap from current UI value
				prev_eqalizer_band[0] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min);	// 0-3600
				slider_level_gap = prev_eqalizer_band[0] - ui->verticalSlider_BandEquilizer31->value();			// 0-40

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_BandEquilizer31->setValue(prev_eqalizer_band[0]);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_2)
			{
				// Gray Purple slider - Equalizer 62Hz control
				// Get new equalizer band value from slider and calculate gap from current UI value
				prev_eqalizer_band[1] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
				slider_level_gap = prev_eqalizer_band[1] - ui->verticalSlider_BandEquilizer62->value();			// 0-40

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_BandEquilizer62->setValue(prev_eqalizer_band[1]);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_3)
			{
				// Gray Blue slider - Equalizer 125Hz control
				// Get new equalizer band value from slider and calculate gap from current UI value
				prev_eqalizer_band[2] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
				slider_level_gap = prev_eqalizer_band[2] - ui->verticalSlider_BandEquilizer125->value();		// 0-40

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_BandEquilizer125->setValue(prev_eqalizer_band[2]);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_4)
			{
				// Gray Green slider - Equalizer 250Hz control
				// Get new equalizer band value from slider and calculate gap from current UI value
				prev_eqalizer_band[3] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
				slider_level_gap = prev_eqalizer_band[3] - ui->verticalSlider_BandEquilizer250->value();		// 0-40

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_BandEquilizer250->setValue(prev_eqalizer_band[3]);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_5)
			{
				// Gray White slider - Equalizer 500Hz control
				// Get new equalizer band value from slider and calculate gap from current UI value
				prev_eqalizer_band[4] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
				slider_level_gap = prev_eqalizer_band[4] - ui->verticalSlider_BandEquilizer500->value();		// 0-40

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_BandEquilizer500->setValue(prev_eqalizer_band[4]);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_6)
			{
				// Gray Yellow slider - Equalizer 1KHz control
				// Get new equalizer band value from slider and calculate gap from current UI value
				prev_eqalizer_band[5] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
				slider_level_gap = prev_eqalizer_band[5] - ui->verticalSlider_BandEquilizer1K->value();			// 0-40

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_BandEquilizer1K->setValue(prev_eqalizer_band[5]);
				}	
			}
			else if (evnt == _I2C_CONTROL_SLIDER_7)
			{
				// Gray Red slider - Equalizer 2KHz control
				// Get new equalizer band value from slider and calculate gap from current UI value
				prev_eqalizer_band[6] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
				slider_level_gap = prev_eqalizer_band[6] - ui->verticalSlider_BandEquilizer2K->value();			// 0-40

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_BandEquilizer2K->setValue(prev_eqalizer_band[6]);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_8)
			{
				// Gray Black slider - Equalizer 4KHz control
				// Get new equalizer band value from slider and calculate gap from current UI value
				prev_eqalizer_band[7] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
				slider_level_gap = prev_eqalizer_band[7] - ui->verticalSlider_BandEquilizer4K->value();			// 0-40

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_BandEquilizer4K->setValue(prev_eqalizer_band[7]);
				}
			}

			// Equalizer 8 and 16KHz (controls 9-16)
			else if (evnt == _I2C_CONTROL_SLIDER_9)
			{
				// White Gray slider - Equalizer 8KHz control
				// Get new equalizer band value from slider and calculate gap from current UI value
				prev_eqalizer_band[8] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
				slider_level_gap = prev_eqalizer_band[8] - ui->verticalSlider_BandEquilizer8K->value();			// 0-40

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_BandEquilizer8K->setValue(prev_eqalizer_band[8]);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_10)
			{
				// White Purple slider - Equalizer 16KHz control
				// Get new equalizer band value from slider and calculate gap from current UI value
				prev_eqalizer_band[9] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
				slider_level_gap = prev_eqalizer_band[9] - ui->verticalSlider_BandEquilizer16K->value();		// 0-40

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_BandEquilizer16K->setValue(prev_eqalizer_band[9]);
				}
			}
		}
	}
	else if (current_tab_index == 2)
	{
		// Modulators
		if ((current_frame_index == 0) || (current_frame_index == 1))
		{
			// LFO 1-2 and ADSR 1-2 (controls 1-8) - unchanged in frame 1
			if (evnt == _I2C_CONTROL_ENCODER_1)
			{
				// Gray Gray dial - LFO 1 symetry control
				lfo_symmetry[0] = update_rotary_encoder_value(
					lfo_symmetry[0],
					val,
					&prev_lfo_symmetry[0],
					lfo_control_min,
					lfo_control_max,
					4);

				ui->dial_LFOsymmetry_1->setValue(lfo_symmetry[0]);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_2)
			{
				// Gray Purple dial - LFO 1 rate filter1 control
				lfo_rate[0] = update_rotary_encoder_value(
					lfo_rate[0],
					val,
					&prev_lfo_rate[0],
					lfo_control_min,
					lfo_control_max,
					4);

				ui->dial_LFOrate_1->setValue(lfo_rate[0]);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_3)
			{
				// Gray Blue combobox - LFO 1 waveform control
				lfo_waveform[0] = update_rotary_encoder_value(
					lfo_waveform[0],
					val,
					&prev_lfo_waveform[0],
					lfo_waveform_min,
					lfo_waveform_max,
					1);

				ui->comboBox_LFOwaveform_1->setCurrentIndex(lfo_waveform[0]);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_4)
			{
				// Gray Green combobox - LFO 2 symmetry control
				lfo_symmetry[1] = update_rotary_encoder_value(
					lfo_symmetry[1],
					val,
					&prev_lfo_symmetry[1],
					lfo_control_min,
					lfo_control_max,
					4);

				ui->dial_LFOsymmetry_2->setValue(lfo_symmetry[1]);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_5)
			{
				// Gray White combobox - LFO 2 rate control
				lfo_rate[1] = update_rotary_encoder_value(
					lfo_rate[1],
					val,
					&prev_lfo_rate[1],
					lfo_control_min,
					lfo_control_max,
					4);

				ui->dial_LFOrate_2->setValue(lfo_rate[1]);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_6)
			{
				// Gray Yellow combobox - LFO 2 waveform control
				lfo_waveform[1] = update_rotary_encoder_value(
					lfo_waveform[1],
					val,
					&prev_lfo_waveform[1],
					lfo_waveform_min,
					lfo_waveform_max,
					1);

				ui->comboBox_LFOwaveform_2->setCurrentIndex(lfo_waveform[1]);
			}
			else if (evnt == _I2C_CONTROL_SLIDER_1)
			{
				// Gray Gray slider - ADSR A control
				// Get new ADSR A1 value from slider and calculate gap from current UI value
				adsr_attack[0] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
				slider_level_gap = adsr_attack[0] - ui->verticalSlider_AdsrA_1->value();				// 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_AdsrA_1->setValue(adsr_attack[0]);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_2)
			{
				// Gray Purple slider - ADSR 1 D control
				// Get new ADSR D1 value from slider and calculate gap from current UI value
				adsr_decay[0] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
				slider_level_gap = adsr_decay[0] - ui->verticalSlider_AdsrD_1->value();			   // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_AdsrD_1->setValue(adsr_decay[0]);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_3)
			{
				// Gray Blue slider - ADSR 1 S control
				// Get new ADSR S1 value from slider and calculate gap from current UI value
				adsr_sustain[0] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
				slider_level_gap = adsr_sustain[0] - ui->verticalSlider_AdsrS_1->value();				// 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_AdsrS_1->setValue(adsr_sustain[0]);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_4)
			{
				// Gray Green slider - ADSR 1 R control
				// Get new ADSR R1 value from slider and calculate gap from current UI value
				adsr_release[0] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
				slider_level_gap = adsr_release[0] - ui->verticalSlider_AdsrR_1->value();				// 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_AdsrR_1->setValue(adsr_release[0]);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_5)
			{
				// Gray White slider - ADSR 2 A control
				// Get new ADSR A2 value from slider and calculate gap from current UI value
				adsr_attack[1] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
				slider_level_gap = adsr_attack[1] - ui->verticalSlider_AdsrA_2->value();			   // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_AdsrA_2->setValue(adsr_attack[1]);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_6)
			{
				// Gray Yellow slider - ADSR 2 D control
				// Get new ADSR D2 value from slider and calculate gap from current UI value
				adsr_decay[1] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
				slider_level_gap = adsr_decay[1] - ui->verticalSlider_AdsrD_2->value();				  // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_AdsrD_2->setValue(adsr_decay[1]);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_7)
			{
				// Gray Red slider - ADSR 2 S control
				// Get new ADSR S2 value from slider and calculate gap from current UI value
				adsr_sustain[1] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
				slider_level_gap = adsr_sustain[1] - ui->verticalSlider_AdsrS_2->value();				// 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_AdsrS_2->setValue(adsr_sustain[1]);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_8)
			{
				// Gray Black slider - ADSR 2 R control
				// Get new ADSR R2 value from slider and calculate gap from current UI value
				adsr_release[1] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
				slider_level_gap = adsr_release[1] - ui->verticalSlider_AdsrR_2->value();				// 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
				{
					// Emits value changed signal.
					ui->verticalSlider_AdsrR_2->setValue(adsr_release[1]);
				}
			}

			if (current_frame_index == 0)
			{
				// LFO 3-4 and ADSR 3-4 (controls 9-16)
				if (evnt == _I2C_CONTROL_ENCODER_9)
				{
					// Gray Gray dial - LFO 3 symetry control
					lfo_symmetry[2] = update_rotary_encoder_value(
						lfo_symmetry[2],
						val,
						&prev_lfo_symmetry[2],
						lfo_control_min,
						lfo_control_max,
						4);

					ui->dial_LFOsymmetry_3->setValue(lfo_symmetry[2]);
				}
				else if (evnt == _I2C_CONTROL_ENCODER_10)
				{
					// White Purple dial - LFO 3 rate filter1 control
					lfo_rate[2] = update_rotary_encoder_value(
						lfo_rate[2],
						val,
						&prev_lfo_rate[2],
						lfo_control_min,
						lfo_control_max,
						4);

					ui->dial_LFOrate_3->setValue(lfo_rate[2]);
				}
				else if (evnt == _I2C_CONTROL_ENCODER_11)
				{
					// White Blue combobox - LFO 3 waveform control
					lfo_waveform[2] = update_rotary_encoder_value(
						lfo_waveform[2],
						val,
						&prev_lfo_waveform[2],
						lfo_waveform_min,
						lfo_waveform_max,
						1);

					ui->comboBox_LFOwaveform_3->setCurrentIndex(lfo_waveform[2]);
				}
				else if (evnt == _I2C_CONTROL_ENCODER_12)
				{
					// Gray Green dial - LFO 4 symetry control
					lfo_symmetry[3] = update_rotary_encoder_value(
						lfo_symmetry[3],
						val,
						&prev_lfo_symmetry[3],
						lfo_control_min,
						lfo_control_max,
						4);

					ui->dial_LFOsymmetry_4->setValue(lfo_symmetry[3]);
				}
				else if (evnt == _I2C_CONTROL_ENCODER_13)
				{
					// White White combobox - LFO 4 rate control
					lfo_rate[3] = update_rotary_encoder_value(
						lfo_rate[3],
						val,
						&prev_lfo_rate[3],
						lfo_control_min,
						lfo_control_max,
						4);

					ui->dial_LFOrate_4->setValue(lfo_rate[3]);
				}
				else if (evnt == _I2C_CONTROL_ENCODER_14)
				{
					// White Yellow combobox - LFO 4 waveform control
					lfo_waveform[3] = update_rotary_encoder_value(
						lfo_waveform[3],
						val,
						&prev_lfo_waveform[3],
						lfo_waveform_min,
						lfo_waveform_max,
						1);

					ui->comboBox_LFOwaveform_4->setCurrentIndex(lfo_waveform[3]);
				}
				else if (evnt == _I2C_CONTROL_SLIDER_9)
				{
					// White Gray slider - ADSR 3 A control
					// Get new ADSR A3 value from slider and calculate gap from current UI value
					adsr_attack[2] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
					slider_level_gap = adsr_attack[2] - ui->verticalSlider_AdsrA_3->value();			   // 0-100

					// Change slider value only when it matches the UI slider position.
					if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
					{
						// Emits value changed signal.
						ui->verticalSlider_AdsrA_3->setValue(adsr_attack[2]);
					}
				}
				else if (evnt == _I2C_CONTROL_SLIDER_10)
				{
					// White Purple slider - ADSR 3 D control
					// Get new ADSR D3 value from slider and calculate gap from current UI value
					adsr_decay[2] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
					slider_level_gap = adsr_decay[2] - ui->verticalSlider_AdsrD_3->value();				  // 0-100

					// Change slider value only when it matches the UI slider position.
					if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
					{
						// Emits value changed signal.
						ui->verticalSlider_AdsrD_3->setValue(adsr_decay[2]);
					}
				}
				else if (evnt == _I2C_CONTROL_SLIDER_11)
				{
					// White Blue slider - ADSR 3 S control
					// Get new ADSR S3 value from slider and calculate gap from current UI value
					adsr_sustain[2] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
					slider_level_gap = adsr_sustain[2] - ui->verticalSlider_AdsrS_3->value();				// 0-100

					// Change slider value only when it matches the UI slider position.
					if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
					{
						// Emits value changed signal.
						ui->verticalSlider_AdsrS_3->setValue(adsr_sustain[2]);
					}
				}
				else if (evnt == _I2C_CONTROL_SLIDER_12)
				{
					// White Green slider - ADSR 3 R control
					// Get new ADSR R3 value from slider and calculate gap from current UI value
					adsr_release[2] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
					slider_level_gap = adsr_release[2] - ui->verticalSlider_AdsrR_3->value();				// 0-100

					// Change slider value only when it matches the UI slider position.
					if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
					{
						// Emits value changed signal.
						ui->verticalSlider_AdsrR_3->setValue(adsr_release[2]);
					}
				}
				else if (evnt == _I2C_CONTROL_SLIDER_13)
				{
					// White White slider - ADSR 4 A control
					// Get new ADSR A4 value from slider and calculate gap from current UI value
					adsr_attack[3] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
					slider_level_gap = adsr_attack[3] - ui->verticalSlider_AdsrA_4->value();			   // 0-100

					// Change slider value only when it matches the UI slider position.
					if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
					{
						// Emits value changed signal.
						ui->verticalSlider_AdsrA_4->setValue(adsr_attack[3]);
					}
				}
				else if (evnt == _I2C_CONTROL_SLIDER_14)
				{
					// White Yellow slider - ADSR 4 D control
					// Get new ADSR D4 value from slider and calculate gap from current UI value
					adsr_decay[3] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
					slider_level_gap = adsr_decay[3] - ui->verticalSlider_AdsrD_4->value();				  // 0-100

					// Change slider value only when it matches the UI slider position.
					if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
					{
						// Emits value changed signal.
						ui->verticalSlider_AdsrD_4->setValue(adsr_decay[3]);
					}
				}
				else if (evnt == _I2C_CONTROL_SLIDER_15)
				{
					// White Red slider - ADSR 4 S control
					// Get new ADSR S4 value from slider and calculate gap from current UI value
					adsr_sustain[3] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
					slider_level_gap = adsr_sustain[3] - ui->verticalSlider_AdsrS_4->value();				// 0-100

					// Change slider value only when it matches the UI slider position.
					if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
					{
						// Emits value changed signal.
						ui->verticalSlider_AdsrS_4->setValue(adsr_sustain[3]);
					}
				}
				else if (evnt == _I2C_CONTROL_SLIDER_16)
				{
					// White Black slider - ADSR 4 R control
					// Get new ADSR R4 value from slider and calculate gap from current UI value
					adsr_release[3] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
					slider_level_gap = adsr_release[3] - ui->verticalSlider_AdsrR_4->value();				// 0-100

					// Change slider value only when it matches the UI slider position.
					if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
					{
						// Emits value changed signal.
						ui->verticalSlider_AdsrR_4->setValue(adsr_release[3]);
					}
				}
			}
			else if (current_frame_index == 1)
			{
				// LFO 5-6 and ADSR 5-6 (controls 9-16)
				if (evnt == _I2C_CONTROL_ENCODER_9)
				{
					// White Gray dial - LFO 5 symetry control
					lfo_symmetry[4] = update_rotary_encoder_value(
						lfo_symmetry[4],
						val,
						&prev_lfo_symmetry[4],
						lfo_control_min,
						lfo_control_max,
						4);

					ui->dial_LFOsymmetry_5->setValue(lfo_symmetry[4]);
				}
				else if (evnt == _I2C_CONTROL_ENCODER_10)
				{
					// White Purple dial - LFO 5 rate filter1 control
					lfo_rate[4] = update_rotary_encoder_value(
						lfo_rate[4],
						val,
						&prev_lfo_rate[4],
						lfo_control_min,
						lfo_control_max,
						4);

					ui->dial_LFOrate_5->setValue(lfo_rate[4]);
				}
				else if (evnt == _I2C_CONTROL_ENCODER_11)
				{
					// White Blue combobox - LFO 5 waveform control
					lfo_waveform[4] = update_rotary_encoder_value(
						lfo_waveform[4],
						val,
						&prev_lfo_waveform[4],
						lfo_waveform_min,
						lfo_waveform_max,
						1);

					ui->comboBox_LFOwaveform_5->setCurrentIndex(lfo_waveform[4]);
				}
				else if (evnt == _I2C_CONTROL_ENCODER_12)
				{
					// White Green combobox - LFO 6 symmetry control
					lfo_symmetry[5] = update_rotary_encoder_value(
						lfo_symmetry[5],
						val,
						&prev_lfo_symmetry[5],
						lfo_control_min,
						lfo_control_max,
						4);

					ui->dial_LFOsymmetry_6->setValue(lfo_symmetry[5]);
				}
				else if (evnt == _I2C_CONTROL_ENCODER_13)
				{
					// White White combobox - LFO 6 rate control
					lfo_rate[5] = update_rotary_encoder_value(
						lfo_rate[5],
						val,
						&prev_lfo_rate[5],
						lfo_control_min,
						lfo_control_max,
						4);

					ui->dial_LFOrate_6->setValue(lfo_rate[5]);
				}
				else if (evnt == _I2C_CONTROL_ENCODER_14)
				{
					// White Yellow combobox - LFO 6 waveform control
					lfo_waveform[5] = update_rotary_encoder_value(
						lfo_waveform[5],
						val,
						&prev_lfo_waveform[5],
						lfo_waveform_min,
						lfo_waveform_max,
						1);

					ui->comboBox_LFOwaveform_6->setCurrentIndex(lfo_waveform[5]);
				}
				else if (evnt == _I2C_CONTROL_SLIDER_9)
				{
					// White Gray slider - ADSR 5 A control
					// Get new ADSR A5 value from slider and calculate gap from current UI value
					adsr_attack[4] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
					slider_level_gap = adsr_attack[4] - ui->verticalSlider_AdsrA_5->value();			   // 0-100

					// Change slider value only when it matches the UI slider position.
					if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
					{
						// Emits value changed signal.
						ui->verticalSlider_AdsrA_5->setValue(adsr_attack[4]);
					}
				}
				else if (evnt == _I2C_CONTROL_SLIDER_10)
				{
					// White Purple slider - ADSR 5 D control
					// Get new ADSR D5 value from slider and calculate gap from current UI value
					adsr_decay[4] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
					slider_level_gap = adsr_decay[4] - ui->verticalSlider_AdsrD_5->value();				  // 0-100

					// Change slider value only when it matches the UI slider position.
					if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
					{
						// Emits value changed signal.
						ui->verticalSlider_AdsrD_5->setValue(adsr_decay[4]);
					}
				}
				else if (evnt == _I2C_CONTROL_SLIDER_11)
				{
					// White Blue slider - ADSR 5 S control
					// Get new ADSR S5 value from slider and calculate gap from current UI value
					adsr_sustain[4] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
					slider_level_gap = adsr_sustain[4] - ui->verticalSlider_AdsrS_5->value();				// 0-100

					// Change slider value only when it matches the UI slider position.
					if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
					{
						// Emits value changed signal.
						ui->verticalSlider_AdsrS_5->setValue(adsr_sustain[4]);
					}
				}
				else if (evnt == _I2C_CONTROL_SLIDER_12)
				{
					// White Green slider - ADSR 5 R control
					// Get new ADSR R5 value from slider and calculate gap from current UI value
					adsr_release[4] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
					slider_level_gap = adsr_release[4] - ui->verticalSlider_AdsrR_5->value();				// 0-100

					// Change slider value only when it matches the UI slider position.
					if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
					{
						// Emits value changed signal.
						ui->verticalSlider_AdsrR_5->setValue(adsr_release[4]);
					}
				}
				else if (evnt == _I2C_CONTROL_SLIDER_13)
				{
					// White White slider - ADSR 6 A control
					// Get new ADSR A6 value from slider and calculate gap from current UI value
					adsr_attack[5] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
					slider_level_gap = adsr_attack[5] - ui->verticalSlider_AdsrA_6->value();			   // 0-100

					// Change slider value only when it matches the UI slider position.
					if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
					{
						// Emits value changed signal.
						ui->verticalSlider_AdsrA_6->setValue(adsr_attack[5]);
					}
				}
				else if (evnt == _I2C_CONTROL_SLIDER_14)
				{
					// White Yellow slider - ADSR 6 D control
					// Get new ADSR D6 value from slider and calculate gap from current UI value
					adsr_decay[5] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
					slider_level_gap = adsr_decay[5] - ui->verticalSlider_AdsrD_6->value();				  // 0-100

					// Change slider value only when it matches the UI slider position.
					if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
					{
						// Emits value changed signal.
						ui->verticalSlider_AdsrD_6->setValue(adsr_decay[5]);
					}
				}
				else if (evnt == _I2C_CONTROL_SLIDER_15)
				{
					// White Red slider - ADSR 6 S control
					// Get new ADSR S6 value from slider and calculate gap from current UI value
					adsr_sustain[5] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
					slider_level_gap = adsr_sustain[5] - ui->verticalSlider_AdsrS_6->value();				// 0-100

					// Change slider value only when it matches the UI slider position.
					if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
					{
						// Emits value changed signal.
						ui->verticalSlider_AdsrS_6->setValue(adsr_sustain[5]);
					}
				}
				else if (evnt == _I2C_CONTROL_SLIDER_16)
				{
					// White Black slider - ADSR 6 R control
					// Get new ADSR R6 value from slider and calculate gap from current UI value
					adsr_release[5] = normalize_slider_value(val / 36, adsr_control_max, adsr_control_min); // 0-3600
					slider_level_gap = adsr_release[5] - ui->verticalSlider_AdsrR_6->value();				// 0-100

					// Change slider value only when it matches the UI slider position.
					if (abs((float)slider_level_gap) < ((adsr_control_max - adsr_control_min) / 5.0))
					{
						// Emits value changed signal.
						ui->verticalSlider_AdsrR_6->setValue(adsr_release[5]);
					}
				}
			}
		}
	}
	
	
}

