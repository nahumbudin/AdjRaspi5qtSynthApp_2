/**
 * @file		Dialog_MidiMixer_GuiEvents.cpp
 *	@author		Nahum Budin
 *	@date		22-Jan-2026
 *	@version	1.1
 *					1. New GUI layout 1620x840.
 *					2. Added pan modulationLFO selection and level control per channel.
 *					3. Added Send control per channel.
 *					4. Aded channel activity indication LED per channel.
 *
 *	@brief		Midi Mixer on GUI events handling
 *
 *	@History:
 *
 *		Version 1.0	22-Aug-2024
 *
 */

#include "Dialog_MidiMixer.h"
#include "Dialog_AnalogSynth_1900x1000.h"
#include "ui_Dialog_MidiMixer_1620x840.h"
#include "Defs.h"

void Dialog_MidiMixer::on_level_slider_changed_ch_1(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return;
	}

	ui->verticalSlider_MixerChLevel_1->blockSignals(true);
	ui->verticalSlider_MixerChLevel_1->setValue(vol);
	ui->verticalSlider_MixerChLevel_1->blockSignals(false);

	ui->spinBox_MixerChLevel_1->blockSignals(true);
	ui->spinBox_MixerChLevel_1->setValue(vol);
	ui->spinBox_MixerChLevel_1->blockSignals(false);

	on_level_changed(0, vol);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MidiMixer::on_level_slider_changed_ch_2(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return;
	}

	ui->verticalSlider_MixerChLevel_2->blockSignals(true);
	ui->verticalSlider_MixerChLevel_2->setValue(vol);
	ui->verticalSlider_MixerChLevel_2->blockSignals(false);

	ui->spinBox_MixerChLevel_2->blockSignals(true);
	ui->spinBox_MixerChLevel_2->setValue(vol);
	ui->spinBox_MixerChLevel_2->blockSignals(false);

	on_level_changed(1, vol);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_level_slider_changed_ch_3(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return;
	}

	ui->verticalSlider_MixerChLevel_3->blockSignals(true);
	ui->verticalSlider_MixerChLevel_3->setValue(vol);
	ui->verticalSlider_MixerChLevel_3->blockSignals(false);

	ui->spinBox_MixerChLevel_3->blockSignals(true);
	ui->spinBox_MixerChLevel_3->setValue(vol);
	ui->spinBox_MixerChLevel_3->blockSignals(false);

	on_level_changed(2, vol);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_level_slider_changed_ch_4(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return;
	}

	ui->verticalSlider_MixerChLevel_4->blockSignals(true);
	ui->verticalSlider_MixerChLevel_4->setValue(vol);
	ui->verticalSlider_MixerChLevel_4->blockSignals(false);

	ui->spinBox_MixerChLevel_4->blockSignals(true);
	ui->spinBox_MixerChLevel_4->setValue(vol);
	ui->spinBox_MixerChLevel_4->blockSignals(false);

	on_level_changed(3, vol);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_level_slider_changed_ch_5(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return;
	}

	ui->verticalSlider_MixerChLevel_5->blockSignals(true);
	ui->verticalSlider_MixerChLevel_5->setValue(vol);
	ui->verticalSlider_MixerChLevel_5->blockSignals(false);

	ui->spinBox_MixerChLevel_5->blockSignals(true);
	ui->spinBox_MixerChLevel_5->setValue(vol);
	ui->spinBox_MixerChLevel_5->blockSignals(false);

	on_level_changed(4, vol);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_level_slider_changed_ch_6(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return;
	}

	ui->verticalSlider_MixerChLevel_6->blockSignals(true);
	ui->verticalSlider_MixerChLevel_6->setValue(vol);
	ui->verticalSlider_MixerChLevel_6->blockSignals(false);

	ui->spinBox_MixerChLevel_6->blockSignals(true);
	ui->spinBox_MixerChLevel_6->setValue(vol);
	ui->spinBox_MixerChLevel_6->blockSignals(false);

	on_level_changed(5, vol);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_level_slider_changed_ch_7(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return;
	}

	ui->verticalSlider_MixerChLevel_7->blockSignals(true);
	ui->verticalSlider_MixerChLevel_7->setValue(vol);
	ui->verticalSlider_MixerChLevel_7->blockSignals(false);

	ui->spinBox_MixerChLevel_7->blockSignals(true);
	ui->spinBox_MixerChLevel_7->setValue(vol);
	ui->spinBox_MixerChLevel_7->blockSignals(false);

	on_level_changed(6, vol);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_level_slider_changed_ch_8(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return;
	}

	ui->verticalSlider_MixerChLevel_8->blockSignals(true);
	ui->verticalSlider_MixerChLevel_8->setValue(vol);
	ui->verticalSlider_MixerChLevel_8->blockSignals(false);

	ui->spinBox_MixerChLevel_8->blockSignals(true);
	ui->spinBox_MixerChLevel_8->setValue(vol);
	ui->spinBox_MixerChLevel_8->blockSignals(false);

	on_level_changed(7, vol);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_level_slider_changed_ch_9(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return;
	}

	ui->verticalSlider_MixerChLevel_9->blockSignals(true);
	ui->verticalSlider_MixerChLevel_9->setValue(vol);
	ui->verticalSlider_MixerChLevel_9->blockSignals(false);

	ui->spinBox_MixerChLevel_9->blockSignals(true);
	ui->spinBox_MixerChLevel_9->setValue(vol);
	ui->spinBox_MixerChLevel_9->blockSignals(false);

	on_level_changed(8, vol);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_level_slider_changed_ch_10(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return;
	}

	ui->verticalSlider_MixerChLevel_10->blockSignals(true);
	ui->verticalSlider_MixerChLevel_10->setValue(vol);
	ui->verticalSlider_MixerChLevel_10->blockSignals(false);

	ui->spinBox_MixerChLevel_10->blockSignals(true);
	ui->spinBox_MixerChLevel_10->setValue(vol);
	ui->spinBox_MixerChLevel_10->blockSignals(false);

	on_level_changed(9, vol);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_level_slider_changed_ch_11(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return;
	}

	ui->verticalSlider_MixerChLevel_11->blockSignals(true);
	ui->verticalSlider_MixerChLevel_11->setValue(vol);
	ui->verticalSlider_MixerChLevel_11->blockSignals(false);

	ui->spinBox_MixerChLevel_11->blockSignals(true);
	ui->spinBox_MixerChLevel_11->setValue(vol);
	ui->spinBox_MixerChLevel_11->blockSignals(false);

	on_level_changed(10, vol);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_level_slider_changed_ch_12(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return;
	}

	ui->verticalSlider_MixerChLevel_12->blockSignals(true);
	ui->verticalSlider_MixerChLevel_12->setValue(vol);
	ui->verticalSlider_MixerChLevel_12->blockSignals(false);

	ui->spinBox_MixerChLevel_12->blockSignals(true);
	ui->spinBox_MixerChLevel_12->setValue(vol);
	ui->spinBox_MixerChLevel_12->blockSignals(false);

	on_level_changed(11, vol);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_level_slider_changed_ch_13(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return;
	}

	ui->verticalSlider_MixerChLevel_13->blockSignals(true);
	ui->verticalSlider_MixerChLevel_13->setValue(vol);
	ui->verticalSlider_MixerChLevel_13->blockSignals(false);

	ui->spinBox_MixerChLevel_13->blockSignals(true);
	ui->spinBox_MixerChLevel_13->setValue(vol);
	ui->spinBox_MixerChLevel_13->blockSignals(false);

	on_level_changed(12, vol);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_level_slider_changed_ch_14(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return;
	}

	ui->verticalSlider_MixerChLevel_14->blockSignals(true);
	ui->verticalSlider_MixerChLevel_14->setValue(vol);
	ui->verticalSlider_MixerChLevel_14->blockSignals(false);

	ui->spinBox_MixerChLevel_14->blockSignals(true);
	ui->spinBox_MixerChLevel_14->setValue(vol);
	ui->spinBox_MixerChLevel_14->blockSignals(false);

	on_level_changed(13, vol);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_level_slider_changed_ch_15(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return;
	}

	ui->verticalSlider_MixerChLevel_15->blockSignals(true);
	ui->verticalSlider_MixerChLevel_15->setValue(vol);
	ui->verticalSlider_MixerChLevel_15->blockSignals(false);

	ui->spinBox_MixerChLevel_15->blockSignals(true);
	ui->spinBox_MixerChLevel_15->setValue(vol);
	ui->spinBox_MixerChLevel_15->blockSignals(false);

	on_level_changed(14, vol);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_level_slider_changed_ch_16(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return;
	}

	ui->verticalSlider_MixerChLevel_16->blockSignals(true);
	ui->verticalSlider_MixerChLevel_16->setValue(vol);
	ui->verticalSlider_MixerChLevel_16->blockSignals(false);

	ui->spinBox_MixerChLevel_16->blockSignals(true);
	ui->spinBox_MixerChLevel_16->setValue(vol);
	ui->spinBox_MixerChLevel_16->blockSignals(false);

	on_level_changed(15, vol);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_level_spinbox_changed_ch_1(int vol)
{
	on_level_slider_changed_ch_1(vol);
}
void Dialog_MidiMixer::on_level_spinbox_changed_ch_2(int vol)
{
	on_level_slider_changed_ch_2(vol);
}

void Dialog_MidiMixer::on_level_spinbox_changed_ch_3(int vol)
{
	on_level_slider_changed_ch_3(vol);
}

void Dialog_MidiMixer::on_level_spinbox_changed_ch_4(int vol)
{
	on_level_slider_changed_ch_4(vol);
}

void Dialog_MidiMixer::on_level_spinbox_changed_ch_5(int vol)
{
	on_level_slider_changed_ch_5(vol);
}

void Dialog_MidiMixer::on_level_spinbox_changed_ch_6(int vol)
{
	on_level_slider_changed_ch_6(vol);
}

void Dialog_MidiMixer::on_level_spinbox_changed_ch_7(int vol)
{
	on_level_slider_changed_ch_7(vol);
}

void Dialog_MidiMixer::on_level_spinbox_changed_ch_8(int vol)
{
	on_level_slider_changed_ch_8(vol);
}

void Dialog_MidiMixer::on_level_spinbox_changed_ch_9(int vol)
{
	on_level_slider_changed_ch_9(vol);
}

void Dialog_MidiMixer::on_level_spinbox_changed_ch_10(int vol)
{
	on_level_slider_changed_ch_10(vol);
}

void Dialog_MidiMixer::on_level_spinbox_changed_ch_11(int vol)
{
	on_level_slider_changed_ch_11(vol);
}

void Dialog_MidiMixer::on_level_spinbox_changed_ch_12(int vol)
{
	on_level_slider_changed_ch_12(vol);
}

void Dialog_MidiMixer::on_level_spinbox_changed_ch_13(int vol)
{
	on_level_slider_changed_ch_13(vol);
}

void Dialog_MidiMixer::on_level_spinbox_changed_ch_14(int vol)
{
	on_level_slider_changed_ch_14(vol);
}

void Dialog_MidiMixer::on_level_spinbox_changed_ch_15(int vol)
{
	on_level_slider_changed_ch_15(vol);
}

void Dialog_MidiMixer::on_level_spinbox_changed_ch_16(int vol)
{
	on_level_slider_changed_ch_16(vol);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_1(int pan)
{
	if ((pan < 0) || (pan > 100))
	{
		return;
	}

	ui->dial_MixerChPan_1->blockSignals(true);
	ui->dial_MixerChPan_1->setValue(pan);
	ui->dial_MixerChPan_1->blockSignals(false);

	ui->spinBox_MixerChPan_1->blockSignals(true);
	ui->spinBox_MixerChPan_1->setValue(pan);
	ui->spinBox_MixerChPan_1->blockSignals(false);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);

	on_pan_changed(0, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_2(int pan)
{
	if ((pan < 0) || (pan > 100))
	{
		return;
	}

	ui->dial_MixerChPan_2->blockSignals(true);
	ui->dial_MixerChPan_2->setValue(pan);
	ui->dial_MixerChPan_2->blockSignals(false);

	ui->spinBox_MixerChPan_2->blockSignals(true);
	ui->spinBox_MixerChPan_2->setValue(pan);
	ui->spinBox_MixerChPan_2->blockSignals(false);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);

	on_pan_changed(1, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_3(int pan)
{
	if ((pan < 0) || (pan > 100))
	{
		return;
	}

	ui->dial_MixerChPan_3->blockSignals(true);
	ui->dial_MixerChPan_3->setValue(pan);
	ui->dial_MixerChPan_3->blockSignals(false);

	ui->spinBox_MixerChPan_3->blockSignals(true);
	ui->spinBox_MixerChPan_3->setValue(pan);
	ui->spinBox_MixerChPan_3->blockSignals(false);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);

	on_pan_changed(2, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_4(int pan)
{
	if ((pan < 0) || (pan > 100))
	{
		return;
	}

	ui->dial_MixerChPan_4->blockSignals(true);
	ui->dial_MixerChPan_4->setValue(pan);
	ui->dial_MixerChPan_4->blockSignals(false);

	ui->spinBox_MixerChPan_4->blockSignals(true);
	ui->spinBox_MixerChPan_4->setValue(pan);
	ui->spinBox_MixerChPan_4->blockSignals(false);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);

	on_pan_changed(3, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_5(int pan)
{
	if ((pan < 0) || (pan > 100))
	{
		return;
	}

	ui->dial_MixerChPan_5->blockSignals(true);
	ui->dial_MixerChPan_5->setValue(pan);
	ui->dial_MixerChPan_5->blockSignals(false);

	ui->spinBox_MixerChPan_5->blockSignals(true);
	ui->spinBox_MixerChPan_5->setValue(pan);
	ui->spinBox_MixerChPan_5->blockSignals(false);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);

	on_pan_changed(4, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_6(int pan)
{
	if ((pan < 0) || (pan > 100))
	{
		return;
	}

	ui->dial_MixerChPan_6->blockSignals(true);
	ui->dial_MixerChPan_6->setValue(pan);
	ui->dial_MixerChPan_6->blockSignals(false);

	ui->spinBox_MixerChPan_6->blockSignals(true);
	ui->spinBox_MixerChPan_6->setValue(pan);
	ui->spinBox_MixerChPan_6->blockSignals(false);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);

	on_pan_changed(5, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_7(int pan)
{
	if ((pan < 0) || (pan > 100))
	{
		return;
	}

	ui->dial_MixerChPan_7->blockSignals(true);
	ui->dial_MixerChPan_7->setValue(pan);
	ui->dial_MixerChPan_7->blockSignals(false);

	ui->spinBox_MixerChPan_7->blockSignals(true);
	ui->spinBox_MixerChPan_7->setValue(pan);
	ui->spinBox_MixerChPan_7->blockSignals(false);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);

	on_pan_changed(6, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_8(int pan)
{
	if ((pan < 0) || (pan > 100))
	{
		return;
	}

	ui->dial_MixerChPan_8->blockSignals(true);
	ui->dial_MixerChPan_8->setValue(pan);
	ui->dial_MixerChPan_8->blockSignals(false);

	ui->spinBox_MixerChPan_8->blockSignals(true);
	ui->spinBox_MixerChPan_8->setValue(pan);
	ui->spinBox_MixerChPan_8->blockSignals(false);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);

	on_pan_changed(7, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_9(int pan)
{
	if ((pan < 0) || (pan > 100))
	{
		return;
	}

	ui->dial_MixerChPan_9->blockSignals(true);
	ui->dial_MixerChPan_9->setValue(pan);
	ui->dial_MixerChPan_9->blockSignals(false);

	ui->spinBox_MixerChPan_9->blockSignals(true);
	ui->spinBox_MixerChPan_9->setValue(pan);
	ui->spinBox_MixerChPan_9->blockSignals(false);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);

	on_pan_changed(8, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_10(int pan)
{
	if ((pan < 0) || (pan > 100))
	{
		return;
	}

	ui->dial_MixerChPan_10->blockSignals(true);
	ui->dial_MixerChPan_10->setValue(pan);
	ui->dial_MixerChPan_10->blockSignals(false);

	ui->spinBox_MixerChPan_10->blockSignals(true);
	ui->spinBox_MixerChPan_10->setValue(pan);
	ui->spinBox_MixerChPan_10->blockSignals(false);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);

	on_pan_changed(9, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_11(int pan)
{
	if ((pan < 0) || (pan > 100))
	{
		return;
	}

	ui->dial_MixerChPan_11->blockSignals(true);
	ui->dial_MixerChPan_11->setValue(pan);
	ui->dial_MixerChPan_11->blockSignals(false);

	ui->spinBox_MixerChPan_11->blockSignals(true);
	ui->spinBox_MixerChPan_11->setValue(pan);
	ui->spinBox_MixerChPan_11->blockSignals(false);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);

	on_pan_changed(10, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_12(int pan)
{
	if ((pan < 0) || (pan > 100))
	{
		return;
	}

	ui->dial_MixerChPan_12->blockSignals(true);
	ui->dial_MixerChPan_12->setValue(pan);
	ui->dial_MixerChPan_12->blockSignals(false);

	ui->spinBox_MixerChPan_12->blockSignals(true);
	ui->spinBox_MixerChPan_12->setValue(pan);
	ui->spinBox_MixerChPan_12->blockSignals(false);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);

	on_pan_changed(11, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_13(int pan)
{
	if ((pan < 0) || (pan > 100))
	{
		return;
	}

	ui->dial_MixerChPan_13->blockSignals(true);
	ui->dial_MixerChPan_13->setValue(pan);
	ui->dial_MixerChPan_13->blockSignals(false);

	ui->spinBox_MixerChPan_13->blockSignals(true);
	ui->spinBox_MixerChPan_13->setValue(pan);
	ui->spinBox_MixerChPan_13->blockSignals(false);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);

	on_pan_changed(13, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_14(int pan)
{
	if ((pan < 0) || (pan > 100))
	{
		return;
	}

	ui->dial_MixerChPan_14->blockSignals(true);
	ui->dial_MixerChPan_14->setValue(pan);
	ui->dial_MixerChPan_14->blockSignals(false);

	ui->spinBox_MixerChPan_14->blockSignals(true);
	ui->spinBox_MixerChPan_14->setValue(pan);
	ui->spinBox_MixerChPan_14->blockSignals(false);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);

	on_pan_changed(13, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_15(int pan)
{
	if ((pan < 0) || (pan > 100))
	{
		return;
	}

	ui->dial_MixerChPan_15->blockSignals(true);
	ui->dial_MixerChPan_15->setValue(pan);
	ui->dial_MixerChPan_15->blockSignals(false);

	ui->spinBox_MixerChPan_15->blockSignals(true);
	ui->spinBox_MixerChPan_15->setValue(pan);
	ui->spinBox_MixerChPan_15->blockSignals(false);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);

	on_pan_changed(14, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_16(int pan)
{
	if ((pan < 0) || (pan > 100))
	{
		return;
	}

	ui->dial_MixerChPan_16->blockSignals(true);
	ui->dial_MixerChPan_16->setValue(pan);
	ui->dial_MixerChPan_16->blockSignals(false);

	ui->spinBox_MixerChPan_16->blockSignals(true);
	ui->spinBox_MixerChPan_16->setValue(pan);
	ui->spinBox_MixerChPan_16->blockSignals(false);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);

	on_pan_changed(15, pan);
}

void Dialog_MidiMixer::on_pan_spinbox_changed_ch_1(int pan)
{
	on_pan_dial_changed_ch_1(pan);
}

void Dialog_MidiMixer::on_pan_spinbox_changed_ch_2(int pan)
{
	on_pan_dial_changed_ch_2(pan);
}

void Dialog_MidiMixer::on_pan_spinbox_changed_ch_3(int pan)
{
	on_pan_dial_changed_ch_3(pan);
}

void Dialog_MidiMixer::on_pan_spinbox_changed_ch_4(int pan)
{
	on_pan_dial_changed_ch_4(pan);
}

void Dialog_MidiMixer::on_pan_spinbox_changed_ch_5(int pan)
{
	on_pan_dial_changed_ch_5(pan);
}

void Dialog_MidiMixer::on_pan_spinbox_changed_ch_6(int pan)
{
	on_pan_dial_changed_ch_6(pan);
}

void Dialog_MidiMixer::on_pan_spinbox_changed_ch_7(int pan)
{
	on_pan_dial_changed_ch_7(pan);
}

void Dialog_MidiMixer::on_pan_spinbox_changed_ch_8(int pan)
{
	on_pan_dial_changed_ch_8(pan);
}

void Dialog_MidiMixer::on_pan_spinbox_changed_ch_9(int pan)
{
	on_pan_dial_changed_ch_9(pan);
}

void Dialog_MidiMixer::on_pan_spinbox_changed_ch_10(int pan)
{
	on_pan_dial_changed_ch_10(pan);
}

void Dialog_MidiMixer::on_pan_spinbox_changed_ch_11(int pan)
{
	on_pan_dial_changed_ch_11(pan);
}

void Dialog_MidiMixer::on_pan_spinbox_changed_ch_12(int pan)
{
	on_pan_dial_changed_ch_12(pan);
}

void Dialog_MidiMixer::on_pan_spinbox_changed_ch_13(int pan)
{
	on_pan_dial_changed_ch_13(pan);
}

void Dialog_MidiMixer::on_pan_spinbox_changed_ch_14(int pan)
{
	on_pan_dial_changed_ch_14(pan);
}

void Dialog_MidiMixer::on_pan_spinbox_changed_ch_15(int pan)
{
	on_pan_dial_changed_ch_15(pan);
}

void Dialog_MidiMixer::on_pan_spinbox_changed_ch_16(int pan)
{
	on_pan_dial_changed_ch_16(pan);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_dial_changed_ch_1(int lvl)
{
	if ((lvl < 0) || (lvl > 100))
	{
		return;
	}

	ui->dial_MixerChPanModLevel_1->blockSignals(true);
	ui->dial_MixerChPanModLevel_1->setValue(lvl);
	ui->dial_MixerChPanModLevel_1->blockSignals(false);

	ui->spinBox_MixerChPanModLevel_1->blockSignals(true);
	ui->spinBox_MixerChPanModLevel_1->setValue(lvl);
	ui->spinBox_MixerChPanModLevel_1->blockSignals(false);

	on_pan_mod_level_changed(0, lvl);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_dial_changed_ch_2(int lvl)
{
	if ((lvl < 0) || (lvl > 100))
	{
		return;
	}

	ui->dial_MixerChPanModLevel_2->blockSignals(true);
	ui->dial_MixerChPanModLevel_2->setValue(lvl);
	ui->dial_MixerChPanModLevel_2->blockSignals(false);

	ui->spinBox_MixerChPanModLevel_2->blockSignals(true);
	ui->spinBox_MixerChPanModLevel_2->setValue(lvl);
	ui->spinBox_MixerChPanModLevel_2->blockSignals(false);

	on_pan_mod_level_changed(1, lvl);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_dial_changed_ch_3(int lvl)
{
	if ((lvl < 0) || (lvl > 100))
	{
		return;
	}
	ui->dial_MixerChPanModLevel_3->blockSignals(true);
	ui->dial_MixerChPanModLevel_3->setValue(lvl);
	ui->dial_MixerChPanModLevel_3->blockSignals(false);

	ui->spinBox_MixerChPanModLevel_3->blockSignals(true);
	ui->spinBox_MixerChPanModLevel_3->setValue(lvl);
	ui->spinBox_MixerChPanModLevel_3->blockSignals(false);

	on_pan_mod_level_changed(2, lvl);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_dial_changed_ch_4(int lvl)
{
	if ((lvl < 0) || (lvl > 100))
	{
		return;
	}

	ui->dial_MixerChPanModLevel_4->blockSignals(true);
	ui->dial_MixerChPanModLevel_4->setValue(lvl);
	ui->dial_MixerChPanModLevel_4->blockSignals(false);

	ui->spinBox_MixerChPanModLevel_4->blockSignals(true);
	ui->spinBox_MixerChPanModLevel_4->setValue(lvl);
	ui->spinBox_MixerChPanModLevel_4->blockSignals(false);

	on_pan_mod_level_changed(3, lvl);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_dial_changed_ch_5(int lvl)
{
	if ((lvl < 0) || (lvl > 100))
	{
		return;
	}

	ui->dial_MixerChPanModLevel_5->blockSignals(true);
	ui->dial_MixerChPanModLevel_5->setValue(lvl);
	ui->dial_MixerChPanModLevel_5->blockSignals(false);

	ui->spinBox_MixerChPanModLevel_5->blockSignals(true);
	ui->spinBox_MixerChPanModLevel_5->setValue(lvl);
	ui->spinBox_MixerChPanModLevel_5->blockSignals(false);

	on_pan_mod_level_changed(4, lvl);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_dial_changed_ch_6(int lvl)
{
	if ((lvl < 0) || (lvl > 100))
	{
		return;
	}

	ui->dial_MixerChPanModLevel_6->blockSignals(true);
	ui->dial_MixerChPanModLevel_6->setValue(lvl);
	ui->dial_MixerChPanModLevel_6->blockSignals(false);

	ui->spinBox_MixerChPanModLevel_6->blockSignals(true);
	ui->spinBox_MixerChPanModLevel_6->setValue(lvl);
	ui->spinBox_MixerChPanModLevel_6->blockSignals(false);

	on_pan_mod_level_changed(5, lvl);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_dial_changed_ch_7(int lvl)
{
	if ((lvl < 0) || (lvl > 100))
	{
		return;
	}

	ui->dial_MixerChPanModLevel_7->blockSignals(true);
	ui->dial_MixerChPanModLevel_7->setValue(lvl);
	ui->dial_MixerChPanModLevel_7->blockSignals(false);

	ui->spinBox_MixerChPanModLevel_7->blockSignals(true);
	ui->spinBox_MixerChPanModLevel_7->setValue(lvl);
	ui->spinBox_MixerChPanModLevel_7->blockSignals(false);

	on_pan_mod_level_changed(6, lvl);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_dial_changed_ch_8(int lvl)
{
	if ((lvl < 0) || (lvl > 100))
	{
		return;
	}

	ui->dial_MixerChPanModLevel_8->blockSignals(true);
	ui->dial_MixerChPanModLevel_8->setValue(lvl);
	ui->dial_MixerChPanModLevel_8->blockSignals(false);

	ui->spinBox_MixerChPanModLevel_8->blockSignals(true);
	ui->spinBox_MixerChPanModLevel_8->setValue(lvl);
	ui->spinBox_MixerChPanModLevel_8->blockSignals(false);

	on_pan_mod_level_changed(7, lvl);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_dial_changed_ch_9(int lvl)
{
	if ((lvl < 0) || (lvl > 100))
	{
		return;
	}

	ui->dial_MixerChPanModLevel_9->blockSignals(true);
	ui->dial_MixerChPanModLevel_9->setValue(lvl);
	ui->dial_MixerChPanModLevel_9->blockSignals(false);

	ui->spinBox_MixerChPanModLevel_9->blockSignals(true);
	ui->spinBox_MixerChPanModLevel_9->setValue(lvl);
	ui->spinBox_MixerChPanModLevel_9->blockSignals(false);

	on_pan_mod_level_changed(10, lvl);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_dial_changed_ch_10(int lvl)
{
	if ((lvl < 0) || (lvl > 100))
	{
		return;
	}

	ui->dial_MixerChPanModLevel_10->blockSignals(true);
	ui->dial_MixerChPanModLevel_10->setValue(lvl);
	ui->dial_MixerChPanModLevel_10->blockSignals(false);

	ui->spinBox_MixerChPanModLevel_10->blockSignals(true);
	ui->spinBox_MixerChPanModLevel_10->setValue(lvl);
	ui->spinBox_MixerChPanModLevel_10->blockSignals(false);

	on_pan_mod_level_changed(9, lvl);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_dial_changed_ch_11(int lvl)
{
	if ((lvl < 0) || (lvl > 100))
	{
		return;
	}

	ui->dial_MixerChPanModLevel_11->blockSignals(true);
	ui->dial_MixerChPanModLevel_11->setValue(lvl);
	ui->dial_MixerChPanModLevel_11->blockSignals(false);

	ui->spinBox_MixerChPanModLevel_11->blockSignals(true);
	ui->spinBox_MixerChPanModLevel_11->setValue(lvl);
	ui->spinBox_MixerChPanModLevel_11->blockSignals(false);

	on_pan_mod_level_changed(10, lvl);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_dial_changed_ch_12(int lvl)
{
	if ((lvl < 0) || (lvl > 100))
	{
		return;
	}

	ui->dial_MixerChPanModLevel_12->blockSignals(true);
	ui->dial_MixerChPanModLevel_12->setValue(lvl);
	ui->dial_MixerChPanModLevel_12->blockSignals(false);

	ui->spinBox_MixerChPanModLevel_12->blockSignals(true);
	ui->spinBox_MixerChPanModLevel_12->setValue(lvl);
	ui->spinBox_MixerChPanModLevel_12->blockSignals(false);

	on_pan_mod_level_changed(11, lvl);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_dial_changed_ch_13(int lvl)
{
	if ((lvl < 0) || (lvl > 100))
	{
		return;
	}

	ui->dial_MixerChPanModLevel_13->blockSignals(true);
	ui->dial_MixerChPanModLevel_13->setValue(lvl);
	ui->dial_MixerChPanModLevel_13->blockSignals(false);

	ui->spinBox_MixerChPanModLevel_13->blockSignals(true);
	ui->spinBox_MixerChPanModLevel_13->setValue(lvl);
	ui->spinBox_MixerChPanModLevel_13->blockSignals(false);

	on_pan_mod_level_changed(12, lvl);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_dial_changed_ch_14(int lvl)
{
	if ((lvl < 0) || (lvl > 100))
	{
		return;
	}

	ui->dial_MixerChPanModLevel_14->blockSignals(true);
	ui->dial_MixerChPanModLevel_14->setValue(lvl);
	ui->dial_MixerChPanModLevel_14->blockSignals(false);

	ui->spinBox_MixerChPanModLevel_14->blockSignals(true);
	ui->spinBox_MixerChPanModLevel_14->setValue(lvl);
	ui->spinBox_MixerChPanModLevel_14->blockSignals(false);

	on_pan_mod_level_changed(13, lvl);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_dial_changed_ch_15(int lvl)
{
	if ((lvl < 0) || (lvl > 100))
	{
		return;
	}

	ui->dial_MixerChPanModLevel_15->blockSignals(true);
	ui->dial_MixerChPanModLevel_15->setValue(lvl);
	ui->dial_MixerChPanModLevel_15->blockSignals(false);

	ui->spinBox_MixerChPanModLevel_15->blockSignals(true);
	ui->spinBox_MixerChPanModLevel_15->setValue(lvl);
	ui->spinBox_MixerChPanModLevel_15->blockSignals(false);

	on_pan_mod_level_changed(14, lvl);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_dial_changed_ch_16(int lvl)
{
	if ((lvl < 0) || (lvl > 100))
	{
		return;
	}

	ui->dial_MixerChPanModLevel_16->blockSignals(true);
	ui->dial_MixerChPanModLevel_16->setValue(lvl);
	ui->dial_MixerChPanModLevel_16->blockSignals(false);

	ui->spinBox_MixerChPanModLevel_16->blockSignals(true);
	ui->spinBox_MixerChPanModLevel_16->setValue(lvl);
	ui->spinBox_MixerChPanModLevel_16->blockSignals(false);

	on_pan_mod_level_changed(15, lvl);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_spinbox_changed_ch_1(int lvl)
{
	on_pan_lfo_mod_level_dial_changed_ch_1(lvl);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_spinbox_changed_ch_2(int lvl)
{
	on_pan_lfo_mod_level_dial_changed_ch_2(lvl);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_spinbox_changed_ch_3(int lvl)
{
	on_pan_lfo_mod_level_dial_changed_ch_3(lvl);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_spinbox_changed_ch_4(int lvl)
{
	on_pan_lfo_mod_level_dial_changed_ch_4(lvl);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_spinbox_changed_ch_5(int lvl)
{
	on_pan_lfo_mod_level_dial_changed_ch_5(lvl);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_spinbox_changed_ch_6(int lvl)
{
	on_pan_lfo_mod_level_dial_changed_ch_6(lvl);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_spinbox_changed_ch_7(int lvl)
{
	on_pan_lfo_mod_level_dial_changed_ch_7(lvl);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_spinbox_changed_ch_8(int lvl)
{
	on_pan_lfo_mod_level_dial_changed_ch_8(lvl);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_spinbox_changed_ch_9(int lvl)
{
	on_pan_lfo_mod_level_dial_changed_ch_9(lvl);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_spinbox_changed_ch_10(int lvl)
{
	on_pan_lfo_mod_level_dial_changed_ch_10(lvl);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_spinbox_changed_ch_11(int lvl)
{
	on_pan_lfo_mod_level_dial_changed_ch_11(lvl);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_spinbox_changed_ch_12(int lvl)
{
	on_pan_lfo_mod_level_dial_changed_ch_12(lvl);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_spinbox_changed_ch_13(int pan)
{
	on_pan_lfo_mod_level_dial_changed_ch_13(pan);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_spinbox_changed_ch_14(int lvl)
{
	on_pan_lfo_mod_level_dial_changed_ch_14(lvl);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_spinbox_changed_ch_15(int lvl)
{
	on_pan_lfo_mod_level_dial_changed_ch_15(lvl);
}

void Dialog_MidiMixer::on_pan_lfo_mod_level_spinbox_changed_ch_16(int lvl)
{
	on_pan_lfo_mod_level_dial_changed_ch_16(lvl);
}

void Dialog_MidiMixer::on_pan_lfo_mod_combo_changed_ch_1(int lfo)
{
	ui->comboBox_MixerChPanModLfo_1->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_1->setCurrentIndex(lfo);
	ui->comboBox_MixerChPanModLfo_1->blockSignals(false);

	on_pan_mod_lfo_changed(0, lfo);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_combo_changed_ch_2(int lfo)
{
	ui->comboBox_MixerChPanModLfo_2->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_2->setCurrentIndex(lfo);
	ui->comboBox_MixerChPanModLfo_2->blockSignals(false);

	on_pan_mod_lfo_changed(1, lfo);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_combo_changed_ch_3(int lfo)
{
	ui->comboBox_MixerChPanModLfo_3->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_3->setCurrentIndex(lfo);
	ui->comboBox_MixerChPanModLfo_3->blockSignals(false);

	on_pan_mod_lfo_changed(2, lfo);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_combo_changed_ch_4(int lfo)
{
	ui->comboBox_MixerChPanModLfo_4->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_4->setCurrentIndex(lfo);
	ui->comboBox_MixerChPanModLfo_4->blockSignals(false);
	on_pan_mod_lfo_changed(3, lfo);
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_combo_changed_ch_5(int lfo)
{
	ui->comboBox_MixerChPanModLfo_5->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_5->setCurrentIndex(lfo);
	ui->comboBox_MixerChPanModLfo_5->blockSignals(false);

	on_pan_mod_lfo_changed(4, lfo);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_combo_changed_ch_6(int lfo)
{
	ui->comboBox_MixerChPanModLfo_6->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_6->setCurrentIndex(lfo);
	ui->comboBox_MixerChPanModLfo_6->blockSignals(false);

	on_pan_mod_lfo_changed(5, lfo);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_combo_changed_ch_7(int lfo)
{
	ui->comboBox_MixerChPanModLfo_7->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_7->setCurrentIndex(lfo);
	ui->comboBox_MixerChPanModLfo_7->blockSignals(false);

	on_pan_mod_lfo_changed(6, lfo);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_combo_changed_ch_8(int lfo)
{
	ui->comboBox_MixerChPanModLfo_8->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_8->setCurrentIndex(lfo);
	ui->comboBox_MixerChPanModLfo_8->blockSignals(false);

	on_pan_mod_lfo_changed(7, lfo);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_combo_changed_ch_9(int lfo)
{
	ui->comboBox_MixerChPanModLfo_9->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_9->setCurrentIndex(lfo);
	ui->comboBox_MixerChPanModLfo_9->blockSignals(false);

	on_pan_mod_lfo_changed(8, lfo);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_combo_changed_ch_10(int lfo)
{
	ui->comboBox_MixerChPanModLfo_10->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_10->setCurrentIndex(lfo);
	ui->comboBox_MixerChPanModLfo_10->blockSignals(false);

	on_pan_mod_lfo_changed(9, lfo);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_combo_changed_ch_11(int lfo)
{
	ui->comboBox_MixerChPanModLfo_11->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_11->setCurrentIndex(lfo);
	ui->comboBox_MixerChPanModLfo_11->blockSignals(false);

	on_pan_mod_lfo_changed(10, lfo);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_combo_changed_ch_12(int lfo)
{
	ui->comboBox_MixerChPanModLfo_12->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_12->setCurrentIndex(lfo);
	ui->comboBox_MixerChPanModLfo_12->blockSignals(false);

	on_pan_mod_lfo_changed(11, lfo);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_combo_changed_ch_13(int lfo)
{
	ui->comboBox_MixerChPanModLfo_13->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_13->setCurrentIndex(lfo);
	ui->comboBox_MixerChPanModLfo_13->blockSignals(false);

	on_pan_mod_lfo_changed(12, lfo);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_combo_changed_ch_14(int lfo)
{
	ui->comboBox_MixerChPanModLfo_14->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_14->setCurrentIndex(lfo);
	ui->comboBox_MixerChPanModLfo_14->blockSignals(false);

	on_pan_mod_lfo_changed(13, lfo);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_combo_changed_ch_15(int lfo)
{
	ui->comboBox_MixerChPanModLfo_15->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_15->setCurrentIndex(lfo);
	ui->comboBox_MixerChPanModLfo_15->blockSignals(false);

	on_pan_mod_lfo_changed(14, lfo);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_pan_lfo_mod_combo_changed_ch_16(int lfo)
{
	ui->comboBox_MixerChPanModLfo_16->blockSignals(true);
	ui->comboBox_MixerChPanModLfo_16->setCurrentIndex(lfo);
	ui->comboBox_MixerChPanModLfo_16->blockSignals(false);

	on_pan_mod_lfo_changed(15, lfo);

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_send_dial_changed_ch_1(int snd)
{
	if ((snd < 0) || (snd > 100))
	{
		return;
	}

	ui->dial_MixerChSend_1->blockSignals(true);
	ui->dial_MixerChSend_1->setValue(snd);
	ui->dial_MixerChSend_1->blockSignals(false);

	ui->spinBox_MixerChSend_1->blockSignals(true);
	ui->spinBox_MixerChSend_1->setValue(snd);
	ui->spinBox_MixerChSend_1->blockSignals(false);

	on_send_level_changed(0, snd);

	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_send_dial_changed_ch_2(int snd)
{
	if ((snd < 0) || (snd > 100))
	{
		return;
	}

	ui->dial_MixerChSend_2->blockSignals(true);
	ui->dial_MixerChSend_2->setValue(snd);
	ui->dial_MixerChSend_2->blockSignals(false);

	ui->spinBox_MixerChSend_2->blockSignals(true);
	ui->spinBox_MixerChSend_2->setValue(snd);
	ui->spinBox_MixerChSend_2->blockSignals(false);

	on_send_level_changed(1, snd);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_send_dial_changed_ch_3(int snd)
{
	if ((snd < 0) || (snd > 100))
	{
		return;
	}

	ui->dial_MixerChSend_3->blockSignals(true);
	ui->dial_MixerChSend_3->setValue(snd);
	ui->dial_MixerChSend_3->blockSignals(false);

	ui->spinBox_MixerChSend_3->blockSignals(true);
	ui->spinBox_MixerChSend_3->setValue(snd);
	ui->spinBox_MixerChSend_3->blockSignals(false);

	on_send_level_changed(2, snd);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_send_dial_changed_ch_4(int snd)
{
	if ((snd < 0) || (snd > 100))
	{
		return;
	}

	ui->dial_MixerChSend_4->blockSignals(true);
	ui->dial_MixerChSend_4->setValue(snd);
	ui->dial_MixerChSend_4->blockSignals(false);

	ui->spinBox_MixerChSend_4->blockSignals(true);
	ui->spinBox_MixerChSend_4->setValue(snd);
	ui->spinBox_MixerChSend_4->blockSignals(false);

	on_send_level_changed(3, snd);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_send_dial_changed_ch_5(int snd)
{
	if ((snd < 0) || (snd > 100))
	{
		return;
	}

	ui->dial_MixerChSend_5->blockSignals(true);
	ui->dial_MixerChSend_5->setValue(snd);
	ui->dial_MixerChSend_5->blockSignals(false);

	ui->spinBox_MixerChSend_5->blockSignals(true);
	ui->spinBox_MixerChSend_5->setValue(snd);
	ui->spinBox_MixerChSend_5->blockSignals(false);

	on_send_level_changed(4, snd);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_send_dial_changed_ch_6(int snd)
{
	if ((snd < 0) || (snd > 100))
	{
		return;
	}

	ui->dial_MixerChSend_6->blockSignals(true);
	ui->dial_MixerChSend_6->setValue(snd);
	ui->dial_MixerChSend_6->blockSignals(false);

	ui->spinBox_MixerChSend_6->blockSignals(true);
	ui->spinBox_MixerChSend_6->setValue(snd);
	ui->spinBox_MixerChSend_6->blockSignals(false);

	on_send_level_changed(5, snd);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_send_dial_changed_ch_7(int snd)
{
	if ((snd < 0) || (snd > 100))
	{
		return;
	}

	ui->dial_MixerChSend_7->blockSignals(true);
	ui->dial_MixerChSend_7->setValue(snd);
	ui->dial_MixerChSend_7->blockSignals(false);

	ui->spinBox_MixerChSend_7->blockSignals(true);
	ui->spinBox_MixerChSend_7->setValue(snd);
	ui->spinBox_MixerChSend_7->blockSignals(false);

	on_send_level_changed(6, snd);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_send_dial_changed_ch_8(int snd)
{
	if ((snd < 0) || (snd > 100))
	{
		return;
	}

	ui->dial_MixerChSend_8->blockSignals(true);
	ui->dial_MixerChSend_8->setValue(snd);
	ui->dial_MixerChSend_8->blockSignals(false);

	ui->spinBox_MixerChSend_8->blockSignals(true);
	ui->spinBox_MixerChSend_8->setValue(snd);
	ui->spinBox_MixerChSend_8->blockSignals(false);

	on_send_level_changed(7, snd);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_send_dial_changed_ch_9(int snd)
{
	if ((snd < 0) || (snd > 100))
	{
		return;
	}

	ui->dial_MixerChSend_9->blockSignals(true);
	ui->dial_MixerChSend_9->setValue(snd);
	ui->dial_MixerChSend_9->blockSignals(false);

	ui->spinBox_MixerChSend_9->blockSignals(true);
	ui->spinBox_MixerChSend_9->setValue(snd);
	ui->spinBox_MixerChSend_9->blockSignals(false);

	on_send_level_changed(8, snd);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_send_dial_changed_ch_10(int snd)
{
	if ((snd < 0) || (snd > 100))
	{
		return;
	}

	ui->dial_MixerChSend_10->blockSignals(true);
	ui->dial_MixerChSend_10->setValue(snd);
	ui->dial_MixerChSend_10->blockSignals(false);

	ui->spinBox_MixerChSend_10->blockSignals(true);
	ui->spinBox_MixerChSend_10->setValue(snd);
	ui->spinBox_MixerChSend_10->blockSignals(false);

	on_send_level_changed(9, snd);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_send_dial_changed_ch_11(int snd)
{
	if ((snd < 0) || (snd > 100))
	{
		return;
	}

	ui->dial_MixerChSend_11->blockSignals(true);
	ui->dial_MixerChSend_11->setValue(snd);
	ui->dial_MixerChSend_11->blockSignals(false);

	ui->spinBox_MixerChSend_11->blockSignals(true);
	ui->spinBox_MixerChSend_11->setValue(snd);
	ui->spinBox_MixerChSend_11->blockSignals(false);

	on_send_level_changed(10, snd);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_send_dial_changed_ch_12(int snd)
{
	if ((snd < 0) || (snd > 100))
	{
		return;
	}

	ui->dial_MixerChSend_12->blockSignals(true);
	ui->dial_MixerChSend_12->setValue(snd);
	ui->dial_MixerChSend_12->blockSignals(false);

	ui->spinBox_MixerChSend_12->blockSignals(true);
	ui->spinBox_MixerChSend_12->setValue(snd);
	ui->spinBox_MixerChSend_12->blockSignals(false);

	on_send_level_changed(11, snd);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_send_dial_changed_ch_13(int snd)
{
	if ((snd < 0) || (snd > 100))
	{
		return;
	}

	ui->dial_MixerChSend_13->blockSignals(true);
	ui->dial_MixerChSend_13->setValue(snd);
	ui->dial_MixerChSend_13->blockSignals(false);

	ui->spinBox_MixerChSend_13->blockSignals(true);
	ui->spinBox_MixerChSend_13->setValue(snd);
	ui->spinBox_MixerChSend_13->blockSignals(false);

	on_send_level_changed(12, snd);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_send_dial_changed_ch_14(int snd)
{
	if ((snd < 0) || (snd > 100))
	{
		return;
	}

	ui->dial_MixerChSend_14->blockSignals(true);
	ui->dial_MixerChSend_14->setValue(snd);
	ui->dial_MixerChSend_14->blockSignals(false);

	ui->spinBox_MixerChSend_14->blockSignals(true);
	ui->spinBox_MixerChSend_14->setValue(snd);
	ui->spinBox_MixerChSend_14->blockSignals(false);

	on_send_level_changed(13, snd);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_send_dial_changed_ch_15(int snd)
{
	if ((snd < 0) || (snd > 100))
	{
		return;
	}

	ui->dial_MixerChSend_15->blockSignals(true);
	ui->dial_MixerChSend_15->setValue(snd);
	ui->dial_MixerChSend_15->blockSignals(false);

	ui->spinBox_MixerChSend_15->blockSignals(true);
	ui->spinBox_MixerChSend_15->setValue(snd);
	ui->spinBox_MixerChSend_15->blockSignals(false);

	on_send_level_changed(14, snd);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_send_dial_changed_ch_16(int snd)
{
	if ((snd < 0) || (snd > 100))
	{
		return;
	}

	ui->dial_MixerChSend_16->blockSignals(true);
	ui->dial_MixerChSend_16->setValue(snd);
	ui->dial_MixerChSend_16->blockSignals(false);

	ui->spinBox_MixerChSend_16->blockSignals(true);
	ui->spinBox_MixerChSend_16->setValue(snd);
	ui->spinBox_MixerChSend_16->blockSignals(false);

	on_send_level_changed(15, snd);
	// Set focus back on the Dialog
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_send_spinbox_changed_ch_1(int snd)
{
	on_send_dial_changed_ch_1(snd);
}

void Dialog_MidiMixer::on_send_spinbox_changed_ch_2(int snd)
{
	on_send_dial_changed_ch_2(snd);
}

void Dialog_MidiMixer::on_send_spinbox_changed_ch_3(int snd)
{
	on_send_dial_changed_ch_3(snd);
}

void Dialog_MidiMixer::on_send_spinbox_changed_ch_4(int snd)
{
	on_send_dial_changed_ch_4(snd);
}

void Dialog_MidiMixer::on_send_spinbox_changed_ch_5(int snd)
{
	on_send_dial_changed_ch_5(snd);
}

void Dialog_MidiMixer::on_send_spinbox_changed_ch_6(int snd)
{
	on_send_dial_changed_ch_6(snd);
}

void Dialog_MidiMixer::on_send_spinbox_changed_ch_7(int snd)
{
	on_send_dial_changed_ch_7(snd);
}

void Dialog_MidiMixer::on_send_spinbox_changed_ch_8(int snd)
{
	on_send_dial_changed_ch_8(snd);
}

void Dialog_MidiMixer::on_send_spinbox_changed_ch_9(int snd)
{
	on_send_dial_changed_ch_9(snd);
}

void Dialog_MidiMixer::on_send_spinbox_changed_ch_10(int snd)
{
	on_send_dial_changed_ch_10(snd);
}

void Dialog_MidiMixer::on_send_spinbox_changed_ch_11(int snd)
{
	on_send_dial_changed_ch_11(snd);
}

void Dialog_MidiMixer::on_send_spinbox_changed_ch_12(int snd)
{
	on_send_dial_changed_ch_12(snd);
}

void Dialog_MidiMixer::on_send_spinbox_changed_ch_13(int snd)
{
	on_send_dial_changed_ch_13(snd);
}

void Dialog_MidiMixer::on_send_spinbox_changed_ch_14(int snd)
{
	on_send_dial_changed_ch_14(snd);
}

void Dialog_MidiMixer::on_send_spinbox_changed_ch_15(int snd)
{
	on_send_dial_changed_ch_15(snd);
}

void Dialog_MidiMixer::on_send_spinbox_changed_ch_16(int snd)
{
	on_send_dial_changed_ch_16(snd);
}

void Dialog_MidiMixer::on_static_level_checkbox_changed_ch_1(bool state)
{
	ui->checkBox_MixerChanStaticLevel_1->blockSignals(true);
	if (state)
	{
		ui->checkBox_MixerChanStaticLevel_1->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MixerChanStaticLevel_1->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MixerChanStaticLevel_1->blockSignals(false);

	on_static_levels_changed(0, state);
}

void Dialog_MidiMixer::on_static_level_checkbox_changed_ch_2(bool state)
{
	ui->checkBox_MixerChanStaticLevel_2->blockSignals(true);
	if (state)
	{
		ui->checkBox_MixerChanStaticLevel_2->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MixerChanStaticLevel_2->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MixerChanStaticLevel_2->blockSignals(false);

	on_static_levels_changed(1, state);
}

void Dialog_MidiMixer::on_static_level_checkbox_changed_ch_3(bool state)
{
	ui->checkBox_MixerChanStaticLevel_3->blockSignals(true);
	if (state)
	{
		ui->checkBox_MixerChanStaticLevel_3->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MixerChanStaticLevel_3->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MixerChanStaticLevel_3->blockSignals(false);

	on_static_levels_changed(2, state);
}

void Dialog_MidiMixer::on_static_level_checkbox_changed_ch_4(bool state)
{
	ui->checkBox_MixerChanStaticLevel_4->blockSignals(true);
	if (state)
	{
		ui->checkBox_MixerChanStaticLevel_4->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MixerChanStaticLevel_4->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MixerChanStaticLevel_4->blockSignals(false);

	on_static_levels_changed(3, state);
}

void Dialog_MidiMixer::on_static_level_checkbox_changed_ch_5(bool state)
{
	ui->checkBox_MixerChanStaticLevel_5->blockSignals(true);
	if (state)
	{
		ui->checkBox_MixerChanStaticLevel_5->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MixerChanStaticLevel_5->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MixerChanStaticLevel_5->blockSignals(false);

	on_static_levels_changed(4, state);
}

void Dialog_MidiMixer::on_static_level_checkbox_changed_ch_6(bool state)
{
	ui->checkBox_MixerChanStaticLevel_6->blockSignals(true);
	if (state)
	{
		ui->checkBox_MixerChanStaticLevel_6->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MixerChanStaticLevel_6->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MixerChanStaticLevel_6->blockSignals(false);

	on_static_levels_changed(5, state);
}

void Dialog_MidiMixer::on_static_level_checkbox_changed_ch_7(bool state)
{
	ui->checkBox_MixerChanStaticLevel_7->blockSignals(true);
	if (state)
	{
		ui->checkBox_MixerChanStaticLevel_7->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MixerChanStaticLevel_7->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MixerChanStaticLevel_7->blockSignals(false);

	on_static_levels_changed(6, state);
}

void Dialog_MidiMixer::on_static_level_checkbox_changed_ch_8(bool state)
{
	ui->checkBox_MixerChanStaticLevel_8->blockSignals(true);
	if (state)
	{
		ui->checkBox_MixerChanStaticLevel_8->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MixerChanStaticLevel_8->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MixerChanStaticLevel_8->blockSignals(false);

	on_static_levels_changed(7, state);
}

void Dialog_MidiMixer::on_static_level_checkbox_changed_ch_9(bool state)
{
	ui->checkBox_MixerChanStaticLevel_9->blockSignals(true);
	if (state)
	{
		ui->checkBox_MixerChanStaticLevel_9->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MixerChanStaticLevel_9->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MixerChanStaticLevel_9->blockSignals(false);

	on_static_levels_changed(8, state);
}

void Dialog_MidiMixer::on_static_level_checkbox_changed_ch_10(bool state)
{
	ui->checkBox_MixerChanStaticLevel_10->blockSignals(true);
	if (state)
	{
		ui->checkBox_MixerChanStaticLevel_10->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MixerChanStaticLevel_10->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MixerChanStaticLevel_10->blockSignals(false);

	on_static_levels_changed(9, state);
}

void Dialog_MidiMixer::on_static_level_checkbox_changed_ch_11(bool state)
{
	ui->checkBox_MixerChanStaticLevel_11->blockSignals(true);
	if (state)
	{
		ui->checkBox_MixerChanStaticLevel_11->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MixerChanStaticLevel_11->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MixerChanStaticLevel_11->blockSignals(false);

	on_static_levels_changed(10, state);
}

void Dialog_MidiMixer::on_static_level_checkbox_changed_ch_12(bool state)
{
	ui->checkBox_MixerChanStaticLevel_12->blockSignals(true);
	if (state)
	{
		ui->checkBox_MixerChanStaticLevel_12->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MixerChanStaticLevel_12->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MixerChanStaticLevel_12->blockSignals(false);

	on_static_levels_changed(11, state);
}

void Dialog_MidiMixer::on_static_level_checkbox_changed_ch_13(bool state)
{
	ui->checkBox_MixerChanStaticLevel_13->blockSignals(true);
	if (state)
	{
		ui->checkBox_MixerChanStaticLevel_13->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MixerChanStaticLevel_13->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MixerChanStaticLevel_13->blockSignals(false);

	on_static_levels_changed(12, state);
}

void Dialog_MidiMixer::on_static_level_checkbox_changed_ch_14(bool state)
{
	ui->checkBox_MixerChanStaticLevel_14->blockSignals(true);
	if (state)
	{
		ui->checkBox_MixerChanStaticLevel_14->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MixerChanStaticLevel_14->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MixerChanStaticLevel_14->blockSignals(false);

	on_static_levels_changed(13, state);
}

void Dialog_MidiMixer::on_static_level_checkbox_changed_ch_15(bool state)
{
	ui->checkBox_MixerChanStaticLevel_15->blockSignals(true);
	if (state)
	{
		ui->checkBox_MixerChanStaticLevel_15->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MixerChanStaticLevel_15->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MixerChanStaticLevel_15->blockSignals(false);

	on_static_levels_changed(14, state);
}

void Dialog_MidiMixer::on_static_level_checkbox_changed_ch_16(bool state)
{
	ui->checkBox_MixerChanStaticLevel_16->blockSignals(true);
	if (state)
	{
		ui->checkBox_MixerChanStaticLevel_16->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MixerChanStaticLevel_16->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MixerChanStaticLevel_16->blockSignals(false);

	on_static_levels_changed(15, state);
}

void Dialog_MidiMixer::on_midi_mixer_modulator_combo_box_mouse_entered(int id)
{
	//int lfo_num = -1;

	switch (id)
	{
	case _MIXER_CHAN1_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_1->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		// Each LFO provides multiple modes: 1. no delay 2. 0.5Sec delay 3. 1Sec 4. 1.5Sec 5. 2Sec
		active_lfo = (ui->comboBox_MixerChPanModLfo_1->currentIndex() - 1) % _NUM_OF_LFOS + 1; // _LFO_1 (0) = 1

		ui->label_LFOtitle->setText("CH1 LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(110, 350);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _MIXER_CHAN2_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_2->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_MixerChPanModLfo_2->currentIndex() - 1) % _NUM_OF_LFOS + 1; // _LFO_1 (0) = 1

		ui->label_LFOtitle->setText("CH2 LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(210, 350);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _MIXER_CHAN3_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_3->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_MixerChPanModLfo_3->currentIndex() - 1) % _NUM_OF_LFOS + 1; // _LFO_1 (0) = 1

		ui->label_LFOtitle->setText("CH3 LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(310, 350);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _MIXER_CHAN4_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_4->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_MixerChPanModLfo_4->currentIndex() - 1) % _NUM_OF_LFOS + 1; // _LFO_1 (0) = 1

		ui->label_LFOtitle->setText("CH4 LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(410, 350);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _MIXER_CHAN5_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_5->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_MixerChPanModLfo_5->currentIndex() - 1) % _NUM_OF_LFOS + 1; // _LFO_1 (0) = 1

		ui->label_LFOtitle->setText("CH5 LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(510, 350);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _MIXER_CHAN6_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_6->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_MixerChPanModLfo_6->currentIndex() - 1) % _NUM_OF_LFOS + 1; // _LFO_1 (0) = 1

		ui->label_LFOtitle->setText("CH6 LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(610, 350);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _MIXER_CHAN7_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_7->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_MixerChPanModLfo_7->currentIndex() - 1) % _NUM_OF_LFOS + 1; // _LFO_1 (0) = 1

		ui->label_LFOtitle->setText("CH7 LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(710, 350);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _MIXER_CHAN8_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_8->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_MixerChPanModLfo_8->currentIndex() - 1) % _NUM_OF_LFOS + 1; // _LFO_1 (0) = 1

		ui->label_LFOtitle->setText("CH8 LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(810, 350);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _MIXER_CHAN9_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_9->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_MixerChPanModLfo_9->currentIndex() - 1) % _NUM_OF_LFOS + 1; // _LFO_1 (0) = 1

		ui->label_LFOtitle->setText("CH9 LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(910, 350);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _MIXER_CHAN10_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_10->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_MixerChPanModLfo_10->currentIndex() - 1) % _NUM_OF_LFOS + 1; // _LFO_1 (0) = 1

		ui->label_LFOtitle->setText("CH10 LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(1010, 350);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _MIXER_CHAN11_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_11->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_MixerChPanModLfo_11->currentIndex() - 1) % _NUM_OF_LFOS + 1; // _LFO_1 (0) = 1

		ui->label_LFOtitle->setText("CH11 LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(1110, 350);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _MIXER_CHAN12_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_12->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_MixerChPanModLfo_12->currentIndex() - 1) % _NUM_OF_LFOS + 1; // _LFO_1 (0) = 1

		ui->label_LFOtitle->setText("CH12 LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(1210, 350);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _MIXER_CHAN13_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_13->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_MixerChPanModLfo_13->currentIndex() - 1) % _NUM_OF_LFOS + 1; // _LFO_1 (0) = 1

		ui->label_LFOtitle->setText("CH13 LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(1310, 350);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _MIXER_CHAN14_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_14->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_MixerChPanModLfo_14->currentIndex() - 1) % _NUM_OF_LFOS + 1; // _LFO_1 (0) = 1

		ui->label_LFOtitle->setText("CH14 LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(1410, 350);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	case _MIXER_CHAN15_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_15->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_MixerChPanModLfo_15->currentIndex() - 1) % _NUM_OF_LFOS + 1; // _LFO_1 (0) = 1

		ui->label_LFOtitle->setText("CH15 LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(1190, 350);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;
	case _MIXER_CHAN16_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_16->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		active_lfo = (ui->comboBox_MixerChPanModLfo_16->currentIndex() - 1) % _NUM_OF_LFOS + 1; // _LFO_1 (0) = 1

		ui->label_LFOtitle->setText("CH16 LFO " + QString::number(active_lfo));
		ui->frame_LFO->move(1290, 350);
		update_active_lfo_frame();
		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		ui->frame_LFO->show();

		break;

	default:
		break;
	}
}

void Dialog_MidiMixer::on_midi_mixer_modulator_combo_box_mouse_exited(int id)
{
	int lfo_num = -1;

	switch (id)
	{
	case _MIXER_CHAN1_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_1->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		break;

	case _MIXER_CHAN2_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_2->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		break;

	case _MIXER_CHAN3_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_3->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		break;

	case _MIXER_CHAN4_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_4->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		break;

	case _MIXER_CHAN5_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_5->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		break;

	case _MIXER_CHAN6_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_6->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		break;

	case _MIXER_CHAN7_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_7->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		break;

	case _MIXER_CHAN8_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_8->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		break;

	case _MIXER_CHAN9_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_9->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		break;

	case _MIXER_CHAN10_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_10->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		break;

	case _MIXER_CHAN11_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_11->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		break;

	case _MIXER_CHAN12_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_12->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		break;

	case _MIXER_CHAN13_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_13->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		break;

	case _MIXER_CHAN14_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_14->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		break;

	case _MIXER_CHAN15_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_15->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		break;
	case _MIXER_CHAN16_PAN_MOD_LFO_COMBOBOX_INDEX:
		if (ui->comboBox_MixerChPanModLfo_16->currentIndex() == 0)
		{
			// No LFO selected yet - nothing to do.
			break;
		}

		break;

	default:
		break;
	}
}

void Dialog_MidiMixer::on_selected_lfo_rate_dial_changed(int val)
{
	if ((active_lfo) > _LFO_NONE && (active_lfo) <= _NUM_OF_LFOS)
	{
		//char text[64];
		//
		//if (Dialog_AnalogSynth_1900x1000::dial_lfo_rate[active_lfo - 1])
		//{
		//	// Not initiated yet - nothing to do. Initated if Dialog_AnalogSynth_1900x1000 is opened at least once.
		//	Dialog_AnalogSynth_1900x1000::dial_lfo_rate[active_lfo - 1]->blockSignals(true); // 1..6 -> 0..5
		//	Dialog_AnalogSynth_1900x1000::dial_lfo_rate[active_lfo - 1]->setValue(val);
		//	Dialog_AnalogSynth_1900x1000::dial_lfo_rate[active_lfo - 1]->blockSignals(false);
		//
		//	sprintf(text, "%.2fHz",
		//			mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(),
		//										  mod_synth_get_lfo_max_frequency(), 10.0,
		//										  val));
		//
		//	Dialog_AnalogSynth_1900x1000::lineedit_lfo_rate[active_lfo - 1]->setText(QString(text));
		//	ui->lineEdit_LFOrate->setText(QString(text));
		//
		//	mod_synth_modulator_event_int(_LFO_1_EVENT + active_lfo - 1, _MOD_LFO_RATE, val);
		//}
		//
		mod_synth_modulator_event_int(_LFO_1_EVENT + active_lfo - 1, _MOD_LFO_RATE, val);

		update_active_lfo_frame();

		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
		
	}
}

void Dialog_MidiMixer::on_selected_lfo_symmetry_dial_changed(int val)
{
	if (active_lfo > _LFO_NONE && active_lfo <= _NUM_OF_LFOS)
	{
		//char text[64];
		//
		//if (Dialog_AnalogSynth_1900x1000::dial_lfo_rate[active_lfo - 1])
		//{
		//	// Not initiated yet - nothing to do. Initated if Dialog_AnalogSynth_1900x1000 is opened at least once.
		//	Dialog_AnalogSynth_1900x1000::dial_lfo_symmetry[active_lfo - 1]->blockSignals(true); // 1..6 -> 0..5
		//	Dialog_AnalogSynth_1900x1000::dial_lfo_symmetry[active_lfo - 1]->setValue(val);
		//	Dialog_AnalogSynth_1900x1000::dial_lfo_symmetry[active_lfo - 1]->blockSignals(false);
		//
		//	sprintf(text, "%i%c", val, '%');
		//	Dialog_AnalogSynth_1900x1000::lineedit_lfo_symmetry[active_lfo - 1]->setText(QString(text));
		//	ui->lineEdit_LFOsymmetry->setText(QString(text));
		//
		//	mod_synth_modulator_event_int(_LFO_1_EVENT + active_lfo - 1, _MOD_LFO_SYMMETRY, val);
		//}

		mod_synth_modulator_event_int(_LFO_1_EVENT + active_lfo - 1, _MOD_LFO_SYMMETRY, val);

		update_active_lfo_frame();

		active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
		active_lfo_widget_showing = true;
	}
}

void Dialog_MidiMixer::on_selected_lfo_waveform_combo_changed(int val)
{
	//if (Dialog_AnalogSynth_1900x1000::dial_lfo_rate[active_lfo - 1])
	//{
	//	// Not initiated yet - nothing to do. Initated if Dialog_AnalogSynth_1900x1000 is opened at least once.
	//	Dialog_AnalogSynth_1900x1000::combo_lfo_waveform[active_lfo - 1]->blockSignals(true);
	//	Dialog_AnalogSynth_1900x1000::combo_lfo_waveform[active_lfo - 1]->setCurrentIndex(val);
	//	Dialog_AnalogSynth_1900x1000::combo_lfo_waveform[active_lfo - 1]->blockSignals(false);
	//
	//	mod_synth_modulator_event_int(_LFO_1_EVENT, _MOD_LFO_WAVEFORM, val);
	//}

	mod_synth_modulator_event_int(_LFO_1_EVENT, _MOD_LFO_WAVEFORM, val);

	update_active_lfo_frame();

	active_lfo_frame_no_activity_counter = _MODULATOR_FRAME_NO_ACTIVITY_TIMOUT_COUNT;
	active_lfo_widget_showing = true;
}

void Dialog_MidiMixer::on_LFO_frame_close_button_clicked()
{
	// Close the LFO frame
	ui->frame_LFO->hide();
}
