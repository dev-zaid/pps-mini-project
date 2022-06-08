#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char AddStudent();
char CheckAttendance();

int main(){
  // AddStudent();
  CheckAttendance();
}

char CheckAttendance(){
  FILE *std; //Student Data
  FILE *atd; //Attendance Data

  int rno;
  printf("Enter Registration Number:");
  scanf("%d",&rno);

  std = fopen("./data/student-data.csv","r");
  atd = fopen("./data/attendance-data.csv","r");
  
  if(!std || !atd){
    printf("Can't access the file.");
  }
  else{
    char buffer[1024];
    long int attendance[7],classConducted[7];
    int row=0,column=0;
    while (fgets(buffer,1024,atd))
    {
      char* value = strtok(buffer,",");
      column=0;
      if(row!=0){
        long int temp = strtoul(value,NULL,10);

        if(temp==rno){
          while (value){ //Store value of the no of hours attended in an array
              if(column==1){
                attendance[0]=strtoul(value,NULL,10);
                }
              if(column==2){
                attendance[1]=strtoul(value,NULL,10);
                }
              if(column==3){
                attendance[2]=strtoul(value,NULL,10);
                }
              if(column==4){
                attendance[3]=strtoul(value,NULL,10);
                }
              if(column==5){
                attendance[4]=strtoul(value,NULL,10);
                }
              if(column==6){
                attendance[5]=strtoul(value,NULL,10);
                }
              if(column==7){
                attendance[6]=strtoul(value,NULL,10);
                }
            
            column++;
            value = strtok(NULL, ",");
          }
        }
      }
      else{
        while(value){
          if(column == 1){
              classConducted[0]=strtoul(value,NULL,10);
              }
          if(column == 2){
            classConducted[1]=strtoul(value,NULL,10);
            }
          if(column == 3){
            classConducted[2]=strtoul(value,NULL,10);
            }
          if(column == 4){
            classConducted[3]=strtoul(value,NULL,10);
            }
          if(column == 5){
            classConducted[4]=strtoul(value,NULL,10);
            }
          if(column == 6){
            classConducted[5]=strtoul(value,NULL,10);
            }
          if(column == 7){
            classConducted[6]=strtoul(value,NULL,10);
            }  
          column++;
          value = strtok(NULL, ",");
          continue;
        }
      }
      row++;
    }
    for(int i=0;i<7;i++){
      float att; 
      att=attendance[i]*100/classConducted[i];
      printf("Subject %d : %.2f %%\n",i+1,att);
    }
  }
}

char AddStudent(){
  FILE *std; //Student Data
  char name[20];
  int rno;
  std = fopen("./data/student-data.csv","a+");
  printf("Enter Student Name:");
  scanf("%s",name);
  printf("Enter Registration Number:");
  scanf("%d",&rno);
  if (!std){
    printf("Can't open file!\n");
  }
  else{
    char buffer[1024];
    int row=0,column=0;
    while (fgets(buffer,1024,std))
    {
      column=0;
      row++;
      if (row==0){
        continue;
      }
      char* value = strtok(buffer,",");
      while (value){
        long int temp = strtoul(value,NULL,10);
        if(temp==rno){
          return printf("Student already exists!\n");
        }
        column++;
        value = strtok(NULL, ",");
        continue;
      }
    }
    fprintf(std,"%s,%d\n",name,rno);
    return printf("Student added\n");
    fclose(std);
  }
}