#include "dockerfileconfigview.h"

DockerfileConfigView::DockerfileConfigView(DockerfileConfig* c, User* ul, QWidget *parent)
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

void DockerfileConfigView::reload()
{
	BaseConfigView::reload();

	DockerfileConfig* d = dynamic_cast<DockerfileConfig*>(config);
	txtText->setText(QString::fromStdString(d->getText()));
}

void DockerfileConfigView::save()
{
	BaseConfigView::save();

	DockerfileConfig* d = dynamic_cast<DockerfileConfig*>(config);
	d->setText(txtText->toPlainText().toStdString());

	validate();
}

bool DockerfileConfigView::validate()
{
	BaseConfigView::validate();

	try {
		config->validate();
	} catch(DockerfileConfig::SyntaxErrorLineException e) {
		showErrors(QString("Errore di sintassi alla linea %1.\n"
				   "Sintassi (per linea): 'KEYWORD argomenti' o '# commento' o vuota").arg(e.line));
	}

	return true;
}

void DockerfileConfigView::setupEditWidget()
{
	QFont font("Monospace");
	font.setStyleHint(QFont::TypeWriter);

	// Settings below are used for a 4-spaces tab width
	font.setFixedPitch(true);
	font.setPointSize(9);
	QFontMetrics metrics(font);

	txtText = new QTextEdit();
	txtText->setFont(font);
	txtText->setWordWrapMode(QTextOption::NoWrap);
	txtText->setTabStopWidth(4 * metrics.width(' '));

	wdgEdit = txtText;
}

void DockerfileConfigView::setupPermissions()
{
	BaseConfigView::setupPermissions(userLogged->canEditService());
}
