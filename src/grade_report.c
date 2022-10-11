#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metadata02.h"

typedef struct{
	int student_number;
	int section_identifier;
	char grade;
} Grade;


//auxiliary functions
void init(char *filename);
int update_field(Grade *info);
void print_identifier(FILE *ptr);

int main(void){
	int choice=1;
	char filename[16]="grade.dat";

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
	void registe(Grade *info);

	FILE *fptr=NULL;
	Grade new_info, infoR;

	if((fptr=fopen(filename, "r+"))==NULL)
		puts("[!] ERRO");
	else{

		fread(&infoR, sizeof(Grade), 1, fptr);
		while(!feof(fptr)){

			if(infoR.section_identifier==0){
				registe(&new_info);
				fseek(fptr, -1*sizeof(Grade), SEEK_CUR);
				fwrite(&new_info, sizeof(Grade), 1, fptr);
				break;
			}

			fread(&infoR, sizeof(Grade), 1, fptr);
		}

		fclose(fptr);
	}
}

void registe(Grade *info){

	printf("Student Number: ");
	scanf("%d", &info->student_number);

	printf("Section Identifier: ");
	scanf("%d", &info->section_identifier);

	printf("Grade: ");
	scanf("\n%c", &info->grade);
}

void update(char *filename){
	FILE *fptr=NULL;

	Grade infoR;
	int toUpdate;

	if((fptr=fopen(filename, "r+"))==NULL)
		puts("[!] ERRO");
	else{
		print_identifier(fptr);
		rewind(fptr);

		printf("\nSection Identifier: ");
		scanf("%d", &toUpdate);

		fread(&infoR, sizeof(Grade), 1, fptr);
		while(!feof(fptr)){

			if(infoR.section_identifier==toUpdate){

				printf("%-18s%-22s%-9s\n", "Student Number", "Section Identifier", "Grade");
				printf("%-18d%-22d%-9c\n", infoR.student_number, infoR.section_identifier, infoR.grade);

				if(update_field(&infoR)){
					fseek(fptr, -1*sizeof(Grade), SEEK_CUR);
					fwrite(&infoR, sizeof(Grade), 1, fptr);
				}else
					infoR.section_identifier=0;
				break;
			}
			fread(&infoR, sizeof(Grade), 1, fptr);
		}
		if(infoR.section_identifier!=0)
			printf("Record updated!\n\n");
		else
			printf("Record didn't update!\n\n");

		fclose(fptr);
	}
}

void print_identifier(FILE *ptr){
	Grade infoR;
	fread(&infoR, sizeof(Grade), 1, ptr);
	while(!feof(ptr)){

		if(infoR.section_identifier!=0)
			printf("%d\n", infoR.section_identifier);

		fread(&infoR, sizeof(Grade), 1, ptr);
	}
}

int update_field(Grade *grade_info){
	char choice;
	printf("\nWhich field do you wish to update?\n");
	printf("1.Student Number\n2.Section Identifier\n3.Grade\n: ");
	scanf("\n%[123]", &choice);

	if('0'<choice && choice<'4')
		printf("New data: ");

	switch(choice){
		case '1':
			scanf("%d", &grade_info->student_number);
			break;

		case '2':
			scanf("%d", &grade_info->section_identifier);
			break;

		case '3':
			scanf("\n%c", &grade_info->grade);
			break;

		default:
			printf("\nInvalid Option!\n");
			return 0;
	}return 1;
}


void delete(char *filename){
	FILE *fptr=NULL;
	Grade infoR, empty={0,0,'-'};
	int toDelete;

	if((fptr=fopen(filename, "r+"))==NULL)
		puts("[!] ERRO");
	else{
		print_identifier(fptr);
		rewind(fptr);

		printf("\nSection Identifier: ");
		scanf("%d", &toDelete);

		fread(&infoR, sizeof(Grade), 1, fptr);
		while(infoR.section_identifier!=0 && !feof(fptr)){

			if(infoR.section_identifier==toDelete){
				fseek(fptr, -1*sizeof(Grade), SEEK_CUR);
				fwrite(&empty, sizeof(Grade), 1, fptr);
				break;
			}

			fread(&infoR, sizeof(Grade), 1, fptr);
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
	Grade infoR;

	char *header[3]={"Student Number", "Section Identifier", "Grade"};
	int space[3]={18,22,9};
	int ans[3]={0};


	if((fptr=fopen(filename, "r"))==NULL)
		puts("[!] ERRO");
	else{

		printf("Which atribute do you wish to view?\n1.Student Number\n2.Section Identifier\n3.Grade\n");
		for(int i=0, a; i<3; i++){
			printf(": ");
			scanf("%d", &ans[i]);

			if(!ans[i]) break;
		}
		
		//header
		putchar('\n');
		for(int f, i=0; i<3 && ans[i]; i++){
				f=ans[i]-1;
				printf("%-*s", space[f], header[f]);
		}putchar('\n');

		fread(&infoR, sizeof(Grade), 1, fptr);
		while(!feof(fptr)){

			if(infoR.section_identifier!=0){

				for(int i=0; i<3 && ans[i]; i++){
					switch(ans[i]){
						case 1:
							printf("%-*d", space[0], infoR.student_number);
							break;

						case 2:
							printf("%-*d", space[1], infoR.section_identifier);
							break;

						case 3:
							printf("%-*c", space[2], infoR.grade);
							break;
					}
				}putchar('\n');
			}

			fread(&infoR, sizeof(Grade), 1, fptr);
		}
		printf("\n--------[End Of File]--------\n\n");

		fclose(fptr);
	}
}


void init(char *filename){
	FILE *fptr=NULL;
	Grade empty={0, 0, '-'};

	if((fptr=fopen(filename, "w"))==NULL)
		puts("[!] ERRO");
	else{

		for(int i=1; i<=32; i++)
			fwrite(&empty, sizeof(Grade), 1, fptr);

		fclose(fptr);
	}
}
