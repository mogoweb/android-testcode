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

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "socketpair-test", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "socketpair-test", __VA_ARGS__))

#define BUF_SIZE 1024

void
Java_com_mogoweb_socketpairtest_MainActivity_testSocketPair( JNIEnv* env,
                                                  jobject thiz )
{
	int s[2];
	int w, r;
	char* test_str = "This is a test string";
	char* buf = (char*)calloc(1, BUF_SIZE);

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, s) == -1) {
		LOGW("create unnamed socket pair failed: %s", strerror(errno));
		return;
	}

	if ((w = write(s[0], test_str, strlen(test_str))) == -1) {
		LOGW("Write socket error: %s", strerror(errno));
		return;
	}

	if ((r = read(s[1], buf, BUF_SIZE)) == -1) {
		LOGW("Read from socket error: %s", strerror(errno));
		return;
	}
	LOGI("Read string in same process: %s", buf);

	LOGI("Test successed\n");
}
