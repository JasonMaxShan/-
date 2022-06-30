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
//链表结构体
typedef struct node {
    Book book;
    struct node* next;
} Node;
//书名索引结构体
typedef struct SeqList
{
    int asc[Maxsize];
    Node* address[Maxsize];
    int length;//当前元素数目
}Name_SeqList;

Node* booklist;// 完整书链表头指针
Node* booklistTail;// 完整书链表尾指针
Node* find;//查找链表头指针
Node* findTail;//查找链表尾指针
Name_SeqList* index; //书名索引顺序表
//各类声明

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

//遍历所有书籍
void show_allbook(Node* node, int cas) {
    Node* pTemp;
    if (node == NULL) {
        printf("未查到相关书籍\n");
    }
    //printf("              书籍ID                书名                作者            现有库存              总库存\n");
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
//修改结果界面
void revise() {
    Node* pTemp;
    char str[20];
    int cas = 0;
    printf("              书籍ID                书名                作者            现有库存              总库存\n");
    show_allbook(booklist, 1);
    printf("请问需要修改那本书的信息，请输入书的ID:\n");
    scanf("%s", str);
    pTemp = findinf(str, (char*)"", 1);
    if (pTemp == NULL)
    {
        printf("所指定的书籍不存在，请确认信息\n");
    }
    else {
        printf("请问修改此书的哪个内容？1、书名 2、书作者 3、现有库存 4、总库存 \n");
        scanf("%d", &cas);
        switch (cas)
        {
        case 1:
            printf("请输入新的书名：\n");
            newfgets(str, 255);
            reviseinf(pTemp, str, 1);
            break;
        case 2:
            printf("请输入新的作者：\n");
            scanf("%s", str);
            reviseinf(pTemp, str, 2);
            break;
        case 3:
            printf("请更正现有库存：\n");
            scanf("%s", str);
            reviseinf(pTemp, str, 3);
            break;
        case 4:
            printf("请更正总库存：\n");
            scanf("%s", str);
            reviseinf(pTemp, str, 4);
            break;
        default:
            printf("输入了未知选项，退出修改界面。\n");
            break;
        }
    };

}
//修改链表中的图书信息
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
            printf("所修改的现有库存大于总库存，请重新确认信息\n");
        }
        else {
            pTemp->book.Now_stock = i;
        }
    }
    else
    {
        int i = atoi(str);
        if (i < pTemp->book.Now_stock) {
            printf("所修改的总库存小于现有库存，请重新确认信息\n");
        }
        else {
            pTemp->book.Total = i;
        }
    }
    printf("当前图书信息为：\n");
    printf("              书籍ID                书名                作者            现有库存              总库存\n");
    show_allbook(pTemp, 2);
}

//添加界面
void add() {
    char info[255];
    printf("请输入新书的信息:（书名，作者，库存，以英文逗号分割）\n");
    fgets(info, 254, stdin);
    fgets(info, 254, stdin);
    Node* pTemp = addinf(info);
    if (pTemp == NULL) {
        printf("书本添加失败：已存在于库中\n");
    }
    else {
        printf("添加成功\n");
        printf("              书籍ID                书名                作者            现有库存              总库存\n");
        printf("%20d%20s%20s%20d%20d\n", pTemp->book.book_id, pTemp->book.book_name,
            pTemp->book.book_author, pTemp->book.Now_stock, pTemp->book.Total);
    }
}
//添加功能，判断添加方式（中间插入or尾插）
Node* addinf(char* info) {
    Node* pTemp;
    int add = 0;
    Book TempBook;
    TempBook = getBookInfo(info);
    add = halfinterval_search(TempBook.book_name);
    if (add != -1)
    {
        pTemp = findinf(TempBook.book_name, TempBook.book_author, 2);
        if (pTemp == NULL)//新书的首字母已存在于索引表，实施中间插入 
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
    else//索引表内不存在此书名的首字母，需要重构索引表
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

//删除界面
void del() {
    char str[256];
    Node* pTemp;
    printf("请输入需要删除的书本的ID\n");
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
        printf("不存在相关书籍，请确定输入信息是否正确\n");
    }

}
//判断结点位置并进行删除
int delBook(Node* node) {
    Node* pTemp;
    if (node->next == NULL)
    {
        for (pTemp = booklist->next; pTemp != NULL; pTemp = pTemp->next) {
            if (node == pTemp->next) {
                pTemp->next = NULL;
                free(node);
                printf("删除成功\n");
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
                printf("删除成功\n");
                break;
            }
        }
    };
    return 0;
}

//对文件进行初始化读取，生成完整链表
//计算数据列数
int colCount(const char* info) {
    int count = 0;
    for (char* p = (char*)info; *p; p++)
    {
        if (*p == ',') count++;
    }
    return count + 1;
}
//获取书籍信息
Book getBookInfo(char* info) {
    time_t t;//时间戳
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
            book.book_id = time(&t) + book.book_name[0];//每本书的ID是当前时间戳与首字母ASCII码的和
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
        printf("添加的信息不足，产生了错误信息\n");
        return book;
    }
    
}
//截取CSV每行信息
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
//将行尾换行符改为终止符
char* remove_quoted(char* str)
{
    if (!str) {
        return 0;
    }
    else {
        char* find = strchr(str, '\n');  //找出str中的"\n"
        if (find)
            *find = '\0';   //替换

        return str;
    };
}
//初始化创建完整书链表
Node* createLinkedList() {
    Node* pHead = (Node*)malloc(sizeof(Node));
    booklistTail = pHead;

    // 打开文件
    FILE* fp = fopen(F_PATH, "r");
    if (fp == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
    else {
        char info[256];
        // 打开成功后读取每一行，一行则代表一个书籍信息
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
//重排序完整链表（按首字母）
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
//退出前保存信息到文件中
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


//计算所需的顺序表长度
int index_length() {
    Node* pTemp;
    int count = 0;//统计顺序表所需的长度
    for (pTemp = booklist->next; pTemp != NULL; pTemp = pTemp->next)
    {
        if (pTemp->book.book_name[0] != pTemp->next->book.book_name[0])
        {
            count++;

        }
    }
    return count;
}
//初始化顺序表
Name_SeqList* init_index() {
    Name_SeqList* index;
    index = (SeqList*)malloc(sizeof(SeqList));
    index->length = 0;
    return index;
}
//创建顺序表
void create_index(SeqList*& index) {
    int i = 0;
    index->asc[0] = booklist->next->book.book_name[0];
    index->address[0] = booklist->next;
    Node* pTemp;
    int count = 0;//统计顺序表所需的长度
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
//释放索引
void destroy_index() {
    free(index);
}
//查找界面
void  search() {
    int cas;
    char info[255];
    printf("请输入搜索方式：1、按ID搜索 2、按书名搜索 3、按作者搜索\n");
    scanf("%d", &cas);
    fgets(info, 254, stdin);
    int nLen = strlen(info);
    switch (cas)
    {
    case 1:
        printf("请输入ID：\n");
        newfgets(info, 254);
        find = findinf(info, (char*)"", 1);
        printf("              书籍ID                书名                作者            现有库存              总库存\n");
        show_allbook(find, 2);
        break;
    case 2:
        printf("请输入书名：\n");
        newfgets(info, 254);
        find = findinfs(info, 1);
        printf("              书籍ID                书名                作者            现有库存              总库存\n");
        show_allbook(find, 1);
        break;
    case 3:
        printf("请输入作者：\n");
        newfgets(info, 254);
        find = findinfs(info, 2);
        printf("              书籍ID                书名                作者            现有库存              总库存\n");
        show_allbook(find, 1);
        break;
    default:
        printf("输入了未知选项，退出搜索界面。\n");
        break;
    }
}
//索引二分法查找
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
//在链表中查找，返回一个查询结果链表
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
//书本精确查找，用于增删改
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
//包装下fgets,删掉/n
char* newfgets(char* info, int count) {
    fgets(info, 255, stdin);
    char* find = strchr(info, '\n');  //找出data中的"\n"
    if (find)
        *find = '\0';   //替换
    return info;
}


void menu_s() {
    printf("\n-------------读者信息管理--------------\n");
    printf("0.书籍添加\n");
    printf("1.书籍删除\n");
    printf("2.书籍查询\n");
    printf("3.书籍修改\n");
    printf("4.退出系统\n");
    printf("---------------------------------------\n");
    printf("请选择：");
}
void keyDown2() {
    int count_s = 0;
    scanf("%d", &count_s);
    switch (count_s) {
    case 0:
        printf("【书籍添加】\n");
        add();//
        break;
    case 1:
        printf("【书籍删除】\n");
        printf("              书籍ID                书名                作者            现有库存              总库存\n");
        show_allbook(booklist, 1);
        del();
        printf("              书籍ID                书名                作者            现有库存              总库存\n");
        show_allbook(booklist, 1);
        break;
    case 2:
        printf("【书籍查询】\n");
        search();
        break;
    case 3:
        printf("【书籍修改】\n");
        revise();
        break;
    case 4:
        printf("【退出系统】\n");
        printf("退出成功");
        write();
        system("pause");
        exit(0);
        break;
    default:
        printf("【error】\n");
        menu_s();
        break;

    }
}

void bookInfo() {
    menu_s();
    keyDown2();
}