#include<stdio.h>
#include<stdlib.h>
struct couse * head1;
struct student * head2;
struct couse//课程信息结构体
{
  int num1;
  char name1[10];
  char teacher[10];
  int score;
  int peo;//课程已选人数
  int maxpeo;//课程人数上限
  struct couse * next;
};
struct student//学生信息结构体
{
  int num2;
  char name2[10];
  int num[3];//已选课程编号
  int cousenum;//已选课程数量
  struct student * next;
};

void startc()//录入课程
{
  FILE * fp;
  struct couse *p1,*p2;
  int n=0;
  if((fp=fopen("课程数据.txt","r"))==NULL)
  {
    printf("找不到文件!\n");
    exit(0);
  }
  p1=p2=(struct couse*)malloc(sizeof(struct couse));
  fscanf(fp,"%d %s %s %d %d %d",&p1->num1,p1->name1,p1->teacher,&p1->score,&p1->peo,&p1->maxpeo);
  head1=NULL;
  while(!feof(fp))
  {
    n=n+1;
    if(n==1)head1=p1;
    else p2->next=p1;
    p2=p1;
    p1=(struct couse * )malloc(sizeof(struct couse));
    fscanf(fp,"%d %s %s %d %d %d",&p1->num1,p1->name1,p1->teacher,&p1->score,&p1->peo,&p1->maxpeo);
  }
  p2->next=NULL;
  fclose(fp);
  printf("课程数据已录入\n");
}
void starts()//录入学生信息
{
  FILE * fp;
  struct student *p1,*p2;
  int n=0;
  if((fp=fopen("学生数据.txt","r"))==NULL)
  {
    printf("找不到文件!\n");
    exit(0);
  }
  p1=p2=(struct student*)malloc(sizeof(struct student));
  fscanf(fp,"%d %s %d %d %d %d",&p1->num2,p1->name2,&p1->num[0],&p1->num[1],&p1->num[2],&p1->cousenum);
  head2=NULL;
  while(!feof(fp))
  {
    n=n+1;
    if(n==1)head2=p1;
    else p2->next=p1;
    p2=p1;
    p1=(struct student * )malloc(sizeof(struct student));
    fscanf(fp,"%d %s %d %d %d %d",&p1->num2,p1->name2,&p1->num[0],&p1->num[1],&p1->num[2],&p1->cousenum);
  }
  p2->next=NULL;
  fclose(fp);
  printf("学生数据已录入\n");
}
void insc(struct couse *newcouse)//增加课程
{
  struct couse *p0,*p1,*p2;
  p1=head1;
  p0=newcouse;
  if(head1==NULL)
  {
    head1=p0;
    p0->next=NULL;
  }
  else
  {
    while((p0->num1 > p1->num1) && (p1->next!=NULL))
    {
      p2=p1;
      p1=p1->next;
    }
    if(p0->num1 <= p1->num1)
    {
      if(head1==p1) head1=p0;
      else p2->next=p0;
      p0->next=p1;
    }
    else
    {
      p1->next=p0;
      p0->next=NULL;
    }
  }

}
void delc(int num1)//删除课程
{
  struct couse *p1,*p2;
  if(head1==NULL)
  {
    printf("\n没有课程,无法删除!\n");
    goto end;
  }
  p1=head1;
  while(num1!=p1->num1 && p1->next!=NULL)
  {
    p2=p1;
    p1=p1->next;
  }
  if(num1==p1->num1)
  {
    if(p1==head1) head1=p1->next;
    else p2->next=p1->next;
    printf("已删除该编号课程!\n");
  }
  else printf("无该编号的课程!\n");
  end:;
}
void managec()//课程管理
{
  struct couse * newcouse;
  int i,num1;
  printf("课程管理\n");
  printf("1.新增课程\n");
  printf("2.删除课程\n");
  scanf("%d",&i);
  switch(i)
  {
  case(1):
    {
      newcouse=(struct couse *)malloc(sizeof(struct couse));
      printf("课程编号 课程名称 任课老师 学分 课程人数上限\n");
      scanf("%d %s %s %d %d",&newcouse->num1,newcouse->name1,newcouse->teacher,&newcouse->score,&newcouse->maxpeo);
      newcouse->peo=0;
      insc(newcouse);
      break;
    }
  case(2):
    {
      printf("请输入要删除课程的编号:\n");
      scanf("%d",&num1);
      delc(num1);
      break;
    }

  }
}

void xuanke(struct student * s)//选课
{
  struct couse * p;
  int num1,i;
  printf("请输入要选课的编号:\n");
  scanf("%d",&num1);
  for(i=0;s->num[i]!=0;i++);
  s->num[i]=num1;
  (s->cousenum)++;
  p=head1;
  while(p->num1!=num1) p=p->next;
  (p->peo)++;
}
void tuike(struct student * s)//退课
{
  struct couse * p;
  int num1,i,j;
  printf("请输入你要退掉的课程编号:\n");
  scanf("%d",&num1);
  p=head1;
  while(p->num1!=num1) p=p->next;
  for(i=0;s->num[i]!=num1;i++);
  for(j=i;s->num[j]!=0&&j<2;j++) s->num[j]=s->num[j+1];
  s->num[2]=0;
  (p->peo)--;
  printf("退课成功!\n");
}
void kexuan()//查询可选课程
{
  char e;
  struct couse * c;
  struct student * s;
  int num2,i,j=0,t=0;
  printf("请输入你的学号:");
  scanf("%d",&num2);
  s=head2;
  while(s->num2!=num2 && s->next!=NULL) s=s->next;
  if(s->num2!=num2)
  {
    printf("不存在你的信息\n");
    goto end;
  }
  c=head1;
  printf("你的可选课程编号:\n");
  while(c!=NULL)
  {
    for(t=0,i=0;s->num[i]!=0;i++)
    {
      if(c->num1==s->num[i]) t=1;
    }
    if(t==0 && (c->peo!=c->maxpeo))
    {
      printf("%d\n",c->num1);
      j++;
    }
    c=c->next;
  }
  if(j==0)
  {
    printf("你选课已满\n");
    goto end;
  }
  printf("选课(y/n)?:\n");
  getchar();
  e=getchar();
  i=0;
  while(e=='y')
  {
    xuanke(s);
    printf("继续选课(y/n)?:\n");
    getchar();
    e=getchar();
  }
  end:;
}

void yixuan()//查询已选课程
{
  char c;
  struct couse * p0;
  struct student * p;
  int num2,i,f=0;
  printf("请输入学号:\n");
  scanf("%d",&num2);
  p=head2;
  while(p->num2!=num2 && p!=NULL) p=p->next;
  if(p==NULL)
  {
    printf("不存在你的信息\n");
    goto end;
  }
  printf("已选课程编号:\n");
  if(p->num[0]==0)
  {
    printf("你还没选课!\n");
    goto end;
  }
  for(i=0;p->num[i]!=0;i++)
  {
    printf("%d\n",p->num[i]);
    p0=head1;
    while(p0->num1!=p->num[i]) p0=p0->next;
    f=f+p0->score;
  }
  printf("总学分:%d\n",f);
  printf("是否进行退课(y/n)?");
  getchar();
  c=getchar();
  while(c=='y')
  {
    tuike(p);
    printf("继续退课(y/n)?");
    getchar();
    c=getchar();
    (p->cousenum)--;
  }
  end:;
}
void choose()//学生选课主函数
{
  int i;
  printf("学生选课\n");
  printf("1.查询可选课程\n");
  printf("2.查询已选课程\n");
  scanf("%d",&i);
  switch(i)
  {
  case(1):kexuan();break;
  case(2):yixuan();break;
  case(3):break;
  }
}
int main()//主函数
{
  int i;
  startc();
  starts();
  start:
  printf("欢迎使用学生选课系统!\n");
  printf("1.课程管理\n");
  printf("2.学生选课\n");
  printf("3.退出系统\n");
  scanf("%d",&i);
  if(i<1 || i>3)
  {
    printf("输入错误,请重输:\n");
    goto start;
  }
  switch(i)
  {

  case(1):
    {
      system("cls");
      managec();
      goto start;
      break;
    }

  case(2):
    {
      system("cls");
      choose();
      goto start;
      break;
    }
  case(3):
    {
      system("cls");
      printf("感谢使用本系统!\n再见!\n");
    }
  }
  return(0);
}
