﻿#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QCheckBox>
#include <QDateEdit>
#include <QFontComboBox>
#include <QSpinBox>
#include <QTextEdit>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGraphicsTextItem>
#include <QFont>
#include <QSettings>
#include <QList>
#include <QComboBox>
#include "templateloader.h"

class MainWindows : public QMainWindow
{
    Q_OBJECT
private:
    //initialize function
    void createLayout();
    void createGraphScene();
    void createSettingPage();
    void signalConnection();
    //care function
    void careBaby();
    //support functon
    QString catStringList(const QStringList *psl);
    void loadSetting();
    void saveSetting();
    //layout Obj
    //main
    QHBoxLayout *phlMain;
    //two part
    QVBoxLayout *pvlGraphScene;
    QVBoxLayout *pvlSetting;
    //setting
    QHBoxLayout *phlFontSet;
    QHBoxLayout *phlBrandSet;
    QHBoxLayout *phlObjectSet;
    QHBoxLayout *phlContentSet;
    QHBoxLayout *phlLogoSet;
    QHBoxLayout *phlDateSet;
    QHBoxLayout *phlFolderSet;
    QHBoxLayout *phlAuthrorizerSet;
    QHBoxLayout *phlButton;
    QHBoxLayout *phlLog;

    //else object
    QGraphicsView *pgvView;
    QGraphicsScene *pgsScene;
    QFontComboBox *pfcFontType;
    QSpinBox *psbFontSize;
    QCheckBox *pcbIsKeyBold;
    QCheckBox *pcbIsUnderline;
    QComboBox *pcbTemplateBox;
    QTextEdit *pteBrandEdit;
    QTextEdit *pteObjectEdit;
    QTextEdit *pteContentEdit;
    QListWidget *plwLogoList;
    QPushButton *ppbOpenLogos;
    QPushButton *ppbRemoveLogo;
    QSpinBox *psbLogoSize;
    QDateEdit *pdeStartDate;
    QDateEdit *pdeEndDate;
    QComboBox *pcbAuthrorizer;
    QLineEdit *pleAuthrorizer;
    QLineEdit *pleOutputPath;
    QPushButton *ppbOpenPath;
    QPushButton *ppbResetGraph;
    QPushButton *ppbGenerate;
    QCheckBox *pcbIsBatchMode;
    QTextEdit *pteTextLog;

    //GraphObj
    QGraphicsTextItem *pgtiAuthrorizedContent;
    QGraphicsTextItem *pgtiAuthrorizedCompany;
    //QList<QGraphicsPixmapItem> *pgpilAuthroizedLogoList;

    //Data
    QStringList slAuthorizerList;
    QString strObject;
    QString strBrand;
    QString strContent;
    QStringList *pslObjectList;
    QStringList *pslBrandList;
    QStringList *pslContentList;
    QStringList *pslLogosList;
    QList<int> *pilLogoSizeList;

    //Font
    QFont *pfGlobalFont;
    QFont *pfObjectFont;
    QFont *pfContentFont;
    QFont *pfBrandFont;
    QFont *pfDateFont;
    QFont *pfAuthrorizerFont;

    //PATH
    QString outPath;
    QString logoPath;

    //Template
    QPixmap *ppmTemplate;

    //Configuation
    QSettings *psIniFile;
    TemplateLoader TmpLoader;
    const TextTemplate *pttTemplate;
    bool isModifyMode;

public:
    MainWindows(QWidget *parent = 0);
    ~MainWindows();
    //Image Output
    void generateImage();

signals:
    void sendLog(QString log);

public slots:
    void updateGraphicsContent();
    void fontTypeChange(QFont font);
    void fontSizeChange(int size);
    void brandChange();
    void objectChange();
    void contentChange();
    void openLogos();
    void currentLogoChange(int r);
    void logoSizeChange(int size);
    void removeLogo();
    void dateChange();
    void authrorizerChange(QString content);
    void outputPathChange(QString content);
    void openPath();
    void generateAllImage();
    void batchModeChange(bool flag);
    void printLog(QString log);
    void modifyModeChange();
    void templateChange();
};

#endif // MAINWINDOWS_H
