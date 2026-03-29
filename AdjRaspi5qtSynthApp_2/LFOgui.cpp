/**
 * @file		LFORgui.cpp
 *	@author		Nahum Budin
 *	@date		9-Jan-2026
 *	@version	2.0
 *
 *	@brief		Analog Synthesizer instrument LFOs GUI handling
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

int Dialog_AnalogSynth_1900x1000::init_lfos_gui()
{
	int result;

	if (string_waveforms_list.size() == 0)
	{
		/* Do only once for all */
		string_waveforms_list.append("Sine");
		string_waveforms_list.append("Square");
		string_waveforms_list.append("Pulse");
		string_waveforms_list.append("Triangle");
		string_waveforms_list.append("Sample & Hold");
	}

	ui->comboBox_LFOwaveform_1->blockSignals(true);
	ui->comboBox_LFOwaveform_1->addItems(string_waveforms_list);
	ui->comboBox_LFOwaveform_1->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_LFOwaveform_1->blockSignals(false);

	ui->comboBox_LFOwaveform_2->blockSignals(true);
	ui->comboBox_LFOwaveform_2->addItems(string_waveforms_list);
	ui->comboBox_LFOwaveform_2->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_LFOwaveform_2->blockSignals(false);

	ui->comboBox_LFOwaveform_3->blockSignals(true);
	ui->comboBox_LFOwaveform_3->addItems(string_waveforms_list);
	ui->comboBox_LFOwaveform_3->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_LFOwaveform_3->blockSignals(false);

	ui->comboBox_LFOwaveform_4->blockSignals(true);
	ui->comboBox_LFOwaveform_4->addItems(string_waveforms_list);
	ui->comboBox_LFOwaveform_4->setTextAlignment(Qt::AlignCenter);	
	ui->comboBox_LFOwaveform_4->blockSignals(false);

	ui->comboBox_LFOwaveform_5->blockSignals(true);
	ui->comboBox_LFOwaveform_5->addItems(string_waveforms_list);
	ui->comboBox_LFOwaveform_5->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_LFOwaveform_5->blockSignals(false);

	ui->comboBox_LFOwaveform_6->blockSignals(true);
	ui->comboBox_LFOwaveform_6->addItems(string_waveforms_list);
	ui->comboBox_LFOwaveform_6->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_LFOwaveform_6->blockSignals(false);

	result = init_dial_control_colors(ui->dial_LFOsymmetry_1);
	result = init_dial_control_colors(ui->dial_LFOrate_1);
	result = init_dial_control_colors(ui->dial_LFOsymmetry_2);
	result = init_dial_control_colors(ui->dial_LFOrate_2);
	result = init_dial_control_colors(ui->dial_LFOsymmetry_3);
	result = init_dial_control_colors(ui->dial_LFOrate_3);
	result = init_dial_control_colors(ui->dial_LFOsymmetry_4);
	result = init_dial_control_colors(ui->dial_LFOrate_4);
	result = init_dial_control_colors(ui->dial_LFOsymmetry_5);
	result = init_dial_control_colors(ui->dial_LFOrate_5);
	result = init_dial_control_colors(ui->dial_LFOsymmetry_6);
	result = init_dial_control_colors(ui->dial_LFOrate_6);

	result = init_combobox_control_colors(ui->comboBox_LFOwaveform_1);
	result = init_combobox_control_colors(ui->comboBox_LFOwaveform_2);
	result = init_combobox_control_colors(ui->comboBox_LFOwaveform_3);
	result = init_combobox_control_colors(ui->comboBox_LFOwaveform_4);
	result = init_combobox_control_colors(ui->comboBox_LFOwaveform_5);
	result = init_combobox_control_colors(ui->comboBox_LFOwaveform_6);

	set_lfos_signals_connections();
	lfos_update();
	
	return 0;
}

void Dialog_AnalogSynth_1900x1000::set_lfos_signals_connections()
{
	connect(ui->comboBox_LFOwaveform_1,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_lfo1_waveform_combo_changed(int)));

	connect(ui->dial_LFOrate_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_lfo1_rate_dial_changed(int)));

	connect(ui->dial_LFOsymmetry_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_lfo1_symmetry_dial_changed(int)));

	connect(ui->comboBox_LFOwaveform_2,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_lfo2_waveform_combo_changed(int)));

	connect(ui->dial_LFOrate_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_lfo2_rate_dial_changed(int)));

	connect(ui->dial_LFOsymmetry_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_lfo2_symmetry_dial_changed(int)));

	connect(ui->comboBox_LFOwaveform_3,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_lfo3_waveform_combo_changed(int)));

	connect(ui->dial_LFOrate_3,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_lfo3_rate_dial_changed(int)));

	connect(ui->dial_LFOsymmetry_3,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_lfo3_symmetry_dial_changed(int)));

	connect(ui->comboBox_LFOwaveform_4,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_lfo4_waveform_combo_changed(int)));

	connect(ui->dial_LFOrate_4,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_lfo4_rate_dial_changed(int)));

	connect(ui->dial_LFOsymmetry_4,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_lfo4_symmetry_dial_changed(int)));

	connect(ui->comboBox_LFOwaveform_5,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_lfo5_waveform_combo_changed(int)));

	connect(ui->dial_LFOrate_5,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_lfo5_rate_dial_changed(int)));

	connect(ui->dial_LFOsymmetry_5,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_lfo5_symmetry_dial_changed(int)));

	connect(ui->comboBox_LFOwaveform_6,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_lfo6_waveform_combo_changed(int)));

	connect(ui->dial_LFOrate_6,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_lfo6_rate_dial_changed(int)));

	connect(ui->dial_LFOsymmetry_6,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_lfo6_symmetry_dial_changed(int)));
}

void Dialog_AnalogSynth_1900x1000::lfos_update()
{
	char text[64];

	ui->comboBox_LFOwaveform_1->blockSignals(true);
	ui->comboBox_LFOwaveform_1->setCurrentIndex(mod_synth_get_active_lfo_mod_1_waveform());
	ui->comboBox_LFOwaveform_1->blockSignals(false);

	ui->dial_LFOsymmetry_1->blockSignals(true);
	ui->dial_LFOsymmetry_1->setValue(mod_synth_get_active_lfo_mod_1_symmetry());
	ui->dial_LFOsymmetry_1->blockSignals(false);
	sprintf(text, "%i%c", mod_synth_get_active_lfo_mod_1_symmetry(), '%');
	ui->lineEdit_LFOsymmetry_1->setText(QString(text));

	ui->dial_LFOrate_1->blockSignals(true);
	ui->dial_LFOrate_1->setValue(mod_synth_get_active_lfo_mod_1_rate());
	ui->dial_LFOrate_1->blockSignals(false);

	sprintf(text, "%.2fHz",
			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
										  mod_synth_get_lfo_max_frequency(), 10.0,
										  mod_synth_get_active_lfo_mod_1_rate()));

	ui->lineEdit_LFOrate_1->setText(QString(text));

	ui->comboBox_LFOwaveform_2->blockSignals(true);
	ui->comboBox_LFOwaveform_2->setCurrentIndex(mod_synth_get_active_lfo_mod_2_waveform());
	ui->comboBox_LFOwaveform_2->blockSignals(false);

	ui->dial_LFOsymmetry_2->blockSignals(true);
	ui->dial_LFOsymmetry_2->setValue(mod_synth_get_active_lfo_mod_2_symmetry());
	ui->dial_LFOsymmetry_2->blockSignals(false);
	sprintf(text, "%i%c", mod_synth_get_active_lfo_mod_2_symmetry(), '%');
	ui->lineEdit_LFOsymmetry_2->setText(QString(text));

	ui->dial_LFOrate_2->blockSignals(true);
	ui->dial_LFOrate_2->setValue(mod_synth_get_active_lfo_mod_2_rate());
	ui->dial_LFOrate_2->blockSignals(false);

	sprintf(text,
			"%.2fHz",
			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
										  mod_synth_get_lfo_max_frequency(),
										  10.0,
										  mod_synth_get_active_lfo_mod_2_rate()));

	ui->lineEdit_LFOrate_2->setText(QString(text));

	ui->comboBox_LFOwaveform_3->blockSignals(true);
	ui->comboBox_LFOwaveform_3->setCurrentIndex(mod_synth_get_active_lfo_mod_3_waveform());
	ui->comboBox_LFOwaveform_3->blockSignals(false);

	ui->dial_LFOsymmetry_3->blockSignals(true);
	ui->dial_LFOsymmetry_3->setValue(mod_synth_get_active_lfo_mod_3_symmetry());
	ui->dial_LFOsymmetry_3->blockSignals(false);
	sprintf(text, "%i%c", mod_synth_get_active_lfo_mod_3_symmetry(), '%');
	ui->lineEdit_LFOsymmetry_3->setText(QString(text));

	ui->dial_LFOrate_3->blockSignals(true);
	ui->dial_LFOrate_3->setValue(mod_synth_get_active_lfo_mod_3_rate());
	ui->dial_LFOrate_3->blockSignals(false);

	sprintf(text,
			"%.2fHz",
			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
										  mod_synth_get_lfo_max_frequency(),
										  10.0,
										  mod_synth_get_active_lfo_mod_3_rate()));

	ui->lineEdit_LFOrate_3->setText(QString(text));

	ui->comboBox_LFOwaveform_4->blockSignals(true);
	ui->comboBox_LFOwaveform_4->setCurrentIndex(mod_synth_get_active_lfo_mod_4_waveform());
	ui->comboBox_LFOwaveform_4->blockSignals(false);

	ui->dial_LFOsymmetry_4->blockSignals(true);
	ui->dial_LFOsymmetry_4->setValue(mod_synth_get_active_lfo_mod_4_symmetry());
	ui->dial_LFOsymmetry_4->blockSignals(false);
	sprintf(text, "%i%c", mod_synth_get_active_lfo_mod_4_symmetry(), '%');
	ui->lineEdit_LFOsymmetry_4->setText(QString(text));

	ui->dial_LFOrate_4->blockSignals(true);
	ui->dial_LFOrate_4->setValue(mod_synth_get_active_lfo_mod_4_rate());
	ui->dial_LFOrate_4->blockSignals(false);

	sprintf(text,
			"%.2fHz",
			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
										  mod_synth_get_lfo_max_frequency(),
										  10.0,
										  mod_synth_get_active_lfo_mod_4_rate()));

	ui->lineEdit_LFOrate_4->setText(QString(text));

	ui->comboBox_LFOwaveform_5->blockSignals(true);
	ui->comboBox_LFOwaveform_5->setCurrentIndex(mod_synth_get_active_lfo_mod_5_waveform());
	ui->comboBox_LFOwaveform_5->blockSignals(false);

	ui->dial_LFOsymmetry_5->blockSignals(true);
	ui->dial_LFOsymmetry_5->setValue(mod_synth_get_active_lfo_mod_5_symmetry());
	ui->dial_LFOsymmetry_5->blockSignals(false);
	sprintf(text, "%i%c", mod_synth_get_active_lfo_mod_5_symmetry(), '%');
	ui->lineEdit_LFOsymmetry_5->setText(QString(text));

	ui->dial_LFOrate_5->blockSignals(true);
	ui->dial_LFOrate_5->setValue(mod_synth_get_active_lfo_mod_5_rate());
	ui->dial_LFOrate_5->blockSignals(false);

	sprintf(text,
			"%.2fHz",
			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
										  mod_synth_get_lfo_max_frequency(),
										  10.0,
										  mod_synth_get_active_lfo_mod_5_rate()));

	ui->lineEdit_LFOrate_5->setText(QString(text));

	ui->comboBox_LFOwaveform_6->blockSignals(true);
	ui->comboBox_LFOwaveform_6->setCurrentIndex(mod_synth_get_active_lfo_mod_6_waveform());
	ui->comboBox_LFOwaveform_6->blockSignals(false);

	ui->dial_LFOsymmetry_6->blockSignals(true);
	ui->dial_LFOsymmetry_6->setValue(mod_synth_get_active_lfo_mod_6_symmetry());
	ui->dial_LFOsymmetry_6->blockSignals(false);
	sprintf(text, "%i%c", mod_synth_get_active_lfo_mod_6_symmetry(), '%');
	ui->lineEdit_LFOsymmetry_6->setText(QString(text));

	ui->dial_LFOrate_6->blockSignals(true);
	ui->dial_LFOrate_6->setValue(mod_synth_get_active_lfo_mod_6_rate());
	ui->dial_LFOrate_6->blockSignals(false);

	sprintf(text,
			"%.2fHz",
			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
										  mod_synth_get_lfo_max_frequency(),
										  10.0,
										  mod_synth_get_active_lfo_mod_6_rate()));

	ui->lineEdit_LFOrate_6->setText(QString(text));
}

void Dialog_AnalogSynth_1900x1000::on_lfo1_waveform_combo_changed(int val)
{
	ui->comboBox_LFOwaveform_1->blockSignals(true);
	ui->comboBox_LFOwaveform_1->setCurrentIndex(val);
	ui->comboBox_LFOwaveform_1->blockSignals(false);

	lfo1_waveform_entry = val;
	mod_synth_modulator_event_int(_LFO_1_EVENT, _MOD_LFO_WAVEFORM, val);
}

void Dialog_AnalogSynth_1900x1000::on_lfo1_symmetry_dial_changed(int val)
{
	char text[64];
	
	ui->dial_LFOsymmetry_1->blockSignals(true);
	ui->dial_LFOsymmetry_1->setValue(val);
	ui->dial_LFOsymmetry_1->blockSignals(false);

	lfo1_symmetry_entry = val;

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_LFOsymmetry_1->setText(QString(text));

	mod_synth_modulator_event_int(_LFO_1_EVENT, _MOD_LFO_SYMMETRY, val);
}

void Dialog_AnalogSynth_1900x1000::on_lfo1_rate_dial_changed(int val)
{
	char text[64];

	ui->dial_LFOrate_1->blockSignals(true);
	ui->dial_LFOrate_1->setValue(val);
	ui->dial_LFOrate_1->blockSignals(false);

	lfo1_rate_entry = val;

	sprintf(text,
			"%.2fHz",
			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
										  mod_synth_get_lfo_max_frequency(),
										  10.0,
										  val));

	ui->lineEdit_LFOrate_1->setText(QString(text));

	mod_synth_modulator_event_int(_LFO_1_EVENT, _MOD_LFO_RATE, val);
}

void Dialog_AnalogSynth_1900x1000::on_lfo2_waveform_combo_changed(int val)
{
	ui->comboBox_LFOwaveform_2->blockSignals(true);
	ui->comboBox_LFOwaveform_2->setCurrentIndex(val);
	ui->comboBox_LFOwaveform_2->blockSignals(false);

	lfo2_waveform_entry = val;
	mod_synth_modulator_event_int(_LFO_2_EVENT, _MOD_LFO_WAVEFORM, val);
}

void Dialog_AnalogSynth_1900x1000::on_lfo2_symmetry_dial_changed(int val)
{
	char text[64];

	ui->dial_LFOsymmetry_2->blockSignals(true);
	ui->dial_LFOsymmetry_2->setValue(val);
	ui->dial_LFOsymmetry_2->blockSignals(false);

	lfo2_symmetry_entry = val;

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_LFOsymmetry_2->setText(QString(text));

	mod_synth_modulator_event_int(_LFO_2_EVENT, _MOD_LFO_SYMMETRY, val);
}

void Dialog_AnalogSynth_1900x1000::on_lfo2_rate_dial_changed(int val)
{
	char text[64];

	ui->dial_LFOrate_2->blockSignals(true);
	ui->dial_LFOrate_2->setValue(val);
	ui->dial_LFOrate_2->blockSignals(false);

	lfo2_rate_entry = val;

	sprintf(text,
			"%.2fHz",
			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
										  mod_synth_get_lfo_max_frequency(),
										  10.0,
										  val));

	ui->lineEdit_LFOrate_2->setText(QString(text));

	mod_synth_modulator_event_int(_LFO_2_EVENT, _MOD_LFO_RATE, val);
}

void Dialog_AnalogSynth_1900x1000::on_lfo3_waveform_combo_changed(int val)
{
	ui->comboBox_LFOwaveform_3->blockSignals(true);
	ui->comboBox_LFOwaveform_3->setCurrentIndex(val);
	ui->comboBox_LFOwaveform_3->blockSignals(false);

	lfo3_waveform_entry = val;
	mod_synth_modulator_event_int(_LFO_3_EVENT, _MOD_LFO_WAVEFORM, val);
}

void Dialog_AnalogSynth_1900x1000::on_lfo3_symmetry_dial_changed(int val)
{
	char text[64];

	ui->dial_LFOsymmetry_3->blockSignals(true);
	ui->dial_LFOsymmetry_3->setValue(val);
	ui->dial_LFOsymmetry_3->blockSignals(false);

	lfo3_symmetry_entry = val;

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_LFOsymmetry_3->setText(QString(text));

	mod_synth_modulator_event_int(_LFO_3_EVENT, _MOD_LFO_SYMMETRY, val);
}

void Dialog_AnalogSynth_1900x1000::on_lfo3_rate_dial_changed(int val)
{
	char text[64];

	ui->dial_LFOrate_3->blockSignals(true);
	ui->dial_LFOrate_3->setValue(val);
	ui->dial_LFOrate_3->blockSignals(false);

	lfo3_rate_entry = val;

	sprintf(text,
			"%.2fHz",
			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
										  mod_synth_get_lfo_max_frequency(),
										  10.0,
										  val));

	ui->lineEdit_LFOrate_3->setText(QString(text));

	mod_synth_modulator_event_int(_LFO_3_EVENT, _MOD_LFO_RATE, val);
}

void Dialog_AnalogSynth_1900x1000::on_lfo4_waveform_combo_changed(int val)
{
	ui->comboBox_LFOwaveform_4->blockSignals(true);
	ui->comboBox_LFOwaveform_4->setCurrentIndex(val);
	ui->comboBox_LFOwaveform_4->blockSignals(false);
	lfo4_waveform_entry = val;
	mod_synth_modulator_event_int(_LFO_4_EVENT, _MOD_LFO_WAVEFORM, val);
}

void Dialog_AnalogSynth_1900x1000::on_lfo4_symmetry_dial_changed(int val)
{
	char text[64];
	
	ui->dial_LFOsymmetry_4->blockSignals(true);
	ui->dial_LFOsymmetry_4->setValue(val);
	ui->dial_LFOsymmetry_4->blockSignals(false);
	
	lfo4_symmetry_entry = val;
	
	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_LFOsymmetry_4->setText(QString(text));
	
	mod_synth_modulator_event_int(_LFO_4_EVENT, _MOD_LFO_SYMMETRY, val);
}

void Dialog_AnalogSynth_1900x1000::on_lfo4_rate_dial_changed(int val)
{
	char text[64];
	
	ui->dial_LFOrate_4->blockSignals(true);
	ui->dial_LFOrate_4->setValue(val);
	ui->dial_LFOrate_4->blockSignals(false);
	
	lfo4_rate_entry = val;
	
	sprintf(text,
			"%.2fHz",
			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
										  mod_synth_get_lfo_max_frequency(),
										  10.0,
										  val));
	ui->lineEdit_LFOrate_4->setText(QString(text));
	
	mod_synth_modulator_event_int(_LFO_4_EVENT, _MOD_LFO_RATE, val);
}

void Dialog_AnalogSynth_1900x1000::on_lfo5_waveform_combo_changed(int val)
{
	ui->comboBox_LFOwaveform_5->blockSignals(true);
	ui->comboBox_LFOwaveform_5->setCurrentIndex(val);
	ui->comboBox_LFOwaveform_5->blockSignals(false);
	lfo5_waveform_entry = val;
	mod_synth_modulator_event_int(_LFO_5_EVENT, _MOD_LFO_WAVEFORM, val);
}

void Dialog_AnalogSynth_1900x1000::on_lfo5_symmetry_dial_changed(int val)
{
	char text[64];
	
	ui->dial_LFOsymmetry_5->blockSignals(true);
	ui->dial_LFOsymmetry_5->setValue(val);
	ui->dial_LFOsymmetry_5->blockSignals(false);
	
	lfo5_symmetry_entry = val;
	
	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_LFOsymmetry_5->setText(QString(text));

	mod_synth_modulator_event_int(_LFO_5_EVENT, _MOD_LFO_SYMMETRY, val);
}

void Dialog_AnalogSynth_1900x1000::on_lfo5_rate_dial_changed(int val)
{
	char text[64];
	
	ui->dial_LFOrate_5->blockSignals(true);
	ui->dial_LFOrate_5->setValue(val);
	ui->dial_LFOrate_5->blockSignals(false);
	
	lfo5_rate_entry = val;
	
	sprintf(text,
			"%.2fHz",
			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
										  mod_synth_get_lfo_max_frequency(),
										  10.0,
										  val));
	ui->lineEdit_LFOrate_5->setText(QString(text));

	mod_synth_modulator_event_int(_LFO_5_EVENT, _MOD_LFO_RATE, val);
}

void Dialog_AnalogSynth_1900x1000::on_lfo6_waveform_combo_changed(int val)
{
	ui->comboBox_LFOwaveform_1->blockSignals(true);
	ui->comboBox_LFOwaveform_1->setCurrentIndex(val);
	ui->comboBox_LFOwaveform_1->blockSignals(false);

	lfo1_waveform_entry = val;
	mod_synth_modulator_event_int(_LFO_1_EVENT, _MOD_LFO_WAVEFORM, val);
}

void Dialog_AnalogSynth_1900x1000::on_lfo6_symmetry_dial_changed(int val)
{
	char text[64];
	
	ui->dial_LFOsymmetry_6->blockSignals(true);
	ui->dial_LFOsymmetry_6->setValue(val);
	ui->dial_LFOsymmetry_6->blockSignals(false);
	
	lfo6_symmetry_entry = val;
	
	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_LFOsymmetry_6->setText(QString(text));
	
	mod_synth_modulator_event_int(_LFO_6_EVENT, _MOD_LFO_SYMMETRY, val);
}

void Dialog_AnalogSynth_1900x1000::on_lfo6_rate_dial_changed(int val)
{
	char text[64];
	
	ui->dial_LFOrate_6->blockSignals(true);
	ui->dial_LFOrate_6->setValue(val);
	ui->dial_LFOrate_6->blockSignals(false);
	
	lfo6_rate_entry = val;
	
	sprintf(text,
			"%.2fHz",
			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
										  mod_synth_get_lfo_max_frequency(),
										  10.0,
										  val));
	ui->lineEdit_LFOrate_6->setText(QString(text));
	
	mod_synth_modulator_event_int(_LFO_6_EVENT, _MOD_LFO_RATE, val);
}

void Dialog_AnalogSynth_1900x1000::init_active_lfo_widget()
{
}

void Dialog_AnalogSynth_1900x1000::update_active_lfo_frame()
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

void Dialog_AnalogSynth_1900x1000::on_selected_lfo_rate_dial_changed(int val)
{
	if ((active_lfo) > _LFO_NONE && (active_lfo) <= _NUM_OF_LFOS)
	{
		char text[64];

		dial_lfo_rate[active_lfo - 1]->blockSignals(true); // 1..6 -> 0..5
		dial_lfo_rate[active_lfo - 1]->setValue(val);
		dial_lfo_rate[active_lfo - 1]->blockSignals(false);

		sprintf(text, "%.2fHz",
				mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
											  mod_synth_get_lfo_max_frequency(), 10.0,
											  val));

		lineedit_lfo_rate[active_lfo - 1]->setText(QString(text));
		ui->lineEdit_LFOrate->setText(QString(text));

		mod_synth_modulator_event_int(_LFO_1_EVENT + active_lfo - 1, _MOD_LFO_RATE, val);

		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
	}
}

void Dialog_AnalogSynth_1900x1000::on_selected_lfo_symmetry_dial_changed(int val)
{
	if (active_lfo > _LFO_NONE && active_lfo <= _NUM_OF_LFOS)
	{
		char text[64];

		dial_lfo_symmetry[active_lfo - 1]->blockSignals(true); // 1..6 -> 0..5
		dial_lfo_symmetry[active_lfo - 1]->setValue(val);
		dial_lfo_symmetry[active_lfo - 1]->blockSignals(false);

		sprintf(text, "%i%c", val, '%');
		lineedit_lfo_symmetry[active_lfo - 1]->setText(QString(text));
		ui->lineEdit_LFOsymmetry->setText(QString(text));

		mod_synth_modulator_event_int(_LFO_1_EVENT + active_lfo - 1, _MOD_LFO_SYMMETRY, val);

		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
	}
}

void Dialog_AnalogSynth_1900x1000::on_selected_lfo_waveform_combo_changed(int val)
{
	combo_lfo_waveform[active_lfo - 1]->blockSignals(true);
	combo_lfo_waveform[active_lfo - 1]->setCurrentIndex(val);
	combo_lfo_waveform[active_lfo - 1]->blockSignals(false);

	mod_synth_modulator_event_int(_LFO_1_EVENT, _MOD_LFO_WAVEFORM, val);

	active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
	active_lfo_widget_showing = true;
}

void Dialog_AnalogSynth_1900x1000::on_LFO_frame_close_button_clicked()
{
	// Close the LFO frame
	ui->frame_LFO->hide();
}
