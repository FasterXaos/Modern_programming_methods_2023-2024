target_sources(radix_sort_mf 
	PRIVATE
		radix_sort.cpp
)

target_include_directories(radix_sort_mf PRIVATE
	"${CURRENT_SOURCE_DIR}"
)
