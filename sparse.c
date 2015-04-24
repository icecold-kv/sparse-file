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
	int size = 0;
	char tmp;
	char buf[2048];
	int l = 0;
	while (read(STDIN_FILENO,&tmp,1) != 0) {
		size++;
		if (tmp == 0) {
			zcnt++;
			if (l != 0) {
				write(of, buf, l);
				l = 0;
			}
		} else {
			if (zcnt > 0) {
				lseek(of, zcnt, SEEK_CUR);
				zcnt = 0;
			}
			buf[l++];
			if (l > 2048) {
				write(of, buf, 2048);
				l = 0;
			}
		}
	}
	if (zcnt > 0) {
		ftruncate(of,size);
	}
	close(of);
	return 0;
}
