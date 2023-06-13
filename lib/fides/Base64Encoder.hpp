#ifndef fides_Base64Encoder_hpp
#define fides_Base64Encoder_hpp

#include <string>
#include "DataView.hpp"

namespace fides {
    class Base64Encoder {
    public:
        Base64Encoder(std::size_t initialInputSize = 0);

        const std::string & getEncoding(DataView input);

    private:
        std::size_t inputSize_;
        std::string buffer_;
    };
}

#endif
