#include "com_greenstar_kernel_hardware_HWRS232.h"
#include "qextserialport.h"
#include "qextserialporconfig.h"

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

<<<<<<< HEAD
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
=======
jboolean setSerialPort(JNIEnv *env, jstring portname, jstring baudrate, jstring flowcontrol, jstring parity, jint databits, jint stopbits , jint timeoutMilliSeconds)
{
  jboolean result=false;
  //const char *nativeString = env->GetStringUTFChars(portname, 0);
 // QString portName=QString::fromStdString(nativeString);
  port=new QextSerialPort("COM17");
  port->setBaudRate(BAUD19200);
  port->setFlowControl(FLOW_OFF);
  port->setParity(PAR_NONE);
  port->setDataBits(DATA_8);
  port->setStopBits(STOP_2);
  //set timeouts to 500 ms
  port->setTimeout(500);
  port->open(QIODevice::ReadWrite | QIODevice::Unbuffered);
  result=true;
  return result;
>>>>>>> origin/A1
}

/*
 * Class:     com_greenstar_kernel_hardware_HWRS232
 * Method:    OpenSerialPort
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;D)Z
 */
JNIEXPORT jboolean JNICALL Java_com_greenstar_kernel_hardware_HWRS232_OpenSerialPort
<<<<<<< HEAD
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

=======
  (JNIEnv * env, jclass strClass, jstring portname, jstring baudrate, jstring flowcontrol, jstring parity, jint databits, jint stopbits , jint timeoutMilliSeconds)
{
    jboolean result=false;

    if(port != NULL)
    {
        if(port->isOpen()){
            Java_com_greenstar_kernel_hardware_HWRS232_CloseSerialPort(env, strClass, portname);
        }

        delete port;
        port=NULL;
    }
    else{
        setSerialPort(env,portname, baudrate, flowcontrol, parity, databits, stopbits , timeoutMilliSeconds);
    }

    result=true;
>>>>>>> origin/A1
    return result;
}

/*
 * Class:     com_greenstar_hardware_HWRS232
 * Method:    CloseSerialPort
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_greenstar_kernel_hardware_HWRS232_CloseSerialPort
<<<<<<< HEAD
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
=======
  (JNIEnv *, jclass, jstring)
{
    if(port != NULL){
        port->close();
>>>>>>> origin/A1
    }

    return true;
}


/*
 * Class:     com_greenstar_hardware_HWRS232
 * Method:    sendByteStream
 * Signature: ([B)Z
 */
<<<<<<< HEAD
JNIEXPORT jboolean JNICALL Java_com_greenstar_kernel_hardware_HWRS232_sendByteStream
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

=======
JNIEXPORT jboolean JNICALL Java_com_greenstar_kernel_hardware_HWRS232_SendByteStream
  (JNIEnv *env, jclass, jbyteArray inputData)
{
    jboolean result=false;
    char* data = (char*)env->GetByteArrayElements(inputData, 0);
    QString message="QString::fromStdString(data);";
    port->write(message.toLatin1(), message.length());
    result=true;
>>>>>>> origin/A1
    return result;
}

/*
 * Class:     com_greenstar_hardware_HWRS232
 * Method:    getByteStream
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_greenstar_kernel_hardware_HWRS232_GetByteStream
<<<<<<< HEAD
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
=======
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
>>>>>>> origin/A1
}
