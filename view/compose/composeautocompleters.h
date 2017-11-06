#ifndef COMPOSEAUTOCOMPLETERS_H
#define COMPOSEAUTOCOMPLETERS_H

#include <QObject>
#include <QCompleter>
#include <QStringList>
#include <QStringListModel>

#include "../../model/compose/composeconfig.h"

class ComposeAutocompleters : public QObject
{
	Q_OBJECT
public:
	explicit ComposeAutocompleters(QObject *parent = nullptr);

	QCompleter* getServices() const;
	QCompleter* getVolumes() const;
	QCompleter* getNetworks() const;
	QCompleter* getDockerfiles() const;

    void updateCompleters(ComposeConfig* c);

private:
	QCompleter* services;
	QCompleter* volumes;
	QCompleter* networks;
	QCompleter* dockerfiles;

	QStringListModel* servicesModel;
	QStringListModel* networksModel;
	QStringListModel* volumesModel;
	QStringListModel* dockerfilesModel;

	QStringList extractList(DockerParts cpl) const;

signals:

public slots:
	void onUpdateComposeConfig(ComposeConfig* c);
};

#endif // COMPOSEAUTOCOMPLETERS_H
