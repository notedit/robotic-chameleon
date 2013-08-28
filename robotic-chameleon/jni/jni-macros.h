#define THROW_ILLEGAL_STATE(MSG) { \
  jclass exClass = env->FindClass("java/lang/IllegalStateException"); \
  env->ThrowNew(exClass, MSG); \
}

#define THROW_ILLEGAL_ARGUMENT(MSG) { \
  jclass exClass = env->FindClass("java/lang/IllegalArgumentException"); \
  env->ThrowNew(exClass, MSG); \
}

#define PLANE(J_BUF, J_STRIDE, BUF, STRIDE, BUF_TYPE) \
  BUF_TYPE BUF = (BUF_TYPE) env->GetDirectBufferAddress(J_BUF); \
  if (BUF == NULL) { \
    THROW_ILLEGAL_ARGUMENT("ByteBuffer " #BUF " is not a direct buffer"); \
    return; \
  } \
  int STRIDE = J_STRIDE; \
  if (STRIDE < 0) { \
    THROW_ILLEGAL_ARGUMENT("Stride " #STRIDE " must be positive"); \
    return; \
  }

#define SRC_PLANE(X) PLANE(j_src ## X, j_srcStride ## X, src ## X, srcStride ## X, const uint8*)
#define DST_PLANE(X) PLANE(j_dst ## X, j_dstStride ## X, dst ## X, dstStride ## X, uint8*)

#define PLANES_1_TO_3(NAME, S1, D1, D2, D3) \
  static void JNICALL JVM_ ## NAME(JNIEnv *env, jclass, \
      jobject j_src ## S1, jint j_srcStride ## S1, \
      jobject j_dst ## D1, jint j_dstStride ## D1, \
      jobject j_dst ## D2, jint j_dstStride ## D2, \
      jobject j_dst ## D3, jint j_dstStride ## D3, \
      jint width, jint height) { \
    SRC_PLANE(S1); \
    DST_PLANE(D1); \
    DST_PLANE(D2); \
    DST_PLANE(D3); \
    int result = NAME( \
      src ## S1, srcStride ## S1, \
      dst ## D1, dstStride ## D1, \
      dst ## D2, dstStride ## D2, \
      dst ## D3, dstStride ## D3, \
      width, height); \
    if (result != 0) { \
      THROW_ILLEGAL_STATE(#NAME " failed") \
    } \
  }

#define PLANES_2_TO_3(NAME, S1, S2, D1, D2, D3) \
  static void JNICALL JVM_ ## NAME(JNIEnv *env, jclass, \
      jobject j_src ## S1, jint j_srcStride ## S1, \
      jobject j_src ## S2, jint j_srcStride ## S2, \
      jobject j_dst ## D1, jint j_dstStride ## D1, \
      jobject j_dst ## D2, jint j_dstStride ## D2, \
      jobject j_dst ## D3, jint j_dstStride ## D3, \
      jint width, jint height) { \
    SRC_PLANE(S1); \
    SRC_PLANE(S2); \
    DST_PLANE(D1); \
    DST_PLANE(D2); \
    DST_PLANE(D3); \
    int result = NAME( \
      src ## S1, srcStride ## S1, \
      src ## S2, srcStride ## S2, \
      dst ## D1, dstStride ## D1, \
      dst ## D2, dstStride ## D2, \
      dst ## D3, dstStride ## D3, \
      width, height); \
    if (result != 0) { \
      THROW_ILLEGAL_STATE(#NAME " failed") \
    } \
  }

#define PLANES_3_TO_3(NAME, S1, S2, S3, D1, D2, D3) \
  static void JNICALL JVM_ ## NAME(JNIEnv *env, jclass, \
      jobject j_src ## S1, jint j_srcStride ## S1, \
      jobject j_src ## S2, jint j_srcStride ## S2, \
      jobject j_src ## S3, jint j_srcStride ## S3, \
      jobject j_dst ## D1, jint j_dstStride ## D1, \
      jobject j_dst ## D2, jint j_dstStride ## D2, \
      jobject j_dst ## D3, jint j_dstStride ## D3, \
      jint width, jint height) { \
    SRC_PLANE(S1); \
    SRC_PLANE(S2); \
    SRC_PLANE(S3); \
    DST_PLANE(D1); \
    DST_PLANE(D2); \
    DST_PLANE(D3); \
    int result = NAME( \
      src ## S1, srcStride ## S1, \
      src ## S2, srcStride ## S2, \
      src ## S3, srcStride ## S3, \
      dst ## D1, dstStride ## D1, \
      dst ## D2, dstStride ## D2, \
      dst ## D3, dstStride ## D3, \
      width, height); \
    if (result != 0) { \
      THROW_ILLEGAL_STATE(#NAME " failed") \
    } \
  }

#define PLANES_1_TO_1(NAME, S1, D1) \
  static void JNICALL JVM_ ## NAME(JNIEnv *env, jclass, \
      jobject j_src ## S1, jint j_srcStride ## S1, \
      jobject j_dst ## D1, jint j_dstStride ## D1, \
      jint width, jint height) { \
    SRC_PLANE(S1); \
    DST_PLANE(D1); \
    int result = NAME( \
      src ## S1, srcStride ## S1, \
      dst ## D1, dstStride ## D1, \
      width, height); \
    if (result != 0) { \
      THROW_ILLEGAL_STATE(#NAME " failed") \
    } \
  }

#define PLANES_2_TO_1(NAME, S1, S2, D1) \
  static void JNICALL JVM_ ## NAME(JNIEnv *env, jclass, \
      jobject j_src ## S1, jint j_srcStride ## S1, \
      jobject j_src ## S2, jint j_srcStride ## S2, \
      jobject j_dst ## D1, jint j_dstStride ## D1, \
      jint width, jint height) { \
    SRC_PLANE(S1); \
    SRC_PLANE(S2); \
    DST_PLANE(D1); \
    int result = NAME( \
      src ## S1, srcStride ## S1, \
      src ## S2, srcStride ## S2, \
      dst ## D1, dstStride ## D1, \
      width, height); \
    if (result != 0) { \
      THROW_ILLEGAL_STATE(#NAME " failed") \
    } \
  }

#define PLANES_3_TO_1(NAME, S1, S2, S3, D1) \
  static void JNICALL JVM_ ## NAME(JNIEnv *env, jclass, \
      jobject j_src ## S1, jint j_srcStride ## S1, \
      jobject j_src ## S2, jint j_srcStride ## S2, \
      jobject j_src ## S3, jint j_srcStride ## S3, \
      jobject j_dst ## D1, jint j_dstStride ## D1, \
      jint width, jint height) { \
    SRC_PLANE(S1); \
    SRC_PLANE(S2); \
    SRC_PLANE(S3); \
    DST_PLANE(D1); \
    int result = NAME( \
      src ## S1, srcStride ## S1, \
      src ## S2, srcStride ## S2, \
      src ## S3, srcStride ## S3, \
      dst ## D1, dstStride ## D1, \
      width, height); \
    if (result != 0) { \
      THROW_ILLEGAL_STATE(#NAME " failed") \
    } \
  }

#define JNI_BUF         "Ljava/nio/ByteBuffer;"
#define JNI_PLANE       JNI_BUF "I"
#define JNI_CONVERT(NAME, PLANES) { #NAME, PLANES "II", (void*) JVM_ ## NAME }