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

class CustomFileDialog : public QDialog
{
	Q_OBJECT

  public:
	explicit CustomFileDialog(QWidget *parent = nullptr,
							  const QString &caption = QString(),
							  const QString &directory = QString(),
							  const QString &filter = QString(),
							  const QColor &backgroundColor = QColor(50, 50, 50));

	QString selectedFile() const;
	void selectFile(const QString &filename);
	void setBackgroundColor(const QColor &color);

  protected:
	void showEvent(QShowEvent *event) override;

  private slots:
	void onFileDoubleClicked(const QModelIndex &index);
	void onFileClicked(const QModelIndex &index);
	void onTreeClicked(const QModelIndex &index);
	void onOkClicked();
	void onCancelClicked();
	void onFilterChanged(int index);
	void onPathEditingFinished();

  private:
	void applyFilter(const QString &filterText);
	void navigateToDirectory(const QString &path);
	void applyColorScheme(const QColor &color);

	QFileSystemModel *model;
	QTreeView *treeView;
	QListView *listView;
	QLineEdit *pathEdit;
	QLineEdit *fileNameEdit;
	QComboBox *filterCombo;
	QString selectedFilePath;
	QString currentDirectory;
	QStringList filterList;
	QString pendingFileSelection; // Add this member variable
};


