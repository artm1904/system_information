#include "app.h"

#include <QGuiApplication>
#include <QScreen>
#include <QStyle>

#include "ui_app.h"

MainWindowImpl::MainWindowImpl(QWidget *parent)
    : QMainWindow(parent),
      ui(std::make_unique<Ui::App>()),
      m_appManager(AppManager::Instance()),
      m_dashboardPage(
          std::make_unique<DashboardPage>(this)) {  // set THIS class how parent for auto delete

    ui->setupUi(this);
    Init();
}

MainWindowImpl::~MainWindowImpl() = default;

void MainWindowImpl::Init() {
    
    const QRect availableGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), availableGeometry));
    
    setWindowIcon(QIcon(":/app_icon.png"));

    ui->pageStacked->addWidget(m_dashboardPage.get());

    on_dashBtn_clicked();
}

void MainWindowImpl::PageClick(QPushButton *btn, QWidget *w, QString title) {
    // all button checked false
    for (QPushButton *b : ui->sidebar->findChildren<QPushButton *>()) {
        b->setChecked(false);
    }

    btn->setChecked(true);  // clicked button set active style
    ui->pageTitle->setText(title);
    ui->pageStacked->setCurrentWidget(w);
}

void MainWindowImpl::on_dashBtn_clicked() {
    PageClick(ui->dashBtn, m_dashboardPage.get(), tr("Dashboard"));
}
