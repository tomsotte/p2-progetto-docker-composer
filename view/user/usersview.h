#ifndef USERSVIEW_H
#define USERSVIEW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>
#include <QListWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>

#include "../../model/user/user.h"
#include "usercreateview.h"
#include "usereditview.h"


class UsersView : public QDialog
{
	Q_OBJECT
public:
	UsersView(User* ul, UserList* ulist, QWidget *parent = nullptr);

private:
	User* userLogged;
	UserList* userList;

	QHBoxLayout* layMain;

	QVBoxLayout* layList;
	QListWidget* lstUsers;
	QPushButton* btnAddUser;
	UserCreateView* createView;

	UserEditView* editView;

	QIcon userIcon;

	void setupEditUser();
	void setupUserList();
	void setupCreateUser();
	void setupMainLayout();

	void repopulateUserList();

signals:
	void saveUserList();
	void sendStatusBarMsg(const QString& msg);

public slots:
	void onAddUser();
	void onCancelCreate();
	void onSelectUser(const QString& name);

	void onSavedUser(User* u);
	void onRemovedUser(User* u);

	void onCreatedUser(User* u);
};

#endif // USERSVIEW_H
