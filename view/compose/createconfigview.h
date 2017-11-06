#ifndef CREATECONFIGVIEW_H
#define CREATECONFIGVIEW_H

#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "../../model/compose/baseconfig.h"
#include "../../model/compose/composeconfig.h"
#include "../../model/user/user.h"

class CreateConfigView : public QDialog
{
	Q_OBJECT
public:
	CreateConfigView(ComposeConfig* cc, User* u, BaseConfig* cf = nullptr,
					 QWidget* parent = nullptr);

	void resetForm();

private:
	ComposeConfig* compose;
	User* user;
	BaseConfig* cloneFrom;

	QVBoxLayout* layMain;
	QComboBox* cmbPartTypes;
	QLineEdit* edtName;
	QLineEdit* edtAuthor;

	QPushButton* btnSave;
	QPushButton* btnCancel;
	QLabel* lblFeedback;

	void setupMainLayout();
	void setupTypesComboBox();

signals:
	void addedConfig(BaseConfig* c);

public slots:
	void onCreate();
};

#endif // CREATECONFIGVIEW_H
