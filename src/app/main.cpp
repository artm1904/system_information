#include <QApplication>
#include <QDebug>

#include "app.h"

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QString level;

    switch (type) {
        case QtDebugMsg:
            level = "Debug";
            break;
        case QtInfoMsg:
            level = "Info";
            break;
        case QtWarningMsg:
            level = "Warning";
            break;
        case QtCriticalMsg:
            level = "Critical";
            break;
        case QtFatalMsg:
            level = "Fatal";
            break;
        default:
            level = "Unknown";
            break;
    }

    if (type != QtWarningMsg) {
        QString message = QString("[%1][%2]%3")
                              .arg(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"))
                              .arg(level)
                              .arg(msg);

        static QString logPath =
            QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/log";

        QDir().mkdir(logPath);

        QFile logFile(logPath + "artm1904.log");

        QIODevice::OpenMode openMode;

        if (logFile.size() > (1L << 20)) {
            openMode = QIODevice::WriteOnly | QIODevice::Truncate;
        } else {
            openMode = QIODevice::WriteOnly | QIODevice::Append;
        }

        if (logFile.open(openMode)) {
            QTextStream stream(&logFile);
            stream << message << "\n";
            logFile.close();
        }
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    qApp->setApplicationName("artm1904");
    qApp->setApplicationDisplayName("artm1904");
    qApp->setApplicationVersion("0.0.1");
    qApp->setWindowIcon(QIcon(":/static/logo.png"));

    qInstallMessageHandler(messageHandler);

    MainWindowImpl w;
    w.show();

    return app.exec();
}
