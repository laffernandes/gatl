# Copyright (C) Leandro Augusto Frata Fernandes
# 
# author     : Fernandes, Leandro A. F.
# e-mail     : laffernandes@ic.uff.br
# home page  : http://www.ic.uff.br/~laffernandes
# repository : https://github.com/laffernandes/gatl.git
# 
# This file is part of The Geometric Algebra Template Library (GATL).
# 
# GATL is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# GATL is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GATL. If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.10)

project(GATL-Example)

find_package(GATL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(target_prefix gatl_example_)

set(example_groups
  concepts
  miscelaneos
)

include_directories(${GATL_INCLUDE_DIRS})

foreach(example_group ${example_groups})
  file(GLOB example_filenames RELATIVE "${PROJECT_SOURCE_DIR}/${example_group}" ${PROJECT_SOURCE_DIR}/${example_group}/*.cpp)
  foreach(example_filename ${example_filenames})
    string(REPLACE ".cpp" "" example_name ${example_filename})
    add_executable(${target_prefix}${example_group}_${example_name} "${PROJECT_SOURCE_DIR}/${example_group}/${example_filename}")
    target_include_directories(${target_prefix}${example_group}_${example_name} PUBLIC ${PROJECT_SOURCE_DIR}/${example_group})
    target_link_libraries(${target_prefix}${example_group}_${example_name})
  endforeach()
endforeach()
