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
void printCWD(byte cwd) {
  struct node_fs node_fs_buf;
  byte stack[FS_MAX_NODE];
  byte current;
  int depth=0;

  readSector(&(node_fs_buf.nodes[0]), FS_NODE_SECTOR_NUMBER);
  readSector(&(node_fs_buf.nodes[32]), FS_NODE_SECTOR_NUMBER);

  if(cwd == FS_NODE_P_ROOT){
    printString("/"); // klo dia root lgsg ngeprint / dan return
    return;
  }
  
  current = cwd;

  while (current != FS_NODE_P_ROOT) { /// iterasi selama current ini ga nyentuh root
      stack[depth] = current;
      depth++;
      current = node_fs_buf.nodes[current].parent_index;
  }

  depth-=1; // karena stack dimulai dari 0
  while(depth >= 0){
    printString("/");
    printString(node_fs_buf.nodes[stack[depth]].node_name);
    depth--;
  }
}

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
  char name[64];
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
void cp(byte cwd, char* src, char* dst) {
  struct file_metadata src_meta, dst_meta;
  enum fs_return status;

  src_meta.parent_index = cwd;
  strcpy(src_meta.node_name, src);
  fsRead(&src_meta, &status);
  if (status != FS_R_SUCCESS) {
    printString("cp: file yang akan dicopy tidak ditemukan\n");
    return;
  }

  dst_meta.parent_index = cwd;
  strcpy(dst_meta.node_name, dst);
  dst_meta.filesize = src_meta.filesize;
  memcpy(dst_meta.buffer, src_meta.buffer, src_meta.filesize);

  fsWrite(&dst_meta, &status);
  if (status == FS_SUCCESS) {
      printString("cp: berhasil menyalin\n");
  } else if (status == FS_W_NODE_ALREADY_EXISTS) {
    printString("cp: nama file sudah ada\n");
  } else if (status == FS_W_NOT_ENOUGH_SPACE) {
    printString("cp: ruang tidak cukup\n");
  } else {
    printString("cp: gagal menyalin file\n");
  }

}


// TODO: 10. Implement cat function
void cat(byte cwd, char* filename) {
  struct file_metadata meta;
  enum fs_return status;
  char c[2];
  int i;

  meta.parent_index = cwd;
  strcpy(meta.node_name, filename);
  fsRead(&meta, &status);

  if (status == FS_SUCCESS) {
    for (i = 0; i < meta.filesize; i++) {
      c[0] = meta.buffer[i];
      c[1] = '\0'; 
      printString(c);
    }
    printString("\n");
  } else if (status == FS_R_NODE_NOT_FOUND) {
    printString("cat: file tidak ditemukan\n");
  } else if (status == FS_R_TYPE_IS_DIRECTORY) {
    printString("cat: tidak bisa membaca direktori\n");
  } else {
    printString("cat: terjadi error misteriuz\n");
  }
}

// TODO: 11. Implement mkdir function
void mkdir(byte cwd, char* dirname) {
  struct file_metadata meta;
  enum fs_return status;

  meta.parent_index = cwd;
  strcpy(meta.node_name, dirname);
  meta.filesize = 0; // Direktori
  memset(meta.buffer, 0, sizeof(meta.buffer));

  fsWrite(&meta, &status);

  if (status == FS_SUCCESS) {
    printString("mkdir: direktori berhasil dibuat\n");
  } else if (status == FS_W_NODE_ALREADY_EXISTS) {
    printString("mkdir: nama sudah ada\n");
  } else if (status == FS_W_NOT_ENOUGH_SPACE) {
    printString("mkdir: tidak cukup ruang\n");
  } else if (status == FS_W_NO_FREE_NODE) {
    printString("mkdir: tidak ada node kosong\n");
  } else if (status == FS_W_INVALID_DIRECTORY) {
    printString("mkdir: direktori tidak valid\n");
  } else {
    printString("mkdir: terjadi error misteriuz\n");
  }
}

