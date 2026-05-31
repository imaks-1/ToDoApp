cmake_minimum_required(VERSION 3.15)

project(ToDoApp)

set(CMAKE_CXX_STANDARD 17)

add_library(messageManager SHARED
    messageManager.cpp
    accountSysCli.cpp
)

add_library(window SHARED
    window.cpp
)
add_library(AccountWindow SHARED
    AccountWindow.cpp
)

add_library(menu SHARED
    menu.cpp
)
add_library(WindowManager SHARED
    WindowManager.cpp
)

add_executable(ToDoApp
    ToDoApp.cpp
)

set_target_properties(ToDoApp PROPERTIES WIN32_EXECUTABLE TRUE)