#ifndef SERVERREQUEST_H
#define SERVERREQUEST_H

#include <QObject>
#include <QNetworkAccessManager>

class ServerRequest : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool yes READ yes NOTIFY yesChanged FINAL)

public:
    explicit ServerRequest(QObject *parent = nullptr);

    void request(const QString &url);
    QString url() const;

    bool yes() const;
    void setYes(bool newYes);

signals:
    void SendAReply(const QByteArray&);

    void yesChanged();

private:
    QNetworkAccessManager m_manager;
    QNetworkReply *m_pReply = nullptr;
    QString m_url;
    bool m_yes { false };
};

#endif // SERVERREQUEST_H
