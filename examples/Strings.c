#include <stdio.h>

#include "../build/cthings.h"

int main(void) {
  String_t hello = String_new("Hello");
  String_t world = String_new("World!");
  String_t hello_world = String_join_by(hello, world, " ");
  printf("%s\n", String_val(hello_world));
  return 0;
}
