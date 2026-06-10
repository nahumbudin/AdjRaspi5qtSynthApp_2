/**
 * @file		Dialog_MSOsynthesizer_GuiHandlers.cpp
 *	@author		Nahum Budin
 *	@date		2-June-2026
 *	@version	1.0
 *
 *	Note - PWM or Symmetry Modulation is not implemented in the current version.
 *
 *	@brief		Adj MSO Synthesizer control dialog GUI widgets event handlers
 *
 */

#include "Dialog_MSOsynthesizer.h"
#include "ui_Dialog_MSOsynthesizer.h"

void Dialog_MSOsynthesizer::on_send_filter_dial_changed(int val)
{
	ui->dial_MsoSynthSendFilter->blockSignals(true);
	ui->dial_MsoSynthSendFilter->setValue(val);
	ui->dial_MsoSynthSendFilter->blockSignals(false);

	ui->spinBox_MsoSynthSendFilter->blockSignals(true);
	ui->spinBox_MsoSynthSendFilter->setValue(val);
	ui->spinBox_MsoSynthSendFilter->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FILTER_SEND_1, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_detune_octave_combobox_changed(int val)
{
	ui->comboBox_MsoSynthTuneOctave->blockSignals(true);
	ui->comboBox_MsoSynthTuneOctave->setCurrentIndex(val);
	ui->comboBox_MsoSynthTuneOctave->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_DETUNE_OCTAVE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_detune_semitones_combobox_changed(int val)
{
	ui->comboBox_MsoSynthTuneSemitones->blockSignals(true);
	ui->comboBox_MsoSynthTuneSemitones->setCurrentIndex(val);
	ui->comboBox_MsoSynthTuneSemitones->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_DETUNE_SEMITONES, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_detune_cents_combobox_changed(int val)
{
	ui->comboBox_MsoSynthTuneCents->blockSignals(true);
	ui->comboBox_MsoSynthTuneCents->setCurrentIndex(val);
	ui->comboBox_MsoSynthTuneCents->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_DETUNE_CENTS, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}	

// In Dialog_MSOsynthesizer.cpp
//void Dialog_MSOsynthesizer::on_preset_file_loaded(const QString &s)
//void Dialog_MSOsynthesizer::on_preset_file_saved(const QString &s)

void Dialog_MSOsynthesizer::on_amp_mod_env_level_dial_changed(int val)
{
	ui->dial_MSOsynth_AmpModAdsrLevel->blockSignals(true);
	ui->dial_MSOsynth_AmpModAdsrLevel->setValue(val);
	ui->dial_MSOsynth_AmpModAdsrLevel->blockSignals(false);
	
	ui->spinBox_MSOsynth_AmpModAdsrLevel->blockSignals(true);
	ui->spinBox_MSOsynth_AmpModAdsrLevel->setValue(val);
	ui->spinBox_MSOsynth_AmpModAdsrLevel->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_AMP_MOD_ENV_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_amp_env_attack_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_MSOsynth_AmpModAdsrA->blockSignals(true);
	ui->verticalSlider_MSOsynth_AmpModAdsrA->setValue(val);
	ui->verticalSlider_MSOsynth_AmpModAdsrA->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0, val));

	ui->lineEdit_MSOsynth_AmpModAdsrA->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_AMP_MOD_ENV_ATTACK, val);

	update_amp_mod_adsr_plot.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_amp_env_decay_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_MSOsynth_AmpModAdsrD->blockSignals(true);
	ui->verticalSlider_MSOsynth_AmpModAdsrD->setValue(val);
	ui->verticalSlider_MSOsynth_AmpModAdsrD->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0, val));

	ui->lineEdit_MSOsynth_AmpModAdsrD->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_AMP_MOD_ENV_DECAY, val);

	update_amp_mod_adsr_plot.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_amp_env_sustain_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_MSOsynth_AmpModAdsrS->blockSignals(true);
	ui->verticalSlider_MSOsynth_AmpModAdsrS->setValue(val);
	ui->verticalSlider_MSOsynth_AmpModAdsrS->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_MSOsynth_AmpModAdsrS->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_AMP_MOD_ENV_SUSTAIN, val);

	update_amp_mod_adsr_plot.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_amp_env_release_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_MSOsynth_AmpModAdsrR->blockSignals(true);
	ui->verticalSlider_MSOsynth_AmpModAdsrR->setValue(val);
	ui->verticalSlider_MSOsynth_AmpModAdsrR->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0, val));

	ui->lineEdit_MSOsynth_AmpModAdsrR->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_AMP_MOD_ENV_RELEASE, val);

	update_amp_mod_adsr_plot.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_amp_mod_lfo_level_dial_changed(int val)
{
	ui->dial_MSOsynth_AmpModLFOLevel->blockSignals(true);
	ui->dial_MSOsynth_AmpModLFOLevel->setValue(val);
	ui->dial_MSOsynth_AmpModLFOLevel->blockSignals(false);

	ui->spinBox_MSOsynth_AmpModLfoLevel->blockSignals(true);
	ui->spinBox_MSOsynth_AmpModLfoLevel->setValue(val);
	ui->spinBox_MSOsynth_AmpModLfoLevel->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_AMP_MOD_LFO_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_amp_mod_lfo_rate_dial_changed(int val)
{
	char text[64];

	ui->dial_MSOsynth_AmpModLFOrate->blockSignals(true);
	ui->dial_MSOsynth_AmpModLFOrate->setValue(val);
	ui->dial_MSOsynth_AmpModLFOrate->blockSignals(false);

	sprintf(text,
			"%.2fHz",
			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
										  mod_synth_get_lfo_max_frequency(),
										  10.0,
										  val));

	ui->lineEdit_MSOsynth_AmpModLFOrate->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_AMP_MOD_LFO_RATE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_amp_mod_lfo_symmetry_dial_changed(int val)
{
	char text[64];

	ui->dial_MSOsynth_AmpModLFOsymmetry->blockSignals(true);
	ui->dial_MSOsynth_AmpModLFOsymmetry->setValue(val);
	ui->dial_MSOsynth_AmpModLFOsymmetry->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_MSOsynth_AmpModLFOsymmetry->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_AMP_MOD_LFO_SYMMETRY, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_amp_mod_lfo_waveform_combobox_changed(int val)
{
	ui->comboBox_MSOsynth_AmpModLFOwaveform->blockSignals(true);
	ui->comboBox_MSOsynth_AmpModLFOwaveform->setCurrentIndex(val);
	ui->comboBox_MSOsynth_AmpModLFOwaveform->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_AMP_MOD_LFO_WAVEFORM, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

/*
void Dialog_MSOsynthesizer::on_sym_mod_env_level_dial_changed(int val)
{
	ui->dial_MSOsynth_PwmModAdsrLevel->blockSignals(true);
	ui->dial_MSOsynth_PwmModAdsrLevel->setValue(val);
	ui->dial_MSOsynth_PwmModAdsrLevel->blockSignals(false);

	ui->spinBox_MSOsynth_PwmModAdsrLevel->blockSignals(true);
	ui->spinBox_MSOsynth_PwmModAdsrLevel->setValue(val);
	ui->spinBox_MSOsynth_PwmModAdsrLevel->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_PWM_MOD_ENV_LEVEL, val);

	// Set focus back on the Dialog 
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_sym_env_attack_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_MSOsynth_PwmModAdsrA->blockSignals(true);
	ui->verticalSlider_MSOsynth_PwmModAdsrA->setValue(val);
	ui->verticalSlider_MSOsynth_PwmModAdsrA->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0, val));

	ui->lineEdit_MSOsynth_PwmModAdsrA->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_SYM_MOD_ENV_ATTACK, val);

	update_sym_mod_adsr_plot.store(true);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_sym_env_decay_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_MSOsynth_PwmModAdsrD->blockSignals(true);
	ui->verticalSlider_MSOsynth_PwmModAdsrD->setValue(val);
	ui->verticalSlider_MSOsynth_PwmModAdsrD->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0, val));

	ui->lineEdit_MSOsynth_PwmModAdsrD->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_SYM_MOD_ENV_DECAY, val);

	update_sym_mod_adsr_plot.store(true);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_sym_env_sustain_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_MSOsynth_PwmModAdsrS->blockSignals(true);
	ui->verticalSlider_MSOsynth_PwmModAdsrS->setValue(val);
	ui->verticalSlider_MSOsynth_PwmModAdsrS->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_MSOsynth_PwmModAdsrS->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_SYM_MOD_ENV_SUSTAIN, val);

	update_sym_mod_adsr_plot.store(true);

	// Set focus back on the Dialog 
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_sym_env_release_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_MSOsynth_PwmModAdsrR->blockSignals(true);
	ui->verticalSlider_MSOsynth_PwmModAdsrR->setValue(val);
	ui->verticalSlider_MSOsynth_PwmModAdsrR->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0, val));

	ui->lineEdit_MSOsynth_PwmModAdsrR->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_SYM_MOD_ENV_RELEASE, val);

	update_sym_mod_adsr_plot.store(true);

	// Set focus back on the Dialog 
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_sym_mod_lfo_level_dial_changed(int val)
{
	ui->dial_MSOsynth_PwmModLFOLevel->blockSignals(true);
	ui->dial_MSOsynth_PwmModLFOLevel->setValue(val);
	ui->dial_MSOsynth_PwmModLFOLevel->blockSignals(false);
	
	ui->spinBox_MSOsynth_PwmModLfoLevel->blockSignals(true);
	ui->spinBox_MSOsynth_PwmModLfoLevel->setValue(val);
	ui->spinBox_MSOsynth_PwmModLfoLevel->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_PWM_MOD_LFO_LEVEL, val);

	// Set focus back on the Dialog 
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_sym_mod_lfo_rate_dial_changed(int val)
{
	char text[64];

	ui->dial_MSOsynth_PwmModLFOrate->blockSignals(true);
	ui->dial_MSOsynth_PwmModLFOrate->setValue(val);
	ui->dial_MSOsynth_PwmModLFOrate->blockSignals(false);

	sprintf(text,
			"%.2fHz",
			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
										  mod_synth_get_lfo_max_frequency(),
										  10.0,
										  val));

	ui->lineEdit_MSOsynth_PwmModLFOrate->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_SYM_MOD_LFO_RATE, val);

	// Set focus back on the Dialog 
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_sym_mod_lfo_symmetry_dial_changed(int val)
{
	char text[64];

	ui->dial_MSOsynth_PwmModLFOsymmetry->blockSignals(true);
	ui->dial_MSOsynth_PwmModLFOsymmetry->setValue(val);
	ui->dial_MSOsynth_PwmModLFOsymmetry->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_MSOsynth_PwmModLFOsymmetry->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_SYM_MOD_LFO_SYMMETRY, val);

	// Set focus back on the Dialog 
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_sym_mod_lfo_waveform_combobox_changed(int val)
{
	ui->comboBox_MSOsynth_PwmModLFOwaveform->blockSignals(true);
	ui->comboBox_MSOsynth_PwmModLFOwaveform->setCurrentIndex(val);
	ui->comboBox_MSOsynth_PwmModLFOwaveform->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_SYM_MOD_LFO_WAVEFORM, val);

	/ Set focus back on the Dialog 
	this->setFocus(Qt::ActiveWindowFocusReason);
}
*/

void Dialog_MSOsynthesizer::on_freq_mod_env_level_dial_changed(int val)
{
	ui->dial_MSOsynth_FreqModAdsrLevel->blockSignals(true);
	ui->dial_MSOsynth_FreqModAdsrLevel->setValue(val);
	ui->dial_MSOsynth_FreqModAdsrLevel->blockSignals(false);
	
	ui->spinBox_MSOsynth_FreqModAdsrLevel->blockSignals(true);
	ui->spinBox_MSOsynth_FreqModAdsrLevel->setValue(val);
	ui->spinBox_MSOsynth_FreqModAdsrLevel->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FREQ_MOD_ENV_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_freq_env_attack_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_MSOsynth_FreqModAdsrA->blockSignals(true);
	ui->verticalSlider_MSOsynth_FreqModAdsrA->setValue(val);
	ui->verticalSlider_MSOsynth_FreqModAdsrA->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0, val));

	ui->lineEdit_MSOsynth_FreqModAdsrA->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FREQ_MOD_ENV_ATTACK, val);

	update_freq_mod_adsr_plot.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_freq_env_decay_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_MSOsynth_FreqModAdsrD->blockSignals(true);
	ui->verticalSlider_MSOsynth_FreqModAdsrD->setValue(val);
	ui->verticalSlider_MSOsynth_FreqModAdsrD->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0, val));

	ui->lineEdit_MSOsynth_FreqModAdsrD->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FREQ_MOD_ENV_DECAY, val);

	update_freq_mod_adsr_plot.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_freq_env_sustain_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_MSOsynth_FreqModAdsrS->blockSignals(true);
	ui->verticalSlider_MSOsynth_FreqModAdsrS->setValue(val);
	ui->verticalSlider_MSOsynth_FreqModAdsrS->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_MSOsynth_FreqModAdsrS->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FREQ_MOD_ENV_SUSTAIN, val);

	update_freq_mod_adsr_plot.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_freq_env_release_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_MSOsynth_FreqModAdsrR->blockSignals(true);
	ui->verticalSlider_MSOsynth_FreqModAdsrR->setValue(val);
	ui->verticalSlider_MSOsynth_FreqModAdsrR->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0, val));

	ui->lineEdit_MSOsynth_FreqModAdsrR->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FREQ_MOD_ENV_RELEASE, val);

	update_freq_mod_adsr_plot.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_freq_mod_lfo_level_dial_changed(int val)
{
	ui->dial_MSOsynth_FreqModLFOLevel->blockSignals(true);
	ui->dial_MSOsynth_FreqModLFOLevel->setValue(val);
	ui->dial_MSOsynth_FreqModLFOLevel->blockSignals(false);
	
	ui->spinBox_MSOsynth_FreqModLfoLevel->blockSignals(true);
	ui->spinBox_MSOsynth_FreqModLfoLevel->setValue(val);
	ui->spinBox_MSOsynth_FreqModLfoLevel->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FREQ_MOD_LFO_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_freq_mod_lfo_rate_dial_changed(int val)
{
	char text[64];

	ui->dial_MSOsynth_FreqModLFOrate->blockSignals(true);
	ui->dial_MSOsynth_FreqModLFOrate->setValue(val);
	ui->dial_MSOsynth_FreqModLFOrate->blockSignals(false);

	sprintf(text,
			"%.2fHz",
			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
										  mod_synth_get_lfo_max_frequency(),
										  10.0,
										  val));

	ui->lineEdit_MSOsynth_FreqModLFOrate->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FREQ_MOD_LFO_RATE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_freq_mod_lfo_symmetry_dial_changed(int val)
{
	char text[64];

	ui->dial_MSOsynth_FreqModLFOsymmetry->blockSignals(true);
	ui->dial_MSOsynth_FreqModLFOsymmetry->setValue(val);
	ui->dial_MSOsynth_FreqModLFOsymmetry->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_MSOsynth_FreqModLFOsymmetry->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FREQ_MOD_LFO_SYMMETRY, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_freq_mod_lfo_waveform_combobox_changed(int val)
{
	ui->comboBox_MSOsynth_FreqModLFOwaveform->blockSignals(true);
	ui->comboBox_MSOsynth_FreqModLFOwaveform->setCurrentIndex(val);
	ui->comboBox_MSOsynth_FreqModLFOwaveform->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FREQ_MOD_LFO_WAVEFORM, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_point_a_slider_moved(int val)
{
	if ((val < 1) || (val > 2046))
	{
		return;
	}

	ui->verticalSlider_MSOSynth_Pos_a->blockSignals(true);
	ui->verticalSlider_MSOSynth_Pos_a->setValue(val);
	ui->verticalSlider_MSOSynth_Pos_a->blockSignals(false);

	ui->spinBox_MSOSynth_Pos_a->blockSignals(true);
	ui->spinBox_MSOSynth_Pos_a->setValue(val);
	ui->spinBox_MSOSynth_Pos_a->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_SEGMENT_A_POSITION, val);

	// setup_mso_plot(ui->widget_MsoWaveformPlot);  Will be initate  by the GUI update
	// ui->widget_MsoWaveformPlot->replot();
	replot_waveform.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_point_b_slider_moved(int val)
{
	if ((val < 1) || (val > 2046))
	{
		return;
	}

	ui->verticalSlider_MSOSynth_Pos_b->blockSignals(true);
	ui->verticalSlider_MSOSynth_Pos_b->setValue(val);
	ui->verticalSlider_MSOSynth_Pos_b->blockSignals(false);

	ui->spinBox_MSOSynth_Pos_b->blockSignals(true);
	ui->spinBox_MSOSynth_Pos_b->setValue(val);
	ui->spinBox_MSOSynth_Pos_b->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_SEGMENT_B_POSITION, val);

	// setup_mso_plot(ui->widget_MsoWaveformPlot);  Will be initate  by the GUI update
	// ui->widget_MsoWaveformPlot->replot();
	replot_waveform.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_point_c_slider_moved(int val)
{
	if ((val < 1) || (val > 2046))
	{
		return;
	}

	ui->verticalSlider_MSOSynth_Pos_c->blockSignals(true);
	ui->verticalSlider_MSOSynth_Pos_c->setValue(val);
	ui->verticalSlider_MSOSynth_Pos_c->blockSignals(false);

	ui->spinBox_MSOSynth_Pos_c->blockSignals(true);
	ui->spinBox_MSOSynth_Pos_c->setValue(val);
	ui->spinBox_MSOSynth_Pos_c->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_SEGMENT_C_POSITION, val);

	// setup_mso_plot(ui->widget_MsoWaveformPlot);  Will be initate  by the GUI update
	// ui->widget_MsoWaveformPlot->replot();
	replot_waveform.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_point_d_slider_moved(int val)
{
	if ((val < 1) || (val > 2046))
	{
		return;
	}

	ui->verticalSlider_MSOSynth_Pos_d->blockSignals(true);
	ui->verticalSlider_MSOSynth_Pos_d->setValue(val);
	ui->verticalSlider_MSOSynth_Pos_d->blockSignals(false);

	ui->spinBox_MSOSynth_Pos_d->blockSignals(true);
	ui->spinBox_MSOSynth_Pos_d->setValue(val);
	ui->spinBox_MSOSynth_Pos_d->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_SEGMENT_D_POSITION, val);

	// setup_mso_plot(ui->widget_MsoWaveformPlot);  Will be initate  by the GUI update
	// ui->widget_MsoWaveformPlot->replot();
	replot_waveform.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_point_e_slider_moved(int val)
{
	if ((val < 1) || (val > 2046))
	{
		return;
	}

	ui->verticalSlider_MSOSynth_Pos_e->blockSignals(true);
	ui->verticalSlider_MSOSynth_Pos_e->setValue(val);
	ui->verticalSlider_MSOSynth_Pos_e->blockSignals(false);

	ui->spinBox_MSOSynth_Pos_e->blockSignals(true);
	ui->spinBox_MSOSynth_Pos_e->setValue(val);
	ui->spinBox_MSOSynth_Pos_e->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_SEGMENT_E_POSITION, val);

	// setup_mso_plot(ui->widget_MsoWaveformPlot);  Will be initate  by the GUI update
	// ui->widget_MsoWaveformPlot->replot();
	replot_waveform.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_point_f_slider_moved(int val)
{
	if ((val < 1) || (val > 2046))
	{
		return;
	}

	ui->verticalSlider_MSOSynth_Pos_f->blockSignals(true);
	ui->verticalSlider_MSOSynth_Pos_f->setValue(val);
	ui->verticalSlider_MSOSynth_Pos_f->blockSignals(false);

	ui->spinBox_MSOSynth_Pos_f->blockSignals(true);
	ui->spinBox_MSOSynth_Pos_f->setValue(val);
	ui->spinBox_MSOSynth_Pos_f->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_SEGMENT_F_POSITION, val);

	// setup_mso_plot(ui->widget_MsoWaveformPlot);  Will be initate  by the GUI update
	// ui->widget_MsoWaveformPlot->replot();
	replot_waveform.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_symetry_slider_changed(int val)
{
	if ((val < 5) || (val > 95))
	{
		return;
	}

	ui->horizontalSlider_MsoSynthMorph->blockSignals(true);
	ui->horizontalSlider_MsoSynthMorph->setValue(val);
	ui->horizontalSlider_MsoSynthMorph->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_SYMETRY, val);

	// setup_mso_plot(ui->widget_MsoWaveformPlot);
	// ui->widget_MsoWaveformPlot->replot();
	replot_waveform.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_preset_combobox_changed(int val)
{
	handle_preset_change(val);

	// The above set back to default
	ui->comboBox_MsoSynthPreset->blockSignals(true);
	ui->comboBox_MsoSynthPreset->setCurrentIndex(val);
	ui->comboBox_MsoSynthPreset->blockSignals(false);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_filter_freq_dial_changed(int val)
{
	char frequency[32];

	ui->dial_MsoSynthFilterFreq->blockSignals(true);
	ui->dial_MsoSynthFilterFreq->setValue(val);
	ui->dial_MsoSynthFilterFreq->blockSignals(false);

	sprintf(frequency,
			"%.1f Hz",
			mod_synth_get_filter_min_center_freq() +
				(mod_synth_get_filter_max_center_freq() -
				 mod_synth_get_filter_min_center_freq()) *
					val / 100.0f);

	ui->lineEdit_MsoSynthFilterFreq->setText(QString(frequency));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _FILTER_FREQ, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_filter_q_dial_changed(int val)
{
	char q[32];

	ui->dial_MsoSynthFilterQ->blockSignals(true);
	ui->dial_MsoSynthFilterQ->setValue(val);
	ui->dial_MsoSynthFilterQ->blockSignals(false);

	sprintf(q,
			"%.1f",
			mod_synth_get_filter_min_Q() +
				(mod_synth_get_filter_max_Q() -
				 mod_synth_get_filter_min_Q()) *
					val / 100.0f);

	ui->lineEdit_MsoSynthFilterQ->setText(QString(q));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _FILTER_Q, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_filter_octave_dial_changed(int val)
{
	char octave[16];

	ui->dial_MsoSynthFilterOctave->blockSignals(true);
	ui->dial_MsoSynthFilterOctave->setValue(val);
	ui->dial_MsoSynthFilterOctave->blockSignals(false);

	sprintf(octave,
			"%.4f",
			val * 6.9999f / 100.0f);

	ui->lineEdit_MsoSynthFilterOctave->setText(QString(octave));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _FILTER_OCT, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_filter_kbd_track_dial_changed(int val)
{
	ui->dial_MsoSynthFilterKbdTrack->blockSignals(true);
	ui->dial_MsoSynthFilterKbdTrack->setValue(val);
	ui->dial_MsoSynthFilterKbdTrack->blockSignals(false);

	ui->lineEdit_MsoSynthFilterKbdTrack->setText(QString::number(val));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _FILTER_KBD_TRACK, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_filter_band_combo_hanged(int val)
{
	ui->comboBox_MsoSynthFilterBand->blockSignals(true);
	ui->comboBox_MsoSynthFilterBand->setCurrentIndex(val);
	ui->comboBox_MsoSynthFilterBand->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _FILTER_BAND, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_filter_freq_mod_level_lfo_dial_changed(int val)
{
	ui->dial_MSOsynth_FilterFreqModLFOLevel->blockSignals(true);
	ui->dial_MSOsynth_FilterFreqModLFOLevel->setValue(val);
	ui->dial_MSOsynth_FilterFreqModLFOLevel->blockSignals(false);

	ui->spinBox_MSOsynth_FilterFreqModLfoLevel->blockSignals(true);
	ui->spinBox_MSOsynth_FilterFreqModLfoLevel->setValue(val);
	ui->spinBox_MSOsynth_FilterFreqModLfoLevel->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FILTER_FREQ_MOD_LFO_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_filter_freq_mod_lfo_waveform_combo_changed(int val)
{
	ui->comboBox_MSOsynth_FilterFreqModLFOwaveform->blockSignals(true);
	ui->comboBox_MSOsynth_FilterFreqModLFOwaveform->setCurrentIndex(val);
	ui->comboBox_MSOsynth_FilterFreqModLFOwaveform->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FILTER_FREQ_MOD_LFO_WAVEFORM, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_filter_freq_mod_lfo_rate_dial_changed(int val)
{
	char text[64];

	ui->dial_MSOsynth_FilterFreqModLFOrate->blockSignals(true);
	ui->dial_MSOsynth_FilterFreqModLFOrate->setValue(val);
	ui->dial_MSOsynth_FilterFreqModLFOrate->blockSignals(false);

	sprintf(text,
			"%.2fHz",
			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
										  mod_synth_get_lfo_max_frequency(),
										  10.0,
										  val));

	ui->lineEdit_MSOsynth_FilterFreqModLFOrate->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FILTER_FREQ_MOD_LFO_RATE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_filter_freq_mod_lfo_symmetry_dial_changed(int val)
{
	char text[64];

	ui->dial_MSOsynth_FilterFreqModLFOsymmetry->blockSignals(true);
	ui->dial_MSOsynth_FilterFreqModLFOsymmetry->setValue(val);
	ui->dial_MSOsynth_FilterFreqModLFOsymmetry->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_MSOsynth_FilterFreqModLFOsymmetry->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FILTER_FREQ_MOD_LFO_SYMMETRY, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_filter_freq_mod_env_level_dial_changed(int val)
{
	ui->dial_MSOsynth_FilterFreqModAdsrLevel->blockSignals(true);
	ui->dial_MSOsynth_FilterFreqModAdsrLevel->setValue(val);
	ui->dial_MSOsynth_FilterFreqModAdsrLevel->blockSignals(false);

	ui->spinBox_MSOsynth_FilterFreqModAdsrLevel->blockSignals(true);
	ui->spinBox_MSOsynth_FilterFreqModAdsrLevel->setValue(val);
	ui->spinBox_MSOsynth_FilterFreqModAdsrLevel->blockSignals(false);

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FILTER_FREQ_MOD_ENV_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_filter_freq_mod_env_attack_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_MSOsynth_FilterFreqModAdsrA->blockSignals(true);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrA->setValue(val);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrA->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0, val));

	ui->lineEdit_MSOsynth_FilterFreqModAdsrA->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FILTER_FREQ_MOD_ENV_ATTACK, val);

	update_filter_freq_mod_adsr_plot.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MSOsynthesizer::on_filter_freq_mod_env_decay_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_MSOsynth_FilterFreqModAdsrD->blockSignals(true);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrD->setValue(val);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrD->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0, val));

	ui->lineEdit_MSOsynth_FilterFreqModAdsrD->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FILTER_FREQ_MOD_ENV_DECAY, val);

	update_filter_freq_mod_adsr_plot.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_filter_freq_mod_env_sustain_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_MSOsynth_FilterFreqModAdsrS->blockSignals(true);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrS->setValue(val);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrS->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_MSOsynth_FilterFreqModAdsrS->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FILTER_FREQ_MOD_ENV_SUSTAIN, val);

	update_filter_freq_mod_adsr_plot.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MSOsynthesizer::on_filter_freq_mod_env_release_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_MSOsynth_FilterFreqModAdsrR->blockSignals(true);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrR->setValue(val);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrR->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0, val));

	ui->lineEdit_MSOsynth_FilterFreqModAdsrR->setText(QString(text));

	mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_FILTER_FREQ_MOD_ENV_RELEASE, val);

	update_filter_freq_mod_adsr_plot.store(true);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
