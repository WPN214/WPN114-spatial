cmake_minimum_required(VERSION 3.1)
project(wpn114spatial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

find_package(Qt5 REQUIRED COMPONENTS Quick Core Qml)
find_package(WPN114 REQUIRED COMPONENTS Audio)

# SOURCES -----------------------------------------------------------------------------------------

set(WPN114_SPATIAL_SOURCE_DIR source)
set(WPN114_SPATIAL_QML_DIR qml)
set(WPN114_SPATIAL_SOURCES
    ${WPN114_SPATIAL_SOURCE_DIR}/surround.hpp
    ${WPN114_SPATIAL_QML_DIR}/qmldir
    ${WPN114_SPATIAL_QML_DIR}/spatial.qmltypes
    qml_plugin.cpp)

# PROJECT -----------------------------------------------------------------------------------------

add_subdirectory(examples)
add_library(${PROJECT_NAME} SHARED ${WPN114_SPATIAL_SOURCES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick Qt5::Qml WPN114::Audio)

# INSTALL -----------------------------------------------------------------------------------------
message("[WPN114] Library will be installed in ${WPN114_AUDIO_ROOT}/Spatial")

install(TARGETS ${PROJECT_NAME} DESTINATION ${WPN114_AUDIO_ROOT}/Spatial)
install(FILES qml/spatial.qmltypes qml/qmldir DESTINATION ${WPN114_AUDIO_ROOT}/Spatial)
