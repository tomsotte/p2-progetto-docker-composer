#include "composeautocompleters.h"

ComposeAutocompleters::ComposeAutocompleters(QObject *parent) : QObject(parent)
{
    servicesModel = new QStringListModel(this);
    networksModel = new QStringListModel(this);
    volumesModel = new QStringListModel(this);
	dockerfilesModel = new QStringListModel(this);

    services = new QCompleter(servicesModel, this);
    networks = new QCompleter(networksModel, this);
    volumes = new QCompleter(volumesModel, this);
	dockerfiles = new QCompleter(dockerfilesModel, this);
}

QCompleter* ComposeAutocompleters::getServices() const
{
	return services;
}

QCompleter* ComposeAutocompleters::getVolumes() const
{
	return volumes;
}

QCompleter* ComposeAutocompleters::getNetworks() const
{
	return networks;
}

QCompleter*ComposeAutocompleters::getDockerfiles() const
{
	return dockerfiles;
}

void ComposeAutocompleters::updateCompleters(ComposeConfig *c)
{
	DockerParts& parts = c->getParts();
	DockerParts s = parts.filterByModelName(ServiceConfig::modelName);
	DockerParts n = parts.filterByModelName(NetworkConfig::modelName);
	DockerParts v = parts.filterByModelName(VolumeConfig::modelName);
	DockerParts d = parts.filterByModelName(DockerfileConfig::modelName);

    servicesModel->setStringList(extractList(s));
    networksModel->setStringList(extractList(n));
    volumesModel->setStringList(extractList(v));
	dockerfilesModel->setStringList(extractList(d));
}

QStringList ComposeAutocompleters::extractList(DockerParts cpl) const
{
	QStringList list;

	for (auto config : cpl) list << QString::fromStdString(config->getName());

	return list;
}

void ComposeAutocompleters::onUpdateComposeConfig(ComposeConfig* c)
{
    updateCompleters(c);
}

