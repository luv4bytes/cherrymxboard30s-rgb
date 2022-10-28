cmake_minimum_required(VERSION 3.0.0)
project(cherrymxboard30s-rgb VERSION 0.1.0)

include(CTest)
enable_testing()

include(FindPkgConfig)
pkg_check_modules(LIBUSB libusb-1.0 REQUIRED)

add_compile_options(-Wall)
add_compile_definitions(VERSION="${CMAKE_PROJECT_VERSION}")
add_compile_definitions(PROJECT_URL="https://github.com/luv4bytes/cherrymxboard30s-rgb")

add_executable(cherrymxboard30s-rgb src/main.c
    src/args/args.c
    src/log/log.c
    src/device/device.c
    src/help/help.c
    src/device/lighting.c)

target_link_libraries(cherrymxboard30s-rgb usb-1.0)
target_link_libraries(cherrymxboard30s-rgb m) # math

set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_GENERATOR "TGZ")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Software for controlling RGB lighting on the Cherry MX Board 3.0 S for Linux.")
set(CPACK_PACKAGE_VENDOR "luv4bytes")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION "${CMAKE_PROJECT_VERSION}")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_PACKAGE_CONTACT "https://gitlab.com/luv4bytes/cherrymxboard30s-rgb")
set(CPACK_PACKAGE_SECTION "misc")

INSTALL(TARGETS cherrymxboard30s-rgb RUNTIME DESTINATION bin)
INSTALL(FILES LICENSE "README.md" DESTINATION share/${PROJECT_NAME}/doc)
INSTALL(DIRECTORY doc/img DESTINATION share/${PROJECT_NAME}/doc/doc FILES_MATCHING PATTERN "*")
INSTALL(FILES 50-cherrymx.rules DESTINATION /etc/udev/rules.d)
INSTALL(CODE "execute_process(COMMAND udevadm control --reload-rules)")
INSTALL(CODE "execute_process(COMMAND udevadm trigger)")

include(CPack)
