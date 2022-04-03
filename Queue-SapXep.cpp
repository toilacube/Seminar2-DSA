#include <iostream>
#include <vector>

using namespace std;

struct INode
{
	int info;
	INode* pNext;
};
struct IQueue
{
	INode* pHead;
	INode* pTail;
};
void CreateEmptyQueue(IQueue& q)
{
	q.pHead = NULL;
	q.pTail = NULL;
}
INode* CreateNodeQueue(int s)
{
	INode* q = new INode();
	q->info = s;
	q->pNext = NULL;
	return q;
}
bool IsEmpty(IQueue q) {
	return q.pHead == NULL;
}
void EnQueue(IQueue& q, INode* s)
{
	if (q.pHead == NULL)
	{
		q.pHead = s;
		q.pTail = s;
	}
	else
	{
		q.pTail->pNext = s;
		q.pTail = s;
	}
}
void DeQueue(IQueue& q)
{
	if (IsEmpty(q) == 1)
		return;
	INode* s = q.pHead;
	q.pHead = q.pHead->pNext;
	if (q.pHead == NULL)
		q.pTail = NULL;
	delete s;
}

int GetFront(IQueue& q)
{
	if (IsEmpty(q))
		exit(1);
	return q.pHead->info;
}
void solve(int N_1, vector<int> arr_1, int N_2, vector<int> arr_2) {
	// Tao Queue s_1 luu tru cac gia tri cua mang arr_1
	IQueue s_1;
	CreateEmptyQueue(s_1);
	for (int i = 0; i < N_1; i++)
		EnQueue(s_1, CreateNodeQueue(arr_1[i]));
	// Tao Queue s_1 luu tru cac gia tri cua mang arr_2
	IQueue s_2;
	CreateEmptyQueue(s_2);
	for (int i = 0; i < N_2; i++)
		EnQueue(s_2, CreateNodeQueue(arr_2[i]));

	vector<int> ans(N_1 + N_2); // Mang ans la mang gop cua 2 mang ban dau
	int cur = 0;
	while (!IsEmpty(s_1) && !IsEmpty(s_2))
	{
		// Lay phan tu be hon o dau 2 Queue, them vao mang ans de giu nguyen thu tu tang dan
		if (GetFront(s_1) < GetFront(s_2)) {
			ans[cur++] = GetFront(s_1);
			DeQueue(s_1);
		}
		else {
			ans[cur++] = GetFront(s_2);
			DeQueue(s_2);
		}
	}
	// Them vao mang ans cac phan tu con lai chua duoc xet
	while (!IsEmpty(s_1)) {
		ans[cur++] = GetFront(s_1);
		DeQueue(s_1);
	}

	while (!IsEmpty(s_2)) {
		ans[cur++] = GetFront(s_2);
		DeQueue(s_2);
	}
	for (int i = 0; i < cur; i++) cout << ans[i] << " ";
}
int main()
{
	int N_1 = 5; vector<int> arr_1 = { 0, 1, 3, 5, 9 };
	int N_2 = 5; vector<int> arr_2 = { 2, 4, 6, 7, 8 };
	solve(N_1, arr_1, N_2, arr_2);
}
