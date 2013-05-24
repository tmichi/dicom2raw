#ifndef DTR_FILE_HPP
#define DTR_FILE_HPP

#include <stddef.h>
#include <iosfwd>
#include <string>
#include <vector>
#include "element.hpp"
#include "information.hpp"
#include "reader.hpp"

namespace dtr
{

//! �t�@�C��
        class File
        {
        public:
                //! �\�z����
                explicit File() {}

                //! ��͂���
                /*!
                    \retval �󕶎���
                        �G���[���������Ȃ�����
                    \retval �G���[���e
                        �G���[����������
                 */
                std::string parse( std::istream& in ); // throw()

                //! ��͂���
                /*!
                    �G���[�����������ꍇ�A��O�𑗏o����B
                 */
                void parse( Reader& reader );

                //! �t�@�C���v���A���u�����擾����
                const std::vector<char>& get_preamble() const {
                        return preamble_;
                }

                //! �����擾����
                const Information& get_information() const {
                        return information_;
                }

                //! �f�[�^�v�f���擾����
                const std::vector<Element>& get_element() const {
                        return element_;
                }

                //! �s�N�Z���f�[�^���擾����
                const void* get_pixel_data() const;

                //! �s�N�Z���f�[�^�������擾����
                size_t get_pixel_data_length() const;

        private:
                std::vector<char> preamble_;
                Information information_;
                std::vector<Element> element_;

                //! �����s��
                explicit File( const File& rhs );

                //! �����s��
                File& operator=( const File& rhs );
        };

} // namespace dtr

#endif
