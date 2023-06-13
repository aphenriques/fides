#ifndef fides_Hasher_hpp
#define fides_Hasher_hpp

#include <initializer_list>
#include <memory>
#include <vector>
#include <openssl/evp.h>
#include "DataView.hpp"

namespace fides {
    class Hasher {
    public:
        Hasher(const char *algorithm);

        const std::vector<unsigned char> & getHash(DataView data);
        const std::vector<unsigned char> & getHash(std::initializer_list<DataView> dataList);

    private:
        const std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> mdCtxUniquePtr_;
        const std::unique_ptr<EVP_MD, decltype(&EVP_MD_free)> mdUniquePtr_;
        std::vector<unsigned char> hashBuffer_;

        void initialize() const;
        void update(const void *data, std::size_t size) const;
        void finalize();
    };
}

#endif
