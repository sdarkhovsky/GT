// NCCodePareser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <ctype.h>
#include <string>

void downcase_and_remove_space_chars(char* buf) {
    int len = strlen(buf);
    char* ptr = buf;
    int i;
    for (i = 0; i < len; i++) {
        if (!isspace(buf[i])) {
            *ptr = tolower(buf[i]);
            ptr++;
        }
    }
    *ptr = 0;
}

void parse_number(char** pptr, double& num) {
    char* ptr = *pptr;
    const std::string chars = "0123456789.+-";
    while (chars.find(*ptr) != std::string::npos) ptr++;
    char tmp = *ptr;
    *ptr = 0;
    num = atof(*pptr);
    *ptr = tmp;
    *pptr = ptr;
}

void parse_and_execute_line(char* buf, std::string& out_str) {
    int inum;
    double num;
    char* ptr = buf;
    while (*ptr) {
        switch (*ptr) {
            case 'g': 
            case 'G':
            {
                char* ptr1 = ptr+1;
                parse_number(&ptr1, num);
                inum = (int)num;
                switch (inum) {
                    case 0: 
                        out_str += "Rapid positioning";
                        break;
                    default:
                        for (char* ptr2 = ptr; ptr2 < ptr1; ptr2++)
                            out_str += *ptr2;
                        break;
                }
                ptr = ptr1;
            }
            break;
            case 'x':
            case 'X':
            {
                char* ptr1 = ptr + 1;
                parse_number(&ptr1, num);
                if (num > 0)
                    out_str += "Right ";
                else
                    out_str += "Left ";
                out_str += std::to_string(fabs(num));
                ptr = ptr1;
            }
            break;
            case 'y':
            case 'Y':
            {
                char* ptr1 = ptr + 1;
                parse_number(&ptr1, num);
                if (num > 0)
                    out_str += "Up ";
                else
                    out_str += "Down ";
                out_str += std::to_string(fabs(num));
                ptr = ptr1;
            }
            break;
            case 'z':
            case 'Z':
            {
                char* ptr1 = ptr + 1;
                parse_number(&ptr1, num);
                if (num > 0)
                    out_str += "Forward ";
                else
                    out_str += "Back ";
                out_str += std::to_string(fabs(num));
                ptr = ptr1;
            }
            break;
            default: {
                out_str += *ptr;
                ptr++;
            }
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
        return 1;
    FILE *f_in, *f_out;
    fopen_s(&f_in, argv[1], "r");
    fopen_s(&f_out, argv[2], "w");
    if (!f_in || !f_out)
        return 1;
    char buf[256];
    int max_len = sizeof(buf);
    while (fgets(buf, max_len, f_in)) {
        std::string str_out;
        parse_and_execute_line(buf, str_out);
        fputs(str_out.c_str(), f_out);
    }

    fclose(f_in);
    fclose(f_out);

    return 0;
}

