#include "src/counter.h"

#include <stdio.h>
#include <unistd.h>

#define LS_FILE_DIR "/bin/ls"
#define LS_COUNT_MAX 5
#define REST_MESSAGE "lsを5回も打ちました．一旦休んだらどうですか？"

int main(int argc, char *argv[]) {
	int ls_count = get_ls_count();
	if(ls_count < 0) {
		fprintf(stderr, "error.\n");
		return 1;
	}
	if(ls_count >= 5) {
		printf("%s\n", REST_MESSAGE);
		return 0;
	}
	execv(LS_FILE_DIR, argv);
	return 0;
}
