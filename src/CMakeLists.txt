cmake_minimum_required(VERSION 3.10)



find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

qt_standard_project_setup()

# Автоматически и рекурсивно находим все файлы в текущей директории и поддиректориях.
# CONFIGURE_DEPENDS гарантирует, что CMake перезапустит конфигурацию,
# если вы добавите или удалите файлы.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "*.h")
file(GLOB_RECURSE UI_FILES CONFIGURE_DEPENDS "*.ui")
file(GLOB_RECURSE RESOURCES CONFIGURE_DEPENDS "*.qrc")


qt_add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    ${RESOURCES}
)


target_link_libraries( ${PROJECT_NAME}
    PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui
    project_options
)
