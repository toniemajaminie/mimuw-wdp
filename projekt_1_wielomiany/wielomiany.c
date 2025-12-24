#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

int strongPasswordChecker(char* password) {
    int upper_case = 0, lower_case = 0, digit = 0;
    int i = 0;
    int len = 0;
    char previus_char = password[0];
    int op = 0;
    int T[50] = {1};

    while (password[i] != '\0') {
        ++len;
        char curr = password[i];
        if (i > 0 && curr == previus_char) {
            T[i] += T[i - 1];
        }
        if (digit == 0 && curr >= '0' && curr <= '9') {
            digit = 1;
        } else if (upper_case == 0 && curr >= 'A' && curr <= 'Z') {
            upper_case = 1;
        } else if (lower_case == 0 && curr >= 'a' && curr <= 'z') {
            lower_case = 1;
        }
        previus_char = curr;
        ++i;
    }
    int sum = upper_case + lower_case + digit;


    // aaa
    //aaabb
    //bbbbb
    //AAAbb
    int j = 0;
    while (len < 6) {
        if (sum < 3) {
            while (T[j] % 3 != 0 && j < len) j++;
            if (j < len) {
                sum++;
                T[j] = 1;
                len++;
                ++op;
            } else {
                
            }

        }
    }







    while (repeat_count > 1) {
        ++op;
        --repeat_count;
        if (len > 20) --len;
        else if (len < 6)++len;
    }

    while (len > 20) {
        ++op;
        --len;
    }

    while (len < 6) {
        ++op;
        ++len;
    }
    return op;
}

int main() {


}
