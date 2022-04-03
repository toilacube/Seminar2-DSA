#include <iostream>
#include <vector>

using namespace std;

struct INode
{
	int info;
	INode* pNext;
};
struct IStack
{
	INode* pHead;
	INode* pTail;
};
void CreateEmptyStack(IStack& s)
{
	s.pHead = NULL;
	s.pTail = NULL;
}
INode* CreateNodeStack(int s)
{
	INode* q = new INode();
	q->info = s;
	q->pNext = NULL;
	return q;
}
bool IsEmpty(IStack s) {
	return s.pHead == NULL;
}
void _push(IStack& s, INode* p)
{
	if (s.pHead == NULL)
	{
		s.pHead = p;
		s.pTail = p;
	}
	else
	{
		p->pNext = s.pHead;
		s.pHead = p;
	}
}
void _pop(IStack& s)
{
	if (IsEmpty(s) == 1)
		return;
	INode* p = s.pHead;
	int x = p->info;
	s.pHead = s.pHead->pNext;
	if (s.pHead == NULL)
		s.pTail = NULL;
	delete p;
}

int _top(IStack& s)
{
	if (IsEmpty(s))
		exit(1);
	return s.pHead->info;
}

void solve(int N, vector<int> arr) {
	int ID = 1;
	IStack DuongPhu;
	CreateEmptyStack(DuongPhu);
	//Kiem tra tung xe, so voi ID hien tai, neu bang thi duoc qua, neu khong thi vao //Duong Phu.
	for (int i = 0; i < N; i++) {
		if (arr[i] != ID) _push(DuongPhu, CreateNodeStack(arr[i]));
		else {
//Sau moi lan co xe duoc qua, tang ID va kiem tra ID voi xe o Duong Phu, neu Duong Phu co xe phu hop thi cho xe qua.
			ID++;
			while (!IsEmpty(DuongPhu) && _top(DuongPhu) == ID) {
				_pop(DuongPhu);
				ID++;
			}
		}
	}
	if (IsEmpty(DuongPhu)) cout << "yes";
	else cout << "no";
}
int main()
{
	int N = 5;  vector<int> arr = { 5, 1, 2, 4, 3 };
	solve(N, arr);
	return 0;
}
