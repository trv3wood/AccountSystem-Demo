cmake_minimum_required(VERSION 3.5)
project(Account LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(OpenSSL REQUIRED)
find_package(GTest REQUIRED)

# 查找libgmpxx
find_library(GMPXX_LIB gmpxx REQUIRED)
if(NOT GMPXX_LIB)
    message(FATAL_ERROR "libgmpxx not found")
endif()
# 查找libgmp
find_library(GMP_LIB gmp REQUIRED)
if(NOT GMP_LIB)
    message(FATAL_ERROR "libgmp not found")
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Encryptable ${CMAKE_CURRENT_SOURCE_DIR}/Encryptable/build)

# 编译Account类的库
set(COMPILE_TEST_UNIT OFF)
file(GLOB ACC_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# 测试单元不包含在库中
list(REMOVE_ITEM ACC_SRC ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)

add_library(${PROJECT_NAME} STATIC ${ACC_SRC}
    account.h
    basicAccount.h
)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GMPXX_LIB} ${GMP_LIB})
target_link_libraries(${PROJECT_NAME} PRIVATE encryptable)

if(COMPILE_TEST_UNIT)
    # 编译测试单元
    add_executable(test_unit test.cpp)
    target_link_libraries(test_unit PRIVATE ${PROJECT_NAME})
    target_link_libraries(test_unit PRIVATE GTest::GTest GTest::Main)
endif()
