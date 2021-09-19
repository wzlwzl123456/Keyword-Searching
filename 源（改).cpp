#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
#include<sstream>
#define MAX_ROOM 1024
using namespace std;
FILE* fp;
char location[MAX_ROOM];
char s1[MAX_ROOM];
int total_num = 0;
int switch_num = 0;
int case_num[MAX_ROOM] = { 0 };
int if_else_num = 0;
int if_else_if_num = 0;
int else_flag = 0;
int str_flag = 1;
int annotation_flag1 = 0;
int annotation_flag2 = 0;
string key[32] = {"auto","break00","case","char","const","continue","default00","do","double","else",
"enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof",
"static","struct","switch","typedef","union","unsigned","void","volatile","while"
};
void openfile(const char* locate) {
	if ((fp = fopen(locate, "r")) == NULL) {
		printf("can't open file\n");
		exit(1);
	}
	else {
		//printf("open success\n");
	}
}
void output() {
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
}
int main() {
	int len;
	cin >> location;
	openfile(location);
	while (!feof(fp)) {
		fgets(s1, MAX_ROOM, fp);
		len = strlen(s1);
		for (int i = 0; i < len; i++ ) {
			if (s1[i] == '/' && s1[i + 1] == '/') {//È¥³ý//ÐÍ×¢ÊÍ
				annotation_flag1 = 1;
			}
			if (s1[i] == '\n') {
				annotation_flag1 = 0;
			}
			if (s1[i] == '/' && s1[i + 1] == '*') {//È¥³ý/**/×¢ÊÍ
				annotation_flag2 = 1;
			}
			if (s1[i] == '*' && s1[i + 1] == '/') {
				s1[i] = s1[i + 1] = ' ';
				annotation_flag2 = 0;
			}
			if (s1[i] == '"') {//È¥³ý""×Ö·û´®
				s1[i] = ' ';
				str_flag = -str_flag;
			}
			if (str_flag <= 0 || annotation_flag2 == 1 || annotation_flag1 == 1 ) {
				s1[i] = ' ';
			}
		}
		istringstream str(s1);
		string out;
		while (str.good()) {
			getline(str, out,' ');
			for (int i = 0; i < out.length(); i++) {
				if (out[i] < 'a' || out[i]>'z') {
					out.replace(i, 1, "0");
				}
			}
			if (!out.empty()) {
				//cout << out << endl;
				for (int i = 0; i < 32; i++) {
					if (out == key[i]) {
						total_num++;// cout << total_num << endl;
						if (i == 25) {
							switch_num++;
						}
						if (i == 2) {
							case_num[switch_num]++;
						}
						break;
					}
				}
			}
		}
	}
	output();
	return 0;
}