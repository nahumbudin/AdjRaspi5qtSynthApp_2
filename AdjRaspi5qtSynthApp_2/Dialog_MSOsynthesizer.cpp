/**
 * @file		Dialog_MSOsynthesizer.cpp
 *	@author		Nahum Budin
 *	@date		29-May-2026
 *	@version	1.0
 *
 *	Note - PWM or Symmetry Modulation is not implemented in the current version.
 *
 *	@brief		Adj MSO Synthesizer control dialog
 *
 */

#include <filesystem>

#include "Dialog_MSOsynthesizer.h"
#include "ui_Dialog_MSOsynthesizer.h"

#include "MainWindow.h"

#include "CustomFileDialog.h"

#define _UPDATE_TIMER_PERIOD_MS 250

Dialog_MSOsynthesizer *Dialog_MSOsynthesizer::dialog_msosynthesizer_instance = NULL;

LoadMSOSynthesizerPresetFileThread *load_mso_synthesizer_preset_file_thread = nullptr;
;
SaveMSOSynthesizerPresetFileThread *save_mso_synthesizer_preset_file_thread = nullptr;

QString mso_synthesizer_preset_file_name = "";

// MSO Sine-wave preset positions
static const int preset_sinus[] = {512, 517, 1024, 1029, 1536, 1542};
// Symetric square-wave preset positions
static const int preset_squar[] = {1, 1011, 1016, 1021, 1026, 2046};
// Symetric square-wave preset positions
static const int preset_pulse[] = {1, 200, 205, 210, 215, 2046};
// Sawtooth-wave preset positions
static const int preset_saw[] = {1, 7, 1024, 1029, 2041, 2046};

void mso_synthesizer_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	Dialog_MSOsynthesizer *instance = Dialog_MSOsynthesizer::get_instance();
	if (instance != nullptr)
	{
		instance->control_box_event_received(evnt, val);
	}
}

void SaveMSOSynthesizerPresetFileThread::run()
{
	int res;

	QString result = QString("Preset File Saved");
	res = mod_synth_save_mso_synthesizer_preset_file(mso_synthesizer_preset_file_name.toStdString());

	emit savePresetFileDone(result);
}

void LoadMSOSynthesizerPresetFileThread::run()
{
	int res;

	QString result = QString("Preset File Loaded");
	res = mod_synth_load_mso_synthesizer_preset_file(mso_synthesizer_preset_file_name.toStdString());

	emit loadPresetFileDone(result);
}

Dialog_MSOsynthesizer::Dialog_MSOsynthesizer(QWidget *parent)
	: QDialog(parent), ui(new Ui::Dialog_MSOsynthesizer)
{
	ui->setupUi(this);
	dialog_msosynthesizer_instance = this;

	// Prevent dialog from being deleted when closed - only hide it
	setAttribute(Qt::WA_DeleteOnClose, false);

	close_event_callback_ptr = NULL;

	// Connect signal to slot with Qt::QueuedConnection for thread-safety
	// This ensures the slot runs in the GUI thread
	connect(this, &Dialog_MSOsynthesizer::control_box_event_signal,
			this, &Dialog_MSOsynthesizer::handle_control_box_event,
			Qt::QueuedConnection);

	// Register control box event callback
	mod_synth_register_callback_control_box_event_update_ui(
		&mso_synthesizer_control_box_event_update_ui_callback_wrapper);

	init_gui_elements();

	// Define frames for the single "tab" (tab 0)
	QMap<int, QList<QString>> frames_per_tab;

	// All frames go under tab index 0
	frames_per_tab[0] << "Signal" << "Modulators" << "Filter";

	// Register dialog WITHOUT a tab widget (nullptr)
	GuiNavigator *nav = GuiNavigator::get_instance();
	
	nav->register_dialog(
		this,
		"MSO Synthesizer",
		nullptr, // No tab widget
		frames_per_tab);

	nav->set_gray_frame_widgets(this, 0, 0, // tab_index = 0, frame_index = 0
								ui->frame_MsoSendFiltersTuneOffset,
								ui->frame_MSOsynth_Presetes,
								nullptr,
								nullptr);

	nav->set_white_frame_widgets(this, 0, 0, // tab_index = 0, frame_index = 0
								 ui->frame_MsoSegments,
								 nullptr,
								 nullptr,
								 nullptr);

	nav->set_gray_frame_widgets(this, 0, 1, // tab_index = 0, frame_index = 1 :
								ui->frame_MSOsynth_AmplitudeModulation,
								nullptr,
								nullptr,
								nullptr);

	nav->set_white_frame_widgets(this, 0, 1, // tab_index = 0, frame_index = 1
								 ui->frame_MSOsynth_FreqModulation,
								 nullptr,
								 nullptr,
								 nullptr);

	nav->set_gray_frame_widgets(this, 0, 2, // tab_index = 0, frame_index = 1 :
								ui->frame_MSOsynthFilter,
								nullptr,
								nullptr,
								nullptr);

	nav->set_white_frame_widgets(this, 0, 2, // tab_index = 0, frame_index = 1
								 ui->frame_MSOsynth_FilterFreqModulation,
								 nullptr,
								 nullptr,
								 nullptr);

	// Highlight the first frame
	nav->refresh_current_highlight();

	// Also register with MainWindow for compatibility
	MainWindow::get_instance()->register_active_dialog(this);

	// GUI Update timer start
	start_update_timer(_UPDATE_TIMER_PERIOD_MS);

	/* Set focus on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

Dialog_MSOsynthesizer::~Dialog_MSOsynthesizer()
{
	// Disable callback during destruction
	mod_synth_register_callback_control_box_event_update_ui(NULL);

	// Reset static instance pointer when destroyed
	dialog_msosynthesizer_instance = nullptr;
	delete ui;
}

Dialog_MSOsynthesizer *Dialog_MSOsynthesizer::get_instance(QWidget *parent)
{
	if (dialog_msosynthesizer_instance == NULL)
	{
		dialog_msosynthesizer_instance = new Dialog_MSOsynthesizer(parent);
	}
	return dialog_msosynthesizer_instance;
}

// Thread-safe function called from callback - just emits signal
void Dialog_MSOsynthesizer::control_box_event_received(int evnt, uint16_t val)
{
	// Emit signal - Qt will queue it to run in GUI thread
	emit control_box_event_signal(evnt, val);
}



void Dialog_MSOsynthesizer::set_signal_slots_connections()
{
	connect(ui->dial_MsoSynthSendFilter,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_send_filter_dial_changed(int)));

	connect(ui->comboBox_MsoSynthTuneOctave,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_detune_octave_combobox_changed(int)));

	connect(ui->comboBox_MsoSynthTuneSemitones,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_detune_semitones_combobox_changed(int)));

	connect(ui->comboBox_MsoSynthTuneCents,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_detune_cents_combobox_changed(int)));

	connect(ui->comboBox_MsoSynthPreset,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_preset_combobox_changed(int)));

	connect(ui->pushButton_MSOsynth_PresetOpen,
			SIGNAL(clicked()),
			this,
			SLOT(on_presets_open_pushbutton_clicked()));

	connect(ui->dial_MSOsynth_AmpModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_amp_mod_env_level_dial_changed(int)));

	connect(ui->verticalSlider_MSOsynth_AmpModAdsrA,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_amp_env_attack_slider_changed(int)));

	connect(ui->verticalSlider_MSOsynth_AmpModAdsrD,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_amp_env_decay_slider_changed(int)));

	connect(ui->verticalSlider_MSOsynth_AmpModAdsrS,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_amp_env_sustain_slider_changed(int)));

	connect(ui->verticalSlider_MSOsynth_AmpModAdsrR,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_amp_env_release_slider_changed(int)));

	connect(ui->dial_MSOsynth_AmpModLFOLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_amp_mod_lfo_level_dial_changed(int)));

	connect(ui->dial_MSOsynth_AmpModLFOrate,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_amp_mod_lfo_rate_dial_changed(int)));

	connect(ui->dial_MSOsynth_AmpModLFOsymmetry,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_amp_mod_lfo_symmetry_dial_changed(int)));

	connect(ui->comboBox_MSOsynth_AmpModLFOwaveform,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_amp_mod_lfo_waveform_combobox_changed(int)));

	/*
	connect(ui->dial_MSOsynth_PwmModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_sym_mod_env_level_dial_changed(int)));

	connect(ui->verticalSlider_MSOsynth_PwmModAdsrA,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_sym_env_attack_slider_changed(int)));

	connect(ui->verticalSlider_MSOsynth_PwmModAdsrD,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_sym_env_decay_slider_changed(int)));

	connect(ui->verticalSlider_MSOsynth_PwmModAdsrS,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_sym_env_sustain_slider_changed(int)));

	connect(ui->verticalSlider_MSOsynth_PwmModAdsrR,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_sym_env_release_slider_changed(int)));

	connect(ui->dial_MSOsynth_PwmModLFOLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_sym_mod_lfo_level_dial_changed(int)));

	connect(ui->dial_MSOsynth_PwmModLFOrate,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_sym_mod_lfo_rate_dial_changed(int)));

	connect(ui->dial_MSOsynth_PwmModLFOsymmetry,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_sym_mod_lfo_symmetry_dial_changed(int)));

	connect(ui->comboBox_MSOsynth_PwmModLFOwaveform,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_sym_mod_lfo_waveform_combobox_changed(int)));
*/

	connect(ui->dial_MSOsynth_FreqModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_freq_mod_env_level_dial_changed(int)));

	connect(ui->verticalSlider_MSOsynth_FreqModAdsrA,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_freq_env_attack_slider_changed(int)));

	connect(ui->verticalSlider_MSOsynth_FreqModAdsrD,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_freq_env_decay_slider_changed(int)));

	connect(ui->verticalSlider_MSOsynth_FreqModAdsrS,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_freq_env_sustain_slider_changed(int)));

	connect(ui->verticalSlider_MSOsynth_FreqModAdsrR,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_freq_env_release_slider_changed(int)));

	connect(ui->dial_MSOsynth_FreqModLFOLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_freq_mod_lfo_level_dial_changed(int)));

	connect(ui->dial_MSOsynth_FreqModLFOrate,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_freq_mod_lfo_rate_dial_changed(int)));

	connect(ui->dial_MSOsynth_FreqModLFOsymmetry,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_freq_mod_lfo_symmetry_dial_changed(int)));

	connect(ui->comboBox_MSOsynth_FreqModLFOwaveform,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_freq_mod_lfo_waveform_combobox_changed(int)));

	connect(ui->verticalSlider_MSOSynth_Pos_a,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_point_a_slider_moved(int)));

	connect(ui->verticalSlider_MSOSynth_Pos_b,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_point_b_slider_moved(int)));

	connect(ui->verticalSlider_MSOSynth_Pos_c,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_point_c_slider_moved(int)));

	connect(ui->verticalSlider_MSOSynth_Pos_d,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_point_d_slider_moved(int)));

	connect(ui->verticalSlider_MSOSynth_Pos_e,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_point_e_slider_moved(int)));

	connect(ui->verticalSlider_MSOSynth_Pos_f,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_point_f_slider_moved(int)));

	connect(ui->horizontalSlider_MsoSynthMorph,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_symetry_slider_changed(int)));

	connect(ui->pushButton_MSOsynth_PresetSave,
			SIGNAL(clicked()),
			this,
			SLOT(on_presets_save_pushbutton_clicked()));

	connect(ui->dial_MsoSynthFilterFreq,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter_freq_dial_changed(int)));

	connect(ui->dial_MsoSynthFilterKbdTrack,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter_kbd_track_dial_changed(int)));

	connect(ui->dial_MsoSynthFilterQ,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter_q_dial_changed(int)));

	connect(ui->dial_MsoSynthFilterOctave,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter_octave_dial_changed(int)));
	
	connect(ui->comboBox_MsoSynthTuneOctave,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_filter_octave_dial_changed(int)));

	connect(ui->comboBox_MsoSynthFilterBand,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_filter_band_combo_hanged(int)));

	connect(ui->dial_MSOsynth_FilterFreqModAdsrLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter_freq_mod_env_level_dial_changed(int)));

	connect(ui->verticalSlider_MSOsynth_FilterFreqModAdsrA,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter_freq_mod_env_attack_slider_changed(int)));

	connect(ui->verticalSlider_MSOsynth_FilterFreqModAdsrD,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter_freq_mod_env_decay_slider_changed(int)));

	connect(ui->verticalSlider_MSOsynth_FilterFreqModAdsrS,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter_freq_mod_env_sustain_slider_changed(int)));

	connect(ui->verticalSlider_MSOsynth_FilterFreqModAdsrR,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter_freq_mod_env_release_slider_changed(int)));

	connect(ui->dial_MSOsynth_FilterFreqModLFOLevel,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter_freq_mod_level_lfo_dial_changed(int)));

	connect(ui->dial_MSOsynth_FilterFreqModLFOrate,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter_freq_mod_lfo_rate_dial_changed(int)));

	connect(ui->dial_MSOsynth_FilterFreqModLFOsymmetry,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_filter_freq_mod_lfo_symmetry_dial_changed(int)));

	connect(ui->comboBox_MSOsynth_FilterFreqModLFOwaveform,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_filter_freq_mod_lfo_waveform_combobox_changed(int)));
}

void Dialog_MSOsynthesizer::set_preset_positions(const int pos[])
{
	// Put all points to their max value to enable any setup
	update_mso_synth_waveform_plot = false;
	
	on_point_f_slider_moved(2035);
	on_point_e_slider_moved(2033);
	on_point_d_slider_moved(2031);
	on_point_c_slider_moved(2029);
	on_point_b_slider_moved(2027);
	on_point_a_slider_moved(2025);

	on_point_a_slider_moved(pos[0]);
	on_point_b_slider_moved(pos[1]);
	on_point_c_slider_moved(pos[2]);
	on_point_d_slider_moved(pos[3]);
	on_point_e_slider_moved(pos[4]);
	on_point_f_slider_moved(pos[5]);

	update_mso_synth_waveform_plot = true;
	
	on_symetry_slider_changed(70);

	ui->verticalSlider_MSOSynth_Pos_a->blockSignals(true);
	ui->verticalSlider_MSOSynth_Pos_a->setValue(pos[0]);
	ui->verticalSlider_MSOSynth_Pos_a->blockSignals(false);

	ui->verticalSlider_MSOSynth_Pos_b->blockSignals(true);
	ui->verticalSlider_MSOSynth_Pos_b->setValue(pos[1]);
	ui->verticalSlider_MSOSynth_Pos_b->blockSignals(false);

	ui->verticalSlider_MSOSynth_Pos_c->blockSignals(true);
	ui->verticalSlider_MSOSynth_Pos_c->setValue(pos[2]);
	ui->verticalSlider_MSOSynth_Pos_c->blockSignals(false);

	ui->verticalSlider_MSOSynth_Pos_d->blockSignals(true);
	ui->verticalSlider_MSOSynth_Pos_d->setValue(pos[3]);
	ui->verticalSlider_MSOSynth_Pos_d->blockSignals(false);

	ui->verticalSlider_MSOSynth_Pos_e->blockSignals(true);
	ui->verticalSlider_MSOSynth_Pos_e->setValue(pos[4]);
	ui->verticalSlider_MSOSynth_Pos_e->blockSignals(false);

	ui->verticalSlider_MSOSynth_Pos_f->blockSignals(true);
	ui->verticalSlider_MSOSynth_Pos_f->setValue(pos[5]);
	ui->verticalSlider_MSOSynth_Pos_f->blockSignals(false);

	ui->horizontalSlider_MsoSynthMorph->blockSignals(true);
	ui->horizontalSlider_MsoSynthMorph->setValue(70);
	ui->horizontalSlider_MsoSynthMorph->blockSignals(false);
}

void Dialog_MSOsynthesizer::handle_preset_change(int newPres)
{
	switch (newPres)
	{
	case 0:
		set_preset_positions(preset_sinus);
		break;

	case 1:
		set_preset_positions(preset_squar);
		break;

	case 2:
		set_preset_positions(preset_pulse);
		break;

	case 3:
		set_preset_positions(preset_saw);
		break;

	default:
		set_preset_positions(preset_sinus);
		break;
	}
}

void Dialog_MSOsynthesizer::setup_plot(QCustomPlot *custom_plot)
{
	if (update_mso_synth_waveform_plot && mod_synth_get_mso_synth_morphed_lookup_table())
	{
		mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_CALC_BASE_LUT, _MSO_SYNTH_PROGRAM_23);
		// Recalculates morphed waveform.
		mod_synth_mso_synth_event_int(_MSO_SYNTH_EVENT, _MSO_CALC_MORPHED_LUT, _MSO_SYNTH_PROGRAM_23);

		// add two(?) new graphs and set their look:
		QPen pen;
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(3);
		pen.setColor(Qt::white);
		custom_plot->addGraph();
		custom_plot->graph(0)->setPen(pen); // line color blue for first graph
											//		custom_plot->addGraph();
											//		custom_plot->graph(1)->setPen(QPen(Qt::red));   // line color red for second graph

		custom_plot->setBackground(QBrush(_CONTROLS_COLOR_BLACK));

		QVector<double> x(mod_synth_get_mso_table_length() + 1), y0(mod_synth_get_mso_table_length() + 1);

		for (int i = 0; i < mod_synth_get_mso_table_length() / 4; ++i)
		{
			x[i] = i;
			y0[i] = mod_synth_get_mso_synth_morphed_lookup_table()[i * 4]; // Table length is getMsoTableLength * 4
																	 //	y1[i] = 52.f + 47.f*qCos(2 * 3.14 * i / 256);
		}
		// x[256] = 257; y0[256] = -2; y1[256] = -2;
		custom_plot->xAxis->setVisible(false);
		custom_plot->xAxis->setTickLabels(false);
		custom_plot->yAxis->setVisible(false);
		custom_plot->yAxis->setTickLabels(false);
		// make left and bottom axes always transfer their ranges to right and top axes:
		// connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
		// connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
		// pass data points to graphs:
		custom_plot->graph(0)->setData(x, y0);
		// let the ranges scale themselves so graph 0 fits perfectly in the visible area:
		custom_plot->graph(0)->rescaleAxes();
	}
}
void Dialog_MSOsynthesizer::update_waveform_plot()
{
	setup_plot(ui->widget_MsoSynthWaveformPlot);
	ui->widget_MsoSynthWaveformPlot->replot();
}

void Dialog_MSOsynthesizer::closeEvent(QCloseEvent *event)
{
	if (close_event_callback_ptr != NULL)
	{
		close_event_callback_ptr();
	}

	// Disable callback when hiding
	mod_synth_register_callback_control_box_event_update_ui(NULL);

	// Unregister from GuiNavigator
	GuiNavigator::get_instance()->unregister_dialog(this);

	// Hide instead of accept (which could trigger deletion)
	event->ignore(); // Don't accept the close event

	hide();
}

void Dialog_MSOsynthesizer::showEvent(QShowEvent *event)
{
	QDialog::showEvent(event);

	// Re-register callback when showing
	mod_synth_register_callback_control_box_event_update_ui(
		&mso_synthesizer_control_box_event_update_ui_callback_wrapper);
}

void Dialog_MSOsynthesizer::on_dialog_close()
{
	close();
}

void Dialog_MSOsynthesizer::on_presets_open_pushbutton_clicked()
{
	QString startDir = last_mso_synth_preset_directory.isEmpty() ? QString(_MSO_SYNTH_PRESETS_FILES_DEFAULT_DIR) : last_mso_synth_preset_directory;

	CustomFileDialog dialog(this,
							tr("Open Preset File"),
							startDir,
							tr("Presets (*.xml *.XML);;All Files (*)"),
							Qt::black); // Background color set here)

	// If we have a last file, select it and scroll to it
	if (!last_mso_synth_preset_load_file.isEmpty())
	{
		dialog.selectFile(last_mso_synth_preset_load_file);
	}

	if (dialog.exec() == QDialog::Accepted)
	{
		mso_synthesizer_preset_file_name = dialog.selectedFile();

		if (!mso_synthesizer_preset_file_name.isEmpty())
		{
			// Remember the directory and file for next time
			last_mso_synth_preset_directory = QFileInfo(mso_synthesizer_preset_file_name).absolutePath();
			last_mso_synth_preset_load_file = mso_synthesizer_preset_file_name;

			std::string file_name;
			// file_name = std::string("Now Loading: ");
			file_name = std::filesystem::path(mso_synthesizer_preset_file_name.toStdString()).stem();

			ui->textEdit_MSOsynth_PresetText->setText(QString::fromStdString(file_name));

			MainWindow *mainWin = MainWindow::get_instance();
			if (mainWin)
			{
				InstrumentPannel *panel =
					mainWin->get_instrument_panel_by_id(en_instruments_ids_t::adj_mso_synth);
				if (panel)
				{
					panel->set_preset_text(QString::fromStdString(file_name));
				}
			}

			// Check if thread is still running - prevent creating duplicate threads
			if (load_mso_synthesizer_preset_file_thread != nullptr &&
				!load_mso_synthesizer_preset_file_thread->isFinished())
			{
				// Thread still running, ignore this request or wait
				return;
			}

			load_mso_synthesizer_preset_file_thread = new LoadMSOSynthesizerPresetFileThread();
			connect(load_mso_synthesizer_preset_file_thread,
					&LoadMSOSynthesizerPresetFileThread::finished,
					this,
					[=]() {
						load_mso_synthesizer_preset_file_thread->deleteLater();
						load_mso_synthesizer_preset_file_thread = nullptr; // Reset to nullptr after deletion
					});
			connect(load_mso_synthesizer_preset_file_thread,
					&LoadMSOSynthesizerPresetFileThread::loadPresetFileDone,
					this,
					&Dialog_MSOsynthesizer::on_preset_file_loaded);
			load_mso_synthesizer_preset_file_thread->start();
		}
	}
}

void Dialog_MSOsynthesizer::on_presets_save_pushbutton_clicked()
{
	QString startDir = last_mso_synth_preset_directory.isEmpty() ? QString(_MSO_SYNTH_PRESETS_FILES_DEFAULT_DIR) : last_mso_synth_preset_directory;

	// Use CustomFileDialog in Save mode
	CustomFileDialog dialog(this,
							tr("Save Preset File"),
							startDir,
							tr("Presets (*.xml *.XML);;All Files (*)"),
							Qt::black,
							CustomFileDialog::SaveMode); // Set to Save mode

	if (dialog.exec() == QDialog::Accepted)
	{
		mso_synthesizer_preset_file_name = dialog.selectedFile();

		if (!mso_synthesizer_preset_file_name.isEmpty())
		{
			// Ensure .xml extension
			if (!mso_synthesizer_preset_file_name.endsWith(".xml", Qt::CaseInsensitive))
			{
				mso_synthesizer_preset_file_name += ".xml";
			}

			// Check if file exists and ask for confirmation
			if (QFile::exists(mso_synthesizer_preset_file_name))
			{
				QMessageBox msgBox;
				msgBox.setIcon(QMessageBox::Warning);
				msgBox.setWindowTitle("Confirm Overwrite");
				msgBox.setText(QString("File '%1' already exists.")
								   .arg(QFileInfo(mso_synthesizer_preset_file_name).fileName()));
				msgBox.setInformativeText("Do you want to overwrite it?");
				msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
				msgBox.setDefaultButton(QMessageBox::Cancel);

				if (msgBox.exec() != QMessageBox::Yes)
				{
					return;
				}
			}

			// Remember the directory and file for next time
			last_mso_synth_preset_directory = QFileInfo(mso_synthesizer_preset_file_name).absolutePath();
			last_mso_synth_preset_save_file = mso_synthesizer_preset_file_name	;

			// Display saving message
			std::string file_name = std::string("Now Saving: ");
			file_name += std::filesystem::path(mso_synthesizer_preset_file_name.toStdString()).stem().string();
			// ui->textEdit_HammondPresetText->setText(QString::fromStdString(file_name));

			// Check if thread is still running
			if (save_mso_synthesizer_preset_file_thread != nullptr &&
				!save_mso_synthesizer_preset_file_thread->isFinished())
			{
				return;
			}

			// Start the save thread
			save_mso_synthesizer_preset_file_thread = new SaveMSOSynthesizerPresetFileThread();

			connect(save_mso_synthesizer_preset_file_thread,
					&SaveMSOSynthesizerPresetFileThread::finished,
					this,
					[=]() {
						save_mso_synthesizer_preset_file_thread->deleteLater();
						save_mso_synthesizer_preset_file_thread = nullptr; // Reset to nullptr after deletion
					});
			connect(save_mso_synthesizer_preset_file_thread,
					&SaveMSOSynthesizerPresetFileThread::savePresetFileDone,
					this,
					&Dialog_MSOsynthesizer::on_preset_file_saved);

			save_mso_synthesizer_preset_file_thread->start();
		}
	}
}

void Dialog_MSOsynthesizer::on_preset_file_loaded(const QString &s)
{
	update_amp_mod_adsr_plot.store(true);
	update_freq_mod_adsr_plot.store(true);
	//update_sym_mod_adsr_plot.store(true);
	update_filter_freq_mod_adsr_plot.store(true);

	replot_waveform.store(true);
}

void Dialog_MSOsynthesizer::on_preset_file_saved(const QString &s)
{
}



void Dialog_MSOsynthesizer::start_update_timer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update_gui()));
	timer->start(interval);
}
