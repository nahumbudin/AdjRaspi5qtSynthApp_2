/**
 * @file		Dialog_MidiMixer_ControlBox.cpp
 *	@author		Nahum Budin
 *	@date		22-Jan-2026
 *	@version	1.1
 *					1. New GUI layout 1620x840.
 *					2. Added pan modulationLFO selection and level control per channel.
 *					3. Added Send control per channel.
 *					4. Aded channel activity indication LED per channel.
 *
 *	@brief		Midi Mixer control dialog control boxs events handling
 *
 *	@History:
 *
 *		Version 1.0	22-Aug-2024
 *
 */

#include "Dialog_MidiMixer.h"
#include "ui_Dialog_MidiMixer_1620x840.h"
#include "GuiNavigator.h"

#include "utils.h"

void Dialog_MidiMixer::handle_control_box_event(int evnt, uint16_t val)
{
	int channel = -1;
	int level, level_slider_gap;
	Qt::CheckState checked;

	const int channel_level_max = 100;
	const int channels_level_min = 0;
	const int pan_max = 100;
	const int pan_min = 0;
	const int pan_mod_level_max = 100;
	const int pan_mod_level_min = 0;
	const int pan_mod_lfo_selection_max = 6; // _LFO_NONE + 5 LFOs
	const int pan_mod_lfo_selection_min = _LFO_NONE;
	const int send_level_max = 100;
	const int send_level_min = 0;

	static int pan_val[16] = {50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50};
	static int pan_mod_level_val[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	static int pan_mod_lfo_selection_val[16] = {_LFO_NONE,_LFO_NONE,_LFO_NONE,_LFO_NONE,_LFO_NONE,											 
												_LFO_NONE,_LFO_NONE,_LFO_NONE,_LFO_NONE,_LFO_NONE,											 
												_LFO_NONE,_LFO_NONE,_LFO_NONE,_LFO_NONE,_LFO_NONE,												 
												_LFO_NONE};
	static int send_level_val[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	static int prev_chan_level_val[16] = {64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64};
	static int prev_knob_pan_val[16] = {64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64};
	static int prev_knob_pan_mod_level_val[16] = {64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64};
	static int prev_knob_pan_mod_lfo_selection_val[16] = {64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64};
	static int prev_chan_send_level_val[16] = { 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64};

	if (!this->hasFocus()){
		// Only process events if this dialog has focus
		return;
	}

	if ((evnt <= _I2C_CONTROL_SLIDER_16) && (evnt >= _I2C_CONTROL_SLIDER_1))
	{
		// Slider events for channels 1-16 level control
		channel = evnt - _I2C_CONTROL_SLIDER_1; // Map slider event to channel index (0-15)

		level = normalize_slider_value(val / 37, channel_level_max, channels_level_min); // 0-3700
		// Change slider value only when it matches the UI slider position
		if (channels_levels[channel] > channel_level_max)
		{
			channels_levels[channel] = channel_level_max; // TODO: how did we get here?
		}
		level_slider_gap = channels_levels[channel] - level;

		if (abs((float)level_slider_gap) < ((channel_level_max - channels_level_min) / 5.0))
		{
			// Emits value changed signal.
			sliders_levels[channel]->setValue(level);
		}
	}
	else
	{
		if ((evnt <= _I2C_CONTROL_ENCODER_16) && (evnt >= _I2C_CONTROL_ENCODER_1))
		{
			// Dial events for channels 1-16 pan control and send control
			channel = evnt - _I2C_CONTROL_ENCODER_1; // Map encoder event to channel index (0-15)

			if (val == 4096)
			{
				// Knob pushbutton pressed - toggle static level state
				checkboxes_static_levels[channel]->setCheckState(checkboxes_static_levels[channel]->checkState() == Qt::Checked ? Qt::Unchecked : Qt::Checked);
			}
			else if (val == 8192)
			{
				// Knob pushbutton released
				
			}
			else
			{
				// Knob rotated
				GuiNavigator *navigator = GuiNavigator::get_instance();
				int current_frame_index = navigator->get_current_frame_index();

				switch (current_frame_index)
				{
				case 0:
					// Pans control box events for channels 1-16
					pan_val[channel] = update_rotary_encoder_value(
						pan_val[channel],
						val,
						&prev_knob_pan_val[channel],
						pan_min,
						pan_max,
						4);

					dials_pan[channel]->setValue(pan_val[channel]);

					break;

				case 1:
					// Pan modulation LFO level control box events for channels 1-16
					pan_mod_level_val[channel] = update_rotary_encoder_value(
						pan_mod_level_val[channel],
						val,
						&prev_knob_pan_mod_level_val[channel],
						pan_mod_level_min,
						pan_mod_level_max,
						4);

					dials_pan_lfo_mod_level[channel]->setValue(pan_mod_level_val[channel]);

					break;

				case 2:
					// Pan modulation LFO selection control box events for channels 1-16
					pan_mod_lfo_selection_val[channel] = update_rotary_encoder_value(
						pan_mod_lfo_selection_val[channel],
						val,
						&prev_knob_pan_mod_lfo_selection_val[channel],
						pan_mod_lfo_selection_min,
						pan_mod_lfo_selection_max,
						1);

					comboboxes_pan_lfo_mod[channel]->setCurrentIndex(pan_mod_lfo_selection_val[channel]);

					break;

				case 3:
					// Send control box events for channels 1-16
					send_level_val[channel] = update_rotary_encoder_value(
						send_level_val[channel],
						val,
						&prev_chan_send_level_val[channel],
						send_level_min,
						send_level_max,
						4);

					dials_send[channel]->setValue(send_level_val[channel]);

					break;
				}
			}
		}
	}

	/*

	if ((evnt == _CONTROL_FUNCTION_PUSHBUTTON_UP) &&
			 (val == 0))
	{

		// Toggle selected channels group
		if (active_channels_tab == _MIDI_MIXER_CHANNELS_1_8)
		{
			active_channels_tab = _MIDI_MIXER_CHANNELS_9_16;
			ui->tabWidget->setCurrentIndex(active_channels_tab);
		}
		else
		{
			active_channels_tab = _MIDI_MIXER_CHANNELS_1_8;
			ui->tabWidget->setCurrentIndex(active_channels_tab);
		}

	}
// COM Port box
	else if (evnt == _CONTROL_SLIDER_BLUE_GRAY)
	{
		channel = active_channels_tab * 8;

		volume = normalize_slider_value(val, channel_volume_max, channels_volume_min);
		// Change slider value only when it matches the UI slider position
		if (channels_volume[channel] > channel_volume_max)
		{
			channels_volume[channel] = channel_volume_max; // TODO: how did we get here?
		}
		volume_slider_gap = channels_volume[channel] - volume;

		if (abs((float)volume_slider_gap) < ((channel_volume_max - channels_volume_min) / 5.0))
		{
			if (channel == 0)
			{
				on_volume_slider_changed_ch_1(volume);
			}
			else
			{
				on_volume_slider_changed_ch_9(volume);
			}
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_RED)
	{
		channel = active_channels_tab * 8 + 1;

		volume = normalize_slider_value(val, channel_volume_max, channels_volume_min);
		// Change slider value only when it matches the UI slider position
		volume_slider_gap = channels_volume[channel] - volume;

		if (abs((float)volume_slider_gap) < ((channel_volume_max - channels_volume_min) / 5.0))
		{
			if (channel == 1)
			{
				on_volume_slider_changed_ch_2(volume);
			}
			else
			{
				on_volume_slider_changed_ch_10(volume);
			}
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_BLUE)
	{
		channel = active_channels_tab * 8 + 2;

		volume = normalize_slider_value(val, channel_volume_max, channels_volume_min);
		// Change slider value only when it matches the UI slider position
		volume_slider_gap = channels_volume[channel] - volume;

		if (abs((float)volume_slider_gap) < ((channel_volume_max - channels_volume_min) / 5.0))
		{
			if (channel == 2)
			{
				on_volume_slider_changed_ch_3(volume);
			}
			else
			{
				on_volume_slider_changed_ch_11(volume);
			}
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_WHITE)
	{
		channel = active_channels_tab * 8 + 3;

		volume = normalize_slider_value(val, channel_volume_max, channels_volume_min);
		// Change slider value only when it matches the UI slider position
		volume_slider_gap = channels_volume[channel] - volume;

		if (abs((float)volume_slider_gap) < ((channel_volume_max - channels_volume_min) / 5.0))
		{
			if (channel == 3)
			{
				on_volume_slider_changed_ch_4(volume);
			}
			else
			{
				on_volume_slider_changed_ch_12(volume);
			}
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_GRAY)
	{
		channel = active_channels_tab * 8 + 4;

		volume = normalize_slider_value(val, channel_volume_max, channels_volume_min);
		// Change slider value only when it matches the UI slider position
		volume_slider_gap = channels_volume[channel] - volume;

		if (abs((float)volume_slider_gap) < ((channel_volume_max - channels_volume_min) / 5.0))
		{
			if (channel == 4)
			{
				on_volume_slider_changed_ch_5(volume);
			}
			else
			{
				on_volume_slider_changed_ch_13(volume);
			}
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_RED)
	{
		channel = active_channels_tab * 8 + 5;

		volume = normalize_slider_value(val, channel_volume_max, channels_volume_min);
		// Change slider value only when it matches the UI slider position
		volume_slider_gap = channels_volume[channel] - volume;

		if (abs((float)volume_slider_gap) < ((channel_volume_max - channels_volume_min) / 5.0))
		{
			if (channel == 5)
			{
				on_volume_slider_changed_ch_6(volume);
			}
			else
			{
				on_volume_slider_changed_ch_14(volume);
			}
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_BLUE)
	{
		channel = active_channels_tab * 8 + 6;

		volume = normalize_slider_value(val, channel_volume_max, channels_volume_min);
		// Change slider value only when it matches the UI slider position
		volume_slider_gap = channels_volume[channel] - volume;
		if (abs((float)volume_slider_gap) < ((channel_volume_max - channels_volume_min) / 5.0))
		{
			if (channel == 6)
			{
				on_volume_slider_changed_ch_7(volume);
			}
			else
			{
				on_volume_slider_changed_ch_15(volume);
			}
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_WHITE)
	{
		channel = active_channels_tab * 8 + 7;

		volume = normalize_slider_value(val, channel_volume_max, channels_volume_min);
		// Change slider value only when it matches the UI slider position
		volume_slider_gap = channels_volume[channel] - volume;
		if (abs((float)volume_slider_gap) < ((channel_volume_max - channels_volume_min) / 5.0))
		{
			if (channel == 7)
			{
				on_volume_slider_changed_ch_8(volume);
			}
			else
			{
				on_volume_slider_changed_ch_16(volume);
			}
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_GREEN)
	{
		channel = active_channels_tab * 8;

		channels_pan[channel] =
			update_rotary_encoder_value(channels_pan[channel],
			val,
			&prev_knob_chan_vol_val[channel],
			channels_pan_min,
			channels_pan_max,
			4);

		if (channel == 0)
		{
			on_pan_dial_changed_ch_1(channels_pan[0]);
		}
		else
		{
			on_pan_dial_changed_ch_9(channels_pan[8]);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_RED)
	{
		channel = active_channels_tab * 8 + 1;

		channels_pan[channel] =
			update_rotary_encoder_value(channels_pan[channel],
			val,
			&prev_knob_chan_vol_val[channel],
			channels_pan_min,
			channels_pan_max,
			4);

		if (channel == 1)
		{
			on_pan_dial_changed_ch_2(channels_pan[1]);
		}
		else
		{
			on_pan_dial_changed_ch_10(channels_pan[9]);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_BLUE)
	{
		channel = active_channels_tab * 8 + 2;

		channels_pan[channel] =
			update_rotary_encoder_value(channels_pan[channel],
			val,
			&prev_knob_chan_vol_val[channel],
			channels_pan_min,
			channels_pan_max,
			4);

		if (channel == 2)
		{
			on_pan_dial_changed_ch_3(channels_pan[2]);
		}
		else
		{
			on_pan_dial_changed_ch_11(channels_pan[10]);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_WHITE)
	{
		channel = active_channels_tab * 8 + 3;

		channels_pan[channel] =
			update_rotary_encoder_value(channels_pan[channel],
			val,
			&prev_knob_chan_vol_val[channel],
			channels_pan_min,
			channels_pan_max,
			4);

		if (channel == 3)
		{
			on_pan_dial_changed_ch_4(channels_pan[3]);
		}
		else
		{
			on_pan_dial_changed_ch_12(channels_pan[11]);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_GREEN)
	{
		channel = active_channels_tab * 8 + 4;

		channels_pan[channel] =
			update_rotary_encoder_value(channels_pan[channel],
			val,
			&prev_knob_chan_vol_val[channel],
			channels_pan_min,
			channels_pan_max,
			4);

		if (channel == 4)
		{
			on_pan_dial_changed_ch_5(channels_pan[4]);
		}
		else
		{
			on_pan_dial_changed_ch_13(channels_pan[12]);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_RED)
	{
		channel = active_channels_tab * 8 + 5;

		channels_pan[channel] =
			update_rotary_encoder_value(channels_pan[channel],
			val,
			&prev_knob_chan_vol_val[channel],
			channels_pan_min,
			channels_pan_max,
			4);

		if (channel == 5)
		{
			on_pan_dial_changed_ch_6(channels_pan[5]);
		}
		else
		{
			on_pan_dial_changed_ch_14(channels_pan[13]);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_BLUE)
	{
		channel = active_channels_tab * 8 + 6;

		channels_pan[channel] =
			update_rotary_encoder_value(channels_pan[channel],
			val,
			&prev_knob_chan_vol_val[channel],
			channels_pan_min,
			channels_pan_max,
			4);

		if (channel == 6)
		{
			on_pan_dial_changed_ch_7(channels_pan[6]);
		}
		else
		{
			on_pan_dial_changed_ch_15(channels_pan[14]);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_WHITE)
	{
		channel = active_channels_tab * 8 + 7;

		channels_pan[channel] =
			update_rotary_encoder_value(channels_pan[channel],
			val,
			&prev_knob_chan_vol_val[channel],
			channels_pan_min,
			channels_pan_max,
			4);

		if (channel == 7)
		{
			on_pan_dial_changed_ch_8(channels_pan[7]);
		}
		else
		{
			on_pan_dial_changed_ch_16(channels_pan[15]);
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_GREEN)
	{
		if (val == 0)
		{
			// Only when pushbutton is pressed
			channel = active_channels_tab * 8;

			if (channel == 0)
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_1->checkState();
			}
			else
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_9->checkState();
			}
			// Toggle
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}

			if (channel == 0)
			{
				on_static_vol_checkbox_changed_ch_1(checked);
			}
			else
			{
				on_static_vol_checkbox_changed_ch_9(checked);
			}
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_RED)
	{
		if (val == 0)
		{
			// Only when pushbutton is pressed
			channel = active_channels_tab * 8 + 1;

			if (channel == 1)
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_2->checkState();
			}
			else
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_10->checkState();
			}
			// Toggle
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}

			if (channel == 1)
			{
				on_static_vol_checkbox_changed_ch_2(checked);
			}
			else
			{
				on_static_vol_checkbox_changed_ch_10(checked);
			}
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_BLUE)
	{
		if (val == 0)
		{
			// Only when pushbutton is pressed
			channel = active_channels_tab * 8 + 2;

			if (channel == 2)
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_3->checkState();
			}
			else
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_11->checkState();
			}
			// Toggle
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}

			if (channel == 2)
			{
				on_static_vol_checkbox_changed_ch_3(checked);
			}
			else
			{
				on_static_vol_checkbox_changed_ch_11(checked);
			}
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_WHITE)
	{
		if (val == 0)
		{
			// Only when pushbutton is pressed
			channel = active_channels_tab * 8 + 3;

			if (channel == 3)
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_4->checkState();
			}
			else
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_12->checkState();
			}
			// Toggle
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}

			if (channel == 3)
			{
				on_static_vol_checkbox_changed_ch_4(checked);
			}
			else
			{
				on_static_vol_checkbox_changed_ch_12(checked);
			}
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_ORANGE_GREEN)
	{
		if (val == 0)
		{
			// Only when pushbutton is pressed
			channel = active_channels_tab * 8 + 4;

			if (channel == 4)
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_5->checkState();
			}
			else
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_13->checkState();
			}
			// Toggle
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}

			if (channel == 4)
			{
				on_static_vol_checkbox_changed_ch_5(checked);
			}
			else
			{
				on_static_vol_checkbox_changed_ch_13(checked);
			}
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_ORANGE_RED)
	{
		if (val == 0)
		{
			// Only when pushbutton is pressed
			channel = active_channels_tab * 8 + 5;

			if (channel == 5)
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_6->checkState();
			}
			else
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_14->checkState();
			}
			// Toggle
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}

			if (channel == 5)
			{
				on_static_vol_checkbox_changed_ch_6(checked);
			}
			else
			{
				on_static_vol_checkbox_changed_ch_14(checked);
			}
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_ORANGE_BLUE)
	{
		if (val == 0)
		{
			// Only when pushbutton is pressed
			channel = active_channels_tab * 8 + 6;

			if (channel == 6)
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_7->checkState();
			}
			else
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_15->checkState();
			}
			// Toggle
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}

			if (channel == 6)
			{
				on_static_vol_checkbox_changed_ch_7(checked);
			}
			else
			{
				on_static_vol_checkbox_changed_ch_15(checked);
			}
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_ORANGE_WHITE)
	{
		if (val == 0)
		{
			// Only when pushbutton is pressed
			channel = active_channels_tab * 8 + 7;

			if (channel == 7)
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_8->checkState();
			}
			else
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_16->checkState();
			}
			// Toggle
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}

			if (channel == 7)
			{
				on_static_vol_checkbox_changed_ch_8(checked);
			}
			else
			{
				on_static_vol_checkbox_changed_ch_16(checked);
			}
		}
	}
*/
}