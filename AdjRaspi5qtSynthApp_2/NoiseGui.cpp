/**
 * @file		NoiseGui.cpp
 *	@author		Nahum Budin
 *	@date		21-Dec-2025
 *	@version	2.0
 *
 *	@brief		Analog Synthesizer instrument Noise Generator GUI handling
 *
 *	History:
 *		Version 1.1		25-Oct-2024
 *		Based on the AdjModSynth project ver 1.1 16-Jan-2021
 *
 */

#include "Defs.h"
#include "Dialog_AnalogSynth_1900x1000.h"
#include "MainWindow.h"
#include "ui_Dialog_AnalogSynth_1900x1000.h"

int Dialog_AnalogSynth_1900x1000::init_noise_gui()
{
	int result;

	set_noise_signals_connections();
	noise_update();

	string_noise_colors_list.append("White");
	string_noise_colors_list.append("Pink");
	string_noise_colors_list.append("Brown");

	// Noise Color frame and controls
	result = init_frame_colors(ui->frame_NoiseColor);

	result = init_combobox_control_colors(ui->comboBox_NoiseColor);
	ui->comboBox_NoiseColor->blockSignals(true);
	ui->comboBox_NoiseColor->addItems(string_noise_colors_list);
	ui->comboBox_NoiseColor->blockSignals(false);

	result = init_dial_control_colors(ui->dial_NoiseSendFilter1);
	result = init_dial_control_colors(ui->dial_NoiseSendFilter2);

	// Noise Amp Modulation frame and controls
	result = init_frame_colors(ui->frame_NoiseAmpMod);

	result = init_dial_control_colors(ui->dial_NoiseAmpModLFOLevel);
	result = init_dial_control_colors(ui->dial_NoiseAmpModAdsrLevel);
	
	result = init_combobox_control_colors(ui->comboBox_NoiseAmpModAdsr);
	ui->comboBox_NoiseAmpModAdsr->blockSignals(true);
	ui->comboBox_NoiseAmpModAdsr->addItems(string_adsr_values);
	ui->comboBox_NoiseAmpModAdsr->setIdentifier(_NOISE_AMP_MOD_ADSR_COMBOBOX_INDEX);
	ui->comboBox_NoiseAmpModAdsr->blockSignals(false);
	
	result = init_combobox_control_colors(ui->comboBox_NoiseAmpModLFO);
	ui->comboBox_NoiseAmpModLFO->blockSignals(true);
	ui->comboBox_NoiseAmpModLFO->addItems(string_lfo_values);
	ui->comboBox_NoiseAmpModLFO->setIdentifier(_NOISE_AMP_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_NoiseAmpModLFO->blockSignals(false);

		return 0;
}

void Dialog_AnalogSynth_1900x1000::set_noise_signals_connections()
{
	connect(ui->spinBox_NoiseSendFilter1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_noise_send_filter_1_spinbox_changed(int)));

	connect(ui->spinBox_NoiseSendFilter2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_noise_send_filter_2_spinbox_changed(int)));

	connect(ui->dial_NoiseSendFilter1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_noise_send_filter_1_dial_changed(int)));

	connect(ui->dial_NoiseSendFilter2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_noise_send_filter_2_dial_changed(int)));

	connect(ui->spinBox_NoiseAmpModLfoLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_noise_amp_mod_lfo_level_spinbox_changed(int)));

	connect(ui->spinBox_NoiseAmpModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_noise_amp_mod_adsr_level_spinbox_changed(int)));

	connect(ui->dial_NoiseAmpModLFOLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_noise_amp_mod_lfo_level_dial_changed(int)));

	connect(ui->dial_NoiseAmpModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_noise_amp_mod_adsr_level_dial_changed(int)));

	connect(ui->comboBox_NoiseAmpModAdsr,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_noise_amp_mod_adsr_combobox_changed(int)));

	connect(ui->comboBox_NoiseAmpModLFO,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_noise_amp_mod_lfo_combobox_changed(int)));

	connect(ui->comboBox_NoiseColor,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_noise_color_combobox_changed(int)));

	connect(ui->checkBox_NoiseEnable,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_noise_enable_changed(bool)));
}

void Dialog_AnalogSynth_1900x1000::noise_update()
{
	ui->comboBox_NoiseColor->blockSignals(true);
	ui->comboBox_NoiseColor->setCurrentIndex(mod_synth_get_active_noise_color());
	ui->comboBox_NoiseColor->blockSignals(false);

	ui->dial_NoiseSendFilter1->blockSignals(true);
	ui->dial_NoiseSendFilter1->setValue(mod_synth_get_active_noise_send_filter_1());
	ui->dial_NoiseSendFilter1->blockSignals(false);

	ui->spinBox_NoiseSendFilter1->blockSignals(true);
	ui->spinBox_NoiseSendFilter1->setValue(mod_synth_get_active_noise_send_filter_1());
	ui->spinBox_NoiseSendFilter1->blockSignals(false);

	ui->dial_NoiseSendFilter2->blockSignals(true);
	ui->dial_NoiseSendFilter2->setValue(mod_synth_get_active_noise_send_filter_2());
	ui->dial_NoiseSendFilter2->blockSignals(false);

	ui->spinBox_NoiseSendFilter2->blockSignals(true);
	ui->spinBox_NoiseSendFilter2->setValue(mod_synth_get_active_noise_send_filter_2());
	ui->spinBox_NoiseSendFilter2->blockSignals(false);

	ui->comboBox_NoiseAmpModLFO->blockSignals(true);
	ui->comboBox_NoiseAmpModLFO->setCurrentIndex(mod_synth_get_active_noise_amp_mod_lfo());
	ui->comboBox_NoiseAmpModLFO->blockSignals(false);

	ui->dial_NoiseAmpModLFOLevel->blockSignals(true);
	ui->dial_NoiseAmpModLFOLevel->setValue(mod_synth_get_active_noise_amp_mod_lfo_level());
	ui->dial_NoiseAmpModLFOLevel->blockSignals(false);

	ui->spinBox_NoiseAmpModLfoLevel->blockSignals(true);
	ui->spinBox_NoiseAmpModLfoLevel->setValue(mod_synth_get_active_noise_amp_mod_lfo_level());
	ui->spinBox_NoiseAmpModLfoLevel->blockSignals(false);

	ui->comboBox_NoiseAmpModAdsr->blockSignals(true);
	ui->comboBox_NoiseAmpModAdsr->setCurrentIndex(mod_synth_get_active_noise_amp_mod_env());
	ui->comboBox_NoiseAmpModAdsr->blockSignals(false);

	ui->dial_NoiseAmpModAdsrLevel->blockSignals(true);
	ui->dial_NoiseAmpModAdsrLevel->setValue(mod_synth_get_active_noise_amp_mod_env_level());
	ui->dial_NoiseAmpModAdsrLevel->blockSignals(false);

	ui->spinBox_NoiseAmpModAdsrLevel->blockSignals(true);
	ui->spinBox_NoiseAmpModAdsrLevel->setValue(mod_synth_get_active_noise_amp_mod_env_level());
	ui->spinBox_NoiseAmpModAdsrLevel->blockSignals(false);

	noise_enabled = mod_synth_get_active_noise_enable_state();
	ui->checkBox_NoiseEnable->blockSignals(true);
	ui->checkBox_NoiseEnable->setChecked(noise_enabled);
	ui->checkBox_NoiseEnable->blockSignals(false);

	if (noise_enabled)
	{
		ui->frame_NoiseAmpMod->setEnabled(true);
		ui->frame_NoiseColor->setEnabled(true);
	}
	else
	{
		ui->frame_NoiseAmpMod->setEnabled(false);
		ui->frame_NoiseColor->setEnabled(false);
	}
}

void Dialog_AnalogSynth_1900x1000::on_noise_enable_changed(bool en)
{
	ui->checkBox_NoiseEnable->blockSignals(true);
	if (en)
	{
		ui->checkBox_NoiseEnable->setCheckState(Qt::Checked);
		mod_synth_enable_noise();
	}
	else
	{
		ui->checkBox_NoiseEnable->setCheckState(Qt::Unchecked);
		mod_synth_disable_noise();
	}
	ui->checkBox_NoiseEnable->blockSignals(false);

	noise_enabled = en;

	mod_synth_noise_event_bool(_NOISE_1_EVENT, _NOISE_ENABLE, en);

	noise_update();

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_noise_send_filter_1_spinbox_changed(int val)
{
	on_noise_send_filter_1_dial_changed(val);
}

void Dialog_AnalogSynth_1900x1000::on_noise_send_filter_2_spinbox_changed(int val)
{
	on_noise_send_filter_2_dial_changed(val);
}

void Dialog_AnalogSynth_1900x1000::on_noise_amp_mod_lfo_level_spinbox_changed(int val)
{
	on_noise_amp_mod_lfo_level_dial_changed(val);
}

void Dialog_AnalogSynth_1900x1000::on_noise_amp_mod_adsr_level_spinbox_changed(int val)
{
	on_noise_amp_mod_adsr_level_dial_changed(val);
}

void Dialog_AnalogSynth_1900x1000::on_noise_send_filter_1_dial_changed(int val)
{
	ui->dial_NoiseSendFilter1->blockSignals(true);
	ui->dial_NoiseSendFilter1->setValue(val);
	ui->dial_NoiseSendFilter1->blockSignals(false);

	ui->spinBox_NoiseSendFilter1->blockSignals(true);
	ui->spinBox_NoiseSendFilter1->setValue(val);
	ui->spinBox_NoiseSendFilter1->blockSignals(false);

	noise_send_filter_1_level = val;
	mod_synth_noise_event_int(_NOISE_1_EVENT, _NOISE_SEND_1, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_noise_send_filter_2_dial_changed(int val)
{
	ui->dial_NoiseSendFilter2->blockSignals(true);
	ui->dial_NoiseSendFilter2->setValue(val);
	ui->dial_NoiseSendFilter2->blockSignals(false);

	ui->spinBox_NoiseSendFilter2->blockSignals(true);
	ui->spinBox_NoiseSendFilter2->setValue(val);
	ui->spinBox_NoiseSendFilter2->blockSignals(false);

	noise_send_filter_2_level = val;
	mod_synth_noise_event_int(_NOISE_1_EVENT, _NOISE_SEND_2, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_noise_amp_mod_lfo_level_dial_changed(int val)
{
	ui->dial_NoiseAmpModLFOLevel->blockSignals(true);
	ui->dial_NoiseAmpModLFOLevel->setValue(val);
	ui->dial_NoiseAmpModLFOLevel->blockSignals(false);

	ui->spinBox_NoiseAmpModLfoLevel->blockSignals(true);
	ui->spinBox_NoiseAmpModLfoLevel->setValue(val);
	ui->spinBox_NoiseAmpModLfoLevel->blockSignals(false);

	noise_amp_mod_lfo_level = val;
	mod_synth_noise_event_int(_NOISE_1_EVENT, _NOISE_AMP_MOD_LFO_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_noise_amp_mod_adsr_level_dial_changed(int val)
{
	ui->dial_NoiseAmpModAdsrLevel->blockSignals(true);
	ui->dial_NoiseAmpModAdsrLevel->setValue(val);
	ui->dial_NoiseAmpModAdsrLevel->blockSignals(false);

	ui->spinBox_NoiseAmpModAdsrLevel->blockSignals(true);
	ui->spinBox_NoiseAmpModAdsrLevel->setValue(val);
	ui->spinBox_NoiseAmpModAdsrLevel->blockSignals(false);

	noise_amp_mod_adsr_level = val;
	mod_synth_noise_event_int(_NOISE_1_EVENT, _NOISE_AMP_MOD_ENV_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_noise_color_combobox_changed(int val)
{
	ui->comboBox_NoiseColor->blockSignals(true);
	ui->comboBox_NoiseColor->setCurrentIndex(val);
	ui->comboBox_NoiseColor->blockSignals(false);

	noise_color = val;
	mod_synth_noise_event_int(_NOISE_1_EVENT, _NOISE_COLOR, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_noise_amp_mod_lfo_combobox_changed(int val)
{
	ui->comboBox_NoiseAmpModLFO->blockSignals(true);
	ui->comboBox_NoiseAmpModLFO->setCurrentIndex(val);
	ui->comboBox_NoiseAmpModLFO->blockSignals(false);

	noise_amp_mod_lfo_num = val;
	mod_synth_noise_event_int(_NOISE_1_EVENT, _NOISE_AMP_MOD_LFO, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_noise_amp_mod_adsr_combobox_changed(int val)
{
	ui->comboBox_NoiseAmpModAdsr->blockSignals(true);
	ui->comboBox_NoiseAmpModAdsr->setCurrentIndex(val);
	ui->comboBox_NoiseAmpModAdsr->blockSignals(false);

	noise_amp_mod_adsr_num = val;
	mod_synth_noise_event_int(_NOISE_1_EVENT, _NOISE_AMP_MOD_ENV, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}


