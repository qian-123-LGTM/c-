#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h> 
#define MAX 50
struct Mistake{
	char title[100];
	char error[200];
	char answer[200];
};
struct Mistake mistakes[MAX];
int count=0;
int review_count=0;
void clear_screen()
{
	#ifdef _WIN32
	system("cls");
	#else
	system("clear");
	#endif
}
void load_from_file()
{
	FILE *fp=fopen("mistakes.txt","r");
	if(fp==NULL) return;
	fscanf(fp,"%d",&count);
	int i=0;
	for(i=0;i<count;i++){
		fscanf(fp,"%s\n",mistakes[i].title);
		fscanf(fp,"%s\n",mistakes[i].error);
		fscanf(fp,"%s\n",mistakes[i].answer);
	}
	fclose(fp);
}
void save_to_file()
{
	FILE *fp=fopen("mistakes.txt","w");
	if(fp==NULL){
		printf("保存失败！");
		return;
	}
	fprintf(fp,"%d\n",count);
	int i=0;
	for(i=0;i<count;i++){
		fprintf(fp,"%s\n",mistakes[i].title);
		fprintf(fp,"%s\n",mistakes[i].error);
		fprintf(fp,"%s\n",mistakes[i].answer);
	}
	printf("保存成功！");
	fclose(fp);
}
void add_mistake()
{
	clear_screen();
	getchar();
	if(count>=MAX){
		printf("错题最多添加50道，目前已记录50道错题，无法继续添加\n");
		printf("按回车键返回");
		getchar();getchar();
		return;
	}
	printf("==========添加错题=========\n");
	printf("请输入题目：");
	fgets(mistakes[count].title,100,stdin);
	mistakes[count].title[strcspn(mistakes[count].title,"\n")]='\0';
	printf("请输入错误原因：");
	fgets(mistakes[count].error,200,stdin);
	mistakes[count].error[strcspn(mistakes[count].error,"\n")]='\0';
	printf("请输入修改过后的答案（即正确答案）：");
	fgets(mistakes[count].answer,200,stdin);
	mistakes[count].answer[strcspn(mistakes[count].answer,"\n")]='\0';
	count++;
	save_to_file();
	printf("保存成功！\n");
	printf("按下回车返回\n");
	getchar();
	clear_screen();
}
void delete_mistake()
{
	clear_screen();
	int ber=0;
	int a=0;
	if(count==0){
		printf("目前没有错题，无法进行删除\n");
		printf("按下回车，返回首页"); 
		getchar();getchar();
		return; 
	}
	else{
		int i=0;
		for(i=0;i<count;i++){
			printf("%d.题目：%s\n",i+1,mistakes[i].title);
			printf("错误：%s\n",mistakes[i].error);
			printf("答案：%s\n",mistakes[i].answer);
			printf("      \n");
		}
		while(1){
			printf("请选择要删除的题目的题号：");
	scanf("%d",&ber);
	if(ber<1||ber>count){
		printf("输入无效！请重新输入！\n");
		getchar();getchar();
	}
	else break;
		}
	}
	for(a=ber-1;a<=count;a++){
		mistakes[a]=mistakes[a+1];
	}
	count--;
	save_to_file();
	getchar();getchar();
	clear_screen();
}
void list_mistakes()
{
	clear_screen();
	if(count==0){
		printf("目前没有错题，继续加油哦！");
		getchar();getchar();
		return; 
	}
	else{
		int i=0;
		for(i=0;i<count;i++){
			printf("%d.题目：%s\n",i+1,mistakes[i].title);
			printf("错误：%s\n",mistakes[i].error);
			printf("答案：%s\n",mistakes[i].answer);
			printf("      \n");
		}
		printf("按下回车返回\n");
		getchar();getchar();
		clear_screen();
	}
}
void review_mistake()
{
	clear_screen();
	if(count==0){
		printf("目前没有错题，继续加油哦！");
		getchar();getchar();
		return; 
	}
	else{
		int t=rand()%count;
		printf("这是你曾经的错题：\n");
		printf("%s\n",mistakes[t].title);
		printf("请回忆正确答案,思考结束后按下回车查看答案：\n");
		getchar();getchar();
		printf("错误答案：%s\n",mistakes[t].error);
		printf("正确答案：%s\n",mistakes[t].answer);
		printf("\n按下回车返回\n");
		review_count++;
		getchar();
		clear_screen();
	}
}
void show_report()
{
	clear_screen();
	printf("==========学习报告==========\n");
	printf("当前错题总数：%d道\n",count);
	printf("累计随即复习次数：%d次\n",review_count);
	printf("坚持就是胜利！！！\n");
	printf("============================\n");
	printf(" \n");
	printf("按下回车，返回主页。。。\n");
	getchar();getchar();
	clear_screen();
	return;
}
int main()
{
	srand(time(NULL));
	system("color 0A");
	load_from_file();
	while(1){
	printf("\n");
    printf("  ==============================\n");
    printf("       C 语言错题本 v1.0\n");
    printf("  ==============================\n");
    printf("  |                            |\n");
    printf("  |   1. 添加错题              |\n");
    printf("  |   2. 查看所有错题          |\n");
    printf("  |   3. 随机抽题复习          |\n");
    printf("  |   4. 删除错题              |\n");
    printf("  |   5. 学习报告              |\n");
    printf("  |   6. 退出                  |\n");
    printf("  |                            |\n");
    printf("  ==============================\n"); 
    printf("\n  请选择（1-6）：");
    int num=0;
    scanf("%d",&num);
    if(num>6){
    	printf("无效输入，请按回车返回主页，重新输入\n");
    	getchar();getchar();
    	clear_screen();
	}
	switch(num){
		case 1:add_mistake();break;
		case 2:list_mistakes();break;
		case 3:review_mistake();break;
		case 4:delete_mistake();break;
		case 5:show_report();break; 
		case 6:
			clear_screen();
			printf("感谢使用c语言错题本！\n");
			printf("祝你早日成为c语言大肘子~~~~\n\n\n\n"); 
		return 0;break;
	}
	}
	return 0;
}
