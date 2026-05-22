/**
 * @file		Dialog_AnalogSynth_1900x1000.cpp
 *	@author		Nahum Budin
 *	@date		22-Dec-2025
 *	@version	1.0
 *					1. First version.
 *
 *	@brief		Used for controling the Analog Synthesizer instrument
 *				A single integrated 1900x1000 dialog version for large screen devices.
 *
 *	History:
 *			Based on the AdjModSynth project ver 1.1 16-Jan-2021
 *
 */

#include <QTimer>
#include <QThread>

#include "Dialog_AnalogSynth_1900x1000.h"
#include "ui_Dialog_AnalogSynth_1900x1000.h"
#include "Defs.h"
#include "MainWindow.h"

#define _UPDATE_TIMER_PERIOD_MS 100

Dialog_AnalogSynth_1900x1000 *Dialog_AnalogSynth_1900x1000::dialog_analog_synth_instance = NULL;

CustomComboBox *Dialog_AnalogSynth_1900x1000::combo_lfo_waveform[_NUM_OF_LFOS];
CustomDial *Dialog_AnalogSynth_1900x1000::dial_lfo_symmetry[_NUM_OF_LFOS];
CustomDial *Dialog_AnalogSynth_1900x1000::dial_lfo_rate[_NUM_OF_LFOS];
QLineEdit *Dialog_AnalogSynth_1900x1000::lineedit_lfo_rate[_NUM_OF_LFOS];
QLineEdit *Dialog_AnalogSynth_1900x1000::lineedit_lfo_symmetry[_NUM_OF_LFOS];

void analog_synth_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	// Just forward to the dialog instance - it will emit a signal
	Dialog_AnalogSynth_1900x1000::get_instance()->control_box_event_received(evnt, val);
}

Dialog_AnalogSynth_1900x1000::Dialog_AnalogSynth_1900x1000(QWidget *parent)
	: QDialog(parent), ui(new Ui::Dialog_AnalogSynth_1900x1000)
{
	int result;

	ui->setupUi(this);
	dialog_analog_synth_instance = this;

	this->setFocus(Qt::ActiveWindowFocusReason);

	// Set tab name font size, color, and padding to prevent text cropping
	ui->tabWidget_AnalogSynth->setStyleSheet(
		"QTabBar::tab {"
		"    font-size: 15pt;"
		"    color: white;"		  // Font color white
		"    padding: 5px 10px;" // Vertical and horizontal padding (larger tabs)
		"    min-width: 150px;"	  // Minimum tab width
		"    min-height: 30px;"	  // Minimum tab height
		"}"
		"QTabBar::tab:selected {"
		"    color: yellow;"		// Selected tab font color
		"    font-weight: bold;" // Make selected tab bold (optional)
		"}"
		"QTabBar::tab:!selected {"
		"    color: #CCCCCC;" // Unselected tab slightly dimmed (optional)
		"}");

	// Set the Modulators Tab Pgae size
	QWidget *tabPage = ui->tabWidget_AnalogSynth->widget(2);
	if (tabPage)
	{
		tabPage->setFixedSize(1400, 800); 
	}

	active_tab = _ANALOG_SOURCES_TAB;
	prev_active_tab = -1;

	// Controls the active remote control colors
	control_widgets_color_manager = new (ControlWidgetsColorManager);

	set_analog_synth_general_signals_connections();

	// Set OSC1 and OSC2 Waveforms Strings for combobboxes
	if (string_waveforms_list.size() == 0)
	{
		/* Do only once for Osc1 and 2*/
		string_waveforms_list.append("Sine");
		string_waveforms_list.append("Square");
		string_waveforms_list.append("Pulse");
		string_waveforms_list.append("Triangle");
		string_waveforms_list.append("Samp&Hold");
	}

	if (string_adsr_values.size() == 0)
	{
		/* Do only once for Osc1 and Osc2 */
		string_adsr_values.append("---");
		string_adsr_values.append("1");
		string_adsr_values.append("2");
		string_adsr_values.append("3");
		string_adsr_values.append("4");
		string_adsr_values.append("5");
		string_adsr_values.append("6");
	}
	
	// LFOs selection strings
	if (string_lfo_values.size() == 0)
	{
		string_lfo_values.append("---");
		string_lfo_values.append("1");
		string_lfo_values.append("2");
		string_lfo_values.append("3");
		string_lfo_values.append("4");
		string_lfo_values.append("5");
		string_lfo_values.append("6");
		string_lfo_values.append("1 0.5s");
		string_lfo_values.append("2 0.5s");
		string_lfo_values.append("3 0.5s");
		string_lfo_values.append("4 0.5s");
		string_lfo_values.append("5 0.5s");
		string_lfo_values.append("6 0.5s");
		string_lfo_values.append("1 1.0s");
		string_lfo_values.append("2 1.0s");
		string_lfo_values.append("3 1.0s");
		string_lfo_values.append("4 1.0s");
		string_lfo_values.append("5 1.0s");
		string_lfo_values.append("6 1.0s");
		string_lfo_values.append("1 1.5s");
		string_lfo_values.append("2 1.5s");
		string_lfo_values.append("3 1.5s");
		string_lfo_values.append("4 1.5s");
		string_lfo_values.append("5 1.5s");
		string_lfo_values.append("6 1.5s");
		string_lfo_values.append("1 2.0s");
		string_lfo_values.append("2 2.0s");
		string_lfo_values.append("3 2.0s");
		string_lfo_values.append("4 2.0s");
		string_lfo_values.append("5 2.0s");
		string_lfo_values.append("6 2.0s");
	}

	// OSC1 Unison Mode strings
	if (string_unison_modes_list.size() == 0)
	{
		string_unison_modes_list.append("Harmonized");
		string_unison_modes_list.append("Hammond");
		string_unison_modes_list.append("Octaves");
		string_unison_modes_list.append("C Chord");
		string_unison_modes_list.append("Cm Chord");
		string_unison_modes_list.append("C7 Chord");
		string_unison_modes_list.append("Cm7 Chord");
	}

	// OSC1 Hammond mode percusion modes strings
	if (string_hammond_modes_list.size() == 0)
	{
		string_hammond_modes_list.append("Percusion OFF");
		string_hammond_modes_list.append("Percusion 2nd Soft Slow");
		string_hammond_modes_list.append("Percusion 2nd Soft Fast");
		string_hammond_modes_list.append("Percusion 2nd Norm Slow");
		string_hammond_modes_list.append("Percusion 2nd Norm Fast");
		string_hammond_modes_list.append("Percusion 3rd Soft Slow");
		string_hammond_modes_list.append("Percusion 3rd Soft Fast");
		string_hammond_modes_list.append("Percusion 3rd Norm Slow");
		string_hammond_modes_list.append("Percusion 3rd Norm Fast");
	}

	// Arrays of the ADSRs vertical sliders to enable computed properties update
	vertical_sliders_adsr_attack[0] = ui->verticalSlider_AdsrA_1;
	vertical_sliders_adsr_attack[1] = ui->verticalSlider_AdsrA_2;
	vertical_sliders_adsr_attack[2] = ui->verticalSlider_AdsrA_3;
	vertical_sliders_adsr_attack[3] = ui->verticalSlider_AdsrA_4;
	vertical_sliders_adsr_attack[4] = ui->verticalSlider_AdsrA_5;
	vertical_sliders_adsr_attack[5] = ui->verticalSlider_AdsrA_6;

	vertical_sliders_adsr_decay[0] = ui->verticalSlider_AdsrD_1;
	vertical_sliders_adsr_decay[1] = ui->verticalSlider_AdsrD_2;
	vertical_sliders_adsr_decay[2] = ui->verticalSlider_AdsrD_3;
	vertical_sliders_adsr_decay[3] = ui->verticalSlider_AdsrD_4;
	vertical_sliders_adsr_decay[4] = ui->verticalSlider_AdsrD_5;
	vertical_sliders_adsr_decay[5] = ui->verticalSlider_AdsrD_6;

	vertical_sliders_adsr_sustain[0] = ui->verticalSlider_AdsrS_1;
	vertical_sliders_adsr_sustain[1] = ui->verticalSlider_AdsrS_2;
	vertical_sliders_adsr_sustain[2] = ui->verticalSlider_AdsrS_3;
	vertical_sliders_adsr_sustain[3] = ui->verticalSlider_AdsrS_4;
	vertical_sliders_adsr_sustain[4] = ui->verticalSlider_AdsrS_5;
	vertical_sliders_adsr_sustain[5] = ui->verticalSlider_AdsrS_6;

	vertical_sliders_adsr_release[0] = ui->verticalSlider_AdsrR_1;
	vertical_sliders_adsr_release[1] = ui->verticalSlider_AdsrR_2;
	vertical_sliders_adsr_release[2] = ui->verticalSlider_AdsrR_3;
	vertical_sliders_adsr_release[3] = ui->verticalSlider_AdsrR_4;
	vertical_sliders_adsr_release[4] = ui->verticalSlider_AdsrR_5;
	vertical_sliders_adsr_release[5] = ui->verticalSlider_AdsrR_6;

	lineedits_adsr_attack[0] = ui->lineEdit_AdsrA_1;
	lineedits_adsr_attack[1] = ui->lineEdit_AdsrA_2;
	lineedits_adsr_attack[2] = ui->lineEdit_AdsrA_3;
	lineedits_adsr_attack[3] = ui->lineEdit_AdsrA_4;
	lineedits_adsr_attack[4] = ui->lineEdit_AdsrA_5;
	lineedits_adsr_attack[5] = ui->lineEdit_AdsrA_6;

	lineedits_adsr_decay[0] = ui->lineEdit_AdsrD_1;
	lineedits_adsr_decay[1] = ui->lineEdit_AdsrD_2;
	lineedits_adsr_decay[2] = ui->lineEdit_AdsrD_3;
	lineedits_adsr_decay[3] = ui->lineEdit_AdsrD_4;
	lineedits_adsr_decay[4] = ui->lineEdit_AdsrD_5;
	lineedits_adsr_decay[5] = ui->lineEdit_AdsrD_6;

	lineedits_adsr_sustain[0] = ui->lineEdit_AdsrS_1;
	lineedits_adsr_sustain[1] = ui->lineEdit_AdsrS_2;
	lineedits_adsr_sustain[2] = ui->lineEdit_AdsrS_3;
	lineedits_adsr_sustain[3] = ui->lineEdit_AdsrS_4;
	lineedits_adsr_sustain[4] = ui->lineEdit_AdsrS_5;
	lineedits_adsr_sustain[5] = ui->lineEdit_AdsrS_6;

	lineedits_adsr_release[0] = ui->lineEdit_AdsrR_1;
	lineedits_adsr_release[1] = ui->lineEdit_AdsrR_2;
	lineedits_adsr_release[2] = ui->lineEdit_AdsrR_3;
	lineedits_adsr_release[3] = ui->lineEdit_AdsrR_4;
	lineedits_adsr_release[4] = ui->lineEdit_AdsrR_5;
	lineedits_adsr_release[5] = ui->lineEdit_AdsrR_6;

	// Same as above for LFOs
	dial_lfo_rate[0] = ui->dial_LFOrate_1;
	dial_lfo_rate[1] = ui->dial_LFOrate_2;
	dial_lfo_rate[2] = ui->dial_LFOrate_3;
	dial_lfo_rate[3] = ui->dial_LFOrate_4;
	dial_lfo_rate[4] = ui->dial_LFOrate_5;
	dial_lfo_rate[5] = ui->dial_LFOrate_6;

	dial_lfo_symmetry[0] = ui->dial_LFOsymmetry_1;
	dial_lfo_symmetry[1] = ui->dial_LFOsymmetry_2;
	dial_lfo_symmetry[2] = ui->dial_LFOsymmetry_3;
	dial_lfo_symmetry[3] = ui->dial_LFOsymmetry_4;
	dial_lfo_symmetry[4] = ui->dial_LFOsymmetry_5;
	dial_lfo_symmetry[5] = ui->dial_LFOsymmetry_6;

	combo_lfo_waveform[0] = ui->comboBox_LFOwaveform_1;
	combo_lfo_waveform[1] = ui->comboBox_LFOwaveform_2;
	combo_lfo_waveform[2] = ui->comboBox_LFOwaveform_3;
	combo_lfo_waveform[3] = ui->comboBox_LFOwaveform_4;
	combo_lfo_waveform[4] = ui->comboBox_LFOwaveform_5;
	combo_lfo_waveform[5] = ui->comboBox_LFOwaveform_6;

	lineedit_lfo_rate[0] = ui->lineEdit_LFOrate_1;
	lineedit_lfo_rate[1] = ui->lineEdit_LFOrate_2;
	lineedit_lfo_rate[2] = ui->lineEdit_LFOrate_3;
	lineedit_lfo_rate[3] = ui->lineEdit_LFOrate_4;
	lineedit_lfo_rate[4] = ui->lineEdit_LFOrate_5;
	lineedit_lfo_rate[5] = ui->lineEdit_LFOrate_6;

	lineedit_lfo_symmetry[0] = ui->lineEdit_LFOsymmetry_1;
	lineedit_lfo_symmetry[1] = ui->lineEdit_LFOsymmetry_2;
	lineedit_lfo_symmetry[2] = ui->lineEdit_LFOsymmetry_3;
	lineedit_lfo_symmetry[3] = ui->lineEdit_LFOsymmetry_4;
	lineedit_lfo_symmetry[4] = ui->lineEdit_LFOsymmetry_5;
	lineedit_lfo_symmetry[5] = ui->lineEdit_LFOsymmetry_6;

	// Init LFO frame waveform combobox

	ui->comboBox_LFOwaveform->blockSignals(true);
	ui->comboBox_LFOwaveform->addItems(string_waveforms_list);
	ui->comboBox_LFOwaveform->blockSignals(false);	

	// Initialize Analog Synth Resources sections
	result = init_osc1_gui();
	result = init_osc2_gui();
	result = init_noise_gui();
	result = init_karplus_strong_gui();
	result = init_mso_gui();
	result = init_pad_gui();
	result = init_filters_gui();
	result = init_distortion_gui();
	result = init_amps_gui();
	//result = init_reverb_gui();  // Now in the reverb instrument dialog
	result = init_equalizer_gui();
	result = init_adsrs_gui();
	result = init_lfos_gui();
	
	

	result = control_widgets_color_manager->set_checkbox_color(ui->checkBox_Osc1Active);
	result = control_widgets_color_manager->set_checkbox_color(ui->checkBox_Osc2Active);
	result = control_widgets_color_manager->set_checkbox_color(ui->checkBox_Osc2SyncOnOsc1);
	result = control_widgets_color_manager->set_checkbox_color(ui->checkBox_Osc1UnisonSquareWave);
	result = control_widgets_color_manager->set_checkbox_color(ui->checkBox_NoiseActive);
	result = control_widgets_color_manager->set_checkbox_color(ui->checkBox_KpsActive);
	result = control_widgets_color_manager->set_checkbox_color(ui->checkBox_MsoActive);
	result = control_widgets_color_manager->set_checkbox_color(ui->checkBox_PadActive);
	result = control_widgets_color_manager->set_checkbox_color(ui->checkBox_Distortion_Active);
	result = control_widgets_color_manager->set_checkbox_color(ui->checkBox_Reverbration3_Active);
	result = control_widgets_color_manager->set_checkbox_color(ui->checkBox_Reverbration_Active);
	result = control_widgets_color_manager->set_checkbox_color(ui->checkBox_Filter2FollowFilter1);
	result = control_widgets_color_manager->set_checkbox_color(ui->checkBox_DistortionAutoGain);
	

	ui->frame_ADSR->hide();
	ui->frame_LFO->hide();

	// Connect signal to slot with Qt::QueuedConnection for thread-safety
	// This ensures the slot runs in the GUI thread
	connect(this, &Dialog_AnalogSynth_1900x1000::control_box_event_signal,
			this, &Dialog_AnalogSynth_1900x1000::handle_control_box_event,
			Qt::QueuedConnection);

	mod_synth_register_callback_control_box_event_update_ui(
		&analog_synth_control_box_event_update_ui_callback_wrapper);

	// Register with GuiNavigator with frames organized per tab
	QMap<int, QList<QString>> frames_per_tab;

	GuiNavigator *nav = GuiNavigator::get_instance();

	// Tab 0: Sources - has OSC1, OSC2, Noise, KPS, MSO, PAD frames
	frames_per_tab[0] << "OSC1-Waveform" << "OSC1-Drawbars"
					  << "OSC2-Waveform" << "OSC2-PWM"
					  << "Noise"
					  << "KPS"
					  << "MSO-Tune" << "MSO-Segments"
					  << "PAD-Tune" << "PAD-Harmonics";

	// Tab 1: Effects - has Filters, Distortion, Reverb, Equalizer frames
	frames_per_tab[1] << "Filters" << "Distortion + Reverb" << "Equalizer";

	// Tab 2: Modulators - has ADSRs, LFOs frames
	frames_per_tab[2] << "ADSR-1 ADSR-2 ADSR-3 ADSR-4 LFO-1 LFO-2 LFO-3 LFO-4"
					  << "ADSR-1 ADSR-2 ADSR-5 ADSR-6 LFO-1 LFO-2 LFO-5 LFO-6";

	nav->register_dialog(
		this,
		"Analog Synth",
		ui->tabWidget_AnalogSynth, // The tab widget
		frames_per_tab			   // Frames organized per tab
	);

	// Set gray frames for Tab 0 - Sources
	nav->set_gray_frame_widgets(this, 0, 0,
								ui->frame_Osc1Waveform,
								ui->frame_Osc1TuneOffset,
								NULL,
								NULL);

	nav->set_gray_frame_widgets(this, 0, 1,
								ui->frame_Osc1Drawbars_1_6,
								ui->frame_Osc1PwmMod,
								NULL,
								NULL);

	nav->set_gray_frame_widgets(this, 0, 2,
								ui->frame_Osc2Waveform,
								ui->frame_Osc2TuneOffset,
								NULL,
								NULL);

	nav->set_gray_frame_widgets(this, 0, 3, // No change for Tab 0, only white frame change.
								ui->frame_Osc2Waveform,
								ui->frame_Osc2TuneOffset,
								NULL,
								NULL);

	nav->set_gray_frame_widgets(this, 0, 4,
								ui->frame_MsoSendFiltersTuneOffset,
								NULL,
								NULL,
								NULL);

	nav->set_gray_frame_widgets(this, 0, 5,
								ui->frame_MsoAmpMod,
								ui->frame_MsoSegments,
								NULL,
								NULL);

	nav->set_gray_frame_widgets(this, 0, 6,
								ui->frame_AnalogSynthSources_Noise,
								NULL,
								NULL,
								NULL);

	nav->set_gray_frame_widgets(this, 0, 7,
								ui->frame_PAD_SendFiltersTuneOffset,
								NULL,
								NULL,
								NULL);


	nav->set_gray_frame_widgets(this, 0, 8,
								ui->frame_PAD_Haromonys1_6,
								ui->frame_PAD_Profile,
								NULL,
								NULL);

	// Set white frames for Tab 0 - Sources
	nav->set_white_frame_widgets(this, 0, 0,
								 ui->frame_Osc1FrequencyModulation,
								 ui->frame_Osc1AmpMod,
								 NULL,
								 NULL);

	nav->set_white_frame_widgets(this, 0, 1,
								 ui->frame_Osc1Drawbars_7_9,
								 NULL,
								 NULL,
								 NULL);

	nav->set_white_frame_widgets(this, 0, 2,
								 ui->frame_Osc2FreqMod,
								 ui->frame_Osc2AmpMod,
								 NULL,
								 NULL);

	nav->set_white_frame_widgets(this, 0, 3,
								 ui->frame_Osc2AmpMod, // Keep it
								 ui->frame_Osc2PwmMod,
								 NULL,
								 NULL);

	nav->set_white_frame_widgets(this, 0, 4,
								 ui->frame_MsoFreqMod,
								 ui->frame_MsoAmpMod,
								 NULL,
								 NULL);

	nav->set_white_frame_widgets(this, 0, 5,
								 ui->frame_MsoAmpMod,
								 ui->frame_MsoPwmMod,
								 NULL,
								 NULL);

	nav->set_white_frame_widgets(this, 0, 6,
								 ui->frame_AnalogSynthSources_KarplusString,
								 NULL,
								 NULL,
								 NULL);

	nav->set_white_frame_widgets(this, 0, 7,
								 ui->frame_PAD_FreqMod,
								 ui->frame_PAD_AmpMod,
								 NULL,
								 NULL);

	nav->set_white_frame_widgets(this, 0, 8,
								 ui->frame_PAD_Haromonys7_10,
								 NULL,
								 NULL,
								 NULL);

	// Set gray frames for Tab 1 - Processors
	nav->set_gray_frame_widgets(this, 1, 0,
								ui->frame_AnalogSynthProcessing_Filter_1,
								NULL,
								NULL,
								NULL);

	nav->set_gray_frame_widgets(this, 1, 1,
								ui->frame_AnalogSynthProcessing_Distortion,
								NULL,
								NULL,
								NULL);

	nav->set_gray_frame_widgets(this, 1, 2,
								ui->frame_Equalizer,
								NULL,
								NULL,
								NULL);

	// Set white frames for Tab 1 - Processors
	nav->set_white_frame_widgets(this, 1, 0,
								ui->frame_AnalogSynthProcessing_Filter_2,
								NULL,
								NULL,
								NULL);

	nav->set_white_frame_widgets(this, 1, 1,
								 ui->frame_freeVerb3,
								 ui->frame_FreeVerb,
								 NULL,
								 NULL);

	nav->set_white_frame_widgets(this, 1, 2,
								 ui->frame_Equalizer_8_16,
								 NULL,
								 NULL,
								 NULL);

	// Set gray frames for Tab 2 - Modulators
	nav->set_gray_frame_widgets(this, 2, 0,
								ui->frame_LFO_1,
								ui->frame_ADSR_1,
								ui->frame_LFO_2,
								ui->frame_ADSR_2);

	nav->set_gray_frame_widgets(this, 2, 1, // No change for Tab 2, only white frame change.
								ui->frame_LFO_1,
								ui->frame_ADSR_1,
								ui->frame_LFO_2,
								ui->frame_ADSR_2);
	
	// Set white frames for Tab 2 - Modulators
	nav->set_white_frame_widgets(this, 2, 0,
								ui->frame_LFO_3,
								ui->frame_ADSR_3,
								ui->frame_LFO_4,
								ui->frame_ADSR_4);

	nav->set_white_frame_widgets(this, 2, 1,
								 ui->frame_LFO_5,
								 ui->frame_ADSR_5,
								 ui->frame_LFO_6,
								 ui->frame_ADSR_6);

	nav->refresh_current_highlight();


	// Connect to frame change signal
	connect(GuiNavigator::get_instance(), &GuiNavigator::frame_changed,
			this, &Dialog_AnalogSynth_1900x1000::on_frame_changed);

	sketch_selected(0); // Default to sketch 1

	MainWindow::get_instance()->register_active_dialog(this);

	// GUI Update timer start
	start_update_timer(_UPDATE_TIMER_PERIOD_MS);
}

Dialog_AnalogSynth_1900x1000::~Dialog_AnalogSynth_1900x1000()
{
	dialog_analog_synth_instance = NULL;
	delete ui;
}	

Dialog_AnalogSynth_1900x1000 *Dialog_AnalogSynth_1900x1000::get_instance(QWidget *parent)
{
	if (dialog_analog_synth_instance == NULL)
	{
		dialog_analog_synth_instance = new Dialog_AnalogSynth_1900x1000(parent);
	}
	return dialog_analog_synth_instance;
}

// Thread-safe function called from callback - just emits signal
void Dialog_AnalogSynth_1900x1000::control_box_event_received(int evnt, uint16_t val)
{
	// Emit signal - Qt will queue it to run in GUI thread
	emit control_box_event_signal(evnt, val);
}

Ui::Dialog_AnalogSynth_1900x1000 *Dialog_AnalogSynth_1900x1000::get_ui_instance()
{
	if (dialog_analog_synth_instance)
	{
		return dialog_analog_synth_instance->ui;
	}

	return nullptr;
}

void Dialog_AnalogSynth_1900x1000::closeEvent(QCloseEvent *event)
{
	// if (close_event_callback_ptr != NULL)
	//{
	//	close_event_callback_ptr();
	// }

	MainWindow::get_instance()->sketches_menu->setDisabled(true);

	// Unregister from GuiNavigator
	GuiNavigator::get_instance()->unregister_dialog(this);

	// Hide instead of accept (which could trigger deletion)
	event->ignore(); // Don't accept the close event

	hide();
}

void Dialog_AnalogSynth_1900x1000::set_analog_synth_general_signals_connections()
{
	connect(ui->pushButton_AnalogSynth_Sketch_1,
			SIGNAL(clicked()),
			this,
			SLOT(on_sketch1_selected()));

	connect(ui->pushButton_AnalogSynth_Sketch_2,
			SIGNAL(clicked()),
			this,
			SLOT(on_sketch2_selected()));

	connect(ui->pushButton_AnalogSynth_Sketch_3,
			SIGNAL(clicked()),
			this,
			SLOT(on_sketch3_selected()));

	connect(ui->pushButton_Panic,
			SIGNAL(clicked()),
			this,
			SLOT(on_panic_cliked()));
	
	connect(ui->tabWidget_AnalogSynth,
			SIGNAL(currentChanged(int)),
			this,
			SLOT(on_tab_selected(int)));

	connect(ui->pushButton_closeADSRframe,
			SIGNAL(clicked()),
			this,
			SLOT(on_ADSR_frame_close_button_clicked()));

	connect(ui->pushButton_closeLFOframe,
			SIGNAL(clicked()),
			this,
			SLOT(on_LFO_frame_close_button_clicked()));
	
	connect(ui->verticalSlider_AdsrA,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_selected_adsr_attack_slider_changed(int)));

	connect(ui->verticalSlider_AdsrD,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_selected_adsr_decay_slider_changed(int)));

	connect(ui->verticalSlider_AdsrS,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_selected_adsr_sustain_slider_changed(int)));

	connect(ui->verticalSlider_AdsrR,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_selected_adsr_release_slider_changed(int)));
	
	connect(ui->comboBox_LFOwaveform,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_lfo_waveform_changed(int)));

	connect(ui->dial_LFOrate,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_selected_lfo_rate_dial_changed(int)));
	
	connect(ui->dial_LFOsymmetry,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_selected_lfo_symmetry_dial_changed(int)));

	connect(ui->comboBox_Osc1FreqModAdsr, 
			SIGNAL(mouseEntered(int)), 
			this, 
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_Osc1FreqModAdsr,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_Osc1AmpModAdsr,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_Osc1AmpModAdsr,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_Osc1PwmModAdsr,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_Osc1PwmModAdsr,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_Osc2FreqModAdsr,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_Osc2FreqModAdsr,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_Osc2AmpModAdsr,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_Osc2AmpModAdsr,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_Osc2PwmModAdsr,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_Osc2PwmModAdsr,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MsoFreqModAdsr,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MsoFreqModAdsr,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MsoAmpModAdsr,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MsoAmpModAdsr,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MsoPwmModAdsr,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MsoPwmModAdsr,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_NoiseAmpModAdsr,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_NoiseAmpModAdsr,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_PadFreqModAdsr,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_PadFreqModAdsr,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_PadAmpModAdsr,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_PadAmpModAdsr,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_FilterFreqModAdsr_1,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_FilterFreqModAdsr_1,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_FilterFreqModAdsr_2,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_FilterFreqModAdsr_2,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	

	connect(ui->comboBox_Osc1FreqModLFO,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_Osc1FreqModLFO,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_Osc1AmpModLFO,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_Osc1AmpModLFO,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_Osc1PwmModLFO,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_Osc1PwmModLFO,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_Osc2FreqModLFO,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_Osc2FreqModLFO,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_Osc2AmpModLFO,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_Osc2AmpModLFO,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_Osc2PwmModLFO,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_Osc2PwmModLFO,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MsoFreqModLFO,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MsoFreqModLFO,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MsoAmpModLFO,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MsoAmpModLFO,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_MsoPwmModLFO,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_MsoPwmModLFO,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_PadFreqModLFO,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_PadFreqModLFO,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_PadAmpModLFO,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_PadAmpModLFO,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_NoiseAmpModLFO,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_NoiseAmpModLFO,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_FilterFreqModLfo_1,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_FilterFreqModLfo_1,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_FilterFreqModLfo_2,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_FilterFreqModLfo_2,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_AmpPanModLfo_1,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_AmpPanModLfo_1,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));

	connect(ui->comboBox_AmpPanModLfo_2,
			SIGNAL(mouseEntered(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_entered(int)));

	connect(ui->comboBox_AmpPanModLfo_2,
			SIGNAL(mouseExited(int)),
			this,
			SLOT(on_modulator_combo_box_mouse_exited(int)));
}

void Dialog_AnalogSynth_1900x1000::update_all()
{
	osc1_update();
	osc2_update();
	noise_update();
	kps_update();
	mso_update();
	pad_update();
	filters_update();
	distortion_update();
	reverb_update();
	equalizer_update();
	amps_update();
	adsrs_update();
	lfos_update();
}

// Periodic GUI update function called by timer (Let Qt event loop to run GUI updates)
void Dialog_AnalogSynth_1900x1000::update_gui()
{
	if (mso_replot_waveform)
	{
		setup_mso_plot(ui->widget_MsoWaveformPlot);
		ui->widget_MsoWaveformPlot->replot();

		mso_replot_waveform = false;
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

	if (active_adsr_widget_showing)
	{
		active_adsr_frame_no_activity_counter--;
		if (active_adsr_frame_no_activity_counter <= 0)
		{
			active_adsr_widget_showing = false;
			ui->frame_ADSR->hide();
		}
	}

	if (active_lfo_widget_showing)
	{
		active_lfo_frame_no_activity_counter--;
		if (active_lfo_frame_no_activity_counter <= 0)
		{
			active_lfo_widget_showing = false;
			ui->frame_LFO->hide();
		}
	}

	if (update_adsr_plot[_ENV_1 - 1])
	{
		set_adsr_plot_widget_points(_ENV_1);
		refresh_adsr_curve_view(ui->widget_ADSRplot_1);
		update_adsr_plot[_ENV_1 - 1] = false;
	}

	if (update_adsr_plot[_ENV_2 - 1])
	{
		set_adsr_plot_widget_points(_ENV_2);
		refresh_adsr_curve_view(ui->widget_ADSRplot_2);
		update_adsr_plot[_ENV_2 - 1] = false;
	}

	if (update_adsr_plot[_ENV_3 - 1])
	{
		set_adsr_plot_widget_points(_ENV_3);
		refresh_adsr_curve_view(ui->widget_ADSRplot_3);
		update_adsr_plot[_ENV_3 - 1] = false;
	}
	
	if (update_adsr_plot[_ENV_4 - 1])
	{
		set_adsr_plot_widget_points(_ENV_4);
		refresh_adsr_curve_view(ui->widget_ADSRplot_4);
		update_adsr_plot[_ENV_4 - 1] = false;
	}
	
	if (update_adsr_plot[_ENV_5 - 1])
	{
		set_adsr_plot_widget_points(_ENV_5);
		refresh_adsr_curve_view(ui->widget_ADSRplot_5);
		update_adsr_plot[_ENV_5 - 1] = false;
	}

	if (update_adsr_plot[_ENV_6 - 1])
	{
		set_adsr_plot_widget_points(_ENV_6);
		refresh_adsr_curve_view(ui->widget_ADSRplot_6);
		update_adsr_plot[_ENV_6 - 1] = false;
	}

	if (update_adsr_plot[_ENV_SELECTED - 1])
	{
		set_adsr_plot_widget_points(active_adsr);
		refresh_adsr_curve_view(ui->widget_ADSRplot);
		update_adsr_plot[_ENV_SELECTED - 1] = false;
	}
	
}

void Dialog_AnalogSynth_1900x1000::start_update_timer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update_gui()));
	timer->start(interval);
}

void Dialog_AnalogSynth_1900x1000::timerEvent(QTimerEvent *event)
{
	killTimer(event->timerId());
	start_update_timer(_UPDATE_TIMER_PERIOD_MS);
}

int Dialog_AnalogSynth_1900x1000::init_frame_colors(CustomFrame *frame)
{
	if (frame == NULL)
	{
		return -1;
	}

	// Check if the frame exists in the map
	if (control_widgets_color_manager->frame_control_colors.find(frame) ==
		control_widgets_color_manager->frame_control_colors.end())
	{
		// Key doesn't exist
		return -1;
	}

	frame->setBorderColor(control_widgets_color_manager->frame_control_colors[frame]);
	frame->setBorderWidth(3);

	return 0;
}

int Dialog_AnalogSynth_1900x1000::init_dial_control_colors(CustomDial *dial)
{
	if (dial == NULL)
	{
		return -1;
	}

	// Check if the dial exists in the map
	if (control_widgets_color_manager->dial_control_colors.find(dial) ==
		control_widgets_color_manager->dial_control_colors.end())
	{
		// Key doesn't exist
		return -1;
	}

	// Additional check: ensure the value is not NULL
	if (control_widgets_color_manager->dial_control_colors[dial] == NULL)
	{
		return -1;
	}

	dial->setKnobColor(control_widgets_color_manager->dial_control_colors[dial][_KNOB_COLOR_INDEX]);
	dial->setCircleColor(control_widgets_color_manager->dial_control_colors[dial][_KNOB_CIRCLE_COLOR_INDEX]);

	return 0;
}

int Dialog_AnalogSynth_1900x1000::init_combobox_control_colors(CustomComboBox *combobox)
{
	if (combobox == NULL)
	{
		return -1;
	}
	
	// Check if the combobox exists in the map
	if (control_widgets_color_manager->combobox_control_colors.find(combobox) ==
		control_widgets_color_manager->combobox_control_colors.end())
	{
		// Key doesn't exist
		return -1;
	}
	
	// Additional check: ensure the value is not NULL
	if (control_widgets_color_manager->combobox_control_colors[combobox] == NULL)
	{
		return -1;
	}

	combobox->setBackgroundColor(control_widgets_color_manager->combobox_control_colors[combobox][_COMBOBOX_BACKGROUND_COLOR_INDEX]);
	combobox->setFrameVisible(true);
	combobox->setFrameColor(control_widgets_color_manager->combobox_control_colors[combobox][_COMBOBOX_FRAME_COLOR_INDEX]);
	combobox->setFrameWidth(2);
	
	return 0;
}

int Dialog_AnalogSynth_1900x1000::init_horizontal_slider_control_colors(CustomHorizontalSlider *hslider)
{
	if (hslider == NULL)
	{
		return -1;
	}

	// Check if the hslider exists in the map
	if (control_widgets_color_manager->horizontal_slider_control_colors.find(hslider) ==
		control_widgets_color_manager->horizontal_slider_control_colors.end())
	{
		// Key doesn't exist
		return -1;
	}
	// Additional check: ensure the value is not NULL
	
	if (control_widgets_color_manager->horizontal_slider_control_colors[hslider] == NULL)
	{
		return -1;
	}

	hslider->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	hslider->setFrameVisible(true);
	
	hslider->setFrameColor(control_widgets_color_manager->horizontal_slider_control_colors[hslider][_HORIZONTAL_SLIDER_FRAME_COLOR_INDEX]);
	hslider->setProgressColor(control_widgets_color_manager->horizontal_slider_control_colors[hslider][_HORIZONTAL_SLIDER_PROGRESS_COLOR_INDEX]);
	hslider->setHandleColor(control_widgets_color_manager->horizontal_slider_control_colors[hslider][_HORIZONTAL_SLIDER_HANDLE_COLOR_INDEX]);

	hslider->setTrackColor(_CONTROLS_COLOR_LIGHT_GRAY);

	return 0;
}

int Dialog_AnalogSynth_1900x1000::init_vertical_slider_control_colors(CustomVerticalSlider *vslider)
{
	if (vslider == NULL)
	{
		return -1;
	}

	// Check if the vslider exists in the map
	if (control_widgets_color_manager->vertical_slider_control_colors.find(vslider) ==
		control_widgets_color_manager->vertical_slider_control_colors.end())
	{
		// Key doesn't exist
		return -1;
	}
	// Additional check: ensure the value is not NULL

	if (control_widgets_color_manager->vertical_slider_control_colors[vslider] == NULL)
	{
		return -1;
	}

	vslider->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	vslider->setFrameVisible(true);

	vslider->setFrameColor(control_widgets_color_manager->vertical_slider_control_colors[vslider][_VERTICAL_SLIDER_FRAME_COLOR_INDEX]);
	vslider->setProgressColor(control_widgets_color_manager->vertical_slider_control_colors[vslider][_VERTICAL_SLIDER_PROGRESS_COLOR_INDEX]);
	vslider->setHandleColor(control_widgets_color_manager->vertical_slider_control_colors[vslider][_VERTICAL_SLIDER_HANDLE_COLOR_INDEX]);

	vslider->setTrackColor(_CONTROLS_COLOR_LIGHT_GRAY);

	return 0;
}

void Dialog_AnalogSynth_1900x1000::sketch_selected(int sketch, bool val)
{
	switch (sketch)
	{
	case 0:
		/* Sketch 1 selected */
		sketch1_active = true;
		sketch2_active = false;
		sketch3_active = false;
		active_sketch = 0;

		mod_synth_set_active_sketch(_SKETCH_PROGRAM_1);

		ui->pushButton_AnalogSynth_Sketch_1->blockSignals(true);
		ui->pushButton_AnalogSynth_Sketch_1->setChecked(true);
		//ui->pushButton_AnalogSynth_Sketch_1->setText("[Sketch 1]");
		ui->pushButton_AnalogSynth_Sketch_1->setTextColor(QColor(_CONTROL_COLOR_GREEN));
		ui->pushButton_AnalogSynth_Sketch_1->blockSignals(false);

		ui->pushButton_AnalogSynth_Sketch_2->blockSignals(true);
		ui->pushButton_AnalogSynth_Sketch_2->setChecked(false);
		//ui->pushButton_AnalogSynth_Sketch_2->setText("Sketch 2");
		ui->pushButton_AnalogSynth_Sketch_2->setTextColor(QColor(_CONTROL_COLOR_WHITE));
		ui->pushButton_AnalogSynth_Sketch_2->blockSignals(false);

		ui->pushButton_AnalogSynth_Sketch_3->blockSignals(true);
		ui->pushButton_AnalogSynth_Sketch_3->setChecked(false);
		//ui->pushButton_AnalogSynth_Sketch_3->setText("Sketch 3");
		ui->pushButton_AnalogSynth_Sketch_3->setTextColor(QColor(_CONTROL_COLOR_WHITE));
		ui->pushButton_AnalogSynth_Sketch_3->blockSignals(false);

		//mod_synth_set_active_sketch(_SKETCH_PROGRAM_1);
		update_all();
		// All notes off
		mod_synth_panic_action();

		update_profile_plot = true;

		break;

	case 1:
		/* Sketch 2 selected */
		sketch1_active = false;
		sketch2_active = true;
		sketch3_active = false;
		active_sketch = 1;

		mod_synth_set_active_sketch(_SKETCH_PROGRAM_2);

		ui->pushButton_AnalogSynth_Sketch_1->blockSignals(true);
		ui->pushButton_AnalogSynth_Sketch_1->setChecked(false);
		//ui->pushButton_AnalogSynth_Sketch_1->setText("Sketch 1");
		ui->pushButton_AnalogSynth_Sketch_1->setTextColor(QColor(_CONTROL_COLOR_WHITE));
		ui->pushButton_AnalogSynth_Sketch_1->blockSignals(false);

		ui->pushButton_AnalogSynth_Sketch_2->blockSignals(true);
		ui->pushButton_AnalogSynth_Sketch_2->setChecked(true);
		//ui->pushButton_AnalogSynth_Sketch_2->setText("[Sketch 2]");
		ui->pushButton_AnalogSynth_Sketch_2->setTextColor(QColor(_CONTROL_COLOR_GREEN));
		ui->pushButton_AnalogSynth_Sketch_2->blockSignals(false);

		ui->pushButton_AnalogSynth_Sketch_3->blockSignals(true);
		ui->pushButton_AnalogSynth_Sketch_3->setChecked(false);
		//ui->pushButton_AnalogSynth_Sketch_3->setText("Sketch 3");
		ui->pushButton_AnalogSynth_Sketch_3->setTextColor(QColor(_CONTROL_COLOR_WHITE));
		ui->pushButton_AnalogSynth_Sketch_3->blockSignals(false);

		//mod_synth_set_active_sketch(_SKETCH_PROGRAM_2);
		update_all();
		// All notes off
		mod_synth_panic_action();

		update_profile_plot = true;

		break;

	case 2:
		/* Sketch 3 selected */
		sketch1_active = false;
		sketch2_active = false;
		sketch3_active = true;
		active_sketch = 2;

		mod_synth_set_active_sketch(_SKETCH_PROGRAM_3);

		ui->pushButton_AnalogSynth_Sketch_1->blockSignals(true);
		ui->pushButton_AnalogSynth_Sketch_1->setChecked(false);
		//ui->pushButton_AnalogSynth_Sketch_1->setText("Sketch 1");
		ui->pushButton_AnalogSynth_Sketch_1->setTextColor(QColor(_CONTROL_COLOR_WHITE));
		ui->pushButton_AnalogSynth_Sketch_1->blockSignals(false);

		ui->pushButton_AnalogSynth_Sketch_2->blockSignals(true);
		ui->pushButton_AnalogSynth_Sketch_2->setChecked(false);
		//ui->pushButton_AnalogSynth_Sketch_2->setText("Sketch 2");
		ui->pushButton_AnalogSynth_Sketch_2->setTextColor(QColor(_CONTROL_COLOR_WHITE));
		ui->pushButton_AnalogSynth_Sketch_2->blockSignals(false);

		ui->pushButton_AnalogSynth_Sketch_3->blockSignals(true);
		ui->pushButton_AnalogSynth_Sketch_3->setChecked(true);
		//ui->pushButton_AnalogSynth_Sketch_3->setText("[Sketch 3]");
		ui->pushButton_AnalogSynth_Sketch_3->setTextColor(QColor(_CONTROL_COLOR_GREEN));
		ui->pushButton_AnalogSynth_Sketch_3->blockSignals(false);

		//mod_synth_set_active_sketch(_SKETCH_PROGRAM_3);
		update_all();
		// All notes off
		mod_synth_panic_action();

		update_profile_plot = true;

		break;
	}
}

// TODO: remove all the bellow set/get functions

void Dialog_AnalogSynth_1900x1000::set_active_adsr(int adsr)
{
	if (adsr < 0 || adsr > _NUM_OF_ADSRS - 1)
	{
		return;
	}
	
	active_adsr = adsr;
}

void Dialog_AnalogSynth_1900x1000::set_active_adsr_attack(int attack)
{
	if (attack < 0 || attack > 100)
	{
		return;
	}
	
	active_adsr_attack = attack;
}

void Dialog_AnalogSynth_1900x1000::set_active_adsr_decay(int decay)
{
	if (decay < 0 || decay > 100)
	{
		return;
	}
	
	active_adsr_decay = decay;
}

void Dialog_AnalogSynth_1900x1000::set_active_adsr_sustain(int sustain)
{
	if (sustain < 0 || sustain > 100)
	{
		return;
	}
	
	active_adsr_sustain = sustain;
}

void Dialog_AnalogSynth_1900x1000::set_active_adsr_release(int release)
{
	if (release < 0 || release > 100)
	{
		return;
	}

	active_adsr_release = release;
}

int Dialog_AnalogSynth_1900x1000::get_active_adsr()
{
	return active_adsr;
}

int Dialog_AnalogSynth_1900x1000::get_active_adsr_attack()
{
	return active_adsr_attack;
}

int Dialog_AnalogSynth_1900x1000::get_active_adsr_decay()
{
	return active_adsr_decay;
}

int Dialog_AnalogSynth_1900x1000::get_active_adsr_sustain()
{
	return active_adsr_sustain;
}

int Dialog_AnalogSynth_1900x1000::get_active_adsr_release()
{
	return active_adsr_release;
}

// TODO: remove all the above set/get functions


void Dialog_AnalogSynth_1900x1000::on_dialog_close()
{
	MainWindow::get_instance()->sketches_menu->setDisabled(true);
	hide();
}

void Dialog_AnalogSynth_1900x1000::on_panic_clicked()
{
	mod_synth_adj_synt_panic_action();
	mod_synth_panic_action();
}

void Dialog_AnalogSynth_1900x1000::on_tab_selected(int tab)
{
	// Hide ADSR and LFOs frames when switching tabs
	ui->frame_ADSR->hide();
	ui->frame_LFO->hide();
}

void Dialog_AnalogSynth_1900x1000::on_sketch1_selected()
{
	sketch_selected(0);
}

void Dialog_AnalogSynth_1900x1000::on_sketch2_selected()
{
	sketch_selected(1);
}

void Dialog_AnalogSynth_1900x1000::on_sketch3_selected()
{
	sketch_selected(2);
}



// Handle frame navigation
void Dialog_AnalogSynth_1900x1000::on_frame_changed(const QString &frame_name, int frame_index)
{
	qDebug() << "Switching to frame:" << frame_name;

	// Hide all frames first
	// ... hide all frames ...

	// Show the selected frame
	if (frame_name == "OSC1")
	{
		//ui->frame_OSC1->show();
	}
	else if (frame_name == "OSC2")
	{
		//ui->frame_OSC2->show();
	}
	// ... etc for all frames ...
}

// Open ADSR control frame when mouse enters an ADSR or LFO combobox
void Dialog_AnalogSynth_1900x1000::on_modulator_combo_box_mouse_entered(int val)
{
	int lfo_num = -1;

	switch (val)
	{
	case _OSC1_FREQ_MOD_ADSR_COMBOBOX_INDEX:
		if (ui->comboBox_Osc1FreqModAdsr->currentIndex() == 0)
		{
			// No ADSR selected yet - nothing to do.
			break;
		}

		active_adsr = ui->comboBox_Osc1FreqModAdsr->currentIndex();
		ui->label_ADSRtitle->setText("ADSR " + QString::number(active_adsr));
		ui->frame_ADSR->move(360, 400);
		update_active_adsr_frame();
		update_adsr_plot[_ENV_SELECTED - 1] = true;
		active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_adsr_widget_showing = true;
		ui->frame_ADSR->show();

		break;

	case _OSC1_AMP_MOD_ADSR_COMBOBOX_INDEX:
		if (ui->comboBox_Osc1AmpModAdsr->currentIndex() == 0)
		{
			// No ADSR selected yet - nothing to do.
			break;
		}

		active_adsr = ui->comboBox_Osc1AmpModAdsr->currentIndex();
		ui->label_ADSRtitle->setText("ADSR " + QString::number(active_adsr));
		ui->frame_ADSR->move(560, 400);
		update_active_adsr_frame();
		update_adsr_plot[_ENV_SELECTED - 1] = true;
		active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_adsr_widget_showing = true;
		ui->frame_ADSR->show();

		break;

	case _OSC1_PWM_MOD_ADSR_COMBOBOX_INDEX:
		if (ui->comboBox_Osc1PwmModAdsr->currentIndex() == 0)
		{
			// No ADSR selected yet - nothing to do.
			break;
		}

		active_adsr = ui->comboBox_Osc1PwmModAdsr->currentIndex();
		ui->label_ADSRtitle->setText("ADSR " + QString::number(active_adsr));
		ui->frame_ADSR->move(760, 400);
		update_active_adsr_frame();
		update_adsr_plot[_ENV_SELECTED - 1] = true;
		active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_adsr_widget_showing = true;
		ui->frame_ADSR->show();

		break;

	case _OSC2_FREQ_MOD_ADSR_COMBOBOX_INDEX:
		if (ui->comboBox_Osc2FreqModAdsr->currentIndex() == 0)
		{
			// No ADSR selected yet - nothing to do.
			break;
		}

		active_adsr = ui->comboBox_Osc2FreqModAdsr->currentIndex();
		ui->label_ADSRtitle->setText("ADSR " + QString::number(active_adsr));
		ui->frame_ADSR->move(1130, 70);
		update_active_adsr_frame();
		update_adsr_plot[_ENV_SELECTED - 1] = true;
		active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_adsr_widget_showing = true;
		ui->frame_ADSR->show();
		break;

	case _OSC2_AMP_MOD_ADSR_COMBOBOX_INDEX:
		if (ui->comboBox_Osc2AmpModAdsr->currentIndex() == 0)
		{
			// No ADSR selected yet - nothing to do.
			break;
		}

		active_adsr = ui->comboBox_Osc2AmpModAdsr->currentIndex();
		ui->label_ADSRtitle->setText("ADSR " + QString::number(active_adsr));
		ui->frame_ADSR->move(1130, 230);
		update_active_adsr_frame();
		update_adsr_plot[_ENV_SELECTED - 1] = true;
		active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_adsr_widget_showing = true;
		ui->frame_ADSR->show();

		break;

	case _OSC2_PWM_MOD_ADSR_COMBOBOX_INDEX:
		if (ui->comboBox_Osc2PwmModAdsr->currentIndex() == 0)
		{
			// No ADSR selected yet - nothing to do.
			break;
		}

		active_adsr = ui->comboBox_Osc2PwmModAdsr->currentIndex();
		ui->label_ADSRtitle->setText("ADSR " + QString::number(active_adsr));
		ui->frame_ADSR->move(1130, 390);
		update_active_adsr_frame();
		update_adsr_plot[_ENV_SELECTED - 1] = true;
		active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_adsr_widget_showing = true;
		ui->frame_ADSR->show();

		break;

	case _MSO_FREQ_MOD_ADSR_COMBOBOX_INDEX:
		if (ui->comboBox_MsoFreqModAdsr->currentIndex() == 0)
		{
			// No ADSR selected yet - nothing to do.
			break;
		}

		active_adsr = ui->comboBox_MsoFreqModAdsr->currentIndex();
		ui->label_ADSRtitle->setText("ADSR " + QString::number(active_adsr));
		ui->frame_ADSR->move(1550, 70);
		update_active_adsr_frame();
		update_adsr_plot[_ENV_SELECTED - 1] = true;
		active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_adsr_widget_showing = true;
		ui->frame_ADSR->show();
		break;

	case _MSO_AMP_MOD_ADSR_COMBOBOX_INDEX:
		if (ui->comboBox_MsoAmpModAdsr->currentIndex() == 0)
		{
			// No ADSR selected yet - nothing to do.
			break;
		}

		active_adsr = ui->comboBox_MsoAmpModAdsr->currentIndex();
		ui->label_ADSRtitle->setText("ADSR " + QString::number(active_adsr));
		ui->frame_ADSR->move(1550, 230);
		update_active_adsr_frame();
		update_adsr_plot[_ENV_SELECTED - 1] = true;
		active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_adsr_widget_showing = true;
		ui->frame_ADSR->show();
		break;

	case _MSO_PWM_MOD_ADSR_COMBOBOX_INDEX:
		if (ui->comboBox_MsoPwmModAdsr->currentIndex() == 0)
		{
			// No ADSR selected yet - nothing to do.
			break;
		}

		active_adsr = ui->comboBox_MsoPwmModAdsr->currentIndex();
		ui->label_ADSRtitle->setText("ADSR " + QString::number(active_adsr));
		ui->frame_ADSR->move(1550, 390);
		update_active_adsr_frame();
		update_adsr_plot[_ENV_SELECTED - 1] = true;
		active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_adsr_widget_showing = true;
		ui->frame_ADSR->show();
		break;

	case _PAD_FREQ_MOD_ADSR_COMBOBOX_INDEX:
		if (ui->comboBox_PadFreqModAdsr->currentIndex() == 0)
		{
			// No ADSR selected yet - nothing to do.
			break;
		}

		active_adsr = ui->comboBox_PadFreqModAdsr->currentIndex();
		ui->label_ADSRtitle->setText("ADSR " + QString::number(active_adsr));
		ui->frame_ADSR->move(950, 610);
		update_active_adsr_frame();
		update_adsr_plot[_ENV_SELECTED - 1] = true;
		active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_adsr_widget_showing = true;
		ui->frame_ADSR->show();
		break;

	case _PAD_AMP_MOD_ADSR_COMBOBOX_INDEX:
		if (ui->comboBox_PadAmpModAdsr->currentIndex() == 0)
		{
			// No ADSR selected yet - nothing to do.
			break;
		}

		active_adsr = ui->comboBox_PadAmpModAdsr->currentIndex();
		ui->label_ADSRtitle->setText("ADSR " + QString::number(active_adsr));
		ui->frame_ADSR->move(950, 610);
		update_active_adsr_frame();
		update_adsr_plot[_ENV_SELECTED - 1] = true;
		active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_adsr_widget_showing = true;
		ui->frame_ADSR->show();
		break;

	case _NOISE_AMP_MOD_ADSR_COMBOBOX_INDEX:
		if (ui->comboBox_NoiseAmpModAdsr->currentIndex() == 0)
		{
			// No ADSR selected yet - nothing to do.
			break;
		}

		active_adsr = ui->comboBox_NoiseAmpModAdsr->currentIndex();
		ui->label_ADSRtitle->setText("ADSR " + QString::number(active_adsr));
		ui->frame_ADSR->move(240, 610);
		update_active_adsr_frame();
		update_adsr_plot[_ENV_SELECTED - 1] = true;
		active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_adsr_widget_showing = true;
		ui->frame_ADSR->show();
		break;

	case _FILTER1_FREQ_MOD_ADSR_COMBOBOX_INDEX:
		if (ui->comboBox_FilterFreqModAdsr_1->currentIndex() == 0)
		{
			// No ADSR selected yet - nothing to do.
			break;
		}

		active_adsr = ui->comboBox_FilterFreqModAdsr_1->currentIndex();
		ui->label_ADSRtitle->setText("ADSR " + QString::number(active_adsr));
		ui->frame_ADSR->move(360, 180);
		update_active_adsr_frame();
		update_adsr_plot[_ENV_SELECTED - 1] = true;
		active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_adsr_widget_showing = true;
		ui->frame_ADSR->show();
		break;

	case _FILTER2_FREQ_MOD_ADSR_COMBOBOX_INDEX:
		if (ui->comboBox_FilterFreqModAdsr_2->currentIndex() == 0)
		{
			// No ADSR selected yet - nothing to do.
			break;
		}

		active_adsr = ui->comboBox_FilterFreqModAdsr_2->currentIndex();
		ui->label_ADSRtitle->setText("ADSR " + QString::number(active_adsr));
		ui->frame_ADSR->move(360, 480);
		update_active_adsr_frame();
		update_adsr_plot[_ENV_SELECTED - 1] = true;
		active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_adsr_widget_showing = true;
		ui->frame_ADSR->show();
		break;

	case _OSC1_FREQ_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_Osc1FreqModLFO->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		// Each LFO provides multiple modes: 1. no delay 2. 0.5Sec delay 3. 1Sec 4. 1.5Sec 5. 2Sec
		active_lfo = (ui->comboBox_Osc1FreqModLFO->currentIndex() - 1) % _NUM_OF_LFOS + 1; // _LFO_1 (0) = 1

		ui->label_LFOtitle->setText("LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(360, 400);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _OSC1_AMP_MOD_LFO_COMBOBOX_INDEX:

		if (ui->comboBox_Osc1AmpModLFO->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_Osc1AmpModLFO->currentIndex() - 1) % _NUM_OF_LFOS + 1;

		ui->label_LFOtitle->setText("LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(560, 400);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _OSC1_PWM_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_Osc1PwmModLFO->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_Osc1PwmModLFO->currentIndex() - 1) % _NUM_OF_LFOS + 1;

		ui->label_LFOtitle->setText("LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(760, 400);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _OSC2_FREQ_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_Osc2FreqModLFO->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_Osc2FreqModLFO->currentIndex() - 1) % _NUM_OF_LFOS + 1;

		ui->label_LFOtitle->setText("LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(1130, 70);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _OSC2_AMP_MOD_LFO_COMBOBOX_INDEX:

		if (ui->comboBox_Osc2AmpModLFO->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_Osc2AmpModLFO->currentIndex() - 1) % _NUM_OF_LFOS + 1;

		ui->label_LFOtitle->setText("LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(1130, 230);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _OSC2_PWM_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_Osc2PwmModLFO->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_Osc2PwmModLFO->currentIndex() - 1) % _NUM_OF_LFOS + 1;

		ui->label_LFOtitle->setText("LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(1130, 390);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _MSO_FREQ_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MsoFreqModLFO->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_MsoFreqModLFO->currentIndex() - 1) % _NUM_OF_LFOS + 1;

		ui->label_LFOtitle->setText("LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(1550, 70);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _MSO_AMP_MOD_LFO_COMBOBOX_INDEX:

		if (ui->comboBox_MsoAmpModLFO->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_MsoAmpModLFO->currentIndex() - 1) % _NUM_OF_LFOS + 1;

		ui->label_LFOtitle->setText("LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(1550, 230);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _MSO_PWM_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MsoPwmModLFO->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_MsoPwmModLFO->currentIndex() - 1) % _NUM_OF_LFOS + 1;

		ui->label_LFOtitle->setText("LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(1550, 390);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _PAD_FREQ_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_PadFreqModLFO->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_PadFreqModLFO->currentIndex() - 1) % _NUM_OF_LFOS + 1;

		ui->label_LFOtitle->setText("LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(950, 610);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _PAD_AMP_MOD_LFO_COMBOBOX_INDEX:

		if (ui->comboBox_PadAmpModLFO->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_PadAmpModLFO->currentIndex() - 1) % _NUM_OF_LFOS + 1;

		ui->label_LFOtitle->setText("LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(950, 610);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _NOISE_AMP_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_NoiseAmpModLFO->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_NoiseAmpModLFO->currentIndex() - 1) % _NUM_OF_LFOS + 1;

		ui->label_LFOtitle->setText("LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(240, 610);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();
		break;

	case _FILTER1_FREQ_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_FilterFreqModLfo_1->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_FilterFreqModLfo_1->currentIndex() - 1) % _NUM_OF_LFOS + 1;

		ui->label_LFOtitle->setText("LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(280, 180);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _FILTER2_FREQ_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_FilterFreqModLfo_2->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_FilterFreqModLfo_2->currentIndex() - 1) % _NUM_OF_LFOS + 1;

		ui->label_LFOtitle->setText("LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(280, 480);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _AMP1_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_AmpPanModLfo_1->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_AmpPanModLfo_1->currentIndex() - 1) % _NUM_OF_LFOS + 1;

		ui->label_LFOtitle->setText("LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(620, 260);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _AMP2_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_AmpPanModLfo_2->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_AmpPanModLfo_2->currentIndex() - 1) % _NUM_OF_LFOS + 1;

		ui->label_LFOtitle->setText("LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(620, 560);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	default:
		return;
		
	}
}

void Dialog_AnalogSynth_1900x1000::on_modulator_combo_box_mouse_exited(int val)
{
	switch (val)
	{
		case _OSC1_FREQ_MOD_ADSR_COMBOBOX_INDEX:
			break;

		case _OSC1_PWM_MOD_ADSR_COMBOBOX_INDEX:
			break;

		case _OSC1_AMP_MOD_ADSR_COMBOBOX_INDEX:
			break;

		case _OSC2_FREQ_MOD_ADSR_COMBOBOX_INDEX:
			break;

		case _OSC2_PWM_MOD_ADSR_COMBOBOX_INDEX:
			break;

		case _OSC2_AMP_MOD_ADSR_COMBOBOX_INDEX:
			break;

		case _MSO_FREQ_MOD_ADSR_COMBOBOX_INDEX:
			break;

		case _MSO_PWM_MOD_ADSR_COMBOBOX_INDEX:
			break;

		case _MSO_AMP_MOD_ADSR_COMBOBOX_INDEX:
			break;

		case _PAD_FREQ_MOD_ADSR_COMBOBOX_INDEX:
			break;

		case _PAD_AMP_MOD_ADSR_COMBOBOX_INDEX:
			break;

		case _NOISE_AMP_MOD_ADSR_COMBOBOX_INDEX:
			break;

		case _OSC1_FREQ_MOD_LFO_COMBOBOX_INDEX:
			break;

		case _OSC1_AMP_MOD_LFO_COMBOBOX_INDEX:
			break;

		case _OSC1_PWM_MOD_LFO_COMBOBOX_INDEX:
			break;

		case _OSC2_FREQ_MOD_LFO_COMBOBOX_INDEX:
			break;

		case _OSC2_AMP_MOD_LFO_COMBOBOX_INDEX:
			break;

		case _OSC2_PWM_MOD_LFO_COMBOBOX_INDEX:
			break;

		case _MSO_FREQ_MOD_LFO_COMBOBOX_INDEX:
			break;

		case _MSO_AMP_MOD_LFO_COMBOBOX_INDEX:
			break;

		case _MSO_PWM_MOD_LFO_COMBOBOX_INDEX:
			break;

		case _PAD_FREQ_MOD_LFO_COMBOBOX_INDEX:
			break;

		case _PAD_AMP_MOD_LFO_COMBOBOX_INDEX:
			break;

		case _NOISE_AMP_MOD_LFO_COMBOBOX_INDEX:
			break;

		default:
			return;
		}

	active_adsr_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
	active_adsr_widget_showing = true;
}




