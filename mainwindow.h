#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qt/qhttp.h>
#include <QDate>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    QString curTrSes;  //текущая сессия тритона
    QString remember_token; // cookie для доступа
    QString email;
    QString pass;
    QHttp*m_hp;
    QHttp* m_http;
    Ui::MainWindow *ui;
public slots:
    void sendHTTP();
    void httpRequestFinished(int, bool);
    void createNewTrSess();
    void getCurTrSes(int, bool);
    void getToken(QHttpResponseHeader);
};

#endif // MAINWINDOW_H
