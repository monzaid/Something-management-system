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
	cout<<"\t\t���������";
	string str1("\n\t\t�ִ�RMB ��+ ");
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
	cout<<"\n\n\t\t�����ɹ��������κμ��������˵���";
	getch();
}
void Function::Drawing(User &u) {
	system("cls");
	cout<<"\n\n\n\t\t*********************************************\n"<<endl;
	cout<<"\t\t������ȡ���";
	string str1("\n\t\t��ȡRMB ��- ");
	string str2;
	int k=0;
	while(k<=3) {
		cin>>SaveAndDrawMoney;
		u.Fmoney -=SaveAndDrawMoney;
		if(u.Fmoney>=0) {
			system("cls");
			cout<<"\n\n\n\t\t���ڳ��������Եȣ�"<<endl;
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
				cerr<<"\n\n\n\t\t�ܱ�Ǹ�����ظ����������"<<endl
				    <<"\n\t\t�����˿��С���"<<endl;
				exit(0);
			}
			system("cls");
			u.Fmoney +=SaveAndDrawMoney;
			cerr<<"\n\n\n\t\t�Բ���������Ľ�����Ч��"<<endl
			    <<"\n\t\t ����������: ";
		}
	}
	cout<<"\n\n\t\t�����ɹ��������κμ��������˵���";
	getch();
}
void Function::Balance(User &u) {
	system("cls");
	cout<<"\n\n\n\t\t*********************************************\n"<<endl;
	cout<<"\t\t�㵱ǰ������ǣ�";
	cout<<"\t\t"<<u.Fmoney<<endl;
	cout<<"\n\t\t*********************************************\n"<<endl;
	cout<<"\n\t\t�����ɹ��������κμ��������˵���";
	getch();
}
void Function::Record(User &u) {
	string str1,str2;
	system("cls");
	cout<<"\n\n\n\t\t*********************************************\n"<<endl;
	cout<<"\t\tժҪ���ֳ����/ȡ����"<<endl;
	strstream ss;
	ss<<u.Accout;
	ss>>str2;
	string frist="Record"+str2 +".txt";
	const char *RecordFile=frist.c_str();
	ifstream infile(RecordFile,ios::in);
	if(!infile) {
		cout<<"\n\t\tû���κ���ʷ��¼��"<<endl;
		getch();
		return ;
	}
	while(!infile.eof()) {
		getline (infile,str1);
		cout<<"\n\t\t"<<str1<<endl;
	}
	cout<<"\n\t\t*********************************************\n"<<endl;
	cout<<"\n\t\t�����ɹ��������κμ��������˵���";
	getch();
}
ostream &User::print(ostream &os) { //mark
	system("cls");
	os<<"\n\n\n\t\t*********************************************\n"<<endl;
	os<<"\n\t\t�û����ţ�"<<Accout<<endl;
	os<<"\n\t\t������ "<<Name <<endl;
	os<<"\n\t\t�˻���"<<Fmoney<<endl;
	os<<"\n\t\t���֤�ţ�"<<ID<<endl;
	os<<"\n\t\t��ַ�� "<<Address <<endl;
	os<<"\n\t\t��ϵ�绰��"<<Telephone <<endl;
	os<<"\n\t\t���룺 "<<Pword1<<endl;
	os<<"\n\t\t*********************************************\n"<<endl;
	cout<<"\n\t\t�����ɹ��������κμ��������˵���";
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
	cout<<"\n\t\t��½�û���"<<endl;
	cout<<"\t\t���ţ�";
	cin>>acc;
	cout<<"\t\t���룺";
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
		cout<<"\n\t\t������λ�������룺";
		for(int i=0; i<8; i++) {
			Pword1[i]=getch();
			cout<<"*";
		}
		Pword1[8]='\0';
		cout<<endl;
		cout<<"\n\t\t����һ��ȷ�����룺";
		for(int i=0; i<8; i++) {
			Pword2[i]=getch();
			cout<<"*";
		}
		cout<<endl;
		Pword2[8]='\0';
		if(strcmp(Pword1,Pword2)==0) {
			cout<<"\n\n\t\t����ȷ�ϳɹ��������κμ��������˵�";
			getch();
			return ;
		} else {
			num++;
			cout<<"\n\t\t�����������������������룡\n"<<endl;
		}
		if(num==3) {
			system("cls");
			cerr<<"\n\n\n\t\t�Բ������������벻��ȷ\n"<<endl
			    <<"\t\t��л���ʹ�ã��ټ��� "<<endl;
			exit(0);
		}
	}
}
void User::get(User& u) {
	system("cls");
	cout<<"\n\n\n\t\t�������û���Ϣ��\n"<<endl;
	cout<<"\t\t*********************************************\n"<<endl;
	cout<<"\n\t\t���ţ�";
	cin>>Accout;
	cout<<"\n\t\t������";
	cin>>Name;
	cout<<"\n\t\t�˻���";
	cin>>Fmoney;
	cout<<"\n\t\t���֤�ţ�";
	cin>>ID;
	cout<<"\n\t\t��ַ��";
	cin>>Address;
	cout<<"\n\t\t��ϵ�绰��";
	cin>>Telephone;
	u.PassWord();
	cout<<"\n\t\t*********************************************\n"<<endl;
}
void Sign() {
	system("cls");
	cout<<"\n\n\n\n\n\n\t\t\tлл��ʹ�����й���ϵͳ\t \n\n"<<endl;
	cout<<"\t\t*********************************************\n"<<endl;
	cout<<"\t\t ����: �ּ��� \n\n"
	    <<"\t\t �༶: 19�Ƽ�1��\n\n"
	    <<"\t\t ѧ��: 201924111149\n\n"<<endl;
	cout<<"\n\t\t �Ѿ��ɹ��˳�"<<endl
	    <<"\n\t\t ��ӭ��Ĺ��٣�" <<endl;
}
char custom(User &u) {
	char x;
	int k=0;
	system("cls");
	cout<<"\n\n\n\t\t������������������������������������������������������\n"
	    <<"\t\t��                                                  ��\n"
	    <<"\t\t��              ��ӭʹ�ô������ϵͳ                ��\n"
	    <<"\t\t��                                                  ��\n"
	    <<"\t\t��              ���û���ʹ��ǰѡ�񿪻���            ��\n"
	    <<"\t\t��                                                  ��\n"
	    <<"\t\t��              ��ѡ��                            ��\n"
	    <<"\t\t��              1��ע�Ὺ��                         ��\n"
	    <<"\t\t��              2���û���¼                         ��\n"
	    <<"\t\t��              �������˳�                          ��\n"
	    <<"\t\t��                                                  ��\n"
	    <<"\t\t��                                                  ��\n"
	    <<"\t\t������������������������������������������������������\n"<<endl;
	cout<<"\n\t\t��ѡ�������ʽ��";
	cin>>x;
	if(x=='1') {
		u.get(u);
	} else if(x=='2') {
		while(k<3) {
			if(u.Login(u)) { //�жϵ�½�Ƿ�ɹ�
				return 0;
			} else {
				system("cls");
				cerr<<"\n\n\n\t\t\t��������!\n"<<endl
				    <<"\t\t\t���������룺"<<endl;
				k++;
			}
			while(k>=3) {
				system("cls");
				cerr<<"\n\n\n\t\t�Բ������������벻��ȷ\n"<<endl
				    <<"\n\t\t��л���ʹ�ã��ټ���\n"<<endl;
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
	cout<<"\n\n\n\t\t ���˵� \n\n" ;
	cout<<"\t\t*********************************************\n"
	    <<"\t\t*                                           *\n"
	    <<"\t\t*      ������ʽ:                            *\n"
	    <<"\t\t*                                           *\n"
	    <<"\t\t*          1.��� 2.ȡ��                    *\n"
	    <<"\t\t*                                           *\n"
	    <<"\t\t*          3.��ѯ��� 4.��ѯ��ʷ��¼        *\n"
	    <<"\t\t*                                           *\n"
	    <<"\t\t*          5.�û���Ϣ 6.���沢�˳�          *\n"
	    <<"\t\t*                                           *\n"
	    <<"\t\t*********************************************\n"<<endl;
	while(k<3) {
		cout<<"\n\t\t��ѡ�������ʽ: ";
		cin>>a;
		if(strlen(a)==1) {
			for(i='1'; i<='6'; i++) {
				c=i;
				if(c==a[0]) return c;
			}
		} else {
			system("cls");
			cerr<<"\n\n\n\t\t\t��������!\n"<<endl
			    <<"\t\t\t���������룺"<<endl;
			k++;
		}
		while(k>=3) {
			system("cls");
			cerr<<"\n\n\n\t\t�Բ������������벻��ȷ\n"<<endl
			    <<"\n\t\t��л���ʹ�ã��ټ���\n"<<endl;
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
