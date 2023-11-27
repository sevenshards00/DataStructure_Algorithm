/*
* ���� �ڷᱸ�� - �迭 ����� ��(Heap)
* ���ϸ�: Heap.c
* ���� ����: 0.2
* �ۼ���: Sevenshards
* �ۼ� ����: 2023-11-24
* ���� ���� �ۼ� ����: 2023-11-24
* ���� ����: �켱 ���� �Ǵ� ������ ���� ������ �� �ֵ��� �Լ� �����ͷ� ����
* ���� ���� ����: ������ ���� ����
*/
#include "Heap.h"

// ���� �ʱ�ȭ
// �켱 ���� ������ �Ǻ��� �Լ����� �޾Ƽ� �ʱ�ȭ
void HeapInit(Heap* ph, PriorityComp pc)
{
	ph->numOfData = 0;
	ph->comp = pc; // �켱 ���� �񱳿� ���� �Լ� ���
}

// ���� ������� Ȯ��
int HisEmpty(Heap* ph)
{
	if (ph->numOfData == 0)
		return TRUE;
	else
		return FALSE;
}

// �θ� ����� �ε��� �� ��ȯ
// �θ� ����� �ε��� �� = �ڽ� ����� �ε��� �� / 2 (������ ������)
int GetParentIDX(int idx)
{
	return idx / 2;
}

// ���� �ڽ� ����� �ε��� �� ��ȯ
// ���� �ڽ� ����� �ε��� �� = �θ� ����� �ε��� �� * 2
int GetLChildIDX(int idx)
{
	return idx * 2;
}

// ������ �ڽ� ����� �ε��� �� ��ȯ
// ������ �ڽ� ����� �ε��� �� = (�θ� ����� �ε��� �� * 2) + 1
int GetRChildIDX(int idx)
{
	return GetLChildIDX(idx) + 1;
}

// �� ���� �ڽ� ��� �� ���� �켱������ �ڽ� ��� �ε��� �� ��ȯ
// �켱 ������ ��� ���� ���� �������� ���� �켱������ ��Ÿ���ٰ� ����
int GetHiPriChildIDX(Heap* ph, int idx)
{
	// ���� "���� ����Ʈ��" �̹Ƿ� ������ �ڽĳ�常 �ִ� ���� ���� ����.
	// �ڽ� ��尡 �ϳ��� ���ٸ�, �ܸ� ��尡 ��.
	// ���� ���� �ڽ� ����� �ε����� ���� ����� ����� ���� �Ѿ�ٸ�?
	// �ش� ���� �ܸ� ��尡 �ǹǷ� 0�� ��ȯ
	if (GetLChildIDX(idx) > ph->numOfData) // �ڽ� ��尡 ���� ��� (�ܸ� ����� ���)
		return 0;
	// �ڽ� ��尡 �ϳ� ���� ���� ���� �ڽ� ����̸�, ���� ������ ��尡 �ȴ�.
	// �׷��� ������ ���ǽ��� �Ʒ��� ���� �ָ� �ڽ� ��尡 �ϳ��� ��Ȳ�� �Ǻ��� �� ����.
	else if (GetLChildIDX(idx) == ph->numOfData) // ���� �ڽ� ��常 �����ϴ� ���
		return GetLChildIDX(idx);
	else // ����, ������ �ڽ� ��尡 �� �ִ� ���.
	{
		if (ph->comp(ph->heapArr[GetLChildIDX(idx)], ph->heapArr[GetRChildIDX(idx)]) < 0)
			return GetRChildIDX(idx); // ������ �ڽ� ����� �켱 ������ ���ٸ�
		else
			return GetLChildIDX(idx); // ���� �ڽ� ����� �켱 ������ ���ٸ�
	}
}

// ���� ������ ����
void HInsert(Heap* ph, HData data)
{
	int idx = ph->numOfData + 1; // ���� ������ ���� �����ǹǷ� ���� ������ �������� �ϳ� ū �ε����� �ʱ�ȭ

	// ���ο� ��尡 ����� ��ġ�� ��Ʈ ����� ��ġ�� �ƴҶ����� �ݺ����� ����
	while (idx != 1)
	{
		// ���� ������ ���� �θ� ����� �켱������ ��
		if (ph->comp(data, ph->heapArr[GetParentIDX(idx)]) > 0) // ���� ������ ����� �켱 ������ ���ٸ�
		{
			ph->heapArr[idx] = ph->heapArr[GetParentIDX(idx)]; // ������ �θ� ����� ������ �ϳ� ������ -> ������ ������ ����
			idx = GetParentIDX(idx); // ���� ������ ����� ������ �ϳ� �ø��� -> �ε����� ����, ������ ������ �ö� ��Ȳ�� �ƴ�
		}
		else
			break; // �켱 ������ ���� �ʴٸ� �ݺ��� ����
	}
	// �ݺ��� ���� ��
	ph->heapArr[idx] = data; // ���� �ݺ����� ���� ���ŵ� idx ��ġ�� ���� ������ ��带 ����
	ph->numOfData += 1; // ������ ���� ����
}

// ���� ������ ����
HData HDelete(Heap* ph)
{
	HData rData = ph->heapArr[1]; // ��Ʈ ��带 �����ϹǷ� ������ �ε����� 1�� �����͸� �����´�.
	HData lastElem = ph->heapArr[ph->numOfData]; // �׸��� ������ ������ ��带 ����Ű�� ���� �ε����� numOfData�� �Ѵ�.

	int parentIdx = 1; // ������ ��带 ��Ʈ ���� �÷������� �ǹǷ� �ε����� 1�� �ʱ�ȭ, ������ ��尡 ����� ��ġ ������ ���� ����
	int childIdx; // �񱳸� ���� ����� �ڽ� ��� �ε��� ����


	// ��Ʈ ������ �����ؼ� �ڽ� ���� �켱 ������ ��
	while (childIdx = GetHiPriChildIDX(ph, parentIdx))
	{
		if (ph->comp(lastElem, ph->heapArr[childIdx]) >= 0) // ������ ���� �켱 ������ ��
			break; // ������ ����� �켱������ ���ų� ���ٸ� �ݺ��� ����
		ph->heapArr[parentIdx] = ph->heapArr[childIdx]; // �׷��� �ʴٸ� ���� �ڽ� ����� ������ �ϳ� �ø���. -> ������ ������ �ø�
		parentIdx = childIdx; // �׸��� ������ ��尡 ����� ��ġ�� �� ���� �Ʒ��� �����. -> �ε����� ����, ������ ������ ����
	}

	// �ݺ����� ������ �� ��
	ph->heapArr[parentIdx] = lastElem; // ������ ���ŵ� parentIdx ��ġ�� ������ ��带 �ش� ��ġ�� ���� 
	ph->numOfData -= 1; // ������ ���� ����
	return rData; // ��Ʈ ����� ������ ��ȯ
}