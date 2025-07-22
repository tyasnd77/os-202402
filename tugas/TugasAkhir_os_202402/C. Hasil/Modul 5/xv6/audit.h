#ifndef AUDIT_H
#define AUDIT_H

#define MAX_AUDIT 128

struct audit_entry {
  int pid;
  int syscall_num;
  int tick;
};

extern struct audit_entry audit_log[MAX_AUDIT];
extern int audit_index;

void get_audit_log(void);  

#endif
