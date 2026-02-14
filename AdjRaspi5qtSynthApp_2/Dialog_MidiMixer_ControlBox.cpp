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

void Dialog_MidiMixer::control_box_ui_update_callback(int evnt, uint16_t val)
{
	int channel = -1;
	int volume, volume_slider_gap;
	Qt::CheckState checked;

	static int prev_knob_chan_vol_val[16] = {64};

	if (!this->hasFocus())
	{
		return;
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