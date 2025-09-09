cmake_minimum_required(VERSION 3.31)
project(UU)

set(CMAKE_CXX_STANDARD 23)

file(GLOB bits
	"bits/*.h"
)

file(GLOB detail
	"detail/*.h"
)

file(GLOB KString
	"string/*.h"
)

add_executable(UU
	test/cmakeTest.cpp
	${bits}
	${detail}
	${string}
)

source_group("Include\\Bits" FILES ${bits})
source_group("Include\\Detail" FILES ${detail})
source_group("Include\\String" FILES ${KString})