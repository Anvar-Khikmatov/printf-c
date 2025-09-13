#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>


int num_len(int num){
    int counter =0;
        if(num < 0)
            counter++;
        while(num != 0){
            num = num / 10;
            counter++;
    }    
    return counter;
}


char* num_to_str(int num, int base) {
    int len = num_len(num);
    int ind = 0;
    char* initial_str = malloc(sizeof(char) * (len + 1));  
    char sign = '-';
    int check_negative = num;

    if (num == 0) {
        char* zero_str = malloc(2);
        zero_str[0] = '0';
        zero_str[1] = '\0';
        free(initial_str);
        return zero_str;

    } else if (num < 0) {
        num = abs(num);
    }

    if (base == 10) {
        while (num != 0) {
            initial_str[ind++] = num % 10 + '0';
            num = num / 10;
        }
    } else if (base == 8) {
        while (num != 0) {
            initial_str[ind++] = num % 8 + '0';
            num = num / 8;
        }
    } else if (base == 16) {
        while (num != 0) {
            initial_str[ind++] = num % 16 < 10 ? num % 16 + '0' : num % 16 + 'A' - 10;
            num = num / 16;
        }
    }

    if(check_negative < 0) {
        initial_str[ind++] = sign;
    }
        initial_str[ind] = '\0'; 

    char* final_str = malloc(sizeof(char) * (len + 1));  
    int start = 0;
    int last = ind - 1;

    while (last >= 0) {
        final_str[start++] = initial_str[last--];
    }

    final_str[start] = '\0';
    free(initial_str);
    return final_str;
}



char* unsign_int(long int num){
    long int constant = UINT_MAX;
    int ind = 0;
    char* initial_str = malloc(sizeof(char) * 11);

      if (num == 0) {
        char* zero_str = malloc(2);
            zero_str[0] = '0';
            zero_str[1] = '\0';
            free(initial_str);
            return zero_str;

      } else if (num < 0) {
            constant = constant - labs(num) + 1;
      } else {
            constant = num;
      }

        while (constant != 0) {
            initial_str[ind++] = constant % 10 + '0';
            constant = constant / 10;
        }
 
            initial_str[ind] = '\0'; 

    char* final_str = malloc(sizeof(char) * (ind + 1));  
    int start = 0;
    int last = ind - 1;

    while (last >= 0) {
        final_str[start++] = initial_str[last--];
    }

        final_str[start] = '\0';
      free(initial_str);
    return final_str;
}



char* ptr_to_str(long int num) {
    
    int ind = 0;
    char* initial_str = malloc(sizeof(char) * 16);  

        while (num != 0) {
            initial_str[ind++] = num % 16 < 10 ? num % 16 + '0' : num % 16 + 'a' - 10;
            num = num / 16;
        }

    char* final_str = malloc(sizeof(char) * 16);  
    int start = 0;
    int last = ind - 1;

    final_str[start++] = '0';
    final_str[start++] = 'x';
    while (last >= 0) {
        final_str[start++] = initial_str[last--];
    }

    final_str[start] = '\0';
    free(initial_str);
    return final_str;
}



int my_printf(char* param, ...) {
    va_list arg_list;
    va_start(arg_list, param);
    int total =0;

    for(int i =0; param[i]; i++){
        if(param[i] == '%') {
        i++;    
        switch (param[i]) {
            case 'c': { 
                char char_format = (char)va_arg(arg_list, int);
                total += write(1, &char_format, 1);
                break;
            
            }case 's': {     
                char* string_format = va_arg(arg_list, char*);
                string_format = string_format ? string_format : "(null)";
                total += write(1, string_format, strlen(string_format)); 
                break;      

            }case 'd': {
                int int_format = va_arg(arg_list, int);
                char* print_int_format = num_to_str(int_format, 10);
                total += write(1, print_int_format, strlen(print_int_format));
                free(print_int_format);
                break; 
            
            }case 'o': {
                int octal_format = va_arg(arg_list, int);
                char* print_octal_format = num_to_str(octal_format, 8);
                total += write(1, print_octal_format, strlen(print_octal_format));
                free(print_octal_format);
                break; 

            }case 'x': {
                int hex_format = va_arg(arg_list, int);
                char* print_hex_format = num_to_str(hex_format, 16);
                total += write(1, print_hex_format, strlen(print_hex_format));
                free(print_hex_format);
                break; 

            }case 'u': {
                long int uint_format = va_arg(arg_list, long int);
                char* print_uint_format = unsign_int(uint_format);
                total += write(1, print_uint_format, strlen(print_uint_format));
                free(print_uint_format);
                break;

            }case 'p': {
                long int ptr_format = va_arg(arg_list, long int);
                char* print_ptr_format = ptr_to_str(ptr_format);
                total += write(1, print_ptr_format, strlen(print_ptr_format));
                free(print_ptr_format);
                break;
            }    
          } 
        }else 
                total+= write(1, &param[i], 1);
    }
    va_end(arg_list);
    return total;
}

int main() {

    int pointer;
    printf("%d\n", my_printf("%c %s %d %o %x %u %p", 'A', "String", 100, 100, 100, -4294967295, &pointer));

    return 0;
}