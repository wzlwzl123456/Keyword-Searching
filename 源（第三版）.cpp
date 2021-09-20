#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
#include<sstream>
#include<stack>
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
int str_flag = 1;
int annotation_flag1 = 0;
int annotation_flag2 = 0;
int len;
int else_if_flag ;
int top1;
char oldstr[4][10] = { "else if","sizeof(","break;","default:"};
char newstr[4][10] = { "elseif ","sizeof ","break ","default "};
string key[33] = {"auto","break","case","char","const","continue","default","do","double","else",
"enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof",
"static","struct","switch","typedef","union","unsigned","void","volatile","while","elseif"
};
void openfile(const char* locate) {
	if ((fp = fopen(locate, "r")) == NULL) {
		printf("can't open file\n");
		exit(1);
	}
}/*打开文件*/
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
		printf("if_else num:%d\n", if_else_num);
		printf("if_else_if num:%d\n", if_else_if_num);
	}
}/*输出函数*/
char* strrpc(char* str, char* oldstr, char* newstr) {
	char bstr[MAX_ROOM];
	memset(bstr, 0, sizeof(bstr));
	for (int i = 0; i < strlen(str); i++) {
		if (!strncmp(str + i, oldstr, strlen(oldstr))) {
			strcat(bstr, newstr);
			i += strlen(oldstr) - 1;
		}
		else {
			strncat(bstr, str + i, 1);
		}
	}
	strcpy(str, bstr);
	return str;
}/*字符数组子串替换*/
int main() {
	stack<int>st;
	cin >> location;
	openfile(location);
	while (!feof(fp)) {
		fgets(s1, MAX_ROOM, fp);
		len = strlen(s1);
		for (int i = 0; i < 4; i++) {
			strrpc(s1, oldstr[i], newstr[i]);
		}//把一些特殊的关键字改成可识别的形式
		for (int i = 0; i < len; i++ ) {
			if (s1[i] == '/' && s1[i + 1] == '/') {//去除//型注释
				annotation_flag1 = 1;
			}
			if (s1[i] == '\n') {
				annotation_flag1 = 0;
			}
			if (s1[i] == '/' && s1[i + 1] == '*') {//去除/**/注释
				annotation_flag2 = 1;
			}
			if (s1[i] == '*' && s1[i + 1] == '/') {
				s1[i] = s1[i + 1] = ' ';
				annotation_flag2 = 0;
			}
			if (s1[i] == '"') {//去除""字符串
				s1[i] = ' ';
				str_flag = -str_flag;
			}
			if (str_flag <= 0 || annotation_flag2 == 1 || annotation_flag1 == 1 ) {
				s1[i] = ' ';
			}	
		}
		istringstream str1(s1);
		string out1;
		while (str1.good()) {
			getline(str1, out1,' ');
			if (!out1.empty()) {
				cout << out1 << endl;
				for (int i = 0; i < 33; i++) {
					if (out1 == key[i]) {
						total_num++; cout << total_num << endl;
						if (i == 25) {
							switch_num++;
						}
						if (i == 2) {
							case_num[switch_num]++;
						}
						if (i == 15) {
							st.push(1);
						}
						if (i == 32) {
							st.push(2);
							total_num++;
						}
						if (i == 9){
							else_if_flag = 0;
							while (1) {
								top1 = st.top();
								st.pop();
								if (top1 == 2) {
									else_if_flag = 1;
								}
								if (top1 == 1) {
									if (else_if_flag == 0) {
										if_else_num++;
									}
									if (else_if_flag == 1) {
										if_else_if_num++;
									}
									break;
								}
							}
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