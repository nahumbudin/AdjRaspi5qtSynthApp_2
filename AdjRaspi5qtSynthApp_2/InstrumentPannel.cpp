/**
 *	@file		InstrumentPannel.cpp
 *	@author		Nahum Budin
 *	@date		27-Jan-2026
 *	@version	1.2
 *				1. Cleaned up - removed all old GuiNavigator references
 *				2. Simplified dialog opening logic
 *
 *	@brief		Handles a single instrument panel
 */

/**
 *	@file		InstrumentPannel.cpp
 *	@author		Nahum Budin
 *	@date		27-Jan-2026
 *	@version	1.2
 *				Fixed circular dependency - explicit dialog opening methods
 */

#include "InstrumentPannel.h"
#include "Dialog_AdjFluidSynth.h"
#include "Dialog_AnalogSynth_1900x1000.h"
#include "Dialog_InstrumentConnections.h"
#include "Dialog_MidiMapper.h"
#include "Dialog_MidiMixer.h"
#include "Dialog_MidiPlayer.h"
#include "Dialog_AnalogReverb.h"
#include "Dialog_AnalogEqualizer.h"
#include "Dialog_HammondOrgan.h"
#include "MainWindow.h"
#include "ui_InstrumentPannel.h"

InstrumentPannel::InstrumentPannel(QWidget *parent,
								   QString instrument_name_str,
								   func_ptr_void_en_instruments_ids_t_t close_instrument_pannel_callback_ptr,
								   en_instruments_ids_t inst_id)
	: QFrame(parent), ui(new Ui::InstrumentPannel), current_state(STATE_IDLE)
{
	ui->setupUi(this);

	widget_parent = parent;
	instrument_name = instrument_name_str;
	instrument_id = inst_id;
	close_callback_ptr = close_instrument_pannel_callback_ptr;

	// Set UI elements
	ui->label_InstrumentName->setText(instrument_name);
	ui->label_InstrumentName->setAttribute(Qt::WA_TranslucentBackground);
	ui->checkBox_InstrumentMIDIin->setAttribute(Qt::WA_TranslucentBackground);

	// Initialize dialog pointers
	connections_dialog = nullptr;
	dialog_adj_fluid_synth = nullptr;
	dialog_analog_synth_1900x1000 = nullptr;
	dialog_adj_midi_player = nullptr;
	dialog_midi_mixer = nullptr;
	dialog_midi_mapper = nullptr;
	dialog_analog_reverb = nullptr;
	dialog_analog_equalizer = nullptr;
	dialog_hammond_organ = nullptr;

	// Connect signals
	connect(ui->pushButton_InstrumentExit,
			SIGNAL(clicked()),
			this,
			SLOT(on_instrument_exit_clicked()));

	connect(ui->pushButton_InstrumentOpen,
			SIGNAL(clicked()),
			this,
			SLOT(on_instrument_open_clicked()));

	connect(ui->pushButton_InstrumentConnections,
			SIGNAL(clicked()),
			this,
			SLOT(on_instrument_connections_clicked()));

	// Disable connections button for certain instruments
	if ((inst_id == adj_midi_player) ||
		(inst_id == adj_reverb_effect) ||
		(inst_id == adj_distortion_effect) ||
		(inst_id == adj_graphic_equilizer) ||
		(inst_id == midi_mixer) ||
		(inst_id == adj_ext_midi_interface))
	{
		ui->pushButton_InstrumentConnections->setDisabled(true);
	}

	// Enable mouse tracking for hover effects
	setMouseTracking(true);

	// Set initial visual state
	update_visual_state();
}

InstrumentPannel::~InstrumentPannel()
{
	delete ui;
}

InstrumentPannel *InstrumentPannel::get_the_instrument_pannel()
{
	return this;
}

void InstrumentPannel::set_state(PannelState state)
{
	if (current_state != state)
	{
		current_state = state;
		update_visual_state();
	}
}

void InstrumentPannel::set_selected(bool selected)
{
	if (selected)
	{
		set_state(STATE_SELECTED);
	}
	else
	{
		set_state(STATE_IDLE);
	}
}

void InstrumentPannel::update_visual_state()
{
	QString styleSheet;

	switch (current_state)
	{
	case STATE_IDLE:
		styleSheet =
			"QFrame {"
			"    background-color: rgba(20, 20, 20, 220);"
			"    border: 1px solid rgba(40, 40, 40, 180);"
			"    border-radius: 4px;"
			"}";
		break;

	case STATE_HOVER:
		styleSheet =
			"QFrame {"
			"    background-color: rgba(35, 35, 35, 230);"
			"    border: 1px solid rgba(60, 60, 60, 200);"
			"    border-radius: 4px;"
			"}";
		break;

	case STATE_SELECTED:
		styleSheet =
			"QFrame {"
			"    background-color: rgba(50, 50, 50, 240);"
			"    border: 2px solid rgba(90, 140, 200, 255);"
			"    border-radius: 4px;"
			"}";
		break;
	}

	setStyleSheet(styleSheet);
}

void InstrumentPannel::enterEvent(QEvent *event)
{
	Q_UNUSED(event);

	if (current_state != STATE_SELECTED)
	{
		set_state(STATE_HOVER);
	}

	QFrame::enterEvent(event);
}

void InstrumentPannel::leaveEvent(QEvent *event)
{
	Q_UNUSED(event);

	if (current_state != STATE_SELECTED)
	{
		set_state(STATE_IDLE);
	}

	QFrame::leaveEvent(event);
}

void InstrumentPannel::hide_checkBox_InstrumentMIDIin()
{
	ui->checkBox_InstrumentMIDIin->hide();
}

void InstrumentPannel::on_instrument_exit_clicked()
{
	if (close_callback_ptr != nullptr)
	{
		close_callback_ptr(instrument_id);
	}
}

void InstrumentPannel::on_instrument_open_clicked()
{
	if (instrument_name == _INSTRUMENT_NAME_FLUID_SYNTH_STR_KEY)
	{
		open_fluid_synth_dialog();
	}
	else if (instrument_name == _INSTRUMENT_NAME_ANALOG_SYNTH_STR_KEY)
	{
		open_analog_synth_dialog();
	}
	else if (instrument_name == _INSTRUMENT_NAME_MIDI_PLAYER_STR_KEY)
	{
		open_midi_player_dialog();
	}
	else if (instrument_name == _INSTRUMENT_NAME_MIDI_MIXER_STR_KEY)
	{
		open_midi_mixer_dialog();
	}
	else if (instrument_name == _INSTRUMENT_NAME_MIDI_MAPPER_STR_KEY)
	{
		open_midi_mapper_dialog();
	}
	else if (instrument_name == _INSTRUMENT_NAME_REVERB_STR_KEY)
	{
		open_analog_reverb_dialog();
	}
	else if (instrument_name == _INSTRUMENT_NAME_GRAPHIC_EQUALIZER_STR_KEY)
	{
		open_analog_equalizer_dialog();
	}
	else if (instrument_name == _INSTRUMENT_NAME_HAMMON_ORGAN_STR_KEY)
	{
		open_hammond_organ_dialog();
	}
}

void InstrumentPannel::open_fluid_synth_dialog()
{
	if (dialog_adj_fluid_synth == nullptr)
	{
		dialog_adj_fluid_synth = Dialog_AdjFluidSynth::get_instance(this);

		MainWindow::get_instance()->window_manager->register_dialog(dialog_adj_fluid_synth, "Fluid Synth");

		connect(dialog_adj_fluid_synth, &QObject::destroyed, [this]() {
			MainWindow::get_instance()->window_manager->unregister_dialog(dialog_adj_fluid_synth);
		});
	}

	dialog_adj_fluid_synth->show();
	dialog_adj_fluid_synth->raise();
	dialog_adj_fluid_synth->activateWindow();
}

void InstrumentPannel::open_analog_synth_dialog()
{
	if (dialog_analog_synth_1900x1000 == nullptr)
	{
		dialog_analog_synth_1900x1000 = Dialog_AnalogSynth_1900x1000::get_instance(this);

		MainWindow::get_instance()->window_manager->register_dialog(dialog_analog_synth_1900x1000, "Analog Synth");

		connect(dialog_analog_synth_1900x1000, &QObject::destroyed, [this]() {
			MainWindow::get_instance()->window_manager->unregister_dialog(dialog_analog_synth_1900x1000);
		});
	}

	dialog_analog_synth_1900x1000->show();
	dialog_analog_synth_1900x1000->raise();
	dialog_analog_synth_1900x1000->activateWindow();
	MainWindow::get_instance()->sketches_menu->setDisabled(false);
}

void InstrumentPannel::open_midi_player_dialog()
{
	if (dialog_adj_midi_player == nullptr)
	{
		dialog_adj_midi_player = Dialog_MidiPlayer::get_instance(widget_parent);

		MainWindow::get_instance()->window_manager->register_dialog(dialog_adj_midi_player, "MIDI Player");

		connect(dialog_adj_midi_player, &QObject::destroyed, [this]() {
			MainWindow::get_instance()->window_manager->unregister_dialog(dialog_adj_midi_player);
		});
	}

	dialog_adj_midi_player->show();
	dialog_adj_midi_player->raise();
	dialog_adj_midi_player->activateWindow();
}

void InstrumentPannel::open_midi_mixer_dialog()
{
	if (dialog_midi_mixer == nullptr)
	{
		dialog_midi_mixer = Dialog_MidiMixer::get_instance(this);

		MainWindow::get_instance()->window_manager->register_dialog(dialog_midi_mixer, "MIDI Mixer");

		connect(dialog_midi_mixer, &QObject::destroyed, [this]() {
			MainWindow::get_instance()->window_manager->unregister_dialog(dialog_midi_mixer);
		});
	}

	dialog_midi_mixer->show();
	dialog_midi_mixer->raise();
	dialog_midi_mixer->activateWindow();
}

void InstrumentPannel::open_midi_mapper_dialog()
{
	if (dialog_midi_mapper == nullptr)
	{
		dialog_midi_mapper = Dialog_MidiMapper::get_instance(this, true);

		MainWindow::get_instance()->window_manager->register_dialog(dialog_midi_mapper, "MIDI Mapper");

		connect(dialog_midi_mapper, &QObject::destroyed, [this]() {
			MainWindow::get_instance()->window_manager->unregister_dialog(dialog_midi_mapper);
		});
	}

	dialog_midi_mapper->show();
	dialog_midi_mapper->raise();
	dialog_midi_mapper->activateWindow();
}

void InstrumentPannel::open_analog_reverb_dialog()
{
	if (dialog_analog_reverb == nullptr)
	{
		dialog_analog_reverb = Dialog_AnalogReverb::get_instance(this);
		MainWindow::get_instance()->window_manager->register_dialog(dialog_analog_reverb, "Analog Reverb");

		connect(dialog_analog_reverb, &QObject::destroyed, [this]() {
			MainWindow::get_instance()->window_manager->unregister_dialog(dialog_analog_reverb);
		});
	}

	dialog_analog_reverb->show();
	dialog_analog_reverb->raise();
	dialog_analog_reverb->activateWindow();
}

void InstrumentPannel::open_analog_equalizer_dialog()
{
	if (dialog_analog_equalizer == nullptr)
	{
		dialog_analog_equalizer = Dialog_AnalogEqualizer::get_instance(this);
		MainWindow::get_instance()->window_manager->register_dialog(dialog_analog_equalizer, "Analog Equalizer");

		connect(dialog_analog_equalizer, &QObject::destroyed, [this]() {
			MainWindow::get_instance()->window_manager->unregister_dialog(dialog_analog_equalizer);
		});
	}

	dialog_analog_equalizer->show();
	dialog_analog_equalizer->raise();
	dialog_analog_equalizer->activateWindow();
}

void InstrumentPannel::open_hammond_organ_dialog()
{
	if (dialog_hammond_organ == nullptr)
	{
		dialog_hammond_organ = Dialog_HammondOrgan::get_instance(this);
		MainWindow::get_instance()->window_manager->register_dialog(dialog_hammond_organ, "Hammond Organ");

		connect(dialog_hammond_organ, &QObject::destroyed, [this]() {
			MainWindow::get_instance()->window_manager->unregister_dialog(dialog_hammond_organ);
		});
	}

	dialog_hammond_organ->show();
	dialog_hammond_organ->raise();
	dialog_hammond_organ->activateWindow();
}

void InstrumentPannel::on_instrument_connections_clicked()
{
	if (!Dialog_InstrumentConnections::dialog_is_open)
	{
		if (connections_dialog == nullptr)
		{
			connections_dialog = new Dialog_InstrumentConnections(this, instrument_name);
			MainWindow::get_instance()->register_active_dialog(connections_dialog);
			connections_dialog->show();
			Dialog_InstrumentConnections::dialog_is_open = true;
		}
		else
		{
			if (!connections_dialog->isVisible())
			{
				MainWindow::get_instance()->register_active_dialog(connections_dialog);
				connections_dialog->show();
				Dialog_InstrumentConnections::dialog_is_open = true;
			}
		}
	}
}

void InstrumentPannel::close_connections_dialog()
{
	if (connections_dialog)
	{
		connections_dialog->close();
	}
}

void InstrumentPannel::close_instrument_dialog()
{
	if (dialog_adj_fluid_synth && dialog_adj_fluid_synth->isVisible())
	{
		dialog_adj_fluid_synth->close();
	}

	if (dialog_analog_synth_1900x1000 && dialog_analog_synth_1900x1000->isVisible())
	{
		dialog_analog_synth_1900x1000->close();
		MainWindow::get_instance()->sketches_menu->setDisabled(true);
	}

	if (dialog_adj_midi_player && dialog_adj_midi_player->isVisible())
	{
		dialog_adj_midi_player->close();
	}

	if (dialog_midi_mixer && dialog_midi_mixer->isVisible())
	{
		dialog_midi_mixer->close();
	}

	if (dialog_midi_mapper && dialog_midi_mapper->isVisible())
	{
		dialog_midi_mapper->close();
	}
}
