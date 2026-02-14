/**
 * @file		CustomHorizontalSlider.cpp
 *	@author		Nahum Budin
 *	@date		22-Dec-2025
 *	@version	1.0
 *					1. First version. Created using GitHub Copilot
 *
 *	@brief		Custom horizontal slider class with advanced styling options
 */

#include <QSlider>
#include <QPainter>
#include <QStylePainter>
#include <QStyleOptionSlider>
#include "CustomHorizontalSlider.h"


CustomHorizontalSlider::CustomHorizontalSlider(QWidget *parent) 
	: QSlider(Qt::Horizontal, parent)
	, handle_color(Qt::gray)
	, track_color(QColor(60, 60, 60))
	, progress_color(QColor(34, 200, 98))
	, frame_color(QColor(100, 100, 100))
	, frame_visible(true)
	, background_color(Qt::transparent) // Add this line
{
}

CustomHorizontalSlider::~CustomHorizontalSlider() {}

QSize CustomHorizontalSlider::sizeHint() const 
{
	return QSize(150, 30); // Width x Height for horizontal slider
}


void CustomHorizontalSlider::paintEvent(QPaintEvent *event) 
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	// Get slider dimensions
	QRect sliderRect = rect();
	int frameMargin = 2;
	int frameThickness = 1;
	int trackHeight = 6;
	int handleWidth = 10;
	int handleHeight = 20;
	int tickLength = 5;
	int tickMargin = 3;

	// 0. Draw background (if not transparent)
	if (background_color != Qt::transparent) {
		painter.setPen(Qt::NoPen);
		painter.setBrush(background_color);
		painter.drawRect(sliderRect);
	}

	// 0. Draw surrounding frame (if enabled)
	if (frame_visible) {
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

	// Calculate track rectangle (centered vertically)
	QRect trackRect(
		handleWidth / 2,
		(sliderRect.height() - trackHeight) / 2,
		sliderRect.width() - handleWidth,
		trackHeight);

	// 1. Draw tick marks (if enabled)
	if (tickPosition() != QSlider::NoTicks && tickInterval() > 0) {
		painter.setPen(QPen(isEnabled() ? QColor(20, 20, 20) : QColor(100, 100, 100), 1));
		
		int trackTop = trackRect.top();
		int trackBottom = trackRect.bottom();
		
		for (int val = minimum(); val <= maximum(); val += tickInterval()) {
			// Calculate X position for this tick value
			qreal valueRange = maximum() - minimum();
			qreal normalizedVal = (val - minimum()) / (qreal)valueRange;
			int tickX = trackRect.left() + normalizedVal * trackRect.width();
			
			// Draw tick on top side
			if (tickPosition() == QSlider::TicksAbove || tickPosition() == QSlider::TicksBothSides) {
				painter.drawLine(
					tickX,
					trackTop - tickMargin - tickLength,
					tickX,
					trackTop - tickMargin);
			}
			
			// Draw tick on bottom side
			if (tickPosition() == QSlider::TicksBelow || tickPosition() == QSlider::TicksBothSides) {
				painter.drawLine(
					tickX,
					trackBottom + tickMargin,
					tickX,
					trackBottom + tickMargin + tickLength);
			}
		}
	}

	// 2. Draw background track
	painter.setPen(Qt::NoPen);
	painter.setBrush(isEnabled() ? track_color : QColor(80, 80, 80));
	painter.drawRoundedRect(trackRect, trackHeight / 2, trackHeight / 2);

	// 3. Calculate handle position based on value
	qreal valueRange = maximum() - minimum();
	qreal normalizedValue = (value() - minimum()) / valueRange;
	
	// For horizontal slider: left = minimum, right = maximum
	int handleX = trackRect.left() + normalizedValue * trackRect.width();

	// 4. Draw progress track (from left to handle)
	QRect progressRect = trackRect;
	progressRect.setRight(handleX);
	
	painter.setBrush(isEnabled() ? progress_color : QColor(100, 100, 100));
	painter.drawRoundedRect(progressRect, trackHeight / 2, trackHeight / 2);

	// 5. Draw rectangular handle (1:2 ratio - width:height)
	QColor handleFillColor = isEnabled() ? handle_color : QColor(100, 100, 100);
	
	// Calculate rectangular handle centered on the track
	QRect handleRect(
		handleX - handleWidth / 2,
		(sliderRect.height() - handleHeight) / 2,
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

	// 6. Draw handle border
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


void CustomHorizontalSlider::setHandleColor(QColor color)
{
	handle_color = color;
	update();
}

void CustomHorizontalSlider::setTrackColor(QColor color)
{
	track_color = color;
	update();
}

void CustomHorizontalSlider::setProgressColor(QColor color)
{
	progress_color = color;
	update();
}

void CustomHorizontalSlider::setFrameColor(QColor color)
{
	frame_color = color;
	update();
}

void CustomHorizontalSlider::setFrameVisible(bool visible)
{
	frame_visible = visible;
	update();
}

void CustomHorizontalSlider::setBackgroundColor(QColor color)
{
	background_color = color;
	update();
}