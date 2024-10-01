#include <lib/array.h>

int main(int argv, char** argc) {
    using namespace ArrayUInt17_t;

    Array arr(2, 2, 3);

    arr[0][0][0] = 1;
    arr[1][0][0] = 2;
    arr[0][1][0] = 4;
    arr[1][1][0] = 8;
    arr[0][0][1] = 16;
    arr[1][0][1] = 32;
    arr[0][1][1] = 64;
    arr[1][1][1] = 128;
    arr[0][0][2] = 256;
    arr[1][0][2] = 512;
    arr[0][1][2] = 1024;
    arr[1][1][2] = 2048;

    arr.PrintArray();

    Array arr2 = arr * 2;

    arr2.PrintArray();

    Array arr3 = arr + arr2;

    arr3.PrintArray();

    Array arr4 = arr * arr2;

    arr4.PrintArray();

    std::cin >> arr4[1][1][2];

    arr4.PrintArray();

    std::cout << arr4[1][1][2] << std::endl;

    return 0;
}