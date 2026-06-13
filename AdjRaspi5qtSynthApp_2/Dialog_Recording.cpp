/**
 * @file		Dialog_Recording
 *	@author		Nahum Budin
 *	@date		12-Jun-2026
 *	@version	1.0
 *					1. 1st. version
 *
 *	@brief		Modular Synthesizer MP3 Files Recording Control
 *
 *	@History:
 *
 */

#include <filesystem>

#include <QMessageBox>
#include <QTimer>

#include "Dialog_Recording.h"
#include "ui_Dialog_Recording.h"

#include "libAdjRaspi5SynthAPI.h"
#include "Defs.h"
#include "CustomFileDialog.h"

Dialog_Recording *Dialog_Recording::dialog_recording_instance = NULL;

static QString recording_file_name = "";

Dialog_Recording::Dialog_Recording(QWidget *parent)
	: QDialog(parent), ui(new Ui::Dialog_Recording)
{
	ui->setupUi(this);
	dialog_recording_instance = this;

	// Prevent dialog from being deleted when closed - only hide it
	setAttribute(Qt::WA_DeleteOnClose, false);

	// Set fixed size - prevents resizing
	setFixedSize(size());

	this->setFocus(Qt::ActiveWindowFocusReason);

	connect(ui->pushButton_StartRecording,
			SIGNAL(clicked()),
			this,
			SLOT(on_start_recording_button_clicked()));

	connect(ui->pushButton_StopRecording,
			SIGNAL(clicked()),
			this,
			SLOT(on_stop_recording_button_clicked()));

	connect(ui->comboBox_RecordingMode,
			SIGNAL(currentIndexChanged(int)),
			this,
			SLOT(on_recording_mode_combo_changed(int)));

	ui->pushButton_StartRecording->setFrameColor(_CONTROLS_COLOR_RED);
	ui->pushButton_StartRecording->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);

	ui->pushButton_StopRecording->setFrameColor(_CONTROLS_COLOR_BLACK);
	ui->pushButton_StopRecording->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);

	ui->checkBox_RecordingON->setLedStyle(true);
	ui->checkBox_RecordingON->setReadOnly(true);
	ui->checkBox_RecordingON->setLedOnColor(_CONTROLS_COLOR_RED);
	ui->checkBox_RecordingON->setLedOffColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_RecordingON->setFrameColor(_CONTROLS_COLOR_GRAY);

	if (string_recording_modes_list.size() == 0)
	{
		string_recording_modes_list.append("Stereo");
		string_recording_modes_list.append("Mono L+R");
		string_recording_modes_list.append("Left");
		string_recording_modes_list.append("Right");
	}

	ui->comboBox_RecordingMode->blockSignals(true);
	ui->comboBox_RecordingMode->setTextAlignment(Qt::AlignCenter);
	ui->comboBox_RecordingMode->addItems(string_recording_modes_list);
	ui->comboBox_RecordingMode->setBackgroundColor(_CONTROLS_COLOR_DARK_GRAY);
	ui->comboBox_RecordingMode->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->comboBox_RecordingMode->setFrameWidth(2);
	ui->comboBox_RecordingMode->setCurrentIndex(_RECORDING_MODE_STEREO);
	ui->comboBox_RecordingMode->blockSignals(false);

	start_update_timer(1000); // Update GUI every second to reflect recording time.
}

Dialog_Recording::~Dialog_Recording()
{
	dialog_recording_instance = NULL;
	delete ui;
}

Dialog_Recording *Dialog_Recording::get_instance(QWidget *parent)
{
	if (dialog_recording_instance == NULL)
	{
		dialog_recording_instance = new Dialog_Recording(parent);
	}
	return dialog_recording_instance		;
}

void Dialog_Recording::closeEvent(QCloseEvent *event)
{
	hide();
}

void Dialog_Recording::on_start_recording_button_clicked()
{
	QString startDir = last_recording_directory.isEmpty() ? QString(_RECORDINGS_MP3_FILES_DEFAULT_DIR) : last_recording_directory;

	CustomFileDialog dialog(this,
							tr("Select Recording MP3 File"),
							startDir,
							tr("MP3 Files (*.mp3);;All Files (*)"),
							Qt::black,
							CustomFileDialog::SaveMode);

	if (dialog.exec() == QDialog::Accepted)
	{
		recording_file_name = dialog.selectedFile();

		if (!recording_file_name.isEmpty())
		{
			// Ensure .mp3 extension
			if (!recording_file_name.endsWith(".mp3", Qt::CaseInsensitive))
			{
				recording_file_name += ".mp3";
			}

			// Check if file exists and ask for confirmation
			if (QFile::exists(recording_file_name))
			{
				QMessageBox msgBox;
				msgBox.setIcon(QMessageBox::Warning);
				msgBox.setWindowTitle("Confirm Overwrite");
				msgBox.setText(QString("File '%1' already exists.")
								   .arg(QFileInfo(recording_file_name).fileName()));
				msgBox.setInformativeText("Do you want to overwrite it?");
				msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
				msgBox.setDefaultButton(QMessageBox::Cancel);

				if (msgBox.exec() != QMessageBox::Yes)
				{
					return;
				}
			}

			// Remember the directory and file for next time
			last_recording_directory = QFileInfo(recording_file_name).absolutePath();
			last_recording_file_name = recording_file_name;

			// Display file name
			std::string file_name;
			file_name = std::filesystem::path(recording_file_name.toStdString()).stem();

			ui->textEdit_RecordingFile->setText(QString::fromStdString(file_name));

			mod_synth_start_mp3_recording(recording_mode,
										  recording_file_name.toStdString().c_str(),
										  192, 44100);

			recording_time_seconds = 0;

			ui->checkBox_RecordingON->setChecked(true);
		}
	}
}

void Dialog_Recording::on_stop_recording_button_clicked()
{
	mod_synth_stop_mp3_recording();
	ui->checkBox_RecordingON->setChecked(false);
}

void Dialog_Recording::on_recording_mode_combo_changed(int val)
{
	if (val > _RECORDING_MODE_RIGHT || val < _RECORDING_MODE_STEREO)
	{
		return;
	}
	
	recording_mode = val;
}

void Dialog_Recording::start_update_timer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
	timer->start(interval);
}

void Dialog_Recording::timerEvent()
{
	update_recording_time_display();
}

void Dialog_Recording::update_recording_time_display()
{
	if (ui->checkBox_RecordingON->isChecked())
	{
		recording_time_seconds++;
		int minutes = recording_time_seconds / 60;
		int seconds = recording_time_seconds % 60;
		ui->textEdit_RecordingTime->setText(QString::asprintf("%02d:%02d", minutes, seconds));
	}
}
