/**
 * @file		Dialog_WindowManager.cpp
 *	@author		Nahum Budin
 *	@date		18-Feb-2026
 *	@version	1.0
 *
 *	@brief		Window Manager Dialog - Shows list of all open application dialogs
 *				Coded with the help of GitHub Copilot
 *
 */

#include "Dialog_WindowsManager.h"
#include <QDebug>
#include <QApplication>

Dialog_WindowManager *Dialog_WindowManager::dialog_manager = nullptr;

Dialog_WindowManager::Dialog_WindowManager(QWidget *parent)
	: QDialog(parent)
{
	setup_ui();
	//setModal(true);
	setWindowTitle("Window Manager");
	resize(200, 400);

	// Stay on top and don't take focus when shown
	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_ShowWithoutActivating);
}

Dialog_WindowManager *Dialog_WindowManager::get_instance(QWidget *parent)
{
	if (dialog_manager == nullptr)
	{
		dialog_manager = new Dialog_WindowManager(parent);
	}

	return dialog_manager;
}

Dialog_WindowManager::~Dialog_WindowManager()
{
	// Cleanup is handled automatically by Qt's parent-child relationship
}

void Dialog_WindowManager::setup_ui()
{
	main_layout = new QVBoxLayout(this);
	main_layout->setSpacing(5);
	main_layout->setContentsMargins(5, 5, 5, 5);

	// Header label
	header_label = new QLabel("Active Dialogs", this);
	QFont headerFont = header_label->font();
	headerFont.setPointSize(12);
	headerFont.setBold(true);
	header_label->setFont(headerFont);
	header_label->setAlignment(Qt::AlignCenter);
	header_label->setStyleSheet("QLabel { color: #FFFFFF; background-color: #050505; " // 2a5a8a
								"padding: 5px; border-radius: 5px; }");
	main_layout->addWidget(header_label);

	// Count label
	headerFont.setPointSize(10);
	headerFont.setBold(false);
	count_label = new QLabel("0 dialogs open", this);
	count_label->setFont(headerFont);
	count_label->setAlignment(Qt::AlignCenter);
	count_label->setStyleSheet("QLabel { padding: 5px; }");
	count_label->setStyleSheet("QLabel { color: #FFFFFF; background-color: #050505; " 
								"padding: 10px; border-radius: 5px; }");
	main_layout->addWidget(count_label);

	// Scroll area for dialog buttons
	scroll_area = new QScrollArea(this);
	scroll_area->setWidgetResizable(true);
	scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scroll_area->setStyleSheet("QScrollArea { border: 2px solid #555; border-radius: 5px; "
							   "background-color: #151515; }"
							   "QScrollArea > QWidget > QWidget { background-color: #151515; }" // Viewport content
							   "QScrollArea > QWidget { background-color: #151515; }");			// Viewport

	scroll_content = new QWidget();
	scroll_layout = new QVBoxLayout(scroll_content);
	scroll_layout->setAlignment(Qt::AlignTop);
	scroll_layout->setSpacing(5);
	scroll_layout->setContentsMargins(5, 5, 5, 5);

	scroll_area->setWidget(scroll_content);
	main_layout->addWidget(scroll_area, 1); // Stretch factor 1

	// Close button
	close_button = new QPushButton("Close", this);
	close_button->setMinimumHeight(20);
	close_button->setStyleSheet("QPushButton {"
								"    font-size: 10pt;"
								"    font-weight: bold;"
								"    border: 2px solid #555;"
								"    border-radius: 3px;"
								"    background-color: #3a3a3a;"
								"    padding: 3px;"
								"}"
								"QPushButton:hover {"
								"    background-color: #4a4a4a;"
								"    border: 2px solid #888;"
								"}"
								"QPushButton:pressed {"
								"    background-color: #5a5a5a;"
								"}");
	connect(close_button, SIGNAL(clicked(bool)), this, SLOT(on_close_button_clicked()));
	main_layout->addWidget(close_button);

	setLayout(main_layout);

	// Set dialog background
	setStyleSheet("QDialog { background-color: #2a2a2a; }");
}

void Dialog_WindowManager::register_dialog(QWidget *window, const QString &windowTitle)
{
	if (!window)
	{
		qDebug() << "Dialog_WindowManager: Cannot register null window";
		return;
	}

	QMutexLocker locker(&dialog_list_mutex);

	// Check if dialog already registered
	for (const auto &info : dialog_list)
	{
		if (info.widget == window)
		{
			qDebug() << "Dialog_WindowManager: Dialog already registered:" << windowTitle;
			return;
		}
	}

	DialogInfo info;
	info.widget = window;
	info.title = windowTitle;
	dialog_list.append(info);

	qDebug() << "Dialog_WindowManager: Registered dialog:" << windowTitle;

	// Update UI if window manager is visible
	if (isVisible())
	{
		rebuild_dialog_list();
	}
}

void Dialog_WindowManager::unregister_dialog(QWidget *window)
{

	QMutexLocker locker(&dialog_list_mutex);
	
	for (int i = 0; i < dialog_list.size(); ++i)
	{
		if (dialog_list.at(i).widget == window)
		{
			qDebug() << "Dialog_WindowManager: Unregistered dialog:" << dialog_list[i].title;
			dialog_list.removeAt(i);
			
			// Update UI if window manager is visible
			if (isVisible())
			{
				rebuild_dialog_list();
			}
			return;
		}
	}
}

void Dialog_WindowManager::clear_all_dialogs()
{
	QMutexLocker locker(&dialog_list_mutex);

	// Close all instrument dialogs
	for (auto dialog : dialog_list)
	{
		if (dialog.widget != nullptr)
		{
			dialog.widget->close();
			//dialog.widget->deleteLater(); // Important: actually delete the dialog
		}
	}
	
	dialog_list.clear();
	qDebug() << "Dialog_WindowManager: Cleared all dialogs";
}

void Dialog_WindowManager::show_window_manager()
{
	rebuild_dialog_list();
	// Show without activating (stealing focus)
	show(); 
	//exec(); // Show as modal dialog
}

void Dialog_WindowManager::rebuild_dialog_list()
{
	// Clear existing buttons
	QLayoutItem *item;
	while ((item = scroll_layout->takeAt(0)) != nullptr)
	{
		delete item->widget();
		delete item;
	}

	// Update count label
	int validCount = 0;

	QMutexLocker locker(&dialog_list_mutex);
	
	// Create buttons for each registered dialog
	for (const auto &info : dialog_list)
	{
		if (!info.widget)
		{
			continue;
		}

		validCount++;

		QPushButton *button = new QPushButton(info.title, scroll_content);
		button->setMinimumHeight(25);
		button->setProperty("dialogPointer", QVariant::fromValue(static_cast<void *>(info.widget)));

		// Style the button with icon-like appearance
		QString styleSheet = "QPushButton {"
							 "    text-align: left;"
							 "    padding-left: 15px;"
							 "    font-size: 10pt;"
							 "    font-weight: bold;"
							 "    border: 2px solid #555;"
							 "    border-radius: 3px;"
							 "    background-color: #2a2a2a;"
							 "    color: #FFFFFF;"
							 "}"
							 "QPushButton:hover {"
							 "    background-color: #3a5a7a;"
							 "    border: 2px solid #4a7aa8;"
							 "}"
							 "QPushButton:pressed {"
							 "    background-color: #4a6a8a;"
							 "    border: 2px solid #5a8ab8;"
							 "}";
		button->setStyleSheet(styleSheet);

		connect(button, SIGNAL(clicked(bool)), this, SLOT(on_dialog_button_clicked()));
		scroll_layout->addWidget(button);
	}

	// Update count
	count_label->setText(QString("%1 dialog%2 open").arg(validCount).arg(validCount == 1 ? "" : "s"));

	// Add stretch at the end
	scroll_layout->addStretch();
}

void Dialog_WindowManager::on_dialog_button_clicked()
{
	QPushButton *button = qobject_cast<QPushButton *>(sender());
	if (!button)
	{
		return;
	}

	void *ptr = button->property("dialogPointer").value<void *>();
	QWidget *dialog = static_cast<QWidget *>(ptr);

	if (dialog)
	{
		// Bring dialog to front and focus it
		dialog->show();
		dialog->raise();
		dialog->activateWindow();
		dialog->setFocus(Qt::ActiveWindowFocusReason);

		qDebug() << "Dialog_WindowManager: Focused dialog:" << button->text();

		// Close the window manager
		//this->close();
	}
	else
	{
		qDebug() << "Dialog_WindowManager: Dialog pointer is null!";
	}
}

void Dialog_WindowManager::on_close_button_clicked()
{
	this->close();
}

void Dialog_WindowManager::simulate_button_hover(int button_index)
{
	// Iterate through all buttons in the scroll layout
	for (int i = 0; i < scroll_layout->count(); ++i)
	{
		QLayoutItem *item = scroll_layout->itemAt(i);
		if (!item)
			continue;

		QPushButton *button = qobject_cast<QPushButton *>(item->widget());
		if (!button)
			continue;

		if (i == button_index)
		{
			// Simulate mouse enter event
			QEvent enterEvent(QEvent::Enter);
			QApplication::sendEvent(button, &enterEvent);

			// Optional: Set focus to make it more visible
			button->setFocus(Qt::MouseFocusReason);

			qDebug() << "Dialog_WindowManager: Simulated hover on button:" << button->text();
		}
		else
		{
			// Simulate mouse leave event for other buttons
			QEvent leaveEvent(QEvent::Leave);
			QApplication::sendEvent(button, &leaveEvent);

			// Clear focus if this button had it
			if (button->hasFocus() && button_index != i)
			{
				button->clearFocus();
			}
		}
	}

	if (button_index == -1)
	{
		qDebug() << "Dialog_WindowManager: Cleared all button hovers";
	}
}

void Dialog_WindowManager::simulate_button_click(int button_index)
{
	if (button_index < 0)
	{
		qDebug() << "Dialog_WindowManager: Invalid button index:" << button_index;
		return;
	}

	// Find the button at the specified index
	QLayoutItem *item = scroll_layout->itemAt(button_index);
	if (!item)
	{
		qDebug() << "Dialog_WindowManager: No item at index:" << button_index;
		return;
	}

	QPushButton *button = qobject_cast<QPushButton *>(item->widget());
	if (!button)
	{
		qDebug() << "Dialog_WindowManager: Item is not a button at index:" << button_index;
		return;
	}

	// Simulate the click
	button->click();

	qDebug() << "Dialog_WindowManager: Simulated click on button:" << button->text();
}
