#include "com_greenstar_hardware_HWRS232.h"
#include "qextserialport.h"


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

bool setSerialPort(JNIEnv *env, jstring portname, jstring baudrate, jstring flowcontrol, jstring parity, jint databits, jint stopbits , jint timeoutMilliSeconds)
{
  const char *nativeString = env->GetStringUTFChars(portname, 0);
  QString portName=QString::fromStdString(nativeString);
  port=new QextSerialPort(portName);
  port->setBaudRate(BAUD19200);
  port->setFlowControl(FLOW_OFF);
  port->setParity(PAR_NONE);
  port->setDataBits(DATA_8);
  port->setStopBits(STOP_2);
  //set timeouts to 500 ms
  port->setTimeout(500);
  port->open(QIODevice::ReadWrite | QIODevice::Unbuffered);
  return true;
}

/*
 * Class:     com_greenstar_hardware_HWRS232
 * Method:    OpenSerialPort
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;III)Z
 */
JNIEXPORT jboolean JNICALL Java_com_greenstar_hardware_HWRS232_OpenSerialPort
  (JNIEnv * env, jclass strClass, jstring portname, jstring baudrate, jstring flowcontrol, jstring parity, jint databits, jint stopbits , jint timeoutMilliSeconds)
{
    jboolean result=false;

    if(port != NULL)
    {
        if(port->isOpen()){
            Java_com_greenstar_hardware_HWRS232_CloseSerialPort(env, strClass, portname);
        }

        delete port;
        port=NULL;
    }
    else{
        setSerialPort(env,portname, baudrate, flowcontrol, parity, databits, stopbits , timeoutMilliSeconds);
    }

    if(port->isOpen()){
        result=true;
    }

    return result;
}

/*
 * Class:     com_greenstar_hardware_HWRS232
 * Method:    CloseSerialPort
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_greenstar_hardware_HWRS232_CloseSerialPort
  (JNIEnv *, jclass, jstring)
{
    if(port != NULL){
        port->close();
    }

    return true;
}


/*
 * Class:     com_greenstar_hardware_HWRS232
 * Method:    sendByteStream
 * Signature: ([B)Z
 */
JNIEXPORT jboolean JNICALL Java_com_greenstar_hardware_HWRS232_sendByteStream
  (JNIEnv *env, jclass, jbyteArray inputData)
{
    jboolean result=false;
    char* data = (char*)env->GetByteArrayElements(inputData, 0);
    QString message=QString::fromStdString(data);
    port->write(message.toLatin1(), message.length());
    result=true;
    return result;
}

/*
 * Class:     com_greenstar_hardware_HWRS232
 * Method:    getByteStream
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_greenstar_hardware_HWRS232_GetByteStream
  (JNIEnv * env, jclass)
{
   // setSerialPort(true, "COM11");
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
    qDebug("bytes available: %d", numBytes);
    qDebug("received: %d", i);

    return storJstring(env, msg.toLatin1());
}
