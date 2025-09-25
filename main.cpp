#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>
#include <sstream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "helpers/string_pair_generator.h"
#include "helpers/random_string_generator.h"

std::string SlaSimHash(std::string& input) {
    if (input.empty()) {
        return "";
    }
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
        num += binary[i] << (7 - i%8);
        if (i % 8 == 7) {
            numbers.push_back(num*(i/8+1));
            num = 0;
        }
    }

    long long total = 0;
    for (int n : numbers) {
        total += n;
    }

    std::vector<int> xor_results={binary[0], binary[1], binary[2], binary[3]};
    std::vector<int> temp;
    for (int i = 4; i < binary.size(); i++) {
        temp.push_back(xor_results[i%4] ^ binary[i]);
        if (i%4==3){
            xor_results = temp;
            temp.clear();
        }
    }
    

    long long xor_numerical_value = 0;
    for (int i = 0; i < xor_results.size(); i++) {
        xor_numerical_value += xor_results[i] << (xor_results.size() - 1 - i);
    }

    long long offset = 1;
    for (int i = 0; i < xor_numerical_value; i++) {
        offset *= total;
        offset %= (1LL << 8);
    }

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
        for (int j = 0; j < one_count+offset + 10; j++) {
            partial_numerical_hash *= (zero_count + total + 10 + partial_numerical_hash%10);
            partial_numerical_hash % (1LL << 32) == 0 ? partial_numerical_hash -= 1 : partial_numerical_hash;
            partial_numerical_hash %= (1LL << 32);
        }

        std::stringstream ss;
        ss << std::hex << std::setw(8) << std::setfill('0') << partial_numerical_hash;
        output += ss.str();
    }

    return output;
}

void base_input(std::istream& in, std::string& a) {
    std::getline(in, a);
}

void test_input(std::istream& in) {
    std::string input{};
    std::string line{};
    int lineCount{0};

    while (std::getline(in, line)) {
        input += line + "\n";
        lineCount++;
        if (lineCount > 0 && (lineCount & (lineCount - 1)) == 0) {
            long long average=0;
            for (int i = 0; i < 50; i++){
                using Clock = std::chrono::high_resolution_clock;
                auto start = Clock::now();
                SlaSimHash(input);
                auto end = Clock::now();
                average += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
            std::cout << "Lines: " << lineCount << " Time: " << average / 50     << " ns\n";
        }
    }
    long long average=0;
    for (int i = 0; i < 50; i++){
        using Clock = std::chrono::high_resolution_clock;
        auto start = Clock::now();
        SlaSimHash(input);
        auto end = Clock::now();
        average += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    std::cout << "Full file. Time: " << average / 50     << " ns\n";
}

void collision_test() {
    std::string files[4]={"pairs10.txt", "pairs100.txt", "pairs500.txt", "pairs1000.txt"};
    for (auto & file : files) {
        std::ifstream f("./tests/" + file);
        if (!f) {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }
        std::string line1, line2;
        int collisionCount = 0;
        while (std::getline(f, line1) && std::getline(f, line2)) {
            if (SlaSimHash(line1) == SlaSimHash(line2)) {
                std::cout << "Collision detected in " << file << ":\n" << line1 << "\n" << line2 << "\n";
                collisionCount++;
            }
        }
        std::cout << "Total collisions found in " << file << ": " << collisionCount << "\n";
        f.close();
    }
}

void avalanche_test() {
    std::ifstream f("./input_files/avalanche/pairs.txt");
    if (!f) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
    std::string line1, line2;
    double maxSimHex = 0, minSimHex = 1, avgSimHex = 0;
    double maxSimBin = 0, minSimBin = 1, avgSimBin = 0;
    while (std::getline(f, line1) && std::getline(f, line2)) {
        //std::cout << "Comparing:\n" << line1 << "\n" << line2 << "\n";
        std::string hash1 = SlaSimHash(line1);
        std::string hash2 = SlaSimHash(line2);
        double simCount = 0;
        for (size_t i = 0; i < hash1.size(); i++) {
            if (hash1[i] == hash2[i]) {
                simCount++;
            }
        }
        maxSimHex = std::max(maxSimHex, simCount/64.0);
        minSimHex = std::min(minSimHex, simCount/64.0);
        avgSimHex += simCount/64.0;

        std::string bin1, bin2;
        for (char c : hash1) {
            bin1 += std::bitset<4>(std::stoi(std::string(1, c), nullptr, 16)).to_string();
        }
        for (char c : hash2) {
            bin2 += std::bitset<4>(std::stoi(std::string(1, c), nullptr, 16)).to_string();
        }
        for (size_t i = 0; i < bin1.size(); i++) {
            if (bin1[i] == bin2[i]) {
                simCount++;
            }
        }
        maxSimBin = std::max(maxSimBin, simCount/256.0);
        minSimBin = std::min(minSimBin, simCount/256.0);
        avgSimBin += simCount/256.0;
    }
    std::cout << "Max similarity (hex): " << maxSimHex*100 << "%\n";
    std::cout << "Min similarity (hex): " << minSimHex*100 << "%\n";
    std::cout << "Average similarity (hex): " << (avgSimHex / 100000)*100 << "%\n";

    std::cout << "Max similarity (bin): " << maxSimBin*100 << "%\n";
    std::cout << "Min similarity (bin): " << minSimBin*100 << "%\n";
    std::cout << "Average similarity (bin): " << (avgSimBin / 100000)*100 << "%\n";

    f.close();
}

void salt_test() {
    std::string input;
    std::cout << "Enter text: ";
    std::cin.ignore();
    std::getline(std::cin, input);
    std::string salt = helpers::generateSalt(10);
    std::cout << "Input: " << input << "\n" << "Generated salt: " << salt << "\n";
    std::cout << "Hash without salt: " << SlaSimHash(input) << "\n";
    std::string saltedInput = input + salt;
    std::cout << "Hash with salt: " << SlaSimHash(saltedInput) << "\n";
}

int main() {
    std::string a;
    std::cout<<"Hello. Choose mode:\n1. Input from file\n2. Input from console\n3. Time testing\n4. Collision testing\n5. Avalanche testing\n6. Generate string pairs\n7. Salt test\n8. Exit\n";
    int choice=0;
    std::cin>>choice;
    while (choice != 8){
        if (choice == 1) {
            std::cout << "Enter file name: ";
            std::string filename;
            std::cin >> filename;
            std::ifstream file("./tests/"+filename);
            if (!file) {
                std::cerr << "Error opening file!" << std::endl;
                return 1;
            }
            base_input(file, a);
            file.close();
            std::cout<<"String: "<<a<<" Hash: "<<SlaSimHash(a)<<std::endl;
        } else if (choice == 2) {
            std::cout << "Enter text: ";
            std::cin.ignore();
            base_input(std::cin, a);
            std::cout<<"String: "<<a<<" Hash: "<<SlaSimHash(a)<<std::endl;
        } else if (choice == 3) {
            std::ifstream file("./tests/konstitucija.txt");
            test_input(file);
        }
        else if (choice == 4) {
            collision_test();
        } else if (choice == 5) {
            avalanche_test();
        } else if (choice == 6) {
            std::cout << "Generating 100,000 string pairs of length 10...\n";
            helpers::generate_string_pairs(100000, 10);
            std::cout << "String pairs generated in input_files/avalanche/pairs.txt\n";
        } else if (choice == 7) {
            salt_test();
        } else {
            std::cerr << "Invalid selection!" << std::endl;
            return 1;
        }
        
        std::cout<<"Hello. Choose mode:\n1. Input from file\n2. Input from console\n3. Time testing\n4. Collision testing\n5. Avalanche testing\n6. Generate string pairs\n7. Salt test\n8. Exit\n";
        std::cin>>choice;
    }
    return 0;
}
