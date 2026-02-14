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

	std::map<CustomFrame *, QColor> frame_control_colors;
	std::map<CustomDial *, QColor[2]> dial_control_colors; // [knob_color, knob_circle_color]
	std::map<CustomComboBox *, QColor[2]> combobox_control_colors; // [background_color, frame_color]
	std::map<CustomHorizontalSlider *, QColor[3]> horizontal_slider_control_colors; // [frame_color, progress_color, handle_color]
	std::map<CustomVerticalSlider *, QColor[3]> vertical_slider_control_colors; // [frame_color, progress_color, handle_color]
	std::map<CustomButton *, QColor> button_control_colors;

	//void set_button_color(CustomButton *button, QColor color);
	//void set_dial_color(CustomDial *dial, QColor color);
	//void set_slider_color(CustomSlider *slider, QColor color);
  private:
};
