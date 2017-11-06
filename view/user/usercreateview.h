#ifndef USERCREATEVIEW_H
#define USERCREATEVIEW_H

#include "userview.h"
#include "../../model/user/userlist.h"

class UserCreateView : public UserView
{
	Q_OBJECT
public:
	UserCreateView(User* ul, UserList* ulist, QWidget *parent = nullptr);

	void resetForm();

protected:
	virtual void setupFormLayout();
	virtual void setupButtonsLayout();

private:
	UserList* userList;

	QHBoxLayout* layBtns;
	QPushButton* btnCreate;
	QPushButton* btnCancel;

signals:
	void createdUser(User* u);
	void cancelCreate();

public slots:
	void onCreateUser();
	void onCancel();
};

#endif // USERCREATEVIEW_H

