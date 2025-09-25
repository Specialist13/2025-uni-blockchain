#ifndef RANDOM_STRING_GENERATOR_H
#define RANDOM_STRING_GENERATOR_H

#include <string>
#include <random>

namespace helpers {

std::string generateSalt(size_t length);

}   // namespace helpers

#endif // RANDOM_STRING_GENERATOR_H