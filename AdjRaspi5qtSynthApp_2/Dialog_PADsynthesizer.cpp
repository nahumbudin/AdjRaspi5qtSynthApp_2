/**
 * @file		Dialog_PADsynthesizer.cpp
 *	@author		Nahum Budin
 *	@date		10-May-2026
 *	@version	1.0
 *
 *	@brief		Adj PAD Synthesizer (KPS) control dialog
 *
 */

#include <filesystem>

#include "Dialog_PADsynthesizer.h"
#include "ui_Dialog_PADsynthesizer.h"

#include "utils.h"

#include "GuiNavigator.h"
#include "MainWindow.h"

#include "CustomFileDialog.h"

#define _UPDATE_TIMER_PERIOD_MS 250

Dialog_PADsynthesizer *Dialog_PADsynthesizer::dialog_pad_synthesizer_instance = nullptr;

LoadPADsynthesizerPresetFileThread *load_pad_synthesizer_preset_file_thread;
SavePADsynthesizerPresetFileThread *save_pad_synthesizer_preset_file_thread;

QString pad_synth_preset_file_name;

void pad_synthesizer_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	Dialog_PADsynthesizer::get_instance()->control_box_ui_update_callback(evnt, val);
}

void SavePADsynthesizerPresetFileThread::run()
{
	int res;

	QString result = QString("Preset File Saved");
	res = mod_synth_save_pad_synthesizer_preset_file(pad_synth_preset_file_name.toStdString());

	emit savePresetFileDone(result);
}

void LoadPADsynthesizerPresetFileThread::run()
{
	int res;

	QString result = QString("Preset File Loaded");
	res = mod_synth_load_pad_synthesizer_preset_file(pad_synth_preset_file_name.toStdString());

	emit loadPresetFileDone(result);
}

Dialog_PADsynthesizer::Dialog_PADsynthesizer(QWidget *parent)
	: QDialog(parent), ui(new Ui::Dialog_PADsynthesizer)
{
	ui->setupUi(this);

	// Prevent dialog from being deleted when closed - only hide it
	setAttribute(Qt::WA_DeleteOnClose, false);

	ui->frame_PADsynthAll->setAutoFillBackground(true);
	ui->frame_PADsynthAll->setStyleSheet("background-color: rgb(5, 5, 5);");

	dialog_pad_synthesizer_instance = this;
	close_event_callback_ptr = NULL;

	// Register control box event callback
	mod_synth_register_callback_control_box_event_update_ui(
		&pad_synthesizer_control_box_event_update_ui_callback_wrapper);

	init_gui_elements();
	set_signal_slots_connections();

	update_adsr_plot = true;
	update_spectrum_plot = true;
	update_adsr_plot = true;

	// Register with GuiNavigator (no tabs, no frames for PAD Synthesizer)
	GuiNavigator::get_instance()->register_dialog(this, "PAD Synthesizer");

	// Also register with MainWindow for compatibility
	MainWindow::get_instance()->register_active_dialog(this);
	
	// Fix Frames.
	ui->frame_PADsynth_Haromonies1_6->setBorderColor(_CONTROLS_COLOR_GRAY);
	ui->frame_PADsynth_Haromonies1_6->setBorderWidth(3);

	GuiNavigator *nav = GuiNavigator::get_instance();

	// Define frames for the single "tab" (tab 0)
	QMap<int, QList<QString>> frames_per_tab;

	// All frames go under tab index 0
	frames_per_tab[0] << "Left Controls"<< "Right Controls";

	// Register dialog WITHOUT a tab widget (nullptr)
	nav->register_dialog(
		this,
		"PAD Synthesizer",
		nullptr, // No tab widget
		frames_per_tab);

	nav->set_gray_frame_widgets(this, 0, 0, // tab_index = 0, frame_index = 0
								ui->frame_PADsynth_SendFiltersTuneOffset,
								ui->frame_PADsynth_Presetes,
								nullptr,
								nullptr);

	nav->set_white_frame_widgets(this, 0, 0, // tab_index = 0, frame_index = 0
								 ui->frame_PADsynth_AmplitudeModulation,
								nullptr,
								nullptr,
								nullptr);

	nav->set_gray_frame_widgets(this, 0, 1, // tab_index = 0, frame_index = 1 : not changing.
								ui->frame_PADsynth_SendFiltersTuneOffset,
								ui->frame_PADsynth_Presetes,
								nullptr,
								nullptr);

	nav->set_white_frame_widgets(this, 0, 1, // tab_index = 0, frame_index = 1
								 ui->frame_PADsynth_Profile,
								 ui->frame_PADsynth_Haromonyies7_10,
								 nullptr,
								 nullptr);

	// Highlight the first frame
	nav->refresh_current_highlight();

	// GUI Update timer start
	start_update_timer(_UPDATE_TIMER_PERIOD_MS);

	/* Set focus on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

Dialog_PADsynthesizer::~Dialog_PADsynthesizer()
{
	// Reset static instance pointer when destroyed
	dialog_pad_synthesizer_instance = nullptr;
	delete ui;
}

Dialog_PADsynthesizer *Dialog_PADsynthesizer::get_instance(QWidget *parent)
{
	if (dialog_pad_synthesizer_instance == NULL)
	{
		dialog_pad_synthesizer_instance = new Dialog_PADsynthesizer(parent);
	}
	return dialog_pad_synthesizer_instance;
}

void Dialog_PADsynthesizer::init_gui_elements()
{
	int result;

	string_pad_qualities_list.append("32K");
	string_pad_qualities_list.append("64K");
	string_pad_qualities_list.append("128K");
	string_pad_qualities_list.append("256K");
	string_pad_qualities_list.append("512K");
	string_pad_qualities_list.append("1024K");

	string_pad_base_notes_list.append("C2");
	string_pad_base_notes_list.append("G2");
	string_pad_base_notes_list.append("C3");
	string_pad_base_notes_list.append("G3");
	string_pad_base_notes_list.append("C4");
	string_pad_base_notes_list.append("G4");
	string_pad_base_notes_list.append("C5");
	string_pad_base_notes_list.append("G5");
	string_pad_base_notes_list.append("C6");
	string_pad_base_notes_list.append("G6");

	string_pad_shapes_list.append("Rectangular");
	string_pad_shapes_list.append("Gaussian");
	string_pad_shapes_list.append("Double Exp.");

	string_pad_shape_cutoffs_list.append("Full");
	string_pad_shape_cutoffs_list.append("Upper");
	string_pad_shape_cutoffs_list.append("Lower");

	// Send and Tune frame and controls
	ui->dial_PADsynthSendFilter1->setKnobColor(_KNOBS_COLOR);
	ui->dial_PADsynthSendFilter1->setCircleColor(_CONTROLS_COLOR_PURPLE);
	ui->dial_PADsynthSendFilter1->setValue(40);

	ui->dial_PADsynthSendFilter2->setKnobColor(_KNOBS_COLOR);
	ui->dial_PADsynthSendFilter2->setCircleColor(_CONTROLS_COLOR_BLUE);
	ui->dial_PADsynthSendFilter2->setValue(40);

	ui->comboBox_PADsynthTuneOctave->blockSignals(true);
	ui->comboBox_PADsynthTuneSemitones->blockSignals(true);
	ui->comboBox_PADsynthTuneCents->blockSignals(true);

	ui->comboBox_PADsynthTuneOctave->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_PADsynthTuneOctave->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_PADsynthTuneOctave->setFrameColor(_CONTROLS_COLOR_WHITE);
	ui->comboBox_PADsynthTuneOctave->setFrameWidth(2);
	ui->comboBox_PADsynthTuneOctave->setCurrentIndex(mod_synth_get_active_osc1_detune_octave() - mod_synth_get_osc_detune_min_octave());

	ui->comboBox_PADsynthTuneSemitones->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_PADsynthTuneSemitones->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_PADsynthTuneSemitones->setFrameColor(_CONTROLS_COLOR_YELLOW);
	ui->comboBox_PADsynthTuneSemitones->setFrameWidth(2);
	ui->comboBox_PADsynthTuneSemitones->setCurrentIndex(mod_synth_get_active_osc1_detune_semitones() - mod_synth_get_osc_detune_min_semitones());

	ui->comboBox_PADsynthTuneCents->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_PADsynthTuneCents->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_PADsynthTuneCents->setFrameColor(_CONTROLS_COLOR_RED);
	ui->comboBox_PADsynthTuneCents->setFrameWidth(2);
	ui->comboBox_PADsynthTuneCents->setCurrentIndex(mod_synth_get_active_osc1_detune_cents() - mod_synth_get_osc_detune_min_cents() * 4.f);

	for (int i = _OSC_DETUNE_MIN_OCTAVE; i <= _OSC_DETUNE_MAX_OCTAVE; i++)
	{
		ui->comboBox_PADsynthTuneOctave->addItem(QString::number(i));
	}

	for (int i = _OSC_DETUNE_MIN_SEMITONES; i <= _OSC_DETUNE_MAX_SEMITONES; i++)
	{
		ui->comboBox_PADsynthTuneSemitones->addItem(QString::number(i));
	}

	for (int i = 4 * _OSC_DETUNE_MIN_CENTS; i <= 4 * _OSC_DETUNE_MAX_CENTS; i++)
	{
		// 0.25 steps
		ui->comboBox_PADsynthTuneCents->addItem(QString::number(i / 4.f));
	}

	ui->comboBox_PADsynthTuneOctave->blockSignals(false);
	ui->comboBox_PADsynthTuneSemitones->blockSignals(false);
	ui->comboBox_PADsynthTuneCents->blockSignals(false);

	// Presets Controls
	ui->pushButton_PADsynth_PresetOpen->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->pushButton_PADsynth_PresetOpen->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);

	ui->pushButton_PADsynth_PresetSave->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->pushButton_PADsynth_PresetSave->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);

	// Amplitude Modulation Controls
	ui->dial_PADsynth_AmpModAdsrLevel->setKnobColor(_KNOBS_COLOR);
	ui->dial_PADsynth_AmpModAdsrLevel->setCircleColor(_CONTROLS_COLOR_PURPLE);

	ui->dial_PADsynth_AmpModLFOLevel->setKnobColor(_KNOBS_COLOR);
	ui->dial_PADsynth_AmpModLFOLevel->setCircleColor(_CONTROLS_COLOR_BLUE);

	ui->dial_PADsynth_LFOsymmetry->setKnobColor(_KNOBS_COLOR);
	ui->dial_PADsynth_LFOsymmetry->setCircleColor(_CONTROLS_COLOR_GREEN);

	ui->dial_PADsynth_LFOrate->setKnobColor(_KNOBS_COLOR);
	ui->dial_PADsynth_LFOrate->setCircleColor(_CONTROLS_COLOR_WHITE);

	string_waveforms_list.append("Sine");
	string_waveforms_list.append("Square");
	string_waveforms_list.append("Pulse");
	string_waveforms_list.append("Triangle");
	string_waveforms_list.append("Samp&Hold");

	ui->comboBox_PADsynth_LFOwaveform->blockSignals(true);
	ui->comboBox_PADsynth_LFOwaveform->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_PADsynth_LFOwaveform->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_PADsynth_LFOwaveform->setFrameColor(_CONTROLS_COLOR_RED);
	ui->comboBox_PADsynth_LFOwaveform->setFrameWidth(2);
	ui->comboBox_PADsynth_LFOwaveform->setCurrentIndex(0);
	ui->comboBox_PADsynth_LFOwaveform->addItems(string_waveforms_list);
	ui->comboBox_PADsynth_LFOwaveform->blockSignals(true);

	ui->verticalSlider_PADsynth_AdsrA->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_PADsynth_AdsrA->setFrameColor(_CONTROLS_COLOR_GRAY);
	ui->verticalSlider_PADsynth_AdsrA->setProgressColor(_CONTROLS_COLOR_GRAY);
	ui->verticalSlider_PADsynth_AdsrA->setHandleColor(_CONTROLS_COLOR_GRAY);

	ui->verticalSlider_PADsynth_AdsrD->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_PADsynth_AdsrD->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_PADsynth_AdsrD->setProgressColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_PADsynth_AdsrD->setHandleColor(_CONTROLS_COLOR_PURPLE);

	ui->verticalSlider_PADsynth_AdsrS->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_PADsynth_AdsrS->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_PADsynth_AdsrS->setProgressColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_PADsynth_AdsrS->setHandleColor(_CONTROLS_COLOR_BLUE);

	ui->verticalSlider_PADsynth_AdsrR->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_PADsynth_AdsrR->setFrameColor(_CONTROLS_COLOR_GREEN);
	ui->verticalSlider_PADsynth_AdsrR->setProgressColor(_CONTROLS_COLOR_GREEN);
	ui->verticalSlider_PADsynth_AdsrR->setHandleColor(_CONTROLS_COLOR_GREEN);

	// Setup ADSR curves plot

#define _PAD_ADSR_CURVE_HEIGHT	60
	
	adsr_curve_max_attack = mod_synth_get_adsr_max_attack_time_sec();
	adsr_curve_max_decay = mod_synth_get_adsr_max_decay_time_sec();
	adsr_curve_max_sustain = 100; //%
	adsr_curve_max_release = mod_synth_get_adsr_max_release_time_sec();

	adsr_plot_length = _ADSR_CURVE_START_POINT + _ADSR_CURVE_SUSTAIN_SEGMENT_LENGTH +
					   (adsr_curve_max_attack + adsr_curve_max_decay +
						adsr_curve_max_release) *
						   _ADSR_CURVE_TIME_MULTIPLIER;

	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(2);
	pen.setColor(Qt::white);

	ui->widget_ADSRplot->addGraph();
	ui->widget_ADSRplot->graph(0)->setPen(pen);
	ui->widget_ADSRplot->addGraph();

	ui->widget_ADSRplot->xAxis->setVisible(false);
	ui->widget_ADSRplot->xAxis->setTickLabels(true);
	ui->widget_ADSRplot->yAxis->setVisible(false);
	ui->widget_ADSRplot->yAxis->setTickLabels(true);

	ui->widget_ADSRplot->yAxis->setRange(0, _PAD_ADSR_CURVE_HEIGHT);
	ui->widget_ADSRplot->xAxis->setRange(0, adsr_plot_length);

	ui->widget_ADSRplot->setMinimumSize(adsr_plot_length, _PAD_ADSR_CURVE_HEIGHT);
	ui->widget_ADSRplot->setBackground(QBrush(_CONTROLS_COLOR_BLACK));


	// Harmonies 1-6 Controls
	ui->verticalSlider_PADsynth_Harmony_1->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_PADsynth_Harmony_1->setFrameColor(_CONTROLS_COLOR_GRAY);
	ui->verticalSlider_PADsynth_Harmony_1->setProgressColor(_CONTROLS_COLOR_GRAY);
	ui->verticalSlider_PADsynth_Harmony_1->setHandleColor(_CONTROLS_COLOR_GRAY);

	ui->verticalSlider_PADsynth_Harmony_2->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_PADsynth_Harmony_2->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_PADsynth_Harmony_2->setProgressColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_PADsynth_Harmony_2->setHandleColor(_CONTROLS_COLOR_PURPLE);

	ui->verticalSlider_PADsynth_Harmony_3->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_PADsynth_Harmony_3->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_PADsynth_Harmony_3->setProgressColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_PADsynth_Harmony_3->setHandleColor(_CONTROLS_COLOR_BLUE);

	ui->verticalSlider_PADsynth_Harmony_4->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_PADsynth_Harmony_4->setFrameColor(_CONTROLS_COLOR_GREEN);
	ui->verticalSlider_PADsynth_Harmony_4->setProgressColor(_CONTROLS_COLOR_GREEN);
	ui->verticalSlider_PADsynth_Harmony_4->setHandleColor(_CONTROLS_COLOR_GREEN);

	ui->verticalSlider_PADsynth_Harmony_5->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_PADsynth_Harmony_5->setFrameColor(_CONTROLS_COLOR_WHITE);
	ui->verticalSlider_PADsynth_Harmony_5->setProgressColor(_CONTROLS_COLOR_WHITE);
	ui->verticalSlider_PADsynth_Harmony_5->setHandleColor(_CONTROLS_COLOR_WHITE);

	ui->verticalSlider_PADsynth_Harmony_6->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_PADsynth_Harmony_6->setFrameColor(_CONTROLS_COLOR_YELLOW);
	ui->verticalSlider_PADsynth_Harmony_6->setProgressColor(_CONTROLS_COLOR_YELLOW);
	ui->verticalSlider_PADsynth_Harmony_6->setHandleColor(_CONTROLS_COLOR_YELLOW);

	// Harmonies 7-10 and Detune Controls
	ui->verticalSlider_PADsynth_Harmony_7->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_PADsynth_Harmony_7->setFrameColor(_CONTROLS_COLOR_GRAY);
	ui->verticalSlider_PADsynth_Harmony_7->setProgressColor(_CONTROLS_COLOR_GRAY);
	ui->verticalSlider_PADsynth_Harmony_7->setHandleColor(_CONTROLS_COLOR_GRAY);

	ui->verticalSlider_PADsynth_Harmony_8->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_PADsynth_Harmony_8->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_PADsynth_Harmony_8->setProgressColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_PADsynth_Harmony_8->setHandleColor(_CONTROLS_COLOR_PURPLE);

	ui->verticalSlider_PADsynth_Harmony_9->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_PADsynth_Harmony_9->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_PADsynth_Harmony_9->setProgressColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_PADsynth_Harmony_9->setHandleColor(_CONTROLS_COLOR_BLUE);

	ui->verticalSlider_PADsynth_Harmony_10->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_PADsynth_Harmony_10->setFrameColor(_CONTROLS_COLOR_GREEN);
	ui->verticalSlider_PADsynth_Harmony_10->setProgressColor(_CONTROLS_COLOR_GREEN);
	ui->verticalSlider_PADsynth_Harmony_10->setHandleColor(_CONTROLS_COLOR_GREEN);

	ui->verticalSlider_PADsynth_HarmonyDetune->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_PADsynth_HarmonyDetune->setFrameColor(_CONTROLS_COLOR_WHITE);
	ui->verticalSlider_PADsynth_HarmonyDetune->setProgressColor(_CONTROLS_COLOR_WHITE);
	ui->verticalSlider_PADsynth_HarmonyDetune->setHandleColor(_CONTROLS_COLOR_WHITE);
	
	// Spectrum Control
	ui->horizontalSlider_PADsynth_BaseWidth->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->horizontalSlider_PADsynth_BaseWidth->setFrameColor(_CONTROLS_COLOR_RED);
	ui->horizontalSlider_PADsynth_BaseWidth->setProgressColor(_CONTROLS_COLOR_RED);
	ui->horizontalSlider_PADsynth_BaseWidth->setHandleColor(_CONTROLS_COLOR_RED);

	ui->comboBox_PADsynth_Shape->blockSignals(true);
	ui->comboBox_PADsynth_BaseNote->blockSignals(true);
	ui->comboBox_PADsynth_Quality->blockSignals(true);
	ui->comboBox_PADsynth_ShapeCutoff->blockSignals(true);

	ui->comboBox_PADsynth_Shape->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_PADsynth_Shape->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_PADsynth_Shape->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->comboBox_PADsynth_Shape->setFrameWidth(2);
	ui->comboBox_PADsynth_Shape->setCurrentIndex(0);
	ui->comboBox_PADsynth_Shape->addItems(string_pad_shapes_list);

	ui->comboBox_PADsynth_ShapeCutoff->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_PADsynth_ShapeCutoff->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_PADsynth_ShapeCutoff->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->comboBox_PADsynth_ShapeCutoff->setFrameWidth(2);
	ui->comboBox_PADsynth_ShapeCutoff->setCurrentIndex(0);
	ui->comboBox_PADsynth_ShapeCutoff->addItems(string_pad_shape_cutoffs_list);

	ui->comboBox_PADsynth_BaseNote->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_PADsynth_BaseNote->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_PADsynth_BaseNote->setFrameColor(_CONTROLS_COLOR_GREEN);
	ui->comboBox_PADsynth_BaseNote->setFrameWidth(2);
	ui->comboBox_PADsynth_BaseNote->setCurrentIndex(0);
	ui->comboBox_PADsynth_BaseNote->addItems(string_pad_base_notes_list);

	ui->comboBox_PADsynth_Quality->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_PADsynth_Quality->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_PADsynth_Quality->setFrameColor(_CONTROLS_COLOR_WHITE);
	ui->comboBox_PADsynth_Quality->setFrameWidth(2);
	ui->comboBox_PADsynth_Quality->setCurrentIndex(0);
	ui->comboBox_PADsynth_Quality->addItems(string_pad_qualities_list);

	ui->comboBox_PADsynth_Shape->blockSignals(false);
	ui->comboBox_PADsynth_BaseNote->blockSignals(false);
	ui->comboBox_PADsynth_Quality->blockSignals(false);
	ui->comboBox_PADsynth_ShapeCutoff->blockSignals(false);

	ui->checkBox_PadPADsynth_Auto->setLedStyle(true);
	ui->checkBox_PadPADsynth_Auto->setLedOnColor(_CONTROLS_COLOR_GREEN);
	ui->checkBox_PadPADsynth_Auto->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->checkBox_PadPADsynth_Auto->setBackgroundColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_PadPADsynth_Auto->setCheckBoxSize(16);
	ui->checkBox_PadPADsynth_Auto->setFrameWidth(2);

	ui->pushButton_PADsynth_Generate->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->pushButton_PADsynth_Generate->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);
}

void Dialog_PADsynthesizer::set_signal_slots_connections()
{
	connect(ui->pushButton_PADsynth_Generate,
			SIGNAL(clicked()),
			this,
			SLOT(on_generate_pushbutton_clicked()));

	connect(ui->comboBox_PADsynthTuneOctave,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_detune_octave_combobox_changed(int)));

	connect(ui->comboBox_PADsynthTuneSemitones,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_detune_semitones_combobox_changed(int)));

	connect(ui->comboBox_PADsynthTuneCents,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_detune_cents_combobox_changed(int)));

	connect(ui->dial_PADsynthSendFilter1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_filter1_dial_changed(int)));

	connect(ui->dial_PADsynthSendFilter2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_filter2_dial_changed(int)));

	connect(ui->comboBox_PADsynth_BaseNote,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_base_note_combobox_changed(int)));

	connect(ui->comboBox_PADsynth_Quality,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_quality_combobox_changed(int)));

	connect(ui->comboBox_PADsynth_Shape,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_shape_combobox_changed(int)));

	connect(ui->comboBox_PADsynth_ShapeCutoff,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_shape_cutoff_combobox_changed(int)));

	connect(ui->horizontalSlider_PADsynth_BaseWidth,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_base_width_slider_changed(int)));

	connect(ui->verticalSlider_PADsynth_Harmony_1,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_harmony1_level_slider_changed(int)));

	connect(ui->verticalSlider_PADsynth_Harmony_2,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_harmony2_level_slider_changed(int)));

	connect(ui->verticalSlider_PADsynth_Harmony_3,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_harmony3_level_slider_changed(int)));

	connect(ui->verticalSlider_PADsynth_Harmony_4,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_harmony4_level_slider_changed(int)));

	connect(ui->verticalSlider_PADsynth_Harmony_5,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_harmony5_level_slider_changed(int)));

	connect(ui->verticalSlider_PADsynth_Harmony_6,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_harmony6_level_slider_changed(int)));

	connect(ui->verticalSlider_PADsynth_Harmony_7,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_harmony7_level_slider_changed(int)));

	connect(ui->verticalSlider_PADsynth_Harmony_8,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_harmony8_level_slider_changed(int)));

	connect(ui->verticalSlider_PADsynth_Harmony_9,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_harmony9_level_slider_changed(int)));

	connect(ui->verticalSlider_PADsynth_Harmony_10,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_harmony10_level_slider_changed(int)));

	connect(ui->verticalSlider_PADsynth_HarmonyDetune,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_harmonies_detune_slider_changed(int)));
	
	
	connect(ui->dial_PADsynth_AmpModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mod_env_level_dial_changed(int)));
	
	connect(ui->verticalSlider_PADsynth_AdsrA,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mod_env_attack_slider_changed(int)));

	connect(ui->verticalSlider_PADsynth_AdsrD,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mod_env_decay_slider_changed(int)));

	connect(ui->verticalSlider_PADsynth_AdsrS,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mod_env_sustain_slider_changed(int)));

	connect(ui->verticalSlider_PADsynth_AdsrR,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mod_env_release_slider_changed(int)));

	connect(ui->dial_PADsynth_AmpModLFOLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mod_lfo_level_dial_changed(int)));

	connect(ui->comboBox_PADsynth_LFOwaveform,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_mod_lfo_waveform_combobox_changed(int)));

	connect(ui->dial_PADsynth_LFOrate,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mod_lfo_frequency_dial_changed(int)));

	connect(ui->dial_PADsynth_LFOsymmetry,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_mod_lfo_symmetry_dial_changed(int)));

	connect(ui->pushButton_PADsynth_PresetOpen,
			SIGNAL(clicked()),
			this,
			SLOT(on_presets_open_pushbutton_clicked()));

	connect(ui->pushButton_PADsynth_PresetSave,
			SIGNAL(clicked()),
			this,
			SLOT(on_presets_save_pushbutton_clicked()));
}

void Dialog_PADsynthesizer::closeEvent(QCloseEvent *event)
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

void Dialog_PADsynthesizer::control_box_ui_update_callback(int evnt, uint16_t val)
{
	// Only process events if this dialog has focus
	if (!this->hasFocus())
	{
		return;
	}

	GuiNavigator *nav = GuiNavigator::get_instance();

	int current_frame_index = nav->get_current_frame_index();

	int slider_level_gap = 0;

	const int pad_control_max = 100;
	const int pad_control_min = 0;
	const int pad_base_width_max = 95;
	const int pad_base_width_min = 5;
	const int pad_shape_max = _PAD_SHAPE_DOUBLE_EXP;
	const int pad_shape_min = _PAD_SHAPE_RECTANGULAR;
	const int pad_shape_cutoff_max = _PAD_SHAPE_CUTOFF_LOWER;
	const int pad_shape_cutoff_min = _PAD_SHAPE_CUTOFF_FULL;
	const int pad_quality_max = _PAD_QUALITY_1024K;
	const int pad_quality_min = _PAD_QUALITY_32K;
	const int pad_base_note_max = _PAD_BASE_NOTE_G6;
	const int pad_base_note_min = _PAD_BASE_NOTE_C2;
	const int tune_offset_octave_max = 12; // -6 octave offset (min) to +6 octave offset (max), with 0 octave offset centered (13 steps total starting at 0)
	const int tune_offset_octave_min = 0;
	const int tune_offset_semitone_max = 22; // -11 semitone offset (min) to +11 semitone offset (max), with 0 semitone offset centered (23 steps total starting at 0)
	const int tune_offset_semitone_min = 0;
	const int tune_offset_cents_max = 60; // -7.5 to +7.5 cents, with 0.25 cent steps (61 steps total starting at 0), with 0 cent offset centered
	const int tune_offset_cents_min = 0;

	static int pad_send_filter_1 = 0;
	static int pad_send_filter_2 = 0;
	static int pad_tune_offset_octave = 7;	  // 0 octave offset (centered), with range of -6 to +6 octaves (13 steps total)
	static int pad_tune_offset_semitone = 12; // 0 semitone offset (centered), with range of -11 to +11 semitones (23 steps total)
	static int pad_tune_offset_cents = 30;	  // 0 cent offset (centered), with range of -7.5 to +7.5 cents (61 steps total)
	static int pad_amp_mod_lfo_level = 0;
	static int pad_amp_mod_lfo_waveform = 0;
	static int pad_amp_mod_lfo_rate = 0;
	static int pad_amp_mod_lfo_symmetry = 0;
	static int pad_amp_mod_adsr_level = 0;
	static int pad_amp_mod_adsr_attack = 0;
	static int pad_amp_mod_adsr_decay = 0;
	static int pad_amp_mod_adsr_sustain = 0;
	static int pad_amp_mod_adsr_release = 0;
	static int pad_harmony_1_level = 100;
	static int pad_harmony_2_level = 0;
	static int pad_harmony_3_level = 0;
	static int pad_harmony_4_level = 0;
	static int pad_harmony_5_level = 0;
	static int pad_harmony_6_level = 0;
	static int pad_harmony_7_level = 0;
	static int pad_harmony_8_level = 0;
	static int pad_harmony_9_level = 0;
	static int pad_harmony_10_level = 0;
	static int pad_harmonies_detune = 0;
	static int pad_base_width = 30;
	static int pad_shape = _PAD_SHAPE_RECTANGULAR;
	static int pad_shape_cutoff = _PAD_SHAPE_CUTOFF_FULL;
	static int pad_quality = _PAD_QUALITY_128K;
	static int pad_base_note = _PAD_BASE_NOTE_C3;

	static int prev_pad_send_filter_1 = 0;
	static int prev_pad_send_filter_2 = 0;
	static int prev_pad_tune_offset_octave = 7;	  // 0 octave offset (centered), with range of -6 to +6 octaves (13 steps total)
	static int prev_pad_tune_offset_semitone = 12; // 0 semitone offset (centered), with range of -11 to +11 semitones (23 steps total)
	static int prev_pad_tune_offset_cents = 30;	  // 0 cent offset (centered), with range of -7.5 to +7.5 cents (61 steps total)
	static int prev_pad_amp_mod_lfo_level = 0;
	static int prev_pad_amp_mod_lfo_waveform = 0;
	static int prev_pad_amp_mod_lfo_rate = 0;
	static int prev_pad_amp_mod_lfo_symmetry = 0;
	static int prev_pad_amp_mod_adsr_level = 0;
	static int prev_pad_amp_mod_adsr_attack = 0;
	static int prev_pad_amp_mod_adsr_decay = 0;
	static int prev_pad_amp_mod_adsr_sustain = 0;
	static int prev_pad_amp_mod_adsr_release = 0;
	static int prev_pad_harmony_1_level = 100;
	static int prev_pad_harmony_2_level = 0;
	static int prev_pad_harmony_3_level = 0;
	static int prev_pad_harmony_4_level = 0;
	static int prev_pad_harmony_5_level = 0;
	static int prev_pad_harmony_6_level = 0;
	static int prev_pad_harmony_7_level = 0;
	static int prev_pad_harmony_8_level = 0;
	static int prev_pad_harmony_9_level = 0;
	static int prev_pad_harmony_10_level = 0;
	static int prev_pad_harmonies_detune = 0;
	static int prev_pad_base_width = 30;
	static int prev_pad_shape = _PAD_SHAPE_RECTANGULAR;
	static int prev_pad_shape_cutoff = _PAD_SHAPE_CUTOFF_FULL;
	static int prev_pad_quality = _PAD_QUALITY_128K;
	static int prev_pad_base_note = _PAD_BASE_NOTE_C3;

	if (current_frame_index == 0)
	{
		// Presets, Send Filter, Tune and Modulation controls and Harmonies 1-6
		if (evnt == _I2C_CONTROL_ENCODER_2)
		{
			// Gray Purple dial - PAD send filter1 control or open presets dialog if pressed
			if (val == 4096)
			{
				// pressed - open presets dialog
				on_presets_open_pushbutton_clicked();
			}
			else
			{
				// Gray Purple dial - PAD send filter1 control
				pad_send_filter_1 = update_rotary_encoder_value(
					pad_send_filter_1,
					val,
					&prev_pad_send_filter_1,
					pad_control_min,
					pad_control_max,
					4);

				ui->dial_PADsynthSendFilter1->setValue(pad_send_filter_1);
			}
		}
		else if (evnt == _I2C_CONTROL_ENCODER_3)
		{
			// GrayBlue dial - PAD send filter1 control or open presets dialog if pressed
			if (val == 4096)
			{
				// pressed - save presets dialog
				on_presets_save_pushbutton_clicked();
			}
			else
			{
				// Gray Blue dial - PAD send filter2 control
				pad_send_filter_2 = update_rotary_encoder_value(
					pad_send_filter_2,
					val,
					&prev_pad_send_filter_2,
					pad_control_min,
					pad_control_max,
					4);

				ui->dial_PADsynthSendFilter2->setValue(pad_send_filter_2);
			}
		}
		else if (evnt == _I2C_CONTROL_ENCODER_5)
		{
			// Gray White dial - tune octave control
			pad_tune_offset_octave = update_rotary_encoder_value(
				pad_tune_offset_octave,
				val,
				&prev_pad_tune_offset_octave,
				tune_offset_octave_min,
				tune_offset_octave_max,
				1);

			ui->comboBox_PADsynthTuneOctave->setCurrentIndex(pad_tune_offset_octave);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_6)
		{
			// Gray White dial - tune semitone control
			pad_tune_offset_semitone = update_rotary_encoder_value(
				pad_tune_offset_semitone,
				val,
				&prev_pad_tune_offset_semitone,
				tune_offset_semitone_min,
				tune_offset_semitone_max,
				1);

			ui->comboBox_PADsynthTuneSemitones->setCurrentIndex(pad_tune_offset_semitone);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_7)
		{
			// Gray Red dial - tune cents control
			pad_tune_offset_cents = update_rotary_encoder_value(
				pad_tune_offset_cents,
				val,
				&prev_pad_tune_offset_cents,
				tune_offset_cents_min,
				tune_offset_cents_max,
				1);

			ui->comboBox_PADsynthTuneCents->setCurrentIndex(pad_tune_offset_cents);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_10)
		{
			// White Purple dial - Amp Mod ADSR level control
			pad_amp_mod_adsr_level = update_rotary_encoder_value(
				pad_amp_mod_adsr_level,
				val,
				&prev_pad_amp_mod_adsr_level,
				pad_control_min,
				pad_control_max,
				4);

			ui->dial_PADsynth_AmpModAdsrLevel->setValue(pad_amp_mod_adsr_level);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_11)
		{
			// White Blue dial - Amp Mod LFO level control
			pad_amp_mod_lfo_level = update_rotary_encoder_value(
				pad_amp_mod_lfo_level,
				val,
				&prev_pad_amp_mod_lfo_level,
				pad_control_min,
				pad_control_max,
				4);

			ui->dial_PADsynth_AmpModLFOLevel->setValue(pad_amp_mod_lfo_level);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_12)
		{
			// White Green dial - Amp Mod LFO symmetry control
			pad_amp_mod_lfo_symmetry = update_rotary_encoder_value(
				pad_amp_mod_lfo_symmetry,
				val,
				&prev_pad_amp_mod_lfo_symmetry,
				pad_control_min,
				pad_control_max,
				4);

			ui->dial_PADsynth_LFOsymmetry->setValue(pad_amp_mod_lfo_symmetry);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_13)
		{
			// White Whit dial - Amp Mod LFO rate control
			pad_amp_mod_lfo_rate = update_rotary_encoder_value(
				pad_amp_mod_lfo_rate,
				val,
				&prev_pad_amp_mod_lfo_rate,
				pad_control_min,
				pad_control_max,
				4);

			ui->dial_PADsynth_LFOrate->setValue(pad_amp_mod_lfo_rate);
		}
		else if (evnt == _I2C_CONTROL_ENCODER_15)
		{
			// White Red dial - Amp Mod LFO waveform control
			pad_amp_mod_lfo_waveform = update_rotary_encoder_value(
				pad_amp_mod_lfo_waveform,
				val,
				&prev_pad_amp_mod_lfo_waveform,
				_OSC_WAVEFORM_SINE,
				_OSC_WAVEFORM_SAMPHOLD,
				1);

			ui->comboBox_PADsynth_LFOwaveform->setCurrentIndex(pad_amp_mod_lfo_waveform);
		}
		else if (evnt == _I2C_CONTROL_SLIDER_9)
		{
			// Whit Gray slider - ADSR Attack control
			// Get new attack value from slider and calculate gap from current UI value
			pad_amp_mod_adsr_attack = normalize_slider_value(val / 37, 100, 0);						 // 0-3700
			slider_level_gap = pad_amp_mod_adsr_attack - ui->verticalSlider_PADsynth_AdsrA->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_PADsynth_AdsrA->setValue(pad_amp_mod_adsr_attack);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_10)
		{
			// White Purple slider - ADSR Decay control
			// Get new decay value from slider and calculate gap from current UI value
			pad_amp_mod_adsr_decay = normalize_slider_value(val / 37, 100, 0);						// 0-3700
			slider_level_gap = pad_amp_mod_adsr_decay - ui->verticalSlider_PADsynth_AdsrD->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_PADsynth_AdsrD->setValue(pad_amp_mod_adsr_decay);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_11)
		{
			// White Blue slider - ADSR Sustain control
			// Get new sustain value from slider and calculate gap from current UI value
			pad_amp_mod_adsr_sustain = normalize_slider_value(val / 37, 100, 0);					  // 0-3700
			slider_level_gap = pad_amp_mod_adsr_sustain - ui->verticalSlider_PADsynth_AdsrS->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_PADsynth_AdsrS->setValue(pad_amp_mod_adsr_sustain);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_12)
		{
			// White Green slider - ADSR Release control
			// Get new release value from slider and calculate gap from current UI value
			pad_amp_mod_adsr_release = normalize_slider_value(val / 37, 100, 0);					  // 0-3700
			slider_level_gap = pad_amp_mod_adsr_release - ui->verticalSlider_PADsynth_AdsrR->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_PADsynth_AdsrR->setValue(pad_amp_mod_adsr_release);
			}
		}
	}
	else if (current_frame_index == 0 | current_frame_index == 1)
	{
		// harmonies 1 - 6
		if (evnt == _I2C_CONTROL_SLIDER_1)
		{
			// Gray Gray slider - Harmony 1 control
			// Get new harmony 1 value from slider and calculate gap from current UI value
			pad_harmony_1_level = normalize_slider_value(val / 37, 100, 0);							 // 0-3700
			slider_level_gap = pad_harmony_1_level - ui->verticalSlider_PADsynth_Harmony_1->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_PADsynth_Harmony_1->setValue(pad_harmony_1_level);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_2)
		{
			// Gray Purple slider - Harmony 2 control
			// Get new harmony 2 value from slider and calculate gap from current UI value
			pad_harmony_2_level = normalize_slider_value(val / 37, 100, 0);							 // 0-3700
			slider_level_gap = pad_harmony_2_level - ui->verticalSlider_PADsynth_Harmony_2->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_PADsynth_Harmony_2->setValue(pad_harmony_2_level);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_3)
		{
			// Gray Blue slider - Harmony 3 control
			// Get new harmony 3 value from slider and calculate gap from current UI value
			pad_harmony_3_level = normalize_slider_value(val / 37, 100, 0);							 // 0-3700
			slider_level_gap = pad_harmony_3_level - ui->verticalSlider_PADsynth_Harmony_3->value(); // 0-100
			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_PADsynth_Harmony_3->setValue(pad_harmony_3_level);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_4)
		{
			// Gray Green slider - Harmony 4 control
			// Get new harmony 4 value from slider and calculate gap from current UI value
			pad_harmony_4_level = normalize_slider_value(val / 37, 100, 0);							 // 0-3700
			slider_level_gap = pad_harmony_4_level - ui->verticalSlider_PADsynth_Harmony_4->value(); // 0-100

			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_PADsynth_Harmony_4->setValue(pad_harmony_4_level);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_5)
		{
			// Gray White slider - Harmony 5 control
			// Get new harmony 5 value from slider and calculate gap from current UI value
			pad_harmony_5_level = normalize_slider_value(val / 37, 100, 0);							 // 0-3700
			slider_level_gap = pad_harmony_5_level - ui->verticalSlider_PADsynth_Harmony_5->value(); // 0-100
			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_PADsynth_Harmony_5->setValue(pad_harmony_5_level);
			}
		}
		else if (evnt == _I2C_CONTROL_SLIDER_6)
		{
			// Gray Yellow slider - Harmony 6 control
			// Get new harmony 6 value from slider and calculate gap from current UI value
			pad_harmony_6_level = normalize_slider_value(val / 37, 100, 0);							 // 0-3700
			slider_level_gap = pad_harmony_6_level - ui->verticalSlider_PADsynth_Harmony_6->value(); // 0-100
			// Change slider value only when it matches the UI slider position.
			if (abs((float)slider_level_gap) < 100 / 5.0)
			{
				// Emits value changed signal.
				ui->verticalSlider_PADsynth_Harmony_6->setValue(pad_harmony_6_level);
			}
		}
		
		if (current_frame_index == 1)
		{
			// spectrum controls, harmonies 7-10 and harmonies detune
			if (evnt == _I2C_CONTROL_SLIDER_9)
			{
				// White Gray slider - Harmony 7 control
				// Get new harmony 7 value from slider and calculate gap from current UI value
				pad_harmony_7_level = normalize_slider_value(val / 37, 100, 0);							 // 0-3700
				slider_level_gap = pad_harmony_7_level - ui->verticalSlider_PADsynth_Harmony_7->value(); // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < 100 / 5.0)
				{
					// Emits value changed signal.
					ui->verticalSlider_PADsynth_Harmony_7->setValue(pad_harmony_7_level);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_10)
			{
				// Gray Purple slider - Harmony 8 control
				// Get new harmony 8 value from slider and calculate gap from current UI value
				pad_harmony_8_level = normalize_slider_value(val / 37, 100, 0);							 // 0-3700
				slider_level_gap = pad_harmony_8_level - ui->verticalSlider_PADsynth_Harmony_8->value(); // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < 100 / 5.0)
				{
					// Emits value changed signal.
					ui->verticalSlider_PADsynth_Harmony_8->setValue(pad_harmony_8_level);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_11)
			{
				// Gray Blue slider - Harmony 9 control
				// Get new harmony 9 value from slider and calculate gap from current UI value
				pad_harmony_9_level = normalize_slider_value(val / 37, 100, 0);							 // 0-3700
				slider_level_gap = pad_harmony_9_level - ui->verticalSlider_PADsynth_Harmony_9->value(); // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < 100 / 5.0)
				{
					// Emits value changed signal.
					ui->verticalSlider_PADsynth_Harmony_9->setValue(pad_harmony_9_level);
				}
			}
			else if (evnt == _I2C_CONTROL_SLIDER_12)
			{
				// Gray Green slider - Harmony 10 control
				// Get new harmony 10 value from slider and calculate gap from current UI value
				pad_harmony_10_level = normalize_slider_value(val / 37, 100, 0);						   // 0-3700
				slider_level_gap = pad_harmony_10_level - ui->verticalSlider_PADsynth_Harmony_10->value(); // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < 100 / 5.0)
				{
					// Emits value changed signal.
					ui->verticalSlider_PADsynth_Harmony_10->setValue(pad_harmony_10_level);
				}
			}
			if (evnt == _I2C_CONTROL_SLIDER_13)
			{
				// Gray White slider - Detune control
				// Get new detune value from slider and calculate gap from current UI value
				pad_harmonies_detune = normalize_slider_value(val / 37, 100, 0);							  // 0-3700
				slider_level_gap = pad_harmonies_detune - ui->verticalSlider_PADsynth_HarmonyDetune->value(); // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < 100 / 5.0)
				{
					// Emits value changed signal.
					ui->verticalSlider_PADsynth_HarmonyDetune->setValue(pad_harmonies_detune);
				}
			}
			if (evnt == _I2C_CONTROL_SLIDER_14)
			{
				// Gray Red slider - Base width control
				// Get new base width value from slider and calculate gap from current UI value
				pad_base_width = normalize_slider_value(val / 37, 100, 0);							  // 0-3700
				slider_level_gap = pad_base_width - ui->horizontalSlider_PADsynth_BaseWidth->value(); // 0-100

				// Change slider value only when it matches the UI slider position.
				if (abs((float)slider_level_gap) < 100 / 5.0)
				{
					// Emits value changed signal.
					ui->horizontalSlider_PADsynth_BaseWidth->setValue(pad_base_width);
				}
			}
			else if (evnt == _I2C_CONTROL_ENCODER_10)
			{
				// White Purple dial - spectrum shape combo control
				pad_shape = update_rotary_encoder_value(
					pad_shape,
					val,
					&prev_pad_shape,
					pad_shape_min,
					pad_shape_max,
					1);

				ui->comboBox_PADsynth_Shape->setCurrentIndex(pad_shape);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_11)
			{
				if (val == 4096)
				{
					// White Blue pressed - generate
					on_generate_pushbutton_clicked();
				}
				else
				{
					// White Blue dial - spectrum shape cutoff combo control
					pad_shape_cutoff = update_rotary_encoder_value(
						pad_shape_cutoff,
						val,
						&prev_pad_shape_cutoff,
						pad_shape_cutoff_min,
						pad_shape_cutoff_max,
						1);

					ui->comboBox_PADsynth_ShapeCutoff->setCurrentIndex(pad_shape_cutoff);
				}
			}
			else if (evnt == _I2C_CONTROL_ENCODER_12)
			{
				// White Green dial - base note combo control
				pad_base_note = update_rotary_encoder_value(
					pad_base_note,
					val,
					&prev_pad_base_note,
					pad_base_note_min,
					pad_base_note_max,
					1);

				ui->comboBox_PADsynth_BaseNote->setCurrentIndex(pad_base_note);
			}
			else if (evnt == _I2C_CONTROL_ENCODER_13)
			{
				// White Whit dial - quality combo control
				pad_quality = update_rotary_encoder_value(
					pad_quality,
					val,
					&prev_pad_quality,
					pad_quality_min,
					pad_quality_max,
					1);

				ui->comboBox_PADsynth_Quality->setCurrentIndex(pad_quality);
			}
		}
	}
}

void Dialog_PADsynthesizer::on_dialog_close()
{
	close();
}

void Dialog_PADsynthesizer::on_presets_open_pushbutton_clicked()
{
	QString startDir = last_pad_synth_preset_directory.isEmpty() ? QString(_PAD_SYNTH_PRESETS_FILES_DEFAULT_DIR) : last_pad_synth_preset_directory;

	CustomFileDialog dialog(this,
							tr("Open Preset File"),
							startDir,
							tr("Presets (*.xml *.XML);;All Files (*)"),
							Qt::black); // Background color set here)

	// If we have a last file, select it and scroll to it
	if (!last_pad_synth_preset_load_file.isEmpty())
	{
		dialog.selectFile(last_pad_synth_preset_load_file);
	}

	if (dialog.exec() == QDialog::Accepted)
	{
		pad_synth_preset_file_name = dialog.selectedFile();

		if (!pad_synth_preset_file_name.isEmpty())
		{
			// Remember the directory and file for next time
			last_pad_synth_preset_directory = QFileInfo(pad_synth_preset_file_name).absolutePath();
			last_pad_synth_preset_load_file = pad_synth_preset_file_name;

			std::string file_name;
			// file_name = std::string("Now Loading: ");
			file_name = std::filesystem::path(pad_synth_preset_file_name.toStdString()).stem();

			ui->textEdit_PADsynth_PresetText->setText(QString::fromStdString(file_name));

			load_pad_synthesizer_preset_file_thread = new LoadPADsynthesizerPresetFileThread();
			connect(load_pad_synthesizer_preset_file_thread,
					&LoadPADsynthesizerPresetFileThread::finished, load_pad_synthesizer_preset_file_thread, &QObject::deleteLater);
			connect(load_pad_synthesizer_preset_file_thread, &LoadPADsynthesizerPresetFileThread::loadPresetFileDone,
					this, &Dialog_PADsynthesizer::on_preset_file_loaded);
			load_pad_synthesizer_preset_file_thread->start();
		}
	}
}

void Dialog_PADsynthesizer::on_presets_save_pushbutton_clicked()
{
	QString startDir = last_pad_synth_preset_directory.isEmpty() ? QString(_PAD_SYNTH_PRESETS_FILES_DEFAULT_DIR) : last_pad_synth_preset_directory;

	// Use CustomFileDialog in Save mode
	CustomFileDialog dialog(this,
							tr("Save Preset File"),
							startDir,
							tr("Presets (*.xml *.XML);;All Files (*)"),
							Qt::black,
							CustomFileDialog::SaveMode); // Set to Save mode

	if (dialog.exec() == QDialog::Accepted)
	{
		pad_synth_preset_file_name = dialog.selectedFile();

		if (!pad_synth_preset_file_name.isEmpty())
		{
			// Ensure .xml extension
			if (!pad_synth_preset_file_name.endsWith(".xml", Qt::CaseInsensitive))
			{
				pad_synth_preset_file_name += ".xml";
			}

			// Check if file exists and ask for confirmation
			if (QFile::exists(pad_synth_preset_file_name))
			{
				QMessageBox msgBox;
				msgBox.setIcon(QMessageBox::Warning);
				msgBox.setWindowTitle("Confirm Overwrite");
				msgBox.setText(QString("File '%1' already exists.")
								   .arg(QFileInfo(pad_synth_preset_file_name).fileName()));
				msgBox.setInformativeText("Do you want to overwrite it?");
				msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
				msgBox.setDefaultButton(QMessageBox::Cancel);

				if (msgBox.exec() != QMessageBox::Yes)
				{
					return;
				}
			}

			// Remember the directory and file for next time
			last_pad_synth_preset_directory = QFileInfo(pad_synth_preset_file_name).absolutePath();
			last_pad_synth_preset_save_file = pad_synth_preset_file_name;

			// Display saving message
			std::string file_name = std::string("Now Saving: ");
			file_name += std::filesystem::path(pad_synth_preset_file_name.toStdString()).stem().string();
			// ui->textEdit_HammondPresetText->setText(QString::fromStdString(file_name));

			// Start the save thread
			save_pad_synthesizer_preset_file_thread = new SavePADsynthesizerPresetFileThread();
			connect(save_pad_synthesizer_preset_file_thread,
					&SavePADsynthesizerPresetFileThread::finished,
					save_pad_synthesizer_preset_file_thread,
					&QObject::deleteLater);
			connect(save_pad_synthesizer_preset_file_thread,
					&SavePADsynthesizerPresetFileThread::savePresetFileDone,
					this,
					&Dialog_PADsynthesizer::on_preset_file_saved);

			save_pad_synthesizer_preset_file_thread->start();
		}
	}
}

void Dialog_PADsynthesizer::on_preset_file_loaded(const QString &s)
{
	update_adsr_plot = true;
	update_profile_plot = true;
	update_spectrum_plot = true;
	update_spectrum_params = true;
}

void Dialog_PADsynthesizer::on_preset_file_saved(const QString &s)
{
}

void Dialog_PADsynthesizer::on_detune_octave_combobox_changed(int val)
{
	ui->comboBox_PADsynthTuneOctave->blockSignals(true);
	ui->comboBox_PADsynthTuneOctave->setCurrentIndex(val);
	ui->comboBox_PADsynthTuneOctave->blockSignals(false);

	tune_octave = val;
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_DETUNE_OCTAVE, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_detune_semitones_combobox_changed(int val)
{
	ui->comboBox_PADsynthTuneSemitones->blockSignals(true);
	ui->comboBox_PADsynthTuneSemitones->setCurrentIndex(val);
	ui->comboBox_PADsynthTuneSemitones->blockSignals(false);

	tune_semitones = val;
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_DETUNE_SEMITONES, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_detune_cents_combobox_changed(int val)
{
	ui->comboBox_PADsynthTuneCents->blockSignals(true);
	ui->comboBox_PADsynthTuneCents->setCurrentIndex(val);
	ui->comboBox_PADsynthTuneCents->blockSignals(false);

	tune_cents = val;
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_DETUNE_CENTS, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_send_filter1_dial_changed(int val)
{
	ui->dial_PADsynthSendFilter1->blockSignals(true);
	ui->dial_PADsynthSendFilter1->setValue(val);
	ui->dial_PADsynthSendFilter1->blockSignals(false);

	ui->spinBox_PADsynthSendFilter1->blockSignals(true);
	ui->spinBox_PADsynthSendFilter1->setValue(val);
	ui->spinBox_PADsynthSendFilter1->blockSignals(false);

	send_filter_1_level = val;
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_FILTER_SEND_1, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_send_filter2_dial_changed(int val)
{
	ui->dial_PADsynthSendFilter2->blockSignals(true);
	ui->dial_PADsynthSendFilter2->setValue(val);
	ui->dial_PADsynthSendFilter2->blockSignals(false);

	ui->spinBox_PADsynthSendFilter2->blockSignals(true);
	ui->spinBox_PADsynthSendFilter2->setValue(val);
	ui->spinBox_PADsynthSendFilter2->blockSignals(false);

	send_filter_2_level = val;
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_FILTER_SEND_2, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_mod_lfo_level_dial_changed(int val)
{
	ui->dial_PADsynth_AmpModLFOLevel->blockSignals(true);
	ui->dial_PADsynth_AmpModLFOLevel->setValue(val);
	ui->dial_PADsynth_AmpModLFOLevel->blockSignals(false);

	ui->spinBox_PADsynth_AmpModLfoLevel->blockSignals(true);
	ui->spinBox_PADsynth_AmpModLfoLevel->setValue(val);
	ui->spinBox_PADsynth_AmpModLfoLevel->blockSignals(false);

	amp_mod_lfo_level = val;
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_AMP_MOD_LFO_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_mod_lfo_frequency_dial_changed(int val)
{
	char text[64];

	ui->dial_PADsynth_LFOrate->blockSignals(true);
	ui->dial_PADsynth_LFOrate->setValue(val);
	ui->dial_PADsynth_LFOrate->blockSignals(false);

	amp_mod_lfo_rate = val;

	sprintf(text,
			"%.2fHz",
			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
										  mod_synth_get_lfo_max_frequency(),
										  10.0,
										  val));

	ui->lineEdit_PADsynth_LFOrate->setText(QString(text));

	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _MOD_LFO_RATE, val);
}

void Dialog_PADsynthesizer::on_mod_lfo_symmetry_dial_changed(int val)
{
	char text[64];

	ui->dial_PADsynth_LFOsymmetry->blockSignals(true);
	ui->dial_PADsynth_LFOsymmetry->setValue(val);
	ui->dial_PADsynth_LFOsymmetry->blockSignals(false);

	amp_mod_lfo_symetry = val;

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_PADsynth_LFOsymmetry->setText(QString(text));

	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _MOD_LFO_SYMMETRY, val);
}

void Dialog_PADsynthesizer::on_mod_lfo_waveform_combobox_changed(int val)
{
	ui->comboBox_PADsynth_LFOwaveform->blockSignals(true);
	ui->comboBox_PADsynth_LFOwaveform->setCurrentIndex(val);
	ui->comboBox_PADsynth_LFOwaveform->blockSignals(false);

	amp_mod_waveform = val;
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _MOD_LFO_WAVEFORM, val);
}

void Dialog_PADsynthesizer::on_mod_env_level_dial_changed(int val)
{
	ui->dial_PADsynth_AmpModAdsrLevel->blockSignals(true);
	ui->dial_PADsynth_AmpModAdsrLevel->setValue(val);
	ui->dial_PADsynth_AmpModAdsrLevel->blockSignals(false);

	ui->spinBox_PADsynth_AmpModAdsrLevel->blockSignals(true);
	ui->spinBox_PADsynth_AmpModAdsrLevel->setValue(val);
	ui->spinBox_PADsynth_AmpModAdsrLevel->blockSignals(false);

	amp_mod_lfo_level = val;
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_AMP_MOD_ENV_LEVEL, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_mod_env_attack_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_PADsynth_AdsrA->blockSignals(true);
	ui->verticalSlider_PADsynth_AdsrA->setValue(val);
	ui->verticalSlider_PADsynth_AdsrA->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_attack_time_sec(),
										  10.0, val));

	ui->lineEdit_PADsynth_AdsrA->setText(QString(text));

	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _MOD_ADSR_ATTACK, val);
	amp_mod_adsr_attack = val;
	
	update_adsr_plot = true;
}

void Dialog_PADsynthesizer::on_mod_env_decay_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_PADsynth_AdsrD->blockSignals(true);
	ui->verticalSlider_PADsynth_AdsrD->setValue(val);
	ui->verticalSlider_PADsynth_AdsrD->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_decay_time_sec(),
										  10.0, val));

	ui->lineEdit_PADsynth_AdsrD->setText(QString(text));

	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _MOD_ADSR_DECAY, val);
	amp_mod_adsr_decay = val;

	update_adsr_plot = true;
}

void Dialog_PADsynthesizer::on_mod_env_sustain_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_PADsynth_AdsrS->blockSignals(true);
	ui->verticalSlider_PADsynth_AdsrS->setValue(val);
	ui->verticalSlider_PADsynth_AdsrS->blockSignals(false);

	sprintf(text, "%i%c", val, '%');
	ui->lineEdit_PADsynth_AdsrS->setText(QString(text));

	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _MOD_ADSR_SUSTAIN, val);
	amp_mod_adsr_sustain = val;

	update_adsr_plot = true;
}

void Dialog_PADsynthesizer::on_mod_env_release_slider_changed(int val)
{
	char text[64];

	ui->verticalSlider_PADsynth_AdsrR->blockSignals(true);
	ui->verticalSlider_PADsynth_AdsrR->setValue(val);
	ui->verticalSlider_PADsynth_AdsrR->blockSignals(false);

	sprintf(text,
			"%.2fS",
			mod_synth_log_scale_100_float(0.0,
										  mod_synth_get_adsr_max_release_time_sec(),
										  10.0, val));

	ui->lineEdit_PADsynth_AdsrR->setText(QString(text));

	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _MOD_ADSR_RELEASE, val);
	amp_mod_adsr_release = val;

	update_adsr_plot = true;
}

void Dialog_PADsynthesizer::on_quality_combobox_changed(int val)
{
	ui->comboBox_PADsynth_Quality->blockSignals(true);
	ui->comboBox_PADsynth_Quality->setCurrentIndex(val);
	ui->comboBox_PADsynth_Quality->blockSignals(false);

	quality = val;

	mod_synth_disable_pad_synth_instrument();
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_QUALITY, val);

	update_profile_plot = true;
	update_spectrum_plot = true;

	mod_synth_enable_pad_synth_instrument();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_base_note_combobox_changed(int val)
{
	ui->comboBox_PADsynth_BaseNote->blockSignals(true);
	ui->comboBox_PADsynth_BaseNote->setCurrentIndex(val);
	ui->comboBox_PADsynth_BaseNote->blockSignals(false);

	base_note = val;

	mod_synth_disable_pad_synth_instrument();
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_BASE_NOTE, val);

	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth_instrument();

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_base_width_slider_changed(int val)
{
	ui->horizontalSlider_PADsynth_BaseWidth->blockSignals(true);
	ui->horizontalSlider_PADsynth_BaseWidth->setValue(val);
	ui->horizontalSlider_PADsynth_BaseWidth->blockSignals(false);

	ui->spinBox_PADsynth_BaseWidth->blockSignals(true);
	ui->spinBox_PADsynth_BaseWidth->setValue(val);
	ui->spinBox_PADsynth_BaseWidth->blockSignals(false);

	base_width = val;

	mod_synth_disable_pad_synth_instrument();
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_BASE_WIDTH, val);

	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth_instrument();

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_shape_combobox_changed(int val)
{
	ui->comboBox_PADsynth_Shape->blockSignals(true);
	ui->comboBox_PADsynth_Shape->setCurrentIndex(val);
	ui->comboBox_PADsynth_Shape->blockSignals(false);

	shape = val;

	mod_synth_disable_pad_synth_instrument();
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_SHAPE, val);

	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth_instrument();

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_shape_cutoff_combobox_changed(int val)
{
	ui->comboBox_PADsynth_ShapeCutoff->blockSignals(true);
	ui->comboBox_PADsynth_ShapeCutoff->setCurrentIndex(val);
	ui->comboBox_PADsynth_ShapeCutoff->blockSignals(false);

	shape_cutoff = val;

	mod_synth_disable_pad_synth_instrument();
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_SHAPE_CUTOFF, val);

	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth_instrument();

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_generate_pushbutton_clicked()
{
	mod_synth_disable_pad_synth_instrument(); 
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth();

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_harmony1_level_slider_changed(int val)
{
	ui->verticalSlider_PADsynth_Harmony_1->blockSignals(true);
	ui->verticalSlider_PADsynth_Harmony_1->setValue(val);
	ui->verticalSlider_PADsynth_Harmony_1->blockSignals(false);

	ui->spinBox_PADsynth_Harmony_1->blockSignals(true);
	ui->spinBox_PADsynth_Harmony_1->setValue(val);
	ui->spinBox_PADsynth_Harmony_1->blockSignals(false);

	harmony_1_level = val;

	mod_synth_disable_pad_synth_instrument();
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_HARMONY_LEVEL_1, val);

	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth_instrument();

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_harmony2_level_slider_changed(int val)
{
	ui->verticalSlider_PADsynth_Harmony_2->blockSignals(true);
	ui->verticalSlider_PADsynth_Harmony_2->setValue(val);
	ui->verticalSlider_PADsynth_Harmony_2->blockSignals(false);
	
	ui->spinBox_PADsynth_Harmony_2->blockSignals(true);
	ui->spinBox_PADsynth_Harmony_2->setValue(val);
	ui->spinBox_PADsynth_Harmony_2->blockSignals(false);
	
	harmony_2_level = val;
	
	mod_synth_disable_pad_synth_instrument();
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_HARMONY_LEVEL_2, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth_instrument();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_harmony3_level_slider_changed(int val)
{
	ui->verticalSlider_PADsynth_Harmony_3->blockSignals(true);
	ui->verticalSlider_PADsynth_Harmony_3->setValue(val);
	ui->verticalSlider_PADsynth_Harmony_3->blockSignals(false);

	ui->spinBox_PADsynth_Harmony_3->blockSignals(true);
	ui->spinBox_PADsynth_Harmony_3->setValue(val);
	ui->spinBox_PADsynth_Harmony_3->blockSignals(false);

	harmony_3_level = val;

	mod_synth_disable_pad_synth_instrument();
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_HARMONY_LEVEL_3, val);

	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth_instrument();

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_harmony4_level_slider_changed(int val)
{
	ui->verticalSlider_PADsynth_Harmony_4->blockSignals(true);
	ui->verticalSlider_PADsynth_Harmony_4->setValue(val);
	ui->verticalSlider_PADsynth_Harmony_4->blockSignals(false);
	
	ui->spinBox_PADsynth_Harmony_4->blockSignals(true);
	ui->spinBox_PADsynth_Harmony_4->setValue(val);
	ui->spinBox_PADsynth_Harmony_4->blockSignals(false);
	
	harmony_4_level = val;
	
	mod_synth_disable_pad_synth_instrument();
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_HARMONY_LEVEL_4, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth_instrument();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_harmony5_level_slider_changed(int val)
{
	ui->verticalSlider_PADsynth_Harmony_5->blockSignals(true);
	ui->verticalSlider_PADsynth_Harmony_5->setValue(val);
	ui->verticalSlider_PADsynth_Harmony_5->blockSignals(false);

	ui->spinBox_PADsynth_Harmony_5->blockSignals(true);
	ui->spinBox_PADsynth_Harmony_5->setValue(val);
	ui->spinBox_PADsynth_Harmony_5->blockSignals(false);

	harmony_5_level = val;

	mod_synth_disable_pad_synth_instrument();
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_HARMONY_LEVEL_5, val);

	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth_instrument();

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_harmony6_level_slider_changed(int val)
{
	ui->verticalSlider_PADsynth_Harmony_6->blockSignals(true);
	ui->verticalSlider_PADsynth_Harmony_6->setValue(val);
	ui->verticalSlider_PADsynth_Harmony_6->blockSignals(false);
	
	ui->spinBox_PADsynth_Harmony_6->blockSignals(true);
	ui->spinBox_PADsynth_Harmony_6->setValue(val);
	ui->spinBox_PADsynth_Harmony_6->blockSignals(false);
	
	harmony_6_level = val;
	
	mod_synth_disable_pad_synth_instrument();
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_HARMONY_LEVEL_6, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	
	mod_synth_enable_pad_synth_instrument();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_harmony7_level_slider_changed(int val)
{
	ui->verticalSlider_PADsynth_Harmony_7->blockSignals(true);
	ui->verticalSlider_PADsynth_Harmony_7->setValue(val);
	ui->verticalSlider_PADsynth_Harmony_7->blockSignals(false);

	ui->spinBox_PADsynth_Harmony_7->blockSignals(true);
	ui->spinBox_PADsynth_Harmony_7->setValue(val);
	ui->spinBox_PADsynth_Harmony_7->blockSignals(false);

	harmony_7_level = val;

	mod_synth_disable_pad_synth_instrument();
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_HARMONY_LEVEL_7, val);
	update_profile_plot = true;

	update_spectrum_plot = true;
	mod_synth_enable_pad_synth_instrument();

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_harmony8_level_slider_changed(int val)
{
	ui->verticalSlider_PADsynth_Harmony_8->blockSignals(true);
	ui->verticalSlider_PADsynth_Harmony_8->setValue(val);
	ui->verticalSlider_PADsynth_Harmony_8->blockSignals(false);
	
	ui->spinBox_PADsynth_Harmony_8->blockSignals(true);
	ui->spinBox_PADsynth_Harmony_8->setValue(val);
	ui->spinBox_PADsynth_Harmony_8->blockSignals(false);
	
	harmony_8_level = val;
	
	mod_synth_disable_pad_synth_instrument();
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_HARMONY_LEVEL_8, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	
	mod_synth_enable_pad_synth_instrument();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_harmony9_level_slider_changed(int val)
{
	ui->verticalSlider_PADsynth_Harmony_9->blockSignals(true);
	ui->verticalSlider_PADsynth_Harmony_9->setValue(val);
	ui->verticalSlider_PADsynth_Harmony_9->blockSignals(false);
	
	ui->spinBox_PADsynth_Harmony_9->blockSignals(true);
	ui->spinBox_PADsynth_Harmony_9->setValue(val);
	ui->spinBox_PADsynth_Harmony_9->blockSignals(false);
	
	harmony_9_level = val;
	
	mod_synth_disable_pad_synth_instrument();
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_HARMONY_LEVEL_9, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	
	mod_synth_enable_pad_synth_instrument();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_harmony10_level_slider_changed(int val)
{
	ui->verticalSlider_PADsynth_Harmony_10->blockSignals(true);
	ui->verticalSlider_PADsynth_Harmony_10->setValue(val);
	ui->verticalSlider_PADsynth_Harmony_10->blockSignals(false);
	
	ui->spinBox_PADsynth_Harmony_10->blockSignals(true);
	ui->spinBox_PADsynth_Harmony_10->setValue(val);
	ui->spinBox_PADsynth_Harmony_10->blockSignals(false);
	
	harmony_10_level = val;
	
	mod_synth_disable_pad_synth_instrument();
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_HARMONY_LEVEL_10, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	
	mod_synth_enable_pad_synth_instrument();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::on_harmonies_detune_slider_changed(int val)
{
	ui->verticalSlider_PADsynth_HarmonyDetune->blockSignals(true);
	ui->verticalSlider_PADsynth_HarmonyDetune->setValue(val);
	ui->verticalSlider_PADsynth_HarmonyDetune->blockSignals(false);
	
	ui->spinBox_PADsynth_HarmonyDetune->blockSignals(true);
	ui->spinBox_PADsynth_HarmonyDetune->setValue(val);
	ui->spinBox_PADsynth_HarmonyDetune->blockSignals(false);
	
	harmonies_detune = val;
	
	mod_synth_disable_pad_synth_instrument();
	mod_synth_pad_synth_event_int(_PAD_SYNTH_EVENT, _PAD_DETUNE, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	
	mod_synth_enable_pad_synth_instrument();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_PADsynthesizer::update_gui()
{
	if (update_adsr_plot)
	{
		adsr_curve_max_attack = mod_synth_get_adsr_max_attack_time_sec();
		adsr_curve_max_decay = mod_synth_get_adsr_max_decay_time_sec();
		adsr_curve_max_sustain = 100; //%
		adsr_curve_max_release = mod_synth_get_adsr_max_release_time_sec();
		
		set_adsr_plot_widget_points();
		refresh_adsr_curve_view(ui->widget_ADSRplot);
		
		update_adsr_plot = false;
	}

	if (update_profile_plot)
	{
		pad_replot_profile();

		update_profile_plot = false;
	}

	if (update_spectrum_plot)
	{
		pad_replot_spectrum();

		update_spectrum_plot = false;
	}

	ui->comboBox_PADsynthTuneOctave->blockSignals(true);
	ui->comboBox_PADsynthTuneOctave->setCurrentIndex(mod_synth_get_pad_synth_int_param(_PAD_DETUNE_OCTAVE) - _OSC_DETUNE_MIN_OCTAVE);
	ui->comboBox_PADsynthTuneOctave->blockSignals(false);

	ui->comboBox_PADsynthTuneSemitones->blockSignals(true);
	ui->comboBox_PADsynthTuneSemitones->setCurrentIndex(mod_synth_get_pad_synth_int_param(_PAD_DETUNE_SEMITONES) - _OSC_DETUNE_MIN_SEMITONES);
	ui->comboBox_PADsynthTuneSemitones->blockSignals(false);

	ui->comboBox_PADsynthTuneCents->blockSignals(true);
	ui->comboBox_PADsynthTuneCents->setCurrentIndex(mod_synth_get_pad_synth_int_param(_PAD_DETUNE_CENTS) - _OSC_DETUNE_MIN_CENTS * 4.f);
	ui->comboBox_PADsynthTuneCents->blockSignals(false);

	ui->dial_PADsynthSendFilter1->blockSignals(true);
	ui->dial_PADsynthSendFilter1->setValue(mod_synth_get_pad_synth_int_param(_PAD_FILTER_SEND_1));
	ui->dial_PADsynthSendFilter1->blockSignals(false);

	ui->dial_PADsynthSendFilter2->blockSignals(true);
	ui->dial_PADsynthSendFilter2->setValue(mod_synth_get_pad_synth_int_param(_PAD_FILTER_SEND_2));
	ui->dial_PADsynthSendFilter2->blockSignals(false);

	ui->dial_PADsynth_AmpModLFOLevel->blockSignals(true);
	ui->dial_PADsynth_AmpModLFOLevel->setValue(mod_synth_get_pad_synth_int_param(_PAD_AMP_MOD_LFO_LEVEL));
	ui->dial_PADsynth_AmpModLFOLevel->blockSignals(false);

	ui->dial_PADsynth_LFOrate->blockSignals(true);
	ui->dial_PADsynth_LFOrate->setValue(mod_synth_get_pad_synth_int_param(_MOD_LFO_RATE));
	ui->dial_PADsynth_LFOrate->blockSignals(false);

	ui->dial_PADsynth_LFOsymmetry->blockSignals(true);
	ui->dial_PADsynth_LFOsymmetry->setValue(mod_synth_get_pad_synth_int_param(_MOD_LFO_SYMMETRY));
	ui->dial_PADsynth_LFOsymmetry->blockSignals(false);

	ui->comboBox_PADsynth_LFOwaveform->blockSignals(true);
	ui->comboBox_PADsynth_LFOwaveform->setCurrentIndex(mod_synth_get_pad_synth_int_param(_MOD_LFO_WAVEFORM));
	ui->comboBox_PADsynth_LFOwaveform->blockSignals(false);

	ui->dial_PADsynth_AmpModAdsrLevel->blockSignals(true);
	ui->dial_PADsynth_AmpModAdsrLevel->setValue(mod_synth_get_pad_synth_int_param(_PAD_AMP_MOD_ENV_LEVEL));
	ui->dial_PADsynth_AmpModAdsrLevel->blockSignals(false);

	ui->verticalSlider_PADsynth_AdsrA->blockSignals(true);
	ui->verticalSlider_PADsynth_AdsrA->setValue(mod_synth_get_pad_synth_int_param(_MOD_ADSR_ATTACK));
	ui->verticalSlider_PADsynth_AdsrA->blockSignals(false);

	ui->verticalSlider_PADsynth_AdsrD->blockSignals(true);
	ui->verticalSlider_PADsynth_AdsrD->setValue(mod_synth_get_pad_synth_int_param(_MOD_ADSR_DECAY));
	ui->verticalSlider_PADsynth_AdsrD->blockSignals(false);

	ui->verticalSlider_PADsynth_AdsrS->blockSignals(true);
	ui->verticalSlider_PADsynth_AdsrS->setValue(mod_synth_get_pad_synth_int_param(_MOD_ADSR_SUSTAIN));
	ui->verticalSlider_PADsynth_AdsrS->blockSignals(false);

	ui->verticalSlider_PADsynth_AdsrR->blockSignals(true);
	ui->verticalSlider_PADsynth_AdsrR->setValue(mod_synth_get_pad_synth_int_param(_MOD_ADSR_RELEASE));
	ui->verticalSlider_PADsynth_AdsrR->blockSignals(false);

	if (update_spectrum_params)
	{
		ui->comboBox_PADsynth_Quality->blockSignals(true);
		ui->comboBox_PADsynth_Quality->setCurrentIndex(mod_synth_get_pad_synth_int_param(_PAD_QUALITY));
		ui->comboBox_PADsynth_Quality->blockSignals(false);

		ui->comboBox_PADsynth_Shape->blockSignals(true);
		ui->comboBox_PADsynth_Shape->setCurrentIndex(mod_synth_get_pad_synth_int_param(_PAD_SHAPE));
		ui->comboBox_PADsynth_Shape->blockSignals(false);

		ui->comboBox_PADsynth_ShapeCutoff->blockSignals(true);
		ui->comboBox_PADsynth_ShapeCutoff->setCurrentIndex(mod_synth_get_pad_synth_int_param(_PAD_SHAPE_CUTOFF));
		ui->comboBox_PADsynth_ShapeCutoff->blockSignals(false);

		ui->comboBox_PADsynth_BaseNote->blockSignals(true);
		ui->comboBox_PADsynth_BaseNote->setCurrentIndex(mod_synth_get_pad_synth_int_param(_PAD_BASE_NOTE));
		ui->comboBox_PADsynth_BaseNote->blockSignals(false);

		ui->horizontalSlider_PADsynth_BaseWidth->blockSignals(true);
		ui->horizontalSlider_PADsynth_BaseWidth->setValue(mod_synth_get_pad_synth_int_param(_PAD_BASE_WIDTH));
		ui->horizontalSlider_PADsynth_BaseWidth->blockSignals(false);

		ui->verticalSlider_PADsynth_Harmony_1->blockSignals(true);
		ui->verticalSlider_PADsynth_Harmony_1->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_1));
		ui->verticalSlider_PADsynth_Harmony_1->blockSignals(false);

		ui->verticalSlider_PADsynth_Harmony_2->blockSignals(true);
		ui->verticalSlider_PADsynth_Harmony_2->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_2));
		ui->verticalSlider_PADsynth_Harmony_2->blockSignals(false);

		ui->verticalSlider_PADsynth_Harmony_3->blockSignals(true);
		ui->verticalSlider_PADsynth_Harmony_3->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_3));
		ui->verticalSlider_PADsynth_Harmony_3->blockSignals(false);

		ui->verticalSlider_PADsynth_Harmony_4->blockSignals(true);
		ui->verticalSlider_PADsynth_Harmony_4->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_4));
		ui->verticalSlider_PADsynth_Harmony_4->blockSignals(false);

		ui->verticalSlider_PADsynth_Harmony_5->blockSignals(true);
		ui->verticalSlider_PADsynth_Harmony_5->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_5));
		ui->verticalSlider_PADsynth_Harmony_5->blockSignals(false);

		ui->verticalSlider_PADsynth_Harmony_6->blockSignals(true);
		ui->verticalSlider_PADsynth_Harmony_6->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_6));
		ui->verticalSlider_PADsynth_Harmony_6->blockSignals(false);

		ui->verticalSlider_PADsynth_Harmony_7->blockSignals(true);
		ui->verticalSlider_PADsynth_Harmony_7->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_7));
		ui->verticalSlider_PADsynth_Harmony_7->blockSignals(false);

		ui->verticalSlider_PADsynth_Harmony_8->blockSignals(true);
		ui->verticalSlider_PADsynth_Harmony_8->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_8));
		ui->verticalSlider_PADsynth_Harmony_8->blockSignals(false);

		ui->verticalSlider_PADsynth_Harmony_9->blockSignals(true);
		ui->verticalSlider_PADsynth_Harmony_9->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_9));
		ui->verticalSlider_PADsynth_Harmony_9->blockSignals(false);

		ui->verticalSlider_PADsynth_Harmony_10->blockSignals(true);
		ui->verticalSlider_PADsynth_Harmony_10->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_10));
		ui->verticalSlider_PADsynth_Harmony_10->blockSignals(false);

		ui->verticalSlider_PADsynth_HarmonyDetune->blockSignals(true);
		ui->verticalSlider_PADsynth_HarmonyDetune->setValue(mod_synth_get_pad_synth_int_param(_PAD_DETUNE));
		ui->verticalSlider_PADsynth_HarmonyDetune->blockSignals(false);

		ui->spinBox_PADsynth_Harmony_1->blockSignals(true);
		ui->spinBox_PADsynth_Harmony_1->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_1));
		ui->spinBox_PADsynth_Harmony_1->blockSignals(false);

		ui->spinBox_PADsynth_Harmony_2->blockSignals(true);
		ui->spinBox_PADsynth_Harmony_2->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_2));
		ui->spinBox_PADsynth_Harmony_2->blockSignals(false);

		ui->spinBox_PADsynth_Harmony_3->blockSignals(true);
		ui->spinBox_PADsynth_Harmony_3->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_3));
		ui->spinBox_PADsynth_Harmony_3->blockSignals(false);

		ui->spinBox_PADsynth_Harmony_4->blockSignals(true);
		ui->spinBox_PADsynth_Harmony_4->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_4));
		ui->spinBox_PADsynth_Harmony_4->blockSignals(false);

		ui->spinBox_PADsynth_Harmony_5->blockSignals(true);
		ui->spinBox_PADsynth_Harmony_5->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_5));
		ui->spinBox_PADsynth_Harmony_5->blockSignals(false);

		ui->spinBox_PADsynth_Harmony_6->blockSignals(true);
		ui->spinBox_PADsynth_Harmony_6->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_6));
		ui->spinBox_PADsynth_Harmony_6->blockSignals(false);

		ui->spinBox_PADsynth_Harmony_7->blockSignals(true);
		ui->spinBox_PADsynth_Harmony_7->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_7));
		ui->spinBox_PADsynth_Harmony_7->blockSignals(false);

		ui->spinBox_PADsynth_Harmony_8->blockSignals(true);
		ui->spinBox_PADsynth_Harmony_8->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_8));
		ui->spinBox_PADsynth_Harmony_8->blockSignals(false);

		ui->spinBox_PADsynth_Harmony_9->blockSignals(true);
		ui->spinBox_PADsynth_Harmony_9->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_9));
		ui->spinBox_PADsynth_Harmony_9->blockSignals(false);

		ui->spinBox_PADsynth_Harmony_10->blockSignals(true);
		ui->spinBox_PADsynth_Harmony_10->setValue(mod_synth_get_pad_synth_int_param(_PAD_HARMONY_LEVEL_10));
		ui->spinBox_PADsynth_Harmony_10->blockSignals(false);

		ui->spinBox_PADsynth_HarmonyDetune->blockSignals(true);
		ui->spinBox_PADsynth_HarmonyDetune->setValue(mod_synth_get_pad_synth_int_param(_PAD_DETUNE));
		ui->spinBox_PADsynth_HarmonyDetune->blockSignals(false);

		update_spectrum_params = false;
	}

	
	
}

void Dialog_PADsynthesizer::start_update_timer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update_gui()));
	timer->start(interval);
}

void Dialog_PADsynthesizer::set_adsr_plot_widget_points()
{
	const int max_param_value = 100;

	adsr_view_widget_attack = mod_synth_get_pad_synth_active_env_mod_attack();
	adsr_view_widget_decay = mod_synth_get_pad_synth_active_env_mod_decay();
	adsr_view_widget_sustain = mod_synth_get_pad_synth_active_env_mod_sustain();
	adsr_view_widget_release = mod_synth_get_pad_synth_active_env_mod_release();

	adsr_view_widget_attack = mod_synth_log_scale_100_int(0, max_param_value, 10, adsr_view_widget_attack);
	adsr_view_widget_decay = mod_synth_log_scale_100_int(0, max_param_value, 10, adsr_view_widget_decay);
	adsr_view_widget_release = mod_synth_log_scale_100_int(0, max_param_value, 10, adsr_view_widget_release);

	adsr_curve_attack_end_point =
		_ADSR_CURVE_START_POINT + 1 +
		((adsr_view_widget_attack * adsr_curve_max_attack * _ADSR_CURVE_TIME_MULTIPLIER) /
		 max_param_value);

	adsr_curve_decay_end_point =
		adsr_curve_attack_end_point + 1 +
		((adsr_view_widget_decay * adsr_curve_max_decay * _ADSR_CURVE_TIME_MULTIPLIER) /
		 max_param_value);

	adsr_curve_sustain_end_point =
		adsr_curve_decay_end_point + 1 +
		_ADSR_CURVE_SUSTAIN_SEGMENT_LENGTH;

	adsr_curve_release_end_point =
		adsr_curve_sustain_end_point + 1 +
		((adsr_view_widget_release * adsr_curve_max_release *
		  _ADSR_CURVE_TIME_MULTIPLIER) /
		 max_param_value);
}

void Dialog_PADsynthesizer::refresh_adsr_curve_view(QCustomPlot *adsr_plot)
{
	if (adsr_plot != NULL)
	{
		QVector<double> x(8), y(8);

		x[0] = 0;
		y[0] = 0;

		x[1] = _ADSR_CURVE_START_POINT;
		y[1] = 0;

		x[2] = adsr_curve_attack_end_point;
		y[2] = _PAD_ADSR_CURVE_HEIGHT;

		x[3] = adsr_curve_decay_end_point;
		y[3] = adsr_view_widget_sustain * _PAD_ADSR_CURVE_HEIGHT / 100;

		x[4] = adsr_curve_sustain_end_point;
		y[4] = adsr_view_widget_sustain * _PAD_ADSR_CURVE_HEIGHT / 100;

		x[5] = adsr_curve_release_end_point;
		y[5] = 0;

		x[6] = adsr_plot_length;
		y[6] = 0;

		adsr_plot->graph(0)->setData(x, y);
		adsr_plot->xAxis->setRange(0, adsr_plot_length);

		adsr_plot->replot();
	}
}

void Dialog_PADsynthesizer::pad_setup_profile_plot(QCustomPlot *profilePlot)
{
	if (update_profile_plot && mod_synth_get_pad_synth_base_harmony_profile())
	{
		// add two new graphs and set their look:
		QPen pen;
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(3);
		pen.setColor(Qt::white);
		profilePlot->addGraph();
		profilePlot->graph(0)->setPen(pen);
		profilePlot->addGraph();

		profilePlot->setBackground(QBrush(_CONTROLS_COLOR_BLACK));

		//		customPlot->graph(1)->setPen(QPen(Qt::red));  // line color red for second graph
		QVector<double> x(mod_synth_get_pad_synth_base_harmony_profile_size() + 1), 
							y0(mod_synth_get_pad_synth_base_harmony_profile_size() + 1);

		for (int i = 0; i < mod_synth_get_pad_synth_base_harmony_profile_size(); ++i)
		{
			x[i] = i;
			y0[i] = *(mod_synth_get_pad_synth_base_harmony_profile() + i);
		}
		profilePlot->xAxis->setVisible(false);
		profilePlot->xAxis->setTickLabels(false);
		profilePlot->yAxis->setVisible(false);
		profilePlot->yAxis->setTickLabels(false);
		profilePlot->graph(0)->setData(x, y0);
		// let the ranges scale themselves so graph 0 fits perfectly in the visible area:
		profilePlot->graph(0)->rescaleAxes();
	}
}

void Dialog_PADsynthesizer::pad_setup_spectrum_plot(QCustomPlot *spectrumPlot)
{
	const int width = 12;
	float sum;

	if (update_spectrum_plot && (mod_synth_get_pad_synth_spectrum() /*!= NULL*/))
	{
		// add two new graphs and set their look:
		QPen pen;
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(3);
		pen.setColor(Qt::white);
		spectrumPlot->addGraph();
		spectrumPlot->graph(0)->setPen(pen);
		spectrumPlot->addGraph();

		spectrumPlot->setBackground(QBrush(_CONTROLS_COLOR_BLACK));

		int spectrumSize = mod_synth_get_pad_synth_spectrum_size();
		int step = spectrumSize / 1024;
		QVector<double> x(1024), y0(1024);
		for (int i = 0; i < 1024; ++i)
		{
			x[i] = i;
			sum = 0;
			for (int j = -width / 2; j < width / 2 + 1; j++)
			{
				if (((i * step / width + j) >= 0) && ((i * step / width + j) < spectrumSize))
				{
					sum += *(mod_synth_get_pad_synth_spectrum() + i * step / width + j);
				}
			}
			y0[i] = sum / width;
			//			y0[i] = *(mod_synth_get_pad_spectrum() + i * step / width );   //  /2 no such high freq
		}
		spectrumPlot->xAxis->setVisible(false);
		spectrumPlot->xAxis->setTickLabels(false);
		spectrumPlot->yAxis->setVisible(false);
		spectrumPlot->yAxis->setTickLabels(false);
		spectrumPlot->graph(0)->setData(x, y0);
		// let the ranges scale themselves so graph 0 fits perfectly in the visible area:
		spectrumPlot->graph(0)->rescaleAxes();
	}
}

void Dialog_PADsynthesizer::pad_replot_profile()
{
	mod_synth_pad_synth_event_int(_PAD_1_EVENT, _PAD_GENERATE, 1);
	pad_setup_profile_plot(ui->widget_PadPlotProfile);
	ui->widget_PadPlotProfile->replot();

	update_spectrum_params = true;
}

void Dialog_PADsynthesizer::pad_replot_spectrum()
{
	pad_setup_spectrum_plot(ui->widget_PADsynthPlotSpectrum);
	ui->widget_PADsynthPlotSpectrum->replot();
}

