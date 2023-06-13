#include <exception>
#include <iostream>
#include <fides/Base64Decoder.hpp>
#include <fides/Base64Encoder.hpp>

int main() {
    try {
        // Ecclesiastes 1:9
        const std::string_view input =
            "What has been is what will be, and what has been done is what will be done; and there is nothing new under the sun";
        fides::Base64Encoder base64Encoder(input.size());
        const std::string encoding = base64Encoder.getEncoding(input);
        std::cout << encoding << std::endl;
        // output: V2hhdCBoYXMgYmVlbiBpcyB3aGF0IHdpbGwgYmUsIGFuZCB3aGF0IGhhcyBiZWVuIGRvbmUgaXMgd2hhdCB3aWxsIGJlIGRvbmU7IGFuZCB0aGVyZSBpcyBub3RoaW5nIG5ldyB1bmRlciB0aGUgc3Vu
        fides::Base64Decoder base64Decoder;
        const std::vector<unsigned char> decoding = base64Decoder.getDecoding(encoding);
        std::cout << std::string_view(reinterpret_cast<const char *>(decoding.data()), decoding.size()) << std::endl;
        // output:
        // What has been is what will be, and what has been done is what will be done; and there is nothing new under the sun
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
        return EXIT_FAILURE;
    }
}

