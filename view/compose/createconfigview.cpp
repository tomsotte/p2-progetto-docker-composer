#include "createconfigview.h"

#include <QFormLayout>
#include <QGroupBox>

#include "../../model/compose/dockerfileconfig.h"
#include "../../model/compose/serviceconfig.h"
#include "../../model/compose/networkconfig.h"
#include "../../model/compose/volumeconfig.h"

CreateConfigView::CreateConfigView(ComposeConfig* cc, User* u, BaseConfig* cf,
								   QWidget* parent)
	: QDialog(parent), compose(cc), user(u), cloneFrom(cf)
{
	setupTypesComboBox();

	setupMainLayout();
	setLayout(layMain);

	// auto delete the window on close
	if (cf) {
		setWindowTitle("Clona configurazione '"
					   + QString::fromStdString(cf->getName()) + "'");
	} else {
		setWindowTitle("Crea nuova configurazione");
	}
	setFixedSize(300, 120);

	setAttribute(Qt::WA_DeleteOnClose);
}

void CreateConfigView::setupMainLayout()
{
	edtName = new QLineEdit();
	if (cloneFrom) edtName->setText(QString::fromStdString(cloneFrom->getName()));
	edtName->setFocus();
	connect(edtName, SIGNAL(returnPressed()), SLOT(onCreate()));

	edtAuthor = new QLineEdit(QString::fromStdString(user->getName()));
	edtAuthor->setReadOnly(true);
	edtAuthor->setFrame(false);

	QFormLayout* layInfo = new QFormLayout();
	layInfo->addRow("Nome", edtName);
	layInfo->addRow("Autore", edtAuthor);

	lblFeedback = new QLabel();
	lblFeedback->setObjectName("LabelFeedback");

	btnSave = new QPushButton("Crea");
	btnSave->setFocus();
	connect(btnSave, SIGNAL(clicked(bool)), this, SLOT(onCreate()));

	btnCancel = new QPushButton("Annulla");
	connect(btnCancel, SIGNAL(clicked(bool)), this, SLOT(close()));

	QHBoxLayout* layBot = new QHBoxLayout();
	layBot->addWidget(lblFeedback);
	layBot->addStretch(1);
	layBot->addWidget(btnCancel);
	layBot->addWidget(btnSave);

	layMain = new QVBoxLayout();
	layMain->addWidget(cmbPartTypes);
	layMain->addLayout(layInfo);
	layMain->addLayout(layBot);
	layMain->addStretch(1);
}

void CreateConfigView::setupTypesComboBox()
{
	cmbPartTypes = new QComboBox();

	if (cloneFrom) {
		cmbPartTypes->addItem(QString::fromStdString(cloneFrom->getModelName()));
		cmbPartTypes->setDisabled(true);
		return;
	}

	if (user->canEditService()) {
		cmbPartTypes->addItem(QString::fromStdString(DockerfileConfig::modelName));
		cmbPartTypes->addItem(QString::fromStdString(ServiceConfig::modelName));
	}
	if (user->canEditNetwork())
		cmbPartTypes->addItem(QString::fromStdString(NetworkConfig::modelName));
	if (user->canEditVolume())
		cmbPartTypes->addItem(QString::fromStdString(VolumeConfig::modelName));
}

void CreateConfigView::onCreate()
{
	lblFeedback->setText("");
	const std::string name = edtName->text().toStdString();
	const std::string type = cmbPartTypes->currentText().toStdString();

	if (name.empty()) {
		lblFeedback->setText("Nome vuoto.");
		return;
	}

	if (compose->getParts().findConfigByName(name)) {
		lblFeedback->setText("Nome già in uso.");
		return;
	}

	BaseConfig* c {nullptr};

	if (cloneFrom) {
		c = cloneFrom->clone();
		c->setName(name);
		c->setAuthor(user->getName());
	} else {
		c = DockerParts::createDockerPart(type, name, user->getName());
	}

	compose->getParts().add(c);

	emit addedConfig(c);
	close();
}
