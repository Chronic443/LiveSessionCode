#include <jni.h>
#include "ramRead_MainClass.h"
#include <sys/uio.h>
#include <iostream>

JNIEXPORT void JNICALL Java_ramRead_MainClass_readRam
  (JNIEnv *env, jclass, jobject byteBuffer, jlong addr, jint pid)
{
        struct iovec local[1];
        struct iovec remote[1];

        void* buf = env->GetDirectBufferAddress(byteBuffer);
        jlong len = env->GetDirectBufferCapacity(byteBuffer);

        local[0].iov_base = buf;
        local[0].iov_len = len;

        remote[0].iov_base = (void *) addr;
        remote[0].iov_len = len;
        //1. process id
        //2. localiov local
        //3. local iov count
        //4. remoteiov
        //5. remote iov count
        //6. flags
        process_vm_readv(pid, local, 1, remote, 1, 0);
}
