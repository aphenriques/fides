#ifndef fides_HexadecimalEncoder_hpp
#define fides_HexadecimalEncoder_hpp

#include <string>
#include "DataView.hpp"

namespace fides {
    class HexadecimalEncoder {
    public:
        HexadecimalEncoder(std::size_t initialInputSize = 0);

        const std::string & getEncoding(DataView input);

    private:
        static std::size_t getEncodingSize(std::size_t inputSize);

        std::size_t inputSize_;
        std::string buffer_;
    };
}

#endif
