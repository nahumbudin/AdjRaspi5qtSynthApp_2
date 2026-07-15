/**
* @file		Dialog_InstrumentConnections.h
*	@author		Nahum Budin
*	@date		5-Jul-2024
*	@version	1.0
*
*	@brief		Used for selecting MIDI inputs and JackAudio outputs,
*				as well as the active MIDI channels
*
*/

#pragma once

#include <QDialog>
#include <QCheckBox>

#include "MainWindow.h"

#include "libAdjRaspi5SynthAPI.h"

#define _MIDI_PANNEL_SELECTED	0
#define _JACK_PANNEL_SELECTED	1

namespace Ui
{
	class Dialog_InstrumentConnections;
}

class Dialog_InstrumentConnections : public QDialog
{
	Q_OBJECT
		
public :
	explicit Dialog_InstrumentConnections(QWidget *parent = 0,
		QString inst_name = "");
	
	~Dialog_InstrumentConnections();
	
	static Dialog_InstrumentConnections *get_instance();

	// Called from callback - thread-safe, just emits signal
	void control_box_event_received(int evnt, uint16_t val);

	void update();
	
	static bool dialog_is_open;

  signals:
	// Signal emitted when control box event is received (thread-safe)
	void control_box_event_signal(int evnt, uint16_t val);

  private slots:
	// Slot that handles the actual UI update (runs in GUI thread)
	void handle_control_box_event(int evnt, uint16_t val);
	
public slots:
	void closeEvent(QCloseEvent *event);
	void showEvent(QShowEvent *event);

  protected slots:
	
	void on_dialog_ok();
	void on_dialog_refresh();
	
	void on_select_MIDI_pannel_clicked();
	void on_select_Jack_pannel_clicked();
	
	void on_select_midi_in_toggled_1(bool sel);
	void on_select_midi_in_toggled_2(bool sel);
	void on_select_midi_in_toggled_3(bool sel);
	void on_select_midi_in_toggled_4(bool sel);
	void on_select_midi_in_toggled_5(bool sel);
	void on_select_midi_in_toggled_6(bool sel);
	void on_select_midi_in_toggled_7(bool sel);
	void on_select_midi_in_toggled_8(bool sel);
	void on_select_midi_in_toggled_9(bool sel);
	void on_select_midi_in_toggled_10(bool sel);
	void on_select_midi_in_toggled_11(bool sel);
	void on_select_midi_in_toggled_12(bool sel);
	void on_select_midi_in_toggled_13(bool sel);
	void on_select_midi_in_toggled_14(bool sel);
	void on_select_midi_in_toggled_15(bool sel);
	void on_select_midi_in_toggled_16(bool sel);
	void on_select_midi_in_toggled_17(bool sel);
	void on_select_midi_in_toggled_18(bool sel);
	void on_select_midi_in_toggled_19(bool sel);
	void on_select_midi_in_toggled_20(bool sel);
	
	void on_select_jack_out_toggled_1(bool sel);
	void on_select_jack_out_toggled_2(bool sel);
	void on_select_jack_out_toggled_3(bool sel);
	void on_select_jack_out_toggled_4(bool sel);
	void on_select_jack_out_toggled_5(bool sel);
	void on_select_jack_out_toggled_6(bool sel);
	void on_select_jack_out_toggled_7(bool sel);
	void on_select_jack_out_toggled_8(bool sel);
	void on_select_jack_out_toggled_9(bool sel);
	void on_select_jack_out_toggled_10(bool sel);
	void on_select_jack_out_toggled_11(bool sel);
	void on_select_jack_out_toggled_12(bool sel);
	void on_select_jack_out_toggled_13(bool sel);
	void on_select_jack_out_toggled_14(bool sel);
	void on_select_jack_out_toggled_15(bool sel);
	void on_select_jack_out_toggled_16(bool sel);
	void on_select_jack_out_toggled_17(bool sel);
	void on_select_jack_out_toggled_18(bool sel);
	void on_select_jack_out_toggled_19(bool sel);
	void on_select_jack_out_toggled_20(bool sel);
	
	
private:
	
	Ui::Dialog_InstrumentConnections *ui;
	
	QString instrument_name;
	int client_number;
	
	QCheckBox *midi_input_clients_select_pb[20];
	QCheckBox *jack_output_clients_select_pb[20];
	
	std::string jack_output_client_names[10];
	std::string jack_output_client_port_names[10];
	
	static Dialog_InstrumentConnections *dialog_InstrumentConnectionsInstance;
	
	int selected_pannel;
	
	uint16_t active_midi_channels;
	
	std::string alsa_connections_names[20];
	std::string jack_connections_names[20];		
};
