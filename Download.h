#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QNetworkAccessManager>
#include <QObject>

class Download : public QObject
{
    Q_OBJECT
public:
    explicit Download(QObject *parent = nullptr);

    QString download(const QString &url, const QString &path, const QString &format = "img");

private:
    void img(const QString &url, const QString &path, const QByteArray &data);
signals:

private:
    QNetworkAccessManager m_manager;
    QNetworkReply *m_pReply = nullptr;
};

#endif // DOWNLOAD_H
