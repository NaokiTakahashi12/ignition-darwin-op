
cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_CXX_STANDARD 17)

find_package(ignition-transport8 REQUIRED log)
if(ignition-transport8_FOUND)
    set(ALL_LINK_LIBRARIES ${ALL_LINK_LIBRARIES}
        ignition-transport8::core
        ${ignition-transport8_LIBRARIES}
    )
    set(ALL_INCLUDE_DIRECTORIES ${ALL_INCLUDE_DIRECTORIES}
        ${ignition-transport8_INCLUDE_DIRS}
    )
else()
    message(FATAL_ERROR " ---- Not found ignition-transport8")
endif()

add_subdirectory(joint_command_publisher)

