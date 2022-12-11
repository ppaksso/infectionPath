//
//  ifct_database.h
//  infection Path
//
//  Created by Juyeop Kim on 2022/10/20.
//

#ifndef ifct_database_h
#define ifct_database_h


int ifctdb_addTail(void* obj);          //add data to tail 새로운 데이터를 추가하는 거 (Linked List)보이트포인터 변수로 받음
int ifctdb_deleteData(int index);       //delete data  지우는 거  
int ifctdb_len(void);                   //get database length 몇개의 데이터가 liked list 에 들어있냐를 일려줌 =>출력으로 데이터 개수가 나옴 
void* ifctdb_getData(int index);        //get index'th data 몇 번쨰인지 인덱스 집어 넣으면 그 몇번째 노드에 들어있는  데이터의 보이드 포인터를 리턴해줌 


#endif /* ifct_database_h */
