#ifndef CRYPTO_HASHER_H
#define CRYPTO_HASHER_H

#include <string>

namespace crypto {
    // Standard cryptographic hash functions using OpenSSL
    std::string md5Hash(std::string& input);
    std::string sha1Hash(std::string& input);
    std::string sha256Hash(std::string& input);
}

#endif // CRYPTO_HASHER_H