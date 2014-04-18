

#ifndef OESPPARSER_LIBESPPARSER_H
#define OESPPARSER_LIBESPPARSER_H

void *esp_open(char *);
void esp_close(void *);

int esp_getloc(void *);
char *esp_read_name(void *);
void esp_read_name_in(void *, char *);
void *esp_get_buffer(void *);

int esp_get_groupsize(void *);
void esp_skip_group(void *);
void esp_enter_group(void *);
void esp_leave_group(void *);

int esp_get_recordsize(void *);
void esp_skip_record(void *);
void esp_enter_record(void *);
void esp_leave_record(void *);

int esp_get_subrecordsize(void *);
void esp_skip_subrecord(void *);

// We need routines which prints these to a given char array.
// esp_print_type
// esp_print_size
// esp_print_grouptype

#endif
