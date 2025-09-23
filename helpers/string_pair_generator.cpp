#include "string_pair_generator.h"

#include <random>

namespace helpers {

void generate_string_pairs(
    const StringPairGeneratorOptions &options) {
    // TODO: implement input validation, generation, and file writing
    (void)options; // silence unused parameter warning for now
}

void generate_string_pairs(
    std::size_t pairCount, std::size_t stringLength,
    const std::string &outputDirectory) {
    StringPairGeneratorOptions opts;
    opts.pairCount = pairCount;
    opts.stringLength = stringLength;
    opts.outputDirectory = outputDirectory;
    generate_string_pairs(opts);
}

} // namespace helpers
