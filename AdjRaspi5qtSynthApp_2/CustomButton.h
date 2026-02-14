/**
 * @file		CustomButton.h
 *	@author		Nahum Budin
 *	@date		22-Dec-2025
 *	@version	1.0
 *					1. First version. Created using GitHub Copilot
 *
 *	@brief		Custom button class with advanced styling options
 */

#pragma once

#include <QPushButton>
#include <QColor>

	class CustomButton : public QPushButton
{
	Q_OBJECT

public :
	CustomButton(QWidget *parent = nullptr);
	CustomButton(const QString &text, QWidget *parent = nullptr);
	~CustomButton();
	
	void setFrameColor(QColor color);
	void setFrameVisible(bool visible);
	void setBackgroundColor(QColor color);
	void setTextColor(QColor color);
	void setHoverColor(QColor color);
	void setPressedColor(QColor color);

protected:
	void paintEvent(QPaintEvent *event) override;
	void enterEvent(QEvent *event) override;
	void leaveEvent(QEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

private:
	QColor frame_color;
	bool frame_visible;
	QColor background_color;
	QColor text_color;
	QColor hover_color;
	QColor pressed_color;
	
	bool is_hovered;
	bool is_pressed;
	
	void updateStyleSheet();
};