# Set the project name
project(sclai)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Find the Qt5 package
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

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
    PRIVATE
    src/commands
    src/core
    src/utils
    src/config
)

# Link the Qt5 Core library
target_link_libraries(${PROJECT_NAME} ${QT_VERSION_MAJOR}::Core)

# Add the myparser library submodule
add_subdirectory(external/ClParser)

# Link the myparser library to your project
target_link_libraries(${PROJECT_NAME} ClParser)

# Install targets and files
install(TARGETS ${PROJECT_NAME}
    DESTINATION /usr/bin
)

# Install config files
install(FILES
    config/config.h
    DESTINATION /etc/${PROJECT_NAME}/scripts/config
)

# Install script files
install(FILES
    scripts/*
    DESTINATION /etc/${PROJECT_NAME}/scripts/scripts
)
