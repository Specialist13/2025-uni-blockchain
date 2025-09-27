#include "crypto_hasher.h"
#include <windows.h>
#include <wincrypt.h>
#include <sstream>
#include <iomanip>
#include <vector>

#pragma comment(lib, "advapi32.lib")

namespace crypto {
    
    // Helper function to convert binary hash to hex string
    std::string bytesToHex(const BYTE* bytes, DWORD length) {
        std::stringstream ss;
        for (DWORD i = 0; i < length; ++i) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bytes[i]);
        }
        return ss.str();
    }

    // Generic Windows CryptoAPI hash function
    std::string computeHash(const std::string& input, ALG_ID algId) {
        HCRYPTPROV hProv = 0;
        HCRYPTHASH hHash = 0;
        std::string result;
        
        if (CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
            if (CryptCreateHash(hProv, algId, 0, 0, &hHash)) {
                if (CryptHashData(hHash, (BYTE*)input.c_str(), (DWORD)input.length(), 0)) {
                    DWORD hashLen = 0;
                    DWORD dataLen = sizeof(DWORD);
                    
                    if (CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE*)&hashLen, &dataLen, 0)) {
                        std::vector<BYTE> hash(hashLen);
                        if (CryptGetHashParam(hHash, HP_HASHVAL, hash.data(), &hashLen, 0)) {
                            result = bytesToHex(hash.data(), hashLen);
                        }
                    }
                }
                CryptDestroyHash(hHash);
            }
            CryptReleaseContext(hProv, 0);
        }
        
        return result;
    }
    
    std::string md5Hash(std::string& input) {
        return computeHash(input, CALG_MD5);
    }
    
    std::string sha1Hash(std::string& input) {
        return computeHash(input, CALG_SHA1);
    }
    
    std::string sha256Hash(std::string& input) {
        // Note: CALG_SHA_256 requires Windows Vista or later
        return computeHash(input, CALG_SHA_256);
    }
}