#include<stdio.h>
#include<stdlib.h>
struct couse * head1;
struct student * head2;
struct couse//�γ���Ϣ�ṹ��
{
  int num1;
  char name1[10];
  char teacher[10];
  int score;
  int peo;//�γ���ѡ����
  int maxpeo;//�γ���������
  struct couse * next;
};
struct student//ѧ����Ϣ�ṹ��
{
  int num2;
  char name2[10];
  int num[3];//��ѡ�γ̱��
  int cousenum;//��ѡ�γ�����
  struct student * next;
};

void startc()//¼��γ�
{
  FILE * fp;
  struct couse *p1,*p2;
  int n=0;
  if((fp=fopen("�γ�����.txt","r"))==NULL)
  {
    printf("�Ҳ����ļ�!\n");
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
  printf("�γ�������¼��\n");
}
void starts()//¼��ѧ����Ϣ
{
  FILE * fp;
  struct student *p1,*p2;
  int n=0;
  if((fp=fopen("ѧ������.txt","r"))==NULL)
  {
    printf("�Ҳ����ļ�!\n");
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
  printf("ѧ��������¼��\n");
}
void insc(struct couse *newcouse)//���ӿγ�
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
void delc(int num1)//ɾ���γ�
{
  struct couse *p1,*p2;
  if(head1==NULL)
  {
    printf("\nû�пγ�,�޷�ɾ��!\n");
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
    printf("��ɾ���ñ�ſγ�!\n");
  }
  else printf("�޸ñ�ŵĿγ�!\n");
  end:;
}
void managec()//�γ̹���
{
  struct couse * newcouse;
  int i,num1;
  printf("�γ̹���\n");
  printf("1.�����γ�\n");
  printf("2.ɾ���γ�\n");
  scanf("%d",&i);
  switch(i)
  {
  case(1):
    {
      newcouse=(struct couse *)malloc(sizeof(struct couse));
      printf("�γ̱�� �γ����� �ο���ʦ ѧ�� �γ���������\n");
      scanf("%d %s %s %d %d",&newcouse->num1,newcouse->name1,newcouse->teacher,&newcouse->score,&newcouse->maxpeo);
      newcouse->peo=0;
      insc(newcouse);
      break;
    }
  case(2):
    {
      printf("������Ҫɾ���γ̵ı��:\n");
      scanf("%d",&num1);
      delc(num1);
      break;
    }

  }
}

void xuanke(struct student * s)//ѡ��
{
  struct couse * p;
  int num1,i;
  printf("������Ҫѡ�εı��:\n");
  scanf("%d",&num1);
  for(i=0;s->num[i]!=0;i++);
  s->num[i]=num1;
  (s->cousenum)++;
  p=head1;
  while(p->num1!=num1) p=p->next;
  (p->peo)++;
}
void tuike(struct student * s)//�˿�
{
  struct couse * p;
  int num1,i,j;
  printf("��������Ҫ�˵��Ŀγ̱��:\n");
  scanf("%d",&num1);
  p=head1;
  while(p->num1!=num1) p=p->next;
  for(i=0;s->num[i]!=num1;i++);
  for(j=i;s->num[j]!=0&&j<2;j++) s->num[j]=s->num[j+1];
  s->num[2]=0;
  (p->peo)--;
  printf("�˿γɹ�!\n");
}
void kexuan()//��ѯ��ѡ�γ�
{
  char e;
  struct couse * c;
  struct student * s;
  int num2,i,j=0,t=0;
  printf("���������ѧ��:");
  scanf("%d",&num2);
  s=head2;
  while(s->num2!=num2 && s->next!=NULL) s=s->next;
  if(s->num2!=num2)
  {
    printf("�����������Ϣ\n");
    goto end;
  }
  c=head1;
  printf("��Ŀ�ѡ�γ̱��:\n");
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
    printf("��ѡ������\n");
    goto end;
  }
  printf("ѡ��(y/n)?:\n");
  getchar();
  e=getchar();
  i=0;
  while(e=='y')
  {
    xuanke(s);
    printf("����ѡ��(y/n)?:\n");
    getchar();
    e=getchar();
  }
  end:;
}

void yixuan()//��ѯ��ѡ�γ�
{
  char c;
  struct couse * p0;
  struct student * p;
  int num2,i,f=0;
  printf("������ѧ��:\n");
  scanf("%d",&num2);
  p=head2;
  while(p->num2!=num2 && p!=NULL) p=p->next;
  if(p==NULL)
  {
    printf("�����������Ϣ\n");
    goto end;
  }
  printf("��ѡ�γ̱��:\n");
  if(p->num[0]==0)
  {
    printf("�㻹ûѡ��!\n");
    goto end;
  }
  for(i=0;p->num[i]!=0;i++)
  {
    printf("%d\n",p->num[i]);
    p0=head1;
    while(p0->num1!=p->num[i]) p0=p0->next;
    f=f+p0->score;
  }
  printf("��ѧ��:%d\n",f);
  printf("�Ƿ�����˿�(y/n)?");
  getchar();
  c=getchar();
  while(c=='y')
  {
    tuike(p);
    printf("�����˿�(y/n)?");
    getchar();
    c=getchar();
    (p->cousenum)--;
  }
  end:;
}
void choose()//ѧ��ѡ��������
{
  int i;
  printf("ѧ��ѡ��\n");
  printf("1.��ѯ��ѡ�γ�\n");
  printf("2.��ѯ��ѡ�γ�\n");
  scanf("%d",&i);
  switch(i)
  {
  case(1):kexuan();break;
  case(2):yixuan();break;
  case(3):break;
  }
}
int main()//������
{
  int i;
  startc();
  starts();
  start:
  printf("��ӭʹ��ѧ��ѡ��ϵͳ!\n");
  printf("1.�γ̹���\n");
  printf("2.ѧ��ѡ��\n");
  printf("3.�˳�ϵͳ\n");
  scanf("%d",&i);
  if(i<1 || i>3)
  {
    printf("�������,������:\n");
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
      printf("��лʹ�ñ�ϵͳ!\n�ټ�!\n");
    }
  }
  return(0);
}
