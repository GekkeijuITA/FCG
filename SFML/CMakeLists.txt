cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB SRC_FILES "src/*.cpp")

# Itera su ogni file sorgente e crea un eseguibile separato
foreach(SRC_FILE ${SRC_FILES})
    # Ottieni il nome del file senza estensione
    get_filename_component(EXECUTABLE_NAME ${SRC_FILE} NAME_WE)

    # Aggiungi un eseguibile con lo stesso nome del file sorgente
    add_executable(${EXECUTABLE_NAME} ${SRC_FILE})
    target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_17)
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE SFML::Graphics)
endforeach()