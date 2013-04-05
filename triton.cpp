#include "triton.h"

triton::triton(QObject *parent) :
    QObject(parent)
{
    qsrand((uint)QTime::currentTime().msec());

    tm = new QTimer(this);
    m_pTcpSocket = new QTcpSocket(this);

    quantityCh=16;
    for (int i=0;i<quantityCh;i++)
    {

        channels["channel "+QString::number(i+1)]=new channel("channel "+QString::number(i+1));

    }

    connect(tm,SIGNAL(timeout()),this,SLOT(sendRequest()));
    m_pTcpSocket->connectToHost("192.168.199.29", 22518);

    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));

}

triton::triton(QString host, int port, QObject *parent) :
    QObject(parent)
{
    qsrand((uint)QTime::currentTime().msec());

    tm = new QTimer(this);
    m_pTcpSocket = new QTcpSocket(this);

    quantityCh=16;
    for (int i=0;i<quantityCh;i++)
    {

        channels["channel "+QString::number(i+1)]=new channel("channel "+QString::number(i+1));

    }

    connect(tm,SIGNAL(timeout()),this,SLOT(sendRequest()));
    m_pTcpSocket->connectToHost(host, port);

    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
}


/*triton::triton(int n)
{
     quantityCh=n;
    for (int i=0;i<quantityCh;i++)
    {

        channels["channel "+QString::number(i+1)]=new channel("channel "+QString::number(i+1));

    }

    //  TODO: write ... !!!

}*/

void triton::sendRequest()
{
    QString sD = "thermometry\r\n";
    qDebug()<<"!!!data send!!!";
    m_pTcpSocket->write(sD.toUtf8());
}


void triton::setData(QString str)
{
      QRegExp rx;
    QStringList lst=str.split("\n");

    for(int i=2;i<lst.count()-3;i++)
    {
       rx.setPattern("(.*)\\;\\ name");
       rx.indexIn(lst[i]);
       if(channels[rx.cap( 1 )]->setChData(lst[i]))
       {
           emit channelChanged(channels[rx.cap( 1 )]);
       }
    }

   /* QMap<QString,channel*>::const_iterator i = channels.constBegin();
channel *ch;
    while(i!=channels.constEnd())
    {
        ch=i.value();
        if(ch->isEnabled())

          qDebug()<<ch->getID()<<ch->getName()<<ch->getTmprt();

        i++;
    }*/

}

void triton::slotConnected()
{
    qDebug()<<"Received the connected() signal";

}

void triton::slotReadyRead()
{

    qDebug()<<"!!!read!!!";
    setData(m_pTcpSocket->readAll());
}

void triton::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
           "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                        "The host was not found." :
                        err == QAbstractSocket::RemoteHostClosedError ?
                        "The remote host is closed." :
                        err == QAbstractSocket::ConnectionRefusedError ?
                        "The connection was refused." :
                        QString(m_pTcpSocket->errorString())
                       );
   // qDebug()<<strError;
}

void triton::startAcquisition()
{
    tm->start(5000); //uncomment when it's done

  /* // TODO: delete all below. this is a test for send channel data.
qDebug()<<"startAcquisition";
    channel* tmpch= new channel("channel 1");




        QString str="channel 1; name: PT2 Plate; calibration: C:/Oxford Instruments/Thermometry Calibration Files/4K Plate Sensor/X71591_4K_plate.cof; enabled: 1; assigned as: 4K channel; time: ";




         str.append(QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch()/1000)); //1344835597.0
        str.append("; resistance: 46739; temperature: ");
        str.append(QString::number(qrand()%100/10.0+10.0)+";");//20.5;
        if (tmpch->setChData(str))
        {
            emit channelChanged(tmpch);
        }
tmpch= new channel("channel 2");
     str="channel 2; name: PT2 Plate; calibration: C:/Oxford Instruments/Thermometry Calibration Files/4K Plate Sensor/X71591_4K_plate.cof; enabled: 1; assigned as: 4K channel; time: ";
     str.append(QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch()/1000)); //1344835597.0
    str.append("; resistance: 46739; temperature: ");
    str.append(QString::number(qrand()%100/10.0+10.0)+";");//20.5;
    if (tmpch->setChData(str))
    {
        emit channelChanged(tmpch);
    }

*/

}

