/**
 * @file		GuiNavigator.h
 *	@author		Nahum Budin
 *	@date		21-Feb-2026
 *	@version	1.1
 *					1. Redesigned to handle only open dialogs
 *
 *	@brief		Navigation through open dialogs, tabs and frames using the control box.
 *
 *				Left/Right = cycle through open dialogs and set the focus on the selected dialog 
 *				Up/Down = in dialogs that has tabs, cycle through 2 modes: 
 *					1) scrollrotation cycle through tabs 
 *					2) cycles through frames (default if no tabs) 
 *				Scroll rotation = cycle throgh focused dialog tabs or frames . 
 *				Scroll button = TBD 
 *				OK = TBD

 *
 *	History:
 *
 *				Coded with the assistance of GitHub Copilot
 */

/**
 * @file		GuiNavigator.h
 *	@author		Nahum Budin
 *	@date		27-Jan-2026
 *	@version	1.2
 *				Added white and gray frame sets (4 pointers each)
 */

#pragma once

#include <QDialog>
#include <QList>
#include <QMap>
#include <QObject>
#include <QString>
#include <QTabWidget>

#include "CustomFrame.h"
#include "GuiNavigatorInfoPanel.h"

class CustomFrame;

enum DialogNavigationMode
{
	TAB_NAVIGATION_MODE,
	FRAME_NAVIGATION_MODE
};

// Structure to hold frame information
struct FrameInfo
{
	QString name;				  // Frame display name
	CustomFrame *white_frames[4]; // White frame widgets (4 pointers)
	CustomFrame *gray_frames[4];  // Gray frame widgets (4 pointers)

	FrameInfo() : name("")
	{
		for (int i = 0; i < 4; i++)
		{
			white_frames[i] = nullptr;
			gray_frames[i] = nullptr;
		}
	}

	FrameInfo(const QString &n) : name(n)
	{
		for (int i = 0; i < 4; i++)
		{
			white_frames[i] = nullptr;
			gray_frames[i] = nullptr;
		}
	}
};

// Structure to hold dialog information
struct DialogInfo
{
	QWidget *dialog;
	QString name;
	QTabWidget *tab_widget;
	QMap<int, QList<FrameInfo>> frames_per_tab; // For tab-based dialogs
	QList<FrameInfo> frames;					// For simple non-tab dialogs ← ADD THIS LINE
	int current_frame_index;
	DialogNavigationMode current_mode;
	bool supports_navigation; // Indicates if widget supports frame/tab navigation

	DialogInfo()
		: dialog(nullptr), name(""), tab_widget(nullptr), current_frame_index(0), current_mode(FRAME_NAVIGATION_MODE)
	{
	}
};

class GuiNavigator : public QObject
{
	Q_OBJECT

  public:
	static GuiNavigator *get_instance();

	// Control box button handlers
	void handle_left_button();
	void handle_right_button();
	void handle_up_button();
	void handle_down_button();
	void handle_scroll_rotation(int delta);
	void handle_scroll_button();
	void handle_ok_button();

	// Dialog management - old method (converts QString to FrameInfo)
	void register_dialog(QWidget *dialog, const QString &name,
						 QTabWidget *tab_widget = nullptr,
						 const QMap<int, QList<QString>> &frame_names_per_tab = QMap<int, QList<QString>>());

	// New method with FrameInfo support
	void register_dialog_with_frames(QWidget *dialog, const QString &name,
									 QTabWidget *tab_widget = nullptr,
									 const QMap<int, QList<FrameInfo>> &frames_per_tab = QMap<int, QList<FrameInfo>>());

	// Simple registration for widgets without frame/tab navigation (like MainWindow)
	void register_widget_simple(QWidget *widget, const QString &name);
	void unregister_dialog(QWidget *dialog);

	// Set white frame widgets for a specific frame
	void set_white_frame_widgets(QWidget *dialog, int tab_index, int frame_index,
								 CustomFrame *widget1, CustomFrame *widget2 = nullptr,
								 CustomFrame *widget3 = nullptr, CustomFrame *widget4 = nullptr);

	// Set gray frame widgets for a specific frame
	void set_gray_frame_widgets(QWidget *dialog, int tab_index, int frame_index,
								CustomFrame *widget1, CustomFrame *widget2 = nullptr,
								CustomFrame *widget3 = nullptr, CustomFrame *widget4 = nullptr);

	void update_dialog_frames(QWidget *dialog, int tab_index, const QList<QString> &frame_names);
	void update_all_dialog_frames(QWidget *dialog, const QMap<int, QList<QString>> &frames_per_tab);

	// Info panel
	void show_info_panel();
	void hide_info_panel();
	void toggle_info_panel();

	// Focus management
	void focus_on_dialog(QWidget *dialog);

	// Queries
	QWidget *get_current_dialog() const;
	QString get_current_dialog_name() const;
	int get_dialog_count() const;
	DialogNavigationMode get_current_mode() const;
	QString get_current_frame_name() const;
	int get_current_frame_index() const;
	int get_current_tab_index() const;

	// Get current frame widgets
	const CustomFrame *const *get_current_white_frames() const;
	const CustomFrame *const *get_current_gray_frames() const;

	void refresh_current_highlight();

  signals:
	void dialog_changed(QWidget *dialog, const QString &name);
	void frame_changed(const QString &frame_name, int frame_index);
	void mode_changed(DialogNavigationMode mode);

  private:
	GuiNavigator();
	~GuiNavigator();

	static GuiNavigator *instance;

	void cycle_dialog_next();
	void cycle_dialog_previous();
	void toggle_navigation_mode();
	void cycle_tabs_forward();
	void cycle_tabs_backward();
	void cycle_frames_forward();
	void cycle_frames_backward();

	// Frame highlighting (automatic)
	void highlight_frame(int frame_index);
	void unhighlight_frame(int frame_index);
	void unhighlight_all_frames();

	QList<FrameInfo> get_current_tab_frames() const;
	void focus_dialog(QWidget *dialog);
	void cleanup_invisible_dialogs();
	int find_dialog_index(QWidget *dialog);
	void update_info_panel();

	QList<DialogInfo> dialogs;
	int current_dialog_index;

	GuiNavigatorInfoPanel *info_panel;
};