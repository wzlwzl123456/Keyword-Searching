#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
#include<sstream>
#include<stack>
#define MAX_ROOM 1024 
using namespace std;
FILE* fp;
int total_num = 0;
int switch_num = 0;
int case_num[MAX_ROOM] = { 0 };
int if_else_num = 0;
int if_else_if_num = 0;
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
void output(int level) {
	if (fclose(fp) == 0) {
		if (level >= 1) {
			printf("total num:%d\n", total_num);
		}
		if (level >= 2) {
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
		}
		if (level >= 3) {
			printf("if_else num:%d\n", if_else_num);
		}
		if (level == 4) {
			printf("if_else_if num:%d\n", if_else_if_num);
		}
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
	int level;//操作等级
	char location[MAX_ROOM];//文件地址
	int top1;
	int str_flag = 1;//用于帮助处理字符串内容
	int annotation_flag1 = 0;//帮助处理//型注释
	int annotation_flag2 = 0;//帮助处理/**/型注释
	char oldstr[5][10] = { "else if","(",";",":","	" };//要替换掉的原有代码字符，有新的需替换代码可再添加
	char newstr[5][10] = { "elseif "," "," "," "," " };//替换的新代码字符
	int len;
	int else_if_flag;
	char s1[MAX_ROOM];//存储每行
	stack<int>st;
	cin >> location;
	cin >> level;
	openfile(location);
	while (!feof(fp)) {
		fgets(s1, MAX_ROOM, fp);
		len = strlen(s1);
		for (int i = 0; i < 5; i++) {
			strrpc(s1, oldstr[i], newstr[i]);
		}//把一些特殊的代码字符改成可识别的形式
		
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
				//cout << out1 << endl;
				for (int i = 0; i < 33; i++) {
					if (out1 == key[i]) {
						total_num++; //cout << total_num << endl;
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
	output(level);
	return 0;
}
