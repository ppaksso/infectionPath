//
//  main.c
//  infestPath
//
//  Created by Juyeop Kim on 2022/10/20.
//

#include <stdio.h>
#include <string.h>
#include "C:\Users\82103\Desktop\전프밍\기말 프로젝트\basecode\infectionPath\ifct_element.h"
#include "C:\Users\82103\Desktop\전프밍\기말 프로젝트\basecode\infectionPath\ifct_database.h"

#define MENU_PATIENT        1
#define MENU_PLACE          2
#define MENU_AGE            3
#define MENU_TRACK          4
#define MENU_EXIT           0

#define TIME_HIDE           2


int trackInfester(int patient_no, int *detected_time, int *place);
int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element;
    FILE* fp;
    FILE* pile;//환자 정보 담긴 텍스트파일  
    int pIndex, age, time;//환자 번호, 나이, 감염 시점 
    int placeHist[N_HISTORY];//이동 장소  


    
    
    //------------- 1. loading patient info file ------------------------------
    //1-1. FILE pointer open
    if (argc != 2)
    {
        printf("[ERROR] syntax : infestPath (file path).");
        return -1;
    }
    
    fp = (argv[1],"r");
    if (fp == NULL)
    {
        printf("[ERROR] Failed to open database file!! (%s)\n", argv[1]);
        return -1;
    }//이렇게 해놔야 디버깅 할 떄나 프로그램을 실행할 떄나 더 편함 
    
    //1-2. loading each patient informations
   #if0  
   
   pile = fopen("patientInfo_sample.txt","r");
 
    while (3 ==fscanf(pile,"%i %i %i",&pIndex,&age,&time))//텍스트파일에서 앞에 3개(번호, 나이, 감염일자) 읽어 왔을 때 
    {
    	int i;
    	for(i=0;i<5;i++)
    	  fscanf(pile,"%i",&placeHist[i]);//앞의 3개 읽은 후 그 뒤부터 읽어옴=>방문 장소 5개를 차례대로 placeHist 배열에 저장  

       unsigned *ifct_ele = ifctele_genElement(pIndex, age, time, placeHist);//텍스트 파일에 있는 환자 정보를 읽어와서  구조체 안에 넣기  
       
       ifctdb_addTail(ifct_ele);
	}
	#endif
    //1-3. FILE pointer close
    fclose(fp);

    do {
        printf("\n=============== INFECTION PATH MANAGEMENT PROGRAM (No. of patients : %i) =============\n", ifctdb_len());
        printf("1. Print details about a patient.\n");                      //MENU_PATIENT
        printf("2. Print list of patients infected at a place.\n");        //MENU_PLACE
        printf("3. Print list of patients in a range of age.\n");          //MENU_AGE
        printf("4. Track the root of the infection\n");                     //MENU_TRACK
        printf("0. Exit.\n");                                               //MENU_EXIT
        printf("=============== ------------------------------------------------------- =============\n\n");
        
        printf("Select a menu :");
        scanf("%d", &menu_selection);
        fflush(stdin);
        
        switch(menu_selection)
        {
            case MENU_EXIT:
                printf("Exiting the program... Bye bye.\n");
                break;
                
            case MENU_PATIENT:
                
                printf("Patient index: \n");
                scanf("%i",&pIndex);//환자 번호 입력받기  
                
                int *ptn_index = ifctdb_getData(pIndex);
                
				ifctele_printElement(*ptn_index);
				// 환자 index,나이,감염날짜,방문 장소 출력  

				
                break;
                
            case MENU_PLACE:
            {
			    char place;
            	
                printf("Place Name : \n");
                scanf("%i",&place);//장소 이름 입력받기  
                
                int patients_cnt;
                int i,j;
                
                for(i=0;i<40;i++)//0번~39번까지의 도시 훑기 
                {
                	if(place==ifctele_getPlaceName_(i))//입력한 감염 장소에서  
                	{
                		for(j=0;j<5;j++)
                		{
                			if( i== placeHist[4])//입력한 장소의 number와 0~4번 환자의 감염 장소가 같은 경우  
                			{
                		    patients_cnt++;//해당 장소에서 감염된 환자의 수(=patients_cnt)에 1을 더해줌  
                		    }
                     	}  
					}
				}
				
                printf("There are %i patients detected in %c .\n",patients_cnt,place);
                break;
            }
                
            case MENU_AGE:
            {	int min_age;//최소 나이 
            	int max_age;//최대 나이 
            	int patient_cnt;//나이가 최소 나이 이상, 최대 이하인 환자의 수  
            	int i;
            	
            	printf("minimal age : \n");
            	scanf("%i",&min_age);//최소 나이 입력받기  
                printf("maximal age : \n");
            	scanf("%i",&max_age);//최대 나이 입력받기  
            	
            	for(i=0;i<4;i++)
                {	if (min_age <= ifctele_getAge(ifctdb_getData(i)) <= max_age)//getAge함수 사용하여 0~4번째 환자의 나이가 최소 이상&최대 이상인 경우  
                	{
                	    patient_cnt++;
					}
			    }
				printf("There are %i patients whose age is between %i and %i .\n",patient_cnt,min_age,max_age);
                break;
				}
                
            case MENU_TRACK:
            {
                printf("Patient index: \n");
                scanf("%i",&pIndex);//환자 번호 입력받기  
                
                while(1)
                {
                printf("-->[TRACKING] patient %i is infected by %i (time : %i, place : %c )",pIndex,,)//환자 감염 경로 추적  
               
			     if()//입력한 번호의 환자와 최초감염자가 다를 때  
			    {
			    printf("The first infector of %i is %i",pIndex);//추적이  끝나면 최초 감염자 누군지 출력  
			    break;
			    
			    }
			     else// 입력한 번호에 해당하는 환자가 최초 감염자인 경우  
			    {
			   	printf("%i is the first infector!!",pIndex);
			   	break;
			    }
			   
			   }

				break;
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
            }
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}
