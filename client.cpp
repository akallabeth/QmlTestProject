#include "client.h"
#include <QDebug>

Client::Client(QObject *parent) : QObject(parent)
{
	connect(this, &Client::nameChanged,
			this, &Client::pslotNameChanged);
}

Client::~Client()
{

}

void Client::slotStartVM(const QString &uuid) {
	qDebug() << uuid;
}

void Client::pslotStartVM(const QString &uuid) {
	qDebug() << uuid;
}

void Client::startVM(const QString &uuid) {
	qDebug() << uuid;
}

void Client::setQmlItem(QObject *item) {
	if (item) {
		m_Item = item;
		connect(m_Item, SIGNAL(signalStartVM(QString)),
				this, SLOT(pslotStartVM(QString)));
	}
}

void Client::setName(const QString &name) {
	this->m_Name = name;
	emit nameChanged();
}

QString Client::name() const {
	return m_Name;
}

void Client::pslotNameChanged() {
	qDebug() << "Name changed " << m_Name;
}
