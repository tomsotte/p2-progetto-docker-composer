#include "usersview.h"

#include <QFormLayout>
#include <QIcon>
#include <QPixmap>

UsersView::UsersView(User* ul, UserList* ulist, QWidget* parent)
	: QDialog(parent), userLogged(ul), userList(ulist)
{
	userIcon = QIcon(QPixmap(":/res/user.svg"));

	setupEditUser();
	setupUserList();
	setupCreateUser();

	setupMainLayout();
	setLayout(layMain);
}

void UsersView::setupUserList()
{
	lstUsers = new QListWidget();
	connect(lstUsers, SIGNAL(currentTextChanged(QString)),
			this, SLOT(onSelectUser(QString)));
	repopulateUserList();
}

void UsersView::setupCreateUser()
{
	btnAddUser = new QPushButton("Aggiungi utente");
	btnAddUser->setIcon(QIcon(QPixmap(":/res/adduser.svg")));
	btnAddUser->setEnabled(userLogged->isAdmin());
	connect(btnAddUser, SIGNAL(clicked(bool)), this, SLOT(onAddUser()));

	createView = new UserCreateView(userLogged, userList);
	createView->hide();
	connect(createView, SIGNAL(createdUser(User*)), this, SLOT(onCreatedUser(User*)));
	connect(createView, SIGNAL(cancelCreate()), this, SLOT(onCancelCreate()));
}

void UsersView::setupEditUser()
{
	editView = new UserEditView(userLogged);
	connect(editView, SIGNAL(saveUser(User*)), this, SLOT(onSavedUser(User*)));
	connect(editView, SIGNAL(removeUser(User*)), this, SLOT(onRemovedUser(User*)));
}

void UsersView::setupMainLayout()
{
	layList = new QVBoxLayout();
	layList->addWidget(lstUsers, 1);
	layList->addWidget(btnAddUser);
	layList->addWidget(createView);

	layMain = new QHBoxLayout();
	layMain->addLayout(layList, 1);
	layMain->addWidget(editView);
}

void UsersView::repopulateUserList()
{
	lstUsers->clear();

	QListWidgetItem* item;

	for (auto u : *userList) {
		item = new QListWidgetItem(userIcon, QString::fromStdString(u->getName()));
		if (*u == *userLogged) item->setBackgroundColor(Qt::GlobalColor::cyan);

		lstUsers->addItem(item);
	}
}

void UsersView::onSavedUser(User* u)
{
	emit sendStatusBarMsg("Info utente " + QString::fromStdString(u->getName()) +
						  " salvate.");
	emit saveUserList();
}

void UsersView::onRemovedUser(User* u)
{
	editView->setUserShow(userLogged);
	userList->remove(u);
	repopulateUserList();

	emit sendStatusBarMsg("Rimosso l'utente. Lista utenti salvata.");
	emit saveUserList();
}

void UsersView::onCreatedUser(User* u)
{
	createView->resetForm();
	createView->hide();
	btnAddUser->show();

	repopulateUserList();

	emit sendStatusBarMsg("Aggiunto un nuovo utente: " +
						  QString::fromStdString(u->getName()) +
						  " (" + QString::fromStdString(u->getRole()) + "). " +
						  "Lista utenti salvata.");
	emit saveUserList();
}

void UsersView::onAddUser()
{
	btnAddUser->hide();
	createView->show();
	createView->setFocus();
}

void UsersView::onCancelCreate()
{
	createView->hide();
	btnAddUser->show();
	btnAddUser->setFocus();
}

void UsersView::onSelectUser(const QString& name)
{
	User* u = userList->findUserByName(name.toStdString());
	if (u) editView->setUserShow(u);
}
