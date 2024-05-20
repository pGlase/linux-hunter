add_executable(LinuxHunter main.cpp memory.cpp mhw_lookup.cpp patterns.cpp utils.cpp ui.cpp wdisplay.cpp fdisplay.cpp)
target_link_libraries(LinuxHunter ncursesw)
set_property(TARGET LinuxHunter PROPERTY CXX_STANDARD 20)
set_property(TARGET LinuxHunter PROPERTY CXX_STANDARD_REQUIRED true)
target_compile_options(LinuxHunter PUBLIC -Werror -Wall -Wextra -Wpedantic)
#TODO: Add -WErr, but there are some uninitalized structs
