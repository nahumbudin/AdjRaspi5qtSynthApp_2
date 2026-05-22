/**
 * @file		Dialog_StringSynthesizer.cpp
 *	@author		Nahum Budin
 *	@date		1-May-2026
 *	@version	1.0
 *
 *	@brief		Adj String Synthesizer (KPS) control dialog
 *
 */


#include "filesystem"

#include <QMessageBox>
#include <QTimer>

#include "Dialog_StringSynthesizer.h"
#include "ui_Dialog_StringSynthesizer.h"
#include "utils.h"

#include "MainWindow.h"
#include "GuiNavigator.h"
#include "CustomFileDialog.h"

#define _UPDATE_TIMER_PERIOD_MS 250

Dialog_StringSynthesizer *Dialog_StringSynthesizer::dialog_string_synthesizer_instance = NULL;

LoadStringSynthesizerPresetFileThread *load_string_synthesizer_preset_file_thread;
SaveStringSynthesizerPresetFileThread *save_string_synthesizer_preset_file_thread;

QString string_synth_preset_file_name;

void string_synthesizer_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	// Just forward to the dialog instance - it will emit a signal
	Dialog_StringSynthesizer::get_instance()->control_box_event_received(evnt, val);
}

void SaveStringSynthesizerPresetFileThread::run()
{
	int res;

	QString result = QString("Preset File Saved");
	res = mod_synth_save_string_synthesizer_preset_file(string_synth_preset_file_name.toStdString());

	emit savePresetFileDone(result);
}

void LoadStringSynthesizerPresetFileThread::run()
{
	int res;

	QString result = QString("Preset File Loaded");
	res = mod_synth_load_string_synthesizer_preset_file(string_synth_preset_file_name.toStdString());

	emit loadPresetFileDone(result);
}

Dialog_StringSynthesizer::Dialog_StringSynthesizer(QWidget *parent)
	: QDialog(parent), ui(new Ui::Dialog_StringSynthesizer)
{
	ui->setupUi(this);

	// Prevent dialog from being deleted when closed - only hide it
	setAttribute(Qt::WA_DeleteOnClose, false);

	ui->frame_KarplusStringAll->setAutoFillBackground(true);
	ui->frame_KarplusStringAll->setStyleSheet("background-color: rgb(5, 5, 5);");
	
	dialog_string_synthesizer_instance = this;
	close_event_callback_ptr = NULL;

	// Connect signal to slot with Qt::QueuedConnection for thread-safety
	// This ensures the slot runs in the GUI thread
	connect(this, &Dialog_StringSynthesizer::control_box_event_signal,
			this, &Dialog_StringSynthesizer::handle_control_box_event,
			Qt::QueuedConnection);

	// Register control box event callback
	mod_synth_register_callback_control_box_event_update_ui(
		&string_synthesizer_control_box_event_update_ui_callback_wrapper);

	init_gui_elements();

	// Register with GuiNavigator (no tabs, no frames for String Synthesizer)
	GuiNavigator::get_instance()->register_dialog(this, "String Synthesizer");

	// Also register with MainWindow for compatibility
	MainWindow::get_instance()->register_active_dialog(this);

	// GUI Update timer start
	start_update_timer(_UPDATE_TIMER_PERIOD_MS);

	/* Set focus on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);

	static int eqalizer_band[10] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
	static int prev_eqalizer_band[10] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
}

Dialog_StringSynthesizer::~Dialog_StringSynthesizer()
{
	// Reset static instance pointer when destroyed
	dialog_string_synthesizer_instance = nullptr;
	delete ui;
}

Dialog_StringSynthesizer *Dialog_StringSynthesizer::get_instance(QWidget *parent)
{
	if (dialog_string_synthesizer_instance == NULL)
	{
		dialog_string_synthesizer_instance = new Dialog_StringSynthesizer(parent);
	}
	return dialog_string_synthesizer_instance;
}

// Thread-safe function called from callback - just emits signal
void Dialog_StringSynthesizer::control_box_event_received(int evnt, uint16_t val)
{
	// Emit signal - Qt will queue it to run in GUI thread
	emit control_box_event_signal(evnt, val);
}

void Dialog_StringSynthesizer::init_gui_elements()
{
	int result;

	ui->frame_KPS_Distortion->setBorderColor(_CONTROLS_COLOR_GRAY);
	ui->frame_KPS_Distortion->setBorderWidth(3);

	ui->comboBox_KPStuneOctave->blockSignals(true);
	ui->comboBox_KPStuneSemitones->blockSignals(true);

	ui->comboBox_KPStuneOctave->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_KPStuneOctave->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_KPStuneOctave->setFrameColor(_CONTROLS_COLOR_YELLOW);
	ui->comboBox_KPStuneOctave->setFrameWidth(2);
	ui->comboBox_KPStuneOctave->setCurrentIndex(mod_synth_get_active_osc1_detune_octave() - mod_synth_get_osc_detune_min_octave());

	ui->comboBox_KPStuneSemitones->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_KPStuneSemitones->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_KPStuneSemitones->setFrameColor(_CONTROLS_COLOR_RED);
	ui->comboBox_KPStuneSemitones->setFrameWidth(2);
	ui->comboBox_KPStuneSemitones->setCurrentIndex(mod_synth_get_active_osc1_detune_semitones() - mod_synth_get_osc_detune_min_semitones());

	for (int i = _OSC_DETUNE_MIN_OCTAVE; i <= _OSC_DETUNE_MAX_OCTAVE; i++)
	{
		ui->comboBox_KPStuneOctave->addItem(QString::number(i));
	}

	for (int i = _OSC_DETUNE_MIN_SEMITONES; i <= _OSC_DETUNE_MAX_SEMITONES; i++)
	{
		ui->comboBox_KPStuneSemitones->addItem(QString::number(i));
	}

	ui->comboBox_KPStuneOctave->setCurrentIndex(6);		// 0 octave offset (centered), with range of -6 to +6 octaves (13 steps total)
	ui->comboBox_KPStuneSemitones->setCurrentIndex(11); // 0 semitone offset (centered), with range of -11 to +11 semitones (23 steps total)

	ui->comboBox_KPStuneOctave->blockSignals(false);
	ui->comboBox_KPStuneSemitones->blockSignals(false);
	
	string_karplus_excitation_waveform_list.append("White Noise");
	string_karplus_excitation_waveform_list.append("Pink Noise");
	string_karplus_excitation_waveform_list.append("Brown Noise");
	string_karplus_excitation_waveform_list.append("Sine Chirp");
	string_karplus_excitation_waveform_list.append("Decayed Sine");
	string_karplus_excitation_waveform_list.append("Sawtooth Wave");
	string_karplus_excitation_waveform_list.append("Square Wave");

	string_karplus_string_damping_calc_mode_list.append("Direct");
	string_karplus_string_damping_calc_mode_list.append("Magic");

	ui->comboBox_KarplusSynth_ExcitationWaveform->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_KarplusSynth_ExcitationWaveform->setFrameColor(_CONTROLS_COLOR_GREEN);
	ui->comboBox_KarplusSynth_ExcitationWaveform->setFrameWidth(2);
	
	ui->comboBox_KarplusSynth_ExcitationWaveform->blockSignals(true);
	ui->comboBox_KarplusSynth_ExcitationWaveform->addItems(string_karplus_excitation_waveform_list);
	ui->comboBox_KarplusSynth_ExcitationWaveform->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_KarplusSynth_ExcitationWaveform->blockSignals(false);

	ui->comboBox_KarplusSynth_CalculationMode->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_KarplusSynth_CalculationMode->setFrameColor(_CONTROLS_COLOR_WHITE);
	ui->comboBox_KarplusSynth_CalculationMode->setFrameWidth(2);
	
	ui->comboBox_KarplusSynth_CalculationMode->blockSignals(true);
	ui->comboBox_KarplusSynth_CalculationMode->addItems(string_karplus_string_damping_calc_mode_list);
	ui->comboBox_KarplusSynth_CalculationMode->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_KarplusSynth_CalculationMode->blockSignals(false);

	ui->dial_KarplusSynth_SendFilter1->setKnobColor(_KNOBS_COLOR);
	ui->dial_KarplusSynth_SendFilter1->setCircleColor(_CONTROLS_COLOR_PURPLE);
	ui->dial_KarplusSynth_SendFilter1->setValue(40);

	ui->spinBox_KarplusSynth_SendFilter1->setValue(40);

	ui->dial_KarplusSynth_SendFilter2->setKnobColor(_KNOBS_COLOR);
	ui->dial_KarplusSynth_SendFilter2->setCircleColor(_CONTROLS_COLOR_BLUE);
	ui->dial_KarplusSynth_SendFilter2->setValue(40);

	ui->spinBox_KarplusSynth_SendFilter2->setValue(40);

	ui->horizontalSlider_KarplusSynth_WaveformVariations->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->horizontalSlider_KarplusSynth_WaveformVariations->setFrameColor(_CONTROLS_COLOR_GRAY);
	ui->horizontalSlider_KarplusSynth_WaveformVariations->setHandleColor(_CONTROLS_COLOR_GRAY);
	ui->horizontalSlider_KarplusSynth_WaveformVariations->setProgressColor(_CONTROLS_COLOR_GRAY);

	ui->horizontalSlider_KarplusSynth_OnDecay->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->horizontalSlider_KarplusSynth_OnDecay->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->horizontalSlider_KarplusSynth_OnDecay->setHandleColor(_CONTROLS_COLOR_PURPLE);
	ui->horizontalSlider_KarplusSynth_OnDecay->setProgressColor(_CONTROLS_COLOR_PURPLE);

	ui->horizontalSlider_KarplusSynth_OffDecay->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->horizontalSlider_KarplusSynth_OffDecay->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->horizontalSlider_KarplusSynth_OffDecay->setHandleColor(_CONTROLS_COLOR_BLUE);
	ui->horizontalSlider_KarplusSynth_OffDecay->setProgressColor(_CONTROLS_COLOR_BLUE);

	ui->horizontalSlider_KarplusSynth_StringDamping->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->horizontalSlider_KarplusSynth_StringDamping->setFrameColor(_CONTROLS_COLOR_GREEN);
	ui->horizontalSlider_KarplusSynth_StringDamping->setHandleColor(_CONTROLS_COLOR_GREEN);
	ui->horizontalSlider_KarplusSynth_StringDamping->setProgressColor(_CONTROLS_COLOR_GREEN);

	ui->horizontalSlider_KarplusSynth_StringDampingVariations->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->horizontalSlider_KarplusSynth_StringDampingVariations->setFrameColor(_CONTROLS_COLOR_WHITE);
	ui->horizontalSlider_KarplusSynth_StringDampingVariations->setHandleColor(_CONTROLS_COLOR_WHITE);
	ui->horizontalSlider_KarplusSynth_StringDampingVariations->setProgressColor(_CONTROLS_COLOR_WHITE);

	ui->horizontalSlider_KarplusSynth_PluckDamping->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->horizontalSlider_KarplusSynth_PluckDamping->setFrameColor(_CONTROLS_COLOR_YELLOW);
	ui->horizontalSlider_KarplusSynth_PluckDamping->setHandleColor(_CONTROLS_COLOR_YELLOW);
	ui->horizontalSlider_KarplusSynth_PluckDamping->setProgressColor(_CONTROLS_COLOR_YELLOW);

	ui->horizontalSlider_KarplusSynth_PluckDampingVariations->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->horizontalSlider_KarplusSynth_PluckDampingVariations->setFrameColor(_CONTROLS_COLOR_RED);
	ui->horizontalSlider_KarplusSynth_PluckDampingVariations->setHandleColor(_CONTROLS_COLOR_RED);
	ui->horizontalSlider_KarplusSynth_PluckDampingVariations->setProgressColor(_CONTROLS_COLOR_RED);

	ui->horizontalSlider_KarplusSynth_CharacterVariations->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->horizontalSlider_KarplusSynth_CharacterVariations->setFrameColor(_CONTROLS_COLOR_BLACK);
	ui->horizontalSlider_KarplusSynth_CharacterVariations->setHandleColor(_CONTROLS_COLOR_BLACK);
	ui->horizontalSlider_KarplusSynth_CharacterVariations->setProgressColor(_CONTROLS_COLOR_BLACK);

	ui->dial_KPSdistortionDrive->setKnobColor(_KNOBS_COLOR);
	ui->dial_KPSdistortionDrive->setCircleColor(_CONTROLS_COLOR_PURPLE);
	ui->dial_KPSdistortionDrive->setValue(0);
	
	ui->dial_KPSdistortionRange->setKnobColor(_KNOBS_COLOR);
	ui->dial_KPSdistortionRange->setCircleColor(_CONTROLS_COLOR_BLUE);
	ui->dial_KPSdistortionRange->setValue(0);

	ui->dial_KPSdistortionBlend->setKnobColor(_KNOBS_COLOR);
	ui->dial_KPSdistortionBlend->setCircleColor(_CONTROLS_COLOR_GREEN);
	ui->dial_KPSdistortionBlend->setValue(0);

	ui->checkBox_KPSdistortionActive->setLedStyle(true);
	ui->checkBox_KPSdistortionActive->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_KPSdistortionActive->setFrameColor(_CONTROLS_COLOR_WHITE);
	ui->checkBox_KPSdistortionActive->setBackgroundColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_KPSdistortionActive->setCheckBoxSize(16);
	ui->checkBox_KPSdistortionActive->setFrameWidth(2);

	ui->checkBox_KPSdistortionAutoGain->setLedStyle(true);
	ui->checkBox_KPSdistortionAutoGain->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_KPSdistortionAutoGain->setFrameColor(_CONTROLS_COLOR_YELLOW);
	ui->checkBox_KPSdistortionAutoGain->setBackgroundColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_KPSdistortionAutoGain->setCheckBoxSize(16);
	ui->checkBox_KPSdistortionAutoGain->setFrameWidth(2);

	ui->spinBox_KarplusSynth_SendFilter2->setValue(40);

	ui->pushButton_KPSpresetOpen->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->pushButton_KPSpresetOpen->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);

	ui->pushButton_KPSpresetSave->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->pushButton_KPSpresetSave->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);

	set_signal_slots_connections();
}

void Dialog_StringSynthesizer::set_signal_slots_connections()
{
	connect(ui->comboBox_KarplusSynth_ExcitationWaveform,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_karplus_excitation_waveform_combobox_changed(int)));

	connect(ui->horizontalSlider_KarplusSynth_WaveformVariations,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_karplus_excitation_waveform_variations_slider_changed(int)));

	connect(ui->comboBox_KarplusSynth_CalculationMode,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_karplus_string_damping_calc_mode_combobox_hanged(int)));

	connect(ui->horizontalSlider_KarplusSynth_StringDamping,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_karplus_string_damping_slider_changed(int)));

	connect(ui->horizontalSlider_KarplusSynth_StringDampingVariations,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_karplus_string_damping_variation_slider_changed(int)));

	connect(ui->horizontalSlider_KarplusSynth_PluckDamping,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_karplus_pluck_damping_slider_changed(int)));

	connect(ui->horizontalSlider_KarplusSynth_PluckDampingVariations,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_karplus_pluck_damping_variation_slider_changed(int)));

	connect(ui->horizontalSlider_KarplusSynth_OnDecay,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_karplus_on_decay_slider_changed(int)));

	connect(ui->horizontalSlider_KarplusSynth_OffDecay,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_karplus_off_decay_slider_changed(int)));

	connect(ui->horizontalSlider_KarplusSynth_CharacterVariations,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_karplus_character_variations_slider_changed(int)));

	connect(ui->dial_KarplusSynth_SendFilter1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_karplus_send_filter1_dial_changed(int)));

	connect(ui->dial_KarplusSynth_SendFilter2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_karplus_send_filter2_dial_changed(int)));

	connect(ui->comboBox_KPStuneOctave,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_karplus_tune_octave_combobox_changed(int)));

	connect(ui->comboBox_KPStuneSemitones,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_karplus_tune_semitones_combobox_changed(int)));

	connect(ui->pushButton_KPSpresetOpen,
			SIGNAL(clicked()),
			this,
			SLOT(on_presets_open_pushbutton_clicked()));

	connect(ui->pushButton_KPSpresetSave,
			SIGNAL(clicked()),
			this,
			SLOT(on_presets_save_pushbutton_clicked()));

	connect(ui->dial_KPSdistortionDrive,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_karplus_distortion_drive_dial_changed(int)));

	connect(ui->dial_KPSdistortionRange,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_karplus_distortion_range_dial_changed(int)));

	connect(ui->dial_KPSdistortionBlend,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_karplus_distortion_blend_dial_changed(int)));

	connect(ui->checkBox_KPSdistortionActive,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_karplus_distortion_enabled_checkbox_changed(bool)));

	connect(ui->checkBox_KPSdistortionAutoGain,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_karplus_distortion_autogain_enabled_checkbox_changed(bool)));
}

void Dialog_StringSynthesizer::closeEvent(QCloseEvent *event)
{
	if (close_event_callback_ptr != NULL)
	{
		close_event_callback_ptr();
	}

	// Unregister from GuiNavigator
	GuiNavigator::get_instance()->unregister_dialog(this);

	// Hide instead of accept (which could trigger deletion)
	event->ignore(); // Don't accept the close event

	hide();
}

void Dialog_StringSynthesizer::handle_control_box_event(int evnt, uint16_t val)
{
	// Only process events if this dialog has focus
	if (!this->hasFocus())
	{
		return;
	}

	int slider_level_gap = 0;

	const int send_max = 100;
	const int send_min = 0;
	const int tune_offset_octave_max = 12;
	const int tune_offset_octave_min = 0;
	const int tune_offset_semitone_max = 22;
	const int tune_offset_semitone_min = 0;
	const int kps_control_max_value = 95;
	const int kps_control_min_value = 5;
	const int waveform_max = _KARPLUS_STRONG_EXCITATION_SQUARE_WAVE;
	const int waveform_min = _KARPLUS_STRONG_EXCITATION_WHITE_NOISE;

	static int tune_offset_octave = 6;	  // 0 octave offset (centered), with range of -6 to +6 octaves (13 steps total)
	static int tune_offset_semitone = 11; // 0 semitone offset (centered), with range of -11 to +11 semitones (23 steps total)
	static int send_filter_1 = 40;
	static int send_filter_2 = 40;
	static int waveform = _KARPLUS_STRONG_EXCITATION_WHITE_NOISE;
	static int calculation_mode = _KARPLUS_STRONG_STRING_DAMPING_CALC_DIRECT;
	static int waveform_variations = 50;
	static int string_damping = 50;
	static int string_damping_variations = 50;
	static int pluck_damping = 50;
	static int pluck_damping_variations = 50;
	static int on_decay = 50;
	static int off_decay = 50;
	static int character_variations = 50;
	static bool distortion_enabled = false;
	static bool distortion_autogain_enabled = false;
	static int distortion_drive = 0;
	static int distortion_range = 0;
	static int distortion_blend = 0;

	static int prev_tune_offset_octave = 6;	  // 0 octave offset (centered), with range of -6 to +6 octaves (13 steps total)
	static int prev_tune_offset_semitone = 11; // 0 semitone offset (centered), with range of -11 to +11 semitones (23 steps total)
	static int prev_send_filter_1 = 40;
	static int prev_send_filter_2 = 40;
	static int prev_waveform = _KARPLUS_STRONG_EXCITATION_WHITE_NOISE;
	static int prev_calculation_mode = _KARPLUS_STRONG_STRING_DAMPING_CALC_DIRECT;
	static int prev_waveform_variations = 50;
	static int prev_string_damping = 50;
	static int prev_string_damping_variations = 50;
	static int prev_pluck_damping = 50;
	static int prev_pluck_damping_variations = 50;
	static int prev_on_decay = 50;
	static int prev_off_decay = 50;
	static int prev_character_variations = 50;
	static bool prev_distortion_enabled = false;
	static bool prev_distortion_autogain_enabled = false;
	static int prev_distortion_drive = 0;
	static int prev_distortion_range = 0;
	static int prev_distortion_blend = 0;

	if (evnt == _I2C_CONTROL_ENCODER_2)
	{
		if (val == 4096)
		{
			// pressed - open presets dialog
			on_presets_open_pushbutton_clicked();
		}
		
		// Gray Purple dial - send filter1 control
		send_filter_1 = update_rotary_encoder_value(
			send_filter_1,
			val,
			&prev_send_filter_1,
			send_min,
			send_max,
			4);

		ui->dial_KarplusSynth_SendFilter1->setValue(send_filter_1);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_3)
	{
		if (val == 4096)
		{
			// pressed - save presets dialog
			on_presets_save_pushbutton_clicked();
		}
		
		// Gray Blue dial - send filter2 control
		send_filter_2 = update_rotary_encoder_value(
			send_filter_2,
			val,
			&prev_send_filter_2,
			send_min,
			send_max,
			4);

		ui->dial_KarplusSynth_SendFilter2->setValue(send_filter_2);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_4)
	{
		// Gray Green Combobox - excitation waveform control
		waveform = update_rotary_encoder_value(
			waveform,
			val,
			&prev_waveform,
			waveform_min,
			waveform_max,
			1);

		ui->comboBox_KarplusSynth_ExcitationWaveform->setCurrentIndex(waveform);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_5)
	{
		// Gray White Combobox - calculation control
		calculation_mode = update_rotary_encoder_value(
			calculation_mode,
			val,
			&prev_calculation_mode,
			_KARPLUS_STRONG_STRING_DAMPING_CALC_DIRECT,
			_KARPLUS_STRONG_STRING_DAMPING_CALC_MAGIC,
			1);

		ui->comboBox_KarplusSynth_CalculationMode->setCurrentIndex(calculation_mode);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_6)
	{
		// Gray Yellow Combobox - Octave offset control
		tune_offset_octave = update_rotary_encoder_value(
			tune_offset_octave,
			val,
			&prev_tune_offset_octave,
			tune_offset_octave_min,
			tune_offset_octave_max,
			1);

		ui->comboBox_KPStuneOctave->setCurrentIndex(tune_offset_octave);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_7)
	{
		// Gray Red Combobox - Semitone offset control
		tune_offset_semitone = update_rotary_encoder_value(
			tune_offset_semitone,
			val,
			&prev_tune_offset_semitone,
			tune_offset_semitone_min,
			tune_offset_semitone_max,
			1);

		ui->comboBox_KPStuneSemitones->setCurrentIndex(tune_offset_semitone);
	}
	if (evnt == _I2C_CONTROL_ENCODER_10)
	{
		// White Purple dial - distortin drive control
		distortion_drive = update_rotary_encoder_value(
			distortion_drive,
			val,
			&prev_distortion_drive,
			kps_control_min_value,
			kps_control_max_value,
			4);

		ui->dial_KPSdistortionDrive->setValue(distortion_drive);
	}
	if (evnt == _I2C_CONTROL_ENCODER_11)
	{
		// White Blue dial - distortin range control
		distortion_range = update_rotary_encoder_value(
			distortion_range,
			val,
			&prev_distortion_range,
			kps_control_min_value,
			kps_control_max_value,
			4);

		ui->dial_KPSdistortionRange->setValue(distortion_range);
	}
	if (evnt == _I2C_CONTROL_ENCODER_12)
	{
		// White Green dial - distortin blend control
		distortion_blend = update_rotary_encoder_value(
			distortion_blend,
			val,
			&prev_distortion_blend,
			kps_control_min_value,
			kps_control_max_value,
			4);

		ui->dial_KPSdistortionBlend->setValue(distortion_blend);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_13)
	{
		// White White Dial Pushbutton - Distortion Enable control
		if (val == 4096)
		{
			// pressed - open presets dialog
			on_karplus_distortion_enabled_checkbox_changed(!ui->checkBox_KPSdistortionActive->isChecked());
		}
	}
	else if (evnt == _I2C_CONTROL_ENCODER_14)
	{
		// White Yelow Dial Pushbutton - Distortion Autogain Enable control
		if (val == 4096)
		{
			// pressed - open presets dialog
			on_karplus_distortion_autogain_enabled_checkbox_changed(!ui->checkBox_KPSdistortionAutoGain->isChecked());
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_1)
	{
		// Gray Gray slider - waveform variations control
		// Get new value from slider and calculate gap from current UI value
		waveform_variations = normalize_slider_value(val / 36, kps_control_max_value, kps_control_min_value); // 0-3600 -> 5-95
		slider_level_gap = waveform_variations - ui->horizontalSlider_KarplusSynth_WaveformVariations->value();										
		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) > 0.9)
		{
			// Emits value changed signal.
			ui->horizontalSlider_KarplusSynth_WaveformVariations->setValue(waveform_variations);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_2)
	{
		// Gray Purple slider - on decay control
		// Get new value from slider and calculate gap from current UI value
		on_decay = normalize_slider_value(val / 36, kps_control_max_value, kps_control_min_value); // 0-3600 -> 5-95
		slider_level_gap = on_decay - ui->horizontalSlider_KarplusSynth_OnDecay->value();
		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) > 0.9)
		{
			// Emits value changed signal.
			ui->horizontalSlider_KarplusSynth_OnDecay->setValue(on_decay);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_3)
	{
		// Gray Blue slider - off decay control
		// Get new value from slider and calculate gap from current UI value
		off_decay = normalize_slider_value(val / 36, kps_control_max_value, kps_control_min_value); // 0-3600 -> 5-95
		slider_level_gap = off_decay - ui->horizontalSlider_KarplusSynth_OffDecay->value();
		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) > 0.9)
		{
			// Emits value changed signal.
			ui->horizontalSlider_KarplusSynth_OffDecay->setValue(off_decay);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_4)
	{
		// Gray Green slider - string damping control
		// Get new value from slider and calculate gap from current UI value
		string_damping = normalize_slider_value(val / 36, kps_control_max_value, kps_control_min_value); // 0-3600 -> 5-95
		slider_level_gap = string_damping - ui->horizontalSlider_KarplusSynth_StringDamping->value();
		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) > 0.9)
		{
			// Emits value changed signal.
			ui->horizontalSlider_KarplusSynth_StringDamping->setValue(string_damping);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_5)
	{
		// Gray White slider - string damping variations control
		// Get new value from slider and calculate gap from current UI value
		string_damping_variations = normalize_slider_value(val / 36, kps_control_max_value, kps_control_min_value); // 0-3600 -> 5-95
		slider_level_gap = string_damping_variations - ui->horizontalSlider_KarplusSynth_StringDampingVariations->value();
		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) > 0.9)
		{
			// Emits value changed signal.
			ui->horizontalSlider_KarplusSynth_StringDampingVariations->setValue(string_damping_variations);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_6)
	{
		// Gray Yellow slider - pluck damping control
		// Get new value from slider and calculate gap from current UI value
		pluck_damping = normalize_slider_value(val / 36, kps_control_max_value, kps_control_min_value); // 0-3600 -> 5-95
		slider_level_gap = pluck_damping - ui->horizontalSlider_KarplusSynth_PluckDamping->value();
		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) > 0.9)
		{
			// Emits value changed signal.
			ui->horizontalSlider_KarplusSynth_PluckDamping->setValue(pluck_damping);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_7)
	{
		// Gray Red slider - pluck damping variations control
		// Get new value from slider and calculate gap from current UI value
		pluck_damping_variations = normalize_slider_value(val / 36, kps_control_max_value, kps_control_min_value); // 0-3600 -> 5-95
		slider_level_gap = pluck_damping_variations - ui->horizontalSlider_KarplusSynth_PluckDampingVariations->value();
		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) > 0.9)
		{
			// Emits value changed signal.
			ui->horizontalSlider_KarplusSynth_PluckDampingVariations->setValue(pluck_damping_variations);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_8)
	{
		// Gray Black slider - character variations control
		// Get new value from slider and calculate gap from current UI value
		character_variations = normalize_slider_value(val / 36, kps_control_max_value, kps_control_min_value); // 0-3600 -> 5-95
		slider_level_gap = character_variations - ui->horizontalSlider_KarplusSynth_CharacterVariations->value();
		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) > 0.9)
		{
			// Emits value changed signal.
			ui->horizontalSlider_KarplusSynth_CharacterVariations->setValue(character_variations);
		}
	}
}

void Dialog_StringSynthesizer::on_dialog_close()
{
	close();
}

void Dialog_StringSynthesizer::on_karplus_excitation_waveform_combobox_changed(int val)
{
	ui->comboBox_KarplusSynth_ExcitationWaveform->blockSignals(true);
	ui->comboBox_KarplusSynth_ExcitationWaveform->setCurrentIndex(val);
	ui->comboBox_KarplusSynth_ExcitationWaveform->blockSignals(false);

	kps_excitation_waveform = val;
	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_EXCITATION_WAVEFORM, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_karplus_excitation_waveform_variations_slider_changed(int val)
{
	ui->horizontalSlider_KarplusSynth_WaveformVariations->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_WaveformVariations->setValue(val);
	ui->horizontalSlider_KarplusSynth_WaveformVariations->blockSignals(false);

	ui->spinBox_KarplusSynth_WaveformVariations->blockSignals(true);
	ui->spinBox_KarplusSynth_WaveformVariations->setValue(val);
	ui->spinBox_KarplusSynth_WaveformVariations->blockSignals(false);

	kps_waveform_variations = val;

	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_EXCITATION_WAVEFORM_VARIATIONS, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_karplus_string_damping_slider_changed(int val)
{
	ui->horizontalSlider_KarplusSynth_StringDamping->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_StringDamping->setValue(val);
	ui->horizontalSlider_KarplusSynth_StringDamping->blockSignals(false);

	ui->spinBox_KarplusSynth_StringDamping->blockSignals(true);
	ui->spinBox_KarplusSynth_StringDamping->setValue(val);
	ui->spinBox_KarplusSynth_StringDamping->blockSignals(false);

	kps_string_damping = val;

	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_STRING_DAMPING, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_karplus_string_damping_variation_slider_changed(int val)
{
	ui->horizontalSlider_KarplusSynth_StringDampingVariations->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_StringDampingVariations->setValue(val);
	ui->horizontalSlider_KarplusSynth_StringDampingVariations->blockSignals(false);

	ui->spinBox_KarplusSynth_StringDampingVariations->blockSignals(true);
	ui->spinBox_KarplusSynth_StringDampingVariations->setValue(val);
	ui->spinBox_KarplusSynth_StringDampingVariations->blockSignals(false);

	kps_string_damping_variations = val;

	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_STRING_DAMPING_VARIATION, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_karplus_pluck_damping_slider_changed(int val)
{
	ui->horizontalSlider_KarplusSynth_PluckDamping->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_PluckDamping->setValue(val);
	ui->horizontalSlider_KarplusSynth_PluckDamping->blockSignals(false);

	ui->spinBox_KarplusSynth_PluckDamping->blockSignals(true);
	ui->spinBox_KarplusSynth_PluckDamping->setValue(val);
	ui->spinBox_KarplusSynth_PluckDamping->blockSignals(false);

	kps_pluck_damping = val;

	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_PLUCK_DAMPING, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_karplus_pluck_damping_variation_slider_changed(int val)
{
	ui->horizontalSlider_KarplusSynth_PluckDampingVariations->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_PluckDampingVariations->setValue(val);
	ui->horizontalSlider_KarplusSynth_PluckDampingVariations->blockSignals(false);

	ui->spinBox_KarplusSynth_PluckDampingVariations->blockSignals(true);
	ui->spinBox_KarplusSynth_PluckDampingVariations->setValue(val);
	ui->spinBox_KarplusSynth_PluckDampingVariations->blockSignals(false);

	kps_pluck_damping_variations = val;

	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_PLUCK_DAMPING_VARIATION, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_karplus_on_decay_slider_changed(int val)
{
	ui->horizontalSlider_KarplusSynth_OnDecay->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_OnDecay->setValue(val);
	ui->horizontalSlider_KarplusSynth_OnDecay->blockSignals(false);

	ui->spinBox_KarplusSynth_OnDecay->blockSignals(true);
	ui->spinBox_KarplusSynth_OnDecay->setValue(val);
	ui->spinBox_KarplusSynth_OnDecay->blockSignals(false);

	kps_on_decay = val;

	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_ON_DECAY, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_karplus_off_decay_slider_changed(int val)
{
	ui->horizontalSlider_KarplusSynth_OffDecay->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_OffDecay->setValue(val);
	ui->horizontalSlider_KarplusSynth_OffDecay->blockSignals(false);

	ui->spinBox_KarplusSynth_OffDecay->blockSignals(true);
	ui->spinBox_KarplusSynth_OffDecay->setValue(val);
	ui->spinBox_KarplusSynth_OffDecay->blockSignals(false);

	kps_off_decay = val;

	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_OFF_DECAY, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_karplus_character_variations_slider_changed(int val)
{
	ui->horizontalSlider_KarplusSynth_CharacterVariations->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_CharacterVariations->setValue(val);
	ui->horizontalSlider_KarplusSynth_CharacterVariations->blockSignals(false);

	ui->spinBox_KarplusSynth_CharacterVariations->blockSignals(true);
	ui->spinBox_KarplusSynth_CharacterVariations->setValue(val);
	ui->spinBox_KarplusSynth_CharacterVariations->blockSignals(false);

	kps_character_variations = val;

	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_CHARACTER_VARIATIONS, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_karplus_string_damping_calc_mode_combobox_hanged(int val)
{
	ui->comboBox_KarplusSynth_CalculationMode->blockSignals(true);
	ui->comboBox_KarplusSynth_CalculationMode->setCurrentIndex(val);
	ui->comboBox_KarplusSynth_CalculationMode->blockSignals(false);

	kps_string_dump_calculation_mode = val;
	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_STRING_DUMP_CALC_MODE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_karplus_send_filter1_dial_changed(int val)
{
	ui->dial_KarplusSynth_SendFilter1->blockSignals(true);
	ui->dial_KarplusSynth_SendFilter1->setValue(val);
	ui->dial_KarplusSynth_SendFilter1->blockSignals(false);

	ui->spinBox_KarplusSynth_SendFilter1->blockSignals(true);
	ui->spinBox_KarplusSynth_SendFilter1->setValue(val);
	ui->spinBox_KarplusSynth_SendFilter1->blockSignals(false);

	kps_send_filter_1_level = val;
	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_SEND_1, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_karplus_send_filter2_dial_changed(int val)
{
	ui->dial_KarplusSynth_SendFilter2->blockSignals(true);
	ui->dial_KarplusSynth_SendFilter2->setValue(val);
	ui->dial_KarplusSynth_SendFilter2->blockSignals(false);

	ui->spinBox_KarplusSynth_SendFilter2->blockSignals(true);
	ui->spinBox_KarplusSynth_SendFilter2->setValue(val);
	ui->spinBox_KarplusSynth_SendFilter2->blockSignals(false);

	kps_send_filter_2_level = val;
	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_SEND_2, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_karplus_tune_octave_combobox_changed(int val)
{
	ui->comboBox_KPStuneOctave->blockSignals(true);
	ui->comboBox_KPStuneOctave->setCurrentIndex(val);
	ui->comboBox_KPStuneOctave->blockSignals(false);

	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KPS_DETUNE_OCTAVE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_karplus_tune_semitones_combobox_changed(int val)
{
	ui->comboBox_KPStuneSemitones->blockSignals(true);
	ui->comboBox_KPStuneSemitones->setCurrentIndex(val);
	ui->comboBox_KPStuneSemitones->blockSignals(false);

	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KPS_DETUNE_SEMITONES, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_karplus_distortion_enabled_checkbox_changed(bool en)
{
	ui->checkBox_KPSdistortionActive->blockSignals(true);
	ui->checkBox_KPSdistortionActive->setCheckState(en ? Qt::Checked : Qt::Unchecked);
	ui->checkBox_KPSdistortionActive->blockSignals(false);

	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KPS_DISTORTION_ACTIVE, en ? 1 : 0);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_karplus_distortion_autogain_enabled_checkbox_changed(bool en)
{
	ui->checkBox_KPSdistortionAutoGain->blockSignals(true);
	ui->checkBox_KPSdistortionAutoGain->setCheckState(en ? Qt::Checked : Qt::Unchecked);
	ui->checkBox_KPSdistortionAutoGain->blockSignals(false);

	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KPS_DISTORTION_AUTO_GAIN_ENABLE, en ? 1 : 0);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_karplus_distortion_drive_dial_changed(int val)
{
	char text[64];
	
	ui->dial_KPSdistortionDrive->blockSignals(true);
	ui->dial_KPSdistortionDrive->setValue(val);
	ui->dial_KPSdistortionDrive->blockSignals(false);

	sprintf(text, "%.2f", (float)val / 100.0f);
	ui->lineEdit_KPSdistortionDrive->setText(QString(text));

	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KPS_DISTORTION_DRIVE, val);
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_karplus_distortion_range_dial_changed(int val)
{
	char text[64];
	
	ui->dial_KPSdistortionRange->blockSignals(true);
	ui->dial_KPSdistortionRange->setValue(val);
	ui->dial_KPSdistortionRange->blockSignals(false);

	sprintf(text, "%.0f", (float)val );
	ui->lineEdit_KPSdistortionRange->setText(QString(text));
	
	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KPS_DISTORTION_RANGE, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_karplus_distortion_blend_dial_changed(int val)
{
	char text[64];
	
	ui->dial_KPSdistortionBlend->blockSignals(true);
	ui->dial_KPSdistortionBlend->setValue(val);
	ui->dial_KPSdistortionBlend->blockSignals(false);

	sprintf(text, "%.2f", (float)val / 100.0f);
	ui->lineEdit_KPSdistortionBlend->setText(QString(text));
	
	mod_synth_set_string_synth_param_value(_STRING_SYNTH_EVENT, _KPS_DISTORTION_BLEND, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_StringSynthesizer::on_presets_open_pushbutton_clicked()
{
	QString startDir = last_string_synth_preset_directory.isEmpty() ? QString(_STRING_SYNTH_PRESETS_FILES_DEFAULT_DIR) : last_string_synth_preset_directory;

	CustomFileDialog dialog(this,
							tr("Open Preset File"),
							startDir,
							tr("Presets (*.xml *.XML);;All Files (*)"),
							Qt::black); // Background color set here)

	// If we have a last file, select it and scroll to it
	if (!last_string_synth_preset_load_file.isEmpty())
	{
		dialog.selectFile(last_string_synth_preset_load_file);
	}

	if (dialog.exec() == QDialog::Accepted)
	{
		string_synth_preset_file_name = dialog.selectedFile();

		if (!string_synth_preset_file_name.isEmpty())
		{
			// Remember the directory and file for next time
			last_string_synth_preset_directory = QFileInfo(string_synth_preset_file_name).absolutePath();
			last_string_synth_preset_load_file = string_synth_preset_file_name;

			std::string file_name;
			// file_name = std::string("Now Loading: ");
			file_name = std::filesystem::path(string_synth_preset_file_name.toStdString()).stem();

			ui->textEdit_KPSpresetText->setText(QString::fromStdString(file_name));

			load_string_synthesizer_preset_file_thread = new LoadStringSynthesizerPresetFileThread();
			connect(load_string_synthesizer_preset_file_thread,
					&LoadStringSynthesizerPresetFileThread::finished, load_string_synthesizer_preset_file_thread, &QObject::deleteLater);
			connect(load_string_synthesizer_preset_file_thread, &LoadStringSynthesizerPresetFileThread::loadPresetFileDone,
					this, &Dialog_StringSynthesizer::on_preset_file_loaded);
			load_string_synthesizer_preset_file_thread->start();
		}
	}
}

void Dialog_StringSynthesizer::on_presets_save_pushbutton_clicked()
{
	QString startDir = last_string_synth_preset_directory.isEmpty() ? QString(_STRING_SYNTH_PRESETS_FILES_DEFAULT_DIR) : last_string_synth_preset_directory;

	// Use CustomFileDialog in Save mode
	CustomFileDialog dialog(this,
							tr("Save Preset File"),
							startDir,
							tr("Presets (*.xml *.XML);;All Files (*)"),
							Qt::black,
							CustomFileDialog::SaveMode); // Set to Save mode

	if (dialog.exec() == QDialog::Accepted)
	{
		string_synth_preset_file_name = dialog.selectedFile();

		if (!string_synth_preset_file_name.isEmpty())
		{
			// Ensure .xml extension
			if (!string_synth_preset_file_name.endsWith(".xml", Qt::CaseInsensitive))
			{
				string_synth_preset_file_name += ".xml";
			}

			// Check if file exists and ask for confirmation
			if (QFile::exists(string_synth_preset_file_name))
			{
				QMessageBox msgBox;
				msgBox.setIcon(QMessageBox::Warning);
				msgBox.setWindowTitle("Confirm Overwrite");
				msgBox.setText(QString("File '%1' already exists.")
								   .arg(QFileInfo(string_synth_preset_file_name).fileName()));
				msgBox.setInformativeText("Do you want to overwrite it?");
				msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
				msgBox.setDefaultButton(QMessageBox::Cancel);

				if (msgBox.exec() != QMessageBox::Yes)
				{
					return;
				}
			}

			// Remember the directory and file for next time
			last_string_synth_preset_directory = QFileInfo(string_synth_preset_file_name).absolutePath();
			last_string_synth_preset_save_file = string_synth_preset_file_name;

			// Display saving message
			std::string file_name = std::string("Now Saving: ");
			file_name += std::filesystem::path(string_synth_preset_file_name.toStdString()).stem().string();
			// ui->textEdit_HammondPresetText->setText(QString::fromStdString(file_name));

			// Start the save thread
			save_string_synthesizer_preset_file_thread = new SaveStringSynthesizerPresetFileThread();

			connect(save_string_synthesizer_preset_file_thread,
					&SaveStringSynthesizerPresetFileThread::finished,
					save_string_synthesizer_preset_file_thread,
					&QObject::deleteLater);
			connect(save_string_synthesizer_preset_file_thread,
					&SaveStringSynthesizerPresetFileThread::savePresetFileDone,
					this,
					&Dialog_StringSynthesizer::on_preset_file_saved);

			save_string_synthesizer_preset_file_thread->start();
		}
	}
}

void Dialog_StringSynthesizer::on_preset_file_loaded(const QString &s)
{
}

void Dialog_StringSynthesizer::on_preset_file_saved(const QString &s)
{
}

void Dialog_StringSynthesizer::update_gui()
{
	int val;

	static int prev_kps_excitation_waveform = -1;
	static int prev_kps_waveform_variations = -1;
	static int prev_kps_string_damping = -1;
	static int prev_kps_string_damping_variations = -1;
	static int prev_kps_pluck_damping = -1;
	static int prev_kps_pluck_damping_variations = -1;
	static int prev_kps_on_decay = -1;
	static int prev_kps_off_decay = -1;
	static int prev_kps_character_variations = -1;
	static int prev_kps_send_filter_1_level = -1;
	static int prev_kps_send_filter_2_level = -1;
	static int prev_kps_string_dump_calculation_mode = -1;
	static int prev_kps_tune_octave = -1;
	static int prev_kps_tune_semitones = -1;

	static bool prev_kps_distortion_active = false;
	static bool prev_kps_distortion_auto_gain_enable = false;

	static int prev_kps_distortion_drive = -1;
	static int prev_kps_distortion_range = -1;
	static int prev_kps_distortion_blend = -1;

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_EXCITATION_WAVEFORM);
	if (val != prev_kps_excitation_waveform)
	{
		prev_kps_excitation_waveform = val;
		ui->comboBox_KarplusSynth_ExcitationWaveform->blockSignals(true);
		ui->comboBox_KarplusSynth_ExcitationWaveform->setCurrentIndex(val);
		ui->comboBox_KarplusSynth_ExcitationWaveform->blockSignals(false);
	}

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_EXCITATION_WAVEFORM_VARIATIONS);
	if (val != prev_kps_waveform_variations)
	{
		prev_kps_waveform_variations = val;
		ui->horizontalSlider_KarplusSynth_WaveformVariations->blockSignals(true);
		ui->horizontalSlider_KarplusSynth_WaveformVariations->setValue(val);
		ui->horizontalSlider_KarplusSynth_WaveformVariations->blockSignals(false);
		ui->spinBox_KarplusSynth_WaveformVariations->blockSignals(true);
		ui->spinBox_KarplusSynth_WaveformVariations->setValue(val);
		ui->spinBox_KarplusSynth_WaveformVariations->blockSignals(false);
	}

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_STRING_DAMPING);
	if (val != prev_kps_string_damping)
	{
		prev_kps_string_damping = val;
		ui->horizontalSlider_KarplusSynth_StringDamping->blockSignals(true);
		ui->horizontalSlider_KarplusSynth_StringDamping->setValue(val);
		ui->horizontalSlider_KarplusSynth_StringDamping->blockSignals(false);
		ui->spinBox_KarplusSynth_StringDamping->blockSignals(true);
		ui->spinBox_KarplusSynth_StringDamping->setValue(val);
		ui->spinBox_KarplusSynth_StringDamping->blockSignals(false);
	}

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_STRING_DAMPING_VARIATION);
	if (val != prev_kps_string_damping_variations)
	{
		prev_kps_string_damping_variations = val;
		ui->horizontalSlider_KarplusSynth_StringDampingVariations->blockSignals(true);
		ui->horizontalSlider_KarplusSynth_StringDampingVariations->setValue(val);
		ui->horizontalSlider_KarplusSynth_StringDampingVariations->blockSignals(false);
		ui->spinBox_KarplusSynth_StringDampingVariations->blockSignals(true);
		ui->spinBox_KarplusSynth_StringDampingVariations->setValue(val);
		ui->spinBox_KarplusSynth_StringDampingVariations->blockSignals(false);
	}

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_PLUCK_DAMPING);
	if (val != prev_kps_pluck_damping)
	{
		prev_kps_pluck_damping = val;
		ui->horizontalSlider_KarplusSynth_PluckDamping->blockSignals(true);
		ui->horizontalSlider_KarplusSynth_PluckDamping->setValue(val);
		ui->horizontalSlider_KarplusSynth_PluckDamping->blockSignals(false);
		ui->spinBox_KarplusSynth_PluckDamping->blockSignals(true);
		ui->spinBox_KarplusSynth_PluckDamping->setValue(val);
		ui->spinBox_KarplusSynth_PluckDamping->blockSignals(false);
	}

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_PLUCK_DAMPING_VARIATION);
	if (val != prev_kps_pluck_damping_variations)
	{
		prev_kps_pluck_damping_variations = val;
		ui->horizontalSlider_KarplusSynth_PluckDampingVariations->blockSignals(true);
		ui->horizontalSlider_KarplusSynth_PluckDampingVariations->setValue(val);
		ui->horizontalSlider_KarplusSynth_PluckDampingVariations->blockSignals(false);
		ui->spinBox_KarplusSynth_PluckDampingVariations->blockSignals(true);
		ui->spinBox_KarplusSynth_PluckDampingVariations->setValue(val);
		ui->spinBox_KarplusSynth_PluckDampingVariations->blockSignals(false);
	}

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_ON_DECAY);
	if (val != prev_kps_on_decay)
	{
		prev_kps_on_decay = val;
		ui->horizontalSlider_KarplusSynth_OnDecay->blockSignals(true);
		ui->horizontalSlider_KarplusSynth_OnDecay->setValue(val);
		ui->horizontalSlider_KarplusSynth_OnDecay->blockSignals(false);
		ui->spinBox_KarplusSynth_OnDecay->blockSignals(true);
		ui->spinBox_KarplusSynth_OnDecay->setValue(val);
		ui->spinBox_KarplusSynth_OnDecay->blockSignals(false);
	}

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_OFF_DECAY);
	if (val != prev_kps_off_decay)
	{
		prev_kps_off_decay = val;
		ui->horizontalSlider_KarplusSynth_OffDecay->blockSignals(true);
		ui->horizontalSlider_KarplusSynth_OffDecay->setValue(val);
		ui->horizontalSlider_KarplusSynth_OffDecay->blockSignals(false);
		ui->spinBox_KarplusSynth_OffDecay->blockSignals(true);
		ui->spinBox_KarplusSynth_OffDecay->setValue(val);
		ui->spinBox_KarplusSynth_OffDecay->blockSignals(false);
	}

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_CHARACTER_VARIATIONS);
	if (val != prev_kps_character_variations)
	{
		prev_kps_character_variations = val;
		ui->horizontalSlider_KarplusSynth_CharacterVariations->blockSignals(true);
		ui->horizontalSlider_KarplusSynth_CharacterVariations->setValue(val);
		ui->horizontalSlider_KarplusSynth_CharacterVariations->blockSignals(false);
		ui->spinBox_KarplusSynth_CharacterVariations->blockSignals(true);
		ui->spinBox_KarplusSynth_CharacterVariations->setValue(val);
		ui->spinBox_KarplusSynth_CharacterVariations->blockSignals(false);
	}

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_SEND_1);
	if (val != prev_kps_send_filter_1_level)
	{
		prev_kps_send_filter_1_level = val;
		ui->dial_KarplusSynth_SendFilter1->blockSignals(true);
		ui->dial_KarplusSynth_SendFilter1->setValue(val);
		ui->dial_KarplusSynth_SendFilter1->blockSignals(false);
		ui->spinBox_KarplusSynth_SendFilter1->blockSignals(true);
		ui->spinBox_KarplusSynth_SendFilter1->setValue(val);
		ui->spinBox_KarplusSynth_SendFilter1->blockSignals(false);
	}

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_SEND_2);
	if (val != prev_kps_send_filter_2_level)
	{
		prev_kps_send_filter_2_level = val;
		ui->dial_KarplusSynth_SendFilter2->blockSignals(true);
		ui->dial_KarplusSynth_SendFilter2->setValue(val);
		ui->dial_KarplusSynth_SendFilter2->blockSignals(false);
		ui->spinBox_KarplusSynth_SendFilter2->blockSignals(true);
		ui->spinBox_KarplusSynth_SendFilter2->setValue(val);
		ui->spinBox_KarplusSynth_SendFilter2->blockSignals(false);
	}

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KARPLUS_STRONG_STRING_DUMP_CALC_MODE);
	if (val != prev_kps_string_dump_calculation_mode)
	{
		prev_kps_string_dump_calculation_mode = val;
		ui->comboBox_KarplusSynth_CalculationMode->blockSignals(true);
		ui->comboBox_KarplusSynth_CalculationMode->setCurrentIndex(val);
		ui->comboBox_KarplusSynth_CalculationMode->blockSignals(false);
	}

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KPS_DETUNE_OCTAVE);
	if (val != prev_kps_tune_octave)
	{
		prev_kps_tune_octave = val;
		ui->comboBox_KPStuneOctave->blockSignals(true);
		ui->comboBox_KPStuneOctave->setCurrentIndex(val - _OSC_DETUNE_MIN_OCTAVE);
		ui->comboBox_KPStuneOctave->blockSignals(false);
	}

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KPS_DETUNE_SEMITONES);
	if (val != prev_kps_tune_semitones)
	{
		prev_kps_tune_semitones = val;
		ui->comboBox_KPStuneSemitones->blockSignals(true);
		ui->comboBox_KPStuneSemitones->setCurrentIndex(val - _OSC_DETUNE_MIN_SEMITONES);
		ui->comboBox_KPStuneSemitones->blockSignals(false);
	}

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KPS_DISTORTION_ACTIVE);
	if ((val > 0) != prev_kps_distortion_active)
	{
		prev_kps_distortion_active = (val > 0);
		ui->checkBox_KPSdistortionActive->blockSignals(true);
		ui->checkBox_KPSdistortionActive->setCheckState(prev_kps_distortion_active ? Qt::Checked : Qt::Unchecked);
		ui->checkBox_KPSdistortionActive->blockSignals(false);
	}

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KPS_DISTORTION_AUTO_GAIN_ENABLE);
	if ((val > 0) != prev_kps_distortion_auto_gain_enable)
	{
		prev_kps_distortion_auto_gain_enable = (val > 0);
		ui->checkBox_KPSdistortionAutoGain->blockSignals(true);
		ui->checkBox_KPSdistortionAutoGain->setCheckState(prev_kps_distortion_auto_gain_enable ? Qt::Checked : Qt::Unchecked);
		ui->checkBox_KPSdistortionAutoGain->blockSignals(false);
	}

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KPS_DISTORTION_DRIVE);
	if (val != prev_kps_distortion_drive)
	{
		prev_kps_distortion_drive = val;
		ui->dial_KPSdistortionDrive->blockSignals(true);
		ui->dial_KPSdistortionDrive->setValue(val);
		ui->dial_KPSdistortionDrive->blockSignals(false);
		char text[64];
		sprintf(text, "%.2f", (float)mod_synth_get_active_distortion_1_drive() / 100.0f);
		ui->lineEdit_KPSdistortionDrive->setText(QString(text));
	}

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KPS_DISTORTION_RANGE);
	if (val != prev_kps_distortion_range)
	{
		prev_kps_distortion_range = val;
		ui->dial_KPSdistortionRange->blockSignals(true);
		ui->dial_KPSdistortionRange->setValue(val);
		ui->dial_KPSdistortionRange->blockSignals(false);
		char text[64];
		sprintf(text, "%.0f", (float)mod_synth_get_active_distortion_1_range());
		ui->lineEdit_KPSdistortionRange->setText(QString(text));
	}

	val = mod_synth_get_string_synth_param_value(_STRING_SYNTH_EVENT, _KPS_DISTORTION_BLEND);
	if (val != prev_kps_distortion_blend)
	{
		prev_kps_distortion_blend = val;
		ui->dial_KPSdistortionBlend->blockSignals(true);
		ui->dial_KPSdistortionBlend->setValue(val);
		ui->dial_KPSdistortionBlend->blockSignals(false);
		char text[64];
		sprintf(text, "%.2f", (float)mod_synth_get_active_distortion_1_blend() / 100.0f);
		ui->lineEdit_KPSdistortionBlend->setText(QString(text));
	}
}

void Dialog_StringSynthesizer::start_update_timer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update_gui()));
	timer->start(interval);
}
