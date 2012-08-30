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
#include <unistd.h>
#include <string.h>
#include <jni.h>

#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "read-link-test", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "read-link-test", __VA_ARGS__))

void
Java_com_mogoweb_test_MainActivity_testReadSymbolLink( JNIEnv* env,
                                                  jobject thiz )
{
	char bin_dir[PATH_MAX + 1];
	int bin_dir_size = readlink("proc/self/exe", bin_dir, PATH_MAX);
	if (bin_dir_size < 0 || bin_dir_size > PATH_MAX) {
		LOGW("readlink failed.");
		return;
	}
	bin_dir[bin_dir_size] = 0;
	LOGI("readlink success. dir: %s", bin_dir);
	return;
}
