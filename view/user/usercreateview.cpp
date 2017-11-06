#include "usercreateview.h"

UserCreateView::UserCreateView(User* ul, UserList* ulist, QWidget *parent)
	: UserView(ul, parent), userList(ulist)
{
	setTitle("Crea utente");

	setupButtonsLayout();
	setupFormLayout();
	setupMainLayout();

	setLayout(layMain);
}

void UserCreateView::setupFormLayout()
{
	UserView::setupFormLayout();

	edtName->setEnabled(true);
	edtPassword->setEnabled(true);
	cmbRole->setEnabled(true);
}

void UserCreateView::setupButtonsLayout()
{
	btnCreate = new QPushButton("Crea");
	connect(btnCreate, SIGNAL(clicked(bool)), this, SLOT(onCreateUser()));

	btnCancel = new QPushButton("Cancella");
	connect(btnCancel, SIGNAL(clicked(bool)), this, SLOT(onCancel()));

	layBtns = new QHBoxLayout();
	layBtns->setMargin(0);
	layBtns->addStretch(1);
	layBtns->addWidget(btnCancel);
	layBtns->addWidget(btnCreate);

	wdgBtns = new QWidget();
	wdgBtns->setLayout(layBtns);
}

void UserCreateView::resetForm()
{
	edtName->setText("");
	edtPassword->setText("");
	cmbRole->setCurrentIndex(0);
}

void UserCreateView::onCreateUser()
{
	const std::string& name = edtName->text().toStdString();
	const std::string& password = edtPassword->text().toStdString();
	const std::string& role = cmbRole->currentText().toStdString();

	lblFeedback->setText("");

	if (name.empty()) {
		lblFeedback->setText("Il nome non può essere vuoto.");
    }

    User* u = UserList::createUser(role, name, password);
    try {
        userList->add(u);
        emit createdUser(u);
	} catch(UserList::UserAlreadyExistsException e) {
        if (u) delete u;
        lblFeedback->setText("Nome già in uso.");
    }
}

void UserCreateView::onCancel()
{
	resetForm();
	emit cancelCreate();
}
