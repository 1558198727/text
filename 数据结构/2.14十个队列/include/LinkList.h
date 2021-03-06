#ifndef LINKLIST_H
#define LINKLIST_H
#include<iostream>
using namespace std;
template<class T1>
class LinkNode
{
public:
   T1 data;
   LinkNode<T1>* Link;
};
template<class T1>
class LinkList
{
    public:
     LinkNode<T1> *head,*tail;  //表头和表尾指针
     LinkNode<T1> *prevPtr,*currPtr;//记录表当前遍历位置的指针，由插入和删除操作更新
     int position;

    int length;
     LinkList();
     //~LinkList();
     void disp();        //遍历输出链表
     int getSize(LinkNode<T1>*p);  //返回链表中的元素个数
     bool isEmpty()const; //链表是否为空
     void reset(int Pos=0);//初始化指针的位置，（第一位数的位置设置为零）
     void next();          //使指针移动到下一个节点
     bool endOfList()const;//指针是否到了链尾
     int  currentPosition(void);//返回指针当前的位置
     void insertHead(const T1&item);//在表头插入节点
     void insertTail(const T1&item);//在表尾插入节点
     void inserAt(const T1&item);   //在当前节点之前插入节点
     void insertAfter(const T1&item);//在当前节点之后插入节点
     T1 deleteHead();                //删除头节点
     void deleteCurrent();          //删除当前节点
     T1 & data();                    //返回对当前节点成员数据的引用
     const T1 &data()const;     //返回对当前节点成员数据的常引用
     void clear();            //清空链表，释放所有节点的数据空间
     LinkNode<T1> *setPos(int Pos);//返回指定位置pos的指针
     bool insertPos(const int i,const T1 value);//在指定位置插入节点
     bool deletePos(const int i); //删除指定位置的节点
     void daozhi();  //倒置链表
     T1 getMaxMember(LinkNode<T1>*p);
     T1 getAverage();
     int sum(LinkNode<T1>*p);


};

template<class T1>
LinkList<T1>::LinkList()
{
    cout<<"创建列表"<<endl;
    head=tail=NULL;
}

template<class T1>
void LinkList<T1>::insertTail(const T1&item)
{
    LinkNode<T1>* ptemp;
     ptemp=new LinkNode<T1>;
     ptemp->data=item;
	 ptemp->Link=0;
	 if(head==NULL)
     {
        head=tail=ptemp;
	 }

	 else
	 {
         tail->Link=ptemp;
         ptemp->Link=0;
         tail=ptemp;
	 }
     length++;
}


template<class T1>
int LinkList<T1>::getSize(LinkNode<T1>*p)
{
    LinkNode<T1> *temp;
    temp=p;
    if(temp->Link==NULL)
        return 1;
    else
    {
        temp=temp->Link;
        return getSize(temp)+1;
    }
}


template<class T1>
int LinkList<T1>::sum(LinkNode<T1>*p)
{
   LinkNode<T1> *temp=p;
    if(temp->Link==NULL)
        return temp->data;
    else
    {
        return sum(temp->Link)+temp->data;
    }
}


template<class T1>
void LinkList<T1>::daozhi()
{
  LinkNode<T1>*p1,*p2,*p3;
  cout<<"链表倒置"<<endl;
  if(length==1)
  {
      ;
  }
  else if(length==2)
  {
    tail->Link=head;
    head->Link=0;
    p1=tail;
    tail=head;
    head=p1;
  }
  else if(length>=3)
  {
    p1=head;
    p2=p1->Link;
    p3=p2->Link;
    p2->Link=p1;
    p1->Link=0;
    tail=p1;
    while(p1 && p2 && p3)
    {
     p1=p2;
     p2=p3;
     p3=p3->Link;
     p2->Link=p1;
    }
    head=p2;
  }
}



template<class T1>
T1 LinkList<T1>::getMaxMember(LinkNode<T1>*p)
{
    LinkNode<T1> * temp=p;
    if(temp->Link==NULL)
        return temp->data;
    else
    {
        int a=temp->data;
        temp=temp->Link;
        int b=getMaxMember(temp);
        return a>b?a:b;
    }
}

template<class T1>
T1 LinkList<T1>::getAverage()
{
  T1 sum=0;
   LinkNode<T1>*p=head;
   while(p)
   {
     sum+=p->data;
     p=p->Link;
   }
 return sum/length;
}

template<class T1>
void LinkList<T1>::disp()
{
   LinkNode<T1> *p;
   p=head;
   cout<<"遍历链表"<<endl;
   while(p)
   {
      (p->data).disp();
      p=p->Link;
   }
  cout<<endl<<endl;
}

#endif // LINKLIST_H
