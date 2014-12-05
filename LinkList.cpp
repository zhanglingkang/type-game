#include"LinkList.h"
#include<iostream>
template <class T>
LinkList<T>:: LinkList( )
{
	first=new Node<T>; first->next=NULL;
}
template <class T>  
LinkList<T>:: LinkList(T a[ ], int n)
{
	first=new Node<T>;   //����ͷ���
	Node<T> *r,*s;
	r=first;          //βָ���ʼ��
	for (int i=0; i<n; i++)
	{ 
		s=new Node<T>; s->data=a[i];  //Ϊÿ������Ԫ�ؽ���һ�����
		r->next=s; r=s;      //���뵽�ն˽��֮��
	}
	r->next=NULL;    //����������ϣ����ն˽���ָ�����ÿ�
}
template <class T>
LinkList<T>:: ~LinkList()
{
}
template <class T>
T LinkList<T>::Get(int i) 
{   
	Node<T> *p; 
	int j;
	p=first->next; 
	j=1;  //��p=first;  j=0;
	while (p && j<i)    
	{
		p=p->next;       //����ָ��p����
		j++;
	}
	if (!p) throw "λ��";
	else return p->data;
}
template <class T> 
int LinkList<T>::Locate(T x)
{
	Node<T> *p; int j;
	p=first->next; j=1;
	if(p&&p->next){
		while(p->data!=x)
		{
			p=p->next;
			j++;
		}
		return j;
	}
	else throw "λ��";

}
template<class T>
void LinkList<T>::Insert(int i, T x)
{  
	Node<T> *p; int j;
	p=first ; j=0;    //����ָ��p��ʼ��
	while(p && j<i-1)
	{
		p=p->next;   //����ָ��p����
		++j;
	}
	if (!p) throw "λ��";
	else { 
		Node<T> *s;
		s=new Node<T>; 
		s->data=x;  //���ڴ�����һ�����s����������Ϊx
		s->next=p->next;       //�����s���뵽���p֮��
		p->next=s;
	}
}
template <class T> 
int LinkList<T>::Length( )
{
	Node <T> *p = first->next;
	int i = 0;
	while(p)
	{
		p = p->next;
		i++;
	}
	return i;
}
template <class T>  
T LinkList<T>::Delete(int i)
{ 
	Node<T> *p; int j;
	p=first ; j=0;  //����ָ��p��ʼ��
	while (p && j<i-1)  //���ҵ�i-1�����
	{
		p=p->next;
		j++;
	}
	if (!p || !p->next) throw "λ��";  //���p�����ڻ���p�ĺ�̽�㲻����
	else {
		Node<T> *q; 
		T x;
		q=p->next;
		x=q->data;  //�ݴ汻ɾ���
		p->next=q->next;  //ժ��
		delete q; 
		return x;
	}
}
template <class T> 
void LinkList<T>::PrintList( )
{
	Node<T> *p;
	p=first->next;
	while (p)
	{
		cout<<p->data<<endl;
		p=p->next;
	}

}
template <class T> 
void LinkList<T>::Reverse()
{
	Node <T> *p,*u;
	p=first->next;
	first->next=NULL;
	while(p)
	{
		u=p->next;
		p->next=first->next;
		first->next=p;
		p=u;
	}
}
template <class T>  
void LinkList<T>::Update(int i,T x)
{
	Node<T> *p; int j;
	p=first ; j=0;    //����ָ��p��ʼ��
	while (p && j<i-1)
	{
		p=p->next;   //����ָ��p����
		j++;
	}
	if(p&&p->next)
		p->next->data=x;
	else throw("λ��");
}
template <class T> 
void LinkList<T>::Clear()
{
	Node<T> *p=this->first->next;
	Node<T> *q =NULL;
	this->first->next=NULL;
	while(NULL!=p)
	{
		q=p;
		p=p->next;
		delete q;
	}
}
