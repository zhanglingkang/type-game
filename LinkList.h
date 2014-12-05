//LinkList.h  ������LinkList
#ifndef LinkList_H
#define LinkList_H
template <class T>
struct Node
{
	T data;
	Node<T> *next;  //�˴�<T>Ҳ����ʡ��
};

template <class T>
class LinkList
{
public:
	LinkList( );  //����ֻ��ͷ���Ŀ�����
	LinkList(T a[ ], int n);  //������n��Ԫ�صĵ�����
	~LinkList();             //��������
	int Length();          //������ĳ���
	T Get(int i);           //ȡ�������е�i������Ԫ��ֵ
	int Locate(T x);       //��������ֵΪx��Ԫ�����
	void Update(int i,T x);  //����i������Ԫ��ֵ�޸�Ϊx
	void Insert(int i, T x);   //�ڵ������е�i��λ�ò���Ԫ��ֵΪx�Ľ��
	T Delete(int i);        //�ڵ�������ɾ����i�����
	void PrintList( );           //������������������������Ԫ��
	void  Reverse();       //��������
	void Clear();
private:
	Node<T> *first;  //�������ͷָ��
};

#endif
