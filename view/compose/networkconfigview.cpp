#include "networkconfigview.h"

#include <QScrollArea>
#include <QFormLayout>

NetworkConfigView::NetworkConfigView(NetworkConfig* c, User* ul, QWidget* parent)
	: BaseConfigView(c, ul, parent)
{
	setupHeaderWidget();
	setupInfoWidget();
	setupEditWidget();
	setupOutputWidget();

	setupMainLayout();
	setupPermissions();
	setLayout(layMain);

	reload();
}

void NetworkConfigView::reload()
{
	BaseConfigView::reload();

	NetworkConfig* n = dynamic_cast<NetworkConfig*>(config);
	edtDriver->setText(QString::fromStdString(n->getDriver()));
	edtExternalName->setText(QString::fromStdString(n->getExternalName()));
	edtIpamDriver->setText(QString::fromStdString(n->getIpamDriver()));
	edtIpamSubnet->setText(QString::fromStdString(n->getIpamSubnet()));
	radExternal->setChecked(n->getExternal());
	radInternal->setChecked(n->getInternal());
	chkIp6->setChecked(n->getIp6());

	validate();
}

void NetworkConfigView::save()
{
	BaseConfigView::save();

	NetworkConfig* n = dynamic_cast<NetworkConfig*>(config);
	n->setDriver(edtDriver->text().toStdString());
	n->setExternalName(edtExternalName->text().toStdString());
	n->setIpamDriver(edtIpamDriver->text().toStdString());
	n->setIpamSubnet(edtIpamSubnet->text().toStdString());
	n->setInternal(radInternal->isChecked());
	n->setExternal(radExternal->isChecked());
	n->setIp6(chkIp6->isChecked());

	validate();
}

bool NetworkConfigView::validate()
{
	BaseConfigView::validate();

	try {
		config->validate();
	} catch(NetworkConfig::DiscardedDriverAndIpamException) {
		showErrors("NOTA: Siccome external, le impostazioni driver e ipam "
				   "non verranno considerate nell'output.");
	}

	return true;
}

void NetworkConfigView::setupEditWidget()
{
	radInternal = new QRadioButton("internal");
	radExternal = new QRadioButton("external");

	QHBoxLayout* layIntExt = new QHBoxLayout();
	layIntExt->addWidget(radInternal);
	layIntExt->addWidget(radExternal);

	bgrIntExt = new QGroupBox();
//	bgrIntExt->setFlat(true);
	bgrIntExt->setLayout(layIntExt);

	edtDriver = new QLineEdit();
	// TODO add check external, if not, dont let change external:name
	edtExternalName = new QLineEdit();
	edtIpamDriver = new QLineEdit();
	edtIpamSubnet = new QLineEdit();
	chkIp6 = new QCheckBox();

	QFormLayout* layForm = new QFormLayout();
//	layForm->setRowWrapPolicy(QFormLayout::WrapAllRows);
	layForm->addRow("driver", edtDriver);
	layForm->addRow("", bgrIntExt);
	layForm->addRow("external:name", edtExternalName);
	layForm->addRow("ip6", chkIp6);
	layForm->addRow("ipam:driver", edtIpamDriver);
	layForm->addRow("ipam:subnet", edtIpamSubnet);

	QWidget* wdgEditContent = new QWidget();
	wdgEditContent->setLayout(layForm);

	QScrollArea* slaEdit = new QScrollArea();
	slaEdit->setWidget(wdgEditContent);
	slaEdit->setWidgetResizable(true);
	slaEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	wdgEdit = slaEdit;
}

void NetworkConfigView::setupPermissions()
{
	BaseConfigView::setupPermissions(userLogged->canEditNetwork());
}

