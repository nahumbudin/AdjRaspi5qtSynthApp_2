/**
 * @file		CustomCheckBox.h
 *	@author		Nahum Budin
 *	@date		22-Dec-2025
 *	@version	1.0
 *					1. First version. Created using GitHub Copilot
 *
 *	@brief		Custom checkbox class with advanced styling options
 */

#pragma once

#include <QCheckBox>
#include <QColor>
#include <QMouseEvent>
#include <QPainter>

class CustomCheckBox : public QCheckBox
{
	Q_OBJECT

  public:
	explicit CustomCheckBox(QWidget *parent = nullptr);
	~CustomCheckBox();

	// Styling methods
	void setCheckBoxColor(const QColor &color);
	void setCheckMarkColor(const QColor &color);
	void setFrameColor(const QColor &color);
	void setBackgroundColor(const QColor &color);
	void setTextColor(const QColor &color);
	void setFrameWidth(int width);
	void setCheckBoxSize(int size);
	void setReadOnly(bool readOnly);

	// Identifier for signal routing
	void setIdentifier(int id);
	int getIdentifier() const;

	// LED-style checkbox (for activity indicators)
	void setLedStyle(bool enabled);
	void setLedOnColor(const QColor &color);
	void setLedOffColor(const QColor &color);

  signals:
	void mouseEntered(int identifier);
	void mouseExited(int identifier);
	void stateChangedWithId(int identifier, bool checked);

  protected:
	void paintEvent(QPaintEvent *event) override;
	void enterEvent(QEvent *event) override;
	void leaveEvent(QEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

  private slots:
	void onStateChanged(int state);

  private:
	QColor m_checkBoxColor;
	QColor m_checkMarkColor;
	QColor m_frameColor;
	QColor m_backgroundColor;
	QColor m_textColor;
	QColor m_ledOnColor;
	QColor m_ledOffColor;

	int m_frameWidth;
	int m_checkBoxSize;
	int m_identifier;

	bool m_readOnly;
	bool m_ledStyle;
	bool m_mouseOver;
	bool m_pressed;

	void drawCheckBox(QPainter &painter);
	void drawLedCheckBox(QPainter &painter);
};