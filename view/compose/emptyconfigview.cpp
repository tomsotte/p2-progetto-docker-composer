#include "emptyconfigview.h"

#include <QLabel>
#include <QVBoxLayout>

EmptyConfigView::EmptyConfigView(QWidget *parent) : BaseConfigView(nullptr, nullptr, parent)
{
	setupEditWidget();

	setupMainLayout();
	setLayout(layMain);
}

void EmptyConfigView::setupMainLayout()
{
	QVBoxLayout* layEmpty = new QVBoxLayout();
	layEmpty->addWidget(wdgEdit, 0, Qt::AlignCenter);

	layMain = layEmpty;
}

void EmptyConfigView::setupEditWidget()
{
	QLabel* lblEmpty = new QLabel("Nessuna configurazione aperta.");
	lblEmpty->setStyleSheet("color: gray;");

	wdgEdit = lblEmpty;
}
