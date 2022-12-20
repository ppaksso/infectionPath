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

char ifctele_getPlaceName_(int placeIndex)//반환형을 포인터로 해야하는건지 그냥 char로 받는 건지 모르겠음 
{
	
	return countryName[placeIndex];//번호를 입력받아 그 번호에 대응하는 장소 이름 출력  
}

typedef struct ifs_ele{
	//typedef를 쓰는 이유는 뒤에서 struct ifs_ele_t ifs1이 아니라  그냥 ifs_ele_t ifs로 선언을 할 수 있어서 더 간단함 
	int index;//번호:정수 
	int age;//나이:정수 
	int ifct_point;//감염 시점:정수 
    place_t place[N_HISTORY];
	
	
	 //감염 직전 이동경로 : enum활용하여 place_t로, 정수 배열 크기는 N_HISTORY 저장! ifct_elemen.h에 매크로로 저장되어있음 (문자열이 아닌 정수로 저장했으니까) 
} ifs_ele_t;
 

void* ifctele_genElement(int index, int age, unsigned int ifct_point, int history_place[N_HISTORY]){
	//정보를 구조체 안에다가 넣는 함수 
	
	ifs_ele_t *ptr;


	
	ptr=(struct ifs_ele_t*)malloc(5*sizeof(ifs_ele_t));
	ptr->index = index;
	ptr->age = age;
	ptr->ifct_point = ifct_point;
	
	int i;
	 
    for(i=0;i<5;i++){
	ptr->place[i] = history_place[i];
    }
	//환자의 정보를 나타내면 됨(번호,나이,감염시점,감염 직전 이동경로)
	//여기서 malloc했다고 해서 free를 해버리면 정보로 이루어진 구조체를 넘겨주기 전에 다 버려버리는거임=>free 하면 안돼 
	return (ptr); 
}



int ifctele_getAge(void* obj){
	
	ifs_ele_t *strPtr = (ifs_ele_t *)obj;
	
	return strPtr->age; 
} 
 
 int ifctele_getHistPlaceindex(void* obj, int index);
 unsigned int ictele_getinfectedTime(void* obj);
 
 
void ifctele_printElement(void *obj){
//배열로 하지 않으면 이게 더 유용할 것 
	
	ifs_ele_t *strPtr = (ifs_ele_t *)obj;
	
	int i;
	 
	printf("index : %i\n",strPtr->index);
	printf("Age : %i\n",strPtr->age);
	printf("Detected time : %i\n",strPtr->ifct_point);
	printf("Path History: ");
	for (i=0;i<4;i++)//마지막 장소, 즉 감염 장소를 제외한 4개의 방문장소 출력  
	{
	    printf(" %c(%i) -> ",ifctele_getPlaceName_(strPtr->place[i]),strPtr->place[i]);
	}
	printf(" %c(%i)\n ",ifctele_getPlaceName_(strPtr->place[4]),strPtr->place[4]);//마지막 장소(=감염장소) 출력

}



