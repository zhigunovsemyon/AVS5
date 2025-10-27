# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("AVS5" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
file(GLOB CXX_FILES "src/*.cc")
set(STACK_SIZE "10000000000000")

find_package(OpenMP)

if (WIN32)
	add_definitions("/W4 /WX") #Wall цепляет ошибки из OpenMP
	add_definitions("/openmp:llvm")
	#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:${STACK_SIZE}")
else ()
	#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,${STACK_SIZE}")
	add_definitions("-Wall -Wextra -Werror -Wconversion -Wsign-conversion")
endif(WIN32)

add_executable (${PROJECT_NAME} ${CXX_FILES}) 
target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)

