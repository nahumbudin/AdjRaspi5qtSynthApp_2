/**
 * @file		CustomDrawbar.h
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

#pragma once

#include <QColor>
#include <QSlider>

class CustomDrawbar : public QSlider
{
	Q_OBJECT

  public:
	explicit CustomDrawbar(QWidget *parent = nullptr);
	~CustomDrawbar();

	void setTipColor(QColor color);
	void setBodyColor(QColor color);
	void setSlotColor(QColor color);
	void setGripLineColor(QColor color);
	void setShowNotches(bool show);

	QSize sizeHint() const override;

  protected:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

  private:
	QColor tip_color;
	QColor body_color;
	QColor slot_color;
	QColor grip_line_color;
	bool show_notches;
};
