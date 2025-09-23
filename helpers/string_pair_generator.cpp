#include "string_pair_generator.h"

#include <filesystem>
#include <fstream>
#include <random>

namespace helpers {

void generate_string_pairs(
    const StringPairGeneratorOptions &options) {
    // Input validation
    if (options.pairCount == 0 || options.stringLength == 0 || options.alphabet.empty()) {
        return;
    }
    
    // Create output directory if it doesn't exist
    std::filesystem::create_directories(options.outputDirectory);
    
    // Setup random number generation
    std::random_device rd;
    std::mt19937 gen(options.seed == 0 ? rd() : options.seed);
    std::uniform_int_distribution<std::size_t> pos_dist(0, options.stringLength - 1);
    std::uniform_int_distribution<std::size_t> char_dist(0, options.alphabet.size() - 1);
    
    // Generate pairs
    for (std::size_t i = 0; i < options.pairCount; ++i) {
        // Generate random base string
        std::string base(options.stringLength, ' ');
        for (std::size_t j = 0; j < options.stringLength; ++j) {
            base[j] = options.alphabet[char_dist(gen)];
        }
        
        // Create second string with exactly one different character
        std::string modified = base;
        std::size_t diff_pos = pos_dist(gen);
        char new_char;
        do {
            new_char = options.alphabet[char_dist(gen)];
        } while (new_char == base[diff_pos]);
        modified[diff_pos] = new_char;
        
        // Write to files
        std::string filename_a = options.outputDirectory + "/pair_" + std::to_string(i) + "_a.txt";
        std::string filename_b = options.outputDirectory + "/pair_" + std::to_string(i) + "_b.txt";
        
        std::ofstream file_a(filename_a);
        std::ofstream file_b(filename_b);
        
        if (file_a.is_open()) file_a << base;
        if (file_b.is_open()) file_b << modified;
    }
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
