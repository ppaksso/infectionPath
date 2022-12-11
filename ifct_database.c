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
    int index;      //index of the node 몇번째 노드냐  
    void* obj;      //object data obj=오브젝트 데이터의 메모리주소를 포인터변수로 갖고 있는 것  
    void* next;         //pointer to the next 넥스트 포인터  
    void* prev;         //pointer to the next 이전 노드에 대한 포인터  
} node_t;
//노드에 대한 정의  

static node_t* list_database = NULL;
//헤더포인터를 만든 거 static으로 해서 바깥에서 접근 못하게... 구조체의 포인터 형태로 선언함 실제로 메모리를 잡고 있는 건 아님 
static node_t* listPtr = NULL;
static int list_cnt = 0;


//Inner functions (cannot used at the outside of this file)
static node_t* genNode(void)//노드를 생성하는 함수 =>노드 만들어서 그 포인터를 뱉어줌 
{
    //allocate memory for creating the node
    node_t* ndPtr = (node_t*)malloc(sizeof(node_t));
	//동적 메모리 할당! 굳이정적 메모리 할당이 아니라  malloc쓴 이유는 함수가 실행됐을 떄 stiac메모리 영역에 구조체가 잡히고 함수가  끝났을 떄 메모리가 다 없어짐
	//그래서 이 함수가 끝나고 이 메모리 할당은 살아있음  
    if (ndPtr != NULL)
    {
        ndPtr->next = NULL;//걍 포인터를 초기화 시켜준 거 =이 포인터는 아직 빈 껍데기다~ 
        ndPtr->obj = NULL;
        ndPtr->prev = NULL; 
    }//에러 났을 떄 잡아주는 거  
    
    return ndPtr;//포인터 리턴  
}

static node_t* ifctList(int index)
{
    node_t* ndPtr = list_database;..//노드 포인터를 하나 만들어서 헤더 포인터랑 똑같이 가리키게  함  
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
        if (ndPtr->index == index)//노드의 번호가 내가 찾고자 하는 노드와 같으면 break통해서 반복문 나가고 그대로 포인터 리턴  
            break;
        ndPtr = ndPtr->next;//반복을 통해 노드 포인터는 노드포인터의 넥스트를 가리키게...이 노드 포인터가 NULL을 가리킬떄 까지(=끝까지 갈때 까지) 
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
int ifctdb_addTail(void* obj)//노드 추가하는 거 & static안 붙어 있는 이유는 바깥으로 제공해야하므로 static을 뺀 거  
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
    newNdPtr->obj = obj;//매개변수를 가리키게끔 포인터 세팅  
    
    //add node to the list tail
    if (list_database == NULL)//노드가 한개도 없으면  
    {
        list_database = newNdPtr;//헤더 포인터가 새로 만든 노드를 가리키게끔  
        newNdPtr->index = 0;// 첫 노드니까 0번쨰임 
    }
    else//링크드 리스트에 노드가 한개라도 있을 떄  
    {
        ndPtr = ifctList(list_cnt-1);
		//노드 포인터가 맨 끝 노드를 가리키게끔 하는 함수  ex)링크드 리스트에 10개 있으면 9번째(0~9번째의  리스트 존재 ) 노드를 뱉어주는 함수  
        ndPtr->next = newNdPtr;//맨 끝 노드의 넥스트가 새로운 노드를 가리키게끔 
        newNdPtr->prev = ndPtr;//이 기존의 마지막 노드를 가리키면 됨 
        newNdPtr->index = ndPtr->index+1;
    }
    
    listPtr = newNdPtr;
    
    list_cnt++;//리스트의 개수 추가 
    
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
    if ( (delNdPtr = ifctList(index)) == NULL)//인덱스 통해서 몇번쨰에 해당하는 포인터(지우고 싶은 거)를 가져와서 포인트 변수에다 저장  
    {
        printf("[ERROR] ifctdb_deleteData() : Failed to do deleteData : input index is invalid (%i)!\n", index);
        return -1;
    }
    
    ndPrevPtr = delNdPtr->prev;//지우려는 포인트의 previous노드 가리키는 포인터를 저장 
    if (ndPrevPtr != NULL)
    {
        ndPrevPtr->next = delNdPtr->next;//지우려는 노드 이전의 넥스트포인터를 delete의 넥스트로 
    }
    ndNextPtr = delNdPtr->next;
    if (ndNextPtr != NULL)
    {
        ndNextPtr->prev = delNdPtr->prev;
    }
    
    free(delNdPtr->obj);//이거 통해서 obj 메모리를 지움  
    free(delNdPtr);//이것도 지움  
    
    list_cnt--;//리스트 개수 하나 줄이고 
    
    if (list_cnt == 0)
    {
        list_database = NULL;
    }
    else
    {
        updateIndex();//중간에 있던 노드를 지웠으면 지운 노드 뒤의 노드들이  인덱스를 업뎃 
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
    return list_cnt;//노드 개수 계산해서 리턴 
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
    if ((ndPtr = ifctList(index)) != NULL)//iftlist함수 통해 몇번째 노드를 가져옴  그리고 그게 NULL이 아닐때  
    {
        obj = (void*)ndPtr->obj; 
        listPtr = ndPtr;
    }
    
    if (obj == NULL)
        printf("[ERROR] ifctdb_len() : there is no data of index %i\n", index);
    
    return obj;//지정한 노드의 메모리  주소를 리턴한다 
}
