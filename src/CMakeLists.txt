file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_library(${LIB_NAME} STATIC
    ${SRC_FILES})

target_link_libraries(${LIB_NAME} Eigen3::Eigen)

find_package(Python3 REQUIRED)

target_include_directories(${LIB_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/includes
)

if ( CMAKE_COMPILER_IS_GNUCC )
    target_compile_options(${LIB_NAME} PRIVATE -Werror -Wall -Wextra -Wuninitialized -pedantic)
endif()
if ( MSVC )
    target_compile_options(${LIB_NAME} PRIVATE /W4)
endif()