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
            settings->endGroup();

            if(!(font_size>=8 && font_size <= 48))
                ModifyFontSize(14);

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
    settings->endGroup();

    // sync to file
    settings->sync();
}


void ConfigManager::ModifyFontFamily(QString font_family) {
    this->font_family = font_family;
    settings->beginGroup("General");
    settings->setValue("font_family", font_family);
    settings->endGroup();
    settings->sync();
}

void ConfigManager::ModifyFontSize(int font_size) {
    this->font_size = font_size;
    settings->beginGroup("General");
    settings->setValue("font_size", font_size);
    settings->endGroup();
    settings->sync();
}

QString ConfigManager::GetFontFamily() {
    return font_family;
}


int ConfigManager::GetFontSize() {
    return font_size;
}

QString ConfigManager::GetDefaultFontFamily() {
    return default_font_family;
}

int ConfigManager::GetDefaultFontSize() {
    return default_font_size;
}




