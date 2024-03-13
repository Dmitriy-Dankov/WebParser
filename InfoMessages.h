#ifndef INFOMESSAGES_H
#define INFOMESSAGES_H

#include <QObject>

class InfoMessages : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged FINAL)
public:
    explicit InfoMessages(QObject *parent = nullptr);

    QString message() const;

public slots:
    void setMessage(const QString &newMessage);

signals:

    void messageChanged();
private:
    QString m_message;
};

#endif // INFOMESSAGES_H
