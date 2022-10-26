// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
typedef struct MinStack{
    int val;
    int current_min;
    struct MinStack* next;
} MinStack;
void minStackFree(MinStack* obj);

MinStack* minStackCreate() {
    MinStack* head;
    head = (MinStack*)malloc(sizeof(MinStack));
    head->current_min = 0;
    head->val = 0;
    head->next = NULL;
    return head;
}

void minStackPush(MinStack* obj, int val) {
    MinStack* pTemp;
    pTemp = (MinStack*)malloc(sizeof(MinStack));
    pTemp->val = val;
    if (obj->next == NULL) {
        pTemp->current_min = val;
    }
    else {
        if (obj->next->current_min<=val)
        {
            pTemp->current_min = obj->next->current_min;
        }
        else
        {
            pTemp->current_min = val;
        }
    }
    pTemp->next = obj->next;
    obj->next = pTemp;
}

void minStackPop(MinStack* obj) {
    MinStack* node;
    node = obj->next;
    obj->next = node->next;
    minStackFree(node);
}

int minStackTop(MinStack* obj) {
    return obj->next->val;
}

int minStackGetMin(MinStack* obj) {
    return obj->next->current_min;
}

void minStackFree(MinStack* obj) {
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);

 * minStackPop(obj);

 * int param_3 = minStackTop(obj);

 * int param_4 = minStackGetMin(obj);

 * minStackFree(obj);
*/
int main()
{
    MinStack* obj = minStackCreate();
    minStackPush(obj, -2);
    minStackPush(obj, 0);
    minStackPush(obj, -3);
    int param_4 = minStackGetMin(obj);
    minStackPop(obj);
    int param_5 = minStackTop(obj);
    int param_6 = minStackGetMin(obj);
    return 0;
}

