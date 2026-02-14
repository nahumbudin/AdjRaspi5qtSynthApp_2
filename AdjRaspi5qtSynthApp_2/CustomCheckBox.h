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

class CustomCheckBox : public QCheckBox
{
public:
	CustomCheckBox(QWidget *parent = nullptr);
	CustomCheckBox(const QString &text, QWidget *parent = nullptr);
	~CustomCheckBox();
	
	void setFrameColor(QColor color);
	void setFrameVisible(bool visible);
	void setBackgroundColor(QColor color);
	void setTextColor(QColor color);
	void setCheckColor(QColor color);

	void setReadOnly(bool readOnly) { read_only = readOnly; }
	bool isReadOnly() const { return read_only; }

 public slots:
	void setChecked(bool checked);

protected:
	void paintEvent(QPaintEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;

	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

private:
	QColor frame_color;
	bool frame_visible;
	QColor background_color;
	QColor text_color;
	QColor check_color;

	bool read_only;
	
	void updateStyleSheet();
	int calculateIndicatorSize() const;
};