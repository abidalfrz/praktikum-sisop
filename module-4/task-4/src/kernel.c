#include "kernel.h"

// Prototypes for local static functions
int getCommands(char *buf, char commands[][128]);
int findPattern(char *buff, char *patt);
void toChar(int num, char *val);
int prefix(char *buf, char *comm);

int main() {
    char res[128];
    char commands[8][128];
    char buf[128];
    int i, count, x;

    clearScreen();
    printString("LilHabOS - C09\n");

    while(true){
        printString("$> ");
        readString(buf);
        printString("\n");

        if (strlen(buf) > 0) {
            count = getCommands(buf, commands);
            for(i = 0; i < count; i++){
                if(prefix(commands[i], "echo")){
                    strcpy(commands[i] + 5, res);
                }else if(prefix(commands[i], "grep")){
                    char *pattern = commands[i] + 5;

                    if(res[0] == '\0'){
                        break;
                    }

                    if(findPattern(res, pattern) == -1){
                        res[0] = '\0';
                        break;
                    }else{
                        clear(res, strlen(res));
                        strcpy(pattern, res);
                    }
                }else if(prefix(commands[i], "wc")){
                    int row, length, words;
                    char val[10];
                    length = strlen(res);
                    if(res[0] == '\0'){
                        words = 0;
                        row = 0;
                    }else{
                        int j;
                        row = 1;
                        words = 1;
                        for(j = 0; j < length; j++){
                            if(res[j] == '\n') row++;
                            if(res[j] == ' ' && res[j+1] != '\0' && res[j+1] != ' ') words++; 
                        }
                    }

                    toChar(row, val);    printString("\t"); printString(val);
                    toChar(words, val);  printString("\t"); printString(val);
                    toChar(length, val); printString("\t"); printString(val);
                    printString("\n");

                }
            }

            if(strlen(res) > 0 && !prefix(commands[count - 1], "wc")){
                printString(res);
                printString("\n");
            }

            clear(buf, 128);
            clear(res, 128);
            for(i=0; i < count;i++){
                clear(commands[i], 128);
            }
        }
    }
    return 0;
}

void printString(char *str){
    int i = 0;
    while(str[i] != '\0'){
        interrupt(0x10, (0x0E << 8) | str[i], 0, 0, 0);
        i++;
    }
}

void readString(char *buf){
    int idx = 0;
    char ch;
    while(true){
        ch = interrupt(0x16, (0x00 << 8) | 0x00, 0, 0, 0) & 0xFF;
        if(ch == 0x0D){ // ENTER
            buf[idx] = '\0';
            interrupt(0x10, (0x0E << 8) | '\n', 0, 0, 0);
            interrupt(0x10, (0x0E << 8) | '\r', 0, 0, 0);
            break;
        }else if(ch == 0x08){ // BACKSPACE
            if(idx > 0){
                idx--;
                interrupt(0x10, (0x0E << 8) | 0x08, 0, 0, 0);
                interrupt(0x10, (0x0E << 8) | ' ', 0, 0, 0);
                interrupt(0x10, (0x0E << 8) | 0x08, 0, 0, 0);
            }
        }else{
            buf[idx++] = ch;
            interrupt(0x10, (0x0E << 8) | ch, 0, 0, 0);
        }
    }
    buf[idx] = '\0';
}

void clearScreen(void){
    unsigned char *vid;
    int i;

    interrupt(0x10, (0x06 << 8) | 0x00, 0x0F00, 0x0000, (24 << 8) | 79);

    interrupt(0x10, (0x02 << 8) | 0x00, 0, 0, 0);

    for(i = 0; i < 80 * 25; i++){
        putInMemory(0xB800, i * 2, ' ');
        putInMemory(0xB800, i * 2 + 1, 0x0F);
    }
}

int prefix(char *buf, char *comms){
    int i, length;
    length = strlen(comms);
    for(i = 0; i < length; i++){
        if(buf[i] != comms[i]) return 0;
    }
    return 1;
}

int getCommands(char *buf, char commands[][128]){
    int i = 0, j = 0, k = 0;
    int length;
    while(true){
        if(buf[i] == '|' || buf[i] == '\0'){
            commands[j][k] = '\0';
            
            length = strlen(commands[j]);
            if(commands[j][length - 1] == ' ') commands[j][length - 1] = '\0';
            
            j++;
            k = 0;

            if(buf[i] == '|'){
                i++;
                while(buf[i] == ' ') i++; 
                continue;
            }else{
                break;
            }
        }

        commands[j][k++] = buf[i++];
    }


    return j;
}


int findPattern(char *buf, char *patt){
    int i, j;
    int len_buf = strlen(buf);
    int len_patt = strlen(patt);

    if(len_patt == 0) return 0;

    for(i = 0; i <= len_buf - len_patt; i++){
        for(j = 0; j < len_patt; j++){
            if(buf[i + j] != patt[j]){
                break;
            }
        }
        if(j == len_patt){
            return i;
        }
    }
    return -1;
}

void toChar(int num, char *val){
    int i = 0, j;
    if(num == 0){
        val[i++] = '0';
        val[i] = '\0';
        return;
    }else if(num > 0){
        while(num > 0){
            val[i++] = mod(num, 10) + '0';
            num = div(num, 10);
        }
    }
    val[i] = '\0';
    for(j = 0; j < div(i, 2); j++){
        char tmp = val[j];
        val[j] = val[i - j - 1];
        val[i - j - 1] = tmp;
    }
}
