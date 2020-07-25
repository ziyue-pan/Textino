#include "ConfigManager.h"

#include <QFile>
#include <QFont>
#include <QFontDatabase>


//* ConfigManager class constructor
ConfigManager::ConfigManager() {
    // set default consolas font
    int consolas_id = QFontDatabase::addApplicationFont(":/fonts/Consolas.ttf");
    consolas = QFontDatabase::applicationFontFamilies(consolas_id).at(0);

    // set default firacode font
    int fira_code_id = QFontDatabase::addApplicationFont(":/fonts/FiraCode.ttf");
    fira_code = QFontDatabase::applicationFontFamilies(fira_code_id).at(0);

    if(QFile(config_path).exists()) {
        try {
            settings = new QSettings(config_path, QSettings::IniFormat);
            settings->beginGroup("General");
            font_size = settings->value("font_size", font_size).toInt();
            font_family = settings->value("font_family", font_family).toString();
            font_italic = settings->value("font_italic", font_italic).toBool();
            font_bold = settings->value("font_bold", font_bold).toBool();
            font_underline = settings->value("font_underline", font_underline).toBool();
            font_strike = settings->value("font_strike", font_strike).toBool();

            settings->endGroup();

        } catch (...) {
            WriteDefault();
        }
    } else {
        WriteDefault();
    }
}

ConfigManager::~ConfigManager() {

}




void ConfigManager::WriteDefault() {
    settings = new QSettings(config_path, QSettings::IniFormat);

    // write default setting item
    settings->beginGroup("General");
    settings->setIniCodec("UTF-8");
    settings->setValue("font_size", 12);
    settings->setValue("font_family", fira_code);
    settings->setValue("font_italic", false);
    settings->setValue("font_bold", false);
    settings->setValue("font_underline", false);
    settings->setValue("font_strike", false);
    settings->endGroup();

    // sync to file
    settings->sync();

    font_size = 12;
    font_family = "Fira Code";
    font_italic = font_bold = font_strike = font_underline = false;
}


void ConfigManager::ModifyFont(QFont &given_font) {
    font_family = given_font.family();
    font_size = given_font.pointSize();
    font_italic = given_font.italic();
    font_bold = given_font.bold();
    font_underline = given_font.underline();
    font_strike = given_font.strikeOut();

    // write modified setting item
    settings->beginGroup("General");
    settings->setIniCodec("UTF-8");
    settings->setValue("font_size", font_size);
    settings->setValue("font_family", font_family);
    settings->setValue("font_italic", font_italic);
    settings->setValue("font_bold", font_bold);
    settings->setValue("font_underline", font_underline);
    settings->setValue("font_strike", font_strike);
    settings->endGroup();

    // sync to file
    settings->sync();
}

QFont ConfigManager::GetFont() {
    QFont font;
    font.setFamily(font_family);
    font.setPointSize(font_size);
    font.setItalic(font_italic);
    font.setBold(font_bold);
    font.setUnderline(font_underline);
    font.setStrikeOut(font_strike);
    return font;
}

QFont ConfigManager::GetDefaultFont() {
    QFont font;
    font.setFamily("Consolas");
    font.setPointSize(11);
    font.setBold(true);
    font.setItalic(false);
    font.setStrikeOut(false);
    font.setUnderline(false);
    return font;
}





