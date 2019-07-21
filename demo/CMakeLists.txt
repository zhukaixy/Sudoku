cmake_minimum_required(VERSION 3.0)
project(demo
	VERSION 1.0.0
	# DESCRIPTION "Demo for testing"
	# HOMEPAGE_URL "www.zhyingkun.com"
	LANGUAGES C CXX)

add_subdirectory(for-c)
add_subdirectory(for-cs)
add_subdirectory(for-lua)
add_subdirectory(for-nodejs)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET for-c PROPERTY FOLDER "demo")
