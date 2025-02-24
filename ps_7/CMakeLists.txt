cmake_minimum_required(VERSION 3.17)

set(MY_PROJECT_NAME ps_7)
project(${MY_PROJECT_NAME} LANGUAGES C)
# CXX)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_CXX_STANDARD 17)
set(PROJECT_COMPILE_OPTIONS -std=c11 -Werror -Wall -lm) #Creating variable 
add_compile_options(${PROJECT_COMPILE_OPTIONS}) # Set the options of compilate(here)

add_executable(${MY_PROJECT_NAME} playfair.c ) 
target_link_libraries(${MY_PROJECT_NAME} curses)  #Link a library to ${MY_PROJECT_NAME}

target_include_directories(${MY_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

