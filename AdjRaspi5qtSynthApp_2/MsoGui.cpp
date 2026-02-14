/**
 * @file		MsoGui.cpp
 *	@author		Nahum Budin
 *	@date		30-Dec-2025
 *	@version	2.0
 *
 *	@brief		Analog Synthesizer instrument Morphed Sine Oscilator (MSO) GUI handling
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

// MSO Sine-wave preset positions
static const int preset_sinus[] = {512, 517, 1024, 1029, 1536, 1542};
// Symetric square-wave preset positions
static const int preset_squar[] = {1, 1011, 1016, 1021, 1026, 2046};
// Symetric square-wave preset positions
static const int preset_pulse[] = {1, 200, 205, 210, 215, 2046};
// Sawtooth-wave preset positions
static const int preset_saw[] = {1, 7, 1024, 1029, 2041, 2046};

int Dialog_AnalogSynth_1900x1000::init_mso_gui()
{
	int result;

	set_mso_signals_connections();
	mso_update();
	mso_replot_waveform = true;

	// Prepare MSO Presets Strings
	if (string_mso_presets_list.size() == 0)
	{
		string_mso_presets_list.append("Sine");
		string_mso_presets_list.append("Square");
		string_mso_presets_list.append("Pulse");
		string_mso_presets_list.append("Sawtooth");
	}

	// MSO send filters and tune frame and controls
	result = init_frame_colors(ui->frame_MsoSendFiltersTuneOffset);

	result = init_dial_control_colors(ui->dial_MsoSendFilter1);
	result = init_dial_control_colors(ui->dial_MsoSendFilter2);
	result = init_combobox_control_colors(ui->comboBox_MsoTuneOctave);
	result = init_combobox_control_colors(ui->comboBox_MsoTuneSemitones);
	result = init_combobox_control_colors(ui->comboBox_MsoTuneCents);

	ui->comboBox_MsoTuneOctave->blockSignals(true);
	ui->comboBox_MsoTuneSemitones->blockSignals(true);
	ui->comboBox_MsoTuneCents->blockSignals(true);
	
	for (int i = _OSC_DETUNE_MIN_OCTAVE; i <= _OSC_DETUNE_MAX_OCTAVE; i++)
	{
		ui->comboBox_MsoTuneOctave->addItem(QString::number(i));
	}
	
	for (int i = _OSC_DETUNE_MIN_SEMITONES; i <= _OSC_DETUNE_MAX_SEMITONES; i++)
	{
		ui->comboBox_MsoTuneSemitones->addItem(QString::number(i));
	}
	
	for (int i = 4 * _OSC_DETUNE_MIN_CENTS; i <= 4 * _OSC_DETUNE_MAX_CENTS; i++)
	{                                  	
		// 0.25 steps
		ui->comboBox_MsoTuneCents->addItem(QString::number(i / 4.f));
	}

	ui->comboBox_MsoTuneOctave->blockSignals(false);
	ui->comboBox_MsoTuneSemitones->blockSignals(false);
	ui->comboBox_MsoTuneCents->blockSignals(false);

	// MSO Frequency Modulation frame and controls
	result = init_frame_colors(ui->frame_MsoFreqMod);

	result = init_dial_control_colors(ui->dial_MsoFreqModLFOLevel);
	result = init_dial_control_colors(ui->dial_MsoFreqModAdsrLevel);
	
	result = init_combobox_control_colors(ui->comboBox_MsoFreqModLFO);
	
	ui->comboBox_MsoFreqModLFO->blockSignals(true);
	ui->comboBox_MsoFreqModLFO->addItems(string_lfo_values);
	ui->comboBox_MsoFreqModLFO->setIdentifier(_MSO_FREQ_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MsoFreqModLFO->blockSignals(false);
	
	result = init_combobox_control_colors(ui->comboBox_MsoFreqModAdsr);
	ui->comboBox_MsoFreqModAdsr->blockSignals(true);
	ui->comboBox_MsoFreqModAdsr->addItems(string_adsr_values);
	ui->comboBox_MsoFreqModAdsr->setIdentifier(_MSO_FREQ_MOD_ADSR_COMBOBOX_INDEX);
	ui->comboBox_MsoFreqModAdsr->blockSignals(false);
	
	// MSO Amplitude Modulation frame and controls
	result = init_frame_colors(ui->frame_MsoAmpMod);
	
	result = init_dial_control_colors(ui->dial_MsoAmpModLFOLevel);
	result = init_dial_control_colors(ui->dial_MsoAmpModAdsrLevel);
	
	result = init_combobox_control_colors(ui->comboBox_MsoAmpModLFO);
	
	ui->comboBox_MsoAmpModLFO->blockSignals(true);
	ui->comboBox_MsoAmpModLFO->addItems(string_lfo_values);
	ui->comboBox_MsoAmpModLFO->setIdentifier(_MSO_AMP_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MsoAmpModLFO->blockSignals(false);
	
	result = init_combobox_control_colors(ui->comboBox_MsoAmpModAdsr);
	ui->comboBox_MsoAmpModAdsr->blockSignals(true);
	ui->comboBox_MsoAmpModAdsr->addItems(string_adsr_values);
	ui->comboBox_MsoAmpModAdsr->setIdentifier(_MSO_AMP_MOD_ADSR_COMBOBOX_INDEX);
	ui->comboBox_MsoAmpModAdsr->blockSignals(false);
	
	// MSO PWM Modulation frame and controls
	result = init_frame_colors(ui->frame_MsoPwmMod);
	
	result = init_dial_control_colors(ui->dial_MsoPwmModLFOLevel);
	result = init_dial_control_colors(ui->dial_MsoPwmModAdsrLevel);
	
	result = init_combobox_control_colors(ui->comboBox_MsoPwmModLFO);
	
	ui->comboBox_MsoPwmModLFO->blockSignals(true);
	ui->comboBox_MsoPwmModLFO->addItems(string_lfo_values);
	ui->comboBox_MsoPwmModLFO->setIdentifier(_MSO_PWM_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_MsoPwmModLFO->blockSignals(false);

	result = init_combobox_control_colors(ui->comboBox_MsoPwmModAdsr);
	ui->comboBox_MsoPwmModAdsr->blockSignals(true);
	ui->comboBox_MsoPwmModAdsr->addItems(string_adsr_values);
	ui->comboBox_MsoPwmModAdsr->setIdentifier(_MSO_PWM_MOD_ADSR_COMBOBOX_INDEX);
	ui->comboBox_MsoPwmModAdsr->blockSignals(false);

	// MSO Segments frame and controls
	result = init_frame_colors(ui->frame_MsoSegments);

	result = init_combobox_control_colors(ui->comboBox_MsoPreset);
	ui->comboBox_MsoPreset->blockSignals(true);
	ui->comboBox_MsoPreset->addItems(string_mso_presets_list);
	ui->comboBox_MsoPreset->blockSignals(false);

	result = init_horizontal_slider_control_colors(ui->horizontalSlider_MsoMorph);

	result = init_vertical_slider_control_colors(ui->verticalSlider_MSO_Pos_a);
	result = init_vertical_slider_control_colors(ui->verticalSlider_MSO_Pos_b);
	result = init_vertical_slider_control_colors(ui->verticalSlider_MSO_Pos_c);
	result = init_vertical_slider_control_colors(ui->verticalSlider_MSO_Pos_d);
	result = init_vertical_slider_control_colors(ui->verticalSlider_MSO_Pos_e);
	result = init_vertical_slider_control_colors(ui->verticalSlider_MSO_Pos_f);

	return 0;
}

void Dialog_AnalogSynth_1900x1000::set_mso_signals_connections()
{
	//connect(ui->pushButton_AnalogSynthClose,
	//		SIGNAL(clicked()),
	//		this,
	//		SLOT(on_dialog_close()));

	connect(ui->checkBox_MSOenable,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_mso_enable_checkbox_changed(bool)));

	connect(ui->verticalSlider_MSO_Pos_a,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_point_a_slider_moved(int)));

	connect(ui->verticalSlider_MSO_Pos_b,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_point_b_slider_moved(int)));

	connect(ui->verticalSlider_MSO_Pos_c,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_point_c_slider_moved(int)));

	connect(ui->verticalSlider_MSO_Pos_d,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_point_d_slider_moved(int)));

	connect(ui->verticalSlider_MSO_Pos_e,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_point_e_slider_moved(int)));

	connect(ui->verticalSlider_MSO_Pos_f,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_point_f_slider_moved(int)));

	connect(ui->horizontalSlider_MsoMorph,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_symetry_slider_changed(int)));

	connect(ui->comboBox_MsoTuneOctave,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_mso_detune_octave_combobox_changed(int)));

	connect(ui->comboBox_MsoTuneSemitones,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_mso_detune_seminotes_combobox_changed(int)));

	connect(ui->comboBox_MsoTuneCents,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_mso_detune_cents_combobox_changed(int)));

	connect(ui->dial_MsoSendFilter1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_send_filter_1_dial_changed(int)));

	connect(ui->dial_MsoSendFilter2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_send_filter_2_dial_changed(int)));

	connect(ui->comboBox_MsoFreqModLFO,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_mso_freq_mod_lfo_combobox_changed(int)));

	connect(ui->dial_MsoFreqModLFOLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_freq_mod_lfo_level_dial_changed(int)));

	connect(ui->comboBox_MsoFreqModAdsr,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_mso_freq_mod_env_combobox_changed(int)));

	connect(ui->dial_MsoFreqModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_freq_mod_env_level_dial_changed(int)));

	connect(ui->comboBox_MsoPwmModLFO,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_mso_pwm_mod_lfo_combobox_changed(int)));

	connect(ui->dial_MsoPwmModLFOLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_pwm_mod_lfo_level_dial_changed(int)));

	connect(ui->comboBox_MsoPwmModAdsr,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_mso_pwm_mod_env_combobox_changed(int)));

	connect(ui->dial_MsoPwmModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_pwm_mod_env_level_dial_changed(int)));

	connect(ui->comboBox_MsoAmpModLFO,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_mso_amp_mod_lfo_combobox_changed(int)));

	connect(ui->dial_MsoAmpModLFOLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_amp_mod_lfo_level_dial_changed(int)));

	connect(ui->comboBox_MsoAmpModAdsr,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_mso_amp_mod_env_combobox_changed(int)));

	connect(ui->dial_MsoAmpModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_amp_mod_env_level_dial_changed(int)));

	connect(ui->comboBox_MsoPreset,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_mso_preset_combobox_changed(int)));

	connect(ui->spinBox_MsoFreqModLfoLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_freq_mod_lfo_level_spinbox_changed(int)));

	connect(ui->spinBox_MsoFreqModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_freq_mod_adsr_level_spinbox_changed(int)));

	connect(ui->spinBox_MsoPwmModLfoLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_pwm_mod_lfo_level_spinbox_changed(int)));

	connect(ui->spinBox_MsoPwmModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_freq_mod_adsr_level_spinbox_changed(int)));

	connect(ui->spinBox_MsoAmpModLfoLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_amp_mod_lfo_level_spinbox_changed(int)));

	connect(ui->spinBox_MsoAmpModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mso_amp_mod_adsr_level_spinbox_changed(int)));
}

void Dialog_AnalogSynth_1900x1000::setup_mso_plot(QCustomPlot *custom_plot)
{
	if (update_mso_plot && mod_synth_get_mso_morphed_lookup_table())
	{
		mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_CALC_BASE_LUT, mod_synth_get_active_sketch());
		// Recalculates morphed waveform.
		mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_CALC_MORPHED_LUT, mod_synth_get_active_sketch());

		// add two(?) new graphs and set their look:
		QPen pen;
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(3);
		pen.setColor(Qt::white);
		custom_plot->addGraph();
		custom_plot->graph(0)->setPen(pen); // line color blue for first graph
											//		custom_plot->addGraph();
											//		custom_plot->graph(1)->setPen(QPen(Qt::red));   // line color red for second graph

		custom_plot->setBackground(QBrush(_CONTROLS_COLOR_BLACK));

		QVector<double> x(mod_synth_get_mso_table_length() + 1), y0(mod_synth_get_mso_table_length() + 1);

		for (int i = 0; i < mod_synth_get_mso_table_length() / 4; ++i)
		{
			x[i] = i;
			y0[i] = mod_synth_get_mso_morphed_lookup_table()[i * 4]; // Table length is getMsoTableLength * 4
																	 //	y1[i] = 52.f + 47.f*qCos(2 * 3.14 * i / 256);
		}
		// x[256] = 257; y0[256] = -2; y1[256] = -2;
		custom_plot->xAxis->setVisible(false);
		custom_plot->xAxis->setTickLabels(false);
		custom_plot->yAxis->setVisible(false);
		custom_plot->yAxis->setTickLabels(false);
		// make left and bottom axes always transfer their ranges to right and top axes:
		// connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
		// connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
		// pass data points to graphs:
		custom_plot->graph(0)->setData(x, y0);
		// let the ranges scale themselves so graph 0 fits perfectly in the visible area:
		custom_plot->graph(0)->rescaleAxes();
	}
}

void Dialog_AnalogSynth_1900x1000::update_mso_waveform_plot()
{
	setup_mso_plot(ui->widget_MsoWaveformPlot);
	ui->widget_MsoWaveformPlot->replot();
}

void Dialog_AnalogSynth_1900x1000::mso_handle_preset_change(int newPres)
{
	switch (newPres)
	{
	case 0:
		mso_set_preset_positions(preset_sinus);
		break;

	case 1:
		mso_set_preset_positions(preset_squar);
		break;

	case 2:
		mso_set_preset_positions(preset_pulse);
		break;

	case 3:
		mso_set_preset_positions(preset_saw);
		break;

	default:
		mso_set_preset_positions(preset_sinus);
		break;
	}
}

void Dialog_AnalogSynth_1900x1000::mso_set_preset_positions(const int pos[])
{
	// Put all points to their max value to enable any setup
	update_mso_plot = false;
	on_mso_point_f_slider_moved(2035);
	on_mso_point_e_slider_moved(2033);
	on_mso_point_d_slider_moved(2031);
	on_mso_point_c_slider_moved(2029);
	on_mso_point_b_slider_moved(2027);
	on_mso_point_a_slider_moved(2025);

	on_mso_point_a_slider_moved(pos[0]);
	on_mso_point_b_slider_moved(pos[1]);
	on_mso_point_c_slider_moved(pos[2]);
	on_mso_point_d_slider_moved(pos[3]);
	on_mso_point_e_slider_moved(pos[4]);
	on_mso_point_f_slider_moved(pos[5]);
	update_mso_plot = true;
	on_mso_symetry_slider_changed(70);

	ui->verticalSlider_MSO_Pos_a->blockSignals(true);
	ui->verticalSlider_MSO_Pos_a->setValue(pos[0]);
	ui->verticalSlider_MSO_Pos_a->blockSignals(false);

	ui->verticalSlider_MSO_Pos_b->blockSignals(true);
	ui->verticalSlider_MSO_Pos_b->setValue(pos[1]);
	ui->verticalSlider_MSO_Pos_b->blockSignals(false);

	ui->verticalSlider_MSO_Pos_c->blockSignals(true);
	ui->verticalSlider_MSO_Pos_c->setValue(pos[2]);
	ui->verticalSlider_MSO_Pos_c->blockSignals(false);

	ui->verticalSlider_MSO_Pos_d->blockSignals(true);
	ui->verticalSlider_MSO_Pos_d->setValue(pos[3]);
	ui->verticalSlider_MSO_Pos_d->blockSignals(false);

	ui->verticalSlider_MSO_Pos_e->blockSignals(true);
	ui->verticalSlider_MSO_Pos_e->setValue(pos[4]);
	ui->verticalSlider_MSO_Pos_e->blockSignals(false);

	ui->verticalSlider_MSO_Pos_f->blockSignals(true);
	ui->verticalSlider_MSO_Pos_f->setValue(pos[5]);
	ui->verticalSlider_MSO_Pos_f->blockSignals(false);

	ui->horizontalSlider_MsoMorph->blockSignals(true);
	ui->horizontalSlider_MsoMorph->setValue(70);
	ui->horizontalSlider_MsoMorph->blockSignals(false);
}

void Dialog_AnalogSynth_1900x1000::mso_update()
{
	ui->verticalSlider_MSO_Pos_a->blockSignals(true);
	ui->verticalSlider_MSO_Pos_a->setValue(mod_synth_get_active_mso_table_segment_point(0));
	ui->verticalSlider_MSO_Pos_a->blockSignals(false);

	ui->verticalSlider_MSO_Pos_b->blockSignals(true);
	ui->verticalSlider_MSO_Pos_b->setValue(mod_synth_get_active_mso_table_segment_point(1));
	ui->verticalSlider_MSO_Pos_b->blockSignals(false);

	ui->verticalSlider_MSO_Pos_c->blockSignals(true);
	ui->verticalSlider_MSO_Pos_c->setValue(mod_synth_get_active_mso_table_segment_point(2));
	ui->verticalSlider_MSO_Pos_c->blockSignals(false);

	ui->verticalSlider_MSO_Pos_d->blockSignals(true);
	ui->verticalSlider_MSO_Pos_d->setValue(mod_synth_get_active_mso_table_segment_point(3));
	ui->verticalSlider_MSO_Pos_d->blockSignals(false);

	ui->verticalSlider_MSO_Pos_e->blockSignals(true);
	ui->verticalSlider_MSO_Pos_e->setValue(mod_synth_get_active_mso_table_segment_point(4));
	ui->verticalSlider_MSO_Pos_e->blockSignals(false);

	ui->verticalSlider_MSO_Pos_f->blockSignals(true);
	ui->verticalSlider_MSO_Pos_f->setValue(mod_synth_get_active_mso_table_segment_point(5));
	ui->verticalSlider_MSO_Pos_f->blockSignals(false);

	ui->spinBox_MSO_Pos_a->blockSignals(true);
	ui->spinBox_MSO_Pos_a->setValue(mod_synth_get_active_mso_table_segment_point(0));
	ui->spinBox_MSO_Pos_a->blockSignals(false);

	ui->spinBox_MSO_Pos_b->blockSignals(true);
	ui->spinBox_MSO_Pos_b->setValue(mod_synth_get_active_mso_table_segment_point(1));
	ui->spinBox_MSO_Pos_b->blockSignals(false);

	ui->spinBox_MSO_Pos_c->blockSignals(true);
	ui->spinBox_MSO_Pos_c->setValue(mod_synth_get_active_mso_table_segment_point(2));
	ui->spinBox_MSO_Pos_c->blockSignals(false);

	ui->spinBox_MSO_Pos_d->blockSignals(true);
	ui->spinBox_MSO_Pos_d->setValue(mod_synth_get_active_mso_table_segment_point(3));
	ui->spinBox_MSO_Pos_d->blockSignals(false);

	ui->spinBox_MSO_Pos_e->blockSignals(true);
	ui->spinBox_MSO_Pos_e->setValue(mod_synth_get_active_mso_table_segment_point(4));
	ui->spinBox_MSO_Pos_e->blockSignals(false);

	ui->spinBox_MSO_Pos_f->blockSignals(true);
	ui->spinBox_MSO_Pos_f->setValue(mod_synth_get_active_mso_table_segment_point(5));
	ui->spinBox_MSO_Pos_f->blockSignals(false);

	ui->horizontalSlider_MsoMorph->blockSignals(true);
	ui->horizontalSlider_MsoMorph->setValue(mod_synth_get_active_mso_symetry());
	ui->horizontalSlider_MsoMorph->blockSignals(false);

	mso_enabled = mod_synth_get_active_mso_enable_state();
	ui->checkBox_MSOenable->blockSignals(true);
	ui->checkBox_MSOenable->setChecked(mso_enabled);
	ui->checkBox_MSOenable->blockSignals(false);

	if (mso_enabled)
	{
		ui->widget_MsoWaveformPlot->setEnabled(true);
		ui->frame_MsoAmpMod->setEnabled(true);
		ui->frame_MsoFreqMod->setEnabled(true);
		ui->frame_MsoPwmMod->setEnabled(true);
		ui->frame_MsoSegments->setEnabled(true);
		ui->frame_MsoSegments->setEnabled(true);
		ui->frame_MsoSendFiltersTuneOffset->setEnabled(true);
	}
	else
	{
		ui->widget_MsoWaveformPlot->setEnabled(false);
		ui->frame_MsoAmpMod->setEnabled(false);
		ui->frame_MsoFreqMod->setEnabled(false);
		ui->frame_MsoPwmMod->setEnabled(false);
		ui->frame_MsoSegments->setEnabled(false);
		ui->frame_MsoSegments->setEnabled(false);
		ui->frame_MsoSendFiltersTuneOffset->setEnabled(false);
	}

	ui->comboBox_MsoTuneOctave->blockSignals(true);
	ui->comboBox_MsoTuneOctave->setCurrentIndex(mod_synth_get_active_mso_detune_octave() - _OSC_DETUNE_MIN_OCTAVE);
	ui->comboBox_MsoTuneOctave->blockSignals(false);

	ui->comboBox_MsoTuneSemitones->blockSignals(true);
	ui->comboBox_MsoTuneSemitones->setCurrentIndex(mod_synth_get_active_mso_detune_semitones() - _OSC_DETUNE_MIN_SEMITONES);
	ui->comboBox_MsoTuneSemitones->blockSignals(false);

	ui->comboBox_MsoTuneCents->blockSignals(true);
	ui->comboBox_MsoTuneCents->setCurrentIndex(mod_synth_get_active_mso_detune_cents() - _OSC_DETUNE_MIN_CENTS * 4.f);
	ui->comboBox_MsoTuneCents->blockSignals(false);

	ui->dial_MsoSendFilter1->blockSignals(true);
	ui->dial_MsoSendFilter1->setValue(mod_synth_get_active_mso_send_filter_1());
	ui->dial_MsoSendFilter1->blockSignals(false);

	ui->spinBox_MsoSendFilter1->blockSignals(true);
	ui->spinBox_MsoSendFilter1->setValue(mod_synth_get_active_mso_send_filter_1());
	ui->spinBox_MsoSendFilter1->blockSignals(false);

	ui->dial_MsoSendFilter2->blockSignals(true);
	ui->dial_MsoSendFilter2->setValue(mod_synth_get_active_mso_send_filter_2());
	ui->dial_MsoSendFilter2->blockSignals(false);

	ui->spinBox_MsoSendFilter2->blockSignals(true);
	ui->spinBox_MsoSendFilter2->setValue(mod_synth_get_active_mso_send_filter_2());
	ui->spinBox_MsoSendFilter2->blockSignals(false);

	ui->comboBox_MsoFreqModLFO->blockSignals(true);
	ui->comboBox_MsoFreqModLFO->setCurrentIndex(mod_synth_get_active_mso_freq_mod_lfo());
	ui->comboBox_MsoFreqModLFO->blockSignals(false);

	ui->dial_MsoFreqModLFOLevel->blockSignals(true);
	ui->dial_MsoFreqModLFOLevel->setValue(mod_synth_get_active_mso_freq_mod_lfo_level());
	ui->dial_MsoFreqModLFOLevel->blockSignals(false);

	ui->spinBox_MsoFreqModLfoLevel->blockSignals(true);
	ui->spinBox_MsoFreqModLfoLevel->setValue(mod_synth_get_active_mso_freq_mod_lfo_level());
	ui->spinBox_MsoFreqModLfoLevel->blockSignals(false);

	ui->comboBox_MsoFreqModAdsr->blockSignals(true);
	ui->comboBox_MsoFreqModAdsr->setCurrentIndex(mod_synth_get_active_mso_freq_mod_env());
	ui->comboBox_MsoFreqModAdsr->blockSignals(false);

	ui->dial_MsoFreqModAdsrLevel->blockSignals(true);
	ui->dial_MsoFreqModAdsrLevel->setValue(mod_synth_get_active_mso_freq_mod_env_level());
	ui->dial_MsoFreqModAdsrLevel->blockSignals(false);

	ui->spinBox_MsoFreqModAdsrLevel->blockSignals(true);
	ui->spinBox_MsoFreqModAdsrLevel->setValue(mod_synth_get_active_mso_freq_mod_env_level());
	ui->spinBox_MsoFreqModAdsrLevel->blockSignals(false);

	ui->comboBox_MsoPwmModLFO->blockSignals(true);
	ui->comboBox_MsoPwmModLFO->setCurrentIndex(mod_synth_get_active_mso_pwm_mod_lfo());
	ui->comboBox_MsoPwmModLFO->blockSignals(false);

	ui->dial_MsoPwmModLFOLevel->blockSignals(true);
	ui->dial_MsoPwmModLFOLevel->setValue(mod_synth_get_active_mso_pwm_mod_lfo_level());
	ui->dial_MsoPwmModLFOLevel->blockSignals(false);

	ui->spinBox_MsoPwmModLfoLevel->blockSignals(true);
	ui->spinBox_MsoPwmModLfoLevel->setValue(mod_synth_get_active_mso_pwm_mod_lfo_level());
	ui->spinBox_MsoPwmModLfoLevel->blockSignals(false);

	ui->comboBox_MsoPwmModAdsr->blockSignals(true);
	ui->comboBox_MsoPwmModAdsr->setCurrentIndex(mod_synth_get_active_mso_pwm_mod_env());
	ui->comboBox_MsoPwmModAdsr->blockSignals(false);

	ui->dial_MsoPwmModAdsrLevel->blockSignals(true);
	ui->dial_MsoPwmModAdsrLevel->setValue(mod_synth_get_active_mso_pwm_mod_env_level());
	ui->dial_MsoPwmModAdsrLevel->blockSignals(false);

	ui->spinBox_MsoPwmModAdsrLevel->blockSignals(true);
	ui->spinBox_MsoPwmModAdsrLevel->setValue(mod_synth_get_active_mso_pwm_mod_env_level());
	ui->spinBox_MsoPwmModAdsrLevel->blockSignals(false);

	ui->comboBox_MsoAmpModLFO->blockSignals(true);
	ui->comboBox_MsoAmpModLFO->setCurrentIndex(mod_synth_get_active_mso_amp_mod_lfo());
	ui->comboBox_MsoAmpModLFO->blockSignals(false);

	ui->dial_MsoAmpModLFOLevel->blockSignals(true);
	ui->dial_MsoAmpModLFOLevel->setValue(mod_synth_get_active_mso_amp_mod_lfo_level());
	ui->dial_MsoAmpModLFOLevel->blockSignals(false);

	ui->spinBox_MsoAmpModLfoLevel->blockSignals(true);
	ui->spinBox_MsoAmpModLfoLevel->setValue(mod_synth_get_active_mso_amp_mod_lfo_level());
	ui->spinBox_MsoAmpModLfoLevel->blockSignals(false);

	ui->comboBox_MsoAmpModAdsr->blockSignals(true);
	ui->comboBox_MsoAmpModAdsr->setCurrentIndex(mod_synth_get_active_mso_amp_mod_env());
	ui->comboBox_MsoAmpModAdsr->blockSignals(false);

	ui->dial_MsoAmpModAdsrLevel->blockSignals(true);
	ui->dial_MsoAmpModAdsrLevel->setValue(mod_synth_get_active_mso_amp_mod_env_level());
	ui->dial_MsoAmpModAdsrLevel->blockSignals(false);

	ui->spinBox_MsoAmpModAdsrLevel->blockSignals(true);
	ui->spinBox_MsoAmpModAdsrLevel->setValue(mod_synth_get_active_mso_amp_mod_env_level());
	ui->spinBox_MsoAmpModAdsrLevel->blockSignals(false);

	if (update_mso_plot == false)
	{
		// Do it only if last update was already completed.
		setup_mso_plot(ui->widget_MsoWaveformPlot);
		// Enable actual refresh waveform plot on GUI update timer interupt
		update_mso_plot = true;
	}
}

void Dialog_AnalogSynth_1900x1000::on_mso_point_a_slider_moved(int val)
{
	if ((val < 1) || (val > 2046))
	{
		return;
	}

	ui->verticalSlider_MSO_Pos_a->blockSignals(true);
	ui->verticalSlider_MSO_Pos_a->setValue(val);
	ui->verticalSlider_MSO_Pos_a->blockSignals(false);

	ui->spinBox_MSO_Pos_a->blockSignals(true);
	ui->spinBox_MSO_Pos_a->setValue(val);
	ui->spinBox_MSO_Pos_a->blockSignals(false);

	mso_pos_a = val;

	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_SEGMENT_A_POSITION, val);

	// setup_mso_plot(ui->widget_MsoWaveformPlot);  Will be initate  by the GUI update
	// ui->widget_MsoWaveformPlot->replot();
	mso_replot_waveform = true;

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_point_b_slider_moved(int val)
{
	if ((val < 1) || (val > 2046))
	{
		return;
	}

	ui->verticalSlider_MSO_Pos_b->blockSignals(true);
	ui->verticalSlider_MSO_Pos_b->setValue(val);
	ui->verticalSlider_MSO_Pos_b->blockSignals(false);

	ui->spinBox_MSO_Pos_b->blockSignals(true);
	ui->spinBox_MSO_Pos_b->setValue(val);
	ui->spinBox_MSO_Pos_b->blockSignals(false);

	mso_pos_b = val;

	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_SEGMENT_B_POSITION, val);

	// setup_mso_plot(ui->widget_MsoWaveformPlot);
	// ui->widget_MsoWaveformPlot->replot();
	mso_replot_waveform = true;

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_point_c_slider_moved(int val)
{
	if ((val < 1) || (val > 2046))
	{
		return;
	}

	ui->verticalSlider_MSO_Pos_c->blockSignals(true);
	ui->verticalSlider_MSO_Pos_c->setValue(val);
	ui->verticalSlider_MSO_Pos_c->blockSignals(false);

	ui->spinBox_MSO_Pos_c->blockSignals(true);
	ui->spinBox_MSO_Pos_c->setValue(val);
	ui->spinBox_MSO_Pos_c->blockSignals(false);

	mso_pos_c = val;

	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_SEGMENT_C_POSITION, val);

	// setup_mso_plot(ui->widget_MsoWaveformPlot);
	// ui->widget_MsoWaveformPlot->replot();
	mso_replot_waveform = true;

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_point_d_slider_moved(int val)
{
	if ((val < 1) || (val > 2046))
	{
		return;
	}

	ui->verticalSlider_MSO_Pos_d->blockSignals(true);
	ui->verticalSlider_MSO_Pos_d->setValue(val);
	ui->verticalSlider_MSO_Pos_d->blockSignals(false);

	ui->spinBox_MSO_Pos_d->blockSignals(true);
	ui->spinBox_MSO_Pos_d->setValue(val);
	ui->spinBox_MSO_Pos_d->blockSignals(false);

	mso_pos_d = val;

	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_SEGMENT_D_POSITION, val);

	// setup_mso_plot(ui->widget_MsoWaveformPlot);
	// ui->widget_MsoWaveformPlot->replot();
	mso_replot_waveform = true;

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_point_e_slider_moved(int val)
{
	if ((val < 1) || (val > 2046))
	{
		return;
	}

	ui->verticalSlider_MSO_Pos_e->blockSignals(true);
	ui->verticalSlider_MSO_Pos_e->setValue(val);
	ui->verticalSlider_MSO_Pos_e->blockSignals(false);

	ui->spinBox_MSO_Pos_e->blockSignals(true);
	ui->spinBox_MSO_Pos_e->setValue(val);
	ui->spinBox_MSO_Pos_e->blockSignals(false);

	mso_pos_e = val;

	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_SEGMENT_E_POSITION, val);

	// setup_mso_plot(ui->widget_MsoWaveformPlot);
	// ui->widget_MsoWaveformPlot->replot();
	mso_replot_waveform = true;

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_point_f_slider_moved(int val)
{
	if ((val < 1) || (val > 2046))
	{
		return;
	}

	ui->verticalSlider_MSO_Pos_f->blockSignals(true);
	ui->verticalSlider_MSO_Pos_f->setValue(val);
	ui->verticalSlider_MSO_Pos_f->blockSignals(false);

	ui->spinBox_MSO_Pos_f->blockSignals(true);
	ui->spinBox_MSO_Pos_f->setValue(val);
	ui->spinBox_MSO_Pos_f->blockSignals(false);

	mso_pos_f = val;

	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_SEGMENT_F_POSITION, val);

	// setup_mso_plot(ui->widget_MsoWaveformPlot);
	// ui->widget_MsoWaveformPlot->replot();
	mso_replot_waveform = true;

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_symetry_slider_changed(int val)
{
	if ((val < 5) || (val > 95))
	{
		return;
	}

	ui->horizontalSlider_MsoMorph->blockSignals(true);
	ui->horizontalSlider_MsoMorph->setValue(val);
	ui->horizontalSlider_MsoMorph->blockSignals(false);

	// ui->spinBox_MsoMorph->blockSignals(true);
	// ui->spinBox_MsoMorph->setValue(val);
	// ui->spinBox_MsoMorph->blockSignals(false);

	mso_symetry = val;

	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_SYMETRY, val);

	// setup_mso_plot(ui->widget_MsoWaveformPlot);
	// ui->widget_MsoWaveformPlot->replot();
	mso_replot_waveform = true;

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_detune_octave_combobox_changed(int val)
{
	ui->comboBox_MsoTuneOctave->blockSignals(true);
	ui->comboBox_MsoTuneOctave->setCurrentIndex(val);
	ui->comboBox_MsoTuneOctave->blockSignals(false);

	mso_tune_octave = val;
	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_DETUNE_OCTAVE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_detune_semitones_combobox_changed(int val)
{
	ui->comboBox_MsoTuneSemitones->blockSignals(true);
	ui->comboBox_MsoTuneSemitones->setCurrentIndex(val);
	ui->comboBox_MsoTuneSemitones->blockSignals(false);

	mso_tune_semitones = val;
	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_DETUNE_SEMITONES, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_detune_cents_combobox_changed(int val)
{
	ui->comboBox_MsoTuneCents->blockSignals(true);
	ui->comboBox_MsoTuneCents->setCurrentIndex(val);
	ui->comboBox_MsoTuneCents->blockSignals(false);

	mso_tune_cents = val;
	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_DETUNE_CENTS, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_preset_combobox_changed(int val)
{
	mso_handle_preset_change(val);
	// The above set back to default
	ui->comboBox_MsoPreset->blockSignals(true);
	ui->comboBox_MsoPreset->setCurrentIndex(val);
	ui->comboBox_MsoPreset->blockSignals(false);
}

void Dialog_AnalogSynth_1900x1000::on_mso_freq_mod_lfo_combobox_changed(int val)
{
	ui->comboBox_MsoFreqModLFO->blockSignals(true);
	ui->comboBox_MsoFreqModLFO->setCurrentIndex(val);
	ui->comboBox_MsoFreqModLFO->blockSignals(false);

	mso_freq_mod_lfo_num = val;
	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_FREQ_MOD_LFO, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_freq_mod_env_combobox_changed(int val)
{
	ui->comboBox_MsoFreqModAdsr->blockSignals(true);
	ui->comboBox_MsoFreqModAdsr->setCurrentIndex(val);
	ui->comboBox_MsoFreqModAdsr->blockSignals(false);

	mso_freq_mod_adsr_num = val;
	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_FREQ_MOD_ENV, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_pwm_mod_lfo_combobox_changed(int val)
{
	ui->comboBox_MsoPwmModLFO->blockSignals(true);
	ui->comboBox_MsoPwmModLFO->setCurrentIndex(val);
	ui->comboBox_MsoPwmModLFO->blockSignals(false);

	mso_pwm_mod_lfo_num = val;
	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_PWM_MOD_LFO, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_pwm_mod_env_combobox_changed(int val)
{
	ui->comboBox_MsoPwmModAdsr->blockSignals(true);
	ui->comboBox_MsoPwmModAdsr->setCurrentIndex(val);
	ui->comboBox_MsoPwmModAdsr->blockSignals(false);

	mso_pwm_mod_adsr_num = val;
	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_PWM_MOD_ENV, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_amp_mod_lfo_combobox_changed(int val)
{
	ui->comboBox_MsoAmpModLFO->blockSignals(true);
	ui->comboBox_MsoAmpModLFO->setCurrentIndex(val);
	ui->comboBox_MsoAmpModLFO->blockSignals(false);

	mso_amp_mod_lfo_num = val;
	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_AMP_MOD_LFO, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_amp_mod_env_combobox_changed(int val)
{
	ui->comboBox_MsoAmpModAdsr->blockSignals(true);
	ui->comboBox_MsoAmpModAdsr->setCurrentIndex(val);
	ui->comboBox_MsoAmpModAdsr->blockSignals(false);

	mso_amp_mod_adsr_num = val;
	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_AMP_MOD_ENV, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_send_filter_1_dial_changed(int val)
{
	ui->dial_MsoSendFilter1->blockSignals(true);
	ui->dial_MsoSendFilter1->setValue(val);
	ui->dial_MsoSendFilter1->blockSignals(false);

	ui->spinBox_MsoSendFilter1->blockSignals(true);
	ui->spinBox_MsoSendFilter1->setValue(val);
	ui->spinBox_MsoSendFilter1->blockSignals(false);

	mso_send_filter_1_level = val;
	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_FILTER_SEND_1, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_send_filter_2_dial_changed(int val)
{
	ui->dial_MsoSendFilter2->blockSignals(true);
	ui->dial_MsoSendFilter2->setValue(val);
	ui->dial_MsoSendFilter2->blockSignals(false);

	ui->spinBox_MsoSendFilter2->blockSignals(true);
	ui->spinBox_MsoSendFilter2->setValue(val);
	ui->spinBox_MsoSendFilter2->blockSignals(false);

	mso_send_filter_2_level = val;
	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_FILTER_SEND_2, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_freq_mod_lfo_level_dial_changed(int val)
{
	ui->dial_MsoFreqModLFOLevel->blockSignals(true);
	ui->dial_MsoFreqModLFOLevel->setValue(val);
	ui->dial_MsoFreqModLFOLevel->blockSignals(false);

	ui->spinBox_MsoFreqModLfoLevel->blockSignals(true);
	ui->spinBox_MsoFreqModLfoLevel->setValue(val);
	ui->spinBox_MsoFreqModLfoLevel->blockSignals(false);

	mso_freq_mod_lfo_level = val;
	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_FREQ_MOD_LFO_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_freq_mod_env_level_dial_changed(int val)
{
	ui->dial_MsoFreqModAdsrLevel->blockSignals(true);
	ui->dial_MsoFreqModAdsrLevel->setValue(val);
	ui->dial_MsoFreqModAdsrLevel->blockSignals(false);

	ui->spinBox_MsoFreqModAdsrLevel->blockSignals(true);
	ui->spinBox_MsoFreqModAdsrLevel->setValue(val);
	ui->spinBox_MsoFreqModAdsrLevel->blockSignals(false);

	mso_freq_mod_lfo_level = val;
	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_FREQ_MOD_ENV_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_pwm_mod_lfo_level_dial_changed(int val)
{
	ui->dial_MsoPwmModLFOLevel->blockSignals(true);
	ui->dial_MsoPwmModLFOLevel->setValue(val);
	ui->dial_MsoPwmModLFOLevel->blockSignals(false);

	ui->spinBox_MsoPwmModLfoLevel->blockSignals(true);
	ui->spinBox_MsoPwmModLfoLevel->setValue(val);
	ui->spinBox_MsoPwmModLfoLevel->blockSignals(false);

	mso_freq_mod_lfo_level = val;
	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_PWM_MOD_LFO_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_pwm_mod_env_level_dial_changed(int val)
{
	ui->dial_MsoPwmModAdsrLevel->blockSignals(true);
	ui->dial_MsoPwmModAdsrLevel->setValue(val);
	ui->dial_MsoPwmModAdsrLevel->blockSignals(false);

	ui->spinBox_MsoPwmModAdsrLevel->blockSignals(true);
	ui->spinBox_MsoPwmModAdsrLevel->setValue(val);
	ui->spinBox_MsoPwmModAdsrLevel->blockSignals(false);

	mso_freq_mod_lfo_level = val;
	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_PWM_MOD_ENV_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_amp_mod_lfo_level_dial_changed(int val)
{
	ui->dial_MsoAmpModLFOLevel->blockSignals(true);
	ui->dial_MsoAmpModLFOLevel->setValue(val);
	ui->dial_MsoAmpModLFOLevel->blockSignals(false);

	ui->spinBox_MsoAmpModLfoLevel->blockSignals(true);
	ui->spinBox_MsoAmpModLfoLevel->setValue(val);
	ui->spinBox_MsoAmpModLfoLevel->blockSignals(false);

	mso_freq_mod_lfo_level = val;
	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_AMP_MOD_LFO_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_amp_mod_env_level_dial_changed(int val)
{
	ui->dial_MsoAmpModAdsrLevel->blockSignals(true);
	ui->dial_MsoAmpModAdsrLevel->setValue(val);
	ui->dial_MsoAmpModAdsrLevel->blockSignals(false);

	ui->spinBox_MsoAmpModAdsrLevel->blockSignals(true);
	ui->spinBox_MsoAmpModAdsrLevel->setValue(val);
	ui->spinBox_MsoAmpModAdsrLevel->blockSignals(false);

	mso_freq_mod_lfo_level = val;
	mod_synth_mso_event_int(_MSO_1_EVENT, _MSO_AMP_MOD_ENV_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_mso_enable_checkbox_changed(bool val)
{
	ui->checkBox_MSOenable->blockSignals(true);
	if (val)
	{
		ui->checkBox_MSOenable->setCheckState(Qt::Checked);
		mod_synth_enable_mso();
	}
	else
	{
		ui->checkBox_MSOenable->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MSOenable->blockSignals(false);
	mod_synth_disable_mso();

	mso_enabled = val;

	mod_synth_mso_event_bool(_MSO_1_EVENT, _MSO_ENABLE, val);

	mso_update();

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
