 #include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M 256// 对应256种颜色 
#define N 512//511个结点 
 struct txt{
   char num[1];   //记录字符
   int frequent;//记录字符出现次数
   int weight;//权值
};
struct HTNodes{
   char  n[2]; //记录结点
   int weight; //记录结点权值
};
typedef struct   //二叉树结构
{
 int weight;
 int lchild,rchild,parent;
}HTNode,*HuffmanTree;
typedef struct     //编码结构
{
 char *code;
 int length;
}CodeType;
 struct HTNodes HS[M];
int getweight()
{    char a;
     int m,s,fre[256]={0};
     int length=0,i,j,d[M];
      struct txt CH[M];
   for(i=0;i<16;i++)
   {
   	for(j=0;j<16;j++)
   	{   
   		if(i<10) CH[i*16+j].num[1]=i+48;
   	    else CH[i*16+j].num[1]=65+i-10;
		if(j<10) CH[i*16+j].num[0]=j+48;
		else CH[i*16+j].num[0]=65+j-10;
   }
   }
 // for(i=0;i<256;i++)
      // printf("%c %c\n",CH[i].num[0],CH[i].num[1]);  
	    //制作数表 
	     for(i=0;i<M;i++)
     {
         CH[i].frequent=0;
         CH[i].weight=0;
     }
   FILE *fp;
     fp=fopen("picture.txt","r");
      while(!feof(fp))    //此循环在找出图文件中颜色码出现的频率 
    {  
        a=fgetc(fp);
//        if(a!=' ')
         for(i=0;i<16;i++)
         {if(a==CH[i].num[0])
         {  m=i;
           break;
		 }}
//		 a=fgetc(fp);
//		 if(a!=' ')
//		  for(i=0;i<16;i++)
//		  {
//		  	if(a==CH[i].num[0])
//		  	{
//			s=i;
//		  	break;
//			}
//		  }
		  CH[s*16+m].frequent++;
		  length++; 
      }
          fclose(fp);
	      for(i=0;i<M;i++)
      {   CH[i].weight=CH[i].frequent*100/length;
         // printf("%c%c: ",CH[i].num[0],CH[i].num[1]);
          //printf("%d ", CH[i].frequent);
         //printf("%d\n",CH[i].weight);
       }
        j=0;
         for(i=0;i<M;i++)
       {
           if(CH[i].weight!=0)
           {
               HS[j].n[0]=CH[i].num[0];
//               HS[j].n[1]=CH[i].num[1];
               HS[j].weight=CH[i].weight;
          // printf("%c%c: ",HS[j].n[0],HS[j].n[1]);
          //printf("%d\n",HS[j].weight);
            j++; 
          }
       }
      // printf("%d%d",j,M);
       return j;
}
void Select(HuffmanTree HT, int n, int *s1, int *s2)
{   int i,min1,min2;
    *s1 = 0;
    for(i = 1; i <= n; i++)
 {
  if((HT+i)->parent == -1)
    {
      min1=(HT+i)->weight;
      *s1=i;
      break;
    }
   }
    for(i = 1; i <= n; i++)
 {
  if((HT+i)->parent == -1 && (HT+i)->weight < min1)
    {
      min1=(HT+i)->weight;
      *s1=i;
    }
   }
   for(i = 1; i <= n; i++)
 {
  if((HT+i)->parent == -1&&i!=*s1)
    {
      min2=(HT+i)->weight;
      *s2=i;
      break;
    }
   }
   for(i = 1; i <= n&&i!=*s1; i++)
 {
  if((HT+i)->parent == -1 && (HT+i)->weight < min2)
    {
      min2=(HT+i)->weight;
      *s2=i;
    }
   }
  // printf("%d %d\n",*s1,*s2);
}
/*void Select2(HuffmanTree HT, int n, int *s1, int *s2)
{
	int m1=100000,m2=100000;
	int i,j;
	for(j=1;i<=n;j++)
	{
		if((HT+i)->weight<m1&&(HT+i)->parent==-1)
		{
			m2=m1;
			*s2=*s1;
			m1=(HT+i)->weight;
			*s1=j;
		}
		else if((HT+i)->weight<m2&&(HT+i)->parent==-1)
		{
			m2=(HT+i)->weight;
			*s2=j;
		}
	}
//	printf("%d %d\n",*s1,*s2);
}*/ 
void Hufcoding(HuffmanTree HT, struct HTNodes HS[], int n) //建立二叉树
{
    int m,i,s1,s2,sum;
    m=2*n-1;
    for(i=1;i<=n;i++)
    {
        (HT+i)->weight=HS[i-1].weight;
        (HT+i)->rchild=-1;
        (HT+i)->lchild=-1;
        (HT+i)->parent=-1;
    }
    for(i=n+1;i<=m;i++)
    {
        (HT+i)->weight=-1;
        (HT+i)->lchild=-1;
        (HT+i)->rchild=-1;
        (HT+i)->parent=-1;
    }
    for(i=1;i<=n-1;i++)
      {   Select(HT,n+i-1,&s1,&s2);
          sum=(HT+s1)->weight+(HT+s2)->weight;
          (HT+n+i)->weight=sum;
          (HT+s1)->parent=(HT+s2)->parent=n+i;
          (HT+n+i)->lchild=s1;
          (HT+n+i)->rchild=s2;
         }
}
void HuftreeCode(HuffmanTree HT, CodeType cd[], int n)
{
    int i,f,k,c,temp[N],sign;
    for(i=1;i<=n;i++)
    {
        c=0; sign=i;
        for(f=(HT+i)->parent;f!=-1;f=(HT+f)->parent)
        {
            if((HT+f)->lchild==sign)
               temp[c++]='0';
        else
              temp[c++]='1';
              sign=f;
        }
        cd[i].code=(char *)malloc(c+1);
        cd[i].code[c--] = '\0';
          k = 0;
       while(c >= 0)
      cd[i].code[k++] = temp[c--];
      cd[i].length = k;
 }
}
void Printfcode(struct HTNodes HS[],HuffmanTree HT,CodeType cd[],int j)
{  int i,sum=0; 
	    for(i = 1; i <= j; i++)
     {
      printf("%c%c 's HuftreeCode is:",HS[i-1].n[0],HS[i-1].n[1]);
      printf("%s\n",cd[i].code);
     }
    printf("L=");
    for(i=1;i<=j;i++)
    {    printf("%d*%d+",(HT+i)->weight,cd[i].length);
         sum=sum+(HT+i)->weight*cd[i].length;
    }
    printf("=%.2f",sum*0.01);
}
void WriteFile(CodeType cd[],int j,struct HTNodes HS[])
{
	int i;
	  FILE *fp;
     fp=fopen("huffmancode.txt","w");
     for(i=0;i<j;i++)
     {fwrite(HS[i].n, sizeof(char),strlen(HS[i].n), fp);
    // fprintf(fp,": ");
     fwrite(cd[i+1].code, sizeof(char), strlen(cd[i+1].code), fp);
     fprintf(fp,"\n");
	 }
	 fclose(fp);
}
void Picturecode(CodeType cd[],int j,struct HTNodes HS[])
{
	int i;
	FILE *fp1,*fp2;
	fp1=fopen("picture.txt","r");
	fp2=fopen("picturecode(huffman).txt","w");
	char a,b,c[2];
	while(!feof(fp1))
	{
		a=fgetc(fp1);
		b=fgetc(fp1);
		c[0]=a;c[1]=b;
		for(i=0;i<j;i++)
	{	if(c[0]==HS[i].n[0]&&c[1]==HS[i].n[1])
		{fwrite(cd[i+1].code,sizeof(char),strlen(cd[i+1].code),fp2);
	    break; 
		}
    }
    }
     fclose(fp1);
     fclose(fp2);
}
int main()
{   int i,j,sum=0,op;
    char k[2];
    printf("please push OK to continue:\n");
    scanf("%s",k);
    j=getweight();
    HuffmanTree HT;
    HT=(HuffmanTree )malloc(N*sizeof(HTNode));
    CodeType cd[N];
    Hufcoding(HT,HS,j);
    HuftreeCode(HT,cd,j);
    WriteFile(cd,j,HS);
    Picturecode(cd,j,HS);
//	Printfcode(HS,HT,cd,j);	 
    printf("The texts are OK,\n");
    printf("if you want to check the huffmantree,please push 1,else push 2 to end\n");
    scanf("%d",&op);
    switch(op)
    {
    	case 1: Printfcode(HS,HT,cd,j);
			break; 
    	case 2:    break;
    }
}
