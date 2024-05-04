cmake_minimum_required(VERSION 3.5)
project(account LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT MSVC)
    set(CXX_COMPILER g++)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(OpenSSL REQUIRED)
find_package(GTest REQUIRED)

set(COMPILE_TEST_UNIT OFF)
if(COMPILE_TEST_UNIT)
    file(GLOB ACC_SRC ${CMAKE_SOURCE_DIR}/*.cpp)
    add_executable(test ${ACC_SRC})
    target_link_libraries(test PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
    target_link_libraries(test PRIVATE OpenSSL::SSL OpenSSL::Crypto)
    target_link_libraries(test PRIVATE GTest::GTest)
else()
    file(GLOB ACC_SRC ${CMAKE_SOURCE_DIR}/*.cpp)
    # Remove test.cpp from the list
    list(REMOVE_ITEM ACC_SRC ${CMAKE_SOURCE_DIR}/test.cpp)

    add_library(${PROJECT_NAME} STATIC ${ACC_SRC})
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()