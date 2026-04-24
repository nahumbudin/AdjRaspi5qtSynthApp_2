/**
 * @file		CustomFrame.h
 *	@author		Nahum Budin
 *	@date		23-Dec-2025
 *	@version	1.0
 *					1. First version. Created using GitHub Copilot
 *
 *	@brief		Custom frame class with advanced styling options
 */

#pragma once

#include <QFrame>
#include <QColor>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>

class CustomFrame : public QFrame
{
	//Q_OBJECT

  public:
	explicit CustomFrame(QWidget *parent = nullptr);
	~CustomFrame();

	void setBorderColor(const QColor &color);
	void setBorderWidth(int width);
	void setTopBorderWidth(int width);
	void setRightBorderWidth(int width);
	void setBottomBorderWidth(int width);
	void setLeftBorderWidth(int width);
	void setBorderStyle(Qt::PenStyle style);

	QColor borderColor() const { return m_borderColor; }
	int borderWidth() const { return m_borderWidth; }

  protected:
	void paintEvent(QPaintEvent *event) override;

  private:
	QColor m_borderColor;
	int m_borderWidth;
	int m_topBorderWidth;
	int m_rightBorderWidth;
	int m_bottomBorderWidth;
	int m_leftBorderWidth;
	Qt::PenStyle m_borderStyle;
	bool m_useIndividualWidths;
};

