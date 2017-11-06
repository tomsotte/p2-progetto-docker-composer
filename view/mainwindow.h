#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStatusBar>
#include <QMenuBar>
#include <QPushButton>
#include <QString>

#include "../model/core.h"
#include "loginview.h"
#include "editview.h"
#include "user/usersview.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(Core* c, QWidget* parent = nullptr);

	void setToLoginScreen();
	void setToEditView();

private:
	Core* core;

	QStatusBar* statusBar;
	QPushButton* btnLogout;

	LoginView* loginView;
	EditView* editView;

	QMenuBar* menuBar;
	UsersView* usersView;

	void setupMenuBar();
	void setupStatusBar();
	void setupLoginView();
	void setupEditView();
	void setupUsersView();

	void setDefaultStyleSheet();

	void setCentralWidget(QWidget* w);

private slots:
	void onLogin(User* u);
	void onLogout();

	void onOpenUsersView();
	void onSaveUsersList();

	void onSendStatusBarMsg(const QString& msg);
};

#endif // MAINWINDOW_H
