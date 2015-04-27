/**
  This class encapsultes below parameters for serial port initiaation
    BaudRateType
    FlowType
    DataBitsType
    StopBitsType
    ParityType

  @author:  Yu-Hua Tseng
  @date:    2015/04/27
  @version: 1.0
  */
#ifndef QEXTSERIALPORCONFIG_H
#define QEXTSERIALPORCONFIG_H

#include <QObject>

class QextSerialPorConfig : public QObject
{
    Q_OBJECT

    Q_ENUMS(BaudRateType)
    Q_ENUMS(FlowType)
    Q_ENUMS(DataBitsType)
    Q_ENUMS(StopBitsType)
    Q_ENUMS(ParityType)

public:
    QextSerialPorConfig();
    ~QextSerialPorConfig();

    enum BaudRateType
    {
        BAUD50,                //POSIX ONLY
        BAUD75,                //POSIX ONLY
        BAUD110,
        BAUD134,               //POSIX ONLY
        BAUD150,               //POSIX ONLY
        BAUD200,               //POSIX ONLY
        BAUD300,
        BAUD600,
        BAUD1200,
        BAUD1800,              //POSIX ONLY
        BAUD2400,
        BAUD4800,
        BAUD9600,
        BAUD14400,             //WINDOWS ONLY
        BAUD19200,
        BAUD38400,
        BAUD56000,             //WINDOWS ONLY
        BAUD57600,
        BAUD76800,             //POSIX ONLY
        BAUD115200,
        BAUD128000,            //WINDOWS ONLY
        BAUD256000             //WINDOWS ONLY
    };

    enum DataBitsType
    {
        DATA_5,
        DATA_6,
        DATA_7,
        DATA_8
    };

    enum ParityType
    {
        PAR_NONE,
        PAR_ODD,
        PAR_EVEN,
        PAR_MARK,               //WINDOWS ONLY
        PAR_SPACE
    };

    enum StopBitsType
    {
        STOP_1,
        STOP_1_5,               //WINDOWS ONLY
        STOP_2
    };

    enum FlowType
    {
        FLOW_OFF,
        FLOW_HARDWARE,
        FLOW_XONXOFF
    };
};

#endif // QEXTSERIALPORCONFIG_H
