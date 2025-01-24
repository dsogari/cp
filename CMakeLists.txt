cmake_minimum_required(VERSION 3.22)
project(codeforces LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

include_directories(utils cpp-dump)
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

subdirs(codeforces)
subdirs(cses)
subdirs(polygon)
subdirs(playground)
subdirs(timus)