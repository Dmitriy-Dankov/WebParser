#include "DataForVisualElements.h"

DataForVisualElements::DataForVisualElements(QObject *parent)
    : QObject{parent}
{
}

size_t DataForVisualElements::srchWord(const QString &data, const QString &word)
{
    m_searchWord.clear();
    QString temp = word.trimmed();
    for (size_t i = 0; i < data.length(); ++i) {

        size_t count = 0;

        for(size_t x = 0; x < temp.length(); ++x) {
            if (data[i+x] == temp[x]) {
                ++count;
            }
            else break;
        }
        if(count == temp.length())  m_searchWord << i;

        count = 0;
    }

    if(m_searchWord.isEmpty()) m_pInfoMessage->setMessage("No matches");

    return  m_searchWord.size();
}

size_t DataForVisualElements::srchPrevious(const size_t &index)
{
    size_t temp = index;
    if (temp > 0) return --temp;
    return index;
}

size_t DataForVisualElements::srchNext(const size_t &index)
{
    size_t temp = index;
    if (temp < m_searchWord.size()-1) return ++temp;
    return index;
}

//======================================================================
//======================== Getters end Setters =========================
//======================================================================

InfoMessages *DataForVisualElements::pInfoMessage() const
{
    return m_pInfoMessage;
}

void DataForVisualElements::setPInfoMessage(InfoMessages *newPInfoMessage)
{
    if (m_pInfoMessage == newPInfoMessage)
        return;
    m_pInfoMessage = newPInfoMessage;
    emit pInfoMessageChanged();
}

size_t DataForVisualElements::progressBarVal() const
{
    return m_progressBarVal;
}

void DataForVisualElements::setProgressBarVal(size_t newProgressBarVal)
{
    if (m_progressBarVal == newProgressBarVal)
        return;
    m_progressBarVal = newProgressBarVal;
    emit progressBarValChanged();
}

QString DataForVisualElements::progressBarPercent() const
{
    return "Progress:  " + m_progressBarPercent + "%";
}

void DataForVisualElements::setProgressBarPercent(const QString &newProgressBarPercent)
{
    if (m_progressBarPercent == newProgressBarPercent) return;
    m_progressBarPercent = newProgressBarPercent;
    emit progressBarPercentChanged();
}

bool DataForVisualElements::busyIndicator() const
{
    return m_busyIndicator;
}

void DataForVisualElements::setBusyIndicator(bool newBusyIndicator)
{
    if (m_busyIndicator == newBusyIndicator) return;
    m_busyIndicator = newBusyIndicator;
    emit busyIndicatorChanged();
}

QList<size_t> DataForVisualElements::searchWord() const
{
    return m_searchWord;
}
