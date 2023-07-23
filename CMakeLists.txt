cmake_minimum_required(VERSION 3.10)
project(simpleCLai)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Uncomment the following line to disable the usage of deprecated Qt APIs
# add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x060000)

# Add the source files
set(SOURCES
    main.cpp
    src/commands/dataset.cpp
    src/commands/model.cpp
    src/commands/profile.cpp
    src/commands/project.cpp
    src/core/parser.cpp
    src/utils/tools.cpp
)

# Add the header files
set(HEADERS
    src/commands/dataset.h
    src/commands/model.h
    src/commands/profile.h
    src/commands/project.h
    src/core/parser.h
    src/utils/tools.h
)

# Find the Qt package and include the core module
find_package(Qt6 COMPONENTS Core REQUIRED)

# Find Python
find_package(Python REQUIRED COMPONENTS Development)

# Add the executable and link against Qt Core
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core)

# Include Python headers
target_include_directories(${PROJECT_NAME} PRIVATE ${Python_INCLUDE_DIRS})

# Link against Python library
target_link_libraries(${PROJECT_NAME} PRIVATE ${Python_LIBRARIES})

# Install target and files for deployment
set(target_path_install "/opt/${PROJECT_NAME}/bin")  # Change this path to the desired installation path

# Install the binary executable to the specified path
install(TARGETS ${PROJECT_NAME} DESTINATION "${target_path_install}")

# Install all files in the config folder
file(GLOB config_files "config/*")
install(FILES ${config_files} DESTINATION "${target_path_install}/config")

# Install all files in the script folder
file(GLOB script_files "scripts/*")
install(FILES ${script_files} DESTINATION "${target_path_install}/scripts")

# Create and install the Debian package using CPack
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_CONTACT "Your Name <your.email@example.com>")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Your Name <your.email@example.com>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Brief description of your package")
set(CPACK_PACKAGE_VERSION "1.0.0") # Set your package version
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON) # Enable automatic library dependency detection

include(CPack)
