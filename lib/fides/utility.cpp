#include "utility.hpp"
#include <openssl/err.h>

namespace fides::utility {
    std::string getErrorString() {
        auto errorCode = ERR_get_error();
        if (errorCode != 0) {
            char stringBuffer[512];
            ERR_error_string_n(errorCode, stringBuffer, sizeof(stringBuffer));
            std::string errorString = stringBuffer;
            while ((errorCode = ERR_get_error()) != 0) {
                ERR_error_string_n(errorCode, stringBuffer, sizeof(stringBuffer));
                errorString += "; ";
                errorString += stringBuffer;
            }
            return errorString;
        } else {
            return {};
        }
    }
}
