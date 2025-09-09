cmake_minimum_required(VERSION 3.31)
project(UU)

set(CMAKE_CXX_STANDARD 23)

file(GLOB bits
	"Bits/*.h"
)

file(GLOB detail
	"Detail/*.h"
)

file(GLOB KString
	"String/*.h"
)

add_executable(UU
	test/cmakeTest.cpp
	${Bits}
	${Detail}
	${String}
)

source_group("Include\\Bits" FILES ${bits})
source_group("Include\\Detail" FILES ${detail})
source_group("Include\\String" FILES ${KString})