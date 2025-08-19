cmake_minimum_required(VERSION 3.10)
project(libsystem_core VERSION 0.1.0)




# Автоматически и рекурсивно находим все файлы в текущей директории и поддиректориях.
# CONFIGURE_DEPENDS гарантирует, что CMake перезапустит конфигурацию,
# если вы добавите или удалите файлы.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "*.h")

add_library(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS})


target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Info,
    ${CMAKE_CURRENT_SOURCE_DIR}/Tool,
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils
)