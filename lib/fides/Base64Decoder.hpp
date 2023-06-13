#ifndef fides_Base64Decoder_hpp
#define fides_Base64Decoder_hpp

#include <string>
#include <vector>
#include "DataView.hpp"

namespace fides {
    class Base64Decoder {
    public:
        const std::vector<unsigned char> & getDecoding(DataView input);

    private:
        std::vector<unsigned char> buffer_;
    };
}

#endif
