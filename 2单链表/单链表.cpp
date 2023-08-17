#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h> 
#include<windows.h>

/*************************预定义*************************/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; 		//数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode{  		//单链表（链式结构）结点的定义
      ElemType data;
      struct LNode *next;
      char name[30];
}LNode,*LinkList;
/********************************************************/

/*************************函数表*************************/
status InitList(LinkList &L);
status DestroyList(LinkList &L);
status ClearList(LinkList &L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType &e);
status LocateElem(LinkList L,ElemType e); 
status PriorElem(LinkList L,ElemType e,ElemType &pre); 
status NextElem(LinkList L,ElemType e,ElemType &next);
status ListInsert(LinkList &L,int i,ElemType e);
status ListDelete(LinkList &L,int i,ElemType &e);
status ListTraverse(LinkList L);
status SaveList(LinkList L,char FileName[]); 
status LoadList(LinkList &L,char FileName[]);
status ReverseList(LinkList &L);
status SortList(LinkList &L);
status RemoveNthFromEnd(LinkList &L,int n);
/********************************************************/

/*************************主函数*************************/
int main(){
	/****************************************************************/
	/*						   程序框设置							*/
	/****************************************************************/ 
	system("mode con cols=82 lines=31 ");	//更改程序框大小 
	system("title 线性表：链式存储结构");	//更改程序框名称
	system("color 1F");						//背景蓝色，字体亮白色
	/****************************************************************/
	/*						    初始化								*/
	/****************************************************************/
	int op=1;			//用户选择选项
	int lp=1;			//操作线性表下标指针 
	int val,pos;		//获取元素用，val:元素的值，pos:元素位置
	ElemType pre,next;	//获取前驱/后继用，pre:前驱，next:后继 
	ElemType ins;		//插入元素用，存储插入元素的值 
	char filename[50];	//文件名 
	LinkList list[11];	//多线性表管理
	char listname[30];	//线性表名 
	for( int i=0 ; i<=10 ; i++ )
		list[i]=NULL;
	int listlength=0;	//线性表数目 
	int cnt=0;			//记录操作次数
	/****************************************************************/
	/*						   菜单主体 							*/
	/****************************************************************/
	while(op){
		system("cls");
		printf("\n\n");
		printf("	  \t\t\t线性表顺序结构菜单\t\t\n\n");
		printf(" 可在最多10个链表进行多表操作，线性表均未初始化，默认对编号为1的线性表操作\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf(" *1. 初始化线性表         \t\t7.  查找元素\t\t\t\t*\n");
		printf(" *2. 摧毁线性表       \t\t\t8.  获取前驱元素\t\t\t*\n");
		printf(" *3. 清空线性表         \t\t9.  获取后继元素 \t\t\t*\n");
		printf(" *4. 线性表判空         \t\t10. 插入元素\t\t\t\t*\n");
		printf(" *5. 线性表长度        \t\t\t11. 删除元素\t\t\t\t*\n");
		printf(" *6. 获取元素           \t\t12. 遍历线性表\t\t\t\t*\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf(" *13.线性表存储          \t\t14. 线性表读取\t\t\t\t*\n");
		printf(" *15.链表翻转            \t\t16. 删除链表倒数第n结点\t\t\t*\n");
		printf(" *17.链表排序            \t\t18. 添加线性表\t\t\t\t*\n");
		printf(" *19.移除线性表          \t\t20. 选择要操作的线性表\t\t\t*\n\n");
		printf(" *0. 退出\t\t\t\n");
		printf(" ----------------------------------------------------------------power by 严浩洋\n");
		printf("当前操作的线性表：线性表%d\n\n",lp);
		printf("请输入数字0~20以选择你的操作:");
		scanf("%d",&op);	//选择op的值,用于switch
		printf("\n");
		switch(op){
			case 0:
				break;
			case 1:
				//初始化线性表
				if( list[lp] )
					printf("创建失败！线性表已存在！");
				else{
					InitList(list[lp]);
					listlength++;
					printf("创建成功！");
				} 
				break;
			case 2:
				//销毁线性表
				if( !list[lp] )
					printf("销毁失败！线性表不存在！");
				else{
					DestroyList(list[lp]);
					printf("销毁成功！");
					listlength--;
				}
				break;
			case 3:
				//清空线性表 
				if( !list[lp] )
					printf("清空失败！线性表不存在！");
				else{
					ClearList(list[lp]);
					printf("线性表已清空！");
				}
				break;
			case 4:
				//线性表判空
				if( !list[lp] )
					printf("线性表不存在！无法判断！");
				else{
					if( ListEmpty(list[lp])==TRUE )
						printf("线性表为空！");
					else
						printf("线性表不为空！");
				} 
				break;
			case 5:
				//线性表长度
				if( !list[lp] )
					printf("线性表不存在！无法判断！");
				else
					printf("线性表长度为：%d",ListLength(list[lp]));
				break;
			case 6:
				//获取元素
				if( !list[lp] )
					printf("线性表不存在！无法获取！");
				else{
					printf("当前正在进行获取元素操作，请输入想要查询的元素在线性表中的逻辑次序：");
					scanf("%d",&pos);
					if( GetElem(list[lp],pos,val)==ERROR )
						printf("\n获取失败，请检查下标值是否合法！");
					else
						printf("\n您要查询的元素为：%d",val);
				}
				break;
			case 7:
				//查找元素
				if( !list[lp] )
					printf("线性表不存在！无法查找！");
				else{
					printf("当前正在进行查找元素操作，请输入想要查询的值："); 
					scanf("%d",&val);
					if( (pos=LocateElem(list[lp],val))==ERROR )
						printf("\n查找失败！请检查所查元素是否在线性表内！");
					else
						printf("您要找的元素在表中第%d个",pos);
				}
				break;
			case 8:
				//获取前驱元素
				if( !list[lp] )
					printf("线性表不存在！无法获取！");
				else{
					printf("当前正在进行获取前驱元素操作，请输入想要查询前驱的元素：");
					scanf("%d",&val);
					if( PriorElem(list[lp],val,pre)==ERROR )
						printf("\n获取失败！请检查您要查询的元素是否在表中或为表头！");
					else
						printf("\n您要找的%d的前驱元素为：%d",val,pre);
				}
				break;
			case 9:
				//获取后继元素
				if( !list[lp] )
					printf("线性表不存在！无法获取！");
				else{
					printf("当前正在进行获取后继元素操作，请输入想要查询后继的元素：");
					scanf("%d",&val);
					if( NextElem(list[lp],val,next)==ERROR )
						printf("\n获取失败！请检查您要查询的元素是否在表中或为表尾！");
					else
						printf("\n您要找的%d的后继元素为：%d",val,next);
				}
				break;
			case 10:
				//插入元素
				if( !list[lp] )
					printf("线性表不存在！无法插入！");
				else{
					int num;		//插入元素个数 
					printf("当前正在进行插入元素操作，请输入要插入元素的个数：");
					scanf("%d",&num);
					while( num ){
						printf("\n当前正在进行插入元素操作，请输入想要插入元素的逻辑次序和元素值\n");
						printf("逻辑次序：");
						scanf("%d",&pos);
						printf("元素值：");
						scanf("%d",&ins); 
						if( ListInsert(list[lp],pos,ins)==ERROR )
							printf("\n插入失败！请检查下标值是否合法\n");
						else
							printf("\n插入成功！\n");
						num--;
					}
				}
				break;
			case 11:
				//删除元素
				if( !list[lp] )
					printf("线性表不存在！无法删除！");
				else{
					printf("当前正在进行删除元素操作，请输入想要删除元素的逻辑次序：");
					scanf("%d",&pos);
					if( ListDelete(list[lp],pos,val)==ERROR )
						printf("\n删除失败！请检查下标值是否合法!");
					else
						printf("\n删除成功！您删除的元素值为：%d",val);
				}
				break;
			case 12:
				//遍历线性表
				if( !list[lp] )
					printf("线性表不存在！无法遍历！");
				else{
					printf("线性表%d的元素依次是：\n",lp);
					if( list[lp]->name )
						printf("%s ",list[lp]->name);
					ListTraverse(list[lp]);
				} 
				break;
			case 13:
				//线性表存储
				if( !list[lp] )
					printf("线性表不存在！无法存储！");
				else{
					printf("当前正在进行线性表存储操作，请输入想要生成的文件名：\n");
					scanf("%s",filename);
					SaveList(list[lp],filename);
					printf("\n存储成功！");
				}
				break;
			case 14:
				//线性表读取
				if( list[lp] )
					printf("线性表已存在！无法读取！");
				else{
					printf("当前正在进行线性表读取操作，请输入想要读取的文件名(包括扩展名)：\n");
					scanf("%s",filename);
					if( LoadList(list[lp],filename)==ERROR )
						printf("\n读取失败！请检查文件是否存在！");
					else{
						printf("\n读取成功！");
						listlength++;
					}
				} 
				break;
			case 15:
				//翻转链表
				if( !list[lp] )
					printf("线性表不存在！无法翻转！");
				else{
					ReverseList(list[lp]);
					printf("翻转成功！");
				}
				break; 
			case 16:
				//删除倒数第n个元素
				if( !list[lp] )
					printf("线性表不存在！无法读取！");
				else{
					printf("当前正在进行删除倒数第n个元素的操作，请输入n值：");
					scanf("%d",&val);
					if( RemoveNthFromEnd(list[lp],val)==ERROR )
						printf("\n删除失败！请检查下标是否合法！");
					else
						printf("\n删除成功！");
				} 
				break;
			case 17:
				//链表排序
				if( !list[lp] )
					printf("线性表不存在！无法排序！");
				else{
					SortList(list[lp]);
					printf("排序成功！");
				} 
				break;
			case 18:
				//添加线性表
				if( listlength>=10 )
					printf("当前线性表数目已超出上限！");
				else{
					printf("当前正在进行添加线性表的操作，请输入想要建立新表的编号(1~10)：\n");
					scanf("%d",&pos);
					if( pos<1||pos>10 )
						printf("\n添加失败！请检查下标是否越界！");
					else if( list[pos] )
						printf("\n线性表已存在！无法添加！");
					else{
						InitList(list[pos]);
						listlength++;
						printf("\n添加成功！该表已初始化！请输入表的名称：\n");
						scanf("%s",list[pos]->name);
					}
				}
				break;
			case 19:
				//移除线性表
				if( listlength==0 )
					printf("当前没有线性表！无法移除！");
				else{
					printf("当前正在进行移除线性表的操作，请输入您要移除的线性表的编号(1~10)：\n");
					scanf("%d",&pos);
					if( pos<1||pos>10 )
						printf("\n移除失败！请检查下标是否合法！");
					else if( !list[pos] )
						printf("\n线性表不存在！无法移除！");
					else{
						DestroyList(list[pos]);
						printf("\n移除成功！");
						if( pos==lp ){
							val=0;
							for( int i=1 ; i<=10 ; i++ )
								if( list[i]!=NULL ){
									val=i;
									break;
								}
							if( val!=0 ){
								printf("\n\n由于您移除了当前操作的线性表%d，下次操作默认对已初始化的线性表%d进行",lp,val);
								lp=val;
							}
							else
								printf("\n\n注意：您移除了当前操作的线性表%d，且当前无可用的线性表！",lp);
						}
						listlength--;
					}
				} 
				break;
			case 20:
				//选择线性表
				printf("当前正在进行选择操作线性表的操作，请输入您要操作的线性表的编号：\n"); 
				scanf("%d",&pos);
				if( pos<1||pos>10 )
					printf("\n选择失败！请检查下标是否合法！");
				else if( list[pos]==NULL )
					printf("\n选择失败！线性表不存在！"); 
				else{
					lp=pos;
					printf("\n选择成功！即将对该表进行操作！");
				}
				break;
		}
		if( op!=0 ){
			printf("\n\n按任意键继续下一个操作\n\n");
			system("pause");
			cnt++;
		}
	}
	printf("谢谢使用！您本次共进行了%d次操作！欢迎下次再来！\n",cnt);
	Sleep(2000);
	return 0;
}
/********************************************************/


/********************************************************
函数名：  InitList
初始条件：线性表L不存在 
函数功能：如果线性表L不存在，操作结果是构造一个空的线性表，
返回OK，否则返回INFEASIBLE。 
返回类型：status 
********************************************************/
status InitList(LinkList &L)
{
    if( L )					//线性表已存在 
        return INFEASIBLE;	//不可行 
    else{
        L=(LinkList)malloc(sizeof(LNode));
        L->next=NULL;
    }
    return OK;
}

/********************************************************
函数名：  DestroyList
初始条件：线性表L已存在 
函数功能：如果线性表L存在，该操作释放线性表的空间，使线性
表成为未初始化状态，返回OK；否则对于一个未初始的线性表，
是不能进行销毁操作的，返回INFEASIBLE。
返回类型：status 
********************************************************/
status DestroyList(LinkList &L)
{
    if( !L )				//线性表不存在 
        return INFEASIBLE;	//不可行 
    else{
        LinkList t=L;		//遍历指针 
        while(t){
            LinkList a=t;	//存储指针，用于模拟移位 
            a=t->next;
            free(t);
            t=a;
        }
        L=NULL;
    }
    return OK;
}

/********************************************************
函数名：  ClearList
初始条件：线性表L已存在 
函数功能：若线性表L不存在，清空L，释放所有数据元素的结点，
返回OK；若线性表L不存在，则返回INFEASIBLE。
返回类型：status 
********************************************************/
status ClearList(LinkList &L)
{
    if( !L )				//线性表不存在 
        return INFEASIBLE;	//不可行 
    else{
        LinkList t=L->next;	//遍历指针 
        while(t){
            LinkList a=t->next;	//模拟移位指针 
            free(t);
            t=a;
        }
        L->next=NULL;
    }
    return OK;
}

/********************************************************
函数名：  ListEmpty
初始条件：线性表L已存在 
函数功能：若线性表L不存在，则返回INFEASIBLE；若线性表L长
度为0，则返回TRUE；不为0则返回FALSE。
返回类型：status 
********************************************************/
status ListEmpty(LinkList L)
{
    if( !L )				//线性表不存在 
        return INFEASIBLE;	//不可行 
    else{
        if( L->next )		//表头下一元素存在。即不空 
            return FALSE;
        else				//线性表为空 
            return TRUE;
    }
}

/********************************************************
函数名：  ListLength
初始条件：线性表L已存在 
函数功能：若线性表L不存在，则返回INFEASIBLE；否则返回线性
表L的长度。
返回类型：int
********************************************************/
int ListLength(LinkList L)
{
    if( !L )				//线性表不存在 
        return INFEASIBLE;	//不可行 
    else{
        LinkList t=L->next;	//遍历指针 
        int cnt;
        while(t){
            cnt++;
            t=t->next;
        }
        return cnt;
    }
}

/********************************************************
函数名：  GetElem
初始条件：线性表L已存在 
函数功能：若线性表L不存在，返回INFEASIBLE；若i<1或者i超过
线性表L的长度，则返回ERROR；若获取成功，则将值赋给e，并返
回OK。
返回类型：status
********************************************************/
status GetElem(LinkList L,int i,ElemType &e)
{
    if( !L )				//线性表不存在 
        return INFEASIBLE;	//不可行 
    if( i<1 )				//下标向下溢出 
        return ERROR;
    LinkList t=L;			//遍历指针 
    for( int j=0 ; j<i ; j++ ){
        t=t->next;
        if( !t )			//下标向上溢出 
            return ERROR;
    }
    e=t->data;
    return OK;
}

/********************************************************
函数名：  LocateElem
初始条件：线性表L已存在 
函数功能：若线性表L不存在，返回INFEASIBLE；若没有找到指定
的元素e，则查找失败，返回ERROR；若查找成功，则返回元素逻
辑序号i。
返回类型：status
********************************************************/
status LocateElem(LinkList L,ElemType e)
{
    if( !L )				//线性表不存在 
        return INFEASIBLE;	//不可行 
    LinkList t=L->next;		//遍历指针 
    int cnt=0;
    while(t){
        cnt++;
        if( t->data==e )
            return cnt;
        t=t->next;
    }
    return ERROR;
}

/********************************************************
函数名：  PriorElem
初始条件：线性表L已存在 
函数功能：若线性表L不存在，返回INFEASIBLE；若没有找到指定
元素e的前驱，则查找失败，返回ERROR；若查找成功，则将值赋
给pre，并返回OK。
返回类型：status
********************************************************/
status PriorElem(LinkList L,ElemType e,ElemType &pre)
{
    if( !L )				//线性表不存在 
        return INFEASIBLE;	//不可行 
    LinkList t=L->next;		//遍历指针 
    if( t->data==e )
    	return ERROR;
    while(t){
        if( t->next&&t->next->data==e ){	//第一个元素无前驱 
            pre=t->data;
            return OK;
        }
        t=t->next;
    }
    return ERROR;
}

/********************************************************
函数名：  NextElem
初始条件：线性表L已存在 
函数功能：若线性表L不存在，返回INFEASIBLE；若没有找到指定
元素e的后继，则查找失败，返回ERROR；若查找成功，则将值赋
给next，并返回OK。
返回类型：status
********************************************************/
status NextElem(LinkList L,ElemType e,ElemType &next)
{
    if( !L )				//线性表不存在 
        return INFEASIBLE;	//不可行 
    LinkList t=L->next;		//遍历指针 
    while(t->next){			//最后一个元素无后继 
        if( t->data==e ){
            next=t->next->data;
            return OK;
        }
        t=t->next;
    }
    return ERROR;
}

/********************************************************
函数名：  ListInsert
初始条件：线性表L已存在 
函数功能：如果线性表L不存在，返回INFEASIBLE；否则在线性表
L的第i个元素前插入新的元素e，插入成功返回OK，失败返回ERROR。
返回类型：status
********************************************************/
status ListInsert(LinkList &L,int i,ElemType e)
{
    if( !L )				//线性表不存在 
        return INFEASIBLE;	//不可行 
    LinkList t=L;			//遍历指针 
    if( i<1 )				//下标向下溢出 
        return ERROR;
    for( int j=1 ; j<i ; j++ ){
        if( !t )			//下标向上溢出 
            return ERROR;
        t=t->next;
    }
    if( !t )				//特殊判断i==length+2的情况 
        return ERROR;
    if( !(t->next) ){		//特殊判断在结尾插入元素 
        LinkList insert;
        insert=(LinkList)malloc(sizeof(LNode));
        insert->data=e;
        t->next=insert;
        insert->next=NULL;
        return OK;
    }
    LinkList a=t->next,insert;	//普通插入 
    insert=(LinkList)malloc(sizeof(LNode));
    insert->data=e;
    t->next=insert;insert->next=a;
    return OK;
}

/********************************************************
函数名：  ListDelete
初始条件：线性表L已存在 
函数功能：若线性表L不存在，返回INFEASIBLE；否则删除线性表
L的第i个元素，若删除成功则将删除的值赋给e并返回OK，若删除
失败则返回ERROR。
返回类型：status
********************************************************/
status ListDelete(LinkList &L,int i,ElemType &e)
{
    if( !L )				//线性表不存在 
        return INFEASIBLE;	//不可行 
    LinkList t=L;			//遍历指针 
    if( i<1 )				//下标向下溢出 
        return ERROR;
    for( int j=1 ; j<i ; j++ ){
        if(!t)				//下标向上溢出 
            return ERROR;
        t=t->next;
    }
    if( !(t->next) )		//特殊判断i==length+1 
        return ERROR;
    LinkList a=t->next->next;	//存储删除后的下一节点 
    e=t->next->data;
    free(t->next);
    t->next=a;
    return OK;
}

/********************************************************
函数名：  ListTraverse
初始条件：线性表L已存在 
函数功能：若线性表L不存在，返回INFEASIBLE；否则输出线性表
的每一个元素，并返回OK。
返回类型：status
********************************************************/
status ListTraverse(LinkList L)
{
    if( !L )				//线性表不存在 
        return INFEASIBLE;	//不可行 
    LinkList t=L->next;
    while(t){
        printf("%d",t->data);
        if( t->next )
            printf(" ");	//迭代 
        t=t->next;
    }
    return OK;
}

/********************************************************
函数名：  SaveList
初始条件：线性表L已存在 
函数功能：如果线性表L不存在，返回INFEASIBLE；否则将线性表
L的全部元素写入到文件名为FileName的文件中，返回OK
返回类型：status
********************************************************/
status SaveList(LinkList L,char FileName[])
{
    if( !L )				//线性表不存在 
        return INFEASIBLE;	//不可行 
    LinkList t=L->next;
    FILE *fp=fopen(FileName,"w");
    while(t){
        fprintf(fp,"%d ",t->data);
        t=t->next;
    }
    fclose(fp);
    return OK;
}

/********************************************************
函数名：  LoadList
初始条件：线性表L不存在 
函数功能：如果线性表L存在，表示L中已经有数据，读入数据会
覆盖原数据造成数据丢失，返回INFEASIBLE；否则将文件名为
FileName的数据读入到线性表L中，返回OK。
返回类型：status
********************************************************/
status LoadList(LinkList &L,char FileName[])
{
    if( L )					//线性表存在 
        return INFEASIBLE;	//不可行 
    L=(LinkList)malloc(sizeof(LNode));	//头节点开空间 
    LinkList t=L;
    //注意以上两句不可调换顺序 
    int val;				//val暂存文件输入值 
    FILE *fp=fopen(FileName,"r");
    while(fscanf(fp,"%d",&val)!=EOF){
        LinkList a=(LinkList)malloc(sizeof(LNode));
        a->data=val;
        t->next=a;
        t=a;
    }
    t->next=NULL;			//尾结点后继置空 
    fclose(fp);
    return OK;
}

/********************************************************
函数名：  ReverseList
初始条件：线性表L已存在 
函数功能：如果线性表L不存在，返回INFEASIBLE；否则将线性表
L的全部元素翻转 
返回类型：status
********************************************************/
status ReverseList(LinkList &L){
	if( !L )				//线性表不存在 
		return INFEASIBLE;	//不可行
	LinkList t=L->next;
	int num[100],cnt=0;		//开辟数组临时存储 
	while(t){
		num[cnt++]=t->data;
		t=t->next;
	} 
	t=L->next;
	for( int i=cnt-1 ; i>=0 ; i-- ){
		t->data=num[i];
		t=t->next;
	}
	return OK;
}

/********************************************************
函数名：  RemoveNthFromEnd
初始条件：线性表L已存在 
函数功能：如果线性表L不存在，返回INFEASIBLE；否则删除该链
表中倒数第n个节点
返回类型：status
********************************************************/
status RemoveNthFromEnd(LinkList &L,int n){
	if( !L )
		return INFEASIBLE;
	if( n<=0 )
		return ERROR;
	LinkList t=L->next;
	int cnt=0;
	while(t){
		cnt++;
		t=t->next;
	}
	if( cnt-n<0 )
		return ERROR;
	t=L->next;
	if( cnt==n ){
		L->next=t->next;
		free(t);
		return OK;
	}
	for( int i=0 ; i<cnt-n-1 ; i++ )
		t=t->next;
	LinkList a=t->next;
	t->next=a->next;
	free(a);
	return OK;
}
/********************************************************
函数名：  SortList
初始条件：线性表L已存在 
函数功能：如果线性表L不存在，返回INFEASIBLE；否则将线性表
L由小到大排序
返回类型：status
********************************************************/
status SortList(LinkList &L){
	if( !L )				//线性表不存在 
		return INFEASIBLE;	//不可行
	LinkList t=L->next;
	int len=0;
	while(t){
		len++;
		t=t->next;
	}
	for( int i=0 ; i<len ; i++ ){	//BubbleSort原理
		t=L->next;
		for( int j=0 ; j<len-i-1 ; j++ ){
			if( t->next->data<t->data ){
				int val=t->data;
				t->data=t->next->data;
				t->next->data=val;
			}
			t=t->next;
		}
	}
	return OK;
} 
