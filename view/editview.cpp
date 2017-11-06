#include "editview.h"

#include <QInputDialog>

#include "compose/emptyconfigview.h"
#include "compose/volumeconfigview.h"
#include "compose/serviceconfigview.h"
#include "compose/networkconfigview.h"
#include "compose/dockerfileconfigview.h"

EditView::EditView(Core* c, QWidget* parent) : QSplitter(parent), core(c)
{
	setupComposeView();
	setupRightView();

	setOrientation(Qt::Horizontal);
	addWidget(composeView);
	addWidget(rightView);
	setChildrenCollapsible(false);
	// equally distribute sizes in 50/50
	setSizes(QList<int>({INT_MAX, INT_MAX}));
}

void EditView::setupComposeView()
{
	completer = new ComposeAutocompleters(this);
	completer->updateCompleters(core->getCompose());
	connect(this, SIGNAL(updatedCompose(ComposeConfig*)),
			completer, SLOT(onUpdateComposeConfig(ComposeConfig*)));

	composeView = new ComposeConfigView(core->getCompose(), core->getLoggedUser());
	connect(composeView, SIGNAL(sendStatusBarMsg(QString)),
			this, SLOT(onSendStatusBarMsg(QString)));
	connect(composeView, SIGNAL(selectConfig(BaseConfig*)),
			this, SLOT(onSelectConfig(BaseConfig*)));
	connect(composeView, SIGNAL(savedConfig(BaseConfig*)),
			this, SLOT(onSavedConfig(BaseConfig*)));
	connect(composeView, SIGNAL(createConfig(BaseConfig*)),
			this, SLOT(onCreateConfig(BaseConfig*)));
}

void EditView::setupRightView()
{
	rightView = new EmptyConfigView(this);
}

void EditView::swapRightView(QWidget* to)
{
	auto s = sizes(); // used to preserve sizes
	int pos = indexOf(rightView);

	// save the previous right view
	QWidget* prevRight = widget(pos);
	// detaches from the view
	prevRight->setParent(nullptr);
	// set to be deleted
	prevRight->deleteLater();

	insertWidget(pos, to);
	rightView = to;
	setSizes(s);
}

BaseConfigView* EditView::createConfigView(BaseConfig* c)
{
	// TODO create correct view based on differnt type
	BaseConfigView* view;

	if (auto svc = dynamic_cast<ServiceConfig*>(c)) {
		view = new ServiceConfigView(svc, core->getLoggedUser(), completer);
	} else if (auto vol = dynamic_cast<VolumeConfig*>(c)) {
		view = new VolumeConfigView(vol, core->getLoggedUser());
	} else if (auto net = dynamic_cast<NetworkConfig*>(c)) {
		view = new NetworkConfigView(net, core->getLoggedUser());
	} else if (auto dok = dynamic_cast<DockerfileConfig*>(c)) {
		view = new DockerfileConfigView(dok, core->getLoggedUser());
	} else {
		view = new EmptyConfigView();
		return view; // there's no point in connecting an empty config view
	}

	connect(view, SIGNAL(sendStatusBarMsg(QString)),
			this, SLOT(onSendStatusBarMsg(QString)));
	connect(view, SIGNAL(savedConfig(BaseConfig*)),
			this, SLOT(onSavedConfig(BaseConfig*)));
	connect(view, SIGNAL(removeConfig(BaseConfig*)),
			this, SLOT(onRemoveConfig(BaseConfig*)));
	connect(view, SIGNAL(cloneConfig(BaseConfig*)),
			this, SLOT(onCreateConfig(BaseConfig*)));

	return view;
}

void EditView::onSendStatusBarMsg(const QString& msg)
{
	// pass-through
	emit sendStatusBarMsg(msg);
}

void EditView::onSelectConfig(BaseConfig* c)
{
	if (auto bcv = dynamic_cast<BaseConfigView*>(rightView)) {
		// if currently viewed config is the same, don't swap
		if (bcv->getConfig() == c) return;
	}

	// select correct config viewer based on config type, then swaps it to the right
	swapRightView(createConfigView(c));
}

void EditView::onSavedConfig(BaseConfig* c)
{
	// save compose config on disk
	core->saveCompose();

	emit sendStatusBarMsg("Configurazione '" + QString::fromStdString(c->getName()) +
						  "' salvata.");

	composeView->reload();
}

void EditView::onAddedConfig(BaseConfig* c)
{
	emit sendStatusBarMsg("Creata una nuova configurazione " +
						  QString::fromStdString(c->getModelName()) + ": '" +
						  QString::fromStdString(c->getName()) +
						  "'. Compose è stato salvato.");

	core->saveCompose();

	emit updatedCompose(core->getCompose());
	composeView->reload();

	onSelectConfig(c);
}

void EditView::onRemoveConfig(BaseConfig* c)
{
	emit sendStatusBarMsg("Rimossa la configurazione '" + QString::fromStdString(c->getName()) +
						  "'. Compose è stato salvato.");

	core->getCompose()->getParts().remove(c);

	core->saveCompose();

	emit updatedCompose(core->getCompose());
	composeView->reload();

	swapRightView(new EmptyConfigView());
}

void EditView::onCreateConfig(BaseConfig* cloneFrom)
{
	CreateConfigView* view = new CreateConfigView(core->getCompose(),
												  core->getLoggedUser(),
												  cloneFrom,
												  this);
	connect(view, SIGNAL(addedConfig(BaseConfig*)),
			this, SLOT(onAddedConfig(BaseConfig*)));

	view->exec();
}
