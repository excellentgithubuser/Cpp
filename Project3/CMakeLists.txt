cmake_minimum_required(VERSION 3.10)

project(test)

aux_source_directory(. DIR_SRCS)

add_executable(test ${DIR_SRCS})