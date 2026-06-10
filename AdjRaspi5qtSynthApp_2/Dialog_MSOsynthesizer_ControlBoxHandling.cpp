/**
 * @file		Dialog_MSOsynthesizer.h
 *	@author		Nahum Budin
 *	@date		6-June-2026
 *	@version	1.0
 *
 *	Note - PWM or Symmetry Modulation is not implemented in the current version.
 *
 *	@brief		Adj MSO Synthesizer control box I2C messages handling
 *
 *	@History
 *
 */

#include "Dialog_MSOsynthesizer.h".cmake/
#include "ui_Dialog_MSOsynthesizer.h"

#include "GuiNavigator.h"
#include "Utils.h"

void Dialog_MSOsynthesizer::handle_control_box_event(int evnt, uint16_t val)
{
	// Only process events if this dialog has focus
	if (!this->hasFocus())
	{
		return;
	}

	GuiNavigator *nav = GuiNavigator::get_instance();

	int current_frame_index = nav->get_current_frame_index();

	int slider_level_gap = 0;

	const int mso_control_max = 100;
	const int mso_control_min = 0;

	const int tune_offset_octave_max = 12; // -6 octave offset (min) to +6 octave offset (max), with 0 octave offset centered (13 steps total starting at 0)
	const int tune_offset_octave_min = 0;
	const int tune_offset_semitone_max = 22; // -11 semitone offset (min) to +11 semitone offset (max), with 0 semitone offset centered (23 steps total starting at 0)
	const int tune_offset_semitone_min = 0;
	const int tune_offset_cents_max = 60; // -7.5 to +7.5 cents, with 0.25 cent steps (61 steps total starting at 0), with 0 cent offset centered
	const int tune_offset_cents_min = 0;

	const int segment_position_max = 2046;
	const int segment_position_min = 1;
	const int morph_max = 95;
	const int morph_min = 5;

	const int mod_lfo_waveform_max = _OSC_WAVEFORM_SAMPHOLD;
	const int mod_lfo_waveform_min = _OSC_WAVEFORM_SINE;

	const int waveform_preset_max = _OSC_WAVEFORM_TRIANGLE;
	const int waveform_preset_min = _OSC_WAVEFORM_SINE;

	const int filter_band_min = _FILTER_BAND_LPF;
	const int filter_band_max = _FILTER_BAND_PASS_ALL;

	int static mso_send_filter_1 = 40;

	static int mso_tune_offset_octave = 7;	  // 0 octave offset (centered), with range of -6 to +6 octaves (13 steps total)
	static int mso_tune_offset_semitone = 12; // 0 semitone offset (centered), with range of -11 to +11 semitones (23 steps total)
	static int mso_tune_offset_cents = 30;	  // 0 cent offset (centered), with range of -7.5 to +7.5 cents (61 steps total)

	static int segment_position_a = 512;  // Sine
	static int segment_position_b = 517;
	static int segment_position_c = 1024;
	static int segment_position_d = 1029;
	static int segment_position_e = 1536;
	static int segment_position_f = 1542;
	static int morph = 70;
	static int waveform_preset = _OSC_WAVEFORM_SINE;

	static int amp_mod_env_level = 0;
	static int amp_mod_env_attack = 5;
	static int amp_mod_env_decay = 10;
	static int amp_mod_env_sustain = 80;
	static int amp_mod_env_release = 10;
	static int amp_mod_lfo_level = 0;
	static int amp_mod_lfo_rate = 10;
	static int amp_mod_lfo_symmetry = 50;
	static int amp_mod_lfo_waveform = _OSC_WAVEFORM_SINE;

	static int freq_mod_env_level = 0;
	static int freq_mod_env_attack = 5;
	static int freq_mod_env_decay = 10;
	static int freq_mod_env_sustain = 80;
	static int freq_mod_env_release = 10;
	static int freq_mod_lfo_level = 0;
	static int freq_mod_lfo_rate = 10;
	static int freq_mod_lfo_symmetry = 50;
	static int freq_mod_lfo_waveform = _OSC_WAVEFORM_SINE;

	static int filter_frequency = 100;
	static int filter_modulation_octave = 100 / 7; // ~1.0,
	static int filter_q = 0;
	static int filter_kbd_tracking = 100;
	static int filter_band = _FILTER_BAND_PASS_ALL;

	static int filter_freq_mod_env_level = 0;
	static int filter_freq_mod_env_attack = 5;
	static int filter_freq_mod_env_decay = 10;
	static int filter_freq_mod_env_sustain = 80;
	static int filter_freq_mod_env_release = 10;
	static int filter_freq_mod_lfo_level = 0;
	static int filter_freq_mod_lfo_rate = 10;
	static int filter_freq_mod_lfo_symmetry = 50;
	static int filter_freq_mod_lfo_waveform = _OSC_WAVEFORM_SINE;

	int static prev_mso_send_filter_1 = 40;

	static int prev_mso_tune_offset_octave = 7;	   // 0 octave offset (centered), with range of -6 to +6 octaves (13 steps total)
	static int prev_mso_tune_offset_semitone = 12; // 0 semitone offset (centered), with range of -11 to +11 semitones (23 steps total)
	static int prev_mso_tune_offset_cents = 30;	  // 0 cent offset (centered), with range of -7.5 to +7.5 cents (61 steps total)

	static int prev_segment_position_a = 512; // Sine
	static int prev_segment_position_b = 517;
	static int prev_segment_position_c = 1024;
	static int prev_segment_position_d = 1029;
	static int prev_segment_position_e = 1536;
	static int prev_segment_position_f = 1542;
	static int prev_morph = 70;
	static int prev_waveform_preset = _OSC_WAVEFORM_SINE;

	static int prev_amp_mod_env_level = 0;
	static int prev_amp_mod_env_attack = 5;
	static int prev_amp_mod_env_decay = 10;
	static int prev_amp_mod_env_sustain = 80;
	static int prev_amp_mod_env_release = 10;
	static int prev_amp_mod_lfo_level = 0;
	static int prev_amp_mod_lfo_rate = 10;
	static int prev_amp_mod_lfo_symmetry = 50;
	static int prev_amp_mod_lfo_waveform = _OSC_WAVEFORM_SINE;

	static int prev_freq_mod_env_level = 0;
	static int prev_freq_mod_env_attack = 5;
	static int prev_freq_mod_env_decay = 10;
	static int prev_freq_mod_env_sustain = 80;
	static int prev_freq_mod_env_release = 10;
	static int prev_freq_mod_lfo_level = 0;
	static int prev_freq_mod_lfo_rate = 10;
	static int prev_freq_mod_lfo_symmetry = 50;
	static int prev_freq_mod_lfo_waveform = _OSC_WAVEFORM_SINE;

	static int prev_filter_frequency = 100;
	static int prev_filter_modulation_octave = 100 / 7; // ~1.0,
	static int prev_filter_q = 0;
	static int prev_filter_kbd_tracking = 100;
	static int prev_filter_band = _FILTER_BAND_PASS_ALL;

	static int prev_filter_freq_mod_env_level = 0;
	static int prev_filter_freq_mod_env_attack = 5;
	static int prev_filter_freq_mod_env_decay = 10;
	static int prev_filter_freq_mod_env_sustain = 80;
	static int prev_filter_freq_mod_env_release = 10;
	static int prev_filter_freq_mod_lfo_level = 0;
	static int prev_filter_freq_mod_lfo_rate = 10;
	static int prev_filter_freq_mod_lfo_symmetry = 50;
	static int prev_filter_freq_mod_lfo_waveform = _OSC_WAVEFORM_SINE;

	if (current_frame_index == 0)
	{
		// Send Filter, Tune and waveform controls
		// Grey Frame
		// Presets, Send Filter, Tune and Modulation controls and Harmonies 1-6
		if (evnt == _I2C_CONTROL_ENCODER_1)
		{
			// Gray Gray dial - Send Filter 1 control
			mso_send_filter_1 = update_rotary_encoder_value(
				mso_send_filter_1,
				val,
				&prev_mso_send_filter_1,
				mso_control_min,
				mso_control_max,
				4);

			ui->dial_MsoSynthSendFilter->setValue(mso_send_filter_1);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_2)
		{
			// Gray Purple dial - Detune Octave control and open presets dialog if pressed
			if (val == 4096)
			{
				// pressed - open presets dialog
				on_presets_open_pushbutton_clicked();
			}
			else
			{
				// Gray Purple dial - Detune Octave control
				mso_tune_offset_octave = update_rotary_encoder_value(
					mso_tune_offset_octave,
					val,
					&prev_mso_tune_offset_octave,
					tune_offset_octave_min,
					tune_offset_octave_max,
					1);

				ui->comboBox_MsoSynthTuneOctave->setCurrentIndex(mso_tune_offset_octave);
			}
		}
		else if (evnt == _I2C_CONTROL_ENCODER_3)
		{
			// Gray Blue dial - Detune Semitone control and save presets dialog if pressed
			if (val == 4096)
			{
				// pressed - save presets dialog
				on_presets_save_pushbutton_clicked();
			}
			else
			{
				// Gray Blue dial - Detune Semitone control
				mso_tune_offset_semitone = update_rotary_encoder_value(
					mso_tune_offset_semitone,
					val,
					&prev_mso_tune_offset_semitone,
					tune_offset_semitone_min,
					tune_offset_semitone_max,
					1);

				ui->comboBox_MsoSynthTuneSemitones->setCurrentIndex(mso_tune_offset_semitone);
			}
		}
		else if (evnt == _I2C_CONTROL_ENCODER_4)
		{
			// Gray Green dial - Detune cents control and save presets dialog if pressed
			mso_tune_offset_cents = update_rotary_encoder_value(
				mso_tune_offset_cents,
				val,
				&prev_mso_tune_offset_cents,
				tune_offset_cents_min,
				tune_offset_cents_max,
				1);

			ui->comboBox_MsoSynthTuneCents->setCurrentIndex(mso_tune_offset_cents);
		}

		// White Frame.
		else if (evnt == _I2C_CONTROL_ENCODER_11)
		{
			// White Blue dial - Preset combobox control
			waveform_preset = update_rotary_encoder_value(
				waveform_preset,
				val,
				&prev_waveform_preset,
				waveform_preset_min,
				waveform_preset_max,
				1);

			ui->comboBox_MsoSynthPreset->setCurrentIndex(waveform_preset);
		}
		else if (evnt == _I2C_CONTROL_SLIDER_9)
		{
			// White Gray slider - Position a
			// Get new position value from slider and calculate gap from current UI value
			segment_position_a = normalize_slider_value(val / 37, segment_position_max, 1);						 // 0-3700
			slider_level_gap = segment_position_a - ui->verticalSlider_MSOSynth_Pos_a->value(); // 1-2046

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < segment_position_max / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_MSOSynth_Pos_a->setValue(segment_position_a);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_10)
		{
			// White Purple slider - Position b
			// Get new position value from slider and calculate gap from current UI value
			segment_position_b = normalize_slider_value(val / 37, segment_position_max, 1);						// 0-3700
			slider_level_gap = segment_position_b - ui->verticalSlider_MSOSynth_Pos_b->value(); // 1-2046

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < segment_position_max / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_MSOSynth_Pos_b->setValue(segment_position_b);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_11)
		{
			// White Blue slider - Position c
			// Get new position value from slider and calculate gap from current UI value
			segment_position_c = normalize_slider_value(val / 37, segment_position_max, 1);						// 0-3700
			slider_level_gap = segment_position_c - ui->verticalSlider_MSOSynth_Pos_c->value(); // 1-2046

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < segment_position_max / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_MSOSynth_Pos_c->setValue(segment_position_c);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_12)
		{
			// White Green slider - Position d
			// Get new position value from slider and calculate gap from current UI value
			segment_position_d = normalize_slider_value(val / 37, segment_position_max, 1);						// 0-3700
			slider_level_gap = segment_position_d - ui->verticalSlider_MSOSynth_Pos_d->value(); // 1-2046

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < segment_position_max / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_MSOSynth_Pos_d->setValue(segment_position_d);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_13)
		{
			// White White slider - Position e
			// Get new position value from slider and calculate gap from current UI value
			segment_position_e = normalize_slider_value(val / 37, segment_position_max, 1);						// 0-3700
			slider_level_gap = segment_position_e - ui->verticalSlider_MSOSynth_Pos_e->value(); // 1-2046

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < segment_position_max / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_MSOSynth_Pos_e->setValue(segment_position_e);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_14)
		{
			// White Yelow slider - Position f
			// Get new position value from slider and calculate gap from current UI value
			segment_position_f = normalize_slider_value(val / 37, segment_position_max, 1);						// 0-3700
			slider_level_gap = segment_position_f - ui->verticalSlider_MSOSynth_Pos_f->value(); // 1-2046

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < segment_position_max / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_MSOSynth_Pos_f->setValue(segment_position_f);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_15)
		{
			// White Red slider - Morph
			// Get new position value from slider and calculate gap from current UI value
			morph = normalize_slider_value(val / 37, 100, 0);						// 0-3700
			slider_level_gap = morph - ui->horizontalSlider_MsoSynthMorph->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->horizontalSlider_MsoSynthMorph->setValue(morph);
			}
		}
	}
	else if (current_frame_index == 1)
	{
		// Amplitude and Frequency Modulation controls
		// Grey Frame
		if (evnt == _I2C_CONTROL_ENCODER_2)
		{
			// Gray Purple dial - Amp Modulation Envelope level control
			amp_mod_env_level = update_rotary_encoder_value(
				amp_mod_env_level,
				val,
				&prev_amp_mod_env_level,
				mso_control_min,
				mso_control_max,
				4);

			ui->dial_MSOsynth_AmpModAdsrLevel->setValue(amp_mod_env_level);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_3)
		{
			// Gray Blue dial - Amp Modulation LFO level control
			amp_mod_lfo_level = update_rotary_encoder_value(
				amp_mod_lfo_level,
				val,
				&prev_amp_mod_lfo_level,
				mso_control_min,
				mso_control_max,
				4);

			ui->dial_MSOsynth_AmpModLFOLevel->setValue(amp_mod_lfo_level);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_4)
		{
			// Gray Green dial - Amp Modulation LFO waveform combobox control
			amp_mod_lfo_waveform = update_rotary_encoder_value(
				amp_mod_lfo_waveform,
				val,
				&prev_amp_mod_lfo_waveform,
				mod_lfo_waveform_min,
				mod_lfo_waveform_max,
				1);

			ui->comboBox_MSOsynth_AmpModLFOwaveform->setCurrentIndex(amp_mod_lfo_waveform);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_5)
		{
			// Gray White dial - Amp Modulation LFO symmetry control
			amp_mod_lfo_symmetry = update_rotary_encoder_value(
				amp_mod_lfo_symmetry,
				val,
				&prev_amp_mod_lfo_symmetry,
				mso_control_min,
				mso_control_max,
				4);

			ui->dial_MSOsynth_AmpModLFOsymmetry->setValue(amp_mod_lfo_symmetry);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_6)
		{
			// Gray Yellow dial - Amp Modulation LFO rate control
			amp_mod_lfo_rate = update_rotary_encoder_value(
				amp_mod_lfo_rate,
				val,
				&prev_amp_mod_lfo_rate,
				mso_control_min,
				mso_control_max,
				4);

			ui->dial_MSOsynth_AmpModLFOrate->setValue(amp_mod_lfo_rate);
		}
		else if (evnt == _I2C_CONTROL_SLIDER_2)
		{
			// Gray Purple slider - Amp Modulation Envelope Attack control
			amp_mod_env_attack = normalize_slider_value(val / 37, 100, 0);						// 0-3700
			slider_level_gap = amp_mod_env_attack - ui->verticalSlider_MSOsynth_AmpModAdsrA->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_MSOsynth_AmpModAdsrA->setValue(amp_mod_env_attack);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_3)
		{
			// Gray Blue slider - Amp Modulation Envelope Decay control
			amp_mod_env_decay = normalize_slider_value(val / 37, 100, 0);							  // 0-3700
			slider_level_gap = amp_mod_env_decay - ui->verticalSlider_MSOsynth_AmpModAdsrD->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_MSOsynth_AmpModAdsrD->setValue(amp_mod_env_decay);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_4)
		{
			// Gray Green slider - Amp Modulation Envelope Sustain control
			amp_mod_env_sustain = normalize_slider_value(val / 37, 100, 0);							  // 0-3700
			slider_level_gap = amp_mod_env_sustain - ui->verticalSlider_MSOsynth_AmpModAdsrS->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_MSOsynth_AmpModAdsrS->setValue(amp_mod_env_sustain);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_5)
		{
			// Gray White slider - Amp Modulation Envelope Release control
			amp_mod_env_release = normalize_slider_value(val / 37, 100, 0);							  // 0-3700
			slider_level_gap = amp_mod_env_release - ui->verticalSlider_MSOsynth_AmpModAdsrR->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_MSOsynth_AmpModAdsrR->setValue(amp_mod_env_release);
			}
		}		
		
		// White Frame.
		else if (evnt == _I2C_CONTROL_ENCODER_10)
		{
			// White Purple dial - Freq Modulation Envelope level control
			freq_mod_env_level = update_rotary_encoder_value(
				freq_mod_env_level,
				val,
				&prev_freq_mod_env_level,
				mso_control_min,
				mso_control_max,
				4);

			ui->dial_MSOsynth_FreqModAdsrLevel->setValue(freq_mod_env_level);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_11)
		{
			// White Blue dial - Freq Modulation LFO level control
			freq_mod_lfo_level = update_rotary_encoder_value(
				freq_mod_lfo_level,
				val,
				&prev_freq_mod_lfo_level,
				mso_control_min,
				mso_control_max,
				4);

			ui->dial_MSOsynth_FreqModLFOLevel->setValue(freq_mod_lfo_level);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_12)
		{
			// White Green dial - Freq Modulation LFO waveform control
			freq_mod_lfo_waveform = update_rotary_encoder_value(
				freq_mod_lfo_waveform,
				val,
				&prev_freq_mod_lfo_waveform,
				mod_lfo_waveform_min,
				mod_lfo_waveform_max,
				1);

			ui->comboBox_MSOsynth_FreqModLFOwaveform->setCurrentIndex(freq_mod_lfo_waveform);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_13)
		{
			// White White dial - Freq Modulation LFO symmetry control
			freq_mod_lfo_symmetry = update_rotary_encoder_value(
				freq_mod_lfo_symmetry,
				val,
				&prev_freq_mod_lfo_symmetry,
				mso_control_min,
				mso_control_max,
				4);

			ui->dial_MSOsynth_FreqModLFOsymmetry->setValue(freq_mod_lfo_symmetry);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_14)
		{
			// White Yellow dial - Freq Modulation LFO rate control
			freq_mod_lfo_rate = update_rotary_encoder_value(
				freq_mod_lfo_rate,
				val,
				&prev_freq_mod_lfo_rate,
				mso_control_min,
				mso_control_max,
				4);

			ui->dial_MSOsynth_FreqModLFOrate->setValue(freq_mod_lfo_rate);
		}
		else if (evnt == _I2C_CONTROL_SLIDER_10)
		{
			// White Purple slider - Freq Modulation Envelope Attack control
			freq_mod_env_attack = normalize_slider_value(val / 37, 100, 0);							  // 0-3700
			slider_level_gap = freq_mod_env_attack - ui->verticalSlider_MSOsynth_FreqModAdsrA->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_MSOsynth_FreqModAdsrA->setValue(freq_mod_env_attack);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_11)
		{
			// White Blue slider - Freq Modulation Envelope Decay control
			freq_mod_env_decay = normalize_slider_value(val / 37, 100, 0);							 // 0-3700
			slider_level_gap = freq_mod_env_decay - ui->verticalSlider_MSOsynth_FreqModAdsrD->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_MSOsynth_FreqModAdsrD->setValue(freq_mod_env_decay);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_12)
		{
			// White Green slider - Freq Modulation Envelope Sustain control
			freq_mod_env_sustain = normalize_slider_value(val / 37, 100, 0);							   // 0-3700
			slider_level_gap = freq_mod_env_sustain - ui->verticalSlider_MSOsynth_FreqModAdsrS->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_MSOsynth_FreqModAdsrS->setValue(freq_mod_env_sustain);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_13)
		{
			// White White slider - Freq Modulation Envelope Release control
			freq_mod_env_release = normalize_slider_value(val / 37, 100, 0);							   // 0-3700
			slider_level_gap = freq_mod_env_release - ui->verticalSlider_MSOsynth_FreqModAdsrR->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_MSOsynth_FreqModAdsrR->setValue(freq_mod_env_release);
			}
		}
	}
	else if (current_frame_index == 2)
	{
		// Filter controls
		// Grey Frame
		if (evnt == _I2C_CONTROL_ENCODER_1)
		{
			// Gray Gray dial - Filter Frequency  control
			filter_frequency = update_rotary_encoder_value(
				filter_frequency,
				val,
				&prev_filter_frequency,
				mso_control_min,
				mso_control_max,
				4);

			ui->dial_MsoSynthFilterFreq->setValue(filter_frequency);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_2)
		{
			// Gray Purple dial - Filter Modulation Octave control
			filter_modulation_octave = update_rotary_encoder_value(
				filter_modulation_octave,
				val,
				&prev_filter_modulation_octave,
				mso_control_min,
				mso_control_max,
				4);

			ui->dial_MsoSynthFilterOctave->setValue(filter_modulation_octave);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_3)
		{
			// Gray Blue dial - Filter Q control
			filter_q = update_rotary_encoder_value(
				filter_q,
				val,
				&prev_filter_q,
				mso_control_min,
				mso_control_max,
				4);

			ui->dial_MsoSynthFilterQ->setValue(filter_q);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_4)
		{
			// Gray Green dial - Filter Keyboard Tracking control
			filter_kbd_tracking = update_rotary_encoder_value(
				filter_kbd_tracking,
				val,
				&prev_filter_kbd_tracking,
				mso_control_min,
				mso_control_max,
				4);

			ui->dial_MsoSynthFilterKbdTrack->setValue(filter_kbd_tracking);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_5)
		{
			// Gray White dial - Filter Band Combobox control
			filter_band = update_rotary_encoder_value(
				filter_band,
				val,
				&prev_filter_band,
				filter_band_min,
				filter_band_max,
				1);

			ui->comboBox_MsoSynthFilterBand->setCurrentIndex(filter_band);
		}

		// White Frame.
		else if (evnt == _I2C_CONTROL_ENCODER_10)
		{
			// White Purple dial - FilterFreq Modulation Envelope level control
			filter_freq_mod_env_level = update_rotary_encoder_value(
				filter_freq_mod_env_level,
				val,
				&prev_filter_freq_mod_env_level,
				mso_control_min,
				mso_control_max,
				4);

			ui->dial_MSOsynth_FilterFreqModAdsrLevel->setValue(filter_freq_mod_env_level);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_11)
		{
			// White Blue dial - Filter Freq Modulation LFO level control
			filter_freq_mod_lfo_level = update_rotary_encoder_value(
				filter_freq_mod_lfo_level,
				val,
				&prev_filter_freq_mod_lfo_level,
				mso_control_min,
				mso_control_max,
				4);

			ui->dial_MSOsynth_FilterFreqModLFOLevel->setValue(filter_freq_mod_lfo_level);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_12)
		{
			// White Green dial - Filter Freq Modulation LFO waveform control
			filter_freq_mod_lfo_waveform = update_rotary_encoder_value(
				filter_freq_mod_lfo_waveform,
				val,
				&prev_filter_freq_mod_lfo_waveform,
				mod_lfo_waveform_min,
				mod_lfo_waveform_max,
				1);

			ui->comboBox_MSOsynth_FilterFreqModLFOwaveform->setCurrentIndex(filter_freq_mod_lfo_waveform);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_13)
		{
			// White White dial - Filter Freq Modulation LFO symmetry control
			filter_freq_mod_lfo_symmetry = update_rotary_encoder_value(
				filter_freq_mod_lfo_symmetry,
				val,
				&prev_filter_freq_mod_lfo_symmetry,
				mso_control_min,
				mso_control_max,
				4);

			ui->dial_MSOsynth_FilterFreqModLFOsymmetry->setValue(filter_freq_mod_lfo_symmetry);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_14)
		{
			// White Yellow dial - Filter Freq Modulation LFO rate control
			filter_freq_mod_lfo_rate = update_rotary_encoder_value(
				filter_freq_mod_lfo_rate,
				val,
				&prev_filter_freq_mod_lfo_rate,
				mso_control_min,
				mso_control_max,
				4);

			ui->dial_MSOsynth_FilterFreqModLFOrate->setValue(filter_freq_mod_lfo_rate);
		}
		else if (evnt == _I2C_CONTROL_SLIDER_10)
		{
			// White Purple slider - Filter Freq Modulation Envelope Attack control
			filter_freq_mod_env_attack = normalize_slider_value(val / 37, 100, 0);								// 0-3700
			slider_level_gap = filter_freq_mod_env_attack - ui->verticalSlider_MSOsynth_FilterFreqModAdsrA->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_MSOsynth_FilterFreqModAdsrA->setValue(filter_freq_mod_env_attack);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_11)
		{
			// White Blue slider - Filter Freq Modulation Envelope Decay control
			filter_freq_mod_env_decay = normalize_slider_value(val / 37, 100, 0);							   // 0-3700
			slider_level_gap = filter_freq_mod_env_decay - ui->verticalSlider_MSOsynth_FilterFreqModAdsrD->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_MSOsynth_FilterFreqModAdsrD->setValue(filter_freq_mod_env_decay);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_12)
		{
			// White Green slider - Filter Freq Modulation Envelope Sustain control
			filter_freq_mod_env_sustain = normalize_slider_value(val / 37, 100, 0);							 // 0-3700
			slider_level_gap = filter_freq_mod_env_sustain - ui->verticalSlider_MSOsynth_FilterFreqModAdsrS->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_MSOsynth_FilterFreqModAdsrS->setValue(filter_freq_mod_env_sustain);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_13)
		{
			// White White slider - Filter Freq Modulation Envelope Release control
			filter_freq_mod_env_release = normalize_slider_value(val / 37, 100, 0);							   // 0-3700
			slider_level_gap = filter_freq_mod_env_release - ui->verticalSlider_MSOsynth_FilterFreqModAdsrR->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_MSOsynth_FilterFreqModAdsrR->setValue(filter_freq_mod_env_release);
			}
		}
	}
}
