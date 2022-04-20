#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
struct data{			//�ṹ�嶨�壻 
	char num[6];
	char name[20];
	double money;
	char word[7];
	int hang;	
};
int size; 		//ȫ�ֱ�����ṹ���ֽ����� 
FILE *fp;      //ȫ�ֱ����ļ�ָ�룻 
int menu(){		//���˵���ʾ�� 
		printf("������������������������������������������\n");
		printf(".         ������ѡ����(0~7):           .\n");
		printf("������������������������������������������\n");
		printf(".          1--���������ļ�               .\n");
		printf(".          2--��                       .\n");
		printf(".          3--��Ǯ                       .\n");
		printf(".          4--����·���                 .\n");
		printf(".          5--ע���ɷ���                 .\n");
		printf(".          6--����������ʧ             .\n");
		printf(".          7--�޸�����                   .\n");
		printf(".          0--�˳�ϵͳ                   .\n");
		printf("������������������������������������������\n");
}
void openfile(char *openmode){				//���ļ������� 
	if((fp=fopen("card.dat",openmode))==NULL){
		printf("���ļ���ʧ�ܣ�\n");
		exit(0); 
	}
} 
void close(){
	if(fclose(fp)) {
			printf("�ļ��йر�ʧ�ܣ�\n");
			exit(0); 
	}
}
int find(char *str){			//���ҷ������Ƿ���ڣ� 
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
void change(struct data s){			//ɾ���ļ���ָ��������Ϣ�� 
	FILE *fp1;
	struct data str;
	fseek(fp,0L,0);
	if((fp1=fopen("linshi.dat","wb+"))==NULL){
		printf("���ļ���ʧ�ܣ�\n");
		exit(0); 
	}
	while(fread(&str,size,1,fp))
		if(strcmp(s.num,str.num)!=0)
			fwrite(&str,size,1,fp1);
	close();	
	fclose(fp1);
	openfile("wb+");
	if((fp1=fopen("linshi.dat","rb"))==NULL){
		printf("���ļ���ʧ�ܣ�\n");
		exit(0); 
	}
	while(fread(&str,size,1,fp1))
		fwrite(&str,size,1,fp);
	close();
	fclose(fp1);
}
void encrypt(char *word){	//���ܺ����� 
	int i;
	for(i=0;i<strlen(word);i++)
		word[i]=word[i]^15;
	
} 
int prove(char *num,char *sec){		//��֤�����Ƿ���ȷ�� 
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
void set(){				//��������ŷ�����Ϣ��
	int mark;
	char again;
	struct data s;
	openfile("ab+");
	do{
		printf("������Ҫ����д������Ϣ\n");
		printf("������(00001~99999):\n");		scanf("%s",s.num);
		mark=find(s.num); 
		if(mark){
			printf("�˷������Ѵ��ڣ�����ѡ���������(A)���߷������˵�(B)��\n"); 
			getchar();
			scanf("%c",&again);
		}
		else{
			printf("����:\n");						scanf("%s",s.name);
			printf("���(��):\n");					scanf("%lf",&s.money);
			printf("����(������6λ):\n");					scanf("%s",s.word);
			s.hang =1;
			encrypt(s.word);
			fwrite(&s,size,1,fp);
			close();
			openfile("ab+");
			printf("��ӷ����ɹ���\n����ѡ���Ƿ������ӷ�����(Y/N)\n");
			getchar();
			scanf("%c",&again); 
		} 
	}while(again=='Y'||again=='y'||again=='a'||again=='A');
	close();
}
void buy(){			//�򷹣� 
	int mark,show,i=0;
	struct data p;
	char num[6],word[7],input;
	double cost,sum,mon;
	openfile("ab+");
high:	
    printf("�������뷹���ţ�\n");
	scanf("%s",num);
	show=0;
	mark=find(num);	
	if(mark==0){//�Ҳ�������������� 
		printf("���޴˷����ţ�����ѡ����������(A)���߷������˵�(B)��\n");
		getchar();
		scanf("%c",&input);
		if(input=='A'||input=='a')
			goto high;
		else
			goto low;
	}
	else{//�ҵ������������ 
		fseek(fp,(mark-1)*size,0);
		fread(&p,size,1,fp);
		if(p.hang==0){//�ѹ�ʧ����� 
			printf("�˿��Ѷ��ᣬ��������������ʹ�ã�\n");
			goto low; 
		}
		else{//δ��ʧ����� 
			if(p.money<5){//����5Ԫ����� 
				printf("���㣬������Ǯ����ʹ�ã�\n"); 
				goto low;
			}
			else{//���ﵽ5Ԫ����� 
				printf("�������뷹��(��)��\n");
				scanf("%lf",&cost); 
				if(cost>p.money){//��Ǯ������������ 
					printf("���㣬������Ǯ����ʹ�ã�\n"); 
					goto low;
				}
				else{//��Ǯ�������������� 
					if(cost>30){//�������ѳ���30Ԫ�������Ҫ�������룻 
						printf("�������ѳ�����30����������������֤���(Three times!)��\n");
						for(i=0;i<3;i++){
							scanf("%s",word);
							if(prove(num,word)!=1){//������������ 
								if(i<2)
									printf("������������������룺\n"); 
								else {//�������ﵽ3������� 
									printf("����������3�Σ������޸��������ʹ�ã�\n");
									goto low;
								}
							}
							else{//��֤����ɹ������
								printf("�����֤�ɹ���\n");
								goto here;
							}
						}
					}
					else//���ʲ�����30Ԫ�������������룻
						goto here;
			here:	//���ѳɹ����������ǰ���� 
						mon=p.money;
						sum=p.money-cost;
						p.money=sum;
						change(p);
					    openfile("ab+");
						fwrite(&p,size,1,fp);
						close();
						openfile("ab+");
						printf("���ѳɹ����ѣ�ף���ò���죡\n����ǰ���(��)��%.2f\n���Ѻ����(��)��%.2f\n",mon,sum);
						printf("����ѡ�񣺼�������(A)���߷������˵�(B)��\n");
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
void keep(){	//��Ǯ�� 
	int mark,i=0;
	struct data p;
	char num[6],fre,input;
	double into,sum,mon;
	openfile("ab+");
	high:
		printf("����������Ǯ�����ţ�\n");
		scanf("%s",num);
		mark=find(num);
		if(mark==0){//�鲻�������ţ� 
			printf("���޴˷����ţ�����ѡ����������(A)���߷������˵�(B)��\n");
			getchar();
			scanf("%c",&input);
			if(input=='A'||input=='a')
				goto high;
			else
				goto low;
		}
		else{//��õ������ţ� 
			fseek(fp,(mark-1)*size,0);
			fread(&p,size,1,fp);
			if(p.hang==0){//�������ѹ�ʧ�� 
				printf("�˿��Ѷ��ᣬ�������������ٽ�����Ǯ��\n");
				printf("����ѡ���Ƿ������᣿(Y/N)\n");		//�Ƿ�����ʧ�� 
				getchar();
				scanf("%c",&fre);
				if(fre=='Y'||fre=='y'){//�����ʧ�� 
					p.hang=1;
					change(p);
					openfile("ab+");
					fwrite(&p,size,1,fp);
					close();
					openfile("ab+");
					printf("�ѳɹ�������ᣬ�������½�����Ǯ��\n");
					goto high; 
				}
				else{
					printf("���������ȡ��������ѡ�񣺸�������������Ǯ(A)���߷������˵�(B)\n");
					getchar();
					scanf("%c",&input);
					if(input=='A'||input=='a')
						goto high;
					else
						goto low;
				} 
			}
			else{//����δ��ʧ��ֱ�ӳ�ֵ�� 
				printf("���������ֵ���(��)��\n");
				scanf("%lf",&into);
				mon=p.money;
				sum=into+p.money;
				p.money=sum;
				change(p);
				openfile("ab+");
				fwrite(&p,size,1,fp);
				close();
				openfile("ab+");
				printf("��Ǯ�ɹ���ף��������죡\n��ֵǰ���(��)��%.2f\n��ֵ������(��)��%.2f\n",mon,sum);
				printf("����ѡ�񣺼�����Ǯ(A)���߷������˵�(B)��\n");
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
void del(){		//ע�� 
	struct data p;
	char num[6],input;
	int mark;
	openfile("ab+");
	do{
		printf("����������Ҫ����ע���ķ����ţ�\n");
		scanf("%s",num); 
		mark=find(num);
		if(mark==0){
			printf("���޴˷����ţ�����ѡ����������(A)���߷������˵�(B)��\n");
			getchar();
			scanf("%c",&input);
		}
		else{
			fseek(fp,(mark-1)*size,0);
			fread(&p,size,1,fp);
			printf("�÷����ֿ��ˣ�%s , ����%.2f��\n����ȷ���Ƿ����ע����(Y/N)\n",p.name,p.money);
			getchar();
			scanf("%c",&input);
			if(input=='Y'||input=='y'){
				change(p);
				openfile("ab+"); 
				printf("ע���ɹ�������ѡ�񣺼���ע��(A)���߷������˵�(B)��\n"); 
				getchar();
				scanf("%c",&input);
			} 
			else{
				printf("ע����ȡ������ѡ������ע��(A)���߷������˵�(B)��\n");
				getchar();
				scanf("%c",&input);
			} 
		}
	}while(input=='A'||input=='a');
	close();
} 
void lost(){		//��ʧ 
	char num[6],input,fre;
	int mark;
	struct data p;
	openfile("ab+");
	do{
		printf("����������Ҫ���й�ʧ/�����ʧ�ķ����ţ�\n");
		scanf("%s",num); 
		mark=find(num);
		if(mark==0){
			printf("���޴˷����ţ�����ѡ����������(A)���߷������˵�(B)��\n");
			getchar();
			scanf("%c",&input);
		}
		else{
			fseek(fp,(mark-1)*size,0);
			fread(&p,size,1,fp);
			printf("�÷��������ߣ�%s\n",p.name);
			if(p.hang==0){
				printf("�÷�����ǰΪ��ʧ״̬������ѡ���Ƿ�����ʧ��(Y/N)\n");
				getchar();
				scanf("%c",&fre); 
				if(fre=='Y'||fre=='y'){
					p.hang=1;
					change(p);
			    	openfile("ab+");
					fwrite(&p,size,1,fp);
	            	close();
					openfile("ab+");
					printf("�ѳɹ������ʧ������ѡ�񣺼�������(A)���߷������˵�(B)��\n");
					getchar();
					scanf("%c",&input);
				}
				else{
					printf("��ȡ�������ʧ������ѡ�񣺼�������(A)���߷������˵�(B)��\n"); 
					getchar();
					scanf("%c",&input);
				}
			}
			else{
				printf("�÷�����ǰΪ����״̬������ѡ���Ƿ���й�ʧ��(Y/N)\n");
				getchar();
				scanf("%c",&fre);
				if(fre=='Y'||fre=='y'){
					p.hang=0;
					change(p);
					openfile("ab+");
					fwrite(&p,size,1,fp);
					close();
					openfile("ab+");
					printf("�ѳɹ���ʧ������ѡ�񣺼�������(A)���߷������˵�(B)��\n");
					getchar();
					scanf("%c",&input);
				}
				else{
					printf("��ȡ����ʧ������ѡ�񣺼�������(A)���߷������˵�(B)��\n"); 
					getchar();
					scanf("%c",&input);
				}
			}
		}
	}while(input=='A'||input=='a'); 
	close();
} 
void password(){		//���� 
	char num[6],name[20],word1[7],word2[7],input,turn;
	int mark,i=0;
	struct data p;
	openfile("ab+");
high:	printf("����������Ҫ�����޸�����ķ����ţ�\n");
	scanf("%s",num); 
	mark=find(num );
	if(mark==0){
		printf("���޴˷����ţ�����ѡ����������(A)���߷������˵�(B)��\n");
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
		printf("��������ֿ�������(Three times!)��\n");
		for(i=0;i<3;i++){
			scanf("%s",name);
			if(strcmp(name,p.name)!=0){
				if(i<2)
					printf("�����֤ʧ�ܣ��������½������룺\n"); 
				else{
					printf("�����֤ʧ��3�Σ�����ȷ�Ϻ��ٽ��в�����\n"); 
					goto low;
				}
			}
			else{
				printf("�����֤�ɹ���\n����ȷ���Ƿ��޸����룡(Y/N)\n");
				getchar();
				scanf("%c",&turn);
				if(turn!='Y'&&turn!='y'){
					printf("�޸�������ȡ��������ѡ�񣺼������½����޸�����(A)���߷������˵�(B)��\n");
					getchar();
					scanf("%c",&input);
					if(input=='A'||input=='a')
						goto high;
					else
						goto low;
				}
				else{
					for(i=0;i<3;i++){
						printf("���������µ����루��������λ����\n");
						scanf("%s",word1);
						printf("�����ٴ������µ����루��������λ����\n");
						scanf("%s",word2);
						if(strcmp(word1,word2)!=0){
							if(i<2)
								printf("�������벻һ�£������������룺\n"); 
							else{
								printf("���������β�һ�£�����ȷ�Ϻ��ٽ��в�����\n"); 
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
							printf("�޸������ѳɹ��������μǴ����룡\n"); 
							printf("����ѡ�񣺼��������޸�����(A)���߷������˵�(B)��\n");
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
		switch(choice){						//ѡ����� 
			case 0: printf("��лʹ�ñ�������������˳����������������\n");
					break;
			case 1: openfile("wb+");//�������ĵ��� 
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
			default:printf("��������\n"); 
		}
	}while(choice!=0);
	return 0;
}
