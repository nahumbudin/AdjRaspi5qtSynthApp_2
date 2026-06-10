/**
 * @file		Dialog_MSOsynthesizer_GuiUpdate.cpp
 *	@author		Nahum Budin
 *	@date		2-June-2026
 *	@version	1.0
 *
 *	Note - PWM or Symmetry Modulation is not implemented in the current version.
 *
 *	@brief		Adj MSO Synthesizer control dialog GUI widgets update functions
 *
 */

#include "Dialog_MSOsynthesizer.h"
#include "ui_Dialog_MSOsynthesizer.h"

#include "Defs.h"

#define _MSO_AMP_MOD		0
#define _MSO_FREQ_MOD		1
#define _MSO_PWM_MOD		2
#define _FILTER_FREQ_MOD	3

void Dialog_MSOsynthesizer::update_gui()
{

	// Don't update if dialog is not visible
	if (!isVisible())
	{
		return;
	}

	int val;
	char text[64];

	ui->verticalSlider_MSOSynth_Pos_a->blockSignals(true);
	ui->verticalSlider_MSOSynth_Pos_a->setValue(mod_synth_get_mso_synth_int_param(_MSO_SEGMENT_A_POSITION));
	ui->verticalSlider_MSOSynth_Pos_a->blockSignals(false);

	ui->verticalSlider_MSOSynth_Pos_b->blockSignals(true);
	ui->verticalSlider_MSOSynth_Pos_b->setValue(mod_synth_get_mso_synth_int_param(_MSO_SEGMENT_B_POSITION));
	ui->verticalSlider_MSOSynth_Pos_b->blockSignals(false);

	ui->verticalSlider_MSOSynth_Pos_c->blockSignals(true);
	ui->verticalSlider_MSOSynth_Pos_c->setValue(mod_synth_get_mso_synth_int_param(_MSO_SEGMENT_C_POSITION));
	ui->verticalSlider_MSOSynth_Pos_c->blockSignals(false);

	ui->verticalSlider_MSOSynth_Pos_d->blockSignals(true);
	ui->verticalSlider_MSOSynth_Pos_d->setValue(mod_synth_get_mso_synth_int_param(_MSO_SEGMENT_D_POSITION));
	ui->verticalSlider_MSOSynth_Pos_d->blockSignals(false);

	ui->verticalSlider_MSOSynth_Pos_e->blockSignals(true);
	ui->verticalSlider_MSOSynth_Pos_e->setValue(mod_synth_get_mso_synth_int_param(_MSO_SEGMENT_E_POSITION));
	ui->verticalSlider_MSOSynth_Pos_e->blockSignals(false);

	ui->verticalSlider_MSOSynth_Pos_f->blockSignals(true);
	ui->verticalSlider_MSOSynth_Pos_f->setValue(mod_synth_get_mso_synth_int_param(_MSO_SEGMENT_F_POSITION));
	ui->verticalSlider_MSOSynth_Pos_f->blockSignals(false);

	ui->spinBox_MSOSynth_Pos_a->blockSignals(true);
	ui->spinBox_MSOSynth_Pos_a->setValue(mod_synth_get_mso_synth_int_param(_MSO_SEGMENT_A_POSITION));
	ui->spinBox_MSOSynth_Pos_a->blockSignals(false);

	ui->spinBox_MSOSynth_Pos_b->blockSignals(true);
	ui->spinBox_MSOSynth_Pos_b->setValue(mod_synth_get_mso_synth_int_param(_MSO_SEGMENT_B_POSITION));
	ui->spinBox_MSOSynth_Pos_b->blockSignals(false);

	ui->spinBox_MSOSynth_Pos_c->blockSignals(true);
	ui->spinBox_MSOSynth_Pos_c->setValue(mod_synth_get_mso_synth_int_param(_MSO_SEGMENT_C_POSITION));
	ui->spinBox_MSOSynth_Pos_c->blockSignals(false);

	ui->spinBox_MSOSynth_Pos_d->blockSignals(true);
	ui->spinBox_MSOSynth_Pos_d->setValue(mod_synth_get_mso_synth_int_param(_MSO_SEGMENT_D_POSITION));
	ui->spinBox_MSOSynth_Pos_d->blockSignals(false);

	ui->spinBox_MSOSynth_Pos_e->blockSignals(true);
	ui->spinBox_MSOSynth_Pos_e->setValue(mod_synth_get_mso_synth_int_param(_MSO_SEGMENT_E_POSITION));
	ui->spinBox_MSOSynth_Pos_e->blockSignals(false);

	ui->spinBox_MSOSynth_Pos_f->blockSignals(true);
	ui->spinBox_MSOSynth_Pos_f->setValue(mod_synth_get_mso_synth_int_param(_MSO_SEGMENT_F_POSITION));
	ui->spinBox_MSOSynth_Pos_f->blockSignals(false);

	ui->horizontalSlider_MsoSynthMorph->blockSignals(true);
	ui->horizontalSlider_MsoSynthMorph->setValue(mod_synth_get_mso_synth_int_param(_MSO_SYMETRY));
	ui->horizontalSlider_MsoSynthMorph->blockSignals(false);

	ui->comboBox_MsoSynthTuneOctave->blockSignals(true);
	ui->comboBox_MsoSynthTuneOctave->setCurrentIndex(mod_synth_get_mso_synth_int_param(_MSO_DETUNE_OCTAVE) - _OSC_DETUNE_MIN_OCTAVE);
	ui->comboBox_MsoSynthTuneOctave->blockSignals(false);

	ui->comboBox_MsoSynthTuneSemitones->blockSignals(true);
	ui->comboBox_MsoSynthTuneSemitones->setCurrentIndex(mod_synth_get_mso_synth_int_param(_MSO_DETUNE_SEMITONES) - _OSC_DETUNE_MIN_SEMITONES);
	ui->comboBox_MsoSynthTuneSemitones->blockSignals(false);

	ui->comboBox_MsoSynthTuneCents->blockSignals(true);
	ui->comboBox_MsoSynthTuneCents->setCurrentIndex(mod_synth_get_mso_synth_int_param(_MSO_DETUNE_CENTS) - _OSC_DETUNE_MIN_CENTS * 4.f);
	ui->comboBox_MsoSynthTuneCents->blockSignals(false);

	ui->dial_MsoSynthSendFilter->blockSignals(true);
	ui->dial_MsoSynthSendFilter->setValue(mod_synth_get_mso_synth_int_param(_MSO_FILTER_SEND_1));
	ui->dial_MsoSynthSendFilter->blockSignals(false);

	ui->spinBox_MsoSynthSendFilter->blockSignals(true);
	ui->spinBox_MsoSynthSendFilter->setValue(mod_synth_get_mso_synth_int_param(_MSO_FILTER_SEND_1));
	ui->spinBox_MsoSynthSendFilter->blockSignals(false);

	ui->dial_MSOsynth_AmpModLFOLevel->blockSignals(true);
	ui->dial_MSOsynth_AmpModLFOLevel->setValue(mod_synth_get_mso_synth_int_param(_MSO_AMP_MOD_LFO_LEVEL));
	ui->dial_MSOsynth_AmpModLFOLevel->blockSignals(false);

	ui->spinBox_MSOsynth_AmpModLfoLevel->blockSignals(true);
	ui->spinBox_MSOsynth_AmpModLfoLevel->setValue(mod_synth_get_mso_synth_int_param(_MSO_AMP_MOD_LFO_LEVEL));
	ui->spinBox_MSOsynth_AmpModLfoLevel->blockSignals(false);

	val = mod_synth_get_mso_synth_int_param(_MSO_AMP_MOD_LFO_RATE);

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

	val = mod_synth_get_mso_synth_int_param(_MSO_AMP_MOD_LFO_SYMMETRY);

	ui->dial_MSOsynth_AmpModLFOsymmetry->blockSignals(true);
	ui->dial_MSOsynth_AmpModLFOsymmetry->setValue(val);
	ui->dial_MSOsynth_AmpModLFOsymmetry->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_MSOsynth_AmpModLFOsymmetry->setText(QString(text));

	ui->comboBox_MSOsynth_AmpModLFOwaveform->blockSignals(true);
	ui->comboBox_MSOsynth_AmpModLFOwaveform->setCurrentIndex(mod_synth_get_mso_synth_int_param(_MSO_AMP_MOD_LFO_WAVEFORM));
	ui->comboBox_MSOsynth_AmpModLFOwaveform->blockSignals(false);

	ui->dial_MSOsynth_AmpModAdsrLevel->blockSignals(true);
	ui->dial_MSOsynth_AmpModAdsrLevel->setValue(mod_synth_get_mso_synth_int_param(_MSO_AMP_MOD_ENV_LEVEL));
	ui->dial_MSOsynth_AmpModAdsrLevel->blockSignals(false);

	ui->spinBox_MSOsynth_AmpModAdsrLevel->blockSignals(true);
	ui->spinBox_MSOsynth_AmpModAdsrLevel->setValue(mod_synth_get_mso_synth_int_param(_MSO_AMP_MOD_ENV_LEVEL));
	ui->spinBox_MSOsynth_AmpModAdsrLevel->blockSignals(false);

	adsr_attack[_MSO_AMP_MOD] = mod_synth_get_mso_synth_int_param(_MSO_AMP_MOD_ENV_ATTACK);
	adsr_decay[_MSO_AMP_MOD] = mod_synth_get_mso_synth_int_param(_MSO_AMP_MOD_ENV_DECAY);
	adsr_sustain[_MSO_AMP_MOD] = mod_synth_get_mso_synth_int_param(_MSO_AMP_MOD_ENV_SUSTAIN);
	adsr_release[_MSO_AMP_MOD] = mod_synth_get_mso_synth_int_param(_MSO_AMP_MOD_ENV_RELEASE);

	ui->verticalSlider_MSOsynth_AmpModAdsrA->blockSignals(true);
	ui->verticalSlider_MSOsynth_AmpModAdsrA->setValue(adsr_attack[_MSO_AMP_MOD]);
	ui->verticalSlider_MSOsynth_AmpModAdsrA->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0, adsr_attack[_MSO_AMP_MOD]));

	ui->lineEdit_MSOsynth_AmpModAdsrA->setText(QString(text));

	ui->verticalSlider_MSOsynth_AmpModAdsrD->blockSignals(true);
	ui->verticalSlider_MSOsynth_AmpModAdsrD->setValue(adsr_decay[_MSO_AMP_MOD]);
	ui->verticalSlider_MSOsynth_AmpModAdsrD->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0, adsr_decay[_MSO_AMP_MOD]));

	ui->lineEdit_MSOsynth_AmpModAdsrD->setText(QString(text));

	ui->verticalSlider_MSOsynth_AmpModAdsrS->blockSignals(true);
	ui->verticalSlider_MSOsynth_AmpModAdsrS->setValue(adsr_sustain[_MSO_AMP_MOD]);
	ui->verticalSlider_MSOsynth_AmpModAdsrS->blockSignals(false);

	sprintf(text, "%i%c", adsr_sustain[_MSO_AMP_MOD], '%');
	ui->lineEdit_MSOsynth_AmpModAdsrS->setText(QString(text));

	ui->verticalSlider_MSOsynth_AmpModAdsrR->blockSignals(true);
	ui->verticalSlider_MSOsynth_AmpModAdsrR->setValue(adsr_release[_MSO_AMP_MOD]);
	ui->verticalSlider_MSOsynth_AmpModAdsrR->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0, adsr_release[_MSO_AMP_MOD]));

	ui->lineEdit_MSOsynth_AmpModAdsrR->setText(QString(text));

	ui->dial_MSOsynth_FreqModLFOLevel->blockSignals(true);
	ui->dial_MSOsynth_FreqModLFOLevel->setValue(mod_synth_get_mso_synth_int_param(_MSO_FREQ_MOD_LFO_LEVEL));
	ui->dial_MSOsynth_FreqModLFOLevel->blockSignals(false);

	ui->spinBox_MSOsynth_FreqModLfoLevel->blockSignals(true);
	ui->spinBox_MSOsynth_FreqModLfoLevel->setValue(mod_synth_get_mso_synth_int_param(_MSO_FREQ_MOD_LFO_LEVEL));
	ui->spinBox_MSOsynth_FreqModLfoLevel->blockSignals(false);

	val = mod_synth_get_mso_synth_int_param(_MSO_FREQ_MOD_LFO_RATE);

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

	val = mod_synth_get_mso_synth_int_param(_MSO_FREQ_MOD_LFO_SYMMETRY);

	ui->dial_MSOsynth_FreqModLFOsymmetry->blockSignals(true);
	ui->dial_MSOsynth_FreqModLFOsymmetry->setValue(val);
	ui->dial_MSOsynth_FreqModLFOsymmetry->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_MSOsynth_FreqModLFOsymmetry->setText(QString(text));

	ui->comboBox_MSOsynth_FreqModLFOwaveform->blockSignals(true);
	ui->comboBox_MSOsynth_FreqModLFOwaveform->setCurrentIndex(mod_synth_get_mso_synth_int_param(_MSO_FREQ_MOD_LFO_WAVEFORM));
	ui->comboBox_MSOsynth_FreqModLFOwaveform->blockSignals(false);

	ui->dial_MSOsynth_FreqModAdsrLevel->blockSignals(true);
	ui->dial_MSOsynth_FreqModAdsrLevel->setValue(mod_synth_get_mso_synth_int_param(_MSO_FREQ_MOD_ENV_LEVEL));
	ui->dial_MSOsynth_FreqModAdsrLevel->blockSignals(false);

	ui->spinBox_MSOsynth_FreqModAdsrLevel->blockSignals(true);
	ui->spinBox_MSOsynth_FreqModAdsrLevel->setValue(mod_synth_get_mso_synth_int_param(_MSO_FREQ_MOD_ENV_LEVEL));
	ui->spinBox_MSOsynth_FreqModAdsrLevel->blockSignals(false);

	adsr_attack[_MSO_FREQ_MOD] = mod_synth_get_mso_synth_int_param(_MSO_FREQ_MOD_ENV_ATTACK);
	adsr_decay[_MSO_FREQ_MOD] = mod_synth_get_mso_synth_int_param(_MSO_FREQ_MOD_ENV_DECAY);
	adsr_sustain[_MSO_FREQ_MOD] = mod_synth_get_mso_synth_int_param(_MSO_FREQ_MOD_ENV_SUSTAIN);
	adsr_release[_MSO_FREQ_MOD] = mod_synth_get_mso_synth_int_param(_MSO_FREQ_MOD_ENV_RELEASE);

	ui->verticalSlider_MSOsynth_FreqModAdsrA->blockSignals(true);
	ui->verticalSlider_MSOsynth_FreqModAdsrA->setValue(adsr_attack[_MSO_FREQ_MOD]);
	ui->verticalSlider_MSOsynth_FreqModAdsrA->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0, adsr_attack[_MSO_FREQ_MOD]));

	ui->lineEdit_MSOsynth_FreqModAdsrA->setText(QString(text));

	ui->verticalSlider_MSOsynth_FreqModAdsrD->blockSignals(true);
	ui->verticalSlider_MSOsynth_FreqModAdsrD->setValue(adsr_decay[_MSO_FREQ_MOD]);
	ui->verticalSlider_MSOsynth_FreqModAdsrD->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0, adsr_decay[_MSO_FREQ_MOD]));

	ui->lineEdit_MSOsynth_FreqModAdsrD->setText(QString(text));

	ui->verticalSlider_MSOsynth_FreqModAdsrS->blockSignals(true);
	ui->verticalSlider_MSOsynth_FreqModAdsrS->setValue(adsr_sustain[_MSO_FREQ_MOD]);
	ui->verticalSlider_MSOsynth_FreqModAdsrS->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_MSOsynth_FreqModAdsrS->setText(QString(text));

	ui->verticalSlider_MSOsynth_FreqModAdsrR->blockSignals(true);
	ui->verticalSlider_MSOsynth_FreqModAdsrR->setValue(adsr_release[_MSO_FREQ_MOD]);
	ui->verticalSlider_MSOsynth_FreqModAdsrR->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0, adsr_release[_MSO_FREQ_MOD]));

	ui->lineEdit_MSOsynth_FreqModAdsrR->setText(QString(text));

	/*
	ui->dial_MSOsynth_PwmModLFOLevel->blockSignals(true);
	ui->dial_MSOsynth_PwmModLFOLevel->setValue(mod_synth_get_mso_synth_int_param(_MSO_PWM_MOD_LFO_LEVEL));
	ui->dial_MSOsynth_PwmModLFOLevel->blockSignals(false);

	ui->spinBox_MSOsynth_PwmModLfoLevel->blockSignals(true);
	ui->spinBox_MSOsynth_PwmModLfoLevel->setValue(mod_synth_get_mso_synth_int_param(_MSO_PWM_MOD_LFO_LEVEL));
	ui->spinBox_MSOsynth_PwmModLfoLevel->blockSignals(false);

	val = mod_synth_get_mso_synth_int_param(_MSO_SYM_MOD_LFO_RATE);

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

	ui->dial_MSOsynth_PwmModLFOsymmetry->blockSignals(true);
	ui->dial_MSOsynth_PwmModLFOsymmetry->setValue(mod_synth_get_mso_synth_int_param(_MSO_SYM_MOD_LFO_SYMMETRY));
	ui->dial_MSOsynth_PwmModLFOsymmetry->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_MSOsynth_PwmModLFOsymmetry->setText(QString(text));

	ui->comboBox_MSOsynth_PwmModLFOwaveform->blockSignals(true);
	ui->comboBox_MSOsynth_PwmModLFOwaveform->setCurrentIndex(mod_synth_get_mso_synth_int_param(_MSO_SYM_MOD_LFO_WAVEFORM));
	ui->comboBox_MSOsynth_PwmModLFOwaveform->blockSignals(false);

	ui->dial_MSOsynth_PwmModAdsrLevel->blockSignals(true);
	ui->dial_MSOsynth_PwmModAdsrLevel->setValue(mod_synth_get_mso_synth_int_param(_MSO_PWM_MOD_ENV_LEVEL));
	ui->dial_MSOsynth_PwmModAdsrLevel->blockSignals(false);

	ui->spinBox_MSOsynth_PwmModAdsrLevel->blockSignals(true);
	ui->spinBox_MSOsynth_PwmModAdsrLevel->setValue(mod_synth_get_mso_synth_int_param(_MSO_PWM_MOD_ENV_LEVEL));
	ui->spinBox_MSOsynth_PwmModAdsrLevel->blockSignals(false);

	adsr_attack[_MSO_PWM_MOD] = mod_synth_get_mso_synth_int_param(_MSO_SYM_MOD_ENV_ATTACK);
	adsr_decay[_MSO_PWM_MOD] = mod_synth_get_mso_synth_int_param(_MSO_SYM_MOD_ENV_DECAY);
	adsr_sustain[_MSO_PWM_MOD] = mod_synth_get_mso_synth_int_param(_MSO_SYM_MOD_ENV_SUSTAIN);
	adsr_release[_MSO_PWM_MOD] = mod_synth_get_mso_synth_int_param(_MSO_SYM_MOD_ENV_RELEASE);

	ui->verticalSlider_MSOsynth_PwmModAdsrA->blockSignals(true);
	ui->verticalSlider_MSOsynth_PwmModAdsrA->setValue(adsr_attack[_MSO_PWM_MOD]);
	ui->verticalSlider_MSOsynth_PwmModAdsrA->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0, adsr_attack[_MSO_PWM_MOD]));

	ui->lineEdit_MSOsynth_PwmModAdsrA->setText(QString(text));

	ui->verticalSlider_MSOsynth_PwmModAdsrD->blockSignals(true);
	ui->verticalSlider_MSOsynth_PwmModAdsrD->setValue(adsr_decay[_MSO_PWM_MOD]);
	ui->verticalSlider_MSOsynth_PwmModAdsrD->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0, adsr_decay[_MSO_PWM_MOD]));

	ui->lineEdit_MSOsynth_PwmModAdsrD->setText(QString(text));

	ui->verticalSlider_MSOsynth_PwmModAdsrS->blockSignals(true);
	ui->verticalSlider_MSOsynth_PwmModAdsrS->setValue(adsr_sustain[_MSO_PWM_MOD]);
	ui->verticalSlider_MSOsynth_PwmModAdsrS->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_MSOsynth_PwmModAdsrS->setText(QString(text));

	ui->verticalSlider_MSOsynth_PwmModAdsrR->blockSignals(true);
	ui->verticalSlider_MSOsynth_PwmModAdsrR->setValue(adsr_release[_MSO_PWM_MOD]);
	ui->verticalSlider_MSOsynth_PwmModAdsrR->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0, adsr_release[_MSO_PWM_MOD]));

	ui->lineEdit_MSOsynth_PwmModAdsrR->setText(QString(text));
*/

	ui->dial_MsoSynthFilterFreq->blockSignals(true);
	ui->dial_MsoSynthFilterFreq->setValue(mod_synth_get_mso_synth_int_param(_FILTER_FREQ));
	ui->dial_MsoSynthFilterFreq->blockSignals(false);

	sprintf(text,
			"%.1f Hz",
			mod_synth_get_filter_min_center_freq() +
				(mod_synth_get_filter_max_center_freq() -
				 mod_synth_get_filter_min_center_freq()) *
					mod_synth_get_mso_synth_int_param(_FILTER_FREQ) / 100.0f);

	ui->lineEdit_MsoSynthFilterFreq->setText(QString(text));

	ui->dial_MsoSynthFilterOctave->blockSignals(true);
	ui->dial_MsoSynthFilterOctave->setValue(mod_synth_get_mso_synth_int_param(_FILTER_OCT));
	ui->dial_MsoSynthFilterOctave->blockSignals(false);

	sprintf(text,
			"%.4f",
			(float)mod_synth_get_mso_synth_int_param(_FILTER_OCT) * 6.9999f / 100.0f);

	ui->lineEdit_MsoSynthFilterOctave->setText(QString(text));

	ui->dial_MsoSynthFilterQ->blockSignals(true);
	ui->dial_MsoSynthFilterQ->setValue(mod_synth_get_mso_synth_int_param(_FILTER_Q));
	ui->dial_MsoSynthFilterQ->blockSignals(false);

	sprintf(text,
			"%.1f",
			mod_synth_get_filter_min_Q() +
				(mod_synth_get_filter_max_Q() -
				 mod_synth_get_filter_min_Q()) *
					mod_synth_get_mso_synth_int_param(_FILTER_Q) / 100.0f);

	ui->lineEdit_MsoSynthFilterQ->setText(QString(text));

	ui->dial_MsoSynthFilterKbdTrack->blockSignals(true);
	ui->dial_MsoSynthFilterKbdTrack->setValue(mod_synth_get_mso_synth_int_param(_FILTER_KBD_TRACK));
	ui->dial_MsoSynthFilterKbdTrack->blockSignals(false);

	ui->lineEdit_MsoSynthFilterKbdTrack->setText(QString::number(mod_synth_get_mso_synth_int_param(_FILTER_KBD_TRACK)));

	ui->comboBox_MsoSynthFilterBand->blockSignals(true);
	ui->comboBox_MsoSynthFilterBand->setCurrentIndex(mod_synth_get_mso_synth_int_param(_FILTER_BAND));
	ui->comboBox_MsoSynthFilterBand->blockSignals(false);

	ui->dial_MSOsynth_FilterFreqModLFOLevel->blockSignals(true);
	ui->dial_MSOsynth_FilterFreqModLFOLevel->setValue(mod_synth_get_mso_synth_int_param(_FILTER_FREQ_MOD_LFO_LEVEL));
	ui->dial_MSOsynth_FilterFreqModLFOLevel->blockSignals(false);

	ui->spinBox_MSOsynth_FilterFreqModLfoLevel->blockSignals(true);
	ui->spinBox_MSOsynth_FilterFreqModLfoLevel->setValue(mod_synth_get_mso_synth_int_param(_FILTER_FREQ_MOD_LFO_LEVEL));
	ui->spinBox_MSOsynth_FilterFreqModLfoLevel->blockSignals(false);

	val = mod_synth_get_mso_synth_int_param(_MSO_FILTER_FREQ_MOD_LFO_RATE);

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

	val = mod_synth_get_mso_synth_int_param(_MSO_FILTER_FREQ_MOD_LFO_SYMMETRY);

	ui->dial_MSOsynth_FilterFreqModLFOsymmetry->blockSignals(true);
	ui->dial_MSOsynth_FilterFreqModLFOsymmetry->setValue(val);
	ui->dial_MSOsynth_FilterFreqModLFOsymmetry->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_MSOsynth_FilterFreqModLFOsymmetry->setText(QString(text));

	ui->comboBox_MSOsynth_FilterFreqModLFOwaveform->blockSignals(true);
	ui->comboBox_MSOsynth_FilterFreqModLFOwaveform->setCurrentIndex(mod_synth_get_mso_synth_int_param(_MSO_FILTER_FREQ_MOD_LFO_WAVEFORM));
	ui->comboBox_MSOsynth_FilterFreqModLFOwaveform->blockSignals(false);

	ui->dial_MSOsynth_FilterFreqModAdsrLevel->blockSignals(true);
	ui->dial_MSOsynth_FilterFreqModAdsrLevel->setValue(mod_synth_get_mso_synth_int_param(_FILTER_FREQ_MOD_ENV_LEVEL));
	ui->dial_MSOsynth_FilterFreqModAdsrLevel->blockSignals(false);

	ui->spinBox_MSOsynth_FilterFreqModAdsrLevel->blockSignals(true);
	ui->spinBox_MSOsynth_FilterFreqModAdsrLevel->setValue(mod_synth_get_mso_synth_int_param(_FILTER_FREQ_MOD_ENV_LEVEL));
	ui->spinBox_MSOsynth_FilterFreqModAdsrLevel->blockSignals(false);

	adsr_attack[_FILTER_FREQ_MOD] = mod_synth_get_mso_synth_int_param(_MSO_FILTER_FREQ_MOD_ENV_ATTACK);
	adsr_decay[_FILTER_FREQ_MOD] = mod_synth_get_mso_synth_int_param(_MSO_FILTER_FREQ_MOD_ENV_DECAY);
	adsr_sustain[_FILTER_FREQ_MOD] = mod_synth_get_mso_synth_int_param(_MSO_FILTER_FREQ_MOD_ENV_SUSTAIN);
	adsr_release[_FILTER_FREQ_MOD] = mod_synth_get_mso_synth_int_param(_MSO_FILTER_FREQ_MOD_ENV_RELEASE);

	ui->verticalSlider_MSOsynth_FilterFreqModAdsrA->blockSignals(true);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrA->setValue(adsr_attack[_FILTER_FREQ_MOD]);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrA->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0, adsr_attack[_FILTER_FREQ_MOD]));

	ui->lineEdit_MSOsynth_FilterFreqModAdsrA->setText(QString(text));

	ui->verticalSlider_MSOsynth_FilterFreqModAdsrD->blockSignals(true);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrD->setValue(adsr_decay[_FILTER_FREQ_MOD]);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrD->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0, adsr_decay[_FILTER_FREQ_MOD]));

	ui->lineEdit_MSOsynth_FilterFreqModAdsrD->setText(QString(text));

	ui->verticalSlider_MSOsynth_FilterFreqModAdsrS->blockSignals(true);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrS->setValue(adsr_sustain[_FILTER_FREQ_MOD]);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrS->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_MSOsynth_FilterFreqModAdsrS->setText(QString(text));

	ui->verticalSlider_MSOsynth_FilterFreqModAdsrR->blockSignals(true);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrR->setValue(adsr_release[_FILTER_FREQ_MOD]);
	ui->verticalSlider_MSOsynth_FilterFreqModAdsrR->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0, adsr_release[_FILTER_FREQ_MOD]));

	ui->lineEdit_MSOsynth_FilterFreqModAdsrR->setText(QString(text));

	if (replot_waveform.load())
	{

		setup_plot(ui->widget_MsoSynthWaveformPlot);
		ui->widget_MsoSynthWaveformPlot->replot();

		replot_waveform.store(false);
	}

	if (update_amp_mod_adsr_plot.load())
	{
		refresh_adsr_curve_view(_MSO_AMP_MOD, ui->widget_MSOsynth_AmpModADSRplot);
		update_amp_mod_adsr_plot.store(false);
	}

	//if (update_sym_mod_adsr_plot.load())
	//{
	//	refresh_adsr_curve_view(_MSO_PWM_MOD, ui->widget_MSOsynth_PwmModADSRplot);
	//	update_sym_mod_adsr_plot.store(false);
	//}

	if (update_freq_mod_adsr_plot.load())
	{
		refresh_adsr_curve_view(_MSO_FREQ_MOD, ui->widget_MSOsynth_FreqModADSRplot);
		update_freq_mod_adsr_plot.store(false);
	}

	if (update_filter_freq_mod_adsr_plot.load())
	{
		refresh_adsr_curve_view(_FILTER_FREQ_MOD, ui->widget_MSOsynth_FilterFreqModADSRplot);
		update_filter_freq_mod_adsr_plot.store(false);
	}
}

void Dialog_MSOsynthesizer::set_adsr_plot_widget_points(int env_id)
{
	if (_MSO_AMP_MOD < 0 || env_id > _FILTER_FREQ_MOD)
	{
		return;
	}

	const int max_param_value = 100;

	adsr_attack[env_id] = mod_synth_log_scale_100_int(0, max_param_value, 10, adsr_attack[env_id]);
	adsr_decay[env_id] = mod_synth_log_scale_100_int(0, max_param_value, 10, adsr_decay[env_id]);
	adsr_release[env_id] = mod_synth_log_scale_100_int(0, max_param_value, 10, adsr_release[env_id]);

	adsr_curve_attack_end_point =
		_MSO_SYNTH_ADSR_CURVE_START_POINT + 1 +
		((adsr_attack[env_id] * adsr_curve_max_attack * _MSO_SYNTH_ADSR_CURVE_TIME_MULTIPLIER) /
		 max_param_value);

	adsr_curve_decay_end_point =
		adsr_curve_attack_end_point + 1 +
		((adsr_decay[env_id] * adsr_curve_max_decay * _MSO_SYNTH_ADSR_CURVE_TIME_MULTIPLIER) /
		 max_param_value);

	adsr_curve_sustain_end_point =
		adsr_curve_decay_end_point + 1 +
		_MSO_SYNTH_ADSR_CURVE_SUSTAIN_SEGMENT_LENGTH;

	adsr_curve_release_end_point =
		adsr_curve_sustain_end_point + 1 +
		((adsr_release[env_id] * adsr_curve_max_release *
		  _MSO_SYNTH_ADSR_CURVE_TIME_MULTIPLIER) /
		 max_param_value);
}

void Dialog_MSOsynthesizer::refresh_adsr_curve_view(int env_id, QCustomPlot *adsr_plot)
{
	if (_MSO_AMP_MOD < 0 || env_id > _FILTER_FREQ_MOD || adsr_plot == NULL)
	{
		return;
	}

	set_adsr_plot_widget_points(env_id);
	
	QVector<double> x(8), y(8);

	x[0] = 0;
	y[0] = 0;

	x[1] = _MSO_SYNTH_ADSR_CURVE_START_POINT;
	y[1] = 0;

	x[2] = adsr_curve_attack_end_point;
	y[2] = _MSO_SYNTH_ADSR_CURVE_HEIGHT;

	x[3] = adsr_curve_decay_end_point;
	y[3] = adsr_sustain[env_id] * _MSO_SYNTH_ADSR_CURVE_HEIGHT / 100;

	x[4] = adsr_curve_sustain_end_point;
	y[4] = adsr_sustain[env_id] * _MSO_SYNTH_ADSR_CURVE_HEIGHT / 100;

	x[5] = adsr_curve_release_end_point;
	y[5] = 0;

	x[6] = adsr_plot_length;
	y[6] = 0;

	adsr_plot->graph(0)->setData(x, y);
	adsr_plot->xAxis->setRange(0, adsr_plot_length);

	adsr_plot->replot();
}
