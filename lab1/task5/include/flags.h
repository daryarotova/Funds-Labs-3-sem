#ifndef FLAGS_H
#define FLAGS_H

#include <stdio.h>

void dFlag(FILE* fileInput, FILE* fileOutput); // исключить символы арабских цифр из входного файла; 
void iFlag(FILE* fileInput, FILE* fileOutput); // сколько раз в этой строке встречаются символы букв латинского алфавита;
void sFlag(FILE* fileInput, FILE* fileOutput); // сколько раз в этой строке встречаются символы, отличные от символов букв латинского алфавита, символов арабских цифр и символа пробела; 
void aFlag(FILE* fileInput, FILE* fileOutput); // заменить символы, отличные от символов цифр, ASCII кодом, записанным в системе счисления с основанием 16.

#endif // FLAGS_H
