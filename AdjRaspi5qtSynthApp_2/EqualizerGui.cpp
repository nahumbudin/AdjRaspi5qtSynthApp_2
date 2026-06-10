/**
 * @file		EqualizerGui.cpp
 *	@author		Nahum Budin
 *	@date		17-Feb-2026
 *	@version	2.0
 *
 *	@brief		Analog Synthesizer instrument Graphic Eqalizer GUI handling
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

int Dialog_AnalogSynth_1900x1000::init_equalizer_gui()
{
	int result;

	result = init_vertical_slider_control_colors(ui->verticalSlider_BandEquilizer31);
	result = init_vertical_slider_control_colors(ui->verticalSlider_BandEquilizer62);
	result = init_vertical_slider_control_colors(ui->verticalSlider_BandEquilizer125);
	result = init_vertical_slider_control_colors(ui->verticalSlider_BandEquilizer250);
	result = init_vertical_slider_control_colors(ui->verticalSlider_BandEquilizer500);
	result = init_vertical_slider_control_colors(ui->verticalSlider_BandEquilizer1K);
	result = init_vertical_slider_control_colors(ui->verticalSlider_BandEquilizer2K);
	result = init_vertical_slider_control_colors(ui->verticalSlider_BandEquilizer4K);
	result = init_vertical_slider_control_colors(ui->verticalSlider_BandEquilizer8K);
	result = init_vertical_slider_control_colors(ui->verticalSlider_BandEquilizer16K);

	result = init_combobox_control_colors(ui->comboBox_BandEquilizerPreset);
	ui->comboBox_BandEquilizerPreset->setTextAlignment(Qt::AlignCenter);

	//result = init_button_control_colors(ui->pushButton_EquilizerSetAllZero);

	set_equalizer_signals_connections();
	equalizer_update();
	
	
	return 0;
}

void Dialog_AnalogSynth_1900x1000::set_equalizer_signals_connections()
{
	connect(ui->verticalSlider_BandEquilizer31,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band31_slider_changed(int)));

	connect(ui->verticalSlider_BandEquilizer62,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band62_slider_changed(int)));

	connect(ui->verticalSlider_BandEquilizer125,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band125_slider_changed(int)));

	connect(ui->verticalSlider_BandEquilizer250,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band250_slider_changed(int)));

	connect(ui->verticalSlider_BandEquilizer500,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band500_slider_changed(int)));

	connect(ui->verticalSlider_BandEquilizer1K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band1K_slider_changed(int)));

	connect(ui->verticalSlider_BandEquilizer2K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band2K_slider_changed(int)));

	connect(ui->verticalSlider_BandEquilizer4K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band4K_slider_changed(int)));

	connect(ui->verticalSlider_BandEquilizer8K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band8k_slider_changed(int)));

	connect(ui->verticalSlider_BandEquilizer16K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band16K_slider_changed(int)));

	connect(ui->spinBox_BandEquilizer31,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band31_spinbox_changed(int)));

	connect(ui->spinBox_BandEquilizer62,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band62_spinbox_changed(int)));
	
	connect(ui->spinBox_BandEquilizer125,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band125_spinbox_changed(int)));
	
	connect(ui->spinBox_BandEquilizer250,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band250_spinbox_changed(int)));

	connect(ui->spinBox_BandEquilizer500,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band500_spinbox_changed(int)));

	connect(ui->spinBox_BandEquilizer1K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band1K_spinbox_changed(int)));

	connect(ui->spinBox_BandEquilizer2K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band2K_spinbox_changed(int)));

	connect(ui->spinBox_BandEquilizer4K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band4k_spinbox_changed(int)));

	connect(ui->spinBox_BandEquilizer8K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band8k_spinbox_changed(int)));

	connect(ui->spinBox_BandEquilizer16K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band16k_spinbox_changed(int)));

	connect(ui->comboBox_BandEquilizerPreset,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_band_equilizer_band_preset_changed(int)));

	connect(ui->pushButton_EquilizerSetAllZero,
			SIGNAL(clicked(bool)),
			this,
			SLOT(on_band_equilizer_set_all_zero_licked(bool)));
}

void Dialog_AnalogSynth_1900x1000::equalizer_update()
{
	// Don't update if dialog is not visible
	if (!isVisible())
	{
		return;
	}
	
	ui->verticalSlider_BandEquilizer31->blockSignals(true);
	ui->verticalSlider_BandEquilizer31->setValue(mod_synth_get_active_equilizer_band31_level() + 20); // -20 ... +20 -> 0 .. 40
	ui->verticalSlider_BandEquilizer31->blockSignals(false);

	ui->verticalSlider_BandEquilizer62->blockSignals(true);
	ui->verticalSlider_BandEquilizer62->setValue(mod_synth_get_active_equilizer_band62_level() + 20);
	ui->verticalSlider_BandEquilizer62->blockSignals(false);

	ui->verticalSlider_BandEquilizer125->blockSignals(true);
	ui->verticalSlider_BandEquilizer125->setValue(mod_synth_get_active_equilizer_band125_level() + 20);
	ui->verticalSlider_BandEquilizer125->blockSignals(false);

	ui->verticalSlider_BandEquilizer250->blockSignals(true);
	ui->verticalSlider_BandEquilizer250->setValue(mod_synth_get_active_equilizer_band250_level() + 20);
	ui->verticalSlider_BandEquilizer250->blockSignals(false);

	ui->verticalSlider_BandEquilizer500->blockSignals(true);
	ui->verticalSlider_BandEquilizer500->setValue(mod_synth_get_active_equilizer_band500_level() + 20);
	ui->verticalSlider_BandEquilizer500->blockSignals(false);

	ui->verticalSlider_BandEquilizer1K->blockSignals(true);
	ui->verticalSlider_BandEquilizer1K->setValue(mod_synth_get_active_equilizer_band1k_level() + 20);
	ui->verticalSlider_BandEquilizer1K->blockSignals(false);

	ui->verticalSlider_BandEquilizer2K->blockSignals(true);
	ui->verticalSlider_BandEquilizer2K->setValue(mod_synth_get_active_equilizer_band2k_level() + 20);
	ui->verticalSlider_BandEquilizer2K->blockSignals(false);

	ui->verticalSlider_BandEquilizer4K->blockSignals(true);
	ui->verticalSlider_BandEquilizer4K->setValue(mod_synth_get_active_equilizer_band4k_level() + 20);
	ui->verticalSlider_BandEquilizer4K->blockSignals(false);

	ui->verticalSlider_BandEquilizer8K->blockSignals(true);
	ui->verticalSlider_BandEquilizer8K->setValue(mod_synth_get_active_equilizer_band8k_level() + 20);
	ui->verticalSlider_BandEquilizer8K->blockSignals(false);

	ui->verticalSlider_BandEquilizer16K->blockSignals(true);
	ui->verticalSlider_BandEquilizer16K->setValue(mod_synth_get_active_equilizer_band16k_level() + 20);
	ui->verticalSlider_BandEquilizer16K->blockSignals(false);

	ui->comboBox_BandEquilizerPreset->blockSignals(true);
	ui->comboBox_BandEquilizerPreset->setCurrentIndex(mod_synth_get_active_equilizer_preset());
	ui->comboBox_BandEquilizerPreset->blockSignals(false);
}

void Dialog_AnalogSynth_1900x1000::init_equalizer_combboxes_and_labels()
{
	// TODO: add the preset names to the preset combo box
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band31_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer31->blockSignals(true);
	ui->verticalSlider_BandEquilizer31->setValue(val);
	ui->verticalSlider_BandEquilizer31->blockSignals(false);

	ui->spinBox_BandEquilizer31->blockSignals(true);
	ui->spinBox_BandEquilizer31->setValue(val - 20);
	ui->spinBox_BandEquilizer31->blockSignals(false);

	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_31_LEVEL, val - 20); // 0..40 -> -20..+20db

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band62_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer62->blockSignals(true);
	ui->verticalSlider_BandEquilizer62->setValue(val);
	ui->verticalSlider_BandEquilizer62->blockSignals(false);

	ui->spinBox_BandEquilizer62->blockSignals(true);
	ui->spinBox_BandEquilizer62->setValue(val - 20);
	ui->spinBox_BandEquilizer62->blockSignals(false);

	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_62_LEVEL, val - 20); // 0..40 -> -20..+20db

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band125_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer125->blockSignals(true);
	ui->verticalSlider_BandEquilizer125->setValue(val);
	ui->verticalSlider_BandEquilizer125->blockSignals(false);
	
	ui->spinBox_BandEquilizer125->blockSignals(true);
	ui->spinBox_BandEquilizer125->setValue(val - 20);
	ui->spinBox_BandEquilizer125->blockSignals(false);
	
	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_125_LEVEL, val - 20); // 0..40 -> -20..+20db
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band250_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer250->blockSignals(true);
	ui->verticalSlider_BandEquilizer250->setValue(val);
	ui->verticalSlider_BandEquilizer250->blockSignals(false);
	
	ui->spinBox_BandEquilizer250->blockSignals(true);
	ui->spinBox_BandEquilizer250->setValue(val - 20);
	ui->spinBox_BandEquilizer250->blockSignals(false);
	
	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_250_LEVEL, val - 20); // 0..40 -> -20..+20db
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band500_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer500->blockSignals(true);
	ui->verticalSlider_BandEquilizer500->setValue(val);
	ui->verticalSlider_BandEquilizer500->blockSignals(false);
	
	ui->spinBox_BandEquilizer500->blockSignals(true);
	ui->spinBox_BandEquilizer500->setValue(val - 20);
	ui->spinBox_BandEquilizer500->blockSignals(false);
	
	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_500_LEVEL, val - 20); // 0..40 -> -20..+20db
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band1K_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer1K->blockSignals(true);
	ui->verticalSlider_BandEquilizer1K->setValue(val);
	ui->verticalSlider_BandEquilizer1K->blockSignals(false);
	
	ui->spinBox_BandEquilizer1K->blockSignals(true);
	ui->spinBox_BandEquilizer1K->setValue(val - 20);
	ui->spinBox_BandEquilizer1K->blockSignals(false);
	
	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_1K_LEVEL, val - 20); // 0..40 -> -20..+20db
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band2K_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer2K->blockSignals(true);
	ui->verticalSlider_BandEquilizer2K->setValue(val);
	ui->verticalSlider_BandEquilizer2K->blockSignals(false);

	ui->spinBox_BandEquilizer2K->blockSignals(true);
	ui->spinBox_BandEquilizer2K->setValue(val - 20);
	ui->spinBox_BandEquilizer2K->blockSignals(false);

	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_2K_LEVEL, val - 20); // 0..40 -> -20..+20db

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band4K_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer4K->blockSignals(true);
	ui->verticalSlider_BandEquilizer4K->setValue(val);
	ui->verticalSlider_BandEquilizer4K->blockSignals(false);

	ui->spinBox_BandEquilizer4K->blockSignals(true);
	ui->spinBox_BandEquilizer4K->setValue(val - 20);
	ui->spinBox_BandEquilizer4K->blockSignals(false);

	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_4K_LEVEL, val - 20); // 0..40 -> -20..+20db

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band8K_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer8K->blockSignals(true);
	ui->verticalSlider_BandEquilizer8K->setValue(val);
	ui->verticalSlider_BandEquilizer8K->blockSignals(false);

	ui->spinBox_BandEquilizer8K->blockSignals(true);
	ui->spinBox_BandEquilizer8K->setValue(val - 20);
	ui->spinBox_BandEquilizer8K->blockSignals(false);

	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_8K_LEVEL, val - 20); // 0..40 -> -20..+20db

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band16K_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer16K->blockSignals(true);
	ui->verticalSlider_BandEquilizer16K->setValue(val);
	ui->verticalSlider_BandEquilizer16K->blockSignals(false);

	ui->spinBox_BandEquilizer16K->blockSignals(true);
	ui->spinBox_BandEquilizer16K->setValue(val - 20);
	ui->spinBox_BandEquilizer16K->blockSignals(false);

	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_16K_LEVEL, val - 20); // 0..40 -> -20..+20db

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band31_spinbox_changed(int val)
{
	on_band_equilizer_band31_slider_changed(val + 20);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band62_spinbox_changed(int val)
{
	on_band_equilizer_band62_slider_changed(val + 20);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band125_spinbox_changed(int val)
{
	on_band_equilizer_band125_slider_changed(val + 20);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band250_spinbox_changed(int val)
{
	on_band_equilizer_band250_slider_changed(val + 20);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band500_spinbox_changed(int val)
{
	on_band_equilizer_band500_slider_changed(val + 20);	
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band1K_spinbox_changed(int val)
{
	on_band_equilizer_band1K_slider_changed(val + 20);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band2K_spinbox_changed(int val)
{
	on_band_equilizer_band2K_slider_changed(val + 20);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band4K_spinbox_changed(int val)
{
	on_band_equilizer_band4K_slider_changed(val + 20);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band8K_spinbox_changed(int val)
{
	on_band_equilizer_band8K_slider_changed(val + 20);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band16K_spinbox_changed(int val)
{
	on_band_equilizer_band16K_slider_changed(val + 20);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_band_preset_changed(int val)
{
	ui->comboBox_BandEquilizerPreset->blockSignals(true);
	ui->comboBox_BandEquilizerPreset->setCurrentIndex(val);
	ui->comboBox_BandEquilizerPreset->blockSignals(false);
	
	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_PRESET, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_band_equilizer_set_all_zero_licked(bool val)
{
	ui->pushButton_EquilizerSetAllZero->blockSignals(true);
	ui->pushButton_EquilizerSetAllZero->setChecked(false);
	ui->pushButton_EquilizerSetAllZero->blockSignals(false);
	
	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_SET_ALL_ZERO, 1);

	equalizer_update();

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
