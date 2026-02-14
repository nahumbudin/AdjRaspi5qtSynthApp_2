/**
 * @file		ReverbrationGui.cpp
 *	@author		Nahum Budin
 *	@date		11-Feb-2026
 *	@version	2.0
 *
 *	@brief		Analog Synthesizer instrument Reverb GUI handling
 *
 *	History:
 *		Version 1.1		25-Oct-2024
 *		Based on the AdjModSynth project ver 1.1 16-Jan-2021
 *
 */

#include "Defs.h"
#include "Dialog_AnalogSynth_1900x1000.h"
#include "ui_Dialog_AnalogSynth_1900x1000.h"

int Dialog_AnalogSynth_1900x1000::init_reverb_gui()
{
	init_reverb_combboxes_and_labels();
	set_reverb_signals_connections();
	reverb_update();

	return 0;
}

void Dialog_AnalogSynth_1900x1000::set_reverb_signals_connections()
{
	connect(ui->checkBox_Reverbration_Active,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_reverb_enable_checkbox_changed(bool)));

	connect(ui->dial_ReverbRoomSize,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_room_size_dial_changed(int)));

	connect(ui->dial_ReverbDamp,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_damp_dial_changed(int)));

	connect(ui->dial_ReverbWet,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_wet_dial_changed(int)));

	connect(ui->dial_ReverbDry,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_dry_dial_changed(int)));

	connect(ui->dial_ReverbWidth,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_width_dial_changed(int)));

	connect(ui->dial_ReverbMode,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_mode_dial_changed(int)));

	connect(ui->spinBox_ReverbRoomSize,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_room_size_spinbox_changed(int)));

	connect(ui->spinBox_ReverbDamp,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_damp_spinbox_changed(int)));

	connect(ui->spinBox_ReverbWet,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_wet_spinbox_changed(int)));

	connect(ui->spinBox_ReverbDry,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_dry_spinbox_changed(int)));

	connect(ui->spinBox_ReverbWidth,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_width_spinbox_changed(int)));

	connect(ui->spinBox_ReverbMode,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_mode_spinbox_changed(int)));

	// Freeverb 3 Mod
	connect(ui->checkBox_Reverbration3_Active,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_reverb_3m_enable_checkbox_hanged(bool)));

	connect(ui->comboBox_ReverbType,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_reverb_type_combobox_changed(int)));
}

void Dialog_AnalogSynth_1900x1000::reverb_update()
{
	ui->checkBox_Reverbration_Active->blockSignals(true);
	ui->checkBox_Reverbration_Active->setChecked(mod_synth_get_active_reverb_enable_state());
	ui->checkBox_Reverbration_Active->blockSignals(false);

	ui->dial_ReverbRoomSize->blockSignals(true);
	ui->dial_ReverbRoomSize->setValue(mod_synth_get_active_reverb_room_size());
	ui->dial_ReverbRoomSize->blockSignals(false);

	ui->dial_ReverbDamp->blockSignals(true);
	ui->dial_ReverbDamp->setValue(mod_synth_get_active_reverb_damp());
	ui->dial_ReverbDamp->blockSignals(false);

	ui->dial_ReverbWet->blockSignals(true);
	ui->dial_ReverbWet->setValue(mod_synth_get_active_reverb_wet());
	ui->dial_ReverbWet->blockSignals(false);

	ui->dial_ReverbDry->blockSignals(true);
	ui->dial_ReverbDry->setValue(mod_synth_get_active_reverb_dry());
	ui->dial_ReverbDry->blockSignals(false);

	ui->dial_ReverbWidth->blockSignals(true);
	ui->dial_ReverbWidth->setValue(mod_synth_get_active_reverb_width());
	ui->dial_ReverbWidth->blockSignals(false);

	ui->dial_ReverbMode->blockSignals(true);
	ui->dial_ReverbMode->setValue(mod_synth_get_active_reverb_mode());
	ui->dial_ReverbMode->blockSignals(false);

	ui->checkBox_Reverbration3_Active->blockSignals(true);
	ui->checkBox_Reverbration3_Active->setChecked(mod_synth_get_active_reverb_3m_enable_state());
	ui->checkBox_Reverbration3_Active->blockSignals(false);
	
	if (mod_synth_get_active_reverb_enable_state())
	{
		ui->frame_FreeVerb->setEnabled(true);
	}
	else
	{
		ui->frame_FreeVerb->setEnabled(false);
	}

	ui->comboBox_ReverbType->blockSignals(true);
	ui->comboBox_ReverbType->setCurrentIndex(mod_synth_get_active_reverb_enable_state());
	ui->comboBox_ReverbType->blockSignals(false);
	if (mod_synth_get_active_reverb_3m_enable_state())
	{
		ui->frame_freeVerb3->setEnabled(true);
	}
	else
	{
		ui->frame_freeVerb3->setEnabled(false);
	}
}

void Dialog_AnalogSynth_1900x1000::init_reverb_combboxes_and_labels()
{
	static bool one_time_initialized = false;

	string_reverb_types_list.append("Default");
	string_reverb_types_list.append("Small Hall 1");
	string_reverb_types_list.append("Small Hall 2");
	string_reverb_types_list.append("Medium Hall 1");
	string_reverb_types_list.append("Medium Hall 2");
	string_reverb_types_list.append("Large Hall 1");
	string_reverb_types_list.append("Large Hall 2");
	string_reverb_types_list.append("Small Room 1");
	string_reverb_types_list.append("Small Room 2");
	string_reverb_types_list.append("Medium Room 1");
	string_reverb_types_list.append("Medium Room 2");
	string_reverb_types_list.append("Large Room 1");
	string_reverb_types_list.append("Large Room 2");
	string_reverb_types_list.append("Medium R 1");
	string_reverb_types_list.append("Medium R 2");
	string_reverb_types_list.append("Plate High");
	string_reverb_types_list.append("Plate Low");
	string_reverb_types_list.append("Long Reverb 1");
	string_reverb_types_list.append("Long Reverb 2");

	if (!one_time_initialized)
	{
		one_time_initialized = true;

		ui->comboBox_ReverbType->blockSignals(true);
		ui->comboBox_ReverbType->addItems(string_reverb_types_list);
		ui->comboBox_ReverbType->blockSignals(false);
	}
}

// Freeverb 3 modified
void Dialog_AnalogSynth_1900x1000::on_reverb_3m_enable_checkbox_hanged(bool val)
{
	ui->checkBox_Reverbration3_Active->blockSignals(true);

	if (val)
	{
		ui->checkBox_Reverbration3_Active->setChecked(true);
		ui->frame_freeVerb3->setEnabled(true);
	}
	else
	{
		ui->checkBox_Reverbration3_Active->setChecked(false);
		ui->frame_freeVerb3->setEnabled(false);
	}

	ui->checkBox_Reverbration3_Active->blockSignals(false);

	mod_synth_reverb_event_bool(_REVERB_EVENT, _REVERB3M_ENABLE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_reverb_type_combobox_changed(int val)
{
	ui->comboBox_ReverbType->blockSignals(true);
	ui->comboBox_ReverbType->setCurrentIndex(val);
	ui->comboBox_ReverbType->blockSignals(false);

	mod_synth_reverb_event_int(_REVERB_EVENT, _REVERB_PRESET, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

// Freverb
void Dialog_AnalogSynth_1900x1000::on_reverb_enable_checkbox_changed(bool val)
{
	ui->checkBox_Reverbration_Active->blockSignals(true);

	if (val)
	{
		ui->checkBox_Reverbration_Active->setChecked(true);
		ui->frame_FreeVerb->setEnabled(true);
	}
	else
	{
		ui->checkBox_Reverbration_Active->setChecked(false);
		ui->frame_FreeVerb->setEnabled(false);
	}

	ui->checkBox_Reverbration_Active->blockSignals(false);

	mod_synth_reverb_event_bool(_REVERB_EVENT, _REVERB_ENABLE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_reverb_room_size_dial_changed(int val)
{
	ui->dial_ReverbRoomSize->blockSignals(true);
	ui->dial_ReverbRoomSize->setValue(val);
	ui->dial_ReverbRoomSize->blockSignals(false);

	ui->spinBox_ReverbRoomSize->blockSignals(true);
	ui->spinBox_ReverbRoomSize->setValue(val);
	ui->spinBox_ReverbRoomSize->blockSignals(false);

	mod_synth_reverb_event_int(_REVERB_EVENT, _REVERB_ROOM_SIZE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_reverb_damp_dial_changed(int val)
{
	ui->dial_ReverbDamp->blockSignals(true);
	ui->dial_ReverbDamp->setValue(val);
	ui->dial_ReverbDamp->blockSignals(false);

	ui->spinBox_ReverbDamp->blockSignals(true);
	ui->spinBox_ReverbDamp->setValue(val);
	ui->spinBox_ReverbDamp->blockSignals(false);

	mod_synth_reverb_event_int(_REVERB_EVENT, _REVERB_DAMP, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_reverb_wet_dial_changed(int val)
{
	ui->dial_ReverbWet->blockSignals(true);
	ui->dial_ReverbWet->setValue(val);
	ui->dial_ReverbWet->blockSignals(false);

	ui->spinBox_ReverbWet->blockSignals(true);
	ui->spinBox_ReverbWet->setValue(val);
	ui->spinBox_ReverbWet->blockSignals(false);

	mod_synth_reverb_event_int(_REVERB_EVENT, _REVERB_WET, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_reverb_dry_dial_changed(int val)
{
	ui->dial_ReverbDry->blockSignals(true);
	ui->dial_ReverbDry->setValue(val);
	ui->dial_ReverbDry->blockSignals(false);

	ui->spinBox_ReverbDry->blockSignals(true);
	ui->spinBox_ReverbDry->setValue(val);
	ui->spinBox_ReverbDry->blockSignals(false);

	mod_synth_reverb_event_int(_REVERB_EVENT, _REVERB_DRY, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_reverb_width_dial_changed(int val)
{
	ui->dial_ReverbWidth->blockSignals(true);
	ui->dial_ReverbWidth->setValue(val);
	ui->dial_ReverbWidth->blockSignals(false);

	ui->spinBox_ReverbWidth->blockSignals(true);
	ui->spinBox_ReverbWidth->setValue(val);
	ui->spinBox_ReverbWidth->blockSignals(false);

	mod_synth_reverb_event_int(_REVERB_EVENT, _REVERB_WIDTH, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_reverb_mode_dial_changed(int val)
{
	ui->dial_ReverbMode->blockSignals(true);
	ui->dial_ReverbMode->setValue(val);
	ui->dial_ReverbMode->blockSignals(false);

	ui->spinBox_ReverbMode->blockSignals(true);
	ui->spinBox_ReverbMode->setValue(val);
	ui->spinBox_ReverbMode->blockSignals(false);

	mod_synth_reverb_event_int(_REVERB_EVENT, _REVERB_MODE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_reverb_room_size_spinbox_changed(int val)
{
	ui->dial_ReverbRoomSize->blockSignals(true);
	ui->dial_ReverbRoomSize->setValue(val);
	ui->dial_ReverbRoomSize->blockSignals(false);

	ui->spinBox_ReverbRoomSize->blockSignals(true);
	ui->spinBox_ReverbRoomSize->setValue(val);
	ui->spinBox_ReverbRoomSize->blockSignals(false);

	mod_synth_reverb_event_int(_REVERB_EVENT, _REVERB_ROOM_SIZE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_reverb_damp_spinbox_changed(int val)
{
	on_reverb_damp_dial_changed(val);
}

void Dialog_AnalogSynth_1900x1000::on_reverb_wet_spinbox_changed(int val)
{
	on_reverb_wet_dial_changed(val);	
}

void Dialog_AnalogSynth_1900x1000::on_reverb_dry_spinbox_changed(int val)
{
	on_reverb_dry_dial_changed(val);
}

void Dialog_AnalogSynth_1900x1000::on_reverb_width_spinbox_changed(int val)
{
	on_reverb_width_dial_changed(val);
}

void Dialog_AnalogSynth_1900x1000::on_reverb_mode_spinbox_changed(int val)
{
	on_reverb_mode_dial_changed(val);
}
