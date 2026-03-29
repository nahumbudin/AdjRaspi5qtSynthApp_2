/**
 * @file		ADSRgui.cpp
 *	@author		Nahum Budin
 *	@date		6-Jan-2026
 *	@version	2.0
 *
 *	@brief		Analog Synthesizer instrument ADSRs GUI handling
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

int Dialog_AnalogSynth_1900x1000::init_adsrs_gui()
{
	int result;

	set_adsrs_signals_connections();
	adsrs_update();

	// Setup ADSR curves plot
	adsr_curve_max_attack = mod_synth_get_adsr_max_attack_time_sec();
	adsr_curve_max_decay = mod_synth_get_adsr_max_decay_time_sec();
	adsr_curve_max_sustain = 100; //%
	adsr_curve_max_release = mod_synth_get_adsr_max_release_time_sec();

	adsr_plot_length = _ADSR_CURVE_START_POINT + _ADSR_CURVE_SUSTAIN_SEGMENT_LENGTH +
					   (adsr_curve_max_attack + adsr_curve_max_decay +
						adsr_curve_max_release) * _ADSR_CURVE_TIME_MULTIPLIER;
	
	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(2);
	pen.setColor(Qt::white);
	
	ui->widget_ADSRplot->addGraph();
	ui->widget_ADSRplot->graph(0)->setPen(pen);
	ui->widget_ADSRplot->addGraph();

	ui->widget_ADSRplot->xAxis->setVisible(false);
	ui->widget_ADSRplot->xAxis->setTickLabels(true);
	ui->widget_ADSRplot->yAxis->setVisible(false);
	ui->widget_ADSRplot->yAxis->setTickLabels(true);

	ui->widget_ADSRplot->yAxis->setRange(0, _ADSR_CURVE_HEIGHT);
	ui->widget_ADSRplot->xAxis->setRange(0, adsr_plot_length);

	ui->widget_ADSRplot->setMinimumSize(adsr_plot_length, _ADSR_CURVE_HEIGHT);
	ui->widget_ADSRplot->setBackground(QBrush(_CONTROLS_COLOR_BLACK));

	// Initiate first ADSR plot
	update_adsr_plot[_ENV_SELECTED - 1] = true;

	ui->widget_ADSRplot_1->addGraph();
	ui->widget_ADSRplot_1->graph(0)->setPen(pen);
	ui->widget_ADSRplot_1->addGraph();

	ui->widget_ADSRplot_1->xAxis->setVisible(false);
	ui->widget_ADSRplot_1->xAxis->setTickLabels(true);
	ui->widget_ADSRplot_1->yAxis->setVisible(false);
	ui->widget_ADSRplot_1->yAxis->setTickLabels(true);

	ui->widget_ADSRplot_1->yAxis->setRange(0, _ADSR_CURVE_HEIGHT);
	ui->widget_ADSRplot_1->xAxis->setRange(0, adsr_plot_length);
					   
	ui->widget_ADSRplot_1->setMinimumSize(adsr_plot_length, _ADSR_CURVE_HEIGHT);
	ui->widget_ADSRplot_1->setBackground(QBrush(_CONTROLS_COLOR_BLACK));

	// Initiate first ADSR plot action
	update_adsr_plot[_ENV_1 - 1] = true;

	ui->widget_ADSRplot_2->addGraph();
	ui->widget_ADSRplot_2->graph(0)->setPen(pen);
	ui->widget_ADSRplot_2->addGraph();

	ui->widget_ADSRplot_2->xAxis->setVisible(false);
	ui->widget_ADSRplot_2->xAxis->setTickLabels(true);
	ui->widget_ADSRplot_2->yAxis->setVisible(false);
	ui->widget_ADSRplot_2->yAxis->setTickLabels(true);

	ui->widget_ADSRplot_2->yAxis->setRange(0, _ADSR_CURVE_HEIGHT);
	ui->widget_ADSRplot_2->xAxis->setRange(0, adsr_plot_length);

	ui->widget_ADSRplot_2->setMinimumSize(adsr_plot_length, _ADSR_CURVE_HEIGHT);
	ui->widget_ADSRplot_2->setBackground(QBrush(_CONTROLS_COLOR_BLACK));

	update_adsr_plot[_ENV_2 - 1] = true;

	ui->widget_ADSRplot_3->addGraph();
	ui->widget_ADSRplot_3->graph(0)->setPen(pen);
	ui->widget_ADSRplot_3->addGraph();

	ui->widget_ADSRplot_3->xAxis->setVisible(false);
	ui->widget_ADSRplot_3->xAxis->setTickLabels(true);
	ui->widget_ADSRplot_3->yAxis->setVisible(false);
	ui->widget_ADSRplot_3->yAxis->setTickLabels(true);

	ui->widget_ADSRplot_3->yAxis->setRange(0, _ADSR_CURVE_HEIGHT);
	ui->widget_ADSRplot_3->xAxis->setRange(0, adsr_plot_length);

	ui->widget_ADSRplot_3->setMinimumSize(adsr_plot_length, _ADSR_CURVE_HEIGHT);
	ui->widget_ADSRplot_3->setBackground(QBrush(_CONTROLS_COLOR_BLACK));

	update_adsr_plot[_ENV_3 - 1] = true;

	ui->widget_ADSRplot_4->addGraph();
	ui->widget_ADSRplot_4->graph(0)->setPen(pen);
	ui->widget_ADSRplot_4->addGraph();

	ui->widget_ADSRplot_4->xAxis->setVisible(false);
	ui->widget_ADSRplot_4->xAxis->setTickLabels(true);
	ui->widget_ADSRplot_4->yAxis->setVisible(false);
	ui->widget_ADSRplot_4->yAxis->setTickLabels(true);
	
	ui->widget_ADSRplot_4->yAxis->setRange(0, _ADSR_CURVE_HEIGHT);
	ui->widget_ADSRplot_4->xAxis->setRange(0, adsr_plot_length);
	
	ui->widget_ADSRplot_4->setMinimumSize(adsr_plot_length, _ADSR_CURVE_HEIGHT);
	ui->widget_ADSRplot_4->setBackground(QBrush(_CONTROLS_COLOR_BLACK));

	update_adsr_plot[_ENV_4 - 1] = true;

	ui->widget_ADSRplot_5->addGraph();
	ui->widget_ADSRplot_5->graph(0)->setPen(pen);
	ui->widget_ADSRplot_5->addGraph();

	ui->widget_ADSRplot_5->xAxis->setVisible(false);
	ui->widget_ADSRplot_5->xAxis->setTickLabels(true);
	ui->widget_ADSRplot_5->yAxis->setVisible(false);
	ui->widget_ADSRplot_5->yAxis->setTickLabels(true);

	ui->widget_ADSRplot_5->yAxis->setRange(0, _ADSR_CURVE_HEIGHT);
	ui->widget_ADSRplot_5->xAxis->setRange(0, adsr_plot_length);

	ui->widget_ADSRplot_5->setMinimumSize(adsr_plot_length, _ADSR_CURVE_HEIGHT);
	ui->widget_ADSRplot_5->setBackground(QBrush(_CONTROLS_COLOR_BLACK));

	update_adsr_plot[_ENV_5 - 1] = true;

	ui->widget_ADSRplot_6->addGraph();
	ui->widget_ADSRplot_6->graph(0)->setPen(pen);
	ui->widget_ADSRplot_6->addGraph();

	ui->widget_ADSRplot_6->xAxis->setVisible(false);
	ui->widget_ADSRplot_6->xAxis->setTickLabels(true);
	ui->widget_ADSRplot_6->yAxis->setVisible(false);
	ui->widget_ADSRplot_6->yAxis->setTickLabels(true);

	ui->widget_ADSRplot_6->yAxis->setRange(0, _ADSR_CURVE_HEIGHT);
	ui->widget_ADSRplot_6->xAxis->setRange(0, adsr_plot_length);

	ui->widget_ADSRplot_6->setMinimumSize(adsr_plot_length, _ADSR_CURVE_HEIGHT);
	ui->widget_ADSRplot_6->setBackground(QBrush(_CONTROLS_COLOR_BLACK));

	update_adsr_plot[_ENV_6 - 1] = true;

	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrA_1);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrD_1);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrS_1);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrR_1);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrA_2);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrD_2);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrS_2);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrR_2);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrA_3);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrD_3);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrS_3);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrR_3);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrA_4);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrD_4);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrS_4);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrR_4);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrA_5);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrD_5);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrS_5);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrR_5);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrA_6);
	result = init_vertical_slider_control_colors(ui->verticalSlider_AdsrD_6);
	result - init_vertical_slider_control_colors(ui->verticalSlider_AdsrS_6);
	result - init_vertical_slider_control_colors(ui->verticalSlider_AdsrR_6);


	

	return 0;
}

void Dialog_AnalogSynth_1900x1000::set_adsrs_signals_connections()
{
	connect(ui->verticalSlider_AdsrA_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr1_attack_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrD_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr1_decay_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrS_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr1_sustain_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrR_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr1_release_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrA_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr2_attack_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrD_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr2_decay_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrS_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr2_sustain_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrR_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr2_release_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrA_3,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr3_attack_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrD_3,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr3_decay_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrS_3,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr3_sustain_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrR_3,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr3_release_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrA_4,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr4_attack_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrD_4,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr4_decay_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrS_4,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr4_sustain_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrR_4,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr4_release_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrA_5,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr5_attack_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrD_5,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr5_decay_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrS_5,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr5_sustain_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrR_5,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr5_release_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrA_6,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr6_attack_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrD_6,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr6_decay_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrS_6,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr6_sustain_level_slider_changed(int)));

	connect(ui->verticalSlider_AdsrR_6,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_adsr6_release_level_slider_changed(int)));
}

void Dialog_AnalogSynth_1900x1000::adsrs_update()
{
	char text[64];

	ui->verticalSlider_AdsrA_1->blockSignals(true);
	ui->verticalSlider_AdsrA_1->setValue(mod_synth_get_active_env_mod_1_attack());
	ui->verticalSlider_AdsrA_1->blockSignals(false);

	sprintf(text, "%.2fS",
			mod_synth_log_scale_100_float(0.0, mod_synth_get_adsr_max_attack_time_sec(), 10.0,
										  mod_synth_get_active_env_mod_1_attack()));

	ui->lineEdit_AdsrA_1->setText(QString(text));

	ui->verticalSlider_AdsrD_1->blockSignals(true);
	ui->verticalSlider_AdsrD_1->setValue(mod_synth_get_active_env_mod_1_decay());
	ui->verticalSlider_AdsrD_1->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0,
										  mod_synth_get_active_env_mod_1_decay()));

	ui->lineEdit_AdsrD_1->setText(QString(text));

	ui->verticalSlider_AdsrS_1->blockSignals(true);
	ui->verticalSlider_AdsrS_1->setValue(mod_synth_get_active_env_mod_1_sustain());
	ui->verticalSlider_AdsrS_1->blockSignals(false);

	sprintf(text, "%i%c", mod_synth_get_active_env_mod_1_sustain(), '%');
	ui->lineEdit_AdsrS_1->setText(QString(text));

	ui->verticalSlider_AdsrR_1->blockSignals(true);
	ui->verticalSlider_AdsrR_1->setValue(mod_synth_get_active_env_mod_1_release());
	ui->verticalSlider_AdsrR_1->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0,
										  mod_synth_get_active_env_mod_1_release()));

	ui->lineEdit_AdsrR_1->setText(QString(text));

	ui->verticalSlider_AdsrA_2->blockSignals(true);
	ui->verticalSlider_AdsrA_2->setValue(mod_synth_get_active_env_mod_2_attack());
	ui->verticalSlider_AdsrA_2->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0,
										  mod_synth_get_active_env_mod_2_attack()));

	ui->lineEdit_AdsrA_2->setText(QString(text));

	ui->verticalSlider_AdsrD_2->blockSignals(true);
	ui->verticalSlider_AdsrD_2->setValue(mod_synth_get_active_env_mod_2_decay());
	ui->verticalSlider_AdsrD_2->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0,
										  mod_synth_get_active_env_mod_2_decay()));

	ui->lineEdit_AdsrD_2->setText(QString(text));

	ui->verticalSlider_AdsrS_2->blockSignals(true);
	ui->verticalSlider_AdsrS_2->setValue(mod_synth_get_active_env_mod_1_sustain());
	ui->verticalSlider_AdsrS_2->blockSignals(false);

	sprintf(text, "%i%c", mod_synth_get_active_env_mod_2_sustain(), '%');
	ui->lineEdit_AdsrS_2->setText(QString(text));

	ui->verticalSlider_AdsrR_2->blockSignals(true);
	ui->verticalSlider_AdsrR_2->setValue(mod_synth_get_active_env_mod_2_release());
	ui->verticalSlider_AdsrR_2->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0,
										  mod_synth_get_active_env_mod_2_release()));

	ui->lineEdit_AdsrR_2->setText(QString(text));

	ui->verticalSlider_AdsrA_3->blockSignals(true);
	ui->verticalSlider_AdsrA_3->setValue(mod_synth_get_active_env_mod_3_attack());
	ui->verticalSlider_AdsrA_3->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0,
										  mod_synth_get_active_env_mod_3_attack()));

	ui->lineEdit_AdsrA_3->setText(QString(text));

	ui->verticalSlider_AdsrD_3->blockSignals(true);
	ui->verticalSlider_AdsrD_3->setValue(mod_synth_get_active_env_mod_3_decay());
	ui->verticalSlider_AdsrD_3->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0,
										  mod_synth_get_active_env_mod_3_decay()));

	ui->lineEdit_AdsrD_3->setText(QString(text));

	ui->verticalSlider_AdsrS_3->blockSignals(true);
	ui->verticalSlider_AdsrS_3->setValue(mod_synth_get_active_env_mod_3_sustain());
	ui->verticalSlider_AdsrS_3->blockSignals(false);

	sprintf(text, "%i%c", mod_synth_get_active_env_mod_3_sustain(), '%');
	ui->lineEdit_AdsrS_3->setText(QString(text));

	ui->verticalSlider_AdsrR_3->blockSignals(true);
	ui->verticalSlider_AdsrR_3->setValue(mod_synth_get_active_env_mod_3_release());
	ui->verticalSlider_AdsrR_3->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0,
										  mod_synth_get_active_env_mod_3_release()));

	ui->lineEdit_AdsrR_3->setText(QString(text));

	ui->verticalSlider_AdsrA_4->blockSignals(true);
	ui->verticalSlider_AdsrA_4->setValue(mod_synth_get_active_env_mod_4_attack());
	ui->verticalSlider_AdsrA_4->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0,
										  mod_synth_get_active_env_mod_4_attack()));

	ui->lineEdit_AdsrA_4->setText(QString(text));

	ui->verticalSlider_AdsrD_4->blockSignals(true);
	ui->verticalSlider_AdsrD_4->setValue(mod_synth_get_active_env_mod_4_decay());
	ui->verticalSlider_AdsrD_4->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0,
										  mod_synth_get_active_env_mod_4_decay()));

	ui->lineEdit_AdsrD_4->setText(QString(text));

	ui->verticalSlider_AdsrS_4->blockSignals(true);
	ui->verticalSlider_AdsrS_4->setValue(mod_synth_get_active_env_mod_4_sustain());
	ui->verticalSlider_AdsrS_4->blockSignals(false);

	sprintf(text, "%i%c", mod_synth_get_active_env_mod_4_sustain(), '%');
	ui->lineEdit_AdsrS_4->setText(QString(text));

	ui->verticalSlider_AdsrR_4->blockSignals(true);
	ui->verticalSlider_AdsrR_4->setValue(mod_synth_get_active_env_mod_4_release());
	ui->verticalSlider_AdsrR_4->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0,
										  mod_synth_get_active_env_mod_4_release()));

	ui->lineEdit_AdsrR_4->setText(QString(text));

	ui->verticalSlider_AdsrA_5->blockSignals(true);
	ui->verticalSlider_AdsrA_5->setValue(mod_synth_get_active_env_mod_5_attack());
	ui->verticalSlider_AdsrA_5->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0,
										  mod_synth_get_active_env_mod_5_attack()));

	ui->lineEdit_AdsrA_5->setText(QString(text));

	ui->verticalSlider_AdsrD_5->blockSignals(true);
	ui->verticalSlider_AdsrD_5->setValue(mod_synth_get_active_env_mod_5_decay());
	ui->verticalSlider_AdsrD_5->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0,
										  mod_synth_get_active_env_mod_5_decay()));

	ui->lineEdit_AdsrD_5->setText(QString(text));

	ui->verticalSlider_AdsrS_5->blockSignals(true);
	ui->verticalSlider_AdsrS_5->setValue(mod_synth_get_active_env_mod_5_sustain());
	ui->verticalSlider_AdsrS_5->blockSignals(false);

	sprintf(text, "%i%c", mod_synth_get_active_env_mod_5_sustain(), '%');
	ui->lineEdit_AdsrS_5->setText(QString(text));

	ui->verticalSlider_AdsrR_5->blockSignals(true);
	ui->verticalSlider_AdsrR_5->setValue(mod_synth_get_active_env_mod_1_release());
	ui->verticalSlider_AdsrR_5->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0,
										  mod_synth_get_active_env_mod_5_release()));

	ui->lineEdit_AdsrR_5->setText(QString(text));

	ui->verticalSlider_AdsrA_6->blockSignals(true);
	ui->verticalSlider_AdsrA_6->setValue(mod_synth_get_active_env_mod_6_attack());
	ui->verticalSlider_AdsrA_6->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0,
										  mod_synth_get_active_env_mod_6_attack()));

	ui->lineEdit_AdsrA_6->setText(QString(text));

	ui->verticalSlider_AdsrD_6->blockSignals(true);
	ui->verticalSlider_AdsrD_6->setValue(mod_synth_get_active_env_mod_6_decay());
	ui->verticalSlider_AdsrD_6->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0,
										  mod_synth_get_active_env_mod_6_decay()));

	ui->lineEdit_AdsrD_6->setText(QString(text));

	ui->verticalSlider_AdsrS_6->blockSignals(true);
	ui->verticalSlider_AdsrS_6->setValue(mod_synth_get_active_env_mod_6_sustain());
	ui->verticalSlider_AdsrS_6->blockSignals(false);

	sprintf(text, "%i%c", mod_synth_get_active_env_mod_6_sustain(), '%');
	ui->lineEdit_AdsrS_6->setText(QString(text));

	ui->verticalSlider_AdsrR_6->blockSignals(true);
	ui->verticalSlider_AdsrR_6->setValue(mod_synth_get_active_env_mod_6_release());
	ui->verticalSlider_AdsrR_6->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0,
										  mod_synth_get_active_env_mod_6_release()));

	ui->lineEdit_AdsrR_6->setText(QString(text));

	//refresh_adsr_curve_view(ui->widget_ADSRplot); TODO:
}

void Dialog_AnalogSynth_1900x1000::on_adsr1_attack_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrA_1->blockSignals(true);
	ui->verticalSlider_AdsrA_1->setValue(val);
	ui->verticalSlider_AdsrA_1->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0, val));

	ui->lineEdit_AdsrA_1->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_1_EVENT, _MOD_ADSR_ATTACK, val);
	adsr_attack_levels[0] = val;

	last_modified_adsr = _ENV_1; TODO:
	update_adsr_plot[_ENV_1 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr1_decay_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrD_1->blockSignals(true);
	ui->verticalSlider_AdsrD_1->setValue(val);
	ui->verticalSlider_AdsrD_1->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0, val));

	ui->lineEdit_AdsrD_1->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_1_EVENT, _MOD_ADSR_DECAY, val);
	adsr_decay_levels[0] = val;

	last_modified_adsr = _ENV_1;
	update_adsr_plot[_ENV_1 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr1_sustain_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrS_1->blockSignals(true);
	ui->verticalSlider_AdsrS_1->setValue(val);
	ui->verticalSlider_AdsrS_1->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_AdsrS_1->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_1_EVENT, _MOD_ADSR_SUSTAIN, val);
	adsr_sustain_levels[0] = val;

	last_modified_adsr = _ENV_1;
	update_adsr_plot[_ENV_1 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr1_release_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrR_1->blockSignals(true);
	ui->verticalSlider_AdsrR_1->setValue(val);
	ui->verticalSlider_AdsrR_1->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0, val));

	ui->lineEdit_AdsrR_1->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_1_EVENT, _MOD_ADSR_RELEASE, val);
	adsr_release_levels[0] = val;

	last_modified_adsr = _ENV_1;
	update_adsr_plot[_ENV_1 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr2_attack_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrA_2->blockSignals(true);
	ui->verticalSlider_AdsrA_2->setValue(val);
	ui->verticalSlider_AdsrA_2->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0, val));

	ui->lineEdit_AdsrA_2->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_2_EVENT, _MOD_ADSR_ATTACK, val);
	adsr_attack_levels[1] = val;

	last_modified_adsr = _ENV_2	; TODO:
	update_adsr_plot[_ENV_2 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr2_decay_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrD_2->blockSignals(true);
	ui->verticalSlider_AdsrD_2->setValue(val);
	ui->verticalSlider_AdsrD_2->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0, val));

	ui->lineEdit_AdsrD_2->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_2_EVENT, _MOD_ADSR_DECAY, val);
	adsr_decay_levels[1] = val;

	last_modified_adsr = _ENV_2;
	update_adsr_plot[_ENV_2 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr2_sustain_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrS_2->blockSignals(true);
	ui->verticalSlider_AdsrS_2->setValue(val);
	ui->verticalSlider_AdsrS_2->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_AdsrS_2->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_2_EVENT, _MOD_ADSR_SUSTAIN, val);
	adsr_sustain_levels[1] = val;

	last_modified_adsr = _ENV_2;
	update_adsr_plot[_ENV_2 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr2_release_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrR_2->blockSignals(true);
	ui->verticalSlider_AdsrR_2->setValue(val);
	ui->verticalSlider_AdsrR_2->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0, val));

	ui->lineEdit_AdsrR_2->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_2_EVENT, _MOD_ADSR_RELEASE, val);
	adsr_release_levels[1] = val;

	last_modified_adsr = _ENV_2;
	update_adsr_plot[_ENV_2 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr3_attack_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrA_3->blockSignals(true);
	ui->verticalSlider_AdsrA_3->setValue(val);
	ui->verticalSlider_AdsrA_3->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0, val));

	ui->lineEdit_AdsrA_3->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_3_EVENT, _MOD_ADSR_ATTACK, val);
	adsr_attack_levels[2] = val;

	last_modified_adsr = _ENV_3; TODO:
	update_adsr_plot[_ENV_3 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr3_decay_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrD_3->blockSignals(true);
	ui->verticalSlider_AdsrD_3->setValue(val);
	ui->verticalSlider_AdsrD_3->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0, val));

	ui->lineEdit_AdsrD_3->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_3_EVENT, _MOD_ADSR_DECAY, val);
	adsr_decay_levels[2] = val;

	last_modified_adsr = _ENV_3;
	update_adsr_plot[_ENV_3 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr3_sustain_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrS_3->blockSignals(true);
	ui->verticalSlider_AdsrS_3->setValue(val);
	ui->verticalSlider_AdsrS_3->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_AdsrS_3->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_3_EVENT, _MOD_ADSR_SUSTAIN, val);
	adsr_sustain_levels[2] = val;

	last_modified_adsr = _ENV_3;
	update_adsr_plot[_ENV_3 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr3_release_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrR_3->blockSignals(true);
	ui->verticalSlider_AdsrR_3->setValue(val);
	ui->verticalSlider_AdsrR_3->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0, val));

	ui->lineEdit_AdsrR_3->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_3_EVENT, _MOD_ADSR_RELEASE, val);
	adsr_release_levels[2] = val;

	last_modified_adsr = _ENV_3;
	update_adsr_plot[_ENV_3 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr4_attack_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrA_4->blockSignals(true);
	ui->verticalSlider_AdsrA_4->setValue(val);
	ui->verticalSlider_AdsrA_4->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0, val));

	ui->lineEdit_AdsrA_4->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_4_EVENT, _MOD_ADSR_ATTACK, val);
	adsr_attack_levels[3] = val;

	last_modified_adsr = _ENV_4; TODO:
	update_adsr_plot[_ENV_4 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr4_decay_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrD_4->blockSignals(true);
	ui->verticalSlider_AdsrD_4->setValue(val);
	ui->verticalSlider_AdsrD_4->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0, val));

	ui->lineEdit_AdsrD_4->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_4_EVENT, _MOD_ADSR_DECAY, val);
	adsr_decay_levels[3] = val;

	last_modified_adsr = _ENV_4;
	update_adsr_plot[_ENV_4 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr4_sustain_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrS_4->blockSignals(true);
	ui->verticalSlider_AdsrS_4->setValue(val);
	ui->verticalSlider_AdsrS_4->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_AdsrS_4->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_4_EVENT, _MOD_ADSR_SUSTAIN, val);
	adsr_sustain_levels[3] = val;

	last_modified_adsr = _ENV_4;
	update_adsr_plot[_ENV_4 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr4_release_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrR_4->blockSignals(true);
	ui->verticalSlider_AdsrR_4->setValue(val);
	ui->verticalSlider_AdsrR_4->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0, val));

	ui->lineEdit_AdsrR_4->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_4_EVENT, _MOD_ADSR_RELEASE, val);
	adsr_release_levels[3] = val;

	last_modified_adsr = _ENV_4;
	update_adsr_plot[_ENV_4 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr5_attack_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrA_5->blockSignals(true);
	ui->verticalSlider_AdsrA_5->setValue(val);
	ui->verticalSlider_AdsrA_5->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0, val));

	ui->lineEdit_AdsrA_5->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_5_EVENT, _MOD_ADSR_ATTACK, val);
	adsr_attack_levels[4] = val;

	last_modified_adsr = _ENV_5; TODO:
	update_adsr_plot[_ENV_5 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr5_decay_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrD_5->blockSignals(true);
	ui->verticalSlider_AdsrD_5->setValue(val);
	ui->verticalSlider_AdsrD_5->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0, val));

	ui->lineEdit_AdsrD_5->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_5_EVENT, _MOD_ADSR_DECAY, val);
	adsr_decay_levels[4] = val;

	last_modified_adsr = _ENV_5;
	update_adsr_plot[_ENV_5 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr5_sustain_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrS_5->blockSignals(true);
	ui->verticalSlider_AdsrS_5->setValue(val);
	ui->verticalSlider_AdsrS_5->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_AdsrS_5->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_5_EVENT, _MOD_ADSR_SUSTAIN, val);
	adsr_sustain_levels[4] = val;

	last_modified_adsr = _ENV_5;
	update_adsr_plot[_ENV_5 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr5_release_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrR_5->blockSignals(true);
	ui->verticalSlider_AdsrR_5->setValue(val);
	ui->verticalSlider_AdsrR_5->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0, val));

	ui->lineEdit_AdsrR_5->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_5_EVENT, _MOD_ADSR_RELEASE, val);
	adsr_release_levels[4] = val;

	last_modified_adsr = _ENV_5;
	update_adsr_plot[_ENV_5 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr6_attack_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrA_6->blockSignals(true);
	ui->verticalSlider_AdsrA_6->setValue(val);
	ui->verticalSlider_AdsrA_6->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0, val));

	ui->lineEdit_AdsrA_6->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_6_EVENT, _MOD_ADSR_ATTACK, val);
	adsr_attack_levels[5] = val;

	last_modified_adsr = _ENV_6; TODO:
	update_adsr_plot[_ENV_6 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr6_decay_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrD_6->blockSignals(true);
	ui->verticalSlider_AdsrD_6->setValue(val);
	ui->verticalSlider_AdsrD_6->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0, val));

	ui->lineEdit_AdsrD_6->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_6_EVENT, _MOD_ADSR_DECAY, val);
	adsr_decay_levels[5] = val;

	last_modified_adsr = _ENV_6;
	update_adsr_plot[_ENV_6 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr6_sustain_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrS_6->blockSignals(true);
	ui->verticalSlider_AdsrS_6->setValue(val);
	ui->verticalSlider_AdsrS_6->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_AdsrS_6->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_6_EVENT, _MOD_ADSR_SUSTAIN, val);
	adsr_sustain_levels[5] = val;

	last_modified_adsr = _ENV_6;
	update_adsr_plot[_ENV_6 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::on_adsr6_release_level_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_AdsrR_6->blockSignals(true);
	ui->verticalSlider_AdsrR_6->setValue(val);
	ui->verticalSlider_AdsrR_6->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0, val));

	ui->lineEdit_AdsrR_6->setText(QString(text));

	mod_synth_modulator_event_int(_ENV_6_EVENT, _MOD_ADSR_RELEASE, val);
	adsr_release_levels[5] = val;

	last_modified_adsr = _ENV_6;
	update_adsr_plot[_ENV_6 - 1] = true;
}

void Dialog_AnalogSynth_1900x1000::show_active_adsr_widget(bool show)
{
	active_adsr_widget_showing = show;

	if (show)
	{
		update_active_adsr_frame();
	}
	else
	{
		ui->frame_ADSR->hide();
	}
}

void Dialog_AnalogSynth_1900x1000::init_active_adsr_widget()
{
}

void Dialog_AnalogSynth_1900x1000::update_active_adsr_frame()
{
	char text[64];

	// Update ADSR frame controls according to active ADSR values
	switch (active_adsr)
	{
	case _ENV_1:
		active_adsr_attack = mod_synth_get_active_env_mod_1_attack();
		active_adsr_decay = mod_synth_get_active_env_mod_1_decay();
		active_adsr_sustain = mod_synth_get_active_env_mod_1_sustain();
		active_adsr_release = mod_synth_get_active_env_mod_1_release();
		break;

	case _ENV_2:
		active_adsr_attack = mod_synth_get_active_env_mod_2_attack();
		active_adsr_decay = mod_synth_get_active_env_mod_2_decay();
		active_adsr_sustain = mod_synth_get_active_env_mod_2_sustain();
		active_adsr_release = mod_synth_get_active_env_mod_2_release();
		break;

	case _ENV_3:
		active_adsr_attack = mod_synth_get_active_env_mod_3_attack();
		active_adsr_decay = mod_synth_get_active_env_mod_3_decay();
		active_adsr_sustain = mod_synth_get_active_env_mod_3_sustain();
		active_adsr_release = mod_synth_get_active_env_mod_3_release();
		break;

	case _ENV_4:
		active_adsr_attack = mod_synth_get_active_env_mod_4_attack();
		active_adsr_decay = mod_synth_get_active_env_mod_4_decay();
		active_adsr_sustain = mod_synth_get_active_env_mod_4_sustain();
		active_adsr_release = mod_synth_get_active_env_mod_4_release();
		break;

	case _ENV_5:
		active_adsr_attack = mod_synth_get_active_env_mod_5_attack();
		active_adsr_decay = mod_synth_get_active_env_mod_5_decay();
		active_adsr_sustain = mod_synth_get_active_env_mod_5_sustain();
		active_adsr_release = mod_synth_get_active_env_mod_5_release();
		break;

	case _ENV_6:
		active_adsr_attack = mod_synth_get_active_env_mod_6_attack();
		active_adsr_decay = mod_synth_get_active_env_mod_6_decay();
		active_adsr_sustain = mod_synth_get_active_env_mod_6_sustain();
		active_adsr_release = mod_synth_get_active_env_mod_6_release();
		break;

	default:
		return;
	}

	ui->verticalSlider_AdsrA->blockSignals(true);
	ui->verticalSlider_AdsrA->setValue(active_adsr_attack);
	ui->verticalSlider_AdsrA->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0, active_adsr_attack));

	ui->lineEdit_AdsrA->setText(QString(text));

	ui->verticalSlider_AdsrD->blockSignals(true);
	ui->verticalSlider_AdsrD->setValue(active_adsr_decay);
	ui->verticalSlider_AdsrD->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0, active_adsr_decay));

	ui->lineEdit_AdsrD->setText(QString(text));

	ui->verticalSlider_AdsrS->blockSignals(true);
	ui->verticalSlider_AdsrS->setValue(active_adsr_sustain);
	ui->verticalSlider_AdsrS->blockSignals(false);

	sprintf(text, "%i%c", active_adsr_sustain, '%');
	ui->lineEdit_AdsrS->setText(QString(text));

	ui->verticalSlider_AdsrR->blockSignals(true);
	ui->verticalSlider_AdsrR->setValue(active_adsr_release);
	ui->verticalSlider_AdsrR->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0, active_adsr_release));

	ui->lineEdit_AdsrR->setText(QString(text));

	// Update plot
}

void Dialog_AnalogSynth_1900x1000::set_adsr_plot_widget_points(int env_id)
{
	const int max_param_value = 100;

	switch (env_id)
	{
	case _ENV_1:
		adsr_view_widget_attack = mod_synth_get_active_env_mod_1_attack();
		adsr_view_widget_decay = mod_synth_get_active_env_mod_1_decay();
		adsr_view_widget_sustain = mod_synth_get_active_env_mod_1_sustain();
		adsr_view_widget_release = mod_synth_get_active_env_mod_1_release();
		break;

	case _ENV_2:
		adsr_view_widget_attack = mod_synth_get_active_env_mod_2_attack();
		adsr_view_widget_decay = mod_synth_get_active_env_mod_2_decay();
		adsr_view_widget_sustain = mod_synth_get_active_env_mod_2_sustain();
		adsr_view_widget_release = mod_synth_get_active_env_mod_2_release();
		break;

	case _ENV_3:
		adsr_view_widget_attack = mod_synth_get_active_env_mod_3_attack();
		adsr_view_widget_decay = mod_synth_get_active_env_mod_3_decay();
		adsr_view_widget_sustain = mod_synth_get_active_env_mod_3_sustain();
		adsr_view_widget_release = mod_synth_get_active_env_mod_3_release();
		;
		break;

	case _ENV_4:
		adsr_view_widget_attack = mod_synth_get_active_env_mod_4_attack();
		adsr_view_widget_decay = mod_synth_get_active_env_mod_4_decay();
		adsr_view_widget_sustain = mod_synth_get_active_env_mod_4_sustain();
		adsr_view_widget_release = mod_synth_get_active_env_mod_4_release();
		break;

	case _ENV_5:
		adsr_view_widget_attack = mod_synth_get_active_env_mod_5_attack();
		adsr_view_widget_decay = mod_synth_get_active_env_mod_5_decay();
		adsr_view_widget_sustain = mod_synth_get_active_env_mod_5_sustain();
		adsr_view_widget_release = mod_synth_get_active_env_mod_5_release();
		break;

	case _ENV_6:
		adsr_view_widget_attack = mod_synth_get_active_env_mod_6_attack();
		adsr_view_widget_decay = mod_synth_get_active_env_mod_6_decay();
		adsr_view_widget_sustain = mod_synth_get_active_env_mod_6_sustain();
		adsr_view_widget_release = mod_synth_get_active_env_mod_6_release();
		break;

	default:
		return;
	}

	adsr_view_widget_attack = mod_synth_log_scale_100_int(0, max_param_value, 10, adsr_view_widget_attack);
	adsr_view_widget_decay = mod_synth_log_scale_100_int(0, max_param_value, 10, adsr_view_widget_decay);
	adsr_view_widget_release = mod_synth_log_scale_100_int(0, max_param_value, 10, adsr_view_widget_release);

	adsr_curve_attack_end_point =
		_ADSR_CURVE_START_POINT + 1 +
		((adsr_view_widget_attack * adsr_curve_max_attack * _ADSR_CURVE_TIME_MULTIPLIER) /
		 max_param_value);

	adsr_curve_decay_end_point =
		adsr_curve_attack_end_point + 1 +
		((adsr_view_widget_decay * adsr_curve_max_decay * _ADSR_CURVE_TIME_MULTIPLIER) /
		 max_param_value);

	adsr_curve_sustain_end_point =
		adsr_curve_decay_end_point + 1 +
		_ADSR_CURVE_SUSTAIN_SEGMENT_LENGTH;

	adsr_curve_release_end_point =
		adsr_curve_sustain_end_point + 1 +
		((adsr_view_widget_release * adsr_curve_max_release *
		  _ADSR_CURVE_TIME_MULTIPLIER) /
		 max_param_value);
}

void Dialog_AnalogSynth_1900x1000::refresh_adsr_curve_view(QCustomPlot *adsr_plot)
{
	if (adsr_plot != NULL)
	{
		QVector<double> x(8), y(8);

		x[0] = 0;
		y[0] = 0;

		x[1] = _ADSR_CURVE_START_POINT;
		y[1] = 0;

		x[2] = adsr_curve_attack_end_point;
		y[2] = _ADSR_CURVE_HEIGHT;

		x[3] = adsr_curve_decay_end_point;
		y[3] = adsr_view_widget_sustain * _ADSR_CURVE_HEIGHT / 100;

		x[4] = adsr_curve_sustain_end_point;
		y[4] = adsr_view_widget_sustain * _ADSR_CURVE_HEIGHT / 100;

		x[5] = adsr_curve_release_end_point;
		y[5] = 0;

		x[6] = adsr_plot_length;
		y[6] = 0;

		adsr_plot->graph(0)->setData(x, y);
		adsr_plot->xAxis->setRange(0, adsr_plot_length);

		adsr_plot->replot();
	}
}

// Selected ADSR Frame slider changed
void Dialog_AnalogSynth_1900x1000::on_selected_adsr_attack_slider_changed(int val)
{
	if ((active_adsr > _ENV_NONE) && (active_adsr <= _NUM_OF_ADSRS)) // 1..6
	{
		char text[64];

		vertical_sliders_adsr_attack[active_adsr - 1]->blockSignals(true); // 1..6 -> 0..5
		vertical_sliders_adsr_attack[active_adsr - 1]->setValue(val);
		vertical_sliders_adsr_attack[active_adsr - 1]->blockSignals(false);

		sprintf(text,
				"%.2fS",
				mod_synth_log_scale_100_float(0.0,
											  mod_synth_get_adsr_max_attack_time_sec(),
											  10.0, val));

		lineedits_adsr_attack[active_adsr - 1]->setText(QString(text));
		ui->lineEdit_AdsrA->setText(QString(text));

		mod_synth_modulator_event_int(_ENV_1_EVENT + active_adsr - 1, _MOD_ADSR_ATTACK, val);
		adsr_attack_levels[active_adsr - 1] = val;

		last_modified_adsr = _ENV_SELECTED;
		update_adsr_plot[_ENV_SELECTED - 1] = true;
		update_adsr_plot[active_adsr - 1] = true;

		active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_adsr_widget_showing = true;
	}
}

void Dialog_AnalogSynth_1900x1000::on_selected_adsr_decay_slider_changed(int val)
{
	if ((active_adsr > _ENV_NONE) && (active_adsr <= _NUM_OF_ADSRS)) // 1..6
	{
		char text[64];

		vertical_sliders_adsr_decay[active_adsr - 1]->blockSignals(true); // 1..6 -> 0..5
		vertical_sliders_adsr_decay[active_adsr - 1]->setValue(val);
		vertical_sliders_adsr_decay[active_adsr - 1]->blockSignals(false);

		sprintf(text,
				"%.2fS",
				mod_synth_log_scale_100_float(0.0,
											  mod_synth_get_adsr_max_decay_time_sec(),
											  10.0, val));

		lineedits_adsr_decay[active_adsr - 1]->setText(QString(text));
		ui->lineEdit_AdsrD->setText(QString(text));

		mod_synth_modulator_event_int(_ENV_1_EVENT + active_adsr - 1, _MOD_ADSR_DECAY, val);
		adsr_decay_levels[active_adsr - 1] = val;

		last_modified_adsr = _ENV_SELECTED;
		update_adsr_plot[_ENV_SELECTED - 1] = true;
		update_adsr_plot[active_adsr - 1] = true;

		active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_adsr_widget_showing = true;
	}
}

void Dialog_AnalogSynth_1900x1000::on_selected_adsr_sustain_slider_changed(int val)
{
	if ((active_adsr > _ENV_NONE) && (active_adsr <= _NUM_OF_ADSRS)) // 1..6
	{
		char text[64];

		vertical_sliders_adsr_sustain[active_adsr - 1]->blockSignals(true);
		vertical_sliders_adsr_sustain[active_adsr - 1]->setValue(val);
		vertical_sliders_adsr_sustain[active_adsr - 1]->blockSignals(false);

		sprintf(text, "%i%c", val, '%');
		lineedits_adsr_sustain[active_adsr - 1]->setText(QString(text));
		ui->lineEdit_AdsrS->setText(QString(text));

		mod_synth_modulator_event_int(_ENV_1_EVENT + active_adsr - 1, _MOD_ADSR_SUSTAIN, val);
		adsr_sustain_levels[active_adsr - 1] = val;

		last_modified_adsr = _ENV_SELECTED;
		update_adsr_plot[_ENV_SELECTED - 1] = true;
		update_adsr_plot[active_adsr - 1] = true;

		active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_adsr_widget_showing = true;
	}
}

void Dialog_AnalogSynth_1900x1000::on_selected_adsr_release_slider_changed(int val)
{

	if ((active_adsr > _ENV_NONE) && (active_adsr <= _NUM_OF_ADSRS)) // 1..6
	{
		char text[64];

		vertical_sliders_adsr_release[active_adsr - 1]->blockSignals(true); // 1..6 -> 0..5
		vertical_sliders_adsr_release[active_adsr - 1]->setValue(val);
		vertical_sliders_adsr_release[active_adsr - 1]->blockSignals(false);

		sprintf(text,
				"%.2fS",
				mod_synth_log_scale_100_float(0.0,
											  mod_synth_get_adsr_max_release_time_sec(),
											  10.0, val));

		lineedits_adsr_release[active_adsr - 1]->setText(QString(text));
		ui->lineEdit_AdsrR->setText(QString(text));

		mod_synth_modulator_event_int(_ENV_1_EVENT + active_adsr - 1, _MOD_ADSR_RELEASE, val);
		adsr_release_levels[active_adsr - 1] = val;

		last_modified_adsr = _ENV_SELECTED;
		update_adsr_plot[_ENV_SELECTED - 1] = true;
		update_adsr_plot[active_adsr - 1] = true;

		active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_adsr_widget_showing = true;
	}
}

void Dialog_AnalogSynth_1900x1000::on_ADSR_frame_close_button_clicked()
{
	// Close the ADSR frame
	ui->frame_ADSR->hide();
}
