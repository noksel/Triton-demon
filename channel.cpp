#include "channel.h"

channel::channel(QObject *parent) :
    QObject(parent)
{
}

channel::channel(QString channelId)
{
    ID=channelId;
    time="";

}

bool channel::isEnabled() // where "enabled" sets?? What it means?
{
    if(enabled=="1")
        return true;
     else
        return false;

}

QString channel::getID()
{
    return ID;
}

QString channel::getTmprt()
{
    return temperature;
}

QString channel::getTime()
{
    return time;
}

QString channel::getName()
{
    return name;
}

QString channel::getAssignedAs()
{
    return assignedAs;
}


bool channel::setChData(QString str)
{

     QRegExp rx;

    QString t_time;


/*channel 1; name: PT2 Head; calibration: C:/Oxford Instruments/Thermometry Calibration Files/4K Head Sensor/X71590_4K_head.cof;
 enabled: 0; assigned as: not assigned; time: 1342430730.0; resistance: 68.299; temperature: 301.893;*/
    rx.setPattern(".*time: (.*)\\;\\ resistance");
    rx.indexIn(str);
    t_time=rx.cap( 1 );

    if (t_time!=time)
    {

     rx.setPattern( ".*name: (.*)\\;\\ calibration" );
     rx.indexIn(str);
     name=rx.cap( 1 );

     rx.setPattern(".*calibration: (.*)\\;\\ enabled");
     rx.indexIn(str);
     calibration=rx.cap( 1 );

     rx.setPattern(".*enabled: (.*)\\;\\ assigned as");
     rx.indexIn(str);
     enabled=rx.cap( 1 );

     rx.setPattern(".*assigned as: (.*)\\;\\ time");
     rx.indexIn(str);
     assignedAs=rx.cap( 1 );

     rx.setPattern(".*time: (.*)\\;\\ resistance");
     rx.indexIn(str);
     time=rx.cap( 1 );

     rx.setPattern(".*resistance: (.*)\\;\\ temperature");
     rx.indexIn(str);
     resistance=rx.cap( 1 );

     rx.setPattern(".*temperature: (.*)\\;");
     rx.indexIn(str);
     temperature=rx.cap( 1 );


    return true;
    }

    return false;

  /* QStringList lstKV =str.split(";");

   for(int i=1;i<lstKV.count()-1;i++) // -1 because  " temperature: 301.893", "")
   {
      tmp=lstKV[i].trimmed();

      data[tmp.split(":")[0].trimmed()]=tmp.split(":")[1].trimmed();

   }
   QMap<QString,QString>::const_iterator i = data.constBegin();

   while(i!=data.constEnd())
   {

       qDebug()<<i.key()<<i.value();
       i++;

   }
*/
}


