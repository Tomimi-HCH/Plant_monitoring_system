# Find all source files in a directory
aux_source_directory(. DIR_examples_SRCS)
# Include Directories
include_directories(../lib/Config)
include_directories(../lib/OLED)
include_directories(../lib/Fonts)
include_directories(../lib/GUI)

# Adds a library target 
add_library(examples ${DIR_examples_SRCS})
target_link_libraries(examples PUBLIC Config OLED )