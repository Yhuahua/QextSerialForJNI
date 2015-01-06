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

bool setSerialPort(bool openFlag, QString portName){

    if(port != NULL){

        if(port->isOpen()){

            if(!openFlag){
               port->close();
            }

        }
        else{
            if(openFlag){
                    port=new QextSerialPort(portName);
                    port->setBaudRate(BAUD19200);
                    port->setFlowControl(FLOW_OFF);
                    port->setParity(PAR_NONE);
                    port->setDataBits(DATA_8);
                    port->setStopBits(STOP_2);
                    //set timeouts to 500 ms
                    port->setTimeout(500);
                    port->open(QIODevice::ReadWrite | QIODevice::Unbuffered);
                }
        }
    }
    else if(openFlag){
        port=new QextSerialPort(portName);
        port->setBaudRate(BAUD19200);
        port->setFlowControl(FLOW_OFF);
        port->setParity(PAR_NONE);
        port->setDataBits(DATA_8);
        port->setStopBits(STOP_2);
        //set timeouts to 500 ms
        port->setTimeout(500);
        port->open(QIODevice::ReadWrite | QIODevice::Unbuffered);
    }
    return true;
}

/*
 * Class:     com_greenstar_hardware_HWRS232
 * Method:    OpenSerialPort
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;III)Z
 */
JNIEXPORT jboolean JNICALL Java_com_greenstar_hardware_HWRS232_OpenSerialPort
  (JNIEnv *, jclass, jstring, jstring, jstring, jstring, jint, jint, jint)
{
    return false;
}

/*
 * Class:     com_greenstar_hardware_HWRS232
 * Method:    CloseSerialPort
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_greenstar_hardware_HWRS232_CloseSerialPort
  (JNIEnv *, jclass, jstring)
{
    return false;
}


/*
 * Class:     com_greenstar_hardware_HWRS232
 * Method:    sendByteStream
 * Signature: ([B)Z
 */
JNIEXPORT jboolean JNICALL Java_com_greenstar_hardware_HWRS232_sendByteStream
  (JNIEnv *, jclass, jbyteArray)
{
    jboolean result=false;

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
    return storJstring(env, "port->portName().toLocal8Bit()");
}
