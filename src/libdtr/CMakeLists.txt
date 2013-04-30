ADD_LIBRARY(dtr STATIC element.cpp 
		   	  element_dictionary.cpp 
			  element_dictionary_data.cpp 
			  element_dictionary_item.cpp 
			  file.cpp 
			  information.cpp 
			  reader.cpp 
			  tag.cpp 
			  uid_dictionary.cpp 
			  uid_dictionary_data.cpp 
			  uid_dictionary_item.cpp 
			  value.cpp )
INCLUDE_DIRECTORIES(../../include)
INSTALL(TARGETS dtr
	LIBRARY
	DESTINATION lib
	ARCHIVE DESTINATION lib)

