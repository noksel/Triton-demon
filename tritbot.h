#ifndef TRITBOT_H
#define TRITBOT_H

#include <QObject>
#include <Qt/qhttp.h>
#include <QDebug>
#include <QDate>

class TritBot : public QObject
{
    Q_OBJECT
public:
    explicit TritBot(QObject *parent = 0);
    int login(QString login, QString Pswd);
    void crteNwSession();
    void sendData(int, int);
    ~TritBot();
private:

    QString remember_token; // cookie для доступа
    QString curTrSes;
    QHttp* m_http;
    QHttp* m_hp;
    void getLastSess();
    
signals:
    void ChangedStatus(QString);
    
public slots:
    void pringRespons(int,bool);
    void getCurTrSes(int,bool);
    void getToken(QHttpResponseHeader resp);
};

#endif // TRITBOT_H
