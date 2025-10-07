cmake_minimum_required(VERSION 3.10)



find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Charts Concurrent LinguistTools) 

qt_standard_project_setup()

set(CMAKE_AUTORCC ON)

# Автоматически и рекурсивно находим все файлы в текущей директории и поддиректориях.
# CONFIGURE_DEPENDS гарантирует, что CMake перезапустит конфигурацию,
# если вы добавите или удалите файлы.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "*.h")
file(GLOB_RECURSE UI_FILES CONFIGURE_DEPENDS "*.ui")
file(GLOB_RECURSE RESOURCES CONFIGURE_DEPENDS "*.qrc")

# Находим файлы переводов
file(GLOB TS_FILES CONFIGURE_DEPENDS "translations/*.ts")

qt_add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    ${RESOURCES}
)

# Эта команда автоматически скомпилирует .ts файлы в .qm и разместит их
# в поддиректории 'translations' рядом с исполняемым файлом.
qt_add_translations(${PROJECT_NAME}
    TS_FILES ${TS_FILES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Charts Qt6::Concurrent
    libsystem_core project_options
)
