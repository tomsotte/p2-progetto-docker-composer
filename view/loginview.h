#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

#include "../model/user/userlist.h"

class LoginView : public QWidget
{
	Q_OBJECT
public:
	LoginView(QWidget* parent, UserList* u);

	void testAdmin();

private:
	UserList* users;

	QHBoxLayout* layMain;

	QWidget* wdgCenterContent;
	QVBoxLayout* layCenter;

	QFormLayout* layForm;
	QLineEdit* edtName;
	QLineEdit* edtPassword;
	QPushButton* btnSubmit;
	QLabel* lblFeedback;

	void setupMainLayout();
	void setupFormLayout();

signals:
	void logged(User* u);

public slots:
	void onAttemptLogin();
};

#endif // LOGINVIEW_H
