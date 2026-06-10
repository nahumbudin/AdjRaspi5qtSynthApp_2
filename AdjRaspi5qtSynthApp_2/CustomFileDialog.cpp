/**
 * @file		CustomFileDialog.cpp
 *	@author		Nahum Budin
 *	@date		21-Apr-2026
 *	@version	1.3
 *					1.3 Fixed styling inheritance using QPalette instead of stylesheets
 *					1.2 Fixed styling inheritance issues - apply styles directly to specific widgets
 *					1.1 Added optional background color parameter to constructor
 *					1.0 First version. Created using GitHub Copilot
 *
 *	@brief		Custom File Dialog that goes back and displays the last selected file on
 *				the list when reopened
 */

#include "CustomFileDialog.h"
#include <QAbstractItemView>
#include <QDir>
#include <QFileInfo>
#include <QHeaderView>
#include <QSplitter>
#include <QTimer>
#include <QPointer>
#include <QDebug>
#include <QApplication>

CustomFileDialog::CustomFileDialog(QWidget *parent,
								   const QString &caption,
								   const QString &directory,
								   const QString &filter,
								   const QColor &backgroundColor,
								   Mode mode)
	: QDialog(parent), dialogMode(mode)
{
	setWindowTitle(caption.isEmpty() ? (mode == SaveMode ? tr("Save File") : tr("Open File")) : caption);
	resize(900, 600);

	currentDirectory = directory.isEmpty() ? QDir::homePath() : directory;

	// Parse filter string: "Presets (*.mid *.MID);;All Files (*)"
	filterList = filter.split(";;", Qt::SkipEmptyParts);

	// Create model
	model = new QFileSystemModel(this);
	model->setRootPath(QDir::rootPath());
	model->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);

	// Create directory path edit (editable)
	pathEdit = new QLineEdit(this);
	pathEdit->setText(currentDirectory);

	// Create tree view for directories
	//treeView = new QTreeView(this);
	treeView = new CustomTreeView(this);

	treeView->setAnimated(false);		   // Disable animations
	treeView->setIndentation(20);		   // Fixed indent
	treeView->setUniformRowHeights(false); // Proper height calculation
	
	treeView->setModel(model);
	treeView->setRootIndex(model->index(QDir::rootPath()));
	treeView->setColumnWidth(0, 200);
	treeView->hideColumn(1);
	treeView->hideColumn(2);
	treeView->hideColumn(3);
	treeView->setHeaderHidden(false);
	treeView->header()->hideSection(1);
	treeView->header()->hideSection(2);
	treeView->header()->hideSection(3);

	// Create list view for files
	listView = new QListView(this);
	listView->setModel(model);
	listView->setRootIndex(model->index(currentDirectory));

	// Create splitter for tree and list views
	QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
	splitter->addWidget(treeView);
	splitter->addWidget(listView);
	splitter->setStretchFactor(0, 1);
	splitter->setStretchFactor(1, 2);

	// Create file name edit
	fileNameEdit = new QLineEdit(this);
	fileNameEdit->setReadOnly(mode == OpenMode); // Editable in Save mode

	// Create filter combo box
	filterCombo = new QComboBox(this);
	filterCombo->addItems(filterList);

	// Create buttons
	QPushButton *okButton = new QPushButton(mode == SaveMode ? tr("Save") : tr("Open"), this);
	QPushButton *cancelButton = new QPushButton(tr("Cancel"), this);

	// Layout
	QVBoxLayout *mainLayout = new QVBoxLayout(this);

	// Path edit layout
	QHBoxLayout *pathLayout = new QHBoxLayout();
	pathLayout->addWidget(new QLabel(tr("Directory:"), this));
	pathLayout->addWidget(pathEdit);
	mainLayout->addLayout(pathLayout);

	// Splitter with tree and list
	mainLayout->addWidget(splitter);

	// File name layout
	QHBoxLayout *fileLayout = new QHBoxLayout();
	fileLayout->addWidget(new QLabel(tr("File name:"), this));
	fileLayout->addWidget(fileNameEdit);
	mainLayout->addLayout(fileLayout);

	// Filter layout
	QHBoxLayout *filterLayout = new QHBoxLayout();
	filterLayout->addWidget(new QLabel(tr("Files of type:"), this));
	filterLayout->addWidget(filterCombo);
	mainLayout->addLayout(filterLayout);

	// Button layout
	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addStretch();
	buttonLayout->addWidget(okButton);
	buttonLayout->addWidget(cancelButton);
	mainLayout->addLayout(buttonLayout);

	// Apply color scheme FIRST
	applyColorScheme(backgroundColor);

	// Apply widget-specific stylesheets AFTER applyColorScheme
	// These will override any parent dialog stylesheets
	pathEdit->setStyleSheet(
		"QLineEdit {"
		"    background-color: rgb(5, 5, 5);"
		"    color: rgb(240, 240, 240);"
		"    border: 1px solid rgb(80, 80, 80);"
		"    padding: 3px;"
		"    selection-background-color: rgb(70, 130, 180);"
		"    selection-color: rgb(255, 255, 255);"
		"}");

	fileNameEdit->setStyleSheet(
		"QLineEdit {"
		"    background-color: rgb(5, 5, 5);"
		"    color: rgb(240, 240, 240);"
		"    border: 1px solid rgb(80, 80, 80);"
		"    padding: 3px;"
		"    selection-background-color: rgb(70, 130, 180);"
		"    selection-color: rgb(255, 255, 255);"
		"}");

	filterCombo->setStyleSheet(
		"QComboBox {"
		"    background-color: rgb(5, 5, 5);"
		"    color: rgb(240, 240, 240);"
		"    border: 1px solid rgb(80, 80, 80);"
		"    padding: 3px;"
		"}"
		"QComboBox::drop-down {"
		"    border: none;"
		"    background-color: rgb(40, 40, 40);"
		"    width: 20px;"
		"}"
		"QComboBox::down-arrow {"
		"    width: 0;"
		"    height: 0;"
		"    border-left: 5px solid transparent;"
		"    border-right: 5px solid transparent;"
		"    border-top: 7px solid rgb(240, 240, 240);"
		"}"
		"QComboBox QAbstractItemView {"
		"    background-color: rgb(5, 5, 5);"
		"    color: rgb(240, 240, 240);"
		"    selection-background-color: rgb(70, 130, 180);"
		"    selection-color: rgb(255, 255, 255);"
		"    border: 1px solid rgb(100, 100, 100);"
		"}");

	// Apply initial filter
	if (!filterList.isEmpty())
	{
		applyFilter(filterList.first());
	}

	// Expand tree to current directory
	//treeView->setCurrentIndex(model->index(currentDirectory));
	//treeView->scrollTo(model->index(currentDirectory), QAbstractItemView::PositionAtCenter);

	// Connect signals
	connect(listView, &QListView::clicked, this, &CustomFileDialog::onFileClicked);
	connect(listView, &QListView::doubleClicked, this, &CustomFileDialog::onFileDoubleClicked);
	
	//connect(treeView, &QTreeView::clicked, this, &CustomFileDialog::onTreeClicked);
	connect(treeView, &CustomTreeView::itemClicked, this, &CustomFileDialog::onTreeClicked);
	
	connect(okButton, &QPushButton::clicked, this, &CustomFileDialog::onOkClicked);
	connect(cancelButton, &QPushButton::clicked, this, &CustomFileDialog::onCancelClicked);
	connect(filterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CustomFileDialog::onFilterChanged);
	connect(pathEdit, &QLineEdit::editingFinished, this, &CustomFileDialog::onPathEditingFinished);

	// Connect file name edit changes in Save mode
	if (mode == SaveMode)
	{
		connect(fileNameEdit, &QLineEdit::textChanged, this, &CustomFileDialog::onFileNameEditChanged);
	}
}

void CustomFileDialog::onFileNameEditChanged(const QString &text)
{
	if (dialogMode == SaveMode && !text.isEmpty())
	{
		selectedFilePath = currentDirectory + "/" + text;
	}
}

void CustomFileDialog::onOkClicked()
{
	// In Save mode, accept even if file doesn't exist
	if (dialogMode == SaveMode)
	{
		QString fileName = fileNameEdit->text();
		if (!fileName.isEmpty())
		{
			selectedFilePath = currentDirectory + "/" + fileName;
			accept();
		}
	}
	else
	{
		// In Open mode, file must exist
		if (!selectedFilePath.isEmpty() && QFile::exists(selectedFilePath))
		{
			accept();
		}
	}
}

QString CustomFileDialog::selectedFile() const
{
	return selectedFilePath;
}

void CustomFileDialog::selectFile(const QString &filename)
{
	if (!filename.isEmpty() && QFile::exists(filename))
	{
		selectedFilePath = filename;
		fileNameEdit->setText(QFileInfo(filename).fileName());
		pendingFileSelection = filename;

		// Set the directory immediately
		QString dir = QFileInfo(filename).absolutePath();
		navigateToDirectory(dir);
	}
}

void CustomFileDialog::setBackgroundColor(const QColor &color)
{
	applyColorScheme(color);
}

void CustomFileDialog::applyColorScheme(const QColor &color)
{
	QString colorStr = QString("rgb(%1, %2, %3)")
						   .arg(color.red())
						   .arg(color.green())
						   .arg(color.blue());

	// Slightly lighter for list/tree view
	QColor listBg = color.lighter(110);
	QString listColorStr = QString("rgb(%1, %2, %3)")
							   .arg(listBg.red())
							   .arg(listBg.green())
							   .arg(listBg.blue());

	// Lighter for buttons
	QColor buttonBg = color.lighter(140);
	QString buttonColorStr = QString("rgb(%1, %2, %3)")
								 .arg(buttonBg.red())
								 .arg(buttonBg.green())
								 .arg(buttonBg.blue());

	// Header color
	QColor headerBg = color.lighter(120);
	QString headerColorStr = QString("rgb(%1, %2, %3)")
								 .arg(headerBg.red())
								 .arg(headerBg.green())
								 .arg(headerBg.blue());

	setStyleSheet(
		QString("QDialog { background-color: %1; color: white; } "
				"QLabel { color: white; background-color: transparent; } " // Added transparent background
				"QTreeView { color: white; background-color: %2; selection-background-color: rgb(0, 120, 215); } "
				"QListView { color: white; background-color: %2; selection-background-color: rgb(0, 120, 215); } "
				"QPushButton { color: white; background-color: %3; padding: 5px; border: 1px solid rgb(80, 80, 80); } "
				"QHeaderView::section { background-color: %4; color: white; padding: 4px; }")
			.arg(colorStr)
			.arg(listColorStr)
			.arg(buttonColorStr)
			.arg(headerColorStr));
}

void CustomFileDialog::navigateToDirectory(const QString &path)
{
	if (QDir(path).exists())
	{
		currentDirectory = path;
		pathEdit->setText(path);

		listView->clearSelection();
		listView->setCurrentIndex(QModelIndex());
		listView->setRootIndex(model->index(path));

		if (dialogMode == OpenMode)
		{
			fileNameEdit->clear();
			selectedFilePath.clear();
		}

		treeView->setCurrentIndex(model->index(path));
		treeView->scrollTo(model->index(path), QAbstractItemView::PositionAtCenter);
	}
}

void CustomFileDialog::onFileClicked(const QModelIndex &index)
{
	QFileInfo info = model->fileInfo(index);

	if (info.isFile())
	{
		fileNameEdit->setText(info.fileName());
		selectedFilePath = info.absoluteFilePath();
	}
	else if (info.isDir())
	{
		navigateToDirectory(info.absoluteFilePath());
	}
}

void CustomFileDialog::onFileDoubleClicked(const QModelIndex &index)
{
	QFileInfo info = model->fileInfo(index);
	if (info.isFile())
	{
		selectedFilePath = info.absoluteFilePath();
		accept();
	}
	else if (info.isDir())
	{
		navigateToDirectory(info.absoluteFilePath());
	}
}

void CustomFileDialog::onTreeClicked(const QModelIndex &index)
{
	QFileInfo info = model->fileInfo(index);

	if (info.isDir() && info.exists())
	{
		navigateToDirectory(info.absoluteFilePath());
	}
}

void CustomFileDialog::onPathEditingFinished()
{
	QString path = pathEdit->text();
	navigateToDirectory(path);
}

void CustomFileDialog::onCancelClicked()
{
	reject();
}

void CustomFileDialog::onFilterChanged(int index)
{
	if (index >= 0 && index < filterList.size())
	{
		applyFilter(filterList.at(index));
	}
}

void CustomFileDialog::applyFilter(const QString &filterText)
{
	// Extract extensions from "Presets (*.mid *.MID)"
	int start = filterText.indexOf('(');
	int end = filterText.indexOf(')');

	if (start != -1 && end != -1)
	{
		QString extensions = filterText.mid(start + 1, end - start - 1);
		QStringList filters = extensions.split(' ', Qt::SkipEmptyParts);

		if (!filters.isEmpty())
		{
			model->setNameFilters(filters);
			model->setNameFilterDisables(false);
		}
	}
}

void CustomFileDialog::showEvent(QShowEvent *event)
{
	QDialog::showEvent(event);

	// Expand tree to current directory
	QModelIndex idx = model->index(currentDirectory);
	QModelIndex parent = idx.parent();
	while (parent.isValid())
	{
		treeView->expand(parent);
		parent = parent.parent();
	}
	treeView->setCurrentIndex(idx);
	treeView->scrollTo(idx, QAbstractItemView::PositionAtCenter);

	// Fix tree view geometry by toggling focus
	// This triggers viewport recalculation after programmatic expansion
	QTimer::singleShot(0, this, [this]() {
		fileNameEdit->setFocus();
		QApplication::processEvents();
		treeView->setFocus();
		treeView->doItemsLayout();
	});

	// Handle pending file selection
	if (!pendingFileSelection.isEmpty())
	{
		QString dir = QFileInfo(pendingFileSelection).absolutePath();
		listView->setRootIndex(model->index(dir));

		QPointer<CustomFileDialog> weakThis(this);
		QString filePath = pendingFileSelection;

		QTimer::singleShot(100, this, [weakThis, filePath]() {
			if (!weakThis)
			{
				return;
			}

			QModelIndex index = weakThis->model->index(filePath);
			if (index.isValid())
			{
				weakThis->listView->selectionModel()->setCurrentIndex(
					index, QItemSelectionModel::ClearAndSelect);
				weakThis->listView->scrollTo(index, QAbstractItemView::PositionAtCenter);
				weakThis->fileNameEdit->setText(QFileInfo(filePath).fileName());
				weakThis->selectedFilePath = filePath;
			}

			weakThis->pendingFileSelection.clear();
		});
	}
}
