
add_library(utility STATIC)
luastg_target_common_options(utility)
luastg_target_more_warning(utility)
target_include_directories(utility PUBLIC .)
set(utility_sources
    utility/encoding.hpp
    utility/encoding.cpp
    utility/path.hpp
    utility/path.cpp
)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${utility_sources})
target_sources(utility PRIVATE ${utility_sources})
