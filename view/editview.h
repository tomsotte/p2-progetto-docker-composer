#ifndef EDITVIEW_H
#define EDITVIEW_H

#include <QSplitter>
#include <QHBoxLayout>

#include "../model/core.h"
#include "compose/composeconfigview.h"
#include "compose/baseconfigview.h"
#include "compose/composeautocompleters.h"
#include "compose/createconfigview.h"

class EditView : public QSplitter
{
	Q_OBJECT
public:
	EditView(Core* c, QWidget *parent = nullptr);

private:
	Core* core;

	ComposeAutocompleters* completer;
	ComposeConfigView* composeView; // left view
	QWidget* rightView; // used for compose parts mostly

	void setupComposeView();
	void setupRightView();

	void swapRightView(QWidget* to);

	BaseConfigView* createConfigView(BaseConfig* c);

signals:
	void updatedCompose(ComposeConfig*);
	void sendStatusBarMsg(const QString&);

public slots:
	void onSendStatusBarMsg(const QString& msg);
	void onSelectConfig(BaseConfig* c);
	void onSavedConfig(BaseConfig* c);
	void onAddedConfig(BaseConfig* c);
	void onRemoveConfig(BaseConfig* c);
	void onCreateConfig(BaseConfig* cloneFrom);
};

#endif // EDITVIEW_H
