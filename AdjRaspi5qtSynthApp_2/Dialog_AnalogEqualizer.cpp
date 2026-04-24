/**
 * @file		Dialog_AnalogEqualizer.cpp
 *	@author		Nahum Budin
 *	@date		9-Apr-2026
 *	@version	1.0
 *
 *	@brief		Analog Synthesizer Band Equalizer control dialog
 *
 *	@History:
 *
 *		Version 1.0	22-Aug-2024
 *
 */

#include <QTimer>

#include "modSynthAPI.h"
#include "synthesizer.h"
#include "gui.h"
#include "controlBox.h"
#include "utils.h"

#include "Dialog_AnalogEqualizer.h"
#include "ui_Dialog_AnalogEqualizer.h"
#include "GuiNavigator.h"

Dialog_AnalogEqualizer *Dialog_AnalogEqualizer::dialog_analog_equalizer_instance = NULL;

void analog_equalizer_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	// Marshal to UI thread - this is non-blocking and thread-safe
	Dialog_AnalogEqualizer *instance = Dialog_AnalogEqualizer::get_instance();
	if (instance != NULL)
	{
		QMetaObject::invokeMethod(instance, [instance, evnt, val]() { instance->control_box_ui_update_callback(evnt, val); }, Qt::QueuedConnection);
	}
}

Dialog_AnalogEqualizer::Dialog_AnalogEqualizer(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::Dialog_AnalogEqualizer)
{
	ui->setupUi(this);
	dialog_analog_equalizer_instance = this;

	close_event_callback_ptr = NULL;

	init_equalizer_gui();

	QMap<int, QList<QString>> frames_per_tab;
	
	GuiNavigator *nav = GuiNavigator::get_instance();

	frames_per_tab[0] << "Analog Equalizer";

	// Register dialog WITHOUT a tab widget (nullptr)
	nav->register_dialog(
		this,
		"Analog Equalizer",
		nullptr, // No tab widget
		frames_per_tab);

	mod_synth_register_callback_control_box_event_update_ui(
		&analog_equalizer_control_box_event_update_ui_callback_wrapper);
}

Dialog_AnalogEqualizer::~Dialog_AnalogEqualizer()
{
	static int eqalizer_band[10] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
	static int prev_eqalizer_band[10] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
}

Dialog_AnalogEqualizer *Dialog_AnalogEqualizer::get_instance(QWidget *parent)
{
	if (dialog_analog_equalizer_instance == NULL)
	{
		dialog_analog_equalizer_instance = new Dialog_AnalogEqualizer(parent);
	}

	return dialog_analog_equalizer_instance;
}

int Dialog_AnalogEqualizer::init_equalizer_gui()
{
	int result;

	ui->verticalSlider_BandEquilizer31->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_BandEquilizer31->setFrameVisible(true);
	ui->verticalSlider_BandEquilizer31->setFrameColor(_CONTROLS_COLOR_GRAY);
	ui->verticalSlider_BandEquilizer31->setProgressColor(_CONTROLS_COLOR_GRAY);
	ui->verticalSlider_BandEquilizer31->setHandleColor(_CONTROLS_COLOR_GRAY);
	ui->verticalSlider_BandEquilizer31->setTrackColor(_CONTROLS_COLOR_LIGHT_GRAY);

	ui->verticalSlider_BandEquilizer62->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_BandEquilizer62->setFrameVisible(true);
	ui->verticalSlider_BandEquilizer62->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_BandEquilizer62->setProgressColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_BandEquilizer62->setHandleColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_BandEquilizer62->setTrackColor(_CONTROLS_COLOR_LIGHT_GRAY);

	ui->verticalSlider_BandEquilizer125->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_BandEquilizer125->setFrameVisible(true);
	ui->verticalSlider_BandEquilizer125->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_BandEquilizer125->setProgressColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_BandEquilizer125->setHandleColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_BandEquilizer125->setTrackColor(_CONTROLS_COLOR_LIGHT_GRAY);

	ui->verticalSlider_BandEquilizer250->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_BandEquilizer250->setFrameVisible(true);
	ui->verticalSlider_BandEquilizer250->setFrameColor(_CONTROLS_COLOR_GREEN);
	ui->verticalSlider_BandEquilizer250->setProgressColor(_CONTROLS_COLOR_GREEN);
	ui->verticalSlider_BandEquilizer250->setHandleColor(_CONTROLS_COLOR_GREEN);
	ui->verticalSlider_BandEquilizer250->setTrackColor(_CONTROLS_COLOR_LIGHT_GRAY);

	ui->verticalSlider_BandEquilizer500->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_BandEquilizer500->setFrameVisible(true);
	ui->verticalSlider_BandEquilizer500->setFrameColor(_CONTROLS_COLOR_WHITE);
	ui->verticalSlider_BandEquilizer500->setProgressColor(_CONTROLS_COLOR_WHITE);
	ui->verticalSlider_BandEquilizer500->setHandleColor(_CONTROLS_COLOR_WHITE);
	ui->verticalSlider_BandEquilizer500->setTrackColor(_CONTROLS_COLOR_LIGHT_GRAY);

	ui->verticalSlider_BandEquilizer1K->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_BandEquilizer1K->setFrameVisible(true);
	ui->verticalSlider_BandEquilizer1K->setFrameColor(_CONTROLS_COLOR_YELLOW);
	ui->verticalSlider_BandEquilizer1K->setProgressColor(_CONTROLS_COLOR_YELLOW);
	ui->verticalSlider_BandEquilizer1K->setHandleColor(_CONTROLS_COLOR_YELLOW);
	ui->verticalSlider_BandEquilizer1K->setTrackColor(_CONTROLS_COLOR_LIGHT_GRAY);

	ui->verticalSlider_BandEquilizer2K->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_BandEquilizer2K->setFrameVisible(true);
	ui->verticalSlider_BandEquilizer2K->setFrameColor(_CONTROLS_COLOR_RED);
	ui->verticalSlider_BandEquilizer2K->setProgressColor(_CONTROLS_COLOR_RED);
	ui->verticalSlider_BandEquilizer2K->setHandleColor(_CONTROLS_COLOR_RED);
	ui->verticalSlider_BandEquilizer2K->setTrackColor(_CONTROLS_COLOR_LIGHT_GRAY);

	ui->verticalSlider_BandEquilizer4K->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_BandEquilizer4K->setFrameVisible(true);
	ui->verticalSlider_BandEquilizer4K->setFrameColor(_CONTROLS_COLOR_BLACK);
	ui->verticalSlider_BandEquilizer4K->setProgressColor(_CONTROLS_COLOR_BLACK);
	ui->verticalSlider_BandEquilizer4K->setHandleColor(_CONTROLS_COLOR_BLACK);
	ui->verticalSlider_BandEquilizer4K->setTrackColor(_CONTROLS_COLOR_LIGHT_GRAY);

	ui->verticalSlider_BandEquilizer8K->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_BandEquilizer8K->setFrameVisible(true);
	ui->verticalSlider_BandEquilizer8K->setFrameColor(_CONTROLS_COLOR_GRAY);
	ui->verticalSlider_BandEquilizer8K->setProgressColor(_CONTROLS_COLOR_GRAY);
	ui->verticalSlider_BandEquilizer8K->setHandleColor(_CONTROLS_COLOR_GRAY);
	ui->verticalSlider_BandEquilizer8K->setTrackColor(_CONTROLS_COLOR_LIGHT_GRAY);

	ui->verticalSlider_BandEquilizer16K->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->verticalSlider_BandEquilizer16K->setFrameVisible(true);
	ui->verticalSlider_BandEquilizer16K->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_BandEquilizer16K->setProgressColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_BandEquilizer16K->setHandleColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_BandEquilizer16K->setTrackColor(_CONTROLS_COLOR_LIGHT_GRAY);

	ui->comboBox_BandEquilizerPreset->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_BandEquilizerPreset->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->comboBox_BandEquilizerPreset->setFrameWidth(2);
	ui->comboBox_BandEquilizerPreset->setTextAlignment(Qt::AlignCenter);

	ui->frame_Equalizer_8_16->setBorderColor(_CONTROLS_COLOR_WHITE);
	ui->frame_Equalizer_8_16->setBorderWidth(2);

	set_equalizer_signals_connections();
	update_gui();

	return 0;
}

void Dialog_AnalogEqualizer::set_equalizer_signals_connections()
{
	connect(ui->verticalSlider_BandEquilizer31,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band31_slider_changed(int)));

	connect(ui->verticalSlider_BandEquilizer62,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band62_slider_changed(int)));

	connect(ui->verticalSlider_BandEquilizer125,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band125_slider_changed(int)));

	connect(ui->verticalSlider_BandEquilizer250,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band250_slider_changed(int)));

	connect(ui->verticalSlider_BandEquilizer500,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band500_slider_changed(int)));

	connect(ui->verticalSlider_BandEquilizer1K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band1K_slider_changed(int)));

	connect(ui->verticalSlider_BandEquilizer2K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band2K_slider_changed(int)));

	connect(ui->verticalSlider_BandEquilizer4K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band4K_slider_changed(int)));

	connect(ui->verticalSlider_BandEquilizer8K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band8k_slider_changed(int)));

	connect(ui->verticalSlider_BandEquilizer16K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band16K_slider_changed(int)));

	connect(ui->spinBox_BandEquilizer31,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band31_spinbox_changed(int)));

	connect(ui->spinBox_BandEquilizer62,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band62_spinbox_changed(int)));

	connect(ui->spinBox_BandEquilizer125,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band125_spinbox_changed(int)));

	connect(ui->spinBox_BandEquilizer250,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band250_spinbox_changed(int)));

	connect(ui->spinBox_BandEquilizer500,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band500_spinbox_changed(int)));

	connect(ui->spinBox_BandEquilizer1K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band1K_spinbox_changed(int)));

	connect(ui->spinBox_BandEquilizer2K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band2K_spinbox_changed(int)));

	connect(ui->spinBox_BandEquilizer4K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band4k_spinbox_changed(int)));

	connect(ui->spinBox_BandEquilizer8K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band8k_spinbox_changed(int)));

	connect(ui->spinBox_BandEquilizer16K,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_band_equilizer_band16k_spinbox_changed(int)));

	connect(ui->comboBox_BandEquilizerPreset,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_band_equilizer_band_preset_changed(int)));

	connect(ui->pushButton_EquilizerSetAllZero,
			SIGNAL(clicked(bool)),
			this,
			SLOT(on_band_equilizer_set_all_zero_licked(bool)));
}

void Dialog_AnalogEqualizer::update_gui()
{
	ui->verticalSlider_BandEquilizer31->blockSignals(true);
	ui->verticalSlider_BandEquilizer31->setValue(mod_synth_get_active_equilizer_band31_level() + 20); // -20 ... +20 -> 0 .. 40
	ui->verticalSlider_BandEquilizer31->blockSignals(false);

	ui->verticalSlider_BandEquilizer62->blockSignals(true);
	ui->verticalSlider_BandEquilizer62->setValue(mod_synth_get_active_equilizer_band62_level() + 20);
	ui->verticalSlider_BandEquilizer62->blockSignals(false);

	ui->verticalSlider_BandEquilizer125->blockSignals(true);
	ui->verticalSlider_BandEquilizer125->setValue(mod_synth_get_active_equilizer_band125_level() + 20);
	ui->verticalSlider_BandEquilizer125->blockSignals(false);

	ui->verticalSlider_BandEquilizer250->blockSignals(true);
	ui->verticalSlider_BandEquilizer250->setValue(mod_synth_get_active_equilizer_band250_level() + 20);
	ui->verticalSlider_BandEquilizer250->blockSignals(false);

	ui->verticalSlider_BandEquilizer500->blockSignals(true);
	ui->verticalSlider_BandEquilizer500->setValue(mod_synth_get_active_equilizer_band500_level() + 20);
	ui->verticalSlider_BandEquilizer500->blockSignals(false);

	ui->verticalSlider_BandEquilizer1K->blockSignals(true);
	ui->verticalSlider_BandEquilizer1K->setValue(mod_synth_get_active_equilizer_band1k_level() + 20);
	ui->verticalSlider_BandEquilizer1K->blockSignals(false);

	ui->verticalSlider_BandEquilizer2K->blockSignals(true);
	ui->verticalSlider_BandEquilizer2K->setValue(mod_synth_get_active_equilizer_band2k_level() + 20);
	ui->verticalSlider_BandEquilizer2K->blockSignals(false);

	ui->verticalSlider_BandEquilizer4K->blockSignals(true);
	ui->verticalSlider_BandEquilizer4K->setValue(mod_synth_get_active_equilizer_band4k_level() + 20);
	ui->verticalSlider_BandEquilizer4K->blockSignals(false);

	ui->verticalSlider_BandEquilizer8K->blockSignals(true);
	ui->verticalSlider_BandEquilizer8K->setValue(mod_synth_get_active_equilizer_band8k_level() + 20);
	ui->verticalSlider_BandEquilizer8K->blockSignals(false);

	ui->verticalSlider_BandEquilizer16K->blockSignals(true);
	ui->verticalSlider_BandEquilizer16K->setValue(mod_synth_get_active_equilizer_band16k_level() + 20);
	ui->verticalSlider_BandEquilizer16K->blockSignals(false);

	ui->comboBox_BandEquilizerPreset->blockSignals(true);
	ui->comboBox_BandEquilizerPreset->setCurrentIndex(mod_synth_get_active_equilizer_preset());
	ui->comboBox_BandEquilizerPreset->blockSignals(false);
}

void Dialog_AnalogEqualizer::init_equalizer_combboxes_and_labels()
{
	// TODO: add the preset names to the preset combo box
}

void Dialog_AnalogEqualizer::on_band_equilizer_band31_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer31->blockSignals(true);
	ui->verticalSlider_BandEquilizer31->setValue(val);
	ui->verticalSlider_BandEquilizer31->blockSignals(false);

	ui->spinBox_BandEquilizer31->blockSignals(true);
	ui->spinBox_BandEquilizer31->setValue(val - 20);
	ui->spinBox_BandEquilizer31->blockSignals(false);

	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_31_LEVEL, val - 20); // 0..40 -> -20..+20db

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band62_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer62->blockSignals(true);
	ui->verticalSlider_BandEquilizer62->setValue(val);
	ui->verticalSlider_BandEquilizer62->blockSignals(false);

	ui->spinBox_BandEquilizer62->blockSignals(true);
	ui->spinBox_BandEquilizer62->setValue(val - 20);
	ui->spinBox_BandEquilizer62->blockSignals(false);

	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_62_LEVEL, val - 20); // 0..40 -> -20..+20db

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band125_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer125->blockSignals(true);
	ui->verticalSlider_BandEquilizer125->setValue(val);
	ui->verticalSlider_BandEquilizer125->blockSignals(false);

	ui->spinBox_BandEquilizer125->blockSignals(true);
	ui->spinBox_BandEquilizer125->setValue(val - 20);
	ui->spinBox_BandEquilizer125->blockSignals(false);

	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_125_LEVEL, val - 20); // 0..40 -> -20..+20db

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band250_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer250->blockSignals(true);
	ui->verticalSlider_BandEquilizer250->setValue(val);
	ui->verticalSlider_BandEquilizer250->blockSignals(false);

	ui->spinBox_BandEquilizer250->blockSignals(true);
	ui->spinBox_BandEquilizer250->setValue(val - 20);
	ui->spinBox_BandEquilizer250->blockSignals(false);

	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_250_LEVEL, val - 20); // 0..40 -> -20..+20db

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band500_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer500->blockSignals(true);
	ui->verticalSlider_BandEquilizer500->setValue(val);
	ui->verticalSlider_BandEquilizer500->blockSignals(false);

	ui->spinBox_BandEquilizer500->blockSignals(true);
	ui->spinBox_BandEquilizer500->setValue(val - 20);
	ui->spinBox_BandEquilizer500->blockSignals(false);

	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_500_LEVEL, val - 20); // 0..40 -> -20..+20db

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_AnalogEqualizer::on_band_equilizer_band1K_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer1K->blockSignals(true);
	ui->verticalSlider_BandEquilizer1K->setValue(val);
	ui->verticalSlider_BandEquilizer1K->blockSignals(false);

	ui->spinBox_BandEquilizer1K->blockSignals(true);
	ui->spinBox_BandEquilizer1K->setValue(val - 20);
	ui->spinBox_BandEquilizer1K->blockSignals(false);

	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_1K_LEVEL, val - 20); // 0..40 -> -20..+20db

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band2K_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer2K->blockSignals(true);
	ui->verticalSlider_BandEquilizer2K->setValue(val);
	ui->verticalSlider_BandEquilizer2K->blockSignals(false);

	ui->spinBox_BandEquilizer2K->blockSignals(true);
	ui->spinBox_BandEquilizer2K->setValue(val - 20);
	ui->spinBox_BandEquilizer2K->blockSignals(false);

	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_2K_LEVEL, val - 20); // 0..40 -> -20..+20db

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band4K_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer4K->blockSignals(true);
	ui->verticalSlider_BandEquilizer4K->setValue(val);
	ui->verticalSlider_BandEquilizer4K->blockSignals(false);

	ui->spinBox_BandEquilizer4K->blockSignals(true);
	ui->spinBox_BandEquilizer4K->setValue(val - 20);
	ui->spinBox_BandEquilizer4K->blockSignals(false);

	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_4K_LEVEL, val - 20); // 0..40 -> -20..+20db

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band8K_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer8K->blockSignals(true);
	ui->verticalSlider_BandEquilizer8K->setValue(val);
	ui->verticalSlider_BandEquilizer8K->blockSignals(false);

	ui->spinBox_BandEquilizer8K->blockSignals(true);
	ui->spinBox_BandEquilizer8K->setValue(val - 20);
	ui->spinBox_BandEquilizer8K->blockSignals(false);

	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_8K_LEVEL, val - 20); // 0..40 -> -20..+20db

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band16K_slider_changed(int val)
{
	ui->verticalSlider_BandEquilizer16K->blockSignals(true);
	ui->verticalSlider_BandEquilizer16K->setValue(val);
	ui->verticalSlider_BandEquilizer16K->blockSignals(false);

	ui->spinBox_BandEquilizer16K->blockSignals(true);
	ui->spinBox_BandEquilizer16K->setValue(val - 20);
	ui->spinBox_BandEquilizer16K->blockSignals(false);

	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_BAND_16K_LEVEL, val - 20); // 0..40 -> -20..+20db

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band31_spinbox_changed(int val)
{
	on_band_equilizer_band31_slider_changed(val + 20);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band62_spinbox_changed(int val)
{
	on_band_equilizer_band62_slider_changed(val + 20);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band125_spinbox_changed(int val)
{
	on_band_equilizer_band125_slider_changed(val + 20);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band250_spinbox_changed(int val)
{
	on_band_equilizer_band250_slider_changed(val + 20);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band500_spinbox_changed(int val)
{
	on_band_equilizer_band500_slider_changed(val + 20);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band1K_spinbox_changed(int val)
{
	on_band_equilizer_band1K_slider_changed(val + 20);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band2K_spinbox_changed(int val)
{
	on_band_equilizer_band2K_slider_changed(val + 20);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band4K_spinbox_changed(int val)
{
	on_band_equilizer_band4K_slider_changed(val + 20);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band8K_spinbox_changed(int val)
{
	on_band_equilizer_band8K_slider_changed(val + 20);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band16K_spinbox_changed(int val)
{
	on_band_equilizer_band16K_slider_changed(val + 20);
}

void Dialog_AnalogEqualizer::on_band_equilizer_band_preset_changed(int val)
{
	ui->comboBox_BandEquilizerPreset->blockSignals(true);
	ui->comboBox_BandEquilizerPreset->setCurrentIndex(val);
	ui->comboBox_BandEquilizerPreset->blockSignals(false);

	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_PRESET, val);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogEqualizer::on_band_equilizer_set_all_zero_licked(bool val)
{
	ui->pushButton_EquilizerSetAllZero->blockSignals(true);
	ui->pushButton_EquilizerSetAllZero->setChecked(false);
	ui->pushButton_EquilizerSetAllZero->blockSignals(false);

	mod_synth_band_equalizer_event(_BAND_EQUALIZER_EVENT, _BAND_EQUALIZER_SET_ALL_ZERO, 1);

	update_gui();

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogEqualizer::closeEvent(QCloseEvent *event)
{
	if (close_event_callback_ptr != NULL)
	{
		close_event_callback_ptr();
	}

	// Unregister from GuiNavigator
	GuiNavigator::get_instance()->unregister_dialog(this);

	hide();
}

void Dialog_AnalogEqualizer::on_dialog_close()
{
	hide();
}

void Dialog_AnalogEqualizer::start_update_timer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update_gui()));
	timer->start(interval);
}

void Dialog_AnalogEqualizer::timerEvent(QTimerEvent *event)
{
	killTimer(event->timerId());
	start_update_timer(250);
}

void Dialog_AnalogEqualizer::control_box_ui_update_callback(int evnt, uint16_t val)
{
	if (!this->hasFocus())
	{
		return;
	}

	const int eqalizer_band_max = 40;
	const int eqalizer_band_min = 0;

	static int eqalizer_band[10] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
	static int preset_number = 0;

	static int prev_eqalizer_band[10] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
	static int prev_preset_number = 0;

	int slider_level_gap = 0;

	// Equalizer (controls 1-8)

	// Equalizer (controls 1-8)
	if (evnt == _I2C_CONTROL_ENCODER_1)
	{
		// Gray Gray pushbutton - Equalizer all zero
		if (val == 4096)
		{
			// Pressed
			on_band_equilizer_set_all_zero_licked(true);
		}
	}
	else if (evnt == _I2C_CONTROL_ENCODER_3)
	{
		// Gray Blue combobox - Equalizer preset control
		// TODO:
	}
	else if (evnt == _I2C_CONTROL_SLIDER_1)
	{
		// Gray Gray slider - Equalizer 31Hz control
		// Get new equalizer band value from slider and calculate gap from current UI value
		prev_eqalizer_band[0] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
		slider_level_gap = prev_eqalizer_band[0] - ui->verticalSlider_BandEquilizer31->value();			// 0-40

		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
		{
			// Emits value changed signal.
			ui->verticalSlider_BandEquilizer31->setValue(prev_eqalizer_band[0]);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_2)
	{
		// Gray Purple slider - Equalizer 62Hz control
		// Get new equalizer band value from slider and calculate gap from current UI value
		prev_eqalizer_band[1] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
		slider_level_gap = prev_eqalizer_band[1] - ui->verticalSlider_BandEquilizer62->value();			// 0-40

		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
		{
			// Emits value changed signal.
			ui->verticalSlider_BandEquilizer62->setValue(prev_eqalizer_band[1]);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_3)
	{
		// Gray Blue slider - Equalizer 125Hz control
		// Get new equalizer band value from slider and calculate gap from current UI value
		prev_eqalizer_band[2] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
		slider_level_gap = prev_eqalizer_band[2] - ui->verticalSlider_BandEquilizer125->value();		// 0-40

		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
		{
			// Emits value changed signal.
			ui->verticalSlider_BandEquilizer125->setValue(prev_eqalizer_band[2]);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_4)
	{
		// Gray Green slider - Equalizer 250Hz control
		// Get new equalizer band value from slider and calculate gap from current UI value
		prev_eqalizer_band[3] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
		slider_level_gap = prev_eqalizer_band[3] - ui->verticalSlider_BandEquilizer250->value();		// 0-40

		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
		{
			// Emits value changed signal.
			ui->verticalSlider_BandEquilizer250->setValue(prev_eqalizer_band[3]);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_5)
	{
		// Gray White slider - Equalizer 500Hz control
		// Get new equalizer band value from slider and calculate gap from current UI value
		prev_eqalizer_band[4] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
		slider_level_gap = prev_eqalizer_band[4] - ui->verticalSlider_BandEquilizer500->value();		// 0-40

		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
		{
			// Emits value changed signal.
			ui->verticalSlider_BandEquilizer500->setValue(prev_eqalizer_band[4]);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_6)
	{
		// Gray Yellow slider - Equalizer 1KHz control
		// Get new equalizer band value from slider and calculate gap from current UI value
		prev_eqalizer_band[5] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
		slider_level_gap = prev_eqalizer_band[5] - ui->verticalSlider_BandEquilizer1K->value();			// 0-40

		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
		{
			// Emits value changed signal.
			ui->verticalSlider_BandEquilizer1K->setValue(prev_eqalizer_band[5]);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_7)
	{
		// Gray Red slider - Equalizer 2KHz control
		// Get new equalizer band value from slider and calculate gap from current UI value
		prev_eqalizer_band[6] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
		slider_level_gap = prev_eqalizer_band[6] - ui->verticalSlider_BandEquilizer2K->value();			// 0-40

		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
		{
			// Emits value changed signal.
			ui->verticalSlider_BandEquilizer2K->setValue(prev_eqalizer_band[6]);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_8)
	{
		// Gray Black slider - Equalizer 4KHz control
		// Get new equalizer band value from slider and calculate gap from current UI value
		prev_eqalizer_band[7] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
		slider_level_gap = prev_eqalizer_band[7] - ui->verticalSlider_BandEquilizer4K->value();			// 0-40

		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
		{
			// Emits value changed signal.
			ui->verticalSlider_BandEquilizer4K->setValue(prev_eqalizer_band[7]);
		}
	}

	// Equalizer 8 and 16KHz (controls 9-16)
	else if (evnt == _I2C_CONTROL_SLIDER_9)
	{
		// White Gray slider - Equalizer 8KHz control
		// Get new equalizer band value from slider and calculate gap from current UI value
		prev_eqalizer_band[8] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
		slider_level_gap = prev_eqalizer_band[8] - ui->verticalSlider_BandEquilizer8K->value();			// 0-40

		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
		{
			// Emits value changed signal.
			ui->verticalSlider_BandEquilizer8K->setValue(prev_eqalizer_band[8]);
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_10)
	{
		// White Purple slider - Equalizer 16KHz control
		// Get new equalizer band value from slider and calculate gap from current UI value
		prev_eqalizer_band[9] = normalize_slider_value(val / 36, eqalizer_band_max, eqalizer_band_min); // 0-3600
		slider_level_gap = prev_eqalizer_band[9] - ui->verticalSlider_BandEquilizer16K->value();		// 0-40

		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) < ((eqalizer_band_max - eqalizer_band_min) / 5.0))
		{
			// Emits value changed signal.
			ui->verticalSlider_BandEquilizer16K->setValue(prev_eqalizer_band[9]);
		}
	}
}
