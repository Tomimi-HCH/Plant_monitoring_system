# Find all source files in a directory
aux_source_directory(. DIR_Fonts_SRCS)

# Adds a library target 
add_library(Fonts ${DIR_Fonts_SRCS})