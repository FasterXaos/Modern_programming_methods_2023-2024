target_sources(sortings_lib 
	PRIVATE
		bubble_sort.cpp
		heap_sort.cpp
		insertion_sort.cpp
		merge_sort.cpp
		quick_sort.cpp
		radix_sort.cpp
		selection_sort.cpp
		shell_sort.cpp
	PUBLIC
		bubble_sort.hpp
		heap_sort.hpp
		insertion_sort.hpp
		merge_sort.hpp
		quick_sort.hpp
		radix_sort.hpp
		selection_sort.hpp
		shell_sort.hpp
)

target_include_directories(sortings_lib PUBLIC
	"${PROJECT_SOURCE_DIR}/src"
)
