#define _OPEN_SYS_ITOA_EXT
#include "Data2Hex.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* LongToHex(long);
char* StringToHex(char*);

JNIEXPORT jstring JNICALL Java_Data2Hex_data2Hex
    (JNIEnv * env, jobject obj, jstring j_d1, jlong j_d2, jstring j_d3){

    const char *c_d1 = env->GetStringUTFChars(j_d1, 0);
    const char *c_d3 = env->GetStringUTFChars(j_d3, 0);
    int d1Len = strlen(c_d1) + 1;
    int d3Len = strlen(c_d3) + 1;
    char *d1 = (char *) malloc(d1Len * 8);
    char *d3 = (char *) malloc(d3Len * 8);
    int resultSize = (d1Len + d3Len + sizeof(j_d2)) * 8;
    char *result = (char *) malloc(resultSize);
    result[0] = '\0';
    strcpy(d1, c_d1);
    strcpy(d3, c_d3);

    strcat(result, StringToHex(d1));
    strcat(result, LongToHex((long) j_d2));
    strcat(result, StringToHex(d3));
    result[resultSize] = '\0';

    env->ReleaseStringUTFChars(j_d1, c_d1);
    env->ReleaseStringUTFChars(j_d3, c_d3);

    free(d1);
    free(d3);

    return env->NewStringUTF(result);

}

char* LongToHex(long input) {

    char *result = (char *) malloc(sizeof(input)*8);
    char *buffer = (char *) malloc(sizeof(long)+1);
    int i = 0;
    result[0] = '\0';
    buffer[0] = '\0';
    for(i=28;i>=0;i-=4) {
        long data = input & 0xF << i;
        sprintf(buffer, "%X", (int)(data >> i));
        strcat(result, buffer);
    }

    return result;

}

char* StringToHex(char* input) {

    char *p = input;
    char *result = (char *) malloc(sizeof(input)*8);
    char *buffer = (char *) malloc(sizeof(int)+1);
    int i = 0;
    result[0] = '\0';
    for(;*p != 0;++p){
        for(i=4;i>=0;i-=4){
            int data = (int)(*p & 0xF << i);
            sprintf(buffer, "%X", data >> i);
            strcat(result, buffer);
        }
    }

    return result;
}
