#include <exception>
#include <iostream>
#include <fides/Hasher.hpp>
#include <fides/HexadecimalEncoder.hpp>

int main() {
    try {
        // Luke 12:2
        const std::string_view data1 = "Everything now covered up will be uncovered, and everything now hidden will be made clear.";
        fides::Hasher sha256("SHA256");
        std::vector<unsigned char> hash = sha256.getHash(data1);
        fides::HexadecimalEncoder hexadecimalEncoder(hash.size());
        std::cout << hexadecimalEncoder.getEncoding(hash) << std::endl;
        // output: AFB452896979287073A137F6421E1458CF434D8FC0759D116B5BAC10D25FB18F

        // encoder and hasher reuse; hashing multiple inputs without concatenation:
        // Proverbs 12:22
        const std::string_view data2 = "Lying lips are an abomination to the Lord, but those who act faithfully are his delight.";
        std::cout << hexadecimalEncoder.getEncoding(sha256.getHash({data1, data2})) << std::endl;
        // output: AE8A0D9EBAECA5BAD6321458D370062AF1A66CBC5685E2756A0A10DD3EF3EC2A
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
        return EXIT_FAILURE;
    }
}

