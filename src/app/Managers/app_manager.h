#pragma once

#include <QObject>
#include <QSettings>
#include <QTranslator>
#include <memory>

#include "Utils/file_util.h"

#define THEME_PROP "ThemeName"
#define LANG_PROP "Language"

class AppManager : public QObject {
    Q_OBJECT

   public:
    std::shared_ptr<AppManager> Instance();

    QString GetLanguageCode();
    void SetLanguage(QString value);
    QMap<QString, QString> GetLanguageList();
    void LoadLanguageList();

    QString GetThemeName() const;
    void SetThemeName(const QString &value);
    QMap<QString, QString> GetThemeList() const;
    void LoadThemeList();

    QSettings *GetStyleValues() const;
    QString GetStylesheetFileContent() const;
    void UpdateStylesheet();

   signals:
    void ChangedTheme();

   private:
    explicit AppManager(QObject *parent = nullptr);
    static std::shared_ptr<AppManager> m_instance;

    QTranslator m_translator;
    QString m_configPath;
    QString m_themeName;
    QSettings *m_settings;
    QSettings *m_styleValues;
    QMap<QString, QString> m_languageList;
    QMap<QString, QString> m_themeList;
    QString m_stylesheetFileContent;
};