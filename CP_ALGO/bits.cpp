#include <iostream>
#include <bitset> // for printing binary nicely

int main() {
    // 1. Using different base literals
    int decimal = 15;         // Decimal
    int octal = 017;          // Octal (equals decimal 15)
    int hex = 0x0F;           // Hexadecimal (equals decimal 15)
    int binary = 0b00001111;  // Binary (equals decimal 15)

    std::cout << "Decimal: " << decimal << "\n";
    std::cout << "Octal (017): " << octal << "\n";
    std::cout << "Hex (0x0F): " << hex << "\n";
    std::cout << "Binary (0b00001111): " << binary << "\n\n";

    // 2. Using binary literals for bitmasking
    int mask = 0b1011; // bits 0, 1, and 3 are set
    std::cout << "Mask in binary: " << std::bitset<4>(mask) << "\n";

    // 3. Bitwise operations examples
    int bitIndex = 2;
    bool isSet = (mask & (1 << bitIndex)) != 0; // check if bit 2 is set
    std::cout << "Is bit 2 set in mask? " << (isSet ? "Yes" : "No") << "\n";

    // Turn on bit 2
    mask |= (1 << bitIndex);
    std::cout << "Mask after turning on bit 2: " << std::bitset<4>(mask) << "\n";

    // Toggle bit 0
    mask ^= (1 << 0);
    std::cout << "Mask after toggling bit 0: " << std::bitset<4>(mask) << "\n";

    // Turn off bit 3
    mask &= ~(1 << 3);
    std::cout << "Mask after turning off bit 3: " << std::bitset<4>(mask) << "\n\n";

    // 4. Built-in bit operations (GCC/Clang/MSVC)
    int value = mask;
    std::cout << "Number of set bits (__builtin_popcount): " << __builtin_popcount(value) << "\n";
    std::cout << "Leading zeros (__builtin_clz) [32-bit]: " << __builtin_clz(value) << "\n";
    std::cout << "Trailing zeros (__builtin_ctz): " << __builtin_ctz(value) << "\n\n";

    // 5. Avoid octal confusion - no extra example needed here, just remember!

    // 6. Hexadecimal for masks
    constexpr int MASK_4_BITS = 0xF;  // 4 bits set (binary 1111)
    constexpr int ALL_ONES = 0b1111;  // equivalent binary mask
    std::cout << "MASK_4_BITS in binary: " << std::bitset<4>(MASK_4_BITS) << "\n";
    std::cout << "ALL_ONES in binary: " << std::bitset<4>(ALL_ONES) << "\n\n";

    // 7. Practice base conversions mentally - just keep practicing!

    // 8. Meaningful constants (already shown with MASK_4_BITS and ALL_ONES)

    // 9. Visualize states using binary masks (subset generation example)
    int n = 4;  // size of set
    std::cout << "All subsets of set {0,1,2,3} represented as masks:\n";
    for (int subsetMask = 0; subsetMask < (1 << n); subsetMask++) {
        std::cout << std::bitset<4>(subsetMask) << " : { ";
        for (int i = 0; i < n; i++) {
            if (subsetMask & (1 << i)) {
                std::cout << i << " ";
            }
        }
        std::cout << "}\n";
    }

    return 0;
}
