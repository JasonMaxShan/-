// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

typedef struct LRUCache{
	int count;
	int key;
	int value;
	LRUCache* next;
	LRUCache* front;
} LRUCache;

LRUCache* head;
LRUCache* tail;

LRUCache* lRUCacheCreate(int capacity) {
	if (capacity > 0) {
		LRUCache* pNode = (LRUCache*)malloc(sizeof(LRUCache));
		head = pNode;
		tail = pNode;
		pNode->next = NULL;
		for (int i = 0; i < capacity; i++)
		{
			LRUCache* pNextNode = (LRUCache*)malloc(sizeof(LRUCache));
			tail->next = pNextNode;
			pNextNode->front = tail;
			tail = tail->next;
			pNextNode->next = NULL;
			pNextNode->count = 0;
			pNextNode->key = NULL;
			pNextNode->value = NULL;
		}
		head->count = capacity;
	}
	return tail;
}

int lRUCacheGet(LRUCache* obj, int key) {
	LRUCache* pNode;
	LRUCache* pResult = NULL;
	for (pNode=head->next; pNode!= NULL;pNode=pNode->next) {
		
		if (pNode->key==key)
		{
			pResult = pNode;
		}
		else
		{
			pNode->count = pNode->count + 1;
		}
	}
	if (pResult != NULL) {
		return 1;
	}
	else
	{
		return -1;
	}
}

void lRUCachePut(LRUCache* obj, int key, int value) {
	LRUCache* pNode;
	LRUCache* pResult = NULL;
	int count=0;
	for (pNode = head->next; pNode != NULL; pNode = pNode->next) {
		if (pNode->key == 0) {
			pResult = pNode;
			break;
		}
		else
		{
			pNode->count = pNode->count + 1;
			if (count<=pNode->count)
			{
				count = pNode->count;
				pResult = pNode;
			}
		}
	}
	pResult->key = key;
	pResult->value = value;
	
}

void lRUCacheFree(LRUCache* obj) {
	free(obj);
}

int main() {
	lRUCacheCreate(2);
	lRUCachePut(head,1,1);
	lRUCachePut(head, 6, 6);
	lRUCachePut(head, 7, 7);
	lRUCachePut(head, 8, 8);
	lRUCacheGet(head, 1);
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
