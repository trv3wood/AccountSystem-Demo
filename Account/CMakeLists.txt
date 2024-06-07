cmake_minimum_required(VERSION 3.5)
project(Account LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_library(GMP gmp REQUIRED)
find_library(GMPXX gmpxx REQUIRED)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Encryptable)

# 编译Account类的库
set(COMPILE_TEST_UNIT ON)
file(GLOB ACC_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# 测试单元不包含在库中
list(REMOVE_ITEM ACC_SRC ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)

add_library(${PROJECT_NAME} STATIC ${ACC_SRC}
    account.h
    basicAccount.h
)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GMP} ${GMPXX})
target_link_libraries(${PROJECT_NAME} PRIVATE encryptable)

if(COMPILE_TEST_UNIT)
    # 编译测试单元
    find_package(GTest REQUIRED)
    add_executable(test_unit test.cpp)
    target_link_libraries(test_unit PRIVATE ${PROJECT_NAME})
    target_link_libraries(test_unit PRIVATE GTest::GTest GTest::Main)
endif()
