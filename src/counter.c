#include "counter.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define LS_COUNT_DIR "/tmp/l5_count"
#define CWD_LEN 256

int get_ls_count() {
	int ls_count = -1;
	char cwd[CWD_LEN];
	char lsd[CWD_LEN];

	if(!getcwd(cwd, CWD_LEN)) {
		perror("getcwd");
		return -1;
	}

	// open for reading
	FILE *fp = fopen(LS_COUNT_DIR, "r");
	if(!fp) {
		perror("fopen");
		return -1;
	}
	fscanf(fp, "%d", &ls_count);
	fscanf(fp, "%s", lsd);

	fclose(fp);

	// re-open for writing
	fp = fopen(LS_COUNT_DIR, "w");
	if(!fp) {
		perror("fopen");
		return -1;
	}

	if(strcmp(cwd, lsd) != 0) {
		fseek(fp, 0, SEEK_SET);
		fprintf(fp, "0\n");
		fprintf(fp, "%s\n", cwd);
		fclose(fp);
		return 0;
	}
	ls_count++;

	// write to file
	fseek(fp, 0, SEEK_SET);

	fprintf(fp, "%d\n", ls_count);
	fprintf(fp, "%s\n", cwd);
	fclose(fp);
	return ls_count;
}

void reset_ls_count() {
	char cwd[CWD_LEN];
	if(!getcwd(cwd, CWD_LEN)) {
		perror("getcwd");
		return;
	}

	FILE *fp = fopen(LS_COUNT_DIR, "r+");
	if(!fp) return;
	fprintf(fp, "0\n");
	fprintf(fp, "%s\n", cwd);
	fclose(fp);
}
