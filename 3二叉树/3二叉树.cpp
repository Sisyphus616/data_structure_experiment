#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h> 
#include<windows.h>

/**************��ض���������***************/
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
} TElemType; 				//������������Ͷ���

typedef struct BiTNode{  	//����������Ķ���
      TElemType  data;
      struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;

typedef struct{  			//���Ա�ļ������Ͷ���
    struct { 
		char name[30];
        BiTree T;    
    }elem[11];
    int length;
}LISTS;

//ȫ�ֱ��� 
int cnt=0;			//����Ԫ�ظ��� 
int num[1000]={0};	//���ڴ洢key����ֹ�ؼ����ظ� 
BiTree pre=NULL;	//ǰ���ڵ� 
BiTree array[100];	//�ļ�����ȡ���� 
//���ж��� 
BiTree queue[100];
int tail=0,front=0; //ͷβ����  
//ջ����
BiTree stack[100];
int top=0;			//ջ�� 
/*******************************************/

/******************������*******************/
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
	/*						   ���������							*/
	/****************************************************************/ 
	
	system("mode con cols=82 lines=34 ");	//���ĳ�����С 
	system("title ���Ա�˳��洢�ṹ");	//���ĳ��������
	system("color 1F");						//������ɫ����������ɫ
	
	/****************************************************************/
	/*						    ��ʼ��								*/
	/****************************************************************/
	int op=1;			//�û�����ѡ�� 
	char filename[50];	//�洢�ļ���
	char treename[50];	//�洢���� 
	TElemType input[50];//�洢�����ֵ 
	int lp=1;			//��ǰ�������ָ��
	int cntnum=0;		//��¼��������
	int keyin;			//��¼���ҽ��Ĺؼ��� 
	int maxlen=0;		//�·�� 
	int mode;			//����ģʽ 
	//������������� 
	LISTS tree;			//��������ʼ��  
	tree.length=0;
	//����ʼ��
	for( int i=0 ; i<11 ; i++ )
		tree.elem[i].T=NULL;
	char defaultname[30]="������";
	//���Ƴ�ʼ�� 
	for( int i=0 ; defaultname[i]!='\0' ; i++ )
		tree.elem[1].name[i]=defaultname[i]; 
	/****************************************************************/
	/*						   �˵����� 							*/
	/****************************************************************/
	while(op){
		system("cls");
	    printf("\n\n");
		printf("	  \t\t\t�������˵�\t\t\n\n");
		printf(" �������10�����������ж�����������������δ��ʼ��������Ĭ��Ϊ����������\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf(" *1. ��ʼ��������         \t\t7.  ������\t\t\t\t*\n");
		printf(" *2. ���ٶ�����       \t\t\t8.  ɾ�����\t\t\t\t*\n");
		printf(" *3. ���������         \t\t9.  ������� \t\t\t\t*\n");
		printf(" *4. ���ҽ��         \t\t\t10. �������\t\t\t\t*\n");
		printf(" *5. ��㸳ֵ        \t\t\t11. �������\t\t\t\t*\n");
		printf(" *6. ����ֵܽ��           \t\t12. �������\t\t\t\t*\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf(" *13.�������洢          \t\t14. ��������ȡ\t\t\t\t*\n");
		printf(" *15.���·����     \t\t\t16. �����������\t\t\t*\n");
		printf(" *17.��ת������         \t\t18. ��Ӷ�����\t\t\t\t*\n");
		printf(" *19.�Ƴ�������          \t\t20. ѡ��Ҫ�����Ķ�����\t\t\t*\n");
		printf(" *21.��ն�����          \t\t22. �жϿն�����\t\t\t*\n\n");
		printf(" *0. �˳�\t\t\t\n");
		printf(" --------------------------------------------------------------powered by �Ϻ���\n");
		printf("��ǰ�����Ķ�������������%d��%s\n\n",lp,tree.elem[lp].name);
		printf("����������0~20��ѡ����Ĳ���:");
		scanf("%d",&op);//ѡ��op��ֵ,����switch
		printf("\n");
		switch(op){
			case 0:
				//�������� 
				break;
			case 1:
				//���������� 
				if( tree.elem[lp].T ){
					printf("����ʧ�ܣ��������Ѵ��ڣ�");
					break;
				}
				else{
					printf("��ǰ���ڽ��ж������ĳ�ʼ�������������������������������飺\n");
					int i=0; 
					do{
						scanf("%d %s",&input[i].key,input[i].others);
					}while(input[i++].key!=-1);
					cnt=0;
					for( int i=0 ; i<1000 ; i++ )
						num[i]=0;
					if( CreateBiTree(tree.elem[lp].T,input)==ERROR )
						printf("\n����ؼ����ظ�������ʧ�ܣ�");
					else{
						printf("\n�����ɹ���");
						tree.length++;
					}
					cnt=0;
				}
				break; 
			case 2:
				//���ٶ����� 
				if( !tree.elem[lp].T )
					printf("�����������ڣ��޷����٣�");
				else{
					DestroyBiTree(tree.elem[lp].T);
					printf("���ٳɹ���");
					tree.length--;
				}
				break;
			case 3:
				//���������
				if( !tree.elem[lp].T )
					printf("�����������ڣ��޷��ж���ȣ�");
				else
					printf("�����������Ϊ��%d",BiTreeDepth(tree.elem[lp].T));
				break;
			case 4:
				//���ҽ��
				if( !tree.elem[lp].T )
					printf("�����������ڣ��޷����ҽ�㣡");
				else{
					printf("��ǰ���ڽ��в��ҽ���������������Ҫ��ѯ���Ĺؼ��֣�");
					scanf("%d",&keyin);
					BiTree t;
					if( (t=LocateNode(tree.elem[lp].T,keyin))==NULL )
						printf("\n����ʧ�ܣ�����������Ĺؼ����Ƿ�����");
					else
						printf("\n��ѯ�ɹ��������ҵĽ��Ϊ��%d,%s",t->data.key,t->data.others);
				} 
				break;
			case 5:
				//��㸳ֵ
				if( !tree.elem[lp].T )
					printf("�����������ڣ����ܽ��н�㸳ֵ������");
				else{
					printf("��ǰ���ڽ��н�㸳ֵ��������������Ҫ��ѯ���Ĺؼ��֣�");
					scanf("%d",&keyin);
					if( LocateNode(tree.elem[lp].T,keyin)==NULL ){
						printf("\nδ��ѯ������Ҫ�Ľ�㣡");
						break;
					}
					printf("��������Ҫ����Ĺؼ��֣�");
					scanf("%d %s",&input[0].key,input[0].others);
					for( int i=0 ; i<1000 ; i++ )
						num[i]=0;
					if(Assign(tree.elem[lp].T,keyin,input[0])==ERROR)
						printf("\n��ֵʧ�ܣ�����������Ĺؼ����Ƿ��ظ���");
					else
						printf("\n��ֵ�ɹ���");
				} 
				break;
			case 6:
				//����ֵܽڵ�
				if( !tree.elem[lp].T )
					printf("�����������ڣ��޷���ȡ�ֵܽڵ㣡");
				else{
					pre=NULL;
					printf("��ǰ���ڽ��л���ֵܽ���������������Ҫ��ѯ���Ĺؼ��֣�");
					scanf("%d",&keyin);
					if( LocateNode(tree.elem[lp].T,keyin)==ERROR ){
						printf("\n������Ĺؼ����ڶ������в����ڣ�");
						break;
					}
					BiTree t;
					if( (t=GetSibling(tree.elem[lp].T,keyin))==ERROR )
						printf("\n����ѯ�Ľ��û���ֵܽڵ㣡");
					else
						printf("\n����ѯ�����ֵܽڵ�Ϊ��%d,%s",t->data.key,t->data.others);
				} 
				break;
			case 7:
				//����ڵ�
				if( !tree.elem[lp].T )
					printf("�����������ڣ��޷������㣡"); 
				else{
					for( int i=0 ; i<1000 ; i++ )
    					num[i]=0;
    				printf("��ǰ���ڽ��в������������������Ҫ��ѯ���Ĺؼ��֣�����ģʽ");
					printf("��-1��ʾ�������룬0��ʾ��Ϊe�����ӣ�1��ʾ��Ϊe���Һ��ӣ����Լ��������ֵ��");
    				scanf("%d %d %d %s",&keyin,&mode,&input[0].key,input[0].others);
    				if( InsertNode(tree.elem[lp].T,keyin,mode,input[0])==ERROR )
    					printf("\n������Ľ����ԭ�ȹؼ����ظ���");
    				else
    					printf("\n����ɹ���");
				}
				break;
			case 8:
				//ɾ�����
				if( !tree.elem[lp].T )
					printf("�����������ڣ��޷�ɾ����㣡");
				else{
					pre=NULL;
					printf("��ǰ���ڽ���ɾ������������������Ҫɾ�����Ĺؼ��֣�");
					scanf("%d",&keyin);
					if( LocateNode(tree.elem[lp].T,keyin)==ERROR ){
						printf("\n��Ҫɾ���Ľ�㲻���ڣ�");
						break;
					}
					if( BiTreeDepth(tree.elem[lp].T)==1 ){
						DestroyBiTree(tree.elem[lp].T);tree.length--;
						printf("\nע�⣺��ɾ���˶�������Ψһ�ڵ㣡�˲�����ͬ�����ٶ�������");
					}
					else{
						DeleteNode(tree.elem[lp].T,keyin);
						printf("\nɾ���ɹ���");
					}
				} 
				break;
			case 9:
				//������� 
				if( !tree.elem[lp].T ){
					printf("�����������ڣ��޷�������");
					break; 
				}
				printf("��������Ľ��Ϊ��\n");
				PreOrderTraverse(tree.elem[lp].T,visit);
				break;
			case 10:
				//������� 
				if( !tree.elem[lp].T ){
					printf("�����������ڣ��޷�������");
					break; 
				}
				top=0; 
				printf("��������Ľ��Ϊ��\n");
				InOrderTraverse(tree.elem[lp].T,visit);
				break;
			case 11:
				//�������
				if( !tree.elem[lp].T ){
					printf("�����������ڣ��޷�������");
					break; 
				}
				printf("��������Ľ��Ϊ��\n"); 
				PostOrderTraverse(tree.elem[lp].T,visit);
				break;
			case 12:
				//��α��� 
				if( !tree.elem[lp].T ){
					printf("�����������ڣ��޷�������");
					break; 
				}
				tail=front=0;
				printf("��α����Ľ��Ϊ��\n");
				LevelOrderTraverse(tree.elem[lp].T,visit);
				break;
			case 13:
				//�������洢 
				if( !tree.elem[lp].T ){
					printf("�����������ڣ����ܽ��д洢������");
					break;
				}
				printf("��ǰ���ڽ��ж������Ĵ洢�������������ļ�����\n");
				scanf("%s",filename);
				SaveBiTree(tree.elem[lp].T,filename);
				printf("\n�洢�ɹ���");
				break;
			case 14:
				//��������ȡ 
				if( tree.elem[lp].T ){
					if(tree.elem[lp].T->lchild||tree.elem[lp].T->rchild){
						printf("��������Ϊ�գ����ܽ��ж�ȡ������");
						break;
					}
					DestroyBiTree(tree.elem[lp].T);
					tree.length--;
				}
				printf("��ǰ���ڽ��ж������Ķ�ȡ�������������ļ�����\n");
				scanf("%s",filename);
				LoadBiTree(tree.elem[lp].T,filename);
				printf("\n��ȡ�ɹ���");
				tree.length++;
				break;
			case 15:
				//�·����
				maxlen=0;
				if( !tree.elem[lp].T )
					printf("�����������ڣ��޷��ж��·���ͣ�");
				else
					printf("�·����Ϊ��%d",DFSMaxLength(tree.elem[lp].T,0));
				break;
			case 16:
				//�����������
				if( !tree.elem[lp].T )
					printf("�����������ڣ��޷��ж�����������ȣ�");
				else{
					printf("��ǰ���ڽ��в�ѯ����������Ȳ�����������Ҫ��ѯ�������Ĺؼ��֣�");
					int e1,e2;
					scanf("%d %d",&e1,&e2);
					for( int i=0 ; i<1000 ; i++ )
						num[i]=0;
					PreOrder_a(tree.elem[lp].T);
					if( num[e1]==0||num[e2]==0 )
						printf("\n������Ĺؼ��ֲ����ڣ�");
					else{
						BiTree t=LowerPublicAncestor(tree.elem[lp].T,e1,e2);
						printf("\n���Ƚ��ؼ���Ϊ��%d",t->data.key);
					}
				}
				break;
			case 17:
				//��ת������
				if( !tree.elem[lp].T )
					printf("�����������ڣ��޷����з�ת������");
				else{
					InvertTree(tree.elem[lp].T);
					printf("\n��ת�ɹ���");
				} 
				break;
			case 18:
				//��Ӷ�����
				if( tree.length>=10 ){
					printf("��ǰ��������Ŀ�ѳ������ޣ�"); 
					break;
				}
				printf("��ǰ���ڽ�����Ӷ�������������������ӵĶ���������");
				scanf("%s",treename); 
				if( AddBiTree(tree,treename)==ERROR )
					printf("\n��ǰ�����Ѵ��ڣ���һ�����ְɣ�");
				else
					printf("\n��ӳɹ���");
				break;
			case 19:
				//ɾ��������
				if( tree.length<=0 ){
					printf("��ǰ�Ѿ�û�ж�����������ɾ����");
					break;
				} 
				int ret_19;
				printf("��ǰ���ڽ���ɾ��������������������ɾ���Ķ���������");
				scanf("%s",treename);
				if( (ret_19=DeleteBiTree(tree,treename))==ERROR )
					printf("\nδ�ҵ���Ҫɾ���Ķ�������");
				else{
					printf("\nɾ���ɹ���");
					tree.length--;
					if( ret_19==lp ){
						printf("������ɾ���˵�ǰ�����Ķ��������´β���Ĭ�϶Զ�����1���У�");
						lp=1;
					}
				}
				break;
			case 20:
				//ѡ��Ҫ�����Ķ�����
				printf("��ǰ����ѡ��Ҫ�����Ķ�������������ѡ��Ķ���������");
				scanf("%s",treename);
				int ret_20;
				if( (ret_20=ChooseBiTree(tree,treename))==ERROR )
					printf("\nû���ҵ���Ҫ�����Ķ������������Ƿ�������ȷ��");
				else{
					printf("\nѡ��ɹ��������Ըö��������в�����");
					lp=ret_20;
				}
				break; 
			case 21:
				//��ն�����
				if( !tree.elem[lp].T )
					printf("�����������ڣ����ʧ�ܣ�");
				else{
					DestroyBiTree(tree.elem[lp].T);tree.length--;
					tree.elem[lp].T=(BiTree)malloc(sizeof(BiTNode));
					tree.length++;
					tree.elem[lp].T->lchild=NULL;
					tree.elem[lp].T->rchild=NULL;
					tree.elem[lp].T->data.key=-1;
					printf("����������գ�");
				} 
				break;
			case 22:
				//�жϿն�����
				if( !tree.elem[lp].T )
					printf("�����������ڣ��޷��пգ�");
				else{
					if( !tree.elem[lp].T->lchild&&!tree.elem[lp].T->rchild )
						printf("������Ϊ�գ�");
					else
						printf("��������Ϊ�գ�");
				} 
				break;
			case 23:
				//��������
				if( tree.elem[lp].T )
					printf("�������Ѵ��ڣ��޷�����������");
				else{
					tree.elem[lp].T=(BiTree)malloc(sizeof(BiTNode));
					tree.length++;
					tree.elem[lp].T->lchild=NULL;
					tree.elem[lp].T->rchild=NULL;
					tree.elem[lp].T->data.key=-1;
					printf("���������ɹ���");
				} 
			default:
				//ѡ���������� 
				printf("��������ȷ��ѡ�");
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
///////////////////////////////////////////////////////


/*******************************************************************
�������ƣ�CreateBiTree
��ʼ��������������������������� 
����˵�������ݴ��������Ķ����������������definition��ע�������Ԫ��
����ΪTElemType��������һ������ͼ��ʾ�Ķ�������T��Ҫ�������T�и����
�ؼ��־���Ψһ�ԣ�����ָ��ָ�����㣬����Ҫ�ڸ����֮��������ͷ��㡣 
����ֵ���ͣ�status
����������Ͱ������ 
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

    if( cnt==0 )							//��ʼ�Ƚ���Ͱ�����������ֹ�ؼ����ظ� 
        if( bullsort(definition)==ERROR )	//�ؼ����ظ� 
            return ERROR;
    if( definition[cnt].key==0 ){			//�ս�� 
        T=NULL;
        cnt++;
    }
    else if( definition[cnt].key==-1 )		//�������� 
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
�������ƣ�DestroyBiTree
��ʼ������������T���� 
����˵������������T�ÿգ����ͷ����н��Ŀռ䡣
����ֵ���ͣ�status
********************************************************************/
status DestroyBiTree(BiTree &T)
{
    if( T==NULL )			//TΪ���������������� 
        return OK;
    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    free(T);
    T=NULL;
    return OK;
}

/*******************************************************************
�������ƣ�BiTreeDepth
��ʼ������������T���� 
����˵�����������T��Ȳ��������ֵ
����ֵ���ͣ�int 
********************************************************************/
int BiTreeDepth(BiTree T)
{
    if( T==NULL )					//TΪ���������������� 
        return 0;
    int ld=BiTreeDepth(T->lchild)+1;
    int rd=BiTreeDepth(T->rchild)+1;
    return (ld>rd)?ld:rd;			//����max���� 
}

/*******************************************************************
�������ƣ�LocateNode
��ʼ������������T���� 
����˵����e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ������e���ҷ��������Ľ��
�����ظý��ָ�룬���޹ؼ���Ϊe�Ľ�㣬����NULL��
����ֵ���ͣ�BiTree 
********************************************************************/
BiTNode* LocateNode(BiTree T,KeyType e)
{
    if( !T )			//TΪ���������������� 
        return NULL;
    if( T->data.key==e )
        return T;
    //�����������β�ѯ 
    pre=T;
    BiTree lt=LocateNode(T->lchild,e);
    if( lt )
        return lt;
    pre=T;
    BiTree rt=LocateNode(T->rchild,e);
    return rt;
}

/*******************************************************************
�������ƣ�Assign
��ʼ������������T���� 
����˵����e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ�����ҽ��ؼ��ֵ���e�Ľ�
�㣬���ý��ֵ�޸ĳ�value������OK��Ҫ����ؼ��ֱ���Ψһ�ԣ��������
��ʧ�ܣ�����ERROR��
����ֵ���ͣ�status
����������Ͱ������������������Һ��� 
********************************************************************/
status bullsort_a(int def[]){	//Ͱ���� 
    for( int i=1 ; i<1000 ; i++ )
        if( def[i]>1 )
            return ERROR;
    return OK;
}
void PreOrder_a(BiTree T)		//������� 
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
    BiTree a=LocateNode(T,e);	//�ȶ�λ 
    if( !a )					//δ�ҵ���� 
        return ERROR;
    TElemType t=a->data;
    a->data=value;
    PreOrder_a(T);					//������� 
    if( bullsort_a(num)==ERROR ){	//�ؼ����ظ� 
        a->data=t;
        return ERROR;
    }
    return OK;
}

/*******************************************************************
�������ƣ�GetSibling
��ʼ������������T���� 
����˵����e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ�����ҽ��ؼ��ֵ���e�Ľ�
����ֵܽ�㣬�������ֵܽ��ָ�롣�������ʧ�ܣ�����NULL��
����ֵ���ͣ�BiTree
********************************************************************/
BiTNode* GetSibling(BiTree T,KeyType e)
{
    if( !T ){					//TΪ���� 
        pre=T;					//ʹǰ�����ΪT 
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
    //�Ⱥ������������ 
    pre=T;
    BiTree a=GetSibling(T->lchild,e);
    if( a )
        return a;
    pre=T->lchild;
    BiTree b=GetSibling(T->rchild,e);
    return b;
}

/*******************************************************************
�������ƣ�InsertNode
��ʼ������������T���� 
����˵����e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��LRΪ0��1��c�Ǵ������㣻
����LRΪ0����1��������c��T�У���Ϊ�ؼ���Ϊe�Ľ�������Һ��ӽ�㣬
���e��ԭ������������������Ϊ���c��������������OK���������ʧ�ܣ�����
ERROR���ر�أ���LRΪ-1ʱ����Ϊ�������룬ԭ�������Ϊc����������
����ֵ���ͣ�status
��������������������� 
********************************************************************/
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
{
    PreOrder_a(T);
    if( num[c.key] )		//����ֵ�ظ� 
        return ERROR;
    if( T==NULL )			//TΪ���� 
        return ERROR;
    if( LR==-1 ){			//���ڵ���� 
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
    //�Ⱥ������������ 
    pre=T;
    int a=InsertNode(T->lchild,e,LR,c);
    if( a==OK )
        return OK;
    pre=T;
    return InsertNode(T->rchild,e,LR,c);
}

/*******************************************************************
�������ƣ�DeleteNode
��ʼ������������T���� 
����˵����e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��ɾ��T�йؼ���Ϊe�Ľ�㣻
ͬʱ�����ݸñ�ɾ���ĶȽ������ۣ�
1.��ؼ���Ϊe�Ľ���Ϊ0��ɾ�����ɣ�
2.��ؼ���Ϊe�Ľ���Ϊ1���ùؼ���Ϊe�Ľ�㺢�Ӵ��汻ɾ����eλ�ã�
3.��ؼ���Ϊe�Ľ���Ϊ2����e�������������ΪLC�����汻ɾ����eλ�ã�
��e�������������ΪRC����ΪLC�����ҽڵ����������
�ɹ�ɾ�����󷵻�OK�����򷵻�ERROR��
����ֵ���ͣ�status
���������������Һ��� 
********************************************************************/
status DeleteNode(BiTree &T,KeyType e)
{
    pre=NULL;
    BiTree a=LocateNode(T,e);		//��λ��� 
    if( !a )						//��λʧ�� 
        return ERROR;
    if( !pre ){						//��ǰ����ɾ�����ڵ㣩 
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
        BiTree t=T;					//���¸��ڵ� 
        T=T->lchild;
        free(t);
        return OK;
    }
    if( !a->lchild&&!a->rchild ){	//���1������Ϊ0 
        if( a==pre->lchild )
            pre->lchild=NULL;
        if( a==pre->rchild )
            pre->rchild=NULL;
        free(a);
        return OK;
    }
    if( !a->lchild&&a->rchild ){	//���2.1������Ϊ1��û������ 
        BiTree b=a->rchild;
        if( pre->rchild==a )
            pre->rchild=b;
        if( pre->lchild==a )
            pre->lchild=b;
        free(a);
        return OK;
    }
    if( !a->rchild&&a->lchild ){	//���2.2������Ϊ1��û���Һ��� 
        BiTree b=a->lchild;
        if( pre->rchild==a )
            pre->rchild=b;
        if( pre->lchild==a )
            pre->lchild=b;
        free(a);
        return OK;
    }
    if( a->rchild&&a->lchild ){		//���3������Ϊ2 
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
�������ƣ�PreOrderTraverse
��ʼ������������T���� 
����˵�����Զ�����T�������������Visit��һ������ָ����βΣ���ʹ�ø�
�����Խ�����������ÿ�������ú���Visit����һ����һ�Ρ�
����ֵ���ͣ�status
����������visit 
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
�������ƣ�InOrderTraverse
��ʼ������������T���� 
����˵�����Զ�����T�������������Visit��һ������ָ����βΣ���ʹ�ø�
�����Խ�����������ÿ�������ú���Visit����һ����һ�Ρ�
����ֵ���ͣ�status
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
�������ƣ�PostOrderTraverse
��ʼ������������T���� 
����˵�����Զ�����T���к��������Visit��һ������ָ����βΣ���ʹ�ø�
�����Խ�����������ÿ�������ú���Visit����һ����һ�Ρ�
����ֵ���ͣ�status
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
�������ƣ�LevelOrderTraverse
��ʼ������������T���� 
����˵�����Զ�����T���а��������Visit��һ������ָ����βΣ���ʹ�ø�
�����Խ�����������ÿ�������ú���Visit����һ����һ�Ρ�
����ֵ���ͣ�status
********************************************************************/
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    if(!T)
        return ERROR;
    if(T->lchild)
        queue[tail++]=T->lchild;		//���ö��� 
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
        queue[tail++]=T->rchild;		//���ö��� 
    if(T->lchild)
        queue[tail++]=T->lchild;
    visit(T);
    if( tail!=front )
        LevelOrderTraverse(queue[front++],visit);
    return OK;
}

/*******************************************************************
�������ƣ�SaveBiTree
��ʼ������������T���� 
����˵������������Tд���ļ���ΪFileName���ļ��У�����OK
����ֵ���ͣ�status
����������������� 
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
�������ƣ�LoadBiTree
��ʼ������������T�����ڻ�Ϊ�� 
����˵���������ļ���ΪFileName�Ľ�����ݣ�������������
����ֵ���ͣ�status
�������������������� 
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
�������ƣ�DFSMaxLength
��ʼ������������T���� 
����˵�������ظ��ڵ㵽Ҷ�ӽڵ�����·���� 
����ֵ���ͣ�int
********************************************************************/
int DFSMaxLength(BiTree T,int num){
	if( !T )
		return num;
	int lnum=DFSMaxLength(T->lchild,num+T->data.key);
	int rnum=DFSMaxLength(T->rchild,num+T->data.key);
	return (lnum>rnum)?lnum:rnum;
}

/*******************************************************************
�������ƣ�LowerPublicAncestor
��ʼ������������T���� 
����˵�������ض������йؼ���Ϊe1�͹ؼ���Ϊe2��������������� 
����ֵ���ͣ�BiTree 
********************************************************************/
BiTree LowerPublicAncestor( BiTree T , int e1 , int e2 ){
	if( !T )
		return NULL;
	if( (T->data.key==e1)||(T->data.key==e2) )
		return T;
	BiTree t1=LowerPublicAncestor(T->lchild,e1,e2);
	BiTree t2=LowerPublicAncestor(T->rchild,e1,e2);
	if( t1&&t2 )		//���߾���ͨ���������ʽ�� 
		return T;		//�������ǵĹ������� 
	if( !t1&&!t2 )
		return NULL;
	if( t1 )			//ֻ��һ�߿ɱ������ʽ�� 
		return t1;		//���ı乫������ֵ�������� 
	if( t2 )
		return t2; 
}

/*******************************************************************
�������ƣ�InvertTree 
��ʼ������������T���� 
����˵����ʹ���������нڵ�����ҽڵ㻥�� 
����ֵ���ͣ�status 
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
�������ƣ�AddBiTree
��ʼ��������ǰ��������Ŀδ�������� 
����˵�������һ���µĶ����������������� 
����ֵ���ͣ�status
********************************************************************/
status AddBiTree(LISTS &tree,char listname[]){
	if( tree.length>=10 )	//����Lists���Χ 
        return ERROR;		//����
	//��ʼ������ 
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
	if( !tree.length )		//ListsΪ�� 
		return INFEASIBLE;	//������
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
	if( !tree.length )		//ListsΪ�� 
		return INFEASIBLE;	//������ 
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
