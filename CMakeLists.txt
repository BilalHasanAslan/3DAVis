cmake_minimum_required(VERSION 3.10)
project(3DAvis_Server_Test)
set(CMAKE_CXX_STANDARD 17)

find_package(HDF5 REQUIRED COMPONENTS CXX)
if (HDF5_FOUND)
    include_directories(${HDF5_INCLUDE_DIR})
    set(LINK_LIBS ${LINK_LIBS} ${HDF5_LIBRARIES})
else ()
    message(FATAL_ERROR "Could not find HDF5.")
endif ()

set(VTK_DIR "~/Desktop/3Davis/VTK-master/build")
find_package(VTK REQUIRED)
if (VTK_FOUND)
    include_directories(${VTK_INCLUDE_DIR})
    set(LINK_LIBS ${LINK_LIBS} ${VTK_LIBRARIES})
else ()
    message(FATAL_ERROR "Could not find VTK.")
endif ()




set(SOURCE_FILES
    ${SOURCE_FILES}
    Maintest.cpp
    HDF5Reader.cpp
    LogKeeper.cpp
    VtkVisul.cpp
    )


add_executable(3DAvis_Server_Test ${SOURCE_FILES})
target_link_libraries(3DAvis_Server_Test ${LINK_LIBS})
