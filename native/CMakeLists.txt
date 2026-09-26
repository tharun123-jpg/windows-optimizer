cmake_minimum_required(VERSION 3.22)
project(TharuOptimizer LANGUAGES CXX)

if(NOT WIN32)
  message(FATAL_ERROR "THARU OPTIMIZER Native is a Windows desktop application. Configure this project on Windows with Visual Studio 2022 or a MinGW-w64 toolchain.")
endif()

add_executable(TharuOptimizer WIN32
  src/main.cpp
)

target_compile_features(TharuOptimizer PRIVATE cxx_std_17)
target_compile_definitions(TharuOptimizer PRIVATE
  UNICODE
  _UNICODE
  WINVER=0x0A00
  _WIN32_WINNT=0x0A00
)

if(MSVC)
  target_compile_options(TharuOptimizer PRIVATE /W4 /utf-8 /permissive-)
elseif(MINGW)
  target_compile_options(TharuOptimizer PRIVATE -Wall -Wextra -Wpedantic)
  target_link_options(TharuOptimizer PRIVATE -municode)
else()
  target_compile_options(TharuOptimizer PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(TharuOptimizer PRIVATE
  user32
  gdi32
  advapi32
  dwmapi
)

set_target_properties(TharuOptimizer PROPERTIES
  OUTPUT_NAME "THARU-OPTIMIZER"
  CXX_EXTENSIONS OFF
)
