/**
* @file		Dialog_MidiMapper.h
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

#ifndef DIALOG_MIDIMAPPER_H
#define DIALOG_MIDIMAPPER_H

#include <QDialog>
#include <QMutex>
#include <QPoint>
#include <QCloseEvent>
#include <QMoveEvent>
#include <vector>

using namespace std;

namespace Ui {
class Dialog_MidiMapper;
}

// Forward declarations
struct active_instrument_data_t;
enum class en_instruments_ids_t;

class Dialog_MidiMapper : public QDialog
{
	Q_OBJECT

public:
	explicit Dialog_MidiMapper(QWidget *parent = nullptr);
	~Dialog_MidiMapper();

	static Dialog_MidiMapper *get_instance(QWidget *parent = nullptr, bool showit = false);

	void control_box_event_received(int evnt, uint16_t val);

	void closeEvent(QCloseEvent *event) override;
	void moveEvent(QMoveEvent *event) override;
	bool event(QEvent *event) override;

	QPoint get_last_position();

	void set_close_event_callback(void (*callback)()) { close_event_callback_ptr = callback; }

signals:
	// Signal emitted from callback thread - will be queued to GUI thread
	void control_box_event_signal(int evnt, uint16_t val);

	// Signal to request GUI update from timer - will be queued to GUI thread
	void updateGuiRequested();

private slots:
	// Slot that handles control box events in GUI thread
	void handle_control_box_event(int evnt, uint16_t val);

	// Channel instrument change slots
	void ch_1_instrument_changed(int inst);
	void ch_2_instrument_changed(int inst);
	void ch_3_instrument_changed(int inst);
	void ch_4_instrument_changed(int inst);
	void ch_5_instrument_changed(int inst);
	void ch_6_instrument_changed(int inst);
	void ch_7_instrument_changed(int inst);
	void ch_8_instrument_changed(int inst);
	void ch_9_instrument_changed(int inst);
	void ch_10_instrument_changed(int inst);
	void ch_11_instrument_changed(int inst);
	void ch_12_instrument_changed(int inst);
	void ch_13_instrument_changed(int inst);
	void ch_14_instrument_changed(int inst);
	void ch_15_instrument_changed(int inst);
	void ch_16_instrument_changed(int inst);
	void set_all_channels_instrument_changed(int inst);

	void on_dialog_close();

	// Timer slot
	void timerEvent();

	// GUI update slots - now runs in main thread
	void update_gui();
	void update_channels_combo_boxes();

private:
	Ui::Dialog_MidiMapper *ui;

	static Dialog_MidiMapper *dialog_adj_midi_mapper_instance;

	QPoint last_position;

	void (*close_event_callback_ptr)();

	QMutex *active_instruments_mutex;

	QComboBox *channels_combos[17];

	typedef void (Dialog_MidiMapper::*on_channel_combo_change_slot)(int);
	on_channel_combo_change_slot on_channel_combo_change_slots[16];

	void start_update_timer(int interval);

	int set_channel_instrument(int ch, int inst);
};

#endif // DIALOG_MIDIMAPPER_H
