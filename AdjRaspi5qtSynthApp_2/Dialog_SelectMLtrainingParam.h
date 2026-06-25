/**
 * @file		Dialog_SelectMLtrainingParam.cpp
 *	@author		Nahum Budin
 *	@date		19-June-2026
 *	@version	1.0
 *
 *	@brief		Hndle the widgets selection for ML training in the main window.
 *				When enabled, clicking on a widget will open this dialog to select the parameter for ML training.
 *
 *	History:
 *
 */

#pragma once

#include <QDialog>

namespace Ui
{
	class Dialog_SelectMLtrainingParam;
}

class Dialog_SelectMLtrainingParam : public QDialog
{
	Q_OBJECT
  public:
	Dialog_SelectMLtrainingParam(
		QWidget *parent = 0,
		QString module_name = "Module",
		QString submodule_name = "Submodule",
		QString param_name = "Parameter",
		QString MAX = "0",
		QString MIN = "0",
		int max = 0,
		int min = 0,
		int mode = 0,
		int type = 0,
		QStringList max_str_list = QStringList(),
		QStringList min_str_list = QStringList(),
		std::vector<std::array<int, 8>> ml_training_params_list = std::vector<std::array<int, 8>>());
	
	~Dialog_SelectMLtrainingParam();

	void update_ml_params_list_display();

  private slots:
	void on_max_dial_val_changed(int value);
	void on_min_dial_val_changed(int value);

	void on_max_slider_val_changed(int value);
	void on_min_slider_val_changed(int value);

	void on_max_combobox_val_changed(int value);
	void on_min_combobox_val_changed(int value);

	void on_max_checkbox_val_toggled(bool checked);

	void on_iterate_mode_toggled(bool checked);

	void on_add_button_clicked();


  private:
	Ui::Dialog_SelectMLtrainingParam *ui;

	bool do_iterate = false;

	int max_value;
	int min_value;

	QString last_ml_training_parms_directory = "";
	QString last_ml_training_parms_load_file = "";
	QString last_ml_training_parms_save_file = "";

};

