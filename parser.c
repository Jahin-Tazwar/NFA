#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

void advance_parser(Parser* parser) {
    parser -> current_token = get_next_token(parser -> laxer);
}