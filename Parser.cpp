#include "Parser.h"
#include "Download.h"

Parser::Parser(QObject *parent)
    : QObject{parent}
{
    m_pSRequest = new ServerRequest(this);
    connect(m_pSRequest, &ServerRequest::SendAReply, this, &Parser::replyProcessing);
}

//======================================================================
//======================= Basics of the program ========================
//======================================================================

void Parser::request(const QString &url)
{
    m_pSRequest->request(url);
    m_toolEdit->setUrl_s(url);
}

void Parser::replyProcessing(const QByteArray &data)
{
    QString temp;
    if (!m_cp_1251) {
        temp = QString::fromUtf8(data);
        m_dataset->setData(m_toolEdit->editData(data));
        m_dataset->setDisplayData(m_toolEdit->editData(data));
    } else {
        temp = QString::fromLocal8Bit(data);
        m_dataset->setData(m_toolEdit->editData(temp));
        m_dataset->setDisplayData(m_toolEdit->editData(temp));
    }
}

void Parser::functionsOfButtons(const QString &buttonName, const QString &prm_1, const QString &prm_2){
    QString temp;
    if(buttonName == "Block") {
        temp = m_toolEdit->block(m_dataset->data(), prm_1, prm_2);
        m_dataset->setDisplayData(m_toolEdit->getBlock());
    } else if(buttonName == "All href...") {
        temp = m_toolEdit->internalLinks(m_dataset->data());
        m_dataset->setDisplayData(m_toolEdit->getInternalLinks());
    } else if(buttonName == "All src...") {
        temp = m_toolEdit->sources(m_dataset->data());
        m_dataset->setDisplayData(m_toolEdit->getSources());
    } else if(buttonName == "imgDwl") {
        m_dataset->srcList().clear();
        m_dataset->setSrcList(m_dataset->displayImage().split('\n'));
        Download loading;
        size_t countList = m_dataset->srcList().count();
        double num;

        if (!prm_1.isEmpty()) {
            m_pforVisualElem->setProgressBarPercent("0.0");
            m_pforVisualElem->setProgressBarVal(0);

            for (size_t i = 0; i < m_dataset->srcList().size(); ++i) {
                if(m_dataset->srcList()[i].isEmpty()) continue;
                num = (static_cast<double>(i) / countList) * 100;
                m_pforVisualElem->setProgressBarVal(num+1);
                m_pforVisualElem->setProgressBarPercent((QString::number(num)+".00").first(4));
                setErrorInfo( loading.download(m_dataset->srcList()[i], prm_1, "img") );
            }
            m_pforVisualElem->setProgressBarPercent("100");
            m_pforVisualElem->setProgressBarVal(100);
        }
        else temp = "Folder path not specified";
    }
    else if(buttonName == "SrchImgs") {
        temp = m_toolEdit->images(m_dataset->data());
        m_toolEdit->setImages( m_toolEdit->removeCopy(m_toolEdit->getImages()));
        m_dataset->setDisplayImage(m_toolEdit->getImages());
        if(m_toolEdit->getImages().isEmpty()) return;
    }

    m_pInfoMessage->setMessage(temp);
}

//======================================================================
//======================== Getters end Setters =========================
//======================================================================

void Parser::setCp_1251(const bool &newCp_1251)
{
    m_cp_1251 = newCp_1251;
    request(m_pSRequest->url());
}

Dataset *Parser::dataset() const
{
    return m_dataset;
}

void Parser::setDataset(Dataset *newDataset)
{
    if (m_dataset == newDataset) return;
    m_dataset = newDataset;
    emit datasetChanged();
}

ToolsEditsOfText *Parser::toolEdit() const
{
    return m_toolEdit;
}

void Parser::setToolEdit(ToolsEditsOfText *newToolEdit)
{
    if (m_toolEdit == newToolEdit)
        return;
    m_toolEdit = newToolEdit;
    emit toolEditChanged();
}

ServerRequest *Parser::pSRequest() const
{
    return m_pSRequest;
}

DataForVisualElements *Parser::pforVisualElem() const
{
    return m_pforVisualElem;
}

void Parser::setPforVisualElem(DataForVisualElements *newPforVisualElem)
{
    if (m_pforVisualElem == newPforVisualElem) return;
    m_pforVisualElem = newPforVisualElem;
    emit pforVisualElemChanged();
}

InfoMessages *Parser::pInfoMessage() const
{
    return m_pInfoMessage;
}

void Parser::setPInfoMessage(InfoMessages *newPInfoMessage)
{
    if (m_pInfoMessage == newPInfoMessage) return;
    m_pInfoMessage = newPInfoMessage;
    emit pInfoMessageChanged();
}

QString Parser::errorInfo() const
{
    return m_errorInfo;
}

void Parser::setErrorInfo(const QString &newErrorInfo)
{
    if (newErrorInfo == "") return;
    m_errorInfo = newErrorInfo;
    emit errorInfoChanged();
}
