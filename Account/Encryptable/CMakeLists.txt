cmake_minimum_required(VERSION 3.5)
project(encryptable C CXX)
find_package(OpenSSL REQUIRED)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)

set(TEST OFF)
list(FILTER SRC_LIST EXCLUDE REGEX "test.cpp")
add_library(${PROJECT_NAME} OBJECT ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto)

if(TEST)
    find_library(GMP gmp REQUIRED)
    find_library(GMPXX gmpxx REQUIRED)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

    find_package(GTest REQUIRED)

    add_executable(test test.cpp)
    target_link_libraries(test ${PROJECT_NAME})
    target_link_libraries(test GTest::GTest GTest::Main)

    target_link_libraries(test ${GMP} ${GMPXX})
    target_link_libraries(test Qt${QT_VERSION_MAJOR}::Core)
endif()
