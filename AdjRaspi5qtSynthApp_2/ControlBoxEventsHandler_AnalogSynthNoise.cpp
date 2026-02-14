/**
 * @file		ControlBoxEventsHandler_AnalogSynthNoise
 *	@author		Nahum Budin
 *	@date		20-Dec-2025
 *	@version	2.0
 *					1. Use new control box event defines.
 *					2. Change background plates colors
 *					3. Split Osc2 and Noise control box event handlers
 *
 *	@brief		Used for controling the Analog Synthesizer Osc2 Tab
 *
 *	History:
 *			ver.1.0	1-Nov-2024
 *					1. First version.
 *
 *
 */

#include "Dialog_AnalogSynth.h"
#include "ui_Dialog_AnalogSynth.h"
#include "utils.h"

#include "libAdjRaspi5SynthAPI.h"

void Dialog_AnalogSynth::control_box_events_handler_noise(int evnt, uint16_t val)
{
	int level, level_slider_gap;
	Qt::CheckState checked;

	static int prev_knob_noise_send_filter_1_val = 64;
	static int prev_knob_noise_send_filter_2_val = 64;
	static int prev_knob_noise_amp_lfo_mod_level = 64;
	static int prev_knob_noise_amp_adsr_mod_level = 64;
	static int prev_combobox_noise_amp_lfo = 64;
	static int prev_combobox_noise_amp_adsr = 64;
	static int prev_combobox_noise_color = 64;

	if (!this->hasFocus())
	{
		return;
	}

	if ((evnt == _CONTROL_FUNCTION_PUSHBUTTON_ENTER) &&
		(val == 0))
	{
		/* Switch active frames */
		active_frames_group_noise++;

		if (active_frames_group_noise > _FRAMES_GROUP_3)
		{
			active_frames_group_noise = _FRAMES_GROUP_1;
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_BLUE)
	{
		/* Enable Noise */
		if (val == 0)
		{
			/* Only when pushbutton is pressed */
			checked = ui->checkBox_NoiseActive->checkState();

			/* Toggle */
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}

			on_noise_enable_changed(checked);
		}
	}

	if (!noise_enabled)
	{
		return;
	}

	if (evnt == _CONTROL_ENCODER_BLUE_PURPLE)
	{
		if ((active_frames_group_noise == _FRAMES_GROUP_3) && noise_enabled)
		{
			/* Noise Send Filter 1 */
			noise_send_filter_1_level = update_rotary_encoder_value(
				noise_send_filter_1_level,
				val,
				&prev_knob_noise_send_filter_2_val,
				_SEND_FILTER_MIN,
				_SEND_FILTER_MAX,
				4);

			on_noise_send_filter_1_dial_changed(noise_send_filter_1_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_GREEN)
	{
		if ((active_frames_group_noise == _FRAMES_GROUP_3) && noise_enabled)
		{
			/* Noise Send Filter 2 */
			noise_send_filter_2_level = update_rotary_encoder_value(
				noise_send_filter_2_level,
				val,
				&prev_knob_noise_send_filter_2_val,
				_SEND_FILTER_MIN,
				_SEND_FILTER_MAX,
				4);

			on_noise_send_filter_2_dial_changed(noise_send_filter_2_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_RED)
	{
		if ((active_frames_group_noise == _FRAMES_GROUP_3) && noise_enabled)
		{
			/* Noise Color */
			noise_color = update_rotary_encoder_value(
				noise_color,
				val,
				&prev_combobox_noise_color,
				_WHITE_NOISE,
				_BROWN_NOISE,
				1);

			on_noise_color_combobox_changed(noise_color);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_PURPLE)
	{
		if ((active_frames_group_noise == _FRAMES_GROUP_3) && noise_enabled)
		{
			/* Noise Select Amplitude Modulation LFO */
			noise_amp_mod_lfo_num = update_rotary_encoder_value(
				noise_amp_mod_lfo_num,
				val,
				&prev_combobox_noise_amp_lfo,
				_LFO_NONE,
				_LFO_6_DELAYED_2000MS,
				1);

			on_noise_amp_mod_lfo_combobox_changed(noise_amp_mod_lfo_num);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_GREEN)
	{
		if ((active_frames_group_noise == _FRAMES_GROUP_3) && noise_enabled)
		{
			/* Noise Amplitude Modulation LFO Level */
			noise_amp_mod_lfo_level = update_rotary_encoder_value(
				noise_amp_mod_lfo_level,
				val,
				&prev_knob_noise_amp_lfo_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);

			on_noise_amp_mod_lfo_level_dial_changed(noise_amp_mod_lfo_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_RED)
	{
		if ((active_frames_group_noise == _FRAMES_GROUP_3) && noise_enabled)
		{
			/* Noise Select Amplitude Modulation ADSR */
			noise_amp_mod_adsr_num = update_rotary_encoder_value(
				noise_amp_mod_adsr_num,
				val,
				&prev_combobox_noise_amp_adsr,
				_ENV_NONE,
				_ENV_6,
				1);

			on_noise_amp_mod_adsr_combobox_changed(noise_amp_mod_adsr_num);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_BLUE)
	{
		if ((active_frames_group_noise == _FRAMES_GROUP_3) && noise_enabled)
		{
			/* Noise Amplitude Modulation ADSR Level */
			noise_amp_mod_adsr_level = update_rotary_encoder_value(
				noise_amp_mod_adsr_level,
				val,
				&prev_knob_noise_amp_adsr_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);

			on_noise_amp_mod_adsr_level_dial_changed(noise_amp_mod_adsr_level);
		}
	}
}