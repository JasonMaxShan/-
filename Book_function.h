#pragma once
#pragma once
#include<time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#define Maxsize 100

#define F_PATH "C:/Users/1028s/Desktop/ConsoleApplication1/book_inf.txt"
typedef struct book {
    int book_id;
    char* book_name;
    char* book_author;
    int Now_stock;
    int Total;
}Book;
//����ṹ��
typedef struct node {
    Book book;
    struct node* next;
} Node;
//���������ṹ��
typedef struct SeqList
{
    int asc[Maxsize];
    Node* address[Maxsize];
    int length;//��ǰԪ����Ŀ
}Name_SeqList;

Node* booklist;// ����������ͷָ��
Node* booklistTail;// ����������βָ��
Node* find;//��������ͷָ��
Node* findTail;//��������βָ��
Name_SeqList* index; //��������˳���
//��������

void show_allbook(Node* node, int cas);
void revise();
void reviseinf(Node* node, const char* str, int cas);
void add();
Node* addinf(char* info);
void del();
int delBook(Node* node);
int colCount(const char* info);
Book getBookInfo(char* info);
char* get_field(char* line, int num);
char* remove_quoted(char* str);
Node* createLinkedList();
void sort();
void write();
int index_length();
Name_SeqList* init_index();
void create_index(SeqList*& index);
void destroy_index();
void  search();
int halfinterval_search(char* str);
Node* findinfs(char* str, int cas);
Node* findinf(char* str, char* name, int cas);
char* newfgets(char* info, int count);

//���������鼮
void show_allbook(Node* node, int cas) {
    Node* pTemp;
    if (node == NULL) {
        printf("δ�鵽����鼮\n");
    }
    //printf("              �鼮ID                ����                ����            ���п��              �ܿ��\n");
    else
    {
        switch (cas)
        {
        case 1:
            for (pTemp = node->next; pTemp != NULL; pTemp = pTemp->next) {
                printf("%20d%20s%20s%20d%20d\n", pTemp->book.book_id, pTemp->book.book_name,
                    pTemp->book.book_author, pTemp->book.Now_stock, pTemp->book.Total);
            }
            break;
        default:
            printf("%20d%20s%20s%20d%20d\n", node->book.book_id, node->book.book_name,
                node->book.book_author, node->book.Now_stock, node->book.Total);
            break;
        }

    }

}
//�޸Ľ������
void revise() {
    Node* pTemp;
    char str[20];
    int cas = 0;
    printf("              �鼮ID                ����                ����            ���п��              �ܿ��\n");
    show_allbook(booklist, 1);
    printf("������Ҫ�޸��Ǳ������Ϣ�����������ID:\n");
    scanf("%s", str);
    pTemp = findinf(str, (char*)"", 1);
    if (pTemp == NULL)
    {
        printf("��ָ�����鼮�����ڣ���ȷ����Ϣ\n");
    }
    else {
        printf("�����޸Ĵ�����ĸ����ݣ�1������ 2�������� 3�����п�� 4���ܿ�� \n");
        scanf("%d", &cas);
        switch (cas)
        {
        case 1:
            printf("�������µ�������\n");
            newfgets(str, 255);
            reviseinf(pTemp, str, 1);
            break;
        case 2:
            printf("�������µ����ߣ�\n");
            scanf("%s", str);
            reviseinf(pTemp, str, 2);
            break;
        case 3:
            printf("��������п�棺\n");
            scanf("%s", str);
            reviseinf(pTemp, str, 3);
            break;
        case 4:
            printf("������ܿ�棺\n");
            scanf("%s", str);
            reviseinf(pTemp, str, 4);
            break;
        default:
            printf("������δ֪ѡ��˳��޸Ľ��档\n");
            break;
        }
    };

}
//�޸������е�ͼ����Ϣ
void reviseinf(Node* node, const char* str, int cas) {
    Node* pTemp = node;
    int ca = cas;
    
    if (ca == 1) {
        pTemp->book.book_name = (char*)str;
        destroy_index();
        index = init_index();
        create_index(index);

    }
    else if (ca == 2) {
        pTemp->book.book_author = (char*)str;
    }
    else if (ca == 3) {
        int i = atoi(str);
        if (i > pTemp->book.Total) {
            printf("���޸ĵ����п������ܿ�棬������ȷ����Ϣ\n");
        }
        else {
            pTemp->book.Now_stock = i;
        }
    }
    else
    {
        int i = atoi(str);
        if (i < pTemp->book.Now_stock) {
            printf("���޸ĵ��ܿ��С�����п�棬������ȷ����Ϣ\n");
        }
        else {
            pTemp->book.Total = i;
        }
    }
    printf("��ǰͼ����ϢΪ��\n");
    printf("              �鼮ID                ����                ����            ���п��              �ܿ��\n");
    show_allbook(pTemp, 2);
}

//��ӽ���
void add() {
    char info[255];
    printf("�������������Ϣ:�����������ߣ���棬��Ӣ�Ķ��ŷָ\n");
    fgets(info, 254, stdin);
    fgets(info, 254, stdin);
    Node* pTemp = addinf(info);
    if (pTemp == NULL) {
        printf("�鱾���ʧ�ܣ��Ѵ����ڿ���\n");
    }
    else {
        printf("��ӳɹ�\n");
        printf("              �鼮ID                ����                ����            ���п��              �ܿ��\n");
        printf("%20d%20s%20s%20d%20d\n", pTemp->book.book_id, pTemp->book.book_name,
            pTemp->book.book_author, pTemp->book.Now_stock, pTemp->book.Total);
    }
}
//��ӹ��ܣ��ж���ӷ�ʽ���м����orβ�壩
Node* addinf(char* info) {
    Node* pTemp;
    int add = 0;
    Book TempBook;
    TempBook = getBookInfo(info);
    add = halfinterval_search(TempBook.book_name);
    if (add != -1)
    {
        pTemp = findinf(TempBook.book_name, TempBook.book_author, 2);
        if (pTemp == NULL)//���������ĸ�Ѵ�����������ʵʩ�м���� 
        {
            Node* pNode = (Node*)malloc(sizeof(Node));
            pNode->book = TempBook;
            pNode->next = index->address[add]->next;
            index->address[add]->next = pNode;
            return pNode;
        }
        else {
            return NULL;
        }
    }
    else//�������ڲ����ڴ�����������ĸ����Ҫ�ع�������
    {
        Node* pNode = (Node*)malloc(sizeof(Node));
        pNode->book = TempBook;
        booklistTail->next = pNode;
        booklistTail = booklistTail->next;
        booklistTail->next = NULL;
        destroy_index();
        sort();
        index = init_index();
        create_index(index);
        pTemp = findinf(TempBook.book_name, TempBook.book_author, 2);
        return pTemp;
    }
}

//ɾ������
void del() {
    char str[256];
    Node* pTemp;
    printf("��������Ҫɾ�����鱾��ID\n");
    newfgets(str, 255);
    newfgets(str, 255);
    pTemp = findinf((char*)str, (char*)"", 1);
    if (pTemp != NULL)
    {
        delBook(pTemp);
        destroy_index();
        index=init_index();
        create_index(index);
    }
    else
    {
        printf("����������鼮����ȷ��������Ϣ�Ƿ���ȷ\n");
    }

}
//�жϽ��λ�ò�����ɾ��
int delBook(Node* node) {
    Node* pTemp;
    if (node->next == NULL)
    {
        for (pTemp = booklist->next; pTemp != NULL; pTemp = pTemp->next) {
            if (node == pTemp->next) {
                pTemp->next = NULL;
                free(node);
                printf("ɾ���ɹ�\n");
                break;
            }
        }
    }
    else
    {
        for (pTemp = booklist; pTemp->next != NULL; pTemp = pTemp->next) {
            if (node == pTemp->next) {
                pTemp->next = node->next;
                free(node);
                printf("ɾ���ɹ�\n");
                break;
            }
        }
    };
    return 0;
}

//���ļ����г�ʼ����ȡ��������������
//������������
int colCount(const char* info) {
    int count = 0;
    for (char* p = (char*)info; *p; p++)
    {
        if (*p == ',') count++;
    }
    return count + 1;
}
//��ȡ�鼮��Ϣ
Book getBookInfo(char* info) {
    time_t t;//ʱ���
    Book book{};
    char* tmp;
    int i = colCount(info), j = 1;
    if (i == 5) {
        while (j < i)
        {
            tmp = get_field(strdup(info), j);
            book.book_id = atoi(tmp);
            j++;
            tmp = get_field(strdup(info), j);
            book.book_name = strdup(tmp);
            j++;
            tmp = get_field(strdup(info), j);
            book.book_author = strdup(tmp);
            j++;
            tmp = get_field(strdup(info), j);
            book.Now_stock = atoi(tmp);
            j++;
            tmp = get_field(strdup(info), j);
            book.Total = atoi(tmp);
            j++;
        }
        return book;
    }
    else if(i==3)
    {
        while (j < i)
        {
            tmp = get_field(strdup(info), j);
            book.book_name = strdup(tmp);
            j++;
            tmp = get_field(strdup(info), j);
            book.book_author = strdup(tmp);
            j++;
            tmp = get_field(strdup(info), j);
            book.Total = atoi(tmp);
            j++;
            book.book_id = time(&t) + book.book_name[0];//ÿ�����ID�ǵ�ǰʱ���������ĸASCII��ĺ�
            book.Now_stock = book.Total;
        }
        return book;
    }
    else {
        book.book_id = -1;
        book.book_name = strdup("ERROR");
        book.book_author = strdup("ERROR");
        book.Total = -1;
        book.Now_stock = -1;
        printf("��ӵ���Ϣ���㣬�����˴�����Ϣ\n");
        return book;
    }
    
}
//��ȡCSVÿ����Ϣ
char* get_field(char* line, int num)
{
    char* tok;
    tok = strtok(line, ",");
    for (int i = 1; i != num; i++) {
        tok = strtok(NULL, ",");
    }
    char* result = remove_quoted(tok);
    return result;
}
//����β���з���Ϊ��ֹ��
char* remove_quoted(char* str)
{
    if (!str) {
        return 0;
    }
    else {
        char* find = strchr(str, '\n');  //�ҳ�str�е�"\n"
        if (find)
            *find = '\0';   //�滻

        return str;
    };
}
//��ʼ����������������
Node* createLinkedList() {
    Node* pHead = (Node*)malloc(sizeof(Node));
    booklistTail = pHead;

    // ���ļ�
    FILE* fp = fopen(F_PATH, "r");
    if (fp == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
    else {
        char info[256];
        // �򿪳ɹ����ȡÿһ�У�һ�������һ���鼮��Ϣ
        while (fgets(info, 256, fp) != NULL) {

            Node* pNode = (Node*)malloc(sizeof(Node));
            pNode->book = getBookInfo(info);
            booklistTail->next = pNode;
            booklistTail = booklistTail->next;
            booklistTail->next = NULL;
        }
    }
    return pHead;
}
//��������������������ĸ��
void sort() {
    Node* pTemp;
    Node* comnode_1 = booklist->next;
    Node* comnode_2 = booklist;
    Book temp;
    while (comnode_1 != NULL)
    {
        while (comnode_1->next != NULL)
        {
            if (comnode_1->book.book_name[0] > comnode_1->next->book.book_name[0])
            {
                temp = comnode_1->book;
                comnode_1->book = comnode_1->next->book;
                comnode_1->next->book = temp;
            }
            comnode_1 = comnode_1->next;
        }
        comnode_1 = comnode_2->next;
        comnode_2 = comnode_1;
    }

}
//�˳�ǰ������Ϣ���ļ���
void write() {
    Node* pTemp;
    FILE* fp = fopen(F_PATH, "w");
    if (fp == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        for (pTemp = booklist->next; pTemp != NULL; pTemp = pTemp->next) {
            fprintf(fp, "%d,%s,%s,%d,%d\n", pTemp->book.book_id, pTemp->book.book_name, pTemp->book.book_author, pTemp->book.Now_stock, pTemp->book.Total);
        }
    }
    fclose(fp);
}


//���������˳�����
int index_length() {
    Node* pTemp;
    int count = 0;//ͳ��˳�������ĳ���
    for (pTemp = booklist->next; pTemp != NULL; pTemp = pTemp->next)
    {
        if (pTemp->book.book_name[0] != pTemp->next->book.book_name[0])
        {
            count++;

        }
    }
    return count;
}
//��ʼ��˳���
Name_SeqList* init_index() {
    Name_SeqList* index;
    index = (SeqList*)malloc(sizeof(SeqList));
    index->length = 0;
    return index;
}
//����˳���
void create_index(SeqList*& index) {
    int i = 0;
    index->asc[0] = booklist->next->book.book_name[0];
    index->address[0] = booklist->next;
    Node* pTemp;
    int count = 0;//ͳ��˳�������ĳ���
    for (pTemp = booklist->next; pTemp->next != NULL; pTemp = pTemp->next)
    {
        if (pTemp->next != NULL && pTemp->book.book_name[0] != pTemp->next->book.book_name[0])
        {
            count++;

        }
    }
    for (pTemp = booklist->next; pTemp != NULL; pTemp = pTemp->next)
    {
        if (pTemp->next != NULL && pTemp->book.book_name[0] != pTemp->next->book.book_name[0])
        {

            index->asc[i + 1] = pTemp->next->book.book_name[0];
            index->address[i + 1] = pTemp->next;
            i++;
        }

    }
    index->length = count + 1;
}
//�ͷ�����
void destroy_index() {
    free(index);
}
//���ҽ���
void  search() {
    int cas;
    char info[255];
    printf("������������ʽ��1����ID���� 2������������ 3������������\n");
    scanf("%d", &cas);
    fgets(info, 254, stdin);
    int nLen = strlen(info);
    switch (cas)
    {
    case 1:
        printf("������ID��\n");
        newfgets(info, 254);
        find = findinf(info, (char*)"", 1);
        printf("              �鼮ID                ����                ����            ���п��              �ܿ��\n");
        show_allbook(find, 2);
        break;
    case 2:
        printf("������������\n");
        newfgets(info, 254);
        find = findinfs(info, 1);
        printf("              �鼮ID                ����                ����            ���п��              �ܿ��\n");
        show_allbook(find, 1);
        break;
    case 3:
        printf("���������ߣ�\n");
        newfgets(info, 254);
        find = findinfs(info, 2);
        printf("              �鼮ID                ����                ����            ���п��              �ܿ��\n");
        show_allbook(find, 1);
        break;
    default:
        printf("������δ֪ѡ��˳��������档\n");
        break;
    }
}
//�������ַ�����
int halfinterval_search(char* str) {
    Node* pTemp;
    int right, left, check, res;
    left = 0;
    right = index->length;
    check = 0;
    res = 0;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (str[0] == index->asc[mid])
        {
            pTemp = index->address[mid];
            res = mid;
            check = 1;
            break;
        }
        else if (str[0] < index->asc[mid])
        {
            right = mid - 1;
        }
        else if (str[0] > index->asc[mid]) {
            left = mid + 1;
        }
    }
    if (check != 0) {
        return res;
    }
    else {
        return -1;
    }
}
//�������в��ң�����һ����ѯ�������
Node* findinfs(char* str, int cas) {
    Node* pHead = (Node*)malloc(sizeof(Node));
    findTail = pHead;
    Node* pTemp;
    int res = 0;
    int ca = cas;
    if (ca == 1) {
        int address = halfinterval_search(str);
        if (address == -1)
        {
            return NULL;
        }
        else {
            for (pTemp = index->address[address]; pTemp != NULL && pTemp != index->address[address + 1]; pTemp = pTemp->next)
                if (strcmp(str, (char*)pTemp->book.book_name) == 0)
                {
                    Node* pNode = (Node*)malloc(sizeof(Node));
                    pNode->book = pTemp->book;
                    findTail->next = pNode;
                    findTail = findTail->next;
                    findTail->next = NULL;
                    res++;
                }
        }
    }
    else {
        for (pTemp = booklist->next; pTemp != NULL; pTemp = pTemp->next) {
            if (strcmp(str, (char*)pTemp->book.book_author) == 0)
            {
                Node* pNode = (Node*)malloc(sizeof(Node));
                pNode->book = pTemp->book;
                findTail->next = pNode;
                findTail = findTail->next;
                findTail->next = NULL;
                res++;
            }
        }
    }
    if (res == 0)
    {
        return NULL;
    }
    else
    {
        return pHead;
    }
}
//�鱾��ȷ���ң�������ɾ��
Node* findinf(char* str, char* name, int cas) {
    Node* pTemp;
    int res = 0, ca = cas, id = atoi(str);
    if (ca == 1) {
        for (pTemp = booklist->next; pTemp != NULL; pTemp = pTemp->next) {
            if (id == pTemp->book.book_id) {
                res++;
                break;
            }
        }
    }
    else {
        int add = halfinterval_search(str);
        if (add == -1)
        {
            return NULL;
        }
        else
        {
            for (pTemp = index->address[add]; pTemp != NULL && pTemp != index->address[add + 1]; pTemp = pTemp->next) {
                if (strcmp(name, (char*)pTemp->book.book_author) == 0)
                {
                    res++;
                    break;
                }
            }
        }

    }
    if (res == 0)
    {
        return NULL;
    }
    else
    {
        return pTemp;
    }
}
//��װ��fgets,ɾ��/n
char* newfgets(char* info, int count) {
    fgets(info, 255, stdin);
    char* find = strchr(info, '\n');  //�ҳ�data�е�"\n"
    if (find)
        *find = '\0';   //�滻
    return info;
}


void menu_s() {
    printf("\n-------------������Ϣ����--------------\n");
    printf("0.�鼮���\n");
    printf("1.�鼮ɾ��\n");
    printf("2.�鼮��ѯ\n");
    printf("3.�鼮�޸�\n");
    printf("4.�˳�ϵͳ\n");
    printf("---------------------------------------\n");
    printf("��ѡ��");
}
void keyDown2() {
    int count_s = 0;
    scanf("%d", &count_s);
    switch (count_s) {
    case 0:
        printf("���鼮��ӡ�\n");
        add();//
        break;
    case 1:
        printf("���鼮ɾ����\n");
        printf("              �鼮ID                ����                ����            ���п��              �ܿ��\n");
        show_allbook(booklist, 1);
        del();
        printf("              �鼮ID                ����                ����            ���п��              �ܿ��\n");
        show_allbook(booklist, 1);
        break;
    case 2:
        printf("���鼮��ѯ��\n");
        search();
        break;
    case 3:
        printf("���鼮�޸ġ�\n");
        revise();
        break;
    case 4:
        printf("���˳�ϵͳ��\n");
        printf("�˳��ɹ�");
        write();
        system("pause");
        exit(0);
        break;
    default:
        printf("��error��\n");
        menu_s();
        break;

    }
}

void bookInfo() {
    menu_s();
    keyDown2();
}