#include <QApplication>

#include <QStyleFactory>

#include "view/mainwindow.h"
#include "model/core.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setStyle(QStyleFactory::create("fusion"));

	Core* c = new Core();
	c->loadCompose();
	c->loadUsers();

	MainWindow* w = new MainWindow(c);
	w->show();

	return a.exec();
}


