#ifndef TEXTFILTERS_H
#define TEXTFILTERS_H

#include <QObject>
#include "ToolsEditsOfText.h"
#include "Dataset.h"
#include "InfoMessages.h"


class TextFilters : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Dataset *dataset READ dataset WRITE setDataset NOTIFY datasetChanged FINAL)
    Q_PROPERTY(ToolsEditsOfText *toolEdit READ toolEdit WRITE setToolEdit NOTIFY toolEditChanged FINAL)
    Q_PROPERTY(InfoMessages *pInfoMessage READ pInfoMessage WRITE setPInfoMessage NOTIFY pInfoMessageChanged FINAL)

public:
    explicit TextFilters(QObject *parent = nullptr);

    Dataset *dataset() const;
    void setDataset(Dataset *newDataset);

    InfoMessages *pInfoMessage() const;
    void setPInfoMessage(InfoMessages *newPInfoMessage);

    ToolsEditsOfText *toolEdit() const;
    void setToolEdit(ToolsEditsOfText *newToolEdit);

    void fromBegining(const QString &name, const QString &regs);

public slots:
    void handler(const QString &nameWin, const QString &nameFilter, const QString &regs);

signals:
    void datasetChanged();
    void pInfoMessageChanged();
    void toolEditChanged();

private:
    Dataset *m_dataset = nullptr;
    ToolsEditsOfText *m_toolEdit = nullptr;
    InfoMessages *m_pInfoMessage = nullptr;

};

#endif // TEXTFILTERS_H
