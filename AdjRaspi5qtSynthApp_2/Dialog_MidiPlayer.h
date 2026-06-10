/**
 * @file		Dialog_MidiPlayer.h
 *	@author		Nahum Budin
 *	@author		Nahum Budin
 *	@date		2-Apr-2026
 *	@version	2.0
 *					1. Custom icons for the control buttons.
 *					2. Added support for loopback playing control.
 *					3. Added support for playback volume and speed control.
 *					4. Added support for retrieving midi file meta data.
 *
 *	@brief		Used for playing MIDI files
 *
 *	History:
 *			ver 1.0 11-Aug-2024 Initial version
 *
*/

#pragma once

#include <QDialog>
#include <QPushButton>
#include <QThread>

#include "libAdjRaspi5SynthAPI.h"

namespace Ui
{
	class Dialog_MidiPlayer;
}

class Dialog_MidiPlayer : public QDialog
{
	Q_OBJECT
		
public :
	
	~Dialog_MidiPlayer();
	
	static Dialog_MidiPlayer *get_instance(QWidget *parent = 0);
	
	
	void control_box_ui_update_callback(int evnt, uint16_t val);
	
	QPoint get_last_position();
	
	Ui::Dialog_MidiPlayer *ui;

public slots :
	virtual void timerEvent(); // Called by a Timer
	void closeEvent(QCloseEvent *event);
	void showEvent(QShowEvent *event);
	void moveEvent(QMoveEvent *event);
	bool event(QEvent *event);
	
	
protected slots :
	
	void on_open_file_clicked();
	
	void on_play_clicked();
	void on_pause_clicked();
	void on_stop_clicked();
	void on_backward_clicked();
	void on_forward_clicked();

	void on_enable_loopback_enable(bool enabled);

	void on_playback_volume_changed(int value);
	void on_playback_speed_changed(int value);

	void on_dialog_close();
	
	void on_midi_file_loaded(const QString &s);
	
protected:
	virtual void update_gui(); 
	
	
private:
	
	explicit Dialog_MidiPlayer(QWidget *parent = 0);
	
	static Dialog_MidiPlayer *dialog_adj_midi_player_instance;	
	
	func_ptr_void_void_t close_event_callback_ptr;
	
	void start_update_timer(int interval);

	void display_channel_utilization(midi_file_meta_data_t &meta_data);

	QPoint last_position;

	QString last_midi_directory; // Store last used directory
	QString last_midi_file;		 // Store last selected file
};

class OpenMidiPlayerFileThread : public QThread
{
	Q_OBJECT	
	void run();
	
signals:
	void resultReady(const QString &s);	
		
};
