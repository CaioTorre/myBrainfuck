#include <stdlib.h>
#include <stdio.h>

#define SIZEMEM 100
#define SIZETXT 10000

int readProg(FILE *f, char*);

void main() {
	int mem[SIZEMEM] = { 0 };
	char txt[SIZETXT];
	int pmem = 1;
	int ptxt = 0, endpos, level;
	
	FILE *fd;
	fd = fopen("sourcecode.txt", "r");
	
	endpos = readProg(fd, txt);
	ptxt = 0;
	
	while (ptxt < endpos) {
		switch(txt[ptxt]){
			case '>': pmem = pmem + 1; if (pmem >= SIZEMEM) pmem = 0; break;
			case '<': pmem = pmem - 1; if (pmem < 0) pmem = SIZEMEM - 1; break;
			case '+': mem[pmem] = mem[pmem] + 1; break;
			case '-': mem[pmem] = mem[pmem] - 1; break;
			case '.': printf("%c", (char) mem[pmem]); break;
			case ',': scanf("%c", &mem[pmem]); break;
			case '[': if (mem[pmem] == 0) {
				level = 0;
				do {
					if (txt[ptxt] == '[') level = level + 1;
					if (txt[ptxt] == ']') level = level - 1;
					ptxt = ptxt + 1;
				} while (level > 0);
			}
			break;
			case ']': if (mem[pmem] != 0) {
				level = 0;
				do {
					if (txt[ptxt] == ']') level = level + 1;
					if (txt[ptxt] == '[') level = level - 1;
					ptxt = ptxt - 1;
				} while (level > 0);
			}
			break;
		}
		ptxt = ptxt + 1;
	}
}

int readProg(FILE *f, char* txt) {
	int pos = 0;
	char c;
	while (feof(f) == 0) {
		c = fgetc(f);
		switch (c) {
			case '>':
			case '<':
			case '+':
			case '-':
			case '.':
			case ',':
			case '[':
			case ']': txt[pos] = c; pos++; break;
		}
	}
	txt[pos] = '\0';
	return pos;
}
