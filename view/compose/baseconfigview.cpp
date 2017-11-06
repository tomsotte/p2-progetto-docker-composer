#include "baseconfigview.h"

#include <QApplication>
#include <QClipboard>

#include <QMessageBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QIcon>
#include <QPixmap>

BaseConfigView::BaseConfigView(BaseConfig* c, User* ul, QWidget *parent)
	: QWidget(parent), config(c), userLogged(ul)
{
    // empty; this way a derived class has total control over the GUI setup

	// Use example:
//	setupInfoWidget();
//	setupHeaderWidget();
//	setupOutputWidget();
//	setupEditWidget();

	// has to go latest as it needs all the above to be called before
	// to initiliaze the various part of the gui
//	setupMainLayout();
//	setupPermissions();
//	setLayout(layMain);

//	reload(); // load config data into the view for the 1st time
}

void BaseConfigView::reload()
{
	edtConfigName->setText(QString::fromStdString(config->getName()));
	edtConfigAuthor->setText(QString::fromStdString(config->getAuthor()));
	reloadOutput();
}

void BaseConfigView::reloadOutput()
{
	const QString& text = QString::fromStdString(config->getText());
	txtOutput->setText(text);

	// count new lines + 1 (the line itself) or 0 (empty)
	int count = (text.length()) ? (text.count('\n') + 1) : 0;
	lblLinesCount->setText(QString("Linee: %1").arg(count));
}

bool BaseConfigView::validate()
{
	resetErrors();
	// to be further implemented in derived classes

	return true;
}

void BaseConfigView::resetErrors()
{
	lblErrors->hide();
	lblErrors->setText("");
}

void BaseConfigView::showErrors(const QString& msg)
{
	lblErrors->show();
	lblErrors->setText(msg);
}

void BaseConfigView::save()
{
//	if (edtConfigName->isModified()) emit changeName(edtConfigName->text());
}

BaseConfig* BaseConfigView::getConfig() const
{
	return config;
}

void BaseConfigView::setupHeaderWidget()
{
	QString type = QString::fromStdString(config->getModelName()).toLower();
	type.replace(0, 1, type.at(0).toUpper()); // uppercase first letter
	lblConfigType = new QLabel(type);
	lblConfigType->setFont(QFont("sans", 11, QFont::Bold));

	lblErrors = new QLabel();
	lblErrors->hide();
	lblErrors->setWordWrap(true);
	lblErrors->setObjectName("LabelFeedback");

	btnSave = new QPushButton("Salva");
	btnSave->setIcon(QIcon(QPixmap(":/res/save.svg")));
	connect(btnSave, SIGNAL(clicked(bool)), this, SLOT(onSaveConfig()));

	btnReload = new QPushButton("Annulla");
	btnReload->setToolTip("Annulla tutte le modifiche non salvate "
						  "e ricarica la config.");
	btnReload->setIcon(QIcon(QPixmap(":/res/undo.svg")));
	connect(btnReload, SIGNAL(clicked(bool)), this, SLOT(onReloadConfig()));

	btnRemove = new QPushButton("Rimuovi");
	btnRemove->setToolTip("Rimuove definitivamente la configurazione. "
						  "È richiesta la conferma");
	btnRemove->setIcon(QIcon(QPixmap(":/res/trashbin.svg")));
	connect(btnRemove, SIGNAL(clicked(bool)), this, SLOT(onRemoveConfig()));

	btnClone = new QPushButton("Clona");
	btnClone->setIcon(QIcon(QPixmap(":/res/clone.svg")));
	connect(btnClone, SIGNAL(clicked(bool)), this, SLOT(onCloneConfig()));

	QHBoxLayout* layTop = new QHBoxLayout();
	layTop->setMargin(0);
	layTop->addWidget(lblConfigType);
	layTop->addStretch(1);
	layTop->addWidget(btnRemove);
	layTop->addWidget(btnReload);
	layTop->addWidget(btnClone);
	layTop->addWidget(btnSave);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->setMargin(0);
	layout->addLayout(layTop);
	layout->addWidget(lblErrors);

	wdgHeader = new QWidget();
	wdgHeader->setLayout(layout);
}

void BaseConfigView::setupInfoWidget()
{
	edtConfigName = new QLineEdit();
	edtConfigName->setReadOnly(true);
	edtConfigName->setFrame(false);
	edtConfigAuthor = new QLineEdit();
	edtConfigAuthor->setReadOnly(true);
	edtConfigAuthor->setFrame(false);

	QFormLayout* layInfo = new QFormLayout();
	layInfo->addRow("Nome", edtConfigName);
	layInfo->addRow("Autore", edtConfigAuthor);

	wdgInfo = new QGroupBox("Info base");
	wdgInfo->setLayout(layInfo);
}

void BaseConfigView::setupOutputWidget()
{
	QFont font("Monospace");
	font.setStyleHint(QFont::TypeWriter);

	// Settings below are used for a 4-spaces tab width
	font.setFixedPitch(true);
	font.setPointSize(10);
	QFontMetrics metrics(font);

	txtOutput = new QTextEdit("(vuoto)");
	txtOutput->setFont(font);
	txtOutput->setReadOnly(true);
	txtOutput->setTabStopWidth(4 * metrics.width(' '));
	txtOutput->hide();

    btnCopy = new QPushButton("Copia");
	btnCopy->setToolTip("Copia il testo in output sugli appunti.");
	btnCopy->setIcon(QIcon(QPixmap(":/res/copy.svg")));
	connect(btnCopy, SIGNAL(clicked(bool)), this, SLOT(copyToClipboard()));

	btnShowHide = new QPushButton("Mostra/Nascondi");
	btnShowHide->setIcon(QIcon(QPixmap(":/res/showhide.svg")));
	connect(btnShowHide, SIGNAL(clicked(bool)), this, SLOT(showHideTxtOut()));

	lblLinesCount = new QLabel();

	QHBoxLayout* layBottomLine = new QHBoxLayout();
	layBottomLine->addWidget(lblLinesCount);
	layBottomLine->addStretch(1);
	layBottomLine->addWidget(btnCopy);
	layBottomLine->addWidget(btnShowHide);

	QVBoxLayout* layTextOutput = new QVBoxLayout();
	layTextOutput->addWidget(txtOutput, 1);
	layTextOutput->addLayout(layBottomLine);

	wdgOutput = new QGroupBox("Testo");
	wdgOutput->setLayout(layTextOutput);
}

void BaseConfigView::setupMainLayout()
{
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(wdgHeader);
	layout->addWidget(wdgInfo);
	layout->addWidget(wdgEdit, 1);
	layout->addWidget(wdgOutput);

	layMain = layout;
}

void BaseConfigView::setupPermissions(bool canEditType)
{
	bool canEditOthers = config->getAuthor() == userLogged->getName()
			|| userLogged->canEditOtherUsers();
	bool canEdit = canEditType && canEditOthers;

	btnSave->setEnabled(canEdit);
	btnReload->setEnabled(canEdit);
	btnClone->setEnabled(canEditType);
	btnRemove->setEnabled(canEdit);

	wdgEdit->setEnabled(canEdit);
}

void BaseConfigView::onCloneConfig()
{
	emit cloneConfig(config);
}

void BaseConfigView::onSaveConfig()
{
	save();
	reloadOutput();
	emit savedConfig(config);
}

void BaseConfigView::onReloadConfig()
{
	reload();
	emit reloadedConfig(config);
	emit sendStatusBarMsg("Configurazione ricaricata. Sono state cancellate "
						  "le modifiche non salvate.");
}

void BaseConfigView::onRemoveConfig()
{
	QMessageBox confirmRemove;
	confirmRemove.setText("Conferma rimozione della configurazione.");
	confirmRemove.setInformativeText("Sei sicuro di volere rimuovere definitivamente"
									 "la configurazione '" +
									 QString::fromStdString(config->getName()) +
									 "'?");
	confirmRemove.setDetailedText(QString::fromStdString(config->getText()));
	confirmRemove.setIcon(QMessageBox::Warning);
	confirmRemove.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
	confirmRemove.setDefaultButton(QMessageBox::Cancel);

	if (confirmRemove.exec() == QMessageBox::Ok) emit removeConfig(config);
}

void BaseConfigView::showHideTxtOut()
{
	txtOutput->isHidden() ? txtOutput->show() : txtOutput->hide();
}

void BaseConfigView::copyToClipboard() const
{
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(txtOutput->toPlainText());
	emit sendStatusBarMsg("Testo della configurazione copiato sugli appunti.");
}
