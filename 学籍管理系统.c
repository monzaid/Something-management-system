#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct student{
	char num[13];
	char name[20];
	int math,English,wuli,computer,ma;
	double average;
	/*int score[5];*/
};
int size;
void inputscore();
void menu2();
void paixu();
void jisuan();
void tongji();
void fenxi();
void menu3();
void bukao();
void tuixue();
void cut(struct student s);
void xinmingdan();
void menu4();
void chazhao();
void mainmenu(){
		printf("����������������������\n");
		printf(".������ѡ����(0~4)��\n");
		printf("����������������������\n");
		printf(".   1--¼��ɼ�     . \n");
		printf(".   2--ͳ�Ƴɼ�     . \n");
		printf(".   3--����ѧ��     . \n");
		printf(".   4--��ѯ�ɼ�     . \n");
		printf(".   0--�˳�ϵͳ     . \n");
		printf("����������������������\n");
}
/*void menu1();*/
void inputscore(){
	int i=0;
	struct student a;
	FILE *fp;
	if((fp=fopen("ѧ��������Ϣ.txt","a+"))==NULL){
		printf("�ļ���ʧ�ܣ�\n");
		exit(0);
	}
	printf("�������ʾ����ѧ���ɼ���Ϣ��\n");
	do{
		i=0;
		printf("ѧ�ţ�");     scanf("%s",a.num); 
		printf("������");     scanf("%s",a.name);
		printf("������");     scanf("%d",&a.math);
		printf("Ӣ�");     scanf("%d",&a.English);
		printf("����");     scanf("%d",&a.wuli);
		printf("��̣�");     scanf("%d",&a.computer);
		printf("���ܣ�");     scanf("%d",&a.ma);
		a.average=(a.math+a.English+a.wuli+a.computer+a.ma)/5;
		fwrite(&a,size,1,fp);
		if(fclose(fp)){
		printf("�ļ��ر�ʧ�ܣ�\n");
		exit(0);
	}
		if((fp=fopen("ѧ��������Ϣ.txt","a+"))==NULL){
		printf("�ļ���ʧ�ܣ�\n");
		exit(0);
	}
		printf("�Ƿ������ӣ���������1�����������򷵻����˵���\n");
		scanf("%d",&i);
	}while(i==1);
	if(fclose(fp)){
		printf("�ļ��ر�ʧ�ܣ�\n");
		exit(0);
	}
}
void menu2(){
	int choice;
	do{
		printf("����������������������\n");
		printf(".������ѡ����(0~4)��\n");
		printf("����������������������\n");
		printf(".1--��ѧ������      . \n");
		printf(".2--����ƽ���ֲ�����. \n");
		printf(".3--ͳ�Ʒ�����      . \n");
		printf(".4--�������˵�      . \n");
		printf(".0--�˳�ϵͳ        . \n");
		printf("����������������������\n");
		scanf("%d", &choice);
	    switch(choice){
		    case 1: 
	            paixu();
	            break;
		   	case 2: 
	            jisuan();
	            break;
		    case 3: 
	            tongji();
	            break;
	        case 4: 
	            main();
	            /*exit(0);*/
	            /*break;*/
	        case 0:
	         	printf("��лʹ�ñ�������������˳����������������\n"); 
	         	exit(0);
	            break;
	        default:
	        	printf("��ѡ����ȷ�Ĺ���ѡ�\n");
	        	continue;
		} 
	}while(choice!=0);
} 
void paixu(){
	int i=0,j=0,n=0;
	struct student p;
	FILE *fp,*fp1;
	if ((fp=fopen("ѧ��������Ϣ.txt","r"))==NULL){
		printf("�ļ���ʧ�ܣ�\n");
		exit(0);
	}
	while(feof(fp)==0){
	fread(&p,size,1,fp);
	n++;
	}
	n-=1;
	struct student b[n],temp;
	fseek(fp,0L,0); 
	while(feof(fp)==0){
	fread(&b[i],size,1,fp);	
	i++;
	}
	fclose(fp);
	for(i=0;i<n-1;i++)
	for(j=i+1;j<n;j++)
	if(strcmp(b[i].num ,b[j].num )>0){
		temp=b[i];
		b[i]=b[j];
		b[j]=temp;
	}
	fp1=fopen("std.txt","w");
    if(fp==NULL){
		printf("�ļ���ʧ�ܣ�\n");
		return;
    }
	fprintf(fp,"ѧ��\t ����\t ����\t Ӣ��\t ����\t ���\t ����\n");
	for(i=0;i<n;i++){ 
	fprintf(fp,"%s\t %s\t %d\t %d\t %d\t %d\t %d\t \n",b[i].num ,b[i].name ,b[i].math ,b[i].English ,b[i].wuli, b[i].computer,b[i].ma);
	}
	printf("�ļ��ѱ�����std.txt����鿴��\n");
	fclose(fp1); 
}
void jisuan(){
	int i=0,j=0,n=0;
	FILE *fp=NULL,*fp1=NULL;
	struct student p;
	fp=fopen("ѧ��������Ϣ.txt","r");
	if(fp==NULL){
		printf("�ļ���ʧ��!\n");
		return;
	}
	while(feof(fp)==0){
	fread(&p,size,1,fp);
	n++;
	}
	n-=1;
	struct student b[n],temp;
	fseek(fp,0L,0); 
	while(feof(fp)==0){
	fread(&b[i],size,1,fp);	
	i++;
	}
	fclose(fp);
	for(i=0;i<n-1;i++)
	for(j=i+1;j<n;j++)
	if(b[i].average <b[j].average ){
		temp=b[i];
		b[i]=b[j];
		b[j]=temp;
	}
	fp1=fopen("sort.txt","w");
	if(fp==NULL){
		printf("�ļ���ʧ��!\n");
		return;
	}
	fprintf(fp,"ѧ��\t ����\t ����\t Ӣ��\t ����\t ���\t ����\t ƽ����\n");
	for(i=0;i<n;i++){
	fprintf(fp,"%s\t %s\t %d\t %d\t %d\t %d\t %d\t %.2f\n",b[i].num ,b[i].name ,b[i].math ,b[i].English ,b[i].wuli,b[i].computer,b[i].ma,b[i].average);	
	}
	
	printf("�ļ��ѱ�����sort.txt����鿴��\n");
	fclose(fp1);
}
void tongji(){
	int i=0,j=0,k=0,n=0,choice=0,count=0;
	struct student p;
	FILE *fp=NULL;
	fp=fopen("ѧ��������Ϣ.txt","r");
	if(fp==NULL){
		printf("�ļ���ʧ�ܣ�\n");
		return ;
	}
	while(feof(fp)==0){
		fread(&p,size,1,fp);
		n++;
	}
	n-=1;
	int list[n][5],a[5][5]={0};
	struct student b[n];
	fseek(fp,0L,0);
	while(feof(fp)==0){
		fread(&b[i],size,1,fp);
		i++;
	}
	fclose(fp);
	for(k=0;k<n;k++){ 
		list[k][0]=b[k].math/10;
		list[k][1]=b[k].English/10;
		list[k][2]=b[k].wuli/10;
		list[k][3]=b[k].computer/10;
		list[k][4]=b[k].ma/10;
	}
	for(k=0;k<n;k++)
	for(j=0;j<5;j++){
		switch(list[k][j]){
			case 10:
				a[j][0]++;
				break;
			case 9:
				a[j][0]++;
				break;
			case 8:
				a[j][1]++;
				break;
			case 7:
				a[j][2]++;
				break;
			case 6:
				a[j][3]++;
				break;
			default:
				a[j][4]++;
				break;	
		}
	}
	printf("\t    ���ſΡ���������ѧ��������\n");
	printf("��������������������������������������������������\n");
	printf("  ��Ŀ\t.90���� .80~89��.70~79��.60~69��.60����\n");
	printf("  ����\t");
	for(i=0;i<5;i++){
		printf("   %d\t",a[0][i]);
	}
	printf("\n"); 
	printf("  Ӣ��\t");
	for(i=0;i<5;i++){
		printf("   %d\t",a[1][i]);
	}
	printf("\n"); 
	printf("  ����\t");
	for(i=0;i<5;i++){
		printf("   %d\t",a[2][i]);
	}
	printf("\n"); 
	printf("  ���\t");
	for(i=0;i<5;i++){
		printf("   %d\t",a[3][i]);
	}
	printf("\n"); 
	printf("  ����\t");
	for(i=0;i<5;i++){
		printf("   %d\t",a[4][i]);
	}
	printf("\n"); 
	printf("��������������������������������������������������\n");	
}
/*void fenxi();*/
void menu3(){
	int choice;
do{
		printf("����������������������������\n");
		printf(".    ������ѡ����(0~4)��  \n");
		printf("����������������������������\n");
		printf(".1--���ɲ���ӡ����֪ͨ��  . \n");
		printf(".2--���ɲ���ӡ��ѧ֪ͨ��  . \n");
		printf(".3--���ɲ���ӡ������      . \n");
		printf(".4--�������˵�            . \n");
		printf(".0--�˳�ϵͳ              . \n");
		printf("����������������������������\n");
		scanf("%d", &choice);
       	switch(choice){
	     case 1: 
            bukao();
            break;
	     case 2: 
            tuixue();
            break;
	     case 3: 
            xinmingdan();
            break;
         case 4: 
            main();
            /*exit(0);
            break;*/
         case 0:
         	printf("��лʹ�ñ�������������˳����������������\n"); 
         	exit(0);
            break;
        default:
        	printf("��ѡ����ȷ�Ĺ���ѡ�\n");
        	continue;
	   } 
	}while(choice!=0);
} 
void choicetime(){
	printf("��������������������������\n");
	printf(".    ��ѡ���ؿ�ʱ�䣺     \n");
	printf("��������������������������\n");
	printf(".    1-- 7:30~ 9:30     . \n");
	printf(".    2-- 9:40~11:40     . \n");
	printf(".    3--14:30~16:30     . \n");
	printf(".    4--16:40~18:40     . \n");
	printf(".    5--19:30~21:30     . \n");
	printf("��������������������������\n");	
}
void bukao(){
	char subject[5][5]={"����","Ӣ��","����","���","����"},loc[40];
	char time[5][12]={" 7:30~ 9:30"," 9:40~11:40","14:30~16:30","16:40~18:40","19:30~21:30"};
	int i=0,j=0,k=0,n=0,choice=0,count=0;
	struct student p;
	FILE *fp=NULL;
	fp=fopen("ѧ��������Ϣ.txt","r");
	while(feof(fp)==0){
		fread(&p,size,1,fp);
		n++;
	}
	n-=1;
	int list[n][5],check[n][5];
	for(k=0;k<n;k++)
	for(j=0;j<5;j++){
		check[k][j]=0;
	}
	struct student b[n];
	fseek(fp,0L,0);
	while(feof(fp)==0){
		fread(&b[i],size,1,fp);
		i++;
	}
	/*fclose(fp);*/
	for(k=0;k<n;k++){ 
		list[k][0]=b[k].math;
		list[k][1]=b[k].English;
		list[k][2]=b[k].wuli;
		list[k][3]=b[k].computer;
		list[k][4]=b[k].ma;
	}
	for(k=0;k<n;k++)
	for(j=0;j<5;j++){
		if(list[k][j]<60){
			fseek(fp,k*size,0);
			fread(&p,size,1,fp);
			printf("ѧ����%s\n��%s�ɼ�������Ϊ%d��\n\n",p.name,subject[j],list[k][j]);
			choicetime();
			scanf("%d",&choice);
			for(i=0;i<5;i++){
				
	
					check[k][j]=choice;
					break; 
				
			}
			printf("�����뿼�Եص㣺\n");
			scanf("%s",&loc);
			printf("����Ϊ����ӡ�ؿ�֪ͨ���� \n\n");
			printf("����������������������������\n");
			printf(".       �ؿ�֪ͨ��        . \n");
			printf("����������������������������\n");
			printf("������%s\n",p.name);
			printf("�γ̣�%s\n",subject[j]);
			printf("ʱ�䣺%s\n",time[j]);
			printf("�ص㣺%s\n",loc);
			printf("����������������������������\n\n");
			count++;
		}
	}
	if(count==0){
		printf("��ѧ�����Բ�����\n"); 
	}
	else{
		printf("�����ؿ�֪ͨ���Ѵ�ӡ��ϣ�\n\n");
	}
	fclose(fp);
} 
void tuixue(){
	int i=0,j=0,k=0,n=0,m=0,a[5],count=0,loc[5];
	char show[5][5]={"����","Ӣ��","����","���","����"};
	struct student p;
	FILE *fp=NULL;
	fp=fopen("ѧ��������Ϣ.txt","r");
	while(feof(fp)==0){
		fread(&p,size,1,fp);
		n++;
	}
	n-=1;
	int list[n][5];
	struct student b[n];
	fseek(fp,0L,0);
	while(feof(fp)==0){
		fread(&b[i],size,1,fp);
		i++;
	}
	for(k=0;k<n;k++){ 
		list[k][0]=b[k].math;
		list[k][1]=b[k].English;
		list[k][2]=b[k].wuli;
		list[k][3]=b[k].computer;
		list[k][4]=b[k].ma;
	}
	for(k=0;k<n;k++){
		i=0;
		for(j=0;j<5;j++){
			if(list[k][j]<60){
				fseek(fp,k*size,0);
				fread(&p,size,1,fp);
				loc[i]=j;
				i++;
			}
		}
		if(i>3){
			printf("����������������������������\n");
			printf(".       ��ѧ֪ͨ��        . \n");
			printf("����������������������������\n");
			printf("ѧ�ţ�%s\n",p.num);
			printf("������%s\n",p.name);
			printf("��ѧԭ��3��ѧ�����ϲ�����\n");
			for(m=0;m<i;m++){
				printf("%s��%d��\n",show[loc[m]],list[k][loc[m]]);
			} 
			printf("����������������������������\n\n");	
			count++;
		}
	}
	if(count==0){
		printf("��ѧ����Ҫ����ѧ��\n\n"); 
	}
	else{
		printf("��ѧ֪ͨ����ӡ��ϣ�\n\n");
	}
	fclose(fp);
}
void shanchu(struct student s){
	FILE *fp;
	fp=fopen("ѧ��������Ϣ.txt","r");
	int n=0,i=0;
	fseek(fp,0L,0);
	struct student p;
	while(!feof(fp)){
		fread(&p,size,1,fp);
		n++;
	}
	n=n-1; 
	fseek(fp,0L,0);
	struct student a[n];
	while(fread(&a[i],size,1,fp)){
		i++;
	}
	fclose(fp);
	fp=fopen("ѧ��������Ϣ.txt","wb+");
	for(i=0;i<n;i++){
		if(strcmp(a[i].num,s.num)!=0){
			fwrite(&a[i],size,1,fp);
		}
	}
	fclose(fp);
}
void xinmingdan(){
	int i=0,j=0,k=0,n=0,m=0,a[5],count=0;	
	struct student p;
	FILE *fp=NULL,*fp1=NULL;
	fp=fopen("ѧ��������Ϣ.txt","r");
	fp1=fopen("next.dat.txt","w");
	fprintf(fp1,"ѧ��\t ����\t ����\t Ӣ��\t ����\t ���\t ����\t ƽ����\n");
	while(feof(fp)==0){
		fread(&p,size,1,fp);
		n++;
	}
	n-=1;
	int list[n][5];
	struct student b[n];
	fseek(fp,0L,0);
	while(feof(fp)==0){
		fread(&b[i],size,1,fp);
		i++;
	}
	for(k=0;k<n;k++){ 
		list[k][0]=b[k].math;
		list[k][1]=b[k].English;
		list[k][2]=b[k].wuli;
		list[k][3]=b[k].computer;
		list[k][4]=b[k].ma;
	}
	for(k=0;k<n;k++){
		i=0;
		for(j=0;j<5;j++){
			if(list[k][j]<60){
				fseek(fp,k*size,0);
				fread(&p,size,1,fp);
				i++;
			}
		}
		if(i==0){
			printf("%s\t %s\t %d\t %d\t %d\t %d\t %d\t %.2f\n",p.num,p.name,p.math,p.English,p.wuli,p.computer,p.ma,p.average);	
			fprintf(fp1,"%s\t %s\t %d\t %d\t %d\t %d\t %d\t %.2f\n",p.num,p.name,p.math,p.English,p.wuli,p.computer,p.ma,p.average);	
		}
		if(i>3){
			fclose(fp);
			shanchu(p);
			fp=fopen("ѧ��������Ϣ.txt","r");
		}
	}
	printf("�ļ��ѱ�����next.txt����鿴��\n\n");
	fclose(fp);
	fclose(fp1);
}
/*void menu4();
void chazhao();*/
int main(){
	int choice;
	size=sizeof(struct student);
	do{
		mainmenu();
		scanf("%d", &choice);
      	switch(choice){
	    case 1: 
            inputscore();
            break;
	    case 2: 
            menu2();
            break;
	    case 3: 
            menu3();
            break;
        /*case 4: 
            menu4();
            break;*/
        case 0:
         	printf("��лʹ�ñ�������������˳����������������\n"); 
            break;
        default:
        	printf("��ѡ����ȷ�Ĺ���ѡ�\n");
        	continue;
	   } 
	}while(choice!=0);
	return 0;
}
