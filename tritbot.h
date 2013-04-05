#ifndef TRITBOT_H
#define TRITBOT_H

#include <QObject>
#include <Qt/qhttp.h>
#include <QDebug>
#include <QDate>
#include "channel.h"

class TritBot : public QObject
{
    Q_OBJECT
public:
    explicit TritBot(QObject *parent = 0);
    explicit TritBot(QString host,int port,QObject *parent = 0);
    int login(QString login, QString Pswd);


    ~TritBot();
private:

    QString remember_token; // cookie для доступа
    QString m_host;
    int m_port;
    QString curTrSes;
    QHttp* m_http_Token;
    QHttp* m_http_CurtrSes;
    QHttp* m_http_point;

    void getLastSess();
    
signals:
    void ChangedStatus(QString);
    
public slots:
    void sendChannelData(channel*);
    void crteNwSession();
    void pringRespons(int,bool);
    void getCurTrSes(int,bool);
    void getToken(QHttpResponseHeader resp);
};

#endif // TRITBOT_H
