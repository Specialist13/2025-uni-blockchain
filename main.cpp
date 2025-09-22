#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>
#include <sstream>

std::string SlaSimHash(std::string& input) {
    std::vector<int> binary;
    std::string output;

    for (char c : input) {
        std::string bin = std::bitset<8>(c).to_string();
        for (char b : bin) {
            binary.push_back(b == '1' ? 1 : 0);
        }
    }

    std::vector<int> numbers;

    int num=0;

    for (int i = 0; i < binary.size(); i++) {
        num += 1 << (7 - i%8);
        if (i % 8 == 7) {
            numbers.push_back(num);
            num = 0;
        }
    }

    int average = 0;
    double log2 = 0;
    for (int n : numbers) {
        average += n;
    }
    log2 = std::log2(average);
    average /= numbers.size();

    for (int i = 0; i < 8; i++) {
        int zero_count = 0;
        int one_count = 0;

        for (int j = input.size()*i; j < input.size()*(i+1); j ++) {
            if (binary[j] == 0) {
                zero_count++;
            } else {
                one_count++;
            }
        }

        long long partial_numerical_hash=1;
        for (int j = 0; j < one_count+log2; j++) {
            partial_numerical_hash *= (zero_count + average);
            partial_numerical_hash %= (1LL << 32);
        }

        std::stringstream ss;
        ss << std::hex << partial_numerical_hash;
        output += ss.str();
    }

    return output;
}


int main() {
    std::string a = "Hello world";
    std::cout<<SlaSimHash(a);
    return 0;
}