#include "loginview.h"

#include <QLabel>
#include <QPicture>
#include <QFormLayout>

#include "../model/user/user.h"

LoginView::LoginView(QWidget* parent, UserList* u) : QWidget(parent), users(u)
{
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

	setupFormLayout();
	setupMainLayout();

	setLayout(layMain);
}

void LoginView::setupMainLayout()
{
	QLabel* logo = new QLabel();
	logo->setPixmap(QPixmap(":/logo").scaled(128, 128));
	logo->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	layCenter = new QVBoxLayout();
	layCenter->addWidget(logo);
	layCenter->addLayout(layForm);
	layCenter->setAlignment(logo, Qt::AlignCenter);

	wdgCenterContent = new QWidget();
	wdgCenterContent->setLayout(layCenter);
	wdgCenterContent->setFixedWidth(320);
	wdgCenterContent->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);

	layMain = new QHBoxLayout();
	layMain->addStretch();
	layMain->addWidget(wdgCenterContent);
	layMain->addStretch();
}

void LoginView::setupFormLayout()
{
	edtName = new QLineEdit();
	edtName->setPlaceholderText("Inserisci il nome utente");
	edtName->setFocus();
	connect(edtName, SIGNAL(returnPressed()), this, SLOT(onAttemptLogin()));

	edtPassword = new QLineEdit();
	edtPassword->setPlaceholderText("Inserisci la password");
	edtPassword->setEchoMode(QLineEdit::Password);
	connect(edtPassword, SIGNAL(returnPressed()), this, SLOT(onAttemptLogin()));

	btnSubmit = new QPushButton("Login");
	btnSubmit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
	connect(btnSubmit, SIGNAL(clicked(bool)), this, SLOT(onAttemptLogin()));

	lblFeedback = new QLabel();
	lblFeedback->setObjectName("LabelFeedback");
	lblFeedback->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

	layForm = new QFormLayout();
	layForm->addRow("Username", edtName);
	layForm->addRow("Password", edtPassword);
	layForm->addRow(btnSubmit);
	layForm->addRow(lblFeedback);
	layForm->setAlignment(btnSubmit, Qt::AlignRight);
}

void LoginView::testAdmin()
{
	User* user = users->findUserByName("admin");
	emit logged(user);
}

void LoginView::onAttemptLogin()
{
	lblFeedback->setText("");

	const std::string& name = edtName->text().toStdString();
	const std::string& pass = edtPassword->text().toStdString();

	User* user = users->findUserByName(name);

	if (!user) {
		lblFeedback->setText("Nessun utente trovato con il nome specificato.");
		return;
	}

	if (!user->checkPassword(pass)) {
		lblFeedback->setText("Password non corretta.");
		return;
	}

	emit logged(user);
}
