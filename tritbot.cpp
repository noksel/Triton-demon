#include "tritbot.h"

TritBot::TritBot(QObject *parent) :
    QObject(parent)
{
   // m_host="tritonmon1.herokuapp.com";
    m_host="192.168.199.38";
   m_port=3000;

    m_http_CurtrSes = new QHttp(m_host,m_port);
    connect( m_http_CurtrSes, SIGNAL(requestFinished(int, bool)),this, SLOT(getCurTrSes(int,bool)));

    m_http_Token = new QHttp(m_host,m_port);
    connect(m_http_Token, SIGNAL(responseHeaderReceived(QHttpResponseHeader)),this, SLOT(getToken(QHttpResponseHeader)));

    m_http_point = new QHttp(m_host,m_port);
    connect( m_http_point, SIGNAL(requestFinished(int, bool)),this, SLOT(pringRespons(int,bool)));

    login(QString ("gnoksel@gmail.com"), QString ("foobar"));
    getLastSess();

}

TritBot::TritBot(QString host, int port, QObject *parent):
    QObject(parent)
{
    // m_host="tritonmon1.herokuapp.com";
     m_host=host;
    m_port=port;

     m_http_CurtrSes = new QHttp(m_host,m_port);
     connect( m_http_CurtrSes, SIGNAL(requestFinished(int, bool)),this, SLOT(getCurTrSes(int,bool)));

     m_http_Token = new QHttp(m_host,m_port);
     connect(m_http_Token, SIGNAL(responseHeaderReceived(QHttpResponseHeader)),this, SLOT(getToken(QHttpResponseHeader)));

     m_http_point = new QHttp(m_host,m_port);
     connect( m_http_point, SIGNAL(requestFinished(int, bool)),this, SLOT(pringRespons(int,bool)));

     login(QString ("gnoksel@gmail.com"), QString ("foobar"));
     getLastSess();
}

int TritBot::login(QString email, QString pass)
{


    QHttpRequestHeader header("POST", "/sessions");
    header.setValue("Host", m_host);
   // header.setValue( "Referer", "tritonmon1.herokuapp.com/sessions");
    header.setContentType("application/x-www-form-urlencoded");
    QString par="utf8=%E2%9C%93&authenticity_token=AXtKzkGTB5yO6UAkRYqdrYxueQiT%2BHyqQ%2BB0SAtn5Mk%3D";
            par+="&session[email]="+email;
            par+="&session[password]="+pass+"&commit=Sign In";
    QByteArray sg (par.toUtf8());
     header.setContentLength(sg.count());

     m_http_Token->request(header,sg);
     return 0;
}

void TritBot::crteNwSession()
{
   // connect( m_http, SIGNAL(requestFinished(int, bool)),this, SLOT(pringRespons(int,bool)));
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
    header.setValue("Host", m_host);
   // header.setValue( "Referer", "tritonmon1.herokuapp.com/triton_sessions");
    header.setValue( "Cookie", "remember_token="+remember_token);
    header.setContentType("application/x-www-form-urlencoded");
    header.setContentLength(sg.count());
    qDebug()<<"crt new";
    m_http_point->request(header,sg);

}



TritBot::~TritBot()
{
    delete m_http_Token;
    delete m_http_point;
    delete m_http_CurtrSes;
}

void TritBot::getLastSess()
{

    m_http_CurtrSes->get("/triton_sessions/last");
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
}

void TritBot::getCurTrSes(int,bool)
{
    QString t=m_http_CurtrSes->readAll();

    QRegExp rx( ".*(\\d+)\\\"\\>red.*" );
     rx.indexIn(t);
    curTrSes=rx.cap( 1 );
     qDebug()<<curTrSes;
     emit ChangedStatus(QString("Last session:"+curTrSes));


}

void TritBot::pringRespons(int, bool)
{
    qDebug()<<m_http_Token->readAll();
    getLastSess();
}

void TritBot::sendChannelData(channel* ch)
{
    QString sx,sy,channelIdn;
    sx=ch->getTime();
    sy=ch->getTmprt();
    channelIdn=ch->getID();

    QHttpRequestHeader header("POST", "/points");
    header.setValue("Host", m_host);
    //header.setValue( "Referer", "tritonmon1.herokuapp.com/points");
    header.setValue( "Cookie", "remember_token="+remember_token);
    header.setContentType("application/x-www-form-urlencoded");
    QString par="utf8=%E2%9C%93&authenticity_token=AXtKzkGTB5yO6UAkRYqdrYxueQiT%2BHyqQ%2BB0SAtn5Mk%3D&point%5Bx%5D="+sx+"&point%5By%5D="+sy+
                    "&point[triton_session_id]="+curTrSes+"&point[channel_name]="+channelIdn+"&commit=Create+Point";
    QByteArray sg (par.toUtf8());

    header.setContentLength(sg.count());
    m_http_point->request(header,sg);
       emit ChangedStatus("send data X:"+sx+" Y:"+sy+"channel:"+channelIdn);

}
