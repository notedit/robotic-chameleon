#include "jni.h"
#include "libyuv.h"

#include "jni-macros.h"

using namespace libyuv;

// Conversions to YUV

#define FROM_1_YUV(NAME, S1) \
  PLANES_1_TO_3(NAME, S1, Y, U, V) \
  PLANES_1_TO_P(NAME, S1, I420, Y, U, V, 2)
#define FROM_2_YUV(NAME, S1, S2) \
  PLANES_2_TO_3(NAME, S1, S2, Y, U, V) \
  PLANES_2_TO_P(NAME, S1, S2, I420, Y, U, V, 2)
#define FROM_P_YUV(NAME, S, S1, S2, S3, SUBY) \
  PLANES_3_TO_3(NAME, S1, S2, S3, Y, U, V) \
  PLANES_P_TO_3(NAME, S, S1, S2, S3, SUBY, Y, U, V) \
  PLANES_3_TO_P(NAME, S1, S2, S3, I420, Y, U, V, 2) \
  PLANES_P_TO_P(NAME, S, S1, S2, S3, SUBY, I420, Y, U, V, 2)
#define FROM_SP_YUV(NAME, S, S1, S2) \
  FROM_2_YUV(NAME, S1, S2) \
  PLANES_SP_TO_3(NAME, S, S1, S2, Y, U, V) \
  PLANES_SP_TO_P(NAME, S, S1, S2, I420, Y, U, V, 2)

FROM_P_YUV( I444ToI420,     I444, Y, U, V, 1);
FROM_P_YUV( I422ToI420,     I422, Y, U, V, 1);
FROM_P_YUV( I411ToI420,     I411, Y, U, V, 1);
FROM_P_YUV( I420Copy,       I420, Y, U, V, 2);
FROM_1_YUV( I400ToI420,     Y);
FROM_SP_YUV(NV12ToI420,     NV12, Y, UV);
FROM_SP_YUV(NV21ToI420,     NV21, Y, VU);
FROM_1_YUV( YUY2ToI420,     YUY2);
FROM_1_YUV( UYVYToI420,     UYVY);
FROM_1_YUV( M420ToI420,     M420);
FROM_2_YUV( Q420ToI420,     Y, YUY2);
FROM_1_YUV( ARGBToI420,     FRAME);
FROM_1_YUV( BGRAToI420,     FRAME);
FROM_1_YUV( ABGRToI420,     FRAME);
FROM_1_YUV( RGBAToI420,     FRAME);
FROM_1_YUV( RGB24ToI420,    FRAME);
FROM_1_YUV( RAWToI420,      FRAME);
FROM_1_YUV( RGB565ToI420,   FRAME);
FROM_1_YUV( ARGB1555ToI420, FRAME);
FROM_1_YUV( ARGB4444ToI420, FRAME);

// Conversions to ARGB

#define FROM_1_ARGB(NAME, S1)         PLANES_1_TO_1(NAME, S1, ARGB)
#define FROM_2_ARGB(NAME, S1, S2)     PLANES_2_TO_1(NAME, S1, S2, ARGB)
#define FROM_3_ARGB(NAME, S1, S2, S3) PLANES_3_TO_1(NAME, S1, S2, S3, ARGB)
#define FROM_P_ARGB(NAME, S, S1, S2, S3, SSUBY) \
  PLANES_3_TO_1(NAME, S1, S2, S3, ARGB) \
  PLANES_P_TO_1(NAME, S, S1, S2, S3, SSUBY, ARGB)
#define FROM_SP_ARGB(NAME, S, S1, S2) \
  PLANES_2_TO_1(NAME, S1, S2, ARGB) \
  PLANES_SP_TO_1(NAME, S, S1, S2, ARGB)

FROM_1_ARGB( ARGBCopy,       ARGB);
FROM_P_ARGB( I420ToARGB,     I420, Y, U, V, 2);
FROM_P_ARGB( I422ToARGB,     I422, Y, U, V, 1);
FROM_P_ARGB( I444ToARGB,     I444, Y, U, V, 1);
FROM_P_ARGB( I411ToARGB,     I411, Y, U, V, 1);
FROM_1_ARGB( I400ToARGB,     Y);
FROM_SP_ARGB(NV12ToARGB,     NV12, Y, UV);
FROM_SP_ARGB(NV21ToARGB,     NV21, Y, VU);
FROM_1_ARGB( M420ToARGB,     M420);
FROM_1_ARGB( YUY2ToARGB,     YUY2);
FROM_1_ARGB( UYVYToARGB,     UYVY);
FROM_1_ARGB( BGRAToARGB,     FRAME);
FROM_1_ARGB( ABGRToARGB,     FRAME);
FROM_1_ARGB( RGBAToARGB,     FRAME);
FROM_1_ARGB( RGB24ToARGB,    FRAME);
FROM_1_ARGB( RAWToARGB,      FRAME);
FROM_1_ARGB( RGB565ToARGB,   FRAME);
FROM_1_ARGB( ARGB1555ToARGB, FRAME);
FROM_1_ARGB( ARGB4444ToARGB, FRAME);

#ifdef __cplusplus
extern "C" {
#endif

#define JNI_FROM_1_YUV(NAME) \
  JNI_CONVERT(NAME, JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE), \
  { #NAME, "(" JNI_PLANE JNI_BUF "III" "II)V", (void*) JVM_ ## NAME ## _D }
#define JNI_FROM_2_YUV(NAME) \
  JNI_CONVERT(NAME, JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE), \
  { #NAME, "(" JNI_PLANE JNI_PLANE JNI_BUF "III" "II)V", (void*) JVM_ ## NAME ## _D }
#define JNI_FROM_1_1(NAME) JNI_CONVERT(NAME, JNI_PLANE JNI_PLANE)
#define JNI_FROM_P_1(NAME) \
  JNI_CONVERT(NAME, JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE), \
  { #NAME, "(" JNI_BUF "III" JNI_PLANE "II)V", (void*) JVM_ ## NAME ## _S }
#define JNI_FROM_SP_1(NAME) \
  JNI_CONVERT(NAME, JNI_PLANE JNI_PLANE JNI_PLANE), \
  { #NAME, "(" JNI_BUF "II" JNI_PLANE "II)V", (void*) JVM_ ## NAME ## _S }
#define JNI_FROM_P_YUV(NAME) \
  JNI_CONVERT(NAME, JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE), \
  { #NAME, "(" JNI_BUF "III" JNI_PLANE JNI_PLANE JNI_PLANE "II)V", (void*) JVM_ ## NAME ## _S }, \
  { #NAME, "(" JNI_PLANE JNI_PLANE JNI_PLANE JNI_BUF "III" "II)V", (void*) JVM_ ## NAME ## _D }, \
  { #NAME, "(" JNI_BUF "III" JNI_BUF "III" "II)V", (void*) JVM_ ## NAME ## _SD }
#define JNI_FROM_SP_YUV(NAME) \
  JNI_CONVERT(NAME, JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE), \
  { #NAME, "(" JNI_BUF "II" JNI_PLANE JNI_PLANE JNI_PLANE "II)V", (void*) JVM_ ## NAME ## _S }, \
  { #NAME, "(" JNI_PLANE JNI_PLANE JNI_BUF "III" "II)V", (void*) JVM_ ## NAME ## _D }, \
  { #NAME, "(" JNI_BUF "II" JNI_BUF "III" "II)V", (void*) JVM_ ## NAME ## _SD }

static JNINativeMethod methods[] = {
  // Conversions to YUV
  JNI_FROM_P_YUV( I444ToI420),
  JNI_FROM_P_YUV( I422ToI420),
  JNI_FROM_P_YUV( I411ToI420),
  JNI_FROM_P_YUV( I420Copy),
  JNI_FROM_1_YUV( I400ToI420),
  JNI_FROM_SP_YUV(NV12ToI420),
  JNI_FROM_SP_YUV(NV21ToI420),
  JNI_FROM_1_YUV( YUY2ToI420),
  JNI_FROM_1_YUV( UYVYToI420),
  JNI_FROM_1_YUV( M420ToI420),
  JNI_FROM_2_YUV( Q420ToI420),
  JNI_FROM_1_YUV( ARGBToI420),
  JNI_FROM_1_YUV( BGRAToI420),
  JNI_FROM_1_YUV( ABGRToI420),
  JNI_FROM_1_YUV( RGBAToI420),
  JNI_FROM_1_YUV( RGB24ToI420),
  JNI_FROM_1_YUV( RAWToI420),
  JNI_FROM_1_YUV( RGB565ToI420),
  JNI_FROM_1_YUV( ARGB1555ToI420),
  JNI_FROM_1_YUV( ARGB4444ToI420),

  // Conversions to ARGB
  JNI_FROM_1_1( ARGBCopy),
  JNI_FROM_P_1( I420ToARGB),
  JNI_FROM_P_1( I422ToARGB),
  JNI_FROM_P_1( I444ToARGB),
  JNI_FROM_P_1( I411ToARGB),
  JNI_FROM_1_1( I400ToARGB),
  JNI_FROM_SP_1(NV12ToARGB),
  JNI_FROM_SP_1(NV21ToARGB),
  JNI_FROM_1_1( M420ToARGB),
  JNI_FROM_1_1( YUY2ToARGB),
  JNI_FROM_1_1( UYVYToARGB),
  JNI_FROM_1_1( BGRAToARGB),
  JNI_FROM_1_1( ABGRToARGB),
  JNI_FROM_1_1( RGBAToARGB),
  JNI_FROM_1_1( RGB24ToARGB),
  JNI_FROM_1_1( RAWToARGB),
  JNI_FROM_1_1( RGB565ToARGB),
  JNI_FROM_1_1( ARGB1555ToARGB),
  JNI_FROM_1_1( ARGB4444ToARGB)
};

jint JNI_OnLoad(JavaVM *vm, void *) {
  JNIEnv *env;
  if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK)
    return JNI_ERR;

  jclass clazz = env->FindClass("fi/gekkio/roboticchameleon/lowlevel/RoboticChameleonJNI");
  if (clazz == NULL)
    return JNI_ERR;

  if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(JNINativeMethod)) < 0)
    return JNI_ERR;

  return JNI_VERSION_1_6;
}

#ifdef __cplusplus
}
#endif
