/**
 * @file		InitDictionaries.cpp
 *	@author		Nahum Budin
 *	@date		18-June-2026
 *	@version	1.0
 *
 *	@brief		MainWindow class dictionaries initialization for ML training data and widgets mapping.
 *
 *	History:
 *
 */

#include "Defs.h"
#include "defines.h"
#include "synthesizer.h"                         
	                                                                                                                                                                                                                                                                                                                                                                                 

	                                                     
                                                                                                                                                                                                                                                   

	                                                      

#include "MainWindow.h"

void MainWindow::init_dictionaries()
{
	modules_names_map[_MOD_SYNTH_EVENT] = "Analog Synthesizer";
	
	
	submodules_names_map[_OSC_1_EVENT] = "Oscillator 1";
	submodules_names_map[_OSC_2_EVENT] = "Oscillator 2";
	submodules_names_map[_MSO_1_EVENT] = "MSO Synth";
	submodules_names_map[_NOISE_1_EVENT] = "Noise";
	submodules_names_map[_KARPLUS_1_EVENT] = "Karplus-Strong String";
	submodules_names_map[_PAD_1_EVENT] = "PAD Synth";
	submodules_names_map[_DISTORTION_1_EVENT] = "Distortion 1";
	submodules_names_map[_FILTER_1_EVENT] = "Filter 1";
	submodules_names_map[_FILTER_2_EVENT] = "Filter 2";

	submodules_names_map[_LFO_1_EVENT] = "LFO 1";
	submodules_names_map[_LFO_2_EVENT] = "LFO 2";
	submodules_names_map[_LFO_3_EVENT] = "LFO 3";
	submodules_names_map[_LFO_4_EVENT] = "LFO 4";
	submodules_names_map[_LFO_5_EVENT] = "LFO 5";
	submodules_names_map[_LFO_6_EVENT] = "LFO 6";

	submodules_names_map[_ENV_1_EVENT] = "ADSR 1";
	submodules_names_map[_ENV_2_EVENT] = "ADSR 2";
	submodules_names_map[_ENV_3_EVENT] = "ADSR 3";
	submodules_names_map[_ENV_4_EVENT] = "ADSR 4";
	submodules_names_map[_ENV_5_EVENT] = "ADSR 5";
	submodules_names_map[_ENV_6_EVENT] = "ADSR 6";
	

	params_names_map[_OSC_ENABLE] = "Oscillator Enable";
	params_names_map[_OSC_PARAM_WAVEFORM] = "Waveform";
	params_names_map[_OSC_PWM_SYMMETRY] = "Symmetry";
	params_names_map[_OSC_FILTER_SEND_1] = "Send Filter 1";
	params_names_map[_OSC_FILTER_SEND_2] = "Send Filter 2";
	params_names_map[_OSC_DETUNE_OCTAVE] = "Detune Octave";
	params_names_map[_OSC_DETUNE_SEMITONES] = "Detune Semitones";
	params_names_map[_OSC_DETUNE_CENTS] = "Detune Cents";
	params_names_map[_OSC_FREQ_MOD_LFO_LEVEL] = "Freq Mod LFO Level";
	params_names_map[_OSC_FREQ_MOD_ENV_LEVEL] = "Freq Mod ADSR Level";
	params_names_map[_OSC_FREQ_MOD_LFO] = "Freq Mod LFO";
	params_names_map[_OSC_FREQ_MOD_ENV] = "Freq Mod ADSR";
	params_names_map[_OSC_AMP_MOD_LFO_LEVEL] = "Amp Mod LFO Level";
	params_names_map[_OSC_AMP_MOD_ENV_LEVEL] = "Amp Mod ADSR Level";
	params_names_map[_OSC_AMP_MOD_LFO] = "Amp Mod LFO";
	params_names_map[_OSC_AMP_MOD_ENV] = "Amp Mod ADSR";
	params_names_map[_OSC_PWM_MOD_LFO_LEVEL] = "Pwm Mod LFO Level";
	params_names_map[_OSC_PWM_MOD_ENV_LEVEL] = "Pwm Mod ADSR Level";
	params_names_map[_OSC_PWM_MOD_LFO] = "Pwm Mod LFO";
	params_names_map[_OSC_PWM_MOD_ENV] = "Pwm Mod ADSR";
	params_names_map[_OSC_UNISON_MODE] = "Unison Mode";
	params_names_map[_OSC_UNISON_LEVEL_1] = "Unison Level 1";
	params_names_map[_OSC_UNISON_LEVEL_2] = "Unison Level 2";
	params_names_map[_OSC_UNISON_LEVEL_3] = "Unison Level 3";
	params_names_map[_OSC_UNISON_LEVEL_4] = "Unison Level 4";
	params_names_map[_OSC_UNISON_LEVEL_5] = "Unison Level 5";
	params_names_map[_OSC_UNISON_LEVEL_6] = "Unison Level 6";
	params_names_map[_OSC_UNISON_LEVEL_7] = "Unison Level 7";
	params_names_map[_OSC_UNISON_LEVEL_8] = "Unison Level 8";
	params_names_map[_OSC_UNISON_LEVEL_9] = "Unison Level 9";
	params_names_map[_OSC_UNISON_DISTORTION] = "Unison Distortion";
	params_names_map[_OSC_UNISON_DETUNE] = "Unison Detune";
	params_names_map[_OSC_HAMMOND_PERCUSION_MODE] = "Hammond Percussion Mode";
	params_names_map[_OSC_1_UNISON_SQUARE] = "Unison Square";
	params_names_map[_OSC_SYNC] = "Osc 2 Sync on Osc 1";

	params_names_map[_MSO_ENABLE] = "MSO Enable";
	params_names_map[_MSO_FILTER_SEND_1] = "MSO Send Filter 1";
	params_names_map[_MSO_FILTER_SEND_2] = "MSO Send Filter 2";
	params_names_map[_MSO_DETUNE_OCTAVE] = "MSO Detune Octave";
	params_names_map[_MSO_DETUNE_SEMITONES] = "MSO Detune Semitones";
	params_names_map[_MSO_DETUNE_CENTS] = "MSO Detune Cents";
	params_names_map[_MSO_FREQ_MOD_LFO_LEVEL] = "MSO Freq Mod LFO Level";
	params_names_map[_MSO_FREQ_MOD_ENV_LEVEL] = "MSO Freq Mod ADSR Level";
	params_names_map[_MSO_FREQ_MOD_LFO] = "MSO Freq Mod LFO";
	params_names_map[_MSO_FREQ_MOD_ENV] = "MSO Freq Mod ADSR";
	params_names_map[_MSO_AMP_MOD_LFO_LEVEL] = "MSO Amp Mod LFO Level";
	params_names_map[_MSO_AMP_MOD_ENV_LEVEL] = "MSO Amp Mod ADSR Level";
	params_names_map[_MSO_AMP_MOD_LFO] = "MSO Amp Mod LFO";
	params_names_map[_MSO_AMP_MOD_ENV] = "MSO Amp Mod ADSR";
	params_names_map[_MSO_SYMETRY] = "MSO Morph";
	params_names_map[_MSO_SEGMENT_A_POSITION] = "MSO Segment A Position";
	params_names_map[_MSO_SEGMENT_B_POSITION] = "MSO Segment B Position";
	params_names_map[_MSO_SEGMENT_C_POSITION] = "MSO Segment C Position";
	params_names_map[_MSO_SEGMENT_D_POSITION] = "MSO Segment D Position";
	params_names_map[_MSO_SEGMENT_E_POSITION] = "MSO Segment E Position";
	params_names_map[_MSO_SEGMENT_F_POSITION] = "MSO Segment F Position";

	params_names_map[_NOISE_ENABLE] = "Noise Enable";
	params_names_map[_NOISE_COLOR] = "Noise Color";
	params_names_map[_NOISE_SEND_1] = "Noise Send Filter 1";
	params_names_map[_NOISE_SEND_2] = "Noise Send Filter 2";
	params_names_map[_NOISE_AMP_MOD_LFO_LEVEL] = "Noise Amp Mod LFO Level";
	params_names_map[_NOISE_AMP_MOD_ENV_LEVEL] = "Noise Amp Mod ADSR Level";
	params_names_map[_NOISE_AMP_MOD_LFO] = "Noise Amp Mod LFO";
	params_names_map[_NOISE_AMP_MOD_ENV] = "Noise Amp Mod ADSR";
	

	params_names_map[_KARPLUS_STRONG_ENABLE] = "Karplus-Strong Enable";
	params_names_map[_KARPLUS_STRONG_EXCITATION_WAVEFORM] = "KPS Excitation Waveform";
	params_names_map[_KARPLUS_STRONG_STRING_DUMP_CALC_MODE] = "KPS String Dump Calc Mode";
	params_names_map[_KARPLUS_STRONG_STRING_DAMPING] = "KPS String Damping";
	params_names_map[_KARPLUS_STRONG_STRING_DAMPING_VARIATION] = "KPS String Damping Variation";
	params_names_map[_KARPLUS_STRONG_PLUCK_DAMPING] = "KPS Pluck Damping";
	params_names_map[_KARPLUS_STRONG_PLUCK_DAMPING_VARIATION] = "KPS Pluck Damping Variation";
	params_names_map[_KARPLUS_STRONG_ON_DECAY] = "KPS On Decay";
	params_names_map[_KARPLUS_STRONG_OFF_DECAY] = "KPS Off Decay";
	params_names_map[_KARPLUS_STRONG_EXCITATION_WAVEFORM_VARIATIONS] = "KPS Excitation Waveform Variations";
	params_names_map[_KARPLUS_STRONG_CHARACTER_VARIATIONS] = "KPS Character Variations";
	params_names_map[_KARPLUS_STRONG_SEND_1] = "KPS Send Filter 1 Level";
	params_names_map[_KARPLUS_STRONG_SEND_2] = "KPS Send Filter 2 Level";

	params_names_map[_PAD_ENABLE] = "PAD Enable";

	params_names_map[_ENABLE_DISTORTION] = "Distortion";
	params_names_map[_DISTORTION_AUTO_GAIN] = "Distortion Auto Gain";

	params_names_map[_FILTER_FREQ] = "Filter Freq";
	params_names_map[_FILTER_OCT] = "Filter Oct";
	params_names_map[_FILTER_Q] = "Filter Q";
	params_names_map[_FILTER_KBD_TRACK] = "Filter Kbd Track";
	params_names_map[_FILTER_BAND] = "Filter Band";
	params_names_map[_FILTER_FREQ_MOD_LFO] = "Filter Freq Mod LFO";
	params_names_map[_FILTER_FREQ_MOD_LFO_LEVEL] = "Filter Freq Mod LFO Level";
	params_names_map[_FILTER_FREQ_MOD_ENV] = "Filter Freq Mod ADSR	";
	params_names_map[_FILTER_FREQ_MOD_ENV_LEVEL] = "Filter Freq Mod ADSR Level";
	params_names_map[_FILTER_2_TRACK_FILT_1] = "Filter 2 Track Filt 1";

	params_names_map[_MOD_ADSR_ATTACK] = "ADSR Attack";
	params_names_map[_MOD_ADSR_DECAY] = "ADSR Decay";
	params_names_map[_MOD_ADSR_SUSTAIN] = "ADSR Sustain";
	params_names_map[_MOD_ADSR_RELEASE] = "ADSR Release";

	params_names_map[_MOD_LFO_RATE] = "LFO Rate";
	params_names_map[_MOD_LFO_SYMMETRY] = "LFO Symmetry";
	params_names_map[_MOD_LFO_WAVEFORM] = "LFO Waveform";
}

