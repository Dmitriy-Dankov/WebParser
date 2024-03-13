#ifndef DATASET_H
#define DATASET_H

#include <QObject>

class Dataset : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString data READ data FINAL)
    Q_PROPERTY(QString displayData READ displayData NOTIFY displayDataChanged FINAL)
    Q_PROPERTY(QString displayImage READ displayImage NOTIFY displayImageChanged FINAL)
    Q_PROPERTY(QString displayText READ displayText NOTIFY displayTextChanged FINAL)
    Q_PROPERTY(QStringList srcList READ srcList NOTIFY srcListChanged FINAL)

public:
    explicit Dataset(QObject *parent = nullptr);

    QString data() const;
    QString displayData() const;

    QString displayImage() const;
    void setDisplayImage(const QString &newDisplayImage);

    QString displayText() const;


    QStringList srcList() const;
    void setSrcList(const QStringList&);

    void setData(const QString &newData);

public slots:
    void dataOutput();
    void setDisplayData(const QString &newDisplayData);
    void setDisplayText(const QString &newDisplayText);

signals:
    void displayDataChanged();
    void displayImageChanged();
    void displayTextChanged();
    void srcListChanged();

private:
    QString m_data;
    QString m_displayData;
    QString m_displayImage;
    QString m_displayText;
    QStringList m_srcList;
};

#endif // DATASET_H
