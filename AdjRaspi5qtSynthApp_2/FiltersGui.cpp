/**
 * @file		FiltersGui.cpp
 *	@author		Nahum Budin
 *	@date		11-Jan-2026
 *	@version	2.0
 *
 *	@brief		Analog Synthesizer instrument Filters GUI handling
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

int Dialog_AnalogSynth_1900x1000::init_filters_gui()
{
	int result = 0;

	std::array<int, 9> values;

	values[0] = _MOD_SYNTH_EVENT;

	if (string_filters_bands.isEmpty())
	{
		string_filters_bands.append("Low Pass");
		string_filters_bands.append("High Pass");
		string_filters_bands.append("Band Pass");
		//string_filters_bands.append("Notch");
		string_filters_bands.append("All Pass");
	}

	result = init_combobox_control_colors(ui->comboBox_FilterBand_1);

	ui->comboBox_FilterBand_1->blockSignals(true);
	ui->comboBox_FilterBand_1->clear();
	ui->comboBox_FilterBand_1->addItems(string_filters_bands);
	ui->comboBox_FilterBand_1->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_FilterBand_1->blockSignals(false);

	values[1] = _FILTER_1_EVENT;
	values[2] = _FILTER_BAND;
	values[3] = _FILTER_BAND_PASS_ALL;
	values[4] = _FILTER_BAND_LPF;
	values[5] = _FILTER_BAND_PASS_ALL;
	values[6] = _FILTER_BAND_LPF;
	values[7] = _ML_TRAINNING_MODE_FIXED_PARAM; // Default.
	values[8] = _WIDGET_TYPE_COMBOBOX;

	MainWindow::widgets_map_ml_training_info[ui->comboBox_FilterBand_1] = values;

	// Register for click detection
	MainWindow::get_instance()->register_widget_for_click_detection(ui->comboBox_FilterBand_1);

	result = init_combobox_control_colors(ui->comboBox_FilterFreqModAdsr_1);
	
	ui->comboBox_FilterFreqModAdsr_1->blockSignals(true);
	ui->comboBox_FilterFreqModAdsr_1->addItems(string_adsr_values);
	ui->comboBox_FilterFreqModAdsr_1->setIdentifier(_FILTER1_FREQ_MOD_ADSR_COMBOBOX_INDEX);
	ui->comboBox_FilterFreqModAdsr_1->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_FilterFreqModAdsr_1->blockSignals(false);

	values[1] = _FILTER_1_EVENT;
	values[2] = _FILTER_FREQ_MOD_ENV;
	values[3] = _ENV_6;
	values[4] = _ENV_NONE;
	values[5] = _ENV_6;
	values[6] = _ENV_NONE;
	values[7] = _ML_TRAINNING_MODE_FIXED_PARAM; // Default.
	values[8] = _WIDGET_TYPE_COMBOBOX;

	MainWindow::widgets_map_ml_training_info[ui->comboBox_FilterFreqModAdsr_1] = values;

	// Register for click detection
	MainWindow::get_instance()->register_widget_for_click_detection(ui->comboBox_FilterFreqModAdsr_1);

	result = init_combobox_control_colors(ui->comboBox_FilterFreqModLfo_1);

	ui->comboBox_FilterFreqModLfo_1->blockSignals(true);
	ui->comboBox_FilterFreqModLfo_1->addItems(string_lfo_values);
	ui->comboBox_FilterFreqModLfo_1->setIdentifier(_FILTER1_FREQ_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_FilterFreqModLfo_1->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_FilterFreqModLfo_1->blockSignals(false);

	values[1] = _FILTER_1_EVENT;
	values[2] = _FILTER_FREQ_MOD_LFO;
	values[3] = _LFO_6_DELAYED_2000MS;
	values[4] = _LFO_NONE;
	values[5] = _LFO_6_DELAYED_2000MS;
	values[6] = _LFO_NONE;
	values[7] = _ML_TRAINNING_MODE_FIXED_PARAM; // Default.
	values[8] = _WIDGET_TYPE_COMBOBOX;

	MainWindow::widgets_map_ml_training_info[ui->comboBox_FilterFreqModLfo_1] = values;

	// Register for click detection
	MainWindow::get_instance()->register_widget_for_click_detection(ui->comboBox_FilterFreqModLfo_1);

	result = init_vertical_slider_control_colors(ui->verticalSlider_FilterFreqModLfoLevel_1);

	values[1] = _FILTER_1_EVENT;
	values[2] = _FILTER_FREQ_MOD_LFO_LEVEL;
	values[3] = 100;
	values[4] = 0;
	values[5] = 100;
	values[6] = 0;
	values[7] = _ML_TRAINNING_MODE_FIXED_PARAM; // Default.
	values[8] = _WIDGET_TYPE_SLIDER;

	MainWindow::widgets_map_ml_training_info[ui->comboBox_FilterFreqModLfo_1] = values;

	// Register for click detection
	MainWindow::get_instance()->register_widget_for_click_detection(ui->verticalSlider_FilterFreqModLfoLevel_1);
	
	result = init_vertical_slider_control_colors(ui->verticalSlider_FilterFreqModAdsrLevel_1);

	values[1] = _FILTER_1_EVENT;
	values[2] = _FILTER_FREQ_MOD_ENV_LEVEL;
	values[3] = 100;
	values[4] = 0;
	values[5] = 100;
	values[6] = 0;
	values[7] = _ML_TRAINNING_MODE_FIXED_PARAM; // Default.
	values[8] = _WIDGET_TYPE_SLIDER;

	MainWindow::widgets_map_ml_training_info[ui->verticalSlider_FilterFreqModAdsrLevel_1] = values;

	// Register for click detection
	MainWindow::get_instance()->register_widget_for_click_detection(ui->verticalSlider_FilterFreqModAdsrLevel_1);

	
	result = init_dial_control_colors(ui->dial_FilterFreq_1);

	values[1] = _FILTER_1_EVENT;
	values[2] = _FILTER_FREQ;
	values[3] = 100; // To be normlized to actual filter frequency range.
	values[4] = 0;
	values[5] = 100;
	values[6] = 0;
	values[7] = _ML_TRAINNING_MODE_FIXED_PARAM; // Default.
	values[8] = _WIDGET_TYPE_DIAL;

	MainWindow::widgets_map_ml_training_info[ui->dial_FilterFreq_1] = values;

	// Register for click detection
	MainWindow::get_instance()->register_widget_for_click_detection(ui->dial_FilterFreq_1);
	
	result = init_dial_control_colors(ui->dial_FilterOctave_1);

	values[1] = _FILTER_1_EVENT;
	values[2] = _FILTER_OCT;
	values[3] = 100; // To be normlized to actual filter modulation octave range.
	values[4] = 0;
	values[5] = 100;
	values[6] = 0;
	values[7] = _ML_TRAINNING_MODE_FIXED_PARAM; // Default.
	values[8] = _WIDGET_TYPE_DIAL;

	MainWindow::widgets_map_ml_training_info[ui->dial_FilterOctave_1] = values;

	// Register for click detection
	MainWindow::get_instance()->register_widget_for_click_detection(ui->dial_FilterOctave_1);
	
	result = init_dial_control_colors(ui->dial_FilterQ_1);

	values[1] = _FILTER_1_EVENT;
	values[2] = _FILTER_Q;
	values[3] = 100; // To be normlized to actual filter modulation Q range.
	values[4] = 0;
	values[5] = 100;
	values[6] = 0;
	values[7] = _ML_TRAINNING_MODE_FIXED_PARAM; // Default.
	values[8] = _WIDGET_TYPE_DIAL;

	MainWindow::widgets_map_ml_training_info[ui->dial_FilterQ_1] = values;

	// Register for click detection
	MainWindow::get_instance()->register_widget_for_click_detection(ui->dial_FilterQ_1);
	
	result = init_dial_control_colors(ui->dial_FilterKbdTrack_1);

	values[1] = _FILTER_1_EVENT;
	values[2] = _FILTER_KBD_TRACK;
	values[3] = 100; // To be normlized to actual filter modulation keyboard tracking range.
	values[4] = 0;
	values[5] = 100;
	values[6] = 0;
	values[7] = _ML_TRAINNING_MODE_FIXED_PARAM; // Default.
	values[8] = _WIDGET_TYPE_DIAL;

	MainWindow::widgets_map_ml_training_info[ui->dial_FilterKbdTrack_1] = values;

	// Register for click detection
	MainWindow::get_instance()->register_widget_for_click_detection(ui->dial_FilterKbdTrack_1);

	result = init_combobox_control_colors(ui->comboBox_FilterBand_2);
	
	ui->comboBox_FilterBand_2->blockSignals(true);
	ui->comboBox_FilterBand_2->clear();
	ui->comboBox_FilterBand_2->addItems(string_filters_bands);
	ui->comboBox_FilterBand_2->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_FilterBand_2->blockSignals(false);

	values[1] = _FILTER_2_EVENT;
	values[2] = _FILTER_BAND;
	values[3] = _FILTER_BAND_PASS_ALL;
	values[4] = _FILTER_BAND_LPF;
	values[5] = _FILTER_BAND_PASS_ALL;
	values[6] = _FILTER_BAND_LPF;
	values[7] = _ML_TRAINNING_MODE_FIXED_PARAM; // Default.
	values[8] = _WIDGET_TYPE_COMBOBOX;

	MainWindow::widgets_map_ml_training_info[ui->comboBox_FilterBand_2] = values;

	// Register for click detection
	MainWindow::get_instance()->register_widget_for_click_detection(ui->comboBox_FilterBand_2);

	result = init_combobox_control_colors(ui->comboBox_FilterFreqModAdsr_2);

	ui->comboBox_FilterFreqModAdsr_2->blockSignals(true);
	ui->comboBox_FilterFreqModAdsr_2->addItems(string_adsr_values);
	ui->comboBox_FilterFreqModAdsr_2->setIdentifier(_FILTER2_FREQ_MOD_ADSR_COMBOBOX_INDEX);
	ui->comboBox_FilterFreqModAdsr_2->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_FilterFreqModAdsr_2->blockSignals(false);

	values[1] = _FILTER_2_EVENT;
	values[2] = _FILTER_FREQ_MOD_ENV;
	values[3] = _ENV_6;
	values[4] = _ENV_NONE;
	values[5] = _ENV_6;
	values[6] = _ENV_NONE;
	values[7] = _ML_TRAINNING_MODE_FIXED_PARAM; // Default.
	values[8] = _WIDGET_TYPE_COMBOBOX;

	MainWindow::widgets_map_ml_training_info[ui->comboBox_FilterFreqModAdsr_2] = values;

	// Register for click detection
	MainWindow::get_instance()->register_widget_for_click_detection(ui->comboBox_FilterFreqModAdsr_2);

	result = init_combobox_control_colors(ui->comboBox_FilterFreqModLfo_2);
	
	ui->comboBox_FilterFreqModLfo_2->blockSignals(true);
	ui->comboBox_FilterFreqModLfo_2->addItems(string_lfo_values);
	ui->comboBox_FilterFreqModLfo_2->setIdentifier(_FILTER2_FREQ_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_FilterFreqModLfo_2->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_FilterFreqModLfo_2->blockSignals(false);

	values[1] = _FILTER_2_EVENT;
	values[2] = _FILTER_FREQ_MOD_LFO;
	values[3] = _LFO_6_DELAYED_2000MS;
	values[4] = _LFO_NONE;
	values[5] = _LFO_6_DELAYED_2000MS;
	values[6] = _LFO_NONE;
	values[7] = _ML_TRAINNING_MODE_FIXED_PARAM; // Default.
	values[8] = _WIDGET_TYPE_COMBOBOX;

	MainWindow::widgets_map_ml_training_info[ui->comboBox_FilterFreqModLfo_2] = values;

	// Register for click detection
	MainWindow::get_instance()->register_widget_for_click_detection(ui->comboBox_FilterFreqModLfo_2);

	result = init_vertical_slider_control_colors(ui->verticalSlider_FilterFreqModLfoLevel_2);

	values[1] = _FILTER_2_EVENT;
	values[2] = _FILTER_FREQ_MOD_LFO_LEVEL;
	values[3] = 100;
	values[4] = 0;
	values[5] = 100;
	values[6] = 0;
	values[7] = _ML_TRAINNING_MODE_FIXED_PARAM; // Default.
	values[8] = _WIDGET_TYPE_SLIDER;

	MainWindow::widgets_map_ml_training_info[ui->verticalSlider_FilterFreqModLfoLevel_2] = values;

	// Register for click detection
	MainWindow::get_instance()->register_widget_for_click_detection(ui->verticalSlider_FilterFreqModLfoLevel_2);
	
	result = init_vertical_slider_control_colors(ui->verticalSlider_FilterFreqModAdsrLevel_2);

	values[1] = _FILTER_2_EVENT;
	values[2] = _FILTER_FREQ_MOD_ENV_LEVEL;
	values[3] = 100;
	values[4] = 0;
	values[5] = 100;
	values[6] = 0;
	values[7] = _ML_TRAINNING_MODE_FIXED_PARAM; // Default.
	values[8] = _WIDGET_TYPE_SLIDER;

	MainWindow::widgets_map_ml_training_info[ui->verticalSlider_FilterFreqModAdsrLevel_2] = values;

	// Register for click detection
	MainWindow::get_instance()->register_widget_for_click_detection(ui->verticalSlider_FilterFreqModAdsrLevel_2);

	result = init_dial_control_colors(ui->dial_FilterFreq_2);

	values[1] = _FILTER_2_EVENT;
	values[2] = _FILTER_FREQ;
	values[3] = 100; // To be normlized to actual filter frequency range.
	values[4] = 0;
	values[5] = 100;
	values[6] = 0;
	values[7] = _ML_TRAINNING_MODE_FIXED_PARAM; // Default.
	values[8] = _WIDGET_TYPE_DIAL;

	MainWindow::widgets_map_ml_training_info[ui->dial_FilterFreq_2] = values;

	// Register for click detection
	MainWindow::get_instance()->register_widget_for_click_detection(ui->dial_FilterFreq_2);
	
	result = init_dial_control_colors(ui->dial_FilterOctave_2);

	values[1] = _FILTER_2_EVENT;
	values[2] = _FILTER_OCT;
	values[3] = 100; // To be normlized to actual filter modulation octave range.
	values[4] = 0;
	values[5] = 100;
	values[6] = 0;
	values[7] = _ML_TRAINNING_MODE_FIXED_PARAM; // Default.
	values[8] = _WIDGET_TYPE_DIAL;

	MainWindow::widgets_map_ml_training_info[ui->dial_FilterOctave_2] = values;

	// Register for click detection
	MainWindow::get_instance()->register_widget_for_click_detection(ui->dial_FilterOctave_2);
	
	result = init_dial_control_colors(ui->dial_FilterQ_2);

	values[1] = _FILTER_2_EVENT;
	values[2] = _FILTER_Q;
	values[3] = 100; // To be normlized to actual filter modulation Q range.
	values[4] = 0;
	values[5] = 100;
	values[6] = 0;
	values[7] = _ML_TRAINNING_MODE_FIXED_PARAM; // Default.
	values[8] = _WIDGET_TYPE_DIAL;

	MainWindow::widgets_map_ml_training_info[ui->dial_FilterQ_2] = values;

	// Register for click detection
	MainWindow::get_instance()->register_widget_for_click_detection(ui->dial_FilterQ_2);
	
	result = init_dial_control_colors(ui->dial_FilterKbdTrack_2);

	values[1] = _FILTER_2_EVENT;
	values[2] = _FILTER_KBD_TRACK;
	values[3] = 100; // To be normlized to actual filter modulation keyboard tracking range.
	values[4] = 0;
	values[5] = 100;
	values[6] = 0;
	values[7] = _ML_TRAINNING_MODE_FIXED_PARAM; // Default.
	values[8] = _WIDGET_TYPE_DIAL;

	MainWindow::widgets_map_ml_training_info[ui->dial_FilterKbdTrack_2] = values;

	// Register for click detection
	MainWindow::get_instance()->register_widget_for_click_detection(ui->dial_FilterKbdTrack_2);	

	set_filters_signals_connections();
	filters_update();

	return 0;
}

void Dialog_AnalogSynth_1900x1000::set_filters_signals_connections()
{
	connect(ui->dial_FilterFreq_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter1_freq_dial_changed(int)));

	connect(ui->dial_FilterOctave_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter1_octave_dial_changed(int)));

	connect(ui->dial_FilterQ_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter1_q_dial_changed(int)));

	connect(ui->dial_FilterKbdTrack_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter1_kbd_track_dial_changed(int)));

	connect(ui->comboBox_FilterBand_1,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_filter1_band_combo_hanged(int)));

	connect(ui->comboBox_FilterFreqModLfo_1,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_filter1_freq_mod_lfo_combo_changed(int)));

	connect(ui->verticalSlider_FilterFreqModLfoLevel_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter1_freq_mod_level_lfo_slider_changed(int)));

	connect(ui->comboBox_FilterFreqModAdsr_1,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_filter1_freq_mod_adsr_combo_changed(int)));

	connect(ui->verticalSlider_FilterFreqModAdsrLevel_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter1_freq_mod_level_adsr_slider_changed(int)));

	connect(ui->dial_FilterFreq_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter2_freq_dial_changed(int)));

	connect(ui->dial_FilterOctave_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter2_octave_dial_changed(int)));

	connect(ui->dial_FilterQ_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter2_q_dial_changed(int)));

	connect(ui->dial_FilterKbdTrack_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter2_kbd_track_dial_changed(int)));

	connect(ui->comboBox_FilterBand_2,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_filter2_band_combo_hanged(int)));

	connect(ui->comboBox_FilterFreqModLfo_2,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_filter2_freq_mod_lfo_combo_changed(int)));

	connect(ui->verticalSlider_FilterFreqModLfoLevel_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter2_freq_mod_level_lfo_slider_changed(int)));

	connect(ui->comboBox_FilterFreqModAdsr_2,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_filter2_freq_mod_adsr_combo_changed(int)));

	connect(ui->verticalSlider_FilterFreqModAdsrLevel_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter2_freq_mod_level_adsr_slider_changed(int)));

	connect(ui->checkBox_Filter2FollowFilter1,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_filter2_track_filter1_checkbox_changed(bool)));
}

void Dialog_AnalogSynth_1900x1000::filters_update()
{
	char frequency[32], octave[16], q[16];

	ui->dial_FilterFreq_1->blockSignals(true);
	ui->dial_FilterFreq_1->setValue(mod_synth_get_active_filter_1_freq());
	ui->dial_FilterFreq_1->blockSignals(false);

	sprintf(frequency,
			"%.1f Hz",
			mod_synth_get_filter_min_center_freq() +
				(mod_synth_get_filter_max_center_freq() -
				 mod_synth_get_filter_min_center_freq()) *
					mod_synth_get_active_filter_1_freq() / 100.0f);

	ui->lineEdit_FilterFreq_1->setText(QString(frequency));

	ui->dial_FilterOctave_1->blockSignals(true);
	ui->dial_FilterOctave_1->setValue(mod_synth_get_active_filter_1_oct());
	ui->dial_FilterOctave_1->blockSignals(false);

	sprintf(octave,
			"%.4f",
			(float)mod_synth_get_active_filter_1_oct() * 6.9999f / 100.0f);

	ui->lineEdit_FilterOctave_1->setText(QString(octave));

	ui->dial_FilterQ_1->blockSignals(true);
	ui->dial_FilterQ_1->setValue(mod_synth_get_active_filter_1_q());
	ui->dial_FilterQ_1->blockSignals(false);

	sprintf(q,
			"%.1f",
			mod_synth_get_filter_min_Q() +
				(mod_synth_get_filter_max_Q() -
				 mod_synth_get_filter_min_Q()) *
					mod_synth_get_active_filter_1_q() / 100.0f);

	ui->lineEdit_FilterQ_1->setText(QString(q));

	ui->dial_FilterKbdTrack_1->blockSignals(true);
	ui->dial_FilterKbdTrack_1->setValue(mod_synth_get_active_filter_1_kbd_track());
	ui->dial_FilterKbdTrack_1->blockSignals(false);

	ui->lineEdit_FilterKbdTrack_1->setText(QString::number(mod_synth_get_active_filter_1_kbd_track()));

	ui->comboBox_FilterBand_1->blockSignals(true);
	ui->comboBox_FilterBand_1->setCurrentIndex(mod_synth_get_active_filter_1_band());
	ui->comboBox_FilterBand_1->blockSignals(false);

	ui->comboBox_FilterFreqModLfo_1->blockSignals(true);
	ui->comboBox_FilterFreqModLfo_1->setCurrentIndex(mod_synth_get_active_filter_1_Freq_mod_lfo());
	ui->comboBox_FilterFreqModLfo_1->blockSignals(false);

	ui->verticalSlider_FilterFreqModLfoLevel_1->blockSignals(true);
	ui->verticalSlider_FilterFreqModLfoLevel_1->setValue(mod_synth_get_active_filter_1_Freq_mod_lfo_level());
	ui->verticalSlider_FilterFreqModLfoLevel_1->blockSignals(false);

	ui->spinBox_FilterFreqModLfoLevel_1->blockSignals(true);
	ui->spinBox_FilterFreqModLfoLevel_1->setValue(mod_synth_get_active_filter_1_Freq_mod_lfo_level());
	ui->spinBox_FilterFreqModLfoLevel_1->blockSignals(false);

	ui->comboBox_FilterFreqModAdsr_1->blockSignals(true);
	ui->comboBox_FilterFreqModAdsr_1->setCurrentIndex(mod_synth_get_active_filter_1_Freq_mod_env());
	ui->comboBox_FilterFreqModAdsr_1->blockSignals(false);

	ui->verticalSlider_FilterFreqModAdsrLevel_1->blockSignals(true);
	ui->verticalSlider_FilterFreqModAdsrLevel_1->setValue(mod_synth_get_active_filter_1_Freq_mod_env_level());
	ui->verticalSlider_FilterFreqModAdsrLevel_1->blockSignals(false);

	ui->spinBox_FilterFreqModAdsrLevel_1->blockSignals(true);
	ui->spinBox_FilterFreqModAdsrLevel_1->setValue(mod_synth_get_active_filter_1_Freq_mod_env_level());
	ui->spinBox_FilterFreqModAdsrLevel_1->blockSignals(false);

	ui->dial_FilterFreq_2->blockSignals(true);
	ui->dial_FilterFreq_2->setValue(mod_synth_get_active_filter_2_freq());
	ui->dial_FilterFreq_2->blockSignals(false);

	sprintf(frequency,
			"%.1f Hz",
			mod_synth_get_filter_min_center_freq() +
				(mod_synth_get_filter_max_center_freq() -
				 mod_synth_get_filter_min_center_freq()) *
					mod_synth_get_active_filter_2_freq() / 100.0f);

	ui->lineEdit_FilterFreq_2->setText(QString(frequency));

	ui->dial_FilterOctave_2->blockSignals(true);
	ui->dial_FilterOctave_2->setValue(mod_synth_get_active_filter_2_oct());
	ui->dial_FilterOctave_2->blockSignals(false);

	sprintf(octave,
			"%.4f",
			(float)mod_synth_get_active_filter_2_oct() * 6.9999f / 100.0f);

	ui->lineEdit_FilterOctave_2->setText(QString(octave));

	ui->dial_FilterQ_2->blockSignals(true);
	ui->dial_FilterQ_2->setValue(mod_synth_get_active_filter_2_q());
	ui->dial_FilterQ_2->blockSignals(false);

	sprintf(q,
			"%.1f",
			mod_synth_get_filter_min_Q() +
				(mod_synth_get_filter_max_Q() -
				 mod_synth_get_filter_min_Q()) *
					mod_synth_get_active_filter_2_q() / 100.0f);

	ui->lineEdit_FilterQ_2->setText(QString(q));

	ui->dial_FilterKbdTrack_2->blockSignals(true);
	ui->dial_FilterKbdTrack_2->setValue(mod_synth_get_active_filter_2_kbd_track());
	ui->dial_FilterKbdTrack_2->blockSignals(false);

	ui->lineEdit_FilterKbdTrack_2->setText(QString::number(mod_synth_get_active_filter_2_kbd_track()));

	ui->comboBox_FilterBand_2->blockSignals(true);
	ui->comboBox_FilterBand_2->setCurrentIndex(mod_synth_get_active_filter_2_band());
	ui->comboBox_FilterBand_2->blockSignals(false);

	ui->comboBox_FilterFreqModLfo_2->blockSignals(true);
	ui->comboBox_FilterFreqModLfo_2->setCurrentIndex(mod_synth_get_active_filter_2_Freq_mod_lfo());
	ui->comboBox_FilterFreqModLfo_2->blockSignals(false);

	ui->verticalSlider_FilterFreqModLfoLevel_2->blockSignals(true);
	ui->verticalSlider_FilterFreqModLfoLevel_2->setValue(mod_synth_get_active_filter_2_Freq_mod_lfo_level());
	ui->verticalSlider_FilterFreqModLfoLevel_2->blockSignals(false);

	ui->spinBox_FilterFreqModLfoLevel_2->blockSignals(true);
	ui->spinBox_FilterFreqModLfoLevel_2->setValue(mod_synth_get_active_filter_2_Freq_mod_lfo_level());
	ui->spinBox_FilterFreqModLfoLevel_2->blockSignals(false);

	ui->comboBox_FilterFreqModAdsr_2->blockSignals(true);
	ui->comboBox_FilterFreqModAdsr_2->setCurrentIndex(mod_synth_get_active_filter_2_Freq_mod_env());
	ui->comboBox_FilterFreqModAdsr_2->blockSignals(false);

	ui->verticalSlider_FilterFreqModAdsrLevel_2->blockSignals(true);
	ui->verticalSlider_FilterFreqModAdsrLevel_2->setValue(mod_synth_get_active_filter_2_Freq_mod_env_level());
	ui->verticalSlider_FilterFreqModAdsrLevel_2->blockSignals(false);

	ui->spinBox_FilterFreqModAdsrLevel_2->blockSignals(true);
	ui->spinBox_FilterFreqModAdsrLevel_2->setValue(mod_synth_get_active_filter_2_Freq_mod_env_level());
	ui->spinBox_FilterFreqModAdsrLevel_2->blockSignals(false);
}

void Dialog_AnalogSynth_1900x1000::copy_filter1_to_filter2()
{
	on_filter2_freq_dial_changed(mod_synth_get_active_filter_1_freq());
	on_filter2_q_dial_changed(mod_synth_get_active_filter_1_q());
	on_filter2_octave_dial_changed(mod_synth_get_active_filter_1_oct());
	on_filter2_kbd_track_dial_changed(mod_synth_get_active_filter_1_kbd_track());
	on_filter2_band_combo_hanged(mod_synth_get_active_filter_1_band());
	on_filter2_freq_mod_lfo_combo_changed(mod_synth_get_active_filter_1_Freq_mod_lfo());
	on_filter2_freq_mod_level_lfo_slider_changed(mod_synth_get_active_filter_1_Freq_mod_lfo_level());
	on_filter2_freq_mod_adsr_combo_changed(mod_synth_get_active_filter_1_Freq_mod_env());
	on_filter2_freq_mod_level_adsr_slider_hanged(mod_synth_get_active_filter_1_Freq_mod_env_level());
}

void Dialog_AnalogSynth_1900x1000::on_filter1_freq_dial_changed(int val)
{
	char frequency[32];

	ui->dial_FilterFreq_1->blockSignals(true);
	ui->dial_FilterFreq_1->setValue(val);
	ui->dial_FilterFreq_1->blockSignals(false);

	sprintf(frequency,
			"%.1f Hz",
			mod_synth_get_filter_min_center_freq() +
				(mod_synth_get_filter_max_center_freq() -
				 mod_synth_get_filter_min_center_freq()) *
					val / 100.0f);

	ui->lineEdit_FilterFreq_1->setText(QString(frequency));

	filter1_frequency_entry = val;
	mod_synth_filter_event_int(_FILTER_1_EVENT, _FILTER_FREQ, val);

	if (filter_2_follows_filter_1)
	{
		ui->dial_FilterFreq_2->blockSignals(true);
		ui->dial_FilterFreq_2->setValue(val);
		ui->dial_FilterFreq_2->blockSignals(false);

		ui->lineEdit_FilterFreq_2->setText(QString(frequency));

		filter2_frequency_entry = val;
		mod_synth_filter_event_int(_FILTER_2_EVENT, _FILTER_FREQ, val);
	}

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_filter1_q_dial_changed(int val)
{
	char q[32];

	ui->dial_FilterQ_1->blockSignals(true);
	ui->dial_FilterQ_1->setValue(val);
	ui->dial_FilterQ_1->blockSignals(false);

	sprintf(q,
			"%.1f",
			mod_synth_get_filter_min_Q() +
				(mod_synth_get_filter_max_Q() -
				 mod_synth_get_filter_min_Q()) *
					val / 100.0f);

	ui->lineEdit_FilterQ_1->setText(QString(q));

	filter1_q_entry = val;
	mod_synth_filter_event_int(_FILTER_1_EVENT, _FILTER_Q, val);

	if (filter_2_follows_filter_1)
	{
		ui->dial_FilterQ_2->blockSignals(true);
		ui->dial_FilterQ_2->setValue(val);
		ui->dial_FilterQ_2->blockSignals(false);

		ui->lineEdit_FilterQ_2->setText(QString(q));

		filter2_q_entry = val;
		mod_synth_filter_event_int(_FILTER_2_EVENT, _FILTER_Q, val);
	}

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_filter1_octave_dial_changed(int val)
{
	char octave[16];

	ui->dial_FilterOctave_1->blockSignals(true);
	ui->dial_FilterOctave_1->setValue(val);
	ui->dial_FilterOctave_1->blockSignals(false);

	sprintf(octave,
			"%.4f",
			val * 6.9999f / 100.0f);

	ui->lineEdit_FilterOctave_1->setText(QString(octave));

	filter1_octave_entry = val;
	mod_synth_filter_event_int(_FILTER_1_EVENT, _FILTER_OCT, val);

	if (filter_2_follows_filter_1)
	{
		ui->dial_FilterOctave_2->blockSignals(true);
		ui->dial_FilterOctave_2->setValue(val);
		ui->dial_FilterOctave_2->blockSignals(false);

		ui->lineEdit_FilterOctave_2->setText(QString(octave));

		filter2_octave_entry = val;
		mod_synth_filter_event_int(_FILTER_2_EVENT, _FILTER_OCT, val);
	}

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_filter1_kbd_track_dial_changed(int val)
{
	ui->dial_FilterKbdTrack_1->blockSignals(true);
	ui->dial_FilterKbdTrack_1->setValue(val);
	ui->dial_FilterKbdTrack_1->blockSignals(false);

	ui->lineEdit_FilterKbdTrack_1->setText(QString::number(val));

	int filter1_keyboard_track = val;
	mod_synth_filter_event_int(_FILTER_1_EVENT, _FILTER_KBD_TRACK, val);

	if (filter_2_follows_filter_1)
	{
		ui->dial_FilterKbdTrack_2->blockSignals(true);
		ui->dial_FilterKbdTrack_2->setValue(val);
		ui->dial_FilterKbdTrack_2->blockSignals(false);

		ui->lineEdit_FilterKbdTrack_1->setText(QString::number(val));
		
		int filter1_keyboard_track = val;
		mod_synth_filter_event_int(_FILTER_2_EVENT, _FILTER_KBD_TRACK, val);
	}

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_filter1_band_combo_hanged(int val)
{
	ui->comboBox_FilterBand_1->blockSignals(true);
	ui->comboBox_FilterBand_1->setCurrentIndex(val);
	ui->comboBox_FilterBand_1->blockSignals(false);

	int filter1_band = val;
	mod_synth_filter_event_int(_FILTER_1_EVENT, _FILTER_BAND, val);

	if (filter_2_follows_filter_1)
	{
		ui->comboBox_FilterBand_2->blockSignals(true);
		ui->comboBox_FilterBand_2->setCurrentIndex(val);
		ui->comboBox_FilterBand_2->blockSignals(false);

		int filter2_band = val;
		mod_synth_filter_event_int(_FILTER_2_EVENT, _FILTER_BAND, val);
	}

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_filter1_freq_mod_lfo_combo_changed(int val)
{
	ui->comboBox_FilterFreqModLfo_1->blockSignals(true);
	ui->comboBox_FilterFreqModLfo_1->setCurrentIndex(val);
	ui->comboBox_FilterFreqModLfo_1->blockSignals(false);

	filter1_freq_mod_lfo = val;
	mod_synth_filter_event_int(_FILTER_1_EVENT, _FILTER_FREQ_MOD_LFO, val);

	if (filter_2_follows_filter_1)
	{
		ui->comboBox_FilterFreqModLfo_2->blockSignals(true);
		ui->comboBox_FilterFreqModLfo_2->setCurrentIndex(val);
		ui->comboBox_FilterFreqModLfo_2->blockSignals(false);

		filter2_freq_mod_lfo = val;
		mod_synth_filter_event_int(_FILTER_2_EVENT, _FILTER_FREQ_MOD_LFO, val);
	}

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_filter1_freq_mod_level_lfo_slider_changed(int val)
{
	ui->verticalSlider_FilterFreqModLfoLevel_1->blockSignals(true);
	ui->verticalSlider_FilterFreqModLfoLevel_1->setValue(val);
	ui->verticalSlider_FilterFreqModLfoLevel_1->blockSignals(false);
	ui->spinBox_FilterFreqModLfoLevel_1->blockSignals(true);
	ui->spinBox_FilterFreqModLfoLevel_1->setValue(val);
	ui->spinBox_FilterFreqModLfoLevel_1->blockSignals(false);

	int filter1_freq_mod_lfo_level = val;
	mod_synth_filter_event_int(_FILTER_1_EVENT, _FILTER_FREQ_MOD_LFO_LEVEL, val);

	if (filter_2_follows_filter_1)
	{
		ui->verticalSlider_FilterFreqModLfoLevel_2->blockSignals(true);
		ui->verticalSlider_FilterFreqModLfoLevel_2->setValue(val);
		ui->verticalSlider_FilterFreqModLfoLevel_2->blockSignals(false);

		ui->spinBox_FilterFreqModLfoLevel_2->blockSignals(true);
		ui->spinBox_FilterFreqModLfoLevel_2->setValue(val);
		ui->spinBox_FilterFreqModLfoLevel_2->blockSignals(false);

		int filter2_freq_mod_lfo_level = val;
		mod_synth_filter_event_int(_FILTER_2_EVENT, _FILTER_FREQ_MOD_LFO_LEVEL, val);
	}

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_filter1_freq_mod_adsr_combo_changed(int val)
{
	ui->comboBox_FilterFreqModAdsr_1->blockSignals(true);
	ui->comboBox_FilterFreqModAdsr_1->setCurrentIndex(val);
	ui->comboBox_FilterFreqModAdsr_1->blockSignals(false);

	filter1_freq_mod_adsr = val;
	mod_synth_filter_event_int(_FILTER_1_EVENT, _FILTER_FREQ_MOD_ENV, val);

	if (filter_2_follows_filter_1)
	{
		ui->comboBox_FilterFreqModAdsr_2->blockSignals(true);
		ui->comboBox_FilterFreqModAdsr_2->setCurrentIndex(val);
		ui->comboBox_FilterFreqModAdsr_2->blockSignals(false);

		filter2_freq_mod_adsr = val;
		mod_synth_filter_event_int(_FILTER_2_EVENT, _FILTER_FREQ_MOD_ENV, val);
	}

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_filter1_freq_mod_level_adsr_slider_hanged(int val)
{
	ui->verticalSlider_FilterFreqModAdsrLevel_1->blockSignals(true);
	ui->verticalSlider_FilterFreqModAdsrLevel_1->setValue(val);
	ui->verticalSlider_FilterFreqModAdsrLevel_1->blockSignals(false);

	ui->spinBox_FilterFreqModAdsrLevel_1->blockSignals(true);
	ui->spinBox_FilterFreqModAdsrLevel_1->setValue(val);
	ui->spinBox_FilterFreqModAdsrLevel_1->blockSignals(false);

	int filter1_freq_mod_adsr_level = val;
	mod_synth_filter_event_int(_FILTER_1_EVENT, _FILTER_FREQ_MOD_ENV_LEVEL, val);

	if (filter_2_follows_filter_1)
	{
		ui->verticalSlider_FilterFreqModAdsrLevel_2->blockSignals(true);
		ui->verticalSlider_FilterFreqModAdsrLevel_2->setValue(val);
		ui->verticalSlider_FilterFreqModAdsrLevel_2->blockSignals(false);

		ui->spinBox_FilterFreqModAdsrLevel_2->blockSignals(true);
		ui->spinBox_FilterFreqModAdsrLevel_2->setValue(val);
		ui->spinBox_FilterFreqModAdsrLevel_2->blockSignals(false);

		int filter2_freq_mod_adsr_level = val;
		mod_synth_filter_event_int(_FILTER_2_EVENT, _FILTER_FREQ_MOD_ENV_LEVEL, val);
	}

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_filter2_freq_dial_changed(int val)
{
	char frequency[32];

	ui->dial_FilterFreq_2->blockSignals(true);
	ui->dial_FilterFreq_2->setValue(val);
	ui->dial_FilterFreq_2->blockSignals(false);

	sprintf(frequency,
			"%.1f Hz",
			mod_synth_get_filter_min_center_freq() +
				(mod_synth_get_filter_max_center_freq() -
				 mod_synth_get_filter_min_center_freq()) *
					val / 100.0f);

	ui->lineEdit_FilterFreq_2->setText(QString(frequency));

	filter2_frequency_entry = val;
	mod_synth_filter_event_int(_FILTER_2_EVENT, _FILTER_FREQ, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_filter2_q_dial_changed(int val)
{
	char q[32];

	ui->dial_FilterQ_2->blockSignals(true);
	ui->dial_FilterQ_2->setValue(val);
	ui->dial_FilterQ_2->blockSignals(false);

	sprintf(q,
			"%.1f",
			mod_synth_get_filter_min_Q() +
				(mod_synth_get_filter_max_Q() -
				 mod_synth_get_filter_min_Q()) *
					val / 100.0f);

	ui->lineEdit_FilterQ_2->setText(QString(q));

	filter2_q_entry = val;
	mod_synth_filter_event_int(_FILTER_2_EVENT, _FILTER_Q, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_filter2_octave_dial_changed(int val)
{
	char octave[16];

	ui->dial_FilterOctave_2->blockSignals(true);
	ui->dial_FilterOctave_2->setValue(val);
	ui->dial_FilterOctave_2->blockSignals(false);

	sprintf(octave,
			"%.4f",
			val * 6.9999f / 100.0f);

	ui->lineEdit_FilterOctave_2->setText(QString(octave));

	filter2_octave_entry = val;
	mod_synth_filter_event_int(_FILTER_2_EVENT, _FILTER_OCT, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_filter2_kbd_track_dial_changed(int val)
{
	ui->dial_FilterKbdTrack_2->blockSignals(true);
	ui->dial_FilterKbdTrack_2->setValue(val);
	ui->dial_FilterKbdTrack_2->blockSignals(false);

	ui->lineEdit_FilterKbdTrack_2->setText(QString::number(val));

	int filter2_keyboard_track = val;
	mod_synth_filter_event_int(_FILTER_2_EVENT, _FILTER_KBD_TRACK, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_filter2_band_combo_hanged(int val)
{
	ui->comboBox_FilterBand_2->blockSignals(true);
	ui->comboBox_FilterBand_2->setCurrentIndex(val);
	ui->comboBox_FilterBand_2->blockSignals(false);

	int filter2_band = val;
	mod_synth_filter_event_int(_FILTER_2_EVENT, _FILTER_BAND, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_filter2_freq_mod_lfo_combo_changed(int val)
{
	ui->comboBox_FilterFreqModLfo_2->blockSignals(true);
	ui->comboBox_FilterFreqModLfo_2->setCurrentIndex(val);
	ui->comboBox_FilterFreqModLfo_2->blockSignals(false);

	filter2_freq_mod_lfo = val;
	mod_synth_filter_event_int(_FILTER_2_EVENT, _FILTER_FREQ_MOD_LFO, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_filter2_freq_mod_level_lfo_slider_changed(int val)
{
	ui->verticalSlider_FilterFreqModLfoLevel_2->blockSignals(true);
	ui->verticalSlider_FilterFreqModLfoLevel_2->setValue(val);
	ui->verticalSlider_FilterFreqModLfoLevel_2->blockSignals(false);
	ui->spinBox_FilterFreqModLfoLevel_2->blockSignals(true);
	ui->spinBox_FilterFreqModLfoLevel_2->setValue(val);
	ui->spinBox_FilterFreqModLfoLevel_2->blockSignals(false);

	int filter2_freq_mod_lfo_level = val;
	mod_synth_filter_event_int(_FILTER_2_EVENT, _FILTER_FREQ_MOD_LFO_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_filter2_freq_mod_adsr_combo_changed(int val)
{
	ui->comboBox_FilterFreqModAdsr_2->blockSignals(true);
	ui->comboBox_FilterFreqModAdsr_2->setCurrentIndex(val);
	ui->comboBox_FilterFreqModAdsr_2->blockSignals(false);

	filter2_freq_mod_adsr = val;
	mod_synth_filter_event_int(_FILTER_2_EVENT, _FILTER_FREQ_MOD_ENV, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_filter2_freq_mod_level_adsr_slider_hanged(int val)
{
	ui->verticalSlider_FilterFreqModAdsrLevel_2->blockSignals(true);
	ui->verticalSlider_FilterFreqModAdsrLevel_2->setValue(val);
	ui->verticalSlider_FilterFreqModAdsrLevel_2->blockSignals(false);
	ui->spinBox_FilterFreqModAdsrLevel_2->blockSignals(true);
	ui->spinBox_FilterFreqModAdsrLevel_2->setValue(val);
	ui->spinBox_FilterFreqModAdsrLevel_2->blockSignals(false);

	int filter2_freq_mod_adsr_level = val;
	mod_synth_filter_event_int(_FILTER_2_EVENT, _FILTER_FREQ_MOD_ENV_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_filter2_track_filter1_checkbox_changed(bool val)
{
	ui->checkBox_Filter2FollowFilter1->blockSignals(true);

	if (val)
	{
		ui->checkBox_Filter2FollowFilter1->setCheckState(Qt::Checked);
		filter_2_follows_filter_1 = true;
		copy_filter1_to_filter2();
	}
	else
	{
		ui->checkBox_Filter2FollowFilter1->setCheckState(Qt::Unchecked);
		filter_2_follows_filter_1 = false;
	}

	ui->checkBox_Filter2FollowFilter1->blockSignals(false);
}
