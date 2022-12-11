//
//  ifct_database.c
//  Infection Path
//  Database platform code for storing infest path elements
//  Created by Juyeop Kim on 2022/10/20.
//

#include <stdio.h>
#include <stdlib.h>

#include "ifct_database.h"

#define LIST_END -1

//node definition for linked list
typedef struct node{
    int index;      //index of the node ���° ����  
    void* obj;      //object data obj=������Ʈ �������� �޸��ּҸ� �����ͺ����� ���� �ִ� ��  
    void* next;         //pointer to the next �ؽ�Ʈ ������  
    void* prev;         //pointer to the next ���� ��忡 ���� ������  
} node_t;
//��忡 ���� ����  

static node_t* list_database = NULL;
//��������͸� ���� �� static���� �ؼ� �ٱ����� ���� ���ϰ�... ����ü�� ������ ���·� ������ ������ �޸𸮸� ��� �ִ� �� �ƴ� 
static node_t* listPtr = NULL;
static int list_cnt = 0;


//Inner functions (cannot used at the outside of this file)
static node_t* genNode(void)//��带 �����ϴ� �Լ� =>��� ���� �� �����͸� ����� 
{
    //allocate memory for creating the node
    node_t* ndPtr = (node_t*)malloc(sizeof(node_t));
	//���� �޸� �Ҵ�! �������� �޸� �Ҵ��� �ƴ϶�  malloc�� ������ �Լ��� ������� �� stiac�޸� ������ ����ü�� ������ �Լ���  ������ �� �޸𸮰� �� ������
	//�׷��� �� �Լ��� ������ �� �޸� �Ҵ��� �������  
    if (ndPtr != NULL)
    {
        ndPtr->next = NULL;//�� �����͸� �ʱ�ȭ ������ �� =�� �����ʹ� ���� �� �������~ 
        ndPtr->obj = NULL;
        ndPtr->prev = NULL; 
    }//���� ���� �� ����ִ� ��  
    
    return ndPtr;//������ ����  
}

static node_t* ifctList(int index)
{
    node_t* ndPtr = list_database;..//��� �����͸� �ϳ� ���� ��� �����Ͷ� �Ȱ��� ����Ű��  ��  
    if (listPtr != NULL && listPtr->index <= index)
    {
        ndPtr = listPtr;
    }
    
    //return for wrong input
    if (index <-1)
    {
        printf("[ERROR] ifctList() : either list is null or index is wrong! (offset : %i)\n", index);
        return NULL;
    }
    if (index >= list_cnt)
    {
        printf("[ERROR] ifctList() : index is larger than length (len:%i, index:%i)\n", list_cnt, index);
        return NULL;
    }
    
    //repeat travelling until the node is the end or offset becomes 0
    while (ndPtr != NULL)
    {
        if (ndPtr->index == index)//����� ��ȣ�� ���� ã���� �ϴ� ���� ������ break���ؼ� �ݺ��� ������ �״�� ������ ����  
            break;
        ndPtr = ndPtr->next;//�ݺ��� ���� ��� �����ʹ� ����������� �ؽ�Ʈ�� ����Ű��...�� ��� �����Ͱ� NULL�� ����ų�� ����(=������ ���� ����) 
    }
    
    return ndPtr;
}

static int updateIndex(void)
{
    int index=0;
    node_t* ndPtr = list_database;
    
    while ( ndPtr != NULL )//travel until it is the end node
    {
        ndPtr->index = index++;
        ndPtr = ndPtr->next; //travel once
    }
    
    return index;
}



//API function
/*
    description : adding a data object to the list end
    input parameters : obj - data object to add to the list
    return value : addition result (0 - succeeded, -1 - failed)
    
    operation : 1. make a new node
                2. find the last node in the list
                3. make the last node's next pointer to point the new node
                4. update the index
*/
int ifctdb_addTail(void* obj)//��� �߰��ϴ� �� & static�� �پ� �ִ� ������ �ٱ����� �����ؾ��ϹǷ� static�� �� ��  
{
    node_t* ndPtr;
    node_t* newNdPtr;
    
    //parameter checking
    if (obj == NULL)
    {
        printf("[ERROR] ifsdb_addTail() : Failed to do addTail : input object indicates NULL!\n");
        return -1;
    }
    
    //generate new node
    newNdPtr = genNode(); 
    if (newNdPtr == NULL)//error handling 
    {
        printf("[ERROR] ifsdb_addTail() : Failed to do addTail : Failed to create a node\n");
        return -1; //indicate to the upper function that node addition is failed
    }
    newNdPtr->obj = obj;//�Ű������� ����Ű�Բ� ������ ����  
    
    //add node to the list tail
    if (list_database == NULL)//��尡 �Ѱ��� ������  
    {
        list_database = newNdPtr;//��� �����Ͱ� ���� ���� ��带 ����Ű�Բ�  
        newNdPtr->index = 0;// ù ���ϱ� 0������ 
    }
    else//��ũ�� ����Ʈ�� ��尡 �Ѱ��� ���� ��  
    {
        ndPtr = ifctList(list_cnt-1);
		//��� �����Ͱ� �� �� ��带 ����Ű�Բ� �ϴ� �Լ�  ex)��ũ�� ����Ʈ�� 10�� ������ 9��°(0~9��°��  ����Ʈ ���� ) ��带 ����ִ� �Լ�  
        ndPtr->next = newNdPtr;//�� �� ����� �ؽ�Ʈ�� ���ο� ��带 ����Ű�Բ� 
        newNdPtr->prev = ndPtr;//�� ������ ������ ��带 ����Ű�� �� 
        newNdPtr->index = ndPtr->index+1;
    }
    
    listPtr = newNdPtr;
    
    list_cnt++;//����Ʈ�� ���� �߰� 
    
    return 0;
}


/*
    description : delete data object from the list
    input parameters : index - index'th data to delete
    return value : deletion result (0 - succeeded, -1 - failed)
*/
int ifctdb_deleteData(int index)
{
    node_t* ndPrevPtr;
    node_t* ndNextPtr;
    node_t* delNdPtr;
    
    //parameter checking
    if ( (delNdPtr = ifctList(index)) == NULL)//�ε��� ���ؼ� ������� �ش��ϴ� ������(����� ���� ��)�� �����ͼ� ����Ʈ �������� ����  
    {
        printf("[ERROR] ifctdb_deleteData() : Failed to do deleteData : input index is invalid (%i)!\n", index);
        return -1;
    }
    
    ndPrevPtr = delNdPtr->prev;//������� ����Ʈ�� previous��� ����Ű�� �����͸� ���� 
    if (ndPrevPtr != NULL)
    {
        ndPrevPtr->next = delNdPtr->next;//������� ��� ������ �ؽ�Ʈ�����͸� delete�� �ؽ�Ʈ�� 
    }
    ndNextPtr = delNdPtr->next;
    if (ndNextPtr != NULL)
    {
        ndNextPtr->prev = delNdPtr->prev;
    }
    
    free(delNdPtr->obj);//�̰� ���ؼ� obj �޸𸮸� ����  
    free(delNdPtr);//�̰͵� ����  
    
    list_cnt--;//����Ʈ ���� �ϳ� ���̰� 
    
    if (list_cnt == 0)
    {
        list_database = NULL;
    }
    else
    {
        updateIndex();//�߰��� �ִ� ��带 �������� ���� ��� ���� ������  �ε����� ���� 
    }
    
    return 0;
}


//functions for list observation -----------------------------

/*
    description : return the number of data objects in the list
    return value : length
*/
int ifctdb_len(void)
{
    return list_cnt;//��� ���� ����ؼ� ���� 
}


/*
    description : get the object data
    input parameters : index
    return value : object pointer
*/
void* ifctdb_getData(int index)
{
    void* obj = NULL;
    node_t* ndPtr;
    
    //parameter checking
    if ((ndPtr = ifctList(index)) != NULL)//iftlist�Լ� ���� ���° ��带 ������  �׸��� �װ� NULL�� �ƴҶ�  
    {
        obj = (void*)ndPtr->obj; 
        listPtr = ndPtr;
    }
    
    if (obj == NULL)
        printf("[ERROR] ifctdb_len() : there is no data of index %i\n", index);
    
    return obj;//������ ����� �޸�  �ּҸ� �����Ѵ� 
}
