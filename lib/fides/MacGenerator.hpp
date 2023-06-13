#ifndef fides_MacGenerator_hpp
#define fides_MacGenerator_hpp

#include <array>
#include <string>
#include <vector>
#include <openssl/evp.h>
#include <openssl/params.h>
#include "DataView.hpp"

namespace fides {
    class MacGenerator {
    public:
        MacGenerator(const char *algorithm, const char *digest, const char *cipher = nullptr);

        const std::vector<unsigned char> & getMac(DataView key, DataView data);
        const std::vector<unsigned char> & getMac(DataView key, std::initializer_list<DataView> dataList);

    private:
        const std::unique_ptr<EVP_MAC, decltype(&EVP_MAC_free)> macUniquePtr_;
        const std::unique_ptr<EVP_MAC_CTX, decltype(&EVP_MAC_CTX_free)> macCtxUniquePtr_;
        std::vector<unsigned char> outputBuffer_;
        std::string digest_;
        std::string cipher_;
        const std::array<OSSL_PARAM, 3> osslParameters_;

        void initialize(const unsigned char *key, std::size_t keySize) const;
        void update(const unsigned char *data, std::size_t dataSize) const;
        void finalize();
    };
}

#endif
