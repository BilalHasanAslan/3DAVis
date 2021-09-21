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

set(ZFP_DIR ${CMAKE_SOURCE_DIR}/third-party/zfp/build)
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

find_package(HDF5 REQUIRED COMPONENTS CXX)
if (HDF5_FOUND)
    include_directories(${HDF5_INCLUDE_DIR})
    set(LINK_LIBS ${LINK_LIBS} ${HDF5_LIBRARIES})
else ()
    message(FATAL_ERROR "Could not find HDF5.")
endif ()

set(VTK_DIR "~/Documents/VTK/vtk-v9.0.3/build")
find_package(VTK REQUIRED)
if (VTK_FOUND)
    include_directories(${VTK_INCLUDE_DIR})
    set(LINK_LIBS ${LINK_LIBS} ${VTK_LIBRARIES})
else ()
    message(FATAL_ERROR "Could not find VTK.")
endif ()

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    set(LINK_LIBS ${LINK_LIBS} ${OpenMP_CXX_LIBRARIES})
endif ()

set(SOURCE_FILES
    ${SOURCE_FILES}
    FileManager.cpp
    Compression.cpp
    HDF5Reader.cpp
    LogKeeper.cpp
    VtkVisul.cpp
    Controller.cpp
    Tile.cpp
    3DAvisMain.cpp
    base64.cpp
    )


add_executable(3DAvis_Server ${SOURCE_FILES})
target_compile_options(3DAvis_Server PUBLIC ${3DAvis_Server_CFLAGS})
target_link_libraries(3DAvis_Server ${LINK_LIBS})
