#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define x 160
#define y 100

typedef struct{
	int red;
	int green;
	int blue;
}DOT;

int main(int argc, char **argv){
	int i, j;
	char *new_line = "\n";
	char *header = "P3\n160 100\n255\n";
	DOT *flag;
	FILE *fp;
	char *buf;

	flag = (DOT *)calloc(x*y, sizeof(DOT));
	buf = (char *)calloc(x*y, sizeof(char));
	
	fp = fopen(argv[1], "w");
	fputs(header, fp);
	for(i=0; i<y; ++i){
		for(j=0; j<x; ++j){
			if(sqrt(pow(abs(y/2 - i), 2) + pow(abs(x/2 - j), 2)) < 25){
				flag[i*x + j].red = 255;
				flag[i*x + j].green = 0;
				flag[i*x + j].blue = 0;
			}
			else{
				flag[i*x + j].red = 255;
				flag[i*x + j].green = 255;
				flag[i*x + j].blue = 255;
			}
		}
	}
	for(i=0; i<y; ++i){
		for(j=0; j<x; ++j){
			sprintf(buf, "%d %d %d ", flag[i*x + j].red, flag[i*x + j].green, flag[i*x + j].blue);
			fputs(buf, fp);
		}
		fputs(new_line, fp);
	}
	free(flag);
	free(buf);

	return 0;
}

	
	
