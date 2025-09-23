#pragma once

#include <QWidget>

namespace Ui {
class LineBar;

}  // namespace Ui

class LineBar : public QWidget {
    Q_OBJECT

   public:
    explicit LineBar(QString title, QWidget *parent = nullptr);
    ~LineBar();

   public slots:
    void SetValue(int value, QString text, QString totalText);

   private:
    Ui::LineBar *ui;
};
