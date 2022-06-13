#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void menu();
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
  menu();
}

void menu()
{
  int choice;
  long int regno;

  system("clear");
  printf("\t\t\t  MENU\t\t\n\n");
  printf("\t1.Add New Student   \t2.Check Attendance \t3.Search Student \n\t4.Exit\n\n");
  scanf("%d",&choice);
  switch(choice)
  {
      case 1:
        AddStudent();
        break;
      case 2: 
        CheckAttendance();
        break;
      case 3:  
        printf("\nEnter Registration Number:");
        scanf("%ld",&regno);
        getUser(regno);
        break;
      case 4: 
        system("clear");
        exit(0);
        break;
      default:
                  system("clear");
                  printf("\nEnter 1 to 4 only");
                  exit(0);
                  
    menu();
  }
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
          printf("\nName: %s\nRegistration No.: %ld\n\n",value,regno);
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
  struct user currentUser;

  long int rno;
  printf("\nEnter Registration Number:");
  scanf("%ld",&rno);
  
  std = fopen("./data/student-data.csv","r");
  atd = fopen("./data/attendance-data.csv","r");
  
  if(!std || !atd){
    printf("Can't access the file.");
  }
  else{
    char buffer[1024];
    struct subject sub[7];
    currentUser.name = getUser(rno);
    currentUser.rno = rno;
    if(currentUser.name == NULL){
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
    for(int i=0;i<7;i++){
      float att;
      att=currentUser.att[i]*100/sub[i].hoursConducted;
      printf("%s : %.2f %%\n",sub[i].name,att);
    }
  }
}

char AddStudent(){
  FILE *std; //Student Data
  FILE *atd; //Attendance Data
  char name[20];
  long int rno;
  std = fopen("./data/student-data.csv","a+");
  atd = fopen("./data/attendance-data.csv","a+");
  printf("Enter Student Name:");
  scanf("%s",name);
  printf("Enter Registration Number:");
  scanf("%ld",&rno);
  if (!std || !atd){
    printf("Can't open file!\n");
  }
  else{
    char buffer[1024];
    int row=0,column=0;
    if(getUser(rno)!=NULL){
      return printf("User already exixts!\n");
    }
    fprintf(std,"%ld,%s\n",rno,name);
    fprintf(atd,"\n%ld,%d,%d,%d,%d,%d,%d,%d",rno,0,0,0,0,0,0,0);
    return printf("Student added\n");
    fclose(std);
  }
}