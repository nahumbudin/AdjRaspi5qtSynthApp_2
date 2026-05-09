/**
 * @file		Dialog_AnalogEqualizer.h
 *	@author		Nahum Budin
 *	@date		9-Apr-2026
 *	@version	1.1
 *
 *	@brief		Analog Synthesizer Band Equalizer control dialog
 *
 *	@History:
 *
 *		Version 1.0	22-Aug-2024
 *
 */

#pragma once

#include <QDialog>

#include "ControlWidgetsColorManager.h"

namespace Ui
{
	class Dialog_AnalogEqualizer;
}

class Dialog_AnalogEqualizer : public QDialog
{
	Q_OBJECT

  public:
	~Dialog_AnalogEqualizer();

	static Dialog_AnalogEqualizer *get_instance(QWidget *parent = 0);

	void control_box_ui_update_callback(int evnt, uint16_t val);

  public slots:
	virtual void update_gui(); // Called by a Timer
	void closeEvent(QCloseEvent *event);

  protected slots:

	void on_dialog_close();

	void on_band_equilizer_band31_slider_changed(int val);
	void on_band_equilizer_band62_slider_changed(int val);
	void on_band_equilizer_band125_slider_changed(int val);
	void on_band_equilizer_band250_slider_changed(int val);
	void on_band_equilizer_band500_slider_changed(int val);
	void on_band_equilizer_band1K_slider_changed(int val);
	void on_band_equilizer_band2K_slider_changed(int val);
	void on_band_equilizer_band4K_slider_changed(int val);
	void on_band_equilizer_band8K_slider_changed(int val);
	void on_band_equilizer_band16K_slider_changed(int val);

	void on_band_equilizer_band31_spinbox_changed(int val);
	void on_band_equilizer_band62_spinbox_changed(int val);
	void on_band_equilizer_band125_spinbox_changed(int val);
	void on_band_equilizer_band250_spinbox_changed(int val);
	void on_band_equilizer_band500_spinbox_changed(int val);
	void on_band_equilizer_band1K_spinbox_changed(int val);
	void on_band_equilizer_band2K_spinbox_changed(int val);
	void on_band_equilizer_band4K_spinbox_changed(int val);
	void on_band_equilizer_band8K_spinbox_changed(int val);
	void on_band_equilizer_band16K_spinbox_changed(int val);

	void on_band_equilizer_band_preset_changed(int val);
	void on_band_equilizer_set_all_zero_licked(bool val);

  protected:
	void timerEvent(QTimerEvent *event);

  private:
	explicit Dialog_AnalogEqualizer(QWidget *parent = 0);

	Ui::Dialog_AnalogEqualizer *ui;

	static Dialog_AnalogEqualizer *dialog_analog_equalizer_instance;

	int init_equalizer_gui();
	void init_equalizer_combboxes_and_labels();

	void set_equalizer_signals_connections();

	void start_update_timer(int interval);

	ControlWidgetsColorManager *control_widgets_color_manager;

	func_ptr_void_void_t close_event_callback_ptr;


};
