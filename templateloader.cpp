#include "sttemplate.h"
#include "templateloader.h"
#include <QDebug>
#include <QStringList>
#include <QSettings>

TemplateLoader::TemplateLoader(QString path) : qdDirectory(path)
{
    QStringList filters;
    filters << "*.ini";
    qslTemplateList = qdDirectory.entryList(filters,QDir::Files);

    qDebug() << qslTemplateList;
}

int TemplateLoader::loadTemplates()
{
    for(QString filename : qslTemplateList)
    {
        TextTemplate *tmp = new TextTemplate();
        QSettings set(qdDirectory.filePath(filename), QSettings::IniFormat);
        set.setIniCodec("System");
        tmp->qsName = set.value("Template/Name","None").toString();
        tmp->qsContent = set.value("Template/Content", "Empty!").toString();
        tmp->qsAuthorizer = set.value("Template/Authorizer",QString()).toString();

        analyseTemplate(tmp);
        qmTemplateContent.insert(tmp->qsName, tmp);
        tmp->showInfo();
        qDebug() << qmTemplateContent.size();
    }

    return qmTemplateContent.size();
}

TemplateLoader::~TemplateLoader()
{
    for(TextTemplate *p : qmTemplateContent)
        delete p;
}

void TemplateLoader::analyseTemplate(TextTemplate *p)
{
    //pattern "%Brand %Object %Company"
    qDebug() << "Brand: " << p->qsContent.indexOf("%Brand");
    qDebug() << "Object:" << p->qsContent.indexOf("%Object");
    qDebug() << "Content:" << p->qsContent.indexOf("%Content");
}

