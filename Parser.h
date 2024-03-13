#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include "ServerRequest.h"
#include "Dataset.h"
#include "ToolsEditsOfText.h"
#include "DataForVisualElements.h"
#include "InfoMessages.h"

class Parser : public QObject
{
    Q_OBJECT    
    Q_PROPERTY(bool cp_1251 FINAL)
    Q_PROPERTY(Dataset *dataset READ dataset WRITE setDataset NOTIFY datasetChanged FINAL)
    Q_PROPERTY(ToolsEditsOfText *toolEdit READ toolEdit WRITE setToolEdit NOTIFY toolEditChanged FINAL)
    Q_PROPERTY(DataForVisualElements *pforVisualElem READ pforVisualElem NOTIFY pforVisualElemChanged FINAL)
    Q_PROPERTY(ServerRequest *pSRequest READ pSRequest NOTIFY pSRequestChanged FINAL)
    Q_PROPERTY(InfoMessages *pInfoMessage READ pInfoMessage NOTIFY pInfoMessageChanged FINAL)
    Q_PROPERTY(QString errorInfo READ errorInfo NOTIFY errorInfoChanged FINAL)

public:
    explicit Parser(QObject *parent = nullptr);    

    ServerRequest *pSRequest() const;
    void replyProcessing(const QByteArray&);
    DataForVisualElements *pforVisualElem() const;
    InfoMessages *pInfoMessage() const;

    Dataset *dataset() const;
    void setDataset(Dataset *newDataset);

    void setPforVisualElem(DataForVisualElements *newPforVisualElem);

    void setPInfoMessage(InfoMessages *newPInfoMessage);

    ToolsEditsOfText *toolEdit() const;
    void setToolEdit(ToolsEditsOfText *newToolEdit);

    QString errorInfo() const;
    void setErrorInfo(const QString &newErrorInfo);

public slots:
    void setCp_1251(const bool &newCp_1251);
    void request(const QString &url);    
    void functionsOfButtons(const QString &buttonName, const QString &param = "", const QString &name = "");

signals:
    void pforVisualElemChanged();
    void pSRequestChanged();
    void pInfoMessageChanged();
    void datasetChanged();
    void toolEditChanged();

    void errorInfoChanged();

private:
    bool m_cp_1251 = false;
    Dataset *m_dataset = nullptr;
    ServerRequest *m_pSRequest = nullptr;
    DataForVisualElements *m_pforVisualElem = nullptr;
    InfoMessages *m_pInfoMessage = nullptr;
    ToolsEditsOfText *m_toolEdit = nullptr;
    QString m_errorInfo;
};

#endif // PARSER_H
