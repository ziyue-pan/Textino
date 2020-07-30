#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QFont>
#include <QString>
#include <QSettings>
#include <QCoreApplication>

class ConfigManager {
    
private:
    // default configuration file path
    const QString config_path = QCoreApplication::applicationDirPath() 
                                    + "/config.ini";

    QSettings *settings;    // default setting class pointer
    QString consolas;       // default font family
    QString fira_code;

    QString font_family;    // current font family
    int font_size;          // current font size
    bool font_italic;       // italic
    bool font_bold;         // bold
    bool font_underline;    // underline
    bool font_strike;       // strike

    void WriteDefault();    // default settings

public:
    ConfigManager();
    ~ConfigManager();

    // set font parameters to settings file according to new font
    void ModifyFont(QFont &given_font);
    QFont GetFont();        // get current font parameters
    QFont GetDefaultFont(); // get default font parameters

};

#endif
