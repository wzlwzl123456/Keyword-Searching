#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
FILE* fp;
char location[100];
char key[32][10];
char s1[10];
int total_num = 0;
int switch_num = 0;
int case_num[100] = { 0 };

void openfile(const char *locate) {
	if ((fp = fopen(locate, "r")) == NULL) {
		printf("can't open file\n");
		exit(1);
	}
	else {
		//printf("open success\n");
	}
}

void setkey() {
	strcpy(key[0], "auto");
	strcpy(key[1], "break;");
	strcpy(key[2], "case");
	strcpy(key[3], "char");
	strcpy(key[4], "const");
	strcpy(key[5], "continue");
	strcpy(key[6], "default:");
	strcpy(key[7], "do");
	strcpy(key[8], "double");
	strcpy(key[9], "else");
	strcpy(key[10], "enum");
	strcpy(key[11], "extern");
	strcpy(key[12], "float");
	strcpy(key[13], "for");
	strcpy(key[14], "goto");
	strcpy(key[15], "if");
	strcpy(key[16], "int");
	strcpy(key[17], "long");
	strcpy(key[18], "register");
	strcpy(key[19], "return");
	strcpy(key[20], "short");
	strcpy(key[21], "signed");
	strcpy(key[22], "sizeof");
	strcpy(key[23], "static");
	strcpy(key[24], "struct");
	strcpy(key[25], "switch");
	strcpy(key[26], "typedef");
	strcpy(key[27], "union");
	strcpy(key[28], "unsigned");
	strcpy(key[29], "void");
	strcpy(key[30], "volatile");
	strcpy(key[31], "while");	
}

 int main() {
	 setkey();
	 scanf("%s", &location);
	 openfile(location);
	 while (!feof(fp)) {
		 fscanf(fp, "%s", s1);
		 //printf("%s\n", s1);
		 for (int i = 0; i < 32; i++) {
			 if (strcmp(key[i], s1) == 0) {
				 total_num++;
				 if (i == 25) {
					 switch_num++;
				 }
				 else if (i == 2) {
					 case_num[switch_num]++;
				 }
			 }
		 }
	 }
	 if (fclose(fp) == 0) {
		 printf("total num:%d\n", total_num);
		 printf("switch num:%d\n", switch_num);
		 printf("case num:");
		 for (int i = 1; i <= switch_num; i++) {
			 printf("%d", case_num[i]);
			 if (i == switch_num) {
				 printf("\n");
			 }
			 else {
				 printf(" ");
			 }
		 }
		 //printf("close success\n");
	 }
	 return 0;
}