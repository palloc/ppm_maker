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


/******************************************
  Change Japanese flag to Bangladesh flag
******************************************/

// ppm file 
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

void image_write(DOT *flag, FILE *fp){
	int i = 0, j;
	char *new_line = "\n";
	char *buf;
	char *header = "P3\n160 100\n255\n";
	buf = (char *)calloc(x*y, sizeof(char));
	//write header
	fputs(header, fp);
	//write flag
	for(i=0; i<y; ++i){
		for(j=0; j<x; ++j){
			sprintf(buf, "%d %d %d ", flag[i*x + j].red, flag[i*x + j].green, flag[i*x + j].blue);
			fputs(buf, fp);
		}
		fputs(new_line, fp);
	}
	free(buf);
}

void image_modify(DOT *flag){
	int i, j;
	//change color(white to green)	
	for(i=0; i<y; ++i){
		for(j=0; j<x; ++j){
			if(flag[i*x + j].red==255 && flag[i*x + j].green==255 && flag[i*x + j].blue==255){
				flag[i*x + j].red = 0;
				flag[i*x + j].green = 107;
				flag[i*x + j].blue = 77;
			}
		}
	}
}

int main(int argc, char **argv){
	FILE *fp_in;
	FILE *fp_out;
	DOT *flag;
	//allocate memory
	flag = (DOT *)calloc(x*y, sizeof(DOT));

	//open files
	fp_in = fopen(argv[1], "r");
	fp_out = fopen(argv[2], "w");

	image_read(flag, fp_in);
	image_modify(flag);
	image_write(flag, fp_out);

	free(flag);
	fclose(fp_in);
	fclose(fp_out);
	return 0;
}



