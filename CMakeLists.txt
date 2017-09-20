cmake_minimum_required (VERSION 3.1)
project (Shannon_RNASeq_Cpp)

set (CMAKE_CXX_STANDARD 11)

find_library(METIS_LIB_ABS_PATH metis)
find_package(Boost COMPONENTS system filesystem REQUIRED)

set(SHANNON_SOURCE
	src/encoding.cpp
	src/Kmer_handler.cpp
	src/basic_log.cpp
	src/log.cpp
	src/main.cpp
	src/basic_log.cpp
	src/Contig_handler.cpp
	src/Contig_graph_handler.cpp
	src/local_file_structure.cpp
	#Fasta_reader.cpp
	#Fasta_entry.cpp
)
 
# add the executable
add_executable(Shannon_RNASeq_Cpp ${SHANNON_SOURCE})

target_link_libraries(Shannon_RNASeq_Cpp ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
target_link_libraries(Shannon_RNASeq_Cpp ${METIS_LIB_ABS_PATH})