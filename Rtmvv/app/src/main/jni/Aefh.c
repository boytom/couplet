//
// Created by whg on 16-1-15.
//

#include "cool_couplet_rtmvv_Aefh.h"
#include "Aefh.h"
#include "decrypt.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>

static struct
{
  jclass clazz;
  jfieldID DT_DIR_ID, DT_REG_ID;
  /* ordinal 和 toString 都不需要类，现在还不知道怎么使用 values 方法 2016年 01月 16日 星期六 10:08:32 CST */
  jmethodID ordinal_ID, toString_ID, valueOf_ID, values_ID;
} DTTypeWrapper;

static inline void initDTTypeWrapper(JNIEnv *penv)
{
  jclass tmpclazz;

  //JNI WARNING: illegal class name 'Lcool/couplet/rtmvv/DTType;' (FindClass)
  //(should be formed like 'dalvik/system/DexFile')
  //or '[Ldalvik/system/DexFile;' or '[[B')
  if ((tmpclazz = (*penv)->FindClass(penv, "cool/couplet/rtmvv/DTType")) == NULL)
    abort();

  DTTypeWrapper.clazz = (jclass)(*penv)->NewGlobalRef(penv, tmpclazz);
  (*penv)->DeleteLocalRef(penv, tmpclazz);

  DTTypeWrapper.DT_DIR_ID = (*penv)->GetStaticFieldID(penv, DTTypeWrapper.clazz,
      "DT_DIR", "Lcool/couplet/rtmvv/DTType;");

  DTTypeWrapper.DT_REG_ID = (*penv)->GetStaticFieldID(penv, DTTypeWrapper.clazz,
      "DT_REG", "Lcool/couplet/rtmvv/DTType;");

  DTTypeWrapper.ordinal_ID = (*penv)->GetMethodID(penv, DTTypeWrapper.clazz,
      "ordinal", "()I");

  DTTypeWrapper.toString_ID = (*penv)->GetMethodID(penv, DTTypeWrapper.clazz,
      "toString", "()Ljava/lang/String;");

  DTTypeWrapper.valueOf_ID = (*penv)->GetStaticMethodID(penv, DTTypeWrapper.clazz,
      "valueOf", "(Ljava/lang/String;)Lcool/couplet/rtmvv/DTType;");

  DTTypeWrapper.values_ID = (*penv)->GetStaticMethodID(penv, DTTypeWrapper.clazz,
      "values", "()[Lcool/couplet/rtmvv/DTType;");
}

static inline jobject DTType_getDT_DIR(JNIEnv *penv)
{
  return (*penv)->GetStaticObjectField(penv, DTTypeWrapper.clazz, 
      DTTypeWrapper.DT_DIR_ID);
}

static inline jobject DTType_getDT_REG(JNIEnv *penv)
{
  return (*penv)->GetStaticObjectField(penv, DTTypeWrapper.clazz, 
      DTTypeWrapper.DT_REG_ID);
}

static inline jint DTType_ordinal(JNIEnv *penv, jobject enumObj)
{
  return (*penv)->CallIntMethod(penv, enumObj, DTTypeWrapper.ordinal_ID);
}

static inline jstring DTType_toString(JNIEnv *penv, jobject enumObj)
{
  return (jstring)(*penv)->CallObjectMethod(penv, enumObj, 
      DTTypeWrapper.toString_ID);
}

static inline jobject DTType_valueOf(JNIEnv *penv, jstring enumName)
{
  return (*penv)->CallStaticObjectMethod(penv, DTTypeWrapper.clazz,
      DTTypeWrapper.valueOf_ID, (jobject)enumName);
}

static struct
{
  jclass clazz;
  jfieldID type_id, level_id, name_id;
} DirentWrapper;

static inline void initDirentWrapper(JNIEnv *penv)
{
  jclass tmpclazz = (*penv)->FindClass(penv, "cool/couplet/rtmvv/Dirent");
  if (tmpclazz == NULL)
    abort();
  DirentWrapper.clazz = (jclass)(*penv)->NewGlobalRef(penv, tmpclazz);
  (*penv)->DeleteLocalRef(penv, tmpclazz);

  DirentWrapper.type_id = (jfieldID)(*penv)->GetFieldID(penv, 
      DirentWrapper.clazz, "type", "Lcool/couplet/rtmvv/DTType;");

  DirentWrapper.level_id = (jfieldID)(*penv)->GetFieldID(penv, 
      DirentWrapper.clazz, "level", "I");

  DirentWrapper.name_id = (jfieldID)(*penv)->GetFieldID(penv,
      DirentWrapper.clazz, "name", "Ljava/lang/String;");
}

static inline jobject Dirent_gettype(JNIEnv *penv, jobject me)
{
  return (*penv)->GetObjectField(penv, me, DirentWrapper.type_id);
}

static inline void Dirent_settype(JNIEnv *penv, jobject me, jobject type)
{
  (*penv)->SetObjectField(penv, me, DirentWrapper.type_id, type);
}

static inline jint Dirent_getlevel(JNIEnv *penv, jobject me)
{
  return (*penv)->GetIntField(penv, me, DirentWrapper.level_id);
}

static inline void Dirent_setlevel(JNIEnv *penv, jobject me, jint level)
{
  (*penv)->SetIntField(penv, me, DirentWrapper.level_id, level);
}

static inline jstring Dirent_getname(JNIEnv *penv, jobject me)
{
  return (jstring)(*penv)->GetObjectField(penv, me, DirentWrapper.name_id);
}

static inline void Dirent_setname(JNIEnv *penv, jobject me, jstring name)
{
  return (*penv)->SetObjectField(penv, me, DirentWrapper.name_id, 
      (jobject)name);
}

static inline jobject Dirent_New(JNIEnv *penv, const struct mydirent *dirent)
{
  if (dirent == NULL)
    return NULL;

  jobject tmp = (*penv)->AllocObject(penv, DirentWrapper.clazz);
  jobject jdirent = (*penv)->NewGlobalRef(penv, tmp);
  (*penv)->DeleteLocalRef(penv, tmp);
#if 0
  jobject jdirent = (*penv)->AllocObject(penv, DirentClass);
#endif

  jobject dttype;
  // 默认是 DT_REG
  dttype = DTType_getDT_REG(penv);
  if (dirent->type == DT_DIR)
    dttype = DTType_getDT_DIR(penv);

  Dirent_settype(penv, jdirent, dttype);
  (*penv)->DeleteLocalRef(penv, dttype);

  jstring name = (*penv)->NewStringUTF(penv, (const char *)dirent->name);
  Dirent_setname(penv, jdirent, name);
  (*penv)->DeleteLocalRef(penv, name);

  Dirent_setlevel(penv, jdirent, dirent->level);

  return jdirent;
}

void initStore(JavaVM *pVM, void *reserved)
{
  JNIEnv *penv = NULL;

  endn(getduilian());

  if ((*pVM)->GetEnv(pVM, (void **) &penv, JNI_VERSION_1_6) != JNI_OK)
    abort();

#if 0
  if ((*pVM)->AttachCurrentThread(pVM, &penv, NULL) != JNI_OK)
    abort();
#endif

  initDTTypeWrapper(penv);
  initDirentWrapper(penv);

#if 0
  (*pVM)->DetachCurrentThread(pVM);
#endif
}

void destroyStore(JavaVM *pVM, void *reserved)
{
  JNIEnv *penv = NULL;

  if ((*pVM)->GetEnv(pVM, (void **) &penv, JNI_VERSION_1_6) != JNI_OK)
    abort();

#if 0
  if ((*pVM)->AttachCurrentThread(pVM, &penv, NULL) != JNI_OK)
    abort();
#endif

  if (DirentWrapper.clazz != NULL)
    (*penv)->DeleteGlobalRef(penv, DirentWrapper.clazz);

  if (DTTypeWrapper.clazz != NULL)
    (*penv)->DeleteGlobalRef(penv, DTTypeWrapper.clazz);

#if 0
    (*pVM)->DetachCurrentThread(pVM);
#endif
}

/*
 * Class:     cool_couplet_rtmvv_Aefh
 * Method:    myreaddir
 * Signature: (I)Lcool/couplet/rtmvv/Dirent;
 */
JNIEXPORT jobject JNICALL Java_cool_couplet_rtmvv_Aefh_myreaddir
        (JNIEnv *penv, jclass me, jint level)
{
  return Dirent_New(penv, myreaddir(getduilian(), level));
}

/*
 * Class:     cool_couplet_rtmvv_Aefh
 * Method:    myreadcouplet
 * Signature: (I)Lcool/couplet/rtmvv/Dirent;
 */
JNIEXPORT jobject JNICALL Java_cool_couplet_rtmvv_Aefh_myreadcouplet
(JNIEnv *penv, jclass me, jint level)
{
  return Dirent_New(penv, myreadcouplet(getduilian(), level));
}

/*
 * Class:     cool_couplet_rtmvv_Aefh
 * Method:    myreaddir2
 * Signature: (I)Lcool/couplet/rtmvv/Dirent;
 */
JNIEXPORT jobject JNICALL Java_cool_couplet_rtmvv_Aefh_myreaddir2
(JNIEnv *penv, jclass me, jint level)
{
  return Dirent_New(penv, myreaddir2(getduilian(), level));
}

/*
 * Class:     cool_couplet_rtmvv_Aefh
 * Method:    myseekdir
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_cool_couplet_rtmvv_Aefh_myseekdir
(JNIEnv *penv, jclass me, jstring path)
{
  const char *cpath = (*penv)->GetStringUTFChars(penv, path, NULL);

  int level = myseekdir((const unsigned char *)cpath, getduilian());
   
  (*penv)->ReleaseStringUTFChars(penv, path, cpath);
  return level;
}

/*
 * Class:     cool_couplet_rtmvv_Aefh
 * Method:    mygetcwd
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jstring JNICALL Java_cool_couplet_rtmvv_Aefh_mygetcwd
(JNIEnv *penv, jclass me)
{
  unsigned char ccwd[PATH_MAX];

  memset(ccwd, 0, sizeof(ccwd));

  mygetcwd(ccwd, sizeof(ccwd), getduilian()); 

  return (*penv)->NewStringUTF(penv, (const char *)ccwd);
}

/*
 * Class:     cool_couplet_rtmvv_Aefh
 * Method:    myrewinddir
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cool_couplet_rtmvv_Aefh_myrewinddir
(JNIEnv *penv, jclass me)
{
  return myrewinddir(getduilian());
}
