/**
 * @file		CustomTabWidget.cpp
 * @author		Nahum Budin
 * @date		11-Jan-2026
 * @version	1.0
 *		1. First version. Created using GitHub Copilot
 *
 * @brief		Custom QTabWidget that allows tabs with different sizes
 *
 */

#include "CustomTabWidget.h"

// CustomTabBar Implementation

CustomTabBar::CustomTabBar(QWidget *parent)
	: QTabBar(parent)
{
	// Allow tabs to be different sizes
	setExpanding(false);
	setDrawBase(false);
}

void CustomTabBar::setTabSize(int index, const QSize &size)
{
	if (index >= 0 && index < count())
	{
		tab_sizes[index] = size;
		update();
	}
}

QSize CustomTabBar::getTabSize(int index) const
{
	if (tab_sizes.contains(index))
	{
		return tab_sizes[index];
	}

	return QTabBar::tabSizeHint(index);
}

void CustomTabBar::clearTabSizes()
{
	tab_sizes.clear();
	update();
}

QSize CustomTabBar::tabSizeHint(int index) const
{
	if (tab_sizes.contains(index))
	{
		return tab_sizes[index];
	}

	// Return default size hint
	return QTabBar::tabSizeHint(index);
}

QSize CustomTabBar::minimumTabSizeHint(int index) const
{
	if (tab_sizes.contains(index))
	{
		return tab_sizes[index];
	}

	// Return default minimum size hint
	return QTabBar::minimumTabSizeHint(index);
}

// CustomTabWidget Implementation

CustomTabWidget::CustomTabWidget(QWidget *parent)
	: QTabWidget(parent)
{
	custom_tab_bar = new CustomTabBar(this);
	setTabBar(custom_tab_bar);
}

void CustomTabWidget::setTabSize(int index, const QSize &size)
{
	custom_tab_bar->setTabSize(index, size);
}

void CustomTabWidget::setTabWidth(int index, int width)
{
	QSize current_size = custom_tab_bar->getTabSize(index);
	current_size.setWidth(width);
	custom_tab_bar->setTabSize(index, current_size);
}

void CustomTabWidget::setTabHeight(int index, int height)
{
	QSize current_size = custom_tab_bar->getTabSize(index);
	current_size.setHeight(height);
	custom_tab_bar->setTabSize(index, current_size);
}

QSize CustomTabWidget::getTabSize(int index) const
{
	return custom_tab_bar->getTabSize(index);
}

void CustomTabWidget::clearTabSizes()
{
	custom_tab_bar->clearTabSizes();
}

void CustomTabWidget::resizeEvent(QResizeEvent *event)
{
	QTabWidget::resizeEvent(event);

	// Force tab bar to update with new sizes
	custom_tab_bar->update();
}