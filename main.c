//
//  main.c
//  infestPath
//
//  Created by Juyeop Kim on 2022/10/20.
//

#include <stdio.h>
#include <string.h>
#include "ifct_element.h"
#include "ifct_database.h"

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
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    
    
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
    //ifsele_genElement( , , , ); 
   #if0 
   //fgets(그 문자를 넣을 변수;읽어올 문자 수 기준(공백),파일포인터)하면 
   //공백기준으로 문자열 읽어와서 변수에다가 해당 문자열 넣어줌 
    while (3 ==fscanf(fp,"%s %s %s",%index,&age,&ifct_point))
    {
    	for(i=0;i<5;i++)
    	  ifctdb_getData(i);
    	  fscanf(fp,"%s",&ifs_ele.place[i]);

       ifctele = ifctele_genElement(index, age, ifct_point, place_history);
       
       ictele_printElement(ifct_element);

	}
	#endif
    //1-3. FILE pointer close
    fclose(fp);
    
    /*장소마다 지정된 숫자에서 장소가 어디인지 화면에 출력하는... 
    {
    	int place1.place2;
    	place1= 11;
    	place2=19
    	printf("The first place is %i\n",ifctele_getPlaceName_(place1));
    	printf("The second place is %i\n",ifctele_getPlaceName_(place2));

	}
	*/
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
                scanf("%i",&pIndex);
                
                int ptn_index* = ifctdb_getData(pIndex);
                
				ifctele_printElement(ptn_index*);
				//printf("age: %i\n",ifctele_getAge(ptn_index*));

				
                break;//나이를 뺴올 때는 ifctele_getAge()쓰기 
                
            case MENU_PLACE:
            {
			    char place;
            	
                printf("Place Name : \n");
                scanf("%i",&place);
                
                int patients_cnt;
                int i,j;
                
                for(i=0;i<40;i++)//0번~39번까지의 도시 훑기 
                {
                	if(place==ifctele_getPlaceName_(i))//입력한 감염 장소에서  
                	{
                		for(j=0;j<5;j++)
                		{
                			if( i==ifs_ele.place[4])//??????
                			{
                		    patienst_cnt++;
                		    }
                     	}  
					}
				}
				
                printf("There are %i patients detected in %c .\n",patients_cnt,place)
                break;
            }
                
            case MENU_AGE:
            {	int min_age;
            	int max_age;
            	int patient_cnt;
            	
            	printf("minimal age : \n");
            	scanf("%i",&min_age);
                printf("maximal age : \n");
            	scanf("%i",&max_age);
            	
            	for(i=0;i<4;i++)
                {	if (min_age <= ifctele_getAge(ifctdb_getData(i)) <= max_age)
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
                scanf("%i",&pIndex);
                
                printf("-->[TRACKING] patient %i is infected by %i (time : %i, place : ??)",pIndex)
                printf("-->[TRACKING] patient %i is infected by %i (time : %i, place : ??)",pIndex)
                printf("The first infector of %i is %i",pIndex)

				break;
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
            }
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}
