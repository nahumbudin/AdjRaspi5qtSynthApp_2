/**
 * @file		DistortionGui.cpp
 *	@author		Nahum Budin
 *	@date		11-Jan-2026
 *	@version	2.0
 *
 *	@brief		Analog Synthesizer instrument Distortion GUI handling
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

int Dialog_AnalogSynth_1900x1000::init_distortion_gui()
{
	int result = -1;

	set_distortion_signals_connections();
	distortion_update();

	result = init_dial_control_colors(ui->dial_DistortionDrive_1);
	result = init_dial_control_colors(ui->dial_DistortionRange_1);
	result = init_dial_control_colors(ui->dial_DistortionBlend_1);
	
	result = init_dial_control_colors(ui->dial_DistortionDrive_2);
	result = init_dial_control_colors(ui->dial_DistortionRange_2);
	result = init_dial_control_colors(ui->dial_DistortionBlend_2);

	return 0;
}

void Dialog_AnalogSynth_1900x1000::set_distortion_signals_connections()
{
	connect(ui->checkBox_Distortion_Active,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_distortion_active_checkbox_Changed(bool)));

	connect(ui->checkBox_DistortionAutoGain,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_distortion_auto_gain_checkbox_Changed(bool)));

	connect(ui->dial_DistortionDrive_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_distortion1_drive_dial_changed(int)));

	connect(ui->dial_DistortionRange_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_distortion1_range_dial_changed(int)));

	connect(ui->dial_DistortionBlend_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_distortion1_blend_dial_changed(int)));

	connect(ui->dial_DistortionDrive_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_distortion2_drive_dial_changed(int)));

	connect(ui->dial_DistortionRange_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_distortion2_range_dial_changed(int)));

	connect(ui->dial_DistortionBlend_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_distortion2_blend_dial_changed(int)));
}

void Dialog_AnalogSynth_1900x1000::distortion_update()
{
	char text[64];

	ui->dial_DistortionDrive_1->blockSignals(true);
	ui->dial_DistortionDrive_1->setValue(mod_synth_get_active_distortion_1_drive());
	ui->dial_DistortionDrive_1->blockSignals(false);

	sprintf(text, "%.2f", (float)mod_synth_get_active_distortion_1_drive() / 100.0f);
	ui->lineEdit_DistortionDrive_1->setText(QString(text));

	ui->dial_DistortionRange_1->blockSignals(true);
	ui->dial_DistortionRange_1->setValue(mod_synth_get_active_distortion_1_range());
	ui->dial_DistortionRange_1->blockSignals(false);

	sprintf(text, "%.0f", (float)mod_synth_get_active_distortion_1_range());
	ui->lineEdit_DistortionRange_1->setText(QString(text));

	ui->dial_DistortionBlend_1->blockSignals(true);
	ui->dial_DistortionBlend_1->setValue(mod_synth_get_active_distortion_1_drive());
	ui->dial_DistortionBlend_1->blockSignals(false);

	sprintf(text, "%.2f", (float)mod_synth_get_active_distortion_1_blend() / 100.0f);
	ui->lineEdit_DistortionBlend_1->setText(QString(text));

	distortion_active = mod_synth_get_active_distortion_enable_state();
	ui->checkBox_Distortion_Active->blockSignals(true);
	ui->checkBox_Distortion_Active->setChecked(distortion_active);
	ui->checkBox_Distortion_Active->blockSignals(false);

	if (distortion_active)
	{
		ui->frame_AnalogSynthProcessing_Distortion->setEnabled(true);
	}
	else
	{
		ui->frame_AnalogSynthProcessing_Distortion->setEnabled(false);
	}

	distortion_auto_gain = mod_synth_get_active_distortion_auto_gain_state();
	ui->checkBox_DistortionAutoGain->blockSignals(true);
	ui->checkBox_DistortionAutoGain->setChecked(distortion_auto_gain);
	ui->checkBox_DistortionAutoGain->blockSignals(false);

	ui->dial_DistortionDrive_2->blockSignals(true);
	ui->dial_DistortionDrive_2->setValue(mod_synth_get_active_distortion_2_drive());
	ui->dial_DistortionDrive_2->blockSignals(false);

	sprintf(text, "%.2f", (float)mod_synth_get_active_distortion_2_drive() / 100.0f);
	ui->lineEdit_DistortionDrive_2->setText(QString(text));

	ui->dial_DistortionRange_2->blockSignals(true);
	ui->dial_DistortionRange_2->setValue(mod_synth_get_active_distortion_2_range());
	ui->dial_DistortionRange_2->blockSignals(false);

	sprintf(text, "%.0f", (float)mod_synth_get_active_distortion_2_range());
	ui->lineEdit_DistortionRange_2->setText(QString(text));

	ui->dial_DistortionBlend_2->blockSignals(true);
	ui->dial_DistortionBlend_2->setValue(mod_synth_get_active_distortion_2_drive());
	ui->dial_DistortionBlend_2->blockSignals(false);

	sprintf(text, "%.2f", (float)mod_synth_get_active_distortion_2_blend() / 100.0f);
	ui->lineEdit_DistortionBlend_2->setText(QString(text));
}

void Dialog_AnalogSynth_1900x1000::on_distortion1_drive_dial_changed(int val)
{
	char text[64];

	ui->dial_DistortionDrive_1->blockSignals(true);
	ui->dial_DistortionDrive_1->setValue(val);
	ui->dial_DistortionDrive_1->blockSignals(false);

	sprintf(text, "%.2f", (float)val / 100.0f);
	ui->lineEdit_DistortionDrive_1->setText(QString(text));

	distortion1_drive = val;

	mod_synth_distortion_event_int(_DISTORTION_1_EVENT, _DISTORTION_DRIVE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_distortion1_range_dial_changed(int val)
{
	char text[64];

	ui->dial_DistortionRange_1->blockSignals(true);
	ui->dial_DistortionRange_1->setValue(val);
	ui->dial_DistortionRange_1->blockSignals(false);

	sprintf(text, "%.0f", (float)val);
	ui->lineEdit_DistortionRange_1->setText(QString(text));

	distortion1_range = val;

	mod_synth_distortion_event_int(_DISTORTION_1_EVENT, _DISTORTION_RANGE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_distortion1_blend_dial_changed(int val)
{
	char text[64];

	ui->dial_DistortionBlend_1->blockSignals(true);
	ui->dial_DistortionBlend_1->setValue(val);
	ui->dial_DistortionBlend_1->blockSignals(false);

	sprintf(text, "%.2f", (float)val / 100.0f);
	ui->lineEdit_DistortionBlend_1->setText(QString(text));

	distortion1_blend = val;

	mod_synth_distortion_event_int(_DISTORTION_1_EVENT, _DISTORTION_BLEND, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_distortion_active_checkbox_Changed(bool val)
{
	ui->checkBox_Distortion_Active->blockSignals(true);
	if (val)
	{
		ui->checkBox_Distortion_Active->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_Distortion_Active->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_Distortion_Active->blockSignals(false);

	distortion_active = val;

	mod_synth_distortion_event_bool(_DISTORTION_1_EVENT, _ENABLE_DISTORTION, val);

	distortion_update();

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_distortion_auto_gain_checkbox_Changed(bool val)
{
	ui->checkBox_DistortionAutoGain->blockSignals(true);
	if (val)
	{
		ui->checkBox_DistortionAutoGain->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_DistortionAutoGain->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_DistortionAutoGain->blockSignals(false);

	distortion_auto_gain = val;

	mod_synth_distortion_event_bool(_DISTORTION_1_EVENT, _DISTORTION_AUTO_GAIN, val);

	distortion_update();

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_distortion2_drive_dial_changed(int val)
{
	char text[64];

	ui->dial_DistortionDrive_2->blockSignals(true);
	ui->dial_DistortionDrive_2->setValue(val);
	ui->dial_DistortionDrive_2->blockSignals(false);

	sprintf(text, "%.2f", (float)val / 100.0f);
	ui->lineEdit_DistortionDrive_2->setText(QString(text));

	distortion2_drive = val;

	mod_synth_distortion_event_int(_DISTORTION_2_EVENT, _DISTORTION_DRIVE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_distortion2_range_dial_changed(int val)
{
	char text[64];

	ui->dial_DistortionRange_2->blockSignals(true);
	ui->dial_DistortionRange_2->setValue(val);
	ui->dial_DistortionRange_2->blockSignals(false);

	sprintf(text, "%.0f", (float)val);
	ui->lineEdit_DistortionRange_2->setText(QString(text));

	distortion2_range = val;

	mod_synth_distortion_event_int(_DISTORTION_2_EVENT, _DISTORTION_RANGE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_distortion2_blend_dial_changed(int val)
{
	char text[64];

	ui->dial_DistortionBlend_2->blockSignals(true);
	ui->dial_DistortionBlend_2->setValue(val);
	ui->dial_DistortionBlend_2->blockSignals(false);

	sprintf(text, "%.2f", (float)val / 100.0f);
	ui->lineEdit_DistortionBlend_2->setText(QString(text));

	distortion2_blend = val;

	mod_synth_distortion_event_int(_DISTORTION_2_EVENT, _DISTORTION_BLEND, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

