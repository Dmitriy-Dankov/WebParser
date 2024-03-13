#include "Dataset.h"

Dataset::Dataset(QObject *parent)
    : QObject{parent}
{
}

void Dataset::dataOutput()
{
    setDisplayData(m_data);
}

QString Dataset::displayData() const
{
    return m_displayData;
}

void Dataset::setDisplayData(const QString &newDisplayData)
{
    if (m_displayData == newDisplayData) return;

    m_displayData = newDisplayData;
    emit displayDataChanged();
}

QString Dataset::displayImage() const
{
    return m_displayImage;
}

void Dataset::setDisplayImage(const QString &newDisplayImage)
{
    if (m_displayImage == newDisplayImage) return;
    m_displayImage = newDisplayImage;
    emit displayImageChanged();
}

QStringList Dataset::srcList() const
{
    return m_srcList;
}

void Dataset::setSrcList(const QStringList &newSrcList)
{
    if (m_srcList == newSrcList) return;

    m_srcList = newSrcList;
    emit srcListChanged();
}

QString Dataset::data() const
{
    return m_data;
}

void Dataset::setData(const QString &newData)
{
    if (m_data == newData) return;
    m_data = newData;
}


QString Dataset::displayText() const
{
    return m_displayText;
}

void Dataset::setDisplayText(const QString &newDisplayText)
{
    if (m_displayText == newDisplayText)
        return;
    m_displayText = newDisplayText;
    emit displayTextChanged();
}
