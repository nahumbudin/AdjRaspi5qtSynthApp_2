/**
 * @file		CustomSpinBox.cpp
 *	@author		Nahum Budin
 *	@date		19-Mar-2026
 *	@version	1.0
 *
 *	@brief		Custom spinbox class with advanced styling options
 *				(Created with the assistance of GitHub Copilot)
 */

#include "CustomSpinBox.h"
#include <QLineEdit>
#include <QPainter>
#include <QStyleOptionSpinBox>

CustomSpinBox::CustomSpinBox(QWidget *parent)
	: QSpinBox(parent),
	  frame_color(QColor(100, 100, 100)),
	  frame_visible(true),
	  frame_width(1),
	  background_color(QColor(60, 60, 60)),
	  text_color(Qt::white),
	  text_alignment(Qt::AlignCenter),
	  id(-1)
{
	setFrame(false); // Disable default frame
	
	updateStyleSheet();

	// Center align the internal line edit
	if (lineEdit())
	{
		lineEdit()->setAlignment(text_alignment);
	}
}

CustomSpinBox::~CustomSpinBox()
{
}

void CustomSpinBox::paintEvent(QPaintEvent *event)
{
	// First, let the default painting happen
	QSpinBox::paintEvent(event);

	// Then draw our custom frame on top
	if (frame_visible && frame_width > 0)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing, false);

		QRect spinRect = rect();
		int halfWidth = frame_width / 2;

		QRect frameRect = spinRect.adjusted(halfWidth, halfWidth, -halfWidth, -halfWidth);

		QPen framePen(isEnabled() ? frame_color : QColor(80, 80, 80), frame_width);
		framePen.setStyle(Qt::SolidLine);
		framePen.setCapStyle(Qt::SquareCap);
		framePen.setJoinStyle(Qt::MiterJoin);
		painter.setPen(framePen);
		painter.setBrush(Qt::NoBrush);
		painter.drawRect(frameRect);
	}
}

void CustomSpinBox::enterEvent(QEvent *event)
{
	QSpinBox::enterEvent(event);
	emit mouseEntered(id);
}

void CustomSpinBox::leaveEvent(QEvent *event)
{
	QSpinBox::leaveEvent(event);
	emit mouseExited(id);
}

void CustomSpinBox::setIdentifier(int idn)
{
	id = idn;
}

int CustomSpinBox::getIdentifier() const
{
	return id;
}

void CustomSpinBox::setFrameColor(QColor color)
{
	frame_color = color;
	updateStyleSheet();
	update();
}

void CustomSpinBox::setFrameVisible(bool visible)
{
	frame_visible = visible;
	update();
}

void CustomSpinBox::setFrameWidth(int width)
{
	frame_width = qMax(0, width);
	update();
}

void CustomSpinBox::setBackgroundColor(QColor color)
{
	background_color = color;
	updateStyleSheet();
	update();
}

void CustomSpinBox::setTextColor(QColor color)
{
	text_color = color;
	updateStyleSheet();
	update();
}

void CustomSpinBox::setTextAlignment(Qt::Alignment alignment)
{
	text_alignment = alignment;
	if (lineEdit())
	{
		lineEdit()->setAlignment(alignment);
	}
	update();
}

void CustomSpinBox::updateStyleSheet()
{
	setStyleSheet(QString(
					  "QSpinBox {"
					  "    background-color: rgb(%1, %2, %3);"
					  "    color: rgb(%4, %5, %6);"
					  "    border: none;"
					  "    padding: 2px;"
					  "    min-height: 0px;"
					  "}"
					  "QSpinBox::up-button, QSpinBox::down-button {"
					  "    background-color: rgb(%7, %8, %9);"
					  "    border: none;"
					  "    width: 16px;"
					  "}"
					  "QSpinBox::up-arrow {"
					  "    image: none;"
					  "    border-left: 4px solid transparent;"
					  "    border-right: 4px solid transparent;"
					  "    border-bottom: 6px solid rgb(%4, %5, %6);"
					  "}"
					  "QSpinBox::down-arrow {"
					  "    image: none;"
					  "    border-left: 4px solid transparent;"
					  "    border-right: 4px solid transparent;"
					  "    border-top: 6px solid rgb(%4, %5, %6);"
					  "}"
					  "QSpinBox::up-arrow:off {"
					  "    border-bottom: 6px solid rgb(50, 50, 50);"
					  "}"
					  "QSpinBox::down-arrow:off {"
					  "    border-top: 6px solid rgb(50, 50, 50);"
					  "}")
					  .arg(background_color.red())
					  .arg(background_color.green())
					  .arg(background_color.blue())
					  .arg(text_color.red())
					  .arg(text_color.green())
					  .arg(text_color.blue())
					  .arg(background_color.darker(120).red())
					  .arg(background_color.darker(120).green())
					  .arg(background_color.darker(120).blue()));
}
