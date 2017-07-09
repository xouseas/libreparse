#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "recordparse.h"

/* 
   D. A. Glynos / May 11th 2014
   Fourth exercise material
   Software Security Course
   University of Piraeus, Department of Informatics

   BUILD instructions:

   $ make

   USAGE: 

   $ ./printavg -v records.db
*/

void usage(void) {
	fprintf(stderr, "usage: printavg [-v] records.db\n"
                 	"   -v: print entries while parsing\n");
}

int main(int argc, char *argv[]) {
	int verbose = 0; // false
	char *fname;
	struct student_mark **p;
	int fd;
	int student_count = 0;
	float mark_sum = 0.0;

	if ((argc == 3) && (!strcmp(argv[1], "-v"))) {
		verbose = 1;
		fname = argv[2];
	} else if (argc == 2) {
		fname = argv[1];
	} else {
		usage();
		exit(1);
	}
	
	fd = open(fname, O_RDONLY);
	if (fd < 0) {
		perror("error opening db file");
		exit(1);
	}

	p = parse_records(fd, verbose);
	if (p == NULL) {
		fprintf(stderr, "parsing finished in error\n");
		exit(1);
	}

	while(*p) {
		mark_sum += (*p)->mark;	
		student_count += 1;
		free_record(*p);
		p += 1;
	}

	fprintf(stdout, "%d marks found with a %.1f average\n",
		student_count, mark_sum / student_count);

	close(fd);
	return 0;
}
