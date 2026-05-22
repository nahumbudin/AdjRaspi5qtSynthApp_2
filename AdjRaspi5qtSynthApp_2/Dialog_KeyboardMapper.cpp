/**
 * @file		Dialog_KeyboardMapper.cpp
 *	@author		Nahum Budin
 *	@date		8-May-2026
 *	@version	1.0
 *
 *	@brief		Adj Keyboard Mapper control dialog
 *
 */

#include "filesystem"
#include <QTimer>

#include "Dialog_KeyboardMapper.h"
#include "ui_Dialog_KeyboardMapper.h"

#include "MainWindow.h"
#include "GuiNavigator.h"
#include "CustomFileDialog.h"

#include "modSynthAPI.h"
#include "utils.h"

#define _UPDATE_TIMER_PERIOD_MS 250

Dialog_KeyboardMapper *Dialog_KeyboardMapper::dialog_keyboard_mapper_instance = NULL;

LoadKeyboardMapperPresetFileThread *load_keyboard_mapper_preset_file_thread;
SaveKeyboardMapperPresetFileThread *save_keyboard_mapper_preset_file_thread;

QString keyboard_mapper_preset_file_name;

void keyboard_mapper_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	// Just forward to the dialog instance - it will emit a signal
	Dialog_KeyboardMapper::get_instance()->control_box_event_received(evnt, val);
}

void SaveKeyboardMapperPresetFileThread::run()
{
	int res;

	QString result = QString("Preset File Saved");
	res = mod_synth_save_keyboard_mapper_preset_file(keyboard_mapper_preset_file_name.toStdString());

	emit savePresetFileDone(result);
}

void LoadKeyboardMapperPresetFileThread::run()
{
	int res;

	QString result = QString("Preset File Loaded");
	res = mod_synth_load_keyboard_mapper_preset_file(keyboard_mapper_preset_file_name.toStdString());

	emit loadPresetFileDone(result);
}

Dialog_KeyboardMapper::Dialog_KeyboardMapper(QWidget *parent)
	: QDialog(parent), ui(new Ui::Dialog_KeyboardMapper)
{
	zone_1_octave_offset = 0;
	zone_1_midi_channel = 0;
	zone_2_octave_offset = 0;
	zone_2_midi_channel = 1;
	split_point_note = 60; // C4
	bypass_on = false;
	
	ui->setupUi(this);

	// Prevent dialog from being deleted when closed - only hide it
	setAttribute(Qt::WA_DeleteOnClose, false);

	ui->frame_KeyboardMapper->setAutoFillBackground(true);
	ui->frame_KeyboardMapper->setStyleSheet("background-color: rgb(5, 5, 5);");

	dialog_keyboard_mapper_instance = this;
	close_event_callback_ptr = NULL;

	// Connect signal to slot with Qt::QueuedConnection for thread-safety
	// This ensures the slot runs in the GUI thread
	connect(this, &Dialog_KeyboardMapper::control_box_event_signal,
			this, &Dialog_KeyboardMapper::handle_control_box_event,
			Qt::QueuedConnection);

	// Register control box event callback
	mod_synth_register_callback_control_box_event_update_ui(
		&keyboard_mapper_control_box_event_update_ui_callback_wrapper);

	init_gui_elements();
	set_signal_slots_connections();

	// Register with GuiNavigator (no tabs, no frames for Keyboard Mapper)
	GuiNavigator::get_instance()->register_dialog(this, "Keyboard Mapper");

	// Also register with MainWindow for compatibility
	MainWindow::get_instance()->register_active_dialog(this);

	// GUI Update timer start
	start_update_timer(_UPDATE_TIMER_PERIOD_MS);

	/* Set focus on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

Dialog_KeyboardMapper::~Dialog_KeyboardMapper()
{
	// Reset static instance pointer when destroyed
	dialog_keyboard_mapper_instance = nullptr;
	delete ui;
}

Dialog_KeyboardMapper *Dialog_KeyboardMapper::get_instance(QWidget *parent)
{
	if (dialog_keyboard_mapper_instance == NULL)
	{
		dialog_keyboard_mapper_instance = new Dialog_KeyboardMapper(parent);
	}
	return dialog_keyboard_mapper_instance;
}

// Thread-safe function called from callback - just emits signal
void Dialog_KeyboardMapper::control_box_event_received(int evnt, uint16_t val)
{
	// Emit signal - Qt will queue it to run in GUI thread
	emit control_box_event_signal(evnt, val);
}

void Dialog_KeyboardMapper::init_gui_elements()
{
	int result;

	ui->frame_KeyboardMapper->setBorderColor(_CONTROLS_COLOR_GRAY);
	ui->frame_KeyboardMapper->setBorderWidth(3);

	ui->comboBox_KeyboardMapper_MidiChannelZone_1->blockSignals(true);
	ui->comboBox_KeyboardMapper_MidiChannelZone_1->blockSignals(true);
	ui->comboBox_KeyboardMapper_MidiChannelZone_2->blockSignals(true);
	ui->comboBox_KeyboardMapper_MidiChannelZone_2->blockSignals(true);

	for (int i = _OSC_DETUNE_MIN_OCTAVE; i <= _OSC_DETUNE_MAX_OCTAVE; i++)
	{
		ui->comboBox_KeyboardMapper_OctaveTransposeZone_1->addItem(QString::number(i));
		ui->comboBox_KeyboardMapper_OctaveTransposeZone_2->addItem(QString::number(i));
	}

	for (int i = 0; i < 16; i++)
	{
		ui->comboBox_KeyboardMapper_MidiChannelZone_1->addItem(QString::number(i + 1));
		ui->comboBox_KeyboardMapper_MidiChannelZone_2->addItem(QString::number(i + 1));
	}

	ui->comboBox_KeyboardMapper_MidiChannelZone_1->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_KeyboardMapper_MidiChannelZone_1->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_KeyboardMapper_MidiChannelZone_1->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->comboBox_KeyboardMapper_MidiChannelZone_1->setFrameWidth(2);
	ui->comboBox_KeyboardMapper_MidiChannelZone_1->setCurrentIndex(0);

	ui->comboBox_KeyboardMapper_OctaveTransposeZone_1->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_KeyboardMapper_OctaveTransposeZone_1->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_KeyboardMapper_OctaveTransposeZone_1->setFrameColor(_CONTROLS_COLOR_GREEN);
	ui->comboBox_KeyboardMapper_OctaveTransposeZone_1->setFrameWidth(2);
	ui->comboBox_KeyboardMapper_OctaveTransposeZone_1->setCurrentIndex(mod_synth_get_active_osc1_detune_octave() - mod_synth_get_osc_detune_min_octave());

	ui->comboBox_KeyboardMapper_MidiChannelZone_2->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_KeyboardMapper_MidiChannelZone_2->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_KeyboardMapper_MidiChannelZone_2->setFrameColor(_CONTROLS_COLOR_WHITE);
	ui->comboBox_KeyboardMapper_MidiChannelZone_2->setFrameWidth(2);
	ui->comboBox_KeyboardMapper_MidiChannelZone_2->setCurrentIndex(1);

	ui->comboBox_KeyboardMapper_OctaveTransposeZone_2->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_KeyboardMapper_OctaveTransposeZone_2->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_KeyboardMapper_OctaveTransposeZone_2->setFrameColor(_CONTROLS_COLOR_YELLOW);
	ui->comboBox_KeyboardMapper_OctaveTransposeZone_2->setFrameWidth(2);
	ui->comboBox_KeyboardMapper_OctaveTransposeZone_2->setCurrentIndex(mod_synth_get_active_osc1_detune_octave() - mod_synth_get_osc_detune_min_octave());

	ui->comboBox_KeyboardMapper_MidiChannelZone_1->blockSignals(false);
	ui->comboBox_KeyboardMapper_MidiChannelZone_1->blockSignals(false);
	ui->comboBox_KeyboardMapper_MidiChannelZone_2->blockSignals(false);
	ui->comboBox_KeyboardMapper_MidiChannelZone_2->blockSignals(false);

	ui->dial_KeyboardMapper_SplitNote->setKnobColor(_KNOBS_COLOR);
	ui->dial_KeyboardMapper_SplitNote->setCircleColor(_CONTROLS_COLOR_PURPLE);
	ui->dial_KeyboardMapper_SplitNote->setValue(50);
	ui->dial_KeyboardMapper_SplitNote->setNotchesVisible(false);
	ui->dial_KeyboardMapper_SplitNote->setWrapping(true);
	ui->dial_KeyboardMapper_SplitNote->setIndicatorVisible(false);

	ui->checkBox_KeyboardMapper_BypassOn->setLedStyle(true);
	ui->checkBox_KeyboardMapper_BypassOn->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_KeyboardMapper_BypassOn->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->checkBox_KeyboardMapper_BypassOn->setBackgroundColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_KeyboardMapper_BypassOn->setCheckBoxSize(16);
	ui->checkBox_KeyboardMapper_BypassOn->setFrameWidth(2);

	update_split_point_note_text();
}

void Dialog_KeyboardMapper::set_signal_slots_connections()
{
	connect(ui->comboBox_KeyboardMapper_OctaveTransposeZone_1,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_octave_transpose_zone_1_combobox_changed(int)));

	connect(ui->comboBox_KeyboardMapper_MidiChannelZone_1,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_midi_channel_zone_1_combobox_changed(int)));

	connect(ui->comboBox_KeyboardMapper_OctaveTransposeZone_2,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_octave_transpose_zone_2_combobox_changed(int)));

	connect(ui->comboBox_KeyboardMapper_MidiChannelZone_2,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_midi_channel_zone_2_combobox_changed(int)));

	connect(ui->dial_KeyboardMapper_SplitNote,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_split_point_note_dial_changed(int)));

	connect(ui->checkBox_KeyboardMapper_BypassOn,
			SIGNAL(stateChanged(int)),
			this,
			SLOT(on_bypass_on_checkbox_changed(int)));
}

void Dialog_KeyboardMapper::closeEvent(QCloseEvent *event)
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

void Dialog_KeyboardMapper::handle_control_box_event(int evnt, uint16_t val)
{
	// Only process events if this dialog has focus
	if (!this->hasFocus())
	{
		return;
	}

	int slider_level_gap = 0;

	static int zone_1_midi_channel = 0;
	static int zone_1_octave_transpose = 6; // 0 octave offset (centered), with range of -6 to +6 octaves (13 steps total)
	static int zone_2_midi_channel = 1;
	static int zone_2_octave_transpose = 6;
	static int split_point_note = 48;
	static bool bypass_on = false;

	static int prev_zone_1_midi_channel = 0;
	static int prev_zone_1_octave_transpose = 6;
	static int prev_zone_2_midi_channel = 1;
	static int prev_zone_2_octave_transpose = 6;
	static int prev_split_point_note = 48;

	if (evnt == _I2C_CONTROL_ENCODER_2)
	{
		if (val == 4096)
		{
			// pressed - toggle bypass state
			bypass_on = !bypass_on;
			on_bypass_on_checkbox_changed(bypass_on);
		}

		// Gray Purple dial - set split note note
		split_point_note = update_rotary_encoder_value(
			split_point_note,
			val,
			&prev_split_point_note,
			-10000000,
			10000000,
			4);

		on_split_point_note_dial_changed(split_point_note);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_3)
	{
		// Gray Blue dial - zone 1 midi channel
		zone_1_midi_channel = update_rotary_encoder_value(
			zone_1_midi_channel,
			val,
			&prev_zone_1_midi_channel,
			0,
			15,
			1);

		ui->comboBox_KeyboardMapper_MidiChannelZone_1->setCurrentIndex(zone_1_midi_channel);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_4)
	{
		// Gray Green dial - zone 1 octave traspose
		zone_1_octave_transpose = update_rotary_encoder_value(
			zone_1_octave_transpose,
			val,
			&prev_zone_1_octave_transpose,
			0,
			12,
			1);

		ui->comboBox_KeyboardMapper_OctaveTransposeZone_1->setCurrentIndex(zone_1_octave_transpose);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_5)
	{
		// Gray White dial - zone 2 midi channel
		zone_2_midi_channel = update_rotary_encoder_value(
			zone_2_midi_channel,
			val,
			&prev_zone_2_midi_channel,
			0,
			15,
			1);

		ui->comboBox_KeyboardMapper_MidiChannelZone_2->setCurrentIndex(zone_2_midi_channel);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_6)
	{
		// Gray Yellow dial - zone 2 octave traspose
		zone_2_octave_transpose = update_rotary_encoder_value(
			zone_2_octave_transpose,
			val,
			&prev_zone_2_octave_transpose,
			0,
			12,
			1);

		ui->comboBox_KeyboardMapper_OctaveTransposeZone_2->setCurrentIndex(zone_2_octave_transpose);
	}
}


void Dialog_KeyboardMapper::on_dialog_close()
{
	close();
}

void Dialog_KeyboardMapper::on_octave_transpose_zone_1_combobox_changed(int val)
{
	ui->comboBox_KeyboardMapper_OctaveTransposeZone_1->blockSignals(true);
	ui->comboBox_KeyboardMapper_OctaveTransposeZone_1->setCurrentIndex(val);
	ui->comboBox_KeyboardMapper_OctaveTransposeZone_1->blockSignals(false);
	
	zone_1_octave_offset = val;
	mod_synth_set_keyboard_mapper_zone_octave_offset(0, zone_1_octave_offset);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_KeyboardMapper::on_midi_channel_zone_1_combobox_changed(int val)
{
	ui->comboBox_KeyboardMapper_MidiChannelZone_1->blockSignals(true);
	ui->comboBox_KeyboardMapper_MidiChannelZone_1->setCurrentIndex(val);
	ui->comboBox_KeyboardMapper_MidiChannelZone_1->blockSignals(false);
	
	zone_1_midi_channel = val;
	mod_synth_set_keyboard_mapper_zone_midi_channel(0, zone_1_midi_channel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_KeyboardMapper::on_octave_transpose_zone_2_combobox_changed(int val)
{
	ui->comboBox_KeyboardMapper_OctaveTransposeZone_2->blockSignals(true);
	ui->comboBox_KeyboardMapper_OctaveTransposeZone_2->setCurrentIndex(val);
	ui->comboBox_KeyboardMapper_OctaveTransposeZone_2->blockSignals(false);
	
	zone_2_octave_offset = val;
	mod_synth_set_keyboard_mapper_zone_octave_offset(1, zone_2_octave_offset);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_KeyboardMapper::on_midi_channel_zone_2_combobox_changed(int val)
{
	ui->comboBox_KeyboardMapper_MidiChannelZone_2->blockSignals(true);
	ui->comboBox_KeyboardMapper_MidiChannelZone_2->setCurrentIndex(val);
	ui->comboBox_KeyboardMapper_MidiChannelZone_2->blockSignals(false);
	
	zone_2_midi_channel = val;
	mod_synth_set_keyboard_mapper_zone_midi_channel(1, zone_2_midi_channel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_KeyboardMapper::on_split_point_note_dial_changed(int val)
{
	static int prev_val = -1;

	// Dont update dial position - used only for detecting changes
	//ui->dial_KeyboardMapper_SplitNote->blockSignals(true);
	//ui->dial_KeyboardMapper_SplitNote->setValue(val);
	//ui->dial_KeyboardMapper_SplitNote->blockSignals(false);

	if (val == prev_val)
	{
		return;
	}

	if (val > prev_val)
	{
		split_point_note++;
	}
	else
	{
		split_point_note--;
	}
	
	if (split_point_note < 0)
	{
		split_point_note = 0;
	}
	else if (split_point_note > 127)
	{
		split_point_note = 127;
	}

	prev_val = val;
	
	update_split_point_note_text();
	
	mod_synth_set_keyboard_mapper_split_point_note(split_point_note);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_KeyboardMapper::on_bypass_on_checkbox_changed(int state)
{
	ui->checkBox_KeyboardMapper_BypassOn->blockSignals(true);
	ui->checkBox_KeyboardMapper_BypassOn->setCheckState(static_cast<Qt::CheckState>(state));
	ui->checkBox_KeyboardMapper_BypassOn->blockSignals(false);
	
	bypass_on = (state == Qt::Checked);
	mod_synth_set_keyboard_mapper_bypass_on(state);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

// Add this helper function after the destructor
QString Dialog_KeyboardMapper::get_note_name(int midi_note)
{
	static const QStringList note_names = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

	int octave = (midi_note / 12) - 1; // MIDI note 60 = C4
	int note_index = midi_note % 12;

	return note_names[note_index] + QString::number(octave);
}

void Dialog_KeyboardMapper::update_split_point_note_text()
{
	QString note_name = get_note_name(split_point_note);
	ui->lineEdit_KeyboardMapper_SplitNote->setText(
		QString("%1 (%2)")
			.arg(split_point_note)
			.arg(note_name));
}

void Dialog_KeyboardMapper::update_gui()
{
	int val;
	bool bool_val;

	static int prev_zone_1_midi_chan = -1;
	static int prev_zone_2_midi_chan = -1;
	static int prev_zone_1_transpose = -1;
	static int prev_zone_2_transpose = -1;
	static int prev_split_tone = -1;
	static bool prev_bypass_on = false;

	val = mod_synth_get_keyboard_mapper_zone_midi_channel(0);
	if (val != prev_zone_1_midi_chan)
	{
		prev_zone_1_midi_chan = val;
		ui->comboBox_KeyboardMapper_MidiChannelZone_1->blockSignals(true);
		ui->comboBox_KeyboardMapper_MidiChannelZone_1->setCurrentIndex(val);
		ui->comboBox_KeyboardMapper_MidiChannelZone_1->blockSignals(false);
	}

	val = mod_synth_get_keyboard_mapper_zone_midi_channel(1);
	if (val != prev_zone_2_midi_chan)
	{
		prev_zone_2_midi_chan = val;
		ui->comboBox_KeyboardMapper_MidiChannelZone_2->blockSignals(true);
		ui->comboBox_KeyboardMapper_MidiChannelZone_2->setCurrentIndex(val);
		ui->comboBox_KeyboardMapper_MidiChannelZone_2->blockSignals(false);
	}

	val = mod_synth_get_keyboard_mapper_zone_octave_offset(0);
	if (val != prev_zone_1_transpose)
	{
		prev_zone_1_transpose = val;
		ui->comboBox_KeyboardMapper_OctaveTransposeZone_1->blockSignals(true);
		ui->comboBox_KeyboardMapper_OctaveTransposeZone_1->setCurrentIndex(val);
		ui->comboBox_KeyboardMapper_OctaveTransposeZone_1->blockSignals(false);
	}

	val = mod_synth_get_keyboard_mapper_zone_octave_offset(1);
	if (val != prev_zone_2_transpose)
	{
		prev_zone_2_transpose = val;
		ui->comboBox_KeyboardMapper_OctaveTransposeZone_2->blockSignals(true);
		ui->comboBox_KeyboardMapper_OctaveTransposeZone_2->setCurrentIndex(val);
		ui->comboBox_KeyboardMapper_OctaveTransposeZone_2->blockSignals(false);
	}

	val = mod_synth_get_keyboard_mapper_split_point_note();
	if (val != prev_split_tone)
	{
		prev_split_tone = val;
		// Dont update the dial value directly since it is used to detect changes only.
		//	ui->dial_KeyboardMapper_SplitNote->blockSignals(true);
		//	ui->dial_KeyboardMapper_SplitNote->setValue(val);
		//	ui->dial_KeyboardMapper_SplitNote->blockSignals(false);
		update_split_point_note_text();
	}

	bool_val = mod_synth_get_keyboard_mapper_bypass_on();
	if (bool_val != prev_bypass_on)
	{
		prev_bypass_on = bool_val;
		ui->checkBox_KeyboardMapper_BypassOn->blockSignals(true);
		ui->checkBox_KeyboardMapper_BypassOn->setCheckState(bool_val ? Qt::Checked : Qt::Unchecked);
		ui->checkBox_KeyboardMapper_BypassOn->blockSignals(false);
	}
}

void Dialog_KeyboardMapper::start_update_timer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update_gui()));
	timer->start(interval);
}

