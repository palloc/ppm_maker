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

void image_read(DOT *flag, FILE *fp){
	int i = 0, j;
	char *buf;
	buf = (char *)calloc(x*y, sizeof(char));
	//remove header 
	for(j=0; j<3; ++j){
		fgets(buf, x*y, fp);
	}
	while(fgets(buf, x*y, fp) != NULL){
		flag[i*x].red = atoi(strtok(buf, " "));
		flag[i*x].green = atoi(strtok(NULL, " "));
		flag[i*x].blue = atoi(strtok(NULL, " "));
		for(j=1; j<x; ++j){
			flag[i*x + j].red = atoi(strtok(NULL, " "));
			flag[i*x + j].green = atoi(strtok(NULL, " "));
			flag[i*x + j].blue = atoi(strtok(NULL, " "));
		}
		++i;
	}
	free(buf);
}



/******************************************
  Change Japanese flag to Bangladesh flag
******************************************/
int main(int argc, char **argv){
	int i, j;
	char *new_line = "\n";
	char *header = "P3\n160 100\n255\n";
	FILE *fp_in;
	FILE *fp_out;
	DOT *flag;
	char *buf;
	//allocate memory
	flag = (DOT *)calloc(x*y, sizeof(DOT));
	buf = (char *)calloc(x*y, sizeof(char));
	//open files
	fp_in = fopen(argv[1], "r");
	fp_out = fopen(argv[2], "w");
	//store flag to flag_in
	image_read(flag, fp_in);
	//write header
	fputs(header, fp_out);
	//
	for(i=0; i<y; ++i){
		for(j=0; j<x; ++j){
			//change color(white to green)
			if(flag[i*x + j].red==255 && flag[i*x + j].green==255 && flag[i*x + j].blue==255){
				flag[i*x + j].red = 0;
				flag[i*x + j].green = 107;
				flag[i*x + j].blue = 77;
			}
			sprintf(buf, "%d %d %d ", flag[i*x + j].red, flag[i*x + j].green, flag[i*x + j].blue);
			fputs(buf, fp_out);
		}
		fputs(new_line, fp_out);
	}

	free(flag);
	free(buf);
	fclose(fp_in);
	fclose(fp_out);
	return 0;
}



