#ifndef USEREDITVIEW_H
#define USEREDITVIEW_H

#include "userview.h"

class UserEditView : public UserView
{
	Q_OBJECT
public:
	UserEditView(User* ul, QWidget* parent = nullptr);

	virtual void setUserShow(User* u);

protected:
	virtual void setupButtonsLayout();
	virtual void setupFormLayout();

private:
	QHBoxLayout* layBtns;
	QPushButton* btnSave;
	QPushButton* btnRemove;

signals:
	void removeUser(User* u);
	void saveUser(User* u);

public slots:
	void onSave();
	void onRemove();
};

#endif // USEREDITVIEW_H
