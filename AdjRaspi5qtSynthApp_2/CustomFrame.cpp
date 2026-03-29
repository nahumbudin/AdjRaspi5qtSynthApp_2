/**
 * @file		CustomFrame.cpp
 *	@author		Nahum Budin
 *	@date		23-Dec-2025
 *	@version	1.0
 *					1. First version. Created using GitHub Copilot
 *
 *	@brief		Custom frame class with advanced styling options
 */

#include "CustomFrame.h"
#include "Defs.h"

CustomFrame::CustomFrame(QWidget *parent)
	: QFrame(parent)
	, m_borderColor(Qt::black)
	, m_borderWidth(1)
	, m_topBorderWidth(1)
	, m_rightBorderWidth(1)
	, m_bottomBorderWidth(1)
	, m_leftBorderWidth(1)
	, m_borderStyle(Qt::SolidLine)
	, m_useIndividualWidths(false)
{
	setFrameShape(QFrame::NoFrame);
}

CustomFrame::~CustomFrame()
{
}

void CustomFrame::setBorderColor(const QColor &color)
{
	m_borderColor = color;
	update();
}

void CustomFrame::setBorderWidth(int width)
{
	m_borderWidth = width;
	m_topBorderWidth = width;
	m_rightBorderWidth = width;
	m_bottomBorderWidth = width;
	m_leftBorderWidth = width;
	m_useIndividualWidths = false;
	update();
}

void CustomFrame::setTopBorderWidth(int width)
{
	m_topBorderWidth = width;
	m_useIndividualWidths = true;
	update();
}

void CustomFrame::setRightBorderWidth(int width)
{
	m_rightBorderWidth = width;
	m_useIndividualWidths = true;
	update();
}

void CustomFrame::setBottomBorderWidth(int width)
{
	m_bottomBorderWidth = width;
	m_useIndividualWidths = true;
	update();
}

void CustomFrame::setLeftBorderWidth(int width)
{
	m_leftBorderWidth = width;
	m_useIndividualWidths = true;
	update();
}

void CustomFrame::setBorderStyle(Qt::PenStyle style)
{
	m_borderStyle = style;
	update();
}

void CustomFrame::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);

	// Fill background and draw custom borders
	QPainter painter(this);
	painter.fillRect(rect(), _CONTROLS_COLOR_BLACK);
	painter.setRenderHint(QPainter::Antialiasing);

	if (m_useIndividualWidths)
	{
		// Draw each border individually with different widths
		if (m_topBorderWidth > 0)
		{
			QPen pen(m_borderColor, m_topBorderWidth, m_borderStyle);
			painter.setPen(pen);
			painter.drawLine(0, m_topBorderWidth / 2, width(), m_topBorderWidth / 2);
		}

		if (m_rightBorderWidth > 0)
		{
			QPen pen(m_borderColor, m_rightBorderWidth, m_borderStyle);
			painter.setPen(pen);
			painter.drawLine(width() - m_rightBorderWidth / 2, 0, width() - m_rightBorderWidth / 2, height());
		}

		if (m_bottomBorderWidth > 0)
		{
			QPen pen(m_borderColor, m_bottomBorderWidth, m_borderStyle);
			painter.setPen(pen);
			painter.drawLine(0, height() - m_bottomBorderWidth / 2, width(), height() - m_bottomBorderWidth / 2);
		}

		if (m_leftBorderWidth > 0)
		{
			QPen pen(m_borderColor, m_leftBorderWidth, m_borderStyle);
			painter.setPen(pen);
			painter.drawLine(m_leftBorderWidth / 2, 0, m_leftBorderWidth / 2, height());
		}
	}
	else
	{
		// Draw uniform border
		if (m_borderWidth > 0)
		{
			QPen pen(m_borderColor, m_borderWidth, m_borderStyle);
			painter.setPen(pen);

			int halfWidth = m_borderWidth / 2;
			QRect rect = this->rect().adjusted(halfWidth, halfWidth, -halfWidth, -halfWidth);
			painter.drawRect(rect);
		}
	}
}
