//
//  ifct_database.h
//  infection Path
//
//  Created by Juyeop Kim on 2022/10/20.
//

#ifndef ifct_database_h
#define ifct_database_h


int ifctdb_addTail(void* obj);          //add data to tail ���ο� �����͸� �߰��ϴ� �� (Linked List) void������ ������ ����
int ifctdb_deleteData(int index);       //delete data  ����� ��  
int ifctdb_len(void);                   //get database length ��� �����Ͱ� liked list �� ����ֳĸ� �Ϸ��� =>������� ������ ������ ���� 
void* ifctdb_getData(int index);        //get index'th data �� �������� index ���� ������ �� ���° node�� ����ִ�  �������� void �����͸� �������� 


#endif /* ifct_database_h */
