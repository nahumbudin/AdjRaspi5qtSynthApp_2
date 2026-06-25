/**
 * @file		Dialog_TrainingParamsEditor.h
 *	@author		Nahum Budin
 *	@date		19-June-2026
 *	@version	1.0
 *
 *	@brief		Convert the selected training parameters for ML into a JSON format, enable editing and saving.
 *
 *	History:
 *
 */

#pragma once

#include <QDialog>
#include <QThread>

#include <vector>
#include <array>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui
{
	class Dialog_TrainingParamsEditor;
}

class Dialog_TrainingParamsEditor : public QDialog
{
	Q_OBJECT
  public:
	explicit Dialog_TrainingParamsEditor(
		QWidget *parent = nullptr,
		std::vector<std::array<int, 8>> ml_training_params_list = std::vector<std::array<int, 8>>());

	~Dialog_TrainingParamsEditor();

	void update_text_display();
	QString convert_params_to_json();

  protected:
	void closeEvent(QCloseEvent *event) override;

  private slots:
	void on_save_button_clicked();
	void on_delete_button_clicked();
	void on_ml_training_params_file_saved(const QString &s);

  private:
	Ui::Dialog_TrainingParamsEditor *ui;

	std::vector<std::array<int, 8>> params_list;

	QString last_ml_training_parms_directory = "";
	QString last_ml_training_parms_load_file = "";
	QString last_ml_training_parms_save_file = "";
};

class SaveMLtrainingParamsFileThread : public QThread
{
	Q_OBJECT
	void run();

  signals:
	void save_ml_training_params_file_done(const QString &s);
};