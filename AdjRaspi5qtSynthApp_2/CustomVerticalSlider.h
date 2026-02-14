/**
 * @file		CustomVerticalSlider.h
 *	@author		Nahum Budin
 *	@date		22-Dec-2025
 *	@version	1.0
 *					1. First version. Created using GitHub Copilot
 *
 *	@brief		Custom vertical slider class with advanced styling options
 */

#pragma once

#include <QWidget>
#include <QSlider>

class CustomVerticalSlider : public QSlider
{
public:
	CustomVerticalSlider(QWidget *parent = nullptr);
	~CustomVerticalSlider();
	
	void setHandleColor(QColor color);
	void setTrackColor(QColor color);
	void setProgressColor(QColor color);
	void setFrameColor(QColor color);
	void setFrameVisible(bool visible);
	void setBackgroundColor(QColor color);

protected:
	void paintEvent(QPaintEvent *event) override;
	QSize sizeHint() const override;

private:
	QColor handle_color;
	QColor track_color;
	QColor progress_color;
	QColor frame_color;
	bool frame_visible;
	QColor background_color;
};
