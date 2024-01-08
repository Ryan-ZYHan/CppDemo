#include <iostream>
#include <algorithm>
/* 测试判断整型数组的内容是否一致 */
bool isArrayEqualTo0111(int arr[], int size)
{
    int target[4] = {1, 1, 1, 1};
    return std::equal(arr, arr + size, target);
}

int main()
{
    int myArray[4] = {1, 1, 1, 1};

    if (isArrayEqualTo0111(myArray, 4))
    {
        std::cout << "Array contains 1, 1, 1, 1." << std::endl;
    }
    else
    {
        std::cout << "Array does not contain 0, 1, 1, 1." << std::endl;
    }

    return 0;
}
