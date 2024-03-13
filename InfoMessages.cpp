#include "InfoMessages.h"

InfoMessages::InfoMessages(QObject *parent)
    : QObject{parent}
{
}

QString InfoMessages::message() const
{
    return m_message;
}

void InfoMessages::setMessage(const QString &newMessage)
{
    if(newMessage.isEmpty()) return;
    if(m_message == newMessage) {
        emit messageChanged(); return;
    }
    m_message = newMessage;
    emit messageChanged();
}
