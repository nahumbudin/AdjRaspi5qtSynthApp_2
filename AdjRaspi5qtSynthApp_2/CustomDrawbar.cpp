/**
 * @file		CustomDrawbar.cpp
 * @author		Nahum Budin
 * @date		19-Apr-2026
 * @version	1.0
 *
 * @brief		Custom vertical slider styled as Hammond Organ drawbar
 *
 * @History:
 *		Version 1.0	19-Apr-2026
 *
 *	Created with the assitace of the GitHub Copilot Claude Sonnet 4.5
 */

#include "CustomDrawbar.h"
#include <QBrush>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QPainterPath>

CustomDrawbar::CustomDrawbar(QWidget *parent)
	: QSlider(Qt::Vertical, parent), tip_color(QColor(139, 69, 19)) // Brown tip (classic Hammond)
	  ,
	  body_color(QColor(240, 240, 240)) // Light gray/white body
	  ,
	  slot_color(QColor(0, 0, 0)) // Black slot
	  ,
	  grip_line_color(QColor(0, 0, 0)) // Black grip line
	  ,
	  show_notches(false)
{
	setMinimum(0);
	setMaximum(8); // Hammond drawbars: 9 positions (0-8)
	setValue(0);   // Default: pushed in (silent)

	// Force no stylesheet interference
	setStyleSheet("QSlider { background: transparent; }");
}

CustomDrawbar::~CustomDrawbar() {}

QSize CustomDrawbar::sizeHint() const
{
	return QSize(30, 180); // Narrow and tall like a drawbar
}

void CustomDrawbar::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, false);

	QRect widgetRect = rect();

	// Fill ENTIRE widget with dialog background color
	painter.fillRect(widgetRect, palette().window());

	// SCALABLE dimensions based on widget size
	const int widgetHeight = widgetRect.height();
	const int widgetWidth = widgetRect.width();

	const int slotHeight = (int)(widgetHeight * 0.90);	 // 72% of height
	const int slotTop = (int)(widgetHeight * 0.08);		 // 8% from top
	const int slotWidth = (int)(widgetWidth * 0.67);	 // 67% of width
	const int barWidth = (int)(widgetWidth * 0.53);		 // 53% of width
	const int handleWidth = (int)(widgetWidth * 0.93);	 // 93% of width
	const int handleHeight = (int)(widgetHeight * 0.19); // 19% of height
	const int handleDiameter = handleHeight;			 // For calculations

	// Center horizontally
	int centerX = widgetWidth / 2;
	int slotX = centerX - slotWidth / 2;
	int slotBottom = slotTop + slotHeight;

	// Calculate position based on value (0=out/top, 8=in/bottom)
	int range = maximum() - minimum();
	float normalizedValue = (float)(value() - minimum()) / range;
	int travelDistance = slotHeight - handleHeight;

	// Handle position: 0 at top, 8 at bottom
	int handleCenterY = slotTop + handleHeight / 2 + (normalizedValue * travelDistance);

	// 1. Draw the Black slot
	painter.fillRect(slotX, slotTop, slotWidth, slotHeight, QColor(15, 15, 15));

	// 2. Draw position markers
	if (show_notches)
	{
		painter.setPen(QPen(QColor(200, 200, 200), 1));
		for (int i = 0; i <= maximum(); i++)
		{
			float pos = (float)i / range;
			int y = slotTop + handleHeight / 2 + (pos * travelDistance);
			int tickLength = (int)(widgetWidth * 0.17);
			painter.drawLine(slotX - 3, y, slotX - 3 - tickLength, y);
		}
	}

	// 3. Draw bar (vertical rod above handle)
	painter.setRenderHint(QPainter::Antialiasing, true);
	int barTop = slotTop - 0;
	int barX = centerX - barWidth / 2;
	QRect barRect(barX, barTop, barWidth, handleCenterY - barTop);

	// Fill bar with black
	painter.setPen(Qt::NoPen);
	painter.fillRect(barRect, QColor(0, 0, 0));

	// Draw white lines on sides
	painter.setPen(QPen(QColor(255, 255, 255), 1));
	painter.drawLine(barX, barTop, barX, handleCenterY);							   // Left line
	painter.drawLine(barX + barWidth - 1, barTop, barX + barWidth - 1, handleCenterY); // Right line

	// 4. Draw digits
	if (value() > 0)
	{
		int fontSize = qMax(7, (int)(widgetHeight * 0.05));
		painter.setFont(QFont("Arial", fontSize, QFont::Bold));
		painter.setPen(QColor(255, 255, 255));

		const int digitHeight = fontSize + 8;
		const int totalDigits = value();
		const int totalStackHeight = totalDigits * digitHeight;

		// Start position just above handle
		int startY = handleCenterY - handleHeight / 2 - digitHeight / 2;

		// Draw from 1 (bottom) up to value (top)
		for (int i = 1; i <= value(); i++)
		{
			int digitY = startY - ((i - 1) * digitHeight);

			painter.drawText(QRect(centerX - 6, digitY - digitHeight / 2, 12, digitHeight),
							 Qt::AlignCenter, QString::number(i));
		}
	}

	// 5. Draw handle
	QRect handleRect(centerX - handleWidth / 2, handleCenterY - handleHeight / 2,
					 handleWidth, handleHeight);
	painter.setBrush(isEnabled() ? tip_color : QColor(100, 100, 100));
	painter.setPen(QPen(Qt::black, 2));

	QPainterPath path;
	int radius = (int)(handleWidth * 0.29);
	int x = handleRect.x();
	int y = handleRect.y();
	int w = handleRect.width();
	int h = handleRect.height();

	path.moveTo(x, y);
	path.lineTo(x + w, y);
	path.lineTo(x + w, y + h - radius);
	path.arcTo(x + w - radius * 2, y + h - radius * 2, radius * 2, radius * 2, 0, -90);
	path.lineTo(x + radius, y + h);
	path.arcTo(x, y + h - radius * 2, radius * 2, radius * 2, 270, -90);
	path.lineTo(x, y);

	painter.drawPath(path);

	// 6. Draw grip line
	int gripY = handleCenterY + handleHeight / 2 - (int)(handleHeight * 0.23);
	int gripWidth = (int)(handleWidth * 0.5);
	painter.setPen(QPen(grip_line_color, 5)); // Use color variable and 5 pixel width
	painter.drawLine(centerX - gripWidth / 2, gripY, centerX + gripWidth / 2, gripY);
}

void CustomDrawbar::setTipColor(QColor color)
{
	tip_color = color;
	update();
}

void CustomDrawbar::setBodyColor(QColor color)
{
	body_color = color;
	update();
}

void CustomDrawbar::setSlotColor(QColor color)
{
	slot_color = color;
	update();
}

void CustomDrawbar::setGripLineColor(QColor color)
{
	grip_line_color = color;
	update();
}

void CustomDrawbar::setShowNotches(bool show)
{
	show_notches = show;
	update();
}

void CustomDrawbar::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		const int widgetHeight = height();
		const int slotHeight = (int)(widgetHeight * 0.72);
		const int slotTop = (int)(widgetHeight * 0.08);
		const int handleHeight = (int)(widgetHeight * 0.19);
		const int travelDistance = slotHeight - handleHeight;

		int y = event->pos().y();
		int relativeY = y - slotTop - handleHeight / 2;

		relativeY = qBound(0, relativeY, travelDistance);
		float normalized = (float)relativeY / (float)travelDistance;
		int newValue = qRound(normalized * (maximum() - minimum()) + minimum());

		setValue(newValue);
		event->accept();
	}
}

void CustomDrawbar::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		const int widgetHeight = height();
		const int slotHeight = (int)(widgetHeight * 0.72);
		const int slotTop = (int)(widgetHeight * 0.08);
		const int handleHeight = (int)(widgetHeight * 0.19);
		const int travelDistance = slotHeight - handleHeight;

		int y = event->pos().y();
		int relativeY = y - slotTop - handleHeight / 2;

		relativeY = qBound(0, relativeY, travelDistance);
		float normalized = (float)relativeY / (float)travelDistance;
		int newValue = qRound(normalized * (maximum() - minimum()) + minimum());

		setValue(newValue);
		event->accept();
	}
}
