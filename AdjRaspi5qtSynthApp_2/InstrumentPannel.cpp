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

#include "filesystem"

#include "InstrumentPannel.h"
#include "Dialog_AdjFluidSynth.h"
#include "Dialog_AnalogSynth_1900x1000.h"
#include "Dialog_InstrumentConnections.h"
#include "Dialog_MidiMapper.h"
#include "Dialog_KeyboardMapper.h"
#include "Dialog_MidiMixer.h"
#include "Dialog_MidiPlayer.h"
#include "Dialog_AnalogReverb.h"
#include "Dialog_AnalogEqualizer.h"
#include "Dialog_HammondOrgan.h"
#include "Dialog_StringSynthesizer.h"
#include "Dialog_PADsynthesizer.h"
#include "Dialog_MSOsynthesizer.h"
#include "MainWindow.h"
#include "CustomFileDialog.h"

#include "ui_InstrumentPannel.h"

LoadSynthesizerPatchPresetFileThread *load_synthesizer_patch_preset_file_thread;

QString string_synth_patch_preset_file_name;
int string_synth_patch_preset_id = -1;

void LoadSynthesizerPatchPresetFileThread::run()
{
	int res;

	QString result = QString("Preset File Loaded");
	res = mod_synth_load_patch_preset_synthesizer_preset_file(
		string_synth_patch_preset_file_name.toStdString(),
		string_synth_patch_preset_id);

	emit loadPresetFileDone(result);
}

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

	ui->label_InstrumentPreset->setText("Preset");
	ui->label_InstrumentPreset->setAttribute(Qt::WA_TranslucentBackground);
	
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
	dialog_string_synthesizer = nullptr;
	dialog_pad_synthesizer = nullptr;
	dialog_mso_synthesizer = nullptr;
	dialog_keyboard_mapper = nullptr;

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

	// Disable connections button and hide Preset labelfor certain instruments
	if ((inst_id == adj_midi_player) ||
		(inst_id == adj_reverb_effect) ||
		(inst_id == adj_distortion_effect) ||
		(inst_id == adj_graphic_equilizer) ||
		(inst_id == midi_mixer) ||
		(inst_id == adj_ext_midi_interface))
	{
		ui->pushButton_InstrumentConnections->setDisabled(true);
		ui->label_InstrumentPreset->setVisible(false);
	}

	// Replace the Open button with a "Preset" button for certain instruments
	if ((inst_id == analog_synth_preset_1) ||
		(inst_id == analog_synth_preset_2) ||
		(inst_id == analog_synth_preset_3) ||
		(inst_id == analog_synth_preset_4) ||
		(inst_id == analog_synth_preset_5) ||
		(inst_id == analog_synth_preset_6) ||
		(inst_id == analog_synth_preset_7) ||
		(inst_id == analog_synth_preset_8) ||
		(inst_id == analog_synth_preset_9) ||
		(inst_id == analog_synth_preset_10) ||
		(inst_id == analog_synth_preset_11) ||
		(inst_id == analog_synth_preset_12) ||
		(inst_id == analog_synth_preset_13) ||
		(inst_id == analog_synth_preset_14) ||
		(inst_id == analog_synth_preset_15) ||
		(inst_id == analog_synth_preset_16))
	{
		ui->pushButton_InstrumentOpen->setText("Preset");
	}

	// Enable mouse tracking for hover effects
	setMouseTracking(true);

	// Set initial visual state
	// update_visual_state();
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
	int r = frame_color.red();
	int g = frame_color.green();
	int b = frame_color.blue();
	int a = frame_color.alpha();

	QString styleSheet;

	switch (current_state)
	{
	case STATE_IDLE:
		styleSheet = QString(
						 "InstrumentPannel {"
						 "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
						 "        stop:0 rgba(25, 25, 25, 200),"  // Changed from 60
						 "        stop:1 rgba(15, 15, 15, 200));" // Changed from 40
						 "    border: 2px solid rgba(%1, %2, %3, %4);"
						 "    border-top: 2px solid rgba(%5, %6, %7, %8);"		 // Lighter top
						 "    border-left: 2px solid rgba(%5, %6, %7, %8);"		 // Lighter left
						 "    border-bottom: 3px solid rgba(%9, %10, %11, %12);" // Darker bottom
						 "    border-right: 3px solid rgba(%9, %10, %11, %12);"	 // Darker right
						 "    border-radius: 6px;"
						 "}")
						 .arg(r)
						 .arg(g)
						 .arg(b)
						 .arg(a) // Base border
						 .arg(qMin(r + 60, 255))
						 .arg(qMin(g + 60, 255))
						 .arg(qMin(b + 60, 255))
						 .arg(a) // Light edge
						 .arg(qMax(r - 30, 0))
						 .arg(qMax(g - 30, 0))
						 .arg(qMax(b - 30, 0))
						 .arg(a); // Dark edge
		break;

	case STATE_HOVER:
		styleSheet = QString(
						 "InstrumentPannel {"
						 "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
						 "        stop:0 rgba(35, 35, 35, 220),"  // Changed from 70
						 "        stop:1 rgba(25, 25, 25, 220));" // Changed from 50
						 "    border: 3px solid rgba(%1, %2, %3, %4);"
						 "    border-top: 3px solid rgba(%5, %6, %7, %8);"
						 "    border-left: 3px solid rgba(%5, %6, %7, %8);"
						 "    border-bottom: 4px solid rgba(%9, %10, %11, %12);"
						 "    border-right: 4px solid rgba(%9, %10, %11, %12);"
						 "    border-radius: 6px;"
						 "}")
						 .arg(qMin(r + 40, 255))
						 .arg(qMin(g + 40, 255))
						 .arg(qMin(b + 40, 255))
						 .arg(qMin(a + 20, 255))
						 .arg(qMin(r + 80, 255))
						 .arg(qMin(g + 80, 255))
						 .arg(qMin(b + 80, 255))
						 .arg(qMin(a + 20, 255))
						 .arg(qMax(r - 20, 0))
						 .arg(qMax(g - 20, 0))
						 .arg(qMax(b - 20, 0))
						 .arg(qMin(a + 20, 255));
		break;

	case STATE_SELECTED:
		styleSheet = QString(
						 "InstrumentPannel {"
						 "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
						 "        stop:0 rgba(45, 45, 45, 240),"  // Changed from 80
						 "        stop:1 rgba(35, 35, 35, 240));" // Changed from 60
						 "    border: 4px solid rgba(%1, %2, %3, 255);"
						 "    border-top: 4px solid rgba(%4, %5, %6, 255);"
						 "    border-left: 4px solid rgba(%4, %5, %6, 255);"
						 "    border-bottom: 5px solid rgba(%7, %8, %9, 255);"
						 "    border-right: 5px solid rgba(%7, %8, %9, 255);"
						 "    border-radius: 6px;"
						 "}")
						 .arg(qMin(r + 70, 255))
						 .arg(qMin(g + 70, 255))
						 .arg(qMin(b + 70, 255))
						 .arg(qMin(r + 100, 255))
						 .arg(qMin(g + 100, 255))
						 .arg(qMin(b + 100, 255))
						 .arg(qMax(r - 10, 0))
						 .arg(qMax(g - 10, 0))
						 .arg(qMax(b - 10, 0));
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

void InstrumentPannel::set_frame_color(const QColor &color)
{
	frame_color = color;
	update_visual_state();
}

void InstrumentPannel::set_frame_color(int r, int g, int b, int a)
{
	frame_color = QColor(r, g, b, a);
	update_visual_state();
}

void InstrumentPannel::set_preset_text(const QString &text)
{
	ui->textEdit_PresetText->setText(text);
}

QString InstrumentPannel::get_preset_text() const
{
	return ui->textEdit_PresetText->toPlainText();
}

void InstrumentPannel::clear_preset_text()
{
	ui->textEdit_PresetText->clear();
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
	else if (instrument_name == _INSTRUMENT_NAME_KARPLUS_STRONG_STRING_SYNTH_STR_KEY)
	{
		open_string_synthesizer_dialog();
	}
	else if (instrument_name == _INSTRUMENT_NAME_PAD_SYNTH_STR_KEY)
	{
		open_pad_synthesizer_dialog();
	}
	else if (instrument_name == _INSTRUMENT_NAME_MSO_SYNTH_STR_KEY)
	{
		open_mso_synthesizer_dialog();
	}
	else if (instrument_name == _INSTRUMENT_NAME_KEYBOARD_MAPPER_STR_KEY)
	{
		open_keyboard_mapper_dialog();
	}
	else if (instrument_name == _INSTRUMENT_NAME_SYNTH_PRESET_1_STR_KEY)
	{
		open_synth_patch_preset_dialog(0);
	}
	else if (instrument_name == _INSTRUMENT_NAME_SYNTH_PRESET_2_STR_KEY)
	{
		open_synth_patch_preset_dialog(1);
	}
	else if (instrument_name == _INSTRUMENT_NAME_SYNTH_PRESET_3_STR_KEY)
	{
		open_synth_patch_preset_dialog(2);
	}
	else if (instrument_name == _INSTRUMENT_NAME_SYNTH_PRESET_4_STR_KEY)
	{
		open_synth_patch_preset_dialog(3);
	}
	else if (instrument_name == _INSTRUMENT_NAME_SYNTH_PRESET_5_STR_KEY)
	{
		open_synth_patch_preset_dialog(4);
	}
	else if (instrument_name == _INSTRUMENT_NAME_SYNTH_PRESET_6_STR_KEY)
	{
		open_synth_patch_preset_dialog(5);
	}
	else if (instrument_name == _INSTRUMENT_NAME_SYNTH_PRESET_7_STR_KEY)
	{
		open_synth_patch_preset_dialog(6);
	}
	else if (instrument_name == _INSTRUMENT_NAME_SYNTH_PRESET_8_STR_KEY)
	{
		open_synth_patch_preset_dialog(7);
	}
	else if (instrument_name == _INSTRUMENT_NAME_SYNTH_PRESET_9_STR_KEY)
	{
		open_synth_patch_preset_dialog(8);
	}
	else if (instrument_name == _INSTRUMENT_NAME_SYNTH_PRESET_10_STR_KEY)
	{
		open_synth_patch_preset_dialog(9);
	}
	else if (instrument_name == _INSTRUMENT_NAME_SYNTH_PRESET_11_STR_KEY)
	{
		open_synth_patch_preset_dialog(10);
	}
	else if (instrument_name == _INSTRUMENT_NAME_SYNTH_PRESET_12_STR_KEY)
	{
		open_synth_patch_preset_dialog(11);
	}
	else if (instrument_name == _INSTRUMENT_NAME_SYNTH_PRESET_13_STR_KEY)
	{
		open_synth_patch_preset_dialog(12);
	}
	else if (instrument_name == _INSTRUMENT_NAME_SYNTH_PRESET_14_STR_KEY)
	{
		open_synth_patch_preset_dialog(13);
	}
	else if (instrument_name == _INSTRUMENT_NAME_SYNTH_PRESET_15_STR_KEY)
	{
		open_synth_patch_preset_dialog(14);
	}
	else if (instrument_name == _INSTRUMENT_NAME_SYNTH_PRESET_16_STR_KEY)
	{
		open_synth_patch_preset_dialog(15);
	}
	else
	{
		
	}
}

void InstrumentPannel::open_fluid_synth_dialog()
{
	if (dialog_adj_fluid_synth == nullptr)
	{
		dialog_adj_fluid_synth = Dialog_AdjFluidSynth::get_instance(nullptr);

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
		dialog_analog_synth_1900x1000 = Dialog_AnalogSynth_1900x1000::get_instance(nullptr);

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
		dialog_adj_midi_player = Dialog_MidiPlayer::get_instance(nullptr);

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
		dialog_midi_mixer = Dialog_MidiMixer::get_instance(nullptr);

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
		dialog_midi_mapper = Dialog_MidiMapper::get_instance(nullptr, true);

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
		dialog_analog_reverb = Dialog_AnalogReverb::get_instance(nullptr);
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
		dialog_analog_equalizer = Dialog_AnalogEqualizer::get_instance(nullptr);
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
		dialog_hammond_organ = Dialog_HammondOrgan::get_instance(nullptr);
		MainWindow::get_instance()->window_manager->register_dialog(dialog_hammond_organ, "Hammond Organ");

		connect(dialog_hammond_organ, &QObject::destroyed, [this]() {
			MainWindow::get_instance()->window_manager->unregister_dialog(dialog_hammond_organ);
		});
	}

	dialog_hammond_organ->show();
	dialog_hammond_organ->raise();
	dialog_hammond_organ->activateWindow();
}

void InstrumentPannel::open_string_synthesizer_dialog()
{
	if (dialog_string_synthesizer == nullptr)
	{
		dialog_string_synthesizer = Dialog_StringSynthesizer::get_instance(nullptr);
		MainWindow::get_instance()->window_manager->register_dialog(dialog_string_synthesizer, "String Synthesizer");
		connect(dialog_string_synthesizer, &QObject::destroyed, [this]() {
			MainWindow::get_instance()->window_manager->unregister_dialog(dialog_string_synthesizer);
		});
	}
	dialog_string_synthesizer->show();
	dialog_string_synthesizer->raise();
	dialog_string_synthesizer->activateWindow();
}

void InstrumentPannel::open_pad_synthesizer_dialog()
{
	if (dialog_pad_synthesizer == nullptr)
	{
		dialog_pad_synthesizer = Dialog_PADsynthesizer::get_instance(nullptr);
		MainWindow::get_instance()->window_manager->register_dialog(dialog_pad_synthesizer, "PAD Synthesizer");
		connect(dialog_pad_synthesizer, &QObject::destroyed, [this]() {
			MainWindow::get_instance()->window_manager->unregister_dialog(dialog_pad_synthesizer);
		});
	}
	dialog_pad_synthesizer->show();
	dialog_pad_synthesizer->raise();
	dialog_pad_synthesizer->activateWindow();
}

void InstrumentPannel::open_mso_synthesizer_dialog()
{
	if (dialog_mso_synthesizer == nullptr)
	{
		dialog_mso_synthesizer = Dialog_MSOsynthesizer::get_instance(nullptr);
		MainWindow::get_instance()->window_manager->register_dialog(dialog_mso_synthesizer, "MSO Synthesizer");
		connect(dialog_mso_synthesizer, &QObject::destroyed, [this]() {
			MainWindow::get_instance()->window_manager->unregister_dialog(dialog_mso_synthesizer);
		});
	}
	dialog_mso_synthesizer->show();
	dialog_mso_synthesizer->raise();
	dialog_mso_synthesizer->activateWindow();
}

void InstrumentPannel::open_keyboard_mapper_dialog()
{
	if (dialog_keyboard_mapper == nullptr)
	{
		dialog_keyboard_mapper = Dialog_KeyboardMapper::get_instance(nullptr);
		MainWindow::get_instance()->window_manager->register_dialog(dialog_keyboard_mapper, "Keyboard Mapper");
		connect(dialog_keyboard_mapper, &QObject::destroyed, [this]() {
			MainWindow::get_instance()->window_manager->unregister_dialog(dialog_keyboard_mapper);
		});
	}

	dialog_keyboard_mapper->show();
	dialog_keyboard_mapper->raise();
	dialog_keyboard_mapper->activateWindow();
}

void InstrumentPannel::open_synth_patch_preset_dialog(int preset_index)
{
	if (preset_index < 0 || preset_index >= _MAX_NUM_OF_ANALOG_PRESET_INSTRUMENTS)
	{
		return; // Invalid index
	}

	QString startDir = last_string_synth_preset_directory[preset_index].isEmpty() ? QString(_STRING_SYNTH_PRESETS_FILES_DEFAULT_DIR) : last_string_synth_preset_directory[preset_index];

	CustomFileDialog dialog(this,
							tr("Open Preset File"),
							startDir,
							tr("Presets (*.xml *.XML);;All Files (*)"),
							Qt::black,
							CustomFileDialog::OpenMode,
							"string_synth_load_presets");

	// If we have a last file, select it and scroll to it - do we still need it. CustomFileDialog selects last file.
	if (!last_string_synth_preset_load_file[preset_index].isEmpty())
	{
		dialog.selectFile(last_string_synth_preset_load_file[preset_index]);
	}

	if (dialog.exec() == QDialog::Accepted)
	{
		string_synth_patch_preset_file_name = dialog.selectedFile();
		string_synth_patch_preset_id = preset_index;

		if (!string_synth_patch_preset_file_name.isEmpty())
		{
			// Remember the directory and file for next time
			last_string_synth_preset_directory[preset_index] = QFileInfo(string_synth_patch_preset_file_name).absolutePath();
			last_string_synth_preset_load_file[preset_index] = string_synth_patch_preset_file_name;

			std::string file_name;
			// file_name = std::string("Now Loading: ");
			file_name = std::filesystem::path(string_synth_patch_preset_file_name.toStdString()).stem();

			MainWindow *mainWin = MainWindow::get_instance();
			if (mainWin)
			{
				InstrumentPannel *panel =
					mainWin->get_instrument_panel_by_id(static_cast<en_instruments_ids_t>(en_instruments_ids_t::analog_synth_preset_1 + preset_index));
				if (panel)
				{
					panel->set_preset_text(QString::fromStdString(file_name));
				}
			}

			load_synthesizer_patch_preset_file_thread = new LoadSynthesizerPatchPresetFileThread();
			//connect(load_synthesizer_patch_preset_file_thread,
			//		&LoadSynthesizerPatchPresetFileThread::finished, 
			//		load_synthesizer_patch_preset_file_thread, 
			//		&QObject::deleteLater);

			connect(load_synthesizer_patch_preset_file_thread,
					&LoadSynthesizerPatchPresetFileThread::finished,
					this,
					[=]() {
						load_synthesizer_patch_preset_file_thread->deleteLater();
						load_synthesizer_patch_preset_file_thread = nullptr; // Reset to nullptr after deletion
					});

			connect(load_synthesizer_patch_preset_file_thread, 
					&LoadSynthesizerPatchPresetFileThread::loadPresetFileDone,
					this, 
					&InstrumentPannel::on_preset_file_loaded);
			
			load_synthesizer_patch_preset_file_thread->start();
		}
	}
	
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

void InstrumentPannel::on_preset_file_loaded(const QString &s)
{
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
