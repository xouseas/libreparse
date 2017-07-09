#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "records.h"

/* 
   WARNING: This software was intentionally implemented in
   an UNSAFE manner. USE ONLY for educational purposes!
   
   D. A. Glynos / May 11th 2015
   Fourth exercise material
   Software Security Course
   University of Piraeus, Department of Informatics
*/

void free_record(struct student_mark *sm) {
	free(sm);
}

struct student_mark **parse_records(int fd, int verbose) {
	int num_records, i;
	struct stat statbuf;
	struct student_mark **array, *rec;
	char temp_buffer[120];
	
	fstat(fd, &statbuf);
	num_records = statbuf.st_size / sizeof(struct student_mark);

	// allocate one more for a NULL sentinel
	array = malloc((num_records + 1) * sizeof(struct student_mark *));
	i = 0;

	while(num_records > 0) {
		rec = malloc(sizeof(struct student_mark));
		read(fd, rec, sizeof(*rec));
		array[i] = rec;
		sprintf(temp_buffer, "found '%s' with mark %.1f", 
			rec->name, rec->mark);
		if (verbose) {
			fprintf(stderr, "parser: %s\n", temp_buffer);
		}
		i++;
		num_records--;
	}	

	// note the end of the array with a NULL sentinel
	array[i] = (struct student_mark *) NULL;

	return array;
}

