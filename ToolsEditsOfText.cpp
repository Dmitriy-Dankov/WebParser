#include "ToolsEditsOfText.h"
#include <QRegularExpression>

ToolsEditsOfText::ToolsEditsOfText(QObject *parent)
    : QObject{parent}
{
}

QString ToolsEditsOfText::editData(const QString &dataString) {
    QString temp;
    QString newDataString;
    newDataString.reserve(dataString.size());

    for (size_t i = 0; i < dataString.size()-1; ++i) {
        if (dataString[i] == '>') {
            size_t j = 1;
            while(dataString[i+j] == ' ') ++j;
            if(dataString[i+j] == '<') {
                temp += dataString[i];
                newDataString += temp.trimmed() + "\n";
                temp.clear();
                i += j-1;
            }else {
                temp += dataString[i];
                i += j-1;
            }

        } else if (dataString[i] == ' ') {
            size_t j = 1;
            while(dataString[i+j] == ' ') ++j;
            if (!temp.isEmpty()) {
                temp += dataString[i];
                i += j-1;
            } else i += j-1;

        } else if (dataString[i] == '\n') {
            if ( dataString[i+1] != '\n' && !temp.isEmpty()) {
                newDataString += temp.trimmed() + "\n";
                temp.clear();
            }

        } else if (dataString[i] == ';') {
            if (dataString[i-1] == '*' || dataString[i-1] == '^' || dataString[i+1] == '"') temp += dataString[i];
            else {
                temp += dataString[i];
                newDataString += temp.trimmed() + "\n";
                temp.clear();
            }
        } else if (dataString[i] == ',') {
            if (dataString[i-1] == '"' && dataString[i+1] == '"') {
                temp += dataString[i];
                newDataString += temp.trimmed() + "\n";
                temp.clear();
            }

        } else if (dataString[i] == '{') {
            if (!temp.isEmpty()) {
                newDataString += temp.trimmed() + "\n";
                newDataString += "{/n";
                temp.clear();
            }

        } else if (dataString[i] == '<' && dataString[i+1] == '/'
                   && dataString[i+2] == 'd' && dataString[i+3] == 'i'
                   && dataString[i+4] == 'v')
        {
            if (!temp.isEmpty()) {
                newDataString += "\n";
                newDataString += "</div>\n";
                temp.clear();
                i += 5;
            } else {
                newDataString += "</div>\n";
                i += 5;
            }

        } else if (dataString[i] == '<' && dataString[i+1] == '!' &&
                   dataString[i+2] == '-' && dataString[i+3] == '-')
        {
            if (!temp.isEmpty()) {
                newDataString += "\n";
                newDataString += "<!--\n";
                temp.clear();
                i += 3;
            } else {
                newDataString += "<!--\n";
                i += 3;
            }
        } else if (dataString[i] == '&' &&
                   dataString[i+4] == 't' && dataString[i+5] == ';') {
            i += 5;
            temp += '"';

        } else temp += dataString[i];

        if (!temp.isEmpty() && temp[0].isSpace()) temp.clear();
    }
    if (!temp.isEmpty()){
        temp += dataString[dataString.size()-1];
        newDataString += temp.trimmed() + "\n";
    }
    return newDataString;
}

QString ToolsEditsOfText::internalLinks(const QString &dataString) {
    QString param = "a href=";
    QRegularExpression pattern (param + "\"\\S\\S+\"");
    QRegularExpressionMatch match;
    QString temp;
    size_t index = 0;
    size_t end;
    m_internalLinks.clear();
    while (index < dataString.size()) {
        end = dataString.indexOf("\n", index);
        temp = dataString.mid(index, end-index);
        match = pattern.match(temp);
        if (match.hasMatch()) {
            int first = match.captured(0).indexOf('"') + 1;
            int last = match.captured(0).lastIndexOf('"');
            if( match.captured(0).mid(first, 4) != "http") {
                m_internalLinks += m_url_s + match.captured(0).mid(first, last - first) + "\n";
            } else
                m_internalLinks += match.captured(0).mid(first, last - first) + "\n";
        }
        index = ++end;
    }

    if (m_internalLinks.isEmpty()) return "No internal links.";
    return "";
}

QString ToolsEditsOfText::sources(const QString &dataString)
{
    QString parameter = "src=";
    QRegularExpression pattern (parameter + "\".+\\.\\w{3,4}\"");
    QRegularExpressionMatch match;
    QString temp;
    size_t index = 0;
    size_t end;

    m_sources.clear();
    while (index < dataString.size()) {
        end = dataString.indexOf("\n", index);
        temp = dataString.mid(index, end-index);
        match = pattern.match(temp);
        if (match.hasMatch()) {
            int first = match.captured(0).indexOf('"') + 1;
            int last = match.captured(0).lastIndexOf('"');
            if( match.captured(0).mid(first, 4) != "http") {
                m_sources += m_url_s + match.captured(0).mid(first, last - first) + "\n";
            } else
                m_sources += match.captured(0).mid(first, last - first) + "\n";
        }
        index = ++end;
    }

    if (m_sources.isEmpty()) return "No sources.";
    return "";
}

QString ToolsEditsOfText::block(const QString &dataString, const QString &param, const QString &name) {
    if (dataString == "") return "";
    QRegularExpression pattern (param + "=\"" + name + "\"");
    QRegularExpression tempPattern;
    QRegularExpressionMatch match;
    QRegularExpressionMatch match1;
    QString temp;
    size_t index = 0;
    size_t end;
    size_t counter = 0;
    bool tgl = false;
    m_block.clear();
    while (index < dataString.size()) {
        end = dataString.indexOf("\n", index);
        temp = dataString.mid(index, end-index);
        match = pattern.match(temp);
        match1 = tempPattern.match(temp);
        if (match.hasMatch()) {
            if(!tgl) {
                tgl = true;
                pattern = static_cast<QRegularExpression>(temp.mid(0, 2));
                tempPattern = QRegularExpression("</" + temp.mid(1, 1));
            }
            ++counter;
        } else if(tgl && match1.hasMatch()) {
            --counter;
        }

        if (tgl && counter == 0) {
            tgl = false;
            pattern = QRegularExpression(param + "=\"" + name + '"');
            m_block += temp + "\n";
        }
        else if (tgl) {
            m_block += temp + "\n";
        }
        index = ++end;
    }

    if (m_block.isEmpty()) return "No block: \"" + name + "\".";
    return "";
}

QString ToolsEditsOfText::selectionByTegs(const QString &dataString, const QString &tgs){
    QStringList tegs = tgs.split(',');

    for (size_t i = 0; i < dataString.size(); ++i) {

        if (dataString[i] == '<') {
            ++i;
            while(dataString[i] == ' ') ++i;

            bool tagVerification = [&](){
                size_t count = 0;
                for ( const auto &teg : tegs) {
                    QString temp = teg.trimmed();
                    for(size_t x = 0; x < temp.size(); ++x) {
                        if (dataString[i+x] == temp[x]) {
                            ++count;
                        }
                        else break;
                    }
                    if(count == temp.size()) return true;
                    else count = 0;
                }
                return false;
            }();

            if(tagVerification) {
                i += 3;
                while (dataString[i] != '>' || !dataString.size()) ++i;
                ++i;
                while(dataString[i].isSpace()) ++i;
                if(dataString[i] == '<');
                else {
                    while (dataString[i] != '<' || !dataString.size()) {
                        if(dataString[i] != '\n')
                            m_text += dataString[i];
                        ++i;
                    }
                    m_text += '\n';
                    ++i;
                    continue;
                }
            }
            --i;
        }
    }

    if (m_text.isEmpty()) return "Text not found.";
    return "";
}

QString ToolsEditsOfText::images(const QString &dataString){
    QRegularExpression pattern("\\.jpg|\\.jpeg|\\.png|\\.gif|\\.bmp");
    QRegularExpressionMatch match;
    QString temp;
    QString tm;
    size_t index = 0;
    size_t end;
    m_images.clear();
    while (index < dataString.size()) {
        end = dataString.indexOf("\n", index);
        temp = dataString.mid(index, end-index);
        match = pattern.match(temp);
        if (match.hasMatch()) {
            int last = temp.lastIndexOf(match.captured(0)) + match.captured(0).size()-1;
            int first = temp.lastIndexOf('"', last);

            if(temp.indexOf("http") == -1) {
                m_images += m_url_s + temp.mid(first+1, last - first) + "\n";
            } else if(temp.mid(first+1, 4) == "http") {
                if(temp[first+5] != ':' && temp[first+6] != ':') {
                    tm = temp.mid(first+1, last-first);
                    m_images += tm.insert(tm.indexOf('/'), ':') + "\n";
                } else
                    m_images += temp.mid(first+1, last-first) + "\n";
            }
        }
        index = ++end;
    }

    if (m_images.isEmpty()) return "Images not found.";
    return "";
}

QString ToolsEditsOfText::begining(const QString &dataString, const QString &exprs) {
    QStringList list = exprs.split(',');
    QString temp;
    size_t index = 0;
    size_t end;
    size_t count = 0;
    m_begining.clear();

    QString expr;

    while (index < dataString.size()) {
        end = dataString.indexOf("\n", index);
        temp = dataString.mid(index, end-index);

        for (const auto &ex : list) {
            expr = ex.trimmed();

            for (size_t i = 0; i < expr.size(); ++i) {
                if(expr.size() <= temp.size()) {
                    if ( temp[i] == expr[i]) ++count;
                }
                else break;
            }
            if(count == expr.size()) m_begining += temp + '\n';
            count = 0;
        }

        index = ++end;
    }

    if (m_begining.isEmpty()) return "Nothing found";
    return "";
}

QString ToolsEditsOfText::regExpr(const QString &dataString, const QString &exprs){
    QStringList listExp = exprs.split(',');
    QString exp;
    QString expression;
    for (size_t i = 0; i < listExp.size(); ++i) {
        exp = listExp[i].trimmed();
        if (i == listExp.size()-1) {
            expression += exp;
            break;
        }
        expression += exp + '|';
    }

    QRegularExpression pattern(expression);
    QRegularExpressionMatch match;

    QString temp;
    size_t index = 0;
    size_t end;

    m_regExpr.clear();
    while (index < dataString.size()) {
        end = dataString.indexOf("\n", index);
        temp = dataString.mid(index, end-index);
        size_t pos = 0;
        bool yes = false;
        while(pos < temp.size()) {
            match = pattern.match(temp, pos);
            if (match.hasMatch()) {
                m_regExpr += match.captured(0) + ' ';
                pos = match.capturedEnd();
                if (pos == -1) { m_regExpr += '\n'; yes = false; break; }
                yes = true;
            }
            else {
                if (yes) { m_regExpr += '\n'; yes = false; }
                break;
            }
        }

        index = ++end;
    }

    if (m_regExpr.isEmpty()) return "Nothing found";
    return "";
}

QString ToolsEditsOfText::removeCopy(const QString &dataString) {
    if(dataString.isEmpty()) return "";
    QStringList list = dataString.split('\n');
    list.removeDuplicates();
    QString temp = list.join('\n');

    return temp;
}

//======================================================================
//======================== Getters end Setters =========================
//======================================================================


QString ToolsEditsOfText::getUrl_s() const
{
    return m_url_s;
}

void ToolsEditsOfText::setUrl_s(const QString &newUrl_s)
{
    size_t index = newUrl_s.indexOf("/", 12) + 1;
    m_url_s = newUrl_s.mid(0, index);
}

QString ToolsEditsOfText::getInternalLinks() const
{
    return m_internalLinks;
}

void ToolsEditsOfText::setInternalLinks(const QString &newInternalLinks)
{
    if (m_internalLinks == newInternalLinks) return;
    m_internalLinks = newInternalLinks;
}

QString ToolsEditsOfText::getSources() const
{
    return m_sources;
}

void ToolsEditsOfText::setSources(const QString &newSources)
{
    if (m_sources == newSources) return;
    m_sources = newSources;
}

QString ToolsEditsOfText::getBlock() const
{
    return m_block;
}

void ToolsEditsOfText::setBlock(const QString &newBlock)
{
    if( m_block == newBlock) return;
    m_block = newBlock;
}

QString ToolsEditsOfText::getText() const
{
    return m_text;
}

void ToolsEditsOfText::setText(const QString &newText)
{
    if( m_text == newText) return;
    m_text = newText;
}

QString ToolsEditsOfText::getImages() const
{
    return m_images;
}

void ToolsEditsOfText::setImages(const QString &newImages)
{
    if( m_images == newImages) return;
    m_images = newImages;
}

QString ToolsEditsOfText::getBegining() const
{
    return m_begining;
}

void ToolsEditsOfText::setBegining(const QString &newBegining)
{
    if( m_begining == newBegining) return;
    m_begining = newBegining;
}

QString ToolsEditsOfText::getRegExpr() const
{
    return m_regExpr;
}


