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

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    set(LINK_LIBS ${LINK_LIBS} ${OpenMP_CXX_LIBRARIES})
endif ()

set(VTK_DIR "~/Downloads/vtk-v9.0.3/build")
find_package(VTK REQUIRED)
if (VTK_FOUND)
    include_directories(${VTK_INCLUDE_DIR})
    set(LINK_LIBS ${LINK_LIBS} ${VTK_LIBRARIES})
else ()
    message(FATAL_ERROR "Could not find VTK.")
endif ()

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_SEARCH_MODULE(CFITSIO REQUIRED cfitsio)
if (CFITSIO_FOUND)
    include_directories(${CFITSIO_INCLUDE_DIRS})
    link_directories(${CFITSIO_LIBRARY_DIRS})
    set(LINK_LIBS ${LINK_LIBS} ${CFITSIO_LIBRARIES})
    message(STATUS "Found CFITSIO: ${CFITSIO_LINK_LIBRARIES} Version: ${CFITSIO_VERSION}")
else ()
    message(FATAL_ERROR "Could not find CFITSIO.")
endif ()

set(SOURCE_FILES
    ${SOURCE_FILES}
    Maintest.cpp
    HDF5Reader.cpp
    LogKeeper.cpp
    VtkVisul.cpp
    Converter.cpp
    MipMap.cpp
    MipMapUtil.cpp
    HDF53DConstructor.cpp
    )


add_executable(3DAvis_Server_Test ${SOURCE_FILES})
target_link_libraries(3DAvis_Server_Test ${LINK_LIBS})
