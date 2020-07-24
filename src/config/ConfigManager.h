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
    const int default_font_size = 11;
    const QString default_font_family = "Consolas";

    QSettings *settings;    // default setting class pointer
    QString consolas;       // default font family
    QString fira_code;

    QString font_family;    // current font family
    int font_size;          // current font size

    // int tab_size;
    // bool dark_mode;

    void WriteDefault();

public:
    ConfigManager();
    ~ConfigManager();

    void ModifyFontFamily(QString font_family);
    void ModifyFontSize(int font_size);
    // void ModifyDarkMode();
    // void ModifyTabSize();

    QString GetDefaultFontFamily();
    int GetDefaultFontSize();
    QString GetFontFamily();
    int GetFontSize();
    // bool GetDarkMode();
    // int GetTabSize();

};





#endif
