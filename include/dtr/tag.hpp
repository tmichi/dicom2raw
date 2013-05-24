#ifndef DTR_TAG_HPP
#define DTR_TAG_HPP

#include <stdint.hpp>
#include "reader.hpp"

namespace dtr
{

//! �f�[�^�v�f�^�O
        class Tag
        {
        public:
                //! �\�z����
                explicit Tag();

                //! �\�z����
                /*!
                    \param[in] group_number
                        �O���[�v�ԍ�
                    \param[in] element_number
                        �v�f�ԍ�
                 */
                explicit Tag( uint16_t group_number, uint16_t element_number );

                //! ��͂���
                bool parse( Reader& reader );

                //! �O���[�v�ԍ����擾����
                uint16_t get_group_number() const {
                        return group_number_;
                }

                //! �v�f�ԍ����擾����
                uint16_t get_element_number() const {
                        return element_number_;
                }

                //! ��������
                void swap( Tag& rhs );

                //! ���l�ł���
                bool operator==( const Tag& rhs ) const {
                        return group_number_ == rhs.group_number_ && element_number_ == rhs.element_number_;
                }

                //! ���l�łȂ�
                bool operator!=( const Tag& rhs ) const {
                        return ! operator==( rhs );
                }

                //! ��r����
                bool operator<( const Tag& rhs ) const;

        private:
                uint16_t group_number_;
                uint16_t element_number_;
        };

} // namespace dtr

#endif
