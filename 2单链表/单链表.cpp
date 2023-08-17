#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h> 
#include<windows.h>

/*************************Ԥ����*************************/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; 		//����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode{  		//��������ʽ�ṹ�����Ķ���
      ElemType data;
      struct LNode *next;
      char name[30];
}LNode,*LinkList;
/********************************************************/

/*************************������*************************/
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
	int op=1;			//�û�ѡ��ѡ��
	int lp=1;			//�������Ա��±�ָ�� 
	int val,pos;		//��ȡԪ���ã�val:Ԫ�ص�ֵ��pos:Ԫ��λ��
	ElemType pre,next;	//��ȡǰ��/����ã�pre:ǰ����next:��� 
	ElemType ins;		//����Ԫ���ã��洢����Ԫ�ص�ֵ 
	char filename[50];	//�ļ��� 
	LinkList list[11];	//�����Ա����
	char listname[30];	//���Ա��� 
	for( int i=0 ; i<=10 ; i++ )
		list[i]=NULL;
	int listlength=0;	//���Ա���Ŀ 
	int cnt=0;			//��¼��������
	/****************************************************************/
	/*						   �˵����� 							*/
	/****************************************************************/
	while(op){
		system("cls");
		printf("\n\n");
		printf("	  \t\t\t���Ա�˳��ṹ�˵�\t\t\n\n");
		printf(" �������10��������ж����������Ա��δ��ʼ����Ĭ�϶Ա��Ϊ1�����Ա����\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf(" *1. ��ʼ�����Ա�         \t\t7.  ����Ԫ��\t\t\t\t*\n");
		printf(" *2. �ݻ����Ա�       \t\t\t8.  ��ȡǰ��Ԫ��\t\t\t*\n");
		printf(" *3. ������Ա�         \t\t9.  ��ȡ���Ԫ�� \t\t\t*\n");
		printf(" *4. ���Ա��п�         \t\t10. ����Ԫ��\t\t\t\t*\n");
		printf(" *5. ���Ա���        \t\t\t11. ɾ��Ԫ��\t\t\t\t*\n");
		printf(" *6. ��ȡԪ��           \t\t12. �������Ա�\t\t\t\t*\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf(" *13.���Ա�洢          \t\t14. ���Ա��ȡ\t\t\t\t*\n");
		printf(" *15.����ת            \t\t16. ɾ����������n���\t\t\t*\n");
		printf(" *17.��������            \t\t18. ������Ա�\t\t\t\t*\n");
		printf(" *19.�Ƴ����Ա�          \t\t20. ѡ��Ҫ���������Ա�\t\t\t*\n\n");
		printf(" *0. �˳�\t\t\t\n");
		printf(" ----------------------------------------------------------------power by �Ϻ���\n");
		printf("��ǰ���������Ա����Ա�%d\n\n",lp);
		printf("����������0~20��ѡ����Ĳ���:");
		scanf("%d",&op);	//ѡ��op��ֵ,����switch
		printf("\n");
		switch(op){
			case 0:
				break;
			case 1:
				//��ʼ�����Ա�
				if( list[lp] )
					printf("����ʧ�ܣ����Ա��Ѵ��ڣ�");
				else{
					InitList(list[lp]);
					listlength++;
					printf("�����ɹ���");
				} 
				break;
			case 2:
				//�������Ա�
				if( !list[lp] )
					printf("����ʧ�ܣ����Ա����ڣ�");
				else{
					DestroyList(list[lp]);
					printf("���ٳɹ���");
					listlength--;
				}
				break;
			case 3:
				//������Ա� 
				if( !list[lp] )
					printf("���ʧ�ܣ����Ա����ڣ�");
				else{
					ClearList(list[lp]);
					printf("���Ա�����գ�");
				}
				break;
			case 4:
				//���Ա��п�
				if( !list[lp] )
					printf("���Ա����ڣ��޷��жϣ�");
				else{
					if( ListEmpty(list[lp])==TRUE )
						printf("���Ա�Ϊ�գ�");
					else
						printf("���Ա�Ϊ�գ�");
				} 
				break;
			case 5:
				//���Ա���
				if( !list[lp] )
					printf("���Ա����ڣ��޷��жϣ�");
				else
					printf("���Ա���Ϊ��%d",ListLength(list[lp]));
				break;
			case 6:
				//��ȡԪ��
				if( !list[lp] )
					printf("���Ա����ڣ��޷���ȡ��");
				else{
					printf("��ǰ���ڽ��л�ȡԪ�ز�������������Ҫ��ѯ��Ԫ�������Ա��е��߼�����");
					scanf("%d",&pos);
					if( GetElem(list[lp],pos,val)==ERROR )
						printf("\n��ȡʧ�ܣ������±�ֵ�Ƿ�Ϸ���");
					else
						printf("\n��Ҫ��ѯ��Ԫ��Ϊ��%d",val);
				}
				break;
			case 7:
				//����Ԫ��
				if( !list[lp] )
					printf("���Ա����ڣ��޷����ң�");
				else{
					printf("��ǰ���ڽ��в���Ԫ�ز�������������Ҫ��ѯ��ֵ��"); 
					scanf("%d",&val);
					if( (pos=LocateElem(list[lp],val))==ERROR )
						printf("\n����ʧ�ܣ���������Ԫ���Ƿ������Ա��ڣ�");
					else
						printf("��Ҫ�ҵ�Ԫ���ڱ��е�%d��",pos);
				}
				break;
			case 8:
				//��ȡǰ��Ԫ��
				if( !list[lp] )
					printf("���Ա����ڣ��޷���ȡ��");
				else{
					printf("��ǰ���ڽ��л�ȡǰ��Ԫ�ز�������������Ҫ��ѯǰ����Ԫ�أ�");
					scanf("%d",&val);
					if( PriorElem(list[lp],val,pre)==ERROR )
						printf("\n��ȡʧ�ܣ�������Ҫ��ѯ��Ԫ���Ƿ��ڱ��л�Ϊ��ͷ��");
					else
						printf("\n��Ҫ�ҵ�%d��ǰ��Ԫ��Ϊ��%d",val,pre);
				}
				break;
			case 9:
				//��ȡ���Ԫ��
				if( !list[lp] )
					printf("���Ա����ڣ��޷���ȡ��");
				else{
					printf("��ǰ���ڽ��л�ȡ���Ԫ�ز�������������Ҫ��ѯ��̵�Ԫ�أ�");
					scanf("%d",&val);
					if( NextElem(list[lp],val,next)==ERROR )
						printf("\n��ȡʧ�ܣ�������Ҫ��ѯ��Ԫ���Ƿ��ڱ��л�Ϊ��β��");
					else
						printf("\n��Ҫ�ҵ�%d�ĺ��Ԫ��Ϊ��%d",val,next);
				}
				break;
			case 10:
				//����Ԫ��
				if( !list[lp] )
					printf("���Ա����ڣ��޷����룡");
				else{
					int num;		//����Ԫ�ظ��� 
					printf("��ǰ���ڽ��в���Ԫ�ز�����������Ҫ����Ԫ�صĸ�����");
					scanf("%d",&num);
					while( num ){
						printf("\n��ǰ���ڽ��в���Ԫ�ز�������������Ҫ����Ԫ�ص��߼������Ԫ��ֵ\n");
						printf("�߼�����");
						scanf("%d",&pos);
						printf("Ԫ��ֵ��");
						scanf("%d",&ins); 
						if( ListInsert(list[lp],pos,ins)==ERROR )
							printf("\n����ʧ�ܣ������±�ֵ�Ƿ�Ϸ�\n");
						else
							printf("\n����ɹ���\n");
						num--;
					}
				}
				break;
			case 11:
				//ɾ��Ԫ��
				if( !list[lp] )
					printf("���Ա����ڣ��޷�ɾ����");
				else{
					printf("��ǰ���ڽ���ɾ��Ԫ�ز�������������Ҫɾ��Ԫ�ص��߼�����");
					scanf("%d",&pos);
					if( ListDelete(list[lp],pos,val)==ERROR )
						printf("\nɾ��ʧ�ܣ������±�ֵ�Ƿ�Ϸ�!");
					else
						printf("\nɾ���ɹ�����ɾ����Ԫ��ֵΪ��%d",val);
				}
				break;
			case 12:
				//�������Ա�
				if( !list[lp] )
					printf("���Ա����ڣ��޷�������");
				else{
					printf("���Ա�%d��Ԫ�������ǣ�\n",lp);
					if( list[lp]->name )
						printf("%s ",list[lp]->name);
					ListTraverse(list[lp]);
				} 
				break;
			case 13:
				//���Ա�洢
				if( !list[lp] )
					printf("���Ա����ڣ��޷��洢��");
				else{
					printf("��ǰ���ڽ������Ա�洢��������������Ҫ���ɵ��ļ�����\n");
					scanf("%s",filename);
					SaveList(list[lp],filename);
					printf("\n�洢�ɹ���");
				}
				break;
			case 14:
				//���Ա��ȡ
				if( list[lp] )
					printf("���Ա��Ѵ��ڣ��޷���ȡ��");
				else{
					printf("��ǰ���ڽ������Ա��ȡ��������������Ҫ��ȡ���ļ���(������չ��)��\n");
					scanf("%s",filename);
					if( LoadList(list[lp],filename)==ERROR )
						printf("\n��ȡʧ�ܣ������ļ��Ƿ���ڣ�");
					else{
						printf("\n��ȡ�ɹ���");
						listlength++;
					}
				} 
				break;
			case 15:
				//��ת����
				if( !list[lp] )
					printf("���Ա����ڣ��޷���ת��");
				else{
					ReverseList(list[lp]);
					printf("��ת�ɹ���");
				}
				break; 
			case 16:
				//ɾ��������n��Ԫ��
				if( !list[lp] )
					printf("���Ա����ڣ��޷���ȡ��");
				else{
					printf("��ǰ���ڽ���ɾ��������n��Ԫ�صĲ�����������nֵ��");
					scanf("%d",&val);
					if( RemoveNthFromEnd(list[lp],val)==ERROR )
						printf("\nɾ��ʧ�ܣ������±��Ƿ�Ϸ���");
					else
						printf("\nɾ���ɹ���");
				} 
				break;
			case 17:
				//��������
				if( !list[lp] )
					printf("���Ա����ڣ��޷�����");
				else{
					SortList(list[lp]);
					printf("����ɹ���");
				} 
				break;
			case 18:
				//������Ա�
				if( listlength>=10 )
					printf("��ǰ���Ա���Ŀ�ѳ������ޣ�");
				else{
					printf("��ǰ���ڽ���������Ա�Ĳ�������������Ҫ�����±�ı��(1~10)��\n");
					scanf("%d",&pos);
					if( pos<1||pos>10 )
						printf("\n���ʧ�ܣ������±��Ƿ�Խ�磡");
					else if( list[pos] )
						printf("\n���Ա��Ѵ��ڣ��޷���ӣ�");
					else{
						InitList(list[pos]);
						listlength++;
						printf("\n��ӳɹ����ñ��ѳ�ʼ���������������ƣ�\n");
						scanf("%s",list[pos]->name);
					}
				}
				break;
			case 19:
				//�Ƴ����Ա�
				if( listlength==0 )
					printf("��ǰû�����Ա��޷��Ƴ���");
				else{
					printf("��ǰ���ڽ����Ƴ����Ա�Ĳ�������������Ҫ�Ƴ������Ա�ı��(1~10)��\n");
					scanf("%d",&pos);
					if( pos<1||pos>10 )
						printf("\n�Ƴ�ʧ�ܣ������±��Ƿ�Ϸ���");
					else if( !list[pos] )
						printf("\n���Ա����ڣ��޷��Ƴ���");
					else{
						DestroyList(list[pos]);
						printf("\n�Ƴ��ɹ���");
						if( pos==lp ){
							val=0;
							for( int i=1 ; i<=10 ; i++ )
								if( list[i]!=NULL ){
									val=i;
									break;
								}
							if( val!=0 ){
								printf("\n\n�������Ƴ��˵�ǰ���������Ա�%d���´β���Ĭ�϶��ѳ�ʼ�������Ա�%d����",lp,val);
								lp=val;
							}
							else
								printf("\n\nע�⣺���Ƴ��˵�ǰ���������Ա�%d���ҵ�ǰ�޿��õ����Ա�",lp);
						}
						listlength--;
					}
				} 
				break;
			case 20:
				//ѡ�����Ա�
				printf("��ǰ���ڽ���ѡ��������Ա�Ĳ�������������Ҫ���������Ա�ı�ţ�\n"); 
				scanf("%d",&pos);
				if( pos<1||pos>10 )
					printf("\nѡ��ʧ�ܣ������±��Ƿ�Ϸ���");
				else if( list[pos]==NULL )
					printf("\nѡ��ʧ�ܣ����Ա����ڣ�"); 
				else{
					lp=pos;
					printf("\nѡ��ɹ��������Ըñ���в�����");
				}
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
/********************************************************/


/********************************************************
��������  InitList
��ʼ���������Ա�L������ 
�������ܣ�������Ա�L�����ڣ���������ǹ���һ���յ����Ա�
����OK�����򷵻�INFEASIBLE�� 
�������ͣ�status 
********************************************************/
status InitList(LinkList &L)
{
    if( L )					//���Ա��Ѵ��� 
        return INFEASIBLE;	//������ 
    else{
        L=(LinkList)malloc(sizeof(LNode));
        L->next=NULL;
    }
    return OK;
}

/********************************************************
��������  DestroyList
��ʼ���������Ա�L�Ѵ��� 
�������ܣ�������Ա�L���ڣ��ò����ͷ����Ա�Ŀռ䣬ʹ����
���Ϊδ��ʼ��״̬������OK���������һ��δ��ʼ�����Ա�
�ǲ��ܽ������ٲ����ģ�����INFEASIBLE��
�������ͣ�status 
********************************************************/
status DestroyList(LinkList &L)
{
    if( !L )				//���Ա����� 
        return INFEASIBLE;	//������ 
    else{
        LinkList t=L;		//����ָ�� 
        while(t){
            LinkList a=t;	//�洢ָ�룬����ģ����λ 
            a=t->next;
            free(t);
            t=a;
        }
        L=NULL;
    }
    return OK;
}

/********************************************************
��������  ClearList
��ʼ���������Ա�L�Ѵ��� 
�������ܣ������Ա�L�����ڣ����L���ͷ���������Ԫ�صĽ�㣬
����OK�������Ա�L�����ڣ��򷵻�INFEASIBLE��
�������ͣ�status 
********************************************************/
status ClearList(LinkList &L)
{
    if( !L )				//���Ա����� 
        return INFEASIBLE;	//������ 
    else{
        LinkList t=L->next;	//����ָ�� 
        while(t){
            LinkList a=t->next;	//ģ����λָ�� 
            free(t);
            t=a;
        }
        L->next=NULL;
    }
    return OK;
}

/********************************************************
��������  ListEmpty
��ʼ���������Ա�L�Ѵ��� 
�������ܣ������Ա�L�����ڣ��򷵻�INFEASIBLE�������Ա�L��
��Ϊ0���򷵻�TRUE����Ϊ0�򷵻�FALSE��
�������ͣ�status 
********************************************************/
status ListEmpty(LinkList L)
{
    if( !L )				//���Ա����� 
        return INFEASIBLE;	//������ 
    else{
        if( L->next )		//��ͷ��һԪ�ش��ڡ������� 
            return FALSE;
        else				//���Ա�Ϊ�� 
            return TRUE;
    }
}

/********************************************************
��������  ListLength
��ʼ���������Ա�L�Ѵ��� 
�������ܣ������Ա�L�����ڣ��򷵻�INFEASIBLE�����򷵻�����
��L�ĳ��ȡ�
�������ͣ�int
********************************************************/
int ListLength(LinkList L)
{
    if( !L )				//���Ա����� 
        return INFEASIBLE;	//������ 
    else{
        LinkList t=L->next;	//����ָ�� 
        int cnt;
        while(t){
            cnt++;
            t=t->next;
        }
        return cnt;
    }
}

/********************************************************
��������  GetElem
��ʼ���������Ա�L�Ѵ��� 
�������ܣ������Ա�L�����ڣ�����INFEASIBLE����i<1����i����
���Ա�L�ĳ��ȣ��򷵻�ERROR������ȡ�ɹ�����ֵ����e������
��OK��
�������ͣ�status
********************************************************/
status GetElem(LinkList L,int i,ElemType &e)
{
    if( !L )				//���Ա����� 
        return INFEASIBLE;	//������ 
    if( i<1 )				//�±�������� 
        return ERROR;
    LinkList t=L;			//����ָ�� 
    for( int j=0 ; j<i ; j++ ){
        t=t->next;
        if( !t )			//�±�������� 
            return ERROR;
    }
    e=t->data;
    return OK;
}

/********************************************************
��������  LocateElem
��ʼ���������Ա�L�Ѵ��� 
�������ܣ������Ա�L�����ڣ�����INFEASIBLE����û���ҵ�ָ��
��Ԫ��e�������ʧ�ܣ�����ERROR�������ҳɹ����򷵻�Ԫ����
�����i��
�������ͣ�status
********************************************************/
status LocateElem(LinkList L,ElemType e)
{
    if( !L )				//���Ա����� 
        return INFEASIBLE;	//������ 
    LinkList t=L->next;		//����ָ�� 
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
��������  PriorElem
��ʼ���������Ա�L�Ѵ��� 
�������ܣ������Ա�L�����ڣ�����INFEASIBLE����û���ҵ�ָ��
Ԫ��e��ǰ���������ʧ�ܣ�����ERROR�������ҳɹ�����ֵ��
��pre��������OK��
�������ͣ�status
********************************************************/
status PriorElem(LinkList L,ElemType e,ElemType &pre)
{
    if( !L )				//���Ա����� 
        return INFEASIBLE;	//������ 
    LinkList t=L->next;		//����ָ�� 
    if( t->data==e )
    	return ERROR;
    while(t){
        if( t->next&&t->next->data==e ){	//��һ��Ԫ����ǰ�� 
            pre=t->data;
            return OK;
        }
        t=t->next;
    }
    return ERROR;
}

/********************************************************
��������  NextElem
��ʼ���������Ա�L�Ѵ��� 
�������ܣ������Ա�L�����ڣ�����INFEASIBLE����û���ҵ�ָ��
Ԫ��e�ĺ�̣������ʧ�ܣ�����ERROR�������ҳɹ�����ֵ��
��next��������OK��
�������ͣ�status
********************************************************/
status NextElem(LinkList L,ElemType e,ElemType &next)
{
    if( !L )				//���Ա����� 
        return INFEASIBLE;	//������ 
    LinkList t=L->next;		//����ָ�� 
    while(t->next){			//���һ��Ԫ���޺�� 
        if( t->data==e ){
            next=t->next->data;
            return OK;
        }
        t=t->next;
    }
    return ERROR;
}

/********************************************************
��������  ListInsert
��ʼ���������Ա�L�Ѵ��� 
�������ܣ�������Ա�L�����ڣ�����INFEASIBLE�����������Ա�
L�ĵ�i��Ԫ��ǰ�����µ�Ԫ��e������ɹ�����OK��ʧ�ܷ���ERROR��
�������ͣ�status
********************************************************/
status ListInsert(LinkList &L,int i,ElemType e)
{
    if( !L )				//���Ա����� 
        return INFEASIBLE;	//������ 
    LinkList t=L;			//����ָ�� 
    if( i<1 )				//�±�������� 
        return ERROR;
    for( int j=1 ; j<i ; j++ ){
        if( !t )			//�±�������� 
            return ERROR;
        t=t->next;
    }
    if( !t )				//�����ж�i==length+2����� 
        return ERROR;
    if( !(t->next) ){		//�����ж��ڽ�β����Ԫ�� 
        LinkList insert;
        insert=(LinkList)malloc(sizeof(LNode));
        insert->data=e;
        t->next=insert;
        insert->next=NULL;
        return OK;
    }
    LinkList a=t->next,insert;	//��ͨ���� 
    insert=(LinkList)malloc(sizeof(LNode));
    insert->data=e;
    t->next=insert;insert->next=a;
    return OK;
}

/********************************************************
��������  ListDelete
��ʼ���������Ա�L�Ѵ��� 
�������ܣ������Ա�L�����ڣ�����INFEASIBLE������ɾ�����Ա�
L�ĵ�i��Ԫ�أ���ɾ���ɹ���ɾ����ֵ����e������OK����ɾ��
ʧ���򷵻�ERROR��
�������ͣ�status
********************************************************/
status ListDelete(LinkList &L,int i,ElemType &e)
{
    if( !L )				//���Ա����� 
        return INFEASIBLE;	//������ 
    LinkList t=L;			//����ָ�� 
    if( i<1 )				//�±�������� 
        return ERROR;
    for( int j=1 ; j<i ; j++ ){
        if(!t)				//�±�������� 
            return ERROR;
        t=t->next;
    }
    if( !(t->next) )		//�����ж�i==length+1 
        return ERROR;
    LinkList a=t->next->next;	//�洢ɾ�������һ�ڵ� 
    e=t->next->data;
    free(t->next);
    t->next=a;
    return OK;
}

/********************************************************
��������  ListTraverse
��ʼ���������Ա�L�Ѵ��� 
�������ܣ������Ա�L�����ڣ�����INFEASIBLE������������Ա�
��ÿһ��Ԫ�أ�������OK��
�������ͣ�status
********************************************************/
status ListTraverse(LinkList L)
{
    if( !L )				//���Ա����� 
        return INFEASIBLE;	//������ 
    LinkList t=L->next;
    while(t){
        printf("%d",t->data);
        if( t->next )
            printf(" ");	//���� 
        t=t->next;
    }
    return OK;
}

/********************************************************
��������  SaveList
��ʼ���������Ա�L�Ѵ��� 
�������ܣ�������Ա�L�����ڣ�����INFEASIBLE���������Ա�
L��ȫ��Ԫ��д�뵽�ļ���ΪFileName���ļ��У�����OK
�������ͣ�status
********************************************************/
status SaveList(LinkList L,char FileName[])
{
    if( !L )				//���Ա����� 
        return INFEASIBLE;	//������ 
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
��������  LoadList
��ʼ���������Ա�L������ 
�������ܣ�������Ա�L���ڣ���ʾL���Ѿ������ݣ��������ݻ�
����ԭ����������ݶ�ʧ������INFEASIBLE�������ļ���Ϊ
FileName�����ݶ��뵽���Ա�L�У�����OK��
�������ͣ�status
********************************************************/
status LoadList(LinkList &L,char FileName[])
{
    if( L )					//���Ա���� 
        return INFEASIBLE;	//������ 
    L=(LinkList)malloc(sizeof(LNode));	//ͷ�ڵ㿪�ռ� 
    LinkList t=L;
    //ע���������䲻�ɵ���˳�� 
    int val;				//val�ݴ��ļ�����ֵ 
    FILE *fp=fopen(FileName,"r");
    while(fscanf(fp,"%d",&val)!=EOF){
        LinkList a=(LinkList)malloc(sizeof(LNode));
        a->data=val;
        t->next=a;
        t=a;
    }
    t->next=NULL;			//β������ÿ� 
    fclose(fp);
    return OK;
}

/********************************************************
��������  ReverseList
��ʼ���������Ա�L�Ѵ��� 
�������ܣ�������Ա�L�����ڣ�����INFEASIBLE���������Ա�
L��ȫ��Ԫ�ط�ת 
�������ͣ�status
********************************************************/
status ReverseList(LinkList &L){
	if( !L )				//���Ա����� 
		return INFEASIBLE;	//������
	LinkList t=L->next;
	int num[100],cnt=0;		//����������ʱ�洢 
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
��������  RemoveNthFromEnd
��ʼ���������Ա�L�Ѵ��� 
�������ܣ�������Ա�L�����ڣ�����INFEASIBLE������ɾ������
���е�����n���ڵ�
�������ͣ�status
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
��������  SortList
��ʼ���������Ա�L�Ѵ��� 
�������ܣ�������Ա�L�����ڣ�����INFEASIBLE���������Ա�
L��С��������
�������ͣ�status
********************************************************/
status SortList(LinkList &L){
	if( !L )				//���Ա����� 
		return INFEASIBLE;	//������
	LinkList t=L->next;
	int len=0;
	while(t){
		len++;
		t=t->next;
	}
	for( int i=0 ; i<len ; i++ ){	//BubbleSortԭ��
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
