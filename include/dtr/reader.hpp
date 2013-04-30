#ifndef DTR_READER_HPP
#define DTR_READER_HPP

#include <stddef.h>
#include <iosfwd>

namespace dtr {

//! バイナリデータリーダ
class Reader {
public:
    //! 構築する
    explicit Reader(std::istream& in);

    //! リトルエンディアンで読み込むように設定する
    void set_little_endian(bool little_endian);

    //! 読み込む
    /*!
        要素のサイズが2以上で、入力データとホストのエンディアンが異なる場合、エンディアン交換処理を行う。

        \param[out] buffer
            要素のサイズと個数をかけただけの容量を持つ出力先バッファ
        \param[in] size
            要素のサイズ
        \param[in] count
            要素の個数
     */
    void read(void* buffer, size_t size, size_t count);

    //! 型情報付きで読み込む
    /*!
        sizeof(T)が2以上で、入力データとホストのエンディアンが異なる場合、エンディアン交換処理を行う。
     */
    template <typename T>
    void read(T& value) {
        read(&value, sizeof(value), 1);
    }

    //! 先頭位置からのオフセットを設定する
    void seek_beg(size_t offset);

    //! 現在位置からのオフセットを設定する
    void seek_cur(size_t offset);

private:
    std::istream& in_;
    bool endian_swap_;

    //! 複製不可
    explicit Reader(const Reader& rhs);

    //! 複製不可
    Reader& operator=(const Reader& rhs);
};

} // namespace dtr

#endif
