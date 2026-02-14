/**
 * @file		AmpssGui.cpp
 *	@author		Nahum Budin
 *	@date		18-Jan-2026
 *	@version	2.0
 *
 *	@brief		Analog Synthesizer instrument Amps GUI handling
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

int Dialog_AnalogSynth_1900x1000::init_amps_gui()
{
	ui->comboBox_AmpPanModLfo_1->blockSignals(true);
	ui->comboBox_AmpPanModLfo_1->addItem("-----");
	ui->comboBox_AmpPanModLfo_1->addItem("LFO 1");
	ui->comboBox_AmpPanModLfo_1->addItem("LFO 2");
	ui->comboBox_AmpPanModLfo_1->addItem("LFO 3");
	ui->comboBox_AmpPanModLfo_1->addItem("LFO 4");
	ui->comboBox_AmpPanModLfo_1->addItem("LFO 5");
	ui->comboBox_AmpPanModLfo_1->addItem("LFO 6");
	ui->comboBox_AmpPanModLfo_1->setIdentifier(_AMP1_PAN_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_AmpPanModLfo_1->blockSignals(false);

	ui->comboBox_AmpPanModLfo_2->blockSignals(true);
	ui->comboBox_AmpPanModLfo_2->addItem("-----");
	ui->comboBox_AmpPanModLfo_2->addItem("LFO 1");
	ui->comboBox_AmpPanModLfo_2->addItem("LFO 2");
	ui->comboBox_AmpPanModLfo_2->addItem("LFO 3");
	ui->comboBox_AmpPanModLfo_2->addItem("LFO 4");
	ui->comboBox_AmpPanModLfo_2->addItem("LFO 5");
	ui->comboBox_AmpPanModLfo_2->addItem("LFO 6");
	ui->comboBox_AmpPanModLfo_2->setIdentifier(_AMP2_PAN_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_AmpPanModLfo_2->blockSignals(false);

	set_amps_signals_connections();
	amps_update();

	return 0;
}

void Dialog_AnalogSynth_1900x1000::set_amps_signals_connections()
{
	connect(ui->dial_AmpAmp_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_amp1_level_dial_hanged(int)));

	connect(ui->dial_AmpPan_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_amp1_pan_dial_changed(int)));

	connect(ui->dial_AmpAmp_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_amp2_level_dial_hanged(int)));

	connect(ui->dial_AmpPan_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_amp2_pan_dial_changed(int)));

	connect(ui->comboBox_AmpPanModLfo_1,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_amp1_pan_mod_lfo_combo_changed(int)));

	connect(ui->dial_AmpPanModLfoLevel_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_amp1_pan_mod_level_lfo_dial_changed(int)));

	connect(ui->comboBox_AmpPanModLfo_2,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_amp2_pan_mod_lfo_combo_changed(int)));

	connect(ui->dial_AmpPanModLfoLevel_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_amp2_pan_mod_level_lfo_dial_changed(int)));

	connect(ui->checkBox_AmpFix,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_fixed_amp_checkbox_Changed(bool)));
}

void Dialog_AnalogSynth_1900x1000::amps_update()
{
	ui->dial_AmpAmp_1->blockSignals(true);
	ui->dial_AmpAmp_1->setValue(mod_synth_get_active_ch_1_level());
	ui->dial_AmpAmp_1->blockSignals(false);

	ui->spinBox_AmpAmp_1->blockSignals(true);
	ui->spinBox_AmpAmp_1->setValue(mod_synth_get_active_ch_1_level());
	ui->spinBox_AmpAmp_1->blockSignals(false);

	ui->dial_AmpPan_1->blockSignals(true);
	ui->dial_AmpPan_1->setValue(mod_synth_get_active_ch_1_pan());
	ui->dial_AmpPan_1->blockSignals(false);

	ui->spinBox_AmpPan_1->blockSignals(true);
	ui->spinBox_AmpPan_1->setValue(mod_synth_get_active_ch_1_pan());
	ui->spinBox_AmpPan_1->blockSignals(false);

	ui->dial_AmpAmp_2->blockSignals(true);
	ui->dial_AmpAmp_2->setValue(mod_synth_get_active_ch_2_level());
	ui->dial_AmpAmp_2->blockSignals(false);

	ui->spinBox_AmpAmp_2->blockSignals(true);
	ui->spinBox_AmpAmp_2->setValue(mod_synth_get_active_ch_2_level());
	ui->spinBox_AmpAmp_2->blockSignals(false);

	ui->dial_AmpPan_2->blockSignals(true);
	ui->dial_AmpPan_2->setValue(mod_synth_get_active_ch_2_pan());
	ui->dial_AmpPan_2->blockSignals(false);

	ui->spinBox_AmpPan_2->blockSignals(true);
	ui->spinBox_AmpPan_2->setValue(mod_synth_get_active_ch_2_pan());
	ui->spinBox_AmpPan_2->blockSignals(false);

	ui->comboBox_AmpPanModLfo_1->blockSignals(true);
	ui->comboBox_AmpPanModLfo_1->setCurrentIndex(mod_synth_get_active_ch_1_pan_mod_lfo());
	ui->comboBox_AmpPanModLfo_1->blockSignals(false);

	ui->dial_AmpPanModLfoLevel_1->blockSignals(true);
	ui->dial_AmpPanModLfoLevel_1->setValue(mod_synth_get_active_ch_1_pan_mod_lfo_level());
	ui->dial_AmpPanModLfoLevel_1->blockSignals(false);

	ui->spinBox_AmpPanModLfoLevel_1->blockSignals(true);
	ui->spinBox_AmpPanModLfoLevel_1->setValue(mod_synth_get_active_ch_1_pan_mod_lfo_level());
	ui->spinBox_AmpPanModLfoLevel_1->blockSignals(false);

	ui->comboBox_AmpPanModLfo_2->blockSignals(true);
	ui->comboBox_AmpPanModLfo_2->setCurrentIndex(mod_synth_get_active_ch_2_pan_mod_lfo());
	ui->comboBox_AmpPanModLfo_2->blockSignals(false);

	ui->dial_AmpPanModLfoLevel_2->blockSignals(true);
	ui->dial_AmpPanModLfoLevel_2->setValue(mod_synth_get_active_ch_2_pan_mod_lfo_level());
	ui->dial_AmpPanModLfoLevel_2->blockSignals(false);

	ui->spinBox_AmpPanModLfoLevel_2->blockSignals(true);
	ui->spinBox_AmpPanModLfoLevel_2->setValue(mod_synth_get_active_ch_2_pan_mod_lfo_level());
	ui->spinBox_AmpPanModLfoLevel_2->blockSignals(false);

	ui->checkBox_AmpFix->blockSignals(true);
	// ui->checkBox_AmpFix->setChecked(mod_synth_get_active_ch_amp_fix()); // TODO:
	ui->checkBox_AmpFix->blockSignals(false);
}

void Dialog_AnalogSynth_1900x1000::on_amp1_level_dial_hanged(int val)
{
	ui->dial_AmpAmp_1->blockSignals(true);
	ui->dial_AmpAmp_1->setValue(val);
	ui->dial_AmpAmp_1->blockSignals(false);

	ui->spinBox_AmpAmp_1->blockSignals(true);
	ui->spinBox_AmpAmp_1->setValue(val);
	ui->spinBox_AmpAmp_1->blockSignals(false);

	int amp1_level = val;
	mod_synth_amp_event_int(_AMP_CH1_EVENT, _AMP_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_amp1_pan_dial_changed(int val)
{
	ui->dial_AmpPan_1->blockSignals(true);
	ui->dial_AmpPan_1->setValue(val);
	ui->dial_AmpPan_1->blockSignals(false);

	ui->spinBox_AmpPan_1->blockSignals(true);
	ui->spinBox_AmpPan_1->setValue(val);
	ui->spinBox_AmpPan_1->blockSignals(false);

	int amp1_pan = val;
	mod_synth_amp_event_int(_AMP_CH1_EVENT, _AMP_PAN, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_amp1_pan_mod_lfo_combo_changed(int val)
{
	ui->comboBox_AmpPanModLfo_1->blockSignals(true);
	ui->comboBox_AmpPanModLfo_1->setCurrentIndex(val);
	ui->comboBox_AmpPanModLfo_1->blockSignals(false);

	amp1_pan_mod_lfo = val;
	mod_synth_filter_event_int(_AMP_CH1_EVENT, _AMP_PAN_MOD_LFO, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_amp1_pan_mod_level_lfo_dial_changed(int val)
{
	ui->dial_AmpPanModLfoLevel_1->blockSignals(true);
	ui->dial_AmpPanModLfoLevel_1->setValue(val);
	ui->dial_AmpPanModLfoLevel_1->blockSignals(false);

	ui->spinBox_AmpPanModLfoLevel_1->blockSignals(true);
	ui->spinBox_AmpPanModLfoLevel_1->setValue(val);
	ui->spinBox_AmpPanModLfoLevel_1->blockSignals(false);

	int amp1_pan_mod_lfo_level = val;
	mod_synth_filter_event_int(_AMP_CH1_EVENT, _AMP_PAN_MOD_LFO_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_amp2_level_dial_hanged(int val)
{
	ui->dial_AmpAmp_2->blockSignals(true);
	ui->dial_AmpAmp_2->setValue(val);
	ui->dial_AmpAmp_2->blockSignals(false);

	ui->spinBox_AmpAmp_2->blockSignals(true);
	ui->spinBox_AmpAmp_2->setValue(val);
	ui->spinBox_AmpAmp_2->blockSignals(false);

	int amp2_level = val;
	mod_synth_amp_event_int(_AMP_CH2_EVENT, _AMP_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_amp2_pan_dial_changed(int val)
{
	ui->dial_AmpPan_2->blockSignals(true);
	ui->dial_AmpPan_2->setValue(val);
	ui->dial_AmpPan_2->blockSignals(false);

	ui->spinBox_AmpPan_2->blockSignals(true);
	ui->spinBox_AmpPan_2->setValue(val);
	ui->spinBox_AmpPan_2->blockSignals(false);

	int amp2_pan = val;
	mod_synth_amp_event_int(_AMP_CH2_EVENT, _AMP_PAN, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_amp2_pan_mod_lfo_combo_changed(int val)
{
	ui->comboBox_AmpPanModLfo_2->blockSignals(true);
	ui->comboBox_AmpPanModLfo_2->setCurrentIndex(val);
	ui->comboBox_AmpPanModLfo_2->blockSignals(false);

	amp2_pan_mod_lfo = val;
	mod_synth_filter_event_int(_AMP_CH2_EVENT, _AMP_PAN_MOD_LFO, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_amp2_pan_mod_level_lfo_dial_changed(int val)
{
	ui->dial_AmpPanModLfoLevel_2->blockSignals(true);
	ui->dial_AmpPanModLfoLevel_2->setValue(val);
	ui->dial_AmpPanModLfoLevel_2->blockSignals(false);

	ui->spinBox_AmpPanModLfoLevel_2->blockSignals(true);
	ui->spinBox_AmpPanModLfoLevel_2->setValue(val);
	ui->spinBox_AmpPanModLfoLevel_2->blockSignals(false);

	int amp2_pan_mod_lfo_level = val;
	mod_synth_filter_event_int(_AMP_CH2_EVENT, _AMP_PAN_MOD_LFO_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_fixed_amp_checkbox_Changed(bool val)
{
	ui->checkBox_AmpFix->blockSignals(true);

	if (val)
	{
		ui->checkBox_AmpFix->setCheckState(Qt::Checked);
		amp_fixed = true;
	}
	else
	{
		ui->checkBox_AmpFix->setCheckState(Qt::Unchecked);
		amp_fixed = false;
	}

	ui->checkBox_AmpFix->blockSignals(false);

	mod_synth_amp_event_int(_AMP_CH1_EVENT, _AMP_FIXED_LEVELS, val);
}
