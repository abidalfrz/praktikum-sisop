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
  readSector(&(nodeT.nodes[0]), FS_NODE_SECTOR_NUMBER);        
  readSector(&(nodeT.nodes[32]), FS_NODE_SECTOR_NUMBER + 1);

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
  readSector(&(nodeT.nodes[0]), FS_NODE_SECTOR_NUMBER);        
  readSector(&(nodeT.nodes[32]), FS_NODE_SECTOR_NUMBER + 1);

  if(strcmp(dirname, ".") || strcmp(dirname, "") || dirname[0] == '\0'){
    for(i = 0; i < FS_MAX_NODE; i++){
      if(nodeT.nodes[i].parent_index == cwd &&
        nodeT.nodes[i].node_name[0] != '\0'){
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
      if(nodeT.nodes[i].parent_index == get &&
        nodeT.nodes[i].node_name[0] != '\0'){
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
  int slash = 0;
  readSector(&(nodeT.nodes[0]), FS_NODE_SECTOR_NUMBER);        
  readSector(&(nodeT.nodes[32]), FS_NODE_SECTOR_NUMBER + 1);

  // find /
  while(dst[j] != '\0'){
    if(dst[j] == '/'){
      slash = 1;
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
  
  if(slash == 1){
    if(j == 0){
      nodeT.nodes[idx].parent_index = FS_NODE_P_ROOT;
      strcpy(nodeT.nodes[idx].node_name, dst + j + 1);
      writeSector(&(nodeT.nodes[0]),FS_NODE_SECTOR_NUMBER);
      writeSector(&(nodeT.nodes[32]),FS_NODE_SECTOR_NUMBER+1);

    }else if(j == 1){
      // implement if ./dir1
      get = cwd;
      memcpy(name, dst + j + 1, strlen(dst) - j - 1);
      name[strlen(dst) - j - 1] = '\0';

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
      writeSector(&(nodeT.nodes[0]),FS_NODE_SECTOR_NUMBER);
      writeSector(&(nodeT.nodes[32]),FS_NODE_SECTOR_NUMBER+1);

    }else if(j == 2){
      get = nodeT.nodes[cwd].parent_index;

      nodeT.nodes[idx].parent_index = get;
      strcpy(nodeT.nodes[idx].node_name, dst + j + 1);
      writeSector(&(nodeT.nodes[0]),FS_NODE_SECTOR_NUMBER);
      writeSector(&(nodeT.nodes[32]),FS_NODE_SECTOR_NUMBER+1);

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
      writeSector(&(nodeT.nodes[0]),FS_NODE_SECTOR_NUMBER);
      writeSector(&(nodeT.nodes[32]),FS_NODE_SECTOR_NUMBER+1);
    
    }
  }else{
    // change name file
    // check if dst exists
    for(i = 0; i < FS_MAX_NODE; i++){
      if(strcmp(nodeT.nodes[i].node_name, dst) &&
      nodeT.nodes[i].parent_index == cwd){
        return; // dst already exists
      }
    }
    
    strcpy(nodeT.nodes[idx].node_name, dst);
    writeSector(&(nodeT.nodes[0]), FS_NODE_SECTOR_NUMBER);
    writeSector(&(nodeT.nodes[32]), FS_NODE_SECTOR_NUMBER + 1);
  }

}

// TODO: 9. Implement cp function
void cp(byte cwd, char* src, char* dst) {
    struct map_fs map_fs_buf;
    struct node_fs node_fs_buf;
    struct data_fs data_fs_buf;
    struct file_metadata src_md;
    struct node_item now_node;
    char dst_buf[64];
    char dst_dir[64];
    char dst_fname[64];
    byte dst_idx = cwd;
    int i, j, found = 0;
    int empty_node, empty_data;
    int sectors, written;
    enum fs_return status;

    readSector(&map_fs_buf, FS_MAP_SECTOR_NUMBER);
    readSector(&(node_fs_buf.nodes[0]), FS_NODE_SECTOR_NUMBER);
    readSector(&(node_fs_buf.nodes[32]), FS_NODE_SECTOR_NUMBER + 1);
    readSector(&data_fs_buf, FS_DATA_SECTOR_NUMBER);

    found = 0;
    for (i = 0; i < FS_MAX_NODE; i++) {
        if (strcmp(node_fs_buf.nodes[i].node_name, src) &&
            node_fs_buf.nodes[i].parent_index == cwd) {
            now_node = node_fs_buf.nodes[i];
            found = 1;
            break;
        }
    }

    if (!found) {
        return;
    }

    if (now_node.data_index == FS_NODE_D_DIR) {
        return;
    }

    src_md.parent_index = cwd;
    strcpy(src_md.node_name, src);
    fsRead(&src_md, &status);

    if (status != FS_SUCCESS) {
        printString("Error\n");
        return;
    }

    strcpy(dst_buf, dst);

    if (dst_buf[0] == '/' && dst_buf[1] != '\0') {
        dst_idx = FS_NODE_P_ROOT;
        strcpy(dst_fname, dst_buf + 1);
    } else if (dst_buf[0] == '.' && dst_buf[1] == '.' && dst_buf[2] == '/') {
        dst_idx = node_fs_buf.nodes[cwd].parent_index;
        strcpy(dst_fname, dst_buf + 3);
    } else {
        int slash_idx = -1;
        for (i = 0; dst_buf[i] != '\0'; i++) {
            if (dst_buf[i] == '/') {
                slash_idx = i;
                break;
            }
        }

        if (slash_idx != -1) {
            for (j = 0; j < slash_idx; j++) dst_dir[j] = dst_buf[j];
            dst_dir[slash_idx] = '\0';
            strcpy(dst_fname, dst_buf + slash_idx + 1);

            found = 0;
            for (i = 0; i < FS_MAX_NODE; i++) {
                if (strcmp(node_fs_buf.nodes[i].node_name, dst_dir) &&
                    node_fs_buf.nodes[i].parent_index == cwd &&
                    node_fs_buf.nodes[i].data_index == FS_NODE_D_DIR) {
                    dst_idx = i;
                    found = 1;
                    break;
                }
            }

            if (!found) {
                return;
            }
        } else {
            strcpy(dst_fname, dst_buf);
        }
    }

    for (empty_node = 0; empty_node < FS_MAX_NODE; empty_node++) {
        if (node_fs_buf.nodes[empty_node].node_name[0] == '\0') break;
    }
    if (empty_node == FS_MAX_NODE) {
        return;
    }

    for (empty_data = 0; empty_data < FS_MAX_DATA; empty_data++) {
        if (data_fs_buf.datas[empty_data].sectors[0] == 0x00) break;
    }
    if (empty_data == FS_MAX_DATA) {
        return;
    }

    strcpy(node_fs_buf.nodes[empty_node].node_name, dst_fname);
    node_fs_buf.nodes[empty_node].parent_index = dst_idx;
    node_fs_buf.nodes[empty_node].data_index = (byte)empty_data;

    sectors = (src_md.filesize + SECTOR_SIZE - 1) / SECTOR_SIZE;
    written = 0;
    for (i = 16; i < SECTOR_SIZE && written < sectors; i++) {
        if (!map_fs_buf.is_used[i]) {
            map_fs_buf.is_used[i] = true;
            data_fs_buf.datas[empty_data].sectors[written] = (byte)i;
            writeSector(src_md.buffer + written * SECTOR_SIZE, i);
            written++;
        }
    }

    writeSector(&map_fs_buf,             FS_MAP_SECTOR_NUMBER);
    writeSector(node_fs_buf.nodes,       FS_NODE_SECTOR_NUMBER);
    writeSector(node_fs_buf.nodes + 32,  FS_NODE_SECTOR_NUMBER + 1);
    writeSector(&data_fs_buf,            FS_DATA_SECTOR_NUMBER);

    printString("File berhasil disalin\n");
}


// TODO: 10. Implement cat function
void cat(byte cwd, char* filename) {
  struct node_fs nodeT;
  struct file_metadata meta;
  enum fs_return status;
  char c[2];
  int i, j;

  readSector(&nodeT, FS_NODE_SECTOR_NUMBER);

  for (i = 0; i < FS_MAX_NODE; i++) {
    if (
      strcmp(nodeT.nodes[i].node_name, filename) &&
      nodeT.nodes[i].parent_index == cwd
    ) {
      if (nodeT.nodes[i].data_index == FS_NODE_D_DIR) {
        printString("cat: tidak bisa membaca direktori\n");
        return;
      } else {
        meta.parent_index = cwd;
        
        strcpy(meta.node_name, filename);
        fsRead(&meta, &status);

        if (status == FS_SUCCESS) {
          for (j = 0; j < meta.filesize; j++) {
            c[0] = meta.buffer[j];
            c[1] = '\0';
            printString(c);
          }
          printString("\n");
        } else {
          printString("cat: gagal membaca file\n");
        }

        return;
      }
    }
  }
  printString("cat: file tidak ditemukan\n");
}



// TODO: 11. Implement mkdir function
void mkdir(byte cwd, char* dirname) {
  struct node_fs nodeT;
  struct node_item new_node;
  int i;
  int free_node_idx = -1;

  readSector(&nodeT, FS_NODE_SECTOR_NUMBER);
  readSector(((byte*)&nodeT) + SECTOR_SIZE, FS_NODE_SECTOR_NUMBER + 1);

  for (i = 0; i < FS_MAX_NODE; i++) {
      if (nodeT.nodes[i].parent_index == cwd &&
          strcmp(nodeT.nodes[i].node_name, dirname)) {
          return;
      }
  }

  for (i = 0; i < FS_MAX_NODE; i++) {
      if (nodeT.nodes[i].node_name[0] == '\0') {
          free_node_idx = i;
          break;
      }
  }

  if (free_node_idx == -1) {
      return;
  }

  new_node.parent_index = cwd;
  new_node.data_index = FS_NODE_D_DIR;
  memset(new_node.node_name, 0, MAX_FILENAME);
  strncpy(new_node.node_name, dirname, MAX_FILENAME);

  nodeT.nodes[free_node_idx] = new_node;

  writeSector(&nodeT, FS_NODE_SECTOR_NUMBER);
  writeSector(((byte*)&nodeT) + SECTOR_SIZE, FS_NODE_SECTOR_NUMBER + 1);

  printString("Direktori berhasil dibuat\n");
}


