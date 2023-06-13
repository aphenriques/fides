# fides

`fides` is a C++ wrapper for some openssl routines:

* message authentication code (MAC);
* hash functions;
* hexadecimal encoding; and
* base 64 encoding and decoding.


# Requirements

* C++20 compiler; and
* libssl and libcrypto.


# Build

Grab the `dependecies/exception/include/exception` directory and all the source files (*.hpp and *.cpp) in the `lib/fides` directory and build (there is no preprocessor configuration for the library).

Alternatively, build and install the library with:

    $ make
    $ make install


# Usage

```cpp
#include <chrono>
#include <exception>
#include <iostream>
#include <fides/Base64Decoder.hpp>
#include <fides/Base64Encoder.hpp>
#include <fides/Hasher.hpp>
#include <fides/HexadecimalEncoder.hpp>
#include <fides/MacGenerator.hpp>

int main() {
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
}

```

See [example](sample/hmacAuth/main.cpp).


# Source

`fides`'s Git repository is available on GitHub, which can be browsed at:

    http://github.com/aphenriques/fides

and cloned with:

    git clone --recurse-submodules git://github.com/aphenriques/fides.git


# Author

`fides` was made by André Pereira Henriques [aphenriques (at) outlook (dot) com].


# Donation

* BTC: 1BdPza4JSYxKt4YAgPm579ZEqK2hHQNfij
* ETH: 0xc8eD4EcCAd66BD928EB9B1696a05AeFf8DBA699e


# License

MIT License

Copyright (c) 2023 André Henriques

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
