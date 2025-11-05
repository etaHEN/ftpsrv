/* Copyright (C) 2025 John Törnblom

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING. If not, see
<http://www.gnu.org/licenses/>.  */

#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/sysctl.h>
#include <sys/syscall.h>

#include <ps5/kernel.h>

#include "srv.h"
#include "log.h"

int
main() {
  uint16_t port = 2121;
  int notify_user = 1;
  pid_t pid;

  signal(SIGPIPE, SIG_IGN);

  // change authid so certain character devices can be read, e.g.,
  // /dev/sflash0
  pid = getpid();
  if(kernel_set_ucred_authid(pid, 0x4801000000000013L)) {
    FTP_LOG_PUTS("Unable to change AuthID");
    return EXIT_FAILURE;
  }

  while(1) {
    ftp_serve(port, notify_user);
    notify_user = 0;
    sleep(3);
  }

  return EXIT_SUCCESS;
}


/*
  Local Variables:
  c-file-style: "gnu"
  End:
*/
