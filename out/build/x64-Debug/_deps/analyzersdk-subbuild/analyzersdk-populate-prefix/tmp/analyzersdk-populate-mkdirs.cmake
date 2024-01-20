# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/languages/c/nled-async-pixel-analyzer/out/build/x64-Debug/_deps/analyzersdk-src"
  "C:/languages/c/nled-async-pixel-analyzer/out/build/x64-Debug/_deps/analyzersdk-build"
  "C:/languages/c/nled-async-pixel-analyzer/out/build/x64-Debug/_deps/analyzersdk-subbuild/analyzersdk-populate-prefix"
  "C:/languages/c/nled-async-pixel-analyzer/out/build/x64-Debug/_deps/analyzersdk-subbuild/analyzersdk-populate-prefix/tmp"
  "C:/languages/c/nled-async-pixel-analyzer/out/build/x64-Debug/_deps/analyzersdk-subbuild/analyzersdk-populate-prefix/src/analyzersdk-populate-stamp"
  "C:/languages/c/nled-async-pixel-analyzer/out/build/x64-Debug/_deps/analyzersdk-subbuild/analyzersdk-populate-prefix/src"
  "C:/languages/c/nled-async-pixel-analyzer/out/build/x64-Debug/_deps/analyzersdk-subbuild/analyzersdk-populate-prefix/src/analyzersdk-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/languages/c/nled-async-pixel-analyzer/out/build/x64-Debug/_deps/analyzersdk-subbuild/analyzersdk-populate-prefix/src/analyzersdk-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/languages/c/nled-async-pixel-analyzer/out/build/x64-Debug/_deps/analyzersdk-subbuild/analyzersdk-populate-prefix/src/analyzersdk-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
