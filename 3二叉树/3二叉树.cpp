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
#define OVERFLOW -2

typedef int status;
typedef int KeyType; 
typedef struct {
     KeyType  key;
     char others[20];
} TElemType; 				//二叉树结点类型定义

typedef struct BiTNode{  	//二叉链表结点的定义
      TElemType  data;
      struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;

typedef struct{  			//线性表的集合类型定义
    struct { 
		char name[30];
        BiTree T;    
    }elem[11];
    int length;
}LISTS;

//全局变量 
int cnt=0;			//数组元素个数 
int num[1000]={0};	//用于存储key，防止关键字重复 
BiTree pre=NULL;	//前驱节点 
BiTree array[100];	//文件树存取数组 
//队列定义 
BiTree queue[100];
int tail=0,front=0; //头尾定义  
//栈定义
BiTree stack[100];
int top=0;			//栈顶 
/*******************************************/

/******************函数表*******************/
status bullsort(TElemType def[]);
status CreateBiTree(BiTree &T,TElemType definition[]);
status DestroyBiTree(BiTree &T);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T,KeyType e);
status bullsort_a(int def[]);
void PreOrder_a(BiTree T);
status Assign(BiTree &T,KeyType e,TElemType value);
BiTNode* GetSibling(BiTree T,KeyType e);
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);
status DeleteNode(BiTree &T,KeyType e);
status PreOrderTraverse(BiTree T,void (*visit)(BiTree));
status InOrderTraverse(BiTree T,void (*visit)(BiTree));
status PostOrderTraverse(BiTree T,void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));
void PreOrder_b(BiTree T);
status SaveBiTree(BiTree T, char FileName[]);
status CreatebiTree(BiTree &T,TElemType definition[]);
status LoadBiTree(BiTree &T,  char FileName[]);
void visit(BiTree T);
int DFSMaxLength(BiTree T,int num);
BiTree LowerPublicAncestor( BiTree T , int e1 , int e2 );
status AddBiTree(LISTS &tree,char listname[]);
int DeleteBiTree(LISTS &tree,char listname[]); 
int ChooseBiTree(LISTS &tree, char listname[]);
status InvertTree( BiTree T );
void PreOrder_c(BiTree T,void (*visit)(BiTree));
void InOrder_c(BiTree T,void (*visit)(BiTree));
void PostOrder_c(BiTree T,void (*visit)(BiTree));
status LevelOrder_c(BiTree T,void (*visit)(BiTree));
/*******************************************/

///////////////////////////////////////////////////////
int main(){
	
	/****************************************************************/
	/*						   程序框设置							*/
	/****************************************************************/ 
	
	system("mode con cols=82 lines=34 ");	//更改程序框大小 
	system("title 线性表：顺序存储结构");	//更改程序框名称
	system("color 1F");						//背景蓝色，字体亮白色
	
	/****************************************************************/
	/*						    初始化								*/
	/****************************************************************/
	int op=1;			//用户操作选项 
	char filename[50];	//存储文件名
	char treename[50];	//存储树名 
	TElemType input[50];//存储输入的值 
	int lp=1;			//当前处理的树指针
	int cntnum=0;		//记录操作次数
	int keyin;			//记录查找结点的关键字 
	int maxlen=0;		//最长路径 
	int mode;			//插入模式 
	//多个二叉树管理 
	LISTS tree;			//二叉树初始化  
	tree.length=0;
	//树初始化
	for( int i=0 ; i<11 ; i++ )
		tree.elem[i].T=NULL;
	char defaultname[30]="二叉树";
	//名称初始化 
	for( int i=0 ; defaultname[i]!='\0' ; i++ )
		tree.elem[1].name[i]=defaultname[i]; 
	/****************************************************************/
	/*						   菜单主体 							*/
	/****************************************************************/
	while(op){
		system("cls");
	    printf("\n\n");
		printf("	  \t\t\t二叉树菜单\t\t\n\n");
		printf(" 可在最多10个二叉树进行多树操作，二叉树尚未初始化，名称默认为“二叉树”\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf(" *1. 初始化二叉树         \t\t7.  插入结点\t\t\t\t*\n");
		printf(" *2. 销毁二叉树       \t\t\t8.  删除结点\t\t\t\t*\n");
		printf(" *3. 二叉树深度         \t\t9.  先序遍历 \t\t\t\t*\n");
		printf(" *4. 查找结点         \t\t\t10. 中序遍历\t\t\t\t*\n");
		printf(" *5. 结点赋值        \t\t\t11. 后序遍历\t\t\t\t*\n");
		printf(" *6. 获得兄弟结点           \t\t12. 按层遍历\t\t\t\t*\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf(" *13.二叉树存储          \t\t14. 二叉树读取\t\t\t\t*\n");
		printf(" *15.最大路径和     \t\t\t16. 最近公共祖先\t\t\t*\n");
		printf(" *17.翻转二叉树         \t\t18. 添加二叉树\t\t\t\t*\n");
		printf(" *19.移除二叉树          \t\t20. 选择要操作的二叉树\t\t\t*\n");
		printf(" *21.清空二叉树          \t\t22. 判断空二叉树\t\t\t*\n\n");
		printf(" *0. 退出\t\t\t\n");
		printf(" --------------------------------------------------------------powered by 严浩洋\n");
		printf("当前操作的二叉树：二叉树%d：%s\n\n",lp,tree.elem[lp].name);
		printf("请输入数字0~20以选择你的操作:");
		scanf("%d",&op);//选择op的值,用于switch
		printf("\n");
		switch(op){
			case 0:
				//结束操作 
				break;
			case 1:
				//创建二叉树 
				if( tree.elem[lp].T ){
					printf("创建失败！二叉树已存在！");
					break;
				}
				else{
					printf("当前正在进行二叉树的初始化操作，请输入二叉树的先序遍历数组：\n");
					int i=0; 
					do{
						scanf("%d %s",&input[i].key,input[i].others);
					}while(input[i++].key!=-1);
					cnt=0;
					for( int i=0 ; i<1000 ; i++ )
						num[i]=0;
					if( CreateBiTree(tree.elem[lp].T,input)==ERROR )
						printf("\n输入关键字重复，创建失败！");
					else{
						printf("\n创建成功！");
						tree.length++;
					}
					cnt=0;
				}
				break; 
			case 2:
				//销毁二叉树 
				if( !tree.elem[lp].T )
					printf("二叉树不存在！无法销毁！");
				else{
					DestroyBiTree(tree.elem[lp].T);
					printf("销毁成功！");
					tree.length--;
				}
				break;
			case 3:
				//二叉树深度
				if( !tree.elem[lp].T )
					printf("二叉树不存在！无法判断深度！");
				else
					printf("二叉树的深度为：%d",BiTreeDepth(tree.elem[lp].T));
				break;
			case 4:
				//查找结点
				if( !tree.elem[lp].T )
					printf("二叉树不存在！无法查找结点！");
				else{
					printf("当前正在进行查找结点操作，请输入想要查询结点的关键字：");
					scanf("%d",&keyin);
					BiTree t;
					if( (t=LocateNode(tree.elem[lp].T,keyin))==NULL )
						printf("\n查找失败！请检查您输入的关键字是否有误！");
					else
						printf("\n查询成功！您查找的结点为：%d,%s",t->data.key,t->data.others);
				} 
				break;
			case 5:
				//结点赋值
				if( !tree.elem[lp].T )
					printf("二叉树不存在！不能进行结点赋值操作！");
				else{
					printf("当前正在进行结点赋值操作，请输入想要查询结点的关键字：");
					scanf("%d",&keyin);
					if( LocateNode(tree.elem[lp].T,keyin)==NULL ){
						printf("\n未查询到您想要的结点！");
						break;
					}
					printf("请输入想要赋予的关键字：");
					scanf("%d %s",&input[0].key,input[0].others);
					for( int i=0 ; i<1000 ; i++ )
						num[i]=0;
					if(Assign(tree.elem[lp].T,keyin,input[0])==ERROR)
						printf("\n赋值失败！请检查您输入的关键字是否重复！");
					else
						printf("\n赋值成功！");
				} 
				break;
			case 6:
				//获得兄弟节点
				if( !tree.elem[lp].T )
					printf("二叉树不存在！无法获取兄弟节点！");
				else{
					pre=NULL;
					printf("当前正在进行获得兄弟结点操作，请输入想要查询结点的关键字：");
					scanf("%d",&keyin);
					if( LocateNode(tree.elem[lp].T,keyin)==ERROR ){
						printf("\n您输入的关键字在二叉树中不存在！");
						break;
					}
					BiTree t;
					if( (t=GetSibling(tree.elem[lp].T,keyin))==ERROR )
						printf("\n您查询的结点没有兄弟节点！");
					else
						printf("\n您查询结点的兄弟节点为：%d,%s",t->data.key,t->data.others);
				} 
				break;
			case 7:
				//插入节点
				if( !tree.elem[lp].T )
					printf("二叉树不存在！无法插入结点！"); 
				else{
					for( int i=0 ; i<1000 ; i++ )
    					num[i]=0;
    				printf("当前正在进行插入结点操作，请输入想要查询结点的关键字，插入模式");
					printf("（-1表示根结点插入，0表示作为e的左孩子，1表示作为e的右孩子），以及插入结点的值：");
    				scanf("%d %d %d %s",&keyin,&mode,&input[0].key,input[0].others);
    				if( InsertNode(tree.elem[lp].T,keyin,mode,input[0])==ERROR )
    					printf("\n您插入的结点与原先关键字重复！");
    				else
    					printf("\n插入成功！");
				}
				break;
			case 8:
				//删除结点
				if( !tree.elem[lp].T )
					printf("二叉树不存在！无法删除结点！");
				else{
					pre=NULL;
					printf("当前正在进行删除结点操作，请输入想要删除结点的关键字：");
					scanf("%d",&keyin);
					if( LocateNode(tree.elem[lp].T,keyin)==ERROR ){
						printf("\n您要删除的结点不存在！");
						break;
					}
					if( BiTreeDepth(tree.elem[lp].T)==1 ){
						DestroyBiTree(tree.elem[lp].T);tree.length--;
						printf("\n注意：您删除了二叉树的唯一节点！此操作等同于销毁二叉树！");
					}
					else{
						DeleteNode(tree.elem[lp].T,keyin);
						printf("\n删除成功！");
					}
				} 
				break;
			case 9:
				//先序遍历 
				if( !tree.elem[lp].T ){
					printf("二叉树不存在！无法遍历！");
					break; 
				}
				printf("先序遍历的结果为：\n");
				PreOrderTraverse(tree.elem[lp].T,visit);
				break;
			case 10:
				//中序遍历 
				if( !tree.elem[lp].T ){
					printf("二叉树不存在！无法遍历！");
					break; 
				}
				top=0; 
				printf("中序遍历的结果为：\n");
				InOrderTraverse(tree.elem[lp].T,visit);
				break;
			case 11:
				//后序遍历
				if( !tree.elem[lp].T ){
					printf("二叉树不存在！无法遍历！");
					break; 
				}
				printf("后序遍历的结果为：\n"); 
				PostOrderTraverse(tree.elem[lp].T,visit);
				break;
			case 12:
				//层次遍历 
				if( !tree.elem[lp].T ){
					printf("二叉树不存在！无法遍历！");
					break; 
				}
				tail=front=0;
				printf("层次遍历的结果为：\n");
				LevelOrderTraverse(tree.elem[lp].T,visit);
				break;
			case 13:
				//二叉树存储 
				if( !tree.elem[lp].T ){
					printf("二叉树不存在！不能进行存储操作！");
					break;
				}
				printf("当前正在进行二叉树的存储操作，请输入文件名：\n");
				scanf("%s",filename);
				SaveBiTree(tree.elem[lp].T,filename);
				printf("\n存储成功！");
				break;
			case 14:
				//二叉树读取 
				if( tree.elem[lp].T ){
					if(tree.elem[lp].T->lchild||tree.elem[lp].T->rchild){
						printf("二叉树不为空！不能进行读取操作！");
						break;
					}
					DestroyBiTree(tree.elem[lp].T);
					tree.length--;
				}
				printf("当前正在进行二叉树的读取操作，请输入文件名：\n");
				scanf("%s",filename);
				LoadBiTree(tree.elem[lp].T,filename);
				printf("\n读取成功！");
				tree.length++;
				break;
			case 15:
				//最长路径和
				maxlen=0;
				if( !tree.elem[lp].T )
					printf("二叉树不存在！无法判断最长路径和！");
				else
					printf("最长路径和为：%d",DFSMaxLength(tree.elem[lp].T,0));
				break;
			case 16:
				//最近公共祖先
				if( !tree.elem[lp].T )
					printf("二叉树不存在！无法判断最近公共祖先！");
				else{
					printf("当前正在进行查询最近公共祖先操作，请输入要查询的两结点的关键字：");
					int e1,e2;
					scanf("%d %d",&e1,&e2);
					for( int i=0 ; i<1000 ; i++ )
						num[i]=0;
					PreOrder_a(tree.elem[lp].T);
					if( num[e1]==0||num[e2]==0 )
						printf("\n您输入的关键字不存在！");
					else{
						BiTree t=LowerPublicAncestor(tree.elem[lp].T,e1,e2);
						printf("\n祖先结点关键字为：%d",t->data.key);
					}
				}
				break;
			case 17:
				//翻转二叉树
				if( !tree.elem[lp].T )
					printf("二叉树不存在！无法进行反转操作！");
				else{
					InvertTree(tree.elem[lp].T);
					printf("\n翻转成功！");
				} 
				break;
			case 18:
				//添加二叉树
				if( tree.length>=10 ){
					printf("当前二叉树数目已超过上限！"); 
					break;
				}
				printf("当前正在进行添加二叉树操作，请输入添加的二叉树名：");
				scanf("%s",treename); 
				if( AddBiTree(tree,treename)==ERROR )
					printf("\n当前名称已存在，换一个名字吧！");
				else
					printf("\n添加成功！");
				break;
			case 19:
				//删除二叉树
				if( tree.length<=0 ){
					printf("当前已经没有二叉树，不能删除！");
					break;
				} 
				int ret_19;
				printf("当前正在进行删除二叉树操作，请输入删除的二叉树名：");
				scanf("%s",treename);
				if( (ret_19=DeleteBiTree(tree,treename))==ERROR )
					printf("\n未找到您要删除的二叉树！");
				else{
					printf("\n删除成功！");
					tree.length--;
					if( ret_19==lp ){
						printf("由于您删除了当前操作的二叉树，下次操作默认对二叉树1进行！");
						lp=1;
					}
				}
				break;
			case 20:
				//选择要操作的二叉树
				printf("当前正在选择要操作的二叉树，请输入选择的二叉树名：");
				scanf("%s",treename);
				int ret_20;
				if( (ret_20=ChooseBiTree(tree,treename))==ERROR )
					printf("\n没有找到您要操作的二叉树，请检查是否输入正确！");
				else{
					printf("\n选择成功！即将对该二叉树进行操作！");
					lp=ret_20;
				}
				break; 
			case 21:
				//清空二叉树
				if( !tree.elem[lp].T )
					printf("二叉树不存在！清空失败！");
				else{
					DestroyBiTree(tree.elem[lp].T);tree.length--;
					tree.elem[lp].T=(BiTree)malloc(sizeof(BiTNode));
					tree.length++;
					tree.elem[lp].T->lchild=NULL;
					tree.elem[lp].T->rchild=NULL;
					tree.elem[lp].T->data.key=-1;
					printf("二叉树已清空！");
				} 
				break;
			case 22:
				//判断空二叉树
				if( !tree.elem[lp].T )
					printf("二叉树不存在！无法判空！");
				else{
					if( !tree.elem[lp].T->lchild&&!tree.elem[lp].T->rchild )
						printf("二叉树为空！");
					else
						printf("二叉树不为空！");
				} 
				break;
			case 23:
				//建立空树
				if( tree.elem[lp].T )
					printf("二叉树已存在！无法建立空树！");
				else{
					tree.elem[lp].T=(BiTree)malloc(sizeof(BiTNode));
					tree.length++;
					tree.elem[lp].T->lchild=NULL;
					tree.elem[lp].T->rchild=NULL;
					tree.elem[lp].T->data.key=-1;
					printf("空树创建成功！");
				} 
			default:
				//选项输入有误 
				printf("请输入正确的选项！");
				break;
		}
		if( op!=0 ){
			printf("\n\n按任意键继续下一个操作\n\n");
			system("pause");
			cntnum++;
		}
	}
	printf("谢谢使用！您本次共进行了%d次操作！欢迎下次再来！\n",cntnum);
	Sleep(2000);
	return 0;
}
///////////////////////////////////////////////////////


/*******************************************************************
函数名称：CreateBiTree
初始条件：给定二叉树先序遍历数组 
功能说明：根据带空子树的二叉树先序遍历序列definition（注意该数组元素
类型为TElemType），构造一个如下图所示的二叉链表T（要求二叉树T中各结点
关键字具有唯一性）。根指针指向根结点，不需要在根结点之上再增加头结点。 
返回值类型：status
辅助函数：桶排序函数 
********************************************************************/
status bullsort(TElemType def[]){
    int nums[1000]={0};
    for( int i=0 ; def[i].key!=-1 ; i++ )
        nums[def[i].key]++;
    for( int i=1 ; i<1000 ; i++ )
        if( nums[i]>1 )
            return ERROR;
    return OK;
}

status CreateBiTree(BiTree &T,TElemType definition[])
{

    if( cnt==0 )							//初始先进行桶排序操作，防止关键字重复 
        if( bullsort(definition)==ERROR )	//关键字重复 
            return ERROR;
    if( definition[cnt].key==0 ){			//空结点 
        T=NULL;
        cnt++;
    }
    else if( definition[cnt].key==-1 )		//结束条件 
    	return OK;
    else{
        if( !T )
            T=(BiTree)malloc(sizeof(BiTNode));
        T->data=definition[cnt++];
        CreateBiTree(T->lchild,definition);
        CreateBiTree(T->rchild,definition);
    }
    return OK;
} 

/*******************************************************************
函数名称：DestroyBiTree
初始条件：二叉树T存在 
功能说明：将二叉树T置空，并释放所有结点的空间。
返回值类型：status
********************************************************************/
status DestroyBiTree(BiTree &T)
{
    if( T==NULL )			//T为空树（结束条件） 
        return OK;
    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    free(T);
    T=NULL;
    return OK;
}

/*******************************************************************
函数名称：BiTreeDepth
初始条件：二叉树T存在 
功能说明：求二叉树T深度并返回深度值
返回值类型：int 
********************************************************************/
int BiTreeDepth(BiTree T)
{
    if( T==NULL )					//T为空树（结束条件） 
        return 0;
    int ld=BiTreeDepth(T->lchild)+1;
    int rd=BiTreeDepth(T->rchild)+1;
    return (ld>rd)?ld:rd;			//类似max函数 
}

/*******************************************************************
函数名称：LocateNode
初始条件：二叉树T存在 
功能说明：e是和T中结点关键字类型相同的给定值；根据e查找符合条件的结点
，返回该结点指针，如无关键字为e的结点，返回NULL。
返回值类型：BiTree 
********************************************************************/
BiTNode* LocateNode(BiTree T,KeyType e)
{
    if( !T )			//T为空树（结束条件） 
        return NULL;
    if( T->data.key==e )
        return T;
    //左右子树依次查询 
    pre=T;
    BiTree lt=LocateNode(T->lchild,e);
    if( lt )
        return lt;
    pre=T;
    BiTree rt=LocateNode(T->rchild,e);
    return rt;
}

/*******************************************************************
函数名称：Assign
初始条件：二叉树T存在 
功能说明：e是和T中结点关键字类型相同的给定值；查找结点关键字等于e的结
点，将该结点值修改成value，返回OK（要求结点关键字保持唯一性）。如果查
找失败，返回ERROR。
返回值类型：status
辅助函数：桶排序、先序遍历、结点查找函数 
********************************************************************/
status bullsort_a(int def[]){	//桶排序 
    for( int i=1 ; i<1000 ; i++ )
        if( def[i]>1 )
            return ERROR;
    return OK;
}
void PreOrder_a(BiTree T)		//先序遍历 
{
    if (T)
    {
        num[T->data.key]++;
        PreOrder_a(T->lchild);
        PreOrder_a(T->rchild);
    }
}
status Assign(BiTree &T,KeyType e,TElemType value)
{
    BiTree a=LocateNode(T,e);	//先定位 
    if( !a )					//未找到结点 
        return ERROR;
    TElemType t=a->data;
    a->data=value;
    PreOrder_a(T);					//先序遍历 
    if( bullsort_a(num)==ERROR ){	//关键字重复 
        a->data=t;
        return ERROR;
    }
    return OK;
}

/*******************************************************************
函数名称：GetSibling
初始条件：二叉树T存在 
功能说明：e是和T中结点关键字类型相同的给定值；查找结点关键字等于e的结
点的兄弟结点，返回其兄弟结点指针。如果查找失败，返回NULL。
返回值类型：BiTree
********************************************************************/
BiTNode* GetSibling(BiTree T,KeyType e)
{
    if( !T ){					//T为空树 
        pre=T;					//使前驱结点为T 
        return NULL;
    }
    if( T->data.key==e ){
        if( !pre )
            return NULL;
        if( pre->lchild==T )
            return pre->rchild;
        else
            return pre;
    }
    //先后遍历左右子树 
    pre=T;
    BiTree a=GetSibling(T->lchild,e);
    if( a )
        return a;
    pre=T->lchild;
    BiTree b=GetSibling(T->rchild,e);
    return b;
}

/*******************************************************************
函数名称：InsertNode
初始条件：二叉树T存在 
功能说明：e是和T中结点关键字类型相同的给定值，LR为0或1，c是待插入结点；
根据LR为0或者1，插入结点c到T中，作为关键字为e的结点的左或右孩子结点，
结点e的原有左子树或右子树则为结点c的右子树，返回OK。如果插入失败，返回
ERROR。特别地，当LR为-1时，作为根结点插入，原根结点作为c的右子树。
返回值类型：status
辅助函数：先序遍历函数 
********************************************************************/
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
{
    PreOrder_a(T);
    if( num[c.key] )		//插入值重复 
        return ERROR;
    if( T==NULL )			//T为空树 
        return ERROR;
    if( LR==-1 ){			//根节点插入 
        BiTree NewNode=(BiTree)malloc(sizeof(BiTNode));
        NewNode->data=c;
        BiTree t=T;
        NewNode->rchild=t;NewNode->lchild=NULL;
        T=NewNode;
        return OK;
    }
    if( T->data.key==e ){
        BiTree a;
        BiTree NewNode=(BiTree)malloc(sizeof(BiTNode));
        NewNode->data=c;NewNode->lchild=NULL;NewNode->rchild=NULL;
        if( LR==0 ){
            a=T->lchild;
            T->lchild=NewNode;
        }
        else if( LR==1 ){
            a=T->rchild;
            T->rchild=NewNode;
        }
        NewNode->rchild=a;
        return OK;
    }
    //先后遍历左右子树 
    pre=T;
    int a=InsertNode(T->lchild,e,LR,c);
    if( a==OK )
        return OK;
    pre=T;
    return InsertNode(T->rchild,e,LR,c);
}

/*******************************************************************
函数名称：DeleteNode
初始条件：二叉树T存在 
功能说明：e是和T中结点关键字类型相同的给定值。删除T中关键字为e的结点；
同时，根据该被删结点的度进行讨论：
1.如关键字为e的结点度为0，删除即可；
2.如关键字为e的结点度为1，用关键字为e的结点孩子代替被删除的e位置；
3.如关键字为e的结点度为2，用e的左子树（简称为LC）代替被删除的e位置，
将e的右子树（简称为RC）作为LC中最右节点的右子树。
成功删除结点后返回OK，否则返回ERROR。
返回值类型：status
辅助函数：结点查找函数 
********************************************************************/
status DeleteNode(BiTree &T,KeyType e)
{
    pre=NULL;
    BiTree a=LocateNode(T,e);		//定位结点 
    if( !a )						//定位失败 
        return ERROR;
    if( !pre ){						//无前驱（删除根节点） 
        if( !T->lchild ){
            free(T);
            return OK;
        }
        if( T->rchild ){
            BiTree t=T->lchild;
            while(t->rchild)
                t=t->rchild;
            t->rchild=T->rchild;
        }
        BiTree t=T;					//更新根节点 
        T=T->lchild;
        free(t);
        return OK;
    }
    if( !a->lchild&&!a->rchild ){	//情况1，结点度为0 
        if( a==pre->lchild )
            pre->lchild=NULL;
        if( a==pre->rchild )
            pre->rchild=NULL;
        free(a);
        return OK;
    }
    if( !a->lchild&&a->rchild ){	//情况2.1，结点度为1，没有左孩子 
        BiTree b=a->rchild;
        if( pre->rchild==a )
            pre->rchild=b;
        if( pre->lchild==a )
            pre->lchild=b;
        free(a);
        return OK;
    }
    if( !a->rchild&&a->lchild ){	//情况2.2，结点度为1，没有右孩子 
        BiTree b=a->lchild;
        if( pre->rchild==a )
            pre->rchild=b;
        if( pre->lchild==a )
            pre->lchild=b;
        free(a);
        return OK;
    }
    if( a->rchild&&a->lchild ){		//情况3，结点度为2 
        BiTree t=a->lchild;
        while(t->rchild)
            t=t->rchild;
        t->rchild=a->rchild;
        BiTree b=a->lchild;
        if( a==pre->rchild )
            pre->rchild=b;
        if( a==pre->lchild )
            pre->lchild=b;
        free(a);
        return OK;
    }
}

/*******************************************************************
函数名称：PreOrderTraverse
初始条件：二叉树T存在 
功能说明：对二叉树T进行先序遍历，Visit是一个函数指针的形参（可使用该
函数对结点操作），对每个结点调用函数Visit访问一次且一次。
返回值类型：status
辅助函数：visit 
********************************************************************/
void visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
}
status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    if( T ){
        visit(T);
        PreOrderTraverse(T->lchild,visit);
        PreOrderTraverse(T->rchild,visit);
    }
    return OK;
}

/*******************************************************************
函数名称：InOrderTraverse
初始条件：二叉树T存在 
功能说明：对二叉树T进行中序遍历，Visit是一个函数指针的形参（可使用该
函数对结点操作），对每个结点调用函数Visit访问一次且一次。
返回值类型：status
********************************************************************/
//status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//{
//    if( T ){
//        InOrderTraverse(T->lchild,visit);
//        visit(T);
//        InOrderTraverse(T->rchild,visit);
//    }
//    return OK;
//}
status InOrderTraverse(BiTree T,void (*visit)(BiTree)){
	stack[top++]=T;
    while(top){
        while(stack[top-1]){
            BiTree t=stack[top-1];
            stack[top++]=t->lchild;
        }
        top--;
        if(top){
            BiTree t=stack[--top];
            visit(t);
            stack[top++]=t->rchild;
        }
    }
}

/*******************************************************************
函数名称：PostOrderTraverse
初始条件：二叉树T存在 
功能说明：对二叉树T进行后序遍历，Visit是一个函数指针的形参（可使用该
函数对结点操作），对每个结点调用函数Visit访问一次且一次。
返回值类型：status
********************************************************************/
status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    if( T ){
        PostOrderTraverse(T->lchild,visit);
        PostOrderTraverse(T->rchild,visit);
        visit(T);
    }
    return OK;
}

/*******************************************************************
函数名称：LevelOrderTraverse
初始条件：二叉树T存在 
功能说明：对二叉树T进行按层遍历，Visit是一个函数指针的形参（可使用该
函数对结点操作），对每个结点调用函数Visit访问一次且一次。
返回值类型：status
********************************************************************/
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    if(!T)
        return ERROR;
    if(T->lchild)
        queue[tail++]=T->lchild;		//借用队列 
    if(T->rchild)
        queue[tail++]=T->rchild;
    visit(T);
    if( tail!=front )
        LevelOrderTraverse(queue[front++],visit);
    return OK;
}

status LevelOrder_c(BiTree T,void (*visit)(BiTree))
{
    if(!T)
        return ERROR;
    if(T->rchild)
        queue[tail++]=T->rchild;		//借用队列 
    if(T->lchild)
        queue[tail++]=T->lchild;
    visit(T);
    if( tail!=front )
        LevelOrderTraverse(queue[front++],visit);
    return OK;
}

/*******************************************************************
函数名称：SaveBiTree
初始条件：二叉树T存在 
功能说明：将二叉树T写到文件名为FileName的文件中，返回OK
返回值类型：status
辅助函数：先序遍历 
********************************************************************/
void PreOrder_b(BiTree T){
    if(T){
        array[cnt++]=T;
        PreOrder_b(T->lchild);
        PreOrder_b(T->rchild);
    }
    else
        array[cnt++]=NULL;
}

status SaveBiTree(BiTree T, char FileName[])
{
	cnt=0;
    PreOrder_b(T);
    FILE *fp;
    fp=fopen(FileName,"w");
    for( int i=0 ; i<cnt ; i++ ){
        if( array[i]==NULL )
            fprintf(fp,"0 null ");
        else{
            fprintf(fp,"%d ",array[i]->data.key);
            fprintf(fp,"%s ",array[i]->data.others);
        }
    }
    fclose(fp);
    return OK;
}

/*******************************************************************
函数名称：LoadBiTree
初始条件：二叉树T不存在或为空 
功能说明：读入文件名为FileName的结点数据，创建二叉树。
返回值类型：status
辅助函数：建立二叉树 
********************************************************************/
status LoadBiTree(BiTree &T,  char FileName[])
{
    FILE *fp;
    fp=fopen(FileName,"r");
    TElemType def[1000];
    cnt=0;
    while(fscanf(fp,"%d",&def[cnt].key)!=EOF)
        fscanf(fp,"%s",def[cnt++].others);
    def[cnt].key=-1;
    cnt=0;
    CreateBiTree(T,def);
    fclose(fp);
    return OK;
}

/*******************************************************************
函数名称：DFSMaxLength
初始条件：二叉树T存在 
功能说明：返回根节点到叶子节点的最大路径和 
返回值类型：int
********************************************************************/
int DFSMaxLength(BiTree T,int num){
	if( !T )
		return num;
	int lnum=DFSMaxLength(T->lchild,num+T->data.key);
	int rnum=DFSMaxLength(T->rchild,num+T->data.key);
	return (lnum>rnum)?lnum:rnum;
}

/*******************************************************************
函数名称：LowerPublicAncestor
初始条件：二叉树T存在 
功能说明：返回二叉树中关键字为e1和关键字为e2结点的最近公共祖先 
返回值类型：BiTree 
********************************************************************/
BiTree LowerPublicAncestor( BiTree T , int e1 , int e2 ){
	if( !T )
		return NULL;
	if( (T->data.key==e1)||(T->data.key==e2) )
		return T;
	BiTree t1=LowerPublicAncestor(T->lchild,e1,e2);
	BiTree t2=LowerPublicAncestor(T->rchild,e1,e2);
	if( t1&&t2 )		//两边均可通过遍历访问结点 
		return T;		//返回它们的公共祖先 
	if( !t1&&!t2 )
		return NULL;
	if( t1 )			//只有一边可遍历访问结点 
		return t1;		//不改变公共祖先值继续返回 
	if( t2 )
		return t2; 
}

/*******************************************************************
函数名称：InvertTree 
初始条件：二叉树T存在 
功能说明：使二叉树所有节点的左右节点互换 
返回值类型：status 
********************************************************************/
status InvertTree( BiTree T ){
	if( !T )
		return OK;
	BiTree t1=T->lchild,t2=T->rchild;
	T->lchild=t2;
	T->rchild=t1;
	InvertTree(t1);InvertTree(t2);
	return OK;
} 
/*******************************************************************
函数名称：AddBiTree
初始条件：当前二叉树数目未超过上限 
功能说明：添加一个新的二叉树，赋予其树名 
返回值类型：status
********************************************************************/
status AddBiTree(LISTS &tree,char listname[]){
	if( tree.length>=10 )	//超出Lists最大范围 
        return ERROR;		//出错
	//初始化操作 
	for( int j=1 ; j<=tree.length ; j++ )
    	if( !strcmp(listname,tree.elem[j].name) )
    		return ERROR;
    tree.length++;
    tree.elem[tree.length].T=(BiTree)malloc(sizeof(BiTNode));
    tree.elem[tree.length].T->lchild=NULL;
	tree.elem[tree.length].T->rchild=NULL;
	tree.elem[tree.length].T->data.key=-1;
    int i;
    for( i=0 ; listname[i]!='\0' ; i++ )
    	tree.elem[tree.length].name[i]=listname[i];
    tree.elem[tree.length].name[i]='\0';
    return OK;
}


int DeleteBiTree(LISTS &tree,char listname[]){
	if( !tree.length )		//Lists为空 
		return INFEASIBLE;	//不可行
	for( int i=1 ; i<=tree.length ; i++ ){
        if( !strcmp(listname,tree.elem[i].name) ){
            //free(Lists.elem[i].L.elem);free(Lists.elem[i].name);
            for( int j=i ; j<tree.length ; j++ )
                tree.elem[j]=tree.elem[j+1];
            tree.elem[tree.length].T=NULL;
            tree.length--;
            return i;
        }
    }
    return ERROR; 
}

int ChooseBiTree(LISTS &tree, char listname[]){
	if( !tree.length )		//Lists为空 
		return INFEASIBLE;	//不可行 
    for( int i=1 ; i<=tree.length ; i++ ){
        if( !strcmp(listname,tree.elem[i].name) )
            return i;
    }
    return 0;
}

void PreOrder_c(BiTree T,void (*visit)(BiTree)){
	if( T ){
        visit(T);
        PreOrderTraverse(T->rchild,visit);
        PreOrderTraverse(T->lchild,visit);
    }
}
void InOrder_c(BiTree T,void (*visit)(BiTree)){
	if( T ){
        PreOrderTraverse(T->rchild,visit);
        visit(T);
        PreOrderTraverse(T->lchild,visit);
    }
}
void PostOrder_c(BiTree T,void (*visit)(BiTree)){
	if( T ){
        PreOrderTraverse(T->rchild,visit);
        PreOrderTraverse(T->lchild,visit);
        visit(T);
    }
}
