# Find all source files in a directory
aux_source_directory(. DIR_OLED_SRCS)

include_directories(../Config)

# Adds a library target 
add_library(OLED ${DIR_OLED_SRCS})
target_link_libraries(OLED PUBLIC Config)