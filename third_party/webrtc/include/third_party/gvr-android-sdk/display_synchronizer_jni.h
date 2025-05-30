// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is of the same format as file that generated by
//     third_party/jni_zero/jni_zero.py
// For
//     com/google/vr/cardboard/DisplaySynchronizer

// Local modification includes:
// 1. Remove all implementation, only keep definition.
// 2. Use absolute path instead of relative path.
// 3. Removed all helper functions such as: Create.
// 4. Added function RegisterDisplaySynchronizerNatives at the end of this file.
// 5. Added "vr" as an argument to base::android::LazyGetClass.

#ifndef com_google_vr_cardboard_DisplaySynchronizer_JNI
#define com_google_vr_cardboard_DisplaySynchronizer_JNI

#include "base/android/jni_android.h"
// ----------------------------------------------------------------------------
// Native JNI methods
// ----------------------------------------------------------------------------
#include <jni.h>
#include <atomic>
#include <type_traits>

#include "third_party/jni_zero/jni_int_wrapper.h"
#include "third_party/jni_zero/jni_zero_helper.h"

// Step 1: forward declarations.
namespace {

const char kDisplaySynchronizerClassPath[] =
    "com/google/vr/cardboard/DisplaySynchronizer";
// Leaking this jclass as we cannot use LazyInstance from some threads.
std::atomic<jclass> g_DisplaySynchronizer_clazz __attribute__((unused))
    (nullptr);
#define DisplaySynchronizer_clazz(env)                                  \
  base::android::LazyGetClass(env, kDisplaySynchronizerClassPath, "vr", \
                              &g_DisplaySynchronizer_clazz)

}  // namespace

namespace DisplaySynchronizer {

extern "C" __attribute__((visibility("default"))) jlong
Java_com_google_vr_cardboard_DisplaySynchronizer_nativeCreate(
    JNIEnv* env,
    jobject jcaller,
    jclass classLoader,
    jobject appContext);

// Step 2: method stubs.
extern "C" __attribute__((visibility("default"))) void
Java_com_google_vr_cardboard_DisplaySynchronizer_nativeDestroy(
    JNIEnv* env,
    jobject jcaller,
    jlong nativeDisplaySynchronizer);

extern "C" __attribute__((visibility("default"))) void
Java_com_google_vr_cardboard_DisplaySynchronizer_nativeReset(
    JNIEnv* env,
    jobject jcaller,
    jlong nativeDisplaySynchronizer,
    jlong expectedInterval,
    jlong vsyncOffset);

extern "C" __attribute__((visibility("default"))) void
Java_com_google_vr_cardboard_DisplaySynchronizer_nativeUpdate(
    JNIEnv* env,
    jobject jcaller,
    jlong nativeDisplaySynchronizer,
    jlong syncTime,
    jint currentRotation);

extern "C" __attribute__((visibility("default"))) void
Java_com_google_vr_cardboard_DisplaySynchronizer_nativeOnMetricsChanged(
    JNIEnv* env,
    jobject obj,
    jlong native_object);

// Step 3: RegisterNatives.

static const JNINativeMethod kMethodsDisplaySynchronizer[] = {
    {"nativeCreate",
     "("
     "Ljava/lang/ClassLoader;"
     "Landroid/content/Context;"
     ")"
     "J",
     reinterpret_cast<void*>(
         Java_com_google_vr_cardboard_DisplaySynchronizer_nativeCreate)},
    {"nativeDestroy",
     "("
     "J"
     ")"
     "V",
     reinterpret_cast<void*>(
         Java_com_google_vr_cardboard_DisplaySynchronizer_nativeDestroy)},
    {"nativeReset",
     "("
     "J"
     "J"
     "J"
     ")"
     "V",
     reinterpret_cast<void*>(
         Java_com_google_vr_cardboard_DisplaySynchronizer_nativeReset)},
    {"nativeUpdate",
     "("
     "J"
     "J"
     "I"
     ")"
     "V",
     reinterpret_cast<void*>(
         Java_com_google_vr_cardboard_DisplaySynchronizer_nativeUpdate)},
    {"nativeOnMetricsChanged",
     "("
     "J"
     ")"
     "V",
     reinterpret_cast<void*>(
         Java_com_google_vr_cardboard_DisplaySynchronizer_nativeOnMetricsChanged)},
};

static bool RegisterNativesImpl(JNIEnv* env) {
  const int kMethodsDisplaySynchronizerSize =
      std::extent<decltype(kMethodsDisplaySynchronizer)>();

  if (env->RegisterNatives(DisplaySynchronizer_clazz(env),
                           kMethodsDisplaySynchronizer,
                           kMethodsDisplaySynchronizerSize) < 0) {
    jni_generator::HandleRegistrationError(env, DisplaySynchronizer_clazz(env),
                                           __FILE__);
    return false;
  }

  return true;
}

static bool RegisterDisplaySynchronizerNatives(JNIEnv* env) {
  return RegisterNativesImpl(env);
}

}  // namespace DisplaySynchronizer

#endif  // com_google_vr_cardboard_DisplaySynchronizer_JNI
