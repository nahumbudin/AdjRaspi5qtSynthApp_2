/**
 * @file		Dialog_MidiMixer.cpp
 *	@author		Nahum Budin
 *	@date		22-Jan-2026
 *	@version	1.1
 *					1. New GUI layout 1620x840.
 *					2. Added pan modulationLFO selection and level control per channel.
 *					3. Added Send control per channel.
 *					4. Aded channel activity indication LED per channel.
 *
 *	@brief		Midi Mixer control dialog
 *
 *	@History:
 *
 *		Version 1.0	22-Aug-2024
 *
 */

#include <QTimer>

#include "utils.h"

#include "MainWindow.h"
#include "Dialog_MidiMixer.h"
#include "ui_Dialog_MidiMixer_1620x840.h"
#include "Defs.h"

void midi_mixer_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	// Marshal to UI thread - this is non-blocking and thread-safe
	Dialog_MidiMixer *instance = Dialog_MidiMixer::get_instance();
	if (instance != NULL)
	{
		QMetaObject::invokeMethod(instance, [instance, evnt, val]() { 
					instance->control_box_ui_update_callback(evnt, val); }, Qt::QueuedConnection);
	}
}

void midi_mixer_update_channels_levels_ui_update_callback_wrapper(int chan, int vol)
{
	Dialog_MidiMixer *instance = Dialog_MidiMixer::get_instance();
	if (instance != NULL)
	{
		QMetaObject::invokeMethod(instance, [instance, chan, vol]() { 
					instance->channels_levels_update_callback(chan, vol); }, Qt::QueuedConnection);
	}
}

void midi_mixer_update_channels_pans_ui_update_callback_wrapper(int chan, int pan)
{
	Dialog_MidiMixer *instance = Dialog_MidiMixer::get_instance();
	if (instance != NULL)
	{
		QMetaObject::invokeMethod(instance, [instance, chan, pan]() { 
					instance->channels_pans_update_callback(chan, pan); }, Qt::QueuedConnection);
	}
}

void midi_mixer_update_channels_static_levels_ui_update_callback_wrapper(int chan, bool state)
{
	Dialog_MidiMixer *instance = Dialog_MidiMixer::get_instance();
	if (instance != NULL)
	{
		QMetaObject::invokeMethod(instance, [instance, chan, state]() { 
					instance->channels_static_levels_update_callback(chan, state); }, Qt::QueuedConnection);
	}
}

void midi_mixer_channels_program_update_callback_wrapper(int chan, int prog)
{
	Dialog_MidiMixer *instance = Dialog_MidiMixer::get_instance();
	if (instance != NULL)
	{
		QMetaObject::invokeMethod(instance, [instance, chan, prog]() { 
					instance->channels_program_update_callback(chan, prog); }, Qt::QueuedConnection);
	}
}

void midi_mixer_channels_activity_update_callback_wrapper(int chan, bool state)
{
	Dialog_MidiMixer *instance = Dialog_MidiMixer::get_instance();
	if (instance != NULL)
	{
		QMetaObject::invokeMethod(instance, [instance, chan, state]() { 
					instance->channels_activity_update_callback(chan, state); }, Qt::QueuedConnection);
	}
}

void midi_mixer_update_channels_pan_lfo_mod_level_ui_update_callback_wrapper(int chan, int lvl)
{
	Dialog_MidiMixer *instance = Dialog_MidiMixer::get_instance();
	if (instance != NULL)
	{
		QMetaObject::invokeMethod(instance, [instance, chan, lvl]() { 
					instance->channels_pan_lfo_mod_level_update_callback(chan, lvl); }, Qt::QueuedConnection);
	}
}

void midi_mixer_update_channels_pan_lfo_ui_update_callback_wrapper(int chan, int lfo)
{
	Dialog_MidiMixer *instance = Dialog_MidiMixer::get_instance();
	if (instance != NULL)
	{
		QMetaObject::invokeMethod(instance, [instance, chan, lfo]() { 
					instance->channels_pan_lfo_update_callback(chan, lfo); }, Qt::QueuedConnection);
	}
}

Dialog_MidiMixer *Dialog_MidiMixer::dialog_midi_mixer_instance = NULL;

Dialog_MidiMixer::Dialog_MidiMixer(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::Dialog_MidiMixer_1620x840)
{
	ui->setupUi(this);
	dialog_midi_mixer_instance = this;

	ui->frame_LFO->hide();
	
	for (int ch = 0; ch < 16; ch++)
	{
		channels_static_level[ch] = false;
		channels_programs_names[ch] = "";
		channels_levels[ch] = 80;
		channels_pan[ch] = 50;
		channels_pan_mod_levels[ch] = 0;
		channels_pan_mod_lfo_selection[ch] = _LFO_NONE;
		channels_send_levels[ch] = 0;
	}

	string_lfos_list.append("---");
	string_lfos_list.append("1");
	string_lfos_list.append("2");
	string_lfos_list.append("3");
	string_lfos_list.append("4");
	string_lfos_list.append("5");
	string_lfos_list.append("6");

	ui->comboBox_MixerChPanModLfo_1->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_1->addItems(string_lfos_list);
	ui->comboBox_MixerChPanModLfo_1->setIdentifier(_MIXER_CHAN1_PAN_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MixerChPanModLfo_1->blockSignals(false);

	ui->comboBox_MixerChPanModLfo_2->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_2->addItems(string_lfos_list);
	ui->comboBox_MixerChPanModLfo_2->setIdentifier(_MIXER_CHAN2_PAN_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MixerChPanModLfo_2->blockSignals(false);

	ui->comboBox_MixerChPanModLfo_3->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_3->addItems(string_lfos_list);
	ui->comboBox_MixerChPanModLfo_3->setIdentifier(_MIXER_CHAN3_PAN_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MixerChPanModLfo_3->blockSignals(false);

	ui->comboBox_MixerChPanModLfo_4->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_4->addItems(string_lfos_list);
	ui->comboBox_MixerChPanModLfo_4->setIdentifier(_MIXER_CHAN4_PAN_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MixerChPanModLfo_4->blockSignals(false);

	ui->comboBox_MixerChPanModLfo_5->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_5->addItems(string_lfos_list);
	ui->comboBox_MixerChPanModLfo_5->setIdentifier(_MIXER_CHAN5_PAN_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MixerChPanModLfo_5->blockSignals(false);

	ui->comboBox_MixerChPanModLfo_6->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_6->addItems(string_lfos_list);
	ui->comboBox_MixerChPanModLfo_6->setIdentifier(_MIXER_CHAN6_PAN_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MixerChPanModLfo_6->blockSignals(false);

	ui->comboBox_MixerChPanModLfo_7->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_7->addItems(string_lfos_list);
	ui->comboBox_MixerChPanModLfo_7->setIdentifier(_MIXER_CHAN7_PAN_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MixerChPanModLfo_7->blockSignals(false);

	ui->comboBox_MixerChPanModLfo_8->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_8->addItems(string_lfos_list);
	ui->comboBox_MixerChPanModLfo_8->setIdentifier(_MIXER_CHAN8_PAN_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MixerChPanModLfo_8->blockSignals(false);

	ui->comboBox_MixerChPanModLfo_9->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_9->addItems(string_lfos_list);
	ui->comboBox_MixerChPanModLfo_9->setIdentifier(_MIXER_CHAN9_PAN_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MixerChPanModLfo_9->blockSignals(false);

	ui->comboBox_MixerChPanModLfo_10->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_10->addItems(string_lfos_list);
	ui->comboBox_MixerChPanModLfo_10->setIdentifier(_MIXER_CHAN10_PAN_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MixerChPanModLfo_10->blockSignals(false);

	ui->comboBox_MixerChPanModLfo_11->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_11->addItems(string_lfos_list);
	ui->comboBox_MixerChPanModLfo_11->setIdentifier(_MIXER_CHAN11_PAN_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MixerChPanModLfo_11->blockSignals(false);

	ui->comboBox_MixerChPanModLfo_12->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_12->addItems(string_lfos_list);
	ui->comboBox_MixerChPanModLfo_12->setIdentifier(_MIXER_CHAN12_PAN_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MixerChPanModLfo_12->blockSignals(false);

	ui->comboBox_MixerChPanModLfo_13->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_13->addItems(string_lfos_list);
	ui->comboBox_MixerChPanModLfo_13->setIdentifier(_MIXER_CHAN13_PAN_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MixerChPanModLfo_13->blockSignals(false);

	ui->comboBox_MixerChPanModLfo_14->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_14->addItems(string_lfos_list);
	ui->comboBox_MixerChPanModLfo_14->setIdentifier(_MIXER_CHAN14_PAN_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MixerChPanModLfo_14->blockSignals(false);

	ui->comboBox_MixerChPanModLfo_15->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_15->addItems(string_lfos_list);
	ui->comboBox_MixerChPanModLfo_15->setIdentifier(_MIXER_CHAN15_PAN_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MixerChPanModLfo_15->blockSignals(false);

	ui->comboBox_MixerChPanModLfo_16->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_16->addItems(string_lfos_list);
	ui->comboBox_MixerChPanModLfo_16->setIdentifier(_MIXER_CHAN16_PAN_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MixerChPanModLfo_16->blockSignals(false);

	dials_pan[0] = ui->dial_MixerChPan_1;
	dials_pan[1] = ui->dial_MixerChPan_2;
	dials_pan[2] = ui->dial_MixerChPan_3;
	dials_pan[3] = ui->dial_MixerChPan_4;
	dials_pan[4] = ui->dial_MixerChPan_5;
	dials_pan[5] = ui->dial_MixerChPan_6;
	dials_pan[6] = ui->dial_MixerChPan_7;
	dials_pan[7] = ui->dial_MixerChPan_8;
	dials_pan[8] = ui->dial_MixerChPan_9;
	dials_pan[9] = ui->dial_MixerChPan_10;
	dials_pan[10] = ui->dial_MixerChPan_11;
	dials_pan[11] = ui->dial_MixerChPan_12;
	dials_pan[12] = ui->dial_MixerChPan_13;
	dials_pan[13] = ui->dial_MixerChPan_14;
	dials_pan[14] = ui->dial_MixerChPan_15;
	dials_pan[15] = ui->dial_MixerChPan_16;

	dials_pan_lfo_mod_level[0] = ui->dial_MixerChPanModLevel_1;
	dials_pan_lfo_mod_level[1] = ui->dial_MixerChPanModLevel_2;
	dials_pan_lfo_mod_level[2] = ui->dial_MixerChPanModLevel_3;
	dials_pan_lfo_mod_level[3] = ui->dial_MixerChPanModLevel_4;
	dials_pan_lfo_mod_level[4] = ui->dial_MixerChPanModLevel_5;
	dials_pan_lfo_mod_level[5] = ui->dial_MixerChPanModLevel_6;
	dials_pan_lfo_mod_level[6] = ui->dial_MixerChPanModLevel_7;
	dials_pan_lfo_mod_level[7] = ui->dial_MixerChPanModLevel_8;
	dials_pan_lfo_mod_level[8] = ui->dial_MixerChPanModLevel_9;
	dials_pan_lfo_mod_level[9] = ui->dial_MixerChPanModLevel_10;
	dials_pan_lfo_mod_level[10] = ui->dial_MixerChPanModLevel_11;
	dials_pan_lfo_mod_level[11] = ui->dial_MixerChPanModLevel_12;
	dials_pan_lfo_mod_level[12] = ui->dial_MixerChPanModLevel_13;
	dials_pan_lfo_mod_level[13] = ui->dial_MixerChPanModLevel_14;
	dials_pan_lfo_mod_level[14] = ui->dial_MixerChPanModLevel_15;
	dials_pan_lfo_mod_level[15] = ui->dial_MixerChPanModLevel_16;

	dials_send[0] = ui->dial_MixerChSend_1;
	dials_send[1] = ui->dial_MixerChSend_2;
	dials_send[2] = ui->dial_MixerChSend_3;
	dials_send[3] = ui->dial_MixerChSend_4;
	dials_send[4] = ui->dial_MixerChSend_5;
	dials_send[5] = ui->dial_MixerChSend_6;
	dials_send[6] = ui->dial_MixerChSend_7;
	dials_send[7] = ui->dial_MixerChSend_8;
	dials_send[8] = ui->dial_MixerChSend_9;
	dials_send[9] = ui->dial_MixerChSend_10;
	dials_send[10] = ui->dial_MixerChSend_11;
	dials_send[11] = ui->dial_MixerChSend_12;
	dials_send[12] = ui->dial_MixerChSend_13;
	dials_send[13] = ui->dial_MixerChSend_14;
	dials_send[14] = ui->dial_MixerChSend_15;
	dials_send[15] = ui->dial_MixerChSend_16;

	sliders_levels[0] = ui->verticalSlider_MixerChLevel_1;
	sliders_levels[1] = ui->verticalSlider_MixerChLevel_2;
	sliders_levels[2] = ui->verticalSlider_MixerChLevel_3;
	sliders_levels[3] = ui->verticalSlider_MixerChLevel_4;
	sliders_levels[4] = ui->verticalSlider_MixerChLevel_5;
	sliders_levels[5] = ui->verticalSlider_MixerChLevel_6;
	sliders_levels[6] = ui->verticalSlider_MixerChLevel_7;
	sliders_levels[7] = ui->verticalSlider_MixerChLevel_8;
	sliders_levels[8] = ui->verticalSlider_MixerChLevel_9;
	sliders_levels[9] = ui->verticalSlider_MixerChLevel_10;
	sliders_levels[10] = ui->verticalSlider_MixerChLevel_11;
	sliders_levels[11] = ui->verticalSlider_MixerChLevel_12;
	sliders_levels[12] = ui->verticalSlider_MixerChLevel_13;
	sliders_levels[13] = ui->verticalSlider_MixerChLevel_14;
	sliders_levels[14] = ui->verticalSlider_MixerChLevel_15;
	sliders_levels[15] = ui->verticalSlider_MixerChLevel_16;

	comboboxes_pan_lfo_mod[0] = ui->comboBox_MixerChPanModLfo_1;
	comboboxes_pan_lfo_mod[1] = ui->comboBox_MixerChPanModLfo_2;
	comboboxes_pan_lfo_mod[2] = ui->comboBox_MixerChPanModLfo_3;
	comboboxes_pan_lfo_mod[3] = ui->comboBox_MixerChPanModLfo_4;
	comboboxes_pan_lfo_mod[4] = ui->comboBox_MixerChPanModLfo_5;
	comboboxes_pan_lfo_mod[5] = ui->comboBox_MixerChPanModLfo_6;
	comboboxes_pan_lfo_mod[6] = ui->comboBox_MixerChPanModLfo_7;
	comboboxes_pan_lfo_mod[7] = ui->comboBox_MixerChPanModLfo_8;
	comboboxes_pan_lfo_mod[8] = ui->comboBox_MixerChPanModLfo_9;
	comboboxes_pan_lfo_mod[9] = ui->comboBox_MixerChPanModLfo_10;
	comboboxes_pan_lfo_mod[10] = ui->comboBox_MixerChPanModLfo_11;
	comboboxes_pan_lfo_mod[11] = ui->comboBox_MixerChPanModLfo_12;
	comboboxes_pan_lfo_mod[12] = ui->comboBox_MixerChPanModLfo_13;
	comboboxes_pan_lfo_mod[13] = ui->comboBox_MixerChPanModLfo_14;
	comboboxes_pan_lfo_mod[14] = ui->comboBox_MixerChPanModLfo_15;
	comboboxes_pan_lfo_mod[15] = ui->comboBox_MixerChPanModLfo_16;

	checkboxes_static_levels[0] = ui->checkBox_MixerChanStaticLevel_1;
	checkboxes_static_levels[1] = ui->checkBox_MixerChanStaticLevel_2;
	checkboxes_static_levels[2] = ui->checkBox_MixerChanStaticLevel_3;
	checkboxes_static_levels[3] = ui->checkBox_MixerChanStaticLevel_4;
	checkboxes_static_levels[4] = ui->checkBox_MixerChanStaticLevel_5;
	checkboxes_static_levels[5] = ui->checkBox_MixerChanStaticLevel_6;
	checkboxes_static_levels[6] = ui->checkBox_MixerChanStaticLevel_7;
	checkboxes_static_levels[7] = ui->checkBox_MixerChanStaticLevel_8;
	checkboxes_static_levels[8] = ui->checkBox_MixerChanStaticLevel_9;
	checkboxes_static_levels[9] = ui->checkBox_MixerChanStaticLevel_10;
	checkboxes_static_levels[10] = ui->checkBox_MixerChanStaticLevel_11;
	checkboxes_static_levels[11] = ui->checkBox_MixerChanStaticLevel_12;
	checkboxes_static_levels[12] = ui->checkBox_MixerChanStaticLevel_13;
	checkboxes_static_levels[13] = ui->checkBox_MixerChanStaticLevel_14;
	checkboxes_static_levels[14] = ui->checkBox_MixerChanStaticLevel_15;
	checkboxes_static_levels[15] = ui->checkBox_MixerChanStaticLevel_16;

	spinboxes_levels[0] = ui->spinBox_MixerChLevel_1;
	spinboxes_levels[1] = ui->spinBox_MixerChLevel_2;
	spinboxes_levels[2] = ui->spinBox_MixerChLevel_3;
	spinboxes_levels[3] = ui->spinBox_MixerChLevel_4;
	spinboxes_levels[4] = ui->spinBox_MixerChLevel_5;
	spinboxes_levels[5] = ui->spinBox_MixerChLevel_6;
	spinboxes_levels[6] = ui->spinBox_MixerChLevel_7;
	spinboxes_levels[7] = ui->spinBox_MixerChLevel_8;
	spinboxes_levels[8] = ui->spinBox_MixerChLevel_9;
	spinboxes_levels[9] = ui->spinBox_MixerChLevel_10;
	spinboxes_levels[10] = ui->spinBox_MixerChLevel_11;
	spinboxes_levels[11] = ui->spinBox_MixerChLevel_12;
	spinboxes_levels[12] = ui->spinBox_MixerChLevel_13;
	spinboxes_levels[13] = ui->spinBox_MixerChLevel_14;
	spinboxes_levels[14] = ui->spinBox_MixerChLevel_15;
	spinboxes_levels[15] = ui->spinBox_MixerChLevel_16;

	spinboxes_pan[0] = ui->spinBox_MixerChPan_1;
	spinboxes_pan[1] = ui->spinBox_MixerChPan_2;
	spinboxes_pan[2] = ui->spinBox_MixerChPan_3;
	spinboxes_pan[3] = ui->spinBox_MixerChPan_4;
	spinboxes_pan[4] = ui->spinBox_MixerChPan_5;
	spinboxes_pan[5] = ui->spinBox_MixerChPan_6;
	spinboxes_pan[6] = ui->spinBox_MixerChPan_7;
	spinboxes_pan[7] = ui->spinBox_MixerChPan_8;
	spinboxes_pan[8] = ui->spinBox_MixerChPan_9;
	spinboxes_pan[9] = ui->spinBox_MixerChPan_10;
	spinboxes_pan[10] = ui->spinBox_MixerChPan_11;
	spinboxes_pan[11] = ui->spinBox_MixerChPan_12;
	spinboxes_pan[12] = ui->spinBox_MixerChPan_13;
	spinboxes_pan[13] = ui->spinBox_MixerChPan_14;
	spinboxes_pan[14] = ui->spinBox_MixerChPan_15;
	spinboxes_pan[15] = ui->spinBox_MixerChPan_16;

	spinboxes_pan_lfo_mod_level[0] = ui->spinBox_MixerChPanModLevel_1;
	spinboxes_pan_lfo_mod_level[1] = ui->spinBox_MixerChPanModLevel_2;
	spinboxes_pan_lfo_mod_level[2] = ui->spinBox_MixerChPanModLevel_3;
	spinboxes_pan_lfo_mod_level[3] = ui->spinBox_MixerChPanModLevel_4;
	spinboxes_pan_lfo_mod_level[4] = ui->spinBox_MixerChPanModLevel_5;
	spinboxes_pan_lfo_mod_level[5] = ui->spinBox_MixerChPanModLevel_6;
	spinboxes_pan_lfo_mod_level[6] = ui->spinBox_MixerChPanModLevel_7;
	spinboxes_pan_lfo_mod_level[7] = ui->spinBox_MixerChPanModLevel_8;
	spinboxes_pan_lfo_mod_level[8] = ui->spinBox_MixerChPanModLevel_9;
	spinboxes_pan_lfo_mod_level[9] = ui->spinBox_MixerChPanModLevel_10;
	spinboxes_pan_lfo_mod_level[10] = ui->spinBox_MixerChPanModLevel_11;
	spinboxes_pan_lfo_mod_level[11] = ui->spinBox_MixerChPanModLevel_12;
	spinboxes_pan_lfo_mod_level[12] = ui->spinBox_MixerChPanModLevel_13;
	spinboxes_pan_lfo_mod_level[13] = ui->spinBox_MixerChPanModLevel_14;
	spinboxes_pan_lfo_mod_level[14] = ui->spinBox_MixerChPanModLevel_15;
	spinboxes_pan_lfo_mod_level[15] = ui->spinBox_MixerChPanModLevel_16;

	spinboxes_send[0] = ui->spinBox_MixerChSend_1;
	spinboxes_send[1] = ui->spinBox_MixerChSend_2;
	spinboxes_send[2] = ui->spinBox_MixerChSend_3;
	spinboxes_send[3] = ui->spinBox_MixerChSend_4;
	spinboxes_send[4] = ui->spinBox_MixerChSend_5;
	spinboxes_send[5] = ui->spinBox_MixerChSend_6;
	spinboxes_send[6] = ui->spinBox_MixerChSend_7;
	spinboxes_send[7] = ui->spinBox_MixerChSend_8;
	spinboxes_send[8] = ui->spinBox_MixerChSend_9;
	spinboxes_send[9] = ui->spinBox_MixerChSend_10;
	spinboxes_send[10] = ui->spinBox_MixerChSend_11;
	spinboxes_send[11] = ui->spinBox_MixerChSend_12;
	spinboxes_send[12] = ui->spinBox_MixerChSend_13;
	spinboxes_send[13] = ui->spinBox_MixerChSend_14;
	spinboxes_send[14] = ui->spinBox_MixerChSend_15;
	spinboxes_send[15] = ui->spinBox_MixerChSend_16;

	textedits_channel_programs[0] = ui->textEdit_MixerChanText_1;
	textedits_channel_programs[1] = ui->textEdit_MixerChanText_2;
	textedits_channel_programs[2] = ui->textEdit_MixerChanText_3;
	textedits_channel_programs[3] = ui->textEdit_MixerChanText_4;
	textedits_channel_programs[4] = ui->textEdit_MixerChanText_5;
	textedits_channel_programs[5] = ui->textEdit_MixerChanText_6;
	textedits_channel_programs[6] = ui->textEdit_MixerChanText_7;
	textedits_channel_programs[7] = ui->textEdit_MixerChanText_8;
	textedits_channel_programs[8] = ui->textEdit_MixerChanText_9;
	textedits_channel_programs[9] = ui->textEdit_MixerChanText_10;
	textedits_channel_programs[10] = ui->textEdit_MixerChanText_11;
	textedits_channel_programs[11] = ui->textEdit_MixerChanText_12;
	textedits_channel_programs[12] = ui->textEdit_MixerChanText_13;
	textedits_channel_programs[13] = ui->textEdit_MixerChanText_14;
	textedits_channel_programs[14] = ui->textEdit_MixerChanText_15;
	textedits_channel_programs[15] = ui->textEdit_MixerChanText_16;

	checkboxes_activity_leds[0] = ui->checkBox_MixerChanActivity_1;
	checkboxes_activity_leds[1] = ui->checkBox_MixerChanActivity_2;
	checkboxes_activity_leds[2] = ui->checkBox_MixerChanActivity_3;
	checkboxes_activity_leds[3] = ui->checkBox_MixerChanActivity_4;
	checkboxes_activity_leds[4] = ui->checkBox_MixerChanActivity_5;
	checkboxes_activity_leds[5] = ui->checkBox_MixerChanActivity_6;
	checkboxes_activity_leds[6] = ui->checkBox_MixerChanActivity_7;
	checkboxes_activity_leds[7] = ui->checkBox_MixerChanActivity_8;
	checkboxes_activity_leds[8] = ui->checkBox_MixerChanActivity_9;
	checkboxes_activity_leds[9] = ui->checkBox_MixerChanActivity_10;
	checkboxes_activity_leds[10] = ui->checkBox_MixerChanActivity_11;
	checkboxes_activity_leds[11] = ui->checkBox_MixerChanActivity_12;
	checkboxes_activity_leds[12] = ui->checkBox_MixerChanActivity_13;
	checkboxes_activity_leds[13] = ui->checkBox_MixerChanActivity_14;
	checkboxes_activity_leds[14] = ui->checkBox_MixerChanActivity_15;
	checkboxes_activity_leds[15] = ui->checkBox_MixerChanActivity_16;

	for (int ch = 0; ch < 16; ch++)
	{
		checkboxes_activity_leds[ch]->setReadOnly(true);
		channels_active_counters[ch] = 0;
	}

	close_event_callback_ptr = NULL;

	set_midi_mixer_signals_connections();
	update_gui();

	this->setFocus(Qt::ActiveWindowFocusReason);
	
	active_channels_tab = _MIDI_MIXER_CHANNELS_1_8;
	
	mod_synth_register_callback_control_box_event_update_ui(
		&midi_mixer_control_box_event_update_ui_callback_wrapper);
	
	mod_synth_register_midi_mixer_channel_volume_update_callback(
			&midi_mixer_update_channels_levels_ui_update_callback_wrapper);
	
	mod_synth_register_midi_mixer_channel_pan_update_callback(
			&midi_mixer_update_channels_pans_ui_update_callback_wrapper);
	
	mod_synth_register_midi_mixer_channel_static_volume_update_callback(
			&midi_mixer_update_channels_static_levels_ui_update_callback_wrapper);
	
	/* Midi mapper channel volume commands trapper */
	mod_synth_register_midi_channel_volume_control_command_trapped_callback
		(&midi_mixer_update_channels_levels_ui_update_callback_wrapper);
	
	/* Midi mapper channel change program commands trapper */
	mod_synth_register_midi_channel_change_program_command_trapped_callback
		(&midi_mixer_channels_program_update_callback_wrapper);
	
	/* Midi channel active indication */
	mod_synth_register_midi_channel_active_indication_update_callback(
		&midi_mixer_channels_activity_update_callback_wrapper);

	set_midi_mixer_signals_connections();

	MainWindow::get_instance()->register_active_dialog(this);
	
	// This initializes the Analog Synthesizer LFO UI widgets pointer arrays, including the LFOs
	Dialog_AnalogSynth_1900x1000::get_instance();

	// start a periodic timer after this timeout - 
	start_update_timer(250);
}

Dialog_MidiMixer::~Dialog_MidiMixer()
{
	// Set breakpoint here when debugging
	int breakpoint_here = 0; // <-- BREAKPOINT
	(void)breakpoint_here;
}

Dialog_MidiMixer *Dialog_MidiMixer::get_instance(QWidget *parent)
{
	if (dialog_midi_mixer_instance == NULL)
	{
		dialog_midi_mixer_instance = new Dialog_MidiMixer(parent);
	}
	
	return dialog_midi_mixer_instance;
}

void Dialog_MidiMixer::closeEvent(QCloseEvent *event)
{
	if (close_event_callback_ptr != NULL)
	{
		close_event_callback_ptr();
	}
	
	hide();
}

void Dialog_MidiMixer::init_active_lfo_widget()
{
}

void Dialog_MidiMixer::update_active_lfo_frame()
{
	char text[64];

	// Update LFO frame controls according to active LFO values
	switch (active_lfo)
	{
	case _LFO_1:
		active_lfo_rate = mod_synth_get_active_lfo_mod_1_rate();
		active_lfo_symmetry = mod_synth_get_active_lfo_mod_1_symmetry();
		active_lfo_waveform = mod_synth_get_active_lfo_mod_1_waveform();
		break;

	case _LFO_2:
		active_lfo_rate = mod_synth_get_active_lfo_mod_2_rate();
		active_lfo_symmetry = mod_synth_get_active_lfo_mod_2_symmetry();
		active_lfo_waveform = mod_synth_get_active_lfo_mod_2_waveform();
		break;

	case _LFO_3:
		active_lfo_rate = mod_synth_get_active_lfo_mod_3_rate();
		active_lfo_symmetry = mod_synth_get_active_lfo_mod_3_symmetry();
		active_lfo_waveform = mod_synth_get_active_lfo_mod_3_waveform();
		break;

	case _LFO_4:
		active_lfo_rate = mod_synth_get_active_lfo_mod_4_rate();
		active_lfo_symmetry = mod_synth_get_active_lfo_mod_4_symmetry();
		active_lfo_waveform = mod_synth_get_active_lfo_mod_4_waveform();
		break;

	case _LFO_5:
		active_lfo_rate = mod_synth_get_active_lfo_mod_5_rate();
		active_lfo_symmetry = mod_synth_get_active_lfo_mod_5_symmetry();
		active_lfo_waveform = mod_synth_get_active_lfo_mod_5_waveform();
		break;

	case _LFO_6:
		active_lfo_rate = mod_synth_get_active_lfo_mod_6_rate();
		active_lfo_symmetry = mod_synth_get_active_lfo_mod_6_symmetry();
		active_lfo_waveform = mod_synth_get_active_lfo_mod_6_waveform();
		break;

	default:
		return;
	}

	ui->comboBox_LFOwaveform->blockSignals(true);
	ui->comboBox_LFOwaveform->setCurrentIndex(active_lfo_waveform);
	ui->comboBox_LFOwaveform->blockSignals(false);

	ui->dial_LFOsymmetry->blockSignals(true);
	ui->dial_LFOsymmetry->setValue(active_lfo_symmetry);
	ui->dial_LFOsymmetry->blockSignals(false);
	sprintf(text, "%i%c", active_lfo_symmetry, '%');
	ui->lineEdit_LFOsymmetry->setText(QString(text));

	ui->dial_LFOrate->blockSignals(true);
	ui->dial_LFOrate->setValue(active_lfo_rate);
	ui->dial_LFOrate->blockSignals(false);

	sprintf(text, "%.2fHz",
			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
										  mod_synth_get_lfo_max_frequency(), 10.0,
										  active_lfo_rate));

	ui->lineEdit_LFOrate->setText(QString(text));
}



void Dialog_MidiMixer::channels_levels_update_callback(int chan, int vol)
{
	levels_updated = true;

	if (chan == 0)
	{
		on_level_slider_changed_ch_1(vol);
	}
	else if (chan == 1)
	{
		on_level_slider_changed_ch_2(vol);
	}
	else if (chan == 2)
	{
		on_level_slider_changed_ch_3(vol);
	}
	else if (chan == 3)
	{
		on_level_slider_changed_ch_4(vol);
	}
	else if (chan == 4)
	{
		on_level_slider_changed_ch_5(vol);
	}
	else if (chan == 5)
	{
		on_level_slider_changed_ch_6(vol);
	}
	else if (chan == 6)
	{
		on_level_slider_changed_ch_7(vol);
	}
	else if (chan == 7)
	{
		on_level_slider_changed_ch_8(vol);
	}
	else if (chan == 8)
	{
		on_level_slider_changed_ch_9(vol);
	}
	else if (chan == 9)
	{
		on_level_slider_changed_ch_10(vol);
	}
	else if (chan == 10)
	{
		on_level_slider_changed_ch_11(vol);
	}
	else if (chan == 11)
	{
		on_level_slider_changed_ch_12(vol);
	}
	else if (chan == 12)
	{
		on_level_slider_changed_ch_13(vol);
	}
	else if (chan == 13)
	{
		on_level_slider_changed_ch_14(vol);
	}
	else if (chan == 14)
	{
		on_level_slider_changed_ch_15(vol);
	}
	else if (chan == 15)
	{
		on_level_slider_changed_ch_16(vol);
	}
	else
	{
		// Invalid channel
		levels_updated = false;
	}
}
void Dialog_MidiMixer::channels_pans_update_callback(int chan, int pan)
{
	pans_updated = true;

	if (chan == 0)
	{
		on_pan_dial_changed_ch_1(pan);
	}
	else if (chan == 1)
	{
		on_pan_dial_changed_ch_2(pan);
	}
	else if (chan == 2)
	{
		on_pan_dial_changed_ch_3(pan);
	}
	else if (chan == 3)
	{
		on_pan_dial_changed_ch_4(pan);
	}
	else if (chan == 4)
	{
		on_pan_dial_changed_ch_5(pan);
	}
	else if (chan == 5)
	{
		on_pan_dial_changed_ch_6(pan);
	}
	else if (chan == 6)
	{
		on_pan_dial_changed_ch_7(pan);
	}
	else if (chan == 7)
	{
		on_pan_dial_changed_ch_8(pan);
	}
	else if (chan == 8)
	{
		on_pan_dial_changed_ch_9(pan);
	}
	else if (chan == 9)
	{
		on_pan_dial_changed_ch_10(pan);
	}
	else if (chan == 10)
	{
		on_pan_dial_changed_ch_11(pan);
	}
	else if (chan == 11)
	{
		on_pan_dial_changed_ch_12(pan);
	}
	else if (chan == 12)
	{
		on_pan_dial_changed_ch_13(pan);
	}
	else if (chan == 13)
	{
		on_pan_dial_changed_ch_14(pan);
	}
	else if (chan == 14)
	{
		on_pan_dial_changed_ch_15(pan);
	}
	else if (chan == 15)
	{
		on_pan_dial_changed_ch_16(pan);
	}
	else
	{
		// Invalid channel
		pans_updated = false;
	}
}

void Dialog_MidiMixer::channels_static_levels_update_callback(int chan, bool state)
{
	static_levels_updated = true;
	
	if (chan == 0)
	{
		on_static_level_checkbox_changed_ch_1(state);
	}
	else if (chan == 1)
	{
		on_static_level_checkbox_changed_ch_2(state);
	}
	else if (chan == 2)
	{
		on_static_level_checkbox_changed_ch_3(state);
	}
	else if (chan == 3)
	{
		on_static_level_checkbox_changed_ch_4(state);
	}
	else if (chan == 4)
	{
		on_static_level_checkbox_changed_ch_5(state);
	}
	else if (chan == 5)
	{
		on_static_level_checkbox_changed_ch_6(state);
	}
	else if (chan == 6)
	{
		on_static_level_checkbox_changed_ch_7(state);
	}
	else if (chan == 7)
	{
		on_static_level_checkbox_changed_ch_8(state);
	}
	else if (chan == 8)
	{
		on_static_level_checkbox_changed_ch_9(state);
	}
	else if (chan == 9)
	{
		on_static_level_checkbox_changed_ch_10(state);
	}
	else if (chan == 10)
	{
		on_static_level_checkbox_changed_ch_11(state);
	}
	else if (chan == 11)
	{
		on_static_level_checkbox_changed_ch_12(state);
	}
	else if (chan == 12)
	{
		on_static_level_checkbox_changed_ch_13(state);
	}
	else if (chan == 13)
	{
		on_static_level_checkbox_changed_ch_14(state);
	}
	else if (chan == 14)
	{
		on_static_level_checkbox_changed_ch_15(state);
	}
	else if (chan == 15)
	{
		on_static_level_checkbox_changed_ch_16(state);
	}
	else
	{
		// Invalid channel
		static_levels_updated = false;
	}
}

void Dialog_MidiMixer::channels_pan_lfo_mod_level_update_callback(int chan, int lvl)
{
	pan_mod_levels_updated = true;

	if (chan == 0)
	{
		on_pan_lfo_mod_level_dial_changed_ch_1(lvl);
	}
	else if (chan == 1)
	{
		on_pan_lfo_mod_level_dial_changed_ch_2(lvl);
	}
	else if (chan == 2)
	{
		on_pan_lfo_mod_level_dial_changed_ch_3(lvl);
	}
	else if (chan == 3)
	{
		on_pan_lfo_mod_level_dial_changed_ch_4(lvl);
	}
	else if (chan == 4)
	{
		on_pan_lfo_mod_level_dial_changed_ch_5(lvl);
	}
	else if (chan == 5)
	{
		on_pan_lfo_mod_level_dial_changed_ch_6(lvl);
	}
	else if (chan == 6)
	{
		on_pan_lfo_mod_level_dial_changed_ch_7(lvl);
	}
	else if (chan == 7)
	{
		on_pan_lfo_mod_level_dial_changed_ch_8(lvl);
	}
	else if (chan == 8)
	{
		on_pan_lfo_mod_level_dial_changed_ch_9(lvl);
	}
	else if (chan == 9)
	{
		on_pan_lfo_mod_level_dial_changed_ch_10(lvl);
	}
	else if (chan == 10)
	{
		on_pan_lfo_mod_level_dial_changed_ch_11(lvl);
	}
	else if (chan == 11)
	{
		on_pan_lfo_mod_level_dial_changed_ch_12(lvl);
	}
	else if (chan == 12)
	{
		on_pan_lfo_mod_level_dial_changed_ch_13(lvl);
	}
	else if (chan == 13)
	{
		on_pan_lfo_mod_level_dial_changed_ch_14(lvl);
	}
	else if (chan == 14)
	{
		on_pan_lfo_mod_level_dial_changed_ch_15(lvl);
	}
	else if (chan == 15)
	{
		on_pan_lfo_mod_level_dial_changed_ch_16(lvl);
	}
	else
	{
		// Invalid channel
		pan_mod_levels_updated = false;
	}
}

void Dialog_MidiMixer::channels_pan_lfo_update_callback(int chan, int lfo)
{
	
}

void Dialog_MidiMixer::channels_activity_update_callback(int chan, bool state)
{	
	if ((chan >= 0) && (chan < 16))
	{
		if (state)
		{
			channels_active_counters[chan] = _CHANNEL_ACTIVE_ON_TIME_COUNTER;
		}
	}
}

void Dialog_MidiMixer::start_update_timer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update_gui()));
	timer->start(interval);
}

void Dialog_MidiMixer::timerEvent(QTimerEvent *event)
{
	killTimer(event->timerId());
	start_update_timer(250);
}



void Dialog_MidiMixer::channels_program_update_callback(int chan, int program)
{
	/* Currently supporting MIDI GM programs */
	if ((program >= 0) && (program <= 128) && (chan >= 0) && (chan < 16))
	{
		channels_programs_names[chan] = QString::fromStdString(midi_instruments_names[program]);
		textedits_programs_updated = true;
	}
}

void Dialog_MidiMixer::on_level_changed(int chan, int vol)
{
	//printf("Channel %i Volume Set to: %i\n", chan, vol);
	
	channels_levels[chan] = vol;
	mod_synth_midi_mixer_set_channel_volume(chan, vol);
}

void Dialog_MidiMixer::on_pan_changed(int chan, int pan)
{
	//printf("Channel %i Pan Set to: %i\n", chan, pan);
	
	channels_pan[chan] = pan;
	mod_synth_midi_mixer_set_channel_pan(chan, pan);
}

void Dialog_MidiMixer::on_pan_mod_level_changed(int chan, int lvl)
{
	channels_pan_mod_levels[chan] = lvl;
	mod_synth_midi_mixer_set_channel_pan_mod_level(chan, lvl);
}

void Dialog_MidiMixer::on_pan_mod_lfo_changed(int chan, int lfo)
{
	channels_pan_mod_lfo_selection[chan] = lfo;
	mod_synth_midi_mixer_set_channel_pan_mod_lfo(chan, lfo);
}

void Dialog_MidiMixer::on_send_level_changed(int chan, int snd)
{
	channels_send_levels[chan] = snd;
	mod_synth_midi_mixer_set_channel_send_level(chan, snd);
}

void Dialog_MidiMixer::on_static_levels_changed(int chan, bool state)
{
	channels_static_level[chan] = state;
	mod_synth_midi_mixer_set_channel_static_volume(chan, state);
}



void Dialog_MidiMixer::on_dialog_close()
{
	hide();
}






