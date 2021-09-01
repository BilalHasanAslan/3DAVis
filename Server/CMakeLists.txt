cmake_minimum_required(VERSION 3.16.3)
project(3DAvis_Server)
include_directories(src)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)
set(CMAKE_LINK_DIRECTORIES_BEFORE ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/third-party/install)
include(uWebSockets)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
FIND_PACKAGE(Threads)
set(LINK_LIBS ${LINK_LIBS} stdc++fs)
include_directories(${CMAKE_SOURCE_DIR}/third-party/include)
install_uWebSockets()

set(ZFP_DIR ${CMAKE_SOURCE_DIR}/third-party/zfp)
find_package(ZFP REQUIRED)
if (ZFP_FOUND)
    include_directories(${ZFP_INCLUDE_DIR})
    set(LINK_LIBS ${LINK_LIBS} ${ZFP_LIBRARIES})
else ()
    message(FATAL_ERROR "Could not find ZFP.")
endif ()

set(LINK_LIBS
        ${LINK_LIBS}
        uSockets
        z
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