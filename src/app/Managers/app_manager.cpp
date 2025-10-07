#include "app_manager.h"

#include <QApplication>
#include <QFontDatabase>
#include <QJsonArray>
#include <QJsonObject>
#include <QStandardPaths>

AppManager::AppManager(QObject *parent) : QObject(parent) {
    // font settings
    QFontDatabase::addApplicationFont(":/static/font/Ubuntu-R.ttf");

    m_configPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    m_settings = std::make_unique<QSettings>(QString("%1/settings.conf").arg(m_configPath),
                                             QSettings::NativeFormat);

    LoadLanguageList();

    LoadThemeList();

    m_themeName = m_settings->value(THEME_PROP, "default").toString();

    // TODO  сейчас файлы перевода лежат прям рядом с бинарем (.qm),  нужно их перенести в папку
    // translations
    if (m_translator.load(QString("stacer_%1").arg(GetLanguageCode()),
                          qApp->applicationDirPath() + "")) {
        //                   qApp->applicationDirPath() + "/translations")) {
        qApp->installTranslator(&m_translator);
    } else {
        qCritical() << "Translator could not load.";
    }

    m_styleValues = std::make_unique<QSettings>(
        QString(":/static/themes/%1/style/values.ini").arg(m_themeName), QSettings::NativeFormat);
}

//'Meyers' Singleton, using static value for multithreding safe (C++11)
std::shared_ptr<AppManager> AppManager::Instance() {
    static std::shared_ptr<AppManager> instance(new AppManager());
    return instance;
}

/** Language */

QString AppManager::GetLanguageCode() { return m_settings->value(LANG_PROP, "en").toString(); }

void AppManager::SetLanguage(QString value) { m_settings->setValue(LANG_PROP, value); }

QMap<QString, QString> AppManager::GetLanguageList() { return m_languageList; }

void AppManager::LoadLanguageList() {
    QJsonArray languages =
        QJsonDocument::fromJson(FileUtil::ReadStringFromFile(":/static/languages.json").toUtf8())
            .array();

    for (int i = 0; i < languages.size(); i++) {
        QJsonObject language = languages.at(i).toObject();
        m_languageList.insert(language["value"].toString(), language["text"].toString());
    }
}

/** Theme */

QString AppManager::GetThemeName() const { return m_themeName; }

void AppManager::SetThemeName(const QString &value) { m_themeName = value; }

QMap<QString, QString> AppManager::GetThemeList() const { return m_themeList; }

void AppManager::LoadThemeList() {
    QJsonArray themes =
        QJsonDocument::fromJson(FileUtil::ReadStringFromFile(":/static/themes.json").toUtf8())
            .array();

    for (int i = 0; i < themes.count(); ++i) {
        QJsonObject theme = themes.at(i).toObject();
        m_themeList.insert(theme["value"].toString(), theme["text"].toString());
    }
}

/** Style */

QSettings *AppManager::GetStyleValues() const { return m_styleValues.get(); }

QString AppManager::GetStylesheetFileContent() const { return m_stylesheetFileContent; }

void AppManager::UpdateStylesheet() {
    // read .ini file with colors and other param
    m_styleValues = std::make_unique<QSettings>(
        QString(":/static/themes/%1/style/values.ini").arg(m_themeName), QSettings::NativeFormat);

    // real .qss file with description-style
    m_stylesheetFileContent = FileUtil::ReadStringFromFile(
        QString(":/static/themes/%1/style/style.qss").arg(m_themeName));

    // replace .qss to param from .ini
    for (QString key : m_styleValues->allKeys()) {
        m_stylesheetFileContent.replace(key, m_styleValues->value(key).toString());
    }

    qApp->setStyleSheet(m_stylesheetFileContent);

    emit ChangedTheme();
}
