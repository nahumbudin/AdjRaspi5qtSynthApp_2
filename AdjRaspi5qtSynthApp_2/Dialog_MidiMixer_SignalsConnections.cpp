/**
 * @file		Dialog_MidiMixer_SignalsConnections.cpp
 *	@author		Nahum Budin
 *	@date		22-Jan-2026
 *	@version	1.1
 *					1. New GUI layout 1620x840.
 *					2. Added pan modulationLFO selection and level control per channel.
 *					3. Added Send control per channel.
 *					4. Aded channel activity indication LED per channel.
 *
 *	@brief		Midi Mixer control dialog signals connections setting
 *
 *	@History:
 *
 *		Version 1.0	22-Aug-2024
 *
 */

#include "Dialog_MidiMixer.h"

#include "ui_Dialog_MidiMixer_1620x840.h"

void Dialog_MidiMixer::set_midi_mixer_signals_connections()
{
	connect(ui->verticalSlider_MixerChLevel_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_slider_changed_ch_1(int)));

	connect(ui->verticalSlider_MixerChLevel_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_slider_changed_ch_2(int)));

	connect(ui->verticalSlider_MixerChLevel_3,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_slider_changed_ch_3(int)));

	connect(ui->verticalSlider_MixerChLevel_4,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_slider_changed_ch_4(int)));

	connect(ui->verticalSlider_MixerChLevel_5,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_slider_changed_ch_5(int)));

	connect(ui->verticalSlider_MixerChLevel_6,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_slider_changed_ch_6(int)));

	connect(ui->verticalSlider_MixerChLevel_7,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_slider_changed_ch_7(int)));

	connect(ui->verticalSlider_MixerChLevel_8,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_slider_changed_ch_8(int)));

	connect(ui->verticalSlider_MixerChLevel_9,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_slider_changed_ch_9(int)));

	connect(ui->verticalSlider_MixerChLevel_10,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_slider_changed_ch_10(int)));

	connect(ui->verticalSlider_MixerChLevel_11,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_slider_changed_ch_11(int)));

	connect(ui->verticalSlider_MixerChLevel_12,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_slider_changed_ch_12(int)));

	connect(ui->verticalSlider_MixerChLevel_13,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_slider_changed_ch_13(int)));

	connect(ui->verticalSlider_MixerChLevel_14,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_slider_changed_ch_14(int)));

	connect(ui->verticalSlider_MixerChLevel_15,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_slider_changed_ch_15(int)));

	connect(ui->verticalSlider_MixerChLevel_16,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_slider_changed_ch_16(int)));

	connect(ui->spinBox_MixerChLevel_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_spinbox_changed_ch_1(int)));

	connect(ui->spinBox_MixerChLevel_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_spinbox_changed_ch_2(int)));

	connect(ui->spinBox_MixerChLevel_3,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_spinbox_changed_ch_3(int)));

	connect(ui->spinBox_MixerChLevel_4,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_spinbox_changed_ch_4(int)));

	connect(ui->spinBox_MixerChLevel_5,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_spinbox_changed_ch_5(int)));

	connect(ui->spinBox_MixerChLevel_6,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_spinbox_changed_ch_6(int)));

	connect(ui->spinBox_MixerChLevel_7,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_spinbox_changed_ch_7(int)));

	connect(ui->spinBox_MixerChLevel_8,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_spinbox_changed_ch_8(int)));

	connect(ui->spinBox_MixerChLevel_9,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_spinbox_changed_ch_9(int)));

	connect(ui->spinBox_MixerChLevel_10,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_spinbox_changed_ch_10(int)));

	connect(ui->spinBox_MixerChLevel_11,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_spinbox_changed_ch_11(int)));

	connect(ui->spinBox_MixerChLevel_12,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_spinbox_changed_ch_12(int)));

	connect(ui->spinBox_MixerChLevel_13,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_spinbox_changed_ch_13(int)));

	connect(ui->spinBox_MixerChLevel_14,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_spinbox_changed_ch_14(int)));

	connect(ui->spinBox_MixerChLevel_15,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_spinbox_changed_ch_15(int)));

	connect(ui->spinBox_MixerChLevel_16,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_spinbox_changed_ch_16(int)));

	connect(ui->checkBox_MixerChanStaticLevel_1,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_static_level_checkbox_changed_ch_1(bool)));

	connect(ui->checkBox_MixerChanStaticLevel_2,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_static_level_checkbox_changed_ch_2(bool)));

	connect(ui->checkBox_MixerChanStaticLevel_3,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_static_level_checkbox_changed_ch_3(bool)));

	connect(ui->checkBox_MixerChanStaticLevel_4,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_static_level_checkbox_changed_ch_4(bool)));

	connect(ui->checkBox_MixerChanStaticLevel_5,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_static_level_checkbox_changed_ch_5(bool)));

	connect(ui->checkBox_MixerChanStaticLevel_6,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_static_level_checkbox_changed_ch_6(bool)));

	connect(ui->checkBox_MixerChanStaticLevel_7,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_static_level_checkbox_changed_ch_7(bool)));

	connect(ui->checkBox_MixerChanStaticLevel_8,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_static_level_checkbox_changed_ch_8(bool)));

	connect(ui->checkBox_MixerChanStaticLevel_9,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_static_level_checkbox_changed_ch_9(bool)));

	connect(ui->checkBox_MixerChanStaticLevel_10,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_static_level_checkbox_changed_ch_10(bool)));

	connect(ui->checkBox_MixerChanStaticLevel_11,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_static_level_checkbox_changed_ch_11(bool)));

	connect(ui->checkBox_MixerChanStaticLevel_12,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_static_level_checkbox_changed_ch_12(bool)));

	connect(ui->checkBox_MixerChanStaticLevel_13,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_static_level_checkbox_changed_ch_13(bool)));

	connect(ui->checkBox_MixerChanStaticLevel_14,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_static_level_checkbox_changed_ch_14(bool)));

	connect(ui->checkBox_MixerChanStaticLevel_15,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_static_level_checkbox_changed_ch_15(bool)));

	connect(ui->checkBox_MixerChanStaticLevel_16,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_static_level_checkbox_changed_ch_16(bool)));

	connect(ui->dial_MixerChPan_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_dial_changed_ch_1(int)));

	connect(ui->dial_MixerChPan_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_dial_changed_ch_2(int)));

	connect(ui->dial_MixerChPan_3,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_dial_changed_ch_3(int)));

	connect(ui->dial_MixerChPan_4,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_dial_changed_ch_4(int)));

	connect(ui->dial_MixerChPan_5,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_dial_changed_ch_5(int)));

	connect(ui->dial_MixerChPan_6,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_dial_changed_ch_6(int)));

	connect(ui->dial_MixerChPan_7,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_dial_changed_ch_7(int)));

	connect(ui->dial_MixerChPan_8,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_dial_changed_ch_8(int)));

	connect(ui->dial_MixerChPan_9,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_dial_changed_ch_9(int)));

	connect(ui->dial_MixerChPan_10,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_dial_changed_ch_10(int)));

	connect(ui->dial_MixerChPan_11,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_dial_changed_ch_11(int)));

	connect(ui->dial_MixerChPan_12,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_dial_changed_ch_12(int)));

	connect(ui->dial_MixerChPan_13,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_dial_changed_ch_13(int)));

	connect(ui->dial_MixerChPan_14,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_dial_changed_ch_14(int)));

	connect(ui->dial_MixerChPan_15,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_dial_changed_ch_15(int)));

	connect(ui->dial_MixerChPan_16,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_dial_changed_ch_16(int)));

	connect(ui->spinBox_MixerChPan_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_spinbox_changed_ch_1(int)));

	connect(ui->spinBox_MixerChPan_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_spinbox_changed_ch_2(int)));

	connect(ui->spinBox_MixerChPan_3,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_spinbox_changed_ch_3(int)));

	connect(ui->spinBox_MixerChPan_4,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_spinbox_changed_ch_4(int)));

	connect(ui->spinBox_MixerChPan_5,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_spinbox_changed_ch_5(int)));

	connect(ui->spinBox_MixerChPan_6,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_spinbox_changed_ch_6(int)));

	connect(ui->spinBox_MixerChPan_7,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_spinbox_changed_ch_7(int)));

	connect(ui->spinBox_MixerChPan_8,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_spinbox_changed_ch_8(int)));

	connect(ui->spinBox_MixerChPan_9,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_spinbox_changed_ch_9(int)));

	connect(ui->spinBox_MixerChPan_10,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_spinbox_changed_ch_10(int)));

	connect(ui->spinBox_MixerChPan_11,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_spinbox_changed_ch_11(int)));

	connect(ui->spinBox_MixerChPan_12,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_spinbox_changed_ch_12(int)));

	connect(ui->spinBox_MixerChPan_13,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_spinbox_changed_ch_13(int)));

	connect(ui->spinBox_MixerChPan_14,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_spinbox_changed_ch_14(int)));

	connect(ui->spinBox_MixerChPan_15,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_spinbox_changed_ch_15(int)));

	connect(ui->spinBox_MixerChPan_16,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_spinbox_changed_ch_16(int)));

	connect(ui->dial_MixerChPanModLevel_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_dial_changed_ch_1(int)));

	connect(ui->dial_MixerChPanModLevel_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_dial_changed_ch_2(int)));

	connect(ui->dial_MixerChPanModLevel_3,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_dial_changed_ch_3(int)));

	connect(ui->dial_MixerChPanModLevel_4,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_dial_changed_ch_4(int)));

	connect(ui->dial_MixerChPanModLevel_5,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_dial_changed_ch_5(int)));

	connect(ui->dial_MixerChPanModLevel_6,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_dial_changed_ch_6(int)));

	connect(ui->dial_MixerChPanModLevel_7,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_dial_changed_ch_7(int)));

	connect(ui->dial_MixerChPanModLevel_8,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_dial_changed_ch_8(int)));

	connect(ui->dial_MixerChPanModLevel_9,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_dial_changed_ch_9(int)));

	connect(ui->dial_MixerChPanModLevel_10,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_dial_changed_ch_10(int)));

	connect(ui->dial_MixerChPanModLevel_11,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_dial_changed_ch_11(int)));

	connect(ui->dial_MixerChPanModLevel_12,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_dial_changed_ch_12(int)));

	connect(ui->dial_MixerChPanModLevel_13,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_dial_changed_ch_13(int)));

	connect(ui->dial_MixerChPanModLevel_14,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_dial_changed_ch_14(int)));

	connect(ui->dial_MixerChPanModLevel_15,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_dial_changed_ch_15(int)));

	connect(ui->dial_MixerChPanModLevel_16,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_dial_changed_ch_16(int)));

	connect(ui->spinBox_MixerChPanModLevel_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_spinbox_changed_ch_1(int)));

	connect(ui->spinBox_MixerChPanModLevel_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_spinbox_changed_ch_2(int)));

	connect(ui->spinBox_MixerChPanModLevel_3,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_spinbox_changed_ch_3(int)));

	connect(ui->spinBox_MixerChPanModLevel_4,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_spinbox_changed_ch_4(int)));

	connect(ui->spinBox_MixerChPanModLevel_5,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_spinbox_changed_ch_5(int)));

	connect(ui->spinBox_MixerChPanModLevel_6,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_spinbox_changed_ch_6(int)));

	connect(ui->spinBox_MixerChPanModLevel_7,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_spinbox_changed_ch_7(int)));

	connect(ui->spinBox_MixerChPanModLevel_8,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_spinbox_changed_ch_8(int)));

	connect(ui->spinBox_MixerChPanModLevel_9,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_spinbox_changed_ch_9(int)));

	connect(ui->spinBox_MixerChPanModLevel_10,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_spinbox_changed_ch_10(int)));

	connect(ui->spinBox_MixerChPanModLevel_11,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_spinbox_changed_ch_11(int)));

	connect(ui->spinBox_MixerChPanModLevel_12,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_spinbox_changed_ch_12(int)));

	connect(ui->spinBox_MixerChPanModLevel_13,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_spinbox_changed_ch_13(int)));

	connect(ui->spinBox_MixerChPanModLevel_14,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_spinbox_changed_ch_14(int)));

	connect(ui->spinBox_MixerChPanModLevel_15,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_spinbox_changed_ch_15(int)));

	connect(ui->spinBox_MixerChPanModLevel_16,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_level_spinbox_changed_ch_16(int)));

	connect(ui->comboBox_MixerChPanModLfo_1,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_combo_changed_ch_1(int)));

	connect(ui->comboBox_MixerChPanModLfo_2,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_combo_changed_ch_2(int)));

	connect(ui->comboBox_MixerChPanModLfo_3,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_combo_changed_ch_3(int)));

	connect(ui->comboBox_MixerChPanModLfo_4,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_combo_changed_ch_4(int)));

	connect(ui->comboBox_MixerChPanModLfo_5,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_combo_changed_ch_5(int)));

	connect(ui->comboBox_MixerChPanModLfo_6,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_combo_changed_ch_6(int)));

	connect(ui->comboBox_MixerChPanModLfo_7,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_combo_changed_ch_7(int)));

	connect(ui->comboBox_MixerChPanModLfo_8,
			SIGNAL(valucurrentIndexChangedeChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_combo_changed_ch_8(int)));

	connect(ui->comboBox_MixerChPanModLfo_9,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_combo_changed_ch_9(int)));

	connect(ui->comboBox_MixerChPanModLfo_10,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_combo_changed_ch_10(int)));

	connect(ui->comboBox_MixerChPanModLfo_11,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_combo_changed_ch_11(int)));

	connect(ui->comboBox_MixerChPanModLfo_12,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_combo_changed_ch_12(int)));

	connect(ui->comboBox_MixerChPanModLfo_13,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_combo_changed_ch_13(int)));

	connect(ui->comboBox_MixerChPanModLfo_14,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_combo_changed_ch_14(int)));

	connect(ui->comboBox_MixerChPanModLfo_15,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_combo_changed_ch_15(int)));

	connect(ui->comboBox_MixerChPanModLfo_16,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_pan_lfo_mod_combo_changed_ch_16(int)));

	connect(ui->dial_MixerChSend_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_dial_changed_ch_1(int)));

	connect(ui->dial_MixerChSend_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_dial_changed_ch_2(int)));

	connect(ui->dial_MixerChSend_3,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_dial_changed_ch_3(int)));

	connect(ui->dial_MixerChSend_4,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_dial_changed_ch_4(int)));

	connect(ui->dial_MixerChSend_5,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_dial_changed_ch_5(int)));

	connect(ui->dial_MixerChSend_6,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_dial_changed_ch_6(int)));

	connect(ui->dial_MixerChSend_7,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_dial_changed_ch_7(int)));

	connect(ui->dial_MixerChSend_8,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_dial_changed_ch_8(int)));

	connect(ui->dial_MixerChSend_9,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_dial_changed_ch_9(int)));

	connect(ui->dial_MixerChSend_10,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_dial_changed_ch_10(int)));

	connect(ui->dial_MixerChSend_11,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_dial_changed_ch_11(int)));

	connect(ui->dial_MixerChSend_12,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_dial_changed_ch_12(int)));

	connect(ui->dial_MixerChSend_13,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_dial_changed_ch_13(int)));

	connect(ui->dial_MixerChSend_14,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_dial_changed_ch_14(int)));

	connect(ui->dial_MixerChSend_15,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_dial_changed_ch_15(int)));

	connect(ui->dial_MixerChSend_16,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_dial_changed_ch_16(int)));

	connect(ui->spinBox_MixerChSend_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_spinbox_changed_ch_1(int)));

	connect(ui->spinBox_MixerChSend_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_spinbox_changed_ch_2(int)));

	connect(ui->spinBox_MixerChSend_3,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_spinbox_changed_ch_3(int)));

	connect(ui->spinBox_MixerChSend_4,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_spinbox_changed_ch_4(int)));

	connect(ui->spinBox_MixerChSend_5,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_spinbox_changed_ch_5(int)));

	connect(ui->spinBox_MixerChSend_6,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_spinbox_changed_ch_6(int)));

	connect(ui->spinBox_MixerChSend_7,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_spinbox_changed_ch_7(int)));

	connect(ui->spinBox_MixerChSend_8,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_spinbox_changed_ch_8(int)));

	connect(ui->spinBox_MixerChSend_9,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_spinbox_changed_ch_9(int)));

	connect(ui->spinBox_MixerChSend_10,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_spinbox_changed_ch_10(int)));

	connect(ui->spinBox_MixerChSend_11,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_spinbox_changed_ch_11(int)));

	connect(ui->spinBox_MixerChSend_12,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_spinbox_changed_ch_12(int)));

	connect(ui->spinBox_MixerChSend_13,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_spinbox_changed_ch_13(int)));

	connect(ui->spinBox_MixerChSend_14,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_spinbox_changed_ch_14(int)));

	connect(ui->spinBox_MixerChSend_15,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_spinbox_changed_ch_15(int)));

	connect(ui->spinBox_MixerChSend_16,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_spinbox_changed_ch_16(int)));

	connect(ui->comboBox_MixerChPanModLfo_1,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MixerChPanModLfo_1,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MixerChPanModLfo_2,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MixerChPanModLfo_2,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MixerChPanModLfo_3,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MixerChPanModLfo_3,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MixerChPanModLfo_4,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MixerChPanModLfo_4,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MixerChPanModLfo_5,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MixerChPanModLfo_5,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MixerChPanModLfo_6,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MixerChPanModLfo_6,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MixerChPanModLfo_7,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MixerChPanModLfo_7,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MixerChPanModLfo_8,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MixerChPanModLfo_8,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MixerChPanModLfo_9,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MixerChPanModLfo_9,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MixerChPanModLfo_10,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MixerChPanModLfo_10,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MixerChPanModLfo_11,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MixerChPanModLfo_11,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MixerChPanModLfo_12,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MixerChPanModLfo_12,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MixerChPanModLfo_13,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MixerChPanModLfo_13,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MixerChPanModLfo_14,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MixerChPanModLfo_14,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MixerChPanModLfo_15,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MixerChPanModLfo_15,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MixerChPanModLfo_16,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MixerChPanModLfo_16,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_midi_mixer_modulator_combo_box_mouse_exited(int)));
	
	
	// LFO Frame
	connect(ui->comboBox_LFOwaveform,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_selected_lfo_waveform_combo_changed(int)));

	connect(ui->dial_LFOrate,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_selected_lfo_rate_dial_changed(int)));

	connect(ui->dial_LFOsymmetry,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_selected_lfo_symmetry_dial_changed(int)));

	connect(ui->pushButton_closeLFOframe,
			SIGNAL(clicked()),
			this,
			SLOT(on_LFO_frame_close_button_clicked()));
	
}
