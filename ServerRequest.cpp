#include "ServerRequest.h"
#include <QEventLoop>
#include <QNetworkReply>

ServerRequest::ServerRequest(QObject *parent)
    : QObject{parent}
{
}

void ServerRequest::request(const QString &url)
{
    if(url.isEmpty()) return;
    m_url = url;
    if (m_pReply) { //не делается ли уже запрос (если не nullptr)
        m_pReply->abort(); //прервать запрос
        m_pReply->deleteLater(); //освободить память
        m_pReply = nullptr;
    }
    m_pReply = m_manager.get(QNetworkRequest(QUrl(url)));

    QEventLoop loop;
    setYes( true );
    connect(m_pReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    setYes( false );

    if (m_pReply->error() == QNetworkReply::NoError) { //если ошибок нет
        emit SendAReply(m_pReply->readAll());
    }
    else if (m_pReply->error() != QNetworkReply::OperationCanceledError) {
        qCritical() << "Error:" << m_pReply->errorString();
    }

    m_pReply->deleteLater();
    m_pReply = nullptr;
}

QString ServerRequest::url() const
{
    return m_url;
}

bool ServerRequest::yes() const
{
    return m_yes;
}

void ServerRequest::setYes(bool newYes)
{
    if (m_yes == newYes) return;
    m_yes = newYes;
    emit yesChanged();
}


