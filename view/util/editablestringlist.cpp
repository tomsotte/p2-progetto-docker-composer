#include "editablestringlist.h"

#include <QIcon>
#include <QPixmap>

EditableStringList::EditableStringList(QWidget *parent) : QWidget(parent)
{
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
	setupMainLayout();
	setLayout(layMain);
}

std::vector<std::string> EditableStringList::getStdStringVector() const
{
	std::vector<std::string> list;

	EditableStringListItem* item;
	for (int i = 0; i < layList->count(); ++i) {
		// we can safely assume itemAt returns a QLayoutItem
		// with a EditableStringListItem* widget
		item = static_cast<EditableStringListItem*>(layList->itemAt(i)->widget());

		// insert only non-empty item
		if (item->getText().length()) list.push_back(item->getText().toStdString());
	}

	return list;
}

void EditableStringList::fromStdStringVector(const std::vector<std::string>& v)
{
	// http://doc.qt.io/qt-4.8/qlayout.html#takeAt
	// Safe way to remove and delete all widget from a layout
	QLayoutItem *child;
	while ((child = layList->takeAt(0)) != 0) {
		delete child->widget();
		delete child;
	}

	for (const std::string& str : v) addRow(QString::fromStdString(str));
}

void EditableStringList::addRow(const QString& str)
{
	EditableStringListItem* item = new EditableStringListItem(str, this);
	if (completer) item->getEdtLine()->setCompleter(completer);
	connect(item, SIGNAL(remove(EditableStringListItem*)),
			this, SLOT(onRemoveRow(EditableStringListItem*)));

	layList->addWidget(item);
}

void EditableStringList::setCompleter(QCompleter* value)
{
	completer = value;
}

void EditableStringList::setupMainLayout()
{
	btnAddRow = new QPushButton();
	btnAddRow->setIcon(QIcon(QPixmap(":/res/add.svg")));
	connect(btnAddRow, SIGNAL(clicked(bool)), this, SLOT(onAddRow()));

	layList = new QVBoxLayout();
	layList->setMargin(0);

	layMain = new QVBoxLayout();
	layMain->setMargin(0);
	layMain->setSpacing(0);
	layMain->addLayout(layList, 1);
	layMain->addWidget(btnAddRow);
}

void EditableStringList::onAddRow()
{
	addRow();
}

void EditableStringList::onRemoveRow(EditableStringListItem* row)
{
	layList->removeWidget(row);
	delete row;
}
