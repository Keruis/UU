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
	"KString/*.h"
)

add_executable(UU
	test/cmakeTest.cpp
	${bits}
	${detail}
	${KString}
)

source_group("Include\\bits" FILES ${bits})
source_group("Include\\detail" FILES ${detail})
source_group("Include\\KString" FILES ${KString})