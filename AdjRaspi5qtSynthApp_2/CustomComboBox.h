/**
 * @file		CustomComboBox.h
 *	@author		Nahum Budin
 *	@date		22-Dec-2025
 *	@version	1.0
 *					1. First version. Created using GitHub Copilot
 *					2. Added mouse hover event support (enterEvent/leaveEvent)
 *					3. Added int argument to mouse signals
 *
 *	@brief		Custom combobox class with advanced styling options
 */

#pragma once

#include <QComboBox>
#include <QColor>
#include <QStyledItemDelegate>
#include <QPainter>	
#include <QStyleOptionViewItem>
#include <QStylePainter>

class CenteredComboBoxDelegate : public QStyledItemDelegate
{
  public:
	explicit CenteredComboBoxDelegate(QObject *parent = nullptr)
		: QStyledItemDelegate(parent), alignment(Qt::AlignLeft | Qt::AlignVCenter) {}

	void setAlignment(Qt::Alignment align) { alignment = align; }

	void paint(QPainter *painter, const QStyleOptionViewItem &option,
			   const QModelIndex &index) const override
	{
		QStyleOptionViewItem opt = option;
		initStyleOption(&opt, index);
		opt.displayAlignment = alignment;
		QStyledItemDelegate::paint(painter, opt, index);
	}

  private:
	Qt::Alignment alignment;
};

class CustomComboBox : public QComboBox
{
	Q_OBJECT
	
  public:
	explicit CustomComboBox(QWidget *parent = nullptr);
	~CustomComboBox();

	// Styling methods
	void setFrameColor(QColor color);
	void setFrameVisible(bool visible);
	void setFrameWidth(int width);
	void setBackgroundColor(QColor color);
	void setTextColor(QColor color);

	void setIdentifier(int idn);
	int getIdentifier() const;

	void setTextAlignment(Qt::Alignment alignment);
	Qt::Alignment getTextAlignment() const;

signals:
	void mouseEntered(int id);
	void mouseExited(int i);

protected:
	void paintEvent(QPaintEvent *event) override;
	void enterEvent(QEvent *event) override;
	void leaveEvent(QEvent *event) override;

private:
	void updateStyleSheet();
  
	QColor frame_color;
	bool frame_visible;
	QColor background_color;
	QColor text_color;
	int frame_width;

	int id;

	Qt::Alignment text_alignment;
	QString alignmentToStyleString(Qt::Alignment alignment) const;

	CenteredComboBoxDelegate *delegate;
};