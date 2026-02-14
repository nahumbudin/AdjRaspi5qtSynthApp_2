/**
 * @file		CustomVerticalSlider.cpp
 *	@author		Nahum Budin
 *	@date		22-Dec-2025
 *	@version	1.0
 *					1. First version. Created using GitHub Copilot
 *
 *	@brief		Custom vertical slider class with advanced styling options
 */

#include <QSlider>
#include <QPainter>
#include <QStylePainter>
#include <QStyleOptionSlider>
#include "CustomVerticalSlider.h"


CustomVerticalSlider::CustomVerticalSlider(QWidget *parent) 
	: QSlider(Qt::Vertical, parent)
	, handle_color(Qt::gray)
	, track_color(QColor(60, 60, 60))
	, progress_color(QColor(34, 200, 98))
	, frame_color(QColor(100, 100, 100))
	, frame_visible(true)
	, background_color(Qt::transparent) // Default: transparent background
{
}

CustomVerticalSlider::~CustomVerticalSlider() {}

QSize CustomVerticalSlider::sizeHint() const 
{
	return QSize(30, 150); // Width x Height for vertical slider
}


void CustomVerticalSlider::paintEvent(QPaintEvent *event) 
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	// Get slider dimensions
	QRect sliderRect = rect();
	int frameMargin = 2;
	int frameThickness = 1;
	int trackWidth = 6;
	int handleWidth = 20;  // Width of handle
	int handleHeight = 10; // Height = width / 2 (1:2 ratio)
	int tickLength = 5;
	int tickMargin = 3; // Space between track and ticks

	// 0. Draw background (if not transparent)
	if (background_color != Qt::transparent)
	{
		painter.setPen(Qt::NoPen);
		painter.setBrush(background_color);
		painter.drawRect(sliderRect);
	}

	// 1. Draw surrounding frame (if enabled)
	if (frame_visible)
	{
		QRect frameRect = sliderRect.adjusted(
			frameMargin,
			frameMargin,
			-frameMargin,
			-frameMargin);

		QPen framePen(isEnabled() ? frame_color : QColor(80, 80, 80), frameThickness);
		painter.setPen(framePen);
		painter.setBrush(Qt::NoBrush);
		painter.drawRect(frameRect);
	}

	// Calculate track rectangle (centered horizontally)
	QRect trackRect(
		(sliderRect.width() - trackWidth) / 2,
		handleHeight / 2,
		trackWidth,
		sliderRect.height() - handleHeight);

	// 2. Draw tick marks (if enabled)
	if (tickPosition() != QSlider::NoTicks && tickInterval() > 0)
	{
		painter.setPen(QPen(isEnabled() ? QColor(20, 20, 20) : QColor(100, 100, 100), 1));

		int trackLeft = trackRect.left();
		int trackRight = trackRect.right();

		for (int val = minimum(); val <= maximum(); val += tickInterval())
		{
			// Calculate Y position for this tick value
			qreal valueRange = maximum() - minimum();
			qreal normalizedVal = (val - minimum()) / (qreal)valueRange;

			// Account for inverted appearance
			int tickY;
			if (invertedAppearance())
			{
				// Inverted: minimum at top, maximum at bottom
				tickY = trackRect.top() + normalizedVal * trackRect.height();
			}
			else
			{
				// Normal: maximum at top, minimum at bottom
				tickY = trackRect.top() + (1.0 - normalizedVal) * trackRect.height();
			}

			// Draw tick on left side
			if (tickPosition() == QSlider::TicksLeft || tickPosition() == QSlider::TicksBothSides)
			{
				painter.drawLine(
					trackLeft - tickMargin - tickLength,
					tickY,
					trackLeft - tickMargin,
					tickY);
			}

			// Draw tick on right side
			if (tickPosition() == QSlider::TicksRight || tickPosition() == QSlider::TicksBothSides)
			{
				painter.drawLine(
					trackRight + tickMargin,
					tickY,
					trackRight + tickMargin + tickLength,
					tickY);
			}
		}
	}

	// 3. Draw background track
	painter.setPen(Qt::NoPen);
	painter.setBrush(isEnabled() ? track_color : QColor(80, 80, 80));
	painter.drawRoundedRect(trackRect, trackWidth / 2, trackWidth / 2);

	// 4. Calculate handle position based on value
	qreal valueRange = maximum() - minimum();
	qreal normalizedValue = (value() - minimum()) / valueRange;

	// Account for inverted appearance
	int handleY;
	if (invertedAppearance())
	{
		// Inverted: minimum at top, maximum at bottom
		handleY = trackRect.top() + normalizedValue * trackRect.height();
	}
	else
	{
		// Normal: maximum at top, minimum at bottom
		handleY = trackRect.top() + (1.0 - normalizedValue) * trackRect.height();
	}

	// 5. Draw progress track (from appropriate end to handle)
	QRect progressRect = trackRect;
	if (invertedAppearance())
	{
		// Inverted: progress from top to handle
		progressRect.setBottom(handleY);
	}
	else
	{
		// Normal: progress from bottom to handle
		progressRect.setTop(handleY);
	}

	painter.setBrush(isEnabled() ? progress_color : QColor(100, 100, 100));
	painter.drawRoundedRect(progressRect, trackWidth / 2, trackWidth / 2);

	// 6. Draw rectangular handle (1:2 ratio - width:height)
	QColor handleFillColor = isEnabled() ? handle_color : QColor(100, 100, 100);

	// Calculate rectangular handle centered on the track
	QRect handleRect(
		(sliderRect.width() - handleWidth) / 2,
		handleY - handleHeight / 2,
		handleWidth,
		handleHeight);

	// Draw handle shadow for depth
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(0, 0, 0, 50));
	QRect shadowRect = handleRect.adjusted(1, 1, 1, 1);
	painter.drawRect(shadowRect);

	// Draw handle
	painter.setBrush(handleFillColor);
	painter.drawRect(handleRect);

	// 7. Draw handle border
	int borderThickness = 3;
	QColor borderColor = isEnabled() ? progress_color.darker(150) : QColor(80, 80, 80);

	QPen borderPen(borderColor, borderThickness);
	painter.setPen(borderPen);
	painter.setBrush(Qt::NoBrush);

	// Draw border slightly inset from the handle edges
	QRect borderRect = handleRect.adjusted(
		borderThickness / 2,
		borderThickness / 2,
		-borderThickness / 2,
		-borderThickness / 2);
	painter.drawRect(borderRect);
}


void CustomVerticalSlider::setHandleColor(QColor color)
{
	handle_color = color;
	update();
}

void CustomVerticalSlider::setTrackColor(QColor color)
{
	track_color = color;
	update();
}

void CustomVerticalSlider::setProgressColor(QColor color)
{
	progress_color = color;
	update();
}

void CustomVerticalSlider::setFrameColor(QColor color)
{
	frame_color = color;
	update();
}

void CustomVerticalSlider::setFrameVisible(bool visible)
{
	frame_visible = visible;
	update();
}

void CustomVerticalSlider::setBackgroundColor(QColor color)
{
	background_color = color;
	update();
}