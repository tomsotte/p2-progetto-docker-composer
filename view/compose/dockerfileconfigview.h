#ifndef DOCKERFILECONFIGVIEW_H
#define DOCKERFILECONFIGVIEW_H

#include <QTextEdit>

#include "baseconfigview.h"
#include "../../model/compose/dockerfileconfig.h"

class DockerfileConfigView : public BaseConfigView
{
	Q_OBJECT
public:
	DockerfileConfigView(DockerfileConfig* c, User* ul, QWidget *parent = nullptr);

	virtual void reload();
	virtual void save();

	virtual bool validate();

protected:
	virtual void setupEditWidget();
	virtual void setupPermissions();

private:
	QTextEdit* txtText;

signals:

public slots:
};

#endif // DOCKERFILECONFIGVIEW_H
