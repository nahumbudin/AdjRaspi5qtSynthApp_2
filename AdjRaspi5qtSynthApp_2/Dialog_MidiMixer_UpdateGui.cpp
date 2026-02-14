/**
 * @file		Dialog_MidiMixer_UpdateGui.cpp
 *	@author		Nahum Budin
 *	@date		22-Jan-2026
 *	@version	1.1
 *					1. New GUI layout 1620x840.
 *					2. Added pan modulationLFO selection and level control per channel.
 *					3. Added Send control per channel.
 *					4. Aded channel activity indication LED per channel.
 *
 *	@brief		Midi Mixer update GUI handling
 *
 *	@History:
 *
 *		Version 1.0	22-Aug-2024
 *
 */

#include <QDebug>

#include "Dialog_MidiMixer.h"
#include "ui_Dialog_MidiMixer_1620x840.h"

void Dialog_MidiMixer::update_gui()
{
	int ch;

	if (active_lfo_widget_showing)
	{
		active_lfo_frame_no_activity_counter--;
		if (active_lfo_frame_no_activity_counter <= 0)
		{
			active_lfo_widget_showing = false;
			ui->frame_LFO->hide();
		}
	}

	for (ch = 0; ch < 16; ch++)
	{
		if (levels_updated)
		{
			sliders_levels[ch]->blockSignals(true);
			sliders_levels[ch]->setValue(channels_levels[ch]);
			sliders_levels[ch]->blockSignals(false);

			spinboxes_levels[ch]->blockSignals(true);
			spinboxes_levels[ch]->setValue(channels_levels[ch]);
			spinboxes_levels[ch]->blockSignals(false);
		}

		if (pans_updated)
		{
			dials_pan[ch]->blockSignals(true);
			dials_pan[ch]->setValue(channels_pan[ch]);
			dials_pan[ch]->blockSignals(false);

			spinboxes_pan[ch]->blockSignals(true);
			spinboxes_pan[ch]->setValue(channels_pan[ch]);
			spinboxes_pan[ch]->blockSignals(false);
		}

		if (pan_mod_levels_updated)
		{
			dials_pan_lfo_mod_level[ch]->blockSignals(true);
			dials_pan_lfo_mod_level[ch]->setValue(channels_pan_mod_levels[ch]);
			dials_pan_lfo_mod_level[ch]->blockSignals(false);

			spinboxes_pan_lfo_mod_level[ch]->blockSignals(true);
			spinboxes_pan_lfo_mod_level[ch]->setValue(channels_pan_mod_levels[ch]);
			spinboxes_pan_lfo_mod_level[ch]->blockSignals(false);
		}

		if (pan_mod_lfos_updated)
		{
			comboboxes_pan_lfo_mod[ch]->blockSignals(true);
			comboboxes_pan_lfo_mod[ch]->setCurrentIndex(channels_pan_mod_lfo_selection[ch]);
			comboboxes_pan_lfo_mod[ch]->blockSignals(false);
		}

		if (send_levels_updated)
		{
			dials_send[ch]->blockSignals(true);
			dials_send[ch]->setValue(channels_send_levels[ch]);
			dials_send[ch]->blockSignals(false);

			spinboxes_send[ch]->blockSignals(true);
			spinboxes_send[ch]->setValue(channels_send_levels[ch]);
			spinboxes_send[ch]->blockSignals(false);
		}

		if (static_levels_updated)
		{
			checkboxes_static_levels[ch]->blockSignals(true);
			checkboxes_static_levels[ch]->setChecked(channels_static_level[ch]);
			checkboxes_static_levels[ch]->blockSignals(false);
		}
		
		if (textedits_programs_updated)
		{
			textedits_channel_programs[ch]->blockSignals(true);
			textedits_channel_programs[ch]->setText(channels_programs_names[ch]);
			textedits_channel_programs[ch]->blockSignals(false);
		}

		// Activity LEDs set and set timer to turn off after some time
		if (channels_active_counters[ch] > 0)
		{
			channels_active_counters[ch]--;
			//qDebug() << "Setting channel" << ch << "LED to TRUE";
			checkboxes_activity_leds[ch]->setChecked(true);
		}
		else
		{
			checkboxes_activity_leds[ch]->setChecked(false);
		}
	}

	levels_updated = false;
	pans_updated = false;
	pan_mod_levels_updated = false;
	pan_mod_lfos_updated = false;
	send_levels_updated = false;
	static_levels_updated = false;
	textedits_programs_updated = false;
}