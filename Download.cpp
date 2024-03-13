#include "Download.h"
#include <QImage>
#include <QNetworkReply>
#include <QEventLoop>

Download::Download(QObject *parent)
    : QObject{parent}
{
}

QString Download::download(const QString &url, const QString &path, const QString &format)
{
    if (m_pReply) { //не делается ли уже запрос (если не nullptr)
        m_pReply->abort(); //прервать запрос
        m_pReply->deleteLater(); //освободить память
        m_pReply = nullptr;
    }
    m_pReply = m_manager.get(QNetworkRequest(url));

    QEventLoop loop;
    connect(m_pReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (m_pReply->error() == QNetworkReply::NoError) {
        if(format == "img") img(url, path, m_pReply->readAll());

    }
    else if (m_pReply->error() != QNetworkReply::OperationCanceledError) {
        return "Error: " + m_pReply->errorString();
    }

    m_pReply->deleteLater();
    m_pReply = nullptr;
    return {};
}

void Download::img(const QString &url, const QString &path, const QByteArray &data)
{
    QImage img;
    QString nameImg = '/' + url.section('/', -1);
    img.loadFromData(data);
    img.save(path + nameImg);
    //qDebug() << "Path: " << path + nameImg;
}
