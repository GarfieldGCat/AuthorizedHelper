#pragma  execution_character_set("UTF-8")

#include "mainwindows.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QLabel>
#include <QString>
#include <QDebug>
#include <QTime>
#include <QFileDialog>
#include <QPainter>
#include <cstdlib>
#include <QCoreApplication>
#include <QMessageBox>

const int MAINWND_SIZE_W = 900;
const int MAINWND_SIZE_H = 586;
const int IMAGE_SIZE_W = 2000;
const int IMAGE_SIZE_H = 2830;
const double IMAGE_SCALE = 1.415;
const int SCENE_SIZE_W = 400;
const int SCENE_SIZE_H = 566;
const double SCENE_SCALE = 0.2;

void MainWindows::createLayout()
{
    // layout
    // main layout
    phlMain = new QHBoxLayout;
    pvlGraphScene = new QVBoxLayout;
    pvlSetting = new QVBoxLayout;
    // setting layout
    phlFontSet = new QHBoxLayout;
    phlBrandSet = new QHBoxLayout;
    phlObjectSet = new QHBoxLayout;
    phlContentSet = new QHBoxLayout;
    phlLogoSet = new QHBoxLayout;
    phlDateSet = new QHBoxLayout;
    phlAuthrorizerSet = new QHBoxLayout;
    phlFolderSet = new QHBoxLayout;
    phlButton = new QHBoxLayout;
    phlLog = new QHBoxLayout;

    //binding
    pvlSetting->addLayout(phlFontSet);
    pvlSetting->addLayout(phlObjectSet);
    pvlSetting->addLayout(phlBrandSet);
    pvlSetting->addLayout(phlContentSet);
    pvlSetting->addLayout(phlLogoSet);
    pvlSetting->addLayout(phlDateSet);
    pvlSetting->addLayout(phlAuthrorizerSet);
    pvlSetting->addLayout(phlFolderSet);
    pvlSetting->addLayout(phlButton);
    pvlSetting->addLayout(phlLog);

    phlMain->addLayout(pvlGraphScene);
    phlMain->addSpacing(10);
    phlMain->addLayout(pvlSetting);
}

void MainWindows::createGraphScene()
{
    ppmTemplate = new QPixmap("template");

    pgsScene = new QGraphicsScene(0,0,IMAGE_SIZE_W,IMAGE_SIZE_H);
    pgsScene->addPixmap(*ppmTemplate);
    pgvView = new QGraphicsView(pgsScene);
    pgvView->setFixedSize(SCENE_SIZE_W,SCENE_SIZE_H);
    pgvView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pgvView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //pgvView->fitInView(0,0,IMAGE_SIZE_W-200,IMAGE_SIZE_H-200,Qt::KeepAspectRatio);
    pgvView->scale(SCENE_SCALE,SCENE_SCALE);
    pvlGraphScene->addWidget(pgvView);

    //set content
    pgtiAuthrorizedContent = new QGraphicsTextItem;
    pgtiAuthrorizedContent->setFont(*pfContentFont);
    pgtiAuthrorizedContent->setTextWidth(IMAGE_SIZE_W*0.7);
    pgtiAuthrorizedContent->setPos(IMAGE_SIZE_W*0.15, IMAGE_SIZE_H*0.33);
    pgsScene->addItem(pgtiAuthrorizedContent);
    //pgtiAuthrorizedContent->setTextInteractionFlags(Qt::TextEditorInteraction);

    //set authrorizer
    pgtiAuthrorizedCompany = new QGraphicsTextItem;
    pgtiAuthrorizedCompany->setFont(*pfAuthrorizerFont);
    pgsScene->addItem(pgtiAuthrorizedCompany);
}

void MainWindows::createSettingPage()
{
    const int LABEL_SIZE = 70;

    //fonts
    QVBoxLayout *pvlCheckBoxLay = new QVBoxLayout;
    QLabel *plaFont = new QLabel(tr("Font Type:"));
    plaFont->setFixedWidth(LABEL_SIZE);
    pfcFontType = new QFontComboBox;
    psbFontSize = new QSpinBox;
    psbFontSize->setMaximum(200);
    pcbIsKeyBold = new QCheckBox(tr("&Bolds"));
    pcbIsUnderline = new QCheckBox(tr("&Underline"));
    pcbIsKeyBold->setChecked(true);
    pcbIsUnderline->setChecked(true);
    pcbTemplateBox = new QComboBox;
    pcbTemplateBox->insertItems(0, TmpLoader.getTemplate().keys());
    pcbTemplateBox->setCurrentText("线下模板");
    phlFontSet->addWidget(plaFont);
    phlFontSet->addWidget(pfcFontType);
    phlFontSet->addWidget(psbFontSize);
    pvlCheckBoxLay->addWidget(pcbIsKeyBold);
    pvlCheckBoxLay->addWidget(pcbIsUnderline);
    phlFontSet->addLayout(pvlCheckBoxLay);
    phlFontSet->addWidget(pcbTemplateBox);

    //setting default font
    pfGlobalFont = new QFont("微软雅黑",40);
    psbFontSize->setValue(40);
    pfcFontType->setCurrentFont(*pfGlobalFont);
    pfObjectFont = new QFont(*pfGlobalFont);
    pfObjectFont->setBold(true);
    pfContentFont =new QFont(*pfGlobalFont);
    pfBrandFont = new QFont(*pfGlobalFont);
    pfBrandFont->setBold(true);
    pfDateFont = new QFont(*pfGlobalFont);
    pfAuthrorizerFont = new QFont(*pfGlobalFont);
    pfAuthrorizerFont->setBold(true);

    //objects
    pslObjectList = new QStringList;
    QLabel *plaObject = new QLabel(tr("Objects:"));
    plaObject->setFixedWidth(LABEL_SIZE);
    pteObjectEdit = new QTextEdit;
    pteObjectEdit->setWordWrapMode(QTextOption::WrapAnywhere);
    phlObjectSet->addWidget(plaObject);
    phlObjectSet->addWidget(pteObjectEdit);

    //brands
    pslBrandList = new QStringList;
    QLabel *plaBrand = new QLabel(tr("Brands:"));
    plaBrand->setFixedWidth(LABEL_SIZE);
    pteBrandEdit = new QTextEdit;
    pteBrandEdit->setWordWrapMode(QTextOption::WrapAnywhere);
    phlBrandSet->addWidget(plaBrand);
    phlBrandSet->addWidget(pteBrandEdit);

    //contents
    pslContentList = new QStringList;
    QLabel *plaContent = new QLabel(tr("Contents:"));
    plaContent->setFixedWidth(LABEL_SIZE);
    pteContentEdit = new QTextEdit;
    pteContentEdit->setWordWrapMode(QTextOption::WrapAnywhere);
    phlContentSet->addWidget(plaContent);
    phlContentSet->addWidget(pteContentEdit);

    //logos
    pslLogosList = new QStringList;
    pilLogoSizeList = new QList<int>;
    QVBoxLayout *pvlOpenBtnLay = new QVBoxLayout;
    QLabel *plaLogo = new QLabel(tr("Logos:"));
    plaLogo->setFixedWidth(LABEL_SIZE);
    plwLogoList = new QListWidget;
    ppbOpenLogos = new QPushButton(tr("&Open"));
    ppbRemoveLogo = new QPushButton(tr("Remove"));
    psbLogoSize = new QSpinBox;
    psbLogoSize->setMaximum(999);
    psbLogoSize->setMinimum(20);
    psbLogoSize->setValue(200);
    pvlOpenBtnLay->addWidget(ppbOpenLogos);
    pvlOpenBtnLay->addWidget(ppbRemoveLogo);
    pvlOpenBtnLay->addWidget(psbLogoSize);
    plwLogoList->setMaximumHeight(70);
    phlLogoSet->addWidget(plaLogo);
    phlLogoSet->addWidget(plwLogoList);
    phlLogoSet->addLayout(pvlOpenBtnLay);

    //date
    QLabel *plaDate = new QLabel(tr("Date:"));
    plaDate->setFixedWidth(LABEL_SIZE);
    QLabel *plaDateTo = new QLabel(tr("To"));
    QDate begin;
    begin.setDate(QDate::currentDate().year(),1,1);
    pdeStartDate = new QDateEdit(begin);
    pdeEndDate = new QDateEdit(begin.addYears(1));
    phlDateSet->addWidget(plaDate);
    phlDateSet->addWidget(pdeStartDate);
    phlDateSet->addWidget(plaDateTo);
    phlDateSet->addWidget(pdeEndDate);

    //Authrorizer
    QLabel *plaAuthrorizer = new QLabel(tr("Authrorizer:"));
    plaAuthrorizer->setFixedWidth(LABEL_SIZE);
    pleAuthrorizer = new QLineEdit;
    pcbAuthrorizer = new QComboBox;
    pcbAuthrorizer->addItems(slAuthorizerList);
    pleAuthrorizer->setText(pcbAuthrorizer->currentText());
    phlAuthrorizerSet->addWidget(plaAuthrorizer);
    phlAuthrorizerSet->addWidget(pleAuthrorizer);
    phlAuthrorizerSet->addWidget(pcbAuthrorizer);

    //output path
    QLabel *plaPath = new QLabel(tr("Path:"));
    plaPath->setFixedWidth(LABEL_SIZE);
    pleOutputPath = new QLineEdit;
    ppbOpenPath = new QPushButton(tr("Open &Path"));
    phlFolderSet->addWidget(plaPath);
    phlFolderSet->addWidget(pleOutputPath);
    phlFolderSet->addWidget(ppbOpenPath);

    //generate btn
    ppbResetGraph = new QPushButton(tr("&Reset"));
    ppbGenerate = new QPushButton(tr("&Generate"));
    pcbIsBatchMode = new QCheckBox(tr("Batch Mode"));
    pcbIsBatchMode->setMaximumWidth(pcbIsBatchMode->sizeHint().width());
    pcbIsBatchMode->setChecked(false);
    phlButton->addWidget(ppbResetGraph);
    phlButton->addWidget(pcbIsBatchMode);
    phlButton->addWidget(ppbGenerate);
    ppbResetGraph->setEnabled(false);//Unfinish function;

    //log
    pteTextLog = new QTextEdit;
    pteTextLog->setReadOnly(true);
    phlLog->addWidget(pteTextLog);
}

void MainWindows::signalConnection()
{
    connect(pfcFontType, SIGNAL(currentFontChanged(QFont)), this, SLOT(fontTypeChange(QFont)));
    connect(psbFontSize, SIGNAL(valueChanged(int)), this, SLOT(fontSizeChange(int)));
    connect(pcbIsKeyBold, SIGNAL(clicked(bool)), this, SLOT(updateGraphicsContent()));
    connect(pcbIsUnderline, SIGNAL(clicked(bool)), this, SLOT(updateGraphicsContent()));
    connect(pteBrandEdit, SIGNAL(textChanged()), this, SLOT(brandChange()));
    connect(pteObjectEdit, SIGNAL(textChanged()), this, SLOT(objectChange()));
    connect(pteContentEdit, SIGNAL(textChanged()), this, SLOT(contentChange()));
    connect(ppbOpenLogos, SIGNAL(clicked(bool)), this, SLOT(openLogos()));
    connect(plwLogoList, SIGNAL(currentRowChanged(int)), this, SLOT(currentLogoChange(int)));
    connect(psbLogoSize, SIGNAL(valueChanged(int)), this, SLOT(logoSizeChange(int)));
    connect(ppbRemoveLogo, SIGNAL(clicked(bool)), this, SLOT(removeLogo()));
    connect(pdeStartDate,SIGNAL(dateChanged(QDate)), this, SLOT(dateChange()));
    connect(pdeEndDate, SIGNAL(dateChanged(QDate)), this, SLOT(dateChange()));
    connect(pleAuthrorizer, SIGNAL(textChanged(QString)), this, SLOT(authrorizerChange(QString)));
    connect(ppbOpenPath, SIGNAL(clicked(bool)), this, SLOT(openPath()));
    connect(pleOutputPath, SIGNAL(textChanged(QString)), this, SLOT(outputPathChange(QString)));
    connect(ppbGenerate, SIGNAL(clicked(bool)), this, SLOT(generateAllImage()));
    connect(pcbIsBatchMode, SIGNAL(toggled(bool)), this, SLOT(batchModeChange(bool)));
    connect(this, SIGNAL(sendLog(QString)), this, SLOT(printLog(QString)));
    connect(pcbTemplateBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(templateChange()));
    connect(pcbAuthrorizer, &QComboBox::currentTextChanged, this, [&](QString t){this->pleAuthrorizer->setText(t);} );
    connect(ppbResetGraph, SIGNAL(clicked(bool)), this, SLOT(modifyModeChange()));
}

QString MainWindows::catStringList(const QStringList *psl)
{
    int sizeofList = psl->size();
    QString res;

    for( int i = 0; i < sizeofList; i++ )
        res += psl->at(i);

    return res;
}

void MainWindows::loadSetting()
{
    psIniFile = new QSettings(QDir::currentPath()+"/Settings.ini",QSettings::IniFormat,this);
    psIniFile->setIniCodec("System");
    outPath = psIniFile->value("MainSet/OutPath", QDir::currentPath()).toString();
    logoPath = psIniFile->value("MainSet/LogoPath", QDir::currentPath()).toString();

    psIniFile->beginGroup("Authorizer");
    QStringList authrorizerKeys = psIniFile->allKeys();
    for( QString key : authrorizerKeys )
        slAuthorizerList.push_back(psIniFile->value(key, "").toString());
    psIniFile->endGroup();
}

void MainWindows::saveSetting()
{
    psIniFile->beginGroup("MainSet");
    psIniFile->setValue("OutPath", outPath);
    psIniFile->setValue("LogoPath", logoPath);
    psIniFile->endGroup();
}

MainWindows::MainWindows(QWidget *parent)
    : QMainWindow(parent)
{
    loadSetting();

    TmpLoader.loadTemplates();
    pttTemplate = TmpLoader.getTemplate().value("线下模板", nullptr);
    Q_ASSERT(pttTemplate != nullptr);

    QWidget *central = new QWidget();
    // initialize windows
    // set window size
    setFixedSize(MAINWND_SIZE_W, MAINWND_SIZE_H);
    // create layout
    createLayout();
    central->setLayout(phlMain);
    setCentralWidget(central);
    createSettingPage();
    createGraphScene();
    signalConnection();

    //set defualt output folder
    pleOutputPath->setText(outPath);
    if( !TmpLoader.templateCount() )
        QMessageBox::information(this, tr("Error"), tr("Can't find any template files."), QMessageBox::Ok);
    emit sendLog(tr("Initialize completed."));
    careBaby();
    updateGraphicsContent();
    emit authrorizerChange(pleAuthrorizer->text());
}

MainWindows::~MainWindows()
{
    saveSetting();

    //Data
    delete pslObjectList;
    delete pslBrandList;
    delete pslContentList;
    delete pslLogosList;
    delete pilLogoSizeList;

    //Font
    delete pfGlobalFont;
    delete pfObjectFont;
    delete pfContentFont;
    delete pfBrandFont;
    delete pfDateFont;
    delete pfAuthrorizerFont;

    //Template
    delete ppmTemplate;

    //Settings
    delete psIniFile;
}

void MainWindows::updateGraphicsContent()
{
    /*local String*/
    QString textObject;
    QString textContent;
    QString textBrand;
    QString textLogo;
    QString textDate;
    QString textString = pttTemplate->qsContent;
    //for html style
    QString checkStyle;
    QString checkStyleEnd;
    //cat for size,  <img height="[size]" align="middle" src="[src]"\>
    QString logoStyle("<img height=\"%1\" align=\"middle\" src=\"");
    const QString logoStyleEnd("\">");
    /*local String*/

    if( pcbIsKeyBold->isChecked() )
    {
        checkStyle = "<b>";
        checkStyleEnd = "</b>";
    }
    if( pcbIsUnderline->isChecked() )
    {
        checkStyle += "<u>";
        checkStyleEnd += "</u>";
    }

    textObject = checkStyle + strObject + checkStyleEnd;
    textString.replace("%Object", textObject);

//    if( !strContent.isEmpty() )
//        textContent = QString("在 %1%2%3 上").arg(checkStyle).arg(strContent).arg(checkStyleEnd);
    textContent = checkStyle + strContent + checkStyleEnd;
    textString.replace("%Content", textContent);

    textBrand = checkStyle + strBrand + checkStyleEnd;
    textString.replace("%Brand", textBrand);

    //Logo
    if( !pslLogosList->empty() )
    {
        textLogo = QString("并在授权范围内使用&nbsp;&nbsp;");

        for(int i = 0; i < pslLogosList->size(); i++)
            textLogo += logoStyle.arg(pilLogoSizeList->at(i)) + pslLogosList->at(i) + logoStyleEnd + "&nbsp;&nbsp;";

        textLogo += QString("&nbsp;&nbsp;的商标。");
    }

    //Date
    QDate Start = pdeStartDate->date();
    QDate End = pdeEndDate->date();
    textDate = QString("此授权有效期自 %1%2年%3月%4日%5 到 %6%7年%8月%9日%10。")
            .arg(checkStyle).arg(Start.year()).arg(Start.month()).arg(Start.day()).arg(checkStyleEnd)
            .arg(checkStyle).arg(End.year()).arg(End.month()).arg(End.day()).arg(checkStyleEnd);
    QString strEmtpySapceForDate;
    for( int i = 4; i >= textDate.length()-58; i-- )
        strEmtpySapceForDate += "&nbsp;";
    textDate = strEmtpySapceForDate + textDate;

    /*
    //[!] BUG
    //When using chinese pinyin for long input, it will raise a abnormal issue, consume to many CPU times. Don't know why yet.
    //but problem located to QString() function.

    pgtiAuthrorizedContent->setHtml(
                QString("<p style=\"text-indent:105px;\">兹授权 %1 %2 销售我司代理的 %3 品牌(系列)产品，于授权范围内负责售后等事宜。%4</p><br><p style=\"text-indent:0px;\">%5</p>")
                .arg(textObject).arg(textContent).arg(textBrand).arg(textLogo).arg(textDate)
                );
                */

    pgtiAuthrorizedContent->setHtml(
                QString("<p style=\"text-indent:105px;\">%1 %2</p><br><p style=\"text-indent:0px;\">%3</p>")
                .arg(textString).arg(textLogo).arg(textDate)
                );
}

void MainWindows::fontTypeChange(QFont font)
{
    pfGlobalFont->setFamily(font.family());
    pgtiAuthrorizedContent->setFont(*pfGlobalFont);
}

void MainWindows::fontSizeChange(int size)
{
    pfGlobalFont->setPointSize(size);
    pfAuthrorizerFont->setPointSize(size);
    pgtiAuthrorizedContent->setFont(*pfGlobalFont);
    pgtiAuthrorizedCompany->setFont(*pfAuthrorizerFont);
}

void MainWindows::brandChange()
{
    *pslBrandList = pteBrandEdit->toPlainText().split('\n');

    if( pcbIsBatchMode->isChecked() )
        strBrand = pslBrandList->at(0);
    else
        strBrand = catStringList(pslBrandList);

    updateGraphicsContent();
}

void MainWindows::objectChange()
{
    *pslObjectList = pteObjectEdit->toPlainText().split('\n');

    if( pcbIsBatchMode->isChecked() )
        strObject = pslObjectList->at(0);
    else
        strObject = catStringList(pslObjectList);

    updateGraphicsContent();
}

void MainWindows::contentChange()
{
    *pslContentList = pteContentEdit->toPlainText().split('\n');

    if( pcbIsBatchMode->isChecked() )
        strContent = pslContentList->at(0);
    else
        strContent = catStringList(pslContentList);

    updateGraphicsContent();
}

void MainWindows::dateChange()
{
    updateGraphicsContent();
}

void MainWindows::authrorizerChange(QString content)
{
    pgtiAuthrorizedCompany->setHtml(content);
    pgtiAuthrorizedCompany->setPos((IMAGE_SIZE_W-pgtiAuthrorizedCompany->boundingRect().width())*0.8,IMAGE_SIZE_H*0.8);
}

void MainWindows::outputPathChange(QString content)
{
    outPath = content;
}

void MainWindows::openPath()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                      QDir::currentPath(),
                                                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    pleOutputPath->setText(dir);
}

void MainWindows::generateImage()
{
    QImage output(IMAGE_SIZE_W, IMAGE_SIZE_H, QImage::Format_ARGB32);
    QString filename;
    updateGraphicsContent();

    //cat arguments for filenames
    //authrorizer part
    if( pleAuthrorizer->text().length() <= 5 )
        filename = pleAuthrorizer->text() + "_";
    else
        filename = pleAuthrorizer->text().mid(2,3) + "_";
    //object part
    filename += strObject.left(5) + "_";
    //brand part
    filename += strBrand.left(10) + "_";
    //content part
    if( strContent.isEmpty() )
        filename += "ALL_";
    else
        filename += strContent.left(5) += "_";
    //time part
    filename += QDate::currentDate().toString("yyMMdd");\
    //add path
    filename = outPath + '/' + filename;
    if( QFile::exists(filename+".png") )
        filename += "(1)";

    QPainter painter(&output);

    painter.setRenderHint(QPainter::Antialiasing);
    pgsScene->render(&painter);

    bool res = output.save(filename+".png");
    if(res)
        emit sendLog(tr("File Saved: %1").arg(filename));
    else
        emit sendLog(tr("Unexpected Error! Save failed."));
}

void MainWindows::generateAllImage()
{
    if( pleAuthrorizer->text().isEmpty() || pslObjectList->empty() || pslBrandList->empty() )
    {
        emit sendLog(tr("Incompleted doucument! Check AGAIN!"));
        return;
    }
    \
    if( pcbIsBatchMode->isChecked() )
    {
        //scan & remove for emtpy line
        for( int i = 0; i < pslObjectList->size(); i++ )
            if( pslObjectList->at(i).isEmpty() )
                pslObjectList->removeAt(i);
        for( int i = 0; i < pslContentList->size(); i++ )
            if( pslContentList->at(i).isEmpty() )
                pslContentList->removeAt(i);
        for( int i = 0; i < pslBrandList->size(); i++ )
            if( pslBrandList->at(i).isEmpty() )
                pslBrandList->removeAt(i);

        int sizeofObject = pslObjectList->size();
        int sizeofBrand = pslBrandList->size();
        int sizeofContent = pslContentList->size();
        int total = sizeofObject * sizeofBrand * sizeofContent;
        int cnt = 0;

        for( int i = 0; i < sizeofObject; i++ )
        {
            strObject = pslObjectList->at(i);
            for( int j = 0; j < sizeofBrand; j++ )
            {
                strBrand = pslBrandList->at(j);
                for( int k = 0; k < sizeofContent; k++ )
                {
                    strContent = pslContentList->at(k);
                    for( int z = 0; z < 5; z++ ) //force to process gui, avoid gui blocked.
                        QCoreApplication::processEvents();

                    generateImage();
                    cnt++;
                    emit sendLog(tr("%1/%2 Done.").arg(cnt).arg(total));
                }
            }
        }
    }
    else
    {
        generateImage();
    }
}

void MainWindows::batchModeChange(bool flag)
{
    contentChange();
    brandChange();
    objectChange();

    if( flag )
    {
        int sizeofObject = pslObjectList->size();
        int sizeofBrand = pslBrandList->size();
        int sizeofContent = pslContentList->size();

        emit sendLog(tr("Switch to Batch Mode, %1 Objs, %2 Brands, %3 Contents.").arg(sizeofObject).arg(sizeofBrand).arg(sizeofContent));
        emit sendLog(tr("<font color=\"red\"><b>%1 files total!</b></font>").arg(sizeofObject*sizeofBrand*sizeofContent));
    }
    else
        emit sendLog(tr("Batch Mode OFF."));
}

void MainWindows::printLog(QString log)
{
    QTextCursor cur = pteTextLog->textCursor();
    cur.movePosition(QTextCursor::End);
    pteTextLog->setTextCursor(cur);
    pteTextLog->insertHtml(QString("<font color=\"blue\">[%1]</font>:%2<br>").arg(QTime::currentTime().toString("hh:mm:ss")).arg(log));
}

void MainWindows::modifyModeChange()
{
    qDebug() << "TextItem Enable.";
    isModifyMode = true;
/*
    ppbResetGraph->setEnabled(true);
    ppbOpenLogos->setEnabled(false);
    psbFontSize->setEnabled(false);
    psbLogoSize->setEnabled(false);
    pteBrandEdit->setEnabled(false);
    pteContentEdit->setEnabled(false);
    pteObjectEdit->setEnabled(false);*/
}

void MainWindows::templateChange()
{
    pttTemplate = TmpLoader.getTemplate().value(pcbTemplateBox->currentText());
    updateGraphicsContent();
//    pleAuthrorizer->setText(pttTemplate->qsAuthorizer);
}

void MainWindows::openLogos()
{
    QStringList files = QFileDialog::getOpenFileNames(
                              this,
                              tr("Select one or more files to open"),
                              logoPath,
                              tr("Images (*.png *.gif *.jpg *.bmp)"));

    if(!files.empty())
    {
        logoPath = files.first();
        logoPath.chop(logoPath.length() - logoPath.lastIndexOf('/'));
    }
    int listcnt = plwLogoList->count();

    for(QString str : files)
    {
        bool isRepeat = false;
        for( int i = 0; i < listcnt; i++ )
        {
            if( plwLogoList->item(i)->text() == str )
            {
                isRepeat = true;
                continue;
            }
        }
        if(!isRepeat)
        {
            plwLogoList->addItem(str);
            pslLogosList->push_back(str);
            pilLogoSizeList->push_back(200);    //logo Default Size
        }
    }

    updateGraphicsContent();
}

void MainWindows::currentLogoChange(int r)
{
    if( r >= 0 )    //when last logo delete, still emit currentChange signal with -1. and ->at() can't process this situation.
        psbLogoSize->setValue( pilLogoSizeList->at(r) );
}

void MainWindows::logoSizeChange(int size)
{
    if(plwLogoList->currentRow() >= 0)
    {
        (*pilLogoSizeList)[plwLogoList->currentRow()] = size;
        updateGraphicsContent();
    }
}

void MainWindows::removeLogo()
{
    int currentRow = plwLogoList->currentRow();
    if(currentRow >= 0)
    {
        pslLogosList->removeAt(currentRow);
        delete plwLogoList->takeItem(currentRow);
        pilLogoSizeList->removeAt(currentRow);
    }

    updateGraphicsContent();
}
