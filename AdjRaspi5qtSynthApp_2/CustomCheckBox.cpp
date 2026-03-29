/**
 * @file		CustomCheckBox.cpp
 *	@author		Nahum Budin
 *	@date		22-Dec-2025
 *	@version	1.0
 *					1. First version. Created using GitHub Copilot
 *
 *	@brief		Custom checkbox class with advanced styling options
 */

#include "CustomCheckBox.h"
#include <QPainterPath>
#include <QStyleOption>

#include "Defs.h"

CustomCheckBox::CustomCheckBox(QWidget *parent)
	: QCheckBox(parent),
	  m_checkBoxColor(_CONTROLS_COLOR_BLACK),
	  m_checkMarkColor(QColor(0, 255, 0)),
	  m_frameColor(QColor(150, 150, 150)),
	  m_backgroundColor(_CONTROLS_COLOR_BLACK), 
	  m_textColor(QColor(255, 255, 255)), 
	  m_ledOnColor(QColor(0, 255, 0)), 
	  m_ledOffColor(QColor(50, 50, 50)), 
	  m_frameWidth(2), m_checkBoxSize(20), 
	  m_identifier(-1), 
	  m_readOnly(false), 
	  m_ledStyle(false), 
	  m_mouseOver(false), 
	  m_pressed(false)
{
	// Remove default styling
	setStyleSheet("");

	// Connect internal state changed signal
	connect(this, &QCheckBox::stateChanged, this, &CustomCheckBox::onStateChanged);
}

CustomCheckBox::~CustomCheckBox()
{
}

void CustomCheckBox::setCheckBoxColor(const QColor &color)
{
	m_checkBoxColor = color;
	update();
}

void CustomCheckBox::setCheckMarkColor(const QColor &color)
{
	m_checkMarkColor = color;
	update();
}

void CustomCheckBox::setFrameColor(const QColor &color)
{
	m_frameColor = color;
	update();
}

void CustomCheckBox::setBackgroundColor(const QColor &color)
{
	m_backgroundColor = color;
	update();
}

void CustomCheckBox::setTextColor(const QColor &color)
{
	m_textColor = color;
	update();
}

void CustomCheckBox::setFrameWidth(int width)
{
	m_frameWidth = qMax(1, width);
	update();
}

void CustomCheckBox::setCheckBoxSize(int size)
{
	m_checkBoxSize = qMax(10, size);
	setMinimumHeight(m_checkBoxSize + 4);
	update();
}

void CustomCheckBox::setReadOnly(bool readOnly)
{
	m_readOnly = readOnly;
	setEnabled(!readOnly);
}

void CustomCheckBox::setIdentifier(int id)
{
	m_identifier = id;
}

int CustomCheckBox::getIdentifier() const
{
	return m_identifier;
}

void CustomCheckBox::setLedStyle(bool enabled)
{
	m_ledStyle = enabled;
	update();
}

void CustomCheckBox::setLedOnColor(const QColor &color)
{
	m_ledOnColor = color;
	update();
}

void CustomCheckBox::setLedOffColor(const QColor &color)
{
	m_ledOffColor = color;
	update();
}

void CustomCheckBox::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	if (m_ledStyle)
	{
		drawLedCheckBox(painter);
	}
	else
	{
		drawCheckBox(painter);
	}
}

void CustomCheckBox::drawCheckBox(QPainter &painter)
{
	int boxSize = m_checkBoxSize;
	int boxX = 2;
	int boxY = (height() - boxSize) / 2;

	// Draw background
	painter.fillRect(rect(), m_backgroundColor);

	// Draw checkbox box
	QRectF checkBoxRect(boxX, boxY, boxSize, boxSize);

	// Fill checkbox
	QColor fillColor = m_checkBoxColor;
	if (m_mouseOver && !m_readOnly)
	{
		fillColor = fillColor.lighter(120);
	}
	if (m_pressed && !m_readOnly)
	{
		fillColor = fillColor.darker(120);
	}

	painter.fillRect(checkBoxRect, fillColor);

	// Draw frame
	painter.setPen(QPen(m_frameColor, m_frameWidth));
	painter.drawRect(checkBoxRect);

	// Draw check mark if checked
	if (isChecked())
	{
		painter.setPen(QPen(m_checkMarkColor, m_frameWidth + 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

		// Draw checkmark
		qreal margin = boxSize * 0.2;
		QPointF p1(boxX + margin, boxY + boxSize / 2);
		QPointF p2(boxX + boxSize * 0.4, boxY + boxSize - margin);
		QPointF p3(boxX + boxSize - margin, boxY + margin);

		painter.drawLine(p1, p2);
		painter.drawLine(p2, p3);
	}
	else if (checkState() == Qt::PartiallyChecked)
	{
		// Draw horizontal line for partially checked
		painter.setPen(QPen(m_checkMarkColor, m_frameWidth + 1));
		qreal margin = boxSize * 0.3;
		painter.drawLine(QPointF(boxX + margin, boxY + boxSize / 2),
						 QPointF(boxX + boxSize - margin, boxY + boxSize / 2));
	}

	// Draw text
	if (!text().isEmpty())
	{
		painter.setPen(m_textColor);
		QFont font = this->font();
		painter.setFont(font);

		QRectF textRect(boxX + boxSize + 5, 0, width() - boxX - boxSize - 7, height());
		painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text());
	}
}

void CustomCheckBox::drawLedCheckBox(QPainter &painter)
{
	int boxSize = m_checkBoxSize;
	int boxX = 2;
	int boxY = (height() - boxSize) / 2;

	// Draw background
	painter.fillRect(rect(), m_backgroundColor);

	// Draw LED circle
	QRectF ledRect(boxX, boxY, boxSize, boxSize);

	// Choose color based on state
	QColor ledColor = isChecked() ? m_ledOnColor : m_ledOffColor;

	if (m_mouseOver && !m_readOnly)
	{
		ledColor = ledColor.lighter(110);
	}

	// Draw outer glow if checked
	if (isChecked())
	{
		painter.setPen(Qt::NoPen);
		QRadialGradient gradient(ledRect.center(), boxSize * 0.7);
		gradient.setColorAt(0, ledColor);
		gradient.setColorAt(0.6, ledColor.darker(150));
		gradient.setColorAt(1, Qt::transparent);
		painter.setBrush(gradient);
		painter.drawEllipse(ledRect.adjusted(-3, -3, 3, 3));
	}

	// Draw LED body
	painter.setPen(QPen(m_frameColor, m_frameWidth));
	painter.setBrush(ledColor);
	painter.drawEllipse(ledRect);

	// Draw highlight
	if (isChecked())
	{
		QRectF highlightRect = ledRect.adjusted(boxSize * 0.2, boxSize * 0.2, -boxSize * 0.5, -boxSize * 0.5);
		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(255, 255, 255, 180));
		painter.drawEllipse(highlightRect);
	}

	// Draw text
	if (!text().isEmpty())
	{
		painter.setPen(m_textColor);
		QFont font = this->font();
		painter.setFont(font);

		QRectF textRect(boxX + boxSize + 5, 0, width() - boxX - boxSize - 7, height());
		painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text());
	}
}

void CustomCheckBox::enterEvent(QEvent *event)
{
	Q_UNUSED(event);
	m_mouseOver = true;
	update();

	if (m_identifier >= 0)
	{
		emit mouseEntered(m_identifier);
	}
}

void CustomCheckBox::leaveEvent(QEvent *event)
{
	Q_UNUSED(event);
	m_mouseOver = false;
	m_pressed = false;
	update();

	if (m_identifier >= 0)
	{
		emit mouseExited(m_identifier);
	}
}

void CustomCheckBox::mousePressEvent(QMouseEvent *event)
{
	if (m_readOnly)
	{
		event->ignore();
		return;
	}

	if (event->button() == Qt::LeftButton)
	{
		m_pressed = true;
		update();
	}

	QCheckBox::mousePressEvent(event);
}

void CustomCheckBox::mouseReleaseEvent(QMouseEvent *event)
{
	if (m_readOnly)
	{
		event->ignore();
		return;
	}

	m_pressed = false;
	update();

	QCheckBox::mouseReleaseEvent(event);
}

void CustomCheckBox::onStateChanged(int state)
{
	if (m_identifier >= 0)
	{
		emit stateChangedWithId(m_identifier, state == Qt::Checked);
	}
}
