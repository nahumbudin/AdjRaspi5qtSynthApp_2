/**
 * @file		CustomComboBox.cpp
 *	@author		Nahum Budin
 *	@date		22-Dec-2025
 *	@version	1.0
 *					1. First version. Created using GitHub Copilot
 *					2. Added mouse hover event support (enterEvent/leaveEvent)
 *					3. Added int argument to mouse signals
 *
 *	@brief		Custom combobox class with advanced styling options
 */

#include "CustomComboBox.h"
#include <QComboBox>
#include <QPainter>
#include <QStyleOptionComboBox>
#include <QStylePainter>

CustomComboBox::CustomComboBox(QWidget *parent)
	: QComboBox(parent), 
	  frame_color(QColor(100, 100, 100)), 
	  frame_visible(true), 
	  frame_width(1), 
	  background_color(QColor(60, 60, 60)), 
	  text_color(Qt::white),
	  id(-1)
{
	updateStyleSheet();
}

CustomComboBox::~CustomComboBox() 
{
}	

void CustomComboBox::paintEvent(QPaintEvent *event)
{
	// First, let the default painting happen
	QComboBox::paintEvent(event);

	// Then draw our custom frame on top
	if (frame_visible && frame_width > 0)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing, false); // Disable for sharper lines

		QRect comboRect = rect();
		int halfWidth = frame_width / 2;

		// Adjust rect to center the border line
		QRect frameRect = comboRect.adjusted(
			halfWidth,
			halfWidth,
			-halfWidth,
			-halfWidth);

		QPen framePen(isEnabled() ? frame_color : QColor(80, 80, 80), frame_width);
		framePen.setStyle(Qt::SolidLine);
		framePen.setCapStyle(Qt::SquareCap);
		framePen.setJoinStyle(Qt::MiterJoin);
		painter.setPen(framePen);
		painter.setBrush(Qt::NoBrush);
		painter.drawRect(frameRect);
	}
}

void CustomComboBox::enterEvent(QEvent *event)
{
	// Mouse entered the combobox area
	QComboBox::enterEvent(event);
	emit mouseEntered(id);
}

void CustomComboBox::leaveEvent(QEvent *event)
{
	// Mouse left the combobox area
	QComboBox::leaveEvent(event);
	emit mouseExited(id);
}

void CustomComboBox::setIdentifier(int idn)
{
	id = idn;
}

int CustomComboBox::getIdentifier() const
{
	return id;
}

void CustomComboBox::setFrameColor(QColor color)
{
	frame_color = color;
	updateStyleSheet();
	update();
}

void CustomComboBox::setFrameVisible(bool visible)
{
	frame_visible = visible;
	update();
}

void CustomComboBox::setFrameWidth(int width)
{
	frame_width = qMax(0, width); // Ensure non-negative
	update();
}

void CustomComboBox::setBackgroundColor(QColor color)
{
	background_color = color;
	updateStyleSheet();
	update();
}

void CustomComboBox::setTextColor(QColor color)
{
	text_color = color;
	updateStyleSheet();
	update();
}

void CustomComboBox::updateStyleSheet()
{
	setStyleSheet(QString(
					  "QComboBox {"
					  "    background-color: rgb(%1, %2, %3);"
					  "    color: rgb(%4, %5, %6);"
					  "    border: none;"
					  "    padding: 5px;"
					  "    min-height: 20px;"
					  "}"
					  "QComboBox::drop-down {"
					  "    border: none;"
					  "    width: 20px;"
					  "}"
					  "QComboBox::down-arrow {"
					  "    image: none;"
					  "    border-left: 4px solid transparent;"
					  "    border-right: 4px solid transparent;"
					  "    border-top: 6px solid rgb(%4, %5, %6);"
					  "    margin-right: 5px;"
					  "}"
					  "QComboBox QAbstractItemView {"
					  "    background-color: rgb(%1, %2, %3);"
					  "    color: rgb(%4, %5, %6);"
					  "    selection-background-color: rgb(34, 200, 98);"
					  "    border: 3px solid rgb(%7, %8, %9);"
					  "}")
					  .arg(background_color.red())
					  .arg(background_color.green())
					  .arg(background_color.blue())
					  .arg(text_color.red())
					  .arg(text_color.green())
					  .arg(text_color.blue())
					  .arg(frame_color.red())
					  .arg(frame_color.green())
					  .arg(frame_color.blue()));
}
