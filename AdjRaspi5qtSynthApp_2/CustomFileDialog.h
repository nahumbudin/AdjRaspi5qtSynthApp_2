/**
 * @file		CustomFileDialog.h
 *	@author		Nahum Budin
 *	@date		21-Apr-2026
 *	@version	1.0
 *					1. First version. Created using GitHub Copilot
 *
 *	@brief		Custom File Dialog that go back and displays the last selected file on
 *				the list when reopened
 */

#pragma once

#include <QDialog>
#include <QFileSystemModel>
#include <QListView>
#include <QTreeView>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QLabel>
#include <QComboBox>
#include <QShowEvent>

#include <QMouseEvent>

// Custom tree view that gets index directly from mouse position
class CustomTreeView : public QTreeView
{
	Q_OBJECT
  public:
	explicit CustomTreeView(QWidget *parent = nullptr) : QTreeView(parent) {}

  protected:
	void mousePressEvent(QMouseEvent *event) override
	{
		if (event->button() == Qt::LeftButton)
		{
			m_pressedIndex = indexAt(event->pos());
		}
		QTreeView::mousePressEvent(event);
	}

	void mouseReleaseEvent(QMouseEvent *event) override
	{
		if (event->button() == Qt::LeftButton && m_pressedIndex.isValid())
		{
			QModelIndex releaseIndex = indexAt(event->pos());
			if (releaseIndex == m_pressedIndex)
			{
				emit itemClicked(m_pressedIndex);
			}
			m_pressedIndex = QModelIndex();
		}
		QTreeView::mouseReleaseEvent(event);
	}

  signals:
	void itemClicked(const QModelIndex &index);

  private:
	QModelIndex m_pressedIndex;
};

class CustomFileDialog : public QDialog
{
	Q_OBJECT

  public:
	enum Mode
	{
		OpenMode,
		SaveMode
	};

	explicit CustomFileDialog(QWidget *parent = nullptr,
							  const QString &caption = QString(),
							  const QString &directory = QString(),
							  const QString &filter = QString(),
							  const QColor &backgroundColor = Qt::black,
							  Mode mode = OpenMode, 
							  const QString &contextId = QString()); 

	QString selectedFile() const;
	void selectFile(const QString &filename);
	void setBackgroundColor(const QColor &color);

	static QString last_selected_file(const QString &contextId);
	static void set_last_selected_file(const QString &contextId, const QString &file);
	static void clear_last_selected_file(const QString &contextId);

  private slots:
	void onFileClicked(const QModelIndex &index);
	void onFileDoubleClicked(const QModelIndex &index);
	void onTreeClicked(const QModelIndex &index);
	void onPathEditingFinished();
	void onOkClicked();
	void onCancelClicked();
	void onFilterChanged(int index);
	void onFileNameEditChanged(const QString &text); // Add this

  private:
	void applyColorScheme(const QColor &color);
	void navigateToDirectory(const QString &path);
	void applyFilter(const QString &filterText);
	void showEvent(QShowEvent *event) override;

	static QMap<QString, QString> last_selected_files; // Per-context storage
	
	// Current dialog context
	QString context_id;
	
	QString file_to_scroll_to; // Add this line

	QFileSystemModel *model;
	
	// *treeView;
	CustomTreeView *treeView;
	
	QListView *listView;
	QLineEdit *fileNameEdit;
	QLineEdit *pathEdit;
	QComboBox *filterCombo;

	QString currentDirectory;
	QString selectedFilePath;
	QStringList filterList;
	QString pending_file_selection;
	Mode dialogMode; // Add this
};



