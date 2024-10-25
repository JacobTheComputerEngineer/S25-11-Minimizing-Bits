#include <iostream>
#include <fstream>
#include <set>

// TODO: Model the word bank

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Please input a text file to simulate" << std::endl;
        std::cout << "For example: .\\PDR_demo_2.exe mobydick.txt" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
