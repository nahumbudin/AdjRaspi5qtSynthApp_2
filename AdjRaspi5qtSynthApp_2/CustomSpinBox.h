/**
 * @file		CustomSpinBox.h
 *	@author		Nahum Budin
 *	@date		19-Mar-2026
 *	@version	1.0
 *
 *	@brief		Custom spinbox class with advanced styling options
 *				(Created with the assistance of GitHub Copilot)
 */

#pragma once

#include <QColor>
#include <QPainter>
#include <QSpinBox>

class CustomSpinBox : public QSpinBox
{
	Q_OBJECT

  public:
	explicit CustomSpinBox(QWidget *parent = nullptr);
	~CustomSpinBox();

	// Styling methods
	void setFrameColor(QColor color);
	void setFrameVisible(bool visible);
	void setFrameWidth(int width);
	void setBackgroundColor(QColor color);
	void setTextColor(QColor color);
	void setTextAlignment(Qt::Alignment alignment);

	void setIdentifier(int idn);
	int getIdentifier() const;

  signals:
	void mouseEntered(int id);
	void mouseExited(int id);

  protected:
	void paintEvent(QPaintEvent *event) override;
	void enterEvent(QEvent *event) override;
	void leaveEvent(QEvent *event) override;

  private:
	void updateStyleSheet();

	QColor frame_color;
	bool frame_visible;
	int frame_width;
	QColor background_color;
	QColor text_color;
	Qt::Alignment text_alignment;
	int id;
};
