#ifndef COMMONHELPER_H
#define COMMONHELPER_H

#include <QString>
#include <QMetaEnum>
#include "qextserialporconfig.h"

class CommonHelper
{
public:
    CommonHelper();
    ~CommonHelper();

    static int GetValueFromEnum(QString, QString);
};

#endif // COMMONHELPER_H
