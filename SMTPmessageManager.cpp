#include "SMTPmessageManager.h"

#include <QDebug>

SMTPmessageManager::SMTPmessageManager(QSharedPointer<QSettings> settings) : _settings(settings)
{
	_smtp = new SmtpClient(_settings->value("SMTP/server").toString(), _settings->value("SMTP/port").toInt());
}

SMTPmessageManager::~SMTPmessageManager()
{
	delete _smtp;
}

void SMTPmessageManager::addEventToLog(const QString& eventText)
{
	_eventLog.push_back(eventText);
}

void SMTPmessageManager::sendMessage(const QStringList& messageText)
{
	_smtp->setHost(_settings->value("SMTP/server").toString());
	_smtp->setPort(_settings->value("SMTP/port").toInt());

	/*if (_settings->value("SMTP/ssl").toInt()) _smtp->setConnectionType(SmtpClient::SslConnection);
	else _smtp->setConnectionType(SmtpClient::TcpConnection);*/
	_smtp->setConnectionType(SmtpClient::SslConnection);

	_smtp->setUser(_settings->value("SMTP/user").toString());
	_smtp->setPassword(_settings->value("SMTP/password").toString());

	MimeMessage message;
	message.setSender(new EmailAddress(_settings->value("SMTP/user").toString(), ""));
	message.addRecipient(new EmailAddress(_settings->value("SMTP/recipient").toString(), "Recipient's Name"));
	message.setSubject("сообщение KRAKENONE");

	QString messageTextLine;
	for (auto& line : messageText)
	{
		messageTextLine += line;
		messageTextLine += "\n";
	}

	MimeText text;
	text.setText(messageTextLine);
	message.addPart(&text);
	_smtp->connectToHost();
	_smtp->login();
	_smtp->sendMail(message);
	_smtp->quit();
}

void SMTPmessageManager::sendEventLog()
{
	if (_eventLog.isEmpty())
	{
		return;
	}

	sendMessage(_eventLog);
	_eventLog.clear();
}
