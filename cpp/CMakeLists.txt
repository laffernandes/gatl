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

set(VERSION_MAJOR 2)
set(VERSION_MINOR 2)
set(VERSION_PATCH 1)

project(GATL
  VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
  DESCRIPTION "GATL: Geometric Algebra Template Library"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(INSTALL "./include" DESTINATION "${CMAKE_INSTALL_PREFIX}" FILES_MATCHING PATTERN "*.hpp")

configure_file("./cmake/GATLConfig.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/GATLConfig.cmake" @ONLY NEWLINE_STYLE UNIX)
file(INSTALL "${CMAKE_CURRENT_BINARY_DIR}/GATLConfig.cmake" DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/gatl")

configure_file("./cmake/GATLConfigVersion.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/GATLConfigVersion.cmake" @ONLY NEWLINE_STYLE UNIX)
file(INSTALL "${CMAKE_CURRENT_BINARY_DIR}/GATLConfigVersion.cmake" DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/gatl")
