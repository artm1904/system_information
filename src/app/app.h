#pragma once

#include <QMainWindow>
#include <QDateTime>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QTextStream>



namespace Ui {
    class App;
}



class App : public QMainWindow {
    Q_OBJECT

   public:
    explicit App(QWidget *parent = nullptr);
    ~App();


    private:
    Ui::App *ui;



    private slots:
    void init();
   

};