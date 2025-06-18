#include "std_lib.h"

unsigned int strlen(char* str){
    int len;
    len = 0;
    while(str[len] != '\0') len++;
    return len;
}

int div(int a, int b){
    int neg, total;
    if(b == 0) return -999;

    neg = 0;
    if(a < 0 && b < 0){
        a *= -1;
        b *= -1;
    }else if(a < 0){
        neg = 1;
        a *= -1;
    }else if(b < 0){
        neg = 1;
        b *= -1;
    }

    total = 0;
    while(a - b >= 0){
        a -= b;
        total += 1;
    }

    if(neg) total *= -1;
    return total;
}

int mod(int a, int b){
    int neg, res;
    if(b == 0) return -999;

    neg = 0;
    if(a < 0 && b < 0){
        neg = 1;
        a *= -1;
        b *= -1;
    }else if(a < 0){
        neg = 1;
        a *= -1;
    }else if(b < 0){
        b *= -1;
    }

    res = a - b * div(a,b);

    if(neg) res *= -1;
    return res;
}

void memcpy(byte* src, byte* dst, unsigned int size){
    unsigned int i;
    for(i = 0; i < size; i++){
        dst[i] = src[i];
    }
}

bool strcmp(char* str1, char* str2){
    int length, i;
    if(strlen(str1) != strlen(str2)) return 0;

    length = strlen(str1);
    for(i = 0; i < length; i++){
        if(str1[i] != str2[i]) return 0;
    }

    return 1;
}

void strcpy(char* src, char* dst){
    int i;
    i = 0;
    while(src[i] != '\0'){
        dst[i] = src[i];
        i+=1;
    }
    dst[i] = '\0';
}

void clear(byte* buf, unsigned int size){
    unsigned int i;
    for(i = 0; i < size; i++){
        buf[i] = '\0';
    }
}
