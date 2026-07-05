/**
 * @file		Dialog_HammondOrgan.cpp
 *	@author		Nahum Budin
 *	@date		19-Apr-2026
 *	@version	1.0
 *
 *	@brief		Adj Hammond Organ control dialog
 *
 */

#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>
#include <QDialogButtonBox>
#include <QTextStream>
# include <QFileInfo>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>

#include <filesystem>

#include "Dialog_HammondOrgan.h"
#include "ui_Dialog_HammondOrgan.h"
#include "CustomFileDialog.h"

#include "MainWindow.h"
#include "utils.h"
#include "Defs.h"

#define _UPDATE_TIMER_PERIOD_MS 250

Dialog_HammondOrgan *Dialog_HammondOrgan::dialog_hammond_organ_instance = NULL;

LoadHammondOrganPresetFileThread *load_hammond_organ_preset_file_thread = nullptr;
;
SaveHammondOrganPresetFileThread *save_hammond_organ_preset_file_thread = nullptr;;

QString hammond_organpreset_file_name;

void hammond_organ_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	Dialog_HammondOrgan *instance = Dialog_HammondOrgan::get_instance();
	if (instance != nullptr)
	{
		instance->control_box_event_received(evnt, val);
	}
}

void SaveHammondOrganPresetFileThread::run()
{
	int res;

	QString result = QString("Preset File Saved");
	res = mod_synth_save_hammond_preset_file(hammond_organpreset_file_name.toStdString());
	
	emit savePresetFileDone(result);
}

void LoadHammondOrganPresetFileThread::run()
{
	int res;

	QString result = QString("Preset File Loaded");
	res = mod_synth_load_hammond_preset_file(hammond_organpreset_file_name.toStdString());

	emit loadPresetFileDone(result);
}


Dialog_HammondOrgan::Dialog_HammondOrgan(QWidget *parent)
	: QDialog(parent), ui(new Ui::Dialog_HammondOrgan)
{
	ui->setupUi(this);
	dialog_hammond_organ_instance = this;

	// Prevent dialog from being deleted when closed - only hide it
	setAttribute(Qt::WA_DeleteOnClose, false);

	close_event_callback_ptr = NULL;

	// Connect signal to slot with Qt::QueuedConnection for thread-safety
	// This ensures the slot runs in the GUI thread
	connect(this, &Dialog_HammondOrgan::control_box_event_signal,
			this, &Dialog_HammondOrgan::handle_control_box_event,
			Qt::QueuedConnection);

	// Register control box event callback
	mod_synth_register_callback_control_box_event_update_ui(
		&hammond_organ_control_box_event_update_ui_callback_wrapper);

	init_gui_elements();
	
	
	// Register with GuiNavigator (no tabs, no frames for Hammond Organ)
	GuiNavigator::get_instance()->register_dialog(this, "Hammond Organ");
	
	// Also register with MainWindow for compatibility
	MainWindow::get_instance()->register_active_dialog(this);
	
	// GUI Update timer start
	start_update_timer(_UPDATE_TIMER_PERIOD_MS);

	/* Set focus on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

Dialog_HammondOrgan::~Dialog_HammondOrgan()
{
	// Disable callback during destruction
	mod_synth_register_callback_control_box_event_update_ui(NULL);
	
	// Reset static instance pointer when destroyed
	dialog_hammond_organ_instance = nullptr;
	delete ui;
}

Dialog_HammondOrgan *Dialog_HammondOrgan::get_instance(QWidget *parent)
{
	if (dialog_hammond_organ_instance == NULL)
	{
		dialog_hammond_organ_instance = new Dialog_HammondOrgan(parent);
	}
	return dialog_hammond_organ_instance;
}

// Thread-safe function called from callback - just emits signal
void Dialog_HammondOrgan::control_box_event_received(int evnt, uint16_t val)
{
	// Emit signal - Qt will queue it to run in GUI thread
	emit control_box_event_signal(evnt, val);
}

void Dialog_HammondOrgan::init_gui_elements()
{
	// Initialize GUI elements

	ui->comboBox_HammondTuneOctave->blockSignals(true);
	ui->comboBox_HammondTuneSemitones->blockSignals(true);
	ui->comboBox_HammondTuneCents->blockSignals(true);

	ui->comboBox_HammondTuneOctave->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_HammondTuneOctave->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_HammondTuneOctave->setFrameColor(_CONTROLS_COLOR_WHITE);
	ui->comboBox_HammondTuneOctave->setFrameWidth(2);
	ui->comboBox_HammondTuneOctave->setCurrentIndex(mod_synth_get_active_osc1_detune_octave() - mod_synth_get_osc_detune_min_octave());

	ui->comboBox_HammondTuneSemitones->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_HammondTuneSemitones->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_HammondTuneSemitones->setFrameColor(_CONTROLS_COLOR_YELLOW);
	ui->comboBox_HammondTuneSemitones->setFrameWidth(2);
	ui->comboBox_HammondTuneSemitones->setCurrentIndex(mod_synth_get_active_osc1_detune_semitones() - mod_synth_get_osc_detune_min_semitones());

	ui->comboBox_HammondTuneCents->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_HammondTuneCents->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_HammondTuneCents->setFrameColor(_CONTROLS_COLOR_RED);
	ui->comboBox_HammondTuneCents->setFrameWidth(2);
	ui->comboBox_HammondTuneCents->setCurrentIndex(mod_synth_get_active_osc1_detune_cents() - mod_synth_get_osc_detune_min_cents() * 4.f);

	for (int i = _OSC_DETUNE_MIN_OCTAVE; i <= _OSC_DETUNE_MAX_OCTAVE; i++)
	{
		ui->comboBox_HammondTuneOctave->addItem(QString::number(i));
	}

	for (int i = _OSC_DETUNE_MIN_SEMITONES; i <= _OSC_DETUNE_MAX_SEMITONES; i++)
	{
		ui->comboBox_HammondTuneSemitones->addItem(QString::number(i));
	}

	for (int i = 4 * _OSC_DETUNE_MIN_CENTS; i <= 4 * _OSC_DETUNE_MAX_CENTS; i++)
	{
		// 0.25 steps
		ui->comboBox_HammondTuneCents->addItem(QString::number(i / 4.f));
	}

	ui->comboBox_HammondTuneOctave->setCurrentIndex(6); // 0 octave offset (centered), with range of -6 to +6 octaves (13 steps total)
	ui->comboBox_HammondTuneSemitones->setCurrentIndex(11); // 0 semitone offset (centered), with range of -11 to +11 semitones (23 steps total)
	ui->comboBox_HammondTuneCents->setCurrentIndex(30);		// 0 cent offset (centered), with range of -7.5 to +7.5 cents (61 steps total)

	ui->comboBox_HammondTuneOctave->blockSignals(false);
	ui->comboBox_HammondTuneSemitones->blockSignals(false);
	ui->comboBox_HammondTuneCents->blockSignals(false);
	
	ui->comboBox_HammondTuneOctave->setFrameWidth(2);

	string_unison_labels_hammond.append("16");
	string_unison_labels_hammond.append("5 1/3");
	string_unison_labels_hammond.append("8");
	string_unison_labels_hammond.append("4");
	string_unison_labels_hammond.append("2 2/3");
	string_unison_labels_hammond.append("2");
	string_unison_labels_hammond.append("1 3/5");
	string_unison_labels_hammond.append("1 1/3");
	string_unison_labels_hammond.append("1");

	bar_level_sliders[0] = ui->verticalSlider_HammondLevel_1;
	bar_level_sliders[1] = ui->verticalSlider_HammondLevel_2;
	bar_level_sliders[2] = ui->verticalSlider_HammondLevel_3;
	bar_level_sliders[3] = ui->verticalSlider_HammondLevel_4;
	bar_level_sliders[4] = ui->verticalSlider_HammondLevel_5;
	bar_level_sliders[5] = ui->verticalSlider_HammondLevel_6;
	bar_level_sliders[6] = ui->verticalSlider_HammondLevel_7;
	bar_level_sliders[7] = ui->verticalSlider_HammondLevel_8;
	bar_level_sliders[8] = ui->verticalSlider_HammondLevel_9;

	bar_level_labels[0] = ui->label_HammondLevel_1;
	bar_level_labels[1] = ui->label_HammondLevel_2;
	bar_level_labels[2] = ui->label_HammondLevel_3;
	bar_level_labels[3] = ui->label_HammondLevel_4;
	bar_level_labels[4] = ui->label_HammondLevel_5;
	bar_level_labels[5] = ui->label_HammondLevel_6;
	bar_level_labels[6] = ui->label_HammondLevel_7;
	bar_level_labels[7] = ui->label_HammondLevel_8;
	bar_level_labels[8] = ui->label_HammondLevel_9;

	string_hammond_modes_list.append("Percusion OFF");
	string_hammond_modes_list.append("Percusion 2nd Soft Slow");
	string_hammond_modes_list.append("Percusion 2nd Soft Fast");
	string_hammond_modes_list.append("Percusion 2nd Norm Slow");
	string_hammond_modes_list.append("Percusion 2nd Norm Fast");
	string_hammond_modes_list.append("Percusion 3rd Soft Slow");
	string_hammond_modes_list.append("Percusion 3rd Soft Fast");
	string_hammond_modes_list.append("Percusion 3rd Norm Slow");
	string_hammond_modes_list.append("Percusion 3rd Norm Fast");

	for (int i = 0; i < 9; i++)
	{
		bar_level_sliders[i]->blockSignals(true);
		bar_level_sliders[i]->setSingleStep(1);
		bar_level_sliders[i]->setMaximum(8);
		bar_level_sliders[i]->setMinimum(0);
		bar_level_sliders[i]->setValue(0);
		//bar_level_sliders[i]->setInvertedAppearance(false);
		bar_level_sliders[i]->blockSignals(false);

		bar_level_labels[i]->setText(string_unison_labels_hammond.at(i));
	}

	bar_level_sliders[0]->setValue(8);

	bar_level_sliders[0]->setGripLineColor(_CONTROLS_COLOR_GRAY);
	bar_level_sliders[1]->setGripLineColor(_CONTROLS_COLOR_PURPLE);
	
	bar_level_sliders[2]->setTipColor(QColor(220, 220, 220));
	bar_level_sliders[2]->setGripLineColor(_CONTROLS_COLOR_BLUE);
	
	bar_level_sliders[3]->setTipColor(QColor(220, 220, 220));
	bar_level_sliders[3]->setGripLineColor(_CONTROLS_COLOR_GREEN);
	
	bar_level_sliders[4]->setTipColor(QColor(30, 30, 30));
	bar_level_sliders[4]->setGripLineColor(_CONTROLS_COLOR_WHITE);
	
	bar_level_sliders[5]->setTipColor(QColor(220, 220, 220));
	bar_level_sliders[5]->setGripLineColor(_CONTROLS_COLOR_YELLOW);
	
	bar_level_sliders[6]->setTipColor(QColor(30, 30, 30));
	bar_level_sliders[6]->setGripLineColor(_CONTROLS_COLOR_GRAY);
	
	bar_level_sliders[7]->setTipColor(QColor(30, 30, 30));
	bar_level_sliders[7]->setGripLineColor(_CONTROLS_COLOR_PURPLE);
	
	bar_level_sliders[8]->setTipColor(QColor(220, 220, 220));
	bar_level_sliders[8]->setGripLineColor(_CONTROLS_COLOR_BLUE);
	
	ui->dial_HammondSendFilter1->setKnobColor(_KNOBS_COLOR);
	ui->dial_HammondSendFilter1->setCircleColor(_CONTROLS_COLOR_GRAY);
	ui->dial_HammondSendFilter1->setValue(40);

	ui->spinBox_HammondSendFilter1->setValue(40);

	ui->dial_HammondSendFilter2->setKnobColor(_KNOBS_COLOR);
	ui->dial_HammondSendFilter2->setCircleColor(_CONTROLS_COLOR_PURPLE);
	ui->dial_HammondSendFilter2->setValue(40);

	ui->spinBox_HammondSendFilter2->setValue(40);

	ui->dial_HammondLeslieSpeed->setKnobColor(_KNOBS_COLOR);
	ui->dial_HammondLeslieSpeed->setCircleColor(_CONTROLS_COLOR_BLUE);
	ui->dial_HammondLeslieSpeed->setValue(50);

	ui->spinBox_HammondLeslieSpeed->setValue(50);

	ui->dial_HammondLeslieLevel->setKnobColor(_KNOBS_COLOR);
	ui->dial_HammondLeslieLevel->setCircleColor(_CONTROLS_COLOR_GREEN);
	ui->dial_HammondLeslieLevel->setValue(0);

	ui->spinBox_HammondLeslieLevel->setValue(0);

	ui->pushButton_HammondPresetOpen->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->pushButton_HammondPresetOpen->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);

	ui->pushButton_HammondPresetSave->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->pushButton_HammondPresetSave->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);

	ui->comboBox_HammondPercussionMode->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_HammondPercussionMode->setFrameColor(_CONTROLS_COLOR_BLACK);
	ui->comboBox_HammondPercussionMode->setFrameWidth(2);

	ui->comboBox_HammondPercussionMode->blockSignals(true);
	ui->comboBox_HammondPercussionMode->addItems(string_hammond_modes_list);
	ui->comboBox_HammondPercussionMode->setVisible(true); // false - hide for non Hammond unison mode
	ui->comboBox_HammondPercussionMode->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_HammondPercussionMode->blockSignals(false);

	ui->checkBox_HammondSquareWave->setLedStyle(true);
	ui->checkBox_HammondSquareWave->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_HammondSquareWave->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->checkBox_HammondSquareWave->setBackgroundColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_HammondSquareWave->setCheckBoxSize(16);
	ui->checkBox_HammondSquareWave->setFrameWidth(2);

	ui->frame_HammondControl->setBorderColor(_CONTROLS_COLOR_GRAY);
	ui->frame_HammondControl->setBorderWidth(3);

	ui->frame_Hammond1Drawbars_1_6->setBorderColor(_CONTROLS_COLOR_GRAY);
	ui->frame_Hammond1Drawbars_1_6->setBorderWidth(3);

	ui->frame_HammondDrawbars_7_9->setBorderColor(_CONTROLS_COLOR_WHITE);
	ui->frame_HammondDrawbars_7_9->setBorderWidth(3);

	set_signal_slots_connections();
}

void Dialog_HammondOrgan::set_signal_slots_connections()
{
	connect(ui->verticalSlider_HammondLevel_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_1_slider_changed(int)));

	connect(ui->verticalSlider_HammondLevel_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_2_slider_changed(int)));

	connect(ui->verticalSlider_HammondLevel_3,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_3_slider_changed(int)));

	connect(ui->verticalSlider_HammondLevel_4,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_4_slider_changed(int)));

	connect(ui->verticalSlider_HammondLevel_5,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_5_slider_changed(int)));

	connect(ui->verticalSlider_HammondLevel_6,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_6_slider_changed(int)));

	connect(ui->verticalSlider_HammondLevel_7,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_7_slider_changed(int)));

	connect(ui->verticalSlider_HammondLevel_8,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_8_slider_changed(int)));

	connect(ui->verticalSlider_HammondLevel_9,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_level_9_slider_changed(int)));

	connect(ui->dial_HammondSendFilter1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_filter_1_dial_changed(int)));

	connect(ui->dial_HammondSendFilter2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_filter_2_dial_changed(int)));

	connect(ui->dial_HammondLeslieSpeed,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_leslie_speaker_speed_dial_changed(int)));

	connect(ui->dial_HammondLeslieLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_leslie_speaker_level_dial_changed(int)));

	connect(ui->comboBox_HammondTuneCents,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_tune_cents_combobox_changed(int)));

	connect(ui->comboBox_HammondTuneOctave,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_tune_octave_combobox_changed(int)));

	connect(ui->comboBox_HammondTuneSemitones,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_tune_semitones_combobox_changed(int)));

	connect(ui->comboBox_HammondPercussionMode,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_percussion_mode_combobox_changed(int)));

	connect(ui->checkBox_HammondSquareWave,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_sqare_enable_changed(bool)));

	connect(ui->pushButton_HammondPresetOpen,
			SIGNAL(clicked()),
			this,
			SLOT(on_presets_open_pushbutton_clicked()));

	connect(ui->pushButton_HammondPresetSave,
			SIGNAL(clicked()),
			this,
			SLOT(on_presets_save_pushbutton_clicked()));
}

void Dialog_HammondOrgan::closeEvent(QCloseEvent *event)
{
	if (close_event_callback_ptr != NULL)
	{
		close_event_callback_ptr();
	}

	// Disable callback when hiding
	mod_synth_register_callback_control_box_event_update_ui(NULL);
	
	// Unregister from GuiNavigator
	GuiNavigator::get_instance()->unregister_dialog(this);

	// Hide instead of accept (which could trigger deletion)
	event->ignore(); // Don't accept the close event
	
	hide();
}

void Dialog_HammondOrgan::showEvent(QShowEvent *event)
{
	QDialog::showEvent(event);

	// Re-register callback when showing
	mod_synth_register_callback_control_box_event_update_ui(
		&hammond_organ_control_box_event_update_ui_callback_wrapper);
}

void Dialog_HammondOrgan::handle_control_box_event(int evnt, uint16_t val)
{
	// Only process events if this dialog has focus
	if (!this->hasFocus())
	{
		return;
	}

	int slider_level_gap = 0;

	const int send_max = 100;
	const int send_min = 0;
	const int tune_offset_octave_max = 12; // -6 octave offset (min) to +6 octave offset (max), with 0 octave offset centered (13 steps total starting at 0)
	const int tune_offset_octave_min = 0;
	const int tune_offset_semitone_max = 22; // -11 semitone offset (min) to +11 semitone offset (max), with 0 semitone offset centered (23 steps total starting at 0)
	const int tune_offset_semitone_min = 0;
	const int tune_offset_cents_max = 60; // -7.5 to +7.5 cents, with 0.25 cent steps (61 steps total starting at 0), with 0 cent offset centered
	const int tune_offset_cents_min = 0;
	const int unison_detune_max = _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX;
	const int unison_detune_min = _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN;
	const int hammond_percussion_mode_max = _HAMMOND_PERCUSION_MODE_3RD_NORM_FAST;
	const int hammond_percussion_mode_min = _HAMMOND_PERCUSION_MODE_OFF;

	static int tune_offset_octave = 6;	   // 0 octave offset (centered), with range of -6 to +6 octaves (13 steps total)
	static int tune_offset_semitone = 11; // 0 semitone offset (centered), with range of -11 to +11 semitones (23 steps total)
	static int tune_offset_cents = 30;	   // 0 cent offset (centered), with range of -7.5 to +7.5 cents (61 steps total)
	static int percussion_mode = _HAMMOND_PERCUSION_MODE_OFF;
	static int drawbar_level_1 = _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX;
	static int drawbar_level_2 = 0;
	static int drawbar_level_3 = 0;
	static int drawbar_level_4 = 0;
	static int drawbar_level_5 = 0;
	static int drawbar_level_6 = 0;
	static int drawbar_level_7 = 0;
	static int drawbar_level_8 = 0;
	static int drawbar_level_9 = 0;
	static int send_filter_1 = 40;
	static int send_filter_2 = 40;
	static int leslie_speed = 50;
	static int leslie_level = 0;
	static bool square_wave_enabled = false;

	static int prev_tune_offset_octave = 6;
	static int prev_tune_offset_semitone = 11;
	static int prev_tune_offset_cents = 30;
	static int prev_percussion_mode = _HAMMOND_PERCUSION_MODE_OFF;
	static int prev_drawbar_level_1 = _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX;
	static int prev_drawbar_level_2 = 0;
	static int prev_drawbar_level_3 = 0;
	static int prev_drawbar_level_4 = 0;
	static int prev_drawbar_level_5 = 0;
	static int prev_drawbar_level_6 = 0;
	static int prev_drawbar_level_7 = 0;
	static int prev_drawbar_level_8 = 0;
	static int prev_drawbar_level_9 = 0;
	static int prev_send_filter_1 = 40;
	static int prev_send_filter_2 = 40;
	static int prev_leslie_speed = 50;
	static int prev_leslie_level = 0;
	static bool prev_square_wave_enabled = false;

	if (evnt == _I2C_CONTROL_ENCODER_1)
	{
		// Gray Gray dial - send filter1 control
		send_filter_1 = update_rotary_encoder_value(
			send_filter_1,
			val,
			&prev_send_filter_1,
			send_min,
			send_max,
			_DIAL_INCREMENTS);

		ui->dial_HammondSendFilter1->setValue(send_filter_1);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_2)
	{
		if (val == 4096)
		{
			// pressed - open presets dialog
			on_presets_open_pushbutton_clicked();
		}
		// Gray Purple dial - send filter2 control
		send_filter_2 = update_rotary_encoder_value(
			send_filter_2,
			val,
			&prev_send_filter_2,
			send_min,
			send_max,
			_DIAL_INCREMENTS);

		ui->dial_HammondSendFilter2->setValue(send_filter_2);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_3)
	{
		// Gray Blue dial - leslie speed control
		leslie_speed = update_rotary_encoder_value(
			leslie_speed,
			val,
			&prev_leslie_speed,
			send_min,
			send_max,
			_DIAL_INCREMENTS);

		ui->dial_HammondLeslieSpeed->setValue(leslie_speed);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_4)
	{
		// Gray Green dial - leslie level control
		leslie_level = update_rotary_encoder_value(
			leslie_level,
			val,
			&prev_leslie_level,
			send_min,
			send_max,
			_DIAL_INCREMENTS);

		ui->dial_HammondLeslieLevel->setValue(leslie_level);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_5)
	{
		// Gray White dial - tune offset octave control
		tune_offset_octave = update_rotary_encoder_value(
			tune_offset_octave,
			val,
			&prev_tune_offset_octave,
			send_min,
			send_max,
			_COMBOBOX_INCREMENTS, _COMBOBOX_TIME_GUARD_MS);

		ui->comboBox_HammondTuneOctave->setCurrentIndex(tune_offset_octave);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_6)
	{
		// Gray Yellow dial - tune offset semitone control
		tune_offset_semitone = update_rotary_encoder_value(
			tune_offset_semitone,
			val,
			&prev_tune_offset_semitone,
			send_min,
			send_max,
			_COMBOBOX_INCREMENTS, _COMBOBOX_TIME_GUARD_MS);

		ui->comboBox_HammondTuneSemitones->setCurrentIndex(tune_offset_semitone);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_7)
	{
		// Gray Red dial - tune offset cents control
		tune_offset_cents = update_rotary_encoder_value(
			tune_offset_cents,
			val,
			&prev_tune_offset_cents,
			send_min,
			send_max,
			_COMBOBOX_INCREMENTS, _COMBOBOX_TIME_GUARD_MS);

		ui->comboBox_HammondTuneCents->setCurrentIndex(tune_offset_cents);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_8)
	{
		// Gray Black dial - percussion mode control
		percussion_mode = update_rotary_encoder_value(
			percussion_mode,
			val,
			&prev_percussion_mode,
			send_min,
			send_max,
			_COMBOBOX_INCREMENTS, _COMBOBOX_TIME_GUARD_MS);

		ui->comboBox_HammondPercussionMode->setCurrentIndex(percussion_mode);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_11)
	{
		// Gray Blue dial pushbutton - square wave mode control
		if (val == 4096)
		{
			// pressed - Toggle square wave mode
			square_wave_enabled = !square_wave_enabled;
			ui->checkBox_HammondSquareWave->setChecked(square_wave_enabled);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_1)
	{
		// Gray Gray slider - drawbar 1 control
		// Get new drawbar 1 value from slider - Note slider is moving from up to down
		// and calculate gap from current UI value
		drawbar_level_1 = _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX - 
						  normalize_slider_value(val / 36, _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX, _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN); // 0-3600
		slider_level_gap = drawbar_level_1 - ui->verticalSlider_HammondLevel_1->value();		// 0-8
		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) > 0.9)
		{
			// Emits value changed signal.
			ui->verticalSlider_HammondLevel_1->setValue(drawbar_level_1);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_2)
	{
		// Gray Purple slider - drawbar 2 control
		// Get new drawbar 2 value from slider - Note slider is moving from up to down
		// and calculate gap from current UI value
		drawbar_level_2 = _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX -
						  normalize_slider_value(val / 36, _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX, _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN); // 0-3600
		slider_level_gap = drawbar_level_2 - ui->verticalSlider_HammondLevel_2->value();										// 0-8
		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) > 0.9)
		{
			// Emits value changed signal.
			ui->verticalSlider_HammondLevel_2->setValue(drawbar_level_2);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_3)
	{
		// Gray Blue slider - drawbar 3 control
		// Get new drawbar 3 value from slider - Note slider is moving from up to down
		// and calculate gap from current UI value
		drawbar_level_3 = _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX -
						  normalize_slider_value(val / 36, _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX, _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN); // 0-3600
		slider_level_gap = drawbar_level_3 - ui->verticalSlider_HammondLevel_3->value();										// 0-8
		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) > 0.9)
		{
			// Emits value changed signal.
			ui->verticalSlider_HammondLevel_3->setValue(drawbar_level_3);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_4)
	{
		// Gray Green slider - drawbar 4 control
		// Get new drawbar 4 value from slider - Note slider is moving from up to down
		// and calculate gap from current UI value
		drawbar_level_4 = _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX -
						  normalize_slider_value(val / 36, _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX, _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN); // 0-3600
		slider_level_gap = drawbar_level_4 - ui->verticalSlider_HammondLevel_4->value();										// 0-8
		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) > 0.9)
		{
			// Emits value changed signal.
			ui->verticalSlider_HammondLevel_4->setValue(drawbar_level_4);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_5)
	{
		// Gray White slider - drawbar 5 control
		// Get new drawbar 5 value from slider - Note slider is moving from up to down
		// and calculate gap from current UI value
		drawbar_level_5 = _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX -
						  normalize_slider_value(val / 36, _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX, _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN); // 0-3600
		slider_level_gap = drawbar_level_5 - ui->verticalSlider_HammondLevel_5->value();										// 0-8
		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) > 0.9)
		{
			// Emits value changed signal.
			ui->verticalSlider_HammondLevel_5->setValue(drawbar_level_5);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_6)
	{
		// Gray Yellow slider - drawbar 6 control
		// Get new drawbar 6 value from slider - Note slider is moving from up to down
		// and calculate gap from current UI value
		drawbar_level_6 = _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX -
						  normalize_slider_value(val / 36, _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX, _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN); // 0-3600
		slider_level_gap = drawbar_level_6 - ui->verticalSlider_HammondLevel_6->value();										// 0-8
		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) > 0.9)
		{
			// Emits value changed signal.
			ui->verticalSlider_HammondLevel_6->setValue(drawbar_level_6);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_9)
	{
		// White Gray slider - drawbar 7 control
		// Get new drawbar 7 value from slider - Note slider is moving from up to down
		// and calculate gap from current UI value
		drawbar_level_7 = _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX -
						  normalize_slider_value(val / 36, _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX, _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN); // 0-3600
		slider_level_gap = drawbar_level_7 - ui->verticalSlider_HammondLevel_7->value();										// 0-8
		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) > 0.9)
		{
			// Emits value changed signal.
			ui->verticalSlider_HammondLevel_7->setValue(drawbar_level_7);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_10)
	{
		// White Purple slider - drawbar 8 control
		// Get new drawbar 8 value from slider - Note slider is moving from up to down
		// and calculate gap from current UI value
		drawbar_level_8 = _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX -
						  normalize_slider_value(val / 36, _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX, _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN); // 0-3600
		slider_level_gap = drawbar_level_8 - ui->verticalSlider_HammondLevel_8->value();										// 0-8
		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) > 0.9)
		{
			// Emits value changed signal.
			ui->verticalSlider_HammondLevel_8->setValue(drawbar_level_8);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_11)
	{
		// White Blue slider - drawbar 9 control
		// Get new drawbar 9 value from slider - Note slider is moving from up to down
		// and calculate gap from current UI value
		drawbar_level_9 = _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX -
						  normalize_slider_value(val / 36, _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX, _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN); // 0-3600
		slider_level_gap = drawbar_level_9 - ui->verticalSlider_HammondLevel_9->value();										// 0-8
		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) > 0.9)
		{
			// Emits value changed signal.
			ui->verticalSlider_HammondLevel_9->setValue(drawbar_level_9);
		}
	}
}

void Dialog_HammondOrgan::on_dialog_close()
{
	close();
}

void Dialog_HammondOrgan::on_send_filter_1_dial_changed(int val)
{
	if (val < 0 || val > 100)
	{
		return;
	}

	// Update the dial and spinbox values without triggering their signals - used by control box event.
	ui->dial_HammondSendFilter1->blockSignals(true);
	ui->dial_HammondSendFilter1->setValue(val);
	ui->dial_HammondSendFilter1->blockSignals(false);

	ui->spinBox_HammondSendFilter1->blockSignals(true);
	ui->spinBox_HammondSendFilter1->setValue(val);
	ui->spinBox_HammondSendFilter1->blockSignals(false);

	mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_SEND_FILTER_1, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_HammondOrgan::on_send_filter_2_dial_changed(int val)
{
	if (val < 0 || val > 100)
	{
		return;
	}
	
	ui->dial_HammondSendFilter2->blockSignals(true);
	ui->dial_HammondSendFilter2->setValue(val);
	ui->dial_HammondSendFilter2->blockSignals(false);

	ui->spinBox_HammondSendFilter2->blockSignals(true);
	ui->spinBox_HammondSendFilter2->setValue(val);
	ui->spinBox_HammondSendFilter2->blockSignals(false);

	mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_SEND_FILTER_2, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_HammondOrgan::on_leslie_speaker_speed_dial_changed(int val)
{
	if (val < 0 || val > 100)
	{
		return;
	}
	
	ui->dial_HammondLeslieSpeed->blockSignals(true);
	ui->dial_HammondLeslieSpeed->setValue(val);
	ui->dial_HammondLeslieSpeed->blockSignals(false);

	ui->spinBox_HammondLeslieSpeed->blockSignals(true);
	ui->spinBox_HammondLeslieSpeed->setValue(val);
	ui->spinBox_HammondLeslieSpeed->blockSignals(false);

	mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_LESLIE_SPEED, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_HammondOrgan::on_leslie_speaker_level_dial_changed(int val)
{
	if (val < 0 || val > 100)
	{
		return;
	}
	
	ui->dial_HammondLeslieLevel->blockSignals(true);
	ui->dial_HammondLeslieLevel->setValue(val);
	ui->dial_HammondLeslieLevel->blockSignals(false);

	ui->spinBox_HammondLeslieLevel->blockSignals(true);
	ui->spinBox_HammondLeslieLevel->setValue(val);
	ui->spinBox_HammondLeslieLevel->blockSignals(false);

	mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_LESLIE_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_HammondOrgan::on_tune_octave_combobox_changed(int val)
{
	ui->comboBox_HammondTuneOctave->blockSignals(true);
	ui->comboBox_HammondTuneOctave->setCurrentIndex(val);
	ui->comboBox_HammondTuneOctave->blockSignals(false);

	mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DETUNE_OCTAVE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_HammondOrgan::on_tune_semitones_combobox_changed(int val)
{
	ui->comboBox_HammondTuneSemitones->blockSignals(true);
	ui->comboBox_HammondTuneSemitones->setCurrentIndex(val);
	ui->comboBox_HammondTuneSemitones->blockSignals(false);

	mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DETUNE_SEMITONES, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_HammondOrgan::on_tune_cents_combobox_changed(int val)
{
	ui->comboBox_HammondTuneCents->blockSignals(true);
	ui->comboBox_HammondTuneCents->setCurrentIndex(val);
	ui->comboBox_HammondTuneCents->blockSignals(false);

	mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DETUNE_CENTS, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_HammondOrgan::on_sqare_enable_changed(bool en)
{
	ui->checkBox_HammondSquareWave->blockSignals(true);
	
	if (en)
	{
		ui->checkBox_HammondSquareWave->setCheckState(Qt::Checked);
		mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_SQUARE_WAVE_ENABLE, 1);
	}
	else
	{
		ui->checkBox_HammondSquareWave->setCheckState(Qt::Unchecked);
		mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_SQUARE_WAVE_ENABLE, 0);
	}
	
	ui->checkBox_HammondSquareWave->blockSignals(false);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_HammondOrgan::on_level_1_slider_changed(int val)
{
	if (val < _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN || val > _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX)
	{
		return;
	}

	ui->verticalSlider_HammondLevel_1->blockSignals(true);
	ui->verticalSlider_HammondLevel_1->setValue(val);
	ui->verticalSlider_HammondLevel_1->blockSignals(false);

	mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DRAWBAR_LEVEL_1, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_HammondOrgan::on_level_2_slider_changed(int val)
{
	if (val < _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN || val > _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX)
	{
		return;
	}
	
	ui->verticalSlider_HammondLevel_2->blockSignals(true);
	ui->verticalSlider_HammondLevel_2->setValue(val);
	ui->verticalSlider_HammondLevel_2->blockSignals(false);
	
	mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DRAWBAR_LEVEL_2, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_HammondOrgan::on_level_3_slider_changed(int val)
{
	if (val < _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN || val > _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX)
	{
		return;
	}
	
	ui->verticalSlider_HammondLevel_3->blockSignals(true);
	ui->verticalSlider_HammondLevel_3->setValue(val);
	ui->verticalSlider_HammondLevel_3->blockSignals(false);
	
	mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DRAWBAR_LEVEL_3, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_HammondOrgan::on_level_4_slider_changed(int val)
{
	if (val < _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN || val > _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX)
	{
		return;
	}
	
	ui->verticalSlider_HammondLevel_4->blockSignals(true);
	ui->verticalSlider_HammondLevel_4->setValue(val);
	ui->verticalSlider_HammondLevel_4->blockSignals(false);
	mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DRAWBAR_LEVEL_4, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_HammondOrgan::on_level_5_slider_changed(int val)
{
	if (val < _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN || val > _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX)
	{
		return;
	}
	
	ui->verticalSlider_HammondLevel_5->blockSignals(true);
	ui->verticalSlider_HammondLevel_5->setValue(val);
	ui->verticalSlider_HammondLevel_5->blockSignals(false);
	
	mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DRAWBAR_LEVEL_5, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_HammondOrgan::on_level_6_slider_changed(int val)
{
	if (val < _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN || val > _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX)
	{
		return;
	}

	ui->verticalSlider_HammondLevel_6->blockSignals(true);
	ui->verticalSlider_HammondLevel_6->setValue(val);
	ui->verticalSlider_HammondLevel_6->blockSignals(false);

	mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DRAWBAR_LEVEL_6, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_HammondOrgan::on_level_7_slider_changed(int val)
{
	if (val < _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN || val > _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX)
	{
		return;
	}
	
	ui->verticalSlider_HammondLevel_7->blockSignals(true);
	ui->verticalSlider_HammondLevel_7->setValue(val);
	ui->verticalSlider_HammondLevel_7->blockSignals(false);
	
	mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DRAWBAR_LEVEL_7, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_HammondOrgan::on_level_8_slider_changed(int val)
{
	if (val < _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN || val > _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX)
	{
		return;
	}

	ui->verticalSlider_HammondLevel_8->blockSignals(true);
	ui->verticalSlider_HammondLevel_8->setValue(val);
	ui->verticalSlider_HammondLevel_8->blockSignals(false);
	
	mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DRAWBAR_LEVEL_8, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_HammondOrgan::on_level_9_slider_changed(int val)
{
	if (val < _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN || val > _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX)
	{
		return;
	}
	
	ui->verticalSlider_HammondLevel_9->blockSignals(true);
	ui->verticalSlider_HammondLevel_9->setValue(val);
	ui->verticalSlider_HammondLevel_9->blockSignals(false);
	
	mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DRAWBAR_LEVEL_9, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_HammondOrgan::on_percussion_mode_combobox_changed(int val)
{
	ui->comboBox_HammondPercussionMode->blockSignals(true);
	ui->comboBox_HammondPercussionMode->setCurrentIndex(val);
	ui->comboBox_HammondPercussionMode->blockSignals(false);

	mod_synth_set_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_PERCUSSION_MODE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_HammondOrgan::on_presets_open_pushbutton_clicked()
{
	QString startDir = last_hammond_preset_directory.isEmpty() ? QString(_HAMMOND_ORGAN_PRESETS_FILES_DEFAULT_DIR) : last_hammond_preset_directory;

	CustomFileDialog dialog(this,
							tr("Open Preset File"),
							startDir,
							tr("Presets (*.xml *.XML);;All Files (*)"),
							Qt::black); // Background color set here)

	// If we have a last file, select it and scroll to it
	if (!last_hammond_preset_load_file.isEmpty())
	{
		dialog.selectFile(last_hammond_preset_load_file);
	}

	if (dialog.exec() == QDialog::Accepted)
	{
		hammond_organpreset_file_name = dialog.selectedFile();

		if (!hammond_organpreset_file_name.isEmpty())
		{
			// Remember the directory and file for next time
			last_hammond_preset_directory = QFileInfo(hammond_organpreset_file_name).absolutePath();
			last_hammond_preset_load_file = hammond_organpreset_file_name;

			std::string file_name;
			//file_name = std::string("Now Loading: ");
			file_name = std::filesystem::path(hammond_organpreset_file_name.toStdString()).stem();

			ui->textEdit_HammondPresetText->setText(QString::fromStdString(file_name));

			MainWindow *mainWin = MainWindow::get_instance();
			if (mainWin)
			{
				InstrumentPannel *panel =
					mainWin->get_instrument_panel_by_id(en_instruments_ids_t::adj_hammond_organ);
				if (panel)
				{
					panel->set_preset_text(QString::fromStdString(file_name));
				}
			}

			// Check if thread is still running - prevent creating duplicate threads
			if (load_hammond_organ_preset_file_thread != nullptr &&
				!load_hammond_organ_preset_file_thread->isFinished())
			{
				// Thread still running, ignore this request or wait
				return;
			}

			load_hammond_organ_preset_file_thread = new LoadHammondOrganPresetFileThread();
			connect(load_hammond_organ_preset_file_thread,
					&LoadHammondOrganPresetFileThread::finished,
					this,
					[=]() {
						load_hammond_organ_preset_file_thread->deleteLater();
						load_hammond_organ_preset_file_thread = nullptr; // Reset to nullptr after deletion
					});
			connect(load_hammond_organ_preset_file_thread,
					&LoadHammondOrganPresetFileThread::loadPresetFileDone,
					this,
					&Dialog_HammondOrgan::on_preset_file_loaded);
			// Reset pointer when thread is destroyed
			connect(load_hammond_organ_preset_file_thread,
					&QObject::destroyed,
					[]() { load_hammond_organ_preset_file_thread = nullptr; });
			load_hammond_organ_preset_file_thread->start();
		}
	}
}

void Dialog_HammondOrgan::on_presets_save_pushbutton_clicked()
{
	QString startDir = last_hammond_preset_directory.isEmpty() ? QString(_HAMMOND_ORGAN_PRESETS_FILES_DEFAULT_DIR) : last_hammond_preset_directory;

	// Use CustomFileDialog in Save mode
	CustomFileDialog dialog(this,
							tr("Save Preset File"),
							startDir,
							tr("Presets (*.xml *.XML);;All Files (*)"),
							Qt::black,
							CustomFileDialog::SaveMode); // Set to Save mode

	if (dialog.exec() == QDialog::Accepted)
	{
		hammond_organpreset_file_name = dialog.selectedFile();

		if (!hammond_organpreset_file_name.isEmpty())
		{
			// Ensure .xml extension
			if (!hammond_organpreset_file_name.endsWith(".xml", Qt::CaseInsensitive))
			{
				hammond_organpreset_file_name += ".xml";
			}

			// Check if file exists and ask for confirmation
			if (QFile::exists(hammond_organpreset_file_name))
			{
				QMessageBox msgBox;
				msgBox.setIcon(QMessageBox::Warning);
				msgBox.setWindowTitle("Confirm Overwrite");
				msgBox.setText(QString("File '%1' already exists.")
								   .arg(QFileInfo(hammond_organpreset_file_name).fileName()));
				msgBox.setInformativeText("Do you want to overwrite it?");
				msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
				msgBox.setDefaultButton(QMessageBox::Cancel);

				if (msgBox.exec() != QMessageBox::Yes)
				{
					return;
				}
			}

			// Remember the directory and file for next time
			last_hammond_preset_directory = QFileInfo(hammond_organpreset_file_name).absolutePath();
			last_hammond_preset_save_file = hammond_organpreset_file_name;

			// Display saving message
			std::string file_name = std::string("Now Saving: ");
			file_name += std::filesystem::path(hammond_organpreset_file_name.toStdString()).stem().string();
			//ui->textEdit_HammondPresetText->setText(QString::fromStdString(file_name));

			// Check if thread is still running
			if (save_hammond_organ_preset_file_thread != nullptr &&
				!save_hammond_organ_preset_file_thread->isFinished())
			{
				return;
			}
			
			// Start the save thread
			save_hammond_organ_preset_file_thread = new SaveHammondOrganPresetFileThread();

			connect(save_hammond_organ_preset_file_thread,
					&SaveHammondOrganPresetFileThread::finished,
					this,
					[=]() {
						save_hammond_organ_preset_file_thread->deleteLater();
						save_hammond_organ_preset_file_thread = nullptr; // Reset to nullptr after deletion
					});
			connect(save_hammond_organ_preset_file_thread,
					&SaveHammondOrganPresetFileThread::savePresetFileDone,
					this,
					&Dialog_HammondOrgan::on_preset_file_saved);
			// Reset pointer when thread is destroyed
			connect(save_hammond_organ_preset_file_thread,
					&QObject::destroyed,
					[]() { save_hammond_organ_preset_file_thread = nullptr; });

			save_hammond_organ_preset_file_thread->start();
		}
	}
}

void Dialog_HammondOrgan::on_preset_file_loaded(const QString &s)
{
	
}

void Dialog_HammondOrgan::on_preset_file_saved(const QString &s)
{
	
}

void Dialog_HammondOrgan::update_gui()
{
	// Don't update if dialog is not visible
	if (!isVisible())
	{
		return;
	}
	
	int val;

	static int prev_send_filter_1_val = -1;
	static int prev_send_filter_2_val = -1;
	static int prev_leslie_speed_val = -1;
	static int prev_leslie_level_val = -1;
	static int prev_percussion_mode_val = -1;
	static int prev_square_wave_enable_val = -1;
	static int prev_drawbar_levels[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
	static int prev_tune_octave_val = -1;
	static int prev_tune_semitones_val = -1;
	static int prev_tune_cents_val = -1;

	val = mod_synth_get_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_SEND_FILTER_1);

	if (val != prev_send_filter_1_val && val >= 0 && val <= 100)
	{
		// This will also trigger the on change event.
		prev_send_filter_1_val = val;
		ui->dial_HammondSendFilter1->setValue(val);
	}

	val = mod_synth_get_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_SEND_FILTER_2);

	if (val != prev_send_filter_2_val && val >= 0 && val <= 100)
	{
		prev_send_filter_2_val = val;
		ui->dial_HammondSendFilter2->setValue(val);
	}

	val = mod_synth_get_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_LESLIE_SPEED);

	if (val != prev_leslie_speed_val && val >= 0 && val <= 100)
	{
		prev_leslie_speed_val = val;
		ui->dial_HammondLeslieSpeed->setValue(val);
	}

	val = mod_synth_get_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_LESLIE_LEVEL);

	if (val != prev_leslie_level_val && val >= 0 && val <= 100)
	{
		prev_leslie_level_val = val;
		ui->dial_HammondLeslieLevel->setValue(val);
	}

	val = mod_synth_get_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DRAWBAR_LEVEL_1);

	if (val != prev_drawbar_levels[0] && val >= _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN && val <= _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX)
	{
		prev_drawbar_levels[0] = val;
		ui->verticalSlider_HammondLevel_1->setValue(val);
	}

	val = mod_synth_get_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DRAWBAR_LEVEL_2);

	if (val != prev_drawbar_levels[1] && val >= _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN && val <= _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX)
	{
		prev_drawbar_levels[1] = val;
		ui->verticalSlider_HammondLevel_2->setValue(val);
	}

	val = mod_synth_get_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DRAWBAR_LEVEL_3);
	if (val != prev_drawbar_levels[2] && val >= _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN && val <= _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX)
	{
		prev_drawbar_levels[2] = val;
		ui->verticalSlider_HammondLevel_3->setValue(val);
	}

	val = mod_synth_get_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DRAWBAR_LEVEL_4);
	if (val != prev_drawbar_levels[3] && val >= _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN && val <= _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX)
	{
		prev_drawbar_levels[3] = val;
		ui->verticalSlider_HammondLevel_4->setValue(val);
	}

	val = mod_synth_get_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DRAWBAR_LEVEL_5);
	if (val != prev_drawbar_levels[4] && val >= _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN && val <= _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX)
	{
		prev_drawbar_levels[4] = val;
		ui->verticalSlider_HammondLevel_5->setValue(val);
	}

	val = mod_synth_get_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DRAWBAR_LEVEL_6);
	if (val != prev_drawbar_levels[5] && val >= _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN && val <= _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX)
	{
		prev_drawbar_levels[5] = val;
		ui->verticalSlider_HammondLevel_6->setValue(val);
	}

	val = mod_synth_get_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DRAWBAR_LEVEL_7);
	if (val != prev_drawbar_levels[6] && val >= _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN && val <= _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX)
	{
		prev_drawbar_levels[6] = val;
		ui->verticalSlider_HammondLevel_7->setValue(val);
	}

	val = mod_synth_get_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DRAWBAR_LEVEL_8);
	
	if (val != prev_drawbar_levels[7] && val >= _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN && val <= _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX)
	{
		prev_drawbar_levels[7] = val;
		ui->verticalSlider_HammondLevel_8->setValue(val);
	}

	val = mod_synth_get_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DRAWBAR_LEVEL_9);
	if (val != prev_drawbar_levels[8] && val >= _HAMMOND_ORGAN_DRAWBAR_LEVEL_MIN && val <= _HAMMOND_ORGAN_DRAWBAR_LEVEL_MAX)
	{
		prev_drawbar_levels[8] = val;
		ui->verticalSlider_HammondLevel_9->setValue(val);
	}

	val = mod_synth_get_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_PERCUSSION_MODE);
	if (val != prev_percussion_mode_val && val >= 0 && val < string_hammond_modes_list.size())
	{
		prev_percussion_mode_val = val;
		ui->comboBox_HammondPercussionMode->setCurrentIndex(val);
	}

	val = mod_synth_get_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_SQUARE_WAVE_ENABLE);
	if (val != prev_square_wave_enable_val && (val == 0 || val == 1))
	{
		prev_square_wave_enable_val = val;
		ui->checkBox_HammondSquareWave->setChecked(val == 1 ? Qt::Checked : Qt::Unchecked);
	}

	val = mod_synth_get_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DETUNE_OCTAVE);
	if (val != prev_tune_octave_val)
	{
		prev_tune_octave_val = val;
		ui->comboBox_HammondTuneOctave->setCurrentIndex(val - _OSC_DETUNE_MIN_OCTAVE);
	}

	val = mod_synth_get_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DETUNE_SEMITONES);
	if (val != prev_tune_semitones_val)
	{
		prev_tune_semitones_val = val;
		ui->comboBox_HammondTuneSemitones->setCurrentIndex(val - _OSC_DETUNE_MIN_SEMITONES);
	}

	val = mod_synth_get_hammond_organ_param_value(_HAMMOND_ORGAN_EVENT, _HAMMOND_ORGAN_DETUNE_CENTS);
	if (val != prev_tune_cents_val)
	{
		prev_tune_cents_val = val;
		ui->comboBox_HammondTuneCents->setCurrentIndex(val - _OSC_DETUNE_MIN_CENTS * 4);
	}
}

void Dialog_HammondOrgan::start_update_timer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update_gui()));
	timer->start(interval);
}

//void Dialog_HammondOrgan::timerEvent(QTimerEvent *event)
//{
//	killTimer(event->timerId());
//	start_update_timer(_UPDATE_TIMER_PERIOD_MS);
//}


