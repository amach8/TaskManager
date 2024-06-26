cmake_minimum_required(VERSION 3.20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(GTEST_ESSENTIALS "gmock" "gtest" "gtest_main")
add_subdirectory(googletest)

add_executable(taskTests
  testTask.cpp 
  hmain.cpp
)
add_executable(MaintaskTests
  testMainTask.cpp 
  hmain.cpp
)
add_executable(TaskListTests
  testTaskList.cpp 
  hmain.cpp
)
add_executable(RunAllTest
  testTask.cpp
  testMainTask.cpp 
  testTaskList.cpp 
  hmain.cpp
)

target_link_libraries(taskTests ${GTEST_ESSENTIALS})
target_link_libraries(taskTests taskLibrary)
target_link_libraries(MaintaskTests ${GTEST_ESSENTIALS})
target_link_libraries(MaintaskTests taskLibrary)
target_link_libraries(TaskListTests ${GTEST_ESSENTIALS})
target_link_libraries(TaskListTests taskLibrary)
target_link_libraries(RunAllTest ${GTEST_ESSENTIALS})
target_link_libraries(RunAllTest taskLibrary)
# Don't run cmake in the test folder.