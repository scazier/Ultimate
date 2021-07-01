#include "setting_manager.h"

SettingManager::SettingManager()
{
    mConfigPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    mSettings = new QSettings(QString("%1/settings.ini").arg(mConfigPath), QSettings::IniFormat);
}

SettingManager *SettingManager::instance = nullptr;

SettingManager* SettingManager::ins()
{
    if (! instance) {
        instance = new SettingManager;
    }
    return instance;
}

QString SettingManager::getConfigPath() const
{
    return mConfigPath;
}

void SettingManager::setLanguage(const QString &value)
{
    mSettings->setValue(SettingKeys::Language, value);
}

QString SettingManager::getLanguage() const
{
    return mSettings->value(SettingKeys::Language, "en").toString();
}

void SettingManager::setThemeName(const QString &value)
{
    mSettings->setValue(SettingKeys::ThemeName, value);
}

QString SettingManager::getThemeName() const
{
    return "default"; //mSettings->value(SettingKeys::ThemeName, "default").toString();
}

void SettingManager::setDiskName(const QString &value)
{
    mSettings->setValue(SettingKeys::DiskName, value);
}

QString SettingManager::getDiskName() const
{
    return mSettings->value(SettingKeys::DiskName, "").toString();
}

void SettingManager::setStartPage(const QString &value)
{
    mSettings->setValue(SettingKeys::StartPage, value);
}

QString SettingManager::getStartPage() const
{
    return mSettings->value(SettingKeys::StartPage, QObject::tr("Antivirus")).toString();
}

void SettingManager::setCpuAlertPercent(const int value)
{
    mSettings->setValue(SettingKeys::CPUAlertPercent, value);
}

int SettingManager::getCpuAlertPercent() const
{
    return mSettings->value(SettingKeys::CPUAlertPercent, 0).toInt();
}

void SettingManager::setMemoryAlertPercent(const int value)
{
    mSettings->setValue(SettingKeys::MemoryAlertPercent, value);
}

int SettingManager::getMemoryAlertPercent() const
{
    return mSettings->value(SettingKeys::MemoryAlertPercent, 0).toInt();
}

void SettingManager::setDiskAlertPercent(const int value)
{
    mSettings->setValue(SettingKeys::DiskAlertPercent, value);
}

int SettingManager::getDiskAlertPercent() const
{
    return mSettings->value(SettingKeys::DiskAlertPercent, 0).toInt();
}

void SettingManager::setAppQuitDialogDontAsk(const bool value)
{
    mSettings->setValue(SettingKeys::AppQuitDialogDontAsk, value);
}

bool SettingManager::getAppQuitDialogDontAsk() const
{
    return mSettings->value(SettingKeys::AppQuitDialogDontAsk, false).toBool();
}

void SettingManager::setAppQuitDialogChoice(const QString &value)
{
    mSettings->setValue(SettingKeys::AppQuitDialogChoice, value);
}

QString SettingManager::getAppQuitDialogChoice() const
{
    return mSettings->value(SettingKeys::AppQuitDialogChoice, "close").toString();
}

QString SettingManager::getSpeedTestHost() const
{
    return QString("http://bouygues.testdebit.info");
}

QString SettingManager::getUploadTestFile() const
{
    return QDir::currentPath()+"/static/speedtestUpload.iso";
}
