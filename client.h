#ifndef THINCASTCLIENT_H
#define THINCASTCLIENT_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QQuickItem>
#include <QString>

class Client : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
	explicit Client(QObject *parent = 0);
	~Client();

	Q_INVOKABLE void startVM(const QString &uuid);
	Q_INVOKABLE void setQmlItem(QObject* item);

	QString name() const;
	void setName(const QString &name);

signals:
	Q_REVISION(1) void signalStartVM(const QString &uuid);
	Q_REVISION(1) void nameChanged();

public slots:
	void slotStartVM(const QString &uuid);

private slots:
	void pslotNameChanged();
	void pslotStartVM(const QString &uuid);

private:
	QObject *m_Item;
	QString m_Name;
};

#endif // THINCASTCLIENT_H
