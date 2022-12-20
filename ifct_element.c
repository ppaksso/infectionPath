//
//  ifs_element.c
//  InfestPath
//
//  Created by Juyeop Kim on 2020/10/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ifct_element.h"

typedef enum place {
    Seoul,          //0
    Jeju,           //1
    Tokyo,          //2
    LosAngeles,     //3
    NewYork,        //4
    Texas,          //5
    Toronto,        //6
    Paris,          //7
    Nice,           //8
    Rome,           //9
    Milan,          //10
    London,         //11
    Manchester,     //12
    Basel,          //13
    Luzern,         //14
    Munich,         //15
    Frankfurt,      //16
    Berlin,         //17
    Barcelona,      //18
    Madrid,         //19
    Amsterdam,      //20
    Stockholm,      //21
    Oslo,           //22
    Hanoi,          //23
    Bangkok,        //24
    KualaLumpur,    //25
    Singapore,      //26
    Sydney,         //27
    SaoPaulo,       //28
    Cairo,          //29
    Beijing,        //30
    Nairobi,        //31
    Cancun,         //32
    BuenosAires,    //33
    Reykjavik,      //34
    Glasgow,        //35
    Warsow,         //36
    Istanbul,       //37
    Dubai,          //38
    CapeTown        //39
} place_t;

char countryName[N_PLACE+1][MAX_PLACENAME] =
{   "Seoul",
    "Jeju",
    "Tokyo",
    "LosAngeles",
    "NewYork",
    "Texas",
    "Toronto",
    "Paris",
    "Nice",
    "Rome",
    "Milan",
    "London",
    "Manchester",
    "Basel",
    "Luzern",
    "Munich",
    "Frankfurt",
    "Berlin",
    "Barcelona",
    "Madrid",
    "Amsterdam",
    "Stockholm",
    "Oslo",
    "Hanoi",
    "Bangkok",
    "KualaLumpur",
    "Singapore",
    "Sydney",
    "SaoPaulo",
    "Cairo",
    "Beijing",
    "Nairobi",
    "Cancun",
    "BuenosAires",
    "Reykjavik",
    "Glasgow",
    "Warsow",
    "Istanbul",
    "Dubai",
    "CapeTown",
    "Unrecognized"
}; 

char ifctele_getPlaceName_(int placeIndex)//��ȯ���� �����ͷ� �ؾ��ϴ°��� �׳� char�� �޴� ���� �𸣰��� 
{
	
	return countryName[placeIndex];//��ȣ�� �Է¹޾� �� ��ȣ�� �����ϴ� ��� �̸� ���  
}

typedef struct ifs_ele{
	//typedef�� ���� ������ �ڿ��� struct ifs_ele_t ifs1�� �ƴ϶�  �׳� ifs_ele_t ifs�� ������ �� �� �־ �� ������ 
	int index;//��ȣ:���� 
	int age;//����:���� 
	int ifct_point;//���� ����:���� 
    place_t place[N_HISTORY];
	
	
	 //���� ���� �̵���� : enumȰ���Ͽ� place_t��, ���� �迭 ũ��� N_HISTORY ����! ifct_elemen.h�� ��ũ�η� ����Ǿ����� (���ڿ��� �ƴ� ������ ���������ϱ�) 
} ifs_ele_t;
 

void* ifctele_genElement(int index, int age, unsigned int ifct_point, int history_place[N_HISTORY]){
	//������ ����ü �ȿ��ٰ� �ִ� �Լ� 
	
	ifs_ele_t *ptr;


	
	ptr=(struct ifs_ele_t*)malloc(5*sizeof(ifs_ele_t));
	ptr->index = index;
	ptr->age = age;
	ptr->ifct_point = ifct_point;
	
	int i;
	 
    for(i=0;i<5;i++){
	ptr->place[i] = history_place[i];
    }
	//ȯ���� ������ ��Ÿ���� ��(��ȣ,����,��������,���� ���� �̵����)
	//���⼭ malloc�ߴٰ� �ؼ� free�� �ع����� ������ �̷���� ����ü�� �Ѱ��ֱ� ���� �� ���������°���=>free �ϸ� �ȵ� 
	return (ptr); 
}



int ifctele_getAge(void* obj){
	
	ifs_ele_t *strPtr = (ifs_ele_t *)obj;
	
	return strPtr->age; 
} 
 
 int ifctele_getHistPlaceindex(void* obj, int index);
 unsigned int ictele_getinfectedTime(void* obj);
 
 
void ifctele_printElement(void *obj){
//�迭�� ���� ������ �̰� �� ������ �� 
	
	ifs_ele_t *strPtr = (ifs_ele_t *)obj;
	
	int i;
	 
	printf("index : %i\n",strPtr->index);
	printf("Age : %i\n",strPtr->age);
	printf("Detected time : %i\n",strPtr->ifct_point);
	printf("Path History: ");
	for (i=0;i<4;i++)//������ ���, �� ���� ��Ҹ� ������ 4���� �湮��� ���  
	{
	    printf(" %c(%i) -> ",ifctele_getPlaceName_(strPtr->place[i]),strPtr->place[i]);
	}
	printf(" %c(%i)\n ",ifctele_getPlaceName_(strPtr->place[4]),strPtr->place[4]);//������ ���(=�������) ���

}



