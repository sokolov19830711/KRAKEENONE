#pragma once

#include <QSettings>
#include "../SmtpClient-for-Qt/src/SmtpMime"

class SMTPmessageManager : public QObject
{
	Q_OBJECT

public:

	SMTPmessageManager(QSharedPointer<QSettings> settings);
	virtual ~SMTPmessageManager();

	void addEventToLog(const QString& eventText);
	void sendMessage(const QStringList& text);

signals:

	void needToShowEvent(const QString& eventText);

public slots:

	void sendEventLog();

private:

	void saveEventLogFile();

	QSharedPointer<QSettings> _settings;
	SmtpClient* _smtp = nullptr;
	QStringList _eventLog;

};
