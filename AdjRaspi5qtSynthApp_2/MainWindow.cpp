/**
 *	@file		MainWindow.cpp
 *	@author		Nahum Budin
 *	@date		30-Apr-2026
 *	@version	2.0
 *					1. Add auto-arrangement of open instrument panels in the main window.
 *					2. Added instruments.
 *
 *
 *	@brief		Application Main Window that hosts the modules pannels as acolomn.
 *
 *	History:	version 1.1	22-Sep-2025
 *					1.Code refactoring and comments
 *					2. Added support for GUI Navigator and Windows Manager
 *					3. Update cleanup code
 *
 *				version 1.0		8-May-2024  initial
 */

#include <QVBoxLayout>
#include <QFrame>
#include <QFileDialog>
#include <QTHread>
#include <QTimer>
#include <QMessageBox>
#include <QtWidgets/qboxlayout.h>

#include <stdio.h>

#include "MainWindow.h"

#include "ui_MainWindow.h"
#include "ui_ModulePannel.h"

#include "InstrumentPannel.h"

#include "Dialog_AdjFluidSynth.h"
#include "Dialog_MasterVolume.h"
#include "Dialog_AnalogSynth_1900x1000.h"

SavePatchFileThread *save_patch_file_thread;
LoadPatchFileThread *load_patch_file_thread;

QString patch_file_name;

/** Callback wrapper */

void wrapper_close_instrument_pannel_id(en_instruments_ids_t inst_id)
{
	MainWindow::get_instance()->close_instrument_pannel_id(inst_id);
}
void wrapper_request_close_instrument_pannel_id(en_instruments_ids_t inst_id)
{
	MainWindow::get_instance()->request_close_instrument_pannel_id(inst_id);
}

void wrapper_request_open_instrument_window_name(string instrument_name)
{
	MainWindow::get_instance()->pending_open_instruments_list.push_back(instrument_name);
}


void wrapper_request_close_instrument_pannel_name(string inst_name)
{
	MainWindow::get_instance()->request_close_instrument_pannel_name(inst_name);
}

void main_window_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	MainWindow::get_instance()->control_box_ui_update_callback(evnt, val);
}

std::vector <std::string> get_active_instruments_names_list_wrapper()
{
	return MainWindow::get_instance()->get_active_instruments_names_list();
}

void SavePatchFileThread::run() 
{		
	QString result = QString("Patch File Saved");
	mod_synth_save_patch_file(patch_file_name.toStdString());
	emit savePatchFileDone(result);
}

void LoadPatchFileThread::run() 
{		
	int res;
	
	QString result = QString("Patch File Loaded");
	res = mod_synth_load_patch_file(patch_file_name.toStdString());
	if (res > 0)
	{
		// At least one new module in patch file
		
	}	
	
	emit loadPatchFileDone(result);
}

MainWindow *MainWindow::mwind = NULL;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
										  ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	this->setWindowFlags(Qt::Window); // Ensure it's treated as a top-level window

	mwind = this;
	mwind->move(100, 50);

	// Use QGridLayout instead of QVBoxLayout for flexible arrangement
	QGridLayout *gridLayout = new QGridLayout;
	gridLayout->setSpacing(10);
	gridLayout->setContentsMargins(10, 10, 10, 10);
	ui->centralwidget->setLayout(gridLayout);
	layout = nullptr; // We'll use gridLayout directly

	// ui->centralwidget->setLayout(new QVBoxLayout);
	// layout = qobject_cast<QVBoxLayout *>(ui->centralwidget->layout());
	layout = nullptr; // Not using VBoxLayout anymore

	// Create tools bar menus actions
	create_actions();
	// Create tools bar menus
	create_menus();

	// Initialize window manager
	window_manager = Dialog_WindowManager::get_instance(this);

	// Initialize GUI Navigator (simplified version)
	gui_navigator = GuiNavigator::get_instance();

	// Register MainWindow with GuiNavigator (no frame/tab navigation)
	gui_navigator->register_widget_simple(this, "Main Window");

	// Show the info panel
	gui_navigator->show_info_panel();

	// Register callbacks
	mod_synth_register_callback_control_box_event_update_ui(
		&main_window_control_box_event_update_ui_callback_wrapper);

	mod_synth_register_callback_get_active_instruments_names_list(
		&get_active_instruments_names_list_wrapper);

	mod_synth_register_callback_wrapper_close_instrument_pannel_id(
		&wrapper_request_close_instrument_pannel_id);

	mod_synth_register_callback_wrapper_close_instrument_pannel_name(
		&wrapper_request_close_instrument_pannel_name);

	mod_synth_register_callback_wrapper_open_instrument_pannel_name(
		&wrapper_request_open_instrument_window_name);

	// Build the instruments map
	instruments_ids_map[_INSTRUMENT_NAME_FLUID_SYNTH_STR_KEY] =
		en_instruments_ids_t::fluid_synth;
	instruments_ids_map[_INSTRUMENT_NAME_HAMMON_ORGAN_STR_KEY] =
		en_instruments_ids_t::adj_hammond_organ;
	instruments_ids_map[_INSTRUMENT_NAME_ANALOG_SYNTH_STR_KEY] =
		en_instruments_ids_t::adj_analog_synth;
	instruments_ids_map[_INSTRUMENT_NAME_KARPLUS_STRONG_STRING_SYNTH_STR_KEY] =
		en_instruments_ids_t::adj_karplusstrong_string_synth;
	instruments_ids_map[_INSTRUMENT_NAME_MORPHED_SINUS_SYNTH_STR_KEY] =
		en_instruments_ids_t::adj_morphed_sin_synth;
	instruments_ids_map[_INSTRUMENT_NAME_PAD_SYNTH_STR_KEY] =
		en_instruments_ids_t::adj_pad_synth;
	instruments_ids_map[_INSTRUMENT_NAME_MIDI_PLAYER_STR_KEY] =
		en_instruments_ids_t::adj_midi_player;
	instruments_ids_map[_INSTRUMENT_NAME_MIDI_MIXER_STR_KEY] =
		en_instruments_ids_t::midi_mixer;
	instruments_ids_map[_INSTRUMENT_NAME_MIDI_MAPPER_STR_KEY] =
		en_instruments_ids_t::adj_midi_mapper;
	instruments_ids_map[_INSTRUMENT_NAME_REVERB_STR_KEY] =
		en_instruments_ids_t::adj_reverb_effect;
	instruments_ids_map[_INSTRUMENT_NAME_DISTORTION_STR_KEY] =
		en_instruments_ids_t::adj_distortion_effect;
	instruments_ids_map[_INSTRUMENT_NAME_GRAPHIC_EQUALIZER_STR_KEY] =
		en_instruments_ids_t::adj_graphic_equilizer;
	instruments_ids_map[_INSTRUMENT_NAME_EXT_MIDI_INT_CONTROL_STR_KEY] =
		en_instruments_ids_t::adj_ext_midi_interface;
	instruments_ids_map[_INSTRUMENT_NAME_KEYBOARD_CONTROL_STR_KEY] =
		en_instruments_ids_t::adj_keyboard_control;
	instruments_ids_map[_INSTRUMENT_NAME_KEYBOARD_MAPPER_STR_KEY] =
		en_instruments_ids_t::adj_keyboard_mapper;

	// Start the periodic gui update timer
	start_update_timer(200);
}

MainWindow::~MainWindow()
{
	// Add cleanup here
	printf("MainWindow destructor - running cleanup...\n");
	//mod_synth_on_exit(); // Already done on exit handler.

	system("xset s blank");
	system("xset s on");
	system("xset -dpms");
	system("pactl unload-module module-jack-sink");
	system("pactl unload-module module-jack-source");
	system("cpu.gov -g ondemand");
	
	delete ui;
}

MainWindow *MainWindow::get_instance() {

	if (!mwind)
		mwind = new MainWindow();

	return mwind;
}

/**
*	@brief	Handels the control messages received from the Control Box that shall update the GUI
*	@param	evnt	the event ID
*	@param	val		the event value
*	@return none
*/
void MainWindow::control_box_ui_update_callback(int evnt, uint16_t val)
{
	/*  Counts over all active dialogs */
	static int last_opened_dialog_index = 0;
	/* Holds a dialog position */
	QPoint position;
	
	// I2C Interface Control Box
	if ((evnt >= _I2C_CONTROL_PUSHBUTTON_OK) && (evnt <= _I2C_CONTROL_PUSHBUTTON_RIGHT) ||
		(evnt == _I2C_CONTROL_ENCODER_SCROLL) || (evnt == _I2C_CONTROL_ENCODER_PUSHBUTTON_SCROLL))
	{
		// I2C Interface Control Box
		switch (evnt)
		{
		case _I2C_CONTROL_PUSHBUTTON_RIGHT:
			control_box_right_key_pressed = true;
			//gui_navigator->handle_right_button(); -> gui_update
			break;

		case _I2C_CONTROL_PUSHBUTTON_LEFT:
			control_box_left_key_pressed = true;
			//gui_navigator->handle_left_button();
			break;

		case _I2C_CONTROL_PUSHBUTTON_OK:
			control_box_ok_key_pressed = true;
			//gui_navigator->handle_ok_button();
			break;

		case _I2C_CONTROL_PUSHBUTTON_UP:
			control_box_up_key_pressed = true;
			//gui_navigator->handle_up_button();
			break;

		case _I2C_CONTROL_PUSHBUTTON_DOWN:
			control_box_down_key_pressed = true;
			//gui_navigator->handle_down_button();
			break;

		case _I2C_CONTROL_ENCODER_SCROLL:
			if (val == 0x1000)
			{
				// Scroll pushbutton pressed
				control_box_scroll_pushbutton_pressed = true;
			}
			else if (val == 0x2000)
			{
				// Scroll pushbutton released
			}
			else
			{
				// Scroll rotated
				control_box_scroll_select_change_value = true;
				control_box_scroll_select_new_value = val;
				// gui_navigator->handle_scroll_rotation(val);
			}

			break;

		default:
			break;			
		}
		
	}
	else if ((evnt >= _CONTROL_FUNCTION_PUSHBUTTON_UP) && (evnt <= _CONTROL_FUNCTION_PUSHBUTTON_ENTER))
	{
		// COM Port based control box
		if (evnt == _CONTROL_FUNCTION_PUSHBUTTON_REDOO)
		{
			if (val == 0)
			{
				// The button is pushed only
				// Used for round-robin selection between all open dialogs.
				// NOTE - in Raspberry Pi 5 Wayland, Openbox window manger must be set to X11 backend
				//		  to enable Qt control over dialogs position!!!

				// Next dialog - ststic: kepy from last time
				last_opened_dialog_index++;

				if (last_opened_dialog_index >= active_dialogs_list.size())
				{
					// Wrap around
					last_opened_dialog_index = 0;
				}

				int next_opened_dialog = 0;

				for (QDialog *dialog : active_dialogs_list)
				{

					if (dialog->isHidden())
					{
						// Skip hidden dialogs
						last_opened_dialog_index++;
						next_opened_dialog++;

						if (last_opened_dialog_index >= active_dialogs_list.size())
						{
							last_opened_dialog_index = 0;
						}

						continue;
					}

					if (next_opened_dialog == last_opened_dialog_index)
					{
						position = dialog->pos();
						// position = mapToGlobal(dialog->rect().center());
						printf("%i %i\n", position.x(), position.y());
						dialog->hide();
						dialog->show();
						dialog->move(position);
						// dialog->move(mapFromGlobal(position));
						dialog->setFocus(Qt::ActiveWindowFocusReason);
						printf("%i %i\n", position.x(), position.y());
						break;
					}

					next_opened_dialog++;
				}
			}
		}
	}

		
}

void MainWindow::show_window_manager()
{
	window_manager->show_window_manager();
}


void MainWindow::on_patch_file_saved(const QString &s)
{
	
}

void MainWindow::on_patch_file_loaded(const QString &s)
{
	
}

/**
*	@brief	Copy the source Sketch parameters to the desitnation Sketch parametrs
*	@param	src		source sketch index
*	@param	dest	destination sketch index
*	@return none
*/
void MainWindow::copy_sketch(int src, int dest)
{
	char mssg[64];
	
	if ((src >= 0) && (src < _NUM_OF_SKETCHES) && 
		(dest >= 0) && (dest < _NUM_OF_SKETCHES) &&
		(dest != src))
	{
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setWindowTitle("Warning");
		
		sprintf(mssg, "Are you sure you want to overide Sketch %i?", dest+1);		
		msgBox.setText(QString(mssg));
		msgBox.setStandardButtons(QMessageBox::Yes);
		msgBox.addButton(QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::No);
		if (msgBox.exec() == QMessageBox::Yes) 
		{
			mod_synth_copy_sketch(_SKETCH_PROGRAM_1 + src, _SKETCH_PROGRAM_1 + dest);
			//Dialog_AnalogSynth_1900x1000::get_instance()->update_all(); // No update. Sketch only copied not changed yet!
		}
		else 
		{
			return;
		}		
	}
}

/**
*	@brief	Add a dialog to the active dialogs list
*	@param	dialog		a pointer to the Dialog object
*	@return none
*/
void MainWindow::register_active_dialog(QDialog *dialog)
{
	int i;
	bool found = false;

	std::list<QDialog*>::iterator it_dialogs = active_dialogs_list.begin();
	// Already registered?
	for (i = 0; i < active_dialogs_list.size(); i++)
	{
		if (*it_dialogs == dialog)
		{
			// Already registered
			found = true;
			break;
		}

		it_dialogs++;
	}

	if (!found)
	{
		active_dialogs_list.push_back(dialog);
	}
}

/**
*	@brief	Remove a dialog to the active dialogs list
*	@param	dialog		a pointer to the Dialog object
*	@return none
*/
void MainWindow::unregister_active_dialog(QDialog *dialog)
{
	active_dialogs_list.remove(dialog);
}

/**
*	@brief	Create the tools bar menus actions
*	@param	None
*	@return none
*/

void MainWindow::create_actions()
{
	add_fluid_synth_act = new QAction(tr("&FluidSynth"), this);
	add_fluid_synth_act->setStatusTip(tr("Open FluidSynth"));
	connect(add_fluid_synth_act, SIGNAL(triggered()), this, SLOT(on_add_fluid_synth_instrument()));
	
	add_hammond_organ_act = new QAction(tr("&Hammond Organ"), this);
	add_hammond_organ_act->setStatusTip(tr("Open Hammond Organ"));
	connect(add_hammond_organ_act, SIGNAL(triggered()), this, SLOT(on_add_hammond_organ_instrument()));
	
	add_adj_analog_synth_act = new QAction(tr("&Analog Synth"), this);
	add_adj_analog_synth_act->setStatusTip(tr("Open AdjHeart Analog Synth"));
	connect(add_adj_analog_synth_act, SIGNAL(triggered()), this, SLOT(on_add_adj_analog_synth_instrument()));
	
	add_adj_karplus_strong_strings_synth_act = new QAction(tr("&Karpuls Strong String Synth"), this);
	add_adj_karplus_strong_strings_synth_act->setStatusTip(tr("Open AdjHeart Karpuls Strong Strings Synth"));
	connect(add_adj_karplus_strong_strings_synth_act, SIGNAL(triggered()), this, SLOT(on_add_adj_karplus_strong_strings_synth_instrument()));
	
	add_adj_morphed_sin_synth_act = new QAction(tr("&Morphed Sinus Synth"), this);
	add_adj_morphed_sin_synth_act->setStatusTip(tr("Open AdjHeart Morphed Sinus Synth"));
	connect(add_adj_morphed_sin_synth_act, SIGNAL(triggered()), this, SLOT(on_add_adj_morphed_sin_synth_instrument()));
	
	add_adj_pad_synth_act = new QAction(tr("&PADsynth"), this);
	add_adj_pad_synth_act->setStatusTip(tr("Open AdjHeart PADsynth Synth"));
	connect(add_adj_pad_synth_act, SIGNAL(triggered()), this, SLOT(on_add_adj_pad_synth_instrument()));
	
	add_adj_midi_player_act = new QAction(tr("&MIDI Player"), this);
	add_adj_midi_player_act->setStatusTip(tr("Open AdjHeart MIDI Player"));
	connect(add_adj_midi_player_act, SIGNAL(triggered()), this, SLOT(on_add_adj_midi_player_instrument()));
	
	add_adj_reverb_effect_act = new QAction(tr("&Reverb Edffect"), this);
	add_adj_reverb_effect_act->setStatusTip(tr("Open AdjHeart Reveb Effect"));
	connect(add_adj_reverb_effect_act, SIGNAL(triggered()), this, SLOT(on_add_adj_reverb_effect_instrument()));
	
	add_adj_distortion_effect_act = new QAction(tr("&Distortion Edffect"), this);
	add_adj_distortion_effect_act->setStatusTip(tr("Open AdjHeart Distortion Effect"));
	connect(add_adj_distortion_effect_act, SIGNAL(triggered()), this, SLOT(on_add_adj_distortion_effect_instrument()));
	
	add_adj_graphic_equilizer_act = new QAction(tr("&Graphic Equilizer"), this);
	add_adj_graphic_equilizer_act->setStatusTip(tr("Open AdjHeart Graphic Equilizer"));
	connect(add_adj_graphic_equilizer_act, SIGNAL(triggered()), this, SLOT(on_add_adj_graphic_equilizer_instrument()));
	
	add_midi_mixer_act = new QAction(tr("&Midi Mixer"), this);
	add_midi_mixer_act->setStatusTip(tr("Open Midi Mixer"));
	connect(add_midi_mixer_act, SIGNAL(triggered()), this, SLOT(on_add_midi_mixer_instrument()));
	
	add_adj_midi_mapper_act = new QAction(tr("&MIDI Mapper"), this);
	add_adj_midi_mapper_act->setStatusTip(tr("Open AdjHeart MIDI Mapper"));
	connect(add_adj_midi_mapper_act, SIGNAL(triggered()), this, SLOT(on_add_adj_midi_mapper_instrument()));

	add_adj_external_midi_interface_control_act = new QAction(tr("&External MIDI Interface Control"), this);
	add_adj_external_midi_interface_control_act->setStatusTip(tr("Open AdjHeart External MIDI Interface Control"));
	connect(add_adj_external_midi_interface_control_act, SIGNAL(triggered()), this, 
									SLOT(on_add_adj_external_midi_interface_control_instrument()));

	add_adj_keyboard_mapper_act = new QAction(tr("&Keyboard Mapper"), this);
	add_adj_keyboard_mapper_act->setStatusTip(tr("Open AdjHeart Keyboard Mapper"));
	connect(add_adj_keyboard_mapper_act, SIGNAL(triggered()), this, SLOT(on_add_adj_keyboard_mapper_instrument()));
	
	add_adj_keyboard_control_act = new QAction(tr("&Keyboard Control"), this);
	add_adj_keyboard_control_act->setStatusTip(tr("Open AdjHeart Keyboard Control"));
	connect(add_adj_keyboard_control_act, SIGNAL(triggered()), this, SLOT(on_add_adj_keyboard_control_instrument()));
	
	save_patch_file_act = new QAction(tr("&Save Patch File"), this);
	save_patch_file_act->setStatusTip(tr("Saves AdjHeart Patch File"));
	connect(save_patch_file_act, SIGNAL(triggered()), this, SLOT(on_save_patch_file()));
	
	load_patch_file_act = new QAction(tr("&Load Patch File"), this);
	load_patch_file_act->setStatusTip(tr("Loads AdjHeart Patch File"));
	connect(load_patch_file_act, SIGNAL(triggered()), this, SLOT(on_load_patch_file()));
	
	copy_sketch1_to_sketch2_act = new QAction(tr("&Copy Sketch 1 to Sketch 2"), this);
	copy_sketch1_to_sketch2_act->setStatusTip(tr("Copy Sketch 1 to Sketch 2"));
	connect(copy_sketch1_to_sketch2_act, SIGNAL(triggered()), this, SLOT(on_copy_sketch1_to_sketch2()));
	
	copy_sketch1_to_sketch3_act = new QAction(tr("&Copy Sketch 1 to Sketch 3"), this);
	copy_sketch1_to_sketch3_act->setStatusTip(tr("Copy Sketch 1 to Sketch 3"));
	connect(copy_sketch1_to_sketch3_act, SIGNAL(triggered()), this, SLOT(on_copy_sketch1_to_sketch3()));
	
	copy_sketch2_to_sketch1_act = new QAction(tr("&Copy Sketch 2 to Sketch 1"), this);
	copy_sketch2_to_sketch1_act->setStatusTip(tr("Copy Sketch 2 to Sketch 1"));
	connect(copy_sketch2_to_sketch1_act, SIGNAL(triggered()), this, SLOT(on_copy_sketch2_to_sketch1()));
	
	copy_sketch2_to_sketch3_act = new QAction(tr("&Copy Sketch 2 to Sketch 3"), this);
	copy_sketch2_to_sketch3_act->setStatusTip(tr("Copy Sketch 2 to Sketch 3"));
	connect(copy_sketch2_to_sketch3_act, SIGNAL(triggered()), this, SLOT(on_copy_sketch2_to_sketch3()));
	
	copy_sketch3_to_sketch1_act = new QAction(tr("&Copy Sketch 3 to Sketch 1"), this);
	copy_sketch3_to_sketch1_act->setStatusTip(tr("Copy Sketch 3 to Sketch 1"));
	connect(copy_sketch3_to_sketch1_act, SIGNAL(triggered()), this, SLOT(on_copy_sketch3_to_sketch1()));
	
	copy_sketch3_to_sketch2_act = new QAction(tr("&Copy Sketch 3 to Sketch 2"), this);
	copy_sketch3_to_sketch2_act->setStatusTip(tr("Copy Sketch 3 to Sketch 2"));
	connect(copy_sketch3_to_sketch2_act, SIGNAL(triggered()), this, SLOT(on_copy_sketch3_to_sketch2()));

	open_master_volume_act = new QAction(tr("&Master Volume"), this);
	open_master_volume_act->setStatusTip(tr("Open Master Volume Control"));
	connect(open_master_volume_act, SIGNAL(triggered()), this, SLOT(on_open_master_volume_dialog()));

	auto_arrange_act = new QAction(tr("&Auto Arrange"), this);
	auto_arrange_act->setStatusTip(tr("Enable/Disable automatic window arrangement"));
	auto_arrange_act->setCheckable(true); // Make it checkable
	auto_arrange_act->setChecked(false);  // Initial state
	connect(auto_arrange_act, SIGNAL(toggled(bool)), this, SLOT(on_auto_arrange_toggled(bool)));
	
	//add_modules_group = new QActionGroup(this);
	//add_modules_group->addAction(add_fluid_synth_act);
	
}

/**
*	@brief	Create the tools bar menus
*	@param	None
*	@return none
*/
void MainWindow::create_menus()
{
	file_menu = ui->menubar->addMenu(tr("&File"));
	file_menu->addAction(save_patch_file_act);
	file_menu->addAction(load_patch_file_act);
	file_menu->addSeparator();

	controls_menu = ui->menubar->addMenu(tr("&Controls"));
	controls_menu->addAction(open_master_volume_act);

	view_menu = ui->menubar->addMenu(tr("&View"));
	view_menu->addAction(auto_arrange_act);

	add_module_menu = ui->menubar->addMenu(tr("&Add Instrument"));
	add_module_menu->addAction(add_fluid_synth_act);
	add_module_menu->addAction(add_hammond_organ_act);
	add_module_menu->addAction(add_adj_analog_synth_act);
	add_module_menu->addAction(add_adj_karplus_strong_strings_synth_act);
	add_module_menu->addAction(add_adj_morphed_sin_synth_act);
	add_module_menu->addAction(add_adj_pad_synth_act);
	add_module_menu->addSeparator();
	add_module_menu->addAction(add_adj_midi_player_act);
	add_module_menu->addSeparator();
	add_module_menu->addAction(add_adj_reverb_effect_act);
	//d_module_menu->addAction(add_adj_distortion_effect_act);
	add_module_menu->addAction(add_adj_graphic_equilizer_act);
	add_module_menu->addSeparator();
	add_module_menu->addAction(add_midi_mixer_act);
	add_module_menu->addAction(add_adj_midi_mapper_act);
	add_module_menu->addSeparator();
	add_module_menu->addAction(add_adj_keyboard_mapper_act);
	add_module_menu->addAction(add_adj_keyboard_control_act);

	add_module_menu->addAction(add_adj_external_midi_interface_control_act);

	sketches_menu = ui->menubar->addMenu(tr("&Sketches"));
	sketches_menu->addAction(copy_sketch1_to_sketch2_act);
	sketches_menu->addAction(copy_sketch1_to_sketch3_act);
	sketches_menu->addAction(copy_sketch2_to_sketch1_act);
	sketches_menu->addAction(copy_sketch2_to_sketch3_act);
	sketches_menu->addAction(copy_sketch3_to_sketch1_act);
	sketches_menu->addAction(copy_sketch3_to_sketch2_act);	
	
	sketches_menu->setDisabled(true);

	// Add Window menu
	QMenu *windowMenu = ui->menubar->addMenu(tr("&Window"));

	QAction *windowManagerAction = new QAction(tr("Show Window Manager"), this);
	windowManagerAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_W));
	windowManagerAction->setStatusTip(tr("Show all open dialogs"));
	connect(windowManagerAction, SIGNAL(triggered()), this, SLOT(show_window_manager()));

	QAction *toggle_info_panel_action = new QAction("Toggle Navigator Info", this);
	connect(toggle_info_panel_action, &QAction::triggered, [this]() {
		GuiNavigator::get_instance()->toggle_info_panel();
	});

	windowMenu->addAction(windowManagerAction);
	windowMenu->addAction(toggle_info_panel_action);

	help_menu = ui->menubar->addMenu(tr("&Help"));
}
/**
*	@brief	Add an instrument pannel
*	@param	None
*	@return none
*/

InstrumentPannel *MainWindow::add_instrument_pannel(QString instrument_name_string)
{
	//QPoint last_position = QPoint(this->x(), this->y());

	if (instruments_ids_map.find(instrument_name_string.toStdString()) == instruments_ids_map.end())
	{
		return nullptr;
	}

	en_instruments_ids_t instrument_id = instruments_ids_map[instrument_name_string.toStdString()];

	if (instrument_id == en_instruments_ids_t::none_instrument_id)
	{
		return nullptr;
	}

	InstrumentPannel *new_pannel = new InstrumentPannel(this,
														instrument_name_string,
														&wrapper_close_instrument_pannel_id,
														instrument_id);

	// Set frame color based on type
	if (instrument_name_string == _INSTRUMENT_NAME_FLUID_SYNTH_STR_KEY ||
		instrument_name_string == _INSTRUMENT_NAME_HAMMON_ORGAN_STR_KEY ||
		instrument_name_string == _INSTRUMENT_NAME_ANALOG_SYNTH_STR_KEY ||
		instrument_name_string == _INSTRUMENT_NAME_KARPLUS_STRONG_STRING_SYNTH_STR_KEY ||
		instrument_name_string == _INSTRUMENT_NAME_MORPHED_SINUS_SYNTH_STR_KEY ||
		instrument_name_string == _INSTRUMENT_NAME_PAD_SYNTH_STR_KEY)
	{
		new_pannel->set_frame_color(_INSTRUMENT_PANNEL_FRAME_COLOR_PLAYER);
	}
	else if (instrument_name_string == _INSTRUMENT_NAME_MIDI_PLAYER_STR_KEY ||
			 instrument_name_string == _INSTRUMENT_NAME_MIDI_MIXER_STR_KEY ||
			 instrument_name_string == _INSTRUMENT_NAME_MIDI_MAPPER_STR_KEY ||
			 instrument_name_string == _INSTRUMENT_NAME_EXT_MIDI_INT_CONTROL_STR_KEY ||
			 instrument_name_string == _INSTRUMENT_NAME_KEYBOARD_MAPPER_STR_KEY ||
			 instrument_name_string == _INSTRUMENT_NAME_KEYBOARD_CONTROL_STR_KEY)
	{
		new_pannel->set_frame_color(_INSTRUMENT_PANNEL_FRAME_COLOR_CONTROL);
	}
	else if (instrument_name_string == _INSTRUMENT_NAME_REVERB_STR_KEY ||
			 instrument_name_string == _INSTRUMENT_NAME_DISTORTION_STR_KEY ||
			 instrument_name_string == _INSTRUMENT_NAME_GRAPHIC_EQUALIZER_STR_KEY)
	{
		new_pannel->set_frame_color(_INSTRUMENT_PANNEL_FRAME_COLOR_EFFECT);
	}

	active_instrument_data_t new_instrument;
	new_instrument.instrument_id = instrument_id;
	new_instrument.instrument_name = instrument_name_string;
	new_instrument.instrument_pannel_object = new_pannel;
	new_instrument.pending_close_event = false;
	active_instruments_list.push_back(new_instrument);

	// Rearrange all panels
	arrange_instrument_panels();

	//move(last_position);

	return new_pannel;
}

int MainWindow::remove_instrument_pannel(InstrumentPannel *instrument)
{
	if (instrument == nullptr)
	{
		return -1;
	}

	QGridLayout *gridLayout = qobject_cast<QGridLayout *>(ui->centralwidget->layout());
	if (gridLayout)
	{
		gridLayout->removeWidget(instrument);
	}

	instrument->hide();
	instrument->deleteLater();

	// Rearrange remaining panels
	arrange_instrument_panels();

	return 0;
}

/**
*   @brief Returns the instrument position in the active instruments list if th instrument is oppened.
*   @param  en_instrumentsIds_t					a unique enum identifier of each instrument type.
*	@return instrument position; -1 otherwise 
*/
int MainWindow::is_instrument_openned(en_instruments_ids_t instId)
{
	for (int i = 0; i < active_instruments_list.size(); ++i)
	{
		if (active_instruments_list[i].instrument_id == instId)
			return i;
	}
	
	return -1;
}

int MainWindow::update_layout_geometry()
{
	QGridLayout *gridLayout = qobject_cast<QGridLayout *>(ui->centralwidget->layout());
	if (!gridLayout)
	{
		return -1;
	}

	int panel_count = active_instruments_list.size();

	if (panel_count == 0)
	{
		return 0;
	}

	int rows = panel_count;
	int cols = 1;

	// When auto-arrange is disabled, always single column
	if (!auto_arrange_enabled)
	{
		rows = panel_count;
		cols = 1;
	}
	// When auto-arrange is enabled, use multiple columns
	else
	{
		if (panel_count <= 5)
		{
			rows = panel_count;
			cols = 1;
		}
		else if (panel_count <= 10)
		{
			rows = (panel_count + 1) / 2;
			cols = 2;
		}
		else
		{
			rows = (panel_count + 2) / 3;
			cols = 3;
		}
	}

	// Get actual panel dimensions from the first panel
	int panel_width = 280;	// Default width
	int panel_height = 120; // Default height

	if (!active_instruments_list.empty() &&
		active_instruments_list[0].instrument_pannel_object)
	{
		QSize panelSize = active_instruments_list[0].instrument_pannel_object->sizeHint();
		if (panelSize.isValid())
		{
			panel_width = panelSize.width();
			panel_height = panelSize.height();
		}
	}

	int spacing = 10;
	int margin = 20;
	int menubar_height = ui->menubar->height();

	int window_width = (cols * panel_width) + ((cols - 1) * spacing) + (2 * margin);
	int window_height = (rows * panel_height) + ((rows - 1) * spacing) + (2 * margin) + menubar_height;

	// Keep the current position, only resize
	QRect currentGeom = this->geometry();
	QRect newGeom = QRect(currentGeom.x(), currentGeom.y(), window_width, window_height);

	// Ensure window stays on screen
	QRect screenGeom = QApplication::desktop()->availableGeometry(this);
	if (newGeom.y() < screenGeom.y())
	{
		newGeom.moveTop(screenGeom.y());
	}
	if (newGeom.x() < screenGeom.x())
	{
		newGeom.moveLeft(screenGeom.x());
	}

	this->setGeometry(newGeom);

	return 0;
}

void MainWindow::close_instrument_pannel_id(en_instruments_ids_t inst_id)
{
	InstrumentPannel *instrument;
	
	int pos = is_instrument_openned(inst_id);
	
	if (pos >= 0)
	{
		instrument = active_instruments_list[pos].instrument_pannel_object;		
		active_instruments_list.erase(active_instruments_list.begin() + pos);
		
		remove_instrument_pannel(instrument);
	}
	
}

void MainWindow::close_instrument_pannel_name(string inst_name)
{
	if (instruments_ids_map.find(inst_name) != instruments_ids_map.end()) {
		// found
		close_instrument_pannel_id(instruments_ids_map[inst_name]);
	}
}

std::vector<std::string> MainWindow::get_active_instruments_names_list()
{
	std::vector<std::string> names_list_str;
	
	for (active_instrument_data_t module : active_instruments_list)
	{
		names_list_str.push_back(module.instrument_name.toStdString());
	}
	
	return names_list_str;
}

void MainWindow::request_close_instrument_pannel_id(en_instruments_ids_t inst_id)
{
	for (int m = 0; m < active_instruments_list.size(); m++)
	{
		if (active_instruments_list.at(m).instrument_id == inst_id)
		{
			active_instruments_list.at(m).pending_close_event = true;
			break;
		}
	}
}

void MainWindow::request_close_instrument_pannel_name(string inst_name)
{
	for (int m = 0; m < active_instruments_list.size(); m++)
	{
		if (active_instruments_list.at(m).instrument_name.toStdString() == inst_name)
		{
			active_instruments_list.at(m).pending_close_event = true;
			break;
		}
	}
}

void MainWindow::start_update_timer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
	timer->start(interval);
}

void MainWindow::timerEvent()
{
	update_gui();
}

void MainWindow::update_gui()
{
	int m;
	
	for (m = 0; m < active_instruments_list.size(); m++)
	{
		if (active_instruments_list.at(m).pending_close_event)
		{
			close_instrument_pannel_id(active_instruments_list.at(m).instrument_id);
		}
	}
	
	for (m = 0; m < pending_open_instruments_list.size(); m++)
	{
		add_instrument_pannel(QString::fromStdString(pending_open_instruments_list.at(m)));
	}
	
	pending_open_instruments_list.erase(pending_open_instruments_list.begin(),
		pending_open_instruments_list.begin() + m);

	if (control_box_right_key_pressed)
	{
		control_box_right_key_pressed = false;
		gui_navigator->handle_right_button();
	}

	if (control_box_left_key_pressed)
	{
		control_box_left_key_pressed = false;
		gui_navigator->handle_left_button();
	}

	if (control_box_up_key_pressed)
	{
		control_box_up_key_pressed = false;
		gui_navigator->handle_up_button();
	}

	if (control_box_down_key_pressed)
	{
		control_box_down_key_pressed = false;
		gui_navigator->handle_down_button();
	}

	if (control_box_ok_key_pressed)
	{
		control_box_ok_key_pressed = false;
		gui_navigator->handle_ok_button();
	}
	
	if (control_box_scroll_select_change_value)
	{
		control_box_scroll_select_change_value = false;
		if (control_box_scroll_select_prev_value == -1)
		{
			// 1st time
			control_box_scroll_select_prev_value = control_box_scroll_select_new_value;
			return; // Skip first time to establish baseline
		}
		
		gui_navigator->handle_scroll_rotation(control_box_scroll_select_new_value - control_box_scroll_select_prev_value);
		control_box_scroll_select_prev_value = control_box_scroll_select_new_value;
	}
	
	if (control_box_scroll_pushbutton_pressed)
	{
		control_box_scroll_pushbutton_pressed = false;
		gui_navigator->handle_scroll_button();
	}
}

void MainWindow::on_add_fluid_synth_instrument()
{
	InstrumentPannel *newPannel;

	if ((is_instrument_openned(en_instruments_ids_t::fluid_synth) < 0) &&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_FLUID_SYNTH_STR_KEY);
		newPannel->set_frame_color(_INSTRUMENT_PANNEL_FRAME_COLOR_PLAYER);
	}
}

void MainWindow::on_add_hammond_organ_instrument()
{
	InstrumentPannel *newPannel;

	if ((is_instrument_openned(en_instruments_ids_t::adj_hammond_organ) < 0) &&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_HAMMON_ORGAN_STR_KEY);
		newPannel->set_frame_color(_INSTRUMENT_PANNEL_FRAME_COLOR_PLAYER);
	}
}

void MainWindow::on_add_adj_analog_synth_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_analog_synth) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_ANALOG_SYNTH_STR_KEY);
		newPannel->set_frame_color(_INSTRUMENT_PANNEL_FRAME_COLOR_PLAYER);
	}
	
	
}

void MainWindow::on_add_adj_karplus_strong_strings_synth_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_karplusstrong_string_synth) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_KARPLUS_STRONG_STRING_SYNTH_STR_KEY);
		newPannel->set_frame_color(_INSTRUMENT_PANNEL_FRAME_COLOR_PLAYER);
	}
}

void MainWindow::on_add_adj_morphed_sin_synth_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_morphed_sin_synth) < 0) &&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_MORPHED_SINUS_SYNTH_STR_KEY);
		newPannel->set_frame_color(_INSTRUMENT_PANNEL_FRAME_COLOR_PLAYER);
	}
}

void MainWindow::on_add_adj_pad_synth_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_pad_synth) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_PAD_SYNTH_STR_KEY);
		newPannel->set_frame_color(_INSTRUMENT_PANNEL_FRAME_COLOR_PLAYER);
	}
}

void MainWindow::on_add_adj_midi_player_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_midi_player) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_MIDI_PLAYER_STR_KEY);
		newPannel->set_frame_color(_INSTRUMENT_PANNEL_FRAME_COLOR_CONTROL);
	}
}

void MainWindow::on_add_adj_reverb_effect_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_reverb_effect) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_REVERB_STR_KEY);
		newPannel->set_frame_color(_INSTRUMENT_PANNEL_FRAME_COLOR_EFFECT);
	}
}

void MainWindow::on_add_adj_distortion_effect_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_distortion_effect) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_DISTORTION_STR_KEY);
		newPannel->set_frame_color(_INSTRUMENT_PANNEL_FRAME_COLOR_EFFECT);
	}
}

void MainWindow::on_add_adj_graphic_equilizer_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_graphic_equilizer) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_GRAPHIC_EQUALIZER_STR_KEY);
		newPannel->set_frame_color(_INSTRUMENT_PANNEL_FRAME_COLOR_EFFECT);
	}
}

void MainWindow::on_add_midi_mixer_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::midi_mixer) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_MIDI_MIXER_STR_KEY);
		newPannel->set_frame_color(_INSTRUMENT_PANNEL_FRAME_COLOR_CONTROL);
	}
}

void MainWindow::on_add_adj_midi_mapper_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_midi_mapper) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_MIDI_MAPPER_STR_KEY);
		newPannel->set_frame_color(_INSTRUMENT_PANNEL_FRAME_COLOR_CONTROL);
	}
}

void MainWindow::on_add_adj_external_midi_interface_control_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_ext_midi_interface) < 0) &&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_EXT_MIDI_INT_CONTROL_STR_KEY);

		newPannel->hide_checkBox_InstrumentMIDIin();
		newPannel->set_frame_color(_INSTRUMENT_PANNEL_FRAME_COLOR_CONTROL);
	}
}

void MainWindow::on_add_adj_keyboard_control_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_keyboard_control) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_KEYBOARD_CONTROL_STR_KEY);
		newPannel->set_frame_color(_INSTRUMENT_PANNEL_FRAME_COLOR_CONTROL);
	}
}

void MainWindow::on_add_adj_keyboard_mapper_instrument()
{
	InstrumentPannel *newPannel;

	if ((is_instrument_openned(en_instruments_ids_t::adj_keyboard_mapper) < 0) &&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_KEYBOARD_MAPPER_STR_KEY);
		newPannel->set_frame_color(_INSTRUMENT_PANNEL_FRAME_COLOR_CONTROL);
	}
}

void MainWindow::on_save_patch_file()
{
	// Create dialog explicitly instead of using static method
	QFileDialog *dialog = new QFileDialog(this,
										  tr("Save Patch File "),
										  QString(_PATCHES_FILES_DEFAULT_DIR),
										  tr("Presets (*.json *.JSON);;All Files (*)"));

	dialog->setAcceptMode(QFileDialog::AcceptSave);
	dialog->setFileMode(QFileDialog::AnyFile);
	dialog->setDefaultSuffix("json");

	connect(dialog, &QFileDialog::finished, [this, dialog](int result) {
		if (result == QDialog::Accepted)
		{
			QStringList files = dialog->selectedFiles();
			if (!files.isEmpty())
			{
				patch_file_name = files.first();

				if (!patch_file_name.isEmpty())
				{
					save_patch_file_thread = new SavePatchFileThread();

					connect(save_patch_file_thread,
							&SavePatchFileThread::finished,
							save_patch_file_thread,
							&QObject::deleteLater);
					connect(save_patch_file_thread,
							&SavePatchFileThread::savePatchFileDone,
							this,
							&MainWindow::on_patch_file_saved);

					save_patch_file_thread->start();
				}
			}
		}
		dialog->deleteLater();
	});

	dialog->open(); // GuiNavigator will handle focus automatically
}

void MainWindow::on_load_patch_file()
{
	// Create dialog explicitly instead of using static method
	QFileDialog *dialog = new QFileDialog(this,
										  tr("Open Patch File "),
										  QString(_PATCHES_FILES_DEFAULT_DIR),
										  tr("Presets (*.json *.JSON);;All Files (*)"));

	dialog->setAcceptMode(QFileDialog::AcceptOpen);
	dialog->setFileMode(QFileDialog::ExistingFile);

	connect(dialog, &QFileDialog::finished, [this, dialog](int result) {
		if (result == QDialog::Accepted)
		{
			QStringList files = dialog->selectedFiles();
			if (!files.isEmpty())
			{
				patch_file_name = files.first();

				if (!patch_file_name.isEmpty())
				{
					load_patch_file_thread = new LoadPatchFileThread();

					connect(load_patch_file_thread,
							&LoadPatchFileThread::finished,
							load_patch_file_thread,
							&QObject::deleteLater);
					connect(load_patch_file_thread,
							&LoadPatchFileThread::loadPatchFileDone,
							this,
							&MainWindow::on_patch_file_loaded);

					load_patch_file_thread->start();
				}
			}
		}
		dialog->deleteLater();
	});

	dialog->open(); // GuiNavigator will handle focus automatically
}
void MainWindow::on_copy_sketch1_to_sketch2()
{
	copy_sketch(0, 1);
}

void MainWindow::on_copy_sketch1_to_sketch3()
{
	copy_sketch(0, 2);
}

void MainWindow::on_copy_sketch2_to_sketch1()
{
	copy_sketch(1, 0);
}

void MainWindow::on_copy_sketch2_to_sketch3()
{
	copy_sketch(1, 2);
}

void MainWindow::on_copy_sketch3_to_sketch1()
{
	copy_sketch(2, 0);
}

void MainWindow::on_copy_sketch3_to_sketch2()
{
	copy_sketch(2, 1);
}

void MainWindow::on_open_master_volume_dialog()
{
	static Dialog_MasterVolume *master_volume_dialog = nullptr;

	if (!master_volume_dialog)
	{
		master_volume_dialog = Dialog_MasterVolume::get_instance(this);
		register_active_dialog(master_volume_dialog);

		// Register with window manager
		window_manager->register_dialog(master_volume_dialog, "Master Volume");

		// Connect destroy signal to unregister
		auto *dialog_ptr = master_volume_dialog;
		connect(master_volume_dialog, &QObject::destroyed, [this, dialog_ptr]() {
			window_manager->unregister_dialog(dialog_ptr);
		});

		// Position the dialog
		QPoint position = this->pos();
		position.setX(position.x() + 50);
		position.setY(position.y() + 50);
		master_volume_dialog->move(position);
	}

	if (master_volume_dialog->isHidden())
	{
		master_volume_dialog->show();
	}

	master_volume_dialog->raise();
	master_volume_dialog->activateWindow();
	master_volume_dialog->setFocus(Qt::ActiveWindowFocusReason);
}

void MainWindow::on_auto_arrange_toggled(bool checked)
{
	auto_arrange_enabled = checked;

	// Rearrange panels immediately when toggled
	arrange_instrument_panels();

	if (checked)
	{
		qDebug() << "Auto Arrange: ENABLED - Panels grouped by type";
	}
	else
	{
		qDebug() << "Auto Arrange: DISABLED - Panels in original order";
	}
}

void MainWindow::set_auto_arrange(bool enabled)
{
	auto_arrange_enabled = enabled;
	auto_arrange_act->setChecked(enabled); // Update menu checkbox
}

/**
 * @brief Get the type order for sorting panels (PLAYER=0, EFFECT=1, CONTROL=2)
 */
int MainWindow::get_panel_type_order(const QString &instrument_name)
{
	// PLAYER instruments
	if (instrument_name == _INSTRUMENT_NAME_FLUID_SYNTH_STR_KEY ||
		instrument_name == _INSTRUMENT_NAME_HAMMON_ORGAN_STR_KEY ||
		instrument_name == _INSTRUMENT_NAME_ANALOG_SYNTH_STR_KEY ||
		instrument_name == _INSTRUMENT_NAME_KARPLUS_STRONG_STRING_SYNTH_STR_KEY ||
		instrument_name == _INSTRUMENT_NAME_MORPHED_SINUS_SYNTH_STR_KEY ||
		instrument_name == _INSTRUMENT_NAME_PAD_SYNTH_STR_KEY)
	{
		return 0; // PLAYER
	}
	// EFFECT instruments
	else if (instrument_name == _INSTRUMENT_NAME_REVERB_STR_KEY ||
			 instrument_name == _INSTRUMENT_NAME_DISTORTION_STR_KEY ||
			 instrument_name == _INSTRUMENT_NAME_GRAPHIC_EQUALIZER_STR_KEY)
	{
		return 1; // EFFECT
	}
	// CONTROL instruments
	else
	{
		return 2; // CONTROL
	}
}

/**
 * @brief Arrange all instrument panels according to auto_arrange setting
 */
void MainWindow::arrange_instrument_panels()
{
	QGridLayout *gridLayout = qobject_cast<QGridLayout *>(ui->centralwidget->layout());
	if (!gridLayout)
	{
		return;
	}

	// Clear current layout
	while (QLayoutItem *item = gridLayout->takeAt(0))
	{
		item->widget()->setParent(nullptr);
		delete item;
	}

	// Clear any existing row/column stretches
	for (int i = 0; i < 10; i++)
	{
		gridLayout->setRowStretch(i, 0);
		gridLayout->setColumnStretch(i, 0);
	}

	// Get working copy of panels
	std::vector<active_instrument_data_t> panels_to_arrange = active_instruments_list;

	int panel_count = panels_to_arrange.size();

	if (panel_count == 0)
	{
		return;
	}

	int row = 0;
	int col = 0;

	// AUTO-ARRANGE DISABLED: Single column, original order
	if (!auto_arrange_enabled)
	{
		// Always single column when auto-arrange is disabled
		for (int i = 0; i < panel_count; i++)
		{
			gridLayout->addWidget(panels_to_arrange[i].instrument_pannel_object, i, 0);
		}
	}
	// AUTO-ARRANGE ENABLED: Multiple columns, sorted by type
	else
	{
		// Sort by type first, then by original order
		std::stable_sort(panels_to_arrange.begin(), panels_to_arrange.end(),
						 [this](const active_instrument_data_t &a, const active_instrument_data_t &b) {
							 return get_panel_type_order(a.instrument_name) <
									get_panel_type_order(b.instrument_name);
						 });

		// Determine layout based on panel count - ARRANGED IN COLUMNS
		if (panel_count <= 5)
		{
			// Single column
			for (int i = 0; i < panel_count; i++)
			{
				gridLayout->addWidget(panels_to_arrange[i].instrument_pannel_object, i, 0);
			}
		}
		else if (panel_count <= 10)
		{
			// 2 columns of up to 5 each, alternating
			for (int i = 0; i < panel_count; i++)
			{
				col = i % 2; // Alternate between column 0 and 1
				row = i / 2; // Row increments every 2 panels
				gridLayout->addWidget(panels_to_arrange[i].instrument_pannel_object, row, col);
			}
		}
		else
		{
			// 3 columns, alternating
			for (int i = 0; i < panel_count; i++)
			{
				col = i % 3; // Alternate between columns 0, 1, 2
				row = i / 3; // Row increments every 3 panels
				gridLayout->addWidget(panels_to_arrange[i].instrument_pannel_object, row, col);
			}
		}
	}

	// Set equal column widths (no stretching, use fixed size)
	gridLayout->setSizeConstraint(QLayout::SetFixedSize);

	// Re-parent widgets back to centralwidget
	for (auto &panel_data : panels_to_arrange)
	{
		panel_data.instrument_pannel_object->setParent(ui->centralwidget);
		panel_data.instrument_pannel_object->show();
	}

	// Update window geometry
	update_layout_geometry();
}



	
