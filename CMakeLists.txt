cmake_minimum_required(VERSION 3.2)

project(FindWdk)

set(LE_PROJECT_NAME sample-windows-driver)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4 /WX")



set(WDK_ADDITIONAL_FLAGS_FILE "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/wdkflags.h")
file(WRITE ${WDK_ADDITIONAL_FLAGS_FILE} "#pragma runtime_checks(\"suc\", off)")


set(WDK_COMPILE_FLAGS
        "/GS-" #disable security cookes
        "/Zp8" # set struct alignment
        "/GF"  # enable string pooling
        "/GR-" # disable RTTI
        "/Gz" # __stdcall by default
        "/kernel"  # create kernel mode binary
        "/Oi" # enable intrinsic functions so that you can use functions like _disable or _enable
        "/Zi"
        "/FIwarning.h" # disable warnings in WDK headers
        "/FI${WDK_ADDITIONAL_FLAGS_FILE}" # include file to disable RTC (only for cl.exe)
        "/D ARCHITECTURE_AMD64"
)


string(CONCAT WDK_LINK_FLAGS
        "/MANIFEST:NO " #
        "/DRIVER " #
        "/OPT:REF " #
        "/INCREMENTAL:NO " #
        "/OPT:ICF " #
        "/SUBSYSTEM:NATIVE " #
        "/MERGE:_TEXT=.text;_PAGE=PAGE " #
        "/NODEFAULTLIB " # do not link default CRT
        "/SECTION:INIT,d " #
        "/VERSION:10.0 " #
)




list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(WDK REQUIRED)

wdk_add_driver(${LE_PROJECT_NAME}
        KMDF 1.15
        src/driver.c
)

#create certificate if it does not exist and store it in .pfx file
add_custom_command(
        POST_BUILD
        TARGET ${LE_PROJECT_NAME}
        COMMAND powershell.exe -ExecutionPolicy Bypass -File "${CMAKE_CURRENT_SOURCE_DIR}/create_certificate.ps1"
)


#sign the .sys file
add_custom_command(
        POST_BUILD
        TARGET ${LE_PROJECT_NAME}
        COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/signtool_amd64.exe" sign /f "${CMAKE_CURRENT_SOURCE_DIR}/MyTestCert.pfx" /p "password123" /td sha256 /fd sha256 "${LE_PROJECT_NAME}.sys"
)
