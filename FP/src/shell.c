#include "shell.h"
#include "kernel.h"
#include "std_lib.h"
#include "filesystem.h"

void shell() {
  char buf[64];
  char cmd[64];
  char arg[2][64];

  byte cwd = FS_NODE_P_ROOT;

  while (true) {
    printString("MengOS:");
    printCWD(cwd);
    printString("$ ");
    readString(buf);
    parseCommand(buf, cmd, arg);

    if (strcmp(cmd, "cd")) cd(&cwd, arg[0]);
    else if (strcmp(cmd, "ls")) ls(cwd, arg[0]);
    else if (strcmp(cmd, "mv")) mv(cwd, arg[0], arg[1]);
    else if (strcmp(cmd, "cp")) cp(cwd, arg[0], arg[1]);
    else if (strcmp(cmd, "cat")) cat(cwd, arg[0]);
    else if (strcmp(cmd, "mkdir")) mkdir(cwd, arg[0]);
    else if (strcmp(cmd, "clear")) clearScreen();
    else printString("Invalid command\n");
  }
}

// TODO: 4. Implement printCWD function
void printCWD(byte cwd) {}

// TODO: 5. Implement parseCommand function
void parseCommand(char* buf, char* cmd, char arg[2][64]) {
  int i = 0, j = 0, len;
  cmd[0] = '\0';
  arg[0][0] = '\0';
  arg[1][0] = '\0';

  len = strlen(buf);

  while(i < len && buf[i] != ' ' && buf[i] != '\0'){
    cmd[j++] = buf[i++];
  }

  cmd[j] = '\0';

  while(i < len && buf[i] == ' ') i++;

  j = 0;
  while(i < len && buf[i] != ' ' && buf[i] != '\0'){
    arg[0][j++] = buf[i++];
  }

  arg[0][j] = '\0';

  while(i < len && buf[i] == ' ') i++;

  j = 0;
  while(i < len && buf[i] != ' ' && buf[i] != '\0'){
    arg[1][j++] = buf[i++];
  }

  arg[1][j] = '\0';

}

// TODO: 6. Implement cd function
void cd(byte* cwd, char* dirname) {
  struct node_fs nodeT;
  int i;
  readSector(&nodeT, FS_NODE_SECTOR_NUMBER);

  if(strcmp(dirname, "/")){
    *cwd = FS_NODE_P_ROOT;

  }else if(strcmp(dirname, "..")){
    if(*cwd == FS_NODE_P_ROOT){
      return;
    }

    *cwd = nodeT.nodes[*cwd].parent_index;

  }else{
    for(i = 0; i < FS_MAX_NODE; i++){
      if(strcmp(nodeT.nodes[i].node_name, dirname) && 
      nodeT.nodes[i].parent_index == *cwd && 
      nodeT.nodes[i].data_index == FS_NODE_D_DIR){
        *cwd = i;
        return;
      }
  
    }
  }


}

// TODO: 7. Implement ls function
void ls(byte cwd, char* dirname) {
  struct node_fs nodeT;
  int i;
  byte get = cwd;
  readSector(&nodeT, FS_NODE_SECTOR_NUMBER);

  if(strcmp(dirname, ".") || strcmp(dirname, "")){
    for(i = 0; i < FS_MAX_NODE; i++){
      if(nodeT.nodes[i].parent_index == cwd){
        printString(nodeT.nodes[i].node_name);
        printString("\n");
      }
    }

  }else{
    for(i = 0; i < FS_MAX_NODE; i++){
      if(strcmp(nodeT.nodes[i].node_name, dirname) && 
      nodeT.nodes[i].parent_index == cwd && 
      nodeT.nodes[i].data_index == FS_NODE_D_DIR){
        get = i;
        break;
      }
    }
  
    if(get == cwd) return;
  
    for(i = 0; i < FS_MAX_NODE; i++){
      if(nodeT.nodes[i].parent_index == get){
        printString(nodeT.nodes[i].node_name);
        printString("\n");
      }
    }
  }

}

// TODO: 8. Implement mv function
void mv(byte cwd, char* src, char* dst) {
  struct node_fs nodeT;
  int i, j = 0, idx = -1;
  byte get;
  readSector(&nodeT, FS_NODE_SECTOR_NUMBER);

  // find /
  while(dst[j] != '\0'){
    if(dst[j] == '/'){
      break;
    }
    j++;
  }

  for(i = 0; i < FS_MAX_NODE; i++){
    if(strcmp(nodeT.nodes[i].node_name, src) &&
    nodeT.nodes[i].parent_index == cwd &&
    nodeT.nodes[i].data_index != FS_NODE_D_DIR){
      idx = i;
      break;
    }
  }

  if(idx == -1) return;

  if(j == 0){
    nodeT.nodes[idx].parent_index = FS_NODE_P_ROOT;
    strcpy(nodeT.nodes[idx].node_name, dst + j + 1);
    writeSector(&nodeT, FS_NODE_SECTOR_NUMBER);

  }else if(j == 2){
    get = nodeT.nodes[cwd].parent_index;

    nodeT.nodes[idx].parent_index = get;
    strcpy(nodeT.nodes[idx].node_name, dst + j + 1);
    writeSector(&nodeT, FS_NODE_SECTOR_NUMBER);

  }else{
    get = cwd;
    char name[64];
    memcpy(name, dst, j);
    name[j] = '\0';


    for(i = 0; i < FS_MAX_NODE; i++){
      if(strcmp(nodeT.nodes[i].node_name, name) &&
      nodeT.nodes[i].parent_index == cwd &&
      nodeT.nodes[i].data_index == FS_NODE_D_DIR){
        get = i;
        break;
      }
    }

    if(get == cwd) return;

    nodeT.nodes[idx].parent_index = get;
    strcpy(nodeT.nodes[idx].node_name, dst + j + 1);
    writeSector(&nodeT, FS_NODE_SECTOR_NUMBER);
  
  }

}

// TODO: 9. Implement cp function
void cp(byte cwd, char* src, char* dst) {}

// TODO: 10. Implement cat function
void cat(byte cwd, char* filename) {}

// TODO: 11. Implement mkdir function
void mkdir(byte cwd, char* dirname) {}

