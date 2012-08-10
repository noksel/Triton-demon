#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qt/qhttp.h>
#include <QDebug>
#include <qregexp.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    email="ddd";
    pass="foobar";
     m_http = new QHttp("localhost",3000);
    connect(m_http, SIGNAL(requestFinished(int, bool)), SLOT(httpRequestFinished(int, bool)));
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




    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(sendHTTP()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(createNewTrSess()));
    m_hp = new QHttp("localhost",3000);
    connect(m_hp, SIGNAL(requestFinished(int, bool)), SLOT(getCurTrSes(int,bool)));
    m_hp->get("/triton_sessions/last");
   // remember_token= "BAhbB2kJSSJFMTM4M2VjYjIzNjUyZjNjYmM0YmFkNmU5N2Y0ZTAzOWVlZWZhMzkyOTI5ZTFhMjA4YWJiNWZjMWI3ZDc4YWQ2OAY6BkVU--ee14207c6ee75cd05d9f3c5cba7a34125e1ef0c1";


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendHTTP()
{
        QHttpRequestHeader header("POST", "/points");
        header.setValue("Host", "localhost:3000");
        header.setValue( "Referer", "http://localhost:3000/points");

        header.setValue( "Cookie", "remember_token="+remember_token);

        header.setContentType("application/x-www-form-urlencoded");


        QString par="utf8=%E2%9C%93&authenticity_token=AXtKzkGTB5yO6UAkRYqdrYxueQiT%2BHyqQ%2BB0SAtn5Mk%3D&point%5Bx%5D="+ui->spinBoxX->text()+"&point%5By%5D="+ui->spinBoxY->text()+
                "&point[triton_session_id]="+curTrSes+"&commit=Create+Point";
         QByteArray sg (par.toUtf8());

        header.setContentLength(sg.count());
        qDebug()<<sg;

        qDebug()<<header.toString();
        m_http->request(header,sg);


}

void MainWindow::httpRequestFinished(int, bool)
{

    qDebug()<<m_http->readAll();
}

void MainWindow::createNewTrSess()
{
    QDate d;
    qDebug()<<d.currentDate().year()<<d.currentDate().month()<<d.currentDate().day();

    QString par="utf8=#x2713&authenticity_token=AXtKzkGTB5yO6UAkRYqdrYxueQiT+HyqQ+B0SAtn5Mk=";
    par+="&triton_session[dateStart(1i)]=";
    par.append(QString("%1").arg(d.currentDate().year()));

    par+="&triton_session[dateStart(2i)]=";
          par.append(QString("%1").arg(d.currentDate().month()));
    par+="&triton_session[dateStart(3i)]=";
           par.append(QString("%1").arg(d.currentDate().day()));
    par+="&commit=Create Triton session";
    QByteArray sg (par.toUtf8());



    QHttpRequestHeader header("POST", "/triton_sessions");
    header.setValue("Host", "localhost:3000");
    header.setValue( "Referer", "http://localhost:3000/triton_sessions");
    header.setValue( "Cookie", "remember_token="+remember_token);
    header.setContentType("application/x-www-form-urlencoded");
    header.setContentLength(sg.count());
    m_hp->request(header,sg);

}

void MainWindow::getCurTrSes(int, bool)
{
    QString t=m_hp->readAll();
    qDebug()<<t;
    QRegExp rx( ".*(\\d+)\\\"\\>red.*" );
     rx.indexIn(t);
    curTrSes=rx.cap( 1 );
     qDebug()<<curTrSes;


}

void MainWindow::getToken(QHttpResponseHeader resp)
{
    QString t= resp.toString();
    QRegExp rx( ".*remember_token\\=(.*)Set-Cookie.*" );
    rx.indexIn(t);
    t=rx.cap( 1 );
    rx.setPattern("(.*)\\;\\ path");
     rx.indexIn(t);
    remember_token=rx.cap( 1 );
    qDebug()<<remember_token;
}
