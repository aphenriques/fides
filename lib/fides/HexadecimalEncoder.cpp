#include "HexadecimalEncoder.hpp"
#include <exception/Exception.hpp>
#include <openssl/crypto.h>
#include "utility.hpp"

namespace fides {
    HexadecimalEncoder::HexadecimalEncoder(std::size_t initialInputSize) :
        inputSize_(initialInputSize),
        buffer_(getEncodingSize(initialInputSize), '\0')
    {}

    const std::string & HexadecimalEncoder::getEncoding(DataView input) {
        if (inputSize_ != input.getSize()) {
            inputSize_ = input.getSize();
            buffer_.resize(getEncodingSize(inputSize_));
        }
        // https://en.cppreference.com/w/cpp/string/basic_string/data
        // The returned array is null-terminated, that is, data() and c_str() perform the same function. (since C++11)
        if (OPENSSL_buf2hexstr_ex(buffer_.data(), buffer_.size() + 1, nullptr, input.getData<unsigned char>(), inputSize_, '\0') == 1) {
            return buffer_;
        } else {
            throw exception::RuntimeException(__FILE__, __LINE__, __func__, "hexadecimal encoding error: [[ ", utility::getErrorString(), " ]]");
        }
    }

    std::size_t HexadecimalEncoder::getEncodingSize(std::size_t inputSize) {
        return 2*inputSize;
    }
}
