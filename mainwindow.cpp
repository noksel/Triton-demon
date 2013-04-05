#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings sttngs("./integration.ini", QSettings::IniFormat);


   /*  bot=new TritBot("192.168.199.38",3000); //web
     trtn=new triton("192.168.199.29",22518); // 192.168.199.29*/

    bot=new TritBot( sttngs.value("Tritbot/host").toString(),sttngs.value("Tritbot/port").toInt()); //web
    trtn=new triton(sttngs.value("Triton/host").toString(),sttngs.value("Triton/port").toInt()); // 192.168.199.29

         connect(bot,SIGNAL(ChangedStatus(QString)),ui->statusBar,SLOT(showMessage(QString)));
   //  connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(sendHTTP()));
     connect(ui->newSessionBtn,SIGNAL(clicked()),bot,SLOT(crteNwSession()));

     connect(trtn,SIGNAL(channelChanged(channel*)),bot,SLOT(sendChannelData(channel*)));
     connect(ui->strMonitBtn,SIGNAL(clicked()),trtn,SLOT(startAcquisition()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
