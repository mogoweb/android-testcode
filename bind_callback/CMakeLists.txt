cmake_minimum_required(VERSION 2.8)

project (base)

set(PROJECT_INCLUDE_DIR
${PROJECT_SOURCE_DIR}
)

include_directories("${PROJECT_INCLUDE_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++1y")

set(BASE_SRCS
base/at_exit.cc
base/base_switches.cc
base/callback_internal.cc
base/command_line.cc
base/debug/alias.cc
base/debug/debugger_posix.cc
base/debug/stack_trace.cc
base/debug/stack_trace_posix.cc
base/files/file_path.cc
base/files/file_path_constants.cc
base/lazy_instance.cc
base/location.cc
base/logging.cc
base/memory/singleton.cc
base/pickle.cc
base/posix/safe_strerror.cc
base/process/process_handle_posix.cc
base/profiler/alternate_timer.cc
base/profiler/tracked_time.cc
base/strings/string_number_conversions.cc
base/strings/string_piece.cc
base/strings/string_split.cc
base/strings/string_util.cc
base/strings/string_util_constants.cc
base/strings/string16.cc
base/strings/stringprintf.cc
base/strings/sys_string_conversions_posix.cc
base/strings/utf_string_conversions.cc
base/strings/utf_string_conversion_utils.cc
base/synchronization/lock.cc
base/synchronization/lock_impl_posix.cc
base/third_party/dmg_fp/dtoa.cc
base/third_party/dmg_fp/g_fmt.cc
base/third_party/icu/icu_utf.cc
base/third_party/nspr/prtime.cc
base/threading/platform_thread_internal_posix.cc
base/threading/platform_thread_linux.cc
base/threading/platform_thread_posix.cc
base/threading/thread_collision_warner.cc
base/threading/thread_id_name_manager.cc
base/threading/thread_local_posix.cc
base/threading/thread_local_storage.cc
base/threading/thread_local_storage_posix.cc
base/threading/thread_restrictions.cc
base/time/time.cc
base/time/time_posix.cc
base/tracked_objects.cc
base/vlog.cc
)

add_library(base ${BASE_SRCS})

set(TEST_SRCS
tests/callback_unittest.cc
)

add_executable(base_unittest ${TEST_SRCS})
target_link_libraries(base_unittest base libgtest.a libgtest_main.a pthread)