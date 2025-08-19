cmake_minimum_required(VERSION 3.10)
project(system_infoQt VERSION 0.1.0 LANGUAGES CXX)

# Создаем INTERFACE библиотеку для хранения общих настроек компиляции
add_library(project_options INTERFACE)

# Устанавливаем стандарт C++ для всех, кто использует эту библиотеку
target_compile_features(project_options INTERFACE cxx_std_20)

# Отключаем нестандартные расширения компилятора
set_property(TARGET project_options PROPERTY CXX_EXTENSIONS OFF)

# Добавляем опции компилятора
# $<CXX_COMPILER_ID:GNU,Clang> - это generator expression, которое применит флаги
# только для компиляторов GCC и Clang.
target_compile_options(project_options INTERFACE
    # Общие флаги для GCC и Clang
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-pedantic>

    # Флаги для Release сборки: высокая оптимизация
    $<$<CONFIG:Release>:-O3>

    # Флаги для Debug сборки: без оптимизации и с отладочными символами
    $<$<CONFIG:Debug>:-O0;-g>
)

add_subdirectory(src)
