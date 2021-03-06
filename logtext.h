/*
 * Copyright 2018 Thomas de Grivel <thoxdg@gmail.com> +33614550127
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef LOGTEXT_H
#define LOGTEXT_H

#include <stdio.h>

typedef unsigned char  line_window_t;
typedef unsigned short line_number_t;
typedef unsigned short line_length_t;
typedef unsigned long  line_offset_t;

typedef struct logtext_file {
  FILE         *data;
  FILE         *lines;
  line_number_t line;
  line_offset_t offset;
} s_logtext_file;
  
#define LOGTEXT_READ   1
#define LOGTEXT_APPEND 2

int  logtext_file_open (s_logtext_file *lf, const char *path,
                        int flags);
int  logtext_file_close (s_logtext_file *lf);
long logtext_file_seek (s_logtext_file *lf, int line, int whence);
int  logtext_file_read (s_logtext_file *lf, char *buffer,
                        line_length_t length);
int  logtext_file_write (s_logtext_file *lf, char *buffer,
                         line_length_t length);
int  logtext_file_reindex (s_logtext_file *lf);

#define LOGTEXT_NUMBER_MAX 1000000
#define LOGTEXT_SIZE_LIMIT      (1 << 21)
#define LOGTEXT_WINDOW          10

typedef struct logtext {
  char           path[PATH_MAX];
  int            flags;
  unsigned long  number;
  s_logtext_file current;
  unsigned long  size_limit;
  line_window_t  window;
  s_logtext_file previous;
} s_logtext;

int logtext_open (s_logtext *lt, const char *path, int flags);
int logtext_close (s_logtext *lt);
int logtext_read (s_logtext *lt, char *buffer, line_length_t length);
int logtext_write (s_logtext *lt, char *buffer, line_length_t length);

#endif
