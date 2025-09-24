#include "app.h"

#include <QGuiApplication>
#include <QScreen>
#include <QStyle>

#include "ui_app.h"

MainWindowImpl::MainWindowImpl(QWidget *parent)
    : QMainWindow(parent), ui(std::make_unique<Ui::App>()) {
    // Создаем экземпляр страницы. `this` в качестве родителя
    // гарантирует, что страница будет удалена вместе с главным окном.
    dashboardPage = new DashboardPage(this);

    ui->setupUi(this);

    init();
}


MainWindowImpl::~MainWindowImpl() = default;

void MainWindowImpl::init() {
    // 3. Используем современный API для получения геометрии экрана
    const QRect availableGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), availableGeometry));
    // 4. Устанавливаем иконку из ресурсов
    setWindowIcon(QIcon(":/app_icon.png"));

    ui->pageStacked->addWidget(dashboardPage);

    on_dashBtn_clicked();
}


void MainWindowImpl::pageClick(QPushButton *btn, QWidget *w, QString title)
{
    // all button checked false
    foreach (QPushButton *b, ui->sidebar->findChildren<QPushButton*>())
        b->setChecked(false);
    btn->setChecked(true); // clicked button set active style
    

    ui->pageTitle->setText(title);
    ui->pageStacked->setCurrentWidget(w);
}

void MainWindowImpl::on_dashBtn_clicked()
{
    pageClick(ui->dashBtn, dashboardPage, tr("Dashboard"));
}
