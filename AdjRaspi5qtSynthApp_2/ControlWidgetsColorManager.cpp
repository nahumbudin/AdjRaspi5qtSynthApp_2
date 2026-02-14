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
#include "MainWindow.h"
#include "ui_Dialog_AnalogSynth_1900x1000.h"

ControlWidgetsColorManager::ControlWidgetsColorManager(){

	int result;

	result = init_frames_colors();
	result = init_dial_controls_colors();
	result = init_combobox_controls_colors();
	result = init_horizontal_slider_controls_colors();
	result = init_vertical_slider_controls_colors();
	result = init_button_controls_colors();
}

ControlWidgetsColorManager::~ControlWidgetsColorManager()
{
}

int ControlWidgetsColorManager::init_frames_colors()
{
	Ui::Dialog_AnalogSynth_1900x1000 *ui = Dialog_AnalogSynth_1900x1000::get_ui_instance();

	frame_control_colors[ui->frame_Sketches] = _CONTROL_GROUP_WHITE; // Allways white

	// OSC1
	frame_control_colors[ui->frame_Osc1Waveform] = _CONTROL_GROUP_GRAY;						// G1
	frame_control_colors[ui->frame_Osc1TuneOffset] = _CONTROL_GROUP_GRAY;					// G1
	frame_control_colors[ui->frame_Osc1FrequencyModulation] = _CONTROL_GROUP_WHITE;			// W1
	frame_control_colors[ui->frame_Osc1AmpMod] = _CONTROL_GROUP_WHITE;						// W1
	frame_control_colors[ui->frame_Osc1Drawbars_1_6] = _CONTROL_GROUP_NOT_SELECTED;			// G2
	frame_control_colors[ui->frame_Osc1PwmMod] = _CONTROL_GROUP_NOT_SELECTED;				// G2
	frame_control_colors[ui->frame_Osc1Drawbars_7_9] = _CONTROL_GROUP_NOT_SELECTED;			// W2

	// OSC2
	frame_control_colors[ui->frame_Osc2Waveform] = _CONTROL_GROUP_NOT_SELECTED;				// G3
	frame_control_colors[ui->frame_Osc2TuneOffset] = _CONTROL_GROUP_NOT_SELECTED;			// G3
	frame_control_colors[ui->frame_Osc2FreqMod] = _CONTROL_GROUP_NOT_SELECTED;	// W3
	frame_control_colors[ui->frame_Osc2AmpMod] = _CONTROL_GROUP_NOT_SELECTED;				// W3
	frame_control_colors[ui->frame_Osc2PwmMod] = _CONTROL_GROUP_NOT_SELECTED;				// W4
	
	// Noise
	frame_control_colors[ui->frame_NoiseColor] = _CONTROL_GROUP_NOT_SELECTED;			// G5
	frame_control_colors[ui->frame_NoiseAmpMod] = _CONTROL_GROUP_NOT_SELECTED;				// G5

	// Karplus-Strong Strings (KPS)
	frame_control_colors[ui->frame_KarplusStringAll] = _CONTROL_GROUP_NOT_SELECTED;			// G6
	
	// MSO
	frame_control_colors[ui->frame_MsoSendFiltersTuneOffset] = _CONTROL_GROUP_NOT_SELECTED;	// G7
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

int ControlWidgetsColorManager::init_dial_controls_colors()
{
	Ui::Dialog_AnalogSynth_1900x1000 *ui = Dialog_AnalogSynth_1900x1000::get_ui_instance();

	// OSC1
	dial_control_colors[ui->dial_Osc1SendFilter1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;					// G1
	dial_control_colors[ui->dial_Osc1SendFilter1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

	dial_control_colors[ui->dial_Osc1SendFilter2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;					// G1
	dial_control_colors[ui->dial_Osc1SendFilter2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;		

	dial_control_colors[ui->dial_Osc1FreqModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;				// W1
	dial_control_colors[ui->dial_Osc1FreqModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

	dial_control_colors[ui->dial_Osc1FreqModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;				// W1
	dial_control_colors[ui->dial_Osc1FreqModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

	dial_control_colors[ui->dial_Osc1AmpModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;					// W1
	dial_control_colors[ui->dial_Osc1AmpModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

	dial_control_colors[ui->dial_Osc1AmpModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;				// W1
	dial_control_colors[ui->dial_Osc1AmpModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

	dial_control_colors[ui->dial_Osc1PwmModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;					// G2
	dial_control_colors[ui->dial_Osc1PwmModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

	dial_control_colors[ui->dial_Osc1PwmModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;				// G2	
	dial_control_colors[ui->dial_Osc1PwmModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

	// OSC2
	dial_control_colors[ui->dial_Osc2SendFilter1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;					// G3
	dial_control_colors[ui->dial_Osc2SendFilter1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

	dial_control_colors[ui->dial_Osc2SendFilter2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;					// G3
	dial_control_colors[ui->dial_Osc2SendFilter2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

	dial_control_colors[ui->dial_Osc2FreqModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;				// W3
	dial_control_colors[ui->dial_Osc2FreqModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

	dial_control_colors[ui->dial_Osc2FreqModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;				// W3
	dial_control_colors[ui->dial_Osc2FreqModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

	dial_control_colors[ui->dial_Osc2AmpModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;					// W3
	dial_control_colors[ui->dial_Osc2AmpModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

	dial_control_colors[ui->dial_Osc2AmpModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;				// W3
	dial_control_colors[ui->dial_Osc2AmpModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

	dial_control_colors[ui->dial_Osc2PwmModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;					// W4
	dial_control_colors[ui->dial_Osc2PwmModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

	dial_control_colors[ui->dial_Osc2PwmModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;				// W4
	dial_control_colors[ui->dial_Osc2PwmModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

	// Noise
	dial_control_colors[ui->dial_NoiseSendFilter1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;					// G4
	dial_control_colors[ui->dial_NoiseSendFilter1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

	dial_control_colors[ui->dial_NoiseSendFilter2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;					// G4
	dial_control_colors[ui->dial_NoiseSendFilter2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

	dial_control_colors[ui->dial_NoiseAmpModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;				// G4
	dial_control_colors[ui->dial_NoiseAmpModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

	dial_control_colors[ui->dial_NoiseAmpModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;				// G4
	dial_control_colors[ui->dial_NoiseAmpModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

	// Karplus-Strong Strings (KPS)
	dial_control_colors[ui->dial_KarplusSynth_SendFilter1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;			// G5
	dial_control_colors[ui->dial_KarplusSynth_SendFilter1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

	dial_control_colors[ui->dial_KarplusSynth_SendFilter2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;			// G5
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
	dial_control_colors[ui->dial_PadSendFilter1][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;						// G9
	dial_control_colors[ui->dial_PadSendFilter1][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

	dial_control_colors[ui->dial_PadSendFilter2][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;						// G9
	dial_control_colors[ui->dial_PadSendFilter2][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

	dial_control_colors[ui->dial_PadFreqModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;					// W9
	dial_control_colors[ui->dial_PadFreqModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

	dial_control_colors[ui->dial_PadFreqModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;					// W9
	dial_control_colors[ui->dial_PadFreqModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

	dial_control_colors[ui->dial_PadAmpModLFOLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;					// W9
	dial_control_colors[ui->dial_PadAmpModLFOLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

	dial_control_colors[ui->dial_PadAmpModAdsrLevel][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;					// W9
	dial_control_colors[ui->dial_PadAmpModAdsrLevel][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLACK;

	return 0;
}

int ControlWidgetsColorManager::init_combobox_controls_colors()
{
	Ui::Dialog_AnalogSynth_1900x1000 *ui = Dialog_AnalogSynth_1900x1000::get_ui_instance();

	
	// OSC1
	combobox_control_colors[ui->comboBox_Osc1Waveform][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;	// G1
	combobox_control_colors[ui->comboBox_Osc1Waveform][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

	combobox_control_colors[ui->comboBox_Osc1TuneOctave][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;	// G1
	combobox_control_colors[ui->comboBox_Osc1TuneOctave][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

	combobox_control_colors[ui->comboBox_Osc1TuneSemitones][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G1
	combobox_control_colors[ui->comboBox_Osc1TuneSemitones][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_RED;

	combobox_control_colors[ui->comboBox_Osc1TuneCents][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;		// G1
	combobox_control_colors[ui->comboBox_Osc1TuneCents][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

	combobox_control_colors[ui->comboBox_Osc1FreqModLFO][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;		// W1
	combobox_control_colors[ui->comboBox_Osc1FreqModLFO][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

	combobox_control_colors[ui->comboBox_Osc1FreqModAdsr][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;	// W1
	combobox_control_colors[ui->comboBox_Osc1FreqModAdsr][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

	combobox_control_colors[ui->comboBox_Osc1AmpModLFO][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;		// W1
	combobox_control_colors[ui->comboBox_Osc1AmpModLFO][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

	combobox_control_colors[ui->comboBox_Osc1AmpModAdsr][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;		// W1
	combobox_control_colors[ui->comboBox_Osc1AmpModAdsr][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

	combobox_control_colors[ui->comboBox_Osc1PwmModLFO][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;		// G2
	combobox_control_colors[ui->comboBox_Osc1PwmModLFO][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_RED;

	combobox_control_colors[ui->comboBox_Osc1PwmModAdsr][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;		// G2
	combobox_control_colors[ui->comboBox_Osc1PwmModAdsr][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

	combobox_control_colors[ui->comboBox_Osc1HammondPercussionMode][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G2
	combobox_control_colors[ui->comboBox_Osc1HammondPercussionMode][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

	combobox_control_colors[ui->comboBox_Osc1UnisonMode][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;				// G2
	combobox_control_colors[ui->comboBox_Osc1UnisonMode][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

	// OSC2
	combobox_control_colors[ui->comboBox_Osc2Waveform][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;				// G3
	combobox_control_colors[ui->comboBox_Osc2Waveform][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

	combobox_control_colors[ui->comboBox_Osc2TuneOctave][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;				// G3
	combobox_control_colors[ui->comboBox_Osc2TuneOctave][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

	combobox_control_colors[ui->comboBox_Osc2TuneSemitones][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;			// G3		
	combobox_control_colors[ui->comboBox_Osc2TuneSemitones][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_RED;

	combobox_control_colors[ui->comboBox_Osc2TuneCents][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;				// G3
	combobox_control_colors[ui->comboBox_Osc2TuneCents][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

	combobox_control_colors[ui->comboBox_Osc2FreqModLFO][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;				// W3
	combobox_control_colors[ui->comboBox_Osc2FreqModLFO][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

	combobox_control_colors[ui->comboBox_Osc2FreqModAdsr][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;			// W3
	combobox_control_colors[ui->comboBox_Osc2FreqModAdsr][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

	combobox_control_colors[ui->comboBox_Osc2AmpModLFO][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;				// W3
	combobox_control_colors[ui->comboBox_Osc2AmpModLFO][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

	combobox_control_colors[ui->comboBox_Osc2AmpModAdsr][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;				// W3
	combobox_control_colors[ui->comboBox_Osc2AmpModAdsr][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

	combobox_control_colors[ui->comboBox_Osc2PwmModLFO][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;				// W4
	combobox_control_colors[ui->comboBox_Osc2PwmModLFO][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

	combobox_control_colors[ui->comboBox_Osc2PwmModAdsr][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;				// W4
	combobox_control_colors[ui->comboBox_Osc2PwmModAdsr][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

	// Noise
	combobox_control_colors[ui->comboBox_NoiseColor][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;					// G4
	combobox_control_colors[ui->comboBox_NoiseColor][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

	combobox_control_colors[ui->comboBox_NoiseAmpModLFO][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;				// G4
	combobox_control_colors[ui->comboBox_NoiseAmpModLFO][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

	combobox_control_colors[ui->comboBox_NoiseAmpModAdsr][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;			// G4
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
	combobox_control_colors[ui->comboBox_MsoTuneSemitones][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_RED;

	combobox_control_colors[ui->comboBox_MsoTuneCents][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY; // G7
	combobox_control_colors[ui->comboBox_MsoTuneCents][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

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

	combobox_control_colors[ui->comboBox_MsoPreset][_COMBOBOX_BACKGROUND_COLOR_INDEX] = _CONTROLS_COLOR_DARK_GRAY;		// G8
	combobox_control_colors[ui->comboBox_MsoPreset][_COMBOBOX_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

	// PAD
	combobox_control_colors[ui->comboBox_PadTuneOctave][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;								// G9
	combobox_control_colors[ui->comboBox_PadTuneOctave][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

	combobox_control_colors[ui->comboBox_PadTuneSemitones][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;							// G9
	combobox_control_colors[ui->comboBox_PadTuneSemitones][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

	combobox_control_colors[ui->comboBox_PadTuneCents][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;								// G9
	combobox_control_colors[ui->comboBox_PadTuneCents][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

	combobox_control_colors[ui->comboBox_PadFreqModLFO][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;								// W9
	combobox_control_colors[ui->comboBox_PadFreqModLFO][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

	combobox_control_colors[ui->comboBox_PadFreqModAdsr][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;								// W9
	combobox_control_colors[ui->comboBox_PadFreqModAdsr][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

	combobox_control_colors[ui->comboBox_PadAmpModLFO][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;								// W9
	combobox_control_colors[ui->comboBox_PadAmpModLFO][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

	combobox_control_colors[ui->comboBox_PadAmpModAdsr][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;								// W9
	combobox_control_colors[ui->comboBox_PadAmpModAdsr][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

	combobox_control_colors[ui->comboBox_PadShape][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;									// G10	
	combobox_control_colors[ui->comboBox_PadShape][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

	combobox_control_colors[ui->comboBox_PadShapeCutoff][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;								// G10
	combobox_control_colors[ui->comboBox_PadShapeCutoff][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

	combobox_control_colors[ui->comboBox_PadBaseNote][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;								// G10
	combobox_control_colors[ui->comboBox_PadBaseNote][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

	combobox_control_colors[ui->comboBox_PadQuality][_KNOB_COLOR_INDEX] = _KNOBS_COLOR;									// G10
	combobox_control_colors[ui->comboBox_PadQuality][_KNOB_CIRCLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

	return 0;
}

int ControlWidgetsColorManager::init_horizontal_slider_controls_colors()
{
	Ui::Dialog_AnalogSynth_1900x1000 *ui = Dialog_AnalogSynth_1900x1000::get_ui_instance();
	
	// OSC1
	horizontal_slider_control_colors[ui->horizontalSlider_Osc1Symmetry][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;	// G1
	horizontal_slider_control_colors[ui->horizontalSlider_Osc1Symmetry][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
	horizontal_slider_control_colors[ui->horizontalSlider_Osc1Symmetry][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

	// OSC2
	horizontal_slider_control_colors[ui->horizontalSlider_Osc2Symmetry][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;	// G3
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
	horizontal_slider_control_colors[ui->horizontalSlider_MsoMorph][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_RED;			// G8
	horizontal_slider_control_colors[ui->horizontalSlider_MsoMorph][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_RED;
	horizontal_slider_control_colors[ui->horizontalSlider_MsoMorph][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

	// PAD
	horizontal_slider_control_colors[ui->horizontalSlider_PadBaseWidth][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_RED;		// G10
	horizontal_slider_control_colors[ui->horizontalSlider_PadBaseWidth][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_RED;
	horizontal_slider_control_colors[ui->horizontalSlider_PadBaseWidth][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_RED;

	return 0;
}

int ControlWidgetsColorManager::init_vertical_slider_controls_colors()
{
	Ui::Dialog_AnalogSynth_1900x1000 *ui = Dialog_AnalogSynth_1900x1000::get_ui_instance();

	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_1][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;		// G2
	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_1][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_1][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_2][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;	// G2
	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_2][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_2][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_3][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;		// G2
	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_3][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_3][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_4][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;		// G2
	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_4][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_4][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_5][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;		// G2
	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_5][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_5][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_6][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;	// G2
	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_6][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;
	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_6][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_7][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;		// W2
	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_7][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_7][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_8][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;	// W2
	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_8][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_8][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_9][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;		// W2
	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_9][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
	vertical_slider_control_colors[ui->verticalSlider_Osc1UnisonLevel_9][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

	vertical_slider_control_colors[ui->verticalSlider_Osc1HarmonyDistortLevel][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN; // W2
	vertical_slider_control_colors[ui->verticalSlider_Osc1HarmonyDistortLevel][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
	vertical_slider_control_colors[ui->verticalSlider_Osc1HarmonyDistortLevel][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

	vertical_slider_control_colors[ui->verticalSlider_Osc1HarmonyDetuneLevel][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE; // W2
	vertical_slider_control_colors[ui->verticalSlider_Osc1HarmonyDetuneLevel][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
	vertical_slider_control_colors[ui->verticalSlider_Osc1HarmonyDetuneLevel][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

	// MSO
	vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_a][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;				// G8
	vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_a][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
	vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_a][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

	vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_b][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;			// G8
	vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_b][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
	vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_b][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

	vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_c][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;				// G8
	vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_c][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
	vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_c][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

	vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_d][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;				// G8
	vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_d][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
	vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_d][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

	vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_e][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;				// G8
	vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_e][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
	vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_e][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

	vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_f][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;			// G8
	vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_f][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;
	vertical_slider_control_colors[ui->verticalSlider_MSO_Pos_f][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

	// PAD
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_1][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;			// G10
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_1][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_1][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_2][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;			// G10
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_2][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_2][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_3][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;			// G10
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_3][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_3][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_4][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;			// G10
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_4][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_4][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_5][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;			// G10
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_5][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_5][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_6][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;			// G10
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_6][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_6][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_YELLOW;

	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_7][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;			// W10
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_7][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_7][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GRAY;

	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_8][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE; // W10
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_8][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_8][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_PURPLE;

	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_9][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_BLUE; // W10
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_9][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_9][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_BLUE;

	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_10][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_10][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;
	vertical_slider_control_colors[ui->verticalSlider_PadHarmony_10][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_GREEN;

	vertical_slider_control_colors[ui->verticalSlider_PadHarmonyDetune][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
	vertical_slider_control_colors[ui->verticalSlider_PadHarmonyDetune][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;
	vertical_slider_control_colors[ui->verticalSlider_PadHarmonyDetune][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX] = _CONTROLS_COLOR_WHITE;

	return 0;
}

int ControlWidgetsColorManager::init_button_controls_colors()
{
	Ui::Dialog_AnalogSynth_1900x1000 *ui = Dialog_AnalogSynth_1900x1000::get_ui_instance();
	
	button_control_colors[ui->pushButton_PadGenerate] = _CONTROLS_COLOR_BLACK;

	button_control_colors[ui->pushButton_AnalogSynth_Sketch_1] = _CONTROLS_COLOR_GRAY;
	button_control_colors[ui->pushButton_AnalogSynth_Sketch_2] = _CONTROLS_COLOR_PURPLE;
	button_control_colors[ui->pushButton_AnalogSynth_Sketch_3] = _CONTROLS_COLOR_BLUE;

	button_control_colors[ui->pushButton_Panic] = _CONTROLS_COLOR_RED;

	return 0;
}
