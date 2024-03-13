#include "TextFilters.h"

TextFilters::TextFilters(QObject *parent)
    : QObject{parent}
{
}

void TextFilters::handler(const QString &nameWin, const QString &nameFilter, const QString &regs)
{
    if(nameFilter == "bgn") fromBegining(nameWin, regs);
    else if(nameFilter == "tags") {
        m_pInfoMessage->setMessage(m_toolEdit->selectionByTegs(m_dataset->displayText(), regs));
        m_dataset->setDisplayText(m_toolEdit->getText());
    } else if(nameFilter == "reg") {
        m_pInfoMessage->setMessage(m_toolEdit->regExpr(m_dataset->displayText(), regs));
        m_dataset->setDisplayText(m_toolEdit->getRegExpr());
    }
}

void TextFilters::fromBegining(const QString &nameWin, const QString &regs){
    if (regs.isEmpty()) m_pInfoMessage->setMessage("Filter Empty");
    if (nameWin == "img") {
        m_pInfoMessage->setMessage(m_toolEdit->begining(m_toolEdit->getImages(), regs));
        m_dataset->setDisplayImage(m_toolEdit->getBegining());
    }
    else if (nameWin == "txt") {
        m_pInfoMessage->setMessage(m_toolEdit->begining(m_dataset->displayData(), regs));
        m_dataset->setDisplayText(m_toolEdit->getBegining());
    }
}


//======================================================================
//======================== Getters end Setters =========================
//======================================================================

Dataset *TextFilters::dataset() const
{
    return m_dataset;
}

void TextFilters::setDataset(Dataset *newDataset)
{
    if (m_dataset == newDataset)
        return;
    m_dataset = newDataset;
    emit datasetChanged();
}

void TextFilters::setToolEdit(ToolsEditsOfText *newToolEdit)
{
    if (m_toolEdit == newToolEdit)
        return;
    m_toolEdit = newToolEdit;
    emit toolEditChanged();
}

InfoMessages *TextFilters::pInfoMessage() const
{
    return m_pInfoMessage;
}

void TextFilters::setPInfoMessage(InfoMessages *newPInfoMessage)
{
    if (m_pInfoMessage == newPInfoMessage)
        return;
    m_pInfoMessage = newPInfoMessage;
    emit pInfoMessageChanged();
}

ToolsEditsOfText *TextFilters::toolEdit() const
{
    return m_toolEdit;
}
