// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    for (int i = nums1Size; i >=0 ; i--)
    {
        if (n <= 0) {
            break;
        }
        else {
            if (m>0&&nums1[m - 1] >= nums2[n - 1]) {
                nums1[i - 1] = nums1[m - 1];
                m--;
            }
            else
            {
                nums1[i - 1] = nums2[n - 1];
                n--;
            }
        } 
    }
}

int main()
{
    int num1[] = { 0 };
    int num2[] = { 1 };
    int num1Size = sizeof(num1)/sizeof(num1[0]);
    int num2Size = sizeof(num2)/ sizeof(num2[0]);
    merge(num1, num1Size, 0, num2, num1Size, 1);
    for (int i = 0; i < num1Size; i++) {
        printf("%d ", num1[i]);
    }
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
