#include <exception>
#include <iostream>
#include <fides/Base64Encoder.hpp>
#include <fides/MacGenerator.hpp>

int main() {
    try {
        // 2 Thessalonians 3:16-17
        const std::string_view key1 =
            "May the Lord of peace himself give you peace at all times and in every way. The Lord be with you all";
        const std::string_view data1 =
            "I, Paul, write this greeting with my own hand. This is the mark in every letter of mine; it is the way I write";
        fides::MacGenerator hmacGenerator("HMAC", "SHA512", nullptr);
        std::vector<unsigned char> hmac = hmacGenerator.getMac(key1, data1);
        fides::Base64Encoder base64Encoder(hmac.size());
        std::cout << base64Encoder.getEncoding(hmac) << std::endl;
        // output: IudC3sCp5O3ambfhVbxrX6a0lQjGXGB6/9/cKH2hTlPWvAIWGbrFEZ0fIsvvCP1tQls8QjSSD0LW9EBsBK6keQ==

        // encoder and mac generator reuse; mac generation with multiple inputs without concatenation:
        // 2 Timothy 3:16-17
        const std::string_view key2 =
            "All scripture is inspired by God and profitable for teaching, for reproof, for correction, and for training in righteousness";
        const std::string_view data2 =
            "that the man of God may be complete, equipped for every good work";
        hmac = hmacGenerator.getMac(key2, {data1, data2});
        std::cout << base64Encoder.getEncoding(hmac) << std::endl;
        // output: PuR9kgswHvE30sN97vALz8v5x8ZackpICTpneDy8rlM2DhsOT4VTJaJ0GS0toxhvwxN5OoYBvZYOrbYp14i7Lw==
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
        return EXIT_FAILURE;
    }
}

