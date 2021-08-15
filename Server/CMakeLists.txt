cmake_minimum_required(VERSION 3.10)
project(3DAvis_Server)
set(CMAKE_CXX_STANDARD 17)


set(SOURCE_FILES
    ${SOURCE_FILES}
    3DAvisMain.cpp
    LogKeeper.cpp
    FileManager.cpp
    )


add_executable(3DAvis_Server ${SOURCE_FILES})
target_link_libraries(3DAvis_Server ${LINK_LIBS})
