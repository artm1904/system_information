#pragma once

#include <QWidget>
#include <QtCharts>
#include <memory>

namespace Ui {
class CircleBar;
}  // namespace Ui

class CircleBar : public QWidget {
    Q_OBJECT

   public:
    explicit CircleBar(QString title, QStringList colors, QWidget *parent = 0);
    ~CircleBar() override;

   public slots:
    void SetValue(int value, QString valueText);

   private slots:
    void Init();

   private:
    std::unique_ptr<Ui::CircleBar> ui;

   private:
    QStringList m_colors;
    QChart *m_chart;
    QChartView *m_chartView;
    QPieSeries *m_series;

    // m_series (add data for view) -> m_charts (diagrams object for draw) -> m_chartView (widget
    // for customer)
};