/*=========================
 * 栈的顺序存储结构（顺序栈）
 ==========================*/

#include "SqStack.h"    //**▲03 栈和队列**//

/*
 * 初始化
 *
 * 构造一个空栈。初始化成功则返回OK，否则返回ERROR。
 */
Status InitStack(SqStack* S) {
    if(S == NULL) {
        return ERROR;
    }

    S->base = (SElemType*) malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if((*S).base == NULL) {
        exit(OVERFLOW);
    }

    S->top = S->base;
    S->stackSize = STACK_INIT_SIZE;

    return OK;
}

/*
 * 销毁(结构)
 *
 * 释放顺序栈所占内存。
 */
Status DestroyStack(SqStack* S) {
    if(S == NULL) {
        return ERROR;
    }

    free(S->base);

    S->top = NULL;
    S->base = NULL;
    S->stackSize = 0;

    return OK;
}

/*
 * 置空(内容)
 *
 * 只是清理顺序栈中存储的数据，不释放顺序栈所占内存。
 */
Status ClearStack(SqStack* S) {
    if(S == NULL || S->base == NULL) {
        return ERROR;
    }

    S->base = S->top;

    return OK;
}

/*
 * 判空
 *
 * 判断顺序栈中是否包含有效数据。
 *
 * 返回值：
 * TRUE : 顺序栈为空
 * FALSE: 顺序栈不为空
 */
Status StackEmpty(SqStack S) {
    if(S.top == S.base) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/*
 * 计数
 *
 * 返回顺序栈包含的有效元素的数量。
 */
int StackLength(SqStack S) {
    if(S.base == NULL) {
        return 0;
    }

    return (int) (S.top - S.base);
}

/*
 * 取值
 *
 * 返回栈顶元素，并用e接收。
 */
Status Peek(SqStack S, SElemType* e) {
    if(S.base == NULL) {
        return ERROR;
    }

    (*e) = *(S.top - 1);

    return OK;
}

/*
 * 入栈
 *
 * 将元素e压入到栈顶。
 */
Status Push(SqStack* S, SElemType e) {
    if(S == NULL || S->base == NULL) {
        return ERROR;
    }

    if (S->top - S->base >= S->stackSize) {
        (*S).base = (SElemType*) realloc((*S).base, ((*S).stackSize + STACKINCREMENT) * sizeof(SElemType));
        if ((*S).base == NULL) {
            exit(OVERFLOW);     // 存储分配失败
        }

        S->top = S->base + S->stackSize;
        S->stackSize += STACKINCREMENT;
    }

    *(S->top++) = e;
    return OK;
}

/*
 * 出栈
 *
 * 将栈顶元素弹出，并用e接收。
 */
Status Pop(SqStack* S, SElemType* e) {
    if(S == NULL || S->base == NULL) {
        return ERROR;
    }

    *e = *(--S->top);
    return OK;
}

/*
 * 遍历
 *
 * 用visit函数访问顺序栈S
 */
Status StackTraverse(SqStack S, void(Visit)(SElemType)) {
    int i;

    if(Q.base == NULL) {
        return ERROR;
    }

    for(i = Q.front; i != Q.rear; i = (i + 1) % MAXQSIZE) {
        Visit(Q.base[i]);
    }

    printf("\n");

    return OK;
}
