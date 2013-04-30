ADD_EXECUTABLE(dicom2raw dicom2raw.cpp
			 dicom2raw_epilogue_html.hpp
			 dicom2raw_prologue_html.hpp )

INSTALL(TARGETS dicom2raw
	RUNTIME
	DESTINATION bin)
INCLUDE_DIRECTORIES(../../include)
TARGET_LINK_LIBRARIES( dicom2raw dtr)
