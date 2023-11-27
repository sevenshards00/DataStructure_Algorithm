// 11.05 ����Ʈ ��� ť
// head�θ� ��尡 ������ ����Ʈ ����, �ٸ� head�� tail�� �����Ѵ� ��������. ��ȸ�� ����
// ListBaseQueue.h

#ifndef __LIST_BASE_QUEUE_H__
#define __LIST_BASE_QUEUE_H__

#define TRUE 1
#define FALSE 0

// ���ǻ� int�� Data��� ��Ī. �ٸ� ������ Ÿ���� ���� �ʹٸ� ���� �ٲٸ� �ȴ�.
typedef int Data;

// ��� ����ü ����
typedef struct _node
{
	Data data;
	struct _node* next;
} Node;

// ť ����ü ����, front�� rear�� ���
typedef struct _listqueue {
	Node* front;
	Node* rear;
} ListQueue;

// ListQueue��� �� ���� �����ϴ� Queue��� ��Ī �ο�
typedef ListQueue Queue;

void QueueInit(Queue* pq); // Queue �ʱ�ȭ

int QisEmpty(Queue* pq); // Queue�� ����°� Ȯ��

void QEnqueue(Queue* pq, Data data); // Queue�� ��� ����

Data QDequeue(Queue* pq); // ���� Queue���� front�� ����Ű�� �ִ� ��� ����

Data QPeek(Queue* pq); // ���� Queue���� front�� ����Ű�� ����� ������ Ȯ�� (���Ŵ� ����)
#endif