#include "volumeconfigview.h"

#include <QScrollArea>
#include <QFormLayout>

VolumeConfigView::VolumeConfigView(VolumeConfig* c, User* ul, QWidget* parent)
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

void VolumeConfigView::reload()
{
	BaseConfigView::reload();

	VolumeConfig* v = dynamic_cast<VolumeConfig*>(config);
	edtDriver->setText(QString::fromStdString(v->getDriver()));
	chkExternal->setChecked(v->getExternal());
	edtExternalName->setText(QString::fromStdString(v->getExternalName()));

	validate();
}

void VolumeConfigView::save()
{
	BaseConfigView::save();

	VolumeConfig* v = dynamic_cast<VolumeConfig*>(config);
	v->setDriver(edtDriver->text().toStdString());
	v->setExternal(chkExternal->isChecked());
	v->setExternalName(edtExternalName->text().toStdString());

	validate();
}

bool VolumeConfigView::validate()
{
	BaseConfigView::validate();

	try {
		config->validate();
	} catch(VolumeConfig::DiscardedDriverException) {
		showErrors("NOTA: Siccome external, le impostazioni driver "
				   "non verranno considerate nell'output.");
	}

	return true;
}

void VolumeConfigView::setupEditWidget()
{
	edtDriver = new QLineEdit();
	chkExternal = new QCheckBox();
	// TODO add check external, if not, dont let change external:name
	edtExternalName = new QLineEdit();

	QFormLayout* layForm = new QFormLayout();
//	layForm->setRowWrapPolicy(QFormLayout::WrapAllRows);
	layForm->addRow("driver", edtDriver);
	layForm->addRow("external", chkExternal);
	layForm->addRow("external:name", edtExternalName);

	QWidget* wdgEditContent = new QWidget();
	wdgEditContent->setLayout(layForm);

	QScrollArea* slaEdit = new QScrollArea();
	slaEdit->setWidget(wdgEditContent);
	slaEdit->setWidgetResizable(true);
	slaEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	wdgEdit = slaEdit;
}

void VolumeConfigView::setupPermissions()
{
	BaseConfigView::setupPermissions(userLogged->canEditNetwork());
}
