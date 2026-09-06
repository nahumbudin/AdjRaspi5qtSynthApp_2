/**
 * @file		Dialog_MidiPlayer.h
 *	@author		Nahum Budin
 *	@date		2-Apr-2026
 *	@version	2.0
 *					1. Custom icons for the control buttons.
 *					2. Added support for loopback playing control.
 *					3. Added support for playback volume and speed control.
 *					4. Added support for retrieving midi file meta data.
 *
 *	@brief		Used for playing MIDI files
 *
 *	History:
 *			ver 1.0 11-Aug-2024 Initial version
 *
 */

#include <filesystem>

#include <QObject>
#include <QFileDialog>
#include <QTimer>
#include <QMoveEvent>
#include <QStyle>
#include <QPainter>


#include "MainWindow.h"
#include "Dialog_MidiPlayer.h"
#include "ui_Dialog_MidiPlayer.h"
#include "midi.h"
#include "utils.h"
#include "CustomFileDialog.h"

QString midi_file_name;
OpenMidiPlayerFileThread *open_file_thread = nullptr;;

int playback_progres_percentegas = 0;

int song_total_playing_time_minutes = 0;
int song_total_playing_time_seconds = 0;
int song_playing_time_minutes = 0;
int song_playing_time_seconds = 0;
int song_remaining_playing_time_minutes = 0;
int song_remaining_playing_time_seconds = 0;

int active_scale_index = 0;

std::vector<simple_scale_segment_t> simple_scale_segments = {};

QString active_scale_text = "Unknown Scale";

void midi_player_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	Dialog_MidiPlayer::get_instance()->control_box_ui_update_callback(evnt, val);
}


void update_ui_progress_percentages(int progress)
{	
	if (progress < 0)
	{
		progress = 0;
	}
	else if (progress > 100)
	{
		progress = 100;
	}
	
	playback_progres_percentegas = progress;
}

void OpenMidiPlayerFileThread::run() 
{		
	QString result = QString("File loaded");
	mod_synth_open_midi_file(midi_file_name.toStdString());
	emit resultReady(result);
}

void update_ui_total_song_playing_time(int min, int sec)
{
	song_total_playing_time_minutes = min;
	song_total_playing_time_seconds = sec;
}

void update_ui_active_scale_segment(int min, int sec)
{
	// Update the UI with the active scale segment information
	if (simple_scale_segments.empty() || active_scale_index >= simple_scale_segments.size())
	{
		return;
	}

	// Build scale list with active segment in red
	std::string scales_display = "";
	char buffer[16];

	for (size_t i = 0; i < simple_scale_segments.size(); i++)
	{
		if (i == active_scale_index)
		{
			// Active segment in red
			scales_display += "<span style='color: red; font-weight: bold;'>" +
							  simple_scale_segments[i].segment_scale +
							  "</span>";
		}
		else
		{
			// Other segments in white
			scales_display += "<span style='color: white;'>" +
							  simple_scale_segments[i].segment_scale +
							  "</span>";
		}

		// Add separator between segments
		if (i < simple_scale_segments.size() - 1)
		{
			scales_display += "  |  ";
		}
	}

	// Add confidence only for active segment
	std::snprintf(buffer, sizeof(buffer), "%.2f", simple_scale_segments[active_scale_index].confidence);
	scales_display += "  | Confidence: " + std::string(buffer) + "%";

	active_scale_text = QString::fromStdString(scales_display);

	if ((active_scale_index < simple_scale_segments.size() - 1) && // Not the last segment
		(min * 60.0 + sec + 1.0 >= simple_scale_segments[active_scale_index + 1].segment_start_time_seconds))
	{
		active_scale_index++;
	}	
}

void update_ui_song_playing_time(int min, int sec)
{
	song_playing_time_minutes = min;
	song_playing_time_seconds = sec;

	update_ui_active_scale_segment(min, sec);
}

void update_ui_song_remaining_playing_time(int min, int sec)
{
	song_remaining_playing_time_minutes = min;
	song_remaining_playing_time_seconds = sec;
}

Dialog_MidiPlayer *Dialog_MidiPlayer::dialog_adj_midi_player_instance = NULL;

static QIcon recolorIcon(const QIcon &icon, const QColor &color, const QSize &size)
{
	QPixmap pixmap = icon.pixmap(size);
	QPixmap colored(pixmap.size());
	colored.fill(Qt::transparent);

	QPainter painter(&colored);
	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.drawPixmap(0, 0, pixmap);
	painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
	painter.fillRect(colored.rect(), color);
	painter.end();

	return QIcon(colored);
}

Dialog_MidiPlayer::Dialog_MidiPlayer(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::Dialog_MidiPlayer)
{
	ui->setupUi(this);
	dialog_adj_midi_player_instance = this;

	// Prevent dialog from being deleted when closed - only hide it
	setAttribute(Qt::WA_DeleteOnClose, false);

	// ADD ICONS TO BUTTONS
	QStyle *style = QApplication::style();
	QSize iconSize(32, 32);

	// Open File button - Gray icon
	ui->pushButton_MidiPlayerOpenFile->setIcon(
		recolorIcon(style->standardIcon(QStyle::SP_DialogOpenButton), Qt::darkGray, iconSize));
	ui->pushButton_MidiPlayerOpenFile->setIconSize(iconSize);
	ui->pushButton_MidiPlayerOpenFile->setFrameColor(_CONTROLS_COLOR_RED);
	ui->pushButton_MidiPlayerOpenFile->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);

	ui->pushButton_MidiPlayerBackward->setIcon(
		recolorIcon(style->standardIcon(QStyle::SP_MediaSkipBackward), Qt::darkGray, iconSize));
	ui->pushButton_MidiPlayerBackward->setIconSize(iconSize);
	ui->pushButton_MidiPlayerBackward->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->pushButton_MidiPlayerBackward->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);
	
	ui->pushButton_MidiPlayerPlay->setIcon(
		recolorIcon(style->standardIcon(QStyle::SP_MediaPlay), Qt::darkGray, iconSize));
	ui->pushButton_MidiPlayerPlay->setIconSize(QSize(32, 32));
	ui->pushButton_MidiPlayerPlay->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->pushButton_MidiPlayerPlay->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);

	ui->pushButton_MidiPlayerPause->setIcon(
		recolorIcon(style->standardIcon(QStyle::SP_MediaPause), Qt::darkGray, iconSize));
	ui->pushButton_MidiPlayerPause->setIconSize(QSize(32, 32));
	ui->pushButton_MidiPlayerPause->setFrameColor(_CONTROLS_COLOR_GREEN);
	ui->pushButton_MidiPlayerPause->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);

	ui->pushButton_MidiPlayerForward->setIcon(
		recolorIcon(style->standardIcon(QStyle::SP_MediaSeekForward), Qt::darkGray, iconSize));
	ui->pushButton_MidiPlayerForward->setIconSize(iconSize);
	ui->pushButton_MidiPlayerForward->setFrameColor(_CONTROLS_COLOR_WHITE);
	ui->pushButton_MidiPlayerForward->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);
	
	

	ui->pushButton_MidiPlayerStop->setIcon(
		recolorIcon(style->standardIcon(QStyle::SP_MediaStop), Qt::darkGray, iconSize));
	ui->pushButton_MidiPlayerStop->setIconSize(QSize(32, 32));
	ui->pushButton_MidiPlayerStop->setFrameColor(_CONTROLS_COLOR_YELLOW);
	ui->pushButton_MidiPlayerStop->setBackgroundColor(_CONTROLS_COLOR_VERY_DARK_GRAY);

	ui->verticalSlider_MidiPlayer_Volume->setFrameColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_MidiPlayer_Volume->setHandleColor(_CONTROLS_COLOR_PURPLE);
	ui->verticalSlider_MidiPlayer_Volume->setProgressColor(_CONTROLS_COLOR_PURPLE);

	ui->verticalSlider_MidiPlayer_Volume->setFrameColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_MidiPlayer_Volume->setHandleColor(_CONTROLS_COLOR_BLUE);
	ui->verticalSlider_MidiPlayer_Volume->setProgressColor(_CONTROLS_COLOR_BLUE);

	ui->checkBox_MidiPlayerLoopback->setLedStyle(true);
	ui->checkBox_MidiPlayerLoopback->setLedOnColor(_CONTROLS_COLOR_YELLOW);
	ui->checkBox_MidiPlayerLoopback->setFrameColor(_CONTROLS_COLOR_GRAY);
	ui->checkBox_MidiPlayerLoopback->setBackgroundColor(_CONTROLS_COLOR_BLACK);
	ui->checkBox_MidiPlayerLoopback->setCheckBoxSize(16);
	ui->checkBox_MidiPlayerLoopback->setFrameWidth(2);

	ui->progressBar_MidiPlayerProgressPercents->setStyleSheet(
		"QProgressBar {"
		"   color: black;"					 // Text color
		"   background-color: #1e1e1e;"		 // Very dark gray" // Keeps default background
		"   border: 1px solid palette(mid);"  // Keeps default border
		"   text-align: left;"
		"}"
		"QProgressBar::chunk {"
		"   background-color: palette(highlight);" // Keeps default progress color
		"}");

	move(100, 100);
	
	this->setFocus(Qt::ActiveWindowFocusReason);
	
	ui->lineEdit_MidiPlayeFileName->setText("");

		
	close_event_callback_ptr = NULL;
	
	mod_synth_register_midi_player_potision_update_callback(&update_ui_progress_percentages);
	mod_synth_register_midi_player_total_song_playing_time_update_callback(&update_ui_total_song_playing_time);
	mod_synth_register_midi_player_song_playing_time_update_callback(&update_ui_song_playing_time);
	mod_synth_register_midi_player_song_remaining_playing_time_update_callback(&update_ui_song_remaining_playing_time);
	
	//open_file_thread = new OpenFileThread();
	//connect(open_file_thread, &OpenFileThread::finished, open_file_thread, &QObject::deleteLater);
	
	mod_synth_register_callback_control_box_event_update_ui(
		&midi_player_control_box_event_update_ui_callback_wrapper);
	
	connect(ui->pushButton_MidiPlayerOpenFile,
		SIGNAL(clicked()),
		this,
		SLOT(on_open_file_clicked()));
	
	connect(ui->pushButton_MidiPlayerPlay,
		SIGNAL(clicked()),
		this,
		SLOT(on_play_clicked()));
	
	connect(ui->pushButton_MidiPlayerPause,
		SIGNAL(clicked()),
		this,
		SLOT(on_pause_clicked()));
	
	connect(ui->pushButton_MidiPlayerStop,
		SIGNAL(clicked()),
		this,
		SLOT(on_stop_clicked()));

	connect(ui->pushButton_MidiPlayerBackward,
			SIGNAL(clicked()),
			this,
			SLOT(on_backward_clicked()));

	connect(ui->pushButton_MidiPlayerForward,
			SIGNAL(clicked()),
			this,
			SLOT(on_forward_clicked()));
	
	connect(ui->checkBox_MidiPlayerLoopback,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_enable_loopback_enable(bool)));

	connect(ui->verticalSlider_MidiPlayer_Volume,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_playback_volume_changed(int)));

	connect(ui->verticalSlider_MidiPlayer_Speed,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_playback_speed_changed(int)));

	MainWindow::get_instance()->register_active_dialog(this);

	// Register with GuiNavigator (no tabs for MIDI Players, but has frames)
	QList<QString> frame_names;
	frame_names << "Frame 1" << "Frame 2";

	GuiNavigator::get_instance()->register_dialog(
		this,
		"MIDI Player",
		nullptr,									// No tab widget
		QMap<int, QList<QString>>{{0, frame_names}} // All frames in tab 0 (no tabs)
	);
	
	// start a periodic timer after this timeout - 
	start_update_timer(200);
	
}

Dialog_MidiPlayer::~Dialog_MidiPlayer()
{
	// Disable callbacks by registering NULL during destruction
	mod_synth_register_midi_player_potision_update_callback(NULL);
	mod_synth_register_midi_player_total_song_playing_time_update_callback(NULL);
	mod_synth_register_midi_player_song_playing_time_update_callback(NULL);
	mod_synth_register_midi_player_song_remaining_playing_time_update_callback(NULL);
	mod_synth_register_callback_control_box_event_update_ui(NULL);
	
	dialog_adj_midi_player_instance = nullptr;
	delete ui;
}

Dialog_MidiPlayer *Dialog_MidiPlayer::get_instance(QWidget *parent)
{
	if (dialog_adj_midi_player_instance == NULL)
	{
		dialog_adj_midi_player_instance = new Dialog_MidiPlayer(parent);
	}
	
	dialog_adj_midi_player_instance->show();
	
	return dialog_adj_midi_player_instance;
}

void Dialog_MidiPlayer::closeEvent(QCloseEvent *event)
{
	if (close_event_callback_ptr != NULL)
	{
		close_event_callback_ptr();
	}

	// Disable callbacks by registering NULL when hiding
	mod_synth_register_midi_player_potision_update_callback(NULL);
	mod_synth_register_midi_player_total_song_playing_time_update_callback(NULL);
	mod_synth_register_midi_player_song_playing_time_update_callback(NULL);
	mod_synth_register_midi_player_song_remaining_playing_time_update_callback(NULL);
	mod_synth_register_callback_control_box_event_update_ui(NULL);

	// Unregister from GuiNavigator
	GuiNavigator::get_instance()->unregister_dialog(this);
	
	hide();

	QDialog::closeEvent(event);
}

void Dialog_MidiPlayer::showEvent(QShowEvent *event)
{
	QDialog::showEvent(event);

	// Re-register callbacks when showing dialog
	mod_synth_register_midi_player_potision_update_callback(&update_ui_progress_percentages);
	mod_synth_register_midi_player_total_song_playing_time_update_callback(&update_ui_total_song_playing_time);
	mod_synth_register_midi_player_song_playing_time_update_callback(&update_ui_song_playing_time);
	mod_synth_register_midi_player_song_remaining_playing_time_update_callback(&update_ui_song_remaining_playing_time);
	mod_synth_register_callback_control_box_event_update_ui(&midi_player_control_box_event_update_ui_callback_wrapper);
}

void Dialog_MidiPlayer::moveEvent(QMoveEvent *event) {
	QWidget::moveEvent(event); // Call the base class implementation first

	last_position = event->pos();
	printf("Playr position %i:%i\n", last_position.x(), last_position.y());
}

bool Dialog_MidiPlayer::event(QEvent *event)
{
	//printf("Event type: %i pos: %i:%i\n", event->type(), this->x(), this->y());

	return QWidget::event(event);
	

}

void Dialog_MidiPlayer::control_box_ui_update_callback(int evnt, uint16_t val)
{
	static int player_volume = 50;
	static int player_speed = 100;

	int slider_level_gap;

	if (!this->hasFocus())
	{
		return;
	}

	if (evnt == _I2C_CONTROL_ENCODER_1)
	{
		// Encoder Pushbutton Gray - Loopback
		if (val == 0x2000)
		{
			/* Only when pressed */
			// Toggle
			ui->checkBox_MidiPlayerLoopback->setChecked(!ui->checkBox_MidiPlayerLoopback->isChecked());
		}
	}
	else if (evnt == _I2C_CONTROL_ENCODER_2)
	{
		// Encoder Pushbutton Purple - Backward
		if (val == 0x2000)
		{
			/* Only when pressed */
			ui->pushButton_MidiPlayerBackward->click();
		}
	}
	else if (evnt == _I2C_CONTROL_ENCODER_3)
	{
		// Encoder Pushbutton Blue - Play
		if (val == 0x2000)
		{
			/* Only when pressed */
			ui->pushButton_MidiPlayerPlay->click();
		}
	}
	else if (evnt == _I2C_CONTROL_ENCODER_4)
	{
		// Encoder Pushbutton Green - Pause
		if (val == 0x2000)
		{
			/* Only when pressed */
			ui->pushButton_MidiPlayerPause->click();
		}
	}
	else if (evnt == _I2C_CONTROL_ENCODER_5)
	{
		// Encoder Pushbutton White - Forward
		if (val == 0x2000)
		{
			/* Only when pressed */
			ui->pushButton_MidiPlayerForward->click();
		}
	}
	else if (evnt == _I2C_CONTROL_ENCODER_6)
	{
		// Encoder Pushbutton Yellow - Stop
		if (val == 0x2000)
		{
			/* Only when pressed */
			ui->pushButton_MidiPlayerStop->click();
		}
	}
	else if (evnt == _I2C_CONTROL_ENCODER_7)
	{
		// Encoder Pushbutton Red - File
		if (val == 0x2000)
		{
			/* Only when pressed */
			ui->pushButton_MidiPlayerOpenFile->click();
		}
	}
	else if (evnt == _I2C_CONTROL_SLIDER_3)
	{
		// Slider Blue - Volume
		// Get new volume value from slider and calculate gap from current UI value
		player_volume = normalize_slider_value(val / 37, 100, 0); // 0-3700
		slider_level_gap = player_volume - ui->verticalSlider_MidiPlayer_Volume->value();						 // 0-100

		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) < ((100 - 0) / 5.0))
		{
			// Emits value changed signal.
			ui->verticalSlider_MidiPlayer_Volume->setValue(player_volume);
		}
		
	}
	else if (evnt == _I2C_CONTROL_SLIDER_4)
	{
		// Slider Green - Speed
		// Get new volume value from slider and calculate gap from current UI value
		player_speed = normalize_slider_value(val / 37, 150, 50);						  // 0-3700
		slider_level_gap = player_speed - ui->verticalSlider_MidiPlayer_Speed->value(); // 50-150

		// Change slider value only when it matches the UI slider position.
		if (abs((float)slider_level_gap) < ((150 - 50) / 5.0))
		{
			// Emits value changed signal.
			ui->verticalSlider_MidiPlayer_Speed->setValue(player_speed);
		}
	}
}

QPoint Dialog_MidiPlayer::get_last_position()
{
	return last_position;
}

void Dialog_MidiPlayer::on_dialog_close()
{
	//mod_synth_unregister_callback_control_box_event_update_ui(
	//	&fluid_control_box_event_update_ui_callback_wrapper);
	
	hide();
}

void Dialog_MidiPlayer::display_channel_utilization(midi_file_meta_data_t &meta_data)
{
	// Find maximum count for normalization
	int max_count = 0;

	for (int ch = 0; ch < 16; ch++)
	{
		if (ch != 9 && meta_data.channels_counters[ch] > max_count)
		{
			max_count = meta_data.channels_counters[ch];
		}
	}

	// Setup table - show all 16 channels, 3 rows of data
	ui->tableWidget_MidiPlayerChannels->setRowCount(3);
	ui->tableWidget_MidiPlayerChannels->setColumnCount(16); // Always show all 16 channels

	// Hide horizontal header (column headers)
	ui->tableWidget_MidiPlayerChannels->horizontalHeader()->setVisible(false);

	// Show vertical header (row headers) and set labels
	ui->tableWidget_MidiPlayerChannels->verticalHeader()->setVisible(true);
	QStringList row_headers;
	row_headers << "Channel" << "Notes" << "Usage %";
	ui->tableWidget_MidiPlayerChannels->setVerticalHeaderLabels(row_headers);

	// Populate table with all 16 channels
	for (int ch = 0; ch < 16; ch++)
	{
		// Row 0: Channel number (1-16)
		QTableWidgetItem *item_ch = new QTableWidgetItem(QString::number(ch + 1));
		item_ch->setTextAlignment(Qt::AlignCenter);

		// Highlight drums channel (Ch 10)
		if (ch == 9)
		{
			item_ch->setBackground(QBrush(QColor(255, 200, 100))); // Orange for drums
		}
		// Gray out unused channels
		else if (meta_data.channels_counters[ch] == 0)
		{
			item_ch->setBackground(QBrush(QColor(80, 80, 80)));	   // Dark gray for unused
			item_ch->setForeground(QBrush(QColor(150, 150, 150))); // Light gray text
		}

		ui->tableWidget_MidiPlayerChannels->setItem(0, ch, item_ch);

		// Row 1: Note count
		QTableWidgetItem *item_count = new QTableWidgetItem(QString::number(meta_data.channels_counters[ch]));
		item_count->setTextAlignment(Qt::AlignCenter);
		item_count->setForeground(QBrush(Qt::black)); // Black text

		if (meta_data.channels_counters[ch] == 0)
		{
			item_count->setBackground(QBrush(QColor(80, 80, 80)));
			item_count->setForeground(QBrush(QColor(150, 150, 150))); // Override to gray for unused
		}

		ui->tableWidget_MidiPlayerChannels->setItem(1, ch, item_count);

		// Row 2: Usage percentage
		int percentage = (max_count > 0) ? 
			static_cast<int>((static_cast<long long>(meta_data.channels_counters[ch]) * 100) / max_count) : 0;
		QTableWidgetItem *item_percent = new QTableWidgetItem(QString::number(percentage) + "%");
		item_percent->setTextAlignment(Qt::AlignCenter);
		item_percent->setForeground(QBrush(Qt::black)); // Black text

		// Color code by usage level
		QColor bgcolor;
		if (meta_data.channels_counters[ch] == 0)
		{
			bgcolor = QColor(80, 80, 80);								// Dark gray - unused
			item_percent->setForeground(QBrush(QColor(150, 150, 150))); // Override to gray for unused
		}
		else if (percentage >= 75)
		{
			bgcolor = QColor(100, 255, 100); // Green - heavy use
		}
		else if (percentage >= 25)
		{
			bgcolor = QColor(255, 255, 100); // Yellow - medium use
		}
		else
		{
			bgcolor = QColor(200, 200, 200); // Gray - light use
		}

		item_percent->setBackground(QBrush(bgcolor));
		ui->tableWidget_MidiPlayerChannels->setItem(2, ch, item_percent);
	}

	// Auto-resize rows and columns
	ui->tableWidget_MidiPlayerChannels->resizeRowsToContents();
	ui->tableWidget_MidiPlayerChannels->resizeColumnsToContents();

	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiPlayer::on_midi_file_loaded(const QString &s)
{
	std::string file_name;
	
	midi_file_meta_data_t meta_data = mod_synth_midi_player_get_file_metadata();

	// Verify the file analyzer is initialized before requesting scale segments
	// This prevents crashes if the file failed to load or parse properly
	try
	{
		simple_scale_segments = mod_synth_get_simple_scale_segments();
	}
	catch (...)
	{
		// If get_simple_scale_segments fails, use empty vector
		simple_scale_segments.clear();
		printf("Warning: Failed to get scale segments - file may not be fully loaded\n");
	}
	
	active_scale_index = 0;

	file_name = std::string("Ready: ");
	file_name += std::filesystem::path(midi_file_name.toStdString()).stem();
	
	ui->lineEdit_MidiPlayeFileName->setText(QString::fromStdString(file_name));

	//ui->lineEdit_MidiPlayerScalesInfo->setText(
	//	QString::fromStdString("File Scale: " + meta_data.major_scale_text + " | " + meta_data.minor_scale_text));

	// Display channel utilization in table
	display_channel_utilization(meta_data);

	ui->pushButton_MidiPlayerPlay->setEnabled(true);
	ui->pushButton_MidiPlayerPause->setEnabled(true);
	ui->pushButton_MidiPlayerStop->setEnabled(true);
	
}

void Dialog_MidiPlayer::on_open_file_clicked()
{
	QString startDir = last_midi_directory.isEmpty() ? QString(_MIDI_PLAYBACK_FILES_DEFAULT_DIR) : last_midi_directory;

	//CustomFileDialog dialog(this,
	CustomFileDialog *dialog = new CustomFileDialog(this,
							tr("Open MIDI File"),
							startDir,
							tr("Presets (*.mid *.MID);;All Files (*)"),
							Qt::black,
							CustomFileDialog::OpenMode,
                           "midi_player");

	// Use Qt::WA_DeleteOnClose to automatically clean up
	dialog->setAttribute(Qt::WA_DeleteOnClose);

	// If we have a last file, select it and scroll to it
	if (!last_midi_file.isEmpty())
	{
		dialog->selectFile(last_midi_file);
	}

	if (dialog->exec() == QDialog::Accepted)
	{
		midi_file_name = dialog->selectedFile();

		if (!midi_file_name.isEmpty())
		{
			// Remember the directory and file for next time
			last_midi_directory = QFileInfo(midi_file_name).absolutePath();
			last_midi_file = midi_file_name;

			std::string file_name;
			file_name = std::string("Now Loading: ");
			file_name += std::filesystem::path(midi_file_name.toStdString()).stem();

			ui->lineEdit_MidiPlayeFileName->setText(QString::fromStdString(file_name));

			// Check if thread is still running
			if (open_file_thread != nullptr && !open_file_thread->isFinished())
			{
				// Thread still running, ignore request
				return;
			}
			
			open_file_thread = new OpenMidiPlayerFileThread();
			connect(open_file_thread,
					&OpenMidiPlayerFileThread::finished, open_file_thread, &QObject::deleteLater);
			connect(open_file_thread, &OpenMidiPlayerFileThread::resultReady, this, &Dialog_MidiPlayer::on_midi_file_loaded);
			// Reset pointer when thread is destroyed
			connect(open_file_thread,
					&QObject::destroyed,
					[]() { open_file_thread = nullptr; });
			open_file_thread->start();

			ui->pushButton_MidiPlayerPlay->setEnabled(false);
			ui->pushButton_MidiPlayerPause->setEnabled(false);
			ui->pushButton_MidiPlayerStop->setEnabled(false);
		}
	}
}

void Dialog_MidiPlayer::on_play_clicked()
{
	std::string file_name;
	
	mod_synth_midi_player_play();
	
	file_name = std::string("Playing: ");
	file_name += std::filesystem::path(midi_file_name.toStdString()).stem();
	ui->lineEdit_MidiPlayeFileName->setText(QString::fromStdString(file_name));
}

void Dialog_MidiPlayer::on_pause_clicked()
{
	mod_synth_midi_player_pause();
}

void Dialog_MidiPlayer::on_stop_clicked()
{
	mod_synth_midi_player_stop();	
}

void Dialog_MidiPlayer::on_backward_clicked()
{
	if (navigation_in_progress)
		return;
	navigation_in_progress = true;

	mod_synth_midi_player_backward();

	// Use QTimer to reset flag after short delay
	QTimer::singleShot(100, this, [this]() {
		navigation_in_progress = false;
	});
}
void Dialog_MidiPlayer::on_forward_clicked()
{
	if (navigation_in_progress)
		return;
	navigation_in_progress = true;

	mod_synth_midi_player_forward();

	// Use QTimer to reset flag after short delay
	QTimer::singleShot(100, this, [this]() {
		navigation_in_progress = false;
	});
}

void Dialog_MidiPlayer::on_enable_loopback_enable(bool enabled)
{
	mod_synth_midi_player_set_auto_loop_back(enabled);
}

void Dialog_MidiPlayer::on_playback_volume_changed(int value)
{
	mod_synth_midi_player_set_playback_volume(value);

	ui->spinBox_MidiPlayer_Volume->blockSignals(true);
	ui->spinBox_MidiPlayer_Volume->setValue(value);
	ui->spinBox_MidiPlayer_Volume->blockSignals(false);
}

void Dialog_MidiPlayer::on_playback_speed_changed(int value)
{
	mod_synth_midi_player_set_playback_speed(value);

	ui->spinBox_MidiPlayer_Speed->blockSignals(true);
	ui->spinBox_MidiPlayer_Speed->setValue(value);
	ui->spinBox_MidiPlayer_Speed->blockSignals(false);
}

void Dialog_MidiPlayer::start_update_timer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
	timer->start(interval);
}

void Dialog_MidiPlayer::timerEvent()
{
	update_gui();
}

void Dialog_MidiPlayer::update_gui()
{
	// Don't update if dialog is not visible
	if (!isVisible())
	{
		return;
	}
	
	char text[16];
	QString qtext;
	
	ui->progressBar_MidiPlayerProgressPercents->setValue(playback_progres_percentegas);
	
	sprintf(text, "%02i:%02i", song_total_playing_time_minutes, song_total_playing_time_seconds);
	qtext = text;
	ui->label_MidiPlayerSongTotalPlayingTime->setText(qtext);
	
	sprintf(text, "%02i:%02i", song_playing_time_minutes, song_playing_time_seconds);
	qtext = text;
	ui->label_MidiPlayerSongPlayingTime->setText(qtext);
	
	sprintf(text, "%02i:%02i", song_remaining_playing_time_minutes, song_remaining_playing_time_seconds);
	qtext = text;
	ui->label_MidiPlayerSongRemainingPlayingTime->setText(qtext);

	ui->label_MidiPlayerScalesInfo->setText(active_scale_text);
}
