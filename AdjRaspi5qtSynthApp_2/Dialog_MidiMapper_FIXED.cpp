/**
* @file		Dialog_MidiMapper.cpp
*	@author		Nahum Budin
*	@date		22-Sep-2025
*	@version	1.2
*					1.2 - FIXED: Removed UpdateGuiThread, fixed thread-safety issues
*					1.1 - Refactoring rename nodules to instruments
*					      Reserving vectors size.
*					      Add a mutex
*
*	@brief		Used for mapping MIDI channels events to instruments
*				
*	History:
*				Ver1.0	19-Oct-2024		Initial 
*
*/

#include <QObject>
#include <QTimer>
#include <QMoveEvent>
#include <QMessageBox>
#include <QMutexLocker>

#include "MainWindow.h"
#include "Dialog_MidiMapper.h"
#include "ui_Dialog_MidiMapper.h"
#include "Defs.h"

// Global mutex - only used for protecting shared data structures, NOT for GUI operations
QMutex qmutex;

// Shared data structures
vector<active_instrument_data_t> active_synth_instruments, prev_active_synth_instruments;
vector<active_instrument_data_t> added_synth_instruments, removed_synth_instruments;
vector<active_instrument_data_t> active_instruments_data;

int channels_combo_box_selection_index[17] = { 0 };
active_instrument_data_t channels_combo_box_selected_instrument_data[17];

bool found;

void midi_mapper_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	// Just forward to the dialog instance - it will emit a signal
	Dialog_MidiMapper::get_instance()->control_box_event_received(evnt, val);
}

Dialog_MidiMapper *Dialog_MidiMapper::dialog_adj_midi_mapper_instance = NULL;

Dialog_MidiMapper::Dialog_MidiMapper(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::Dialog_MidiMapper)
{
	ui->setupUi(this);
	dialog_adj_midi_mapper_instance = this;

	active_synth_instruments.reserve(_MAX_NUM_OF_INSTRUMENTS);
	active_synth_instruments.clear();

	prev_active_synth_instruments.reserve(_MAX_NUM_OF_INSTRUMENTS);
	prev_active_synth_instruments.clear();

	active_instruments_data.reserve(_MAX_NUM_OF_INSTRUMENTS);
	active_instruments_data.clear();

	added_synth_instruments.reserve(_MAX_NUM_OF_INSTRUMENTS);
	added_synth_instruments.clear();

	removed_synth_instruments.reserve(_MAX_NUM_OF_INSTRUMENTS);
	removed_synth_instruments.clear();	

	move(100, 100);

	this->setFocus(Qt::ActiveWindowFocusReason);

	close_event_callback_ptr = NULL;

	// Connect signal to slot with Qt::QueuedConnection for thread-safety
	// This ensures the slot runs in the GUI thread
	connect(this, &Dialog_MidiMapper::control_box_event_signal,
			this, &Dialog_MidiMapper::handle_control_box_event,
			Qt::QueuedConnection);

	// Connect GUI update signal to slot - runs in main thread
	connect(this, &Dialog_MidiMapper::updateGuiRequested,
			this, &Dialog_MidiMapper::update_gui,
			Qt::QueuedConnection);

	mod_synth_register_callback_control_box_event_update_ui(
		&midi_mapper_control_box_event_update_ui_callback_wrapper);

	MainWindow::get_instance()->register_active_dialog(this);

	// Register with GuiNavigator (no tabs for MIDI Mixer, but has frames)
	QList<QString> frame_names;
	frame_names << "Channel 1-8" << "Channel 9-16";

	GuiNavigator::get_instance()->register_dialog(
		this,
		"MIDI Mixer",
		nullptr,									// No tab widget
		QMap<int, QList<QString>>{{0, frame_names}} // All frames in tab 0 (no tabs)
	);

	channels_combos[0] = ui->comboBox_MidiMapperCh_1;
	channels_combos[1] = ui->comboBox_MidiMapperCh_2;
	channels_combos[2] = ui->comboBox_MidiMapperCh_3;
	channels_combos[3] = ui->comboBox_MidiMapperCh_4;
	channels_combos[4] = ui->comboBox_MidiMapperCh_5;
	channels_combos[5] = ui->comboBox_MidiMapperCh_6;
	channels_combos[6] = ui->comboBox_MidiMapperCh_7;
	channels_combos[7] = ui->comboBox_MidiMapperCh_8;
	channels_combos[8] = ui->comboBox_MidiMapperCh_9;
	channels_combos[9] = ui->comboBox_MidiMapperCh_10;
	channels_combos[10] = ui->comboBox_MidiMapperCh_11;
	channels_combos[11] = ui->comboBox_MidiMapperCh_12;
	channels_combos[12] = ui->comboBox_MidiMapperCh_13;
	channels_combos[13] = ui->comboBox_MidiMapperCh_14;
	channels_combos[14] = ui->comboBox_MidiMapperCh_15;
	channels_combos[15] = ui->comboBox_MidiMapperCh_16;
	channels_combos[16] = ui->comboBox_MidiMapperSetAll;

	on_channel_combo_change_slots[0] = &Dialog_MidiMapper::ch_1_instrument_changed;
	on_channel_combo_change_slots[1] = &Dialog_MidiMapper::ch_2_instrument_changed;
	on_channel_combo_change_slots[2] = &Dialog_MidiMapper::ch_3_instrument_changed;
	on_channel_combo_change_slots[3] = &Dialog_MidiMapper::ch_4_instrument_changed;
	on_channel_combo_change_slots[4] = &Dialog_MidiMapper::ch_5_instrument_changed;
	on_channel_combo_change_slots[5] = &Dialog_MidiMapper::ch_6_instrument_changed;
	on_channel_combo_change_slots[6] = &Dialog_MidiMapper::ch_7_instrument_changed;
	on_channel_combo_change_slots[7] = &Dialog_MidiMapper::ch_8_instrument_changed;
	on_channel_combo_change_slots[8] = &Dialog_MidiMapper::ch_9_instrument_changed;
	on_channel_combo_change_slots[9] = &Dialog_MidiMapper::ch_10_instrument_changed;
	on_channel_combo_change_slots[10] = &Dialog_MidiMapper::ch_11_instrument_changed;
	on_channel_combo_change_slots[11] = &Dialog_MidiMapper::ch_12_instrument_changed;
	on_channel_combo_change_slots[12] = &Dialog_MidiMapper::ch_13_instrument_changed;
	on_channel_combo_change_slots[13] = &Dialog_MidiMapper::ch_14_instrument_changed;
	on_channel_combo_change_slots[14] = &Dialog_MidiMapper::ch_15_instrument_changed;
	on_channel_combo_change_slots[15] = &Dialog_MidiMapper::ch_16_instrument_changed;

	update_channels_combo_boxes();

	connect(ui->comboBox_MidiMapperCh_1,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_1_instrument_changed(int)));

	connect(ui->comboBox_MidiMapperCh_2,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_2_instrument_changed(int)));

	connect(ui->comboBox_MidiMapperCh_3,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_3_instrument_changed(int)));

	connect(ui->comboBox_MidiMapperCh_4,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_4_instrument_changed(int)));

	connect(ui->comboBox_MidiMapperCh_5,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_5_instrument_changed(int)));

	connect(ui->comboBox_MidiMapperCh_6,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_6_instrument_changed(int)));

	connect(ui->comboBox_MidiMapperCh_7,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_7_instrument_changed(int)));

	connect(ui->comboBox_MidiMapperCh_8,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_8_instrument_changed(int)));

	connect(ui->comboBox_MidiMapperCh_9,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_9_instrument_changed(int)));

	connect(ui->comboBox_MidiMapperCh_10,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_10_instrument_changed(int)));

	connect(ui->comboBox_MidiMapperCh_11,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_11_instrument_changed(int)));

	connect(ui->comboBox_MidiMapperCh_12,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_12_instrument_changed(int)));

	connect(ui->comboBox_MidiMapperCh_13,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_13_instrument_changed(int)));

	connect(ui->comboBox_MidiMapperCh_14,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_14_instrument_changed(int)));

	connect(ui->comboBox_MidiMapperCh_15,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_15_instrument_changed(int)));

	connect(ui->comboBox_MidiMapperCh_16,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_16_instrument_changed(int)));

	connect(ui->comboBox_MidiMapperSetAll,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(set_all_channels_instrument_changed(int)));

	connect(ui->pushButton_MidiMapperOK,
		SIGNAL(clicked()),
		this,
		SLOT(on_dialog_close()));

	active_instruments_mutex = new QMutex();

	// Start a periodic timer - 200ms interval
	start_update_timer(200);
}

Dialog_MidiMapper::~Dialog_MidiMapper()
{
	delete active_instruments_mutex;
	delete ui;
}

Dialog_MidiMapper *Dialog_MidiMapper::get_instance(QWidget *parent, bool showit)
{
	if (dialog_adj_midi_mapper_instance == NULL)
	{
		dialog_adj_midi_mapper_instance = new Dialog_MidiMapper(parent);
	}

	if (showit)
	{
		dialog_adj_midi_mapper_instance->show();
	}

	return dialog_adj_midi_mapper_instance;
}

// Thread-safe function called from callback - just emits signal
void Dialog_MidiMapper::control_box_event_received(int evnt, uint16_t val)
{
	// Emit signal - Qt will queue it to run in GUI thread
	emit control_box_event_signal(evnt, val);
}

void Dialog_MidiMapper::closeEvent(QCloseEvent *event)
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

void Dialog_MidiMapper::moveEvent(QMoveEvent *event) {
	QWidget::moveEvent(event); // Call the base class implementation first

	last_position = event->pos();
}

bool Dialog_MidiMapper::event(QEvent *event)
{
	return QWidget::event(event);
}

int Dialog_MidiMapper::set_channel_instrument(int ch, int inst)
{
	en_instruments_ids_t instrument_id;

	// Only lock for reading shared data
	qmutex.lock();

	if (inst == 0)
	{
		instrument_id = en_instruments_ids_t::none_instrument_id;
	}
	else
	{
		instrument_id = channels_combo_box_selected_instrument_data[ch].instrument_id;
	}

	qmutex.unlock();

	mod_synth_allocate_midi_channel_synth(ch, instrument_id);

	return 0;
}

void Dialog_MidiMapper::ch_1_instrument_changed(int inst)
{	
	qmutex.lock();
	channels_combo_box_selection_index[0] = inst;
	if (inst == 0)
	{
		channels_combo_box_selected_instrument_data[0] = en_instruments_ids_t::none_instrument_id;
	}
	else
	{
		channels_combo_box_selected_instrument_data[0] = active_instruments_data[inst - 1];
	}
	qmutex.unlock();

	set_channel_instrument(0, inst);
}

void Dialog_MidiMapper::ch_2_instrument_changed(int inst)
{	
	qmutex.lock();
	channels_combo_box_selection_index[1] = inst;

	if (inst == 0)
	{
		channels_combo_box_selected_instrument_data[1] = en_instruments_ids_t::none_instrument_id;
	}
	else
	{
		channels_combo_box_selected_instrument_data[1] = active_instruments_data[inst - 1];
	}
	qmutex.unlock();

	set_channel_instrument(1, inst);
}

void Dialog_MidiMapper::ch_3_instrument_changed(int inst)
{
	qmutex.lock();
	channels_combo_box_selection_index[2] = inst;

	if (inst == 0)
	{
		channels_combo_box_selected_instrument_data[2] = en_instruments_ids_t::none_instrument_id;
	}
	else
	{
		channels_combo_box_selected_instrument_data[2] = active_instruments_data[inst - 1];
	}
	qmutex.unlock();

	set_channel_instrument(2, inst);
}

void Dialog_MidiMapper::ch_4_instrument_changed(int inst)
{
	qmutex.lock();
	channels_combo_box_selection_index[3] = inst;

	if (inst == 0)
	{
		channels_combo_box_selected_instrument_data[3] = en_instruments_ids_t::none_instrument_id;
	}
	else
	{
		channels_combo_box_selected_instrument_data[3] = active_instruments_data[inst - 1];
	}
	qmutex.unlock();

	set_channel_instrument(3, inst);
}

void Dialog_MidiMapper::ch_5_instrument_changed(int inst)
{
	qmutex.lock();
	channels_combo_box_selection_index[4] = inst;

	if (inst == 0)
	{
		channels_combo_box_selected_instrument_data[4] = en_instruments_ids_t::none_instrument_id;
	}
	else
	{
		channels_combo_box_selected_instrument_data[4] = active_instruments_data[inst - 1];
	}
	qmutex.unlock();

	set_channel_instrument(4, inst);
}

void Dialog_MidiMapper::ch_6_instrument_changed(int inst)
{
	qmutex.lock();
	channels_combo_box_selection_index[5] = inst;

	if (inst == 0)
	{
		channels_combo_box_selected_instrument_data[5] = en_instruments_ids_t::none_instrument_id;
	}
	else
	{
		channels_combo_box_selected_instrument_data[5] = active_instruments_data[inst - 1];
	}
	qmutex.unlock();

	set_channel_instrument(5, inst);
}

void Dialog_MidiMapper::ch_7_instrument_changed(int inst)
{
	qmutex.lock();
	channels_combo_box_selection_index[6] = inst;

	if (inst == 0)
	{
		channels_combo_box_selected_instrument_data[6] = en_instruments_ids_t::none_instrument_id;
	}
	else
	{
		channels_combo_box_selected_instrument_data[6] = active_instruments_data[inst - 1];
	}
	qmutex.unlock();

	set_channel_instrument(6, inst);
}

void Dialog_MidiMapper::ch_8_instrument_changed(int inst)
{
	qmutex.lock();
	channels_combo_box_selection_index[7] = inst;

	if (inst == 0)
	{
		channels_combo_box_selected_instrument_data[7] = en_instruments_ids_t::none_instrument_id;
	}
	else
	{
		channels_combo_box_selected_instrument_data[7] = active_instruments_data[inst - 1];
	}
	qmutex.unlock();

	set_channel_instrument(7, inst);
}

void Dialog_MidiMapper::ch_9_instrument_changed(int inst)
{
	qmutex.lock();
	channels_combo_box_selection_index[8] = inst;

	if (inst == 0)
	{
		channels_combo_box_selected_instrument_data[8] = en_instruments_ids_t::none_instrument_id;
	}
	else
	{
		channels_combo_box_selected_instrument_data[8] = active_instruments_data[inst - 1];
	}
	qmutex.unlock();

	set_channel_instrument(8, inst);
}

void Dialog_MidiMapper::ch_10_instrument_changed(int inst)
{
	qmutex.lock();
	channels_combo_box_selection_index[9] = inst;

	if (inst == 0)
	{
		channels_combo_box_selected_instrument_data[9] = en_instruments_ids_t::none_instrument_id;
	}
	else
	{
		channels_combo_box_selected_instrument_data[9] = active_instruments_data[inst - 1];
	}
	qmutex.unlock();

	set_channel_instrument(9, inst);
}

void Dialog_MidiMapper::ch_11_instrument_changed(int inst)
{
	qmutex.lock();
	channels_combo_box_selection_index[10] = inst;

	if (inst == 0)
	{
		channels_combo_box_selected_instrument_data[10] = en_instruments_ids_t::none_instrument_id;
	}
	else
	{
		channels_combo_box_selected_instrument_data[10] = active_instruments_data[inst - 1];
	}
	qmutex.unlock();

	set_channel_instrument(10, inst);
}

void Dialog_MidiMapper::ch_12_instrument_changed(int inst)
{
	qmutex.lock();
	channels_combo_box_selection_index[11] = inst;

	if (inst == 0)
	{
		channels_combo_box_selected_instrument_data[11] = en_instruments_ids_t::none_instrument_id;
	}
	else
	{
		channels_combo_box_selected_instrument_data[11] = active_instruments_data[inst - 1];
	}
	qmutex.unlock();

	set_channel_instrument(11, inst);
}

void Dialog_MidiMapper::ch_13_instrument_changed(int inst)
{
	qmutex.lock();
	channels_combo_box_selection_index[12] = inst;

	if (inst == 0)
	{
		channels_combo_box_selected_instrument_data[12] = en_instruments_ids_t::none_instrument_id;
	}
	else
	{
		channels_combo_box_selected_instrument_data[12] = active_instruments_data[inst - 1];
	}
	qmutex.unlock();

	set_channel_instrument(12, inst);
}

void Dialog_MidiMapper::ch_14_instrument_changed(int inst)
{
	qmutex.lock();
	channels_combo_box_selection_index[13] = inst;

	if (inst == 0)
	{
		channels_combo_box_selected_instrument_data[13] = en_instruments_ids_t::none_instrument_id;
	}
	else
	{
		channels_combo_box_selected_instrument_data[13] = active_instruments_data[inst - 1];
	}
	qmutex.unlock();

	set_channel_instrument(13, inst);
}

void Dialog_MidiMapper::ch_15_instrument_changed(int inst)
{
	qmutex.lock();
	channels_combo_box_selection_index[14] = inst;

	if (inst == 0)
	{
		channels_combo_box_selected_instrument_data[14] = en_instruments_ids_t::none_instrument_id;
	}
	else
	{
		channels_combo_box_selected_instrument_data[14] = active_instruments_data[inst - 1];
	}
	qmutex.unlock();

	set_channel_instrument(14, inst);
}

void Dialog_MidiMapper::ch_16_instrument_changed(int inst)
{
	qmutex.lock();
	channels_combo_box_selection_index[15] = inst;

	if (inst == 0)
	{
		channels_combo_box_selected_instrument_data[15] = en_instruments_ids_t::none_instrument_id;
	}
	else
	{
		channels_combo_box_selected_instrument_data[15] = active_instruments_data[inst - 1];
	}
	qmutex.unlock();

	set_channel_instrument(15, inst);
}

void Dialog_MidiMapper::set_all_channels_instrument_changed(int inst)
{
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::QMessageBox::Warning);
	msgBox.setWindowTitle("Warning?");
	msgBox.setText("Are you sure you want to set all channels instrument?\nAll current settings will be lost!");
	msgBox.setStandardButtons(QMessageBox::Yes);
	msgBox.addButton(QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	if (msgBox.exec() == QMessageBox::Yes)
	{
		for (int ch = 0; ch < 16; ch++)
		{
			channels_combos[ch]->blockSignals(true);
			channels_combos[ch]->setCurrentIndex(inst);
			(this->*on_channel_combo_change_slots[ch])(inst);
			channels_combos[ch]->blockSignals(false);
		}
	}
}

void Dialog_MidiMapper::handle_control_box_event(int evnt, uint16_t val)
{	
	if (!this->hasFocus())
	{
		return;
	}

	if (evnt == _CONTROL_PUSHBUTTON_BLUE_GREEN)
	{
		// Handle control box event
	}	
}

QPoint Dialog_MidiMapper::get_last_position()
{	
	return last_position;
}

void Dialog_MidiMapper::on_dialog_close()
{
	hide();
}

void Dialog_MidiMapper::start_update_timer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
	timer->start(interval);
}

// FIXED: Timer now just emits a signal instead of creating threads
void Dialog_MidiMapper::timerEvent()
{
	// Emit signal - will be queued to run update_gui() in main thread
	emit updateGuiRequested();
}

// FIXED: This method now runs in the main GUI thread via signal/slot mechanism
void Dialog_MidiMapper::update_channels_combo_boxes()
{
	// Lock only for reading shared data, NOT for widget operations
	qmutex.lock();

	bool last_selected = false;

	for (int ch = 0; ch <= 16; ch++)
	{
		channels_combos[ch]->blockSignals(true);
		channels_combos[ch]->clear();
		channels_combos[ch]->addItem(QString("--------------"));

		int i = 1;
		for (active_instrument_data_t module : active_instruments_data)
		{
			channels_combos[ch]->addItem(QString(module.instrument_name));

			/* Locate the last selected item */
			if (module.instrument_id == channels_combo_box_selected_instrument_data[ch].instrument_id)
			{
				channels_combo_box_selection_index[ch] = i;
				last_selected = true;
			}
			i++;
		}

		if (last_selected)
		{
			channels_combos[ch]->setCurrentIndex(channels_combo_box_selection_index[ch]);
			last_selected = false;
		}
		else
		{
			/* Last selected is no longer active. */
			channels_combo_box_selected_instrument_data[ch].instrument_id = en_instruments_ids_t::none_instrument_id;
			channels_combo_box_selection_index[ch] = 0;
			channels_combos[ch]->setCurrentIndex(0);

			if (ch < 16)
			{
				/* Skip the all channels selection */
				qmutex.unlock();
				mod_synth_allocate_midi_channel_synth(ch, en_instruments_ids_t::none_instrument_id);
				qmutex.lock();
			}
		}

		channels_combos[ch]->blockSignals(false);
	}

	qmutex.unlock();
}

// FIXED: This method now runs in the main GUI thread via signal/slot mechanism
void Dialog_MidiMapper::update_gui()
{	
	// Lock only for data operations, not GUI operations
	qmutex.lock();

	en_instruments_ids_t inst_id;
	static bool first_time = true;

	active_synth_instruments.clear();
	added_synth_instruments.clear();
	removed_synth_instruments.clear();

	/* Get all currently active instruments */
	for (active_instrument_data_t instrument : MainWindow::get_instance()->active_instruments_list)
	{
		if (mod_synth_get_instrument_type(instrument.instrument_id) == en_instruments_types_t::synth)
		{
			active_synth_instruments.push_back(instrument);
		}
	}

	if (active_synth_instruments.size() == 0)
	{
		/* No active instrument. */
		if (prev_active_synth_instruments.size() != 0)
		{
			/* All active instruments were just removed */			
			for (active_instrument_data_t prev_active_instrument : prev_active_synth_instruments)
			{
				removed_synth_instruments.push_back(prev_active_instrument);
			}
		}
	}
	else
	{
		/* There are active instruments. */
		if (prev_active_synth_instruments.size() == 0)
		{
			/* All active instruments were just added. */
			for (active_instrument_data_t active_module : active_synth_instruments)
			{
				added_synth_instruments.push_back(active_module);
			}
		}
		else
		{
			/* Some active instruments might be added and some might be removed. */
			/* Look for added instruments */
			for (active_instrument_data_t active_instrument : active_synth_instruments)
			{
				found = false;
				/* Check if active instrument was already in prev list */
				for (active_instrument_data_t prev_active_instrument : prev_active_synth_instruments)
				{
					if (active_instrument.instrument_id == prev_active_instrument.instrument_id)
					{
						found = true; 
					}
				}

				if (!found)
				{
					/* Was not found in prev list */
					added_synth_instruments.push_back(active_instrument);
				}
			}
			/* Look for removed instruments */
			for (active_instrument_data_t prev_active_instrument : prev_active_synth_instruments)
			{
				found = false;
				/* Check if prev instrument is still an active instrument */
				for (active_instrument_data_t active_instrument : active_synth_instruments)
				{
					if (active_instrument.instrument_id == prev_active_instrument.instrument_id)
					{
						found = true;
					}
				}

				if (!found)
				{
					/* No longer active */
					removed_synth_instruments.push_back(prev_active_instrument);
				}
			}			
		}
	}

	/* Update prev with current */
	prev_active_synth_instruments.clear();
	for (active_instrument_data_t instrument : active_synth_instruments)
	{
		prev_active_synth_instruments.push_back(instrument);
	}

	if (added_synth_instruments.size() > 0)
	{
		/* New modules added */
		for (active_instrument_data_t instrument : added_synth_instruments)
		{
			active_instruments_data.push_back(instrument);
		}

		qmutex.unlock();

		// Safe to call - we're in main thread now
		update_channels_combo_boxes();

		qmutex.lock();
	}

	if (removed_synth_instruments.size() > 0)
	{
		/* Prev module removed */
		for (active_instrument_data_t instrument : removed_synth_instruments)
		{
			int i = 0;
			for (active_instrument_data_t inst : active_instruments_data)
			{
				if (instrument.instrument_id == inst.instrument_id)
				{
					active_instruments_data.erase(active_instruments_data.begin() + i);
					break;
				}

				i++;
			}
		}

		qmutex.unlock();

		// Safe to call - we're in main thread now
		update_channels_combo_boxes();

		qmutex.lock();
	}

	qmutex.unlock();
}
