/**
 * @file		ControlWidgetsColorManager.cpp
 *	@author		Nahum Budin
 *	@date		27-Dec-2025
 *	@version	1.0
 *					1. First version.
 *
 *	@brief		Controls the Analog Synthesizer instrument GUI control-widgets colors
 *
 *	History:
 *
 */

#include "ControlWidgetsColorManager.h"
#include "Dialog_AnalogSynth_1900x1000.h"
#include "Dialog_MidiMixer.h"
#include "MainWindow.h"
#include "ui_Dialog_AnalogSynth_1900x1000.h"
#include "ui_Dialog_MidiMixer_1620x840.h"

ControlWidgetsColorManager::ControlWidgetsColorManager(){

	int result;

	result = init_frames_colors();
	result = init_dial_controls_colors();
	result = init_combobox_controls_colors();
	result = init_horizontal_slider_controls_colors();
	result = init_vertical_slider_controls_colors();
	result = init_button_controls_colors();
	result = init_checkbox_controls_colors();
}

ControlWidgetsColorManager::~ControlWidgetsColorManager()
{
}

int ControlWidgetsColorManager::init_frames_colors()
{
	if (!analog_synth_frames_colors_initialized)
	{
		analog_synth_frames_colors_initialized = true;

		Ui::Dialog_AnalogSynth_1900x1000 *ui = Dialog_AnalogSynth_1900x1000::get_ui_instance();

		if (ui)
		{
			frame_control_colors[ui->frame_Sketches] = _CONTROL_GROUP_WHITE; // Allways white

			// OSC1
			frame_control_colors[ui->frame_Osc1Waveform] = _CONTROL_GROUP_GRAY;				// G1
			frame_control_colors[ui->frame_Osc1TuneOffset] = _CONTROL_GROUP_GRAY;			// G1
			frame_control_colors[ui->frame_Osc1FrequencyModulation] = _CONTROL_GROUP_WHITE; // W1
			frame_control_colors[ui->frame_Osc1AmpMod] = _CONTROL_GROUP_WHITE;				// W1
			frame_control_colors[ui->frame_Osc1Drawbars_1_6] = _CONTROL_GROUP_NOT_SELECTED; // G2
			frame_control_colors[ui->frame_Osc1PwmMod] = _CONTROL_GROUP_NOT_SELECTED;		// G2
			frame_control_colors[ui->frame_Osc1Drawbars_7_9] = _CONTROL_GROUP_NOT_SELECTED; // W2

			// OSC2
			frame_control_colors[ui->frame_Osc2Waveform] = _CONTROL_GROUP_NOT_SELECTED;	  // G3
			frame_control_colors[ui->frame_Osc2TuneOffset] = _CONTROL_GROUP_NOT_SELECTED; // G3
			frame_control_colors[ui->frame_Osc2FreqMod] = _CONTROL_GROUP_NOT_SELECTED;	  // W3
			frame_control_colors[ui->frame_Osc2AmpMod] = _CONTROL_GROUP_NOT_SELECTED;	  // W3
			frame_control_colors[ui->frame_Osc2PwmMod] = _CONTROL_GROUP_NOT_SELECTED;	  // W4

			// Noise
			frame_control_colors[ui->frame_NoiseColor] = _CONTROL_GROUP_NOT_SELECTED;  // G5
			frame_control_colors[ui->frame_NoiseAmpMod] = _CONTROL_GROUP_NOT_SELECTED; // G5

			// Karplus-Strong Strings (KPS)
			frame_control_colors[ui->frame_KarplusStringAll] = _CONTROL_GROUP_NOT_SELECTED; // G6

			// MSO
			frame_control_colors[ui->frame_MsoSendFiltersTuneOffset] = _CONTROL_GROUP_NOT_SELECTED; // G7
			frame_control_colors[ui->frame_MsoFreqMod] = _CONTROL_GROUP_NOT_SELECTED;				// W7
			frame_control_colors[ui->frame_MsoPwmMod] = _CONTROL_GROUP_NOT_SELECTED;				// W7
			frame_control_colors[ui->frame_MsoAmpMod] = _CONTROL_GROUP_NOT_SELECTED;				// G8
			frame_control_colors[ui->frame_MsoSegments] = _CONTROL_GROUP_NOT_SELECTED;				// G8

			// Pad
			frame_control_colors[ui->frame_PAD_SendFiltersTuneOffset] = _CONTROL_GROUP_NOT_SELECTED; // G9
			frame_control_colors[ui->frame_PAD_AmpMod] = _CONTROL_GROUP_NOT_SELECTED;				 // G9
			frame_control_colors[ui->frame_PAD_FreqMod] = _CONTROL_GROUP_NOT_SELECTED;				 // W9
			frame_control_colors[ui->frame_PAD_AmpMod] = _CONTROL_GROUP_NOT_SELECTED;				 // W9
			frame_control_colors[ui->frame_PAD_Haromonys1_6] = _CONTROL_GROUP_NOT_SELECTED;			 //  G10
			frame_control_colors[ui->frame_PAD_Profile] = _CONTROL_GROUP_NOT_SELECTED;				 //  G10
			frame_control_colors[ui->frame_PAD_Haromonys7_10] = _CONTROL_GROUP_NOT_SELECTED;		 //  W10

			return 0;
		}
	}
}

int ControlWidgetsColorManager::init_dial_controls_colors()
{
	if (!analog_synth_dials_colors_initialized)
	{
		analog_synth_dials_colors_initialized = true;

		Ui::Dialog_AnalogSynth_1900x1000 *ui = Dialog_AnalogSynth_1900x1000::get_ui_instance();

		if (ui)
		{
			// OSC1
			dial_control_colors[ui->dial_Osc1SendFilter1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[ui->dial_Osc1SendFilter1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			dial_control_colors[ui->dial_Osc1SendFilter2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[ui->dial_Osc1SendFilter2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[ui->dial_Osc1FreqModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[ui->dial_Osc1FreqModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[ui->dial_Osc1FreqModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[ui->dial_Osc1FreqModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			dial_control_colors[ui->dial_Osc1AmpModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[ui->dial_Osc1AmpModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			dial_control_colors[ui->dial_Osc1AmpModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[ui->dial_Osc1AmpModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

			dial_control_colors[ui->dial_Osc1PwmModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G2
			dial_control_colors[ui->dial_Osc1PwmModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			dial_control_colors[ui->dial_Osc1PwmModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G2
			dial_control_colors[ui->dial_Osc1PwmModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

			// OSC2
			dial_control_colors[ui->dial_Osc2SendFilter1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G3
			dial_control_colors[ui->dial_Osc2SendFilter1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			dial_control_colors[ui->dial_Osc2SendFilter2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G3
			dial_control_colors[ui->dial_Osc2SendFilter2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[ui->dial_Osc2FreqModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W3
			dial_control_colors[ui->dial_Osc2FreqModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[ui->dial_Osc2FreqModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W3
			dial_control_colors[ui->dial_Osc2FreqModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			dial_control_colors[ui->dial_Osc2AmpModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W3
			dial_control_colors[ui->dial_Osc2AmpModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			dial_control_colors[ui->dial_Osc2AmpModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W3
			dial_control_colors[ui->dial_Osc2AmpModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

			dial_control_colors[ui->dial_Osc2PwmModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W4
			dial_control_colors[ui->dial_Osc2PwmModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[ui->dial_Osc2PwmModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W4
			dial_control_colors[ui->dial_Osc2PwmModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			// Noise
			dial_control_colors[ui->dial_NoiseSendFilter1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G4
			dial_control_colors[ui->dial_NoiseSendFilter1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			dial_control_colors[ui->dial_NoiseSendFilter2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G4
			dial_control_colors[ui->dial_NoiseSendFilter2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[ui->dial_NoiseAmpModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G4
			dial_control_colors[ui->dial_NoiseAmpModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			dial_control_colors[ui->dial_NoiseAmpModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G4
			dial_control_colors[ui->dial_NoiseAmpModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

			// Karplus-Strong Strings (KPS)
			dial_control_colors[ui->dial_KarplusSynth_SendFilter1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G5
			dial_control_colors[ui->dial_KarplusSynth_SendFilter1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			dial_control_colors[ui->dial_KarplusSynth_SendFilter2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G5
			dial_control_colors[ui->dial_KarplusSynth_SendFilter2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			// MSO
			dial_control_colors[ui->dial_MsoSendFilter1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G7
			dial_control_colors[ui->dial_MsoSendFilter1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			dial_control_colors[ui->dial_MsoSendFilter2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G7
			dial_control_colors[ui->dial_MsoSendFilter2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[ui->dial_MsoFreqModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W7
			dial_control_colors[ui->dial_MsoFreqModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[ui->dial_MsoFreqModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W7
			dial_control_colors[ui->dial_MsoFreqModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			dial_control_colors[ui->dial_MsoAmpModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W7
			dial_control_colors[ui->dial_MsoAmpModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			dial_control_colors[ui->dial_MsoAmpModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W7
			dial_control_colors[ui->dial_MsoAmpModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

			dial_control_colors[ui->dial_MsoPwmModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W7
			dial_control_colors[ui->dial_MsoPwmModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[ui->dial_MsoPwmModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G8
			dial_control_colors[ui->dial_MsoPwmModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			// PAD
			dial_control_colors[ui->dial_PadSendFilter1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G9
			dial_control_colors[ui->dial_PadSendFilter1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			dial_control_colors[ui->dial_PadSendFilter2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G9
			dial_control_colors[ui->dial_PadSendFilter2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[ui->dial_PadFreqModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W9
			dial_control_colors[ui->dial_PadFreqModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[ui->dial_PadFreqModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W9
			dial_control_colors[ui->dial_PadFreqModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			dial_control_colors[ui->dial_PadAmpModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W9
			dial_control_colors[ui->dial_PadAmpModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			dial_control_colors[ui->dial_PadAmpModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W9
			dial_control_colors[ui->dial_PadAmpModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

			// Filter 1
			dial_control_colors[ui->dial_FilterFreq_1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[ui->dial_FilterFreq_1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			dial_control_colors[ui->dial_FilterOctave_1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[ui->dial_FilterOctave_1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[ui->dial_FilterQ_1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[ui->dial_FilterQ_1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			dial_control_colors[ui->dial_FilterKbdTrack_1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[ui->dial_FilterKbdTrack_1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			// Filter 2
			dial_control_colors[ui->dial_FilterFreq_2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[ui->dial_FilterFreq_2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			dial_control_colors[ui->dial_FilterOctave_2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[ui->dial_FilterOctave_2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[ui->dial_FilterQ_2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[ui->dial_FilterQ_2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			dial_control_colors[ui->dial_FilterKbdTrack_2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[ui->dial_FilterKbdTrack_2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			// Distortion 1
			dial_control_colors[ui->dial_DistortionDrive_1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G2
			dial_control_colors[ui->dial_DistortionDrive_1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			dial_control_colors[ui->dial_DistortionRange_1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G2
			dial_control_colors[ui->dial_DistortionRange_1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[ui->dial_DistortionBlend_1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G2
			dial_control_colors[ui->dial_DistortionBlend_1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			// Distortion 2
			dial_control_colors[ui->dial_DistortionDrive_2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G2
			dial_control_colors[ui->dial_DistortionDrive_2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			dial_control_colors[ui->dial_DistortionRange_2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G2
			dial_control_colors[ui->dial_DistortionRange_2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			dial_control_colors[ui->dial_DistortionBlend_2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G2
			dial_control_colors[ui->dial_DistortionBlend_2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			// FreeVerb
			dial_control_colors[ui->dial_ReverbRoomSize][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W2
			dial_control_colors[ui->dial_ReverbRoomSize][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[ui->dial_ReverbDamp][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W2
			dial_control_colors[ui->dial_ReverbDamp][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			dial_control_colors[ui->dial_ReverbWet][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W2
			dial_control_colors[ui->dial_ReverbWet][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			dial_control_colors[ui->dial_ReverbDry][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W2
			dial_control_colors[ui->dial_ReverbDry][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			dial_control_colors[ui->dial_ReverbWidth][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W2
			dial_control_colors[ui->dial_ReverbWidth][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			dial_control_colors[ui->dial_ReverbMode][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W2
			dial_control_colors[ui->dial_ReverbMode][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;			
			
			// LFOs
			dial_control_colors[ui->dial_LFOsymmetry_1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;
			dial_control_colors[ui->dial_LFOsymmetry_1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			dial_control_colors[ui->dial_LFOrate_1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;
			dial_control_colors[ui->dial_LFOrate_1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			dial_control_colors[ui->dial_LFOsymmetry_2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;
			dial_control_colors[ui->dial_LFOsymmetry_2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			dial_control_colors[ui->dial_LFOrate_2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;
			dial_control_colors[ui->dial_LFOrate_2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			dial_control_colors[ui->dial_LFOsymmetry_3][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;
			dial_control_colors[ui->dial_LFOsymmetry_3][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			dial_control_colors[ui->dial_LFOrate_3][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;
			dial_control_colors[ui->dial_LFOrate_3][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			dial_control_colors[ui->dial_LFOsymmetry_4][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;
			dial_control_colors[ui->dial_LFOsymmetry_4][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			dial_control_colors[ui->dial_LFOrate_4][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;
			dial_control_colors[ui->dial_LFOrate_4][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			dial_control_colors[ui->dial_LFOsymmetry_5][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;
			dial_control_colors[ui->dial_LFOsymmetry_5][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			dial_control_colors[ui->dial_LFOrate_5][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;
			dial_control_colors[ui->dial_LFOrate_5][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			dial_control_colors[ui->dial_LFOsymmetry_6][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;
			dial_control_colors[ui->dial_LFOsymmetry_6][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			dial_control_colors[ui->dial_LFOrate_6][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;
			dial_control_colors[ui->dial_LFOrate_6][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
			
		}
	}

	if (!midi_mixer_dials_colors_initialized)
	{
		midi_mixer_dials_colors_initialized = true;

		// MIDI Mixer
		Ui::Dialog_MidiMixer_1620x840 *mixer_ui = Dialog_MidiMixer::get_ui_instance();
		
		if (mixer_ui)
		{
			dial_control_colors[mixer_ui->dial_MixerChPan_1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChPan_1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			dial_control_colors[mixer_ui->dial_MixerChPan_2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChPan_2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			dial_control_colors[mixer_ui->dial_MixerChPan_3][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChPan_3][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[mixer_ui->dial_MixerChPan_4][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChPan_4][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			dial_control_colors[mixer_ui->dial_MixerChPan_5][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChPan_5][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			dial_control_colors[mixer_ui->dial_MixerChPan_6][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChPan_6][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			dial_control_colors[mixer_ui->dial_MixerChPan_7][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChPan_7][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			dial_control_colors[mixer_ui->dial_MixerChPan_8][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChPan_8][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;
			
			dial_control_colors[mixer_ui->dial_MixerChPan_9][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChPan_9][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			dial_control_colors[mixer_ui->dial_MixerChPan_10][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChPan_10][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			dial_control_colors[mixer_ui->dial_MixerChPan_11][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChPan_11][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[mixer_ui->dial_MixerChPan_12][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChPan_12][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			dial_control_colors[mixer_ui->dial_MixerChPan_13][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChPan_13][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			dial_control_colors[mixer_ui->dial_MixerChPan_14][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChPan_14][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			dial_control_colors[mixer_ui->dial_MixerChPan_15][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChPan_15][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			dial_control_colors[mixer_ui->dial_MixerChPan_16][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChPan_16][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_3][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_3][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_4][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_4][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_5][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_5][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_6][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_6][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_7][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_7][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_8][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_8][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_9][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_9][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_10][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_10][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_11][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_11][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_12][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_12][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_13][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_13][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_14][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_14][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_15][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_15][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_16][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChPanModLevel_16][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

			dial_control_colors[mixer_ui->dial_MixerChSend_1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChSend_1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			dial_control_colors[mixer_ui->dial_MixerChSend_2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChSend_2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			dial_control_colors[mixer_ui->dial_MixerChSend_3][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChSend_3][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[mixer_ui->dial_MixerChSend_4][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChSend_4][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			dial_control_colors[mixer_ui->dial_MixerChSend_5][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChSend_5][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			dial_control_colors[mixer_ui->dial_MixerChSend_6][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChSend_6][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			dial_control_colors[mixer_ui->dial_MixerChSend_7][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChSend_7][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			dial_control_colors[mixer_ui->dial_MixerChSend_8][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			dial_control_colors[mixer_ui->dial_MixerChSend_8][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

			dial_control_colors[mixer_ui->dial_MixerChSend_9][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChSend_9][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			dial_control_colors[mixer_ui->dial_MixerChSend_10][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChSend_10][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			dial_control_colors[mixer_ui->dial_MixerChSend_11][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChSend_11][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			dial_control_colors[mixer_ui->dial_MixerChSend_12][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChSend_12][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			dial_control_colors[mixer_ui->dial_MixerChSend_13][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChSend_13][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			dial_control_colors[mixer_ui->dial_MixerChSend_14][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChSend_14][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			dial_control_colors[mixer_ui->dial_MixerChSend_15][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChSend_15][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			dial_control_colors[mixer_ui->dial_MixerChSend_16][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			dial_control_colors[mixer_ui->dial_MixerChSend_16][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;
			
			
		}
	}

	return 0;
}

int	ControlWidgetsColorManager::init_combobox_controls_colors()
{
	if (!analog_synth_comboboxes_colors_initialized)
	{
		analog_synth_comboboxes_colors_initialized = true;
		Ui::Dialog_AnalogSynth_1900x1000 *ui = Dialog_AnalogSynth_1900x1000::get_ui_instance();

		if (ui)
		{
			// OSC1
			combobox_control_colors[ui->comboBox_Osc1Waveform][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G1
			combobox_control_colors[ui->comboBox_Osc1Waveform][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			combobox_control_colors[ui->comboBox_Osc1TuneOctave][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G1
			combobox_control_colors[ui->comboBox_Osc1TuneOctave][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			combobox_control_colors[ui->comboBox_Osc1TuneSemitones][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G1
			combobox_control_colors[ui->comboBox_Osc1TuneSemitones][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			combobox_control_colors[ui->comboBox_Osc1TuneCents][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G1
			combobox_control_colors[ui->comboBox_Osc1TuneCents][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			combobox_control_colors[ui->comboBox_Osc1FreqModLFO][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // W1
			combobox_control_colors[ui->comboBox_Osc1FreqModLFO][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			combobox_control_colors[ui->comboBox_Osc1FreqModAdsr][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // W1
			combobox_control_colors[ui->comboBox_Osc1FreqModAdsr][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			combobox_control_colors[ui->comboBox_Osc1AmpModLFO][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // W1
			combobox_control_colors[ui->comboBox_Osc1AmpModLFO][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			combobox_control_colors[ui->comboBox_Osc1AmpModAdsr][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // W1
			combobox_control_colors[ui->comboBox_Osc1AmpModAdsr][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			combobox_control_colors[ui->comboBox_Osc1PwmModLFO][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G2
			combobox_control_colors[ui->comboBox_Osc1PwmModLFO][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			combobox_control_colors[ui->comboBox_Osc1PwmModAdsr][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G2
			combobox_control_colors[ui->comboBox_Osc1PwmModAdsr][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			combobox_control_colors[ui->comboBox_Osc1HammondPercussionMode][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G2
			combobox_control_colors[ui->comboBox_Osc1HammondPercussionMode][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			combobox_control_colors[ui->comboBox_Osc1UnisonMode][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G2
			combobox_control_colors[ui->comboBox_Osc1UnisonMode][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			// OSC2
			combobox_control_colors[ui->comboBox_Osc2Waveform][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G3
			combobox_control_colors[ui->comboBox_Osc2Waveform][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			combobox_control_colors[ui->comboBox_Osc2TuneOctave][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G3
			combobox_control_colors[ui->comboBox_Osc2TuneOctave][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			combobox_control_colors[ui->comboBox_Osc2TuneSemitones][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G3
			combobox_control_colors[ui->comboBox_Osc2TuneSemitones][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			combobox_control_colors[ui->comboBox_Osc2TuneCents][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G3
			combobox_control_colors[ui->comboBox_Osc2TuneCents][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			combobox_control_colors[ui->comboBox_Osc2FreqModLFO][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // W3
			combobox_control_colors[ui->comboBox_Osc2FreqModLFO][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			combobox_control_colors[ui->comboBox_Osc2FreqModAdsr][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // W3
			combobox_control_colors[ui->comboBox_Osc2FreqModAdsr][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			combobox_control_colors[ui->comboBox_Osc2AmpModLFO][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // W3
			combobox_control_colors[ui->comboBox_Osc2AmpModLFO][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			combobox_control_colors[ui->comboBox_Osc2AmpModAdsr][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // W3
			combobox_control_colors[ui->comboBox_Osc2AmpModAdsr][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			combobox_control_colors[ui->comboBox_Osc2PwmModLFO][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // W4
			combobox_control_colors[ui->comboBox_Osc2PwmModLFO][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			combobox_control_colors[ui->comboBox_Osc2PwmModAdsr][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // W4
			combobox_control_colors[ui->comboBox_Osc2PwmModAdsr][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			// Noise
			combobox_control_colors[ui->comboBox_NoiseColor][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G4
			combobox_control_colors[ui->comboBox_NoiseColor][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			combobox_control_colors[ui->comboBox_NoiseAmpModLFO][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G4
			combobox_control_colors[ui->comboBox_NoiseAmpModLFO][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			combobox_control_colors[ui->comboBox_NoiseAmpModAdsr][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G4
			combobox_control_colors[ui->comboBox_NoiseAmpModAdsr][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			// Karplus-Strong Strings (KPS)
			combobox_control_colors[ui->comboBox_KarplusSynth_ExcitationWaveform][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G5
			combobox_control_colors[ui->comboBox_KarplusSynth_ExcitationWaveform][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			combobox_control_colors[ui->comboBox_KarplusSynth_CalculationMode][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G5
			combobox_control_colors[ui->comboBox_KarplusSynth_CalculationMode][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			// MSO
			combobox_control_colors[ui->comboBox_MsoTuneOctave][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G7
			combobox_control_colors[ui->comboBox_MsoTuneOctave][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			combobox_control_colors[ui->comboBox_MsoTuneSemitones][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G7
			combobox_control_colors[ui->comboBox_MsoTuneSemitones][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			combobox_control_colors[ui->comboBox_MsoTuneCents][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G7
			combobox_control_colors[ui->comboBox_MsoTuneCents][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			combobox_control_colors[ui->comboBox_MsoFreqModLFO][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // W7
			combobox_control_colors[ui->comboBox_MsoFreqModLFO][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			combobox_control_colors[ui->comboBox_MsoFreqModAdsr][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // W7
			combobox_control_colors[ui->comboBox_MsoFreqModAdsr][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			combobox_control_colors[ui->comboBox_MsoAmpModLFO][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // W7
			combobox_control_colors[ui->comboBox_MsoAmpModLFO][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			combobox_control_colors[ui->comboBox_MsoAmpModAdsr][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // W7
			combobox_control_colors[ui->comboBox_MsoAmpModAdsr][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			combobox_control_colors[ui->comboBox_MsoPwmModLFO][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G8
			combobox_control_colors[ui->comboBox_MsoPwmModLFO][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			combobox_control_colors[ui->comboBox_MsoPwmModAdsr][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G8
			combobox_control_colors[ui->comboBox_MsoPwmModAdsr][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			combobox_control_colors[ui->comboBox_MsoPreset][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G8
			combobox_control_colors[ui->comboBox_MsoPreset][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			// PAD
			combobox_control_colors[ui->comboBox_PadTuneOctave][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G9
			combobox_control_colors[ui->comboBox_PadTuneOctave][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			combobox_control_colors[ui->comboBox_PadTuneSemitones][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G9
			combobox_control_colors[ui->comboBox_PadTuneSemitones][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			combobox_control_colors[ui->comboBox_PadTuneCents][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G9
			combobox_control_colors[ui->comboBox_PadTuneCents][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			combobox_control_colors[ui->comboBox_PadFreqModLFO][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W9
			combobox_control_colors[ui->comboBox_PadFreqModLFO][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			combobox_control_colors[ui->comboBox_PadFreqModAdsr][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W9
			combobox_control_colors[ui->comboBox_PadFreqModAdsr][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			combobox_control_colors[ui->comboBox_PadAmpModLFO][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W9
			combobox_control_colors[ui->comboBox_PadAmpModLFO][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			combobox_control_colors[ui->comboBox_PadAmpModAdsr][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W9
			combobox_control_colors[ui->comboBox_PadAmpModAdsr][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			combobox_control_colors[ui->comboBox_PadShape][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G10
			combobox_control_colors[ui->comboBox_PadShape][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			combobox_control_colors[ui->comboBox_PadShapeCutoff][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G10
			combobox_control_colors[ui->comboBox_PadShapeCutoff][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			combobox_control_colors[ui->comboBox_PadBaseNote][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G10
			combobox_control_colors[ui->comboBox_PadBaseNote][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			combobox_control_colors[ui->comboBox_PadQuality][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G10
			combobox_control_colors[ui->comboBox_PadQuality][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			// Filter 1
			combobox_control_colors[ui->comboBox_FilterFreqModLfo_1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			combobox_control_colors[ui->comboBox_FilterFreqModLfo_1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			combobox_control_colors[ui->comboBox_FilterFreqModAdsr_1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			combobox_control_colors[ui->comboBox_FilterFreqModAdsr_1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			combobox_control_colors[ui->comboBox_FilterBand_1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G1
			combobox_control_colors[ui->comboBox_FilterBand_1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			// Filter 2
			combobox_control_colors[ui->comboBox_FilterFreqModLfo_2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			combobox_control_colors[ui->comboBox_FilterFreqModLfo_2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			combobox_control_colors[ui->comboBox_FilterFreqModAdsr_2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			combobox_control_colors[ui->comboBox_FilterFreqModAdsr_2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			combobox_control_colors[ui->comboBox_FilterBand_2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W1
			combobox_control_colors[ui->comboBox_FilterBand_2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			// FreeVerb3
			combobox_control_colors[ui->comboBox_ReverbType][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W2
			combobox_control_colors[ui->comboBox_ReverbType][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			// Equalizer
			combobox_control_colors[ui->comboBox_BandEquilizerPreset][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G3
			combobox_control_colors[ui->comboBox_BandEquilizerPreset][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			
			//LFOs
			combobox_control_colors[ui->comboBox_LFOwaveform_1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G3
			combobox_control_colors[ui->comboBox_LFOwaveform_1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			combobox_control_colors[ui->comboBox_LFOwaveform_2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G3
			combobox_control_colors[ui->comboBox_LFOwaveform_2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			combobox_control_colors[ui->comboBox_LFOwaveform_3][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G3
			combobox_control_colors[ui->comboBox_LFOwaveform_3][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			combobox_control_colors[ui->comboBox_LFOwaveform_4][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G3
			combobox_control_colors[ui->comboBox_LFOwaveform_4][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			combobox_control_colors[ui->comboBox_LFOwaveform_5][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G3
			combobox_control_colors[ui->comboBox_LFOwaveform_5][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			combobox_control_colors[ui->comboBox_LFOwaveform_6][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G3
			combobox_control_colors[ui->comboBox_LFOwaveform_6][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;
		}

		if (!midi_mixer_comboboxes_colors_initialized)
		{
			midi_mixer_comboboxes_colors_initialized = true;

			// MIDI Mixer
			Ui::Dialog_MidiMixer_1620x840 *mixer_ui = Dialog_MidiMixer::get_ui_instance();

			if (mixer_ui)
			{
				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G3
				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G3
				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_3][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G3
				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_3][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_4][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G3
				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_4][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_5][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G3
				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_5][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_6][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G3
				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_6][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_7][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G3
				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_7][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_8][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // G3
				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_8][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_9][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W3
				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_9][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_10][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W3
				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_10][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_11][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W3
				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_11][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_12][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W3
				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_12][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_13][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W3
				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_13][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_14][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W3
				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_14][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_15][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W3
				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_15][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_16][_KNOB_COLOR_INDEX] = _KNOBS_COLOR; // W3
				combobox_control_colors[mixer_ui->comboBox_MixerChPanModLfo_16][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;
			}
		}
	}

	return 0;
}

int ControlWidgetsColorManager::init_horizontal_slider_controls_colors()
{
	if (!analog_synth_horizontal_sliders_colors_initialized)
	{
		analog_synth_horizontal_sliders_colors_initialized = true;

		Ui::Dialog_AnalogSynth_1900x1000 *ui = Dialog_AnalogSynth_1900x1000::get_ui_instance();

		if (ui)
		{
			// OSC1
			horizontal_slider_control_colors[ui->horizontalSlider_Osc1Symmetry][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE; // G1
			horizontal_slider_control_colors[ui->horizontalSlider_Osc1Symmetry][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			horizontal_slider_control_colors[ui->horizontalSlider_Osc1Symmetry][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			// OSC2
			horizontal_slider_control_colors[ui->horizontalSlider_Osc2Symmetry][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE; // G3
			horizontal_slider_control_colors[ui->horizontalSlider_Osc2Symmetry][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			horizontal_slider_control_colors[ui->horizontalSlider_Osc2Symmetry][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			// Karplus-Strong Strings (KPS)
			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_WaveformVariations][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY; // G5
			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_WaveformVariations][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_WaveformVariations][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_OnDecay][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_OnDecay][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_OnDecay][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_OffDecay][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_OffDecay][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_OffDecay][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_StringDamping][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_StringDamping][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_StringDamping][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_StringDampingVariations][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_StringDampingVariations][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_StringDampingVariations][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_PluckDamping][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;
			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_PluckDamping][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;
			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_PluckDamping][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_PluckDampingVariations][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_RED;
			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_PluckDampingVariations][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_RED;
			horizontal_slider_control_colors[ui->horizontalSlider_KarplusSynth_PluckDampingVariations][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			// MSO
			horizontal_slider_control_colors[ui->horizontalSlider_MsoMorph][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_RED; // G8
			horizontal_slider_control_colors[ui->horizontalSlider_MsoMorph][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_RED;
			horizontal_slider_control_colors[ui->horizontalSlider_MsoMorph][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			// PAD
			horizontal_slider_control_colors[ui->horizontalSlider_PadBaseWidth][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_RED; // G10
			horizontal_slider_control_colors[ui->horizontalSlider_PadBaseWidth][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_RED;
			horizontal_slider_control_colors[ui->horizontalSlider_PadBaseWidth][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;
		}
	}

	return 0;
}

int ControlWidgetsColorManager::init_vertical_slider_controls_colors()
{

	if (!analog_synth_vertical_sliders_colors_initialized)
	{
		analog_synth_vertical_sliders_colors_initialized = true;
		Ui::Dialog_AnalogSynth_1900x1000 *ui = Dialog_AnalogSynth_1900x1000::get_ui_instance();

		if (ui)
		{
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_1][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY; // G2
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_1][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_1][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_2][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE; // G2
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_2][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_2][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_3][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE; // G2
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_3][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_3][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_4][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN; // G2
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_4][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_4][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_5][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE; // G2
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_5][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_5][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_6][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW; // G2
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_6][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_6][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_7][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY; // W2
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_7][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_7][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_8][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE; // W2
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_8][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_8][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_9][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE; // W2
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_9][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_9][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			vertical_slider_control_colors[ui->verticalSlider_Osc1HarmonyDistortLevel][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN; // W2
			vertical_slider_control_colors[ui->verticalSlider_Osc1HarmonyDistortLevel][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
			vertical_slider_control_colors[ui->verticalSlider_Osc1HarmonyDistortLevel][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			vertical_slider_control_colors[ui->verticalSlider_Osc1HarmonyDetuneLevel][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE; // W2
			vertical_slider_control_colors[ui->verticalSlider_Osc1HarmonyDetuneLevel][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
			vertical_slider_control_colors[ui->verticalSlider_Osc1HarmonyDetuneLevel][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			// MSO
			vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_a][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY; // G8
			vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_a][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
			vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_a][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_b][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE; // G8
			vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_b][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_b][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_c][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE; // G8
			vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_c][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_c][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_d][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN; // G8
			vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_d][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
			vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_d][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_e][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE; // G8
			vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_e][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
			vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_e][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_f][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW; // G8
			vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_f][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;
			vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_f][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			// PAD
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_1][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY; // G10
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_1][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_1][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_2][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE; // G10
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_2][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_2][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_3][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE; // G10
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_3][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_3][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_4][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN; // G10
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_4][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_4][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_5][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE; // G10
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_5][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_5][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_6][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW; // G10
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_6][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_6][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_7][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY; // W10
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_7][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_7][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_8][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE; // W10
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_8][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_8][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_9][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE; // W10
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_9][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_9][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_10][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_10][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
			vertical_slider_control_colors[ui->verticalSlider_PadHarmony_10][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			vertical_slider_control_colors[ui->verticalSlider_PadHarmonyDetune][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
			vertical_slider_control_colors[ui->verticalSlider_PadHarmonyDetune][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
			vertical_slider_control_colors[ui->verticalSlider_PadHarmonyDetune][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			// Filter 1
			vertical_slider_control_colors[ui->verticalSlider_FilterFreqModLfoLevel_1][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE; // G1
			vertical_slider_control_colors[ui->verticalSlider_FilterFreqModLfoLevel_1][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			vertical_slider_control_colors[ui->verticalSlider_FilterFreqModLfoLevel_1][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			vertical_slider_control_colors[ui->verticalSlider_FilterFreqModAdsrLevel_1][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE; // G1
			vertical_slider_control_colors[ui->verticalSlider_FilterFreqModAdsrLevel_1][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			vertical_slider_control_colors[ui->verticalSlider_FilterFreqModAdsrLevel_1][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			// Filter 2
			vertical_slider_control_colors[ui->verticalSlider_FilterFreqModLfoLevel_2][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE; // G1
			vertical_slider_control_colors[ui->verticalSlider_FilterFreqModLfoLevel_2][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			vertical_slider_control_colors[ui->verticalSlider_FilterFreqModLfoLevel_2][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			vertical_slider_control_colors[ui->verticalSlider_FilterFreqModAdsrLevel_2][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE; // G1
			vertical_slider_control_colors[ui->verticalSlider_FilterFreqModAdsrLevel_2][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			vertical_slider_control_colors[ui->verticalSlider_FilterFreqModAdsrLevel_2][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			// Equalizer
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer31][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY; // G3
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer31][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer31][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer62][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE; // G3
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer62][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer62][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer125][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE; // G3
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer125][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer125][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer250][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN; // G3
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer250][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer250][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer500][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE; // G3
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer500][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer500][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer1K][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW; // G3
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer1K][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer1K][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer2K][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_RED; // G3
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer2K][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_RED;
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer2K][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer4K][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLACK; // G3
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer4K][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer4K][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer8K][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY; // W3
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer8K][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer8K][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer16K][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE; // W3
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer16K][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			vertical_slider_control_colors[ui->verticalSlider_BandEquilizer16K][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			
			// ADSRs
			vertical_slider_control_colors[ui->verticalSlider_AdsrA_1][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
			vertical_slider_control_colors[ui->verticalSlider_AdsrA_1][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
			vertical_slider_control_colors[ui->verticalSlider_AdsrA_1][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			vertical_slider_control_colors[ui->verticalSlider_AdsrD_1][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			vertical_slider_control_colors[ui->verticalSlider_AdsrD_1][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			vertical_slider_control_colors[ui->verticalSlider_AdsrD_1][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			vertical_slider_control_colors[ui->verticalSlider_AdsrS_1][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			vertical_slider_control_colors[ui->verticalSlider_AdsrS_1][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			vertical_slider_control_colors[ui->verticalSlider_AdsrS_1][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			vertical_slider_control_colors[ui->verticalSlider_AdsrR_1][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
			vertical_slider_control_colors[ui->verticalSlider_AdsrR_1][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
			vertical_slider_control_colors[ui->verticalSlider_AdsrR_1][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			vertical_slider_control_colors[ui->verticalSlider_AdsrA_2][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
			vertical_slider_control_colors[ui->verticalSlider_AdsrA_2][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
			vertical_slider_control_colors[ui->verticalSlider_AdsrA_2][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			vertical_slider_control_colors[ui->verticalSlider_AdsrD_2][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;
			vertical_slider_control_colors[ui->verticalSlider_AdsrD_2][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;
			vertical_slider_control_colors[ui->verticalSlider_AdsrD_2][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			vertical_slider_control_colors[ui->verticalSlider_AdsrS_2][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_RED;
			vertical_slider_control_colors[ui->verticalSlider_AdsrS_2][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_RED;
			vertical_slider_control_colors[ui->verticalSlider_AdsrS_2][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			vertical_slider_control_colors[ui->verticalSlider_AdsrR_2][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;
			vertical_slider_control_colors[ui->verticalSlider_AdsrR_2][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;
			vertical_slider_control_colors[ui->verticalSlider_AdsrR_2][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

			vertical_slider_control_colors[ui->verticalSlider_AdsrA_3][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
			vertical_slider_control_colors[ui->verticalSlider_AdsrA_3][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
			vertical_slider_control_colors[ui->verticalSlider_AdsrA_3][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			vertical_slider_control_colors[ui->verticalSlider_AdsrD_3][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			vertical_slider_control_colors[ui->verticalSlider_AdsrD_3][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			vertical_slider_control_colors[ui->verticalSlider_AdsrD_3][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			vertical_slider_control_colors[ui->verticalSlider_AdsrS_3][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			vertical_slider_control_colors[ui->verticalSlider_AdsrS_3][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			vertical_slider_control_colors[ui->verticalSlider_AdsrS_3][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			vertical_slider_control_colors[ui->verticalSlider_AdsrR_3][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
			vertical_slider_control_colors[ui->verticalSlider_AdsrR_3][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
			vertical_slider_control_colors[ui->verticalSlider_AdsrR_3][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			vertical_slider_control_colors[ui->verticalSlider_AdsrA_4][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
			vertical_slider_control_colors[ui->verticalSlider_AdsrA_4][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
			vertical_slider_control_colors[ui->verticalSlider_AdsrA_4][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			vertical_slider_control_colors[ui->verticalSlider_AdsrD_4][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;
			vertical_slider_control_colors[ui->verticalSlider_AdsrD_4][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;
			vertical_slider_control_colors[ui->verticalSlider_AdsrD_4][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			vertical_slider_control_colors[ui->verticalSlider_AdsrS_4][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_RED;
			vertical_slider_control_colors[ui->verticalSlider_AdsrS_4][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_RED;
			vertical_slider_control_colors[ui->verticalSlider_AdsrS_4][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			vertical_slider_control_colors[ui->verticalSlider_AdsrR_4][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;
			vertical_slider_control_colors[ui->verticalSlider_AdsrR_4][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;
			vertical_slider_control_colors[ui->verticalSlider_AdsrR_4][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

			vertical_slider_control_colors[ui->verticalSlider_AdsrA_5][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
			vertical_slider_control_colors[ui->verticalSlider_AdsrA_5][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
			vertical_slider_control_colors[ui->verticalSlider_AdsrA_5][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			vertical_slider_control_colors[ui->verticalSlider_AdsrD_5][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			vertical_slider_control_colors[ui->verticalSlider_AdsrD_5][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			vertical_slider_control_colors[ui->verticalSlider_AdsrD_5][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			vertical_slider_control_colors[ui->verticalSlider_AdsrS_5][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			vertical_slider_control_colors[ui->verticalSlider_AdsrS_5][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			vertical_slider_control_colors[ui->verticalSlider_AdsrS_5][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			vertical_slider_control_colors[ui->verticalSlider_AdsrR_5][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
			vertical_slider_control_colors[ui->verticalSlider_AdsrR_5][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
			vertical_slider_control_colors[ui->verticalSlider_AdsrR_5][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			vertical_slider_control_colors[ui->verticalSlider_AdsrA_6][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
			vertical_slider_control_colors[ui->verticalSlider_AdsrA_6][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
			vertical_slider_control_colors[ui->verticalSlider_AdsrA_6][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			vertical_slider_control_colors[ui->verticalSlider_AdsrD_6][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;
			vertical_slider_control_colors[ui->verticalSlider_AdsrD_6][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;
			vertical_slider_control_colors[ui->verticalSlider_AdsrD_6][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			vertical_slider_control_colors[ui->verticalSlider_AdsrS_6][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_RED;
			vertical_slider_control_colors[ui->verticalSlider_AdsrS_6][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_RED;
			vertical_slider_control_colors[ui->verticalSlider_AdsrS_6][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			vertical_slider_control_colors[ui->verticalSlider_AdsrR_6][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;
			vertical_slider_control_colors[ui->verticalSlider_AdsrR_6][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;
			vertical_slider_control_colors[ui->verticalSlider_AdsrR_6][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;
			
		}
	}

	if (!midi_mixer_vertical_sliders_colors_initialized)
	{
		midi_mixer_vertical_sliders_colors_initialized = true;

		// MIDI Mixer
		Ui::Dialog_MidiMixer_1620x840 *mixer_ui = Dialog_MidiMixer::get_ui_instance();

		if (mixer_ui)
		{
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_1][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY; // G1
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_1][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_1][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_2][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE; // G1
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_2][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_2][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_3][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE; // G1
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_3][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_3][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_4][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN; // G1
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_4][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_4][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_5][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE; // G1
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_5][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_5][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_6][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW; // G1
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_6][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_6][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_7][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_RED; // G1
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_7][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_RED;
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_7][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_8][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLACK; // G1
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_8][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_8][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_9][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY; // W1
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_9][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_9][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_10][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE; // W1
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_10][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_10][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_11][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE; // W1
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_11][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_11][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_12][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN; // W1
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_12][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_12][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_13][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE; // W1
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_13][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_13][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_14][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW; // W1
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_14][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_14][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_15][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_RED; // W1
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_15][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_RED;
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_15][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_16][_VERTICAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLACK; // W1
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_16][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;
			vertical_slider_control_colors[mixer_ui->verticalSlider_MixerChLevel_16][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;
		}
	}

	return 0;
}

int ControlWidgetsColorManager::init_button_controls_colors()
{
	if (!analog_synth_buttons_colors_initialized)
	{
		analog_synth_buttons_colors_initialized = true;
		Ui::Dialog_AnalogSynth_1900x1000 *ui = Dialog_AnalogSynth_1900x1000::get_ui_instance();

		if (ui)
		{
			//button_control_colors[ui->pushButton_PadGenerate] = _CONTROLS_COLOR_BLACK;
			//
			//button_control_colors[ui->pushButton_AnalogSynth_Sketch_1] = _CONTROLS_COLOR_GRAY;
			//button_control_colors[ui->pushButton_AnalogSynth_Sketch_2] = _CONTROLS_COLOR_PURPLE;
			//button_control_colors[ui->pushButton_AnalogSynth_Sketch_3] = _CONTROLS_COLOR_BLUE;
			//
			//button_control_colors[ui->pushButton_Panic] = _CONTROLS_COLOR_RED;
			//
			//button_control_colors[ui->pushButton_EquilizerSetAllZero] = _CONTROLS_COLOR_RED;
		}
	}

	return 0;
}

int ControlWidgetsColorManager::init_checkbox_controls_colors()
{

	if (!analog_synth_checkboxes_colors_initialized)
	{		
		Ui::Dialog_AnalogSynth_1900x1000 *ui = Dialog_AnalogSynth_1900x1000::get_ui_instance();

		if (ui)
		{
			analog_synth_checkboxes_colors_initialized = true;
			
			checkbox_control_colors[ui->checkBox_Osc1Active] = new QColor[2];
			checkbox_control_colors[ui->checkBox_Osc1Active][0] = _CONTROLS_COLOR_GREEN;	// LED ON
			checkbox_control_colors[ui->checkBox_Osc1Active][1] = _CONTROLS_COLOR_GRAY; // Frame

			checkbox_control_colors[ui->checkBox_Osc1UnisonSquareWave] = new QColor[2];
			checkbox_control_colors[ui->checkBox_Osc1UnisonSquareWave][0] = _CONTROLS_COLOR_GREEN; // LED ON
			checkbox_control_colors[ui->checkBox_Osc1UnisonSquareWave][1] = _CONTROLS_COLOR_BLUE;  // Frame

			checkbox_control_colors[ui->checkBox_Osc2Active] = new QColor[2];
			checkbox_control_colors[ui->checkBox_Osc2Active][0] = _CONTROLS_COLOR_GREEN;	  // LED ON
			checkbox_control_colors[ui->checkBox_Osc2Active][1] = _CONTROLS_COLOR_GRAY;		  // Frame

			checkbox_control_colors[ui->checkBox_Osc2SyncOnOsc1] = new QColor[2];
			checkbox_control_colors[ui->checkBox_Osc2SyncOnOsc1][0] = _CONTROLS_COLOR_GREEN; // LED ON
			checkbox_control_colors[ui->checkBox_Osc2SyncOnOsc1][1] = _CONTROLS_COLOR_GRAY;	 // Frame

			checkbox_control_colors[ui->checkBox_MsoActive] = new QColor[2];
			checkbox_control_colors[ui->checkBox_MsoActive][0] = _CONTROLS_COLOR_GREEN;  // LED ON
			checkbox_control_colors[ui->checkBox_MsoActive][1] = _CONTROLS_COLOR_GRAY; // Frame

			checkbox_control_colors[ui->checkBox_NoiseActive] = new QColor[2];
			checkbox_control_colors[ui->checkBox_NoiseActive][0] = _CONTROLS_COLOR_GREEN;	  // LED ON
			checkbox_control_colors[ui->checkBox_NoiseActive][1] = _CONTROLS_COLOR_GRAY; // Frame

			checkbox_control_colors[ui->checkBox_KpsActive] = new QColor[2];
			checkbox_control_colors[ui->checkBox_KpsActive][0] = _CONTROLS_COLOR_GREEN;	// LED ON
			checkbox_control_colors[ui->checkBox_KpsActive][1] = _CONTROLS_COLOR_GRAY; // Frame

			checkbox_control_colors[ui->checkBox_PadActive] = new QColor[2];
			checkbox_control_colors[ui->checkBox_PadActive][0] = _CONTROLS_COLOR_GREEN;	 // LED ON
			checkbox_control_colors[ui->checkBox_PadActive][1] = _CONTROLS_COLOR_GRAY; // Frame

			checkbox_control_colors[ui->checkBox_Distortion_Active] = new QColor[2];
			checkbox_control_colors[ui->checkBox_Distortion_Active][0] = _CONTROLS_COLOR_GREEN;  // LED ON
			checkbox_control_colors[ui->checkBox_Distortion_Active][1] = _CONTROLS_COLOR_GRAY; // Frame

			checkbox_control_colors[ui->checkBox_Reverbration3_Active] = new QColor[2];
			checkbox_control_colors[ui->checkBox_Reverbration3_Active][0] = _CONTROLS_COLOR_GREEN;	// LED ON
			checkbox_control_colors[ui->checkBox_Reverbration3_Active][1] = _CONTROLS_COLOR_GRAY; // Frame

			checkbox_control_colors[ui->checkBox_Reverbration_Active] = new QColor[2];
			checkbox_control_colors[ui->checkBox_Reverbration_Active][0] = _CONTROLS_COLOR_GREEN;	 // LED ON
			checkbox_control_colors[ui->checkBox_Reverbration_Active][1] = _CONTROLS_COLOR_GRAY; // Frame

			checkbox_control_colors[ui->checkBox_Distortion_Active] = new QColor[2];
			checkbox_control_colors[ui->checkBox_Distortion_Active][0] = _CONTROLS_COLOR_GREEN; // LED ON
			checkbox_control_colors[ui->checkBox_Distortion_Active][1] = _CONTROLS_COLOR_GRAY;  // Frame

			checkbox_control_colors[ui->checkBox_Reverbration3_Active] = new QColor[2];
			checkbox_control_colors[ui->checkBox_Reverbration3_Active][0] = _CONTROLS_COLOR_GREEN; // LED ON
			checkbox_control_colors[ui->checkBox_Reverbration3_Active][1] = _CONTROLS_COLOR_GRAY;	// Frame

			checkbox_control_colors[ui->checkBox_Reverbration_Active] = new QColor[2];
			checkbox_control_colors[ui->checkBox_Reverbration_Active][0] = _CONTROLS_COLOR_GREEN; // LED ON
			checkbox_control_colors[ui->checkBox_Reverbration_Active][1] = _CONTROLS_COLOR_GRAY;  // Frame

			checkbox_control_colors[ui->checkBox_Filter2FollowFilter1] = new QColor[2];
			checkbox_control_colors[ui->checkBox_Filter2FollowFilter1][0] = _CONTROLS_COLOR_GREEN; // LED ON
			checkbox_control_colors[ui->checkBox_Filter2FollowFilter1][1] = _CONTROLS_COLOR_GRAY;  // Frame

			checkbox_control_colors[ui->checkBox_DistortionAutoGain] = new QColor[2];
			checkbox_control_colors[ui->checkBox_DistortionAutoGain][0] = _CONTROLS_COLOR_GREEN; // LED ON
			checkbox_control_colors[ui->checkBox_DistortionAutoGain][1] = _CONTROLS_COLOR_GRAY;  // Frame
		}
	}

	if (!midi_mixer_checkboxes_colors_initialized)
	{
		Ui::Dialog_MidiMixer_1620x840 *mixer_ui = Dialog_MidiMixer::get_ui_instance();

		if (mixer_ui)
		{

			midi_mixer_checkboxes_colors_initialized = true;

			// Activity LED checkboxes (LED style)
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_1] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_1][0] = _CONTROLS_COLOR_GREEN; // LED ON
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_1][1] = _CONTROLS_COLOR_GRAY;	// Frame

			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_2] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_2][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_2][1] = _CONTROLS_COLOR_PURPLE;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_3] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_3][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_3][1] = _CONTROLS_COLOR_BLUE;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_4] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_4][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_4][1] = _CONTROLS_COLOR_GREEN;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_5] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_5][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_5][1] = _CONTROLS_COLOR_WHITE;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_6] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_6][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_6][1] = _CONTROLS_COLOR_YELLOW;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_7] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_7][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_7][1] = _CONTROLS_COLOR_RED;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_8] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_8][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_8][1] = _CONTROLS_COLOR_BLACK;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_9] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_9][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_9][1] = _CONTROLS_COLOR_GRAY;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_10] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_10][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_10][1] = _CONTROLS_COLOR_PURPLE;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_11] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_11][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_11][1] = _CONTROLS_COLOR_BLUE;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_12] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_12][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_12][1] = _CONTROLS_COLOR_GREEN;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_13] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_13][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_13][1] = _CONTROLS_COLOR_WHITE;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_14] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_14][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_14][1] = _CONTROLS_COLOR_YELLOW;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_15] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_15][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_15][1] = _CONTROLS_COLOR_RED;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_16] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_16][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanActivity_16][1] = _CONTROLS_COLOR_BLACK;

			// Static level checkboxes (normal checkbox style)
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_1] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_1][0] = _CONTROLS_COLOR_GREEN; // Check
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_1][1] = _CONTROLS_COLOR_GRAY;  // Frame

			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_2] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_2][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_2][1] = _CONTROLS_COLOR_PURPLE;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_3] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_3][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_3][1] = _CONTROLS_COLOR_BLUE;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_4] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_4][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_4][1] = _CONTROLS_COLOR_GREEN;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_5] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_5][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_5][1] = _CONTROLS_COLOR_WHITE;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_6] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_6][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_6][1] = _CONTROLS_COLOR_YELLOW;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_7] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_7][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_7][1] = _CONTROLS_COLOR_RED;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_8] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_8][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_8][1] = _CONTROLS_COLOR_BLACK;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_9] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_9][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_9][1] = _CONTROLS_COLOR_GRAY;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_10] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_10][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_10][1] = _CONTROLS_COLOR_PURPLE;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_11] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_11][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_11][1] = _CONTROLS_COLOR_BLUE;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_12] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_12][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_12][1] = _CONTROLS_COLOR_GREEN;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_13] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_13][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_13][1] = _CONTROLS_COLOR_WHITE;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_14] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_14][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_14][1] = _CONTROLS_COLOR_YELLOW;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_15] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_15][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_15][1] = _CONTROLS_COLOR_RED;

			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_16] = new QColor[2];
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_16][0] = _CONTROLS_COLOR_GREEN;
			checkbox_control_colors[mixer_ui->checkBox_MixerChanStaticLevel_16][1] = _CONTROLS_COLOR_BLACK;
		}
	}

	return 0;
}

int ControlWidgetsColorManager::set_frame_color(CustomFrame *frame)
{

	return 0;	
}

int ControlWidgetsColorManager::set_dial_color(CustomDial *dial)
{
	if (dial == NULL)
	{
		return -1;
	}

	// Check if the dial exists in the map
	if (dial_control_colors.find(dial) ==
		dial_control_colors.end())
	{
		// Key doesn't exist
		return -1;
	}

	// Additional check: ensure the value is not NULL
	if (dial_control_colors[dial] == NULL)
	{
		return -1;
	}

	dial->setKnobColor(dial_control_colors[dial][_KNOB_COLOR_INDEX]);
	dial->setCircleColor(dial_control_colors[dial][_KNOB_CIRCLE_COLOR_INDEX]);

	return 0;
}

int ControlWidgetsColorManager::set_combobox_color(CustomComboBox *combobox)
{
	if (combobox == NULL)
	{
		return -1;
	}

	// Check if the combobox exists in the map
	if (combobox_control_colors.find(combobox) ==
		combobox_control_colors.end())
	{
		// Key doesn't exist
		return -1;
	}

	// Additional check: ensure the value is not NULL
	if (combobox_control_colors[combobox] == NULL)
	{
		return -1;
	}

	combobox->setBackgroundColor(combobox_control_colors[combobox][_COMBOBOX_BACKGROUND_COLOR_INDEX]);
	combobox->setFrameVisible(true);
	combobox->setFrameColor(combobox_control_colors[combobox][_COMBOBOX_FRAME_COLOR_INDEX]);
	combobox->setFrameWidth(2);
	
	return 0;
}

int ControlWidgetsColorManager::set_horizontal_slider_color(CustomHorizontalSlider *hslider)
{

	return 0;
}

int ControlWidgetsColorManager::set_vertical_slider_color(CustomVerticalSlider *vslider)
{

	if (vslider == NULL)
	{
		return -1;
	}

	// Check if the vslider exists in the map
	if (vertical_slider_control_colors.find(vslider) ==
		vertical_slider_control_colors.end())
	{
		// Key doesn't exist
		return -1;
	}
	// Additional check: ensure the value is not NULL

	if (vertical_slider_control_colors[vslider] == NULL)
	{
		return -1;
	}

	vslider->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	vslider->setFrameVisible(true);

	vslider->setFrameColor(vertical_slider_control_colors[vslider][_VERTICAL_SLIDER_FRAME_COLOR_INDEX]);
	vslider->setProgressColor(vertical_slider_control_colors[vslider][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX]);
	vslider->setHandleColor(vertical_slider_control_colors[vslider][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX]);

	vslider->setTrackColor(_CONTROLS_COLOR_LIGHT_GRAY);
	
	return 0;
}

int ControlWidgetsColorManager::set_button_color(CustomButton *button)
{
	if (button == NULL)
	{
		return -1;
	}

	// Check if the button exists in the map
	if (button_control_colors.find(button) ==
		button_control_colors.end())
	{
		// Key doesn't exist
		return -1;
	}
	// Additional check: ensure the value is not NULL	
	if (button_control_colors[button] == nullptr)
	{
		return -1;
	}

	button->setFrameColor(button_control_colors[button][_BUTTON_FRAME_COLOR_INDEX]);
	button->setTextColor(button_control_colors[button][_BUTTON_TEXT_COLOR_INDEX]);
	button->setBackgroundColor(button_control_colors[button][_BUTTON_BACKGROUND_COLOR_INDEX]);

	return 0;
}

int ControlWidgetsColorManager::set_checkbox_color(CustomCheckBox *checkbox)
{
	if (checkbox == nullptr)
	{
		return -1;
	}

	// Check if the checkbox exists in the map
	if (checkbox_control_colors.find(checkbox) == checkbox_control_colors.end())
	{
		return -1;
	}

	if (checkbox_control_colors[checkbox] == nullptr)
	{
		return -1;
	}

	// Set LED style for activity indicators
	checkbox->setLedStyle(true);
	checkbox->setLedOnColor(checkbox_control_colors[checkbox][0]);
	checkbox->setFrameColor(checkbox_control_colors[checkbox][1]);
	checkbox->setBackgroundColor(_CONTROLS_COLOR_BLACK);
	checkbox->setCheckBoxSize(16);
	checkbox->setFrameWidth(2);

	return 0;
}
