#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include <QDebug>

class channel : public QObject
{
    Q_OBJECT
private:
    QString ID;
    QString name;
    QString calibration;
    QString enabled;
    QString assignedAs;
    QString time;
    QString resistance;
    QString temperature;
    bool available;

public:
    explicit channel(QObject *parent = 0);
    channel(QString channelId);
    bool isEnabled();    // Включён ли в отображение.-отключается в стойке в программе  .

    QString getID();
    QString getTmprt();
    QString getTime();
    QString getName();
    QString getAssignedAs();
    bool setChData(QString str);
signals:

public slots:

    
};

#endif // CHANNEL_H
