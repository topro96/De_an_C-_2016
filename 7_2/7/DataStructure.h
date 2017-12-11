#pragma once
#include <iostream>
#include <ctime>
using namespace std;

template <class T>
struct note
{
	int _key;
	T *_data;
	note<T> *_left, *_right;
	int _bf;
	note(T *val, int k) {
		_data = val;
		_key = k;
		_left = _right = 0;
		_bf = 0;
	}
	note()
	{
		_data = new note<T>;
		_key = -1;
		_left = _right = 0;
		_bf = 0;
	}
};

template <class T>
class AVL
{

public:
	note<T> *_root;
	~AVL() {}
	note<T>* RotateLeft(note<T>* root) {
		note<T>* p = 0;
		if (root != 0 && root->_right != 0) {
			p = root->_right;
			root->_right = p->_left;
			p->_left = root;
		}
		return p;
	}
	note<T>* RotateRight(note<T>* root) {
		note<T>* p = 0;
		if (root != 0 && root->_left != 0) {
			p = root->_left;
			root->_left = p->_right;
			p->_right = root;
		}
		return p;
	}
	template <class type>
	void Swap(type &a, type &b) {
		type c = a;
		a = b;
		b = c;
	}

	void RotateLeftLeft(note<T>* &root) {
		if (root->_left->_bf == 0)
		{
			root->_left->_bf = -1;
		}
		else
		{
			root->_bf = 0;
			root->_left->_bf = 0;
		}
		root = RotateRight(root);
	}

	void RotateRightRight(note<T>* &root) {
		if (root->_right->_bf == 0)
		{
			root->_right->_bf = 1;
		}
		else {
			root->_bf = 0;
			root->_right->_bf = 0;
		}

		root = RotateLeft(root);
	}

	void RotateLeftRight(note<T>* &root) {
		note<T> *ya, *s;
		ya = root;
		s = root->_left;
		root->_left = RotateLeft(s);
		root = RotateRight(root);
		if (root->_bf == 0)
		{
			ya->_bf = 0;
			s->_bf = 0;
		}
		else {
			if (root->_bf == 1)
			{
				ya->_bf = -1;
				s->_bf = 0;
			}
			else
			{
				ya->_bf = 0;
				s->_bf = 1;
			}
			root->_bf = 0;
		}
	}

	void RotateRightLeft(note<T>* &root) {
		note<T> *ya, *s;
		ya = root;
		s = root->_right;
		root->_right = RotateRight(s);
		root = RotateLeft(root);
		if (root->_bf == 0)
		{
			ya->_bf = 0;
			s->_bf = 0;
		}
		else {
			if (root->_bf == -1)
			{
				ya->_bf = 1;
				s->_bf = 0;
			}
			else
			{
				ya->_bf = 0;
				s->_bf = -1;
			}
			root->_bf = 0;
		}
	}

	int Insert(note<T>* &root, T *val, int k) {
		if (root == 0)
		{
			root = new note<T>(val, k);
			return 1;
		}
		note<T>* fp, *q, *p, *fya, *ya, *s;
		int imbal;
		p = root;
		ya = p;
		fp = fya = 0;
		while (p != 0)
		{
			if (k == p->_key)
				return 0;
			if (k < p->_key)
				q = p->_left;
			else
				q = p->_right;
			if (q != 0)
				if (q->_bf != 0) {
					fya = p;
					ya = q;
				}
			fp = p;
			p = q;
		}
		q = new note<T>(val, k);
		if (k > fp->_key)
			fp->_right = q;
		else
			fp->_left = q;

		if (k < ya->_key)
			p = ya->_left;
		else
			p = ya->_right;

		s = p;
		while (p != q)
		{
			if (k < p->_key) {
				p->_bf = 1;
				p = p->_left;
			}
			else {
				p->_bf = -1;
				p = p->_right;
			}
		}

		if (k < ya->_key)
			imbal = 1;
		else
			imbal = -1;

		if (ya->_bf == 0) {
			ya->_bf = imbal;
			return 1;
		}
		if (ya->_bf != imbal) {
			ya->_bf = 0;
			return 1;
		}

		if (s->_bf == imbal)
			if (imbal == 1)//l-l
				RotateLeftLeft(ya);
			else    //r-r
				RotateRightRight(ya);
		else
			if (imbal == 1) //l-r
				RotateLeftRight(ya);
			else //r-l
				RotateRightLeft(ya);

		if (fya == 0)
			root = ya;
		else
			if (ya->_key > fya->_key)
				fya->_right = ya;
			else
				fya->_left = ya;
		return 1;
	}

	void BalancLeft(note<T>* &root) {
		if (root->_left->_bf == 1 || root->_left->_bf == 0)
		{
			RotateLeftLeft(root);
		}
		else
		{
			RotateLeftRight(root);
		}
	}

	void BalancRight(note<T>* &root) {
		if (root->_right->_bf == -1 || root->_right->_bf == 0)
		{
			RotateRightRight(root);
		}
		else
		{
			RotateRightLeft(root);
		}
	}

	int DeleteLeft(note<T>* &p) {
		if (p->_bf == 0)
		{
			p->_bf = -1;
			return 0;
		}
		else
		{
			if (p->_bf == -1)//mat can bang ben phai
			{
				BalancRight(p);
				//if (fp != 0)fp->_left = p;
			}
			else
			{
				p->_bf = 0;
			}
		}
		return 1;
	}

	int DeleteRight(note<T>* &p) {
		if (p->_bf == 0)
		{
			p->_bf = 1;
			return 0;
		}
		else
		{
			if (p->_bf == -1)
			{
				p->_bf = 0;
			}
			else
			{
				BalancLeft(p);
				//if (fp != 0)fp->_right = p;
			}
		}
		return 1;
	}

	int DeleteNode(note<T>* &p, int k, note<T>* q = 0, int huong = 0) {
		int res;
		if (p != 0) //p==0 nghia la tim khong co gia tri
			if (q == 0) //tim q co key == k
				if (k < p->_key) ///////////////////////////////// trai
				{
					res = DeleteNode(p->_left, k);
					if (res == 1)
						res = DeleteLeft(p);
				}
				else
				{
					if (k > p->_key) //////////////////////////////////phai
					{
						res = DeleteNode(p->_right, k);
						if (res == 1)
							res = DeleteRight(p);
					}
					else {
						q = p;
						if (p->_left != 0) {
							res = DeleteNode(p->_left, k, q, 1);//huong==1 da~ di qua trai
							if (res == 1)
								res = DeleteLeft(p);
						}
						else
							if (p->_right != 0) {
								res = DeleteNode(p->_right, k, q, -1);//da di qua phai
								if (res == 1)
									res = DeleteRight(p);
							}
							else
							{
								delete p;
								p = 0;
								return 1;
							}
					}
				}
			else //da xac dinh duoc q
			{
				if (huong == 1)
				{
					if (p->_right != 0) {
						res = DeleteNode(p->_right, k, q, 1);
						if (res == 1)
							res = DeleteRight(p);
					}
					else {
						if (p->_left == 0) {
							Swap(q->_key, p->_key);
							Swap(q->_data, p->_data);
							delete p;
							p = 0;
						}
						else
						{
							Swap(q->_key, p->_key);
							Swap(q->_data, p->_data);
							q = p;
							p = p->_left;
							delete q;
						}
						return 1;
					}
				}
				else
				{
					if (p->_left != 0) {
						res = DeleteNode(p->_left, k, q, -1);
						if (res == 1)
							res = DeleteLeft(p);
					}
					else {
						if (p->_right == 0) {
							Swap(q->_key, p->_key);
							Swap(q->_data, p->_data);
							delete p;
							p = 0;
						}
						else
						{
							Swap(q->_key, p->_key);
							Swap(q->_data, p->_data);
							q = p;
							p = p->_right;
							delete q;
						}
						return 1;
					}
				}
			}
		return 0;
	}

	void DeleteTree(note<T>* &p)
	{
		if (p != NULL)
		{
			DeleteTree(p->_left);
			DeleteTree(p->_right);
			delete p;
		}
	}

	note<T>* Search(int k, note<T>* root) {
		note <T> *p;
		p = root;
		while (p!=NULL)
		{
			if (k < p->_key)
				p = p->_left;
			else
				if (k > p->_key)
					p = p->_right;
				else
					return p;
		}
		return NULL;
	}
	void LNR(note<T>* root) {
		if (root != 0)
		{
			LNR(root->_left);
			std::cout << root->_key << " ";
			LNR(root->_right);
		}
	}

	AVL()
	{
		_root = NULL;
	}

};

#define MAX  500
struct MyArray
{
	int myArray[MAX];
	int index; //số phân tử đã được chọn

	//thêm vị trí x tong mảng từ index đến 500 được chọn
	void Insert(int x) 
	{
		if (index < MAX)
		{
			swap(myArray[index], myArray[x]);
			index++;
		}
		else
		{
			//khong the them
		}
	}

	//xóa đi 1 giá trị được chọn
	void Delete(int i)
	{
		if (index > 0)
		{
			swap(myArray[i], myArray[index - 1]);//đổi giá trị ô chọn với ô cuối cùng
			index--;
		}
	}
	
	int getRandFree() //trả về giá trị random được ben phia chua chon
	{
		if (index >= MAX)
		{
			//đã chọn hết
			return -1;
		}
		else
		{
			srand(time(NULL));
			int x = rand() % (MAX - index + 1) + index;
			return x;
		}
	}

	int getRandSelected()
	{
		if (index ==0)
		{
			return -1;
		}
		else
		{
			srand(time(NULL));
			int x = rand() % (index);
			return x;
		}
	}

	//khoi tao lai tu dau
	void Remake()
	{
		for (int i = 0; i < 500; i++)
			myArray[i] = i;
		index = 0;
	}

	MyArray()
	{
		for (int i = 0; i < 500; i++)
			myArray[i] = i;
		index = 0;
	}

};

