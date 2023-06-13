#include "Hasher.hpp"
#include <exception/Exception.hpp>
#include "utility.hpp"

namespace fides {
    Hasher::Hasher(const char *algorithm) :
        mdCtxUniquePtr_(
            []()-> decltype(mdCtxUniquePtr_) {
                EVP_MD_CTX * const mdCtx = EVP_MD_CTX_new();
                if (mdCtx != nullptr) {
                    return {mdCtx, EVP_MD_CTX_free};
                } else {
                    throw exception::RuntimeException(__FILE__, __LINE__, __func__, "failed to create EVP_MD_CTX: [[ ", utility::getErrorString(), " ]]");
                }
            }()
        ),
        mdUniquePtr_(
            [algorithm]() -> decltype(mdUniquePtr_) {
                EVP_MD * const md = EVP_MD_fetch(nullptr, algorithm, nullptr);
                if (md != nullptr) {
                    return {md, EVP_MD_free};
                } else {
                    throw exception::RuntimeException(__FILE__, __LINE__, __func__, "failed to create EVP_MD: [[ ", utility::getErrorString(), " ]]");
                }
            }()
        ),
        hashBuffer_(EVP_MD_get_size(mdUniquePtr_.get()), 0)
    {}

    const std::vector<unsigned char> & Hasher::getHash(DataView data) {
        initialize();
        update(data.getData(), data.getSize());
        finalize();
        return hashBuffer_;
    }

    const std::vector<unsigned char> & Hasher::getHash(std::initializer_list<DataView> dataList) {
        initialize();
        for (auto data : dataList) {
            update(data.getData(), data.getSize());
        }
        finalize();
        return hashBuffer_;
    }

    void Hasher::initialize() const {
        if (EVP_DigestInit_ex(mdCtxUniquePtr_.get(), mdUniquePtr_.get(), nullptr) != 1) {
            throw exception::RuntimeException(__FILE__, __LINE__, __func__, "initialization error: [[ ", utility::getErrorString(), " ]]");
        }
    }

    void Hasher::update(const void *data, std::size_t size) const {
        if (EVP_DigestUpdate(mdCtxUniquePtr_.get(), data, size) != 1) {
            throw exception::RuntimeException(__FILE__, __LINE__, __func__, "update error: [[ ", utility::getErrorString(), " ]]");
        }
    }

    void Hasher::finalize() {
        if (EVP_DigestFinal(mdCtxUniquePtr_.get(), hashBuffer_.data(), nullptr) != 1) {
            throw exception::RuntimeException(__FILE__, __LINE__, __func__, "finalization error: [[ ", utility::getErrorString(), " ]]");
        }
    }
}
