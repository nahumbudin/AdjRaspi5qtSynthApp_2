/**
 * @file		Osc2Gui.cpp
 *	@author		Nahum Budin
 *	@date		21-Dec-2025
 *	@version	2.0
 *
 *	@brief		Analog Synthesizer instrument Osc2 GUI handling
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

int Dialog_AnalogSynth_1900x1000::init_osc2_gui()
{
	int result;

	set_osc2_signals_connections();
	osc2_update();

	// OSC2 Waveform frame and controls
	result = init_frame_colors(ui->frame_Osc2Waveform);

	result = init_combobox_control_colors(ui->comboBox_Osc2Waveform);
	ui->comboBox_Osc2Waveform->blockSignals(true);
	ui->comboBox_Osc2Waveform->addItems(string_waveforms_list);
	ui->comboBox_Osc2Waveform->blockSignals(false);

	result = init_horizontal_slider_control_colors(ui->horizontalSlider_Osc2Symmetry);
	result = init_dial_control_colors(ui->dial_Osc2SendFilter1);
	result = init_dial_control_colors(ui->dial_Osc2SendFilter2);

	// OSC2 TuneOffset frame and controls
	result = init_frame_colors(ui->frame_Osc2TuneOffset);

	result = init_combobox_control_colors(ui->comboBox_Osc2TuneOctave);
	result = init_combobox_control_colors(ui->comboBox_Osc2TuneSemitones);
	result = init_combobox_control_colors(ui->comboBox_Osc2TuneCents);

	ui->comboBox_Osc2TuneOctave->blockSignals(true);
	ui->comboBox_Osc2TuneSemitones->blockSignals(true);
	ui->comboBox_Osc2TuneCents->blockSignals(true);

	for (int i = _OSC_DETUNE_MIN_OCTAVE; i <= _OSC_DETUNE_MAX_OCTAVE; i++)
	{
		ui->comboBox_Osc2TuneOctave->addItem(QString::number(i));
	}

	for (int i = _OSC_DETUNE_MIN_SEMITONES; i <= _OSC_DETUNE_MAX_SEMITONES; i++)
	{
		ui->comboBox_Osc2TuneSemitones->addItem(QString::number(i));
	}

	for (int i = 4 * _OSC_DETUNE_MIN_CENTS; i <= 4 * _OSC_DETUNE_MAX_CENTS; i++)
	{
		// 0.25 steps
		ui->comboBox_Osc2TuneCents->addItem(QString::number(i / 4.f));
	}

	ui->comboBox_Osc2TuneOctave->blockSignals(false);
	ui->comboBox_Osc2TuneSemitones->blockSignals(false);
	ui->comboBox_Osc2TuneCents->blockSignals(false);
	ui->comboBox_Osc2TuneOctave->setFrameWidth(2);

	// OSC2 Frequency Modulation frame and controls
	result = init_frame_colors(ui->frame_Osc2FreqMod);

	result = init_dial_control_colors(ui->dial_Osc2FreqModLFOLevel);
	result = init_dial_control_colors(ui->dial_Osc2FreqModAdsrLevel);

	result = init_combobox_control_colors(ui->comboBox_Osc2FreqModLFO);
	ui->comboBox_Osc2FreqModLFO->blockSignals(true);
	ui->comboBox_Osc2FreqModLFO->addItems(string_lfo_values);
	ui->comboBox_Osc2FreqModLFO->setIdentifier(_OSC2_FREQ_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_Osc2FreqModLFO->blockSignals(false);

	result = init_combobox_control_colors(ui->comboBox_Osc2FreqModAdsr);
	ui->comboBox_Osc2FreqModAdsr->blockSignals(true);
	ui->comboBox_Osc2FreqModAdsr->addItems(string_adsr_values);
	ui->comboBox_Osc2FreqModAdsr->setIdentifier(_OSC2_FREQ_MOD_ADSR_COMBOBOX_INDEX);
	ui->comboBox_Osc2FreqModAdsr->blockSignals(false);

	// OSC2 Amplitude Modulation frame and controls
	result = init_frame_colors(ui->frame_Osc2AmpMod);

	result = init_dial_control_colors(ui->dial_Osc2AmpModLFOLevel);
	result = init_dial_control_colors(ui->dial_Osc2AmpModAdsrLevel);

	result = init_combobox_control_colors(ui->comboBox_Osc2AmpModLFO);
	ui->comboBox_Osc2AmpModLFO->blockSignals(true);
	ui->comboBox_Osc2AmpModLFO->addItems(string_lfo_values);
	ui->comboBox_Osc2AmpModLFO->setIdentifier(_OSC2_AMP_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_Osc2AmpModLFO->blockSignals(false);

	result = init_combobox_control_colors(ui->comboBox_Osc2AmpModAdsr);
	ui->comboBox_Osc2AmpModAdsr->blockSignals(true);
	ui->comboBox_Osc2AmpModAdsr->addItems(string_adsr_values);
	ui->comboBox_Osc2AmpModAdsr->setIdentifier(_OSC2_AMP_MOD_ADSR_COMBOBOX_INDEX);
	ui->comboBox_Osc2AmpModAdsr->blockSignals(false);

	// OSC2 PWM Modulation frame and controls
	result = init_frame_colors(ui->frame_Osc2PwmMod);

	result = init_dial_control_colors(ui->dial_Osc2PwmModLFOLevel);
	result = init_dial_control_colors(ui->dial_Osc2PwmModAdsrLevel);

	result = init_combobox_control_colors(ui->comboBox_Osc2PwmModLFO);
	ui->comboBox_Osc2PwmModLFO->blockSignals(true);
	ui->comboBox_Osc2PwmModLFO->addItems(string_lfo_values);
	ui->comboBox_Osc2PwmModLFO->setIdentifier(_OSC2_PWM_MOD_LFO_COMBOBOX_INDEX);
	ui->comboBox_Osc2PwmModLFO->blockSignals(false);

	result = init_combobox_control_colors(ui->comboBox_Osc2PwmModAdsr);
	ui->comboBox_Osc2PwmModAdsr->blockSignals(true);
	ui->comboBox_Osc2PwmModAdsr->addItems(string_adsr_values);
	ui->comboBox_Osc2PwmModAdsr->setIdentifier(_OSC2_PWM_MOD_ADSR_COMBOBOX_INDEX);
	ui->comboBox_Osc2PwmModAdsr->blockSignals(false);

	return 0;
}

void Dialog_AnalogSynth_1900x1000::set_osc2_signals_connections()
{
	connect(ui->horizontalSlider_Osc2Symmetry,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_osc2_waveform_symmetry_slider_cahanged(int)));

	connect(ui->spinBox_Osc2Symmetry,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_osc2_waveform_symmetry_spinbox_changed(int)));

	connect(ui->spinBox_Osc2SendFilter1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_osc2_send_filter_1_spinbox_changed(int)));

	connect(ui->spinBox_Osc2SendFilter2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_osc2_send_filter_2_spinbox_changed(int)));

	connect(ui->spinBox_Osc2FreqModLfoLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_osc2_freq_mod_lfo_level_spinbox_changed(int)));

	connect(ui->spinBox_Osc2FreqModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_osc2_freq_mod_adsr_level_spinbox_changed(int)));

	connect(ui->spinBox_Osc2PwmModLfoLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_osc2_pwm_mod_lfo_level_spinbox_changed(int)));

	connect(ui->spinBox_Osc2PwmModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_osc2_pwm_mod_adsr_level_spinbox_changed(int)));

	connect(ui->spinBox_Osc2AmpModLfoLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_osc2_amp_mod_lfo_level_spinbox_changed(int)));

	connect(ui->spinBox_Osc2AmpModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_osc2_amp_mod_adsr_level_spinbox_changed(int)));

	connect(ui->dial_Osc2SendFilter1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_osc2_send_filter_1_dial_changed(int)));

	connect(ui->dial_Osc2SendFilter2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_osc2_send_filter_2_dial_changed(int)));

	connect(ui->dial_Osc2FreqModLFOLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_osc2_freq_mod_lfo_level_dial_changed(int)));

	connect(ui->dial_Osc2FreqModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_osc2_freq_mod_adsr_level_dial_changed(int)));

	connect(ui->dial_Osc2PwmModLFOLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_osc2_pwm_mod_lfo_level_dial_changed(int)));

	connect(ui->dial_Osc2PwmModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_osc2_pwm_mod_adsr_level_dial_changed(int)));

	connect(ui->dial_Osc2AmpModLFOLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_osc2_amp_mod_lfo_level_dial_changed(int)));

	connect(ui->dial_Osc2AmpModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_osc2_amp_mod_adsr_level_dial_changed(int)));

	connect(ui->comboBox_Osc2AmpModAdsr,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_osc2_amp_mod_adsr_combobox_changed(int)));

	connect(ui->comboBox_Osc2AmpModLFO,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_osc2_amp_mod_lfo_combobox_changed(int)));

	connect(ui->comboBox_Osc2FreqModAdsr,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_osc2_freq_mod_adsr_combobox_changed(int)));

	connect(ui->comboBox_Osc2FreqModLFO,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_osc2_freq_mod_lfo_combobox_changed(int)));

	connect(ui->comboBox_Osc2PwmModAdsr,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_osc2_pwm_mod_adsr_combobox_changed(int)));

	connect(ui->comboBox_Osc2PwmModLFO,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_osc2_pwm_mod_lfo_combobox_changed(int)));

	connect(ui->comboBox_Osc2TuneCents,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_osc2_tune_cents_combobox_changed(int)));

	connect(ui->comboBox_Osc2TuneOctave,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_osc2_tune_octave_combobox_changed(int)));

	connect(ui->comboBox_Osc2TuneSemitones,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_osc2_tune_semitones_combobox_changed(int)));

	connect(ui->comboBox_Osc2Waveform,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_osc2_waveform_combobox_changed(int)));

	connect(ui->checkBox_Osc2Active,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_osc2_enable_changed(bool)));

	connect(ui->checkBox_Osc2SyncOnOsc1,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_osc2_sync_on_osc1_enable_changed(bool)));
}

void Dialog_AnalogSynth_1900x1000::osc2_update()
{
	ui->comboBox_Osc2Waveform->blockSignals(true);
	ui->comboBox_Osc2Waveform->setCurrentIndex(mod_synth_get_active_osc2_waveform());
	ui->comboBox_Osc2Waveform->blockSignals(false);

	ui->horizontalSlider_Osc2Symmetry->blockSignals(true);
	ui->horizontalSlider_Osc2Symmetry->setValue(mod_synth_get_active_osc2_pwm_percents());
	ui->horizontalSlider_Osc2Symmetry->blockSignals(false);

	ui->spinBox_Osc2Symmetry->blockSignals(true);
	ui->spinBox_Osc2Symmetry->setValue(mod_synth_get_active_osc2_pwm_percents());
	ui->spinBox_Osc2Symmetry->blockSignals(false);

	ui->comboBox_Osc2TuneOctave->blockSignals(true);
	ui->comboBox_Osc2TuneOctave->setCurrentIndex(mod_synth_get_active_osc2_detune_octave() -
												 mod_synth_get_osc_detune_min_octave());
	ui->comboBox_Osc2TuneOctave->blockSignals(false);

	ui->comboBox_Osc2TuneSemitones->blockSignals(true);
	ui->comboBox_Osc2TuneSemitones->setCurrentIndex(mod_synth_get_active_osc2_detune_semitones() -
													mod_synth_get_osc_detune_min_semitones());
	ui->comboBox_Osc2TuneSemitones->blockSignals(false);

	ui->comboBox_Osc2TuneCents->blockSignals(true);
	ui->comboBox_Osc2TuneCents->setCurrentIndex(mod_synth_get_active_osc2_detune_cents() -
												mod_synth_get_osc_detune_min_cents() * 4.f);
	ui->comboBox_Osc2TuneCents->blockSignals(false);

	ui->dial_Osc2SendFilter1->blockSignals(true);
	ui->dial_Osc2SendFilter1->setValue(mod_synth_get_active_osc2_send_filter_1());
	ui->dial_Osc2SendFilter1->blockSignals(false);

	ui->spinBox_Osc2SendFilter1->blockSignals(true);
	ui->spinBox_Osc2SendFilter1->setValue(mod_synth_get_active_osc2_send_filter_1());
	ui->spinBox_Osc2SendFilter1->blockSignals(false);

	ui->dial_Osc2SendFilter2->blockSignals(true);
	ui->dial_Osc2SendFilter2->setValue(mod_synth_get_active_osc2_send_filter_2());
	ui->dial_Osc2SendFilter2->blockSignals(false);

	ui->spinBox_Osc2SendFilter2->blockSignals(true);
	ui->spinBox_Osc2SendFilter2->setValue(mod_synth_get_active_osc2_send_filter_2());
	ui->spinBox_Osc2SendFilter2->blockSignals(false);

	ui->comboBox_Osc2FreqModLFO->blockSignals(true);
	ui->comboBox_Osc2FreqModLFO->setCurrentIndex(mod_synth_get_active_osc2_freq_mod_lfo());
	ui->comboBox_Osc2FreqModLFO->blockSignals(false);

	ui->dial_Osc2FreqModLFOLevel->blockSignals(true);
	ui->dial_Osc2FreqModLFOLevel->setValue(mod_synth_get_active_osc2_freq_mod_lfo_level());
	ui->dial_Osc2FreqModLFOLevel->blockSignals(false);

	ui->spinBox_Osc2FreqModLfoLevel->blockSignals(true);
	ui->spinBox_Osc2FreqModLfoLevel->setValue(mod_synth_get_active_osc2_freq_mod_lfo_level());
	ui->spinBox_Osc2FreqModLfoLevel->blockSignals(false);

	ui->comboBox_Osc2FreqModAdsr->blockSignals(true);
	ui->comboBox_Osc2FreqModAdsr->setCurrentIndex(mod_synth_get_active_osc2_freq_mod_env());
	ui->comboBox_Osc2FreqModAdsr->blockSignals(false);

	ui->dial_Osc2FreqModAdsrLevel->blockSignals(true);
	ui->dial_Osc2FreqModAdsrLevel->setValue(mod_synth_get_active_osc2_freq_mod_env_level());
	ui->dial_Osc2FreqModAdsrLevel->blockSignals(false);

	ui->spinBox_Osc2FreqModAdsrLevel->blockSignals(true);
	ui->spinBox_Osc2FreqModAdsrLevel->setValue(mod_synth_get_active_osc2_freq_mod_env_level());
	ui->spinBox_Osc2FreqModAdsrLevel->blockSignals(false);

	ui->comboBox_Osc2PwmModLFO->blockSignals(true);
	ui->comboBox_Osc2PwmModLFO->setCurrentIndex(mod_synth_get_active_osc2_pwm_mod_lfo());
	ui->comboBox_Osc2PwmModLFO->blockSignals(false);

	ui->dial_Osc2PwmModLFOLevel->blockSignals(true);
	ui->dial_Osc2PwmModLFOLevel->setValue(mod_synth_get_active_osc2_pwm_mod_lfo_level());
	ui->dial_Osc2PwmModLFOLevel->blockSignals(false);

	ui->spinBox_Osc2PwmModLfoLevel->blockSignals(true);
	ui->spinBox_Osc2PwmModLfoLevel->setValue(mod_synth_get_active_osc2_pwm_mod_lfo_level());
	ui->spinBox_Osc2PwmModLfoLevel->blockSignals(false);

	ui->comboBox_Osc2PwmModAdsr->blockSignals(true);
	ui->comboBox_Osc2PwmModAdsr->setCurrentIndex(mod_synth_get_active_osc2_pwm_mod_env());
	ui->comboBox_Osc2PwmModAdsr->blockSignals(false);

	ui->dial_Osc2PwmModAdsrLevel->blockSignals(true);
	ui->dial_Osc2PwmModAdsrLevel->setValue(mod_synth_get_active_osc2_pwm_mod_env_level());
	ui->dial_Osc2PwmModAdsrLevel->blockSignals(false);

	ui->spinBox_Osc2PwmModAdsrLevel->blockSignals(true);
	ui->spinBox_Osc2PwmModAdsrLevel->setValue(mod_synth_get_active_osc2_pwm_mod_env_level());
	ui->spinBox_Osc2PwmModAdsrLevel->blockSignals(false);

	ui->comboBox_Osc1AmpModLFO->blockSignals(true);
	ui->comboBox_Osc1AmpModLFO->setCurrentIndex(mod_synth_get_active_osc1_amp_mod_lfo());
	ui->comboBox_Osc1AmpModLFO->blockSignals(false);

	ui->dial_Osc2AmpModLFOLevel->blockSignals(true);
	ui->dial_Osc2AmpModLFOLevel->setValue(mod_synth_get_active_osc2_amp_mod_lfo_level());
	ui->dial_Osc2AmpModLFOLevel->blockSignals(false);

	ui->spinBox_Osc2AmpModLfoLevel->blockSignals(true);
	ui->spinBox_Osc2AmpModLfoLevel->setValue(mod_synth_get_active_osc2_amp_mod_lfo_level());
	ui->spinBox_Osc2AmpModLfoLevel->blockSignals(false);

	ui->comboBox_Osc2AmpModAdsr->blockSignals(true);
	ui->comboBox_Osc2AmpModAdsr->setCurrentIndex(mod_synth_get_active_osc2_amp_mod_env());
	ui->comboBox_Osc2AmpModAdsr->blockSignals(false);

	ui->dial_Osc2AmpModAdsrLevel->blockSignals(true);
	ui->dial_Osc2AmpModAdsrLevel->setValue(mod_synth_get_active_osc2_amp_mod_env_level());
	ui->dial_Osc2AmpModAdsrLevel->blockSignals(false);

	ui->spinBox_Osc2AmpModAdsrLevel->blockSignals(true);
	ui->spinBox_Osc2AmpModAdsrLevel->setValue(mod_synth_get_active_osc2_amp_mod_env_level());
	ui->spinBox_Osc2AmpModAdsrLevel->blockSignals(false);

	osc2_enabled = mod_synth_get_active_osc2_enable_state();
	ui->checkBox_Osc2Active->blockSignals(true);
	ui->checkBox_Osc2Active->setChecked(osc2_enabled);
	ui->checkBox_Osc2Active->blockSignals(false);

	if (osc2_enabled)
	{
		ui->frame_Osc2AmpMod->setEnabled(true);
		ui->frame_Osc2FreqMod->setEnabled(true);
		ui->frame_Osc2PwmMod->setEnabled(true);
		ui->checkBox_Osc2SyncOnOsc1->setEnabled(true);
		ui->frame_Osc2TuneOffset->setEnabled(true);
		ui->frame_Osc2Waveform->setEnabled(true);
	}
	else
	{
		ui->frame_Osc2AmpMod->setEnabled(false);
		ui->frame_Osc2FreqMod->setEnabled(false);
		ui->frame_Osc2PwmMod->setEnabled(false);
		ui->checkBox_Osc2SyncOnOsc1->setEnabled(false);
		ui->frame_Osc2TuneOffset->setEnabled(false);
		ui->frame_Osc2Waveform->setEnabled(false);
	}
}

void Dialog_AnalogSynth_1900x1000::on_osc2_enable_changed(bool en)
{
	ui->checkBox_Osc2Active->blockSignals(true);
	if (en)
	{
		ui->checkBox_Osc2Active->setCheckState(Qt::Checked);
		mod_synth_enable_osc2();
	}
	else
	{
		ui->checkBox_Osc2Active->setCheckState(Qt::Unchecked);
		mod_synth_disable_osc2();
	}
	ui->checkBox_Osc2Active->blockSignals(false);

	osc2_enabled = en;

	mod_synth_vco_event_bool(_OSC_2_EVENT, _OSC_ENABLE, en);

	osc2_update();

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_sync_on_osc1_enable_changed(bool en)
{
	ui->checkBox_Osc2SyncOnOsc1->blockSignals(true);
	if (en)
	{
		ui->checkBox_Osc2SyncOnOsc1->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_Osc2SyncOnOsc1->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_Osc2SyncOnOsc1->blockSignals(false);

	osc_2_sync_on_osc_1 = en;

	mod_synth_vco_event_bool(_OSC_2_EVENT, _OSC_SYNC, en);

	osc2_update();

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_waveform_symmetry_spinbox_changed(int val)
{
	on_osc2_waveform_symmetry_slider_cahanged(val);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_send_filter_1_spinbox_changed(int val)
{
	on_osc2_send_filter_1_dial_changed(val);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_send_filter_2_spinbox_changed(int val)
{
	on_osc2_send_filter_2_dial_changed(val);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_freq_mod_lfo_level_spinbox_changed(int val)
{
	on_osc2_freq_mod_lfo_level_dial_changed(val);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_freq_mod_adsr_level_spinbox_changed(int val)
{
	on_osc2_freq_mod_adsr_level_dial_changed(val);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_pwm_mod_lfo_level_spinbox_changed(int val)
{
	on_osc2_pwm_mod_lfo_level_dial_changed(val);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_pwm_mod_adsr_level_spinbox_changed(int val)
{
	on_osc2_pwm_mod_adsr_level_dial_changed(val);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_amp_mod_lfo_level_spinbox_changed(int val)
{
	on_osc2_amp_mod_lfo_level_dial_changed(val);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_amp_mod_adsr_level_spinbox_changed(int val)
{
	on_osc2_amp_mod_adsr_level_dial_changed(val);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_waveform_symmetry_slider_cahanged(int val)
{
	if ((val < _OSC_WAVEFORM_SYMETRY_MIN) || (val > _OSC_WAVEFORM_SYMETRY_MAX))
	{
		return;
	}

	ui->horizontalSlider_Osc2Symmetry->blockSignals(true);
	ui->horizontalSlider_Osc2Symmetry->setValue(val);
	ui->horizontalSlider_Osc2Symmetry->blockSignals(false);

	ui->spinBox_Osc2Symmetry->blockSignals(true);
	ui->spinBox_Osc2Symmetry->setValue(val);
	ui->spinBox_Osc2Symmetry->blockSignals(false);

	osc2_waveform_symmetry = val;

	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_PWM_SYMMETRY, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_send_filter_1_dial_changed(int val)
{
	ui->dial_Osc2SendFilter1->blockSignals(true);
	ui->dial_Osc2SendFilter1->setValue(val);
	ui->dial_Osc2SendFilter1->blockSignals(false);

	ui->spinBox_Osc2SendFilter1->blockSignals(true);
	ui->spinBox_Osc2SendFilter1->setValue(val);
	ui->spinBox_Osc2SendFilter1->blockSignals(false);

	osc2_send_filter_1_level = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_FILTER_SEND_1, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_send_filter_2_dial_changed(int val)
{
	ui->dial_Osc2SendFilter2->blockSignals(true);
	ui->dial_Osc2SendFilter2->setValue(val);
	ui->dial_Osc2SendFilter2->blockSignals(false);

	ui->spinBox_Osc2SendFilter2->blockSignals(true);
	ui->spinBox_Osc2SendFilter2->setValue(val);
	ui->spinBox_Osc2SendFilter2->blockSignals(false);

	osc2_send_filter_2_level = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_FILTER_SEND_2, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_freq_mod_lfo_level_dial_changed(int val)
{
	// int log_val = mod_synth_log_scale_100_int(0, 100, 10, val);

	ui->dial_Osc2FreqModLFOLevel->blockSignals(true);
	ui->dial_Osc2FreqModLFOLevel->setValue(val);
	ui->dial_Osc2FreqModLFOLevel->blockSignals(false);

	ui->spinBox_Osc2FreqModLfoLevel->blockSignals(true);
	ui->spinBox_Osc2FreqModLfoLevel->setValue(val);
	ui->spinBox_Osc2FreqModLfoLevel->blockSignals(false);

	osc2_freq_mod_lfo_level = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_FREQ_MOD_LFO_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_freq_mod_adsr_level_dial_changed(int val)
{
	ui->dial_Osc2FreqModAdsrLevel->blockSignals(true);
	ui->dial_Osc2FreqModAdsrLevel->setValue(val);
	ui->dial_Osc2FreqModAdsrLevel->blockSignals(false);

	ui->spinBox_Osc2FreqModAdsrLevel->blockSignals(true);
	ui->spinBox_Osc2FreqModAdsrLevel->setValue(val);
	ui->spinBox_Osc2FreqModAdsrLevel->blockSignals(false);

	osc2_freq_mod_adsr_level = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_FREQ_MOD_ENV_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_pwm_mod_lfo_level_dial_changed(int val)
{
	ui->dial_Osc2PwmModLFOLevel->blockSignals(true);
	ui->dial_Osc2PwmModLFOLevel->setValue(val);
	ui->dial_Osc2PwmModLFOLevel->blockSignals(false);

	ui->spinBox_Osc2PwmModLfoLevel->blockSignals(true);
	ui->spinBox_Osc2PwmModLfoLevel->setValue(val);
	ui->spinBox_Osc2PwmModLfoLevel->blockSignals(false);

	osc2_pwm_mod_lfo_level = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_PWM_MOD_LFO_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_pwm_mod_adsr_level_dial_changed(int val)
{
	ui->dial_Osc2PwmModAdsrLevel->blockSignals(true);
	ui->dial_Osc2PwmModAdsrLevel->setValue(val);
	ui->dial_Osc2PwmModAdsrLevel->blockSignals(false);

	ui->spinBox_Osc2PwmModAdsrLevel->blockSignals(true);
	ui->spinBox_Osc2PwmModAdsrLevel->setValue(val);
	ui->spinBox_Osc2PwmModAdsrLevel->blockSignals(false);

	osc2_pwm_mod_adsr_level = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_PWM_MOD_ENV_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_amp_mod_lfo_level_dial_changed(int val)
{
	ui->dial_Osc2AmpModLFOLevel->blockSignals(true);
	ui->dial_Osc2AmpModLFOLevel->setValue(val);
	ui->dial_Osc2AmpModLFOLevel->blockSignals(false);

	ui->spinBox_Osc2AmpModLfoLevel->blockSignals(true);
	ui->spinBox_Osc2AmpModLfoLevel->setValue(val);
	ui->spinBox_Osc2AmpModLfoLevel->blockSignals(false);

	osc2_amp_mod_lfo_level = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_AMP_MOD_LFO_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_amp_mod_adsr_level_dial_changed(int val)
{
	ui->dial_Osc2AmpModAdsrLevel->blockSignals(true);
	ui->dial_Osc2AmpModAdsrLevel->setValue(val);
	ui->dial_Osc2AmpModAdsrLevel->blockSignals(false);

	ui->spinBox_Osc2AmpModAdsrLevel->blockSignals(true);
	ui->spinBox_Osc2AmpModAdsrLevel->setValue(val);
	ui->spinBox_Osc2AmpModAdsrLevel->blockSignals(false);

	osc2_amp_mod_adsr_level = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_AMP_MOD_ENV_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_waveform_combobox_changed(int val)
{
	ui->comboBox_Osc2Waveform->blockSignals(true);
	ui->comboBox_Osc2Waveform->setCurrentIndex(val);
	ui->comboBox_Osc2Waveform->blockSignals(false);

	osc2_waveform = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_PARAM_WAVEFORM, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_tune_octave_combobox_changed(int val)
{
	ui->comboBox_Osc2TuneOctave->blockSignals(true);
	ui->comboBox_Osc2TuneOctave->setCurrentIndex(val);
	ui->comboBox_Osc2TuneOctave->blockSignals(false);

	osc2_tune_octave = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_DETUNE_OCTAVE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_tune_semitones_combobox_changed(int val)
{
	ui->comboBox_Osc2TuneSemitones->blockSignals(true);
	ui->comboBox_Osc2TuneSemitones->setCurrentIndex(val);
	ui->comboBox_Osc2TuneSemitones->blockSignals(false);

	osc2_tune_cents = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_DETUNE_SEMITONES, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_tune_cents_combobox_changed(int val)
{
	ui->comboBox_Osc2TuneCents->blockSignals(true);
	ui->comboBox_Osc2TuneCents->setCurrentIndex(val);
	ui->comboBox_Osc2TuneCents->blockSignals(false);

	osc2_tune_cents = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_DETUNE_CENTS, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_freq_mod_lfo_combobox_changed(int val)
{
	ui->comboBox_Osc2FreqModLFO->blockSignals(true);
	ui->comboBox_Osc2FreqModLFO->setCurrentIndex(val);
	ui->comboBox_Osc2FreqModLFO->blockSignals(false);

	osc2_freq_mod_lfo_num = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_FREQ_MOD_LFO, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_freq_mod_adsr_combobox_changed(int val)
{
	ui->comboBox_Osc2FreqModAdsr->blockSignals(true);
	ui->comboBox_Osc2FreqModAdsr->setCurrentIndex(val);
	ui->comboBox_Osc2FreqModAdsr->blockSignals(false);

	osc2_freq_mod_adsr_num = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_FREQ_MOD_ENV, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_pwm_mod_lfo_combobox_changed(int val)
{
	ui->comboBox_Osc2PwmModLFO->blockSignals(true);
	ui->comboBox_Osc2PwmModLFO->setCurrentIndex(val);
	ui->comboBox_Osc2PwmModLFO->blockSignals(false);

	osc2_pwm_mod_lfo_num = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_PWM_MOD_LFO, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_pwm_mod_adsr_combobox_changed(int val)
{
	ui->comboBox_Osc2PwmModAdsr->blockSignals(true);
	ui->comboBox_Osc2PwmModAdsr->setCurrentIndex(val);
	ui->comboBox_Osc2PwmModAdsr->blockSignals(false);

	osc2_pwm_mod_adsr_num = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_PWM_MOD_ENV, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_amp_mod_lfo_combobox_changed(int val)
{
	ui->comboBox_Osc2AmpModLFO->blockSignals(true);
	ui->comboBox_Osc2AmpModLFO->setCurrentIndex(val);
	ui->comboBox_Osc2AmpModLFO->blockSignals(false);

	osc2_amp_mod_lfo_num = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_AMP_MOD_LFO, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth_1900x1000::on_osc2_amp_mod_adsr_combobox_changed(int val)
{
	ui->comboBox_Osc2AmpModAdsr->blockSignals(true);
	ui->comboBox_Osc2AmpModAdsr->setCurrentIndex(val);
	ui->comboBox_Osc2AmpModAdsr->blockSignals(false);

	osc2_amp_mod_adsr_num = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_AMP_MOD_ENV, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
