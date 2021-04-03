/*=========================
 * 队列的链式存储结构（链队）
 ==========================*/

#include "LinkQueue.h"                    //**▲03 栈和队列**//

/*
 * 初始化
 *
 * 构造一个空的链队。
 * 初始化成功则返回OK，否则返回ERROR。
 *
 *【注】
 * 这里的队列带有头结点
 */
Status InitQueue(LinkQueue* Q) {
    if(Q == NULL)
        return ERROR;

    Q->front = (QueuePtr) malloc(sizeof(QNode));

    if (Q->front == NULL)
        exit(OVERFLOW);

    Q->front->next = NULL;

    Q->rear = Q->front;

    return OK;
}

/*
 * 销毁(结构)
 *
 * 释放链队所占内存。
 */
Status DestroyQueue(LinkQueue* Q) {
    if(Q == NULL || Q->front == NULL)
        return ERROR;

    while (Q->front) {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }

    return OK;
}

/*
 * 置空(内容)
 *
 * 这里需要释放链队中非头结点处的空间。
 */
Status ClearQueue(LinkQueue* Q) {
    if(Q == NULL || Q->front == NULL)
        return ERROR;

    while (Q->front->next) {
        Q->rear = Q->front->next;
        Q->front->next = Q->rear->next;
        free(Q->rear);
    }
    Q->rear = Q->front;

    return OK;
}

/*
 * 判空
 *
 * 判断链队中是否包含有效数据。
 *
 * 返回值：
 * TRUE : 链队为空
 * FALSE: 链队不为空
 */
Status QueueEmpty(LinkQueue Q) {
    if(Q.front == NULL || Q.rear == NULL)
        return ERROR;

    return Q.front == Q.rear;
}

/*
 * 计数
 *
 * 返回链队包含的有效元素的数量。
 */
int QueueLength(LinkQueue Q) {
    int count = 0;
    QueuePtr p = Q.front;

    while(p != Q.rear) {
        count++;
        p = p->next;
    }

    return count;
}

/*
 * 取值
 *
 * 获取队头元素，将其存储到e中。
 * 如果可以找到，返回OK，否则，返回ERROR。
 */
Status GetHead(LinkQueue Q, QElemType* e) {
    if(Q.front == NULL || Q.front->next == NULL)
        return ERROR;

    *e = Q.front->next->data;
    return OK;
}

/*
 * 入队
 *
 * 将元素e添加到队列尾部。
 */
Status EnQueue(LinkQueue* Q, QElemType e) {
    if(Q == NULL || Q->rear == NULL)
        return ERROR;

    QueuePtr s = (QueuePtr) malloc(sizeof(QNode));

    if (!s)
        exit(OVERFLOW);

    s->data = e;
    s->next = NULL;

    Q->rear->next = s;
    Q->rear = s;

    return OK;
}

/*
 * 出队
 *
 * 移除队列头部的元素，将其存储到e中。
 */
Status DeQueue(LinkQueue* Q, QElemType* e) {
    QueuePtr p;

    if(Q == NULL || Q->front == NULL || Q->front == Q->rear)
        return ERROR;

    p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    
    if(Q->rear == p)
        Q->rear = Q->front;

    free(p);

    return OK;
}

/*
 * 遍历
 *
 * 用visit函数访问队列Q
 */
Status QueueTraverse(LinkQueue Q, void(Visit)(QElemType)) {
    QueuePtr p;

    if(Q.front == NULL) {
        return ERROR;
    }

    p = Q.front->next;

    while(p != NULL) {
        Visit(p->data);
        p = p->next;
    }

    printf("\n");

    return OK;
}