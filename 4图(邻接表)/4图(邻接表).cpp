#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h> 
#include<windows.h>

/*************************预定义*************************/
#define TRUE 1					//判断正确 
#define FALSE 0					//判断错误 
#define OK 1					//成功 
#define ERROR 0					//逻辑错误 
#define INFEASIBLE -1			//不可行错误 
#define OVERFLOW -2				//溢出错误 
#define MAX_VERTEX_NUM 20		//最大结点数 

typedef int status;							//状态类型 
typedef int KeyType; 						//关键字类型 
typedef enum {DG,DN,UDG,UDN} GraphKind;		//图类型 

typedef struct {
     KeyType  key;
     char others[20];
} VertexType; 					//顶点类型定义


typedef struct ArcNode {       	//表结点类型定义
	 int adjvex;              	//顶点位置编号 
	 struct ArcNode  *nextarc;	//下一个表结点指针
} ArcNode;

typedef struct VNode{			//头结点及其数组类型定义
	 VertexType data;       	//顶点信息
	 ArcNode *firstarc; 	 	//指向第一条弧
	} VNode,AdjList[MAX_VERTEX_NUM];

typedef  struct {  				//邻接表的类型定义
    AdjList vertices;     	 	//头结点数组
    int vexnum,arcnum;   	  	//顶点数、弧数
    int  kind;        			//图的类型
   } ALGraph;

typedef struct{  				//线性表的集合类型定义
    struct { 
		char name[30];			//表名 
        ALGraph G;    			//线性表内容 
    } elem[11];			
    int length;					//表长 
}LISTS;
   
//全局变量
char flag[100]={0};				//判断结点是否遍历过 
int adjvex[100];				//存储结点位序 
int nums=0;						//存储节点数目 
int Min=100;					//最短路径 

/********************************************************/

/*************************函数表*************************/
status InsertArc(ALGraph &G,KeyType v,KeyType w);
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2]);
status DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G,KeyType u);
status PutVex(ALGraph &G,KeyType u,VertexType value);
int FirstAdjVex(ALGraph G,KeyType u);
int NextAdjVex(ALGraph G,KeyType v,KeyType w); 
status InsertVex(ALGraph &G,VertexType v);
status DeleteVex(ALGraph &G,KeyType v);
status DeleteArc(ALGraph &G,KeyType v,KeyType w);
void visit(VertexType v);
void dfs(ALGraph &G,int v,void (*visit)(VertexType));
status DFSTraverse(ALGraph &G,void (*visit)(VertexType));
status BFSTraverse(ALGraph &G,void (*visit)(VertexType)); 
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]); 
status AddGraph(LISTS &graph,char graphname[]); 
int DeleteGraph(LISTS &graph,char graphname[]);
int ChooseGraph(LISTS &graph,char graphname[]);
status VerticesSetLessThanK(ALGraph &G,KeyType v,int k);
void dfs_lessk(ALGraph &G,int k,int adj);
int ShortestPathLength(ALGraph &G,KeyType v,KeyType w);
void dfs_connect(ALGraph &G,char flag[],int v);
int ConnectedComponentsNums(ALGraph &G);
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
	
	int op=1;			//用户操作选项
	char filename[50];	//存储文件名
	char graphname[50];	//存储图名
	int lp=1; 			//记录当前处理的图指针
	int cntnum=0;		//记录操作数目
	int kv,kw,ku;		//记录关键字值
	VertexType input[100];
	int VR[100][2];		//弧数组 
	
	//多图管理
	LISTS graph;		//线性表集合管理多图
	graph.length=0;		//长度初始化
	
	//图初始化
	for( int i=0 ; i<11 ; i++ ){
		graph.elem[i].G.arcnum=0; 		//结点与弧数目归零 
		graph.elem[i].G.vexnum=0;
		graph.elem[i].G.kind=0;
	}
	
	//名称初始化
	char defaultname[50]="初始图";		//默认名称
	for( int i=0 ; defaultname[i]!='\0' ; i++ )
		graph.elem[1].name[i]=defaultname[i];
		
	/****************************************************************/
	/*						   菜单主体 							*/
	/****************************************************************/
	
	while(op){
		system("cls");
	    printf("\n\n");
		printf("	  \t\t\t\t图菜单\t\t\n\n");
		printf(" \t可在最多10个图进行多图操作，二叉树尚未初始化，名称默认为“图”\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf(" *1. 创建图         \t\t\t7.  插入顶点\t\t\t\t*\n");
		printf(" *2. 销毁图       \t\t\t8.  删除顶点\t\t\t\t*\n");
		printf(" *3. 查找顶点         \t\t\t9.  插入弧 \t\t\t\t*\n");
		printf(" *4. 顶点赋值         \t\t\t10. 删除弧\t\t\t\t*\n");
		printf(" *5. 获得第一邻接点        \t\t11. 深度优先搜索\t\t\t*\n");
		printf(" *6. 获得下一邻接点           \t\t12. 广度优先搜索\t\t\t*\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf(" *13.图文件存储          \t\t14. 图文件读取\t\t\t\t*\n");
		printf(" *15.距离小于k的顶点集合 \t\t16. 顶点间最短路径的长度\t\t*\n");
		printf(" *17.图的连通分量        \t\t18. 添加图\t\t\t\t*\n");
		printf(" *19.移除图          \t\t\t20. 选择要操作的图\t\t\t*\n");
		printf(" *0. 退出\t\t\t\n");
		printf(" --------------------------------------------------------------powered by 严浩洋\n");
		printf("当前操作的图：图%d：%s\n\n",lp,graph.elem[lp].name);
		printf("请输入数字0~20以选择你的操作:");
		scanf("%d",&op);//选择op的值,用于switch
		printf("\n");
		int i=0;
		switch(op){
			
			case 0:
				//结束操作
				break;
			
			case 1:
				//创建图
				if( graph.elem[lp].G.arcnum||graph.elem[lp].G.vexnum ){
					printf("建立失败！图已存在！");
					break;
				}
				
				//输入顶点数组 
				printf("当前正在进行创建图操作，请输入图的顶点与弧数组：\n");
				
				do{
					scanf("%d %s",&input[i].key,input[i].others);
				}while(input[i++].key!=-1);
				
				//超过二十个点 
				if( i>20 ){
					printf("\n创建失败！超过二十个点！");
					break;
				}
				
				//空图 
				else if( i<=1 ){
					printf("\n创建失败！结点数为0！");
					break;
				}
				
				//输入弧数组 
				i=0;
				do{
					scanf("%d %d",&VR[i][0],&VR[i][1]);
				}while(VR[i++][0]!=-1);
				
				if( CreateCraph(graph.elem[lp].G,input,VR)==ERROR )
					printf("\n创建失败！请检查关键字是否重复！");
				else{
					printf("\n创建成功！"); 
					if( graph.elem[lp].G.kind==0 )
						graph.length++;
				}
				break;
			
			case 2:
				//销毁图
				if( !graph.elem[lp].G.vexnum ){
					printf("销毁失败！图不存在！");
					break;
				}
				DestroyGraph(graph.elem[lp].G);
				printf("销毁成功！");
				graph.length--;
				break;
			
			case 3:
				//查找顶点
				if( graph.elem[lp].G.vexnum==0 ){
					printf("该图为空，无法进行操作！");
					break;
				}
				printf("当前正在进行查找顶点操作，请输入要查找顶点的关键字：");
				scanf("%d",&ku);
				int ret3;
				if( (ret3=LocateVex(graph.elem[lp].G,ku))==-1 )
					printf("\n未查询到您想要的结点！");
				else{
					printf("\n您查找结点的位序为%d,",ret3);
					printf("值为：%d %s",graph.elem[lp].G.vertices[ret3].data.key,graph.elem[lp].G.vertices[ret3].data.others);
				}
				break;
			
			case 4:
				//顶点赋值 
				if( graph.elem[lp].G.vexnum==0 ){
					printf("该图为空，无法进行操作！");
					break;
				}
				printf("当前正在进行顶点赋值操作，请输入要赋值顶点的关键字及要赋的值：");
				scanf("%d %d %s",&ku,&input[0].key,input[0].others);
				if( PutVex(graph.elem[lp].G,ku,input[0])==ERROR )
					printf("\n赋值失败！请检查关键字是否重复或查询结点是否存在！");
				else
					printf("\n赋值成功！");
				break;
			
			case 5:
				//获得第一邻接点
				if( graph.elem[lp].G.vexnum==0 ){
					printf("该图为空，无法进行操作！");
					break;
				}
				printf("当前正在进行获得第一邻接点操作，请输入要查找结点的关键字：");
				scanf("%d",&ku);
				int ret5;
				if( (ret5=FirstAdjVex(graph.elem[lp].G,ku))==-1 )
					printf("\n您要查找的结点不存在！");
				else{
					printf("\n您要查找的结点的第一临界点位序为：%d,值为：",ret5);
					printf("%d,%s",graph.elem[lp].G.vertices[ret5].data.key,graph.elem[lp].G.vertices[ret5].data.others);
				}
				break;
			
			case 6:
				//获得下一邻接点
				if( graph.elem[lp].G.vexnum==0 ){
					printf("该图为空，无法进行操作！");
					break;
				}
				printf("当前正在进行获得下一邻接点操作，请输入要查找结点的关键字：");
				scanf("%d %d",&kv,&kw);
				int ret6;
				if( (ret6=NextAdjVex(graph.elem[lp].G,kv,kw))==-1 )
					printf("\n获取失败！请检查结点是否存在或是否无下一邻接点！");
				else{
					printf("\n您要查找的结点的下一临界点位序为：%d,值为：",ret6);
					printf("\n%d,%s",graph.elem[lp].G.vertices[ret6].data.key,graph.elem[lp].G.vertices[ret6].data.others);
				}
				break;
			
			case 7:
				//插入顶点
				if( graph.elem[lp].G.vexnum==0 ){
					printf("该图为空，无法进行操作！");
					break;
				}
				if( graph.elem[lp].G.vexnum>=20 ){
					printf("结点数已达到最大，无法插入！");
					break;
				}
				printf("当前正在进行插入结点操作，请输入要插入结点的值：");
				scanf("%d %s",&input[0].key,input[0].others); 
				if( InsertVex(graph.elem[lp].G,input[0])==ERROR )
					printf("\n插入失败！请检查关键字是否重复！");
				else
					printf("插入成功！");
				break;
			
			case 8:
				//删除顶点
				if( graph.elem[lp].G.vexnum==0 ){
					printf("该图为空，无法进行操作！");
					break;
				}
				if( graph.elem[lp].G.vexnum==1 ){
					printf("该图只有一个结点，无法删除！");
					break;
				}
				printf("当前正在进行删除结点操作，请输入要删除结点的关键字：");
				scanf("%d",&ku);
				if( DeleteVex(graph.elem[lp].G,ku)==ERROR )
					printf("\n删除失败！请检查结点是否存在！");
				else
					printf("\n删除成功！");
				break;
			
			case 9:
				//插入弧
				if( graph.elem[lp].G.vexnum==0 ){
					printf("该图为空，无法进行操作！");
					break;
				}
				printf("当前正在进行插入弧操作，请输入要插入弧端点的关键字：");
				scanf("%d %d",&kv,&kw);
				if( InsertArc(graph.elem[lp].G,kv,kw)==ERROR )
					printf("\n插入失败！请检查顶点是否存在或顶点之间已存在弧");
				else
					printf("\n插入成功！");
				break;
			
			case 10:
				//删除弧
				if( graph.elem[lp].G.vexnum==0 ){
					printf("该图为空，无法进行操作！");
					break;
				}
				printf("当前正在进行删除弧操作，请输入要删除弧端点的关键字：");
				scanf("%d %d",&kv,&kw);
				if( DeleteArc(graph.elem[lp].G,kv,kw)==ERROR )
					printf("\n删除失败！请检查顶点是否存在或顶点之间不存在弧");
				else
					printf("\n删除成功！");
				break;
			
			case 11:
				//深度优先搜索
				if( graph.elem[lp].G.vexnum==0 ){
					printf("该图为空，无法进行操作！");
					break;
				}
				for( int i=0 ; i<100 ; i++ )
					flag[i]=0;
				printf("遍历结果为：\n");
				DFSTraverse(graph.elem[lp].G,visit);
				break; 
			
			case 12:
				//广度优先搜索
				if( graph.elem[lp].G.vexnum==0 ){
					printf("该图为空，无法进行操作！");
					break;
				}
				printf("遍历结果为：\n");
				BFSTraverse(graph.elem[lp].G,visit);
				break;
			
			case 13:
				//存储图
				if( graph.elem[lp].G.vexnum==0 ){
					printf("该图为空，无法进行操作！");
					break;
				}
				printf("当前正在进行存储图操作，请输入要存储的文件名：");
				scanf("%s",filename);
				SaveGraph(graph.elem[lp].G,filename);
				printf("\n存储成功！");
				break;
			
			case 14:
				//读取图
				if( graph.elem[lp].G.vexnum ){
					printf("该图不为空，无法进行操作！");
					break;
				}
				printf("当前正在进行图的读取操作，请输入文件名：\n");
				scanf("%s",filename);
				LoadGraph(graph.elem[lp].G,filename);
				if( graph.elem[lp].G.kind==0 )
					graph.length++;
				printf("\n读取成功！");
				break;
				
			case 15:
				//距离小于k的顶点集合
				if( !graph.elem[lp].G.vexnum ){
					printf("该图为空，无法进行操作！");
					break;
				}
				printf("当前正在进行返回距离小于k的顶点集合操作，请输入k和起点关键字：");
				int k;
				nums=0;
				for( int i=0 ; i<100 ; i++ ){
					adjvex[i]=-1;
					flag[i]=0;
				}
				scanf("%d %d",&k,&ku);
				if( VerticesSetLessThanK(graph.elem[lp].G,ku,k)==ERROR ){
					printf("\n查找失败！请检查结点是否存在！");
					break;
				}
				else{
					printf("\n距离小于k的顶点为：\n");
					for( int i=0 ; adjvex[i]!=-1 ; i++ )
						printf("%d,%s\n",graph.elem[lp].G.vertices[adjvex[i]].data.key,graph.elem[lp].G.vertices[adjvex[i]].data.others);
				}
				break;
			
			case 16:
				//顶点间最短路径长度
				if( !graph.elem[lp].G.vexnum ){
					printf("该图为空，无法进行操作！");
					break;
				}
				int ret16;
				for( int i=0 ; i<100 ; i++ )
					flag[i]=0;
				printf("当前正在进行返回顶点间最短路径长度操作操作，请输入起点和终点关键字：");
				scanf("%d %d",&kv,&kw);
				if( (ret16=ShortestPathLength(graph.elem[lp].G,kv,kw))==ERROR )
					printf("\n查找失败！请检查结点是否存在！");
				else if( ret16==10000 )
					printf("\n两点之间不存在路径！");
				else
					printf("\n最短路径长度为：%d",ret16);
				break;
			
			case 17:
				//图的连通分量 
				if( !graph.elem[lp].G.vexnum ){
					printf("该图为空，无法进行操作！");
					break;
				}
				printf("当前图的连通分量为：%d",ConnectedComponentsNums(graph.elem[lp].G));
				break;
			
			case 18:
				//添加图
				if( graph.length>=10 ){
					printf("当前图的数目已达上限，无法添加！");
					break;
				}
				printf("当前正在进行添加图操作，请输入图名称：");
				scanf("%s",graphname);
				if( AddGraph(graph,graphname)==ERROR )
					printf("\n当前名称已存在，换一个名字吧！");
				else
					printf("\n添加成功！");
				break;
			
			case 19:
				//移除图
				if( graph.length<=0 ){
					printf("当前已没有图，无法进行移除操作！");
					break;
				} 
				int ret19;
				printf("当前正在进行移除图操作，请输入移除图的名称：");
				scanf("%s",graphname);
				if( (ret19=DeleteGraph(graph,graphname))==0 )
					printf("\n删除失败！请检查图是否存在！");
				else{
					printf("\n删除成功！");
					if( ret19==lp ){
						printf("由于您删除了当前操作的图，下次操作默认对图1进行！");
						lp=1;
					}
				}
				break;
			
			case 20:
				//选择要操作的图
				printf("当前正在进行选择图操作，请输入要选择的图的名称：");
				scanf("%s",graphname);
				int ret20;
				if( (ret20=ChooseGraph(graph,graphname))==0 )
					printf("\n选择失败！未找到您输入的图！");
				else{
					lp=ret20;
					printf("\n选择成功！即将对图%d进行操作！",lp);
				}
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

/********************************************************/

/********************************************************
函数名：  CreateCraph
初始条件：无向图G不存在，给定结点与邻接数组 
函数功能：根据顶点序列V和关系对序列VR构造一个无向图G（要
求无向图G中各顶点关键字具有唯一性，结点数目不多于MAX_VERT
EX_NUM）。
返回类型：status 
辅助函数：插入弧函数 
********************************************************/
status InsertArc(ALGraph &G,KeyType v,KeyType w)
{
    int t=G.vexnum,a=-1,b=-1;			//结点数与v和w的下标 
    
    //判断v和w是否存在 
    for( int i=0 ; i<t ; i++ ){
        if( G.vertices[i].data.key==v ){
            a=i;
            break;
        }
    }
    if(a==-1)
        return ERROR;
    for( int i=0 ; i<t ; i++ ){
        if( G.vertices[i].data.key==w ){
            b=i;
            break;
        }
    }
    if(b==-1)
        return ERROR;
        
    //判断原先是否已存在相应的边 
    ArcNode *arc=G.vertices[a].firstarc;
    while(arc){
        if( arc->adjvex==b )
            return ERROR;
        arc=arc->nextarc;
    }
    
    //插入弧（双向） 
    G.arcnum++;
    ArcNode *insert=(ArcNode*)malloc(sizeof(ArcNode));
    insert->adjvex=b;
    insert->nextarc=G.vertices[a].firstarc;
    G.vertices[a].firstarc=insert;
    ArcNode *insert2=(ArcNode*)malloc(sizeof(ArcNode));
    insert2->adjvex=a;
    insert2->nextarc=G.vertices[b].firstarc;
    G.vertices[b].firstarc=insert2;
    return OK;
}

status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
{
    //计算边数和弧数
    int vexnum=0,arcnum=0;
    for( int i=0 ; V[i].key!=-1 ; i++ )
        vexnum++;
    for( int i=0 ; VR[i][0]!=-1 ; i++ )
        arcnum++;

    //判断关键字重复
    char bull[1000]={0};
    for( int i=0 ; i<vexnum ; i++ ){
        bull[V[i].key]++;
        if( bull[V[i].key]>1 )
            return ERROR;
    }

    //特判：空图
    if( vexnum==0 )
        return ERROR;
    //特判：超过二十个点
    if( vexnum>20 )
        return ERROR;

    //判断弧没有错误
    for( int i=0 ; i<arcnum ; i++ )
        if( !bull[VR[i][0]]||!bull[VR[i][1]] )
            return ERROR;

    //更改图相应值
    G.vexnum=vexnum;
    for( int i=0 ; i<vexnum ; i++ ){
        G.vertices[i].data=V[i];
        G.vertices[i].firstarc=NULL;
    }
    
    //建立边
    for( int i=0 ; i<arcnum ; i++ ){
        InsertArc(G,VR[i][0],VR[i][1]);
    }
    return OK;
}

/********************************************************
函数名：  DestroyGraph
初始条件：无向图G存在
函数功能：将邻接表表示的无向图销毁，并释放所有表结点的空间。
返回类型：status 
********************************************************/
status DestroyGraph(ALGraph &G)
{
    int t=G.vexnum;
    
    //从firstarc依次释放空间 
    for( int i=0 ; i<t ; i++ ){
        ArcNode *a=G.vertices[i].firstarc;
        while(a){
            ArcNode *next=a->nextarc;
            free(a);
            a=next;
        }
    }
    
    //相关值归零 
    G.vexnum=0;G.arcnum=0;
    return OK;
}

/********************************************************
函数名：  LocateVex
初始条件：无向图G存在
函数功能：u是和G中顶点关键字类型相同的给定值；根据u查找顶
点，成功时返回关键字为u的顶点位置序号（简称位序），否则返
回-1。
返回类型：int
********************************************************/
int LocateVex(ALGraph G,KeyType u)
{
    int t=G.vexnum;
    
    //遍历顶点数组 
    for( int i=0 ; i<t ; i++ )
        if( u==G.vertices[i].data.key )
            return i;
    return -1;
}

/********************************************************
函数名：  PutVex
初始条件：无向图G存在
函数功能：u是和G中顶点关键字类型相同的给定值；操作结果是
对关键字为u的顶点赋值value（要求关键字具有唯一性）。成功
赋值返回OK，否则返回ERROR。
返回类型：status
********************************************************/
status PutVex(ALGraph &G,KeyType u,VertexType value)
{
    int t=G.vexnum;
    
    int num[100]={0};		//判定关键字重复数组 
    for( int i=0 ; i<t ; i++ )
        num[G.vertices[i].data.key]++;
    if( u!=value.key&&num[value.key] )
        return ERROR;		//关键字重复 
    for( int i=0 ; i<t ; i++ ){
        if( u==G.vertices[i].data.key ){
            G.vertices[i].data=value;
            return OK;
        }
    }
    return ERROR;
}

/********************************************************
函数名：  FirstAdjVex
初始条件：无向图G存在
函数功能：u是和G中顶点关键字类型相同的给定值；返回关键字
为u的顶点第一个邻接顶点位置序号（简称位序），否则返回-1。
返回类型：int
********************************************************/
int FirstAdjVex(ALGraph G,KeyType u)
{
    int t=G.vexnum,a;
    
    //遍历顶点数组 
    for( int i=0 ; i<t ; i++ ){
        if( u==G.vertices[i].data.key ){
            return G.vertices[i].firstarc->adjvex;
        }
    }
    return -1;
}

/********************************************************
函数名：  NextAdjVex
初始条件：无向图G存在
函数功能：v和w是G中两个顶点的位序，v对应G的一个顶点,w对应
v的邻接顶点；操作结果是返回v的（相对于w）下一个邻接顶点的
位序；如果w是最后一个邻接顶点，或v、w对应顶点不存在，则返
回-1。
返回类型：int
********************************************************/
int NextAdjVex(ALGraph G,KeyType v,KeyType w)
{
    int t=G.vexnum,a=-1;
    
    //寻找对应v的结点 
    for( int i=0 ; i<t ; i++ )
        if( v==G.vertices[i].data.key ){
            a=i;
            break;
        }
    if( a==-1 )
        return -1;
        
    //在v的邻接结点中寻找w 
    ArcNode *arc=G.vertices[a].firstarc;
    while( arc ){
        if( G.vertices[arc->adjvex].data.key==w )
            break;
        arc=arc->nextarc;
    }
    if( !arc )
        return -1;
    if( !(arc->nextarc) )   //最后一个邻接顶点
        return -1;
    return arc->nextarc->adjvex;
}

/********************************************************
函数名：  InsertVex
初始条件：无向图G存在
函数功能：在图G中插入新顶点关v（要求关键字具有唯一性，注意
判断顶点个数是否已满）。成功返回OK，否则返回ERROR。
返回类型：status
********************************************************/
status InsertVex(ALGraph &G,VertexType v)
{
    //判断顶点数是否超过最大值
    if( G.vexnum>=MAX_VERTEX_NUM )
        return ERROR;
    
    int t=G.vexnum;
    
    //判断关键字唯一性
    int num[1000]={0};
    for( int i=0 ; i<t ; i++ )
        num[G.vertices[i].data.key]++;
    if( num[v.key] )
        return ERROR;
    G.vertices[t].data=v;
    G.vexnum++;
    return OK;
}

/********************************************************
函数名：  DeleteVex
初始条件：无向图G存在
函数功能：v是和G中顶点关键字类型相同的给定值；操作结果是在
图G中删除关键字v对应的顶点以及相关的弧。成功返回OK，否则返
回ERROR。
返回类型：status
********************************************************/
status DeleteVex(ALGraph &G,KeyType v)
{
    int t=G.vexnum,a=-1;

    //顶点数组移位
    for( int i=0 ; i<t ; i++ )
        if( G.vertices[i].data.key==v )
            a=i;
    if( a==-1 )
        return ERROR;
    if( t==1 )
        return ERROR;
    ArcNode *arc=G.vertices[a].firstarc;
    while(arc){
        ArcNode *c=arc->nextarc;
        free(arc);
        arc=c;
    }
    for( int i=a ; i<t-1 ; i++ )
        G.vertices[i]=G.vertices[i+1];
    G.vexnum--;t--;
    
    //遍历找相关弧
    for( int i=0 ; i<t ; i++ ){
        ArcNode *arc=G.vertices[i].firstarc,*pre=NULL,*usearc=NULL,*usepre=NULL;
        while( arc ){
            if( arc->adjvex==a ){
                usearc=arc;
                usepre=pre;
            }
            if( arc->adjvex>a )
                arc->adjvex--;
            pre=arc;
            arc=arc->nextarc;
        }
        if( !usearc )
            continue;
        G.arcnum--;
        if(usepre==NULL){
            G.vertices[i].firstarc=usearc->nextarc;
            free(usearc);
            continue;
        }
        if( !(usearc->nextarc) ){
            free(usearc);
            usepre->nextarc=NULL;
            continue;
        }
        usepre->nextarc=usearc->nextarc;
        free(usearc);
    }
    return OK;
}

/********************************************************
函数名：  DeleteArc
初始条件：无向图G存在
函数功能：v、w是和G中顶点关键字类型相同的给定值；操作结果
是在图G中删除弧<v,w>。成功返回OK，否则返回ERROR。
返回类型：status
********************************************************/
status DeleteArc(ALGraph &G,KeyType v,KeyType w)
{
    int t=G.vexnum,a=-1,b=-1;
    
    //遍历寻找v和w对应结点 
    for( int i=0 ; i<t ; i++ )
        if( G.vertices[i].data.key==v ){
            a=i;
            break;
        }
    for( int i=0 ; i<t ; i++ )
        if( G.vertices[i].data.key==w ){
            b=i;
            break;
        }
    if( a==-1||b==-1 )
        return ERROR;
    
    //删除弧（双向） 
    G.arcnum--;
    ArcNode *arc=G.vertices[a].firstarc,*pre=NULL;
    while(arc){
        if( arc->adjvex==b ){
            if( !pre ){
                G.vertices[a].firstarc=arc->nextarc;
                free(arc);
            }
            else{
                pre->nextarc=arc->nextarc;
                free(arc);
            }
            break;
        }
        pre=arc;
        arc=arc->nextarc;
    }
    if( !arc )		//未找到对应的弧，即v和w不邻接 
        return ERROR;
    arc=G.vertices[b].firstarc;pre=NULL;
    while(arc){
        if( arc->adjvex==a ){
            if( !pre ){
                G.vertices[b].firstarc=arc->nextarc;
                free(arc);
            }
            else{
                pre->nextarc=arc->nextarc;
                free(arc);
            }
            break;
        }
        pre=arc;
        arc=arc->nextarc;
    }
    return OK;
}

/********************************************************
函数名：  DFSTraverse 
初始条件：无向图G存在
函数功能：对图G进行深度优先搜索遍历，依次对图中的每一个顶
点使用函数visit访问一次，且仅访问一次。
返回类型：status
辅助函数：深度优先搜索函数 
********************************************************/
void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}

void dfs(ALGraph &G,int v,void (*visit)(VertexType)){
    ArcNode *arc=G.vertices[v].firstarc;
    visit(G.vertices[v].data);
    flag[v]=1;			//标记已遍历结点 
    while( arc ){
        if( !flag[arc->adjvex] )
            dfs(G,arc->adjvex,visit);
        arc=arc->nextarc;
    }
    return ;
}

status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
{
    int t=G.vexnum;
    for( int i=0 ; i<t ; i++ ){
        if( !flag[i] )
            dfs(G,i,visit);
    }
    return OK;
}

/********************************************************
函数名：  BFSTraverse 
初始条件：无向图G存在
函数功能：对图G进行广度优先搜索遍历，依次对图中的每一个顶
点使用函数visit访问一次，且仅访问一次。
返回类型：status
********************************************************/
status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
{
    int t=G.vexnum;
    
    char flag[100]={0};		//标记已遍历结点
	
	//构建队列 
    ArcNode *queue[100];int front=0,tail=0;
    
    //遍历阶段 
    for( int i=0 ; i<t ; i++ ){
        if( !flag[i] ){		//若结点未遍历过 
            visit(G.vertices[i].data);
            front=tail=0;	//队列初始化 
            queue[tail++]=G.vertices[i].firstarc;	//进队 
            while(front<tail){
                ArcNode* arc=queue[front++];
            	if( !arc )
            		break;
                if( !flag[arc->adjvex] ){
                    flag[arc->adjvex]=1;
                    visit(G.vertices[arc->adjvex].data);
                    arc=arc->nextarc;
                    while(arc){
                        queue[tail++]=arc;			//邻接结点全部进队 
                        arc=arc->nextarc;
                    }
                }
            }
        }
    }
    //这个大括号结尾真丑(bushi) 
    return OK;
}

/********************************************************
函数名：  SaveGrapgh 
初始条件：无向图G存在
函数功能：将图G写到文件名为FileName的文件中，返回OK
返回类型：status
********************************************************/
status SaveGraph(ALGraph G, char FileName[])
{
	//文件操作初始化 
    FILE *fp;
    fp=fopen(FileName,"w+");
    
    //文件内容数组 
    VertexType V[100];
    KeyType VR[100][2];
    
    //构造V和VR数组 
    char flag[100][100]={0};		//用于判断边是否重复 
    int num=0;
    for( int i=0 ; i<G.vexnum ; i++ )
        V[i]=G.vertices[i].data;
    for( int i=0 ; i<G.vexnum ; i++ ){
        ArcNode *arc=G.vertices[i].firstarc;
        while(arc){
            int a=G.vertices[i].data.key,b=G.vertices[arc->adjvex].data.key;
            if( flag[a][b]||flag[b][a] ){
                arc=arc->nextarc;
                continue;
            }
            flag[a][b]=1;
            VR[num][0]=a;VR[num][1]=b;
            num++;
            arc=arc->nextarc;
        }
    }
    for( int i=0 ; i<num ; i++ ){
        if( VR[i][0]>VR[i][1] ){
            int t=VR[i][0];
            VR[i][0]=VR[i][1];
            VR[i][1]=t;
        }
    }
    
    //对VR数组进行插入排序（第一维） 
    for( int i=0 ; i<num ; i++ ){
        int Min=VR[i][0],Mini=i;
        for( int j=i ; j<num ; j++ ){
            if( VR[j][0]<Min ){
                Min=VR[j][0];
                Mini=j;
            }
        }
        int t1=VR[i][0],t2=VR[i][1];
        VR[i][0]=VR[Mini][0];VR[i][1]=VR[Mini][1];
        VR[Mini][0]=t1;VR[Mini][1]=t2;
    }
    
    //对VR数组进行插入排序（第二维）
    for( int i=0 ; i<num ; i++ ){
        int tail=i;
        while(VR[tail][0]==VR[i][0])
            tail++;
        if( tail-i==0 )
            continue;
        for( int k=i ; k<tail ; k++ ){
            int Min=VR[k][1],Mini=k;
            for( int j=k ; j<tail ; j++ ){
                if( VR[j][1]<Min){
                    Min=VR[j][1];
                    Mini=j;
                }
            }
            int t=VR[k][1];
            VR[k][1]=VR[Mini][1];
            VR[Mini][1]=t;
        }
        i=tail-1;
    }
    
    //文件输入 
    for( int i=0 ; i<G.vexnum ; i++ )
        fprintf(fp,"%d %s ",V[i].key,V[i].others);
    fprintf(fp,"%d %s ",-1,"nil");
    for( int i=0 ; i<num ; i++ )
        fprintf(fp,"%d %d ",VR[i][0],VR[i][1]);
    fprintf(fp,"%d %d",-1,-1);
    fclose(fp);		//关闭文件好习惯 
    return OK;
}

/********************************************************
函数名：  LoadGraph
初始条件：无向图G不存在
函数功能：将图G写到文件名为FileName的文件中，返回OK
返回类型：status
********************************************************/
status LoadGraph(ALGraph &G, char FileName[])
{
	//文件初始化 
    FILE *fp;
    fp=fopen(FileName,"r+");
    
    //从文件中读入V和VR数组 
    int vexnum=0,arcnum=0,v1,v2;
    VertexType V[100];
    KeyType VR[100][2];
    fscanf(fp,"%d %s",&V[0].key,V[0].others);
    while(V[vexnum].key!=-1){
        vexnum++;
        fscanf(fp,"%d %s",&V[vexnum].key,V[vexnum].others);
    }
    fscanf(fp,"%d %d",&VR[0][0],&VR[0][1]);
    while(VR[arcnum][0]!=-1){
        arcnum++;
        fscanf(fp,"%d %d",&VR[arcnum][0],&VR[arcnum][1]);
    }
    
    //利用CreateCraph函数构造无向图 
    CreateCraph(G,V,VR);
    fclose(fp);
    return OK;
}

/*******************************************************************
函数名称：AddGraph
初始条件：当前图数目未超过上限 
功能说明：添加一个新的图，赋予其图名 
返回值类型：status
********************************************************************/
status AddGraph(LISTS &graph,char graphname[])
{
	for( int i=1 ; i<11 ; i++ )
		if( !strcmp(graphname,graph.elem[i].name) )
			return ERROR;
	graph.length++;
	graph.elem[graph.length].G.vexnum=0;
	graph.elem[graph.length].G.arcnum=0;
	int i;
	for( i=0 ; graphname[i]!='\0' ; i++ )
		graph.elem[graph.length].name[i]=graphname[i];
	graph.elem[graph.length].name[i]='\0';
	graph.elem[graph.length].G.kind=1;
	return OK;
}

int DeleteGraph(LISTS &graph,char graphname[]){
	for( int i=1 ; i<11 ; i++ ){
		if( !strcmp(graphname,graph.elem[i].name) ){
			for( int j=i ; j<graph.length ; j++ )
				graph.elem[j]=graph.elem[j+1];
			graph.elem[graph.length].G.vexnum=0;
			graph.elem[graph.length].G.arcnum=0;
			graph.length--;
			return i;
		}
	}
	return 0;
}

int ChooseGraph(LISTS &graph,char graphname[])
{
	for( int i=1 ; i<11 ; i++ )
		if( !strcmp(graphname,graph.elem[i].name) )
			return i;
	return 0;
}

/*******************************************************************
函数名称：VerticesSetLessThanK
初始条件：图G存在 
功能说明：返回与顶点v距离小于k的顶点集合
返回值类型：status
辅助函数：深度优先搜索函数 
********************************************************************/
void dfs_lessk(ALGraph &G,int k,int adj){
	if( k<=0 )
		return ;
	if( flag[adj] )
		return ;
	flag[adj]++;
	adjvex[nums++]=adj;
	ArcNode *arc=G.vertices[adj].firstarc;
	while(arc){
		dfs_lessk(G,k-1,arc->adjvex);
		arc=arc->nextarc;
	}
} 
status VerticesSetLessThanK(ALGraph &G,KeyType v,int k){
	int t=G.vexnum,a=-1;
	for( int i=0 ; i<t ; i++ )
		if( G.vertices[i].data.key==v ){
			a=i;
			break;
		}
	if( a==-1 )
		return ERROR;
	dfs_lessk(G,k,a);
	return OK;
}

/*******************************************************************
函数名称：ShortestPathLength
初始条件：图G存在 
功能说明：返回顶点v与顶点w的最短路径的长度
返回值类型：int
********************************************************************/
int ShortestPathLength(ALGraph &G,KeyType v,KeyType w){
	int t=G.vexnum,a=-1,b=-1,Min,u;
	for( int i=0 ; i<t ; i++ )
		if( G.vertices[i].data.key==v ){
			a=i;
			break;
		}
	for( int i=0 ; i<t ; i++ )
		if( G.vertices[i].data.key==w ){
			b=i;
			break;
		}
	if( a==-1||b==-1 )
		return ERROR;
	int grid[100][100]={0};
	for( int i=0 ; i<t ; i++ ){
		ArcNode *arc=G.vertices[i].firstarc;
		while(arc){
			grid[i][arc->adjvex]=1;
			arc=arc->nextarc;
		}
	}
	for( int i=0 ; i<100 ; i++ )
		for( int j=0 ; j<100 ; j++ )
			if( !grid[i][j] )
				grid[i][j]=10000;
	for( int i=0 ; i<100 ; i++ )
		grid[i][i]=0;
	for( int i=0 ; i<t ; i++ )
		for( int j=0 ; j<t ; j++ )
			for( int k=0 ; k<t ; k++ )
				if( grid[i][j]>grid[i][k]+grid[k][j] )
					grid[i][j]=grid[i][k]+grid[k][j];
	return grid[a][b];
}

/*******************************************************************
函数名称：ConnectedComponentsNums
初始条件：图G存在 
功能说明：返回图G的所有连通分量的个数
返回值类型：int
********************************************************************/
void dfs_connect(ALGraph &G,char flag[],int v){
	ArcNode *arc=G.vertices[v].firstarc;
    flag[v]=1;			//标记已遍历结点 
    while( arc ){
        if( !flag[arc->adjvex] )
            dfs_connect(G,flag,arc->adjvex);
        arc=arc->nextarc;
    }
    return ;
}

int ConnectedComponentsNums(ALGraph &G){
	char flag[100]={0};
	int t=G.vexnum;
	int ret=0;
	for( int i=0 ; i<t ; i++ ){
		if( !flag[i] ){
			ret++;
			dfs_connect(G,flag,i);
		}
	}
	return ret;
}
