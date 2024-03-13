#ifndef ToolsEditsOfText_H
#define ToolsEditsOfText_H

#include <QObject>

class ToolsEditsOfText : public QObject
{
    Q_OBJECT
public:
    explicit ToolsEditsOfText(QObject *parent = nullptr);

    QString editData(const QString &newDataString);

    QString internalLinks(const QString &dataString);
    QString sources(const QString &dataString);
    QString block(const QString &dataString, const QString &param, const QString &name);
    QString selectionByTegs(const QString &dataString, const QString &tegs);
    QString images(const QString &dataString);
    QString begining(const QString &dataString, const QString &expr);
    QString regExpr(const QString &dataString, const QString &exprs);
    QString removeCopy(const QString &dataString);

    QString testText(const QString &dataString);

    QString getBlock() const;
    void setBlock(const QString &newStrBlock);

    QString getUrl_s() const;
    void setUrl_s(const QString &newUrl_s);

    QString getInternalLinks() const;
    void setInternalLinks(const QString &newInternalLinks);

    QString getSources() const;
    void setSources(const QString &newSources);

    QString getText() const;
    void setText(const QString &newText);

    QString getImages() const;
    void setImages(const QString &newImages);

    QString getBegining() const;
    void setBegining(const QString &newBegining);

    QString getRegExpr() const;

signals:

private:
    QString m_url_s;
    QString m_internalLinks;
    QString m_sources;
    QString m_block;
    QString m_text;
    QString m_images;
    QString m_begining;
    QString m_regExpr;

};

#endif // ToolsEditsOfText_H
