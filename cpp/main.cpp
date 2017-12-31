#include<iostream>
#include<fstream>
#include"RBTree.h"
#include<regex>
#include<string>
#include<ctime>
#include<vector>
using namespace std;

/*判断字符是否为字母*/
bool isalpha(char a)
{
	if (a >= 'a'&&a <= 'z')
		return true;
	if (a >= 'A'&&a <= 'Z')
		return true;
	return false;
}

int main()
{
	RBTree tree;

	
	//读写文件流
	ifstream in("input.txt", ios::in);
	ofstream out("words.txt", ios::out);


	/*存储文本提取后的单词*/
	vector<string> words;

	if (!in.is_open()) {
		cout << "Error opened file" << endl;
		exit(1);
	}

	clock_t time1 = clock();

	/*读取文件流中的单词*/
	while (!in.eof()) {
		string temp;
		getline(in, temp);
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);	//将单词全部转换为小写形式
		for (size_t it = 0; it < temp.size(); it++)
		{
			if (isalpha(temp[it])) {
				int len = 0;
				while (isalpha(temp[it + len])) {
					len++;
				}
				words.push_back(string(temp.begin() + it, temp.begin() + it + len));
				it = it + len;
			}
		}
	}

	clock_t time2 = clock();
	cout << "It took " << ((double)time2 - time1) / CLOCKS_PER_SEC << " seconds" << endl;

	/*遍历vector，将单词存入红黑树中*/
	for (string word : words) {
		int num = tree.get(word);
		if (num == 0) {
			tree.put(word, 1);
		}
		else {
			tree.put(word, num + 1);
		}
	}

	//中序遍历红黑树并写入文件流中
	tree.output(out);

	//树的大小
	cout << tree.size() << endl;


	clock_t time3 = clock();
	cout << "It took " << ((double)time3-time1) / CLOCKS_PER_SEC << " seconds" << endl;
	tree.print();
	out.close();
	in.close();
	tree.deleteall();
	cin.get();
	
	return 0;
}