#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "client.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setOrganizationName("ACME Inc");
	app.setOrganizationDomain("acme.example.com");
	app.setApplicationName("ACME Client");

	QQmlApplicationEngine engine;

	// Register signals / slots from QML in C++
	Client client;
	engine.rootContext()->setContextProperty("Client", &client);
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	return app.exec();
}
