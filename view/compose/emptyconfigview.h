#ifndef CONFIGPARTVIEW_H
#define CONFIGPARTVIEW_H

#include "baseconfigview.h"


class EmptyConfigView : public BaseConfigView
{
	Q_OBJECT
public:
	explicit EmptyConfigView(QWidget *parent = nullptr);

protected:
	virtual void setupEditWidget();

	virtual void setupMainLayout();
};

#endif // CONFIGPARTVIEW_H
