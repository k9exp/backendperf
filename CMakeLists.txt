cmake_minimum_required(VERSION 3.28)
project(webserver)
set(SOURCE
    webserver.c)
add_executable(${PROJECT_NAME} ${SOURCE})
