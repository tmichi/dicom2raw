#include <dtr/element_dictionary.hpp>
#include <dtr/element_dictionary_data.hpp>

namespace dtr
{

        Element_Dictionary& Element_Dictionary::get_instance()
        {
                static Element_Dictionary instance;
                return instance;
        }

        Element_Dictionary::Element_Dictionary()
        {
                std::pair<const Element_Dictionary_Data*, const Element_Dictionary_Data*> range( get_element_dictionary_data() );
                for ( const Element_Dictionary_Data* i = range.first; i != range.second; ++i ) {
                        insert( i->group_mask, i->element_mask, i->group_number, i->element_number, i->name, i->vr, i->vm, i->retired );
                }
        }

        void Element_Dictionary::insert( uint16_t group_mask, uint16_t element_mask, uint16_t group_number, uint16_t element_number, const std::string& name, const std::string& vr, const std::string& vm, bool retired )
        {
                mask_.insert( Tag( group_mask, element_mask ) );
                dictionary_.insert( std::make_pair( Tag( group_number, element_number ), Element_Dictionary_Item( name, vr, vm, retired ) ) );
        }

        const Element_Dictionary_Item* Element_Dictionary::find( const Tag& tag ) const
        {
                for ( std::set<Tag>::const_reverse_iterator i = mask_.rbegin(); i != mask_.rend(); ++i ) {
                        std::map<Tag, Element_Dictionary_Item>::const_iterator j = dictionary_.find( Tag( tag.get_group_number() & i->get_group_number(), tag.get_element_number() & i->get_element_number() ) );
                        if ( j != dictionary_.end() ) {
                                return &j->second;
                        }
                }
                return 0;
        }

} // namespace dtr
