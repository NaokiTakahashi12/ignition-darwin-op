
cmake_minimum_required(VERSION 3.5)
project(joint_command_publisher)

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

set(ALL_INCLUDE_DIRECTORIES ${ALL_INCLUDE_DIRECTORIES}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(joint_command_publisher SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/src/joint_command_publisher.cpp
)
target_include_directories(joint_command_publisher PUBLIC
    ${LOCAL_INCLUDE_DIRECTORY}
    ${ALL_INCLUDE_DIRECTORIES}
)
target_link_libraries(joint_command_publisher PUBLIC
    ${ALL_LINK_LIBRARIES}
)

add_executable(demo_cmd_pos_node
    ${CMAKE_CURRENT_SOURCE_DIR}/src/demo/cmd_pos_node.cpp
)
target_include_directories(demo_cmd_pos_node PRIVATE
    ${LOCAL_INCLUDE_DIRECTORY}
    ${ALL_INCLUDE_DIRECTORIES}
)
target_link_libraries(demo_cmd_pos_node PRIVATE
    joint_command_publisher
    ${ALL_LINK_LIBRARIES}
)

add_executable(demo_multiple_cmd_pos_node
    ${CMAKE_CURRENT_SOURCE_DIR}/src/demo/joint_command_publisher_node.cpp
)
target_include_directories(demo_multiple_cmd_pos_node PRIVATE
    ${LOCAL_INCLUDE_DIRECTORY}
    ${ALL_INCLUDE_DIRECTORIES}
)
target_link_libraries(demo_multiple_cmd_pos_node PRIVATE
    joint_command_publisher
    ${ALL_LINK_LIBRARIES}
)

