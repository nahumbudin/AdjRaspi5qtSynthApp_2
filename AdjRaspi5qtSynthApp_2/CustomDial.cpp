/**
 * @file		CustomDial.cpp
 *	@author		Nahum Budin
 *	@date		22-Dec-2025
 *	@version	1.0
 *					1. First version. Created using GitHub Copilot
 *
 *	@brief		Custom dial class with advanced styling options
 */

#include <QDial>
#include <QPainter>
#include <QStylePainter>
#include <QStyleOptionSlider>
#include <QtMath>
#include "CustomDial.h"


CustomDial::CustomDial(QWidget *parent) : QDial(parent) {}

CustomDial::~CustomDial() {}

QSize CustomDial::sizeHint() const 
{
	return QSize(50, 50); // Default dial size
}


void CustomDial::paintEvent(QPaintEvent *event) 
{
	// 1. Draw only the dial background (not the knob handle)
	QStylePainter p(this);
	QStyleOptionSlider option;
	initStyleOption(&option);
	
	// Draw only the groove/background, skip the handle
	option.subControls = QStyle::SC_DialGroove | QStyle::SC_DialTickmarks;
	p.drawComplexControl(QStyle::CC_Dial, option);
	p.end();

	// 2. Draw custom colored knob
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	// Get the dial's center and size
	QRect dialRect = rect();
	QPointF center = dialRect.center();
	
	// Calculate the knob size
	qreal dialSize = qMin(dialRect.width(), dialRect.height());
	qreal knobDiameter = dialSize * 0.7; // Knob size
	qreal knobRadius = knobDiameter / 2.0;

	// 3. Draw the colored knob circle
	QColor knobFillColor = isEnabled() ? knob_color : QColor(100, 100, 100);
	
	painter.setPen(Qt::NoPen); // No outline for the knob itself
	painter.setBrush(knobFillColor);
	painter.drawEllipse(center, knobRadius, knobRadius);

	// 4. Draw the knob indicator line
	qreal valueRange = maximum() - minimum();
	qreal normalizedValue = (value() - minimum()) / valueRange;
	
	// QDial uses a 270-degree range, starting from the bottom-left
	qreal angleOffset = 225.0;
	qreal angleRange = 270.0;
	qreal angle = angleOffset - (normalizedValue * angleRange);
	qreal angleRad = qDegreesToRadians(angle);

	// Calculate indicator line end point
	qreal indicatorLength = knobRadius * 0.7;
	qreal offset = 1.5; // 3 is the line thickness - see bellow
	center = center + QPoint(offset, offset); 
	QPointF lineEnd(
		center.x() + indicatorLength * qCos(angleRad) + offset, 
		center.y() - indicatorLength * qSin(angleRad) + offset);

	// Draw indicator line
	QPen indicatorPen(Qt::white, 3); // White line as indicator
	painter.setPen(indicatorPen);
	painter.drawLine(center, lineEnd);

	// 5. Draw border circle around the knob
	int thickness = 5;
	QColor borderColor = isEnabled() ? circle_color.darker(150) : QColor(80, 80, 80);
	
	QPen borderPen(borderColor, thickness);
	painter.setPen(borderPen);
	painter.setBrush(Qt::NoBrush);
	
	int centerX = qRound(center.x());
	int centerY = qRound(center.y());
	int radius = qRound(knobRadius);
	
	painter.drawEllipse(QPoint(centerX, centerY), radius, radius);
}


void CustomDial::setKnobColor(QColor color)
{
	knob_color = color;
	update(); // Trigger repaint to apply new color
}

void CustomDial::setCircleColor(QColor color)
{
	circle_color = color;
	update(); // Trigger repaint to apply new color
}

