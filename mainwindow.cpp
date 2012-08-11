#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qt/qhttp.h>
#include <QDebug>
#include <qregexp.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    bot=new TritBot();
    connect(bot,SIGNAL(ChangedStatus(QString)),ui->statusBar,SLOT(showMessage(QString)));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(sendHTTP()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(createNewTrSess()));
  /*  email="ddd";
    pass="foobar";
     m_http = new QHttp("localhost",3000);

    connect(m_http, SIGNAL(responseHeaderReceived(QHttpResponseHeader)), SLOT(getToken(QHttpResponseHeader)));
    QHttpRequestHeader header("POST", "/sessions");
    header.setValue("Host", "localhost:3000");
    header.setValue( "Referer", "http://localhost:3000/sessions");
    header.setContentType("application/x-www-form-urlencoded");


    QString par="utf8=%E2%9C%93&authenticity_token=AXtKzkGTB5yO6UAkRYqdrYxueQiT%2BHyqQ%2BB0SAtn5Mk%3D";
            par+="&session[email]="+email;
            par+="&session[password]="+pass+"&commit=Sign In";
     QByteArray sg (par.toUtf8());


     header.setContentLength(sg.count());
  //  qDebug()<<header.toString();
    m_http->request(header,sg);






    m_hp = new QHttp("localhost",3000);
    connect(m_hp, SIGNAL(requestFinished(int, bool)), SLOT(getCurTrSes(int,bool)));
    m_hp->get("/triton_sessions/last");
   // remember_token= "BAhbB2kJSSJFMTM4M2VjYjIzNjUyZjNjYmM0YmFkNmU5N2Y0ZTAzOWVlZWZhMzkyOTI5ZTFhMjA4YWJiNWZjMWI3ZDc4YWQ2OAY6BkVU--ee14207c6ee75cd05d9f3c5cba7a34125e1ef0c1";
*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendHTTP()
{

    bot->sendData(ui->spinBoxX->value(),ui->spinBoxY->value());


}



void MainWindow::createNewTrSess()
{
  bot->crteNwSession();
}



