#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>
#include <sstream>
#include <fstream>
#include <chrono>
#include "helpers/string_pair_generator.h"
#include "hash_algorithms/personal_hash.h"

static PersonalHash personal;

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
                personal.hash(input);
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
        personal.hash(input);
        auto end = Clock::now();
        average += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    std::cout << "Full file. Time: " << average / 50     << " ns\n";
}

void collision_input() {
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
            if (personal.hash(line1) == personal.hash(line2)) {
                std::cout << "Collision detected in " << file << ":\n" << line1 << "\n" << line2 << "\n";
                collisionCount++;
            }
        }
        std::cout << "Total collisions found in " << file << ": " << collisionCount << "\n";
        f.close();
    }
}

int main() {
    std::string a;
    std::cout<<"Hello. Choose mode:\n1. Input from file\n2. Input from console\n3. Time testing\n4. Collision testing\n5. Generate string pairs\n6. Exit\n";
    int choice=0;
    std::cin>>choice;
    while (choice != 6){
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
        } else if (choice == 2) {
            std::cout << "Enter text: ";
            std::cin.ignore();
            base_input(std::cin, a);
        } else if (choice == 3) {
            std::ifstream file("./tests/konstitucija.txt");
            test_input(file);
        }
        else if (choice == 4) {
            collision_input();
        } else if (choice == 5) {
            std::cout << "Generating 100,000 string pairs of length 10...\n";
            helpers::generate_string_pairs(100000, 10);
            std::cout << "String pairs generated in input_files/avalanche/pairs.txt\n";
        } else {
            std::cerr << "Invalid selection!" << std::endl;
            return 1;
        }
        std::cout<<personal.hash(a)<<std::endl;
        std::cout<<"Hello. Choose mode:\n1. Input from file\n2. Input from console\n3. Time testing\n4. Collision testing\n5. Generate string pairs\n6. Exit\n";
        std::cin>>choice;
    }
    return 0;
}
