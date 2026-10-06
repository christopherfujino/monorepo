#include <stdio.h> // printf()

typedef struct Person {
  unsigned int age;
  const char *name;
} Person;

typedef struct Employee {
  Person super;
  float salary;
} Employee;

typedef struct Coder {
  Employee super;
  char **favoriteLanguages;
} Coder;

void person_describe(Person *person) {
  printf("%s's age is %d\n", person->name, person->age);
}

int main(void) {
  Employee employee = (Employee){
    .super = (Person){
      .age = 42,
      .name = "Drone",
    },
    .salary = 42'000,
  };

  Coder coder = (Coder){
    .super = (Employee){
      .super = (Person){
        .age = 23,
        .name = "L337",
      },
      .salary = 420'000,
    },
    .favoriteLanguages = (char *[]){
      "OCaml",
      "Go",
      "C",
      nullptr,
    },
  };

  person_describe((Person *)&employee);
  person_describe((Person *)&coder);
}
