//
// Created by whg on 16-1-15.
//

#include "cool_couplet_rtmvv_Aefh.h"
#include "Aefh.h"

JNIEXPORT jint JNI_OnLoad(JavaVM *pVM, void *reserved) {
   initStore(pVM, reserved);
   return JNI_VERSION_1_6;
}

JNIEXPORT void JNI_OnUnLoad(JavaVM *pVM, void *reserved) {
  destroyStore(pVM, reserved);
}
