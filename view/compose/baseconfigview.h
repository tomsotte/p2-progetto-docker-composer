#ifndef BASECONFIGVIEW_H
#define BASECONFIGVIEW_H

#include <QWidget>
#include <QLineEdit>
#include <QLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QString>

#include "../../model/compose/baseconfig.h"
#include "../../model/user/user.h"

class BaseConfigView : public QWidget
{
	Q_OBJECT
public:
	BaseConfigView(BaseConfig* c, User* ul, QWidget *parent = nullptr);

	virtual BaseConfig* getConfig() const;

	virtual void save();
	virtual void reload();
	virtual void reloadOutput();

	virtual bool validate();
	virtual void resetErrors();
	virtual void showErrors(const QString& msg);

protected:
	BaseConfig* config {nullptr};
	User* userLogged; // needed for permissions support

	QLayout* layMain;

	// main part of the view; to be expanded on derived classes
	QWidget* wdgEdit;

	QWidget* wdgHeader;
	QLabel* lblConfigType;
	QLabel* lblErrors;
	QPushButton* btnSave;
	QPushButton* btnReload;
	QPushButton* btnClone;
	QPushButton* btnRemove;

	QWidget* wdgInfo;
	QLineEdit* edtConfigName;
	QLineEdit* edtConfigAuthor;

	QWidget* wdgOutput;
	QLabel* lblLinesCount;
	QTextEdit* txtOutput;
	QPushButton* btnCopy;
	QPushButton* btnShowHide;

	virtual void setupHeaderWidget();
	virtual void setupInfoWidget();
	virtual void setupEditWidget() = 0;
	virtual void setupOutputWidget();
	virtual void setupMainLayout();

	virtual void setupPermissions(bool canEditType);

signals:
	void sendStatusBarMsg(const QString&) const;

	void cloneConfig(BaseConfig*);
	void savedConfig(BaseConfig*);
	void reloadedConfig(BaseConfig*);
	void removeConfig(BaseConfig*);

public slots:
	void onCloneConfig();
	void onSaveConfig();
	void onReloadConfig();
	void onRemoveConfig();

	void showHideTxtOut();
	void copyToClipboard() const;
};

#endif // BASECONFIGVIEW_H
