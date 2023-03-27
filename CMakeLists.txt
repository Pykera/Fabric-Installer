cmake_minimum_required(VERSION 3.24)
project(Fabric_Installer C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(Fabric_Installer main.c helpers/downloader.h helpers/url_verifier.h helpers/env_checker.h)
target_link_libraries(Fabric_Installer -lcurl)
