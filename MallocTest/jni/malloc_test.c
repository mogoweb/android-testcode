/*
 * Copyright (C) 2012 mogoweb.net
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <jni.h>

#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "malloc-test", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "malloc-test", __VA_ARGS__))

#define BUF_SIZE 1024

void
Java_com_mogoweb_malloctest_MainActivity_startMallocTest( JNIEnv* env,
                                                  jobject thiz )
{
    int i = 0;
    while (1) {
        i++;
        char* p = (char*)malloc(1024 * 1024);
        if (p) {
            LOGI("malloc success");
            strcpy(p, "hello");
        } else {
            LOGW("malloc failed after malloc %d M", i);
            break;
        }
    }
}
