#include "composeconfigview.h"

#include "../../model/compose/dockerfileconfig.h"
#include "../../model/compose/serviceconfig.h"
#include "../../model/compose/networkconfig.h"
#include "../../model/compose/volumeconfig.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QString>
#include <QStringList>
#include <QGroupBox>
#include <string>

ComposeConfigView::ComposeConfigView(ComposeConfig* c, User* ul, QWidget *parent)
	: BaseConfigView(c, ul, parent), compose(c)
{
	setupInfoWidget();
	setupHeaderWidget();
	setupOutputWidget();
	setupEditWidget();

	setupMainLayout();
	setLayout(layMain);

	reload();
}

void ComposeConfigView::reload()
{
	BaseConfigView::reload();
    cmbVersion->setCurrentText(QString::fromStdString(compose->getVersion()));
	buildComposeTree();
}

void ComposeConfigView::save()
{
	BaseConfigView::save();
    compose->setVersion(cmbVersion->currentText().toStdString());
	// add/remove configparts
}

void ComposeConfigView::setupHeaderWidget()
{
	BaseConfigView::setupHeaderWidget();

	// The info in composeconfig aren't relevant, so there's no point to show them
	wdgInfo->hide();

	// ComposeConfig can't be removed or cloned
	btnRemove->hide();
	btnClone->hide();
}

void ComposeConfigView::setupEditWidget()
{
    cmbVersion = new QComboBox();
	for (const auto& ver : ComposeConfig::versions) {
		cmbVersion->addItem(QString::fromStdString(ver));
	}

	QFormLayout* layForm = new QFormLayout();
    layForm->addRow("Compose version", cmbVersion);

	composeTree = new QTreeWidget();
	composeTree->setColumnCount(1);
	composeTree->setHeaderLabels(QStringList({"Nome"}));
	connect(composeTree, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
			this, SLOT(onClickItem(QTreeWidgetItem*)));

	btnCreate = new QPushButton("Aggiungi");
	btnCreate->setIcon(QIcon(QPixmap(":/res/addcircle.svg")));
	connect(btnCreate, SIGNAL(clicked(bool)), this, SLOT(onCreate()));

	layEdit = new QVBoxLayout();
	layEdit->setMargin(0);
	layEdit->addLayout(layForm);
	layEdit->addWidget(composeTree, 1);
	layEdit->addWidget(btnCreate);

	wdgEdit = new QWidget();
	wdgEdit->setLayout(layEdit);
}

void ComposeConfigView::setupPermissions()
{
	// empty implementation; everyone can work on composeconfig
}

QTreeWidgetItem* ComposeConfigView::buildPartsTree(QTreeWidget* tree,
											 const std::string& typeFilter) const
{
	const DockerParts typeParts = compose->getParts().filterByModelName(typeFilter);
	QList<QTreeWidgetItem*> subTreeList;
	QTreeWidgetItem* subTreeItem;

	for (const auto c : typeParts) {
		subTreeItem = new QTreeWidgetItem();
		subTreeItem->setText(0, QString::fromStdString(c->getName()));
		subTreeList.append(subTreeItem);
	}

    QTreeWidgetItem* subTreeHead = new QTreeWidgetItem(tree, QStringList());
    subTreeHead->addChildren(subTreeList);

	// ex. "services (n)"
    subTreeHead->setText(0, QString::fromStdString(typeFilter + "s (%1)")
                         .arg(subTreeList.count()));

	return subTreeHead;
}

void ComposeConfigView::buildComposeTree()
{
	composeTree->clear();

	// creates subtrees
	servicesTree = buildPartsTree(composeTree, ServiceConfig::modelName);
	networksTree = buildPartsTree(composeTree, NetworkConfig::modelName);
	volumesTree = buildPartsTree(composeTree, VolumeConfig::modelName);
	dockerfilesTree = buildPartsTree(composeTree, DockerfileConfig::modelName);

	// add trees root to the topLevel list
	QList<QTreeWidgetItem*> topLevel;
	topLevel.append(servicesTree);
	topLevel.append(networksTree);
	topLevel.append(volumesTree);
	topLevel.append(dockerfilesTree);

	// expand all
	composeTree->expandItem(servicesTree);
	composeTree->expandItem(networksTree);
	composeTree->expandItem(volumesTree);
	composeTree->expandItem(dockerfilesTree);

	composeTree->insertTopLevelItems(0, topLevel);
}

void ComposeConfigView::onClickItem(QTreeWidgetItem* item)
{
	const std::string& name = item->text(0).toStdString();

	// Header labels can be clicked too, this ensure only a config item can be selected
	if (BaseConfig* c = compose->getParts().findConfigByName(name)) {
		emit selectConfig(c);
	}
}

void ComposeConfigView::onCreate()
{
	emit createConfig(nullptr);
}
