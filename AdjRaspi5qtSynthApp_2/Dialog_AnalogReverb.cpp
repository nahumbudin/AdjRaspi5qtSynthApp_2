/**
 * @file		Dialog_AnalogReverb.cpp
 *	@author		Nahum Budin
 *	@date		9-Apr-2026
 *	@version	1.0
 *
 *	@brief		Analog Synthesizer Reverbration control dialog
 *
 *	@History:
 *
 *		Version 1.0	22-Aug-2024
 *
 */

#include <QTimer>

#include "Dialog_AnalogReverb.h"
#include "ui_Dialog_AnalogReverb.h"
#include "controlBox.h"
#include "utils.h"

#include "modSynthAPI.h"
#include "synthesizer.h"
#include "GuiNavigator.h"
#include "gui.h"

Dialog_AnalogReverb *Dialog_AnalogReverb::dialog_analog_reverb_instance = NULL;

void analog_reverb_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	Dialog_AnalogReverb *instance = Dialog_AnalogReverb::get_instance();
	if (instance != nullptr)
	{
		instance->control_box_event_received(evnt, val);
	}
}

Dialog_AnalogReverb::Dialog_AnalogReverb(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::Dialog_AnalogReverb)
{
	ui->setupUi(this);
	dialog_analog_reverb_instance = this;

	// Disable callback when hiding
	mod_synth_register_callback_control_box_event_update_ui(NULL);

	// Prevent dialog from being deleted when closed - only hide it
	setAttribute(Qt::WA_DeleteOnClose, false);

	close_event_callback_ptr = NULL;

	init_reverb_combboxes_and_labels();
	init_reverb_gui();

	QMap<int, QList<QString>> frames_per_tab;

	GuiNavigator *nav = GuiNavigator::get_instance();

	frames_per_tab[0] << "Analog Reverb";

	// Register dialog WITHOUT a tab widget (nullptr)
	nav->register_dialog(
		this,
		"Analog Reverb",
		nullptr, // No tab widget
		frames_per_tab);

	// Connect signal to slot with Qt::QueuedConnection for thread-safety
	// This ensures the slot runs in the GUI thread
	connect(this, &Dialog_AnalogReverb::control_box_event_signal,
			this, &Dialog_AnalogReverb::handle_control_box_event,
			Qt::QueuedConnection);

	mod_synth_register_callback_control_box_event_update_ui(
		&analog_reverb_control_box_event_update_ui_callback_wrapper);

	// Re-focus on the  dialog
	nav->focus_on_dialog(this);

	// start a periodic timer after this timeout -
	start_update_timer(250);
}

Dialog_AnalogReverb::~Dialog_AnalogReverb()
{
	// Disable callback during destruction
	mod_synth_register_callback_control_box_event_update_ui(NULL);

	dialog_analog_reverb_instance = nullptr;
	delete ui;
}

Dialog_AnalogReverb *Dialog_AnalogReverb::get_instance(QWidget *parent)
{
	if (dialog_analog_reverb_instance == NULL)
	{
		dialog_analog_reverb_instance = new Dialog_AnalogReverb(parent);
	}

	return dialog_analog_reverb_instance;
}

void Dialog_AnalogReverb::control_box_event_received(int evnt, uint16_t val)
{
	// Emit signal - Qt will queue it to run in GUI thread
	emit control_box_event_signal(evnt, val);
}

int Dialog_AnalogReverb::init_reverb_gui()
{
	int result = -1;

	init_reverb_combboxes_and_labels();

	ui->dial_ReverbRoomSize->setKnobColor(_KNOBS_COLOR);
	ui->dial_ReverbRoomSize->setCircleColor(_CONTROLS_COLOR_BLUE);

	ui->dial_ReverbDamp->setKnobColor(_KNOBS_COLOR);
	ui->dial_ReverbDamp->setCircleColor(_CONTROLS_COLOR_GREEN);

	ui->dial_ReverbWet->setKnobColor(_KNOBS_COLOR);
	ui->dial_ReverbWet->setCircleColor(_CONTROLS_COLOR_WHITE);

	ui->dial_ReverbDry->setKnobColor(_KNOBS_COLOR);
	ui->dial_ReverbDry->setCircleColor(_CONTROLS_COLOR_YELLOW);

	ui->dial_ReverbWidth->setKnobColor(_KNOBS_COLOR);
	ui->dial_ReverbWidth->setCircleColor(_CONTROLS_COLOR_RED);

	ui->dial_ReverbMode->setKnobColor(_KNOBS_COLOR);
	ui->dial_ReverbMode->setCircleColor(_CONTROLS_COLOR_BLACK);

	ui->comboBox_ReverbType->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_ReverbType->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->comboBox_ReverbType->setFrameWidth(2);
	ui->comboBox_ReverbType->setTextAlignment(Qt::AlignCenter);

	ui->checkBox_Reverbration3_Active->setLedStyle(true);
	ui->checkBox_Reverbration3_Active->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_Reverbration3_Active->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->checkBox_Reverbration3_Active->setBackgroundColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_Reverbration3_Active->setCheckBoxSize(16);
	ui->checkBox_Reverbration3_Active->setFrameWidth(2);

	ui->checkBox_Reverbration_Active->setLedStyle(true);
	ui->checkBox_Reverbration_Active->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_Reverbration_Active->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->checkBox_Reverbration_Active->setBackgroundColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_Reverbration_Active->setCheckBoxSize(16);
	ui->checkBox_Reverbration_Active->setFrameWidth(2);

	set_reverb_signals_connections();
	update_gui();

	return 0;
}

void Dialog_AnalogReverb::init_reverb_combboxes_and_labels()
{
	static bool one_time_initialized = false;

	string_reverb_types_list.append("Default");
	string_reverb_types_list.append("Small Hall 1");
	string_reverb_types_list.append("Small Hall 2");
	string_reverb_types_list.append("Medium Hall 1");
	string_reverb_types_list.append("Medium Hall 2");
	string_reverb_types_list.append("Large Hall 1");
	string_reverb_types_list.append("Large Hall 2");
	string_reverb_types_list.append("Small Room 1");
	string_reverb_types_list.append("Small Room 2");
	string_reverb_types_list.append("Medium Room 1");
	string_reverb_types_list.append("Medium Room 2");
	string_reverb_types_list.append("Large Room 1");
	string_reverb_types_list.append("Large Room 2");
	string_reverb_types_list.append("Medium R 1");
	string_reverb_types_list.append("Medium R 2");
	string_reverb_types_list.append("Plate High");
	string_reverb_types_list.append("Plate Low");
	string_reverb_types_list.append("Long Reverb 1");
	string_reverb_types_list.append("Long Reverb 2");

	if (!one_time_initialized)
	{
		one_time_initialized = true;

		ui->comboBox_ReverbType->blockSignals(true);
		ui->comboBox_ReverbType->addItems(string_reverb_types_list);
		ui->comboBox_ReverbType->blockSignals(false);
	}
}

void Dialog_AnalogReverb::set_reverb_signals_connections()
{
	connect(ui->checkBox_Reverbration_Active,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_reverb_enable_checkbox_changed(bool)));

	connect(ui->dial_ReverbRoomSize,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_room_size_dial_changed(int)));

	connect(ui->dial_ReverbDamp,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_damp_dial_changed(int)));

	connect(ui->dial_ReverbWet,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_wet_dial_changed(int)));

	connect(ui->dial_ReverbDry,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_dry_dial_changed(int)));

	connect(ui->dial_ReverbWidth,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_width_dial_changed(int)));

	connect(ui->dial_ReverbMode,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_mode_dial_changed(int)));

	connect(ui->spinBox_ReverbRoomSize,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_room_size_spinbox_changed(int)));

	connect(ui->spinBox_ReverbDamp,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_damp_spinbox_changed(int)));

	connect(ui->spinBox_ReverbWet,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_wet_spinbox_changed(int)));

	connect(ui->spinBox_ReverbDry,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_dry_spinbox_changed(int)));

	connect(ui->spinBox_ReverbWidth,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_width_spinbox_changed(int)));

	connect(ui->spinBox_ReverbMode,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_reverb_mode_spinbox_changed(int)));

	// Freeverb 3 Mod
	connect(ui->checkBox_Reverbration3_Active,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_reverb_3m_enable_checkbox_changed(bool)));

	connect(ui->comboBox_ReverbType,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_reverb_type_combobox_changed(int)));
}

void Dialog_AnalogReverb::update_gui()
{
	// Don't update if dialog is not visible
	if (!isVisible())
	{
		return;
	}
	
	ui->checkBox_Reverbration_Active->blockSignals(true);
	ui->checkBox_Reverbration_Active->setChecked(mod_synth_get_active_reverb_enable_state());
	ui->checkBox_Reverbration_Active->blockSignals(false);

	ui->dial_ReverbRoomSize->blockSignals(true);
	ui->dial_ReverbRoomSize->setValue(mod_synth_get_active_reverb_room_size());
	ui->dial_ReverbRoomSize->blockSignals(false);

	ui->dial_ReverbDamp->blockSignals(true);
	ui->dial_ReverbDamp->setValue(mod_synth_get_active_reverb_damp());
	ui->dial_ReverbDamp->blockSignals(false);

	ui->dial_ReverbWet->blockSignals(true);
	ui->dial_ReverbWet->setValue(mod_synth_get_active_reverb_wet());
	ui->dial_ReverbWet->blockSignals(false);

	ui->dial_ReverbDry->blockSignals(true);
	ui->dial_ReverbDry->setValue(mod_synth_get_active_reverb_dry());
	ui->dial_ReverbDry->blockSignals(false);

	ui->dial_ReverbWidth->blockSignals(true);
	ui->dial_ReverbWidth->setValue(mod_synth_get_active_reverb_width());
	ui->dial_ReverbWidth->blockSignals(false);

	ui->dial_ReverbMode->blockSignals(true);
	ui->dial_ReverbMode->setValue(mod_synth_get_active_reverb_mode());
	ui->dial_ReverbMode->blockSignals(false);

	ui->checkBox_Reverbration3_Active->blockSignals(true);
	ui->checkBox_Reverbration3_Active->setChecked(mod_synth_get_active_reverb_3m_enable_state());
	ui->checkBox_Reverbration3_Active->blockSignals(false);

	if (mod_synth_get_active_reverb_enable_state())
	{
		ui->frame_FreeVerb->setEnabled(true);
	}
	else
	{
		ui->frame_FreeVerb->setEnabled(false);
	}

	ui->comboBox_ReverbType->blockSignals(true);
	ui->comboBox_ReverbType->setCurrentIndex(mod_synth_get_active_reverb_3m_preset());
	ui->comboBox_ReverbType->blockSignals(false);
}

// Freeverb 3 modified
void Dialog_AnalogReverb::on_reverb_3m_enable_checkbox_changed(bool val)
{
	ui->checkBox_Reverbration3_Active->blockSignals(true);

	if (val)
	{
		ui->checkBox_Reverbration3_Active->setChecked(true);
		ui->frame_freeVerb3->setEnabled(true);
	}
	else
	{
		ui->checkBox_Reverbration3_Active->setChecked(false);
		ui->frame_freeVerb3->setEnabled(false);
	}

	ui->checkBox_Reverbration3_Active->blockSignals(false);

	mod_synth_reverb_event_bool(_REVERB_EVENT, _REVERB3M_ENABLE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogReverb::on_reverb_type_combobox_changed(int val)
{
	ui->comboBox_ReverbType->blockSignals(true);
	ui->comboBox_ReverbType->setCurrentIndex(val);
	ui->comboBox_ReverbType->blockSignals(false);

	mod_synth_reverb_event_int(_REVERB_EVENT, _REVERB_PRESET, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

// Freverb
void Dialog_AnalogReverb::on_reverb_enable_checkbox_changed(bool val)
{
	ui->checkBox_Reverbration_Active->blockSignals(true);

	if (val)
	{
		ui->checkBox_Reverbration_Active->setChecked(true);
		ui->frame_FreeVerb->setEnabled(true);
	}
	else
	{
		ui->checkBox_Reverbration_Active->setChecked(false);
		ui->frame_FreeVerb->setEnabled(false);
	}

	ui->checkBox_Reverbration_Active->blockSignals(false);

	mod_synth_reverb_event_bool(_REVERB_EVENT, _REVERB_ENABLE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogReverb::on_reverb_room_size_dial_changed(int val)
{
	ui->dial_ReverbRoomSize->blockSignals(true);
	ui->dial_ReverbRoomSize->setValue(val);
	ui->dial_ReverbRoomSize->blockSignals(false);

	ui->spinBox_ReverbRoomSize->blockSignals(true);
	ui->spinBox_ReverbRoomSize->setValue(val);
	ui->spinBox_ReverbRoomSize->blockSignals(false);

	mod_synth_reverb_event_int(_REVERB_EVENT, _REVERB_ROOM_SIZE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogReverb::on_reverb_damp_dial_changed(int val)
{
	ui->dial_ReverbDamp->blockSignals(true);
	ui->dial_ReverbDamp->setValue(val);
	ui->dial_ReverbDamp->blockSignals(false);

	ui->spinBox_ReverbDamp->blockSignals(true);
	ui->spinBox_ReverbDamp->setValue(val);
	ui->spinBox_ReverbDamp->blockSignals(false);

	mod_synth_reverb_event_int(_REVERB_EVENT, _REVERB_DAMP, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogReverb::on_reverb_wet_dial_changed(int val)
{
	ui->dial_ReverbWet->blockSignals(true);
	ui->dial_ReverbWet->setValue(val);
	ui->dial_ReverbWet->blockSignals(false);

	ui->spinBox_ReverbWet->blockSignals(true);
	ui->spinBox_ReverbWet->setValue(val);
	ui->spinBox_ReverbWet->blockSignals(false);

	mod_synth_reverb_event_int(_REVERB_EVENT, _REVERB_WET, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogReverb::on_reverb_dry_dial_changed(int val)
{
	ui->dial_ReverbDry->blockSignals(true);
	ui->dial_ReverbDry->setValue(val);
	ui->dial_ReverbDry->blockSignals(false);

	ui->spinBox_ReverbDry->blockSignals(true);
	ui->spinBox_ReverbDry->setValue(val);
	ui->spinBox_ReverbDry->blockSignals(false);

	mod_synth_reverb_event_int(_REVERB_EVENT, _REVERB_DRY, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogReverb::on_reverb_width_dial_changed(int val)
{
	ui->dial_ReverbWidth->blockSignals(true);
	ui->dial_ReverbWidth->setValue(val);
	ui->dial_ReverbWidth->blockSignals(false);

	ui->spinBox_ReverbWidth->blockSignals(true);
	ui->spinBox_ReverbWidth->setValue(val);
	ui->spinBox_ReverbWidth->blockSignals(false);

	mod_synth_reverb_event_int(_REVERB_EVENT, _REVERB_WIDTH, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogReverb::on_reverb_mode_dial_changed(int val)
{
	ui->dial_ReverbMode->blockSignals(true);
	ui->dial_ReverbMode->setValue(val);
	ui->dial_ReverbMode->blockSignals(false);

	ui->spinBox_ReverbMode->blockSignals(true);
	ui->spinBox_ReverbMode->setValue(val);
	ui->spinBox_ReverbMode->blockSignals(false);

	mod_synth_reverb_event_int(_REVERB_EVENT, _REVERB_MODE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogReverb::on_reverb_room_size_spinbox_changed(int val)
{
	ui->dial_ReverbRoomSize->blockSignals(true);
	ui->dial_ReverbRoomSize->setValue(val);
	ui->dial_ReverbRoomSize->blockSignals(false);

	ui->spinBox_ReverbRoomSize->blockSignals(true);
	ui->spinBox_ReverbRoomSize->setValue(val);
	ui->spinBox_ReverbRoomSize->blockSignals(false);

	mod_synth_reverb_event_int(_REVERB_EVENT, _REVERB_ROOM_SIZE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogReverb::on_reverb_damp_spinbox_changed(int val)
{
	on_reverb_damp_dial_changed(val);
}

void Dialog_AnalogReverb::on_reverb_wet_spinbox_changed(int val)
{
	on_reverb_wet_dial_changed(val);
}

void Dialog_AnalogReverb::on_reverb_dry_spinbox_changed(int val)
{
	on_reverb_dry_dial_changed(val);
}

void Dialog_AnalogReverb::on_reverb_width_spinbox_changed(int val)
{
	on_reverb_width_dial_changed(val);
}

void Dialog_AnalogReverb::on_reverb_mode_spinbox_changed(int val)
{
	on_reverb_mode_dial_changed(val);
}

void Dialog_AnalogReverb::closeEvent(QCloseEvent *event)
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

void Dialog_AnalogReverb::showEvent(QShowEvent *event)
{
	QDialog::showEvent(event);

	// Re-register callback when showing
	mod_synth_register_callback_control_box_event_update_ui(
		&analog_reverb_control_box_event_update_ui_callback_wrapper);
}

void Dialog_AnalogReverb::on_dialog_close()
{
	hide();
}

void Dialog_AnalogReverb::start_update_timer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update_gui()));
	timer->start(interval);
}

void Dialog_AnalogReverb::timerEvent(QTimerEvent *event)
{
	killTimer(event->timerId());
	start_update_timer(250);
}

void Dialog_AnalogReverb::handle_control_box_event(int evnt, uint16_t val)
{
	if (!this->hasFocus())
	{
		return;
	}

	const int reverb_preset_max = _REVERB_PRESET_LONG_REVERB_2;
	const int reverb_preset_min = _REVERB_PRESET_DEFAULT;
	const int reverb_room_size_max = 98;
	const int reverb_room_size_min = 10;
	const int reverb_control_max = 100;
	const int reverb_control_min = 0;
	const int reverb_width_min = 1;
	const int reverb_mode_max = 50;

	static int reverb_preset = _REVERB_PRESET_DEFAULT;
	static int reverb_room_size = 0;
	static int reverb_damping = 0;
	static int reverb_wet = 0;
	static int reverb_dry = 0;
	static int reverb_width = 0;
	static int reverb_mode = 0;

	static int prev_reverb_preset = _REVERB_PRESET_DEFAULT;
	static int prev_reverb_room_size = 0;
	static int prev_reverb_damping = 0;
	static int prev_reverb_wet = 0;
	static int prev_reverb_dry = 0;
	static int prev_reverb_width = 0;
	static int prev_reverb_mode = 0;

	// Reverb (controls 1-8)
	if (evnt == _I2C_CONTROL_ENCODER_2)
	{
		if (val == 4096)
		{
			// Gray Blue pushbutton - Reverb enable control
			on_reverb_3m_enable_checkbox_changed(!ui->checkBox_Reverbration3_Active->isChecked());
		}
		else
		{
			// Gray Purple combobox - Reverb 3 type control
			reverb_preset = update_rotary_encoder_value(
				reverb_preset,
				val,
				&prev_reverb_preset,
				reverb_preset_min,
				reverb_preset_max,
				1);

			ui->comboBox_ReverbType->setCurrentIndex(reverb_preset);
		}
	}
	else if (evnt == _I2C_CONTROL_ENCODER_3)
	{
		if (val == 4096)
		{
			// Gray Blue pushbutton - Reverb enable control
			on_reverb_enable_checkbox_changed(!ui->checkBox_Reverbration_Active->isChecked());
		}
		else
		{
			// Gray Blue dial - Reverb room size control
			reverb_room_size = update_rotary_encoder_value(
				reverb_room_size,
				val,
				&prev_reverb_room_size,
				reverb_room_size_min,
				reverb_room_size_max,
				4);

			ui->dial_ReverbRoomSize->setValue(reverb_room_size);
		}
	}
	else if (evnt == _I2C_CONTROL_ENCODER_4)
	{
		// Gray Green dial - Reverb damp control
		reverb_damping = update_rotary_encoder_value(
			reverb_damping,
			val,
			&prev_reverb_damping,
			reverb_control_min,
			reverb_control_max,
			4);

		ui->dial_ReverbDamp->setValue(reverb_damping);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_5)
	{
		// Gray White dial - Reverb wet control
		reverb_wet = update_rotary_encoder_value(
			reverb_wet,
			val,
			&prev_reverb_wet,
			reverb_control_min,
			reverb_control_max,
			4);

		ui->dial_ReverbWet->setValue(reverb_wet);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_6)
	{
		// Gray Yellow combobox - Reverb dry control
		reverb_dry = update_rotary_encoder_value(
			reverb_dry,
			val,
			&prev_reverb_dry,
			reverb_control_min,
			reverb_control_max,
			4);

		ui->dial_ReverbDry->setValue(reverb_dry);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_7)
	{
		// Gray Red combobox - Reverb width control
		reverb_width = update_rotary_encoder_value(
			reverb_width,
			val,
			&prev_reverb_width,
			reverb_width_min,
			reverb_control_max,
			4);

		ui->dial_ReverbWidth->setValue(reverb_width);
	}
	else if (evnt == _I2C_CONTROL_ENCODER_8)
	{
		// Gray Black dial - Reverb mode control
		reverb_mode = update_rotary_encoder_value(
			reverb_mode,
			val,
			&prev_reverb_mode,
			reverb_control_min,
			reverb_mode_max,
			4);

		ui->dial_ReverbMode->setValue(reverb_mode);
	}
}
