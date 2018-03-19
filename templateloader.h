#ifndef TEMPLATELOADER_H
#define TEMPLATELOADER_H
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QMap>
#include "sttemplate.h"

class TemplateLoader
{
public:
    TemplateLoader(QString path = "templates/");
    int loadTemplates();
    int templateCount() { return qmTemplateContent.size(); }
    ~TemplateLoader();

    const QMap<QString,TextTemplate *>& getTemplate() { return qmTemplateContent; }
private:
    //debug function;
    void analyseTemplate(TextTemplate *p);

    QDir qdDirectory;
    QStringList qslTemplateList;
    QMap<QString,TextTemplate *> qmTemplateContent;
};

#endif // TEMPLATELOADER_H
