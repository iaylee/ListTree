#pragma once

#include "element.h"

/* Forward reference to a str_element. */
struct str_element;

/* Static constructor that creates new string elements. */
struct str_element *str_element_new(char *value);
/* Static function that obtains the string from a str_element. */
char *str_element_get_value(struct str_element *);
/* Static function that determines whether this is a str_element. */
int is_str_element(struct element *);
