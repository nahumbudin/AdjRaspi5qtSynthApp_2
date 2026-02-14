/**
 * @file		CustomCheckBox.cpp
 *	@author		Nahum Budin
 *	@date		22-Dec-2025
 *	@version	1.0
 *					1. First version. Created using GitHub Copilot
 *
 *	@brief		Custom checkbox class with advanced styling options
 */

#include <QCheckBox>
#include <QPainter>
#include <QStylePainter>
#include <QResizeEvent>
#include <QDebug>
#include "CustomCheckBox.h"

CustomCheckBox::CustomCheckBox(QWidget *parent)
	: QCheckBox(parent), frame_color(QColor(100, 100, 100)), frame_visible(true), background_color(QColor(40, 40, 40)), text_color(Qt::white), check_color(QColor(34, 200, 98)) // Default green
{
	connect(this, &QCheckBox::stateChanged, this, [this]() { update(); });
}

CustomCheckBox::CustomCheckBox(const QString &text, QWidget *parent)
	: QCheckBox(text, parent), frame_color(QColor(100, 100, 100)), frame_visible(true), background_color(QColor(40, 40, 40)), text_color(Qt::white), check_color(QColor(34, 200, 98)) // Default green
{
	connect(this, &QCheckBox::stateChanged, this, [this]() { update(); });
}

CustomCheckBox::~CustomCheckBox()
{
}

void CustomCheckBox::mousePressEvent(QMouseEvent *event)
{
	if (!read_only)
	{
		QCheckBox::mousePressEvent(event);
	}
	// If read_only, ignore the event (don't call base class)
}

void CustomCheckBox::mouseReleaseEvent(QMouseEvent *event)
{
	if (!read_only)
	{
		QCheckBox::mouseReleaseEvent(event);
	}
}

void CustomCheckBox::setChecked(bool checked)
{
	QCheckBox::setChecked(checked);
	update(); // Force repaint after state change
}

void CustomCheckBox::setFrameColor(QColor color)
{
	frame_color = color;
	update();
}

void CustomCheckBox::setFrameVisible(bool visible)
{
	frame_visible = visible;
	update();
}

void CustomCheckBox::setBackgroundColor(QColor color)
{
	background_color = color;
	update();
}

void CustomCheckBox::setTextColor(QColor color)
{
	text_color = color;
	update();
}

void CustomCheckBox::setCheckColor(QColor color)
{
	check_color = color;
	update();
}

int CustomCheckBox::calculateIndicatorSize() const
{
	// Calculate indicator size based on font metrics
	QFontMetrics fm(font());
	int size = fm.height() - 2; // Slightly smaller than text height

	// Ensure minimum and maximum sizes
	if (size < 14)
		size = 14;
	if (size > 22)
		size = 22;

	return size;
}

void CustomCheckBox::paintEvent(QPaintEvent *event)
{
	//static int paintCount = 0;
	//qDebug() << "paintEvent called" << ++paintCount << "isChecked:" << isChecked();
	
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	// Get dimensions
	int indicatorSize = calculateIndicatorSize();
	int spacing = 6; // Space between checkbox and text
	int borderWidth = 2;
	int frameMargin = 1;

	// Calculate checkbox rectangle position
	QRect checkboxRect(frameMargin, (height() - indicatorSize) / 2, indicatorSize, indicatorSize);

	// 1. Draw outer frame (if visible)
	if (frame_visible)
	{
		QPen framePen(isEnabled() ? frame_color : QColor(80, 80, 80), 1);
		painter.setPen(framePen);
		painter.setBrush(Qt::NoBrush);

		QRect outerFrame = checkboxRect.adjusted(-frameMargin, -frameMargin, frameMargin, frameMargin);
		painter.drawRect(outerFrame);
	}

	// 2. Draw checkbox background
	painter.setPen(Qt::NoPen);
	painter.setBrush(isEnabled() ? background_color : QColor(60, 60, 60));
	painter.drawRect(checkboxRect);

	// 3. Draw checkbox border
	QPen borderPen(isEnabled() ? frame_color.lighter(120) : QColor(80, 80, 80), borderWidth);
	painter.setPen(borderPen);
	painter.setBrush(Qt::NoBrush);
	QRect borderRect = checkboxRect.adjusted(
		borderWidth / 2,
		borderWidth / 2,
		-borderWidth / 2,
		-borderWidth / 2);
	painter.drawRect(borderRect);

	// 4. Draw colored rectangle when checked
	if (isChecked())
	{
		int margin = 4; // Margin from checkbox edges for the colored rectangle
		QRect fillRect = checkboxRect.adjusted(margin, margin, -margin, -margin);

		painter.setPen(Qt::NoPen);
		painter.setBrush(isEnabled() ? check_color : QColor(100, 100, 100));
		painter.drawRect(fillRect);
	}

	// 5. Draw text label (if exists)
	if (!text().isEmpty())
	{
		QRect textRect(
			checkboxRect.right() + spacing,
			0,
			width() - checkboxRect.right() - spacing,
			height());

		painter.setPen(isEnabled() ? text_color : QColor(120, 120, 120));
		QFont textFont = font();
		painter.setFont(textFont);
		painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text());
	}

	// 6. Draw focus indicator if widget has focus
	if (hasFocus())
	{
		QPen focusPen(check_color.lighter(150), 1, Qt::DotLine);
		painter.setPen(focusPen);
		painter.setBrush(Qt::NoBrush);
		painter.drawRect(rect().adjusted(1, 1, -1, -1));
	}
}

void CustomCheckBox::resizeEvent(QResizeEvent *event)
{
	QCheckBox::resizeEvent(event);
	update();
}

void CustomCheckBox::updateStyleSheet()
{
	// This method can be used for additional stylesheet updates if needed
	// Currently, all styling is done in paintEvent
	update();
}
