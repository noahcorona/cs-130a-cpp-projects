#include <iostream>
#include <bitset>
using namespace std;

int main() {
    uint32_t temp = 0xFFFFFFFF;
    uint32_t Hour = 0x11;
    uint32_t Minute = 0x11;
    uint32_t Second = 0x11;

    std::bitset<32> a(temp);
    std::cout << a << '\n';

    a &= ~(1UL << 22);
    a &= ~(3UL << 20);
    a &= ~(0xF << 16);
    a &= ~(0x7 << 12);
    a &= ~(0xF << 8);
    a &= ~(0x7 << 4);
    a &= ~(0xF);

    std::cout << a << '\n';

    a |= (Second & 0xF);
    a |= (Second & 0xF0);
    a |= (Minute & 0xF) << 8;
    a |= (Minute & 0xF0) << 8;
    a |= (Hour & 0xF) << 16;
    a |= (Hour & 0xF0) << 16;

    std::cout << a << '\n';

    std::bitset<32> secU(Second & 0xF);
    std::bitset<32> secT(Second & 0xF0);
    std::bitset<32> minU(Second & 0xF);
    std::bitset<32> minT(Second & 0xF0);
    std::bitset<32> hrU(Second & 0xF);
    std::bitset<32> hrT(Second & 0xF0);

    std::cout << "Hours (T then U): \n" << hrT << '\n' << hrU << '\n';
    std::cout << "\nMinutes (T then U): \n" << minT << '\n' << minU << '\n';
    std::cout << "\nSeconds (T then U): \n" << secT << '\n' << secU << '\n';


    return 0;
}