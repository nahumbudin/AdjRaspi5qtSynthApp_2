/**
 * @file		ControlWidgetsColorManager.h
 *	@author		Nahum Budin
 *	@date		27-Dec-2025
 *	@version	1.0
 *					1. First version.
 *
 *	@brief		Controls the Analog Synthesizer instrument GUI control-widgets colors
 *
 *	History:
 *
 */

#pragma once

#include <QColor>
#include <QWidget>

#include "Defs.h"
#include "CustomButton.h"
#include "CustomDial.h"
#include "CustomFrame.h"
#include "CustomHorizontalSlider.h"
#include "CustomVerticalSlider.h"
#include "CustomComboBox.h"
#include "CustomCheckBox.h"

class ControlWidgetsColorManager
{
  public:
	ControlWidgetsColorManager();
	~ControlWidgetsColorManager();

	int init_frames_colors();
	int init_dial_controls_colors();
	int init_combobox_controls_colors();
	int init_horizontal_slider_controls_colors();
	int init_vertical_slider_controls_colors();
	int init_button_controls_colors();
	int init_checkbox_controls_colors();

	int set_frame_color(CustomFrame *frame);
	int set_dial_color(CustomDial *dial);
	int set_combobox_color(CustomComboBox *combobox);
	int set_horizontal_slider_color(CustomHorizontalSlider *hslider);
	int set_vertical_slider_color(CustomVerticalSlider *vslider);
	int set_button_color(CustomButton *button);
	int set_checkbox_color(CustomCheckBox *checkbox);

	std::map<CustomFrame *, QColor> frame_control_colors;
	std::map<CustomDial *, QColor[2]> dial_control_colors;							// [knob_color, knob_circle_color]
	std::map<CustomComboBox *, QColor[2]> combobox_control_colors;					// [background_color, frame_color]
	std::map<CustomHorizontalSlider *, QColor[3]> horizontal_slider_control_colors; // [frame_color, progress_color, handle_color]
	std::map<CustomVerticalSlider *, QColor[3]> vertical_slider_control_colors;		// [frame_color, progress_color, handle_color]
	std::map<CustomButton *, QColor[3]> button_control_colors;						// [frame_color, text_color, background_color]
	std::map<CustomCheckBox *, QColor *> checkbox_control_colors;

  protected:

	//void set_button_color(CustomButton *button, QColor color);
	//void set_dial_color(CustomDial *dial, QColor color);
	//void set_slider_color(CustomSlider *slider, QColor color);
  private:
	bool analog_synth_frames_colors_initialized = false;
	bool analog_synth_dials_colors_initialized = false;
	bool analog_synth_comboboxes_colors_initialized = false;
	bool analog_synth_horizontal_sliders_colors_initialized = false;
	bool analog_synth_vertical_sliders_colors_initialized = false;
	bool analog_synth_buttons_colors_initialized = false;
	bool analog_synth_checkboxes_colors_initialized = false;

	bool midi_mixer_frames_colors_initialized = false;
	bool midi_mixer_dials_colors_initialized = false;
	bool midi_mixer_comboboxes_colors_initialized = false;
	bool midi_mixer_horizontal_sliders_colors_initialized = false;
	bool midi_mixer_vertical_sliders_colors_initialized = false;
	bool midi_mixer_buttons_colors_initialized = false;
	bool midi_mixer_checkboxes_colors_initialized = false;
	
};
