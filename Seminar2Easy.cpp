#include <iostream>
#include <vector>
using namespace std;
// Thông tin của 1 người bao gồm: chiều cao-height, số người cao hơn đứng trước-check_behind,
// số người cao bằng đứng sau-the_same.
struct info
{
	int height;
	int check_behind;
	int the_same;
};
struct INode
{
	info data;
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
INode* CreateNodeStack(info s)
{
	INode* q = new INode();
	q->data = s;
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
	s.pHead = s.pHead->pNext;
	if (s.pHead == NULL)
		s.pTail = NULL;
	delete p;
}

info _top(IStack& s)
{
	if (IsEmpty(s))
		exit(1);
	return s.pHead->data;
}

info data(int h, int behind, int same)
{
	info temp;
	temp.height = h;
	temp.check_behind = behind;
	temp.the_same = same;
	return temp;
}

int Solution(vector<int> arr, int n)
{
	IStack S;
	CreateEmptyStack(S);
	info TOP;

	//Số cặp thỏa mãn
	int count = 0;
	for (int i = 0; i < n; i++)
	{

		// Nếu có người đứng trước chưa kiểm tra (phần tử đầu trong Stack )
		if (!IsEmpty(S)) TOP = _top(S);

		// TH1: Nếu Stack rỗng thì cho người này vào Stack để kiểm tra với người tiếp theo
		if (IsEmpty(S))
		{
			_push(S, CreateNodeStack(data(arr[i], 0, 0)));
		}

		/*TH3: Nếu Stack không rỗng=có người ở trước,
		 và người đang xét thấp hơn người ở trước
		 ==> người ở trước vẫn có thể thấy được người tiếp theo
		 ==> đưa người đang xét vào Stack để xét ở lượt sau
		*/
		else if (!IsEmpty(S) && TOP.height > arr[i])
		{
			// Xét tiếp xem còn người tiếp theo nào mà người ở trước đó còn có thể nhìn thấy không

			_push(S, CreateNodeStack(data(arr[i], 1, 0)));

			//count++ để thêm 1 cặp 2 người liên tiếp có thể thấy nhau.
			count++;
		}

		/* TH4: Stack không rỗng và người đang xét cao bằng người ở trước
			Lưu ý là người cao bằng nhau liên tiếp vẫn có thể thấy người
			cao hơn ở sau đó.

		*/
		else if (!IsEmpty(S) && TOP.height == arr[i])
		{
			//count++ để thêm 1 cặp 2 người liên tiếp có thể thấy nhau.
			count++;

			count += TOP.the_same;
			if (TOP.check_behind == 1)
			{
				count++;
			}

			// TOP.the_same + 1 để đếm số người sau này cao bằng
			_push(S, CreateNodeStack(data(arr[i], TOP.check_behind, TOP.the_same + 1)));
		}

		/*
			TH2: Stack không rỗng và người đang xét cao hơn người ở trước
		*/
		else if (!IsEmpty(S) && TOP.height < arr[i])
		{

			// Kiểm tra tất cả những người còn ở trong Stack
			while (TOP.height < arr[i])
			{
				count++;
				_pop(S);
				if (IsEmpty(S)) break;
				TOP = _top(S);
			}

			// Bây giờ ta xét những người ở trước sau khi đã loại những người thấp hơn.
			// Người ở trước đó nhiều vị trí vẫn có thể
			// thấy được người đang xét, sau khi đã loại hết những người thấp hơn ở giữa.
			if (!IsEmpty(S)) TOP = _top(S);


			if (!IsEmpty(S) && TOP.height == arr[i])
			{
				count++;
				count += TOP.the_same;
				if (TOP.check_behind == 1)
				{
					count++;
				}
				_push(S, CreateNodeStack(data(arr[i], TOP.check_behind, TOP.the_same + 1)));
			}


			else if (!IsEmpty(S) && TOP.height > arr[i])
			{
				count++;

				// Xét tiếp xem còn người tiếp theo nào mà người ở trước đó nhiều vị trí còn có thể nhìn thấy không
				_push(S, CreateNodeStack(data(arr[i], 1, 0)));
			}

			// Đưa và Stack để xét cho người sau
			else _push(S, CreateNodeStack(data(arr[i], 0, 0)));
		}
	}
	return count;
}
int main()
{
	int N = 7;
	vector <int> arr = { 2, 4, 1, 2, 2, 5, 1 };
	cout << "Answer: " << Solution(arr, N);
	return 0;

}