/**
 * @file		CustomDial.h
 *	@author		Nahum Budin
 *	@date		22-Dec-2025
 *	@version	1.0
 *					1. First version. Created using GitHub Copilot
 *
 *	@brief		Custom dial class with advanced styling options
 */

#pragma once

#include <QWidget>
#include <QDial>

class CustomDial : public QDial
{
public:
    CustomDial(QWidget *parent = nullptr);
    ~CustomDial();
	
	void setColor(QColor color);
	void setKnobColor(QColor color);
	void setCircleColor(QColor color);
	void setIndicatorVisible(bool visible);

  protected:
    void paintEvent(QPaintEvent *event) override;
    QSize sizeHint() const override;

private:
    int m_value;
	
	QColor knob_color;
	QColor circle_color;
	bool indicator_visible;
};