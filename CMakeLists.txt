cmake_minimum_required(VERSION 3.30)
project(webserver)
set(SOURCE
    webserver.c)
add_executable(${PROJECT_NAME} ${SOURCE})
