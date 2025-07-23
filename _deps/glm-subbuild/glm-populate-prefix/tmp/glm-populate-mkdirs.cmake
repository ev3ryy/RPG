# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/jannett/Coding/RPG/_deps/glm-src")
  file(MAKE_DIRECTORY "/home/jannett/Coding/RPG/_deps/glm-src")
endif()
file(MAKE_DIRECTORY
  "/home/jannett/Coding/RPG/_deps/glm-build"
  "/home/jannett/Coding/RPG/_deps/glm-subbuild/glm-populate-prefix"
  "/home/jannett/Coding/RPG/_deps/glm-subbuild/glm-populate-prefix/tmp"
  "/home/jannett/Coding/RPG/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp"
  "/home/jannett/Coding/RPG/_deps/glm-subbuild/glm-populate-prefix/src"
  "/home/jannett/Coding/RPG/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/jannett/Coding/RPG/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/jannett/Coding/RPG/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
