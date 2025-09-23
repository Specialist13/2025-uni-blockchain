#ifndef STRING_PAIR_GENERATOR_H
#define STRING_PAIR_GENERATOR_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace helpers {

struct StringPairGeneratorOptions {
    std::size_t pairCount = 100000;
    std::size_t stringLength = 10;
    std::string alphabet =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::uint64_t seed = 0;
    std::string outputDirectory = "input_files/avalanche";
};

void generate_string_pairs(
    const StringPairGeneratorOptions &options);

void generate_string_pairs(
    std::size_t pairCount, std::size_t stringLength = 10,
    const std::string &outputDirectory = "input_files/avalanche");

} // namespace helpers

#endif // STRING_PAIR_GENERATOR_H
