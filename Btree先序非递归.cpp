// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <math.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


//中序改变输出结果的位置就变先序
int* inorderTraversal(struct TreeNode* root, int* returnSize){
    //栈
    struct TreeNode* stack[101];
    int top = 0;
    
    //结果链表和计数
    int* res = (int*)malloc(sizeof(int) * 100);
    *returnSize = 0;
    struct TreeNode* p = root;
    while (top != 0||p!= NULL) {

        if (p!= NULL) {
            stack[top] = p;
            res[*returnSize] = stack[top]->val;
            *returnSize = *returnSize + 1;
            top++;
            p = p->right;
        }
        else {
            p = stack[top - 1];//返回父节点
            //弹出结点到结果数组中
            top--;
            //探查右子树
            p = p->left;
        }
        
    }
    return res;
}



int main()
{
    //head->next = NULL;
    
    
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
