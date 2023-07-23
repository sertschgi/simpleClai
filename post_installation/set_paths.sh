#!/bin/bash

# This script will add your application to the system's PATH during installation

# Set the installation path (adjust if needed)
target_path_install="/opt/${PROJECT_NAME}/bin"

# Add the installation path to the user's .bashrc
echo "export PATH=${target_path_install}:\$PATH" >> $HOME/.bashrc

# Add the installation path to the user's .bash_profile (if it exists)
if [ -e "$HOME/.bash_profile" ]; then
    echo "export PATH=${target_path_install}:\$PATH" >> $HOME/.bash_profile
fi
