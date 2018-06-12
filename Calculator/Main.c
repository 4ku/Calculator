#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#include "Functions.h"
#include<string.h>

int main() {
	char s[1000];
	gets(s);
	deleteSpaces(s);

	struct nexus cell[100];
	int NumVar = 0;
	int NumCell = 0;
	struct variable var[10];

	addScoba(s);

	{int open = 0; int op[100];
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] == '(') {
			op[open] = i;
			open++;
			if (i - 1 >= 0 && !(s[i - 1] == '+' || s[i - 1] == '-' || s[i - 1] == '*' || s[i - 1] == '/' || s[i - 1] == '(')) {
				int j = strlen(s)+1;
				
				for (; j >= i; j--) {
					s[j] = s[j - 1];
				}
				s[i - 1] = '*';
			}
		}
		else if (s[i] == ')') {
			cell[NumCell].end = i; open--;
			cell[NumCell].start = op[open];
			NumCell++;
			/*if (i + 1 < strlen(s) && s[i + 1] == '(') {
				int j = strlen(s);
				int u = j;
				for (; j >= i + 2; j--) {
					s[j] = s[j - 1];
				}
				s[i + 1] = '*';
				s[u + 1] = '\0';
			}*/
		}
	}
	}

	findVar: {
		char str[10] = "";
		for (int i = 0; i < strlen(s); i++) {
			int fl = 0;
			while (((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A'&&s[i] <= 'Z')) && (i < strlen(s))) {
				int u = strlen(str);
				str[u] = s[i];
				str[u + 1] = '\0';
				i++; fl = 1;
			}
			if (fl == 1) {
				for (int j = 0; j < NumVar; j++) {
					if(strcmp(str, var[j].name)==0){
						fl = 0;
						for (int j = strlen(str) - 1; j >= 0; j--) str[j] = '\0';
						break;
					}
				}
				if (fl == 1) {
					for (int j = 0; j < strlen(str); j++) {
						var[NumVar].name[j] = str[j];
					}
					var[NumVar].name[strlen(str)] = '\0';
					var[NumVar].ind = i - strlen(str);
					NumVar++;
					for (int j = strlen(str) - 1; j >= 0; j--) str[j] = '\0';
				}
			}
		}
	
		for (int i = 0; i < NumVar; i++) {
			printf("enter value of %s\n", var[i].name);
			scanf("%s", var[i].value);
			if (var[i].value[0] != '-') {
				int y = strlen(var[i].value);
				for (int j = y; j > 0; j--) {
					var[i].value[j] = var[i].value[j - 1];
				}
				var[i].value[0] = ' ';
				var[i].value[y + 1] = '\0';
			}
		}
	}


	/*cell[NumCell].start = 0;
	cell[NumCell].end = strlen(s)-1;
	NumCell++;*/
    int	operations[100];
	int NumOp = 0; 
	int n = NumCell;
	int minus = 0; int check = 0;

	for (int i = 0; i < n; i++) {
		int k = cell[i].start + 1;
		int cOp = 0;
		//if (s[cell[i].start] == '(')k = cell[i].start + 1; else k = cell[i].start;
		if (s[k] == '-') {
			minus = 1;
			if (s[k + 1] == '(') {
				struct nexus c=findCellSt(cell,NumCell,k+1);
				if (c.value[0] == '-')c.value[0] = ' '; else c.value[0] = '-';
				k = c.end + 1;
			}
			else {
				k++;
			check:
				{	if (s[k] >= '0'&&s[k] <= '9') {
					cell[NumCell].start = k;

					while (s[k] >= '0'&&s[k] <= '9' || s[k] == '.') k++;

					cell[NumCell].end = k - 1;
					if(minus==1)cell[NumCell].value[0] = '-';else cell[NumCell].value[0] = ' ';
					int p = 1;
					for (int j = cell[NumCell].start; j < k; j++, p++)cell[NumCell].value[p] = s[j];
					cell[NumCell].value[p] = '\0';
					NumCell++;
				}
				else {
					char r[10]; cell[NumCell].start = k;
					int t = 0;
					while ((s[k] >= 'a' && s[k] <= 'z') || (s[k] >= 'A'&&s[k] <= 'Z')) {
						r[t] = s[k]; t++;
						k++;
					}
					r[t] = '\0';
					cell[NumCell].end = k - 1;
					for (int j = 0; j < NumVar; j++) {
						if (isEqStr(var[j].name, r) == 1) {
							int b;
							if (var[j].value[0] == '-' || var[j].value[0] == ' ')b = 0; else {
								b = 1; cell[NumCell].value[0] = ' ';
							}
							for (int y = 0; y < strlen(var[j].value); y++, b++)cell[NumCell].value[b] = var[j].value[y];
							cell[NumCell].value[b] = '\0';
							if (minus == 1) {
								if (cell[NumCell].value[0] == '-')cell[NumCell].value[0] = ' '; else cell[NumCell].value[0] = '-';
							}
							break;
						}

					}
					NumCell++;
				}
				if (check == 1) goto icheck;
				}
			}
		}
		int sOp[100]; int in = 0;
		for (int j = k; j < cell[i].end; j++) {
			if (s[j] == '+' || s[j] == '-' || s[j] == '*' || s[j] == '/') {
				//operations[NumOp++] = j;
				sOp[in++] = j;
				cOp++;
			}
			else if (s[j]=='(') {
				struct nexus c = findCellSt(cell,NumCell,j);
				j = c.end;
			}
			else {
				minus = 0; check = 1; k = j;
				goto check;
			icheck: {
				check = 0;
				j = k-1;
				}
			}
		}
		sortOp(sOp, in, s);
		for (int j = 0; j < in; j++)operations[NumOp++] = sOp[j];

		if (cOp == 0) {
			NumCell--;
			for (int j = 0; j <= strlen(cell[NumCell].value); j++) cell[i].value[j] = cell[NumCell].value[j];
			
		}
		
	}
	for (int i = 0; i < NumOp; i++) {
		struct nexus left = findCellEn(cell, NumCell, operations[i] - 1);
		struct nexus right = findCellSt(cell, NumCell, operations[i] + 1);
		char *res;
		switch (s[operations[i]]) {
		case '+':
			res = plus(left.value, right.value);
			break;
		case '-':
			res = subtraction(left.value, right.value);
			break;
		case '*':
			res = multiply(left.value, right.value);
			break;
		case '/':
			res = divide(left.value, right.value);
			break;
		}
		removeCell(cell, NumCell, left);
		removeCell(cell, NumCell, right);
		NumCell -= 2;
		if (s[left.start - 1] == '(' && s[right.end + 1] == ')') {
			int nom = 0;
			for (int i = 0; i < NumCell; i++) {
				if (cell[i].start == left.start - 1) {
					nom = i;
					break;
				}
			}
			for (int j = 0; j < strlen(res); j++)cell[nom].value[j] = res[j];
			cell[nom].value[strlen(res)] = '\0';
		}
		else {
			cell[NumCell].start = left.start;
			cell[NumCell].end = right.end ;
			for (int j = 0; j < strlen(res); j++)cell[NumCell].value[j] = res[j];
			cell[NumCell].value[strlen(res)] = '\0';
			NumCell++;
		}
		
	}
	char *result;
	for (int i = 0; i < NumCell; i++) {
		if ((cell[i].value[1] >= '0'&&cell[i].value[1] <= '9') && ((cell[i].value[0] == ' ' || cell[i].value[0] == '-'))) {
			result = cell[i].value;
			break;
		}
	}
	printf("%s\n", result);
	
	int x;
	scanf("%d", &x);

}
