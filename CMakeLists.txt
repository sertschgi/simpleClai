cmake_minimum_required(VERSION 3.24)

# Set the project name
project(sclai)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Find the Qt5 package
find_package(Qt6 COMPONENTS Core REQUIRED)

# Add the executable
add_executable(${PROJECT_NAME}
    main.cpp
    src/commands/dataset.cpp
    src/commands/model.cpp
    src/commands/profile.cpp
    src/commands/project.cpp
    src/commands/frameworks.cpp
    src/core/parser.cpp
    src/utils/tools.cpp
    src/utils/errors.cpp
)

# Include directories for headers
target_include_directories(${PROJECT_NAME}
    PUBLIC
    src/commands
    src/core
    src/utils
    src/config
)

# Add the myparser library submodule
add_subdirectory(external/ClParser)

# Link the Qt5 Core library
target_link_libraries(${PROJECT_NAME} ClParser Qt${QT_VERSION_MAJOR}::Core)


