cmake_minimum_required(VERSION 3.0.0)
project(infoQueue VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(sender sender.cpp)
add_executable(receiver receiver.cpp)

target_link_libraries(sender pthread rt)
target_link_libraries(receiver pthread rt)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
