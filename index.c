#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char AddStudent();

int main(){
  AddStudent();
}

char AddStudent(){
  FILE *std;
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
        int temp = atoi(value);
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