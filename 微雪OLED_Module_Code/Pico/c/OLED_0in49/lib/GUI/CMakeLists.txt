# Find all source files in a directory
aux_source_directory(. DIR_GUI_SRCS)

include_directories(../Config)
# Adds a library target 
add_library(GUI ${DIR_GUI_SRCS})
target_link_libraries(GUI PUBLIC Config)