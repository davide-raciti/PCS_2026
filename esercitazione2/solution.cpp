# include <iostream>

int main()
{
    double ad[4] = {0.0, 1.1, 2.2, 3.3};  // 8*4 byte
    float af[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};  // 4*8 byte
    int ai[3] = {0, 1, 2};  // 4*3 byte

    int x = 1;  // 4 byte
    float y = 1.1;  // 4 byte

    (&y)[1] = 0; 

    std::cout << x << "\n";
    // std::cout << &ad[0] << "\n";
    // std::cout << &af[0] << "\n";
    // std::cout << &ai[0] << "\n";
    std::cout << &y << "\n";
    std::cout << &x << "\n";

    return 0;
}