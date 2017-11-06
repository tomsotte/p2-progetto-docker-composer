#ifndef USERVIEW_H
#define USERVIEW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>

#include "../../model/user/user.h"

class UserView : public QGroupBox
{
	Q_OBJECT
public:
	UserView(User* ul, QWidget *parent = nullptr);

	virtual void setUserShow(User* u);

protected:
	User* userLogged {nullptr};
	User* userShow {nullptr};
	bool isAdmin;

	QVBoxLayout* layMain;

	QFormLayout* layForm;
	QLineEdit* edtName;
	QLineEdit* edtPassword;
	QComboBox* cmbRole;
	QLabel* lblFeedback;
	QWidget* wdgBtns;

	virtual void setupButtonsLayout();
	virtual void setupFormLayout();
	virtual void setupMainLayout();

	bool isCurrentUser();

signals:

public slots:
};

#endif // USERVIEW_H
