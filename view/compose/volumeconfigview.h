#ifndef VOLUMECONFIGVIEW_H
#define VOLUMECONFIGVIEW_H

#include <QCheckBox>

#include "baseconfigview.h"
#include "../../model/compose/volumeconfig.h"

class VolumeConfigView : public BaseConfigView
{
	Q_OBJECT
public:
	VolumeConfigView(VolumeConfig* c, User* ul, QWidget* parent = nullptr);

	virtual void reload();
	virtual void save();

	virtual bool validate();

protected:
	virtual void setupEditWidget();
	virtual void setupPermissions();

private:
	QLineEdit* edtDriver;
	QCheckBox* chkExternal;
	QLineEdit* edtExternalName;
};

#endif // VOLUMECONFIGVIEW_H
