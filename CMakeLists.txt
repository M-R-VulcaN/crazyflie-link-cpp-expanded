cmake_minimum_required (VERSION 3.5)
project(crazyflie-link-cpp)


# Enable C++14 and warnings
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
  # Avoid min/max macros in Windows.h (pulled in from libusb)
  add_definitions(-DNOMINMAX)
  # warning level 4
  # Ideally we would also treat warnings as errors (/WX), but there are still some warnings to fix
  add_compile_options(/W4)
else()
  # lots of warnings and all warnings as errors
  add_compile_options(-Wall -Wextra -Werror)
endif()


# dependencies
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/tools/build)
find_package(libusb REQUIRED)

set(BITCRAZE_INCLUDE ${CMAKE_SOURCE_DIR}/include/bitcraze)
set(M_R_VULKAN_INCLUDE ${CMAKE_SOURCE_DIR}/include/M-R-VulkaN)

include_directories(
  ${BITCRAZE_INCLUDE}
  ${M_R_VULKAN_INCLUDE}
  ${LIBUSB_INCLUDE_DIR}
)

# C++ library

add_library(crazyflieLinkCpp
  src/bitcraze/USBManager.cpp
  src/bitcraze/Connection.cpp
  src/bitcraze/USBDevice.cpp
  src/bitcraze/Crazyradio.cpp
  src/bitcraze/CrazyradioThread.cpp
  src/bitcraze/CrazyflieUSB.cpp
  src/bitcraze/CrazyflieUSBThread.cpp
  src/bitcraze/Version.cpp

  
  src/M-R-VulkaN/ConnectionWorker.cpp
  src/M-R-VulkaN/Crazyflie.cpp
  src/M-R-VulkaN/Toc.cpp
  src/M-R-VulkaN/Log.cpp
  src/M-R-VulkaN/Param.cpp
  src/M-R-VulkaN/AppChannel.cpp
  src/M-R-VulkaN/CrtpTocProtocol.cpp
)

# target_include_directories(libCrazyflieLinkCpp
#   PUBLIC
#     $<INSTALL_INTERFACE:include/crazyflie_cpp>
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/crazyflie_cpp>
# )

# Apple macOS libraries
if (APPLE)
  set(CMAKE_EXE_LINKER_FLAGS "-lobjc -framework IOKit -framework CoreFoundation")
  set(CMAKE_MODULE_LINKER_FLAGS "-lobjc -framework IOKit -framework CoreFoundation")
endif()

# Link pthread on Linux and Mac only
if (NOT MSVC)
target_link_libraries(crazyflieLinkCpp
  PRIVATE
    pthread
)
endif()

target_link_libraries(crazyflieLinkCpp
  PRIVATE
    ${LIBUSB_LIBRARY}
)
set_property(TARGET crazyflieLinkCpp PROPERTY POSITION_INDEPENDENT_CODE ON)

# C++ example application

# example_console
add_executable(example_console
  examples/bitcraze/console.cpp
)
target_link_libraries(example_console
  crazyflieLinkCpp
)

# example_scan
add_executable(example_scan
  examples/bitcraze/scan.cpp
)
target_link_libraries(example_scan
  crazyflieLinkCpp
)

# example_benchmark
add_executable(example_benchmark
  examples/bitcraze/benchmark.cpp
)
target_link_libraries(example_benchmark
  crazyflieLinkCpp
)

# # example_basicLog
# add_executable(example_basicLog
#   examples/M-R-VulkaN/basicLog.cpp
# )
# target_link_libraries(example_basicLog
#   crazyflieLinkCpp
# )

# # example_basicLogRead
# add_executable(example_basicLogRead
#   examples/M-R-VulkaN/basicLogRead.cpp
# )
# target_link_libraries(example_basicLogRead
#   crazyflieLinkCpp
# )

# # example_basicToc
# add_executable(example_basicToc
#   examples/M-R-VulkaN/basicToc.cpp
# )
# target_link_libraries(example_basicToc
#   crazyflieLinkCpp
# )

# # example_appChannelTest
# add_executable(example_appChannelTest
#   examples/M-R-VulkaN/appChannelTest.cpp
# )
# target_link_libraries(example_appChannelTest
#   crazyflieLinkCpp
# )

# # example_logViaAppChannel
# add_executable(example_logViaAppChannel
#   examples/M-R-VulkaN/logViaAppChannel.cpp
# )
# target_link_libraries(example_logViaAppChannel
#   crazyflieLinkCpp
# )

# # example_basicParamCSV
# add_executable(example_basicParamCSV
#   examples/M-R-VulkaN/basicParamCSV.cpp
# )
# target_link_libraries(example_basicParamCSV
#   crazyflieLinkCpp
# )
