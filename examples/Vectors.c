#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Vectors.h"

typedef struct {
  int age;
  char *name;
} Person;

Person *person_new(char *name, int age) {
  Person *p = malloc(sizeof(Person));
  p->age = age;
  p->name = malloc(sizeof(char) * strlen(name) + 1);
  memcpy(p->name, name, strlen(name));
  p->name[strlen(name)] = 0;
  return p;
}

Any_t double_person_age(Any_t x) {
  Person *src = x;
  Person *cloned = malloc(sizeof(Person));
  cloned->age = src->age * 2;
  cloned->name = Str(src->name);
  return cloned;
}
void acc_person_age(Any_t x, Any_t y) { *(double *)y += ((Person *)x)->age; }
int filter_under_50(Any_t x) { return ((Person *)x)->age < 50; }

void print_people_vec(Vector_t vec) {
  Person *p;
  while (Vector_iter(vec, (Any_t *)&p)) {
    printf("%s => %d\n", p->name, 10);
  }
  Vector_iter_reset(vec);
}

int main(void) {
  /*
   * All vector elements must allocated on heap before pushed
   *
   */

  Vector_t people = Vector_new();

  Vector_push(people, person_new("John Conway", 67));
  Vector_push(people, person_new("Edilson Hacker", 19));
  Vector_push(people, person_new("Fabio Akita", 53));
  Vector_push(people, person_new("Ismael Grahms", 25));

  printf("\nOriginal Vector:\n");
  print_people_vec(people);

  /*
   * Task: Calc the age avg.
   *
   */

  double people_cout = people->size;
  double age_acc = 0;

  Vector_reduce(people, acc_person_age, &age_acc);
  printf("\nThe age avg is %.2f\n", age_acc / people_cout);

  /*
   * Task: Filter under 50
   *
   */

  Vector_t under_50 = Vector_filter(people, filter_under_50);
  printf("\nUnder 50:\n");
  print_people_vec(under_50);

  /*
   * Task: Double people age
   *
   */

  Vector_t people_double_age = Vector_map(people, double_person_age);

  printf("\nDouble Age Vector:\n");
  print_people_vec(people_double_age);

  return 0;
}
