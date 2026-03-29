/**
 * @file		GuiNavigatorInfoPanel.h
 *	@author		Nahum Budin
 *	@date		21-Feb-2026
 *	@version	1.0
 *
 *	@brief		Info panel widget for GuiNavigator to display navigation state
 *
 *	History:
 *				Coded with the assistance of GitHub Copilot
 */

#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>

class GuiNavigatorInfoPanel : public QWidget
{
	Q_OBJECT

  public:
	explicit GuiNavigatorInfoPanel(QWidget *parent = nullptr);
	~GuiNavigatorInfoPanel();

	void update_info(const QString &line1, const QString &line2);
	void show_panel();
	void hide_panel();

  protected:
	// Mouse event handlers for dragging
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

  private:
	QLabel *label_line1;
	QLabel *label_line2;
	QVBoxLayout *layout;

	// Drag state
	bool is_dragging;
	QPoint drag_start_position;
};
