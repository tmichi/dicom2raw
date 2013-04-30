#include <iostream>
#include <dtr/uid_dictionary.hpp>
#include <dtr/uid_dictionary_data.hpp>

namespace dtr
{

        Uid_Dictionary& Uid_Dictionary::get_instance()
        {
                static Uid_Dictionary instance;
                return instance;
        }

        Uid_Dictionary::Uid_Dictionary()
        {
                std::pair<const Uid_Dictionary_Data*, const Uid_Dictionary_Data*> range( get_uid_dictionary_data() );
                for ( const Uid_Dictionary_Data* i = range.first; i != range.second; ++i ) {
                        insert( i->uid, i->name, i->type );
                }
        }

        void Uid_Dictionary::insert( const std::string& uid, const std::string& name, const std::string& type )
        {
                dictionary_.insert( std::make_pair( uid, Uid_Dictionary_Item( name, type ) ) );
        }

        const Uid_Dictionary_Item* Uid_Dictionary::find( const std::string& uid ) const
        {
                std::map<std::string, Uid_Dictionary_Item>::const_iterator i = dictionary_.find( uid );
                return i == dictionary_.end() ? 0 : &i->second;
        }

} // namespace dtr
