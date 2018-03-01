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

    //setting default font
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
    pcbIsBatchMode->setChecked(true);
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
    connect(ppbRemoveLogo, SIGNAL(clicked(bool)), this, SLOT(removeLogo()));
    connect(pdeStartDate,SIGNAL(dateChanged(QDate)), this, SLOT(dateChange()));
    connect(pdeEndDate, SIGNAL(dateChanged(QDate)), this, SLOT(dateChange()));
    connect(pleAuthrorizer, SIGNAL(textChanged(QString)), this, SLOT(authrorizerChange(QString)));
    connect(ppbOpenPath, SIGNAL(clicked(bool)), this, SLOT(openPath()));
    connect(pleOutputPath, SIGNAL(textChanged(QString)), this, SLOT(outputPathChange(QString)));
    connect(ppbGenerate, SIGNAL(clicked(bool)), this, SLOT(generateAllImage()));
    connect(pcbIsBatchMode, SIGNAL(toggled(bool)), this, SLOT(batchModeChange(bool)));
    connect(this, SIGNAL(sendLog(QString)), this, SLOT(printLog(QString)));
}

void MainWindows::careBaby()
{
    QDateTime time = QDateTime::currentDateTime();
    srand(time.toTime_t());
    QDate calDate = time.date();
    calDate.setDate(calDate.year(), calDate.month(), 1);
    int secSunday = 1+7-calDate.dayOfWeek()+7;
    bool isFestival = false;

    switch( int month = time.date().month() )
    {
    case 1:
        //新年
        if(time.date().day() == 1)
        {
            emit sendLog("<b><font color=\"blue\">新年快乐！我红包呢？！</font></b>");
            emit sendLog("<b><font color=\"purple\">祝我宝宝一帆风顺，万事如意！</font></b>");
            emit sendLog("<b><font color=\"aqua\">❤很快就是纪念日啦，爱你=3=❤</font></b>");
        }
        //纪念日
        else if(time.date().day() == 23)
        {
            emit sendLog("<b><font color=\"red\">❤今天可是我们的纪念日呢❤</font></b>");
            emit sendLog(QString("<b><font color=\"green\">❤我们不知不觉就一起 %1 年啦❤</font></b>").arg(time.date().year() - 2012));
            emit sendLog("<b><font color=\"blue\">❤可你今天是在工作呢还是就想来看看呢？❤</font></b>");
            emit sendLog("<b><font color=\"purple\">❤要注意补充水分呀❤</font></b>");
            emit sendLog("<b><font color=\"aqua\">❤没多久就是情人节啦，最爱你❤</font></b>");
            isFestival = true;
        }
        break;
    case 2:
        //情人节
        if(time.date().day() == 14)
        {
            emit sendLog("<b><font color=\"blue\">❤情人节快乐~❤</font></b>");
            emit sendLog("<b><font color=\"purple\">❤我知道今天你一定会打开来看看的！❤</font></b>");
            emit sendLog("<b><font color=\"aqua\">❤被识破是不是很恐怖呀❤</font></b>");
            emit sendLog("<b><font color=\"red\">❤爱你哟❤</font></b>");
            isFestival = true;
        }
        break;
    case 3:
        //妇女节
        if(time.date().day() == 8)
        {
            emit sendLog("<b><font color=\"red\">恭喜你成功获取三八节资格！</font></b>");
            emit sendLog("<b><font color=\"green\">❤Love U (= 3=) ❤</font></b>");
            isFestival = true;
        }
        break;
    case 4:
        break;
    case 5:
        //劳动节
        if(time.date().day() == 1)
        {
            emit sendLog("<b><font color=\"red\">Σ( ° △ °|||)︴怎么今天你还打开了这个软件</font></b>");
            emit sendLog("<b><font color=\"green\">❤那就多劳动劳动吧~❤</font></b>");
            emit sendLog("<b><font color=\"blue\">❤嘿嘿嘿也算哟❤</font></b>");
            isFestival = true;
        }
        //母亲节
        if(time.date().day() == secSunday)
        {
            emit sendLog("<b><font color=\"blue\">今天母亲节哟</font></b>");
            emit sendLog("<b><font color=\"red\">记得给妈妈捎个问候呀</font></b>");
            isFestival = true;
        }
        break;
    case 6:
        //儿童节
        if(time.date().day() == 1)
        {
            pteBrandEdit->setMaximumHeight(45);
            pteContentEdit->setMaximumHeight(45);
            pteObjectEdit->setMaximumHeight(45);
            emit sendLog("╭╮＿＿＼｜／＿＿╭╮");
            emit sendLog("│&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~&nbsp;│");
            emit sendLog("│&nbsp;≥╭———╮&nbsp;≤ │");
            emit sendLog("│／／│０&nbsp;０│／／.│");
            emit sendLog("│&nbsp;&nbsp;╰———╯&nbsp;&nbsp; │");
            emit sendLog("╰——┬Ｏ————┬╯");
            emit sendLog("&nbsp;&nbsp;●│&nbsp;&nbsp;&nbsp;&nbsp;│");
            emit sendLog("&nbsp;&nbsp;╰│&nbsp;&nbsp;Ｏ&nbsp;│");
            emit sendLog("&nbsp;&nbsp;╰｜｜-｜｜╯");
            emit sendLog("<b><font color=\"red\">儿童节快乐呀猪猪！</b></font>");
            isFestival = true;
        }
        break;
    case 7:
        //生日
        if(time.date().day() == 6)
        {
            emit sendLog("<b><font color=\"red\">❤宝贝生日快乐！❤</font></b>");
            emit sendLog("<b><font color=\"green\">❤宝贝生日快乐！❤</font></b>");
            emit sendLog("<b><font color=\"blue\">❤宝贝生日快乐！❤</font></b>");
            emit sendLog("<b><font color=\"aqua\">❤宝贝生日快乐！❤</font></b>");
            emit sendLog("<b><font color=\"purple\">❤宝贝生日快乐！❤</font></b>");
            emit sendLog("<b><font color=\"red\">❤我爱你！❤</font></b>");
            isFestival = true;
        }
        break;
    case 8:
        break;
    case 9:
        break;
    case 10:
        //国庆1-7
        if(time.date().day() <= 7)
        {
            emit sendLog("<b><font color=\"red\">━━∑(￣□￣*|||━━</font></b>");
            emit sendLog("<b><font color=\"green\">你怎么可能会在国庆用这个东西呢</font></b>");
            emit sendLog("<b><font color=\"blue\">一定是你调皮就是想开了看看</font></b>");
            emit sendLog("<b><font color=\"aqua\">❤好吧，爱你~❤</font></b>");
            isFestival = true;
        }
        break;
    case 11:
        break;
    case 12:
        //平安夜
        if(time.date().day() == 24)
        {
            emit sendLog("<b><font color=\"green\">猪猪要平平安安哟</font></b>");
            emit sendLog("<b><font color=\"blue\">Love u</font></b>");
            emit sendLog("<b><font color=\"aqua\">❤(= 3=)❤</font></b>");
        }//剩蛋节
        else if(time.date().day() == 25)
        {
            emit sendLog("<b><font color=\"red\">❤剩蛋节快乐呀❤</font></b>");
            emit sendLog("<b><font color=\"green\">❤是一个旅店业业绩爆炸的日子呢❤</font></b>");
            emit sendLog("<b><font color=\"blue\">❤喜欢你❤</font></b>");
            isFestival = true;
        }//跨年
        else if(time.date().day() == 31)
        {
            emit sendLog("<b><font color=\"blue\">要跨年啦！</font></b>");
            emit sendLog("<b><font color=\"green\">今天开没开动物之森呀</font></b>");
            emit sendLog("<b><font color=\"aqua\">❤还是开着我了呢~❤</font></b>");
            emit sendLog("<b><font color=\"purple\">❤来年身体要倍儿健康呀❤</font></b>");
            isFestival = true;
        }
    default:
        break;
    };

    //加班
    if(time.time().hour() >= 18 && isFestival || (rand() % 100 + 1) >= 50)
    {
        int n = rand()%5;
        if( isFestival )
            n = 3;  //节日加班固定组合
        switch (n)
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
    psIniFile = new QSettings(QDir::currentPath()+"/Settings.ini",QSettings::IniFormat);
    outPath = psIniFile->value("MainSet/OutPath", QDir::currentPath()).toString();
    delete psIniFile;
}

void MainWindows::saveSetting()
{
    psIniFile = new QSettings(QDir::currentPath()+"/Settings.ini",QSettings::IniFormat);
    psIniFile->beginGroup("MainSet");
    psIniFile->setValue("OutPath", outPath);
    psIniFile->endGroup();
    delete psIniFile;
}

MainWindows::MainWindows(QWidget *parent)
    : QMainWindow(parent)
{
    loadSetting();
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

    emit sendLog(tr("Initialize completed."));
    careBaby();
}

MainWindows::~MainWindows()
{
    saveSetting();
}

void MainWindows::updateGraphicsContent()
{
    QString textObject;
    QString textContent;
    QString textBrand;
    QString textLogo;
    QString textDate;
    //for html style
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

    textObject = checkStyle + strObject + checkStyleEnd;

    if( !strContent.isEmpty() )
        textContent = QString("在 %1%2%3 上").arg(checkStyle).arg(strContent).arg(checkStyleEnd);

    textBrand = checkStyle + strBrand + checkStyleEnd;

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

    //[!] BUG
    //When using chinese pinyin for long input, it will raise a abnormal issue, consume to many CPU times. Don't know why yet.
    //but problem located to QString() function.
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
    filename += strBrand + "_";
    //content part
    if( strContent.isEmpty() )
        filename += "ALL_";
    else
        filename += strContent.left(5) += "_";
    //time part
    filename += QDate::currentDate().toString("yyMMdd") + ".png";

    QPainter painter(&output);

    painter.setRenderHint(QPainter::Antialiasing);
    pgsScene->render(&painter);

    bool res = output.save(outPath + '/' + filename);
    if(res)
        emit sendLog(tr("File Saved: %1").arg(outPath + '/' + filename));
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
