#include "MacGenerator.hpp"
#include <openssl/core_names.h>
#include <exception/Exception.hpp>
#include "utility.hpp"

namespace fides {
    MacGenerator::MacGenerator(const char *algorithm, const char *digest, const char *cipher) :
        macUniquePtr_(
            [algorithm]() -> decltype(macUniquePtr_) {
                EVP_MAC * const mac = EVP_MAC_fetch(nullptr, algorithm, nullptr);
                if (mac != nullptr) {
                    return {mac, EVP_MAC_free};
                } else {
                    throw exception::RuntimeException(__FILE__, __LINE__, __func__, "failed to create EVP_MAC: [[ ", utility::getErrorString(), " ]]");
                }
            }()
        ),
        macCtxUniquePtr_(
            [this]()-> decltype(macCtxUniquePtr_) {
                EVP_MAC_CTX * const macCtx = EVP_MAC_CTX_new(macUniquePtr_.get());
                if (macCtx != nullptr) {
                    return {macCtx, EVP_MAC_CTX_free};
                } else {
                    throw exception::RuntimeException(__FILE__, __LINE__, __func__, "failed to create EVP_MAC_CTX: [[ ", utility::getErrorString(), " ]]");
                }
            }()
        ),
        digest_(digest != nullptr ? digest : ""),
        cipher_(cipher != nullptr ? cipher : ""),
        osslParameters_(
            [this] {
                std::array<OSSL_PARAM, 3> osslParameters;
                auto parameterIterator = osslParameters.begin();
                // https://en.cppreference.com/w/cpp/string/basic_string/data:
                // The returned array is null-terminated, that is, data() and c_str() perform the same function. (since C++11)
                if (digest_.empty() == false) {
                    // OSSL_PARAM_construct_utf8_string takes a char * (not const char *), that is why digest_ is used and digest is not used directly
                    *parameterIterator++ = OSSL_PARAM_construct_utf8_string(OSSL_MAC_PARAM_DIGEST, digest_.data(), 0);
                }
                if (cipher_.empty() == false) {
                    *parameterIterator++ = OSSL_PARAM_construct_utf8_string(OSSL_MAC_PARAM_CIPHER, cipher_.data(), 0);
                }
                *parameterIterator = OSSL_PARAM_construct_end();
                return osslParameters;
            }()
        )
    {}

    const std::vector<unsigned char> & MacGenerator::getMac(DataView key, DataView data) {
        initialize(key.getData<unsigned char>(), key.getSize());
        update(data.getData<unsigned char>(), data.getSize());
        finalize();
        return outputBuffer_;
    }

    const std::vector<unsigned char> & MacGenerator::getMac(DataView key, std::initializer_list<DataView> dataList) {
        initialize(key.getData<unsigned char>(), key.getSize());
        for (auto data : dataList) {
            update(data.getData<unsigned char>(), data.getSize());
        }
        finalize();
        return outputBuffer_;
    }

    void MacGenerator::initialize(const unsigned char *key, std::size_t keySize) const {
        if (EVP_MAC_init(macCtxUniquePtr_.get(), key, keySize, osslParameters_.data()) != 1) {
            throw exception::RuntimeException(__FILE__, __LINE__, __func__, "initialization error: [[ ", utility::getErrorString(), " ]]");
        }
    }

    void MacGenerator::update(const unsigned char *data, std::size_t dataSize) const {
        if (EVP_MAC_update(macCtxUniquePtr_.get(), data, dataSize) != 1) {
            throw exception::RuntimeException(__FILE__, __LINE__, __func__, "update error: [[ ", utility::getErrorString(), " ]]");
        }
    }

    void MacGenerator::finalize() {
        std::size_t outputSize;
        // Make a call to the final with a NULL buffer to get the length of the MAC
        if (EVP_MAC_final(macCtxUniquePtr_.get(), nullptr, &outputSize, 0) == 1) {
            // https://en.cppreference.com/w/cpp/container/vector/resize
            // Resizes the container to contain count elements, does nothing if count == size()
            outputBuffer_.resize(outputSize, 0);
            if (EVP_MAC_final(macCtxUniquePtr_.get(), outputBuffer_.data(), &outputSize, outputBuffer_.size()) != 1) {
                throw exception::RuntimeException(__FILE__, __LINE__, __func__, "final error: [[ ", utility::getErrorString(), " ]]");
            }
        } else {
            throw exception::RuntimeException(__FILE__, __LINE__, __func__, "final error (get size): [[ ", utility::getErrorString(), " ]]");
        }
    }
}
