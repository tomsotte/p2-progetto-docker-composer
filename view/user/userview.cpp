#include "userview.h"

#include <QIcon>
#include <QPixmap>

#include "../../model/user/adminuser.h"
#include "../../model/user/networkuser.h"
#include "../../model/user/completeuser.h"
#include "../../model/user/volumeuser.h"
#include "../../model/user/manageruser.h"

UserView::UserView(User* ul, QWidget *parent)
	: QGroupBox(parent), userLogged(ul), userShow(ul), isAdmin(ul->isAdmin())
{
	setTitle("Visualizza utente");
}

void UserView::setUserShow(User* u)
{
	userShow = u;

	edtName->setText(QString::fromStdString(userShow->getName()));
	edtPassword->setText(QString::fromStdString(userShow->getPassword()));
	cmbRole->setCurrentText(QString::fromStdString(userShow->getRole()));

	edtPassword->setFocus();
}

void UserView::setupMainLayout()
{
	layMain = new QVBoxLayout();
	layMain->addLayout(layForm, 1);
}

bool UserView::isCurrentUser()
{
	return *userLogged == *userShow;
}

void UserView::setupButtonsLayout()
{
	wdgBtns = new QWidget();
}

void UserView::setupFormLayout()
{
	edtName = new QLineEdit();
	edtName->setDisabled(true);

	edtPassword = new QLineEdit();
	edtPassword->setEchoMode(QLineEdit::Password);
	edtPassword->setDisabled(true);

	cmbRole = new QComboBox();
	cmbRole->addItem(QString::fromStdString(CompleteUser::modelName));
	cmbRole->addItem(QString::fromStdString(NetworkUser::modelName));
	cmbRole->addItem(QString::fromStdString(VolumeUser::modelName));
	cmbRole->addItem(QString::fromStdString(AdminUser::modelName));
	cmbRole->addItem(QString::fromStdString(ManagerUser::modelName));
	cmbRole->setDisabled(true);

	lblFeedback = new QLabel();
	lblFeedback->setObjectName("LabelFeedback");

	layForm = new QFormLayout();
	layForm->addRow("Nome", edtName);
	layForm->addRow("Password", edtPassword);
	layForm->addRow("Ruolo", cmbRole);
	layForm->addRow(wdgBtns);
	layForm->addRow(lblFeedback);
}
