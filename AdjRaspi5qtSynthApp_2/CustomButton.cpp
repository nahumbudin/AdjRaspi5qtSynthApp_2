/**
 * @file		CustomButton.cpp
 *	@author		Nahum Budin
 *	@date		22-Dec-2025
 *	@version	1.0
 *					1. First version. Created using GitHub Copilot
 *
 *	@brief		Custom button class with advanced styling options
 */

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include "CustomButton.h"



CustomButton::CustomButton(QWidget *parent) 
	: QPushButton(parent)
	, frame_color(QColor(100, 100, 100))
	, frame_visible(true)
	, background_color(QColor(60, 60, 60))
	, text_color(Qt::white)
	, hover_color(QColor(80, 80, 80))
	, pressed_color(QColor(34, 200, 98))
	, is_hovered(false)
	, is_pressed(false)
{
	updateStyleSheet();
	setMouseTracking(true);
}

CustomButton::CustomButton(const QString &text, QWidget *parent)
	: QPushButton(text, parent)
	, frame_color(QColor(100, 100, 100))
	, frame_visible(true)
	, background_color(QColor(60, 60, 60))
	, text_color(Qt::white)
	, hover_color(QColor(80, 80, 80))
	, pressed_color(QColor(34, 200, 98))
	, is_hovered(false)
	, is_pressed(false)
{
	updateStyleSheet();
	setMouseTracking(true);
}

CustomButton::~CustomButton() {}


void CustomButton::paintEvent(QPaintEvent *event) 
{
	// First, let the default painting happen
	QPushButton::paintEvent(event);
	
	// Then draw our custom frame on top
	if (frame_visible) {
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);
		
		QRect buttonRect = rect();
		int frameMargin = 2;
		int frameThickness = 2;
		
		QRect frameRect = buttonRect.adjusted(
			frameMargin,
			frameMargin,
			-frameMargin,
			-frameMargin);
		
		// Use different frame color when pressed
		QColor currentFrameColor = frame_color;
		if (is_pressed) {
			currentFrameColor = pressed_color.darker(120);
		}
		else if (is_hovered) {
			currentFrameColor = frame_color.lighter(110);
		}
		
		QPen framePen(isEnabled() ? currentFrameColor : QColor(80, 80, 80), frameThickness);
		painter.setPen(framePen);
		painter.setBrush(Qt::NoBrush);
		painter.drawRect(frameRect);
	}
}


void CustomButton::enterEvent(QEvent *event)
{
	is_hovered = true;
	updateStyleSheet();
	QPushButton::enterEvent(event);
}

void CustomButton::leaveEvent(QEvent *event)
{
	is_hovered = false;
	updateStyleSheet();
	QPushButton::leaveEvent(event);
}

void CustomButton::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		is_pressed = true;
		updateStyleSheet();
	}
	QPushButton::mousePressEvent(event);
}

void CustomButton::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		is_pressed = false;
		updateStyleSheet();
	}
	QPushButton::mouseReleaseEvent(event);
}


void CustomButton::updateStyleSheet()
{
	QColor currentBgColor = background_color;
	
	if (!isEnabled()) {
		currentBgColor = QColor(100, 100, 100);
	}
	else if (is_pressed) {
		currentBgColor = pressed_color;
	}
	else if (is_hovered) {
		currentBgColor = hover_color;
	}
	
	setStyleSheet(QString(
		"QPushButton {"
		"    background-color: rgb(%1, %2, %3);"
		"    color: rgb(%4, %5, %6);"
		"    border: none;"
		"    padding: 8px 16px;"
		"    text-align: center;"
		"    font-size: 12px;"
		"}"
		"QPushButton:disabled {"
		"    background-color: rgb(100, 100, 100);"
		"    color: rgb(150, 150, 150);"
		"}"
	)
	.arg(currentBgColor.red()).arg(currentBgColor.green()).arg(currentBgColor.blue())
	.arg(text_color.red()).arg(text_color.green()).arg(text_color.blue())
	);
	
	update(); // Trigger repaint
}


void CustomButton::setFrameColor(QColor color)
{
	frame_color = color;
	update();
}

void CustomButton::setFrameVisible(bool visible)
{
	frame_visible = visible;
	update();
}

void CustomButton::setBackgroundColor(QColor color)
{
	background_color = color;
	updateStyleSheet();
}

void CustomButton::setTextColor(QColor color)
{
	text_color = color;
	updateStyleSheet();
}

void CustomButton::setHoverColor(QColor color)
{
	hover_color = color;
	updateStyleSheet();
}

void CustomButton::setPressedColor(QColor color)
{
	pressed_color = color;
	updateStyleSheet();
}
