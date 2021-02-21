#include <stdio.h>
#include "Status.h"
#include "LinkList.h"                        //**▲02 线性表**//


int main(int argc, char** argv) {
    LinkList L;
    int i;
    ElemType e;

    printf("******** InitList \n");
    {
        printf("* 初始化单链表 L ...\n");
        InitList(&L);
    }

    printf("******** ListInsert \n");
    {
        for(i = 1; i <= 8; i++) {
            printf("* 在 L 第 %d 个位置插入 \"%d\" ...\n", i, 2 * i);
            ListInsert(L, i, 2 * i);
        }
    }

    printf("******** GetElem \n");
    {
        int k;
        for (k = 0; k < 8; k++) {
            GetElem(L, k, &e);
            printf("* L 中第 %d 个位置的元素为 \"%d\" \n", k, e);
        }
    }

    printf("******** getKthFromEnd \n");
    {
        int k = 5;
        LNode* aa = getKthFromEnd(&L, k);
        aa
        ? printf("* L 中倒数第 %d 个位置的元素为 \"%d\" \n", k, aa->data)
        : printf("err\n");
    }

    printf("******** DestroyList \n");
    {
        printf("* 销毁 L 前：");
        L ? printf(" L 存在！\n") : printf(" L 不存在！！\n");

        DestroyList(&L);

        printf("* 销毁 L 后：");
        L ? printf(" L 存在！\n") : printf(" L 不存在！！\n");
    }

    return 0;
}

