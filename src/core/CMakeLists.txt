cmake_minimum_required(VERSION 3.10)
project(libsystem_core VERSION 0.1.0)


find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

# Автоматически и рекурсивно находим все файлы в текущей директории и поддиректориях.
# CONFIGURE_DEPENDS гарантирует, что CMake перезапустит конфигурацию,
# если вы добавите или удалите файлы.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "*.h")


add_library(${PROJECT_NAME} SHARED
    ${SOURCES}
    ${HEADERS})


target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Core project_options)
target_compile_definitions(${PROJECT_NAME} PRIVATE LIBSYSTEM_CORE_LIBRARY)


target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Info,
    ${CMAKE_CURRENT_SOURCE_DIR}/Tool,
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils
)
