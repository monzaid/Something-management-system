#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<iomanip>
#include <list>
using namespace std;
class item
{
	public:
	string name;
	string item_type;
	bool Register;
};
//杂志类
class magazine :public item
{
	string Type;
	string Writer;
};
//MusicCd类
class MusicCd :public item
{
	string Singer;
};
//电影类
class Movie :public item
{
	string Type;
	string Director;
	string Actor;
};
//书籍类
class Book : public item
{
public:
	Book() { borrow_flag = false; }   //无参构造函数
	Book(string name, string num, string auther)
		:name(name), num(num), auther(auther) {
		borrow_flag = false;
	}  //有参构造函数
	void setReader(string reader, int lcn, string data); //设置读者
	void setInfo(string name, string num, string auther); //设置书籍信息
	string getName() {
		return name;
	}
	string getNum() { return num; }
	string getAuther() {
		return auther;
	}
	bool getBorrow_flag() {
		return borrow_flag;
	}
	string getReader() {
		return reader;
	}
	int getLcn() {
		return lcn;
	}
	string getData() {
		return data;
	}
	bool isBorrow() { return borrow_flag; }        //判断书籍是否借出
	void setBorrow_flag(bool b) { borrow_flag = b; }
	void showInfo();        //显示数据信息
private:
	string name;  //书名
	string num;   //编号（唯一标示）
	string auther; //作者

	bool borrow_flag;
	string reader; //读者
	int lcn;       //借书证号
	string data;   //借书日期
};
//DVD电影类
class DVD :public Movie
{
	string Type;
	string Director;
	string Actor;
};
//蓝光电影类
class Blue_ligh :public Movie
{
    string Type;
	string Director;
	string Actor;
};

//用户
class Person
{
public:
	string Name;
	string Adress;
	list<item> Regist_items;
};

void Book::setReader(string reader, int lcn, string data)
{
	borrow_flag = true;
	this->reader.assign(reader);
	this->lcn = lcn;
	this->data.assign(data);
}
void Book::setInfo(string name, string num, string auther)
{
	this->name.assign(name);
	this->num.assign(num);
	this->auther.assign(auther);
}
void Book::showInfo()
{
	cout << "书籍名称：" << setiosflags(ios_base::left) << setw(56) << name << endl
		 << "书籍编号：" << setw(56) << num<< endl
		 << "书籍作者：" << setw(56) << auther  << endl;
	if (borrow_flag)
	{
	   cout << "书籍被借出。                                                      \n"
			<< "读者姓名：" << setw(56) << reader<< endl
			<< "借书证号：" << setw(56) << lcn << endl
			<< "借书日期：" << setw(56) << data << endl;
	}
	else {
		cout << "书籍未被借出。                                                    \n";
	}
}
class Library
{
public:
	//书籍库
	list<item> itemList;
	Library() { currentNum = 0; brrowNum = 0; }
	void addBook();                //向图书馆里加书籍
	void addBook(string name, string num, string auther);
	void deleteBook();   //删除无用书籍
	void brrowBook();   //借书，之前先判断书籍是否存在
	void returnBook();   //还书
	void getReader();  //查询某编号的书是谁借了
	int indexOfNum(string num); //根据编号得到书在数组中的下标
	vector<Book> getBooks() {
		return books;
	}
	void showInfo();
	int getTotalBooks() { return currentNum + brrowNum; }
private:
	vector<Book> books;//所有书籍
	map<string, int> readers;  //存储读者及其所借的书籍数目 
	int currentNum;   //库存书籍数目(不包括借出的)
	int brrowNum;     //借出书籍数目
};
void Library::showInfo()
{
	cout << "  ***************************所有图书信息***************************\n\n";
	for (int i = 0; i < books.size(); i++)
	{
		cout << "第" << i + 1 << "本书籍的信息。" << endl;
		books[i].showInfo();
	}
	system("pause");
	system("cls");
}
int Library::indexOfNum(string num)
{
	int i;
	for (i = 0; i < books.size(); i++)
	{
		if (books[i].getNum() == num)
			return i;
	}
	return -1;
}
void Library::addBook()
{
	Book b;
	int temp;
	string name, num, auther;
	cout << "  *****************************增加界面*****************************\n\n";
	do {
		cout << "输入书籍名称，编号，作者：";
		cin >> name >> num >> auther;
		b.setInfo(name, num, auther);
		if (indexOfNum(num) == -1) {
			books.push_back(b);
			currentNum++;
			cout << "\n添加成功。" << endl;
			cout << "输入1继续增加,返回上一层输入2：";
			cin >> temp;
		}
		else {
			cout << "已存在该编号的书籍，添加失败。" << endl;
			cout << "输入1继续重新增加,返回上一层输入2：";
			cin >> temp;
		}
	} while (temp == 1);
	system("pause");
	system("cls");
}
void Library::addBook(string name, string num, string auther)
{
	Book b;
	b.setInfo(name, num, auther);
	books.push_back(b);
}
void Library::deleteBook()
{
	int index, temp;
	string num;
	cout << "  *****************************删除界面*****************************\n\n";
	do {
		cout << "输入要删除的书籍的编号：";
		cin >> num;
		index = indexOfNum(num);
		if (index != -1) {
			if (!books[index].getBorrow_flag()) {
				cout << "删除的书籍的信息：\n";
				books[index].showInfo();
				books.erase(books.begin() + index);
				currentNum--;
				cout << "删除成功。" << endl;
				cout << "输入1继续继续删除,返回上一层输入2：";
				cin >> temp;
			}
			else {
				cout << "删除失败！书籍已经被借出。" << endl;
				cout << "输入1继续继续删除,返回上一层输入2：";
				cin >> temp;
			}
		}
		else
		{
			cout << "删除失败。未找到编号为" << num << "的书籍。\n";
			cout << "输入1继续继续删除,返回上一层输入2：";
			cin >> temp;
		}
	} while (temp == 1);
	system("pause");
	system("cls");
}
void Library::brrowBook()
{
	string num;
	int index;
	cout << "  *****************************借阅界面*****************************\n\n";
	cout << "输入要借阅的书籍的编号：";
	cin >> num;
	index = indexOfNum(num);
	if (index != -1) {
		if (books[index].isBorrow()) {
			cout << "借阅失败，书籍以及被借出。\n";
			system("pause");
			system("cls");
		}
		else
		{
			cout << "要借的书籍的信息：\n";
			books[index].showInfo();
			string reader, data;
			int lcn;
			cout << "输入读者姓名，借书证号，借书日期：";
			cin >> reader >> lcn >> data;
			if (readers[reader] != 2) {
				books[index].setReader(reader, lcn, data);
				cout << "借书完成。\n";
				currentNum--;
				brrowNum++;
				readers[reader]++;
				system("pause");
				system("cls");
			}
			else
			{
				cout << "借书失败，该读者以借超过两本书籍。\n";
				system("pause");
				system("cls");
			}
		}
	}
	else
	{
		cout << "借书失败。未找到编号为" << num << "的书籍.\n";
		system("pause");
		system("cls");
	}

}
void Library::returnBook()
{
	string num;
	cout << "  *****************************还书界面*****************************\n\n";
	cout << "输入要还的书籍的编号：";
	cin >> num;
	int index;
	index = indexOfNum(num);
	if (index != -1)
	{
		cout << "要还的书籍的信息为：\n";
		books[index].showInfo();
		books[index].setBorrow_flag(false);
		readers[books[index].getReader()]--;
		cout << "还书成功。\n";
		system("pause");
		system("cls");
	}
	else
	{
		cout << "还书失败，请检查书籍编号是否输入错误！\n";
		system("pause");
		system("cls");
	}
}
void Library::getReader()
{
	string num;
	cout << "  *****************************查询界面*****************************\n\n";
	cout << "输入要查找的书籍编号：";
	cin >> num;
	int index;
	index = indexOfNum(num);
	if (index != -1)
	{
		if (books[index].getBorrow_flag())
			cout << "读者为：" << books[index].getReader() << endl;
		else {
			cout << "无读者。" << endl;
		}
		system("pause");
		system("cls");
	}
	else
	{
		cout << "查询失败，请检查书籍编号是否输入错误！\n";
		system("pause");
		system("cls");
	}
}
Library l;

void menu()
{
	int temp;
	
	while (1)
	{
		cout << "___________________________ 图书馆管理系统____________________________\n";
	    cout << "                  ┏--------------------------┓                      \n";
		cout << "                  ┃ [0]退出系统。            ┃                      \n";
		cout << "                  ┃ [1]增加图书。            ┃                      \n";
		cout << "                  ┃ [2]删除图书。            ┃                      \n";
		cout << "                  ┃ [3]借阅图书。            ┃                      \n";
		cout << "                  ┃ [4]归还图书。            ┃                      \n";
		cout << "                  ┃ [5]显示图书信息。        ┃                      \n";
		cout << "                  ┃ [6]查询图书。            ┃                      \n";
		cout << "                  ┗--------------------------┛                      \n";
		cout << "输入要进行的操作：";
		cin >> temp;
		switch (temp) {
		case 1:
			system("cls");
			l.addBook(); 
			break;
		case 2:system("cls");
			l.deleteBook(); 
			break;
		case 3:system("cls");
			l.brrowBook(); 
			break;
		case 4:system("cls");
			l.returnBook(); 
			break;
		case 5:system("cls");
			l.showInfo();
			break;
		case 6:system("cls");
			l.getReader();
			break;
		case 0:
			
			exit(1);
			break;
		default:
			cout << "输入错误！" << endl;
			system("pause");
			system("cls");
		}
	}
}
int main()
{
	menu();
	return 0;
}
