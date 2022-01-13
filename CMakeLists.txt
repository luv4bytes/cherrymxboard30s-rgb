cmake_minimum_required(VERSION 3.0.0)
project(cherrymxboard30s-rgb VERSION 0.1.0)

include(CTest)
enable_testing()

add_compile_options(-Wall)
add_compile_definitions(VERSION="${CMAKE_PROJECT_VERSION}")

add_executable(cherrymxboard30s-rgb src/main.c
                                    src/args/args.c
                                    src/log/log.c
                                    src/device/device.c
                                    src/help/help.c
                                    src/device/lighting.c)

target_link_libraries(cherrymxboard30s-rgb usb-1.0)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
