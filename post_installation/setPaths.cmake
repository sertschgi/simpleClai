set(install_path @target_path_install@)

file(APPEND "$ENV{HOME}/.bashrc" "export PATH=${install_path}:\$PATH\n")
if (EXISTS "$ENV{HOME}/.bash_profile")
    file(APPEND "$ENV{HOME}/.bash_profile" "export PATH=${install_path}:\$PATH\n")
endif()

message("added ${install_path}")
