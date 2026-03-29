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

#include "GuiNavigator.h"
#include <QDebug>
#include <QApplication>
#include <QKeyEvent>
#include <QTimer>
#include <MainWindow.h>



#include "Defs.h"

GuiNavigator *GuiNavigator::instance = nullptr;

GuiNavigator::GuiNavigator()
	: current_dialog_index(-1), info_panel(nullptr)
{
	// Create info panel
	info_panel = new GuiNavigatorInfoPanel();
	info_panel->hide();

	qDebug() << "GuiNavigator: Initialized (Frames per Tab)";
}

GuiNavigator::~GuiNavigator()
{
	if (info_panel)
	{
		delete info_panel;
		info_panel = nullptr;
	}
}

GuiNavigator *GuiNavigator::get_instance()
{
	if (instance == nullptr)
	{
		instance = new GuiNavigator();
	}
	return instance;
}

// ============================================================================
// Control Box Button Handlers
// ============================================================================

void GuiNavigator::handle_left_button()
{
	qDebug() << "GuiNavigator: Left button - Previous dialog";
	cycle_dialog_previous();
}

void GuiNavigator::handle_right_button()
{
	qDebug() << "GuiNavigator: Right button - Next dialog";
	cycle_dialog_next();
}

void GuiNavigator::handle_up_button()
{
	qDebug() << "GuiNavigator: Up button - Toggle mode";
	toggle_navigation_mode();
}

void GuiNavigator::handle_down_button()
{
	qDebug() << "GuiNavigator: Down button - Toggle mode";
	toggle_navigation_mode();
}

void GuiNavigator::handle_scroll_rotation(int delta)
{
	static int accumulated_delta = 0;
	static int prev_delta = 0;

	// Wrap around detection
	if (abs(delta) > 100)
	{
		delta = 0;
	}

	// wait for 2 deltas with the same sign before acting, to prevent noise and small accidental rotations from triggering navigation
	if ((delta > 0 && prev_delta < 0) || (delta < 0 && prev_delta > 0))
	{
		accumulated_delta = 0; // Reset accumulated delta on direction change
	}

	prev_delta = delta;

	accumulated_delta += delta;

	fprintf(stderr, "Delta=%i Acc Delta=%i\n", delta, accumulated_delta);

	if (dialogs.isEmpty() || current_dialog_index < 0)
	{
		qDebug() << "GuiNavigator: No active dialog for scroll";
		return;
	}

	DialogInfo &current = dialogs[current_dialog_index];

	if (current.current_mode == TAB_NAVIGATION_MODE && current.tab_widget)
	{
		// Cycle through tabs
		if (accumulated_delta > 3)
		{
			cycle_tabs_forward();
			accumulated_delta = 0;
			QTimer::singleShot(200, []() {}); // Small delay to prevent rapid cycling
		}
		else if (accumulated_delta < -3)
		{
			cycle_tabs_backward();
			accumulated_delta = 0;
			QTimer::singleShot(200, []() {}); // Small delay to prevent rapid cycling
		}
	}
	else
	{
		// Cycle through frames
		if (accumulated_delta >= 4)
		{
			cycle_frames_forward();
			accumulated_delta = 0;
			QTimer::singleShot(200, []() {}); // Small delay to prevent rapid cycling
		}
		else if (accumulated_delta <= -4)
		{
			cycle_frames_backward();
			accumulated_delta = 0;
			QTimer::singleShot(200, []() {}); // Small delay to prevent rapid cycling
		}
	}

	update_info_panel();
}

void GuiNavigator::handle_scroll_button()
{
	qDebug() << "GuiNavigator: Scroll button - TBD";
	// To be determined
}

void GuiNavigator::handle_ok_button()
{
	qDebug() << "GuiNavigator: OK button - TBD";
	// To be determined
}

// ============================================================================
// Dialog Management
// ============================================================================

void GuiNavigator::register_widget_simple(QWidget *widget, const QString &name)
{
	if (!widget)
		return;

	// Check if already registered
	int index = find_dialog_index(widget);
	if (index >= 0)
	{
		qDebug() << "GuiNavigator: Widget already registered:" << name;
		return;
	}

	// Add simple widget with no navigation support
	DialogInfo info;
	info.dialog = widget;
	info.name = name;
	info.tab_widget = nullptr;
	info.current_frame_index = 0;
	info.current_mode = FRAME_NAVIGATION_MODE;
	info.supports_navigation = false; // No frame/tab navigation

	dialogs.append(info);

	// Make this the current dialog
	current_dialog_index = dialogs.count() - 1;

	connect(widget, &QWidget::destroyed, this, [this, widget]() {
		unregister_dialog(widget);
	});

	emit dialog_changed(widget, name);

	qDebug() << "GuiNavigator: Registered simple widget:" << name;

	update_info_panel();
}

void GuiNavigator::register_dialog(QWidget *dialog, const QString &name,
								   QTabWidget *tab_widget,
								   const QMap<int, QList<QString>> &frame_names_per_tab)
{
	// Convert QString names to FrameInfo
	QMap<int, QList<FrameInfo>> frames_per_tab;

	for (auto it = frame_names_per_tab.begin(); it != frame_names_per_tab.end(); ++it)
	{
		int tab_index = it.key();
		QList<FrameInfo> frame_infos;

		for (const QString &frame_name : it.value())
		{
			frame_infos.append(FrameInfo(frame_name));
		}

		frames_per_tab[tab_index] = frame_infos;
	}

	register_dialog_with_frames(dialog, name, tab_widget, frames_per_tab);
}

void GuiNavigator::register_dialog_with_frames(QWidget *dialog, const QString &name,
											   QTabWidget *tab_widget,
											   const QMap<int, QList<FrameInfo>> &frames_per_tab)
{
	if (!dialog)
		return;

	// Check if already registered
	int index = find_dialog_index(dialog);
	if (index >= 0)
	{
		// Update existing
		dialogs[index].name = name;
		dialogs[index].tab_widget = tab_widget;
		dialogs[index].frames_per_tab = frames_per_tab;
		dialogs[index].current_frame_index = 0;
		dialogs[index].supports_navigation = !frames_per_tab.isEmpty(); // ADD THIS
		qDebug() << "GuiNavigator: Updated dialog:" << name;
		return;
	}

	// Add new dialog
	DialogInfo info;
	info.dialog = dialog;
	info.name = name;
	info.tab_widget = tab_widget;
	info.frames_per_tab = frames_per_tab;
	info.current_frame_index = 0;
	info.current_mode = FRAME_NAVIGATION_MODE;
	info.supports_navigation = !frames_per_tab.isEmpty(); // ADD THIS - Enable navigation if frames exist

	dialogs.append(info);
	current_dialog_index = dialogs.count() - 1;

	connect(dialog, &QWidget::destroyed, this, [this, dialog]() {
		unregister_dialog(dialog);
	});

	// Connect to tab changes for manual tab switching
	if (tab_widget && info.supports_navigation)
	{
		connect(tab_widget, &QTabWidget::currentChanged, this, [this, dialog](int index) {
			// Find this dialog
			int dialog_idx = find_dialog_index(dialog);
			if (dialog_idx >= 0 && dialog_idx == current_dialog_index)
			{
				// Only handle if this is the active dialog
				DialogInfo &current = dialogs[dialog_idx];
				current.current_frame_index = 0; // Reset to first frame

				// Refresh highlighting
				unhighlight_all_frames();
				highlight_frame(0);

				qDebug() << "GuiNavigator: Tab switched manually to index" << index;
			}
		});
	}

	// Highlight initial frame if this dialog supports navigation
	if (info.supports_navigation && current_dialog_index == dialogs.count() - 1)
	{
		QTimer::singleShot(100, this, [this]() {
			// Delayed to ensure UI is fully constructed
			if (current_dialog_index >= 0 && current_dialog_index < dialogs.count())
			{
				if (dialogs[current_dialog_index].supports_navigation)
				{
					highlight_frame(0);
				}
			}
		});
	}

	emit dialog_changed(dialog, name);

	qDebug() << "GuiNavigator: Registered dialog:" << name
			 << "Tabs:" << (tab_widget ? tab_widget->count() : 0)
			 << "Supports navigation:" << info.supports_navigation; // ADD THIS for debugging

	update_info_panel();
}

void GuiNavigator::set_white_frame_widgets(QWidget *dialog, int tab_index, int frame_index,
										   CustomFrame *widget1, CustomFrame *widget2,
										   CustomFrame *widget3, CustomFrame *widget4)
{
	int dialog_index = find_dialog_index(dialog);
	if (dialog_index < 0)
	{
		qDebug() << "GuiNavigator: Dialog not found for set_white_frame_widgets";
		return;
	}

	DialogInfo &info = dialogs[dialog_index];

	if (!info.frames_per_tab.contains(tab_index))
	{
		qDebug() << "GuiNavigator: Tab index" << tab_index << "not found";
		return;
	}

	QList<FrameInfo> &frames = info.frames_per_tab[tab_index];

	if (frame_index < 0 || frame_index >= frames.count())
	{
		qDebug() << "GuiNavigator: Frame index" << frame_index << "out of range";
		return;
	}

	// Set the white frame widget pointers
	frames[frame_index].white_frames[0] = widget1;
	frames[frame_index].white_frames[1] = widget2;
	frames[frame_index].white_frames[2] = widget3;
	frames[frame_index].white_frames[3] = widget4;

	qDebug() << "GuiNavigator: Set white frame widgets for" << info.name
			 << "Tab" << tab_index << "Frame" << frame_index << ":" << frames[frame_index].name;
}

void GuiNavigator::set_gray_frame_widgets(QWidget *dialog, int tab_index, int frame_index,
										  CustomFrame *widget1, CustomFrame *widget2,
										  CustomFrame *widget3, CustomFrame *widget4)
{
	int dialog_index = find_dialog_index(dialog);
	if (dialog_index < 0)
	{
		qDebug() << "GuiNavigator: Dialog not found for set_gray_frame_widgets";
		return;
	}

	DialogInfo &info = dialogs[dialog_index];

	if (!info.frames_per_tab.contains(tab_index))
	{
		qDebug() << "GuiNavigator: Tab index" << tab_index << "not found";
		return;
	}

	QList<FrameInfo> &frames = info.frames_per_tab[tab_index];

	if (frame_index < 0 || frame_index >= frames.count())
	{
		qDebug() << "GuiNavigator: Frame index" << frame_index << "out of range";
		return;
	}

	// Set the gray frame widget pointers
	frames[frame_index].gray_frames[0] = widget1;
	frames[frame_index].gray_frames[1] = widget2;
	frames[frame_index].gray_frames[2] = widget3;
	frames[frame_index].gray_frames[3] = widget4;

	qDebug() << "GuiNavigator: Set gray frame widgets for" << info.name
			 << "Tab" << tab_index << "Frame" << frame_index << ":" << frames[frame_index].name;
}

const CustomFrame *const *GuiNavigator::get_current_white_frames() const
{
	if (current_dialog_index < 0 || current_dialog_index >= dialogs.count())
		return nullptr;

	const DialogInfo &current = dialogs[current_dialog_index];
	QList<FrameInfo> frames = get_current_tab_frames();

	if (current.current_frame_index >= 0 && current.current_frame_index < frames.count())
	{
		return frames[current.current_frame_index].white_frames;
	}

	return nullptr;
}

const CustomFrame *const *GuiNavigator::get_current_gray_frames() const
{
	if (current_dialog_index < 0 || current_dialog_index >= dialogs.count())
		return nullptr;

	const DialogInfo &current = dialogs[current_dialog_index];
	QList<FrameInfo> frames = get_current_tab_frames();

	if (current.current_frame_index >= 0 && current.current_frame_index < frames.count())
	{
		return frames[current.current_frame_index].gray_frames;
	}

	return nullptr;
}

void GuiNavigator::unregister_dialog(QWidget *dialog)
{
	if (!dialog)
		return;

	int index = find_dialog_index(dialog);
	if (index >= 0)
	{
		QString name = dialogs[index].name;
		dialogs.removeAt(index);

		// Adjust current index
		if (current_dialog_index >= dialogs.count())
		{
			current_dialog_index = dialogs.count() - 1;
		}

		qDebug() << "GuiNavigator: Unregistered dialog:" << name;
		update_info_panel();
	}
}

void GuiNavigator::update_dialog_frames(QWidget *dialog, int tab_index, const QList<QString> &frame_names)
{
	int index = find_dialog_index(dialog);
	if (index >= 0)
	{
		// Convert QString list to FrameInfo list
		QList<FrameInfo> frame_infos;
		for (const QString &name : frame_names)
		{
			frame_infos.append(FrameInfo(name));
		}

		dialogs[index].frames_per_tab[tab_index] = frame_infos;
		dialogs[index].current_frame_index = 0; // Reset to first frame

		qDebug() << "GuiNavigator: Updated frames for" << dialogs[index].name
				 << "Tab" << tab_index << "- Count:" << frame_names.count();
		update_info_panel();
	}
}

void GuiNavigator::update_all_dialog_frames(QWidget *dialog, const QMap<int, QList<QString>> &frames_per_tab)
{
	int index = find_dialog_index(dialog);
	if (index >= 0)
	{
		// Convert QMap<int, QList<QString>> to QMap<int, QList<FrameInfo>>
		QMap<int, QList<FrameInfo>> converted_frames;

		for (auto it = frames_per_tab.begin(); it != frames_per_tab.end(); ++it)
		{
			int tab_idx = it.key();
			QList<FrameInfo> frame_infos;

			for (const QString &name : it.value())
			{
				frame_infos.append(FrameInfo(name));
			}

			converted_frames[tab_idx] = frame_infos;
		}

		dialogs[index].frames_per_tab = converted_frames;
		dialogs[index].current_frame_index = 0; // Reset to first frame

		qDebug() << "GuiNavigator: Updated all frames for" << dialogs[index].name;
		update_info_panel();
	}
}

// ============================================================================
// Helper Methods
// ============================================================================

void GuiNavigator::cycle_dialog_next()
{
	cleanup_invisible_dialogs();

	if (dialogs.isEmpty())
	{
		qDebug() << "GuiNavigator: No dialogs to cycle";
		return;
	}

	// Move to next dialog (with wrap-around)
	current_dialog_index = (current_dialog_index + 1) % dialogs.count();

	DialogInfo &current = dialogs[current_dialog_index];
	current.current_frame_index = 0; // Reset frame index when switching dialogs
	focus_dialog(current.dialog);

	emit dialog_changed(current.dialog, current.name);

	qDebug() << "GuiNavigator: Cycled to next dialog:" << current.name
			 << "(" << (current_dialog_index + 1) << "/" << dialogs.count() << ")";

	update_info_panel();
}

void GuiNavigator::cycle_dialog_previous()
{
	cleanup_invisible_dialogs();

	if (dialogs.isEmpty())
	{
		qDebug() << "GuiNavigator: No dialogs to cycle";
		return;
	}

	// Move to previous dialog (with wrap-around)
	current_dialog_index = (current_dialog_index - 1 + dialogs.count()) % dialogs.count();

	DialogInfo &current = dialogs[current_dialog_index];
	current.current_frame_index = 0; // Reset frame index when switching dialogs
	focus_dialog(current.dialog);

	emit dialog_changed(current.dialog, current.name);

	qDebug() << "GuiNavigator: Cycled to previous dialog:" << current.name
			 << "(" << (current_dialog_index + 1) << "/" << dialogs.count() << ")";

	update_info_panel();
}

void GuiNavigator::toggle_navigation_mode()
{
	if (dialogs.isEmpty() || current_dialog_index < 0)
	{
		qDebug() << "GuiNavigator: No active dialog to toggle mode";
		return;
	}

	DialogInfo &current = dialogs[current_dialog_index];

	// Only toggle if dialog has tabs
	if (!current.tab_widget || current.tab_widget->count() == 0)
	{
		qDebug() << "GuiNavigator: Dialog has no tabs, cannot toggle mode";
		return;
	}

	// Toggle mode
	if (current.current_mode == TAB_NAVIGATION_MODE)
	{
		current.current_mode = FRAME_NAVIGATION_MODE;
		current.current_frame_index = 0; // Reset frame index
		qDebug() << "GuiNavigator: Switched to FRAME mode";
	}
	else
	{
		current.current_mode = TAB_NAVIGATION_MODE;
		qDebug() << "GuiNavigator: Switched to TAB mode";
	}

	emit mode_changed(current.current_mode);
	update_info_panel();
}

void GuiNavigator::cycle_tabs_forward()
{
	if (current_dialog_index < 0 || current_dialog_index >= dialogs.count())
		return;

	DialogInfo &current = dialogs[current_dialog_index];

	if (!current.tab_widget || current.tab_widget->count() == 0)
	{
		qDebug() << "GuiNavigator: No tabs to cycle";
		return;
	}

	int current_tab = current.tab_widget->currentIndex();
	int next_tab = (current_tab + 1) % current.tab_widget->count();

	current.tab_widget->setCurrentIndex(next_tab);
	current.current_frame_index = 0; // Reset frame index when changing tabs

	if (current.supports_navigation)
	{
		unhighlight_all_frames();
		highlight_frame(0); // Highlight first frame of new tab
	}	
	
	qDebug() << "GuiNavigator: Cycled to next tab:"
			 << current.tab_widget->tabText(next_tab);

	update_info_panel();
}

void GuiNavigator::cycle_tabs_backward()
{
	if (current_dialog_index < 0 || current_dialog_index >= dialogs.count())
		return;

	DialogInfo &current = dialogs[current_dialog_index];

	if (!current.tab_widget || current.tab_widget->count() == 0)
	{
		qDebug() << "GuiNavigator: No tabs to cycle";
		return;
	}

	int current_tab = current.tab_widget->currentIndex();
	int prev_tab = (current_tab - 1 + current.tab_widget->count()) % current.tab_widget->count();

	current.tab_widget->setCurrentIndex(prev_tab);
	current.current_frame_index = 0; // Reset frame index when changing tabs

	if (current.supports_navigation)
	{
		unhighlight_all_frames();
		highlight_frame(0); // Highlight first frame of new tab
	}

	qDebug() << "GuiNavigator: Cycled to previous tab:"
			 << current.tab_widget->tabText(prev_tab);

	update_info_panel();
}

void GuiNavigator::cycle_frames_forward()
{
	if (current_dialog_index < 0 || current_dialog_index >= dialogs.count())
		return;

	DialogInfo &current = dialogs[current_dialog_index];

	// Skip if widget doesn't support navigation
	if (!current.supports_navigation)
	{
		qDebug() << "GuiNavigator: Widget doesn't support frame navigation";
		return;
	}

	QList<FrameInfo> frames = get_current_tab_frames();

	if (frames.isEmpty())
	{
		qDebug() << "GuiNavigator: No frames to cycle";
		return;
	}

	// Unhighlight current frame BEFORE changing
	unhighlight_frame(current.current_frame_index);

	// Move to next frame
	current.current_frame_index = (current.current_frame_index + 1) % frames.count();

	const FrameInfo &frame_info = frames[current.current_frame_index];

	// Highlight new frame
	highlight_frame(current.current_frame_index);

	qDebug() << "GuiNavigator: Frame forward ->" << frame_info.name
			 << "(" << (current.current_frame_index + 1) << "/" << frames.count() << ")";

	emit frame_changed(frame_info.name, current.current_frame_index);
	update_info_panel();
}

void GuiNavigator::cycle_frames_backward()
{
	if (current_dialog_index < 0 || current_dialog_index >= dialogs.count())
		return;

	DialogInfo &current = dialogs[current_dialog_index];

	// Skip if widget doesn't support navigation (consistency with forward)
	if (!current.supports_navigation)
	{
		qDebug() << "GuiNavigator: Widget doesn't support frame navigation";
		return;
	}

	QList<FrameInfo> frames = get_current_tab_frames();

	if (frames.isEmpty())
	{
		qDebug() << "GuiNavigator: No frames to cycle";
		return;
	}

	// Unhighlight current frame BEFORE changing
	unhighlight_frame(current.current_frame_index);

	// Move to previous frame
	current.current_frame_index = (current.current_frame_index - 1 + frames.count()) % frames.count();

	const FrameInfo &frame_info = frames[current.current_frame_index];

	// Highlight new frame
	highlight_frame(current.current_frame_index);

	qDebug() << "GuiNavigator: Frame backward ->" << frame_info.name
			 << "(" << (current.current_frame_index + 1) << "/" << frames.count() << ")";

	emit frame_changed(frame_info.name, current.current_frame_index);
	update_info_panel();
}

// Add these new private methods to GuiNavigator:

void GuiNavigator::highlight_frame(int frame_index)
{
	QList<FrameInfo> frames = get_current_tab_frames();

	if (frame_index < 0 || frame_index >= frames.count())
		return;

	const FrameInfo &frame_info = frames[frame_index];

	// Highlight white frames - WHITE color, 6px
	for (int i = 0; i < 4; i++)
	{
		if (frame_info.white_frames[i] != nullptr)
		{
			frame_info.white_frames[i]->setBorderColor(_CONTROL_GROUP_WHITE);
			frame_info.white_frames[i]->setBorderWidth(6);
		}
	}

	// Highlight gray frames - GRAY color, 6px
	for (int i = 0; i < 4; i++)
	{
		if (frame_info.gray_frames[i] != nullptr)
		{
			frame_info.gray_frames[i]->setBorderColor(_CONTROL_GROUP_GRAY);
			frame_info.gray_frames[i]->setBorderWidth(6);
		}
	}
}

void GuiNavigator::unhighlight_frame(int frame_index)
{
	QList<FrameInfo> frames = get_current_tab_frames();

	if (frame_index < 0 || frame_index >= frames.count())
		return;

	const FrameInfo &frame_info = frames[frame_index];

	// Unhighlight white frames - Light gray, 1px
	for (int i = 0; i < 4; i++)
	{
		if (frame_info.white_frames[i] != nullptr)
		{
			frame_info.white_frames[i]->setBorderColor(_CONTROL_GROUP_NOT_SELECTED);
			frame_info.white_frames[i]->setBorderWidth(1);
		}
	}

	// Unhighlight gray frames - Light gray, 1px
	for (int i = 0; i < 4; i++)
	{
		if (frame_info.gray_frames[i] != nullptr)
		{
			frame_info.gray_frames[i]->setBorderColor(_CONTROL_GROUP_NOT_SELECTED);
			frame_info.gray_frames[i]->setBorderWidth(1);
		}
	}
}

void GuiNavigator::unhighlight_all_frames()
{
	QList<FrameInfo> frames = get_current_tab_frames();

	for (int i = 0; i < frames.count(); i++)
	{
		unhighlight_frame(i);
	}
}

void GuiNavigator::refresh_current_highlight()
{
	if (current_dialog_index < 0 || current_dialog_index >= dialogs.count())
		return;

	DialogInfo &current = dialogs[current_dialog_index];

	// Unhighlight all first, then highlight the current frame
	unhighlight_all_frames();
	highlight_frame(current.current_frame_index);

	qDebug() << "GuiNavigator: Refreshed highlight for frame" << current.current_frame_index;
}

QList<FrameInfo> GuiNavigator::get_current_tab_frames() const
{
	if (current_dialog_index < 0 || current_dialog_index >= dialogs.count())
		return QList<FrameInfo>();

	const DialogInfo &current = dialogs[current_dialog_index];

	// Use simple frames list for non-tab dialogs
	if (!current.tab_widget)
	{
		// Check frames_per_tab[0] first for dialogs registered with frames but no tabs
		if (current.frames_per_tab.contains(0))
		{
			return current.frames_per_tab.value(0);
		}
		return current.frames;
	}

	// Use frames_per_tab for tab-based dialogs
	int tab_index = current.tab_widget->currentIndex();
	return current.frames_per_tab.value(tab_index, QList<FrameInfo>());
}

void GuiNavigator::focus_dialog(QWidget *dialog)
{
	if (!dialog)
		return;

	QMainWindow *mainwindow = qobject_cast<QMainWindow *>(dialog);

	// Ensure visible and normal state
	if (dialog->isMinimized())
		dialog->showNormal();

	// For MainWindow - use hide/show cycle to force re-stacking
	if (mainwindow)
	{
		qDebug() << "GuiNavigator: Activating MainWindow";

		if (dialog->isVisible())
		{
			// Quick hide/show to force window manager to restack
			dialog->hide();
			QApplication::processEvents(); // Process the hide event
			dialog->show();
			QApplication::processEvents(); // Process the show event
		}
		else
		{
			dialog->show();
		}

		// Standard activation
		mainwindow->raise();
		mainwindow->activateWindow();
		mainwindow->setFocus(Qt::ActiveWindowFocusReason);

		// Force one more raise
		QTimer::singleShot(10, [mainwindow]() {
			mainwindow->raise();
		});
	}
	else
	{
		// Normal dialog activation
		if (!dialog->isVisible())
			dialog->show();

		dialog->raise();
		dialog->activateWindow();
		dialog->setFocus(Qt::ActiveWindowFocusReason);
	}

	// Update frame highlighting
	unhighlight_all_frames();
	if (current_dialog_index >= 0 && current_dialog_index < dialogs.count())
	{
		if (dialogs[current_dialog_index].supports_navigation)
		{
			highlight_frame(dialogs[current_dialog_index].current_frame_index);
		}
	}
}
void GuiNavigator::cleanup_invisible_dialogs()
{
	for (int i = dialogs.count() - 1; i >= 0; --i)
	{
		if (!dialogs[i].dialog->isVisible())
		{
			QString name = dialogs[i].name;
			dialogs.removeAt(i);
			qDebug() << "GuiNavigator: Removed invisible dialog:" << name;
		}
	}

	if (current_dialog_index >= dialogs.count())
	{
		current_dialog_index = qMax(0, dialogs.count() - 1);
	}
}

int GuiNavigator::find_dialog_index(QWidget *dialog)
{
	for (int i = 0; i < dialogs.count(); ++i)
	{
		if (dialogs[i].dialog == dialog)
		{
			return i;
		}
	}
	return -1;
}

void GuiNavigator::update_info_panel()
{
	if (!info_panel)
		return;

	QString line1 = "No Dialogs";
	QString line2 = "";

	if (!dialogs.isEmpty() && current_dialog_index >= 0 && current_dialog_index < dialogs.count())
	{
		DialogInfo &current = dialogs[current_dialog_index];

		// Line 1: Dialog name
		line1 = QString("%1").arg(current.name);

		// Line 2: Mode
		if (current.tab_widget && current.tab_widget->count() > 0)
		{
			if (current.current_mode == TAB_NAVIGATION_MODE)
			{
				line2 = "Mode: TAB Navigation";
			}
			else
			{
				line2 = "Mode: FRAME Navigation";
			}
		}
		else
		{
			// No tabs - always frame mode
			line2 = "Mode: FRAME Navigation";
		}
	}

	// Update panel with 2 lines
	info_panel->update_info(line1, line2);
}

// ============================================================================
// Focus Management
// ============================================================================

void GuiNavigator::focus_on_dialog(QWidget *dialog)
{
	if (!dialog)
		return;

	int index = find_dialog_index(dialog);
	if (index >= 0)
	{
		current_dialog_index = index;
		focus_dialog(dialog);
		emit dialog_changed(dialog, dialogs[index].name);
		update_info_panel();

		qDebug() << "GuiNavigator: Focused on dialog:" << dialogs[index].name;
	}
}

// ============================================================================
// Info Panel
// ============================================================================

void GuiNavigator::show_info_panel()
{
	qDebug() << "=== Showing info panel ===";
	if (info_panel)
	{
		qDebug() << "Info panel exists";
		update_info_panel();
		info_panel->show_panel();
		qDebug() << "Info panel visible:" << info_panel->isVisible();
		qDebug() << "Info panel geometry:" << info_panel->geometry();
	}
	else
	{
		qDebug() << "ERROR: Info panel is nullptr!";
	}
}

void GuiNavigator::hide_info_panel()
{
	if (info_panel)
	{
		info_panel->hide_panel();
	}
}

void GuiNavigator::toggle_info_panel()
{
	if (info_panel)
	{
		if (info_panel->isVisible())
		{
			hide_info_panel();
		}
		else
		{
			show_info_panel();
		}
	}
}

// ============================================================================
// Queries
// ============================================================================

QWidget *GuiNavigator::get_current_dialog() const
{
	if (current_dialog_index >= 0 && current_dialog_index < dialogs.count())
	{
		return dialogs[current_dialog_index].dialog;
	}
	return nullptr;
}

QString GuiNavigator::get_current_dialog_name() const
{
	if (current_dialog_index >= 0 && current_dialog_index < dialogs.count())
	{
		return dialogs[current_dialog_index].name;
	}
	return QString();
}

int GuiNavigator::get_dialog_count() const
{
	return dialogs.count();
}

DialogNavigationMode GuiNavigator::get_current_mode() const
{
	if (current_dialog_index >= 0 && current_dialog_index < dialogs.count())
	{
		return dialogs[current_dialog_index].current_mode;
	}
	return FRAME_NAVIGATION_MODE;
}

QString GuiNavigator::get_current_frame_name() const
{
	QList<FrameInfo> frames = get_current_tab_frames();

	if (current_dialog_index >= 0 && current_dialog_index < dialogs.count())
	{
		const DialogInfo &current = dialogs[current_dialog_index];

		if (current.current_frame_index >= 0 && current.current_frame_index < frames.count())
		{
			return frames[current.current_frame_index].name;
		}
	}

	return QString();
}

int GuiNavigator::get_current_frame_index() const
{
	if (current_dialog_index >= 0 && current_dialog_index < dialogs.count())
	{
		return dialogs[current_dialog_index].current_frame_index;
	}
	return 0;
}

int GuiNavigator::get_current_tab_index() const
{
	if (current_dialog_index < 0 || current_dialog_index >= dialogs.count())
		return -1;

	const DialogInfo &current = dialogs[current_dialog_index];

	if (!current.tab_widget)
		return -1; // No tabs

	return current.tab_widget->currentIndex();
}

