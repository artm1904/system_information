#include "circlebar.h"

#include "Managers/app_manager.h"
#include "ui_circlebar.h"

CircleBar::~CircleBar() = default;

CircleBar::CircleBar(QString title, QStringList colors, QWidget *parent)
    : QWidget(parent),
      ui(std::make_unique<Ui::CircleBar>()),
      m_colors(colors),
      // QChart does not have a QObject* parent constructor, so we create it without a parent first.
      m_chart(new QChart()),
      m_chartView(new QChartView(this)),
      m_series(new QPieSeries(this)) {
    ui->setupUi(this);
    ui->chartTitle->setText(title);
    // Now we set the parent for m_chart to ensure automatic memory management, because in
    // costructor it cann't take QWidget*
    m_chart->setParent(this);

    Init();
}

void CircleBar::Init() {
    // series settings
    m_series->setHoleSize(0.67);
    m_series->setPieSize(165);
    m_series->setPieStartAngle(-115);
    m_series->setPieEndAngle(115);
    m_series->setLabelsVisible(false);

    m_series->append("1", 0);
    m_series->append("2", 0);

    m_series->slices().first()->setBorderColor("transparent");  // for CPU load
    m_series->slices().last()->setBorderColor("transparent");   // for free CPU resources

    QConicalGradient gradient;
    gradient.setAngle(115);
    for (int i = 0; i < m_colors.count(); ++i) {
        gradient.setColorAt(i, QColor(m_colors.at(i)));
    }
    m_series->slices().first()->setBrush(gradient);

    // chart settings
    m_chart->setBackgroundBrush(QBrush("transparent"));
    m_chart->setContentsMargins(-15, -18, -15, -60);
    m_chart->addSeries(m_series);
    m_chart->legend()->hide();

    // chartview settings
    m_chartView->setRenderHint(QPainter::Antialiasing);

    ui->chartLayout->insertWidget(1, m_chartView);  // insert set up widget in QVBoxLayout from .iu

    // Set the start color
    m_series->slices().last()->setColor(
        AppManager::Instance()->GetStyleValues()->value("@pageContent").toString());
    m_chartView->setBackgroundBrush(QColor(
        AppManager::Instance()->GetStyleValues()->value("@circleChartBackgroundColor").toString()));


    // We need to get the raw pointer from the shared_ptr for connect
    connect(AppManager::Instance().get(), &AppManager::ChangedTheme, this, [this]() {
        m_chartView->setBackgroundBrush(QColor(AppManager::Instance()
                                                   ->GetStyleValues()
                                                   ->value("@circleChartBackgroundColor")
                                                   .toString()));

        m_series->slices().last()->setColor(AppManager::Instance()
                                                ->GetStyleValues()
                                                ->value("@pageContent")
                                                .toString());  // trail color
    });
}

void CircleBar::SetValue(int value, QString valueText) {
    m_series->slices().first()->setValue(value);
    m_series->slices().last()->setValue(100 - value);

    ui->chartValue->setText(valueText);
}