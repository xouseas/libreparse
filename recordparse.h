#ifndef RECORDPARSE_H
#define RECORDPARSE_H 1

#include "records.h"

struct student_mark **parse_records(int fd, int verbose);
void free_record(struct student_mark *sm);

#endif
