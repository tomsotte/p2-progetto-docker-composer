#include "editablestringlistitem.h"

EditableStringListItem::EditableStringListItem(const QString& str, QWidget *parent)
	: QWidget(parent)
{
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
	// TODO this can be static; too many initializations
	icnRemove = QIcon(QPixmap(":/res/removecircle.svg"));

	setupMainLayout();
	edtLine->setText(str);
	setLayout(layMain);
}

QString EditableStringListItem::getText() const
{
	return edtLine->text();
}

QLineEdit* EditableStringListItem::getEdtLine() const
{
	return edtLine;
}

void EditableStringListItem::setupMainLayout()
{
	btnRemove = new QPushButton();
	btnRemove->setIcon(icnRemove);
	btnRemove->setObjectName("FlatTransparentBtn");
	connect(btnRemove, SIGNAL(clicked(bool)), this, SLOT(onRemoveClicked()));

	edtLine = new QLineEdit();

	layMain = new QHBoxLayout();
//	layMain->setSpacing(0);
	layMain->setMargin(0);
	layMain->addWidget(edtLine, 1);
	layMain->addWidget(btnRemove);
}

void EditableStringListItem::onRemoveClicked()
{
	emit remove(this);
}
