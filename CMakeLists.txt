#
# project: oryol-tbui
#
cmake_minimum_required(VERSION 2.8)
get_filename_component(FIPS_ROOT_DIR "../fips" ABSOLUTE)
include("${FIPS_ROOT_DIR}/cmake/fips.cmake")

include_directories(src)
fips_setup()
fips_project(oryol-tbui)
fips_add_subdirectory(src/TBUI)
fips_finish()


