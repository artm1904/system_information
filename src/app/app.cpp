#include "app.h"

#include <QGuiApplication>
#include <QScreen>
#include <QStyle>

#include "ui_app.h"

MainWindowImpl::MainWindowImpl(QWidget *parent) : QMainWindow(parent), ui(new Ui::App) {
    ui->setupUi(this);

    init();
}

MainWindowImpl::~MainWindowImpl() { delete ui; }

void MainWindowImpl::init() {
    // 3. Используем современный API для получения геометрии экрана
    const QRect availableGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), availableGeometry));
    // 4. Устанавливаем иконку из ресурсов
    setWindowIcon(QIcon(":/app_icon.png"));
}
