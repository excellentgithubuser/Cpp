cmake_minimum_required(VERSION 3.10)

project(mul)

aux_source_directory(. DIR_SRCS)

add_executable(mul ${DIR_SRCS})