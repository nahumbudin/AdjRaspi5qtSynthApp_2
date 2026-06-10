/**
 * @file		Dialog_MidiMixer.cpp
 *	@author		Nahum Budin
 *	@date		22-Jan-2026
 *	@version	1.1
 *					1. New GUI layout 1620x840.
 *					2. Added pan modulationLFO selection and level control per channel.
 *					3. Added Send control per channel.
 *					4. Aded channel activity indication LED per channel.
 *
 *	@brief		Midi Mixer control dialog
 *
 *	@History:
 *
 *		Version 1.0	22-Aug-2024
 *
 */

#pragma once

#include <QDialog>
#include <QTHread>
#include <QSpinBox>
#include <QTextEdit>
#include <QMutex>

#include "libAdjRaspi5SynthAPI.h"


#include "CustomDial.h"
#include "CustomVerticalSlider.h"
#include "CustomComboBox.h"
#include "CustomCheckBox.h"
#include "ControlWidgetsColorManager.h"

#define _CHANNEL_ACTIVE_ON_TIME_COUNTER 1 // 0.25sec (assuming timer period of 250ms)

namespace Ui
{
	class Dialog_MidiMixer_1620x840;
}

class Dialog_MidiMixer : public QDialog
{
	Q_OBJECT
		
public :
	
	~Dialog_MidiMixer();
	
	static Dialog_MidiMixer *get_instance(QWidget *parent = 0);

	static Ui::Dialog_MidiMixer_1620x840 *get_ui_instance();

	// Called from callback - thread-safe, just emits signal
	void control_box_event_received(int evnt, uint16_t val);
	
	
	void channels_levels_update_callback(int chan, int vol);
	void channels_pans_update_callback(int chan, int vol);

	void channels_sends_update_callback(int chan, int send);

	void channels_pan_mod_lfo_level_update_callback(int chan, int lvl);
	void channels_pan_mod_lfo_update_callback(int chan, int lfo);

	void channels_static_levels_update_callback(int chan, bool state);
	void channels_program_update_callback(int chan, int prog);

	void channels_activity_update_callback(int chan, bool state);

	// Handle frame navigation
	void on_frame_changed(const QString &frame_name, int frame_index);

  signals:
	// Signal emitted when control box event is received (thread-safe)
	void control_box_event_signal(int evnt, uint16_t val);

  public slots:
	virtual void update_gui(); // Called by a Timer
	void closeEvent(QCloseEvent *event);
	void showEvent(QShowEvent *event);

  private slots:
	// Slot that handles the actual UI update (runs in GUI thread)
	void handle_control_box_event(int evnt, uint16_t val);
	
	protected slots :
	
		void on_dialog_close();
		
		void on_level_slider_changed_ch_1(int vol);
		void on_level_slider_changed_ch_2(int vol);
		void on_level_slider_changed_ch_3(int vol);
		void on_level_slider_changed_ch_4(int vol);
		void on_level_slider_changed_ch_5(int vol);
		void on_level_slider_changed_ch_6(int vol);
		void on_level_slider_changed_ch_7(int vol);
		void on_level_slider_changed_ch_8(int vol);
		void on_level_slider_changed_ch_9(int vol);
		void on_level_slider_changed_ch_10(int vol);
		void on_level_slider_changed_ch_11(int vol);
		void on_level_slider_changed_ch_12(int vol);
		void on_level_slider_changed_ch_13(int vol);
		void on_level_slider_changed_ch_14(int vol);
		void on_level_slider_changed_ch_15(int vol);
		void on_level_slider_changed_ch_16(int vol);
				
		void on_level_spinbox_changed_ch_1(int vol);
		void on_level_spinbox_changed_ch_2(int vol);
		void on_level_spinbox_changed_ch_3(int vol);
		void on_level_spinbox_changed_ch_4(int vol);
		void on_level_spinbox_changed_ch_5(int vol);
		void on_level_spinbox_changed_ch_6(int vol);
		void on_level_spinbox_changed_ch_7(int vol);
		void on_level_spinbox_changed_ch_8(int vol);
		void on_level_spinbox_changed_ch_9(int vol);
		void on_level_spinbox_changed_ch_10(int vol);
		void on_level_spinbox_changed_ch_11(int vol);
		void on_level_spinbox_changed_ch_12(int vol);
		void on_level_spinbox_changed_ch_13(int vol);
		void on_level_spinbox_changed_ch_14(int vol);
		void on_level_spinbox_changed_ch_15(int vol);
		void on_level_spinbox_changed_ch_16(int vol);
		
		void on_pan_dial_changed_ch_1(int pan);
		void on_pan_dial_changed_ch_2(int pan);
		void on_pan_dial_changed_ch_3(int pan);
		void on_pan_dial_changed_ch_4(int pan);
		void on_pan_dial_changed_ch_5(int pan);
		void on_pan_dial_changed_ch_6(int pan);
		void on_pan_dial_changed_ch_7(int pan);
		void on_pan_dial_changed_ch_8(int pan);
		void on_pan_dial_changed_ch_9(int pan);
		void on_pan_dial_changed_ch_10(int pan);
		void on_pan_dial_changed_ch_11(int pan);
		void on_pan_dial_changed_ch_12(int pan);
		void on_pan_dial_changed_ch_13(int pan);
		void on_pan_dial_changed_ch_14(int pan);
		void on_pan_dial_changed_ch_15(int pan);
		void on_pan_dial_changed_ch_16(int pan);

		void on_pan_spinbox_changed_ch_1(int pan);
		void on_pan_spinbox_changed_ch_2(int pan);
		void on_pan_spinbox_changed_ch_3(int pan);
		void on_pan_spinbox_changed_ch_4(int pan);
		void on_pan_spinbox_changed_ch_5(int pan);
		void on_pan_spinbox_changed_ch_6(int pan);
		void on_pan_spinbox_changed_ch_7(int pan);
		void on_pan_spinbox_changed_ch_8(int pan);
		void on_pan_spinbox_changed_ch_9(int pan);
		void on_pan_spinbox_changed_ch_10(int pan);
		void on_pan_spinbox_changed_ch_11(int pan);
		void on_pan_spinbox_changed_ch_12(int pan);
		void on_pan_spinbox_changed_ch_13(int pan);
		void on_pan_spinbox_changed_ch_14(int pan);
		void on_pan_spinbox_changed_ch_15(int pan);
		void on_pan_spinbox_changed_ch_16(int pan);

		void on_pan_lfo_mod_level_dial_changed_ch_1(int lvl);
		void on_pan_lfo_mod_level_dial_changed_ch_2(int lvl);
		void on_pan_lfo_mod_level_dial_changed_ch_3(int lvl);
		void on_pan_lfo_mod_level_dial_changed_ch_4(int lvl);
		void on_pan_lfo_mod_level_dial_changed_ch_5(int lvl);
		void on_pan_lfo_mod_level_dial_changed_ch_6(int lvl);
		void on_pan_lfo_mod_level_dial_changed_ch_7(int lvl);
		void on_pan_lfo_mod_level_dial_changed_ch_8(int lvl);
		void on_pan_lfo_mod_level_dial_changed_ch_9(int lvl);
		void on_pan_lfo_mod_level_dial_changed_ch_10(int lvl);
		void on_pan_lfo_mod_level_dial_changed_ch_11(int lvl);
		void on_pan_lfo_mod_level_dial_changed_ch_12(int lvl);
		void on_pan_lfo_mod_level_dial_changed_ch_13(int lvl);
		void on_pan_lfo_mod_level_dial_changed_ch_14(int lvl);
		void on_pan_lfo_mod_level_dial_changed_ch_15(int lvl);
		void on_pan_lfo_mod_level_dial_changed_ch_16(int lvl);

		void on_pan_lfo_mod_level_spinbox_changed_ch_1(int lvl);
		void on_pan_lfo_mod_level_spinbox_changed_ch_2(int lvl);
		void on_pan_lfo_mod_level_spinbox_changed_ch_3(int lvl);
		void on_pan_lfo_mod_level_spinbox_changed_ch_4(int lvl);
		void on_pan_lfo_mod_level_spinbox_changed_ch_5(int lvl);
		void on_pan_lfo_mod_level_spinbox_changed_ch_6(int lvl);
		void on_pan_lfo_mod_level_spinbox_changed_ch_7(int lvl);
		void on_pan_lfo_mod_level_spinbox_changed_ch_8(int lvl);
		void on_pan_lfo_mod_level_spinbox_changed_ch_9(int lvl);
		void on_pan_lfo_mod_level_spinbox_changed_ch_10(int lvl);
		void on_pan_lfo_mod_level_spinbox_changed_ch_11(int lvl);
		void on_pan_lfo_mod_level_spinbox_changed_ch_12(int lvl);
		void on_pan_lfo_mod_level_spinbox_changed_ch_13(int lvl);
		void on_pan_lfo_mod_level_spinbox_changed_ch_14(int lvl);
		void on_pan_lfo_mod_level_spinbox_changed_ch_15(int lvl);
		void on_pan_lfo_mod_level_spinbox_changed_ch_16(int lvl);

		void on_pan_lfo_mod_combo_changed_ch_1(int lfo);
		void on_pan_lfo_mod_combo_changed_ch_2(int lfo);
		void on_pan_lfo_mod_combo_changed_ch_3(int lfo);
		void on_pan_lfo_mod_combo_changed_ch_4(int lfo);
		void on_pan_lfo_mod_combo_changed_ch_5(int lfo);
		void on_pan_lfo_mod_combo_changed_ch_6(int lfo);
		void on_pan_lfo_mod_combo_changed_ch_7(int lfo);
		void on_pan_lfo_mod_combo_changed_ch_8(int lfo);
		void on_pan_lfo_mod_combo_changed_ch_9(int lfo);
		void on_pan_lfo_mod_combo_changed_ch_10(int lfo);
		void on_pan_lfo_mod_combo_changed_ch_11(int lfo);
		void on_pan_lfo_mod_combo_changed_ch_12(int lfo);
		void on_pan_lfo_mod_combo_changed_ch_13(int lfo);
		void on_pan_lfo_mod_combo_changed_ch_14(int lfo);
		void on_pan_lfo_mod_combo_changed_ch_15(int lfo);
		void on_pan_lfo_mod_combo_changed_ch_16(int lfo);
		

		void on_send_dial_changed_ch_1(int snd);
		void on_send_dial_changed_ch_2(int snd);
		void on_send_dial_changed_ch_3(int snd);
		void on_send_dial_changed_ch_4(int snd);
		void on_send_dial_changed_ch_5(int snd);
		void on_send_dial_changed_ch_6(int snd);
		void on_send_dial_changed_ch_7(int snd);
		void on_send_dial_changed_ch_8(int snd);
		void on_send_dial_changed_ch_9(int snd);
		void on_send_dial_changed_ch_10(int snd);
		void on_send_dial_changed_ch_11(int snd);
		void on_send_dial_changed_ch_12(int snd);
		void on_send_dial_changed_ch_13(int snd);
		void on_send_dial_changed_ch_14(int snd);
		void on_send_dial_changed_ch_15(int snd);
		void on_send_dial_changed_ch_16(int snd);

		void on_send_spinbox_changed_ch_1(int snd);
		void on_send_spinbox_changed_ch_2(int snd);
		void on_send_spinbox_changed_ch_3(int snd);
		void on_send_spinbox_changed_ch_4(int snd);
		void on_send_spinbox_changed_ch_5(int snd);
		void on_send_spinbox_changed_ch_6(int snd);
		void on_send_spinbox_changed_ch_7(int snd);
		void on_send_spinbox_changed_ch_8(int snd);
		void on_send_spinbox_changed_ch_9(int snd);
		void on_send_spinbox_changed_ch_10(int snd);
		void on_send_spinbox_changed_ch_11(int snd);
		void on_send_spinbox_changed_ch_12(int snd);
		void on_send_spinbox_changed_ch_13(int snd);
		void on_send_spinbox_changed_ch_14(int snd);
		void on_send_spinbox_changed_ch_15(int snd);
		void on_send_spinbox_changed_ch_16(int snd);
		
		
		void on_static_level_checkbox_changed_ch_1(bool state);
		void on_static_level_checkbox_changed_ch_2(bool state);
		void on_static_level_checkbox_changed_ch_3(bool state);
		void on_static_level_checkbox_changed_ch_4(bool state);
		void on_static_level_checkbox_changed_ch_5(bool state);
		void on_static_level_checkbox_changed_ch_6(bool state);
		void on_static_level_checkbox_changed_ch_7(bool state);
		void on_static_level_checkbox_changed_ch_8(bool state);
		void on_static_level_checkbox_changed_ch_9(bool state);
		void on_static_level_checkbox_changed_ch_10(bool state);
		void on_static_level_checkbox_changed_ch_11(bool state);
		void on_static_level_checkbox_changed_ch_12(bool state);
		void on_static_level_checkbox_changed_ch_13(bool state);
		void on_static_level_checkbox_changed_ch_14(bool state);
		void on_static_level_checkbox_changed_ch_15(bool state);
		void on_static_level_checkbox_changed_ch_16(bool state);

		void on_midi_mixer_modulator_combo_box_mouse_entered(int id);
		void on_midi_mixer_modulator_combo_box_mouse_exited(int id);

		void on_selected_lfo_rate_dial_changed(int val);
		void on_selected_lfo_symmetry_dial_changed(int val);
		void on_selected_lfo_waveform_combo_changed(int val);

		void on_LFO_frame_close_button_clicked();
	
protected:
	void timerEvent(QTimerEvent *event);
	
private:
	
	explicit Dialog_MidiMixer(QWidget *parent = 0);
	
	Ui::Dialog_MidiMixer_1620x840 *ui;
	
	static Dialog_MidiMixer *dialog_midi_mixer_instance;

	void set_midi_mixer_signals_connections();

	void init_active_lfo_widget();
	void update_active_lfo_frame();

	func_ptr_void_void_t close_event_callback_ptr;
	
	int active_channels_tab;
	
	int channels_levels[16];
	int channel_level_max = 100;
	int channels_level_min = 0;
	
	int channels_pan[16];
	int channels_pan_max = 50;
	int channels_pan_min = -50;

	int channels_pan_mod_levels[16];
	int channels_pan_mod_level_max = 100;
	int channels_pan_mod_level_min = 0;

	int channels_pan_mod_lfo_selection[16];
	int channels_send_levels[16];

	bool channels_static_level[16];

	int channels_active_counters[16];

	QString channels_programs_names[16];
	QList<QString> string_lfos_list;
	QList<QString> string_waveforms_list;

	CustomDial *dials_pan[16];
	CustomDial *dials_pan_lfo_mod_level[16];
	CustomDial *dials_send[16];
	CustomVerticalSlider *sliders_levels[16];
	CustomComboBox *comboboxes_pan_lfo_mod[16];
	CustomCheckBox *checkboxes_static_levels[16];
	CustomCheckBox *checkboxes_activity_leds[16];
	QSpinBox *spinboxes_levels[16];
	QSpinBox *spinboxes_pan[16];
	QSpinBox *spinboxes_pan_lfo_mod_level[16];
	QSpinBox *spinboxes_send[16];
	QTextEdit *textedits_channel_programs[16];

	std::atomic<bool> levels_updated{true};
	std::atomic<bool> pans_updated{true};
	std::atomic<bool> sends_updated{true};
	std::atomic<bool> pan_mod_levels_updated{true};
	std::atomic<bool> pan_mod_lfos_updated{true};
	std::atomic<bool> send_levels_updated{true};
	std::atomic<bool> static_levels_updated{true};
	std::atomic<bool> textedits_programs_updated{true};
	std::atomic<bool> activity_leds_updated{true};

	int active_lfo = _LFO_NONE;
	int active_lfo_waveform = _OSC_WAVEFORM_SINE;
	int active_lfo_symmetry = 50;
	int active_lfo_rate = 50;
	bool active_lfo_widget_showing = false;

	// Used for counting down ADSR/LFO frame no activity show timeout based on GUI update timer. _UPDATE_TIMER_PERIOD_MS (100ms)
	int active_lfo_frame_no_activity_counter = 0;

	void on_level_changed(int chan, int vol);
	void on_pan_changed(int chan, int pan);
	void on_pan_mod_level_changed(int chan, int lvl);
	void on_pan_mod_lfo_changed(int chan, int lfo);
	void on_send_level_changed(int chan, int snd);
	void on_static_levels_changed(int chan, bool state);

	void start_update_timer(int interval);

	ControlWidgetsColorManager *control_widgets_color_manager;
	
};
