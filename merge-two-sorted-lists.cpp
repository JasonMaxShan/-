// ConsoleApplication2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

typedef struct ListNode {
    int val;
    struct ListNode *next;
};
struct ListNode* createList(int val, int step) {
    ListNode* ptemp, * node, * head;
    head = (ListNode*)malloc(sizeof(ListNode));
    head->next = NULL;
    node = head;
    for (int i = 0; i < val; i++)
    {
        ptemp = (ListNode*)malloc(sizeof(ListNode));
        ptemp->val = i+step;
        ptemp->next = nullptr;
        node->next = ptemp;
        node = node->next;
    }
    return head->next;
}
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    ListNode *head,*prev;
    head= (ListNode*)malloc(sizeof(ListNode));
    prev = head;
    while (list1&& list2) {
        if (list1->val<=list2->val)
        {
            prev->next = list1;
            list1 = list1->next;
        }
        else
        {
            prev->next = list2;
            list2 = list2->next;
        }
        prev = prev->next;
    }
    if (list1) {
        prev->next=list1;
    }
    if(list2)
    {
        prev->next=list2;
    }
    return head->next;
}
int main()
{
    ListNode* list1, *list2,*list3;
    list1 = createList(3, 1);
    list2 = createList(3, 2);
    list3 = mergeTwoLists(list1, list2);
    return 0;

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
