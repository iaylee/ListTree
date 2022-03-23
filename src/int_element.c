#include "int_element.h"
#include "str_element.h"
#include "refcount.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

/*
* Polymorphism implementation (extends element)
*/
struct int_element_class {
    void(*print)(struct int_element*);
    int(*compare)(struct element*, struct element*);
};

struct int_element{
    struct int_element_class* class;
    int isIntElem;
    int a;
};

struct int_element_class int_element_table;

void int_element_finalizer(){
    return;
}

/* Static constructor that creates new integer elements. */
struct int_element *int_element_new(int value){
    struct int_element *this = rc_malloc(sizeof(*this), int_element_finalizer);
    this->isIntElem = 1;
    this->class = &int_element_table;
    this->a = value;
    return this;
}


/* Static function that obtains the value held in an int_element. */
int int_element_get_value(struct int_element *ie){
    return ie->a;
}


/* Static function that determines whether this is an int_element. */
int is_int_element(struct element *e){
    int* p = ((int*)++e);
    if(*p == 1){
        return 1;
    }
    return 0;
}

void int_print(struct element *ie);
void int_print(struct element *ie){
  if(is_int_element(ie)){
        struct int_element* uno = (struct int_element *) ie;
        printf("%d", uno->a);
    }
}

/* Compare two elements. int_element should always compare LESS than str_element.
   * The compare function should return:
   *   a number < 0 if the first element is less than the second element,
   *   0 if the elements compare equal,
   *   a number > 0 otherwise.
 */
int int_compare(struct element *ie1, struct element *ie2);
int int_compare(struct element *ie1, struct element *ie2){
      if(is_int_element(ie1) && is_int_element(ie2)){
          struct int_element* one = (struct int_element *) ie1;
          struct int_element* two = (struct int_element *) ie2;
          return one->a - two->a;
      }
      else if(is_int_element(ie1) && is_str_element(ie2)){
          return -1;
      }
      else if(is_str_element(ie1) && is_int_element(ie2)){
          return 1;
      } 
      else{
          return ie1->class->compare(ie1, ie2);
      }
}

struct int_element_class int_element_table = {int_print, int_compare};
