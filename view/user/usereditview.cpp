#include "usereditview.h"

#include <QMessageBox>

UserEditView::UserEditView(User* ul, QWidget* parent)
	: UserView(ul, parent)
{
	setTitle("Modifica utente");

	setupButtonsLayout();
	setupFormLayout();
	setupMainLayout();

	setLayout(layMain);

	setUserShow(ul);
}

void UserEditView::setUserShow(User* u)
{
	UserView::setUserShow(u);

	bool isAdminOrLogged = isAdmin || userLogged == userShow;
	edtPassword->setEnabled(isAdminOrLogged);
	edtPassword->setText(isAdminOrLogged
						 ? QString::fromStdString(u->getPassword())
						 : "password");
	btnSave->setEnabled(isAdminOrLogged);
	// prevent an admin account to delete itself
	btnRemove->setEnabled(isAdmin && userLogged != userShow);
}

void UserEditView::setupButtonsLayout()
{
	btnSave = new QPushButton("Salva");
	btnSave->setIcon(QIcon(QPixmap(":/res/save.svg")));
	connect(btnSave, SIGNAL(clicked(bool)), this, SLOT(onSave()));

	btnRemove = new QPushButton("Rimuovi");
	btnRemove->setIcon(QIcon(QPixmap(":/res/trashbin.svg")));
	btnRemove->setEnabled(false);
	connect(btnRemove, SIGNAL(clicked(bool)), this, SLOT(onRemove()));

	layBtns = new QHBoxLayout();
	layBtns->setMargin(0);
	layBtns->addStretch(1);
	layBtns->addWidget(btnRemove);
	layBtns->addWidget(btnSave);

	wdgBtns = new QWidget();
	wdgBtns->setLayout(layBtns);
}

void UserEditView::setupFormLayout()
{
	UserView::setupFormLayout();

	lblFeedback->hide();
}

void UserEditView::onSave()
{
	userShow->setPassword(edtPassword->text().toStdString());

	emit saveUser(userShow);
}

void UserEditView::onRemove()
{
	QMessageBox confirmRemove;
	confirmRemove.setText("Conferma rimozione dell'utente.");
	confirmRemove.setInformativeText("Sei sicuro di volere rimuovere definitivamente "
									 "l'utente '" +
									 QString::fromStdString(userShow->getName()) +
									 "' (" + QString::fromStdString(userShow->getRole()) +
									 ")?");

	confirmRemove.setIcon(QMessageBox::Warning);
	confirmRemove.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
	confirmRemove.setDefaultButton(QMessageBox::Cancel);

	if (confirmRemove.exec() == QMessageBox::Ok) emit removeUser(userShow);
}
