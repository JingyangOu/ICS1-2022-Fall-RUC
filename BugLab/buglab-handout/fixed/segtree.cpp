#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

const int MAXN=1e5+10;

struct Node{
	long long  l;
	long long  r;
	long long  add;
	long long  sum;
	int size;
	Node* lch;
	Node* rch;
    ~Node();
	Node(long long ,long long );
	void Maintain();
	void PushDown();
	long long Query(const int &,const int &);
	void Add(const long long &,const long long &,const long long &);
};

long long  data[MAXN];

int main(){
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%lld",data+i);
	Node* N=new Node(1,n);
	int t,l,r,d;
	for(int i=0;i<q;i++){
		scanf("%d",&t);
		if(t==1){
			scanf("%lld%lld%lld",&l,&r,&d);
			N->Add(l,r,d);
		}
		else if(t==2){
			scanf("%d%d",&l,&r);
			printf("%lld\n",N->Query(l,r));
		}
	}
    delete N;
	return 0;
}

Node::Node(long long  l,long long  r){
	this->l=l;
	this->r=r;
	this->add=0;
	this->size=r-l+1;
	if(l==r)
		{this->sum=data[r];
		this->lch = nullptr;
		this->rch = nullptr;
		}
	else{
		int mid=(l+r)>>1;
		this->lch=new Node(l,mid);
		this->rch=new Node(mid+1,r);
		this->Maintain();
	}
}

Node::~Node(){
    if(this->lch != nullptr)
        delete this->lch;
    if(this->rch != nullptr)
        delete this->rch;
}

void Node::Add(const long long & l,const long long & r,const long long & d){
	if(l<=this->l&&this->r<=r){
		this->add+=d;
		this->sum+=d*this->size;
	}
	else{
		this->PushDown();
		if(l<=this->lch->r)
			this->lch->Add(l,r,d);
		if(this->rch->l<=r)
			this->rch->Add(l,r,d);
		this->Maintain();
	}
}

long long Node::Query(const int& l,const int& r){
	if(l<=this->l&&this->r<=r)
		return this->sum;
	else{
		this->PushDown();
		if(r<=this->lch->r)
			return this->lch->Query(l,r);
		if(this->rch->l<=l)
			return this->rch->Query(l,r);
		return this->lch->Query(l,r)+this->rch->Query(l,r);
	}
}

inline void Node::Maintain(){
	this->sum=this->lch->sum+this->rch->sum;
}

inline void Node::PushDown(){
	if(this->add){
		this->lch->add+=this->add;
		this->rch->add+=this->add;
		this->lch->sum+=this->add*this->lch->size;
		this->rch->sum+=this->add*this->rch->size;
		this->add=0;
	}
}
