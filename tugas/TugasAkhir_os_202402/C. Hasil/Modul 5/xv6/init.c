// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(void)
{
  // Buka console (stdin, stdout, stderr)
  if(open("console", O_RDWR) < 0){
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr

  // --- Jalankan audit sebagai proses pertama (PID 1) ---
  char *audit_argv[] = { "audit", 0 };
  exec("audit", audit_argv);

  // Jika gagal menjalankan audit, fallback ke shell
  printf(1, "init: exec audit failed, fallback to sh\n");

  char *sh_argv[] = { "sh", 0 };
  for(;;){
    printf(1, "init: starting sh\n");
    int pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      exec("sh", sh_argv);
      printf(1, "init: exec sh failed\n");
      exit();
    }
    while(wait() >= 0)
      ; // Tunggu shell selesai, lalu ulang
  }
}