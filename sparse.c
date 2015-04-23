#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Error: No output file.\n");
		return -1;
	}
	int of = open(argv[1], O_WRONLY|O_CREAT, S_IREAD|S_IWRITE);
	if (of == -1) {
		printf("Error: Can't open output file.\n");
		return -1;
	}
	int zcnt = 0;
	char tmp;
	while (read(STDIN_FILENO,&tmp,1) != 0) {
		if (tmp == 0) {
			zcnt++;
		} else {
			if (zcnt > 0) {
				lseek(of, zcnt, SEEK_CUR);
			}
			write(of, &tmp, 1);
			zcnt = 0;
		}
	}
	if (zcnt > 0) {
		lseek(of, zcnt, SEEK_CUR);
	}
	close(of);
	return 0;
}
