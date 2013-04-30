#include <dtr/element_dictionary_item.hpp>

namespace dtr
{

        Element_Dictionary_Item::Element_Dictionary_Item( const std::string& name, const std::string& vr, const std::string& vm, bool retired )
                : name_( name )
                , vr_( vr )
                , vm_( vm )
                , retired_( retired ) {}

} // namespace dtr
