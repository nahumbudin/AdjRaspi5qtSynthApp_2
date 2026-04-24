/**
 * @file		CustomRadioButton.h
 *	@author		Nahum Budin
 *	@date		3-Apr-2026
 *	@version	1.0
 *
 *	@brief		Custom radio button class with advanced styling options
 *				(Created with the assistance of GitHub Copilot)
 */

#pragma once

#include <QRadioButton>
#include <QColor>
#include <QPainter>
#include <QStyleOption>

class CustomRadioButton : public QRadioButton
{
	Q_OBJECT

  public:
	explicit CustomRadioButton(QWidget *parent = nullptr);

	void setFrameColor(const QColor &color);
	void setBackgroundColor(const QColor &color);
	void setIndicatorColor(const QColor &color);
	void setLedStyle(bool enabled);
	void setLedOnColor(const QColor &color);
	void setLedOffColor(const QColor &color);
	void setButtonSize(int size);
	void setFrameWidth(int width);

  protected:
	void paintEvent(QPaintEvent *event) override;
	QSize sizeHint() const override;
	QSize minimumSizeHint() const override;

  private:
	QColor frameColor;
	QColor backgroundColor;
	QColor indicatorColor;
	QColor ledOnColor;
	QColor ledOffColor;
	int buttonSize;
	int frameWidth;
	bool ledStyle;

	void drawStandardRadio(QPainter &painter, const QRect &buttonRect);
	void drawLedRadio(QPainter &painter, const QRect &buttonRect);
};
