//https://www.geeksforgeeks.org/count-of-numbers-in-given-array-greater-than-next-k-elements/
/*
Đề: Cho 1 mảng arr[] chứa N số nguyên, tìm số phần tử trong mảng có giá trị lớn hơn K phần tử bên phải phần tử đó. 
Nếu có phần tử có ít hơn K phần tử ở bên phải thì mọi phần tử ở bên phải phần tử đó
phải nhỏ hơn nó.
Ví dụ với mảng arr[] = {9, 7, 7, 7, 4}, N = 5, K = 3
Xét từ cuối lên đầu: phần tử 4 không có phần tử nào bên phải nên thỏa mãn
Phần tử 7(vị trí thứ 4) có 1 phần tử 4 ở bên phải nên thỏa mãn
Phần tử 7(vị trí thứ 3) có 2 phần tử bên phải là 7 với 4, nhưng 7 không lớn hơn 7 nên không thỏa mãn.
Tương tự cho phần tử 7(vị trí thứ 2) có k=3 phần tử bên phải là 7,7 và 4 nên không thỏa mãn.
Phần tử 9(vị trí thứ 1) có K=3 phần tử bên phải đều nhỏ hơn là 7,7 và 7 nên thỏa mãn.
Vậy đáp là 3 với 3 vị trí thỏa mã là 1,4 và 5.
*/
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
{	//EnQueue is add pTail
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

//Tìm Node lớn nhất trong 1 Queue
int Find_Max(IQueue q)  
{
	int ans = INT_MIN;
	INode* temp = q.pHead;
	while (temp!=NULL)
	{
		ans = max(ans, temp->info);
		temp = temp->pNext;
	}
	return ans;
}

// Giải
int Solution(int n, int k, vector<int> arr)
{
	IQueue q;
	CreateEmptyQueue(q);

	int max_value = INT_MIN;
	int count = 0;

	//Xác định đoạn có các phần tử có số phần tử ở bên phải bé hơn K.
	int p = n - k;

	// Kiểm tra trường hợp đặc biệt
	if (n == 0)
		return 0;
	else if (k == 0)
		return n;

	// Đưa K phần tử cuối cùng vào Queue
	for (int i = n - 1; i >= p; i--)
	{
		EnQueue(q, CreateNodeQueue(arr[i]));

		// Nếu phần tử vừa thêm vào lớn phần tử lớn nhất 
		// đang có trong mảng thì phần tử đó thỏa mãn
		if (arr[i] > max_value)
		{
			max_value = arr[i];
			count++;
		}
	}

	// Đưa các phần tử còn lại vào Queue
	for (int i = p - 1; i >= 0; i--)
	{
		int x = GetFront(q);

		// Bỏ phần tử cuối cùng ra vì ta chỉ cần xét
		// K phần tử bên phải phần tử cần xét
		DeQueue(q);

		// Thêm
		EnQueue(q, CreateNodeQueue(arr[i]));
		if (arr[i] > max_value)
		{
			count++;
			max_value = arr[i];
		}
		else
		{
			if (x == max_value)
			{
				// If DeQueueped value
				// is same as max value
				// then update max value

				max_value = Find_Max(q);
			}
		}
	}
	return count;
}
int main()
{
	int N, K;
	N = 5;
	K = 2;
	 vector<int> arr = { 4, 3, 5, 1, 2};
	cout << "Answer: " <<Solution(N, K, arr) << "\n";
	return 0;
}


