#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
struct data{			//结构体定义； 
	char num[6];
	char name[20];
	double money;
	char word[7];
	int hang;	
};
int size; 		//全局变量存结构体字节数； 
FILE *fp;      //全局变量文件指针； 
int menu(){		//主菜单显示； 
		printf("………………………………………………………\n");
		printf(".         请输入选项编号(0~7):           .\n");
		printf("………………………………………………………\n");
		printf(".          1--建立饭卡文件               .\n");
		printf(".          2--买饭                       .\n");
		printf(".          3--续钱                       .\n");
		printf(".          4--添加新饭卡                 .\n");
		printf(".          5--注销旧饭卡                 .\n");
		printf(".          6--设置与解除挂失             .\n");
		printf(".          7--修改密码                   .\n");
		printf(".          0--退出系统                   .\n");
		printf("………………………………………………………\n");
}
void openfile(char *openmode){				//打开文件函数； 
	if((fp=fopen("card.dat",openmode))==NULL){
		printf("打开文件夹失败！\n");
		exit(0); 
	}
} 
void close(){
	if(fclose(fp)) {
			printf("文件夹关闭失败！\n");
			exit(0); 
	}
}
int find(char *str){			//查找饭卡号是否存在； 
	int i=0;
	struct data p;
	fseek(fp,0L,0);
	while(!feof(fp)){
		fread(&p,size,1,fp);
		i++;
		if(strcmp(p.num,str)==0)
			return i;
	}
	return 0;
}
void change(struct data s){			//删除文件内指定饭卡信息； 
	FILE *fp1;
	struct data str;
	fseek(fp,0L,0);
	if((fp1=fopen("linshi.dat","wb+"))==NULL){
		printf("打开文件夹失败！\n");
		exit(0); 
	}
	while(fread(&str,size,1,fp))
		if(strcmp(s.num,str.num)!=0)
			fwrite(&str,size,1,fp1);
	close();	
	fclose(fp1);
	openfile("wb+");
	if((fp1=fopen("linshi.dat","rb"))==NULL){
		printf("打开文件夹失败！\n");
		exit(0); 
	}
	while(fread(&str,size,1,fp1))
		fwrite(&str,size,1,fp);
	close();
	fclose(fp1);
}
void encrypt(char *word){	//加密函数； 
	int i;
	for(i=0;i<strlen(word);i++)
		word[i]=word[i]^15;
	
} 
int prove(char *num,char *sec){		//验证密码是否正确； 
	int i;
	struct data s;
	i=find(num);
	fseek(fp,((i-1)*size),0);
	fread(&s,size,1,fp);
	encrypt(sec);
	if(strcmp(s.word,sec)==0)
		return 1;
	else 
		return 0;
}
void set(){				//添加若干张饭卡信息；
	int mark;
	char again;
	struct data s;
	openfile("ab+");
	do{
		printf("请您按要求填写以下信息\n");
		printf("饭卡号(00001~99999):\n");		scanf("%s",s.num);
		mark=find(s.num); 
		if(mark){
			printf("此饭卡号已存在，请您选择：重新添加(A)或者返回主菜单(B)！\n"); 
			getchar();
			scanf("%c",&again);
		}
		else{
			printf("姓名:\n");						scanf("%s",s.name);
			printf("金额(￥):\n");					scanf("%lf",&s.money);
			printf("密码(不超过6位):\n");					scanf("%s",s.word);
			s.hang =1;
			encrypt(s.word);
			fwrite(&s,size,1,fp);
			close();
			openfile("ab+");
			printf("添加饭卡成功！\n请您选择是否继续添加饭卡？(Y/N)\n");
			getchar();
			scanf("%c",&again); 
		} 
	}while(again=='Y'||again=='y'||again=='a'||again=='A');
	close();
}
void buy(){			//买饭； 
	int mark,show,i=0;
	struct data p;
	char num[6],word[7],input;
	double cost,sum,mon;
	openfile("ab+");
high:	
    printf("请您输入饭卡号：\n");
	scanf("%s",num);
	show=0;
	mark=find(num);	
	if(mark==0){//找不到饭卡号情况； 
		printf("查无此饭卡号，请您选择：重新输入(A)或者返回主菜单(B)！\n");
		getchar();
		scanf("%c",&input);
		if(input=='A'||input=='a')
			goto high;
		else
			goto low;
	}
	else{//找到饭卡号情况； 
		fseek(fp,(mark-1)*size,0);
		fread(&p,size,1,fp);
		if(p.hang==0){//已挂失情况； 
			printf("此卡已冻结，请您解除冻结后再使用！\n");
			goto low; 
		}
		else{//未挂失情况； 
			if(p.money<5){//余额不足5元情况； 
				printf("余额不足，请您续钱后再使用！\n"); 
				goto low;
			}
			else{//余额达到5元情况； 
				printf("请您输入饭费(￥)：\n");
				scanf("%lf",&cost); 
				if(cost>p.money){//饭钱超过余额情况； 
					printf("余额不足，请您续钱后再使用！\n"); 
					goto low;
				}
				else{//饭钱不超过余额情况； 
					if(cost>30){//单笔消费超过30元情况，需要输入密码； 
						printf("单笔消费超过￥30，请您输入密码验证身份(Three times!)：\n");
						for(i=0;i<3;i++){
							scanf("%s",word);
							if(prove(num,word)!=1){//密码错误情况； 
								if(i<2)
									printf("密码错误，请您重新输入：\n"); 
								else {//密码错误达到3次情况； 
									printf("密码错误次数3次，请您修改密码后再使用！\n");
									goto low;
								}
							}
							else{//验证密码成功情况；
								printf("身份验证成功！\n");
								goto here;
							}
						}
					}
					else//单笔不超过30元，无需输入密码；
						goto here;
			here:	//消费成功，输出消费前后余额； 
						mon=p.money;
						sum=p.money-cost;
						p.money=sum;
						change(p);
					    openfile("ab+");
						fwrite(&p,size,1,fp);
						close();
						openfile("ab+");
						printf("您已成功消费，祝您用餐愉快！\n消费前余额(￥)：%.2f\n消费后余额(￥)：%.2f\n",mon,sum);
						printf("请您选择：继续消费(A)或者返回主菜单(B)！\n");
						getchar();
						scanf("%c",&input);
						if(input=='A'||input=='a')
							goto high; 
						else
							goto low;
				}
			}
		}
	}	
	low:;
	close();
}
void keep(){	//续钱； 
	int mark,i=0;
	struct data p;
	char num[6],fre,input;
	double into,sum,mon;
	openfile("ab+");
	high:
		printf("请您输入续钱饭卡号：\n");
		scanf("%s",num);
		mark=find(num);
		if(mark==0){//查不到饭卡号； 
			printf("查无此饭卡号，请您选择：重新输入(A)或者返回主菜单(B)！\n");
			getchar();
			scanf("%c",&input);
			if(input=='A'||input=='a')
				goto high;
			else
				goto low;
		}
		else{//查得到饭卡号； 
			fseek(fp,(mark-1)*size,0);
			fread(&p,size,1,fp);
			if(p.hang==0){//饭卡号已挂失； 
				printf("此卡已冻结，请您解除冻结后再进行续钱！\n");
				printf("请您选择是否解除冻结？(Y/N)\n");		//是否解除挂失； 
				getchar();
				scanf("%c",&fre);
				if(fre=='Y'||fre=='y'){//解除挂失； 
					p.hang=1;
					change(p);
					openfile("ab+");
					fwrite(&p,size,1,fp);
					close();
					openfile("ab+");
					printf("已成功解除冻结，请您重新进行续钱！\n");
					goto high; 
				}
				else{
					printf("解除冻结已取消，请您选择：更换饭卡进行续钱(A)或者返回主菜单(B)\n");
					getchar();
					scanf("%c",&input);
					if(input=='A'||input=='a')
						goto high;
					else
						goto low;
				} 
			}
			else{//饭卡未挂失，直接充值； 
				printf("请您输入充值金额(￥)：\n");
				scanf("%lf",&into);
				mon=p.money;
				sum=into+p.money;
				p.money=sum;
				change(p);
				openfile("ab+");
				fwrite(&p,size,1,fp);
				close();
				openfile("ab+");
				printf("续钱成功，祝您生活愉快！\n充值前余额(￥)：%.2f\n充值后后余额(￥)：%.2f\n",mon,sum);
				printf("请您选择：继续续钱(A)或者返回主菜单(B)！\n");
				getchar(); 
				scanf("%c",&input);
				if(input=='A'||input=='a')
					goto high;
				else
					goto low;
			}
		}
	low:
	close();
}
void del(){		//注销 
	struct data p;
	char num[6],input;
	int mark;
	openfile("ab+");
	do{
		printf("请您输入需要进行注销的饭卡号：\n");
		scanf("%s",num); 
		mark=find(num);
		if(mark==0){
			printf("查无此饭卡号，请您选择：重新输入(A)或者返回主菜单(B)！\n");
			getchar();
			scanf("%c",&input);
		}
		else{
			fseek(fp,(mark-1)*size,0);
			fread(&p,size,1,fp);
			printf("该饭卡持卡人：%s , 余额：￥%.2f。\n请您确认是否进行注销！(Y/N)\n",p.name,p.money);
			getchar();
			scanf("%c",&input);
			if(input=='Y'||input=='y'){
				change(p);
				openfile("ab+"); 
				printf("注销成功，请您选择：继续注销(A)或者返回主菜单(B)！\n"); 
				getchar();
				scanf("%c",&input);
			} 
			else{
				printf("注销已取消，请选择：重新注销(A)或者返回主菜单(B)！\n");
				getchar();
				scanf("%c",&input);
			} 
		}
	}while(input=='A'||input=='a');
	close();
} 
void lost(){		//挂失 
	char num[6],input,fre;
	int mark;
	struct data p;
	openfile("ab+");
	do{
		printf("请您输入需要进行挂失/解除挂失的饭卡号：\n");
		scanf("%s",num); 
		mark=find(num);
		if(mark==0){
			printf("查无此饭卡号，请您选择：重新输入(A)或者返回主菜单(B)！\n");
			getchar();
			scanf("%c",&input);
		}
		else{
			fseek(fp,(mark-1)*size,0);
			fread(&p,size,1,fp);
			printf("该饭卡持有者：%s\n",p.name);
			if(p.hang==0){
				printf("该饭卡当前为挂失状态，请您选择是否解除挂失！(Y/N)\n");
				getchar();
				scanf("%c",&fre); 
				if(fre=='Y'||fre=='y'){
					p.hang=1;
					change(p);
			    	openfile("ab+");
					fwrite(&p,size,1,fp);
	            	close();
					openfile("ab+");
					printf("已成功解除挂失，请您选择：继续设置(A)或者返回主菜单(B)！\n");
					getchar();
					scanf("%c",&input);
				}
				else{
					printf("已取消解除挂失，请您选择：继续设置(A)或者返回主菜单(B)！\n"); 
					getchar();
					scanf("%c",&input);
				}
			}
			else{
				printf("该饭卡当前为正常状态，请您选择是否进行挂失！(Y/N)\n");
				getchar();
				scanf("%c",&fre);
				if(fre=='Y'||fre=='y'){
					p.hang=0;
					change(p);
					openfile("ab+");
					fwrite(&p,size,1,fp);
					close();
					openfile("ab+");
					printf("已成功挂失，请您选择：继续设置(A)或者返回主菜单(B)！\n");
					getchar();
					scanf("%c",&input);
				}
				else{
					printf("已取消挂失，请您选择：继续设置(A)或者返回主菜单(B)！\n"); 
					getchar();
					scanf("%c",&input);
				}
			}
		}
	}while(input=='A'||input=='a'); 
	close();
} 
void password(){		//改密 
	char num[6],name[20],word1[7],word2[7],input,turn;
	int mark,i=0;
	struct data p;
	openfile("ab+");
high:	printf("请您输入需要进行修改密码的饭卡号：\n");
	scanf("%s",num); 
	mark=find(num );
	if(mark==0){
		printf("查无此饭卡号，请您选择：重新输入(A)或者返回主菜单(B)！\n");
		getchar();
		scanf("%c",&input);
		if(input=='A'||input=='a') 
			goto high;
		else
			goto low;
	}
	else{
		fseek(fp,(mark-1)*size,0);
		fread(&p,size,1,fp);
		printf("请您输入持卡人姓名(Three times!)：\n");
		for(i=0;i<3;i++){
			scanf("%s",name);
			if(strcmp(name,p.name)!=0){
				if(i<2)
					printf("身份验证失败，请您重新进行输入：\n"); 
				else{
					printf("身份验证失败3次，请您确认后再进行操作！\n"); 
					goto low;
				}
			}
			else{
				printf("身份验证成功！\n请您确认是否修改密码！(Y/N)\n");
				getchar();
				scanf("%c",&turn);
				if(turn!='Y'&&turn!='y'){
					printf("修改密码已取消，请您选择：继续重新进行修改密码(A)或者返回主菜单(B)！\n");
					getchar();
					scanf("%c",&input);
					if(input=='A'||input=='a')
						goto high;
					else
						goto low;
				}
				else{
					for(i=0;i<3;i++){
						printf("请您输入新的密码（不超过六位）：\n");
						scanf("%s",word1);
						printf("请您再次输入新的密码（不超过六位）：\n");
						scanf("%s",word2);
						if(strcmp(word1,word2)!=0){
							if(i<2)
								printf("密码输入不一致，请您重新输入：\n"); 
							else{
								printf("密码输入多次不一致，请您确认后再进行操作！\n"); 
								goto low;
							}
						}
						else{
							encrypt(word1);
							strcpy(p.word,word1);
							change(p);
							openfile("ab+");
							fwrite(&p,size,1,fp);
							close();
							openfile("ab+");
							printf("修改密码已成功，请您牢记此密码！\n"); 
							printf("请您选择：继续进行修改密码(A)或者返回主菜单(B)！\n");
							getchar();
							scanf("%c",&input);
							if(input=='A'||input=='a')
								goto high;
							else
								goto low;
						}
					}
				}
			}
		}
	}
	low:;
	close();
} 
int main(void){
	int choice;
	size=sizeof(data);
	do{ 
		menu();
		scanf("%d",&choice);
		switch(choice){						//选择服务； 
			case 0: printf("感谢使用本软件！已正常退出，按任意键结束！\n");
					break;
			case 1: openfile("wb+");//建立新文档； 
					close();
					set();
					break;
			case 2:	buy();
					break;
			case 3:	keep();
					break;
			case 4: set();
				    break;
			case 5: del();
					break;
			case 6: lost();
					break;
			case 7:	password();
					break;
			default:printf("输入有误！\n"); 
		}
	}while(choice!=0);
	return 0;
}
