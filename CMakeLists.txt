cmake_minimum_required(VERSION 3.24)
project(Fabric_Installer C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Fabric_Installer main.c helpers/downloader.h helpers/url_verifier.h helpers/env_checker.h helpers/get_latest_mc.h helpers/start_server.h helpers/install_server.h)
target_link_libraries(Fabric_Installer -lcurl -ljson-c -lz -lssl -lcrypto -lgssapi_krb5)
