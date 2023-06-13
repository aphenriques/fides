#include "Base64Encoder.hpp"
#include <openssl/evp.h>

namespace fides {
    Base64Encoder::Base64Encoder(std::size_t initialInputSize) :
        inputSize_(initialInputSize),
        buffer_((initialInputSize + 2)/3*4, '\0')
    {}

    const std::string & Base64Encoder::getEncoding(DataView input) {
        if (inputSize_ != input.getSize()) {
            inputSize_ = input.getSize();
            buffer_.resize((inputSize_ + 2)/3*4);
        }
        EVP_EncodeBlock(reinterpret_cast<unsigned char *>(buffer_.data()), input.getData<unsigned char>(), input.getSize());
        return buffer_;
    }
}
