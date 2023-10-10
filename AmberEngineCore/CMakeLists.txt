cmake_minimum_required(VERSION 3.12)

set(CORE_PROJECT_NAME AmberEngineCore)

add_library(${CORE_PROJECT_NAME} STATIC
	src/AmberEngineCore/Utils/test.cpp
	includes/AmberEngineCore/Utils/test.hpp
)

target_include_directories(${CORE_PROJECT_NAME} PUBLIC includes)
target_compile_features(${CORE_PROJECT_NAME} PUBLIC cxx_std_17)