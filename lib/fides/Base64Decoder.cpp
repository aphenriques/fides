#include "Base64Decoder.hpp"
#include <exception/Exception.hpp>
#include <openssl/evp.h>
#include "utility.hpp"

namespace fides {
    const std::vector<unsigned char> & Base64Decoder::getDecoding(DataView input) {
        buffer_.resize((input.getSize() + 3)/4*3);
        const auto decodeSize = EVP_DecodeBlock(buffer_.data(), input.getData<unsigned char>(), input.getSize());
        if (decodeSize != -1) {
            buffer_.resize(decodeSize);
            return buffer_;
        } else {
            throw exception::RuntimeException(__FILE__, __LINE__, __func__, "failed to decode base 64: [[ ", utility::getErrorString(), " ]], for input: [[ ", std::string_view(input.getData<char>(), input.getSize()), " ]]");
        }
    }
}
