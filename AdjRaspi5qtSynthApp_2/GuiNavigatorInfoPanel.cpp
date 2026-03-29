/**
 * @file		GuiNavigatorInfoPanel.cpp
 *	@author		Nahum Budin
 *	@date		21-Feb-2026
 *	@version	1.0
 *
 *	@brief		Info panel widget for GuiNavigator
 *
 *	History:
 *				Coded with the assistance of GitHub Copilot
 */

#include "GuiNavigatorInfoPanel.h"
#include <QGuiApplication>
#include <QScreen>

GuiNavigatorInfoPanel::GuiNavigatorInfoPanel(QWidget *parent)
	: QWidget(parent, Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint), is_dragging(false)
{
	// Create labels
	label_line1 = new QLabel("No Dialogs", this);
	label_line2 = new QLabel("", this);

	// Set font and style
	QFont font;
	font.setPointSize(12);
	font.setBold(true);

	label_line1->setFont(font);
	label_line2->setFont(font);

	label_line1->setStyleSheet("color: white; padding: 5px;");
	label_line2->setStyleSheet("color: yellow; padding: 5px;");

	// Layout
	layout = new QVBoxLayout(this);
	layout->addWidget(label_line1);
	layout->addWidget(label_line2);
	layout->setContentsMargins(10, 5, 10, 5);
	layout->setSpacing(2);

	// Widget style - add hover effect
	setStyleSheet(
		"QWidget {"
		"    background-color: rgba(30, 30, 30, 220);"
		"    border: 2px solid rgba(100, 100, 100, 255);"
		"    border-radius: 5px;"
		"}"
		"QWidget:hover {"
		"    border: 2px solid rgba(150, 150, 150, 255);"
		"}");

	// Size
	setFixedSize(300, 80);

	// Enable mouse tracking
	setMouseTracking(true);

	// Change cursor to indicate it's draggable
	setCursor(Qt::OpenHandCursor);

	// Position at top-right of screen
	QScreen *screen = QGuiApplication::primaryScreen();
	if (screen)
	{
		QRect screenGeometry = screen->geometry();
		int x = screenGeometry.width() - width() - 20;
		int y = 20;
		move(x, y);
	}
}

GuiNavigatorInfoPanel::~GuiNavigatorInfoPanel()
{
}

void GuiNavigatorInfoPanel::update_info(const QString &line1, const QString &line2)
{
	label_line1->setText(line1);
	label_line2->setText(line2);
}

void GuiNavigatorInfoPanel::show_panel()
{
	show();
	raise();
}

void GuiNavigatorInfoPanel::hide_panel()
{
	hide();
}

void GuiNavigatorInfoPanel::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		is_dragging = true;
		drag_start_position = event->globalPos() - frameGeometry().topLeft();
		setCursor(Qt::ClosedHandCursor);
		event->accept();
	}
}

void GuiNavigatorInfoPanel::mouseMoveEvent(QMouseEvent *event)
{
	if (is_dragging && (event->buttons() & Qt::LeftButton))
	{
		// Move the panel
		move(event->globalPos() - drag_start_position);
		event->accept();
	}
}

void GuiNavigatorInfoPanel::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		is_dragging = false;
		setCursor(Qt::OpenHandCursor);
		event->accept();
	}
}
