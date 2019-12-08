#include "EncounterManager.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	EncounterManager w;
	w.show();
	return a.exec();
}
