/**
 * @file		Dialog_MSOsynthesizer_GuiInit.cpp
 *	@author		Nahum Budin
 *	@date		2-June-2026
 *	@version	1.0
 *
 *	@brief		Adj MSO Synthesizer control dialog GUI widgets initialization

 *
 */

#include "Dialog_MSOsynthesizer.h"
#include "ui_Dialog_MSOsynthesizer.h"

#include "Defs.h"

void Dialog_MSOsynthesizer::init_gui_elements()
{
	// Initialize GUI elements
	int result;

	set_signal_slots_connections();
	// mso_update();
	replot_waveform.store(true);

	// Init ADSR curve plots
	update_amp_mod_adsr_plot.store(true);
	update_freq_mod_adsr_plot.store(true);
	update_sym_mod_adsr_plot.store(true);
	update_filter_freq_mod_adsr_plot.store(true);

	adsr_curve_max_attack = mod_synth_get_adsr_max_attack_time_sec();
	adsr_curve_max_decay = mod_synth_get_adsr_max_decay_time_sec();
	adsr_curve_max_sustain = 100; //%
	adsr_curve_max_release = mod_synth_get_adsr_max_release_time_sec();

	adsr_plot_length = _MSO_SYNTH_ADSR_CURVE_START_POINT + _MSO_SYNTH_ADSR_CURVE_SUSTAIN_SEGMENT_LENGTH +
					   (adsr_curve_max_attack + adsr_curve_max_decay +
						adsr_curve_max_release) *
						   _MSO_SYNTH_ADSR_CURVE_TIME_MULTIPLIER;

	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(2);
	pen.setColor(Qt::white);

	ui->widget_MSOsynth_AmpModADSRplot->addGraph();
	ui->widget_MSOsynth_AmpModADSRplot->graph(0)->setPen(pen);
	ui->widget_MSOsynth_AmpModADSRplot->addGraph();

	// Disable auto margins completely
	ui->widget_MSOsynth_AmpModADSRplot->axisRect()->setAutoMargins(QCP::msNone);
	// After disabling auto margins, set manual margins
	ui->widget_MSOsynth_AmpModADSRplot->axisRect()->setMargins(QMargins(5, 5, 5, 5));

	ui->widget_MSOsynth_AmpModADSRplot->xAxis->setVisible(false);
	ui->widget_MSOsynth_AmpModADSRplot->xAxis->setTickLabels(true);
	ui->widget_MSOsynth_AmpModADSRplot->yAxis->setVisible(false);
	ui->widget_MSOsynth_AmpModADSRplot->yAxis->setTickLabels(true);

	ui->widget_MSOsynth_AmpModADSRplot->yAxis->setRange(0, _MSO_SYNTH_ADSR_CURVE_HEIGHT);
	ui->widget_MSOsynth_AmpModADSRplot->xAxis->setRange(0, adsr_plot_length);

	ui->widget_MSOsynth_AmpModADSRplot->setMinimumSize(adsr_plot_length, _MSO_SYNTH_ADSR_CURVE_HEIGHT);
	ui->widget_MSOsynth_AmpModADSRplot->setBackground(QBrush(_CONTROLS_COLOR_BLACK));

	ui->widget_MSOsynth_FreqModADSRplot->addGraph();
	ui->widget_MSOsynth_FreqModADSRplot->graph(0)->setPen(pen);
	ui->widget_MSOsynth_FreqModADSRplot->addGraph();

	// Disable auto margins completely
	ui->widget_MSOsynth_FreqModADSRplot->axisRect()->setAutoMargins(QCP::msNone);
	// After disabling auto margins, set manual margins
	ui->widget_MSOsynth_FreqModADSRplot->axisRect()->setMargins(QMargins(5, 5, 5, 5));

	ui->widget_MSOsynth_FreqModADSRplot->xAxis->setVisible(false);
	ui->widget_MSOsynth_FreqModADSRplot->xAxis->setTickLabels(true);
	ui->widget_MSOsynth_FreqModADSRplot->yAxis->setVisible(false);
	ui->widget_MSOsynth_FreqModADSRplot->yAxis->setTickLabels(true);

	ui->widget_MSOsynth_FreqModADSRplot->yAxis->setRange(0, _MSO_SYNTH_ADSR_CURVE_HEIGHT);
	ui->widget_MSOsynth_FreqModADSRplot->xAxis->setRange(0, adsr_plot_length);

	ui->widget_MSOsynth_FreqModADSRplot->setMinimumSize(adsr_plot_length, _MSO_SYNTH_ADSR_CURVE_HEIGHT);
	ui->widget_MSOsynth_FreqModADSRplot->setBackground(QBrush(_CONTROLS_COLOR_BLACK));

	/*
	ui->widget_MSOsynth_PwmModADSRplot->addGraph();
	ui->widget_MSOsynth_PwmModADSRplot->graph(0)->setPen(pen);
	ui->widget_MSOsynth_PwmModADSRplot->addGraph();

	ui->widget_MSOsynth_PwmModADSRplot->xAxis->setVisible(false);
	ui->widget_MSOsynth_PwmModADSRplot->xAxis->setTickLabels(true);
	ui->widget_MSOsynth_PwmModADSRplot->yAxis->setVisible(false);
	ui->widget_MSOsynth_PwmModADSRplot->yAxis->setTickLabels(true);

	ui->widget_MSOsynth_PwmModADSRplot->yAxis->setRange(0, _MSO_SYNTH_ADSR_CURVE_HEIGHT);
	ui->widget_MSOsynth_PwmModADSRplot->xAxis->setRange(0, adsr_plot_length);

	ui->widget_MSOsynth_PwmModADSRplot->setMinimumSize(adsr_plot_length, _MSO_SYNTH_ADSR_CURVE_HEIGHT);
	ui->widget_MSOsynth_PwmModADSRplot->setBackground(QBrush(_CONTROLS_COLOR_BLACK));
	*/

	ui->widget_MSOsynth_FilterFreqModADSRplot->addGraph();
	ui->widget_MSOsynth_FilterFreqModADSRplot->graph(0)->setPen(pen);
	ui->widget_MSOsynth_FilterFreqModADSRplot->addGraph();

	// Disable auto margins completely
	ui->widget_MSOsynth_FilterFreqModADSRplot->axisRect()->setAutoMargins(QCP::msNone);
	// After disabling auto margins, set manual margins
	ui->widget_MSOsynth_FilterFreqModADSRplot->axisRect()->setMargins(QMargins(5, 5, 5, 5));

	ui->widget_MSOsynth_FilterFreqModADSRplot->xAxis->setVisible(false);
	ui->widget_MSOsynth_FilterFreqModADSRplot->xAxis->setTickLabels(true);
	ui->widget_MSOsynth_FilterFreqModADSRplot->yAxis->setVisible(false);
	ui->widget_MSOsynth_FilterFreqModADSRplot->yAxis->setTickLabels(true);

	ui->widget_MSOsynth_FilterFreqModADSRplot->yAxis->setRange(0, _MSO_SYNTH_ADSR_CURVE_HEIGHT);
	ui->widget_MSOsynth_FilterFreqModADSRplot->xAxis->setRange(0, adsr_plot_length);

	ui->widget_MSOsynth_FilterFreqModADSRplot->setMinimumSize(adsr_plot_length, _MSO_SYNTH_ADSR_CURVE_HEIGHT);
	ui->widget_MSOsynth_FilterFreqModADSRplot->setBackground(QBrush(_CONTROLS_COLOR_BLACK));
	
	// Prepare MSO Presets Strings
	if (string_presets_list.size() == 0)
	{
		string_presets_list.append("Sine");
		string_presets_list.append("Square");
		string_presets_list.append("Pulse");
		string_presets_list.append("Sawtooth");
	}

	if (string_waveforms_list.size() == 0)
	{
		string_waveforms_list.append("Sine");
		string_waveforms_list.append("Square");
		string_waveforms_list.append("Pulse");
		string_waveforms_list.append("Triangle");
		string_waveforms_list.append("Samp&Hold");
	}

	if (string_filters_bands.isEmpty())
	{
		string_filters_bands.append("Low Pass");
		string_filters_bands.append("High Pass");
		string_filters_bands.append("Band Pass");
		string_filters_bands.append("All Pass");
	}

	// Send and Tune frame and controls
	ui->dial_MsoSynthSendFilter->setKnobColor(_KNOBS_COLOR);
	ui->dial_MsoSynthSendFilter->setCircleColor(_CONTROLS_COLOR_GRAY);
	ui->dial_MsoSynthSendFilter->setValue(40);

	ui->comboBox_MsoSynthTuneOctave->blockSignals(true);
	ui->comboBox_MsoSynthTuneSemitones->blockSignals(true);
	ui->comboBox_MsoSynthTuneCents->blockSignals(true);

	ui->comboBox_MsoSynthTuneOctave->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_MsoSynthTuneOctave->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_MsoSynthTuneOctave->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->comboBox_MsoSynthTuneOctave->setFrameWidth(2);
	ui->comboBox_MsoSynthTuneOctave->setCurrentIndex(mod_synth_get_active_osc1_detune_octave() - mod_synth_get_osc_detune_min_octave());

	ui->comboBox_MsoSynthTuneSemitones->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_MsoSynthTuneSemitones->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_MsoSynthTuneSemitones->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->comboBox_MsoSynthTuneSemitones->setFrameWidth(2);
	ui->comboBox_MsoSynthTuneSemitones->setCurrentIndex(mod_synth_get_active_osc1_detune_semitones() - mod_synth_get_osc_detune_min_semitones());

	ui->comboBox_MsoSynthTuneCents->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_MsoSynthTuneCents->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_MsoSynthTuneCents->setFrameColor(_CONTROLS_COLOR_GREEN);
	ui->comboBox_MsoSynthTuneCents->setFrameWidth(2);
	ui->comboBox_MsoSynthTuneCents->setCurrentIndex(mod_synth_get_active_osc1_detune_cents() - mod_synth_get_osc_detune_min_cents() * 4.f);

	for (int i = _OSC_DETUNE_MIN_OCTAVE; i <= _OSC_DETUNE_MAX_OCTAVE; i++)
	{
		ui->comboBox_MsoSynthTuneOctave->addItem(QString::number(i));
	}

	for (int i = _OSC_DETUNE_MIN_SEMITONES; i <= _OSC_DETUNE_MAX_SEMITONES; i++)
	{
		ui->comboBox_MsoSynthTuneSemitones->addItem(QString::number(i));
	}

	for (int i = 4 * _OSC_DETUNE_MIN_CENTS; i <= 4 * _OSC_DETUNE_MAX_CENTS; i++)
	{
		// 0.25 steps
		ui->comboBox_MsoSynthTuneCents->addItem(QString::number(i / 4.f));
	}

	ui->comboBox_MsoSynthTuneOctave->blockSignals(false);
	ui->comboBox_MsoSynthTuneSemitones->blockSignals(false);
	ui->comboBox_MsoSynthTuneCents->blockSignals(false);

	// Presets Controls
	ui->pushButton_MSOsynth_PresetOpen->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->pushButton_MSOsynth_PresetOpen->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);

	ui->pushButton_MSOsynth_PresetSave->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->pushButton_MSOsynth_PresetSave->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);

	// MSO Segments frame and controls
	ui->verticalSlider_MSOSynth_Pos_a->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_MSOSynth_Pos_a->setFrameColor(_CONTROLS_COLOR_GRAY);
	ui->verticalSlider_MSOSynth_Pos_a->setProgressColor(_CONTROLS_COLOR_GRAY);
	ui->verticalSlider_MSOSynth_Pos_a->setHandleColor(_CONTROLS_COLOR_GRAY);

	ui->verticalSlider_MSOSynth_Pos_b->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_MSOSynth_Pos_b->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_MSOSynth_Pos_b->setProgressColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_MSOSynth_Pos_b->setHandleColor(_CONTROLS_COLOR_PURPLE);

	ui->verticalSlider_MSOSynth_Pos_c->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_MSOSynth_Pos_c->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_MSOSynth_Pos_c->setProgressColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_MSOSynth_Pos_c->setHandleColor(_CONTROLS_COLOR_BLUE);

	ui->verticalSlider_MSOSynth_Pos_d->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_MSOSynth_Pos_d->setFrameColor(_CONTROLS_COLOR_GREEN);
	ui->verticalSlider_MSOSynth_Pos_d->setProgressColor(_CONTROLS_COLOR_GREEN);
	ui->verticalSlider_MSOSynth_Pos_d->setHandleColor(_CONTROLS_COLOR_GREEN);

	ui->verticalSlider_MSOSynth_Pos_e->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_MSOSynth_Pos_e->setFrameColor(_CONTROLS_COLOR_WHITE);
	ui->verticalSlider_MSOSynth_Pos_e->setProgressColor(_CONTROLS_COLOR_WHITE);
	ui->verticalSlider_MSOSynth_Pos_e->setHandleColor(_CONTROLS_COLOR_WHITE);

	ui->verticalSlider_MSOSynth_Pos_f->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_MSOSynth_Pos_f->setFrameColor(_CONTROLS_COLOR_YELLOW);
	ui->verticalSlider_MSOSynth_Pos_f->setProgressColor(_CONTROLS_COLOR_YELLOW);
	ui->verticalSlider_MSOSynth_Pos_f->setHandleColor(_CONTROLS_COLOR_YELLOW);

	ui->horizontalSlider_MsoSynthMorph->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->horizontalSlider_MsoSynthMorph->setFrameColor(_CONTROLS_COLOR_RED);
	ui->horizontalSlider_MsoSynthMorph->setProgressColor(_CONTROLS_COLOR_RED);
	ui->horizontalSlider_MsoSynthMorph->setHandleColor(_CONTROLS_COLOR_RED);

	ui->comboBox_MsoSynthPreset->blockSignals(true);
	ui->comboBox_MsoSynthPreset->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_MsoSynthPreset->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_MsoSynthPreset->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->comboBox_MsoSynthPreset->setFrameWidth(2);
	ui->comboBox_MsoSynthPreset->addItems(string_presets_list);
	ui->comboBox_MsoSynthPreset->setCurrentIndex(0);
	ui->comboBox_MsoSynthPreset->blockSignals(false);

	// MSO Amplitude Modulation frame and controls
	ui->dial_MSOsynth_AmpModAdsrLevel->setKnobColor(_KNOBS_COLOR);
	ui->dial_MSOsynth_AmpModAdsrLevel->setCircleColor(_CONTROLS_COLOR_PURPLE);
	ui->dial_MSOsynth_AmpModAdsrLevel->setValue(0);

	ui->dial_MSOsynth_AmpModLFOLevel->setKnobColor(_KNOBS_COLOR);
	ui->dial_MSOsynth_AmpModLFOLevel->setCircleColor(_CONTROLS_COLOR_BLUE);
	ui->dial_MSOsynth_AmpModLFOLevel->setValue(0);

	ui->comboBox_MSOsynth_AmpModLFOwaveform->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_MSOsynth_AmpModLFOwaveform->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_MSOsynth_AmpModLFOwaveform->setFrameColor(_CONTROLS_COLOR_GREEN);
	ui->comboBox_MSOsynth_AmpModLFOwaveform->setFrameWidth(2);
	ui->comboBox_MSOsynth_AmpModLFOwaveform->addItems(string_waveforms_list);
	ui->comboBox_MSOsynth_AmpModLFOwaveform->setCurrentIndex(0);

	ui->dial_MSOsynth_AmpModLFOsymmetry->setKnobColor(_KNOBS_COLOR);
	ui->dial_MSOsynth_AmpModLFOsymmetry->setCircleColor(_CONTROLS_COLOR_WHITE);
	ui->dial_MSOsynth_AmpModLFOsymmetry->setValue(0);

	ui->dial_MSOsynth_AmpModLFOrate->setKnobColor(_KNOBS_COLOR);
	ui->dial_MSOsynth_AmpModLFOrate->setCircleColor(_CONTROLS_COLOR_YELLOW);
	ui->dial_MSOsynth_AmpModLFOrate->setValue(0);

	ui->verticalSlider_MSOsynth_AmpModAdsrA->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_MSOsynth_AmpModAdsrA->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_MSOsynth_AmpModAdsrA->setProgressColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_MSOsynth_AmpModAdsrA->setHandleColor(_CONTROLS_COLOR_PURPLE);

	ui->verticalSlider_MSOsynth_AmpModAdsrD->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_MSOsynth_AmpModAdsrD->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_MSOsynth_AmpModAdsrD->setProgressColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_MSOsynth_AmpModAdsrD->setHandleColor(_CONTROLS_COLOR_BLUE);

	ui->verticalSlider_MSOsynth_AmpModAdsrS->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_MSOsynth_AmpModAdsrS->setFrameColor(_CONTROLS_COLOR_GREEN);
	ui->verticalSlider_MSOsynth_AmpModAdsrS->setProgressColor(_CONTROLS_COLOR_GREEN);
	ui->verticalSlider_MSOsynth_AmpModAdsrS->setHandleColor(_CONTROLS_COLOR_GREEN);

	ui->verticalSlider_MSOsynth_AmpModAdsrR->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_MSOsynth_AmpModAdsrR->setFrameColor(_CONTROLS_COLOR_WHITE);
	ui->verticalSlider_MSOsynth_AmpModAdsrR->setProgressColor(_CONTROLS_COLOR_WHITE);
	ui->verticalSlider_MSOsynth_AmpModAdsrR->setHandleColor(_CONTROLS_COLOR_WHITE);

	// MSO Frequency Modulation frame and controls
	ui->dial_MSOsynth_FreqModAdsrLevel->setKnobColor(_KNOBS_COLOR);
	ui->dial_MSOsynth_FreqModAdsrLevel->setCircleColor(_CONTROLS_COLOR_PURPLE);
	ui->dial_MSOsynth_FreqModAdsrLevel->setValue(0);

	ui->dial_MSOsynth_FreqModLFOLevel->setKnobColor(_KNOBS_COLOR);
	ui->dial_MSOsynth_FreqModLFOLevel->setCircleColor(_CONTROLS_COLOR_BLUE);
	ui->dial_MSOsynth_FreqModLFOLevel->setValue(0);

	ui->comboBox_MSOsynth_FreqModLFOwaveform->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_MSOsynth_FreqModLFOwaveform->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_MSOsynth_FreqModLFOwaveform->setFrameColor(_CONTROLS_COLOR_GREEN);
	ui->comboBox_MSOsynth_FreqModLFOwaveform->setFrameWidth(2);
	ui->comboBox_MSOsynth_FreqModLFOwaveform->addItems(string_waveforms_list);
	ui->comboBox_MSOsynth_FreqModLFOwaveform->setCurrentIndex(0);

	ui->dial_MSOsynth_FreqModLFOsymmetry->setKnobColor(_KNOBS_COLOR);
	ui->dial_MSOsynth_FreqModLFOsymmetry->setCircleColor(_CONTROLS_COLOR_WHITE);
	ui->dial_MSOsynth_FreqModLFOsymmetry->setValue(0);

	ui->dial_MSOsynth_FreqModLFOrate->setKnobColor(_KNOBS_COLOR);
	ui->dial_MSOsynth_FreqModLFOrate->setCircleColor(_CONTROLS_COLOR_YELLOW);
	ui->dial_MSOsynth_FreqModLFOrate->setValue(0);

	ui->verticalSlider_MSOsynth_FreqModAdsrA->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_MSOsynth_FreqModAdsrA->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_MSOsynth_FreqModAdsrA->setProgressColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_MSOsynth_FreqModAdsrA->setHandleColor(_CONTROLS_COLOR_PURPLE);

	ui->verticalSlider_MSOsynth_FreqModAdsrD->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_MSOsynth_FreqModAdsrD->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_MSOsynth_FreqModAdsrD->setProgressColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_MSOsynth_FreqModAdsrD->setHandleColor(_CONTROLS_COLOR_BLUE);

	ui->verticalSlider_MSOsynth_FreqModAdsrS->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_MSOsynth_FreqModAdsrS->setFrameColor(_CONTROLS_COLOR_GREEN);
	ui->verticalSlider_MSOsynth_FreqModAdsrS->setProgressColor(_CONTROLS_COLOR_GREEN);
	ui->verticalSlider_MSOsynth_FreqModAdsrS->setHandleColor(_CONTROLS_COLOR_GREEN);

	ui->verticalSlider_MSOsynth_FreqModAdsrR->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_MSOsynth_FreqModAdsrR->setFrameColor(_CONTROLS_COLOR_WHITE);
	ui->verticalSlider_MSOsynth_FreqModAdsrR->setProgressColor(_CONTROLS_COLOR_WHITE);
	ui->verticalSlider_MSOsynth_FreqModAdsrR->setHandleColor(_CONTROLS_COLOR_WHITE);	

	// Filter Controls
	ui->dial_MsoSynthFilterFreq->setKnobColor(_KNOBS_COLOR);
	ui->dial_MsoSynthFilterFreq->setCircleColor(_CONTROLS_COLOR_GRAY);
	ui->dial_MsoSynthFilterFreq->setValue(50);

	ui->dial_MsoSynthFilterOctave->setKnobColor(_KNOBS_COLOR);
	ui->dial_MsoSynthFilterOctave->setCircleColor(_CONTROLS_COLOR_PURPLE);
	ui->dial_MsoSynthFilterOctave->setValue(50);

	ui->dial_MsoSynthFilterQ->setKnobColor(_KNOBS_COLOR);
	ui->dial_MsoSynthFilterQ->setCircleColor(_CONTROLS_COLOR_BLUE);
	ui->dial_MsoSynthFilterQ->setValue(50);

	ui->dial_MsoSynthFilterKbdTrack->setKnobColor(_KNOBS_COLOR);
	ui->dial_MsoSynthFilterKbdTrack->setCircleColor(_CONTROLS_COLOR_GREEN);
	ui->dial_MsoSynthFilterKbdTrack->setValue(100);

	ui->comboBox_MsoSynthFilterBand->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_MsoSynthFilterBand->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_MsoSynthFilterBand->setFrameColor(_CONTROLS_COLOR_WHITE);
	ui->comboBox_MsoSynthFilterBand->setFrameWidth(2);
	ui->comboBox_MsoSynthFilterBand->addItems(string_filters_bands);
	ui->comboBox_MsoSynthFilterBand->setCurrentIndex(0);

	// Filter Frequency Modulation frame and controls
	ui->dial_MSOsynth_FilterFreqModAdsrLevel->setKnobColor(_KNOBS_COLOR);
	ui->dial_MSOsynth_FilterFreqModAdsrLevel->setCircleColor(_CONTROLS_COLOR_PURPLE);
	ui->dial_MSOsynth_FilterFreqModAdsrLevel->setValue(0);

	ui->dial_MSOsynth_FilterFreqModLFOLevel->setKnobColor(_KNOBS_COLOR);
	ui->dial_MSOsynth_FilterFreqModLFOLevel->setCircleColor(_CONTROLS_COLOR_BLUE);
	ui->dial_MSOsynth_FilterFreqModLFOLevel->setValue(0);

	ui->comboBox_MSOsynth_FilterFreqModLFOwaveform->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_MSOsynth_FilterFreqModLFOwaveform->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_MSOsynth_FilterFreqModLFOwaveform->setFrameColor(_CONTROLS_COLOR_GREEN);
	ui->comboBox_MSOsynth_FilterFreqModLFOwaveform->setFrameWidth(2);
	ui->comboBox_MSOsynth_FilterFreqModLFOwaveform->addItems(string_waveforms_list);
	ui->comboBox_MSOsynth_FilterFreqModLFOwaveform->setCurrentIndex(0);

	ui->dial_MSOsynth_FilterFreqModLFOsymmetry->setKnobColor(_KNOBS_COLOR);
	ui->dial_MSOsynth_FilterFreqModLFOsymmetry->setCircleColor(_CONTROLS_COLOR_WHITE);
	ui->dial_MSOsynth_FilterFreqModLFOsymmetry->setValue(0);

	ui->dial_MSOsynth_FilterFreqModLFOrate->setKnobColor(_KNOBS_COLOR);
	ui->dial_MSOsynth_FilterFreqModLFOrate->setCircleColor(_CONTROLS_COLOR_YELLOW);
	ui->dial_MSOsynth_FilterFreqModLFOrate->setValue(0);

	ui->verticalSlider_MSOsynth_FilterFreqModAdsrA->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrA->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrA->setProgressColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrA->setHandleColor(_CONTROLS_COLOR_PURPLE);

	ui->verticalSlider_MSOsynth_FilterFreqModAdsrD->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrD->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrD->setProgressColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrD->setHandleColor(_CONTROLS_COLOR_BLUE);

	ui->verticalSlider_MSOsynth_FilterFreqModAdsrS->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrS->setFrameColor(_CONTROLS_COLOR_GREEN);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrS->setProgressColor(_CONTROLS_COLOR_GREEN);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrS->setHandleColor(_CONTROLS_COLOR_GREEN);

	ui->verticalSlider_MSOsynth_FilterFreqModAdsrR->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrR->setFrameColor(_CONTROLS_COLOR_WHITE);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrR->setProgressColor(_CONTROLS_COLOR_WHITE);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrR->setHandleColor(_CONTROLS_COLOR_WHITE);

	update_amp_mod_adsr_plot.store(true);
	update_sym_mod_adsr_plot.store(true);
	update_freq_mod_adsr_plot.store(true);
	update_filter_freq_mod_adsr_plot.store(true);

	update_gui();
}