/**
 * @file		Dialog_MasterVolume.cpp
 *	@author		Nahum Budin
 *	@date		6-Jan-2026
 *	@version	1.0
 *					1. 1st. version
 *
 *	@brief		Modular Synthesizer Master Volume Control
 *
 *	@History:
 *
 */

#include "Dialog_MasterVolume.h"
#include "ui_Dialog_MasterVolume.h"

#include "libAdjRaspi5SynthAPI.h"
#include "Defs.h"

Dialog_MasterVolume *Dialog_MasterVolume::dialog_master_volume_instance = NULL;

Dialog_MasterVolume::Dialog_MasterVolume(QWidget *parent)
	: QDialog(parent), ui(new Ui::Dialog_MasterVolume)
{
	ui->setupUi(this);
	dialog_master_volume_instance = this;

	// Prevent dialog from being deleted when closed - only hide it
	setAttribute(Qt::WA_DeleteOnClose, false);

	// Set fixed size - prevents resizing
	setFixedSize(size());
	
	this->setFocus(Qt::ActiveWindowFocusReason);

	connect(ui->verticalSlider_MasterVolume,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_master_volume_dial_changed(int)));

	connect(ui->spinBox_MasterVolume,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_master_volume_spinbox_changed(int)));

	ui->verticalSlider_MasterVolume->setValue(mod_synth_get_master_volume());
	ui->spinBox_MasterVolume->setValue(mod_synth_get_master_volume());	

	ui->verticalSlider_MasterVolume->setFrameColor(_CONTROLS_COLOR_GRAY);
	ui->verticalSlider_MasterVolume->setProgressColor(_CONTROLS_COLOR_GRAY);
	ui->verticalSlider_MasterVolume->setHandleColor(_CONTROLS_COLOR_GRAY);

	ui->verticalSlider_MasterVolume->setTrackColor(_CONTROLS_COLOR_LIGHT_GRAY);

	ui->frame_MasterVolume->setBorderColor(_CONTROL_GROUP_GRAY);
}

Dialog_MasterVolume::~Dialog_MasterVolume()
{
	dialog_master_volume_instance = NULL;
	delete ui;
}

Dialog_MasterVolume *Dialog_MasterVolume::get_instance(QWidget *parent)
{
	if (dialog_master_volume_instance == NULL)
	{
		dialog_master_volume_instance = new Dialog_MasterVolume(parent);
	}
	return dialog_master_volume_instance;
}

void Dialog_MasterVolume::closeEvent(QCloseEvent *event)
{
	hide();
}

void Dialog_MasterVolume::on_master_volume_dial_changed(int vol)
{
	ui->verticalSlider_MasterVolume->blockSignals(true);
	ui->verticalSlider_MasterVolume->setValue(vol);
	ui->verticalSlider_MasterVolume->blockSignals(false);
	
	ui->spinBox_MasterVolume->blockSignals(true);
	ui->spinBox_MasterVolume->setValue(vol);
	ui->spinBox_MasterVolume->blockSignals(false);
	
	mod_synth_set_master_volume(vol);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MasterVolume::on_master_volume_spinbox_changed(int vol)
{
	ui->spinBox_MasterVolume->blockSignals(true);
	ui->spinBox_MasterVolume->setValue(vol);
	ui->spinBox_MasterVolume->blockSignals(false);

	ui->verticalSlider_MasterVolume->blockSignals(true);
	ui->verticalSlider_MasterVolume->setValue(vol);
	ui->verticalSlider_MasterVolume->blockSignals(false);
	
	mod_synth_set_master_volume(vol);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MasterVolume::control_box_ui_update_callback(int evnt, uint16_t val)
{
	/*
	if (evnt == _CONTROL_BOX_MASTER_VOLUME_EVENT)
	{
		ui->dial_MasterVolume->blockSignals(true);
		ui->dial_MasterVolume->setValue(val);
		ui->dial_MasterVolume->blockSignals(false);

		ui->spinBox_MasterVolume->blockSignals(true);
		ui->spinBox_MasterVolume->setValue(val);
		ui->spinBox_MasterVolume->blockSignals(false);
	}
	*/
}


