set(target_path_install "/opt/simpleClai/bin")

file(APPEND "$ENV{HOME}/.bashrc" "export PATH=${target_path_install}:\$PATH\n")
if (EXISTS "$ENV{HOME}/.bash_profile")
    file(APPEND "$ENV{HOME}/.bash_profile" "export PATH=${target_path_install}:\$PATH\n")
endif()

message("added: ${target_path_install}")
