cmake_minimum_required(VERSION 3.20)
project(Simple_Banking_System CXX)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        glfw
        URL https://github.com/glfw/glfw/archive/refs/tags/3.4.zip
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
        imgui
        URL https://github.com/ocornut/imgui/archive/refs/tags/v1.90.4.zip
)
FetchContent_MakeAvailable(imgui)

set(IMGUI_SOURCES
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

include_directories(src/core ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)

add_executable(Simple_Banking_System
        src/main.cpp
        src/core/Account.h
        src/core/Account.cpp
        src/core/Bank.h
        src/core/Bank.cpp
        ${IMGUI_SOURCES}
)

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

target_link_libraries(Simple_Banking_System PRIVATE
        glfw
        OpenGL::GL
        Threads::Threads
        ${CMAKE_DL_LIBS}
)

add_subdirectory(tests)