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

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/syslimits.h>
#include "logtext.h"

int logtext_file_open (s_logtext_file *lf, const char *path,
                       int flags)
{
  char lines_path[PATH_MAX];
  (void) flags;
  assert(lf);
  assert(path);
  if (!(lf->data = fopen(path, "a+")))
    return -1;
  strlcpy(lines_path, path, sizeof(lines_path));
  strlcat(lines_path, ".lines", sizeof(lines_path));
  if (!(lf->lines = fopen(lines_path, "a+"))) {
    fclose(lf->data);
    return -1;
  }
  lf->line = ftell(lf->lines) / sizeof(line_offset_t);
  lf->offset = ftell(lf->data);
  return 0;
}

int logtext_file_close (s_logtext_file *lf)
{
  int e = 0;
  assert(lf);
  if (fclose(lf->data))
    e += 1;
  lf->data = 0;
  if (fclose(lf->lines))
    e += 2;
  lf->lines = 0;
  lf->line = 0;
  lf->offset = 0;
  return 0;
}

long logtext_file_seek (s_logtext_file *lf, int line,
                        int whence)
{
  long offset;
  if (fseek(lf->lines, line * sizeof(line_offset_t), whence))
    return -1;
  if ((offset = ftell(lf->lines)) < 0)
    return -1;
  if (fread(&offset, sizeof(line_offset_t), 1, lf->lines) != 1)
    return -1;
  if (fseek(lf->data, offset, SEEK_SET))
    return -1;
  return offset;
}

int logtext_file_read (s_logtext_file *lf, char *buffer,
                       line_length_t length)
{
  long          start;
  line_offset_t end;
  line_offset_t line_length;
  assert(lf);
  assert(lf->data);
  assert(lf->lines);
  if ((start = ftell(lf->data)) < 0)
    return -1;
  if (fread(&end, sizeof(line_offset_t), 1, lf->lines) != 1)
    return -1;
  line_length = end - start;
  if (length <= line_length)
    return -1;
  if (fread(buffer, line_length, 1, lf->data) != 1)
    return -1;
  buffer[line_length] = 0;
  return 0;
}

int logtext_file_write (s_logtext_file *lf, char *buffer,
                        line_length_t length)
{
  line_offset_t offset;
  assert(lf);
  assert(buffer);
  assert((long) lf->offset == ftell(lf->data));
  if (fwrite(buffer, length, 1, lf->data) != 1) {
    fseek(lf->data, lf->offset, SEEK_SET);
    return -1;
  }
  offset = lf->offset + length;
  if (fwrite(&offset, sizeof(line_offset_t), 1, lf->lines) != 1) {
    fseek(lf->lines, lf->line * sizeof(line_offset_t), SEEK_SET);
    fseek(lf->data, lf->offset, SEEK_SET);
    return -1;
  }
  lf->offset = offset;
  lf->lines++;
  return 0;
}

int logtext_open_file (s_logtext *lt)
{
  assert(lt);
  return -1;
}

int logtext_open (s_logtext *lt, const char *path, int flags)
{
  char *d;
  assert(lt);
  assert(path);
  d = lt->path;
  while (*path)
    *d++ = *path++;
  *d++ = 0;
  lt->flags = flags;
  lt->number = 0;
  lt->size_limit = LOGTEXT_SIZE_LIMIT;
  lt->window = LOGTEXT_WINDOW;
  while (lt->number < LOGTEXT_NUMBER_MAX && !logtext_open_file(lt))
    lt->number++;
  if (lt->number == LOGTEXT_NUMBER_MAX)
    return -1;
  return 0;
}

int logtext_close (s_logtext *lt)
{
  assert(lt);
  return -1;
}

int logtext_read (s_logtext *lt, char *buffer, line_length_t length)
{
  assert(lt);
  assert(buffer);
  assert(length);
  return -1;
}

int logtext_write (s_logtext *lt, char *buffer, line_length_t length)
{
  assert(lt);
  assert(buffer);
  assert(length);
  return -1;
}
