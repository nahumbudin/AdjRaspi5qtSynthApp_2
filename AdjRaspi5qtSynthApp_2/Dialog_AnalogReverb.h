/**
 * @file		Dialog_AnalogReverb.h
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

#pragma once

#include <QDialog>

#include "ControlWidgetsColorManager.h"

namespace Ui
{
	class Dialog_AnalogReverb;
}

class Dialog_AnalogReverb : public QDialog
{
	Q_OBJECT

  public:
	~Dialog_AnalogReverb();

	static Dialog_AnalogReverb *get_instance(QWidget *parent = 0);

	// Called from callback - thread-safe, just emits signal
	void control_box_event_received(int evnt, uint16_t val);

  signals:
	// Signal emitted when control box event is received (thread-safe)
	void control_box_event_signal(int evnt, uint16_t val);

  private slots:
	// Slot that handles the actual UI update (runs in GUI thread)
	void handle_control_box_event(int evnt, uint16_t val);

  public slots:
	virtual void update_gui(); // Called by a Timer
	void closeEvent(QCloseEvent *event);

  protected slots:

	void on_dialog_close();

	// Freeverb 3 modified
	void on_reverb_3m_enable_checkbox_changed(bool val);
	void on_reverb_type_combobox_changed(int val);

	// Freverb
	void on_reverb_enable_checkbox_changed(bool val);
	void on_reverb_room_size_dial_changed(int val);
	void on_reverb_damp_dial_changed(int val);
	void on_reverb_wet_dial_changed(int val);
	void on_reverb_dry_dial_changed(int val);
	void on_reverb_width_dial_changed(int val);
	void on_reverb_mode_dial_changed(int val);

	void on_reverb_room_size_spinbox_changed(int val);
	void on_reverb_damp_spinbox_changed(int val);
	void on_reverb_wet_spinbox_changed(int val);
	void on_reverb_dry_spinbox_changed(int val);
	void on_reverb_width_spinbox_changed(int val);
	void on_reverb_mode_spinbox_changed(int val);

  protected:
	void timerEvent(QTimerEvent *event);

  private:
	explicit Dialog_AnalogReverb(QWidget *parent = 0);

	Ui::Dialog_AnalogReverb *ui;

	static Dialog_AnalogReverb *dialog_analog_reverb_instance;

	int init_reverb_gui();
	void init_reverb_combboxes_and_labels();
	void set_reverb_signals_connections();


	void start_update_timer(int interval);
	
	QList<QString> string_reverb_types_list;

	ControlWidgetsColorManager *control_widgets_color_manager;

	func_ptr_void_void_t close_event_callback_ptr;
};
