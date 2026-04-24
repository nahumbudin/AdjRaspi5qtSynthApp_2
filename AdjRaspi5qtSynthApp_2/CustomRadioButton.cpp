/**
 * @file		CustomRadioButton.h
 *	@author		Nahum Budin
 *	@date		3-Apr-2026
 *	@version	1.0
 *
 *	@brief		Custom radio button class with advanced styling options
 *				(Created with the assistance of GitHub Copilot)
 */

#include "CustomRadioButton.h"
#include <QPainterPath>
#include <QRadialGradient>

CustomRadioButton::CustomRadioButton(QWidget *parent)
	: QRadioButton(parent), frameColor(Qt::gray), backgroundColor(Qt::black), indicatorColor(Qt::white), ledOnColor(Qt::green), ledOffColor(Qt::darkGray), buttonSize(20), frameWidth(2), ledStyle(false)
{
	setMinimumHeight(buttonSize + 4);
}

void CustomRadioButton::setFrameColor(const QColor &color)
{
	frameColor = color;
	update();
}

void CustomRadioButton::setBackgroundColor(const QColor &color)
{
	backgroundColor = color;
	update();
}

void CustomRadioButton::setIndicatorColor(const QColor &color)
{
	indicatorColor = color;
	update();
}

void CustomRadioButton::setLedStyle(bool enabled)
{
	ledStyle = enabled;
	update();
}

void CustomRadioButton::setLedOnColor(const QColor &color)
{
	ledOnColor = color;
	update();
}

void CustomRadioButton::setLedOffColor(const QColor &color)
{
	ledOffColor = color;
	update();
}

void CustomRadioButton::setButtonSize(int size)
{
	buttonSize = size;
	setMinimumHeight(size + 4);
	update();
}

void CustomRadioButton::setFrameWidth(int width)
{
	frameWidth = width;
	update();
}

QSize CustomRadioButton::sizeHint() const
{
	QSize textSize = fontMetrics().size(Qt::TextShowMnemonic, text());
	return QSize(buttonSize + 8 + textSize.width(), qMax(buttonSize + 4, textSize.height()));
}

QSize CustomRadioButton::minimumSizeHint() const
{
	return QSize(buttonSize + 4, buttonSize + 4);
}

void CustomRadioButton::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	// Calculate button rectangle (left-aligned, circular)
	QRect buttonRect(2, (height() - buttonSize) / 2, buttonSize, buttonSize);

	// Draw radio button (either LED or standard)
	if (ledStyle)
	{
		drawLedRadio(painter, buttonRect);
	}
	else
	{
		drawStandardRadio(painter, buttonRect);
	}

	// Draw text label
	if (!text().isEmpty())
	{
		QRect textRect(buttonRect.right() + 8, 0, width() - buttonRect.right() - 10, height());
		painter.setPen(palette().text().color());
		painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text());
	}
}

void CustomRadioButton::drawStandardRadio(QPainter &painter, const QRect &buttonRect)
{
	// Draw outer circle (frame)
	painter.setPen(QPen(frameColor, frameWidth));
	painter.setBrush(backgroundColor);
	painter.drawEllipse(buttonRect);

	// Draw inner indicator if checked
	if (isChecked())
	{
		int indicatorMargin = buttonSize / 4;
		QRect indicatorRect = buttonRect.adjusted(indicatorMargin, indicatorMargin,
												  -indicatorMargin, -indicatorMargin);

		painter.setPen(Qt::NoPen);
		painter.setBrush(indicatorColor);
		painter.drawEllipse(indicatorRect);
	}
}

void CustomRadioButton::drawLedRadio(QPainter &painter, const QRect &buttonRect)
{
	// Draw outer circle (frame)
	painter.setPen(QPen(frameColor, frameWidth));
	painter.setBrush(backgroundColor);
	painter.drawEllipse(buttonRect);

	// Draw inner LED
	if (isChecked())
	{
		int ledMargin = buttonSize / 4;
		QRect ledRect = buttonRect.adjusted(ledMargin, ledMargin, -ledMargin, -ledMargin);

		// Create radial gradient for LED glow effect
		QRadialGradient gradient(ledRect.center(), ledRect.width() / 2);
		gradient.setColorAt(0, ledOnColor.lighter(180));
		gradient.setColorAt(0.4, ledOnColor.lighter(140));
		gradient.setColorAt(0.7, ledOnColor);
		gradient.setColorAt(1, ledOnColor.darker(120));

		painter.setPen(Qt::NoPen);
		painter.setBrush(gradient);
		painter.drawEllipse(ledRect);

		// Add outer glow
		painter.setPen(QPen(ledOnColor.lighter(150), 1));
		painter.setBrush(Qt::NoBrush);
		painter.drawEllipse(ledRect.adjusted(-1, -1, 1, 1));
	}
	else
	{
		// Draw dimmed LED when off
		int ledMargin = buttonSize / 4;
		QRect ledRect = buttonRect.adjusted(ledMargin, ledMargin, -ledMargin, -ledMargin);
		painter.setPen(Qt::NoPen);
		painter.setBrush(ledOffColor);
		painter.drawEllipse(ledRect);
	}
}
