/**
 * @file		Dialog_MasterVolume
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

#pragma once

#include <QDialog>

namespace Ui
{
	class Dialog_MasterVolume;
}

class Dialog_MasterVolume : public QDialog
{
	Q_OBJECT

  public:
	~Dialog_MasterVolume();
	static Dialog_MasterVolume *get_instance(QWidget *parent = 0);

	void control_box_ui_update_callback(int evnt, uint16_t val);

  public slots:
	void closeEvent(QCloseEvent *event);

  protected slots:
	void on_master_volume_dial_changed(int vol);	
	void on_master_volume_spinbox_changed(int vol);

  private:
	explicit Dialog_MasterVolume(QWidget *parent = 0);
	Ui::Dialog_MasterVolume *ui;
	static Dialog_MasterVolume *dialog_master_volume_instance;
	
};

