
#include "LinkList.h"

/*
 * 初始化
 *
 * 只是初始化一个头结点。
 * 初始化成功则返回OK，否则返回ERROR。
 */
Status InitList(LinkList* L) {
    (*L) = (LinkList) malloc(sizeof(LNode));
    if (*L == NULL) {
        return ERROR;
    }
    (*L)->next = NULL;
    return OK;
}

/*
 * 销毁(结构)
 *
 * 释放链表所占内存。
 */
Status DestroyList(LinkList* L) {
    LinkList p;

    // 确保链表结构存在
    if(L == NULL || *L == NULL) {
        return ERROR;
    }

    p = *L;
    while (p) {
        p = (*L)->next; // 头结点后续1节点
        free(*L); // 回收最前的结点
        (*L) = p; // 头结点后移
    }

    *L = NULL;
    return OK;
}

/*
 * 置空(内容)
 *
 * 这里需要释放链表中非头结点处的空间。
 */
Status ClearList(LinkList L) {
    LinkList p, q;

    // 确保链表结构存在
    if(L == NULL) {
        return ERROR;
    }

    p = L->next; // 头结点后续1节点
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }

    L->next = NULL;  // 头节点后续指针的指向置空
    return OK;
}

/*
 * 判空
 *
 * 判断链表中是否包含有效数据。
 *
 * 返回值：
 * TRUE : 链表为空
 * FALSE: 链表不为空
 */
Status ListEmpty(LinkList L);

/*
 * 计数
 *
 * 返回链表包含的有效元素的数量。
 */
int ListLength(LinkList L) {
    int cnt;
    LinkList q;

    // 确保链表结构存在
    if(L == NULL) {
        return ERROR;
    }

    cnt = 0;
    q = L->next;

    while (q) {
        q = q->next;
        cnt++;
    }

    return cnt;
}

/*
 * 取值
 *
 * 获取链表中第i个元素，将其存储到e中。
 * 如果可以找到，返回OK，否则，返回ERROR。
 *
 *【备注】
 * 教材中i的含义是元素位置，从1开始计数，但这不符合编码的通用约定。
 * 通常，i的含义应该指索引，即从0开始计数。
 */
Status GetElem(LinkList L, int i, ElemType* e) {
    int j;
    LinkList p;

    // 确保链表存在且不为空表
    if(L == NULL || L->next == NULL) {
        return ERROR;
    }

    j = 0;
    p = L->next;

    while (p && j < i) {
        p = p->next;
        j++;
    }

    if (!p || j > i) {
        return ERROR;
    }

    (*e) = p->data;

    return OK;
}

/*
 * 链表倒计
 *
 * 获取链表倒数第k个结点。
 *
 *【备注】
 * 从1开始计数。
 */
LNode* getKthFromEnd(LinkList* L, int k) {
    int j;
    LinkList fast, slow;

    // 确保链表存在且不为空表
    if((*L) == NULL || (*L)->next == NULL || k == 0) {
        return NULL;
    }

    j = 0;
    fast = slow = *L;

    // 快指针先走 i - 1 步
    while (fast && j < k - 1) {
        fast = fast->next;
        j++;
    }

    // fast 走到合法范围之外
    if (!fast || j > k - 1) {
        return NULL;
    }

    while (fast->next) {
        fast = fast->next;
        slow = slow->next;
    }

    // 若 slow 正好在头结点
    if (slow == *L)
        return NULL;

    return slow;
}

/*
 * 查找
 *
 * 返回链表中首个与e满足Compare关系的元素位序。
 * 如果不存在这样的元素，则返回0。
 *
 *【备注】
 * 元素e是Compare函数第二个形参
 */
int LocateElem(LinkList L, ElemType e, Status(Compare)(ElemType, ElemType));

/*
 * 前驱
 *
 * 获取元素cur_e的前驱，
 * 如果存在，将其存储到pre_e中，返回OK，
 * 如果不存在，则返回ERROR。
 */
Status PriorElem(LinkList L, ElemType cur_e, ElemType* pre_e);

/*
 * 后继
 *
 * 获取元素cur_e的后继，
 * 如果存在，将其存储到next_e中，返回OK，
 * 如果不存在，则返回ERROR。
 */
Status NextElem(LinkList L, ElemType cur_e, ElemType* next_e);

/*
 * 插入
 *
 * 向链表第i个位置上插入e，插入成功则返回OK，否则返回ERROR。
 *
 *【备注】
 * 教材中i的含义是元素位置，从1开始计数
 */
Status ListInsert(LinkList L, int i, ElemType e) {
    LinkList p, node;
    int j;

    // 确保链表存在且不为空表
    if(L == NULL) {
        return ERROR;
    }

    p = L;
    j = 1;

    while (p && j < i) {
        p = p->next;
        j++;
    }

    // 如果遍历到头了，或者i的值不合规(比如i<=0)，说明没找到合乎目标的结点
    if (!p || j > i) {
        return ERROR;
    }

    node = (LinkList) malloc(sizeof(LNode));
    node->data = e;
    node->next = p->next;
    p->next = node;

    return OK;
}

/*
 * 删除
 *
 * 删除链表第i个位置上的元素，并将被删除元素存储到e中。
 * 删除成功则返回OK，否则返回ERROR。
 *
 *【备注】
 * 教材中i的含义是元素位置，从1开始计数
 */
Status ListDelete(LinkList L, int i, ElemType* e);

/*
 * 遍历
 *
 * 用visit函数访问链表L
 */
void ListTraverse(LinkList L, void(Visit)(ElemType));

/*
 * 头插法创建链表
 *
 *
 *【备注】
 *
 * 教材中默认从控制台读取数据。
 * 这里为了方便测试，避免每次运行都手动输入数据，
 * 因而允许选择从预设的文件path中读取测试数据。
 *
 * 如果需要从控制台读取数据，则path为NULL或者为空串，
 * 如果需要从文件中读取数据，则需要在path中填写文件名信息。
 */
Status CreateList_Head(LinkList* L, int n, char* path);

/*
 * 尾插法创建链表
 *
 *
 *【备注】
 * 教材中默认从控制台读取数据。
 * 这里为了方便测试，避免每次运行都手动输入数据，
 * 因而允许选择从预设的文件path中读取测试数据。
 *
 * 如果需要从控制台读取数据，则path为NULL或者为空串，
 * 如果需要从文件中读取数据，则需要在path中填写文件名信息。
 */
Status CreateList_Tail(LinkList* L, int n, char* path);

