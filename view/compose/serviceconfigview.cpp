#include "serviceconfigview.h"

#include <QFormLayout>
#include <QScrollArea>
//#include <QLayout>

ServiceConfigView::ServiceConfigView(ServiceConfig* c, User* ul,
									 ComposeAutocompleters* cac, QWidget* parent)
	: BaseConfigView(c, ul, parent), completers(cac)
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

void ServiceConfigView::reload()
{
	BaseConfigView::reload();

	ServiceConfig* s = dynamic_cast<ServiceConfig*>(config);

	edtImage->setText(QString::fromStdString(s->getImage()));
	edtBuildContext->setText(QString::fromStdString(s->getBuildContext()));
	edtBuildDockerfile->setText(QString::fromStdString(s->getBuildDockerfile()));
	edtContainerName->setText(QString::fromStdString(s->getContainerName()));

	eslEnvironment->fromStdStringVector(s->getEnvironment());
	eslPorts->fromStdStringVector(s->getPorts());
	eslNetworks->fromStdStringVector(s->getNetworks());
	eslLinks->fromStdStringVector(s->getLinks());
	eslVolumes->fromStdStringVector(s->getVolumes());

	validate();
}

void ServiceConfigView::save()
{
	BaseConfigView::save();

	ServiceConfig* s = dynamic_cast<ServiceConfig*>(config);

	s->setLinks(eslLinks->getStdStringVector());
	s->setEnvironment(eslEnvironment->getStdStringVector());
	s->setNetworks(eslNetworks->getStdStringVector());
	s->setVolumes(eslVolumes->getStdStringVector());
	s->setPorts(eslPorts->getStdStringVector());

	s->setBuildDockerfile(edtBuildDockerfile->text().toStdString());
	s->setContainerName(edtContainerName->text().toStdString());

	s->setBuildContext(edtBuildContext->text().toStdString());
	s->setImage(edtImage->text().toStdString());

	validate();
}

bool ServiceConfigView::validate()
{
	BaseConfigView::validate();

	try {
		config->validate();
		return true;
	} catch(ServiceConfig::EmptyImageOrBuildException) {
		showErrors("Image o BuildContext devono essere non vuoti.");
		return false;
	}
}

void ServiceConfigView::setupEditWidget()
{
	edtImage = new QLineEdit();
	edtBuildContext = new QLineEdit();
	edtBuildDockerfile = new QLineEdit();
	edtBuildDockerfile->setCompleter(completers->getDockerfiles());
	edtContainerName = new QLineEdit();

	eslEnvironment = new EditableStringList();
	eslPorts = new EditableStringList();
	eslLinks = new EditableStringList();
	eslLinks->setCompleter(completers->getServices());
	eslNetworks = new EditableStringList();
	eslNetworks->setCompleter(completers->getNetworks());
	eslVolumes = new EditableStringList();
	eslVolumes->setCompleter(completers->getVolumes());

	QFormLayout* layForm = new QFormLayout();
	// let field widget to be of any size
	layForm->setSizeConstraint(QLayout::SetMinimumSize);
	layForm->addRow("build:context", edtBuildContext);
	layForm->addRow("build:dockerfile", edtBuildDockerfile);
	layForm->addRow("container", edtContainerName);
	layForm->addRow("image", edtImage);
	layForm->addRow("environment", eslEnvironment);
	layForm->addRow("links", eslLinks);
	layForm->addRow("networks", eslNetworks);
	layForm->addRow("ports", eslPorts);
	layForm->addRow("volumes", eslVolumes);

	QWidget* wdgEditContent = new QWidget();
	wdgEditContent->setLayout(layForm);

	QScrollArea* slaEdit = new QScrollArea();
	slaEdit->setWidget(wdgEditContent);
	// prevents the widget from collapsing to the minimum size
	slaEdit->setWidgetResizable(true);
	slaEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	wdgEdit = slaEdit;
}

void ServiceConfigView::setupPermissions()
{
	BaseConfigView::setupPermissions(userLogged->canEditService());

	eslNetworks->setEnabled(userLogged->canEditNetwork());
	eslVolumes->setEnabled(userLogged->canEditVolume());
}
