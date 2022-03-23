#include "str_element.h"
#include "int_element.h"
#include "refcount.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

/*
* Polymorphism implementation (extends element)
*/
struct str_element_class {
    void(*print)(struct element*);
    int (*compare)(struct element*, struct element*);
};

struct str_element{
    struct str_element_class* class;
    int isStrElem;
    char* a;
};

struct str_element_class str_element_table;

void str_element_finalizer(void *e){
    struct str_element *s = (struct str_element*)e;
  free(s->a);
}

/* Static constructor that creates new streger elements. */
struct str_element *str_element_new(char* value){
    struct str_element *this = rc_malloc(sizeof(*this), str_element_finalizer);
    this->class = &str_element_table;
    this->isStrElem = 0;
    this->a = malloc(strlen(value)+1);
    strcpy(this->a, value);
    return this;
}


/* Static function that obtains the value held in an str_element. */
char *str_element_get_value(struct str_element *se){
        return se->a;
}


/* Static function that determines whether this is an str_element. */
int is_str_element(struct element *e){
    int* p = ((int*)++e);
    if(*p == 0){
        return 1;
    }
    return 0;
}

void str_print(struct element *se);
void str_print(struct element *se){
    if(is_str_element(se)){
        struct str_element* uno = (struct str_element *) se;
        printf("%s", uno->a);
    }
}

/* Compare two elements. int_element should always compare LESS than str_element.
   * The compare function should return:
   *   a number < 0 if the first element is less than the second element,
   *   0 if the elements compare equal,
   *   a number > 0 otherwise.
 */
int str_compare(struct element *se1, struct element *se2);
int str_compare(struct element *se1, struct element *se2){
      if(is_str_element(se1) && is_str_element(se2)){
          struct str_element* one = (struct str_element *) se1;
          struct str_element* two = (struct str_element *) se2;
          return strcmp(one->a, two->a);
      }
      else if(is_int_element(se1) && is_str_element(se2)){
          return -1;
      }
      else if(is_str_element(se1) && is_int_element(se2)){
          return 1;
      } 
      else{
          return se1->class->compare(se1, se2);
      }
}

struct str_element_class str_element_table = {str_print, str_compare};