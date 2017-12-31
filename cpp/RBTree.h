#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<cstdio>
#define RED  true;
#define BLACK false;
using namespace std;
class RBTree
{
private:

	class Node
	{
	public:
		string word;
		bool color;
		int cnt;
		int N;
		Node *left=NULL, *right=NULL;
		Node(string _word, int _cnt, int _N, bool _color) :word(_word), cnt(_cnt), N(_N), color(_color) {}
		Node() {}
	};

	Node *root = NULL;

	bool isRed(Node *x)
	{
		if (x == NULL)
			return false;
		return x->color == RED;
	}

	int size(Node* x)
	{
		if (x == NULL)
			return 0;
		else
			return x->N;
	}

	/*左旋转*/
	Node* rotateLeft(Node *h)
	{
		Node *x = h->right;
		h->right = x->left;
		x->left = h;
		x->color = h->color;
		h->color = RED;
		x->N = h->N;
		h->N = 1 + size(h->left) + size(h->right);
		return x;
	}

	/*右旋转*/
	Node* rotateRight(Node *h)
	{
		Node *x = h->left;
		h->left = x->right;
		x->right = h;
		x->color = h->color;
		h->color = RED;
		x->N = h->N;
		h->N = 1 + size(h->left) + size(h->right);
		return x;
	}

	/*变换颜色*/
	void flipColors(Node *h)
	{
		h->color = RED;
		h->left->color = BLACK;
		h->right->color = BLACK;
	}

	Node* put(Node* h, string word, int cnt)
	{
		if (h == NULL){
			cout << word<<endl;
			return new Node(word,cnt, 1, true);}
		int cmp = h->word.compare(word);
		if (cmp>0) 
			h->left = put(h->left, word, cnt);
		else if (cmp<0) 
			h->right = put(h->right, word, cnt);
		else
			h->cnt = cnt;
		if (isRed(h->right) && !isRed(h->left))
			h = rotateLeft(h);
		if (isRed(h->left) && isRed(h->left->left))
			h = rotateRight(h);
		if (isRed(h->left) && isRed(h->right)) 
			flipColors(h);

		h->N = size(h->left) + size(h->right) + 1;
		return h;
	}

	int get(Node* h, string word)
	{
		if (h == NULL)
			return 0;
		int cmp = h->word.compare(word);
		if (!cmp)
			return h->cnt;
		else if (cmp>0&&h->left)
			return get(h->left, word);
		else if(h->right)
			return get(h->right, word);
		return 0;
	}

	bool find(Node* h,string word)
	{
		if (h == NULL)
			return false;
		int cmp = h->word.compare(word);
		if (cmp<0)
			return find(root->right, word);
		else if (cmp>0)
			return find(root->left, word);
		else if(h->word==word)
			return true;
		return false;
	}

	void print(Node* h)
	{
		if (h == NULL)
			return;
		else {
			print(h->left);
			printf("%-20s%5d\n", h->word.c_str(), h->cnt);
			print(h->right);
		}
	}
	
	void output(Node* h, ofstream& out)
	{
		if (h == NULL)
			return;
		else {
			char strs[100];
			snprintf(strs, sizeof(strs), "%-30s%5d\n", h->word.c_str(), h->cnt);
			output(h->left, out);
			out << string(strs);
			output(h->right, out);
		}
	}

	void deleteall(Node* h)
	{
		if (h == NULL)
			return;
		else {
			deleteall(h->left);
			deleteall(h->right);
			delete h;
		}
	}

public:
	/*默认初始化*/
	RBTree() {}

	/*讲键值对存入树中*/
	void put(string key, int cnt)
	{
		root = put(root, key, cnt);
		root->color = BLACK;
	}

	/*在树中查找是否存在该字符串*/
	bool find(string key)
	{
		return find(root, key);
	}


	/*在树中查找该字符串对应的频率*/
	int get(string key)
	{
		return get(root,key);
	}

	/*先序遍历红黑树,并输出*/
	void print()
	{
		print(root);
	}

	/*中序遍历红黑树，并存入文件流*/
	void output(ofstream& out)
	{
		output(root, out);
	}

	/*该树的大小*/
	int size()
	{
		return size(root);
	}

	/*删除所有节点*/
	void deleteall()
	{
		deleteall(root);
	}
};