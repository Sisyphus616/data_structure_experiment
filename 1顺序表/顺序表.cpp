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
#define OVERFLOW -2			//��� 
typedef int status;
typedef int ElemType;
#define LIST_INIT_SIZE 100	//˳���ĳ�ʼ��С 
#define LISTINCREMENT  10	//˳���ÿ�η������ӵĴ�С 
typedef int ElemType;
typedef struct{  			//˳���˳��ṹ���Ķ���
      ElemType * elem;
      int length;
      int listsize;
 }SqList;
 typedef struct{  //���Ա�ļ������Ͷ���
     struct { char name[30];
               SqList L;    
     } elem[11];
     int length;
}LISTS;
LISTS Lists;      //���Ա��ϵĶ���Lists
/*******************************************/

/******************������*******************/
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

/*****************������********************/ 
int main(){
	/****************************************************************/
	/*						   ���������							*/
	/****************************************************************/ 
	system("mode con cols=82 lines=32 ");	//���ĳ�����С 
	system("title ���Ա�˳��洢�ṹ");	//���ĳ��������
	system("color 1F");						//������ɫ����������ɫ
	/****************************************************************/
	/*						    ��ʼ��								*/
	/****************************************************************/
	int op=1;			//�û�����ѡ�� 
	SqList L[11];		//�����Ա���
	LISTS list;			//�����Ա��ʼ�� 
	list.length=1;
	char filename[50];	//�洢�ļ���
	char listname[50];	//�洢���Ա��� 
	int lp=1;			//��ǰ��������Ա�ָ��
	int val,pos;		//��ȡ/����Ԫ���ã�val:Ԫ�ص�ֵ,pos:Ԫ�ص��߼����� 
	ElemType pre,next;	//��ȡǰ��/����ã�pre:ǰ����next:��� 
	ElemType ins;		//����Ԫ���ã��洢����Ԫ�ص�ֵ 
	int cnt=0;			//��¼�������� 
	//���Ա��ʼ�� 
	for( int i=1 ; i<11 ; i++ ){
		list.elem[i].L.elem=NULL;
		list.elem[i].L.length=0;
		list.elem[i].L.listsize=0;
	} 
	char *defaultname="���Ա�";
	for( int i=0 ; defaultname[i]!='\0' ; i++ )
		list.elem[1].name[i]=defaultname[i];
	/****************************************************************/
	/*						   �˵����� 							*/
	/****************************************************************/
	while(op){
		system("cls");
	    printf("\n\n");
		printf("	  \t\t\t���Ա�˳��ṹ�˵�\t\t\n\n");
		printf(" �������10��˳�����ж���������ʼ����δ��ʼ��������Ĭ��Ϊ�����Ա�\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf(" *1. ��ʼ�����Ա�         \t\t7.  ����Ԫ��\t\t\t\t*\n");
		printf(" *2. �ݻ����Ա�       \t\t\t8.  ��ȡǰ��Ԫ��\t\t\t*\n");
		printf(" *3. ������Ա�         \t\t9.  ��ȡ���Ԫ�� \t\t\t*\n");
		printf(" *4. ���Ա��п�         \t\t10. ����Ԫ��\t\t\t\t*\n");
		printf(" *5. ���Ա���        \t\t\t11. ɾ��Ԫ��\t\t\t\t*\n");
		printf(" *6. ��ȡԪ��           \t\t12. �������Ա�\t\t\t\t*\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf(" *13.���Ա�洢          \t\t14. ���Ա��ȡ\t\t\t\t*\n");
		printf(" *15.��������������     \t\t16. ��ΪK��������\t\t\t*\n");
		printf(" *17.��С��������         \t\t18. ������Ա�\t\t\t\t*\n");
		printf(" *19.�Ƴ����Ա�          \t\t20. ѡ��Ҫ���������Ա�\t\t\t*\n\n");
		printf(" *0. �˳�\t\t\t\n");
		printf(" --------------------------------------------------------------powered by �Ϻ���\n");
		printf("��ǰ���������Ա����Ա�%d��%s\n\n",lp,list.elem[lp].name);
		printf("����������0~20��ѡ����Ĳ���:");
		scanf("%d",&op);//ѡ��op��ֵ,����switch
		printf("\n");
		switch(op){
			case 0:
				break;
			case 1:
				//��ʼ�����Ա�
				if( list.elem[lp].L.elem ){
					printf("����ʧ�ܣ����Ա��Ѵ��ڣ�");
					break;
				}
				if( InitList(list.elem[lp].L)==OK )
					printf("���Ա����ɹ���");
				else
					printf("����ʧ�ܣ����Ա��Ѵ��ڣ�");
				break;
			case 2:
				//�ݻ����Ա�
				if( !list.elem[lp].L.elem ){
					printf("����ʧ�ܣ����Ա����ڣ�");
					break;
				}
				if( DestroyList(list.elem[lp].L)==OK )
					printf("���������Ա�");
				else
					printf("����ʧ�ܣ����Ա����ڣ�");
				break; 
			case 3:
				//������Ա�
				if( !list.elem[lp].L.elem ){
					printf("���ʧ�ܣ����Ա����ڣ�");
					break;
				}
				if( ClearList(list.elem[lp].L)==OK )
					printf("��������Ա�");
				else
					printf("���ʧ�ܣ����Ա����ڣ�");
				break;
			case 4:
				//�ж����Ա��Ƿ�Ϊ��
				if( ListEmpty(list.elem[lp].L)==INFEASIBLE ) 
					printf("�ж�ʧ�ܣ����Ա����ڣ�");
				else if( ListEmpty(list.elem[lp].L)==TRUE )
					printf("���Ա�Ϊ�գ�");
				else	//ListEmpty(L[lp])==FALSE
					printf("���Ա�Ϊ�գ�"); 
				break;
			case 5:
				//���Ա���
				if( !list.elem[lp].L.elem ){
					printf("���Ա����ڣ�");
					break;
				}
				if( ListLength(list.elem[lp].L)==INFEASIBLE )
					printf("���Ա����ڣ�");
				else
					printf("���Ա���Ϊ%d",ListLength(list.elem[lp].L)); 
				break;
			case 6:
				//��ȡԪ��
				if( !list.elem[lp].L.elem ){
					printf("���Ա����ڣ�");
					break;
				}
				printf("��ǰ���ڽ��л�ȡԪ�ز�������������Ҫ��ѯ��Ԫ�������Ա��е��߼�����");
				scanf("%d",&pos);
				if( GetElem(list.elem[lp].L,pos,val)==INFEASIBLE )
					printf("\n���Ա����ڣ�");
				else if( GetElem(list.elem[lp].L,pos,val)==ERROR )
					printf("\n��ȡʧ�ܣ������±�ֵ�Ƿ�Ϸ���");
				else
					printf("\n����Ҫ��ѯ��Ԫ��ֵΪ%d",val);
				break;
			case 7:
				//����Ԫ��
				if( !list.elem[lp].L.elem ){
					printf("���Ա����ڣ�");
					break;
				} 
				printf("��ǰ���ڽ��в���Ԫ�ز�������������Ҫ��ѯ��ֵ��"); 
				scanf("%d",&val);
				if( (pos=LocateElem(list.elem[lp].L,val))==INFEASIBLE )	//�ѷ���ֵ����pos�У������ظ����� 
					printf("\n���Ա����ڣ�");
				else if( pos!=ERROR )
					printf("\n��ѯ�ɹ�������Ҫ��ֵ�ڱ��е�%d����",pos);
				else
					printf("\n��Ҫ��ѯ��ֵ���ڱ��У�");
				break;
			case 8:
				//��ȡǰ��Ԫ��
				if( !list.elem[lp].L.elem ){
					printf("���Ա����ڣ�");
					break;
				}
				printf("��ǰ���ڽ��л�ȡǰ��Ԫ�ز�������������Ҫ��ѯǰ����Ԫ�أ�");
				scanf("%d",&val);
				if( PriorElem(list.elem[lp].L,val,pre)==INFEASIBLE )
					printf("\n���Ա����ڣ�");
				else if( PriorElem(list.elem[lp].L,val,pre)==ERROR )
					printf("\n��ȡʧ�ܣ�������Ҫ��ѯ��Ԫ���Ƿ��ڱ��л�Ϊ��ͷ��");
				else
					printf("\n��ȡ�ɹ���%d��ǰ��Ԫ��Ϊ%d",val,pre);
				break;
			case 9:
				//��ȡ���Ԫ��
				if( !list.elem[lp].L.elem ){
					printf("���Ա����ڣ�");
					break;
				}
				printf("��ǰ���ڽ��л�ȡ���Ԫ�ز�������������Ҫ��ѯ��̵�Ԫ�أ�");
				scanf("%d",&val);
				if( NextElem(list.elem[lp].L,val,pre)==INFEASIBLE )
					printf("\n���Ա����ڣ�");
				else if( NextElem(list.elem[lp].L,val,pre)==ERROR )
					printf("\n��ȡʧ�ܣ�������Ҫ��ѯ��Ԫ���Ƿ��ڱ��л�Ϊ��β��");
				else
					printf("\n��ȡ�ɹ���%d�ĺ��Ԫ��Ϊ%d",val,pre);
				break;
			case 10:
				//����Ԫ�� 
				if( !list.elem[lp].L.elem ){
					printf("���Ա����ڣ�");
					break;
				}
				printf("��ǰ���ڽ��в���Ԫ�ز�������������Ҫ����Ԫ�صĸ�����");
				int num;
				scanf("%d",&num);
				while( num ){
					printf("\n��ǰ���ڽ��в���Ԫ�ز�������������Ҫ����Ԫ�ص��߼������Ԫ��ֵ\n");
					printf("�߼�����");
					scanf("%d",&pos);
					printf("Ԫ��ֵ��");
					scanf("%d",&ins); 
					if( ListInsert(list.elem[lp].L,pos,ins)==OK )
						printf("\n����ɹ���\n");
					else if( ListInsert(list.elem[lp].L,pos,ins)==INFEASIBLE )
						printf("\n���Ա�����\n");
					else
						printf("\n����ʧ�ܣ������±�ֵ�Ƿ�Ϸ�\n");
					num--;
				}
				break;
			case 11:
				//ɾ��Ԫ��
				if( !list.elem[lp].L.elem ){
					printf("���Ա����ڣ�");
					break;
				}
				printf("��ǰ���ڽ���ɾ��Ԫ�ز�������������Ҫɾ��Ԫ�ص��߼�����");
				scanf("%d",&pos);
				if( ListDelete(list.elem[lp].L,pos,ins)==OK )
					printf("\nɾ���ɹ���ɾ����Ԫ��Ϊ%d",ins);
				else if( ListDelete(list.elem[lp].L,pos,ins)==INFEASIBLE )
					printf("\n���Ա�����");
				else
					printf("\nɾ��ʧ�ܣ������±�ֵ�Ƿ�Ϸ�!");
				break;
			case 12:
				//�������Ա�
				//������Ҫ���ж����Ա��Ƿ����
				if( !list.elem[lp].L.elem )
					printf("���Ա����ڣ�");
				else{
					printf("���Ա�%d��Ԫ�������ǣ�\n",lp);
					ListTraverse(list.elem[lp].L);
				} 
				break;
			case 13:
				//���Ա�洢
				if( !list.elem[lp].L.elem ){
					printf("���Ա����ڣ�");
					break;
				}
				printf("��ǰ���ڽ������Ա�洢��������������Ҫ���ɵ��ļ�����\n");
				scanf("%s",filename);
				if( SaveList(list.elem[lp].L,filename)==INFEASIBLE )
					printf("\n���Ա����ڣ�");
				else
					printf("\n�洢�ɹ���");
				break;
			case 14:
				//���Ա��ȡ
				printf("��ǰ���ڽ������Ա��ȡ��������������Ҫ��ȡ���ļ���(������չ��)��\n");
				scanf("%s",filename);
				if( LoadList(list.elem[lp].L,filename)==OK )
					printf("\n��ȡ�ɹ���");
				else if( LoadList(list.elem[lp].L,filename)==INFEASIBLE )
					printf("\n���Ա�Ϊ�գ����ܽ��ж�ȡ������");
				else
					printf("\n��ȡʧ�ܣ������ļ��Ƿ���ڣ�");
				break;
			case 15:
				//��������������
				int ret15;
				if( (ret15=MaxSubArray(list.elem[lp].L))==INFEASIBLE )
					printf("���Ա����ڻ�Ϊ�գ�");
				else
					printf("��������������Ϊ��%d",ret15);
				break;
			case 16:
				//���غ�ΪK����������Ŀ 
				int ret16,k;
				printf("��ǰ���ڽ������ΪK����������Ŀ�Ĳ�����������K��ֵ��");
				scanf("%d",&k);
				if( (ret16=SubArrayNum(list.elem[lp].L,k))==INFEASIBLE )
					printf("\n���Ա����ڻ�Ϊ�գ�");
				else
					printf("\n��ΪK����������ĿΪ��%d",ret16);
				break;
			case 17:
				//��С��������
				if( sortList(list.elem[lp].L)==INFEASIBLE )
					printf("���Ա����ڻ�Ϊ�գ�");
				else
					printf("����ɹ���");
				break; 
			case 18:
				//�����Ա����������±� 
				if( list.length>=10 )
					printf("��ǰ���Ա���Ŀ�ѳ������ޣ�");
				else{
					printf("��ǰ���ڽ���������Ա�Ĳ�������������Ҫ�����±�����ƣ�\n");
					scanf("%s",listname);
					if( AddList(list,listname)==ERROR )
						printf("\n���������ظ�����һ�����ְɣ�");
					else
						printf("\n��ӳɹ���");
				}
				break;
			case 19:
				//�����Ա�������Ƴ���
				if( !list.elem )
					printf("���Ա�����û�����Ա��ȴ���һ���ɣ�");
				else{
					int ret19;
					printf("��ǰ���ڽ����Ƴ����Ա�Ĳ�������������Ҫ�Ƴ������Ա�����ƣ�\n");
					scanf("%s",listname);
					if((ret19=RemoveList(list,listname))==ERROR)
						printf("\nû���ҵ�����������Ա�Ү���������Ƿ��������");
					else{
						printf("\n�Ƴ��ɹ��ˣ�\n");
						if( ret19<lp )
							lp--;
						else if( ret19==lp ){
							printf("\n������ɾ���˵�ǰ���Ա��´β���Ĭ�϶Ե�һ�����Ա���У�");
							lp=1;
						}
					}
				}
				break; 
			case 20:
				//�����Ա������ѡ��Ҫ���������Ա� 
				printf("��ǰ���ڽ���ѡ��������Ա�Ĳ�������������Ҫ���������Ա�����ƣ�\n");
				scanf("%s",listname);
				int ret20;
				if( (ret20=LocateList(list,listname))==INFEASIBLE )
					printf("\n���Ա�����û�����Ա��ȴ���һ���ɣ�");
				else if( ret20==ERROR )
					printf("\nû���ҵ�����������Ա�Ү���������Ƿ��������");
				else{
					lp=ret20;
					printf("\n��λ�ɹ���");
				}
				break;
			default:
				//����op����
				printf("��������ȷ��ѡ�");
				break; 
		}
		if( op!=0 ){
			printf("\n\n�������������һ������\n\n");
			system("pause");
			cnt++;
		}
	} 
	printf("ллʹ�ã������ι�������%d�β�������ӭ�´�������\n",cnt);
	Sleep(2000);
	return 0;
}
/*******************************************/


/*******************************************************************
�������ƣ�InitList
��ʼ���������Ա�L������ 
����˵����������Ա�L�����ڣ���������ǹ���һ���յ����Ա�����OK��
���򷵻�INFEASIBLE�� 
����ֵ���ͣ�  
********************************************************************/
status InitList(SqList& L)
{
    if(L.elem)				//���Ա��Ѵ��� 
        return INFEASIBLE;	//������ 
    L.elem=(ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    L.length=0;
    L.listsize=LIST_INIT_SIZE;
    return OK;
}

/*******************************************************************
�������ƣ�DestroyList
��ʼ���������Ա�L�Ѵ��� 
����˵����������Ա�L���ڣ��ò����ͷ����Ա�Ŀռ䣬ʹ���Ա��Ϊδ��
ʼ��״̬������OK���������һ��δ��ʼ�����Ա��ǲ��ܽ������ٲ����ģ�
����INFEASIBLE��
����ֵ���ͣ� status 
********************************************************************/
status DestroyList(SqList& L)
{
    if(L.elem){				//�����Ա���� 
        free(L.elem);
        //�����ֵ��� 
        L.elem=NULL;
        L.length=0;
        L.listsize=0;
    }
    else					//���Ա����� 
        return INFEASIBLE;	//������ 
    return OK;
}

/*******************************************************************
�������ƣ�ClearList
��ʼ���������Ա�L�Ѵ��� 
����˵���������Ա�L�����ڣ�����INFEASIBLE������������Ա�L������OK��
����ֵ���ͣ� status 
********************************************************************/
status ClearList(SqList& L)
{
    if( L.elem ){			//�����Ա���� 
        L.length=0;
    }
    else					//���Ա����� 
        return INFEASIBLE;	//������ 
    return OK;
}

/*******************************************************************
�������ƣ�ListEmpty
��ʼ���������Ա�L�Ѵ��� 
����˵���������Ա�L�����ڣ��򷵻�INFEASIBLE�������Ա�L����Ϊ0����
��TRUE����Ϊ0�򷵻�FALSE��
����ֵ���ͣ� status 
********************************************************************/
status ListEmpty(SqList L)
{
    if( !L.elem )			//�����Ա����� 
        return INFEASIBLE;	//������ 
    if( L.length==0 )		//���Ա�Ϊ�� 
        return TRUE;
    else					//���Ա�Ϊ�� 
        return FALSE;
}

/*******************************************************************
�������ƣ�ListLength 
��ʼ���������Ա�L�Ѵ��� 
����˵���������Ա�L�����ڣ�����INFEASIBLE�����򷵻����Ա�L�ĳ��ȡ�
����ֵ���ͣ� status 
********************************************************************/
status ListLength(SqList L)
{
    if( !L.elem )			//�����Ա����� 
        return INFEASIBLE;	//������ 
    else
        return L.length; 
}

/*******************************************************************
�������ƣ�GetElem 
��ʼ���������Ա�L�Ѵ��� 
����˵���������Ա�L�����ڣ�����INFEASIBLE����i<1����i�������Ա�L�ĳ�
�ȣ��򷵻�ERROR������ȡ�ɹ�����ֵ����e��������OK��
����ֵ���ͣ� status 
********************************************************************/
status GetElem(SqList L,int i,ElemType &e)
{
    if( !L.elem )			//�����Ա����� 
        return INFEASIBLE;	//������ 
    if( i<1||i>L.length )	//���±�ֵ���Ϸ� 
        return ERROR;		//���� 
    e=L.elem[i-1];
    return OK;
}

/*******************************************************************
�������ƣ�LocateElem
��ʼ���������Ա�L�Ѵ��� 
����˵���������Ա�L�����ڣ�����INFEASIBLE����û���ҵ�ָ����Ԫ��e����
����ʧ�ܣ�����ERROR�������ҳɹ����򷵻�Ԫ���߼����i��
����ֵ���ͣ� int
********************************************************************/
int LocateElem(SqList L,ElemType e)
{
    if( !L.elem )			//�����Ա����� 
        return INFEASIBLE;	//������ 
    int pos=-1;				//����Ԫ���±꣬��ʼ��Ϊ-1 
    for( int i=0 ; i<L.length ; i++ ){
        if( L.elem[i]==e ){
            pos=i;
            break;
        }
    }
    if( pos==-1 )			//pos��δԭֵ����δ�ҵ� 
        return ERROR;		//���� 
    return pos+1;
}

/*******************************************************************
�������ƣ�PriorElem
��ʼ���������Ա�L�Ѵ��� 
����˵���������Ա�L�����ڣ�����INFEASIBLE����û���ҵ�ָ��Ԫ��e��ǰ����
�����ʧ�ܣ�����ERROR�������ҳɹ�����ֵ����pre��������OK��
����ֵ���ͣ� status
********************************************************************/
status PriorElem(SqList L,ElemType e,ElemType &pre)
{
    if( !L.elem )			//�����Ա����� 
        return INFEASIBLE;	//������ 
    for( int i=0 ; i<L.length ; i++ ){
        if( L.elem[i]==e ){	//�ҵ���ֵ 
            if( i==0 )		//����ֵ��Ӧ������Ԫ�أ���ǰ�� 
                return ERROR;
            pre=L.elem[i-1];
            return OK;		//Ԫ�ش����Ҳ�Ϊ��Ԫ�� 
        }
    }
    return ERROR;			//ѭ����������δ�ҵ���Ԫ�� 
}
//ע�������һ��дʱû�п�����Ԫ��û��ǰ�����������޸�ʱֱ�ӽ�����������
//Ԫ���Ƿ�Ϊ��Ԫ�أ�����һ�ָķ���������Һ�����õķ������ƣ�����ѭ��ʱ
//ֱ�Ӵ�i=1��ʼѭ���� 

/*******************************************************************
�������ƣ�NextElem
��ʼ���������Ա�L�Ѵ��� 
����˵���������Ա�L�����ڣ�����INFEASIBLE����û���ҵ�ָ��Ԫ��e�ĺ�̣�
�����ʧ�ܣ�����ERROR�������ҳɹ�����ֵ����next��������OK��
����ֵ���ͣ� status
********************************************************************/
status NextElem(SqList L,ElemType e,ElemType &next)
{
    if( !L.elem )			//�����Ա����� 
        return INFEASIBLE;	//������ 
    for( int i=0 ; i<L.length-1 ; i++ ){
	//����ѭ����L.length-2���ɣ���Ϊ��ʹL.elem[L.length-1]==eҲû�к�� 
        if( L.elem[i]==e ){	//�ҵ���ֵ 
            next=L.elem[i+1];
            return OK;
        }
    }
    return ERROR;			//ѭ����������δ�ҵ���Ԫ�� 
}

/*******************************************************************
�������ƣ�ListInsert
��ʼ���������Ա�L�Ѵ��� 
����˵����������Ա�L�����ڣ�����INFEASIBLE�����������Ա�L�ĵ�i��Ԫ��
ǰ�����µ�Ԫ��e������ɹ�����OK��ʧ�ܷ���ERROR��
����ֵ���ͣ� status
********************************************************************/
status ListInsert(SqList &L,int i,ElemType e)
{
    if( !L.elem )					//�����Ա����� 
        return INFEASIBLE;			//������ 
    if( L.length==L.listsize ){		//���Ա����� 
        L.elem=(ElemType*)realloc(L.elem,sizeof(ElemType)*(L.listsize+LISTINCREMENT));
        L.listsize+=LISTINCREMENT;
    }
    if( i<1||i>L.length+1)			//���±겻�Ϸ� 
        return ERROR;				//���� 
    for( int j=L.length ; j>=i ; j-- )		//�ƶ�Ԫ�� 
        L.elem[j]=L.elem[j-1];
    L.elem[i-1]=e;
    L.length++;
    return OK;
}

/*******************************************************************
�������ƣ�ListDelete
��ʼ���������Ա�L�Ѵ��� 
����˵���������Ա�L�����ڣ�����INFEASIBLE������ɾ�����Ա�L�ĵ�i��Ԫ
�أ���ɾ���ɹ���ɾ����ֵ����e������OK����ɾ��ʧ���򷵻�ERROR��
����ֵ���ͣ� status
********************************************************************/
status ListDelete(SqList &L,int i,ElemType &e)
{
    if( !L.elem )			//�����Ա����� 
        return INFEASIBLE;	//������ 
    if( i<1||i>L.length)	//���±겻�Ϸ� 
        return ERROR;		//���� 
    e=L.elem[i-1];
    for( int j=i ; j<L.length ; j++ )		//�ƶ�Ԫ�� 
        L.elem[j-1]=L.elem[j];
    L.length--;
    return OK;
}

/*******************************************************************
�������ƣ�ListTraverse
��ʼ���������Ա�L�Ѵ��� 
����˵���������Ա�L�����ڣ�����INFEASIBLE������������Ա��ÿһ��Ԫ
�أ�������OK��
����ֵ���ͣ� status
********************************************************************/
status ListTraverse(SqList L)
{
    if( !L.elem )			//�����Ա����� 
        return INFEASIBLE;	//������ 
    for( int i=0 ; i<L.length ; i++ ){
        printf("%d",L.elem[i]);
        if( i!=L.length-1 )
        printf(" ");
    }
    return OK;
}

/*******************************************************************
�������ƣ�SaveList
��ʼ���������Ա�L�Ѵ��� 
����˵����������Ա�L�����ڣ�����INFEASIBLE���������Ա�L��ȫ��Ԫ��
д�뵽�ļ���ΪFileName���ļ��У�����OK��
����ֵ���ͣ� status
********************************************************************/
status  SaveList(SqList L,char FileName[])
{
    if( !L.elem )			//�����Ա����� 
        return INFEASIBLE;	//������ 
    FILE *fp;
    fp=fopen(FileName,"w+");
    fprintf(fp,"%d ",L.length);			//Ԫ�ظ����ͱ���д���ļ���������� 
    fprintf(fp,"%d ",L.listsize);
    for( int i=0 ; i<L.length ; i++ )
        fprintf(fp,"%d ",L.elem[i]);
    fclose(fp);
    return OK;
}

/*******************************************************************
�������ƣ�LoadList
��ʼ���������Ա�LΪ�� 
����˵����������Ա�L���ڣ���ʾL���Ѿ������ݣ��������ݻḲ��ԭ������
�����ݶ�ʧ������INFEASIBLE�������ļ���ΪFileName�����ݶ��뵽���Ա�
L�У�����OK����ʵ�鲻������׷�ӵķ�ʽ�����ļ�����׷�ӵ��������Ա��С�
����ֵ���ͣ� status
********************************************************************/
status  LoadList(SqList &L,char FileName[])
{
    if( L.elem )			//�����Ա�Ϊ�� 
        return INFEASIBLE;	//������ 
    FILE *fp;
    fp=fopen(FileName,"r+");
    if( fp==NULL )			//�ļ������� 
    	return ERROR;
    fscanf(fp,"%d %d",&L.length,&L.listsize);		//�ȶ���Ԫ�ظ����ͱ� 
    L.elem=(ElemType*)malloc(sizeof(ElemType)*L.listsize);
    for( int i=0 ; i<L.length ; i++ )
        fscanf(fp,"%d",&L.elem[i]);
    fclose(fp);
    return OK;
}

/*******************************************************************
�������ƣ�AddList
��ʼ��������Ҫ��ӵ����Ա�LΪ��
����˵����Lists��һ����˳�����ʽ��������Ա�ļ��ϣ��ڼ���������һ
���µĿ����Ա����ӳɹ�����OK�����򷵻�ERROR��
����ֵ���ͣ� status
********************************************************************/
status AddList(LISTS &Lists,char ListName[])
{
    if( Lists.length>=10 )	//����Lists���Χ 
        return ERROR;		//����
	//��ʼ������ 
	for( int j=1 ; j<=Lists.length ; j++ )
    	if( !strcmp(ListName,Lists.elem[j].name) )
    		return ERROR;
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
�������ƣ�RemoveList
��ʼ������Lists���� 
����˵����Lists��һ����˳�����ʽ��������Ա�ļ��ϣ��ڼ����в�����
��ΪListName�����Ա�����ɾ��������OK�����򷵻�ERROR��
����ֵ���ͣ� status
********************************************************************/
status RemoveList(LISTS &Lists,char ListName[])
{
	if( !Lists.length )		//ListsΪ�� 
		return INFEASIBLE;	//������ 
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
�������ƣ�LocateList
��ʼ������Lists���� 
����˵����Lists��һ����˳�����ʽ��������Ա�ļ��ϣ��ڼ����в�������
ΪListName�����Ա����򷵻����Ա���߼���ţ����򷵻�0��
����ֵ���ͣ� int
********************************************************************/
int LocateList(LISTS Lists,char ListName[])
{
	if( !Lists.length )		//ListsΪ�� 
		return INFEASIBLE;	//������ 
    for( int i=1 ; i<=Lists.length ; i++ ){
        if( !strcmp(ListName,Lists.elem[i].name) )
            return i;
    }
    return 0;
}

/*******************************************************************
�������ƣ�MaxSubArray
��ʼ���������Ա�L�����ҷǿ� 
����˵�����ҳ�һ���������͵����������飨���������ٰ���һ��Ԫ�أ���
����������
����ֵ���ͣ� int
********************************************************************/
int MaxSubArray( SqList &L ){
	if( !L.elem||L.length==0 )		//���Ա����ڻ�Ϊ�� 
		return INFEASIBLE;			//������ 
	int sum=0;
	int ans=L.elem[0];
	for( int i=0 ; i<L.length ; i++ ){	//���ߴ��� 
		sum+=L.elem[i];
		ans=(sum>ans)?sum:ans;		//ģ��max���� 
		if( sum<0 )					//sumС��0������ 
			sum=0;
	}
	return ans;
}

/*******************************************************************
�������ƣ�SubArrayNum
��ʼ���������Ա�L�����ҷǿ� 
����˵�������ظ������к�Ϊk������������ĸ���
����ֵ���ͣ� int
********************************************************************/
int SubArrayNum( SqList &L,int k ){
	if( !L.elem||L.length==0 )		//���Ա����ڻ�Ϊ�� 
		return INFEASIBLE;			//������
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
�������ƣ�sortList
��ʼ���������Ա�L�����ҷǿ� 
����˵������L��С��������
����ֵ���ͣ� status
********************************************************************/
status sortList( SqList &L ){
	if( !L.elem||L.length==0 )		//���Ա����ڻ�Ϊ�� 
		return INFEASIBLE;			//������
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
