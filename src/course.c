#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metadata.h"

typedef struct{
	char name[64];
	char number[16];
	int hour;
	char departament[8];
} Course;


//auxiliary functions
void init(char *filename);
int update_field(Course *info);
void courseName(FILE *ptr);

int main(void){
	int choice=1;
	char filename[16]="course.dat";

	init(filename);

	while((choice=menu())!=5){
		switch(choice){

			case 1:
				insert(filename);
				system("clear");
				break;

			case 2:
				system("clear");
				update(filename);
				break;

			case 3:
				delete(filename);
				break;

			case 4:
				system("clear");
				print_dataField(filename);
				break;

			default:
				printf("Invalid Option!\n");
		}
	}

	return 0x00;
}

void insert(char *filename){
	void registe(Course *info);

	FILE *fptr=NULL;
	Course course, info;

	if((fptr=fopen(filename, "r+"))==NULL)
		puts("[!] ERRO");
	else{

		fread(&info, sizeof(Course), 1, fptr);
		while(!feof(fptr)){

			if(!strcmp(info.name, "-")){
				registe(&course);
				fseek(fptr, -1*sizeof(Course), SEEK_CUR);
				fwrite(&course, sizeof(Course), 1, fptr);
				break;
			}

			fread(&info, sizeof(Course), 1, fptr);
		}

		fclose(fptr);
	}
}

void registe(Course *info){

	printf("Course name: ");
	scanf("\n%48[^\n]", info->name);

	printf("course number: ");
	scanf("\n%s", info->number);

	printf("Credit Hours: ");
	scanf("%d", &info->hour);

	printf("Departament: ");
	scanf("\n%s", info->departament);
}

void update(char *filename){
	FILE *fptr=NULL;

	Course info;
	char toUpdate[48];

	if((fptr=fopen(filename, "r+"))==NULL)
		puts("[!] ERRO");
	else{
		courseName(fptr);
		rewind(fptr);

		printf("\nCourse Name: ");
		scanf("\n%48[^\n]", toUpdate);

		fread(&info, sizeof(Course), 1, fptr);
		while(!feof(fptr)){

			if(!strcmp(info.name, toUpdate)){

				printf("%-24s%-12s%-12s%s\n", "Name", "Number", "Hours", "Departament");
				printf("%-24s%-12s%-12d%s\n", info.name, info.number, info.hour, info.departament);

				if(update_field(&info)){
					fseek(fptr, -1*sizeof(Course), SEEK_CUR);
					fwrite(&info, sizeof(Course), 1, fptr);
				}else
					strcpy(info.number, "-");
				break;
			}
			fread(&info, sizeof(Course), 1, fptr);
		}
		if(strcmp(info.number, "-"))
			printf("Record updated!\n\n");
		else
			printf("Record didn't update!\n\n");

		fclose(fptr);
	}
}

void courseName(FILE *ptr){
	Course info;
	fread(&info, sizeof(info), 1, ptr);
	while(strcmp(info.number, "-") && !feof(ptr)){

		printf("%s\n", info.name);

		fread(&info, sizeof(Course), 1, ptr);
	}
}

int update_field(Course *course){
	char choice;
	printf("\nWhich field do you wish to update?\n");
	printf("%s\n%s\n%s\n%s\n: ", "1.Course Name", "2.Course Number", "3.Hours", "4.Departament");
	scanf("\n%[1234]", &choice);

	if('0'<choice && choice<'5')
		printf("New Data: ");

	switch(choice){
		case '1':
			scanf("\n%48[^\n]", course->name);
			break;

		case '2':
			scanf("\n%s", course->number);
			break;

		case '3':
			scanf("%d", &course->hour);
			break;

		case '4':
			scanf("\n%s", course->departament);
			break;

		default:
			printf("Invalid Option!: ");
			return 0;
	}
}


void delete(char *filename){
	FILE *fptr=NULL;
	Course info, empty={"-", "-", 0, "-"};
	char toDelete[48];

	if((fptr=fopen(filename, "r+"))==NULL)
		puts("[!] ERRO");
	else{
		courseName(fptr);
		rewind(fptr);

		printf("Course Name: ");
		scanf("\n%48[^\n]", toDelete);

		fread(&info, sizeof(Course), 1, fptr);
		while((strcmp(info.number, "-")) && !feof(fptr)){

			if(!strcmp(info.name, toDelete)){
				fseek(fptr, -1*sizeof(Course), SEEK_CUR);
				fwrite(&empty, sizeof(Course), 1, fptr);
				break;
			}

			fread(&info, sizeof(Course), 1, fptr);
		}

		if(strcmp(info.number, "-"))
			printf("Course Deleted!\n\n");
		else
			printf("Course didn't find!\n\n");

		fclose(fptr);
	}

}

void print_dataField(char *filename){
	FILE *fptr=NULL;
	Course info;

	char *fieldName[4]={"Name", "Number", "Hours", "Departament"};
	int tab[4]={28, 15, 14, 16};
	int ans[4]={0};

	if((fptr=fopen(filename, "r"))==NULL)
		puts("[!] ERRO");
	else{

		printf("Which atribute do you wish to view?\n1.Course Name\n2.Course Number\n3.Hours\n4.Departament\n");
		for(int i=0, a; i<4; i++){
			printf(": ");
			scanf("%d", &ans[i]);

			if(!ans[i]) break;
		}
		
		//header
		putchar('\n');
		for(int f, i=0; i<4 && ans[i]; i++){
				f=ans[i]-1;
				printf("%-*s", tab[f], fieldName[f]);
		}putchar('\n');

		fread(&info, sizeof(Course), 1, fptr);
		while(!feof(fptr)){

			if(strcmp(info.number, "-")){

				for(int i=0; i<4 && ans[i]; i++){
					switch(ans[i]){
						case 1:
							printf("%-*s", tab[0], info.name);
							break;

						case 2:
							printf("%-*s", tab[1], info.number);
							break;

						case 3:
							printf("%-*d", tab[2], info.hour);
							break;

						case 4:
							printf("%-*s", tab[3], info.departament);
							break;
					}
				}putchar('\n');
			}

			fread(&info, sizeof(Course), 1, fptr);
		}
		printf("\n----------[End Of File]----------\n\n");

		fclose(fptr);
	}
}

void init(char *filename){
	FILE *fptr=NULL;
	Course empty={"-", "-", 0, "-"};

	if((fptr=fopen(filename, "w"))==NULL)
		puts("[!] ERRO");
	else{

		for(int i=1; i<=32; i++)
			fwrite(&empty, sizeof(Course), 1, fptr);

		fclose(fptr);
	}
}
