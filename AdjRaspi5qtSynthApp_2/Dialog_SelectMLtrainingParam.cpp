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

#include <QString>
#include "Dialog_SelectMLtrainingParam.h"
#include "ui_Dialog_SelectMLtrainingParam.h"
#include "MainWindow.h"

#include "defines.h"

Dialog_SelectMLtrainingParam::Dialog_SelectMLtrainingParam(
	QWidget *parent,
	QString module_name,
	QString submodule_name,
	QString param_name,
	QString MAX,
	QString MIN,
	int max,
	int min,
	int mode,
	int type,
	QStringList max_str_list,
	QStringList min_str_list,
	std::vector<std::array<int, 8>> ml_training_params_list) : QDialog(parent),
				
	ui(new Ui::Dialog_SelectMLtrainingParam)
{
	ui->setupUi(this);

	max_value = max;
	min_value = min;

	ui->lineEdit_SelectMlparams_Module->setText(module_name);
	ui->lineEdit_SelectMlparams_Submodule->setText(submodule_name);
	ui->lineEdit_SelectMlparams_Param->setText(param_name);
	ui->lineEdit_SelectMlparams_MAXparamVal->setText(MAX);
	ui->lineEdit_SelectMlparams_MINparamVal->setText(MIN);

	if (type == _WIDGET_TYPE_SLIDER)
	{
		ui->comboBox_SelectMlparams_MaxIterationsVal->setEnabled(false);
		ui->comboBox_SelectMlparams_MaxIterationsVal->setVisible(false);
		ui->comboBox_SelectMlparams_MinIterationsVal->setEnabled(false);
		ui->comboBox_SelectMlparams_MinIterationsVal->setVisible(false);

		ui->dial_SelectMlparams_MaxIterationsVal->setEnabled(false);
		ui->dial_SelectMlparams_MaxIterationsVal->setVisible(false);
		ui->dial_SelectMlparams_MinIterationsVal->setEnabled(false);
		ui->dial_SelectMlparams_MinIterationsVal->setVisible(false);

		ui->horizontalSlider_SelectMlparams_MaxIterationsVal->setEnabled(true);
		ui->horizontalSlider_SelectMlparams_MaxIterationsVal->setVisible(true);
		ui->horizontalSlider_SelectMlparams_MaxIterationsVal->setRange(min, max);
		ui->horizontalSlider_SelectMlparams_MaxIterationsVal->setValue(max);

		ui->horizontalSlider_SelectMlparams_MinIterationsVal->setEnabled(true);
		ui->horizontalSlider_SelectMlparams_MinIterationsVal->setVisible(true);
		ui->horizontalSlider_SelectMlparams_MinIterationsVal->setRange(min, max);
		ui->horizontalSlider_SelectMlparams_MinIterationsVal->setValue(min);

		ui->lineEdit_SelectMlparams_MaxIterationsVal->setEnabled(true);
		ui->lineEdit_SelectMlparams_MaxIterationsVal->setVisible(true);
		ui->lineEdit_SelectMlparams_MinIterationsVal->setEnabled(true);
		ui->lineEdit_SelectMlparams_MinIterationsVal->setVisible(true);

		ui->lineEdit_SelectMlparams_MaxIterationsVal->setText(QString::number(max));
		ui->lineEdit_SelectMlparams_MinIterationsVal->setText(QString::number(min));

		ui->checkBox_SelectMlparams_MaxIterationsVal->setEnabled(false);
		ui->checkBox_SelectMlparams_MaxIterationsVal->setVisible(false);

		ui->checkBox_SelectMlparams_MinIterationsVal->setEnabled(false);
		ui->checkBox_SelectMlparams_MinIterationsVal->setVisible(false);
	}
	else if (type == _WIDGET_TYPE_DIAL)
	{
		ui->comboBox_SelectMlparams_MaxIterationsVal->setEnabled(false);
		ui->comboBox_SelectMlparams_MaxIterationsVal->setVisible(false);
		ui->comboBox_SelectMlparams_MinIterationsVal->setEnabled(false);
		ui->comboBox_SelectMlparams_MinIterationsVal->setVisible(false);

		ui->horizontalSlider_SelectMlparams_MaxIterationsVal->setEnabled(false);
		ui->horizontalSlider_SelectMlparams_MaxIterationsVal->setVisible(false);
		ui->horizontalSlider_SelectMlparams_MinIterationsVal->setEnabled(false);
		ui->horizontalSlider_SelectMlparams_MinIterationsVal->setVisible(false);

		ui->dial_SelectMlparams_MaxIterationsVal->setEnabled(true);
		ui->dial_SelectMlparams_MaxIterationsVal->setVisible(true);
		ui->dial_SelectMlparams_MaxIterationsVal->setRange(min, max);
		ui->dial_SelectMlparams_MaxIterationsVal->setValue(max);

		ui->dial_SelectMlparams_MinIterationsVal->setEnabled(true);
		ui->dial_SelectMlparams_MinIterationsVal->setVisible(true);
		ui->dial_SelectMlparams_MinIterationsVal->setRange(min, max);
		ui->dial_SelectMlparams_MinIterationsVal->setValue(min);

		ui->lineEdit_SelectMlparams_MaxIterationsVal->setEnabled(true);
		ui->lineEdit_SelectMlparams_MaxIterationsVal->setVisible(true);
		ui->lineEdit_SelectMlparams_MinIterationsVal->setEnabled(true);
		ui->lineEdit_SelectMlparams_MinIterationsVal->setVisible(true);

		ui->lineEdit_SelectMlparams_MaxIterationsVal->setText(QString::number(max));
		ui->lineEdit_SelectMlparams_MinIterationsVal->setText(QString::number(min));

		ui->checkBox_SelectMlparams_MaxIterationsVal->setEnabled(false);
		ui->checkBox_SelectMlparams_MaxIterationsVal->setVisible(false);

		ui->checkBox_SelectMlparams_MinIterationsVal->setEnabled(false);
		ui->checkBox_SelectMlparams_MinIterationsVal->setVisible(false);
	}
	else if (type == _WIDGET_TYPE_COMBOBOX)
	{
		// Combbox requires special handling to get the actual value range
		// and how to sedlect the min and max values for ML training.
		ui->horizontalSlider_SelectMlparams_MaxIterationsVal->setEnabled(false);
		ui->horizontalSlider_SelectMlparams_MaxIterationsVal->setVisible(false);
		ui->horizontalSlider_SelectMlparams_MinIterationsVal->setEnabled(false);
		ui->horizontalSlider_SelectMlparams_MinIterationsVal->setVisible(false);

		ui->dial_SelectMlparams_MaxIterationsVal->setEnabled(false);
		ui->dial_SelectMlparams_MaxIterationsVal->setVisible(false);
		ui->dial_SelectMlparams_MinIterationsVal->setEnabled(false);
		ui->dial_SelectMlparams_MinIterationsVal->setVisible(false);

		ui->lineEdit_SelectMlparams_MaxIterationsVal->setEnabled(false);
		ui->lineEdit_SelectMlparams_MaxIterationsVal->setVisible(false);
		ui->lineEdit_SelectMlparams_MinIterationsVal->setEnabled(false);
		ui->lineEdit_SelectMlparams_MinIterationsVal->setVisible(false);

		ui->comboBox_SelectMlparams_MaxIterationsVal->blockSignals(true);
		ui->comboBox_SelectMlparams_MaxIterationsVal->setEnabled(true);
		ui->comboBox_SelectMlparams_MaxIterationsVal->setVisible(true);
		ui->comboBox_SelectMlparams_MaxIterationsVal->addItems(max_str_list);
		ui->comboBox_SelectMlparams_MaxIterationsVal->setCurrentIndex(max_str_list.indexOf(MAX));
		ui->comboBox_SelectMlparams_MaxIterationsVal->blockSignals(false);

		ui->comboBox_SelectMlparams_MinIterationsVal->blockSignals(true);
		ui->comboBox_SelectMlparams_MinIterationsVal->setEnabled(true);
		ui->comboBox_SelectMlparams_MinIterationsVal->setVisible(true);
		ui->comboBox_SelectMlparams_MinIterationsVal->addItems(min_str_list);
		ui->comboBox_SelectMlparams_MinIterationsVal->setCurrentIndex(min_str_list.indexOf(MIN));
		ui->comboBox_SelectMlparams_MinIterationsVal->blockSignals(false);

		ui->checkBox_SelectMlparams_MaxIterationsVal->setEnabled(false);
		ui->checkBox_SelectMlparams_MaxIterationsVal->setVisible(false);

		ui->checkBox_SelectMlparams_MinIterationsVal->setEnabled(false);
		ui->checkBox_SelectMlparams_MinIterationsVal->setVisible(false);
		
	}
	else if (type == _WIDGET_TYPE_CHECKBOX)
	{
		ui->checkBox_SelectMlparams_MaxIterationsVal->setEnabled(true);
		ui->checkBox_SelectMlparams_MaxIterationsVal->setVisible(true);

		ui->checkBox_SelectMlparams_MinIterationsVal->setEnabled(true);
		ui->checkBox_SelectMlparams_MinIterationsVal->setVisible(true);
		
		ui->comboBox_SelectMlparams_MaxIterationsVal->setEnabled(false);
		ui->comboBox_SelectMlparams_MaxIterationsVal->setVisible(false);

		ui->horizontalSlider_SelectMlparams_MaxIterationsVal->setEnabled(false);
		ui->horizontalSlider_SelectMlparams_MaxIterationsVal->setVisible(false);
		ui->horizontalSlider_SelectMlparams_MinIterationsVal->setEnabled(false);
		ui->horizontalSlider_SelectMlparams_MinIterationsVal->setVisible(false);

		ui->dial_SelectMlparams_MaxIterationsVal->setEnabled(false);
		ui->dial_SelectMlparams_MaxIterationsVal->setVisible(false);
		ui->dial_SelectMlparams_MinIterationsVal->setEnabled(false);
		ui->dial_SelectMlparams_MinIterationsVal->setVisible(false);

		ui->lineEdit_SelectMlparams_MaxIterationsVal->setEnabled(false);
		ui->lineEdit_SelectMlparams_MaxIterationsVal->setVisible(false);
		
		ui->lineEdit_SelectMlparams_MinIterationsVal->setEnabled(false);
		ui->lineEdit_SelectMlparams_MinIterationsVal->setVisible(false);

		ui->comboBox_SelectMlparams_MaxIterationsVal->setEnabled(false);
		ui->comboBox_SelectMlparams_MaxIterationsVal->setVisible(false);

		ui->comboBox_SelectMlparams_MinIterationsVal->setEnabled(false);
		ui->comboBox_SelectMlparams_MinIterationsVal->setVisible(false);
		
		

		max_value = 0; // Default for checkbox is 0 (unchecked) - Disabled
	}
	else if (type == _WIDGET_TYPE_BUTTON)
	{
	}

	connect(ui->comboBox_SelectMlparams_MaxIterationsVal,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_max_combobox_val_changed(int)));

	connect(ui->comboBox_SelectMlparams_MinIterationsVal,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_min_combobox_val_changed(int)));

	connect(ui->dial_SelectMlparams_MaxIterationsVal,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_max_dial_val_changed(int)));

	connect(ui->dial_SelectMlparams_MinIterationsVal,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_min_dial_val_changed(int)));

	connect(ui->horizontalSlider_SelectMlparams_MaxIterationsVal,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_max_slider_val_changed(int)));

	connect(ui->horizontalSlider_SelectMlparams_MinIterationsVal,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_min_slider_val_changed(int)));

	connect(ui->pushButton_SelectMlparams_Add,
			SIGNAL(clicked()),
			this,
			SLOT(on_add_button_clicked()));

	connect(ui->pushButton_SelectMlparams_Cancell,
			SIGNAL(clicked()),
			this,
			SLOT(on_cancel_button_clicked()));

	connect(ui->checkBox_SelectMlparams_MaxIterationsVal,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_max_checkbox_val_toggled(bool)));

	connect(ui->checkBox_SelectMlparams_MinIterationsVal,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_min_checkbox_val_toggled(bool)));

	update_ml_params_list_display();

	/* Set focus on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

Dialog_SelectMLtrainingParam::~Dialog_SelectMLtrainingParam()
{
	delete ui;
}

void Dialog_SelectMLtrainingParam::update_ml_params_list_display()
{
	QString html_text = "<html><body>";

	for (size_t i = 0; i < MainWindow::ml_training_params_list.size(); i++)
	{
		const auto &param_info = MainWindow::ml_training_params_list[i];

		int module = param_info[0];
		int submodule = param_info[1];
		int param = param_info[2];
		int MAX = param_info[3];
		int MIN = param_info[4];
		int max = param_info[5];
		int min = param_info[6];
		int mode = param_info[7];

		QString module_name = QString::fromStdString(MainWindow::modules_names_map[module]);
		QString submodule_name = QString::fromStdString(MainWindow::submodules_names_map[submodule]);
		QString param_name = QString::fromStdString(MainWindow::params_names_map[param]);
		QString mode_text = (mode == _ML_TRAINNING_MODE_FIXED_PARAM) ? "Fixed" : "Iterate";

		QString line = QString(
						   "<p style='margin:5px;'>"
						   "<span style='color:cyan;'>%1.</span> "
						   "<span style='color:lightblue;'>%2</span> &gt; "
						   "<span style='color:lightgreen;'>%3</span> &gt; "
						   "<span style='color:orange;'>%4</span> | "
						   "<span style='color:purple;'><b>Range: [%5-%6]</b></span> "
						   "<span style='color:white;'><b>Iterate: [%7-%8]</b></span> | "
						   "Mode: %9"
						   "</p>")
						   .arg(i + 1)
						   .arg(module_name)
						   .arg(submodule_name)
						   .arg(param_name)
						   .arg(MIN)
						   .arg(MAX)
						   .arg(min)
						   .arg(max)
						   .arg(mode_text);

		html_text += line;
	}

	html_text += "</body></html>";

	ui->textEdit_SelectMLparams_List->setHtml(html_text);
}


void Dialog_SelectMLtrainingParam::on_max_dial_val_changed(int value)
{
	if (value > min_value)
	{
		max_value = value;
		ui->dial_SelectMlparams_MaxIterationsVal->setValue(max_value);
		ui->lineEdit_SelectMlparams_MaxIterationsVal->setText(QString::number(max_value));
		
	}
	else if (value <= min_value)
	{
		max_value = min_value;
		ui->dial_SelectMlparams_MaxIterationsVal->setValue(max_value);
		ui->lineEdit_SelectMlparams_MaxIterationsVal->setText(QString::number(max_value));
	}
}

void Dialog_SelectMLtrainingParam::on_min_dial_val_changed(int value)
{
	if (value < max_value)
	{
		min_value = value;
		ui->dial_SelectMlparams_MinIterationsVal->setValue(min_value);
		ui->lineEdit_SelectMlparams_MinIterationsVal->setText(QString::number(min_value));
	}
	else if (value >= max_value)
	{
		min_value = max_value;
		ui->dial_SelectMlparams_MinIterationsVal->setValue(min_value);
		ui->lineEdit_SelectMlparams_MinIterationsVal->setText(QString::number(min_value));
	}
}

void Dialog_SelectMLtrainingParam::on_max_slider_val_changed(int value)
{
	if (value > min_value)
	{
		max_value = value;
		ui->horizontalSlider_SelectMlparams_MaxIterationsVal->setValue(max_value);
		ui->lineEdit_SelectMlparams_MaxIterationsVal->setText(QString::number(max_value));
	}
	else if (value <= min_value)
	{
		max_value = min_value;
		ui->horizontalSlider_SelectMlparams_MaxIterationsVal->setValue(max_value);
		ui->lineEdit_SelectMlparams_MaxIterationsVal->setText(QString::number(max_value));
	}
}

void Dialog_SelectMLtrainingParam::on_min_slider_val_changed(int value)
{
	if (value < max_value)
	{
		min_value = value;
		ui->horizontalSlider_SelectMlparams_MinIterationsVal->setValue(min_value);
		ui->lineEdit_SelectMlparams_MinIterationsVal->setText(QString::number(min_value));
	}
	else if (value >= max_value)
	{
		min_value = max_value;
		ui->horizontalSlider_SelectMlparams_MinIterationsVal->setValue(min_value);
		ui->lineEdit_SelectMlparams_MinIterationsVal->setText(QString::number(min_value));
	}
}

void Dialog_SelectMLtrainingParam::on_max_combobox_val_changed(int value)
{
	if (value > min_value)
	{
		max_value = value;
	}
	else if (value <= min_value)
	{
		max_value = min_value;
	}
}

void Dialog_SelectMLtrainingParam::on_min_combobox_val_changed(int value)
{
	if (value < max_value)
	{
		min_value = value;
		ui->comboBox_SelectMlparams_MinIterationsVal->setCurrentIndex(min_value);
	}
	else if (value >= max_value)
	{
		min_value = max_value;
		ui->comboBox_SelectMlparams_MinIterationsVal->setCurrentIndex(min_value);
	}
}

void Dialog_SelectMLtrainingParam::on_max_checkbox_val_toggled(bool checked)
{
	if (checked)
	{
		max_value = 1;
		ui->checkBox_SelectMlparams_MaxIterationsVal->setChecked(true);
	}
	else
	{
		max_value = 0;
		ui->checkBox_SelectMlparams_MaxIterationsVal->setChecked(false);
	}
}

void Dialog_SelectMLtrainingParam::on_min_checkbox_val_toggled(bool checked)
{
	if (checked)
	{
		min_value = 1;
		ui->checkBox_SelectMlparams_MaxIterationsVal->setChecked(true);
	}
	else
	{
		min_value = 0;
		ui->checkBox_SelectMlparams_MinIterationsVal->setChecked(false);
	}
}

void Dialog_SelectMLtrainingParam::on_add_button_clicked()
{
	MainWindow::param_info[5] = max_value;
	MainWindow::param_info[6] = min_value;

	if (max_value > min_value)
	{
		MainWindow::param_info[7] = _ML_TRAINNING_MODE_ITERATIVE_PARAM;
	}
	else
	{
		// If max_value is equal to min_value, set the mode to fixed parameter
		MainWindow::param_info[7] = _ML_TRAINNING_MODE_FIXED_PARAM;
	}

	MainWindow::add_new_ml_iterare_parm_min_max_values();

	this->close();
}

void Dialog_SelectMLtrainingParam::on_cancel_button_clicked()
{
	this->close();
}
