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

    //set title
    //    pgtiAuthrorizedTitle = new QGraphicsTextItem(" 代理授权书");
    //    pgtiAuthrorizedTitle->setFont(*pfTitleFont);
    //    pgtiAuthrorizedTitle->setPos((IMAGE_SIZE_W-pgtiAuthrorizedTitle->boundingRect().width())/2,100);
    //    pgsScene->addItem(pgtiAuthrorizedTitle);

    //set content
    pgtiAuthrorizedContent = new QGraphicsTextItem;
    pgtiAuthrorizedContent->setFont(*pfContentFont);
    pgtiAuthrorizedContent->setTextWidth(IMAGE_SIZE_W*0.7);
    pgtiAuthrorizedContent->setPos(IMAGE_SIZE_W*0.15, IMAGE_SIZE_H*0.33);
    pgsScene->addItem(pgtiAuthrorizedContent);
    pgtiAuthrorizedContent->setTextInteractionFlags(Qt::TextEditorInteraction);
    //set date
    pgtiAuthrorizedDate = new QGraphicsTextItem;
    pgtiAuthrorizedDate->setFont(*pfDateFont);
    pgtiAuthrorizedDate->setTextWidth(IMAGE_SIZE_W*0.7);

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
    psbFontSize->setMaximum(999);
    pcbIsKeyBold = new QCheckBox(tr("&Bolds"));
    pcbIsUnderline = new QCheckBox(tr("&Underline"));
    pcbIsKeyBold->setChecked(true);
    pcbIsUnderline->setChecked(true);
    phlFontSet->addWidget(plaFont);
    phlFontSet->addWidget(pfcFontType);
    phlFontSet->addWidget(psbFontSize);
    pvlCheckBoxLay->addWidget(pcbIsKeyBold);
    pvlCheckBoxLay->addWidget(pcbIsUnderline);
    phlFontSet->addLayout(pvlCheckBoxLay);

    //pfTitleFont = new QFont(pfcFontType->font());
    pfTitleFont = new QFont("微软雅黑");
    pfTitleFont->setLetterSpacing(QFont::AbsoluteSpacing, 40);
    pfTitleFont->setBold(true);
    pfTitleFont->setPixelSize(80);

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
    QVBoxLayout *pvlOpenBtnLay = new QVBoxLayout;
    QLabel *plaLogo = new QLabel(tr("Logos:"));
    plaLogo->setFixedWidth(LABEL_SIZE);
    plwLogoList = new QListWidget;
    ppbOpenLogos = new QPushButton(tr("&Open"));
    ppbRemoveLogo = new QPushButton(tr("Remove"));
    pvlOpenBtnLay->addWidget(ppbOpenLogos);
    pvlOpenBtnLay->addWidget(ppbRemoveLogo);
    plwLogoList->setMaximumHeight(55);
    phlLogoSet->addWidget(plaLogo);
    phlLogoSet->addWidget(plwLogoList);
    phlLogoSet->addLayout(pvlOpenBtnLay);

    //date
    QLabel *plaDate = new QLabel(tr("Date:"));
    plaDate->setFixedWidth(LABEL_SIZE);
    QLabel *plaDateTo = new QLabel(tr("To"));
    pdeStartDate = new QDateEdit(QDate::currentDate());
    pdeEndDate = new QDateEdit(QDate::currentDate().addYears(1));
    phlDateSet->addWidget(plaDate);
    phlDateSet->addWidget(pdeStartDate);
    phlDateSet->addWidget(plaDateTo);
    phlDateSet->addWidget(pdeEndDate);

    //Authrorizer
    QLabel *plaAuthrorizer = new QLabel(tr("Authrorizer:"));
    plaAuthrorizer->setFixedWidth(LABEL_SIZE);
    pleAuthrorizer = new QLineEdit;
    phlAuthrorizerSet->addWidget(plaAuthrorizer);
    phlAuthrorizerSet->addWidget(pleAuthrorizer);

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
    phlButton->addWidget(ppbResetGraph);
    phlButton->addWidget(pcbIsBatchMode);
    phlButton->addWidget(ppbGenerate);
    ppbResetGraph->setEnabled(false);//Unfinish function;
    pcbIsBatchMode->setEnabled(false);//Unfinish function;

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
    connect(ppbRemoveLogo, SIGNAL(clicked(bool)), this, SLOT(removeLogo()));
    connect(pdeStartDate,SIGNAL(dateChanged(QDate)), this, SLOT(dateChange()));
    connect(pdeEndDate, SIGNAL(dateChanged(QDate)), this, SLOT(dateChange()));
    connect(pleAuthrorizer, SIGNAL(textChanged(QString)), this, SLOT(authrorizerChange(QString)));
    connect(ppbOpenPath, SIGNAL(clicked(bool)), this, SLOT(openPath()));
    connect(pleOutputPath, SIGNAL(textChanged(QString)), this, SLOT(outputPathChange(QString)));
    connect(ppbGenerate, SIGNAL(clicked(bool)), this, SLOT(generateImage()));
    connect(this, SIGNAL(sendLog(QString)), this, SLOT(showLog(QString)));
}

void MainWindows::careBaby()
{
    QDateTime time = QDateTime::currentDateTime();
    srand(time.toTime_t());

    if(time.date().month() == 7 && time.date().day() == 6)
    {
        emit sendLog("<b><font color=\"red\">❤宝贝生日快乐！❤</font></b>");
        emit sendLog("<b><font color=\"green\">❤宝贝生日快乐！❤</font></b>");
        emit sendLog("<b><font color=\"blue\">❤宝贝生日快乐！❤</font></b>");
        emit sendLog("<b><font color=\"aqua\">❤宝贝生日快乐！❤</font></b>");
        emit sendLog("<b><font color=\"purple\">❤宝贝生日快乐！❤</font></b>");
        emit sendLog("<b><font color=\"red\">❤我爱你！❤</font></b>");
    }

    if(time.date().month() == 1 && time.date().day() == 23)
    {
        emit sendLog("<b><font color=\"red\">❤今天可是我们的纪念日呢❤</font></b>");
        emit sendLog(QString("<b><font color=\"green\">❤我们不知不觉就一起 %1 年啦❤</font></b>").arg(time.date().year() - 2012));
        emit sendLog("<b><font color=\"blue\">❤可你今天还在工作呢❤</font></b>");
        emit sendLog("<b><font color=\"purple\">❤要注意补充水分呀❤</font></b>");
        emit sendLog("<b><font color=\"aqua\">❤最爱你❤</font></b>");
    }

    if(time.time().hour() >= 18 && (rand() % 100 + 1) >= 50)
    {
        switch (int n=rand()%5)
        {
        case 0:
            emit sendLog("<b><font color=\"red\">6点了哦，还在忙呢？</font></b>");
            break;
        case 1:
            emit sendLog("<b><font color=\"red\">累坏了哈，喝杯热水。</font></b>");
            break;
        case 2:
            emit sendLog("<b><font color=\"red\">小宝宝真努力，奖励你上个厕所。</font></b>");
            break;
        case 3:
            emit sendLog("<b><font color=\"red\">爱你~别累坏了呀。</font></b>");
            break;
        case 4:
            emit sendLog("<b><font color=\"red\">小宝贝，加班呢？</font></b>");
            break;
        }
    }
}

MainWindows::MainWindows(QWidget *parent)
    : QMainWindow(parent)
{
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
    pleOutputPath->setText(QDir::currentPath());

    emit sendLog("Initialize completed.");
    careBaby();
}

MainWindows::~MainWindows()
{

}

void MainWindows::updateGraphicsContent()
{
    QString textObject;
    QString textContent;
    QString textBrand;
    QString textLogo;
    QString textDate;
    QString checkStyle;
    QString checkStyleEnd;
    QString logoStyle("<img height=\"200\" align=\"middle\" src=\"");
    QString logoStyleEnd("\">");

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

    if( !pslObjectList->empty() )
        textObject = checkStyle + pslObjectList->first() + checkStyleEnd;

    if( !pslContentList->empty() && !pslContentList->first().isEmpty() )
        textContent = QString("在 %1%2%3 上").arg(checkStyle).arg(pslContentList->first()).arg(checkStyleEnd);

    if( !pslBrandList->empty() )
        textBrand = checkStyle + pslBrandList->first() + checkStyleEnd;

    if( !pslLogosList->empty() )
    {
        textLogo = QString("并在授权范围内使用&nbsp;&nbsp;");

        for(QString path : *pslLogosList)
            textLogo += logoStyle + path + logoStyleEnd + "&nbsp;&nbsp;";

        textLogo += QString("&nbsp;&nbsp;的商标。");
    }

    QDate Start = pdeStartDate->date();
    QDate End = pdeEndDate->date();
    textDate = QString("此授权有效期自 %1%2年%3月%4日%5 到 %6%7年%8月%9日%10。")
            .arg(checkStyle).arg(Start.year()).arg(Start.month()).arg(Start.day()).arg(checkStyleEnd)
            .arg(checkStyle).arg(End.year()).arg(End.month()).arg(End.day()).arg(checkStyleEnd);

    //QString拼接时有中文输入法会异常耗费CPU
    pgtiAuthrorizedContent->setHtml(
                QString("<p style=\"text-indent:105px;\">兹授权 %1 %2 销售我司代理的 %3 品牌(系列)产品，于授权范围内负责售后等事宜。%4</p><br><p style=\"text-indent:105px;\">%5</p>")
                .arg(textObject).arg(textContent).arg(textBrand).arg(textLogo).arg(textDate)
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
    pgtiAuthrorizedContent->setFont(*pfGlobalFont);
}

void MainWindows::brandChange()
{
    *pslBrandList = pteBrandEdit->toPlainText().split('\n');
    updateGraphicsContent();
}

void MainWindows::objectChange()
{
    *pslObjectList = pteObjectEdit->toPlainText().split('\n');
    updateGraphicsContent();
}

void MainWindows::contentChange()
{
    *pslContentList = pteContentEdit->toPlainText().split('\n');
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

    if( pleAuthrorizer->text().isEmpty() || pslObjectList->empty() || pslBrandList->empty() )
    {
        emit sendLog("Incompleted doucument! Check AGAIN!");
        return;
    }

    if( pleAuthrorizer->text().length() <= 5 )
        filename = pleAuthrorizer->text() + "_";
    else
        filename = pleAuthrorizer->text().mid(2,3) + "_";
    if( pslObjectList->first().length() <= 5 )
        filename += pslObjectList->first() + "_";
    else
        filename += pslObjectList->first().left(5) + "_";

    filename += pslBrandList->first() + "_";

    filename += QDate::currentDate().toString("yyMMdd") + ".png";

    QPainter painter(&output);

    painter.setRenderHint(QPainter::Antialiasing);
    pgsScene->render(&painter);

    bool res = output.save(outPath + '/' + filename);
    if(res)
        emit sendLog("File Saved: outPath + '/' + filename;");
    else
        emit sendLog("Unexpected Error! Save failed.");
}

void MainWindows::showLog(QString log)
{
    pteTextLog->insertHtml(QString("<font color=\"blue\">[%1]</font>:%2<br>").arg(QTime::currentTime().toString("hh:mm:ss")).arg(log));
    QTextCursor cur = pteTextLog->textCursor();
    cur.movePosition(QTextCursor::End);
    pteTextLog->setTextCursor(cur);
}

void MainWindows::openLogos()
{
    QStringList files = QFileDialog::getOpenFileNames(
                              this,
                              tr("Select one or more files to open"),
                              "/",
                              tr("Images (*.png *.gif *.jpg *.bmp)"));

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
        }
    }

    updateGraphicsContent();
}

void MainWindows::removeLogo()
{
    int currentRow = plwLogoList->currentRow();
    if(currentRow >= 0)
    {
        pslLogosList->removeAt(currentRow);
        delete plwLogoList->takeItem(currentRow);
    }

    updateGraphicsContent();
}
