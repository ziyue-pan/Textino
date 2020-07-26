#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QFont>
#include <QString>
#include <QSettings>
#include <QCoreApplication>

class ConfigManager
{
private:
    // default configuration file path
    const QString config_path = QCoreApplication::applicationDirPath() + "/config.ini";

    QSettings *settings;    // default setting class pointer
    QString consolas;       // default font family
    QString fira_code;

    QString font_family;    // current font family
    int font_size;          // current font size
    bool font_italic;
    bool font_bold;
    bool font_underline;
    bool font_strike;

    // int tab_size;
    // bool dark_mode;

    void WriteDefault();

public:
    ConfigManager();
    ~ConfigManager();

    void ModifyFont(QFont &given_font);
    QFont GetFont();
    QFont GetDefaultFont();

};

#endif
