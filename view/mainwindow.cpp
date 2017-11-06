#include "mainwindow.h"

#include <QIcon>
#include <QPixmap>
#include <QFile>

MainWindow::MainWindow(Core* c, QWidget* parent) : QMainWindow(parent), core(c)
{
	setWindowTitle("DockerComposer");
	setWindowIcon(QIcon(QPixmap(":/logo")));
	setMinimumSize(960, 640);
	setDefaultStyleSheet();

	setupMenuBar();
	setupStatusBar();
	setupLoginView();

	setMenuBar(menuBar);
	setStatusBar(statusBar);
	setToLoginScreen();
}

void MainWindow::setToLoginScreen()
{
	setCentralWidget(loginView);
}

void MainWindow::setToEditView()
{
	setCentralWidget(editView);
}

void MainWindow::setCentralWidget(QWidget* w)
{
	// Prevents setCentralWidget to deleting the current central widget
	// Needed for hot swapping between login and edit views
	if (centralWidget()) centralWidget()->setParent(nullptr);

	QMainWindow::setCentralWidget(w);
}

void MainWindow::setupMenuBar()
{
	menuBar = new QMenuBar();
	menuBar->hide();
	QAction* openUsersAct = menuBar->addAction("Utenti");
	connect(openUsersAct, SIGNAL(triggered(bool)), this, SLOT(onOpenUsersView()));
}

void MainWindow::setupStatusBar()
{
	btnLogout = new QPushButton();
	btnLogout->setText("Logout");
	btnLogout->hide();
	connect(btnLogout, SIGNAL(clicked(bool)), this, SLOT(onLogout()));

	statusBar = new QStatusBar();
	statusBar->showMessage("Applicazione avviata. Nessun utente connesso.");
	statusBar->addPermanentWidget(btnLogout);
}

void MainWindow::setupLoginView()
{
	loginView = new LoginView(this, core->getUsers());
	connect(loginView, SIGNAL(logged(User*)), this, SLOT(onLogin(User*)));
}

void MainWindow::setupEditView()
{
	editView = new EditView(core, this);
	connect(editView, SIGNAL(sendStatusBarMsg(QString)),
			this, SLOT(onSendStatusBarMsg(QString)));
}

void MainWindow::setupUsersView()
{
	usersView = new UsersView(core->getLoggedUser(), core->getUsers(), this);
	connect(usersView, SIGNAL(saveUserList()), this, SLOT(onSaveUsersList()));
	connect(usersView, SIGNAL(sendStatusBarMsg(QString)),
			this, SLOT(onSendStatusBarMsg(QString)));
}

void MainWindow::setDefaultStyleSheet()
{
	QFile File(":/style");
	File.open(QFile::ReadOnly);
	QString StyleSheet = QString(File.readAll());

	setStyleSheet(StyleSheet);
}

void MainWindow::onLogin(User* u)
{
	statusBar->showMessage("Sei collegato con l'utente " +
						   QString::fromStdString(u->getName()));

	core->setLoggedUser(u);
	setupUsersView();

	btnLogout->show();
	menuBar->show();

	setupEditView();
	setToEditView();
}

void MainWindow::onLogout()
{
	core->setLoggedUser(nullptr);

	statusBar->showMessage("Logout completato.");

	btnLogout->hide();
	menuBar->hide();

	// delete at every logout because these views permissions
	// are specific to the logged user
	usersView->deleteLater();
	editView->deleteLater();

	setToLoginScreen();
}

void MainWindow::onOpenUsersView()
{
	usersView->show();
}

void MainWindow::onSaveUsersList()
{
	core->saveUsers();
}

void MainWindow::onSendStatusBarMsg(const QString& msg)
{
	statusBar->showMessage(msg);
}
