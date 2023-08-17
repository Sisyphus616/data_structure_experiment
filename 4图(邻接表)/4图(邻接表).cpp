#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h> 
#include<windows.h>

/*************************Ԥ����*************************/
#define TRUE 1					//�ж���ȷ 
#define FALSE 0					//�жϴ��� 
#define OK 1					//�ɹ� 
#define ERROR 0					//�߼����� 
#define INFEASIBLE -1			//�����д��� 
#define OVERFLOW -2				//������� 
#define MAX_VERTEX_NUM 20		//������� 

typedef int status;							//״̬���� 
typedef int KeyType; 						//�ؼ������� 
typedef enum {DG,DN,UDG,UDN} GraphKind;		//ͼ���� 

typedef struct {
     KeyType  key;
     char others[20];
} VertexType; 					//�������Ͷ���


typedef struct ArcNode {       	//�������Ͷ���
	 int adjvex;              	//����λ�ñ�� 
	 struct ArcNode  *nextarc;	//��һ������ָ��
} ArcNode;

typedef struct VNode{			//ͷ��㼰���������Ͷ���
	 VertexType data;       	//������Ϣ
	 ArcNode *firstarc; 	 	//ָ���һ����
	} VNode,AdjList[MAX_VERTEX_NUM];

typedef  struct {  				//�ڽӱ�����Ͷ���
    AdjList vertices;     	 	//ͷ�������
    int vexnum,arcnum;   	  	//������������
    int  kind;        			//ͼ������
   } ALGraph;

typedef struct{  				//���Ա�ļ������Ͷ���
    struct { 
		char name[30];			//���� 
        ALGraph G;    			//���Ա����� 
    } elem[11];			
    int length;					//�� 
}LISTS;
   
//ȫ�ֱ���
char flag[100]={0};				//�жϽ���Ƿ������ 
int adjvex[100];				//�洢���λ�� 
int nums=0;						//�洢�ڵ���Ŀ 
int Min=100;					//���·�� 

/********************************************************/

/*************************������*************************/
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

/*************************������*************************/

int main(){
	
	/****************************************************************/
	/*						   ���������							*/
	/****************************************************************/ 
	
	system("mode con cols=82 lines=31 ");	//���ĳ�����С 
	system("title ���Ա���ʽ�洢�ṹ");	//���ĳ��������
	system("color 1F");						//������ɫ����������ɫ
	
	/****************************************************************/
	/*						    ��ʼ��								*/
	/****************************************************************/
	
	int op=1;			//�û�����ѡ��
	char filename[50];	//�洢�ļ���
	char graphname[50];	//�洢ͼ��
	int lp=1; 			//��¼��ǰ�����ͼָ��
	int cntnum=0;		//��¼������Ŀ
	int kv,kw,ku;		//��¼�ؼ���ֵ
	VertexType input[100];
	int VR[100][2];		//������ 
	
	//��ͼ����
	LISTS graph;		//���Ա��Ϲ����ͼ
	graph.length=0;		//���ȳ�ʼ��
	
	//ͼ��ʼ��
	for( int i=0 ; i<11 ; i++ ){
		graph.elem[i].G.arcnum=0; 		//����뻡��Ŀ���� 
		graph.elem[i].G.vexnum=0;
		graph.elem[i].G.kind=0;
	}
	
	//���Ƴ�ʼ��
	char defaultname[50]="��ʼͼ";		//Ĭ������
	for( int i=0 ; defaultname[i]!='\0' ; i++ )
		graph.elem[1].name[i]=defaultname[i];
		
	/****************************************************************/
	/*						   �˵����� 							*/
	/****************************************************************/
	
	while(op){
		system("cls");
	    printf("\n\n");
		printf("	  \t\t\t\tͼ�˵�\t\t\n\n");
		printf(" \t�������10��ͼ���ж�ͼ��������������δ��ʼ��������Ĭ��Ϊ��ͼ��\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf(" *1. ����ͼ         \t\t\t7.  ���붥��\t\t\t\t*\n");
		printf(" *2. ����ͼ       \t\t\t8.  ɾ������\t\t\t\t*\n");
		printf(" *3. ���Ҷ���         \t\t\t9.  ���뻡 \t\t\t\t*\n");
		printf(" *4. ���㸳ֵ         \t\t\t10. ɾ����\t\t\t\t*\n");
		printf(" *5. ��õ�һ�ڽӵ�        \t\t11. �����������\t\t\t*\n");
		printf(" *6. �����һ�ڽӵ�           \t\t12. �����������\t\t\t*\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf(" *13.ͼ�ļ��洢          \t\t14. ͼ�ļ���ȡ\t\t\t\t*\n");
		printf(" *15.����С��k�Ķ��㼯�� \t\t16. ��������·���ĳ���\t\t*\n");
		printf(" *17.ͼ����ͨ����        \t\t18. ���ͼ\t\t\t\t*\n");
		printf(" *19.�Ƴ�ͼ          \t\t\t20. ѡ��Ҫ������ͼ\t\t\t*\n");
		printf(" *0. �˳�\t\t\t\n");
		printf(" --------------------------------------------------------------powered by �Ϻ���\n");
		printf("��ǰ������ͼ��ͼ%d��%s\n\n",lp,graph.elem[lp].name);
		printf("����������0~20��ѡ����Ĳ���:");
		scanf("%d",&op);//ѡ��op��ֵ,����switch
		printf("\n");
		int i=0;
		switch(op){
			
			case 0:
				//��������
				break;
			
			case 1:
				//����ͼ
				if( graph.elem[lp].G.arcnum||graph.elem[lp].G.vexnum ){
					printf("����ʧ�ܣ�ͼ�Ѵ��ڣ�");
					break;
				}
				
				//���붥������ 
				printf("��ǰ���ڽ��д���ͼ������������ͼ�Ķ����뻡���飺\n");
				
				do{
					scanf("%d %s",&input[i].key,input[i].others);
				}while(input[i++].key!=-1);
				
				//������ʮ���� 
				if( i>20 ){
					printf("\n����ʧ�ܣ�������ʮ���㣡");
					break;
				}
				
				//��ͼ 
				else if( i<=1 ){
					printf("\n����ʧ�ܣ������Ϊ0��");
					break;
				}
				
				//���뻡���� 
				i=0;
				do{
					scanf("%d %d",&VR[i][0],&VR[i][1]);
				}while(VR[i++][0]!=-1);
				
				if( CreateCraph(graph.elem[lp].G,input,VR)==ERROR )
					printf("\n����ʧ�ܣ�����ؼ����Ƿ��ظ���");
				else{
					printf("\n�����ɹ���"); 
					if( graph.elem[lp].G.kind==0 )
						graph.length++;
				}
				break;
			
			case 2:
				//����ͼ
				if( !graph.elem[lp].G.vexnum ){
					printf("����ʧ�ܣ�ͼ�����ڣ�");
					break;
				}
				DestroyGraph(graph.elem[lp].G);
				printf("���ٳɹ���");
				graph.length--;
				break;
			
			case 3:
				//���Ҷ���
				if( graph.elem[lp].G.vexnum==0 ){
					printf("��ͼΪ�գ��޷����в�����");
					break;
				}
				printf("��ǰ���ڽ��в��Ҷ��������������Ҫ���Ҷ���Ĺؼ��֣�");
				scanf("%d",&ku);
				int ret3;
				if( (ret3=LocateVex(graph.elem[lp].G,ku))==-1 )
					printf("\nδ��ѯ������Ҫ�Ľ�㣡");
				else{
					printf("\n�����ҽ���λ��Ϊ%d,",ret3);
					printf("ֵΪ��%d %s",graph.elem[lp].G.vertices[ret3].data.key,graph.elem[lp].G.vertices[ret3].data.others);
				}
				break;
			
			case 4:
				//���㸳ֵ 
				if( graph.elem[lp].G.vexnum==0 ){
					printf("��ͼΪ�գ��޷����в�����");
					break;
				}
				printf("��ǰ���ڽ��ж��㸳ֵ������������Ҫ��ֵ����Ĺؼ��ּ�Ҫ����ֵ��");
				scanf("%d %d %s",&ku,&input[0].key,input[0].others);
				if( PutVex(graph.elem[lp].G,ku,input[0])==ERROR )
					printf("\n��ֵʧ�ܣ�����ؼ����Ƿ��ظ����ѯ����Ƿ���ڣ�");
				else
					printf("\n��ֵ�ɹ���");
				break;
			
			case 5:
				//��õ�һ�ڽӵ�
				if( graph.elem[lp].G.vexnum==0 ){
					printf("��ͼΪ�գ��޷����в�����");
					break;
				}
				printf("��ǰ���ڽ��л�õ�һ�ڽӵ������������Ҫ���ҽ��Ĺؼ��֣�");
				scanf("%d",&ku);
				int ret5;
				if( (ret5=FirstAdjVex(graph.elem[lp].G,ku))==-1 )
					printf("\n��Ҫ���ҵĽ�㲻���ڣ�");
				else{
					printf("\n��Ҫ���ҵĽ��ĵ�һ�ٽ��λ��Ϊ��%d,ֵΪ��",ret5);
					printf("%d,%s",graph.elem[lp].G.vertices[ret5].data.key,graph.elem[lp].G.vertices[ret5].data.others);
				}
				break;
			
			case 6:
				//�����һ�ڽӵ�
				if( graph.elem[lp].G.vexnum==0 ){
					printf("��ͼΪ�գ��޷����в�����");
					break;
				}
				printf("��ǰ���ڽ��л����һ�ڽӵ������������Ҫ���ҽ��Ĺؼ��֣�");
				scanf("%d %d",&kv,&kw);
				int ret6;
				if( (ret6=NextAdjVex(graph.elem[lp].G,kv,kw))==-1 )
					printf("\n��ȡʧ�ܣ��������Ƿ���ڻ��Ƿ�����һ�ڽӵ㣡");
				else{
					printf("\n��Ҫ���ҵĽ�����һ�ٽ��λ��Ϊ��%d,ֵΪ��",ret6);
					printf("\n%d,%s",graph.elem[lp].G.vertices[ret6].data.key,graph.elem[lp].G.vertices[ret6].data.others);
				}
				break;
			
			case 7:
				//���붥��
				if( graph.elem[lp].G.vexnum==0 ){
					printf("��ͼΪ�գ��޷����в�����");
					break;
				}
				if( graph.elem[lp].G.vexnum>=20 ){
					printf("������Ѵﵽ����޷����룡");
					break;
				}
				printf("��ǰ���ڽ��в����������������Ҫ�������ֵ��");
				scanf("%d %s",&input[0].key,input[0].others); 
				if( InsertVex(graph.elem[lp].G,input[0])==ERROR )
					printf("\n����ʧ�ܣ�����ؼ����Ƿ��ظ���");
				else
					printf("����ɹ���");
				break;
			
			case 8:
				//ɾ������
				if( graph.elem[lp].G.vexnum==0 ){
					printf("��ͼΪ�գ��޷����в�����");
					break;
				}
				if( graph.elem[lp].G.vexnum==1 ){
					printf("��ͼֻ��һ����㣬�޷�ɾ����");
					break;
				}
				printf("��ǰ���ڽ���ɾ����������������Ҫɾ�����Ĺؼ��֣�");
				scanf("%d",&ku);
				if( DeleteVex(graph.elem[lp].G,ku)==ERROR )
					printf("\nɾ��ʧ�ܣ��������Ƿ���ڣ�");
				else
					printf("\nɾ���ɹ���");
				break;
			
			case 9:
				//���뻡
				if( graph.elem[lp].G.vexnum==0 ){
					printf("��ͼΪ�գ��޷����в�����");
					break;
				}
				printf("��ǰ���ڽ��в��뻡������������Ҫ���뻡�˵�Ĺؼ��֣�");
				scanf("%d %d",&kv,&kw);
				if( InsertArc(graph.elem[lp].G,kv,kw)==ERROR )
					printf("\n����ʧ�ܣ����鶥���Ƿ���ڻ򶥵�֮���Ѵ��ڻ�");
				else
					printf("\n����ɹ���");
				break;
			
			case 10:
				//ɾ����
				if( graph.elem[lp].G.vexnum==0 ){
					printf("��ͼΪ�գ��޷����в�����");
					break;
				}
				printf("��ǰ���ڽ���ɾ����������������Ҫɾ�����˵�Ĺؼ��֣�");
				scanf("%d %d",&kv,&kw);
				if( DeleteArc(graph.elem[lp].G,kv,kw)==ERROR )
					printf("\nɾ��ʧ�ܣ����鶥���Ƿ���ڻ򶥵�֮�䲻���ڻ�");
				else
					printf("\nɾ���ɹ���");
				break;
			
			case 11:
				//�����������
				if( graph.elem[lp].G.vexnum==0 ){
					printf("��ͼΪ�գ��޷����в�����");
					break;
				}
				for( int i=0 ; i<100 ; i++ )
					flag[i]=0;
				printf("�������Ϊ��\n");
				DFSTraverse(graph.elem[lp].G,visit);
				break; 
			
			case 12:
				//�����������
				if( graph.elem[lp].G.vexnum==0 ){
					printf("��ͼΪ�գ��޷����в�����");
					break;
				}
				printf("�������Ϊ��\n");
				BFSTraverse(graph.elem[lp].G,visit);
				break;
			
			case 13:
				//�洢ͼ
				if( graph.elem[lp].G.vexnum==0 ){
					printf("��ͼΪ�գ��޷����в�����");
					break;
				}
				printf("��ǰ���ڽ��д洢ͼ������������Ҫ�洢���ļ�����");
				scanf("%s",filename);
				SaveGraph(graph.elem[lp].G,filename);
				printf("\n�洢�ɹ���");
				break;
			
			case 14:
				//��ȡͼ
				if( graph.elem[lp].G.vexnum ){
					printf("��ͼ��Ϊ�գ��޷����в�����");
					break;
				}
				printf("��ǰ���ڽ���ͼ�Ķ�ȡ�������������ļ�����\n");
				scanf("%s",filename);
				LoadGraph(graph.elem[lp].G,filename);
				if( graph.elem[lp].G.kind==0 )
					graph.length++;
				printf("\n��ȡ�ɹ���");
				break;
				
			case 15:
				//����С��k�Ķ��㼯��
				if( !graph.elem[lp].G.vexnum ){
					printf("��ͼΪ�գ��޷����в�����");
					break;
				}
				printf("��ǰ���ڽ��з��ؾ���С��k�Ķ��㼯�ϲ�����������k�����ؼ��֣�");
				int k;
				nums=0;
				for( int i=0 ; i<100 ; i++ ){
					adjvex[i]=-1;
					flag[i]=0;
				}
				scanf("%d %d",&k,&ku);
				if( VerticesSetLessThanK(graph.elem[lp].G,ku,k)==ERROR ){
					printf("\n����ʧ�ܣ��������Ƿ���ڣ�");
					break;
				}
				else{
					printf("\n����С��k�Ķ���Ϊ��\n");
					for( int i=0 ; adjvex[i]!=-1 ; i++ )
						printf("%d,%s\n",graph.elem[lp].G.vertices[adjvex[i]].data.key,graph.elem[lp].G.vertices[adjvex[i]].data.others);
				}
				break;
			
			case 16:
				//��������·������
				if( !graph.elem[lp].G.vexnum ){
					printf("��ͼΪ�գ��޷����в�����");
					break;
				}
				int ret16;
				for( int i=0 ; i<100 ; i++ )
					flag[i]=0;
				printf("��ǰ���ڽ��з��ض�������·�����Ȳ��������������������յ�ؼ��֣�");
				scanf("%d %d",&kv,&kw);
				if( (ret16=ShortestPathLength(graph.elem[lp].G,kv,kw))==ERROR )
					printf("\n����ʧ�ܣ��������Ƿ���ڣ�");
				else if( ret16==10000 )
					printf("\n����֮�䲻����·����");
				else
					printf("\n���·������Ϊ��%d",ret16);
				break;
			
			case 17:
				//ͼ����ͨ���� 
				if( !graph.elem[lp].G.vexnum ){
					printf("��ͼΪ�գ��޷����в�����");
					break;
				}
				printf("��ǰͼ����ͨ����Ϊ��%d",ConnectedComponentsNums(graph.elem[lp].G));
				break;
			
			case 18:
				//���ͼ
				if( graph.length>=10 ){
					printf("��ǰͼ����Ŀ�Ѵ����ޣ��޷���ӣ�");
					break;
				}
				printf("��ǰ���ڽ������ͼ������������ͼ���ƣ�");
				scanf("%s",graphname);
				if( AddGraph(graph,graphname)==ERROR )
					printf("\n��ǰ�����Ѵ��ڣ���һ�����ְɣ�");
				else
					printf("\n��ӳɹ���");
				break;
			
			case 19:
				//�Ƴ�ͼ
				if( graph.length<=0 ){
					printf("��ǰ��û��ͼ���޷������Ƴ�������");
					break;
				} 
				int ret19;
				printf("��ǰ���ڽ����Ƴ�ͼ�������������Ƴ�ͼ�����ƣ�");
				scanf("%s",graphname);
				if( (ret19=DeleteGraph(graph,graphname))==0 )
					printf("\nɾ��ʧ�ܣ�����ͼ�Ƿ���ڣ�");
				else{
					printf("\nɾ���ɹ���");
					if( ret19==lp ){
						printf("������ɾ���˵�ǰ������ͼ���´β���Ĭ�϶�ͼ1���У�");
						lp=1;
					}
				}
				break;
			
			case 20:
				//ѡ��Ҫ������ͼ
				printf("��ǰ���ڽ���ѡ��ͼ������������Ҫѡ���ͼ�����ƣ�");
				scanf("%s",graphname);
				int ret20;
				if( (ret20=ChooseGraph(graph,graphname))==0 )
					printf("\nѡ��ʧ�ܣ�δ�ҵ��������ͼ��");
				else{
					lp=ret20;
					printf("\nѡ��ɹ���������ͼ%d���в�����",lp);
				}
				break;
		}
		if( op!=0 ){
			printf("\n\n�������������һ������\n\n");
			system("pause");
			cntnum++;
		}
	}
	printf("ллʹ�ã������ι�������%d�β�������ӭ�´�������\n",cntnum);
	Sleep(2000);
	return 0;
}

/********************************************************/

/********************************************************
��������  CreateCraph
��ʼ����������ͼG�����ڣ�����������ڽ����� 
�������ܣ����ݶ�������V�͹�ϵ������VR����һ������ͼG��Ҫ
������ͼG�и�����ؼ��־���Ψһ�ԣ������Ŀ������MAX_VERT
EX_NUM����
�������ͣ�status 
�������������뻡���� 
********************************************************/
status InsertArc(ALGraph &G,KeyType v,KeyType w)
{
    int t=G.vexnum,a=-1,b=-1;			//�������v��w���±� 
    
    //�ж�v��w�Ƿ���� 
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
        
    //�ж�ԭ���Ƿ��Ѵ�����Ӧ�ı� 
    ArcNode *arc=G.vertices[a].firstarc;
    while(arc){
        if( arc->adjvex==b )
            return ERROR;
        arc=arc->nextarc;
    }
    
    //���뻡��˫�� 
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
    //��������ͻ���
    int vexnum=0,arcnum=0;
    for( int i=0 ; V[i].key!=-1 ; i++ )
        vexnum++;
    for( int i=0 ; VR[i][0]!=-1 ; i++ )
        arcnum++;

    //�жϹؼ����ظ�
    char bull[1000]={0};
    for( int i=0 ; i<vexnum ; i++ ){
        bull[V[i].key]++;
        if( bull[V[i].key]>1 )
            return ERROR;
    }

    //���У���ͼ
    if( vexnum==0 )
        return ERROR;
    //���У�������ʮ����
    if( vexnum>20 )
        return ERROR;

    //�жϻ�û�д���
    for( int i=0 ; i<arcnum ; i++ )
        if( !bull[VR[i][0]]||!bull[VR[i][1]] )
            return ERROR;

    //����ͼ��Ӧֵ
    G.vexnum=vexnum;
    for( int i=0 ; i<vexnum ; i++ ){
        G.vertices[i].data=V[i];
        G.vertices[i].firstarc=NULL;
    }
    
    //������
    for( int i=0 ; i<arcnum ; i++ ){
        InsertArc(G,VR[i][0],VR[i][1]);
    }
    return OK;
}

/********************************************************
��������  DestroyGraph
��ʼ����������ͼG����
�������ܣ����ڽӱ��ʾ������ͼ���٣����ͷ����б���Ŀռ䡣
�������ͣ�status 
********************************************************/
status DestroyGraph(ALGraph &G)
{
    int t=G.vexnum;
    
    //��firstarc�����ͷſռ� 
    for( int i=0 ; i<t ; i++ ){
        ArcNode *a=G.vertices[i].firstarc;
        while(a){
            ArcNode *next=a->nextarc;
            free(a);
            a=next;
        }
    }
    
    //���ֵ���� 
    G.vexnum=0;G.arcnum=0;
    return OK;
}

/********************************************************
��������  LocateVex
��ʼ����������ͼG����
�������ܣ�u�Ǻ�G�ж���ؼ���������ͬ�ĸ���ֵ������u���Ҷ�
�㣬�ɹ�ʱ���عؼ���Ϊu�Ķ���λ����ţ����λ�򣩣�����
��-1��
�������ͣ�int
********************************************************/
int LocateVex(ALGraph G,KeyType u)
{
    int t=G.vexnum;
    
    //������������ 
    for( int i=0 ; i<t ; i++ )
        if( u==G.vertices[i].data.key )
            return i;
    return -1;
}

/********************************************************
��������  PutVex
��ʼ����������ͼG����
�������ܣ�u�Ǻ�G�ж���ؼ���������ͬ�ĸ���ֵ�����������
�Թؼ���Ϊu�Ķ��㸳ֵvalue��Ҫ��ؼ��־���Ψһ�ԣ����ɹ�
��ֵ����OK�����򷵻�ERROR��
�������ͣ�status
********************************************************/
status PutVex(ALGraph &G,KeyType u,VertexType value)
{
    int t=G.vexnum;
    
    int num[100]={0};		//�ж��ؼ����ظ����� 
    for( int i=0 ; i<t ; i++ )
        num[G.vertices[i].data.key]++;
    if( u!=value.key&&num[value.key] )
        return ERROR;		//�ؼ����ظ� 
    for( int i=0 ; i<t ; i++ ){
        if( u==G.vertices[i].data.key ){
            G.vertices[i].data=value;
            return OK;
        }
    }
    return ERROR;
}

/********************************************************
��������  FirstAdjVex
��ʼ����������ͼG����
�������ܣ�u�Ǻ�G�ж���ؼ���������ͬ�ĸ���ֵ�����عؼ���
Ϊu�Ķ����һ���ڽӶ���λ����ţ����λ�򣩣����򷵻�-1��
�������ͣ�int
********************************************************/
int FirstAdjVex(ALGraph G,KeyType u)
{
    int t=G.vexnum,a;
    
    //������������ 
    for( int i=0 ; i<t ; i++ ){
        if( u==G.vertices[i].data.key ){
            return G.vertices[i].firstarc->adjvex;
        }
    }
    return -1;
}

/********************************************************
��������  NextAdjVex
��ʼ����������ͼG����
�������ܣ�v��w��G�����������λ��v��ӦG��һ������,w��Ӧ
v���ڽӶ��㣻��������Ƿ���v�ģ������w����һ���ڽӶ����
λ�����w�����һ���ڽӶ��㣬��v��w��Ӧ���㲻���ڣ���
��-1��
�������ͣ�int
********************************************************/
int NextAdjVex(ALGraph G,KeyType v,KeyType w)
{
    int t=G.vexnum,a=-1;
    
    //Ѱ�Ҷ�Ӧv�Ľ�� 
    for( int i=0 ; i<t ; i++ )
        if( v==G.vertices[i].data.key ){
            a=i;
            break;
        }
    if( a==-1 )
        return -1;
        
    //��v���ڽӽ����Ѱ��w 
    ArcNode *arc=G.vertices[a].firstarc;
    while( arc ){
        if( G.vertices[arc->adjvex].data.key==w )
            break;
        arc=arc->nextarc;
    }
    if( !arc )
        return -1;
    if( !(arc->nextarc) )   //���һ���ڽӶ���
        return -1;
    return arc->nextarc->adjvex;
}

/********************************************************
��������  InsertVex
��ʼ����������ͼG����
�������ܣ���ͼG�в����¶����v��Ҫ��ؼ��־���Ψһ�ԣ�ע��
�ж϶�������Ƿ����������ɹ�����OK�����򷵻�ERROR��
�������ͣ�status
********************************************************/
status InsertVex(ALGraph &G,VertexType v)
{
    //�ж϶������Ƿ񳬹����ֵ
    if( G.vexnum>=MAX_VERTEX_NUM )
        return ERROR;
    
    int t=G.vexnum;
    
    //�жϹؼ���Ψһ��
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
��������  DeleteVex
��ʼ����������ͼG����
�������ܣ�v�Ǻ�G�ж���ؼ���������ͬ�ĸ���ֵ�������������
ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK������
��ERROR��
�������ͣ�status
********************************************************/
status DeleteVex(ALGraph &G,KeyType v)
{
    int t=G.vexnum,a=-1;

    //����������λ
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
    
    //��������ػ�
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
��������  DeleteArc
��ʼ����������ͼG����
�������ܣ�v��w�Ǻ�G�ж���ؼ���������ͬ�ĸ���ֵ���������
����ͼG��ɾ����<v,w>���ɹ�����OK�����򷵻�ERROR��
�������ͣ�status
********************************************************/
status DeleteArc(ALGraph &G,KeyType v,KeyType w)
{
    int t=G.vexnum,a=-1,b=-1;
    
    //����Ѱ��v��w��Ӧ��� 
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
    
    //ɾ������˫�� 
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
    if( !arc )		//δ�ҵ���Ӧ�Ļ�����v��w���ڽ� 
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
��������  DFSTraverse 
��ʼ����������ͼG����
�������ܣ���ͼG������������������������ζ�ͼ�е�ÿһ����
��ʹ�ú���visit����һ�Σ��ҽ�����һ�Ρ�
�������ͣ�status
������������������������� 
********************************************************/
void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}

void dfs(ALGraph &G,int v,void (*visit)(VertexType)){
    ArcNode *arc=G.vertices[v].firstarc;
    visit(G.vertices[v].data);
    flag[v]=1;			//����ѱ������ 
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
��������  BFSTraverse 
��ʼ����������ͼG����
�������ܣ���ͼG���й�������������������ζ�ͼ�е�ÿһ����
��ʹ�ú���visit����һ�Σ��ҽ�����һ�Ρ�
�������ͣ�status
********************************************************/
status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
{
    int t=G.vexnum;
    
    char flag[100]={0};		//����ѱ������
	
	//�������� 
    ArcNode *queue[100];int front=0,tail=0;
    
    //�����׶� 
    for( int i=0 ; i<t ; i++ ){
        if( !flag[i] ){		//�����δ������ 
            visit(G.vertices[i].data);
            front=tail=0;	//���г�ʼ�� 
            queue[tail++]=G.vertices[i].firstarc;	//���� 
            while(front<tail){
                ArcNode* arc=queue[front++];
            	if( !arc )
            		break;
                if( !flag[arc->adjvex] ){
                    flag[arc->adjvex]=1;
                    visit(G.vertices[arc->adjvex].data);
                    arc=arc->nextarc;
                    while(arc){
                        queue[tail++]=arc;			//�ڽӽ��ȫ������ 
                        arc=arc->nextarc;
                    }
                }
            }
        }
    }
    //��������Ž�β���(bushi) 
    return OK;
}

/********************************************************
��������  SaveGrapgh 
��ʼ����������ͼG����
�������ܣ���ͼGд���ļ���ΪFileName���ļ��У�����OK
�������ͣ�status
********************************************************/
status SaveGraph(ALGraph G, char FileName[])
{
	//�ļ�������ʼ�� 
    FILE *fp;
    fp=fopen(FileName,"w+");
    
    //�ļ��������� 
    VertexType V[100];
    KeyType VR[100][2];
    
    //����V��VR���� 
    char flag[100][100]={0};		//�����жϱ��Ƿ��ظ� 
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
    
    //��VR������в������򣨵�һά�� 
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
    
    //��VR������в������򣨵ڶ�ά��
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
    
    //�ļ����� 
    for( int i=0 ; i<G.vexnum ; i++ )
        fprintf(fp,"%d %s ",V[i].key,V[i].others);
    fprintf(fp,"%d %s ",-1,"nil");
    for( int i=0 ; i<num ; i++ )
        fprintf(fp,"%d %d ",VR[i][0],VR[i][1]);
    fprintf(fp,"%d %d",-1,-1);
    fclose(fp);		//�ر��ļ���ϰ�� 
    return OK;
}

/********************************************************
��������  LoadGraph
��ʼ����������ͼG������
�������ܣ���ͼGд���ļ���ΪFileName���ļ��У�����OK
�������ͣ�status
********************************************************/
status LoadGraph(ALGraph &G, char FileName[])
{
	//�ļ���ʼ�� 
    FILE *fp;
    fp=fopen(FileName,"r+");
    
    //���ļ��ж���V��VR���� 
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
    
    //����CreateCraph������������ͼ 
    CreateCraph(G,V,VR);
    fclose(fp);
    return OK;
}

/*******************************************************************
�������ƣ�AddGraph
��ʼ��������ǰͼ��Ŀδ�������� 
����˵�������һ���µ�ͼ��������ͼ�� 
����ֵ���ͣ�status
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
�������ƣ�VerticesSetLessThanK
��ʼ������ͼG���� 
����˵���������붥��v����С��k�Ķ��㼯��
����ֵ���ͣ�status
������������������������� 
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
�������ƣ�ShortestPathLength
��ʼ������ͼG���� 
����˵�������ض���v�붥��w�����·���ĳ���
����ֵ���ͣ�int
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
�������ƣ�ConnectedComponentsNums
��ʼ������ͼG���� 
����˵��������ͼG��������ͨ�����ĸ���
����ֵ���ͣ�int
********************************************************************/
void dfs_connect(ALGraph &G,char flag[],int v){
	ArcNode *arc=G.vertices[v].firstarc;
    flag[v]=1;			//����ѱ������ 
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
