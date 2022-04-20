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
		printf("……………………………\n");
		printf(".请输入选项编号(0~4)：\n");
		printf("……………………………\n");
		printf(".   1--录入成绩     . \n");
		printf(".   2--统计成绩     . \n");
		printf(".   3--处理学籍     . \n");
		printf(".   4--查询成绩     . \n");
		printf(".   0--退出系统     . \n");
		printf("……………………………\n");
}
/*void menu1();*/
void inputscore(){
	int i=0;
	struct student a;
	FILE *fp;
	if((fp=fopen("学生基本信息.txt","a+"))==NULL){
		printf("文件打开失败！\n");
		exit(0);
	}
	printf("请根据提示输入学生成绩信息！\n");
	do{
		i=0;
		printf("学号：");     scanf("%s",a.num); 
		printf("姓名：");     scanf("%s",a.name);
		printf("高数：");     scanf("%d",&a.math);
		printf("英语：");     scanf("%d",&a.English);
		printf("物理：");     scanf("%d",&a.wuli);
		printf("编程：");     scanf("%d",&a.computer);
		printf("马哲：");     scanf("%d",&a.ma);
		a.average=(a.math+a.English+a.wuli+a.computer+a.ma)/5;
		fwrite(&a,size,1,fp);
		if(fclose(fp)){
		printf("文件关闭失败！\n");
		exit(0);
	}
		if((fp=fopen("学生基本信息.txt","a+"))==NULL){
		printf("文件打开失败！\n");
		exit(0);
	}
		printf("是否继续添加？是请输入1，输入其它则返回主菜单。\n");
		scanf("%d",&i);
	}while(i==1);
	if(fclose(fp)){
		printf("文件关闭失败！\n");
		exit(0);
	}
}
void menu2(){
	int choice;
	do{
		printf("……………………………\n");
		printf(".请输入选项编号(0~4)：\n");
		printf("……………………………\n");
		printf(".1--按学号排序      . \n");
		printf(".2--计算平均分并排序. \n");
		printf(".3--统计分数段      . \n");
		printf(".4--返回主菜单      . \n");
		printf(".0--退出系统        . \n");
		printf("……………………………\n");
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
	         	printf("感谢使用本软件！已正常退出，按任意键结束。\n"); 
	         	exit(0);
	            break;
	        default:
	        	printf("请选择正确的功能选项！\n");
	        	continue;
		} 
	}while(choice!=0);
} 
void paixu(){
	int i=0,j=0,n=0;
	struct student p;
	FILE *fp,*fp1;
	if ((fp=fopen("学生基本信息.txt","r"))==NULL){
		printf("文件打开失败！\n");
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
		printf("文件打开失败！\n");
		return;
    }
	fprintf(fp,"学号\t 姓名\t 高数\t 英语\t 物理\t 编程\t 马哲\n");
	for(i=0;i<n;i++){ 
	fprintf(fp,"%s\t %s\t %d\t %d\t %d\t %d\t %d\t \n",b[i].num ,b[i].name ,b[i].math ,b[i].English ,b[i].wuli, b[i].computer,b[i].ma);
	}
	printf("文件已保存至std.txt，请查看。\n");
	fclose(fp1); 
}
void jisuan(){
	int i=0,j=0,n=0;
	FILE *fp=NULL,*fp1=NULL;
	struct student p;
	fp=fopen("学生基本信息.txt","r");
	if(fp==NULL){
		printf("文件打开失败!\n");
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
		printf("文件打开失败!\n");
		return;
	}
	fprintf(fp,"学号\t 姓名\t 高数\t 英语\t 物理\t 编程\t 马哲\t 平均分\n");
	for(i=0;i<n;i++){
	fprintf(fp,"%s\t %s\t %d\t %d\t %d\t %d\t %d\t %.2f\n",b[i].num ,b[i].name ,b[i].math ,b[i].English ,b[i].wuli,b[i].computer,b[i].ma,b[i].average);	
	}
	
	printf("文件已保存至sort.txt，请查看。\n");
	fclose(fp1);
}
void tongji(){
	int i=0,j=0,k=0,n=0,choice=0,count=0;
	struct student p;
	FILE *fp=NULL;
	fp=fopen("学生基本信息.txt","r");
	if(fp==NULL){
		printf("文件打开失败！\n");
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
	printf("\t    各门课、各分数段学生的人数\n");
	printf("…………………………………………………………………\n");
	printf("  科目\t.90以上 .80~89分.70~79分.60~69分.60以下\n");
	printf("  高数\t");
	for(i=0;i<5;i++){
		printf("   %d\t",a[0][i]);
	}
	printf("\n"); 
	printf("  英语\t");
	for(i=0;i<5;i++){
		printf("   %d\t",a[1][i]);
	}
	printf("\n"); 
	printf("  物理\t");
	for(i=0;i<5;i++){
		printf("   %d\t",a[2][i]);
	}
	printf("\n"); 
	printf("  编程\t");
	for(i=0;i<5;i++){
		printf("   %d\t",a[3][i]);
	}
	printf("\n"); 
	printf("  马哲\t");
	for(i=0;i<5;i++){
		printf("   %d\t",a[4][i]);
	}
	printf("\n"); 
	printf("…………………………………………………………………\n");	
}
/*void fenxi();*/
void menu3(){
	int choice;
do{
		printf("……………………………………\n");
		printf(".    请输入选项编号(0~4)：  \n");
		printf("……………………………………\n");
		printf(".1--生成并打印补考通知单  . \n");
		printf(".2--生成并打印退学通知单  . \n");
		printf(".3--生成并打印新名册      . \n");
		printf(".4--返回主菜单            . \n");
		printf(".0--退出系统              . \n");
		printf("……………………………………\n");
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
         	printf("感谢使用本软件！已正常退出，按任意键结束。\n"); 
         	exit(0);
            break;
        default:
        	printf("请选择正确的功能选项！\n");
        	continue;
	   } 
	}while(choice!=0);
} 
void choicetime(){
	printf("…………………………………\n");
	printf(".    请选择重考时间：     \n");
	printf("…………………………………\n");
	printf(".    1-- 7:30~ 9:30     . \n");
	printf(".    2-- 9:40~11:40     . \n");
	printf(".    3--14:30~16:30     . \n");
	printf(".    4--16:40~18:40     . \n");
	printf(".    5--19:30~21:30     . \n");
	printf("…………………………………\n");	
}
void bukao(){
	char subject[5][5]={"高数","英语","物理","编程","马哲"},loc[40];
	char time[5][12]={" 7:30~ 9:30"," 9:40~11:40","14:30~16:30","16:40~18:40","19:30~21:30"};
	int i=0,j=0,k=0,n=0,choice=0,count=0;
	struct student p;
	FILE *fp=NULL;
	fp=fopen("学生基本信息.txt","r");
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
			printf("学生：%s\n其%s成绩不及格，为%d分\n\n",p.name,subject[j],list[k][j]);
			choicetime();
			scanf("%d",&choice);
			for(i=0;i<5;i++){
				
	
					check[k][j]=choice;
					break; 
				
			}
			printf("请输入考试地点：\n");
			scanf("%s",&loc);
			printf("以下为您打印重考通知单！ \n\n");
			printf("……………………………………\n");
			printf(".       重考通知单        . \n");
			printf("……………………………………\n");
			printf("姓名：%s\n",p.name);
			printf("课程：%s\n",subject[j]);
			printf("时间：%s\n",time[j]);
			printf("地点：%s\n",loc);
			printf("……………………………………\n\n");
			count++;
		}
	}
	if(count==0){
		printf("无学生考试不及格！\n"); 
	}
	else{
		printf("所有重考通知书已打印完毕！\n\n");
	}
	fclose(fp);
} 
void tuixue(){
	int i=0,j=0,k=0,n=0,m=0,a[5],count=0,loc[5];
	char show[5][5]={"高数","英语","物理","编程","马哲"};
	struct student p;
	FILE *fp=NULL;
	fp=fopen("学生基本信息.txt","r");
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
			printf("……………………………………\n");
			printf(".       退学通知单        . \n");
			printf("……………………………………\n");
			printf("学号：%s\n",p.num);
			printf("姓名：%s\n",p.name);
			printf("退学原因：3门学科以上不及格\n");
			for(m=0;m<i;m++){
				printf("%s：%d分\n",show[loc[m]],list[k][loc[m]]);
			} 
			printf("……………………………………\n\n");	
			count++;
		}
	}
	if(count==0){
		printf("无学生需要被退学！\n\n"); 
	}
	else{
		printf("退学通知单打印完毕！\n\n");
	}
	fclose(fp);
}
void shanchu(struct student s){
	FILE *fp;
	fp=fopen("学生基本信息.txt","r");
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
	fp=fopen("学生基本信息.txt","wb+");
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
	fp=fopen("学生基本信息.txt","r");
	fp1=fopen("next.dat.txt","w");
	fprintf(fp1,"学号\t 姓名\t 高数\t 英语\t 物理\t 编程\t 马哲\t 平均分\n");
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
			fp=fopen("学生基本信息.txt","r");
		}
	}
	printf("文件已保存至next.txt，请查看。\n\n");
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
         	printf("感谢使用本软件！已正常退出，按任意键结束。\n"); 
            break;
        default:
        	printf("请选择正确的功能选项！\n");
        	continue;
	   } 
	}while(choice!=0);
	return 0;
}
