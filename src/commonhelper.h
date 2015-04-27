#ifndef COMMONHELPER_H
#define COMMONHELPER_H

#include <QString>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <QMetaEnum>
#include "qextserialporconfig.h"

class CommonHelper
{
public:
    CommonHelper();
    ~CommonHelper();

    static int GetValueFromEnum(QString, QString);
    static void Log(char*);

private:

    static bool InitLogFile();
};

#endif // COMMONHELPER_H
