#include "commonhelper.h"

static QFile LogFile;

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

/**
****************************************************************************************************************
@ description:�Ndata�g�Jlog��
@ param:char* string: ���g�J������
@ author: Yu-Hua Tseng
@ date: 2010.05.22
@ version: 1.0
@ Histroy: Initial version.
****************************************************************************************************************
*/
void CommonHelper::Log(char* string)
{
    bool isOpened=false;

    if(!LogFile.isOpen())
    {
        if(CommonHelper::InitLogFile())
        {
            isOpened=true;
        }
    }
    else
    {
        isOpened=true;
    }

    if(isOpened)
    {
        QDateTime DT;
        QTextStream out(&LogFile);
        out <<"["<<DT.currentDateTime().toString("yyyy.MM.dd hh:mm:ss").toLocal8Bit().data()<< "]"<<":"<<string<<"\n";
    }
}

/**
****************************************************************************************************************
@ description:���l��log�� (QFile)
@ author: Yu-Hua Tseng
@ date: 2010.05.23
@ version: 1.0
@ Histroy: Initial version.
2010.06.04: �ץ�log�ɦs�����|
****************************************************************************************************************
*/
bool CommonHelper::InitLogFile()
{
    bool result=false;

    LogFile.setFileName("Log.QextSerialEx.txt");

    if(LogFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QString qtVersion=QT_VERSION_STR;
        qtVersion="Qt version=" + qtVersion;
        CommonHelper::Log((char*)qtVersion.toLatin1().data());
        CommonHelper::Log((char*)"**********************************Log Start**********************************\n");
        result=true;
    }

    return result;
}
