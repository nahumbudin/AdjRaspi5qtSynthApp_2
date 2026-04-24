/**
 * @file		CustomFileDialog.cpp
 *	@author		Nahum Budin
 *	@date		21-Apr-2026
 *	@version	1.0
 *					1. First version. Created using GitHub Copilot
 *
 *	@brief		Custom File Dialog that go back and displays the last selected file on 
 *				the list when reopened
 */

/**
 * @file		CustomFileDialog.cpp
 *	@author		Nahum Budin
 *	@date		21-Apr-2026
 *	@version	1.1
 *					1.1 Added optional background color parameter to constructor
 *					1.0 First version. Created using GitHub Copilot
 *
 *	@brief		Custom File Dialog that goes back and displays the last selected file on
 *				the list when reopened
 */

#include "CustomFileDialog.h"
#include <QFileInfo>
#include <QDir>
#include <QAbstractItemView>
#include <QTimer>
#include <QSplitter>
#include <QHeaderView>

CustomFileDialog::CustomFileDialog(QWidget *parent,
								   const QString &caption,
								   const QString &directory,
								   const QString &filter,
								   const QColor &backgroundColor)
	: QDialog(parent)
{
	setWindowTitle(caption.isEmpty() ? tr("Open File") : caption);
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
	treeView = new QTreeView(this);
	treeView->setModel(model);
	treeView->setRootIndex(model->index(QDir::rootPath()));
	treeView->setColumnWidth(0, 200);
	treeView->hideColumn(1); // Size
	treeView->hideColumn(2); // Type
	treeView->hideColumn(3); // Date Modified
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
	splitter->setStretchFactor(0, 1); // Tree view
	splitter->setStretchFactor(1, 2); // List view gets more space

	// Create file name edit
	fileNameEdit = new QLineEdit(this);
	fileNameEdit->setReadOnly(true);

	// Create filter combo box
	filterCombo = new QComboBox(this);
	filterCombo->addItems(filterList);

	// Create buttons
	QPushButton *okButton = new QPushButton(tr("Open"), this);
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

	// Apply color scheme BEFORE showing dialog
	applyColorScheme(backgroundColor);

	// Apply initial filter
	if (!filterList.isEmpty())
	{
		applyFilter(filterList.first());
	}

	// Expand tree to current directory
	treeView->setCurrentIndex(model->index(currentDirectory));
	treeView->scrollTo(model->index(currentDirectory), QAbstractItemView::PositionAtCenter);

	// Connect signals
	connect(listView, &QListView::clicked, this, &CustomFileDialog::onFileClicked);
	connect(listView, &QListView::doubleClicked, this, &CustomFileDialog::onFileDoubleClicked);
	connect(treeView, &QTreeView::clicked, this, &CustomFileDialog::onTreeClicked);
	connect(okButton, &QPushButton::clicked, this, &CustomFileDialog::onOkClicked);
	connect(cancelButton, &QPushButton::clicked, this, &CustomFileDialog::onCancelClicked);
	connect(filterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CustomFileDialog::onFilterChanged);
	connect(pathEdit, &QLineEdit::editingFinished, this, &CustomFileDialog::onPathEditingFinished);
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
				"QLabel { color: white; } "
				"QTreeView { color: white; background-color: %2; selection-background-color: rgb(0, 120, 215); } "
				"QListView { color: white; background-color: %2; selection-background-color: rgb(0, 120, 215); } "
				"QLineEdit { color: white; background-color: %1; } "
				"QComboBox { color: white; background-color: %1; } "
				"QPushButton { color: white; background-color: %3; padding: 5px; } "
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
		listView->setRootIndex(model->index(path));
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
	if (info.isDir())
	{
		navigateToDirectory(info.absoluteFilePath());
	}
}

void CustomFileDialog::onPathEditingFinished()
{
	QString path = pathEdit->text();
	navigateToDirectory(path);
}

void CustomFileDialog::onOkClicked()
{
	if (!selectedFilePath.isEmpty())
	{
		accept();
	}
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

	// Scroll after dialog is shown
	if (!pendingFileSelection.isEmpty())
	{
		// First ensure the directory is set
		QString dir = QFileInfo(pendingFileSelection).absolutePath();
		listView->setRootIndex(model->index(dir));
		
		// Then scroll with a longer delay
		QTimer::singleShot(500, this, [this]() {
			QModelIndex index = model->index(pendingFileSelection);
			if (index.isValid())
			{
				// Use selection model and ensure visibility
				listView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::ClearAndSelect);
				listView->scrollTo(index, QAbstractItemView::PositionAtCenter);
				
				// Alternative: Try EnsureVisible if PositionAtCenter doesn't work
				// listView->scrollTo(index, QAbstractItemView::EnsureVisible);
				
				pendingFileSelection.clear();
			}
		});
	}
}
