/**
 * @file		CustomTabWidget.h
 * @author		Nahum Budin
 * @date		11-Jan-2026
 * @version	1.0
 *		1. First version. Created using GitHub Copilot
 *
 * @brief		Custom QTabWidget that allows tabs with different sizes
 *
 */

#pragma once

#include <QMap>
#include <QResizeEvent>
#include <QSize>
#include <QTabBar>
#include <QTabWidget>

class CustomTabBar : public QTabBar
{
	Q_OBJECT

  public:
	explicit CustomTabBar(QWidget *parent = nullptr);

	void setTabSize(int index, const QSize &size);
	QSize getTabSize(int index) const;
	void clearTabSizes();

  protected:
	QSize tabSizeHint(int index) const override;
	QSize minimumTabSizeHint(int index) const override;

  private:
	QMap<int, QSize> tab_sizes;
};

class CustomTabWidget : public QTabWidget
{
	Q_OBJECT

  public:
	explicit CustomTabWidget(QWidget *parent = nullptr);

	/**
	 * @brief Set custom size for a specific tab
	 * @param index Tab index
	 * @param size Custom size for the tab
	 */
	void setTabSize(int index, const QSize &size);

	/**
	 * @brief Set custom width for a specific tab
	 * @param index Tab index
	 * @param width Custom width for the tab
	 */
	void setTabWidth(int index, int width);

	/**
	 * @brief Set custom height for a specific tab
	 * @param index Tab index
	 * @param height Custom height for the tab
	 */
	void setTabHeight(int index, int height);

	/**
	 * @brief Get the custom size for a specific tab
	 * @param index Tab index
	 * @return Custom size, or default size if not set
	 */
	QSize getTabSize(int index) const;

	/**
	 * @brief Clear all custom tab sizes
	 */
	void clearTabSizes();

  protected:
	void resizeEvent(QResizeEvent *event) override;

  private:
	CustomTabBar *custom_tab_bar;
};

