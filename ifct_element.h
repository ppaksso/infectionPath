//
//  ifct_element.h
//  infection path
//
//  Created by Juyeop Kim on 2022/10/20.
//

#ifndef ifct_element_h
#define ifct_element_h

#define N_PLACE                     40
#define N_HISTORY                   5
#define MAX_PLACENAME               100

void* ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY]);
char* ifctele_getPlaceName(int placeIndex);
int ifctele_getHistPlaceIndex(void* obj, int index);//요것도 getAge랑 비슷하게 
unsigned int ifctele_getinfestedTime(void* obj);//요것도 getAge랑 비슷하게  
int ifctele_getAge(void* obj);
/*다른 소스코드에 제공하는 문과 같은 함수, element.c에서 선언한 구조체 안에서 나이를 뺴오는 함수
void 포인터로 받는 이유는 얘는 받는 구조체의 자료형을 보르기 떄문 */
void ifctele_printElement(void* obj);
#endif /* ifct_element_h */
