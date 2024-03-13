#ifndef DATAFORVISUALELEMENTS_H
#define DATAFORVISUALELEMENTS_H

#include <QObject>
#include "InfoMessages.h"

class DataForVisualElements : public QObject
{
    Q_OBJECT
    Q_PROPERTY(InfoMessages *pInfoMessage READ pInfoMessage NOTIFY pInfoMessageChanged FINAL)
    Q_PROPERTY(size_t progressBarVal READ progressBarVal NOTIFY progressBarValChanged FINAL)
    Q_PROPERTY(QString progressBarPercent READ progressBarPercent NOTIFY progressBarPercentChanged FINAL)
    Q_PROPERTY(bool busyIndicator READ busyIndicator NOTIFY busyIndicatorChanged FINAL)
    Q_PROPERTY(QList<size_t> searchWord READ searchWord NOTIFY searchWordChanged FINAL)

public:
    explicit DataForVisualElements(QObject *parent = nullptr);

    size_t progressBarVal() const;
    void setProgressBarVal(size_t newProgressBarVal);
    QString progressBarPercent() const;
    void setProgressBarPercent(const QString &newProgressBarPercent);

    bool busyIndicator() const;
    void setBusyIndicator(bool newBusyIndicator);
    QList<size_t> searchWord() const;

    InfoMessages *pInfoMessage() const;
    void setPInfoMessage(InfoMessages *newPInfoMessage);

public slots:
    size_t srchWord(const QString &data, const QString &word);
    size_t srchPrevious(const size_t &index);
    size_t srchNext(const size_t &index);

signals:
    void progressBarValChanged();
    void progressBarPercentChanged();
    void busyIndicatorChanged();    
    void searchWordChanged();

    void pInfoMessageChanged();

private:
    InfoMessages *m_pInfoMessage = nullptr;
    size_t m_progressBarVal{0};
    QString m_progressBarPercent{"0.0"};
    bool m_busyIndicator;
    QList<size_t> m_searchWord;
};

#endif // DATAFORVISUALELEMENTS_H
