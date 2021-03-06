#include "file.h"

#include <assert.h>
#include <stdio.h>


bool rs_register_file(
  FILE** file,
  const char* restrict filename,
  const char* restrict mode,
  ResourceDisposer disposer,
  Resources* rss
) {
  assert(file != NULL);
  assert(rss != NULL);
  
  *file = fopen(filename, mode);
  
  return rs_register(*file, disposer, rss);
}

ResourceDisposer rs_disposer_file(void (*error)(void* file, int status)) {
  return rs_disposer_s(fclose_void, error);
}

int fclose_void(void* file) {
  return fclose(file);
}

void fclose_stderr(
  __attribute__((unused)) void* file,
  __attribute__((unused)) int err
) {
  perror("fclose");
}
