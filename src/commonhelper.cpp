#include "commonhelper.h"

CommonHelper::CommonHelper()
{

}

CommonHelper::~CommonHelper()
{

}

int CommonHelper::GetValueFromEnum(QString enumName, QString name)
{
    QMetaObject metaObject = QextSerialPorConfig::staticMetaObject;
    QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator(enumName.toLatin1()));
    return metaEnum.keysToValue(name.toLatin1());
}
