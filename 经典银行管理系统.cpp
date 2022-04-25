#include<iostream>
#include<fstream>
#include<cstring>
#include<string> 
#include<vector>
#include<algorithm>
#include<strstream>
#include<conio.h>
using namespace std;
class Function;
class User {
	public:
		void get(User& );
		friend class Function;
		ostream &print(ostream &os);
		//friend ostream & operator<<(ostream & o, const User & u);
		friend istream & operator>>(istream & i, User & u);
		void PassWord();
		bool Login(User &);
		void SaveFile(User &);
		vector<string> StrFunction;
		User() {}
		User(int A,string N,int F,string I,string Ad,int
		     T):Accout(A),Name(N),Fmoney(F),ID(I),Address(Ad),Telephone(T) {}
	private:
		int Accout;
		string Name;
		int Fmoney;
		string ID;
		string Address;
		int Telephone;
		char Pword1[9];
		char Pword2[9];
};
class Function {
	public:
		void Saving(User &);
		void Drawing(User &);
		void Balance(User &);
		void Record(User &);
	private:
		int SaveAndDrawMoney;
};
void Function::Saving(User &u) {
	system("cls");
	cout<<"\n\n\n\t\t*********************************************\n"<<endl;
	cout<<"\t\t请输入存款金额：";
	string str1("\n\t\t现存RMB 钞+ ");
	cin>>SaveAndDrawMoney;
	u.Fmoney+=SaveAndDrawMoney;
	strstream ss;
	string str2;
	ss<<u.Accout;
	ss>>str2;
	string frist="Record"+str2 +".txt";
	const char *RecordFile=frist.c_str();
	ofstream outfile(RecordFile,ios::out|ios::app);
	outfile<<str1<<SaveAndDrawMoney<<endl;
	outfile.close();
	outfile.clear();
	cout<<"\n\n\t\t操作成功，单击任何键返回主菜单！";
	getch();
}
void Function::Drawing(User &u) {
	system("cls");
	cout<<"\n\n\n\t\t*********************************************\n"<<endl;
	cout<<"\t\t请输入取款金额：";
	string str1("\n\t\t现取RMB 钞- ");
	string str2;
	int k=0;
	while(k<=3) {
		cin>>SaveAndDrawMoney;
		u.Fmoney -=SaveAndDrawMoney;
		if(u.Fmoney>=0) {
			system("cls");
			cout<<"\n\n\n\t\t正在出钞，请稍等！"<<endl;
			strstream ss;
			ss<<u.Accout;
			ss>>str2;
			string frist="Record"+str2 +".txt";
			const char *RecordFile=frist.c_str();
			ofstream outfile(RecordFile,ios::out|ios::app);
			outfile<<str1<<SaveAndDrawMoney<<endl;
			outfile.close();
			outfile.clear();
			break;
		} else {
			k++;
			if(k>=3) {
				system("cls");
				cerr<<"\n\n\n\t\t很抱歉，你重复输入错误多次"<<endl
				    <<"\n\t\t正在退卡中……"<<endl;
				exit(0);
			}
			system("cls");
			u.Fmoney +=SaveAndDrawMoney;
			cerr<<"\n\n\n\t\t对不起，你输入的金额超出有效金额。"<<endl
			    <<"\n\t\t 请重新输入: ";
		}
	}
	cout<<"\n\n\t\t操作成功，单击任何键返回主菜单！";
	getch();
}
void Function::Balance(User &u) {
	system("cls");
	cout<<"\n\n\n\t\t*********************************************\n"<<endl;
	cout<<"\t\t你当前的余额是：";
	cout<<"\t\t"<<u.Fmoney<<endl;
	cout<<"\n\t\t*********************************************\n"<<endl;
	cout<<"\n\t\t操作成功，单击任何键返回主菜单！";
	getch();
}
void Function::Record(User &u) {
	string str1,str2;
	system("cls");
	cout<<"\n\n\n\t\t*********************************************\n"<<endl;
	cout<<"\t\t摘要币种钞汇存/取款金额"<<endl;
	strstream ss;
	ss<<u.Accout;
	ss>>str2;
	string frist="Record"+str2 +".txt";
	const char *RecordFile=frist.c_str();
	ifstream infile(RecordFile,ios::in);
	if(!infile) {
		cout<<"\n\t\t没有任何历史记录！"<<endl;
		getch();
		return ;
	}
	while(!infile.eof()) {
		getline (infile,str1);
		cout<<"\n\t\t"<<str1<<endl;
	}
	cout<<"\n\t\t*********************************************\n"<<endl;
	cout<<"\n\t\t操作成功，单击任何键返回主菜单！";
	getch();
}
ostream &User::print(ostream &os) { //mark
	system("cls");
	os<<"\n\n\n\t\t*********************************************\n"<<endl;
	os<<"\n\t\t用户卡号："<<Accout<<endl;
	os<<"\n\t\t姓名： "<<Name <<endl;
	os<<"\n\t\t账户金额："<<Fmoney<<endl;
	os<<"\n\t\t身份证号："<<ID<<endl;
	os<<"\n\t\t地址： "<<Address <<endl;
	os<<"\n\t\t联系电话："<<Telephone <<endl;
	os<<"\n\t\t密码： "<<Pword1<<endl;
	os<<"\n\t\t*********************************************\n"<<endl;
	cout<<"\n\t\t操作成功，单击任何键返回主菜单！";
	getch();
	return os;
}
void User::SaveFile(User &u) {
	int filename=u.Accout;
	string frist;
	string last(".txt");
	strstream ss;
	ss<<filename;
	ss>>frist;
	frist+=last;
	const char *UserID=frist.c_str();
	ofstream outfile(UserID,ios::out |ios::trunc );
	//outfile<<(*this);
	outfile<<Accout<<' '<<Name<<' '<<Fmoney<<' '<<ID<<' '<<Address<<' '<<Telephone<<' '<<Pword1<<endl;
	outfile.close();
}
bool User::Login(User &u) {
	int acc;
	string pwd;
	cout<<"\n\t\t登陆用户："<<endl;
	cout<<"\t\t卡号：";
	cin>>acc;
	cout<<"\t\t密码：";
	cin>>pwd;
	int filename=acc;
	string frist;
	string last(".txt");
	strstream ss;
	ss<<filename;
	ss>>frist;
	frist+=last;
	const char *UserID=frist.c_str();
	ifstream infile(UserID,ios::in );
	while (infile >> (*this)) {
		if (u.Accout == acc ) {
			string str;
			str=Pword1;
			if(str== pwd) {
				return true;
			}
		}
	}
	return false;
}
/*ostream & operator<<(ostream & o, const User & u) {
	o<<u.Accout <<' '<<u.Name<<' '<<u.Fmoney<<' ' <<u.ID<<' '
		<<u.Address <<' '<<u.Telephone<<' ' <<u.Pword1 <<endl;
	return o;
}*/
istream & operator>>(istream & i, User & u) {

	i>>u.Accout >>u.Name >>u.Fmoney >>u.ID >>u.Address >>u.Telephone >>u.Pword1 ;
	return i;
}
void User::PassWord() {
	int num=0;
	while(num<3) {
		cout<<"\n\t\t请输入位储蓄密码：";
		for(int i=0; i<8; i++) {
			Pword1[i]=getch();
			cout<<"*";
		}
		Pword1[8]='\0';
		cout<<endl;
		cout<<"\n\t\t请再一次确认密码：";
		for(int i=0; i<8; i++) {
			Pword2[i]=getch();
			cout<<"*";
		}
		cout<<endl;
		Pword2[8]='\0';
		if(strcmp(Pword1,Pword2)==0) {
			cout<<"\n\n\t\t密码确认成功，单击任何键进入主菜单";
			getch();
			return ;
		} else {
			num++;
			cout<<"\n\t\t你输入的密码错误，请重新输入！\n"<<endl;
		}
		if(num==3) {
			system("cls");
			cerr<<"\n\n\n\t\t对不起，你三次输入不正确\n"<<endl
			    <<"\t\t感谢你的使用，再见！ "<<endl;
			exit(0);
		}
	}
}
void User::get(User& u) {
	system("cls");
	cout<<"\n\n\n\t\t请输入用户信息：\n"<<endl;
	cout<<"\t\t*********************************************\n"<<endl;
	cout<<"\n\t\t卡号：";
	cin>>Accout;
	cout<<"\n\t\t姓名：";
	cin>>Name;
	cout<<"\n\t\t账户金额：";
	cin>>Fmoney;
	cout<<"\n\t\t身份证号：";
	cin>>ID;
	cout<<"\n\t\t地址：";
	cin>>Address;
	cout<<"\n\t\t联系电话：";
	cin>>Telephone;
	u.PassWord();
	cout<<"\n\t\t*********************************************\n"<<endl;
}
void Sign() {
	system("cls");
	cout<<"\n\n\n\n\n\n\t\t\t谢谢您使用银行管理系统\t \n\n"<<endl;
	cout<<"\t\t*********************************************\n"<<endl;
	cout<<"\t\t 姓名: 林鉴洲 \n\n"
	    <<"\t\t 班级: 19科技1班\n\n"
	    <<"\t\t 学号: 201924111149\n\n"<<endl;
	cout<<"\n\t\t 已经成功退出"<<endl
	    <<"\n\t\t 欢迎你的光临！" <<endl;
}
char custom(User &u) {
	char x;
	int k=0;
	system("cls");
	cout<<"\n\n\n\t\t※※※※※※※※※※※※※※※※※※※※※※※※※※※\n"
	    <<"\t\t※                                                  ※\n"
	    <<"\t\t※              欢迎使用储蓄管理系统                ※\n"
	    <<"\t\t※                                                  ※\n"
	    <<"\t\t※              请用户在使用前选择开户：            ※\n"
	    <<"\t\t※                                                  ※\n"
	    <<"\t\t※              请选择：                            ※\n"
	    <<"\t\t※              1：注册开户                         ※\n"
	    <<"\t\t※              2：用户登录                         ※\n"
	    <<"\t\t※              其他：退出                          ※\n"
	    <<"\t\t※                                                  ※\n"
	    <<"\t\t※                                                  ※\n"
	    <<"\t\t※※※※※※※※※※※※※※※※※※※※※※※※※※※\n"<<endl;
	cout<<"\n\t\t请选择操作方式：";
	cin>>x;
	if(x=='1') {
		u.get(u);
	} else if(x=='2') {
		while(k<3) {
			if(u.Login(u)) { //判断登陆是否成功
				return 0;
			} else {
				system("cls");
				cerr<<"\n\n\n\t\t\t输入有误!\n"<<endl
				    <<"\t\t\t请重新输入："<<endl;
				k++;
			}
			while(k>=3) {
				system("cls");
				cerr<<"\n\n\n\t\t对不起，你三次输入不正确\n"<<endl
				    <<"\n\t\t感谢你的使用，再见！\n"<<endl;
				exit(0);
			}
		}
	} else {
		Sign();
		exit(0);
	}
	return 0;
}
char menu() {
	int k=0;
	char a[3],c,i;
	system("cls");
	cout<<"\n\n\n\t\t 主菜单 \n\n" ;
	cout<<"\t\t*********************************************\n"
	    <<"\t\t*                                           *\n"
	    <<"\t\t*      操作方式:                            *\n"
	    <<"\t\t*                                           *\n"
	    <<"\t\t*          1.存款 2.取款                    *\n"
	    <<"\t\t*                                           *\n"
	    <<"\t\t*          3.查询余额 4.查询历史记录        *\n"
	    <<"\t\t*                                           *\n"
	    <<"\t\t*          5.用户信息 6.保存并退出          *\n"
	    <<"\t\t*                                           *\n"
	    <<"\t\t*********************************************\n"<<endl;
	while(k<3) {
		cout<<"\n\t\t请选择操作方式: ";
		cin>>a;
		if(strlen(a)==1) {
			for(i='1'; i<='6'; i++) {
				c=i;
				if(c==a[0]) return c;
			}
		} else {
			system("cls");
			cerr<<"\n\n\n\t\t\t输入有误!\n"<<endl
			    <<"\t\t\t请重新输入："<<endl;
			k++;
		}
		while(k>=3) {
			system("cls");
			cerr<<"\n\n\n\t\t对不起，你三次输入不正确\n"<<endl
			    <<"\n\t\t感谢你的使用，再见！\n"<<endl;
			exit(0);
		}
	}
	return c;
}
char Choose( User &u,Function &F) {
	char c=menu();
	while(c!='6') {
		switch(c) {
			case '1':
				F.Saving(u);
				c=menu();
				break;
			case '2':
				F.Drawing(u);
				c=menu();
				break;
			case '3':
				F.Balance(u);
				c=menu();
				break;
			case '4':
				F.Record(u);
				c=menu();
				break;
			case '5':
				u.print(cout);
				c=menu();
				break;
		}

	}
	u.SaveFile(u);
	Sign();
	return 0;
}
int main() {
	User u;
	Function F;
	vector<Function> FunctionUser;
	custom(u);
	Choose(u,F);
}
