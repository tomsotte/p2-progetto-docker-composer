#ifndef SERVICECONFIGVIEW_H
#define SERVICECONFIGVIEW_H

#include "baseconfigview.h"

#include "../../model/compose/serviceconfig.h"
#include "composeautocompleters.h"
#include "../util/editablestringlist.h"

class ServiceConfigView : public BaseConfigView
{
	Q_OBJECT
public:
	ServiceConfigView(ServiceConfig* c, User* ul, ComposeAutocompleters* cac,
					  QWidget *parent = nullptr);

	virtual void reload();
	virtual void save();

	virtual bool validate();

protected:
	virtual void setupEditWidget();
	virtual void setupPermissions();

private:
	ComposeAutocompleters* completers;

	QLineEdit* edtImage;
	QLineEdit* edtBuildContext;
	QLineEdit* edtBuildDockerfile;
	QLineEdit* edtContainerName;

	EditableStringList* eslPorts;
	EditableStringList* eslLinks;
	EditableStringList* eslNetworks;
	EditableStringList* eslVolumes;
	EditableStringList* eslEnvironment;

public slots:
//	void onUpdateCompose();

};

#endif // SERVICECONFIGVIEW_H
