cmake_minimum_required(VERSION 3.10)

project(calculator)

aux_source_directory(. DIR_SRCS)

add_executable(calculator ${DIR_SRCS})