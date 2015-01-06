/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_greenstar_hardware_HWRS232 */

#ifndef _Included_com_greenstar_hardware_HWRS232
#define _Included_com_greenstar_hardware_HWRS232
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_greenstar_hardware_HWRS232
 * Method:    OpenSerialPort
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;III)Z
 */
JNIEXPORT jboolean JNICALL Java_com_greenstar_hardware_HWRS232_OpenSerialPort
  (JNIEnv *, jclass, jstring, jstring, jstring, jstring, jint, jint, jint);

/*
 * Class:     com_greenstar_hardware_HWRS232
 * Method:    CloseSerialPort
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_greenstar_hardware_HWRS232_CloseSerialPort
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_greenstar_hardware_HWRS232
 * Method:    SendByteStream
 * Signature: ([B)Z
 */
JNIEXPORT jboolean JNICALL Java_com_greenstar_hardware_HWRS232_SendByteStream
  (JNIEnv *, jclass, jbyteArray);

/*
 * Class:     com_greenstar_hardware_HWRS232
 * Method:    GetByteStream
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_greenstar_hardware_HWRS232_GetByteStream
  (JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
