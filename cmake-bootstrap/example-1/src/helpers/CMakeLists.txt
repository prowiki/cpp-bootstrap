# save all source files to variable `DIR_LIB_SRCS`
aux_source_directory(. DIR_LIB_SRCS)

# build library from all source files
add_library (helper ${DIR_LIB_SRCS})