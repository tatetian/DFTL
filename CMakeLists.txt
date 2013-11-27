cmake_minimum_required(VERSION 2.6)
project(DFTL)
set(CMAKE_C_FLAGS "-Wall")
add_executable(test_dftl test_dftl.c flash.c mem.c misc.c dftl.c hash_table.c
	cmt.c)
add_executable(test_hash_table test_hash_table.c hash_table.c)
add_executable(test_cmt test_cmt.c cmt.c hash_table.c)
