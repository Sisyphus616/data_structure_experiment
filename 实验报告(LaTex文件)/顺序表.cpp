#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h> 
#include<windows.h>

/**************相关定义与声明***************/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2			//溢出 
typedef int status;
typedef int ElemType;
#define LIST_INIT_SIZE 100	//顺序表的初始大小 
#define LISTINCREMENT  10	//顺序表每次分配增加的大小 
typedef int ElemType;
typedef struct{  			//顺序表（顺序结构）的定义
      ElemType * elem;
      int length;
      int listsize;
 }SqList;
 typedef struct{  //线性表的集合类型定义
     struct { char name[30];
               SqList L;    
     } elem[11];
     int length;
}LISTS;
LISTS Lists;      //线性表集合的定义Lists
/*******************************************/

/******************函数表*******************/
status InitList(SqList& L); 
status DestroyList(SqList& L); 
status ClearList(SqList& L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L,int i,ElemType &e);
int LocateElem(SqList L,ElemType e);
status PriorElem(SqList L,ElemType e,ElemType &pre);
status NextElem(SqList L,ElemType e,ElemType &next);
status ListInsert(SqList &L,int i,ElemType e);
status ListDelete(SqList &L,int i,ElemType &e);
status ListTraverse(SqList L);
status  SaveList(SqList L,char FileName[]); 
status  LoadList(SqList &L,char FileName[]);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
int LocateList(LISTS Lists,char ListName[]); 
int MaxSubArray( SqList &L );
int SubArrayNum( SqList &L,int k );
status sortList( SqList &L ); 
/*******************************************/

/*****************主函数********************/ 
int main(){
	/****************************************************************/
	/*						   程序框设置							*/
	/****************************************************************/ 
	system("mode con cols=82 lines=32 ");	//更改程序框大小 
	system("title 线性表：顺序存储结构");	//更改程序框名称
	system("color 1F");						//背景蓝色，字体亮白色
	/****************************************************************/
	/*						    初始化								*/
	/****************************************************************/
	int op=1;			//用户操作选项 
	SqList L[11];		//多线性表处理
	LISTS list;			//多线性表初始化 
	list.length=1;
	char filename[50];	//存储文件名
	char listname[50];	//存储线性表名 
	int lp=1;			//当前处理的线性表指针
	int val,pos;		//获取/查找元素用，val:元素的值,pos:元素的逻辑次序 
	ElemType pre,next;	//获取前驱/后继用，pre:前驱，next:后继 
	ElemType ins;		//插入元素用，存储插入元素的值 
	int cnt=0;			//记录操作次数 
	//线性表初始化 
	for( int i=1 ; i<11 ; i++ ){
		list.elem[i].L.elem=NULL;
		list.elem[i].L.length=0;
		list.elem[i].L.listsize=0;
	} 
	char *defaultname="线性表";
	for( int i=0 ; defaultname[i]!='\0' ; i++ )
		list.elem[1].name[i]=defaultname[i];
	/****************************************************************/
	/*						   菜单主体 							*/
	/****************************************************************/
	while(op){
		system("cls");
	    printf("\n\n");
		printf("	  \t\t\t线性表顺序结构菜单\t\t\n\n");
		printf(" 可在最多10个顺序表进行多表操作，初始表尚未初始化，名称默认为“线性表”\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf(" *1. 初始化线性表         \t\t7.  查找元素\t\t\t\t*\n");
		printf(" *2. 摧毁线性表       \t\t\t8.  获取前驱元素\t\t\t*\n");
		printf(" *3. 清空线性表         \t\t9.  获取后继元素 \t\t\t*\n");
		printf(" *4. 线性表判空         \t\t10. 插入元素\t\t\t\t*\n");
		printf(" *5. 线性表长度        \t\t\t11. 删除元素\t\t\t\t*\n");
		printf(" *6. 获取元素           \t\t12. 遍历线性表\t\t\t\t*\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf(" *13.线性表存储          \t\t14. 线性表读取\t\t\t\t*\n");
		printf(" *15.最大连续子数组和     \t\t16. 和为K的子数组\t\t\t*\n");
		printf(" *17.从小到大排序         \t\t18. 添加线性表\t\t\t\t*\n");
		printf(" *19.移除线性表          \t\t20. 选择要操作的线性表\t\t\t*\n\n");
		printf(" *0. 退出\t\t\t\n");
		printf(" --------------------------------------------------------------powered by 严浩洋\n");
		printf("当前操作的线性表：线性表%d：%s\n\n",lp,list.elem[lp].name);
		printf("请输入数字0~20以选择你的操作:");
		scanf("%d",&op);//选择op的值,用于switch
		printf("\n");
		switch(op){
			case 0:
				break;
			case 1:
				//初始化线性表
				if( list.elem[lp].L.elem ){
					printf("创建失败，线性表已存在！");
					break;
				}
				if( InitList(list.elem[lp].L)==OK )
					printf("线性表创建成功！");
				else
					printf("创建失败，线性表已存在！");
				break;
			case 2:
				//摧毁线性表
				if( !list.elem[lp].L.elem ){
					printf("销毁失败，线性表不存在！");
					break;
				}
				if( DestroyList(list.elem[lp].L)==OK )
					printf("已销毁线性表！");
				else
					printf("销毁失败，线性表不存在！");
				break; 
			case 3:
				//清空线性表
				if( !list.elem[lp].L.elem ){
					printf("清空失败，线性表不存在！");
					break;
				}
				if( ClearList(list.elem[lp].L)==OK )
					printf("已清空线性表！");
				else
					printf("清空失败，线性表不存在！");
				break;
			case 4:
				//判断线性表是否为空
				if( ListEmpty(list.elem[lp].L)==INFEASIBLE ) 
					printf("判断失败，线性表不存在！");
				else if( ListEmpty(list.elem[lp].L)==TRUE )
					printf("线性表为空！");
				else	//ListEmpty(L[lp])==FALSE
					printf("线性表不为空！"); 
				break;
			case 5:
				//线性表长度
				if( !list.elem[lp].L.elem ){
					printf("线性表不存在！");
					break;
				}
				if( ListLength(list.elem[lp].L)==INFEASIBLE )
					printf("线性表不存在！");
				else
					printf("线性表长度为%d",ListLength(list.elem[lp].L)); 
				break;
			case 6:
				//获取元素
				if( !list.elem[lp].L.elem ){
					printf("线性表不存在！");
					break;
				}
				printf("当前正在进行获取元素操作，请输入想要查询的元素在线性表中的逻辑次序：");
				scanf("%d",&pos);
				if( GetElem(list.elem[lp].L,pos,val)==INFEASIBLE )
					printf("\n线性表不存在！");
				else if( GetElem(list.elem[lp].L,pos,val)==ERROR )
					printf("\n获取失败，请检查下标值是否合法！");
				else
					printf("\n您想要查询的元素值为%d",val);
				break;
			case 7:
				//查找元素
				if( !list.elem[lp].L.elem ){
					printf("线性表不存在！");
					break;
				} 
				printf("当前正在进行查找元素操作，请输入想要查询的值："); 
				scanf("%d",&val);
				if( (pos=LocateElem(list.elem[lp].L,val))==INFEASIBLE )	//把返回值存在pos中，避免重复调用 
					printf("\n线性表不存在！");
				else if( pos!=ERROR )
					printf("\n查询成功！您需要的值在表中第%d个！",pos);
				else
					printf("\n您要查询的值不在表中！");
				break;
			case 8:
				//获取前驱元素
				if( !list.elem[lp].L.elem ){
					printf("线性表不存在！");
					break;
				}
				printf("当前正在进行获取前驱元素操作，请输入想要查询前驱的元素：");
				scanf("%d",&val);
				if( PriorElem(list.elem[lp].L,val,pre)==INFEASIBLE )
					printf("\n线性表不存在！");
				else if( PriorElem(list.elem[lp].L,val,pre)==ERROR )
					printf("\n获取失败！请检查您要查询的元素是否在表中或为表头！");
				else
					printf("\n获取成功！%d的前驱元素为%d",val,pre);
				break;
			case 9:
				//获取后继元素
				if( !list.elem[lp].L.elem ){
					printf("线性表不存在！");
					break;
				}
				printf("当前正在进行获取后继元素操作，请输入想要查询后继的元素：");
				scanf("%d",&val);
				if( PriorElem(list.elem[lp].L,val,pre)==INFEASIBLE )
					printf("\n线性表不存在！");
				else if( PriorElem(list.elem[lp].L,val,pre)==ERROR )
					printf("\n获取失败！请检查您要查询的元素是否在表中或为表尾！");
				else
					printf("\n获取成功！%d的后继元素为%d",val,pre);
				break;
			case 10:
				//插入元素 
				if( !list.elem[lp].L.elem ){
					printf("线性表不存在！");
					break;
				}
				printf("当前正在进行插入元素操作，请输入想要插入元素的逻辑次序和元素值\n");
				printf("逻辑次序：");
				scanf("%d",&pos);
				printf("元素值：");
				scanf("%d",&ins); 
				if( ListInsert(list.elem[lp].L,pos,ins)==OK )
					printf("\n插入成功！");
				else if( ListInsert(list.elem[lp].L,pos,ins)==INFEASIBLE )
					printf("\n线性表不存在");
				else
					printf("\n插入失败！请检查下标值是否合法");
				break;
			case 11:
				//删除元素
				if( !list.elem[lp].L.elem ){
					printf("线性表不存在！");
					break;
				}
				printf("当前正在进行删除元素操作，请输入想要删除元素的逻辑次序：");
				scanf("%d",&pos);
				if( ListDelete(list.elem[lp].L,pos,ins)==OK )
					printf("\n删除成功！删除的元素为%d",ins);
				else if( ListDelete(list.elem[lp].L,pos,ins)==INFEASIBLE )
					printf("\n线性表不存在");
				else
					printf("\n删除失败！请检查下标值是否合法!");
				break;
			case 12:
				//遍历线性表
				//这里需要先判断线性表是否存在
				if( !list.elem[lp].L.elem )
					printf("线性表不存在！");
				else{
					printf("线性表%d的元素依次是：\n",lp);
					ListTraverse(list.elem[lp].L);
				} 
				break;
			case 13:
				//线性表存储
				if( !list.elem[lp].L.elem ){
					printf("线性表不存在！");
					break;
				}
				printf("当前正在进行线性表存储操作，请输入想要生成的文件名：\n");
				scanf("%s",filename);
				if( SaveList(list.elem[lp].L,filename)==INFEASIBLE )
					printf("线性表不存在！");
				else
					printf("存储成功！");
				break;
			case 14:
				//线性表读取
				printf("当前正在进行线性表读取操作，请输入想要读取的文件名(包括扩展名)：\n");
				scanf("%s",filename);
				if( LoadList(list.elem[lp].L,filename)==OK )
					printf("\n读取成功！");
				else if( LoadList(list.elem[lp].L,filename)==INFEASIBLE )
					printf("\n线性表不为空！不能进行读取操作！");
				else
					printf("\n读取失败！请检查文件是否存在！");
				break;
			case 15:
				//最大连续子数组和
				int ret15;
				if( (ret15=MaxSubArray(list.elem[lp].L))==INFEASIBLE )
					printf("线性表不存在或为空！");
				else
					printf("最大连续子数组和为：%d",ret15);
				break;
			case 16:
				//返回和为K的子数组数目 
				int ret16,k;
				printf("当前正在进行求和为K的子数组数目的操作，请输入K的值：");
				scanf("%d",&k);
				if( (ret16=SubArrayNum(list.elem[lp].L,k))==INFEASIBLE )
					printf("\n线性表不存在或为空！");
				else
					printf("\n和为K的子数组数目为：%d",ret16);
				break;
			case 17:
				//从小到大排序
				if( sortList(list.elem[lp].L)==INFEASIBLE )
					printf("线性表不存在或为空！");
				else
					printf("排序成功！");
				break; 
			case 18:
				//多线性表管理——添加新表 
				if( list.length>=10 )
					printf("当前线性表数目已超过上限！");
				else{
					printf("当前正在进行添加线性表的操作，请输入想要建立新表的名称：\n");
					scanf("%s",listname);
					AddList(list,listname);
					printf("\n添加成功！");
				}
				break;
			case 19:
				//多线性表管理——移除表
				if( !list.elem )
					printf("线性表组中没有线性表，先创建一个吧！");
				else{
					int ret19;
					printf("当前正在进行移除线性表的操作，请输入您要移除的线性表的名称：\n");
					scanf("%s",listname);
					if((ret19=RemoveList(list,listname))==ERROR)
						printf("\n没有找到您输入的线性表耶，请检查您是否输入错误！");
					else{
						printf("\n移除成功了！\n");
						if( ret19<lp )
							lp--;
						else if( ret19==lp ){
							printf("\n由于你删除了当前线性表，下次操作默认对第一个线性表进行！");
							lp=1;
						}
					}
				}
				break; 
			case 20:
				//多线性表管理——选择要操作的线性表 
				printf("当前正在进行选择操作线性表的操作，请输入您要操作的线性表的名称：\n");
				scanf("%s",listname);
				int ret20;
				if( (ret20=LocateList(list,listname))==INFEASIBLE )
					printf("\n线性表组中没有线性表！先创建一个吧！");
				else if( ret20==ERROR )
					printf("\n没有找到您输入的线性表耶，请检查您是否输入错误！");
				else{
					lp=ret20;
					printf("\n定位成功！");
				}
				break;
			default:
				//输入op错误
				printf("请输入正确的选项！");
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
/*******************************************/


/*******************************************************************
函数名称：InitList
初始条件：线性表L不存在 
功能说明：如果线性表L不存在，操作结果是构造一个空的线性表，返回OK，
否则返回INFEASIBLE。 
返回值类型：  
********************************************************************/
status InitList(SqList& L)
{
    if(L.elem)				//线性表已存在 
        return INFEASIBLE;	//不可行 
    L.elem=(ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    L.length=0;
    L.listsize=LIST_INIT_SIZE;
    return OK;
}

/*******************************************************************
函数名称：DestroyList
初始条件：线性表L已存在 
功能说明：如果线性表L存在，该操作释放线性表的空间，使线性表成为未初
始化状态，返回OK；否则对于一个未初始的线性表，是不能进行销毁操作的，
返回INFEASIBLE。
返回值类型： status 
********************************************************************/
status DestroyList(SqList& L)
{
    if(L.elem){				//若线性表存在 
        free(L.elem);
        //相关数值清空 
        L.elem=NULL;
        L.length=0;
        L.listsize=0;
    }
    else					//线性表不存在 
        return INFEASIBLE;	//不可行 
    return OK;
}

/*******************************************************************
函数名称：ClearList
初始条件：线性表L已存在 
功能说明：若线性表L不存在，返回INFEASIBLE。否则清空线性表L，返回OK；
返回值类型： status 
********************************************************************/
status ClearList(SqList& L)
{
    if( L.elem ){			//若线性表存在 
        L.length=0;
    }
    else					//线性表不存在 
        return INFEASIBLE;	//不可行 
    return OK;
}

/*******************************************************************
函数名称：ListEmpty
初始条件：线性表L已存在 
功能说明：若线性表L不存在，则返回INFEASIBLE；若线性表L长度为0，则返
回TRUE；不为0则返回FALSE。
返回值类型： status 
********************************************************************/
status ListEmpty(SqList L)
{
    if( !L.elem )			//若线性表不存在 
        return INFEASIBLE;	//不可行 
    if( L.length==0 )		//线性表为空 
        return TRUE;
    else					//线性表不为空 
        return FALSE;
}

/*******************************************************************
函数名称：ListLength 
初始条件：线性表L已存在 
功能说明：若线性表L不存在，返回INFEASIBLE；否则返回线性表L的长度。
返回值类型： status 
********************************************************************/
status ListLength(SqList L)
{
    if( !L.elem )			//若线性表不存在 
        return INFEASIBLE;	//不可行 
    else
        return L.length; 
}

/*******************************************************************
函数名称：GetElem 
初始条件：线性表L已存在 
功能说明：若线性表L不存在，返回INFEASIBLE；若i<1或者i超过线性表L的长
度，则返回ERROR；若获取成功，则将值赋给e，并返回OK。
返回值类型： status 
********************************************************************/
status GetElem(SqList L,int i,ElemType &e)
{
    if( !L.elem )			//若线性表不存在 
        return INFEASIBLE;	//不可行 
    if( i<1||i>L.length )	//若下标值不合法 
        return ERROR;		//出错 
    e=L.elem[i-1];
    return OK;
}

/*******************************************************************
函数名称：LocateElem
初始条件：线性表L已存在 
功能说明：若线性表L不存在，返回INFEASIBLE；若没有找到指定的元素e，则
查找失败，返回ERROR；若查找成功，则返回元素逻辑序号i。
返回值类型： int
********************************************************************/
int LocateElem(SqList L,ElemType e)
{
    if( !L.elem )			//若线性表不存在 
        return INFEASIBLE;	//不可行 
    int pos=-1;				//所求元素下标，初始化为-1 
    for( int i=0 ; i<L.length ; i++ ){
        if( L.elem[i]==e ){
            pos=i;
            break;
        }
    }
    if( pos==-1 )			//pos仍未原值，即未找到 
        return ERROR;		//出错 
    return pos+1;
}

/*******************************************************************
函数名称：PriorElem
初始条件：线性表L已存在 
功能说明：若线性表L不存在，返回INFEASIBLE；若没有找到指定元素e的前驱，
则查找失败，返回ERROR；若查找成功，则将值赋给pre，并返回OK。
返回值类型： status
********************************************************************/
status PriorElem(SqList L,ElemType e,ElemType &pre)
{
    if( !L.elem )			//若线性表不存在 
        return INFEASIBLE;	//不可行 
    for( int i=0 ; i<L.length ; i++ ){
        if( L.elem[i]==e ){	//找到该值 
            if( i==0 )		//所求值对应表中首元素，无前驱 
                return ERROR;
            pre=L.elem[i-1];
            return OK;		//元素存在且不为首元素 
        }
    }
    return ERROR;			//循环结束，即未找到该元素 
}
//注：这里第一次写时没有考虑首元素没有前驱，于是在修改时直接进行特判所查
//元素是否为首元素，还有一种改法与下面查找后继所用的方法类似，即在循环时
//直接从i=1开始循环。 

/*******************************************************************
函数名称：NextElem
初始条件：线性表L已存在 
功能说明：若线性表L不存在，返回INFEASIBLE；若没有找到指定元素e的后继，
则查找失败，返回ERROR；若查找成功，则将值赋给next，并返回OK。
返回值类型： status
********************************************************************/
status NextElem(SqList L,ElemType e,ElemType &next)
{
    if( !L.elem )			//若线性表不存在 
        return INFEASIBLE;	//不可行 
    for( int i=0 ; i<L.length-1 ; i++ ){
	//这里循环到L.length-2即可，因为即使L.elem[L.length-1]==e也没有后继 
        if( L.elem[i]==e ){	//找到该值 
            next=L.elem[i+1];
            return OK;
        }
    }
    return ERROR;			//循环结束，即未找到该元素 
}

/*******************************************************************
函数名称：ListInsert
初始条件：线性表L已存在 
功能说明：如果线性表L不存在，返回INFEASIBLE；否则在线性表L的第i个元素
前插入新的元素e，插入成功返回OK，失败返回ERROR。
返回值类型： status
********************************************************************/
status ListInsert(SqList &L,int i,ElemType e)
{
    if( !L.elem )					//若线性表不存在 
        return INFEASIBLE;			//不可行 
    if( L.length==L.listsize ){		//线性表已满 
        L.elem=(ElemType*)realloc(L.elem,sizeof(ElemType)*(L.listsize+LISTINCREMENT));
        L.listsize+=LISTINCREMENT;
    }
    if( i<1||i>L.length+1)			//若下标不合法 
        return ERROR;				//出粗 
    for( int j=L.length ; j>=i ; j-- )		//移动元素 
        L.elem[j]=L.elem[j-1];
    L.elem[i-1]=e;
    L.length++;
    return OK;
}

/*******************************************************************
函数名称：ListDelete
初始条件：线性表L已存在 
功能说明：若线性表L不存在，返回INFEASIBLE；否则删除线性表L的第i个元
素，若删除成功则将删除的值赋给e并返回OK，若删除失败则返回ERROR。
返回值类型： status
********************************************************************/
status ListDelete(SqList &L,int i,ElemType &e)
{
    if( !L.elem )			//若线性表不存在 
        return INFEASIBLE;	//不可行 
    if( i<1||i>L.length)	//若下标不合法 
        return ERROR;		//出错 
    e=L.elem[i-1];
    for( int j=i ; j<L.length ; j++ )		//移动元素 
        L.elem[j-1]=L.elem[j];
    L.length--;
    return OK;
}

/*******************************************************************
函数名称：ListTraverse
初始条件：线性表L已存在 
功能说明：若线性表L不存在，返回INFEASIBLE；否则输出线性表的每一个元
素，并返回OK。
返回值类型： status
********************************************************************/
status ListTraverse(SqList L)
{
    if( !L.elem )			//若线性表不存在 
        return INFEASIBLE;	//不可行 
    for( int i=0 ; i<L.length ; i++ ){
        printf("%d",L.elem[i]);
        if( i!=L.length-1 )
        printf(" ");
    }
    return OK;
}

/*******************************************************************
函数名称：SaveList
初始条件：线性表L已存在 
功能说明：如果线性表L不存在，返回INFEASIBLE；否则将线性表L的全部元素
写入到文件名为FileName的文件中，返回OK。
返回值类型： status
********************************************************************/
status  SaveList(SqList L,char FileName[])
{
    if( !L.elem )			//若线性表不存在 
        return INFEASIBLE;	//不可行 
    FILE *fp;
    fp=fopen(FileName,"w+");
    fprintf(fp,"%d ",L.length);			//元素个数和表长都写入文件，方便操作 
    fprintf(fp,"%d ",L.listsize);
    for( int i=0 ; i<L.length ; i++ )
        fprintf(fp,"%d ",L.elem[i]);
    fclose(fp);
    return OK;
}

/*******************************************************************
函数名称：LoadList
初始条件：线性表L为空 
功能说明：如果线性表L存在，表示L中已经有数据，读入数据会覆盖原数据造
成数据丢失，返回INFEASIBLE；否则将文件名为FileName的数据读入到线性表
L中，返回OK。本实验不考虑用追加的方式读入文件数据追加到现有线性表中。
返回值类型： status
********************************************************************/
status  LoadList(SqList &L,char FileName[])
{
    if( L.elem )			//若线性表不为空 
        return INFEASIBLE;	//不可行 
    FILE *fp;
    fp=fopen(FileName,"r+");
    if( fp==NULL )			//文件不存在 
    	return ERROR;
    fscanf(fp,"%d %d",&L.length,&L.listsize);		//先读入元素个数和表长 
    L.elem=(ElemType*)malloc(sizeof(ElemType)*L.listsize);
    for( int i=0 ; i<L.length ; i++ )
        fscanf(fp,"%d",&L.elem[i]);
    fclose(fp);
    return OK;
}

/*******************************************************************
函数名称：AddList
初始条件：想要添加的线性表L为空
功能说明：Lists是一个以顺序表形式管理的线性表的集合，在集合中增加一
个新的空线性表。增加成功返回OK，否则返回ERROR。
返回值类型： status
********************************************************************/
status AddList(LISTS &Lists,char ListName[])
{
    if( Lists.length>=10 )	//超出Lists最大范围 
        return ERROR;		//出错
	//初始化操作 
	Lists.length++;
    Lists.elem[Lists.length].L.length=0;
    Lists.elem[Lists.length].L.listsize=0;
    int i;
    for( i=0 ; ListName[i]!='\0' ; i++ )
        Lists.elem[Lists.length].name[i]=ListName[i];
    Lists.elem[Lists.length].name[i]='\0';
    return OK;
}

/*******************************************************************
函数名称：RemoveList
初始条件：Lists存在 
功能说明：Lists是一个以顺序表形式管理的线性表的集合，在集合中查找名
称为ListName的线性表，有则删除，返回OK，无则返回ERROR。
返回值类型： status
********************************************************************/
status RemoveList(LISTS &Lists,char ListName[])
{
	if( !Lists.length )		//Lists为空 
		return INFEASIBLE;	//不可行 
    for( int i=1 ; i<=Lists.length ; i++ ){
        if( !strcmp(ListName,Lists.elem[i].name) ){
            //free(Lists.elem[i].L.elem);free(Lists.elem[i].name);
            for( int j=i ; j<Lists.length ; j++ )
                Lists.elem[j]=Lists.elem[j+1];
            Lists.elem[Lists.length].L.elem=NULL;
            Lists.elem[Lists.length].L.listsize=0;
            Lists.elem[Lists.length].L.length=0;
            Lists.length--;
            return i;
        }
    }
    return ERROR;
}

/*******************************************************************
函数名称：LocateList
初始条件：Lists存在 
功能说明：Lists是一个以顺序表形式管理的线性表的集合，在集合中查找名称
为ListName的线性表，有则返回线性表的逻辑序号，无则返回0。
返回值类型： int
********************************************************************/
int LocateList(LISTS Lists,char ListName[])
{
	if( !Lists.length )		//Lists为空 
		return INFEASIBLE;	//不可行 
    for( int i=1 ; i<=Lists.length ; i++ ){
        if( !strcmp(ListName,Lists.elem[i].name) )
            return i;
    }
    return 0;
}

/*******************************************************************
函数名称：MaxSubArray
初始条件：线性表L存在且非空 
功能说明：找出一个具有最大和的连续子数组（子数组最少包含一个元素），
返回其最大和
返回值类型： int
********************************************************************/
int MaxSubArray( SqList &L ){
	if( !L.elem||L.length==0 )		//线性表不存在或为空 
		return INFEASIBLE;			//不可行 
	int sum=0;
	int ans=L.elem[0];
	for( int i=0 ; i<L.length ; i++ ){	//在线处理 
		sum+=L.elem[i];
		ans=(sum>ans)?sum:ans;		//模拟max函数 
		if( sum<0 )					//sum小于0则舍弃 
			sum=0;
	}
	return ans;
}

/*******************************************************************
函数名称：SubArrayNum
初始条件：线性表L存在且非空 
功能说明：返回该数组中和为k的连续子数组的个数
返回值类型： int
********************************************************************/
int SubArrayNum( SqList &L,int k ){
	if( !L.elem||L.length==0 )		//线性表不存在或为空 
		return INFEASIBLE;			//不可行
	int cnt=0;
	for( int start=0 ; start<L.length ; start++ ){
		int sum=0;
		for( int end=start ; end>=0 ; end-- ){
			sum+=L.elem[end];
			if( sum==k )
				cnt++;
		}
	}
	return cnt;
}

/*******************************************************************
函数名称：sortList
初始条件：线性表L存在且非空 
功能说明：将L由小到大排序
返回值类型： status
********************************************************************/
status sortList( SqList &L ){
	if( !L.elem||L.length==0 )		//线性表不存在或为空 
		return INFEASIBLE;			//不可行
	for( int i=0 ; i<L.length ; i++ ){	//BubbleSort
		for( int j=1 ; j<L.length-i ; j++ ){
			if( L.elem[j]<L.elem[j-1] ){
				int t=L.elem[j];
				L.elem[j]=L.elem[j-1];
				L.elem[j-1]=t;
			}
		}
	}
	return OK;
}