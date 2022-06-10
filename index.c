#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char AddStudent();
char CheckAttendance();
char* getUser(long int regno);

struct subject
{
  char name[20];
  long int hoursConducted;
};

struct user
{
  char* name;
  long int rno;
  long int att[7];
};

int main(){
  // AddStudent();
  CheckAttendance();
}
char* getUser(long int regno){
  FILE *std; //Student Data
  std = fopen("./data/student-data.csv","r");
  if(!std){
    printf("Can't access the file.");
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
      long int temp = strtoul(value,NULL,10); //int of value
      if(regno==temp){
        while (value){
        if(column == 1){
          return value;
        }
        column++;
        value = strtok(NULL, ",");
        continue;
      }
      }
      
    }
    fclose(std);
  }
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
    struct user currentUser;
    char buffer[1024];
    struct subject sub[7];

    currentUser.name = getUser(rno);
    currentUser.rno = rno;

    if(getUser == NULL){
      exit(0);
    }

    int row=0,column=0;
    while (fgets(buffer,1024,atd))
    {
      char* value = strtok(buffer,",");
      column=0;
      if(row==0){
        while(value){
          if(column == 1){
            strcpy(sub[0].name,value);
          }
          else if(column == 2){
            strcpy(sub[1].name,value);
          }
          else if(column == 3){
            strcpy(sub[2].name,value);
          }
          else if(column == 4){
            strcpy(sub[3].name,value);
          }
          else if(column == 5){
            strcpy(sub[4].name,value);
          }
          else if(column == 6){
            strcpy(sub[5].name,value);
          }
          else if(column == 7){
            strcpy(sub[6].name,value);
          }

          column++;
          value = strtok(NULL, ",");
          continue;
        }

      }

      else if(row==1){
        while(value){
          if(column == 1){
            sub[0].hoursConducted=strtoul(value,NULL,10);
          }
          if(column == 2){
            sub[1].hoursConducted=strtoul(value,NULL,10);
          }
          if(column == 3){
            sub[2].hoursConducted=strtoul(value,NULL,10);
          }
          if(column == 4){
            sub[3].hoursConducted=strtoul(value,NULL,10);
          }
          if(column == 5){
            sub[4].hoursConducted=strtoul(value,NULL,10);
          }
          if(column == 6){
            sub[5].hoursConducted=strtoul(value,NULL,10);
          }
          if(column == 7){
            sub[6].hoursConducted=strtoul(value,NULL,10);
          }
          column++;
          value = strtok(NULL, ",");
          continue;
        }
      }
      
      else{
        long int temp = strtoul(value,NULL,10);
        if(temp==rno){
          while (value){ //Store value of the no of hours attended in an array
              if(column==1){
                currentUser.att[0]=strtoul(value,NULL,10);
                }
              if(column==2){
                currentUser.att[1]=strtoul(value,NULL,10);
                }
              if(column==3){
                currentUser.att[2]=strtoul(value,NULL,10);
                }
              if(column==4){
                currentUser.att[3]=strtoul(value,NULL,10);
                }
              if(column==5){
                currentUser.att[4]=strtoul(value,NULL,10);
                }
              if(column==6){
                currentUser.att[5]=strtoul(value,NULL,10);
                }
              if(column==7){
                currentUser.att[6]=strtoul(value,NULL,10);
                }
            
            column++;
            value = strtok(NULL, ",");
          }
        }
      }      
      row++;
    }
    printf("\nName: %s",currentUser.name);
    printf("\nRegistration No.: %ld\n",currentUser.rno);
    for(int i=0;i<7;i++){
      float att;
      att=currentUser.att[i]*100/sub[i].hoursConducted;
      printf("\n%s : %.2f %%",sub[i].name,att);
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