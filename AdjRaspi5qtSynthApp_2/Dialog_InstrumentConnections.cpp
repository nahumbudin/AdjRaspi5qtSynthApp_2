/**
 * @file		Dialog_InstrumentConnections.cpp
 *	@author		Nahum Budin
 *	@date		15-Jul-2026
 *	@version	1.1
 *					1. Expanding the number of MIDI and Jack clients to 20.
 *
 *	@brief		Used for selecting MIDI inputs and JackAudio outputs,
 *				as well as the active MIDI channels
 *
 *	@History
 *			version 1.0	5-Jul-2024	Initial version
 *
 */

#include <time.h>

#include <QString>
#include <QThread>

#include "libAdjRaspi5SynthAPI.h"

#include "Dialog_InstrumentConnections.h"
#include "ui_Dialog_InstrumentConnections.h"

#include "utils.h"

/* Used as a mutex to enable only a single oppened dialog. */
bool Dialog_InstrumentConnections::dialog_is_open;


void connections_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	// Just forward to the dialog instance - it will emit a signal
	Dialog_InstrumentConnections::get_instance()->control_box_event_received(evnt, val);
}

Dialog_InstrumentConnections *Dialog_InstrumentConnections::dialog_InstrumentConnectionsInstance = NULL;

/** Constructor */
Dialog_InstrumentConnections::Dialog_InstrumentConnections(
	QWidget *parent, 
	QString inst_name)
	: QDialog(parent)
	, ui(new Ui::Dialog_InstrumentConnections)
{
	ui->setupUi(this);
	dialog_InstrumentConnectionsInstance = this;

	// Prevent dialog from being deleted when closed - only hide it
	setAttribute(Qt::WA_DeleteOnClose, false);
	
	this->setFocus(Qt::ActiveWindowFocusReason);
	
	instrument_name = inst_name;
	
	midi_input_clients_select_pb[0] = ui->checkBox_source_1;
	midi_input_clients_select_pb[1] = ui->checkBox_source_2;
	midi_input_clients_select_pb[2] = ui->checkBox_source_3;
	midi_input_clients_select_pb[3] = ui->checkBox_source_4;
	midi_input_clients_select_pb[4] = ui->checkBox_source_5;
	midi_input_clients_select_pb[5] = ui->checkBox_source_6;
	midi_input_clients_select_pb[6] = ui->checkBox_source_7;
	midi_input_clients_select_pb[7] = ui->checkBox_source_8;
	midi_input_clients_select_pb[8] = ui->checkBox_source_9;
	midi_input_clients_select_pb[9] = ui->checkBox_source_10;
	midi_input_clients_select_pb[10] = ui->checkBox_source_11;
	midi_input_clients_select_pb[11] = ui->checkBox_source_12;
	midi_input_clients_select_pb[12] = ui->checkBox_source_13;
	midi_input_clients_select_pb[13] = ui->checkBox_source_14;
	midi_input_clients_select_pb[14] = ui->checkBox_source_15;
	midi_input_clients_select_pb[15] = ui->checkBox_source_16;
	midi_input_clients_select_pb[16] = ui->checkBox_source_17;
	midi_input_clients_select_pb[17] = ui->checkBox_source_18;
	midi_input_clients_select_pb[18] = ui->checkBox_source_19;
	midi_input_clients_select_pb[19] = ui->checkBox_source_20;
	
	jack_output_clients_select_pb[0] = ui->checkBox_JackOut_1;
	jack_output_clients_select_pb[1] = ui->checkBox_JackOut_2;
	jack_output_clients_select_pb[2] = ui->checkBox_JackOut_3;
	jack_output_clients_select_pb[3] = ui->checkBox_JackOut_4;
	jack_output_clients_select_pb[4] = ui->checkBox_JackOut_5;
	jack_output_clients_select_pb[5] = ui->checkBox_JackOut_6;
	jack_output_clients_select_pb[6] = ui->checkBox_JackOut_7;
	jack_output_clients_select_pb[7] = ui->checkBox_JackOut_8;
	jack_output_clients_select_pb[8] = ui->checkBox_JackOut_9;
	jack_output_clients_select_pb[9] = ui->checkBox_JackOut_10;
	jack_output_clients_select_pb[10] = ui->checkBox_JackOut_11;
	jack_output_clients_select_pb[11] = ui->checkBox_JackOut_12;
	jack_output_clients_select_pb[12] = ui->checkBox_JackOut_13;
	jack_output_clients_select_pb[13] = ui->checkBox_JackOut_14;
	jack_output_clients_select_pb[14] = ui->checkBox_JackOut_15;
	jack_output_clients_select_pb[15] = ui->checkBox_JackOut_16;
	jack_output_clients_select_pb[16] = ui->checkBox_JackOut_17;
	jack_output_clients_select_pb[17] = ui->checkBox_JackOut_18;
	jack_output_clients_select_pb[18] = ui->checkBox_JackOut_19;
	jack_output_clients_select_pb[19] = ui->checkBox_JackOut_20;

	// Connect signal to slot with Qt::QueuedConnection for thread-safety
	// This ensures the slot runs in the GUI thread
	connect(this, &Dialog_InstrumentConnections::control_box_event_signal,
			this, &Dialog_InstrumentConnections::handle_control_box_event,
			Qt::QueuedConnection);

	// Register control box event callback
	mod_synth_register_callback_control_box_event_update_ui(
		&connections_control_box_event_update_ui_callback_wrapper);
	
	this->ui->label_InstrumentName->setText(instrument_name);
	
	selected_pannel = _MIDI_PANNEL_SELECTED;
	ui->frame_MIDI->setFrameShadow(QFrame::Sunken);
	ui->frame_MIDI->setLineWidth(5);
	ui->frame_MIDI->setMidLineWidth(5);	
	ui->frame_Jack->setFrameShadow(QFrame::Plain);
	ui->frame_Jack->setLineWidth(0);
	ui->frame_Jack->setMidLineWidth(0);
	ui->radioButton_MIDI->setChecked(true);
	ui->radioButton_Jack->setChecked(false);
	
	ui->checkBox_source_1->setReadOnly(false);
	ui->checkBox_source_1->setLedStyle(true);
	ui->checkBox_source_1->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_1->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_1->setFrameColor(_CONTROLS_COLOR_GRAY);

	ui->checkBox_source_2->setReadOnly(false);
	ui->checkBox_source_2->setLedStyle(true);
	ui->checkBox_source_2->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_2->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_2->setFrameColor(_CONTROLS_COLOR_PURPLE);

	ui->checkBox_source_3->setReadOnly(false);
	ui->checkBox_source_3->setLedStyle(true);
	ui->checkBox_source_3->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_3->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_3->setFrameColor(_CONTROLS_COLOR_BLUE);

	ui->checkBox_source_4->setReadOnly(false);
	ui->checkBox_source_4->setLedStyle(true);
	ui->checkBox_source_4->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_4->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_4->setFrameColor(_CONTROLS_COLOR_GREEN);

	ui->checkBox_source_5->setReadOnly(false);
	ui->checkBox_source_5->setLedStyle(true);
	ui->checkBox_source_5->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_5->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_5->setFrameColor(_CONTROLS_COLOR_WHITE);

	ui->checkBox_source_6->setReadOnly(false);
	ui->checkBox_source_6->setLedStyle(true);
	ui->checkBox_source_6->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_6->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_6->setFrameColor(_CONTROLS_COLOR_YELLOW);

	ui->checkBox_source_7->setReadOnly(false);
	ui->checkBox_source_7->setLedStyle(true);
	ui->checkBox_source_7->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_7->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_7->setFrameColor(_CONTROLS_COLOR_RED);

	ui->checkBox_source_8->setReadOnly(false);
	ui->checkBox_source_8->setLedStyle(true);
	ui->checkBox_source_8->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_8->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_8->setFrameColor(_CONTROLS_COLOR_BLACK);

	ui->checkBox_source_9->setReadOnly(false);
	ui->checkBox_source_9->setLedStyle(true);
	ui->checkBox_source_9->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_9->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_9->setFrameColor(_CONTROLS_COLOR_DARK_GRAY);

	ui->checkBox_source_10->setReadOnly(false);
	ui->checkBox_source_10->setLedStyle(true);
	ui->checkBox_source_10->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_10->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_10->setFrameColor(_CONTROLS_COLOR_DARK_GRAY);

	ui->checkBox_source_11->setReadOnly(false);
	ui->checkBox_source_11->setLedStyle(true);
	ui->checkBox_source_11->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_11->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_11->setFrameColor(_CONTROLS_COLOR_GRAY);

	ui->checkBox_source_12->setReadOnly(false);
	ui->checkBox_source_12->setLedStyle(true);
	ui->checkBox_source_12->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_12->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_12->setFrameColor(_CONTROLS_COLOR_PURPLE);

	ui->checkBox_source_13->setReadOnly(false);
	ui->checkBox_source_13->setLedStyle(true);
	ui->checkBox_source_13->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_13->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_13->setFrameColor(_CONTROLS_COLOR_BLUE);

	ui->checkBox_source_14->setReadOnly(false);
	ui->checkBox_source_14->setLedStyle(true);
	ui->checkBox_source_14->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_14->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_14->setFrameColor(_CONTROLS_COLOR_GREEN);

	ui->checkBox_source_15->setReadOnly(false);
	ui->checkBox_source_15->setLedStyle(true);
	ui->checkBox_source_15->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_15->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_15->setFrameColor(_CONTROLS_COLOR_WHITE);

	ui->checkBox_source_16->setReadOnly(false);
	ui->checkBox_source_16->setLedStyle(true);
	ui->checkBox_source_16->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_16->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_16->setFrameColor(_CONTROLS_COLOR_YELLOW);

	ui->checkBox_source_17->setReadOnly(false);
	ui->checkBox_source_17->setLedStyle(true);
	ui->checkBox_source_17->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_17->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_17->setFrameColor(_CONTROLS_COLOR_RED);

	ui->checkBox_source_18->setReadOnly(false);
	ui->checkBox_source_18->setLedStyle(true);
	ui->checkBox_source_18->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_18->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_18->setFrameColor(_CONTROLS_COLOR_BLACK);

	ui->checkBox_source_19->setReadOnly(false);
	ui->checkBox_source_19->setLedStyle(true);
	ui->checkBox_source_19->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_19->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_19->setFrameColor(_CONTROLS_COLOR_DARK_GRAY);

	ui->checkBox_source_20->setReadOnly(false);
	ui->checkBox_source_20->setLedStyle(true);
	ui->checkBox_source_20->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_source_20->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_source_20->setFrameColor(_CONTROLS_COLOR_DARK_GRAY);
	
	
	ui->checkBox_JackOut_1->setReadOnly(false);
	ui->checkBox_JackOut_1->setLedStyle(true);
	ui->checkBox_JackOut_1->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_1->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_1->setFrameColor(_CONTROLS_COLOR_GRAY);

	ui->checkBox_JackOut_2->setReadOnly(false);
	ui->checkBox_JackOut_2->setLedStyle(true);
	ui->checkBox_JackOut_2->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_2->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_2->setFrameColor(_CONTROLS_COLOR_PURPLE);

	ui->checkBox_JackOut_3->setReadOnly(false);
	ui->checkBox_JackOut_3->setLedStyle(true);
	ui->checkBox_JackOut_3->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_3->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_3->setFrameColor(_CONTROLS_COLOR_BLUE);

	ui->checkBox_JackOut_4->setReadOnly(false);
	ui->checkBox_JackOut_4->setLedStyle(true);
	ui->checkBox_JackOut_4->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_4->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_4->setFrameColor(_CONTROLS_COLOR_GREEN);

	ui->checkBox_JackOut_5->setReadOnly(false);
	ui->checkBox_JackOut_5->setLedStyle(true);
	ui->checkBox_JackOut_5->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_5->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_5->setFrameColor(_CONTROLS_COLOR_WHITE);

	ui->checkBox_JackOut_6->setReadOnly(false);
	ui->checkBox_JackOut_6->setLedStyle(true);
	ui->checkBox_JackOut_6->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_6->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_6->setFrameColor(_CONTROLS_COLOR_YELLOW);

	ui->checkBox_JackOut_7->setReadOnly(false);
	ui->checkBox_JackOut_7->setLedStyle(true);
	ui->checkBox_JackOut_7->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_7->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_7->setFrameColor(_CONTROLS_COLOR_RED);

	ui->checkBox_JackOut_8->setReadOnly(false);
	ui->checkBox_JackOut_8->setLedStyle(true);
	ui->checkBox_JackOut_8->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_8->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_8->setFrameColor(_CONTROLS_COLOR_BLACK);

	ui->checkBox_JackOut_9->setReadOnly(false);
	ui->checkBox_JackOut_9->setLedStyle(true);
	ui->checkBox_JackOut_9->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_9->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_9->setFrameColor(_CONTROLS_COLOR_DARK_GRAY);

	ui->checkBox_JackOut_10->setReadOnly(false);
	ui->checkBox_JackOut_10->setLedStyle(true);
	ui->checkBox_JackOut_10->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_10->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_10->setFrameColor(_CONTROLS_COLOR_DARK_GRAY);

	ui->checkBox_JackOut_11->setReadOnly(false);
	ui->checkBox_JackOut_11->setLedStyle(true);
	ui->checkBox_JackOut_11->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_11->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_11->setFrameColor(_CONTROLS_COLOR_GRAY);

	ui->checkBox_JackOut_12->setReadOnly(false);
	ui->checkBox_JackOut_12->setLedStyle(true);
	ui->checkBox_JackOut_12->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_12->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_12->setFrameColor(_CONTROLS_COLOR_PURPLE);

	ui->checkBox_JackOut_13->setReadOnly(false);
	ui->checkBox_JackOut_13->setLedStyle(true);
	ui->checkBox_JackOut_13->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_13->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_13->setFrameColor(_CONTROLS_COLOR_BLUE);

	ui->checkBox_JackOut_14->setReadOnly(false);
	ui->checkBox_JackOut_14->setLedStyle(true);
	ui->checkBox_JackOut_14->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_14->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_14->setFrameColor(_CONTROLS_COLOR_GREEN);

	ui->checkBox_JackOut_15->setReadOnly(false);
	ui->checkBox_JackOut_15->setLedStyle(true);
	ui->checkBox_JackOut_15->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_15->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_15->setFrameColor(_CONTROLS_COLOR_WHITE);

	ui->checkBox_JackOut_16->setReadOnly(false);
	ui->checkBox_JackOut_16->setLedStyle(true);
	ui->checkBox_JackOut_16->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_16->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_16->setFrameColor(_CONTROLS_COLOR_YELLOW);

	ui->checkBox_JackOut_17->setReadOnly(false);
	ui->checkBox_JackOut_17->setLedStyle(true);
	ui->checkBox_JackOut_17->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_17->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_17->setFrameColor(_CONTROLS_COLOR_RED);

	ui->checkBox_JackOut_18->setReadOnly(false);
	ui->checkBox_JackOut_18->setLedStyle(true);
	ui->checkBox_JackOut_18->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_18->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_18->setFrameColor(_CONTROLS_COLOR_BLACK);

	ui->checkBox_JackOut_19->setReadOnly(false);
	ui->checkBox_JackOut_19->setLedStyle(true);
	ui->checkBox_JackOut_19->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_19->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_19->setFrameColor(_CONTROLS_COLOR_DARK_GRAY);

	ui->checkBox_JackOut_20->setReadOnly(false);
	ui->checkBox_JackOut_20->setLedStyle(true);
	ui->checkBox_JackOut_20->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_JackOut_20->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_JackOut_20->setFrameColor(_CONTROLS_COLOR_DARK_GRAY);
	

	update();
	
	connect(ui->pushButton_Ok,
		SIGNAL(clicked()),
		this,
		SLOT(on_dialog_ok()));
	
	connect(ui->pushButton_Refresh,
		SIGNAL(clicked()),
		this,
		SLOT(on_dialog_refresh()));
	
	connect(ui->radioButton_MIDI,
		SIGNAL(clicked()),
		this,
		SLOT(on_select_MIDI_pannel_clicked()));
	
	connect(ui->radioButton_Jack,
		SIGNAL(clicked()),
		this,
		SLOT(on_select_Jack_pannel_clicked()));
	
	connect(ui->checkBox_source_1,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_1(bool)));
	
	connect(ui->checkBox_source_2,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_2(bool)));
	
	connect(ui->checkBox_source_3,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_3(bool)));
	
	connect(ui->checkBox_source_4,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_4(bool)));
	
	connect(ui->checkBox_source_5,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_5(bool)));
	
	connect(ui->checkBox_source_6,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_6(bool)));
	
	connect(ui->checkBox_source_7,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_7(bool)));
	
	connect(ui->checkBox_source_8,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_8(bool)));
	
	connect(ui->checkBox_source_9,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_9(bool)));
	
	connect(ui->checkBox_source_10,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_10(bool)));
	
	connect(ui->checkBox_source_11,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_11(bool)));
	
	connect(ui->checkBox_source_12,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_12(bool)));

	connect(ui->checkBox_source_13,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_select_midi_in_toggled_13(bool)));

	connect(ui->checkBox_source_14,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_select_midi_in_toggled_14(bool)));

	connect(ui->checkBox_source_15,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_select_midi_in_toggled_15(bool)));

	connect(ui->checkBox_source_16,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_select_midi_in_toggled_16(bool)));

	connect(ui->checkBox_source_17,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_select_midi_in_toggled_17(bool)));

	connect(ui->checkBox_source_18,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_select_midi_in_toggled_18(bool)));

	connect(ui->checkBox_source_19,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_select_midi_in_toggled_19(bool)));

	connect(ui->checkBox_source_20,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_select_midi_in_toggled_20(bool)));
	
	
	connect(ui->checkBox_JackOut_1,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_1(bool)));
	
	connect(ui->checkBox_JackOut_2,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_2(bool)));
	
	connect(ui->checkBox_JackOut_3,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_3(bool)));
	
	connect(ui->checkBox_JackOut_4,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_4(bool)));
	
	connect(ui->checkBox_JackOut_5,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_5(bool)));
	
	connect(ui->checkBox_JackOut_6,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_6(bool)));
	
	connect(ui->checkBox_JackOut_7,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_7(bool)));
	
	connect(ui->checkBox_JackOut_8,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_8(bool)));
	
	connect(ui->checkBox_JackOut_9,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_9(bool)));
	
	connect(ui->checkBox_JackOut_10,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_10(bool)));
	
	connect(ui->checkBox_JackOut_11,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_11(bool)));
	
	connect(ui->checkBox_JackOut_12,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_12(bool)));

	connect(ui->checkBox_JackOut_13,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_select_jack_out_toggled_13(bool)));
	
	connect(ui->checkBox_JackOut_14,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_select_jack_out_toggled_14(bool)));

	connect(ui->checkBox_JackOut_15,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_select_jack_out_toggled_15(bool)));

	connect(ui->checkBox_JackOut_16,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_select_jack_out_toggled_16(bool)));

	connect(ui->checkBox_JackOut_17,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_select_jack_out_toggled_17(bool)));

	connect(ui->checkBox_JackOut_18,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_select_jack_out_toggled_18(bool)));

	connect(ui->checkBox_JackOut_19,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_select_jack_out_toggled_19(bool)));

	connect(ui->checkBox_JackOut_20,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_select_jack_out_toggled_20(bool)));

	MainWindow::get_instance()->register_active_dialog(this);
}

Dialog_InstrumentConnections::~Dialog_InstrumentConnections()
{
	// Disable callback during destruction
	mod_synth_register_callback_control_box_event_update_ui(NULL);

	dialog_InstrumentConnectionsInstance = nullptr;
	delete ui;
}

Dialog_InstrumentConnections *Dialog_InstrumentConnections::get_instance()
{	
	return dialog_InstrumentConnectionsInstance;
}

// Thread-safe function called from callback - just emits signal
void Dialog_InstrumentConnections::control_box_event_received(int evnt, uint16_t val)
{
	// Emit signal - Qt will queue it to run in GUI thread
	emit control_box_event_signal(evnt, val);
}

void Dialog_InstrumentConnections::closeEvent(QCloseEvent *event)
{
	// Disable callback when hiding
	mod_synth_register_callback_control_box_event_update_ui(NULL);
	
	MainWindow::get_instance()->unregister_active_dialog(this);
	dialog_is_open = false;
	hide();
}

void Dialog_InstrumentConnections::showEvent(QShowEvent *event)
{
	QDialog::showEvent(event);

	// Re-register callback when showing
	mod_synth_register_callback_control_box_event_update_ui(
		&connections_control_box_event_update_ui_callback_wrapper);
}

void Dialog_InstrumentConnections::handle_control_box_event(int evnt, uint16_t val)
{
	// Currently ignore. Update this function to handle control box events if needed and 6->10 

	return;

	int pb_num;
	int selected;
	
	if (!this->hasFocus())
	{
		return;
	}
	
	// TODO: update to support I2C control box events.
	if ((evnt >= _CONTROL_PUSHBUTTON_BLUE_BLACK) &&
		(evnt <= _CONTROL_PUSHBUTTON_ORANGE_YELLOW) &&
		(val == 0))
	{
		/* Pushbuttons pressed event */
		pb_num = evnt - _CONTROL_PUSHBUTTON_BLUE_BLACK;
		
		if (selected_pannel == _MIDI_PANNEL_SELECTED)
		{
			/* MIDI inputs selection */
			switch (pb_num)
			{
			case 0:
				if (!midi_input_clients_select_pb[0]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[0]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[0]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_1(false);
				}
				else
				{
					midi_input_clients_select_pb[0]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_1(true);
				}
				
				break;
				
			case 1:
				if (!midi_input_clients_select_pb[1]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[1]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[1]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_2(false);
				}
				else
				{
					midi_input_clients_select_pb[1]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_2(true);
				}
					
				break;
				
			case 2:
				if (!midi_input_clients_select_pb[2]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[2]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[2]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_3(false);
				}
				else
				{
					midi_input_clients_select_pb[2]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_3(true);
				}
					
				break;
				
			case 3:
				if (!midi_input_clients_select_pb[3]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[3]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[3]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_4(false);
				}
				else
				{
					midi_input_clients_select_pb[3]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_4(true);
				}
					
				break;
				
			case 4:
				if (!midi_input_clients_select_pb[4]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[4]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[4]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_5(false);
				}
				else
				{
					midi_input_clients_select_pb[4]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_5(true);
				}
					
				break;
				
			case 5:
				if (!midi_input_clients_select_pb[5]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[5]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[5]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_6(false);
				}
				else
				{
					midi_input_clients_select_pb[5]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_6(true);
				}
					
				break;
				
			case 6:
				if (!midi_input_clients_select_pb[6]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[6]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[6]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_7(false);
				}
				else
				{
					midi_input_clients_select_pb[6]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_7(true);
				}
					
				break;
				
			case 7:
				if (!midi_input_clients_select_pb[7]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[7]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[7]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_8(false);
				}
				else
				{
					midi_input_clients_select_pb[7]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_8(true);
				}
					
				break;
				
			case 8:
				if (!midi_input_clients_select_pb[8]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[8]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[8]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_9(false);
				}
				else
				{
					midi_input_clients_select_pb[8]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_9(true);
				}
					
				break;
				
			case 9:
				if (!midi_input_clients_select_pb[9]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[9]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[9]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_10(false);
				}
				else
				{
					midi_input_clients_select_pb[9]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_10(true);
				}
					
				break;
				
			case 10:
				if (!midi_input_clients_select_pb[10]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[10]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[10]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_11(false);
				}
				else
				{
					midi_input_clients_select_pb[10]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_11(true);
				}
					
				break;
				
			case 11:
				if (!midi_input_clients_select_pb[11]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[11]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[11]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_12(false);
				}
				else
				{
					midi_input_clients_select_pb[11]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_12(true);
				}
					
				break;
				
			}
		
			
		}
		else if (selected_pannel == _JACK_PANNEL_SELECTED)
		{
			/* Jack outputs selection */
			switch (pb_num)
			{
				case 0:
					if (!jack_output_clients_select_pb[0]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[0]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[0]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_1(false);
					}
					else
					{
						jack_output_clients_select_pb[0]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_1(true);
					}
					
					break;
				
				case 1:
					if (!jack_output_clients_select_pb[1]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[1]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[1]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_2(false);
					}
					else
					{
						jack_output_clients_select_pb[1]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_2(true);
					}
						
					break;
				
				case 2:
					if (!jack_output_clients_select_pb[2]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[2]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[2]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_3(false);
					}
					else
					{
						jack_output_clients_select_pb[2]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_3(true);
					}
						
					break;
				
				case 3:
					if (!jack_output_clients_select_pb[3]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[3]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[3]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_4(false);
					}
					else
					{
						jack_output_clients_select_pb[3]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_4(true);
					}
						
					break;
				
				case 4:
					if (!jack_output_clients_select_pb[4]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[4]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[4]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_5(false);
					}
					else
					{
						jack_output_clients_select_pb[4]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_5(true);
					}
							
					break;
				
				case 5:
					if (!jack_output_clients_select_pb[5]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[5]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[5]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_6(false);
					}
					else
					{
						jack_output_clients_select_pb[5]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_6(true);
					}
						
					break;
				
				case 6:
					if (!jack_output_clients_select_pb[6]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[6]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[6]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_7(false);
					}
					else
					{
						jack_output_clients_select_pb[6]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_7(true);
					}
							
					break;
				
				case 7:
					if (!jack_output_clients_select_pb[7]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[7]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[7]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_8(false);
					}
					else
					{
						jack_output_clients_select_pb[7]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_8(true);
					}
						
					break;
				
				case 8:
					if (!jack_output_clients_select_pb[8]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[8]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[8]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_9(false);
					}
					else
					{
						jack_output_clients_select_pb[8]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_9(true);
					}
							
					break;
				
				case 9:
					if (!jack_output_clients_select_pb[9]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[9]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[9]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_10(false);
					}
					else
					{
						jack_output_clients_select_pb[9]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_10(true);
					}
						
					break;
				
				case 10:
					if (!jack_output_clients_select_pb[10]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[10]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[10]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_11(false);
					}
					else
					{
						jack_output_clients_select_pb[10]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_11(true);
					}
						
					break;
				
				case 11:
					if (!jack_output_clients_select_pb[11]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[11]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[11]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_12(false);
					}
					else
					{
						jack_output_clients_select_pb[11]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_12(true);
					}
						
					break;
			}
		}
	}
	else if ((evnt == _CONTROL_FUNCTION_PUSHBUTTON_UP) &&
			 (val == 0))
	{
		/* Toggle selected pannel */
		if (selected_pannel == _MIDI_PANNEL_SELECTED)
		{
			on_select_Jack_pannel_clicked();			
		}
		else
		{
			on_select_MIDI_pannel_clicked();
		}
		
		/* Avoid fast switching ???*/
		QThread::msleep(1500);
		
	}
	else if ((evnt == _CONTROL_FUNCTION_PUSHBUTTON_ENTER) &&
			 (val == 0))
	{
		/* Close the dialog */
		on_dialog_ok();
	}
	
}

void Dialog_InstrumentConnections::update()
{	
	int cln;
	std::string cln_name, port_name, input_name;
	int num_of_alsa_input_clients, connection_number;
	int num_of_jack_input_clients;
	int num_of_connected_jack_input_clients_left, num_of_connected_jack_input_clients_right;
	int num_of_ports, port, input_ports_count;
	std::list<std::string> connected_to_midi_clients_names_list;
	std::list<std::string> connected_to_jack_clients_names_list_left;
	std::list<std::string> connected_to_jack_clients_names_list_right;
	
	list<string>::iterator names_it;
	list<string>::iterator connections_it;
	
	mod_synth_refresh_alsa_clients_data();
	mod_synth_refresh_jack_clients_data();
	
	/* Update the list of ALSA input clients.  
	 * Names order is the same as in the alsa input clients tables prder.
	 * So, the 1st name corresponds to the 1st client in the input clients table. */
	list<string> midi_inputs_names = mod_synth_get_midi_input_client_name_strings();
	
	num_of_alsa_input_clients = midi_inputs_names.size();
	/* Get the instrument client number. */
	client_number = mod_synth_get_midi_client_connection_num(instrument_name.toStdString());
	/* Get a list of the clients that this instrument is connected to. */
	mod_synth_get_midi_client_connected_to_clients_names_list(client_number, true, 
																&connected_to_midi_clients_names_list);
	
	if (num_of_alsa_input_clients > 0)
	{
		names_it = midi_inputs_names.begin();
		
		for (int i = 0; i < num_of_alsa_input_clients && i < 20; i++)
		{
			midi_input_clients_select_pb[i]->setEnabled(true);
			midi_input_clients_select_pb[i]->setText(QString::fromStdString(names_it->c_str()));
			alsa_connections_names[i] = names_it->c_str();
			
			/* Uncheck all - connected will be checked below*/
			midi_input_clients_select_pb[i]->blockSignals(true);
			midi_input_clients_select_pb[i]->setChecked(false);
			midi_input_clients_select_pb[i]->blockSignals(false);
			
			advance(names_it, 1);
		}
		
		for (int i = num_of_alsa_input_clients; i < 20; i++)
		{
			midi_input_clients_select_pb[i]->setEnabled(false);
			midi_input_clients_select_pb[i]->setText("");
			
			/* Uncheck all - connected will be checked below*/
			midi_input_clients_select_pb[i]->blockSignals(true);
			midi_input_clients_select_pb[i]->setChecked(false);
			midi_input_clients_select_pb[i]->blockSignals(false);
		}
	}
	
	/* Connected to? */
	if (connected_to_midi_clients_names_list.size() > 0)
	{
		connections_it = connected_to_midi_clients_names_list.begin();
				
		for (int c = 0; c < connected_to_midi_clients_names_list.size(); c++)
		{
			names_it = midi_inputs_names.begin();
		
			for (int i = 0; i < num_of_alsa_input_clients; i++)
			{
				if (strip_client_name_prefix(names_it->c_str()) == connections_it->c_str())
				{
					midi_input_clients_select_pb[i]->blockSignals(true);
					midi_input_clients_select_pb[i]->setChecked(true);
					midi_input_clients_select_pb[i]->blockSignals(false);
				}
				
				advance(names_it, 1);
			}
					
			advance(connections_it, 1);
		}
	}
				
	/* Update the list of Jack iput clients */	
	num_of_jack_input_clients = mod_synth_get_num_of_input_jack_clients();
	
	if (num_of_jack_input_clients > _MAX_NUM_OF_GUI_JACK_CLIENTS)
	{
		num_of_jack_input_clients = _MAX_NUM_OF_GUI_JACK_CLIENTS;
	}
	
	input_ports_count = 0;
	
	if (num_of_jack_input_clients > 0)
	{		
		for (cln = 0; cln < num_of_jack_input_clients && input_ports_count < 10; cln++)
		{
			cln_name = mod_synth_get_jack_input_client_name(cln);

			if ((cln_name.find("PipeWire") == std::string::npos) &&
				(cln_name.find("PulseAudio") == std::string::npos))
			{
				num_of_ports = mod_synth_get_num_of_jack_input_client_ports(cln);

				if (num_of_ports > 0)
				{
					for (port = 0; port < num_of_ports && input_ports_count < 10; port++)
					{
						port_name = mod_synth_get_jack_input_client_port_name(cln, port);

						if ((port_name != "") && (port_name.find("midi_playback") == std::string::npos))
						{
							jack_output_client_names[input_ports_count] = cln_name;
							jack_output_client_port_names[input_ports_count] = port_name;
							input_name = cln_name + ":" + port_name;
							/* Instrument Right output connections */
							jack_output_clients_select_pb[input_ports_count]->setEnabled(true);
							jack_output_clients_select_pb[input_ports_count]->setText(QString::fromStdString(input_name.c_str()));
							jack_connections_names[input_ports_count] = input_name.c_str();
							/* Uncheck all - connected will be checked below*/
							jack_output_clients_select_pb[input_ports_count]->blockSignals(true);
							jack_output_clients_select_pb[input_ports_count]->setChecked(false);
							jack_output_clients_select_pb[input_ports_count]->blockSignals(false);
							/* Instrument Left output connections */
							jack_output_clients_select_pb[input_ports_count + 10]->setEnabled(true);
							jack_output_clients_select_pb[input_ports_count + 10]->setText(QString::fromStdString(input_name.c_str()));
							jack_connections_names[input_ports_count + 10] = input_name.c_str();
							/* Uncheck all - connected will be checked below*/
							jack_output_clients_select_pb[input_ports_count + 10]->blockSignals(true);
							jack_output_clients_select_pb[input_ports_count + 10]->setChecked(false);
							jack_output_clients_select_pb[input_ports_count + 10]->blockSignals(false);

							input_ports_count++;
						}
					}

					for (port = input_ports_count; port < 10; port++)
					{
						/* Instrument Right output connections */
						jack_output_clients_select_pb[input_ports_count]->setEnabled(false);
						jack_output_clients_select_pb[input_ports_count]->setText("");
						/* Uncheck all */
						jack_output_clients_select_pb[input_ports_count]->blockSignals(true);
						jack_output_clients_select_pb[input_ports_count]->setChecked(false);
						jack_output_clients_select_pb[input_ports_count]->blockSignals(false);
						/* Instrument Left output connections */
						jack_output_clients_select_pb[input_ports_count + 10]->setEnabled(false);
						jack_output_clients_select_pb[input_ports_count + 10]->setText("");
						/* Uncheck all */
						jack_output_clients_select_pb[input_ports_count + 10]->blockSignals(true);
						jack_output_clients_select_pb[input_ports_count + 10]->setChecked(false);
						jack_output_clients_select_pb[input_ports_count + 10]->blockSignals(false);
					}
				}
			}
		}		
	}
	
	for (int i = input_ports_count; i < 10; i++)
	{
		jack_output_clients_select_pb[i]->setEnabled(false);
		jack_output_clients_select_pb[i]->setText("");
		
		jack_output_clients_select_pb[i+10]->setEnabled(false);
		jack_output_clients_select_pb[i+10]->setText("");
	}
	
	/* Connected to? */
	std::string client_out_name = "";

	if ((instrument_name.toStdString() == _INSTRUMENT_NAME_ANALOG_SYNTH_STR_KEY) ||
		(instrument_name.toStdString() == _INSTRUMENT_NAME_HAMMON_ORGAN_STR_KEY) ||
		(instrument_name.toStdString() == _INSTRUMENT_NAME_KARPLUS_STRONG_STRING_SYNTH_STR_KEY) ||
		(instrument_name.toStdString() == _INSTRUMENT_NAME_MSO_SYNTH_STR_KEY) ||
		(instrument_name.toStdString() == _INSTRUMENT_NAME_PAD_SYNTH_STR_KEY ||
		 (instrument_name.toStdString() == _INSTRUMENT_NAME_SYNTH_PRESET_1_STR_KEY) ||
		 (instrument_name.toStdString() == _INSTRUMENT_NAME_SYNTH_PRESET_2_STR_KEY) ||
		 (instrument_name.toStdString() == _INSTRUMENT_NAME_SYNTH_PRESET_3_STR_KEY) ||
		 (instrument_name.toStdString() == _INSTRUMENT_NAME_SYNTH_PRESET_4_STR_KEY) ||
		 (instrument_name.toStdString() == _INSTRUMENT_NAME_SYNTH_PRESET_5_STR_KEY) ||
		 (instrument_name.toStdString() == _INSTRUMENT_NAME_SYNTH_PRESET_6_STR_KEY) ||
		 (instrument_name.toStdString() == _INSTRUMENT_NAME_SYNTH_PRESET_7_STR_KEY) ||
		 (instrument_name.toStdString() == _INSTRUMENT_NAME_SYNTH_PRESET_8_STR_KEY) ||
		 (instrument_name.toStdString() == _INSTRUMENT_NAME_SYNTH_PRESET_9_STR_KEY) ||
		 (instrument_name.toStdString() == _INSTRUMENT_NAME_SYNTH_PRESET_10_STR_KEY) ||
		 (instrument_name.toStdString() == _INSTRUMENT_NAME_SYNTH_PRESET_11_STR_KEY) ||
		 (instrument_name.toStdString() == _INSTRUMENT_NAME_SYNTH_PRESET_12_STR_KEY) ||
		 (instrument_name.toStdString() == _INSTRUMENT_NAME_SYNTH_PRESET_13_STR_KEY) ||
		 (instrument_name.toStdString() == _INSTRUMENT_NAME_SYNTH_PRESET_14_STR_KEY) ||
		 (instrument_name.toStdString() == _INSTRUMENT_NAME_SYNTH_PRESET_15_STR_KEY) ||
		 (instrument_name.toStdString() == _INSTRUMENT_NAME_SYNTH_PRESET_16_STR_KEY)))
	{
		client_out_name = "AdjHeartSynth_out";
	}

	num_of_connected_jack_input_clients_left = mod_synth_get_jack_input_connections(
		client_out_name,
		"AdjHeartSynthL_out", // TODO:
		&connected_to_jack_clients_names_list_left);
	
	num_of_connected_jack_input_clients_right = mod_synth_get_jack_input_connections(
		client_out_name,
		"AdjHeartSynthR_out", // TODO
		&connected_to_jack_clients_names_list_right);
	
	if (num_of_connected_jack_input_clients_left > 0)
	{
		connections_it = connected_to_jack_clients_names_list_left.begin();
		
		for (int j = 0; j < num_of_connected_jack_input_clients_left; j++)
		{
			for (int c = 0; c < 10; c++)
			{
				if (connections_it->c_str() == jack_connections_names[c])
				{
					jack_output_clients_select_pb[c]->blockSignals(true);
					jack_output_clients_select_pb[c]->setChecked(true);
					jack_output_clients_select_pb[c]->blockSignals(false);
				}
			}
			
			advance(connections_it, 1);
		} 
	}
	
	if (num_of_connected_jack_input_clients_right > 0)
	{
		connections_it = connected_to_jack_clients_names_list_right.begin();
		
		for (int j = 0; j < num_of_connected_jack_input_clients_right; j++)
		{
			for (int c = 10; c < 20; c++)
			{
				if (connections_it->c_str() == jack_connections_names[c])
				{
					jack_output_clients_select_pb[c]->blockSignals(true);
					jack_output_clients_select_pb[c]->setChecked(true);
					jack_output_clients_select_pb[c]->blockSignals(false);
				}
			}
			
			advance(connections_it, 1);
		} 
	}
	
	
}

void Dialog_InstrumentConnections::on_dialog_ok()
{	
	mod_synth_unregister_callback_control_box_event_update_ui(
		&connections_control_box_event_update_ui_callback_wrapper);
	
	close();
}

void Dialog_InstrumentConnections::on_dialog_refresh()
{
	update();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_MIDI_pannel_clicked()
{
	selected_pannel = _MIDI_PANNEL_SELECTED;
	
	ui->frame_MIDI->setFrameShadow(QFrame::Sunken);
	ui->frame_MIDI->setLineWidth(5);
	ui->frame_MIDI->setMidLineWidth(5);
	ui->frame_Jack->setFrameShadow(QFrame::Plain);
	ui->frame_Jack->setLineWidth(0);
	ui->frame_Jack->setMidLineWidth(0);
	ui->radioButton_MIDI->setChecked(true);
	ui->radioButton_Jack->setChecked(false);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_Jack_pannel_clicked()
{
	selected_pannel = _JACK_PANNEL_SELECTED;
	
	ui->frame_MIDI->setFrameShadow(QFrame::Plain);
	ui->frame_MIDI->setLineWidth(0);
	ui->frame_MIDI->setMidLineWidth(0);
	ui->frame_Jack->setFrameShadow(QFrame::Sunken);
	ui->frame_Jack->setLineWidth(5);
	ui->frame_Jack->setMidLineWidth(5);
	ui->radioButton_MIDI->setChecked(false);
	ui->radioButton_Jack->setChecked(true);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
	
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_1(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 0, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_2(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 1, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_3(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 2, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_4(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 3, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_5(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 4, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_6(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 5, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_7(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 6, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_8(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 7, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_9(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 8, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_10(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 9, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_11(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 10, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_12(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 11, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_13(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 12, 0, sel);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_14(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 13, 0, sel);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_15(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 14, 0, sel);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_16(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 15, 0, sel);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_17(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 16, 0, sel);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_18(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 17, 0, sel);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_19(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 18, 0, sel);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_20(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 19, 0, sel);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}


void Dialog_InstrumentConnections::on_select_jack_out_toggled_1(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[0]),
		replace_white_spaces(jack_output_client_port_names[0]),
		instrument_name.toStdString(),
		"left",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_2(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[1]),
		replace_white_spaces(jack_output_client_port_names[1]),
		instrument_name.toStdString(),
		"left",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_3(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[2]),
		replace_white_spaces(jack_output_client_port_names[2]),
		instrument_name.toStdString(),
		"left",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_4(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[3]),
		replace_white_spaces(jack_output_client_port_names[3]),
		instrument_name.toStdString(),
		"left",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_5(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[4]),
		replace_white_spaces(jack_output_client_port_names[4]),
		instrument_name.toStdString(),
		"left",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_6(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[5]),
		replace_white_spaces(jack_output_client_port_names[5]),
		instrument_name.toStdString(),
		"left",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_7(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[6]),
		replace_white_spaces(jack_output_client_port_names[6]),
		instrument_name.toStdString(),
		"right",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_8(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[7]),
		replace_white_spaces(jack_output_client_port_names[7]),
		instrument_name.toStdString(),
		"right",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_9(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[8]),
		replace_white_spaces(jack_output_client_port_names[8]),
		instrument_name.toStdString(),
		"right",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_10(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[9]),
		replace_white_spaces(jack_output_client_port_names[9]),
		instrument_name.toStdString(),
		"right",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_11(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[0]),
		replace_white_spaces(jack_output_client_port_names[0]),
		instrument_name.toStdString(),
		"right",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_12(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[1]),
		replace_white_spaces(jack_output_client_port_names[1]),
		instrument_name.toStdString(),
		"right",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_13(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[2]),
		replace_white_spaces(jack_output_client_port_names[2]),
		instrument_name.toStdString(),
		"right",
		sel);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_14(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[3]),
		replace_white_spaces(jack_output_client_port_names[3]),
		instrument_name.toStdString(),
		"right",
		sel);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_15(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[4]),
		replace_white_spaces(jack_output_client_port_names[4]),
		instrument_name.toStdString(),
		"right",
		sel);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_16(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[5]),
		replace_white_spaces(jack_output_client_port_names[5]),
		instrument_name.toStdString(),
		"right",
		sel);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_17(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[6]),
		replace_white_spaces(jack_output_client_port_names[6]),
		instrument_name.toStdString(),
		"right",
		sel);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_18(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[7]),
		replace_white_spaces(jack_output_client_port_names[7]),
		instrument_name.toStdString(),
		"right",
		sel);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_19(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[8]),
		replace_white_spaces(jack_output_client_port_names[8]),
		instrument_name.toStdString(),
		"right",
		sel);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_20(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[9]),
		replace_white_spaces(jack_output_client_port_names[9]),
		instrument_name.toStdString(),
		"right",
		sel);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
