#ifndef RUNNER_H
#define RUNNER_H

#include <stdio.h>
#include "parser.h"
#include "tokens.h"

ParseStatus process_input(FILE* source, FILE* log_output);
void run_program(int argc, char** argv);

#endif
