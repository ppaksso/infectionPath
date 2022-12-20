//
//  main.c
//  infestPath
//
//  Created by Juyeop Kim on 2022/10/20.
//

#include <stdio.h>
#include <string.h>
#include "C:\Users\82103\Desktop\������\�⸻ ������Ʈ\basecode\infectionPath\ifct_element.h"
#include "C:\Users\82103\Desktop\������\�⸻ ������Ʈ\basecode\infectionPath\ifct_database.h"

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
    FILE* pile;//ȯ�� ���� ��� �ؽ�Ʈ����  
    int pIndex, age, time;//ȯ�� ��ȣ, ����, ���� ���� 
    int placeHist[N_HISTORY];//�̵� ���  


    
    
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
    }//�̷��� �س��� ����� �� ���� ���α׷��� ������ ���� �� ���� 
    
    //1-2. loading each patient informations
   #if0  
   
   pile = fopen("patientInfo_sample.txt","r");
 
    while (3 ==fscanf(pile,"%i %i %i",&pIndex,&age,&time))//�ؽ�Ʈ���Ͽ��� �տ� 3��(��ȣ, ����, ��������) �о� ���� �� 
    {
    	int i;
    	for(i=0;i<5;i++)
    	  fscanf(pile,"%i",&placeHist[i]);//���� 3�� ���� �� �� �ں��� �о��=>�湮 ��� 5���� ���ʴ�� placeHist �迭�� ����  

       unsigned *ifct_ele = ifctele_genElement(pIndex, age, time, placeHist);//�ؽ�Ʈ ���Ͽ� �ִ� ȯ�� ������ �о�ͼ�  ����ü �ȿ� �ֱ�  
       
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
                scanf("%i",&pIndex);//ȯ�� ��ȣ �Է¹ޱ�  
                
                int *ptn_index = ifctdb_getData(pIndex);
                
				ifctele_printElement(*ptn_index);
				// ȯ�� index,����,������¥,�湮 ��� ���  

				
                break;
                
            case MENU_PLACE:
            {
			    char place;
            	
                printf("Place Name : \n");
                scanf("%i",&place);//��� �̸� �Է¹ޱ�  
                
                int patients_cnt;
                int i,j;
                
                for(i=0;i<40;i++)//0��~39�������� ���� �ȱ� 
                {
                	if(place==ifctele_getPlaceName_(i))//�Է��� ���� ��ҿ���  
                	{
                		for(j=0;j<5;j++)
                		{
                			if( i== placeHist[4])//�Է��� ����� number�� 0~4�� ȯ���� ���� ��Ұ� ���� ���  
                			{
                		    patients_cnt++;//�ش� ��ҿ��� ������ ȯ���� ��(=patients_cnt)�� 1�� ������  
                		    }
                     	}  
					}
				}
				
                printf("There are %i patients detected in %c .\n",patients_cnt,place);
                break;
            }
                
            case MENU_AGE:
            {	int min_age;//�ּ� ���� 
            	int max_age;//�ִ� ���� 
            	int patient_cnt;//���̰� �ּ� ���� �̻�, �ִ� ������ ȯ���� ��  
            	int i;
            	
            	printf("minimal age : \n");
            	scanf("%i",&min_age);//�ּ� ���� �Է¹ޱ�  
                printf("maximal age : \n");
            	scanf("%i",&max_age);//�ִ� ���� �Է¹ޱ�  
            	
            	for(i=0;i<4;i++)
                {	if (min_age <= ifctele_getAge(ifctdb_getData(i)) <= max_age)//getAge�Լ� ����Ͽ� 0~4��° ȯ���� ���̰� �ּ� �̻�&�ִ� �̻��� ���  
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
                scanf("%i",&pIndex);//ȯ�� ��ȣ �Է¹ޱ�  
                
                while(1)
                {
                printf("-->[TRACKING] patient %i is infected by %i (time : %i, place : %c )",pIndex,,)//ȯ�� ���� ��� ����  
               
			     if()//�Է��� ��ȣ�� ȯ�ڿ� ���ʰ����ڰ� �ٸ� ��  
			    {
			    printf("The first infector of %i is %i",pIndex);//������  ������ ���� ������ ������ ���  
			    break;
			    
			    }
			     else// �Է��� ��ȣ�� �ش��ϴ� ȯ�ڰ� ���� �������� ���  
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
