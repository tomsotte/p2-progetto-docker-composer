#ifndef COMPOSECONFIGVIEW_H
#define COMPOSECONFIGVIEW_H

#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QList>
#include <QComboBox>
#include <QTreeWidgetItem>

#include "baseconfigview.h"
#include "../../model/compose/baseconfig.h"
#include "../../model/compose/composeconfig.h"
#include "../../model/compose/dockerparts.h"
#include "../../model/user/user.h"

class ComposeConfigView : public BaseConfigView
{
	Q_OBJECT
public:
	ComposeConfigView(ComposeConfig* c, User* ul, QWidget *parent = nullptr);

	virtual void reload();
	virtual void save();

protected:
	virtual void setupHeaderWidget();
	virtual void setupEditWidget();

	virtual void setupPermissions();

private:
	ComposeConfig* compose; // used for quick reference, instead of casting everytime

	QVBoxLayout* layEdit;

    QComboBox* cmbVersion;
	QTreeWidget* composeTree;
	QTreeWidgetItem* servicesTree;
	QTreeWidgetItem* networksTree;
	QTreeWidgetItem* volumesTree;
	QTreeWidgetItem* dockerfilesTree;

	QPushButton* btnCreate;

	void buildComposeTree();
	QTreeWidgetItem* buildPartsTree(QTreeWidget* tree,
									const std::string& typeFilter) const;

signals:
	void selectConfig(BaseConfig*);
	void createConfig(BaseConfig*);

public slots:
	void onCreate();
	void onClickItem(QTreeWidgetItem* item);
};

#endif // COMPOSECONFIGVIEW_H
