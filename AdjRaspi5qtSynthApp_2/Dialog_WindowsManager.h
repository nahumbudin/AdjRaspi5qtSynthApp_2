/**
 * @file		Dialog_WindowsManager.h
 *	@author		Nahum Budin
 *	@date		18-Feb-2026
 *	@version	1.0
 *
 *	@brief		Window Manager Dialog - Shows list of all open application dialogs
 *				Coded with the help of GitHub Copilot
 *
 */

#pragma once

#include <QDialog>
#include <QLabel>
#include <QList>
#include <QMap>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
#include <QMutex>

class Dialog_WindowManager : public QDialog
{
	Q_OBJECT

  public:
	static Dialog_WindowManager *get_instance(QWidget *parent = nullptr);

	~Dialog_WindowManager();

	/**
	 * @brief Register a dialog window
	 * @param window Pointer to the dialog widget
	 * @param windowTitle Display name for the dialog
	 */
	void register_dialog(QWidget *window, const QString &windowTitle);

	/**
	 * @brief Unregister a dialog window
	 * @param window Pointer to the dialog widget to remove
	 */
	void unregister_dialog(QWidget *window);

	/**
	 * @brief Clear all registered dialogs
	 */
	void clear_all_dialogs();

	/**
	 * @brief Refresh and show the window manager
	 */
	void show_window_manager();

	void simulate_button_hover(int button_index); // -1 to clear hover
	void simulate_button_click(int button_index);

  private slots:
	/**
	 * @brief Handle dialog button clicks
	 */
	void on_dialog_button_clicked();

	/**
	 * @brief Handle close button click
	 */
	void on_close_button_clicked();

  private:
	explicit Dialog_WindowManager(QWidget *parent = nullptr);
	
	/**
	 * @brief Initialize the UI components
	 */
	void setup_ui();

	/**
	 * @brief Rebuild the dialog list display
	 */
	void rebuild_dialog_list();

	struct DialogInfo
	{
		QWidget *widget;
		QString title;
	};

	QVBoxLayout *main_layout;
	QScrollArea *scroll_area;
	QWidget *scroll_content;
	QVBoxLayout *scroll_layout;
	QLabel *header_label;
	QLabel *count_label;
	QPushButton *close_button;

	QList<DialogInfo> dialog_list;

	QMutex dialog_list_mutex;

	static Dialog_WindowManager *dialog_manager;
};
