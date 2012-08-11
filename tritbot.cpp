#include "tritbot.h"

TritBot::TritBot(QObject *parent) :
    QObject(parent)
{
    m_hp = new QHttp("localhost",3000);
    m_http = new QHttp("localhost",3000);
    login(QString ("ddd"), QString ("foobar"));
    getLastSess();

}

int TritBot::login(QString email, QString pass)
{

    connect(m_http, SIGNAL(responseHeaderReceived(QHttpResponseHeader)),this, SLOT(getToken(QHttpResponseHeader)));

    QHttpRequestHeader header("POST", "/sessions");
    header.setValue("Host", "localhost:3000");
    header.setValue( "Referer", "http://localhost:3000/sessions");
    header.setContentType("application/x-www-form-urlencoded");
    QString par="utf8=%E2%9C%93&authenticity_token=AXtKzkGTB5yO6UAkRYqdrYxueQiT%2BHyqQ%2BB0SAtn5Mk%3D";
            par+="&session[email]="+email;
            par+="&session[password]="+pass+"&commit=Sign In";
    QByteArray sg (par.toUtf8());
     header.setContentLength(sg.count());

     m_http->request(header,sg);
     return 0;
}

void TritBot::crteNwSession()
{
    connect( m_http, SIGNAL(requestFinished(int, bool)),this, SLOT(pringRespons(int,bool)));
    QDate d;
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
    m_http->request(header,sg);
    getLastSess();
}

void TritBot::sendData(int x, int y)
{

    QString sx,sy;
    sx=QString::number(x);
    sy=QString::number(y);
    connect( m_http, SIGNAL(requestFinished(int, bool)),this, SLOT(pringRespons(int,bool)));
    QHttpRequestHeader header("POST", "/points");
    header.setValue("Host", "localhost:3000");
    header.setValue( "Referer", "http://localhost:3000/points");
    header.setValue( "Cookie", "remember_token="+remember_token);
    header.setContentType("application/x-www-form-urlencoded");
    QString par="utf8=%E2%9C%93&authenticity_token=AXtKzkGTB5yO6UAkRYqdrYxueQiT%2BHyqQ%2BB0SAtn5Mk%3D&point%5Bx%5D="+sx+"&point%5By%5D="+sy+
                    "&point[triton_session_id]="+curTrSes+"&commit=Create+Point";
    QByteArray sg (par.toUtf8());

    header.setContentLength(sg.count());
    m_http->request(header,sg);
}

TritBot::~TritBot()
{
    delete m_http;
    delete m_hp;
}

void TritBot::getLastSess()
{


    connect( m_hp, SIGNAL(requestFinished(int, bool)),this, SLOT(getCurTrSes(int,bool)));

    m_hp->get("/triton_sessions/last");
}

void TritBot::getToken(QHttpResponseHeader resp)
{
    QString t= resp.toString();
    QRegExp rx( ".*remember_token\\=(.*)Set-Cookie.*" );
    rx.indexIn(t);
    t=rx.cap( 1 );
    rx.setPattern("(.*)\\;\\ path");
     rx.indexIn(t);
    remember_token=rx.cap( 1 );
    qDebug()<<remember_token;
    emit ChangedStatus(QString("login ok"));

    disconnect(m_http, SIGNAL(responseHeaderReceived(QHttpResponseHeader)),this,SLOT(getToken(QHttpResponseHeader)));
}

void TritBot::getCurTrSes(int,bool)
{
    QString t=m_hp->readAll();

    QRegExp rx( ".*(\\d+)\\\"\\>red.*" );
     rx.indexIn(t);
    curTrSes=rx.cap( 1 );
     qDebug()<<curTrSes;
     emit ChangedStatus(QString("Last session:"+curTrSes));
     disconnect( m_hp, SIGNAL(requestFinished(int, bool)),this, SLOT(getCurTrSes(int,bool)));
}

void TritBot::pringRespons(int, bool)
{
    qDebug()<<m_http->readAll();
}
