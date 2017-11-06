#ifndef NETWORKCONFIGVIEW_H
#define NETWORKCONFIGVIEW_H

#include <QCheckBox>
#include <QGroupBox>
#include <QRadioButton>

#include "baseconfigview.h"
#include "../../model/compose/networkconfig.h"

class NetworkConfigView : public BaseConfigView
{
	Q_OBJECT
public:
	NetworkConfigView(NetworkConfig* c, User* ul, QWidget* parent = nullptr);

	virtual void reload();
	virtual void save();

	virtual bool validate();

protected:
	virtual void setupEditWidget();
	virtual void setupPermissions();

private:
	QGroupBox* bgrIntExt;
	QRadioButton* radInternal;
	QRadioButton* radExternal;

	QLineEdit* edtDriver;
	QLineEdit* edtExternalName;
	QCheckBox* chkIp6;
	QLineEdit* edtIpamDriver;
	QLineEdit* edtIpamSubnet;
};

#endif // NETWORKCONFIGVIEW_H
