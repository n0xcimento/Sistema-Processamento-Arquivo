#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metadata02.h"

typedef struct{
	int section_identifier;
	char course_number[16];
	char semester[8];
	int year;
	char instructor[16];
} Section;


//auxiliary functions
void init(char *filename);
int update_field(Section *info);
void print_identifier(FILE *ptr);

int main(void){
	int choice=1;
	char filename[16]="section.dat";

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
	void registe(Section *info);

	FILE *fptr=NULL;
	Section new_info, infoR;

	if((fptr=fopen(filename, "r+"))==NULL)
		puts("[!] ERRO");
	else{

		fread(&infoR, sizeof(Section), 1, fptr);
		while(!feof(fptr)){

			if(infoR.section_identifier==0){
				registe(&new_info);
				fseek(fptr, -1*sizeof(Section), SEEK_CUR);
				fwrite(&new_info, sizeof(Section), 1, fptr);
				break;
			}

			fread(&infoR, sizeof(Section), 1, fptr);
		}

		fclose(fptr);
	}
}

void update(char *filename){
	FILE *fptr=NULL;

	Section infoR;
	int toUpdate;

	if((fptr=fopen(filename, "r+"))==NULL)
		puts("[!] ERRO");
	else{
		print_identifier(fptr);
		rewind(fptr);

		printf("\nSection Identifier: ");
		scanf("%d", &toUpdate);

		fread(&infoR, sizeof(Section), 1, fptr);
		while(!feof(fptr)){

			if(infoR.section_identifier==toUpdate){

				printf("%-22s%-17s%-12s%-8s%-14s\n", "Section Identifier", "Course Number", "Semester", "Year", "Instructor");
				printf("%-22d%-17s%-12s%-8d%-14s\n", infoR.section_identifier, infoR.course_number, infoR.semester, infoR.year, infoR.instructor);

				if(update_field(&infoR)){
					fseek(fptr, -1*sizeof(Section), SEEK_CUR);
					fwrite(&infoR, sizeof(Section), 1, fptr);
				}else
					infoR.section_identifier=0;
				break;
			}
			fread(&infoR, sizeof(Section), 1, fptr);
		}
		if(infoR.section_identifier!=0)
			printf("Record updated!\n\n");
		else
			printf("Record didn't update!\n\n");

		fclose(fptr);
	}
}

void print_identifier(FILE *ptr){
	Section infoR;
	fread(&infoR, sizeof(Section), 1, ptr);
	while(infoR.section_identifier!=0 && !feof(ptr)){

		printf("%d\n", infoR.section_identifier);

		fread(&infoR, sizeof(Section), 1, ptr);
	}
}

int update_field(Section *section_info){
	char choice;
	printf("\nWhich field do you wish to update?\n");
	printf("%s\n%s\n%s\n%s\n%s\n: ", "1.Section Identifier", "2.Course Number", "3.Semester", "4.Year", "5.Instructor");
	scanf("\n%[12345]", &choice);

	if('0'<choice && choice<'6')
		printf("New data: ");

	switch(choice){
		case '1':
			scanf("%d", &section_info->section_identifier);
			break;

		case '2':
			scanf("\n%s", section_info->course_number);
			break;

		case '3':
			scanf("\n%s", section_info->semester);
			break;

		case '4':
			scanf("%d", &section_info->year);
			break;

		case '5':
			scanf("\n%s", section_info->instructor);
			break;

		default:
			printf("\nInvalid Option!\n");
			return 0;
	}return 1;
}


void delete(char *filename){
	FILE *fptr=NULL;
	Section infoR, empty={0, "-", "-", 0, "-"};
	int toDelete;

	if((fptr=fopen(filename, "r+"))==NULL)
		puts("[!] ERRO");
	else{

		printf("Section Identifier: ");
		scanf("%d", &toDelete);

		fread(&infoR, sizeof(Section), 1, fptr);
		while(infoR.section_identifier!=0 && !feof(fptr)){

			if(infoR.section_identifier==toDelete){
				fseek(fptr, -1*sizeof(Section), SEEK_CUR);
				fwrite(&empty, sizeof(Section), 1, fptr);
				break;
			}

			fread(&infoR, sizeof(Section), 1, fptr);
		}

		if(infoR.section_identifier==0)
			printf("Section didn't find!\n\n");
		else
			printf("Section deleted!\n\n");

		fclose(fptr);
	}

}

void print_dataField(char *filename){
	FILE *fptr=NULL;
	Section infoR;

	char *header[5]={"Section Identifier", "Course Number", "Semester", "Year", "Instructor"};
	int space[5]={22, 17, 12, 8, 14};
	int ans[5]={0};


	if((fptr=fopen(filename, "r"))==NULL)
		puts("[!] ERRO");
	else{

		printf("Which atribute do you wish to view?\n1.Section Identifier\n2.Course Number\n3.Semester\n4.Year\n5.Instructor\n0. Mostrar\n");
		for(int i=0, a; i<5; i++){
			printf(": ");
			scanf("%d", &ans[i]);

			if(!ans[i]) break;
		}
		
		//header
		putchar('\n');
		for(int f, i=0; i<5 && ans[i]; i++){
				f=ans[i]-1;
				printf("%-*s", space[f], header[f]);
		}putchar('\n');

		fread(&infoR, sizeof(Section), 1, fptr);
		while(!feof(fptr)){

			if(infoR.section_identifier!=0){

				for(int i=0; i<5 && ans[i]; i++){
					switch(ans[i]){
						case 1:
							printf("%-*d", space[0], infoR.section_identifier);
							break;

						case 2:
							printf("%-*s", space[1], infoR.course_number);
							break;

						case 3:
							printf("%-*s", space[2], infoR.semester);
							break;

						case 4:
							printf("%-*d", space[3], infoR.year);
							break;

						case 5:
							printf("%-*s", space[4], infoR.instructor);
							break;
					}
				}putchar('\n');
			}

			fread(&infoR, sizeof(Section), 1, fptr);
		}
		printf("\n--------[End Of File]--------\n\n");

		fclose(fptr);
	}
}

void registe(Section *info){

	printf("Section Identifier: ");
	scanf("%d", &info->section_identifier);

	printf("Course Number: ");
	scanf("\n%s", info->course_number);

	printf("Semester: ");
	scanf("\n%s", info->semester);

	printf("Year: ");
	scanf("%d", &info->year);

	printf("Instructor: ");
	scanf("\n%s", info->instructor);

}

void init(char *filename){
	FILE *fptr=NULL;
	Section empty={0, "-", "-", 0, "-"};

	if((fptr=fopen(filename, "w"))==NULL)
		puts("[!] ERRO");
	else{

		for(int i=1; i<=32; i++)
			fwrite(&empty, sizeof(Section), 1, fptr);

		fclose(fptr);
	}
}