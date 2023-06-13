#include <chrono>
#include <exception>
#include <iostream>
#include <fides/Base64Decoder.hpp>
#include <fides/Base64Encoder.hpp>
#include <fides/Hasher.hpp>
#include <fides/HexadecimalEncoder.hpp>
#include <fides/MacGenerator.hpp>

int main() {
    try {
        // Psalm 62:5
        const std::string_view keyBase64 = "Rm9yIEdvZCBhbG9uZSBteSBzb3VsIHdhaXRzIGluIHNpbGVuY2UsIGZvciBteSBob3BlIGlzIGZyb20gaGltLg==";
        fides::Base64Decoder base64Decoder;
        const auto key = base64Decoder.getDecoding(keyBase64);
        const std::string nonce = std::to_string(
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
            ).count()
        );
        const std::string_view path = "Christ";
        // Romans 12:21
        const std::string message = "nonce=" + nonce + "&asset=Do not be overcome by evil, but overcome evil with good";
        fides::Hasher sha256hasher("SHA256");
        const auto sha256 = sha256hasher.getHash({nonce, message});
        fides::MacGenerator hmacGenerator("HMAC", "SHA512");
        const auto hmac = hmacGenerator.getMac(key, {path, sha256});
        fides::Base64Encoder base64Encoder(hmac.size());
        std::cout << base64Encoder.getEncoding(hmac) << std::endl;
        // outputs base 64 encoded string (varies according to the nonce value)
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
        return EXIT_FAILURE;
    }
}

