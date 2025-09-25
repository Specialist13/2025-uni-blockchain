#include "../helpers/random_string_generator.h"

namespace helpers {

std::string generateSalt(size_t length = 10) {
    const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, charset.size() - 1);

    std::string salt;
    for (size_t i = 0; i < length; ++i) {
        salt += charset[dist(gen)];
    }
    return salt;
}

} // namespace helpers