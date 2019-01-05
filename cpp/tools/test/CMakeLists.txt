# Copyright (C) 2018 Leandro Augusto Frata Fernandes
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

project(GATL-Test)

enable_testing()

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(target_prefix gatl_test_)

set(test_groups
  core_operations
  core_products
  extra
  miscellaneous
  sign_change_operations
  size
  util
)

include_directories(${GTEST_INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}/../../include")

foreach(test_group ${test_groups})
  file(GLOB test_filenames RELATIVE "${PROJECT_SOURCE_DIR}/${test_group}" ${PROJECT_SOURCE_DIR}/${test_group}/*.cpp)
  foreach(test_filename ${test_filenames})
    string(REPLACE ".cpp" "" test_name ${test_filename})
    add_executable(${target_prefix}${test_group}_${test_name} "${PROJECT_SOURCE_DIR}/${test_group}/${test_filename}")
    target_include_directories(${target_prefix}${test_group}_${test_name} PUBLIC ${PROJECT_SOURCE_DIR}/${test_group})
    target_link_libraries(${target_prefix}${test_group}_${test_name} ${GTEST_BOTH_LIBRARIES})
    add_test(${target_prefix}${test_group}_${test_name} ${target_prefix}${test_group}_${test_name})
  endforeach()
endforeach()
