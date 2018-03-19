#ifndef STTEMPLATE_H
#define STTEMPLATE_H
#include <QString>
#include <QFont>
#include <QDebug>

struct TextTemplate
{
    QString qsName;
    QString qsContent;
    QString qsAuthorizer;

//    QString qsBrand;
//    QString qsObject;
//    QFont qfFont;
//    bool isBold;
//    bool isUnderline;

//    TextTemplate() {}
    void showInfo(){ qDebug() << "Name: " << qsName << "  Content: " << qsContent << "  Authorizer: " << qsAuthorizer; }
};

#endif // STTEMPLATE_H
