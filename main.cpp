#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>
#include <sstream>
#include <fstream>

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
        num += 1 << (7 - i%8);
        if (i % 8 == 7) {
            numbers.push_back(num*(i/8+1));
            num = 0;
        }
    }

    long long average = 0;
    for (int n : numbers) {
        average += n;
    }
    average /= numbers.size();

    

    std::vector<int> xor_results={binary[0], binary[1], binary[2], binary[3]};
    for (int i = 4; i < binary.size(); i++) {
        std::vector<int> temp;
        for (int j = 0; j < xor_results.size(); j++) {
            temp.push_back(xor_results[j] ^ binary[i]);
        }
        xor_results = temp;
    }

    long long xor_numerical_value = 0;
    for (int i = 0; i < xor_results.size(); i++) {
        xor_numerical_value += xor_results[i] << (xor_results.size() - 1 - i);
    }

    long long offset = 1;
    for (int i = 0; i < xor_numerical_value; i++) {
        offset *= average;
        offset %= (1LL << 32);
    }

    offset = log2(offset);

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
            partial_numerical_hash *= (zero_count + average + 10 + partial_numerical_hash%10);
            partial_numerical_hash % (1LL << 32) == 0 ? partial_numerical_hash -= 1 : partial_numerical_hash;
            partial_numerical_hash %= (1LL << 32);
        }

        

        std::stringstream ss;
        ss << std::hex << partial_numerical_hash;
        output += ss.str();
    }

    return output;
}

void ivestis(std::istream& in, std::string& a) {
    std::getline(in, a);
}

int main() {
    std::string a;
    std::cout<<"Sveiki. Pasirinkite ivesties buda:\n1. Ivesti is failo\n2. Ivesti per konsole\n3. Baigti darba\n";
    int pasirinkimas=0;
    std::cin>>pasirinkimas;
    while (pasirinkimas != 3){
        if (pasirinkimas == 1) {
            std::cout << "Iveskite failo pavadinima: ";
            std::string filename;
            std::cin >> filename;
            std::ifstream file("./tests/"+filename);
            if (!file) {
                std::cerr << "Klaida atidarant faila!" << std::endl;
                return 1;
            }
            ivestis(file, a);
            file.close();
        } else if (pasirinkimas == 2) {
            std::cout << "Iveskite teksta: ";
            std::cin.ignore();
            ivestis(std::cin, a);
        } else {
            std::cerr << "Neteisingas pasirinkimas!" << std::endl;
        
            return 1;
        }
        std::cout<<SlaSimHash(a)<<std::endl;
        std::cout<<"Pasirinkite ivesties buda:\n1. Ivesti is failo\n2. Ivesti per konsole\n3. Baigti darba\n";
        std::cin>>pasirinkimas;
    }
    return 0;
}