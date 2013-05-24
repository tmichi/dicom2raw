SET (include_files dtr.hpp stdint.hpp stdint_msc.h )
SET (dtr_include_files dtr/element.hpp
      dtr/element_dictionary.hpp
      dtr/element_dictionary_data.hpp
      dtr/element_dictionary_item.hpp
      dtr/file.hpp
      dtr/information.hpp
      dtr/invalid_format.hpp
      dtr/invalid_vr.hpp
      dtr/reader.hpp
      dtr/tag.hpp
      dtr/uid_dictionary.hpp
      dtr/uid_dictionary_data.hpp
      dtr/uid_dictionary_item.hpp
      dtr/unexpected_eof.hpp
      dtr/unsupported_transfer_syntax.hpp
      dtr/value.hpp )

INSTALL( FILES ${include_files}
         DESTINATION include
         PERMISSIONS OWNER_READ GROUP_READ WORLD_READ )

INSTALL( FILES ${dtr_include_files}
         DESTINATION include/dtr
         PERMISSIONS OWNER_READ GROUP_READ WORLD_READ )
