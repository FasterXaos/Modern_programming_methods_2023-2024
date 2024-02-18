target_sources(radix_sort_mf 
	PRIVATE
		radix_sort.cpp
		radix_sort.hpp
)

target_include_directories(radix_sort_mf PRIVATE
	"${PROJECT_SOURCE_DIR}/sortings"
)