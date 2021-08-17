cmake_minimum_required(VERSION 3.16.3)
project(3DAvis_Server)
include_directories(src)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)
set(CMAKE_LINK_DIRECTORIES_BEFORE ON)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/third_party/install)
include(uWebSockets)
FIND_PACKAGE(Threads)
include_directories(${CMAKE_SOURCE_DIR}/third-party/include)
install_uWebSockets()

set(LINK_LIBS
        ${LINK_LIBS}
        uSockets
        ${CMAKE_THREAD_LIBS_INIT}
        )


set(SOURCE_FILES
    ${SOURCE_FILES}
    3DAvisMain.cpp
    LogKeeper.cpp
    FileManager.cpp
    Server.cpp
    )


add_executable(3DAvis_Server ${SOURCE_FILES})
target_compile_options(3DAvis_Server PUBLIC ${3DAvis_Server_CFLAGS})
target_link_libraries(3DAvis_Server ${LINK_LIBS})