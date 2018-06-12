#ifndef Heh
#define Heh
#include <string.h>
#include <stdlib.h>
#include <math.h>
struct nexus {
	int start;
	int end;
	char value[255];
};
struct variable {
	char name[10];
	int ind;
	char value[255];
};
void deleteSpaces(char *s)
{
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] == ' ') {
			for (int j = i; j < strlen(s); j++) {
				s[j] = s[j + 1];
			}
			i--;
		}
	}

}
struct nexus findCellSt(struct nexus *cell,int NumCell,int st) {
	for (int i = 0; i < NumCell; i++) {
		if (cell[i].start == st) return cell[i];
	}
	struct nexus c = { 10, 20, "her" };
	return c;
}
struct nexus findCellEn(struct nexus *cell, int NumCell, int en) {
	for (int i = 0; i < NumCell; i++) {
		if (cell[i].end == en) return cell[i];
	}
	struct nexus c= { 10, 20, "her" };
	return c;
}

int isEqStr(char *s1, char *s2) {
	if (strlen(s1) != strlen(s2))return 0;
	for (int i = 0; i < strlen(s1); i++) {
		if (s1[i] != s2[i])return 0;
	}
	return 1;
	
}
void sortOp(int *sOp, int in,char *s) {
	int h = 0;
	for (int i = 0; i < in; i++) {
		if ((s[sOp[i]] == '*' || s[sOp[i]] == '/')) {
			if (i == h)h++;
			else {
				/*int t = sOp[i];
				sOp[i] = sOp[h];
				sOp[h] = t;
				h++;*/
				int t = sOp[i];
				for (int j = i; j > h; j--) {
					sOp[j] = sOp[j - 1];
				}
				sOp[h] = t;
				h++;
			}
		}
	}
	//return sOp;
}
void addScoba(char *s) {
	int p = strlen(s);
	for (int i = p; i >= 1; i--) {
		s[i] = s[i - 1];
	}
	s[0] = '(';
	s[p+1] = ')';
	s[p + 2] = '\0';
}
void removeCell(struct nexus *cell, int NumCell, struct nexus g) {
	for (int i = 0; i < NumCell; i++) {
		if (cell[i].start == g.start && cell[i].end == g.end) {
			NumCell--;
			for (int j = i; j < NumCell; j++) {
				cell[j] = cell[j + 1];
			}
			break;
		}
	}
}
char* subtraction(char *s1, char *s2);
char* plus(char *s1, char *s2);
char* multiply(char *s1, char *s2);
char* divide(char *s1, char *s2);
int comp(char *s1, char *s2);
int compi(int *r, int *b);
char* plus(char *s1, char *s2) {
	if (s1[0] != s2[0]) {
		if (s2[0] == ' ')s2[0] = '-'; else s2[0] = ' ';
		return subtraction(s1, s2);
	}
	
	 int max = max(strlen(s1), strlen(s2))-1;
	 int *a;
		a=(int*)malloc(max*sizeof(int));
		int *b;
		b= (int*)malloc(max*sizeof(int));
	for (int i = 0; i < max; i++) { a[i] = 0; b[i] = 0; }
		for (int i = 0; i < strlen(s1)-1; i++) {
			int k= s1[strlen(s1) - 1 - i] - '0';
			a[i] = k;
		}
		for (int i = 0; i < strlen(s2) - 1; i++) {
			b[i] = s2[strlen(s2) - 1 - i]-'0';
		}
		
		int p = 0;
		for (int i = 0; i < max; i++) {
			a[i] = a[i] + b[i]+p;
			p = a[i] / 10;
			a[i] %= 10;
		}
		while (p > 0) {
			a[max]=  p % 10;
			p/= 10;
			max++;
		}
		char *result;
		result= malloc(max*sizeof(char));
		
		if (s1[0] == ' ')result[0] = ' '; else result[0] = '-';
		for (int i = max-1,j=1; i >= 0; i--,j++) {
			char ch=a[i]+'0';
			
			result[j] = ch;
		}
		result[max+1] = '\0';
		//free(a); free(b);
	return result;
}
char* subtraction(char *s1, char *s2) {
	if (s2[0] == ' ')s2[0] = '-'; else s2[0] = ' ';
	if (s1[0] == s2[0]) {
		return plus(s1, s2);
	}
	int max = max(strlen(s1), strlen(s2)) - 1;
	int *a;
	a = (int*)malloc(max*sizeof(int));
	int *b;
	b = (int*)malloc(max*sizeof(int));
	for (int i = 0; i < max; i++) { a[i] = 0; b[i] = 0; }
	char *smin; char *smax;
	if (comp(s1, s2) == 0) return " 0";
	if (comp(s1, s2) > 0) { smax = s1; smin = s2; }
		else { smax = s2; smin = s1; }
	
		for (int i = 0; i < strlen(smax) - 1; i++) {
			a[i] = smax[strlen(smax) - 1 - i] - '0';
		}
		for (int i = 0; i < strlen(smin) - 1; i++) {
			b[i] = smin[strlen(smin) - 1 - i] - '0';
		}
	
	int p = 0;
	for (int i = 0; i < max; i++) {
		a[i] = a[i] - b[i] + p;
		if (a[i] < 0) { p = -1; a[i] += 10; }
	}
	int k = max - 1;
	while (a[k] == 0) k--;
	
	char *result;
	result = malloc(max*sizeof(char));

	if (smax[0] == ' ')result[0] = ' '; else result[0] = '-';
	for (int i = k, j = 1; i >= 0; i--, j++) {
		char ch = a[i] + '0';
		result[j] = ch;
	}
	result[k + 2] = '\0';
	//free(a); free(b);
	return result;
}

char* multiply(char *s1, char *s2) {
	//int max = max(strlen(s1), strlen(s2)) - 1;
	int cl = (strlen(s1) + strlen(s2));
	int bl = (strlen(s2) - 1);
	int al = (strlen(s1) - 1);
	int *a;
	a = (int*)malloc(al*sizeof(int));
	int *b;
	b = (int*)malloc((strlen(s2)-1)*sizeof(int));
	int *c;
	c = (int*)malloc(cl*sizeof(int));
	for (int i = 0; i < al; i++)a[i] = 0;
	for (int i = 0; i < bl; i++)b[i] = 0;
	for (int i = 0; i < cl; i++)c[i] = 0;

	for (int i = 0; i < al; i++) {
		a[i] = s1[strlen(s1) - 1 - i] - '0';
	}
	for (int i = 0; i < bl; i++) {
		b[i] = s2[strlen(s2) - 1 - i] - '0';
	}
	
	for (int i = 0; i < al; i++) {
		for (int j = 0; j < bl; j++) {
			c[i + j]+= a[i] * b[j];
		}
	}
	int p = 0;
	for (int i = 0; i < cl; i++) {
		p = (c[i]+p) / 10;
		c[i] = (c[i]+p)%10;
	}
	p = cl - 1;
	while (c[p] == 0)p--;
	char *result;
	result = malloc((p+2)*sizeof(char));
	if (s1[0] == s2[0])result[0] = ' '; else result[0] = '-';
	for (int i = p, j = 1; i >= 0; i--, j++) {
		result[j] = c[i] + '0';
	}
	result[p + 2] = '\0';
	//free(a); free(b);
	return result;
}
int* minus(int* r, int *m);
int* mul(int *b, int k);
char* divide(char *s1, char *s2) {
	int bl = (strlen(s2) - 1);
	int al = (strlen(s1) - 1);
	int max = max(al, bl);
	int cl = max;
	int *a;
	a = (int*)malloc((al+1)*sizeof(int));
	int *b;
	b = (int*)malloc((bl+1)*sizeof(int));
	int *c;
	c = (int*)malloc((cl+1)*sizeof(int));
	for (int i = 0; i <= al; i++)a[i] = 0;
	for (int i = 0; i <= bl; i++)b[i] = 0;
	for (int i = 0; i <= cl; i++)c[i] = 0;

	a[0] = al; b[0] = bl;
	for (int i = 1; i <= al; i++) {
		a[i] = s1[strlen(s1)  - i] - '0';
	}
	for (int i = 1; i <= bl; i++) {
		b[i] = s2[strlen(s2)  - i] - '0';
	}
	int *r;
	r = (int*)malloc((bl+2)*sizeof(int));
	for (int i = 0; i <= bl+1; i++)r[i] = 0;
	int ain = 0;
start: {
	if (bl > al)return " 0";
	for (int i = al,j=bl; i >al-bl; i--,j--) {
		r[j] = a[i];
	}
	r[0] = bl; ain = al-bl;
	if (compi(r, b) == -1) {
		if (bl > al - 1) return " 0";
		//r[0]++; r[r[0]] = a[ain]; ain--;
		r[0]++;
		for (int i = r[0]; i > 1; i--) {
			r[i] = r[i - 1];
		}
		r[1] = a[ain--];
	}
	}
	   char *result; int nom = 1;
	   result = (int*)malloc(cl*sizeof(int));
	   if (s1[0] == s2[0])result[0] = ' '; else result[0] = '-';

	   while (1) {
		   int *m;
		   for (int k = 9; k >= 0; k--) {
			   m = mul(b, k);
			   if (compi(r, m) >= 0) {
				   r = minus(r, m);
				   result[nom++] = k + '0';
				   break;
			   }
		   }
		   if (ain == 0)break;
		   r[0]++;
		   for (int i = r[0]; i > 1; i--) {
			   r[i] = r[i - 1];
		   }
		   r[1] = a[ain--];
	   }
	   result[nom] = '\0';

	return result;
}

int comp(char *s1, char *s2) {
	if (strlen(s1) > strlen(s2))return 1;
	if (strlen(s1) < strlen(s2))return -1;
	for (int i = 1; i < strlen(s1); i++) {
		if (s1[i] > s2[i])return 1;
		if (s1[i] < s2[i])return -1;
	}
	return 0;
}
int compi(int *r, int *b) {
	if (r[0] > b[0])return 1;
	if (r[0] < b[0]) return -1;
	for (int i = r[0]; i >0; i--) {
		if (r[i] > b[i]) return 1;
		if (r[i] < b[i]) return - 1;
	}
	return 0;
}
int* mul(int *b, int k) {
	int *res;
	int c = 0;
	int ss = b[0];
	res = (int*)malloc((ss + 2)*sizeof(int));
	if (k == 0) {
		res[0] = 1; res[1] = 0;
		return res;
	}
	
	for (int i = 0; i <= ss + 1; i++)res[i] = 0;
	for (int i = 1; i <=ss; i++) {
		res[i] = (k*b[i] + c) % 10;
		c= (k*b[i] + c) /10;
	}
	while (c > 0) {
		res[++ss] = c % 10;
		c /= 10;
	}
	res[0] = ss;
	return res;
}
int* minus(int* r, int *m) {
	int p = 0;
	for (int i = 1; i <= max(r[0],m[0]); i++) {
		r[i] = r[i] - m[i] + p;
		if (r[i] < 0) { p = -1; r[i] += 10; }
	}
	int k = max(r[0], m[0]);
	while (r[k] == 0) k--;
	r[0] = k;
	return r;
}

#endif