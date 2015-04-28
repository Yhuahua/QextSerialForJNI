#include "com_greenstar_kernel_hardware_HWRS232.h"
#include "qextserialport.h"
#include "qextserialporconfig.h"
#include <QtSerialPort/QSerialPortInfo>

QextSerialPort *port=NULL;

jstring storJstring(JNIEnv* env, const char* pat)
{
    jclass strClass = env->FindClass("Ljava/lang/String;");
    jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray(strlen(pat));
    env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
    jstring encoding = env->NewStringUTF("utf-8");
    return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
}

const char* TranslateJStringToString(JNIEnv* env, jstring jstr)
{
    char* rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);

    if (alen > 0)
    {
        rtn = (char*)malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}

/*
 * Class:     com_greenstar_kernel_hardware_HWRS232
 * Method:    OpenSerialPort
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;D)Z
 */
JNIEXPORT jboolean JNICALL Java_com_greenstar_kernel_hardware_HWRS232_OpenSerialPort
  (JNIEnv *env, jclass rootClass, jstring portName, jstring baudRate, jstring flowControl, jstring parity, jstring dataBits, jstring stopBits, jdouble timeoutMilliSeconds)
{
    jboolean result=false;

    try{
            port=new QextSerialPort(QString(TranslateJStringToString(env, portName)));
            port->setBaudRate(QString(TranslateJStringToString(env, baudRate)));
            port->setFlowControl(QString(TranslateJStringToString(env, flowControl)));
            port->setParity(QString(TranslateJStringToString(env, parity)));
            port->setDataBits(QString(TranslateJStringToString(env, dataBits)));
            port->setStopBits(QString(TranslateJStringToString(env, stopBits)));
            port->setTimeout(timeoutMilliSeconds);
            port->open(QIODevice::ReadWrite | QIODevice::Unbuffered);

            if(port->isOpen())
            {
                result=true;
            }
    }
    catch(...)
    {
        qDebug("Too bad, cannot initalize port");
    }

    return result;
}

/*
 * Class:     com_greenstar_hardware_HWRS232
 * Method:    CloseSerialPort
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_greenstar_kernel_hardware_HWRS232_CloseSerialPort
  (JNIEnv *env, jclass, jstring data)
{       
    if(port != NULL)
    {
        port->close();
        delete port;
        port = NULL;

        QString logString=QString(TranslateJStringToString(env, data));
        logString="Close the port=" + logString;
        CommonHelper::Log(logString.toLatin1().data());
    }

    return true;
}


/*
 * Class:     com_greenstar_hardware_HWRS232
 * Method:    sendByteStream
 * Signature: ([B)Z
 */
JNIEXPORT jboolean JNICALL Java_com_greenstar_kernel_hardware_HWRS232_SendByteStream
  (JNIEnv * env, jclass, jbyteArray strIn)
{
    jboolean result=false;

    if(port != NULL)
    {
        if(port->isOpen())
        {
            char* data=(char*) env->GetByteArrayElements(strIn, 0);
            port->write(data);
            CommonHelper::Log(data);
        }
    }

    return result;
}

/*
 * Class:     com_greenstar_hardware_HWRS232
 * Method:    getByteStream
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_greenstar_kernel_hardware_HWRS232_GetByteStream
  (JNIEnv *env, jclass rootClass)
{
    char* str="";
    jstring data=env->NewStringUTF(str);

    if(port != NULL)
    {
      char buff[1024];
      int numBytes;

      numBytes = port->bytesAvailable();
      if(numBytes > 1024)
          numBytes = 1024;

      int i = port->read(buff, numBytes);
      if (i != -1)
          buff[i] = '\0';
      else
          buff[0] = '\0';
      QString msg = buff;

      QString value=QString(numBytes);
      value="number bytes=" + value;
      CommonHelper::Log(value.toLatin1().data());

      data=storJstring(env, msg.toLatin1());
    }

    return data;
}

/*
 * Class:     com_greenstar_kernel_hardware_HWRS232
 * Method:    ResettSerialPort
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_greenstar_kernel_hardware_HWRS232_ResettSerialPort
  (JNIEnv *, jclass)
{
    jboolean result=false;

    if(port != NULL)
    {
        port->close();
        delete port;
        port=NULL;
        result=true;
    }

    return result;
}

/*
 * Class:     com_greenstar_kernel_hardware_HWRS232
 * Method:    GetAvailableSerialPorts
 * Signature: ()[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_com_greenstar_kernel_hardware_HWRS232_GetAvailableSerialPorts
  (JNIEnv *env, jclass rootClass)
{
      QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();

      jobjectArray strarr = env->NewObjectArray(list.count(), env->FindClass("java/lang/String"), nullptr);

      int index=0;

      foreach(QSerialPortInfo portInfo , list)
      {
           QString portInfoString="Port : " + QString(portInfo.portName());
           CommonHelper::Log(portInfoString.toLatin1().data());
           env->SetObjectArrayElement(strarr, index, env->NewStringUTF(portInfo.portName().toLatin1().data()));
           index++;
      }

      return strarr;
}
