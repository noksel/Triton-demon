#ifndef TRITON_H
#define TRITON_H

#include <QObject>
#include <QMap>
#include "channel.h"
#include <QString>
#include <QTimer>
#include <QTcpSocket>
#include "tritbot.h"
#include <QDateTime>
class triton : public QObject
{
    Q_OBJECT
private:
    int quantityCh;
    QTcpSocket* m_pTcpSocket;
    QTimer* tm;

  QMap <QString, channel*> channels;
  void setData(QString);

public:
    explicit triton(QObject *parent = 0);
explicit triton(QString host,int port,QObject *parent = 0);
 // triton(int n);
    
signals:
  void channelChanged(channel*);
    
public slots:

 void sendRequest(); //�������� ������ �� ������� �����������
 void slotReadyRead   (); //������ �����
 void slotError       (QAbstractSocket::SocketError err); //������
 void startAcquisition(); // ������ ����
 void slotConnected   (); //���������� ����������
    
};

#endif // TRITON_H
