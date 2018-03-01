#ifndef MAINWINDOWS_H
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
#include <QList>

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
    QTextEdit *pteBrandEdit;
    QTextEdit *pteObjectEdit;
    QTextEdit *pteContentEdit;
    QListWidget *plwLogoList;
    QPushButton *ppbOpenLogos;
    QPushButton *ppbRemoveLogo;
    QDateEdit *pdeStartDate;
    QDateEdit *pdeEndDate;
    QLineEdit *pleAuthrorizer;
    QLineEdit *pleOutputPath;
    QPushButton *ppbOpenPath;
    QPushButton *ppbResetGraph;
    QPushButton *ppbGenerate;
    QCheckBox *pcbIsBatchMode;
    QTextEdit *pteTextLog;

    //GraphObj
    QGraphicsTextItem *pgtiAuthrorizedDate;
    QGraphicsTextItem *pgtiAuthrorizedContent;
    QGraphicsTextItem *pgtiAuthrorizedCompany;
    //QList<QGraphicsPixmapItem> *pgpilAuthroizedLogoList;

    //Data
    QString strObject;
    QString strBrand;
    QString strContent;
    QStringList *pslObjectList;
    QStringList *pslBrandList;
    QStringList *pslContentList;
    QStringList *pslLogosList;

    //Font
    QFont *pfGlobalFont;
    QFont *pfTitleFont;
    QFont *pfObjectFont;
    QFont *pfContentFont;
    QFont *pfBrandFont;
    QFont *pfDateFont;
    QFont *pfAuthrorizerFont;

    //PATH
    QString outPath;

    //Template
    QPixmap *ppmTemplate;

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
    void removeLogo();
    void dateChange();
    void authrorizerChange(QString content);
    void outputPathChange(QString content);
    void openPath();
    void generateAllImage();
    void batchModeChange(bool flag);
    void printLog(QString log);
};

#endif // MAINWINDOWS_H
