cmake_minimum_required(VERSION 3.1)
project(wpn114spatial-qml LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_LINK_FLAGS)

find_package(Qt5 REQUIRED COMPONENTS Quick Core Qml)

set(WPN114SPATIAL_QML_SOURCES
    qml_plugin.cpp
    source/surround.hpp
    )

set(WPN114AUDIO_ROOT /usr/lib/qt/qml/WPN114/Audio)

add_subdirectory(examples)
add_library(${PROJECT_NAME} SHARED ${WPN114SPATIAL_QML_SOURCES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick Qt5::Qml -L${WPN114AUDIO_ROOT} -lwpn114audio-qml)
target_include_directories(${PROJECT_NAME} PUBLIC ${WPN114AUDIO_ROOT}/include)

if(APPLE)
elseif(UNIX AND NOT APPLE)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/lib/qt/qml/WPN114/Audio/Spatial)
install(FILES qml/spatial.qmltypes qml/qmldir DESTINATION /usr/lib/qt/qml/WPN114/Audio/Spatial)
