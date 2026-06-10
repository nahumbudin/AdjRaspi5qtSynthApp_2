/**
 *	@file		InstrumentPannel.h
 *	Pannel.h
 *	@author		Nahum Budin
 *	@date		22-Sep-2025
 *	@version	1.1
 *			1. Renaming file from ModulePannel to InstrumentPannel
 *			2. Refactoring rename modules to instruments
 *			3. Added 3 pannel states: idle, hover and selected (GitHub Copilot assistance)
 *
 *	History:
 *			Version	1.0		8-May-2024	Initial
 *
 *	@brief		Handles a single Instrument pannel.
 */

#pragma once

#include <QFrame>
#include <QThread>
#include <functional>

#include "libAdjRaspi5SynthAPI.h"

// Forward declarations only
class Dialog_InstrumentConnections;
class Dialog_AdjFluidSynth;
class Dialog_AnalogSynth_1900x1000;
class Dialog_MidiPlayer;
class Dialog_MidiMixer;
class Dialog_MidiMapper;
class Dialog_KeyboardMapper;
class Dialog_AnalogReverb;
class Dialog_AnalogEqualizer;
class Dialog_HammondOrgan;
class Dialog_StringSynthesizer;
class Dialog_PADsynthesizer;
class Dialog_MSOsynthesizer;
class MainWindow;

namespace Ui
{
	class InstrumentPannel;
}

/* void foo(en_instrumentsIds_t) function pointer */
typedef void (*func_ptr_void_en_instruments_ids_t_t)(en_instruments_ids_t);

class InstrumentPannel : public QFrame
{
	Q_OBJECT

  public:
	explicit InstrumentPannel(QWidget *parent = 0,
							  QString instrument_name_str = "Instrument",
							  func_ptr_void_en_instruments_ids_t_t close_instrument_pannel_callback_ptr = NULL,
							  en_instruments_ids_t inst = en_instruments_ids_t::none_instrument_id);
	~InstrumentPannel();

	enum PannelState
	{
		STATE_IDLE,
		STATE_HOVER,
		STATE_SELECTED
	};

	InstrumentPannel *get_the_instrument_pannel();

	void hide_checkBox_InstrumentMIDIin();

	void set_state(PannelState state);
	PannelState get_state() const { return current_state; }
	void set_selected(bool selected);
	bool is_selected() const { return current_state == STATE_SELECTED; }

	void set_frame_color(const QColor &color);
	void set_frame_color(int r, int g, int b, int a = 220);

	// Method to set preset text in the instrument panel
	void set_preset_text(const QString &text);
	QString get_preset_text() const;
	void clear_preset_text();

	// Instrument info getters
	QString get_instrument_name() const { return instrument_name; }

	Ui::InstrumentPannel *ui;

	en_instruments_ids_t instrument_id;
	QString instrument_name;

  protected:
	void enterEvent(QEvent *event) override;
	void leaveEvent(QEvent *event) override;

  protected slots:
	void on_instrument_exit_clicked();
	void on_instrument_open_clicked();
	void on_instrument_connections_clicked();

	void on_preset_file_loaded(const QString &s);

  private:
	void close_connections_dialog();
	void close_instrument_dialog();
	void update_visual_state();

	// Helper methods for each dialog type
	void open_fluid_synth_dialog();
	void open_analog_synth_dialog();
	void open_midi_player_dialog();
	void open_midi_mixer_dialog();
	void open_midi_mapper_dialog();
	void open_analog_reverb_dialog();
	void open_analog_equalizer_dialog();
	void open_hammond_organ_dialog();
	void open_string_synthesizer_dialog();
	void open_pad_synthesizer_dialog();
	void open_mso_synthesizer_dialog();
	void open_keyboard_mapper_dialog();

	void open_synth_patch_preset_dialog(int preset_index);

	PannelState current_state;

	func_ptr_void_en_instruments_ids_t_t close_callback_ptr;

	Dialog_InstrumentConnections *connections_dialog;
	Dialog_AdjFluidSynth *dialog_adj_fluid_synth;
	Dialog_AnalogSynth_1900x1000 *dialog_analog_synth_1900x1000;
	Dialog_HammondOrgan *dialog_hammond_organ;
	Dialog_StringSynthesizer *dialog_string_synthesizer;
	Dialog_PADsynthesizer *dialog_pad_synthesizer;
	Dialog_MSOsynthesizer *dialog_mso_synthesizer;

	Dialog_MidiPlayer *dialog_adj_midi_player;
	Dialog_MidiMixer *dialog_midi_mixer;
	Dialog_MidiMapper *dialog_midi_mapper;
	Dialog_KeyboardMapper *dialog_keyboard_mapper;

	Dialog_AnalogReverb *dialog_analog_reverb;
	Dialog_AnalogEqualizer *dialog_analog_equalizer;
	

	QWidget *widget_parent;

	QColor frame_color = QColor(20, 20, 20, 220); // Default color

	QString last_string_synth_preset_directory[_MAX_NUM_OF_ANALOG_PRESET_INSTRUMENTS] = {""};
	QString last_string_synth_preset_load_file[_MAX_NUM_OF_ANALOG_PRESET_INSTRUMENTS] = {""};
};

class LoadSynthesizerPatchPresetFileThread : public QThread
{
	Q_OBJECT
	void run();

  signals:
	void loadPresetFileDone(const QString &s);
};