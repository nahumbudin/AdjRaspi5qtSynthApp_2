/**
 * @file		Dialog_TrainingParamsEditor.cpp
 *	@author		Nahum Budin
 *	@date		19-June-2026
 *	@version	1.0
 *
 *	@brief		Convert the selected training parameters for ML into a JSON format, enable editing and saving.
 *
 *	History:
 *
 */

#include <QMessageBox>

#include <filesystem>

#include "Dialog_TrainingParamsEditor.h"
#include "ui_Dialog_TrainingParamsEditor.h"

#include "MainWindow.h"

#include "Defs.h"

#include "CustomFileDialog.h"

QString ml_training_params_file_name;
QString json_content_to_save;

SaveMLtrainingParamsFileThread *save_ml_training_params_file_thread = nullptr;

void SaveMLtrainingParamsFileThread::run()
{
	QString result = QString("ML Training Params File Saved");


	// Save the JSON string (read the current text from the text edit and save it to the file).
	QFile file(ml_training_params_file_name);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		result = QString("Error: Could not open file for writing: %1").arg(ml_training_params_file_name);
		qDebug() << result;
		emit save_ml_training_params_file_done(result);
		return;
	}

	QTextStream out(&file);
	out << json_content_to_save; // Write the JSON string to file
	file.close();

	result = QString("ML Training Params File Saved: %1").arg(ml_training_params_file_name);
	qDebug() << result;

	emit save_ml_training_params_file_done(result);
}

Dialog_TrainingParamsEditor::Dialog_TrainingParamsEditor(
	QWidget *parent,
	std::vector<std::array<int, 8>> ml_training_params_list) : QDialog(parent),
		ui(new Ui::Dialog_TrainingParamsEditor), 
		params_list(ml_training_params_list)
{
	ui->setupUi(this);

	connect(ui->pushButton_SelectMlparams_Save,
			SIGNAL(clicked()),
			this,
			SLOT(on_save_button_clicked()));

	// Convert to JSON and display
	update_text_display();
}

Dialog_TrainingParamsEditor::~Dialog_TrainingParamsEditor()
{
	delete ui;
}

void Dialog_TrainingParamsEditor::closeEvent(QCloseEvent *event)
{
	qDebug() << "Dialog_TrainingParamsEditor closing";

	// Unregister from MainWindow's active dialogs
	//MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
	//if (mainWindow)
	//{
	//	mainWindow->unregister_active_dialog(this);
	//}

	// Accept the close event - dialog will be deleted due to WA_DeleteOnClose
	event->accept();
}

void Dialog_TrainingParamsEditor::update_text_display()
{
	QString json_string = convert_params_to_json();

	// Display in text edit
	if (ui->textEdit_SelectMLparams_List)
	{
		ui->textEdit_SelectMLparams_List->setPlainText(json_string);
	}
}

QString Dialog_TrainingParamsEditor::convert_params_to_json()
{
	QString json_string = "{\n";
	json_string += "  \"parameter_count\": " + QString::number(params_list.size()) + ",\n";
	json_string += "  \"training_parameters\": [\n";

	for (size_t i = 0; i < params_list.size(); i++)
	{
		const auto &param_info = params_list[i];

		int module = param_info[0];
		int submodule = param_info[1];
		int param = param_info[2];
		int MAX = param_info[3];
		int MIN = param_info[4];
		int max = param_info[5];
		int min = param_info[6];
		int mode = param_info[7];

		// Get names from dictionaries
		QString module_name = QString::fromStdString(MainWindow::modules_names_map[module]);
		QString submodule_name = QString::fromStdString(MainWindow::submodules_names_map[submodule]);
		QString param_name = QString::fromStdString(MainWindow::params_names_map[param]);
		QString mode_text = (mode == _ML_TRAINNING_MODE_FIXED_PARAM) ? "fixed" : "iterate";

		// Build parameter object with guaranteed order
		json_string += "    {\n";
		//json_string += "      \"index\": " + QString::number(i + 1) + ",\n";
		json_string += "      \"module\": {\n";
		json_string += "        \"id\": " + QString::number(module) + ",\n";
		json_string += "        \"name\": \"" + module_name + "\"\n";
		json_string += "      },\n";
		json_string += "      \"submodule\": {\n";
		json_string += "        \"id\": " + QString::number(submodule) + ",\n";
		json_string += "        \"name\": \"" + submodule_name + "\"\n";
		json_string += "      },\n";
		json_string += "      \"parameter\": {\n";
		json_string += "        \"id\": " + QString::number(param) + ",\n";
		json_string += "        \"name\": \"" + param_name + "\"\n";
		json_string += "      },\n";
		json_string += "      \"range\": {\n";
		json_string += "        \"MAX\": " + QString::number(MAX) + ",\n";
		json_string += "        \"MIN\": " + QString::number(MIN) + "\n";
		json_string += "      },\n";
		json_string += "      \"mode\": \"" + mode_text + "\",\n";
		json_string += "      \"iterate\": {\n";
		json_string += "        \"max\": " + QString::number(max) + ",\n";
		json_string += "        \"min\": " + QString::number(min) + "\n";
		json_string += "      }\n";
		json_string += "    }";

		// Add comma if not last element
		if (i < params_list.size() - 1)
		{
			json_string += ",";
		}
		json_string += "\n";
	}

	json_string += "  ]\n";
	json_string += "}\n";

	return json_string;
}

void Dialog_TrainingParamsEditor::on_save_button_clicked()
{
	// Get current JSON text from text edit widget (may be edited by user)
	json_content_to_save = ui->textEdit_SelectMLparams_List->toPlainText();

	if (json_content_to_save.isEmpty())
	{
		QMessageBox::warning(this, "Save ML Training Params",
							 "No content to save!");
		return;
	}
	
	QString startDir = last_ml_training_parms_directory.isEmpty() ? QString(_ML_TRAINING_PARAMS_DIR) : last_ml_training_parms_directory;

	// Use CustomFileDialog in Save mode
	CustomFileDialog dialog(this,
							tr("Save ML Training Parameters File"),
							startDir,
							tr("ML Training Parameters (*.json *.JSON);;All Files (*)"),
							Qt::black,
							CustomFileDialog::SaveMode,
							"training_save_params");

	if (dialog.exec() == QDialog::Accepted)
	{
		ml_training_params_file_name = dialog.selectedFile();

		if (!ml_training_params_file_name.isEmpty())
		{
			// Ensure .json extension
			if (!ml_training_params_file_name.endsWith(".json", Qt::CaseInsensitive))
			{
				ml_training_params_file_name += ".json";
			}

			// Check if file exists and ask for confirmation
			if (QFile::exists(ml_training_params_file_name))
			{
				QMessageBox msgBox;
				msgBox.setIcon(QMessageBox::Warning);
				msgBox.setWindowTitle("Confirm Overwrite");
				msgBox.setText(QString("File '%1' already exists.")
								   .arg(QFileInfo(ml_training_params_file_name).fileName()));
				msgBox.setInformativeText("Do you want to overwrite it?");
				msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
				msgBox.setDefaultButton(QMessageBox::Cancel);

				if (msgBox.exec() != QMessageBox::Yes)
				{
					return;
				}
			}

			// Remember the directory and file for next time
			last_ml_training_parms_directory = QFileInfo(ml_training_params_file_name).absolutePath();
			last_ml_training_parms_save_file = ml_training_params_file_name;

			// Display saving message
			std::string file_name = std::string("Now Saving: ");
			file_name += std::filesystem::path(ml_training_params_file_name.toStdString()).stem().string();
			// ui->textEdit_HammondPresetText->setText(QString::fromStdString(file_name));

			// Check if thread is still running
			if (save_ml_training_params_file_thread != nullptr &&
				!save_ml_training_params_file_thread->isFinished())
			{
				return;
			}

			// Start the save thread
			save_ml_training_params_file_thread = new SaveMLtrainingParamsFileThread();
			connect(save_ml_training_params_file_thread,
					&SaveMLtrainingParamsFileThread::finished,
					save_ml_training_params_file_thread,
					&QObject::deleteLater);
			connect(save_ml_training_params_file_thread,
					&SaveMLtrainingParamsFileThread::save_ml_training_params_file_done,
					this,
					&Dialog_TrainingParamsEditor::on_ml_training_params_file_saved);
			// Reset pointer when thread is destroyed
			connect(save_ml_training_params_file_thread,
					&QObject::destroyed,
					[]() { save_ml_training_params_file_thread = nullptr; });

			save_ml_training_params_file_thread->start();
		}
	}
}

void Dialog_TrainingParamsEditor::on_ml_training_params_file_saved(const QString &s)
{
	
}

void Dialog_TrainingParamsEditor::on_delete_button_clicked()
{
	
}
