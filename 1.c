#include <stdio.h>       
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define N 100//размер таблицы
int NUM=50;//глобальная переменная для автоматического ввода значений в таблицу
char name[]="table.txt";//имя файла
int key=0;//ключ для каждой записи

struct date{
  int dd,mm,yy;
};

void getDate(struct date A)
{
printf("дата последнего изменения - ");
printf(" %d,",A.dd);
printf(" %d,",A.mm);
printf(" %d\n",A.yy);
}

struct account{
  int key;
  char surname [20];
  int accNum;
  int accAmount;
  struct date dateLastChange;
};

struct account setAcc(struct account *A)//ввод самой записи
{
  int day=0, month=0, year=0;
  A->key=++key;
  printf("Введите фамилию ");
  //scanf("%c",stdin);
  //fgets(A->surname, sizeof(A->surname), stdin);
  gets(A->surname);
  printf("Введите номер счета ");
  
  scanf("%d", &A->accNum);
  printf("Введите сумму на счете ");
  scanf("%d", &A->accAmount);
  while(1)
  {
     printf("Введите последнюю дату изменения(день, месяц, год):\n");
  scanf("%d", &day);
  scanf("%d", &month);
  scanf("%d", &year);
  if(day<31&&month<12&&year>1900&&day>0&&month>0)
  {
    A->dateLastChange.dd=day;
    A->dateLastChange.mm=month;
    A->dateLastChange.yy=year;
    scanf("%c",stdin);
    break;
  }
  else 
    printf("неверно введена дата, введите дату еще раз\n");
  }
}

void getAcc(struct account A)
{
  printf("Номер записи %d\n", A.key);
  printf("Фамилия %s\n", A.surname);
  printf("номер счета %d\n", A.accNum);
  printf("сумма на счете %d\n", A.accAmount);
  getDate(A.dateLastChange);
  printf("\n");
}

struct table
{
  struct account TBL[N];
  int nn;
};


void addAccount(struct table *tbl){//вызов функции добавления в таблицу
  if(tbl->nn!=N){setAcc(&tbl->TBL[tbl->nn]);tbl->nn++;}
  /*if(tbl->nn!=N){
    struct account A={++key,"asd",NUM-=20,111111,{11,10,2000+NUM}};
    tbl->TBL[tbl->nn]=A;
    tbl->nn++;
  }*/

}


int lenNum(int num)
{
 int n=num,k=0;
    while(n)
    {
        k++;
        n=n/10;
    }
    return k;
}

void WriteToFile(struct table tbl)//запись в файл
{
    printf("\n");

  FILE *fp;
  if((fp=fopen(name,"w"))==NULL){
    printf("не далось открыть файл\n");
    return;
  }
  char *p;
  for(int i=0;i<tbl.nn;i++)
  {
    int e=strlen(tbl.TBL[i].surname)+sizeof(char)*(lenNum(tbl.TBL[i].key)+lenNum(tbl.TBL[i].accNum)+lenNum(tbl.TBL[i].accAmount)+lenNum(tbl.TBL[i].dateLastChange.dd)+  lenNum(tbl.TBL[i].dateLastChange.mm)+lenNum(tbl.TBL[i].dateLastChange.yy));
  p=malloc(strlen(tbl.TBL[i].surname)+sizeof(char)*(7+lenNum(tbl.TBL[i].key)+lenNum(tbl.TBL[i].accNum)+lenNum(tbl.TBL[i].accAmount)+lenNum(tbl.TBL[i].dateLastChange.dd)+  lenNum(tbl.TBL[i].dateLastChange.mm)+lenNum(tbl.TBL[i].dateLastChange.yy)));
  sprintf(p,"%d %s %d %d %d %d %d\n",tbl.TBL[i].key,tbl.TBL[i].surname,tbl.TBL[i].accNum,tbl.TBL[i].accAmount,tbl.TBL[i].dateLastChange.dd,tbl.TBL[i].dateLastChange.mm,tbl.TBL[i].dateLastChange.yy);
  e=strlen(p);
  if(fputs(p, fp)<0)
  {
    printf("Не удалось записать в файл");
    return;
  }
  }
  fclose(fp);
  printf("Таблица сохранениа в файл\n");
  printf("\n");

}

void WriteToFile2(struct table tbl)//запись в файл
{
    printf("\n");

  FILE *fp;
  if((fp=fopen(name,"w"))==NULL){
    printf("не далось открыть файл\n");
    return;
  }
  char *p;
  for(int i=0;i<tbl.nn;i++)
  {
  p=malloc(strlen(tbl.TBL[i].surname)+sizeof(char)*(lenNum(tbl.TBL[i].accNum)+
  lenNum(tbl.TBL[i].accAmount)+lenNum(tbl.TBL[i].dateLastChange.dd)+
  lenNum(tbl.TBL[i].dateLastChange.mm)+lenNum(tbl.TBL[i].dateLastChange.yy)));
  sprintf(p,"%s %d %d %d %d %d\n",
   tbl.TBL[i].surname,tbl.TBL[i].accNum,tbl.TBL[i].accAmount,tbl.TBL[i].dateLastChange.dd,
   tbl.TBL[i].dateLastChange.mm,tbl.TBL[i].dateLastChange.yy);
  fputs(p, fp);
  }
  fclose(fp);
  printf("Таблица сохранениа в файл\n");
    printf("\n");

}


char **SplittingString(char **p, char str[])//деление 1 большой строки из файла на несколько маленьких
{
  int k=0, j=0;
  char a[]={""};
  char buff[strlen(str)];
  p=(char**)malloc(sizeof(char*)*7);
  for (int i=0;i<strlen(str);i++)
  {
    if(str[i]!=' ')
      buff[i-k]=str[i];
    else
    {
      k=i+1;
      p[j]=(char*)malloc(sizeof(char)*strlen(buff));
      strcat(p[j],buff);
      j++;
      memset(buff,0,strlen(buff));
    }
  }
  p[j]=(char*)malloc(sizeof(char)*strlen(buff));
  strcat(p[j],buff);
  memset(buff,0,strlen(buff));
  return p;
}

void ReadToFile(struct table *tbl)//чтение из файла
{
    printf("\n");

  FILE *fp;
  char **p;
  int i=0;
  if((fp=fopen(name,"r"))==NULL){
    printf("не далось открыть файл\n");
    return;
  }
  char str[50];
  while(1)
  {
  fgets(str, 50, fp);
  if(feof(fp)!=0)
    break;

  p=SplittingString(p,str);
  key++;
  tbl->TBL[i].key=atoi(p[0]);
  strcpy(tbl->TBL[i].surname,p[1]);
  tbl->TBL[i].accNum=atoi(p[2]);
  tbl->TBL[i].accAmount=atoi(p[3]);
  tbl->TBL[i].dateLastChange.dd=atoi(p[4]);
  tbl->TBL[i].dateLastChange.mm=atoi(p[5]);
  tbl->TBL[i].dateLastChange.yy=atoi(p[6]);
  i++;
  }
  tbl->nn=i;
  fclose(fp);
  printf("Таблица прочитана из файла\n");
    printf("\n");

}

void getTable(struct table tbl)//печать таблицы
{
    printf("\n");
  if(tbl.nn==0)
  {
    printf("Таблица пуста\n");
    return;
  }
  for(int i=0;i<tbl.nn;i++)
    getAcc(tbl.TBL[i]);
}

int compKey(const void *a,const void *b){//сортировка по сумме на счете
  return ((struct account*)a)->key - ((struct account*)b)->key; 
}

int strcomp(const void * a, const void * b) {//сортировка фамилии
    return strcmp(((struct account*)a)->surname, ((struct account*)b)->surname);
}

int compNum(const void *a,const void *b){//сортировка по номеру счета
  return ((struct account*)a)->accNum - ((struct account*)b)->accNum; 
}

int compAmount(const void *a,const void *b){//сортировка по сумме на счете
  return ((struct account*)a)->accAmount - ((struct account*)b)->accAmount; 
}

int compDate(const void *a,const void *b){//сортировка по дате
  int ad;
    if ( ((struct account*)a)->dateLastChange.yy == ((struct account*)b)->dateLastChange.yy ) {
        if ( ((struct account*)a)->dateLastChange.mm == ((struct account*)b)->dateLastChange.mm )
            return ((struct account*)a)->dateLastChange.dd - ((struct account*)b)->dateLastChange.dd;
        else
            return ((struct account*)a)->dateLastChange.mm - ((struct account*)b)->dateLastChange.mm;
    }
    else
        return ((struct account*)a)->dateLastChange.yy - ((struct account*)b)->dateLastChange.yy;
}

void SortTable(struct table *tbl, int var)//функция выбора сортировки
{
  struct account tmp;
  switch(var)
  {
     case 1:
    {
      qsort(tbl->TBL, tbl->nn,sizeof(struct account),(int (*) (const void *, const void*)) compKey);
    } break;
    case 2:
    {
      qsort(tbl->TBL, tbl->nn,sizeof(struct account),(int (*) (const void *, const void*)) strcomp);
    } break;
    case 3:
    {
      qsort(tbl->TBL, tbl->nn,sizeof(struct account),(int (*) (const void *, const void*)) compNum);
    } break;
    case 4:
    {
      qsort(tbl->TBL, tbl->nn,sizeof(struct account),(int (*) (const void *, const void*)) compAmount);
      
    } break;
    case 5:
    {
      qsort(tbl->TBL, tbl->nn,sizeof(struct account),(int (*) (const void *, const void*)) compDate);
    } break;
  }   
  printf("Таблица отсортирована\n");
    printf("\n");

}

struct account EditRecord(struct account *A)//функция редактирования
{
    printf("\n");

   int day=0, month=0, year=0;
  printf("Введите новую фамилию (старая - %s): ",A->surname);
  gets(A->surname);
  printf("Введите новый номер счета (старый %d): ", A->accNum);
  scanf("%d", &A->accNum);
  printf("Введите новую сумму на счете (старое значение %d): ",A->accAmount);
  scanf("%d", &A->accAmount);
  while(1)
  {
     printf("Введите последнюю дату изменения(день, месяц, год) (старая дата %d, %d, %d):\n",
      A->dateLastChange.dd,  A->dateLastChange.mm, A->dateLastChange.yy);
  scanf("%d", &day);
  scanf("%d", &month);
  scanf("%d", &year);
  if(day<31&&month<12&&year>1900&&day>0&&month>0)
  {
    A->dateLastChange.dd=day;
    A->dateLastChange.mm=month;
    A->dateLastChange.yy=year;
    scanf("%c",stdin);
    break;
  }
  else 
    printf("неверно введена дата, введите дату еще раз/n");
  }
    printf("\n");

}

void MoveTbl(struct table *tbl, int n)//смешение элементов массива
{
  for(int i=n;i<tbl->nn;i++)
    tbl->TBL[i]=tbl->TBL[i+1];
}

void DeleteRecord(struct table *tbl, int k)
{
    printf("\n");

  for(int i=0;i<tbl->nn;i++)
  {
    if(tbl->TBL[i].key==k)
    {
      MoveTbl(tbl,i);
      tbl->nn-=1;
      return;
    }
  }
  printf("Записи с заданным ключом не существует\n");
    printf("\n");

}

void Edit(struct table *tbl, int k)
{
   for(int i=0;i<tbl->nn;i++)
  {
    if(tbl->TBL[i].key==k)
    {
      scanf("%c", stdin);
      EditRecord(&tbl->TBL[i]);
      return;
    }
  }
  printf("Записи с заданным ключом не существует\n");
    printf("\n");

}


int main(void)     
{    
  struct table TABLE;
  TABLE.nn=0;
  char var;
  int sort=0, numEdit=0;
  while(1)
  {
    printf("1-Ввод записи с клавиатуры, 2-Сохранить на файл, 3-Загрузить из файла, 4-Просмотр таблицы, 5-Сортировка таблицы, 6-Удаление, 7-Редактирование, q-Выход\n");
     scanf("%c",&var);
     switch (var)
     {
     case '1':
      scanf("%c", stdin);
      addAccount(&TABLE);
       break;

     case '2':
      WriteToFile(TABLE);
      scanf("%c", stdin);
       break;

       case '3':
      ReadToFile(&TABLE);
      scanf("%c", stdin);
       break;

       case '4':
      getTable(TABLE);
      scanf("%c", stdin);
       break;

       case '5':
       {
         printf("1-Сортировка по ключу, 2-по фамилии, 3-по номеру счета, 4-по сумме на счете, 5-по дате\n");
          scanf("%d", &sort);
         SortTable(&TABLE,sort);
         scanf("%c", stdin);
       }
       break;

       case '6':
     printf("Введите ключ записи\n");
         scanf("%d", &numEdit);
         DeleteRecord(&TABLE,numEdit);
         scanf("%c", stdin);
       break;

       case '7':
       {
         printf("Введите ключ записи\n");
         scanf("%d", &numEdit);
         Edit(&TABLE, numEdit);
       }
       break;

       case 'q':
       exit(0);
       break;

     default:
       break;
     }
  }
}     
