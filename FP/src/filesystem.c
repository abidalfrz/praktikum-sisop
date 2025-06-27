#include "kernel.h"
#include "std_lib.h"
#include "filesystem.h"

void fsInit() {
  struct map_fs map_fs_buf;
  int i = 0;

  readSector(&map_fs_buf, FS_MAP_SECTOR_NUMBER);
  for (i = 0; i < 16; i++) map_fs_buf.is_used[i] = true;
  for (i = 256; i < 512; i++) map_fs_buf.is_used[i] = true;
  writeSector(&map_fs_buf, FS_MAP_SECTOR_NUMBER);
}

// TODO: 2. Implement fsRead function
void fsRead(struct file_metadata* metadata, enum fs_return* status) {
  struct node_fs node_fs_buf;
  struct data_fs data_fs_buf;

  /**
   * add local variable here
   * ...
  */

  int found = -1;
  byte sector;
  int i;

  readSector(&data_fs_buf, FS_DATA_SECTOR_NUMBER);
  readSector(&(node_fs_buf.nodes[0]), FS_NODE_SECTOR_NUMBER);
  readSector(&(node_fs_buf.nodes[32]), FS_NODE_SECTOR_NUMBER);

  /**
   *  add your code here
   * ...
  */
  
  // iterasi buat nyari node yg sama kek metadata->node_name dan parent index yg sama kek metadata->parent_index
  for (i = 0; i < FS_MAX_NODE; i++) {
    if (node_fs_buf.nodes[i].node_name[0] != '\0' &&
        strcmp(node_fs_buf.nodes[i].node_name, metadata->node_name) == 0 &&
        node_fs_buf.nodes[i].parent_index == metadata->parent_index) {
      found = i;
      break;
    }
  }

  if (found == -1) { // klo node nya gk ketemu, set status not found
    *status = FS_R_NODE_NOT_FOUND;
    return;
  }
  
  if (node_fs_buf.nodes[found].data_index == FS_NODE_D_DIR) {
    *status = FS_R_TYPE_IS_DIRECTORY; // klo ketemu nya direktori, set status FS_R_TYPE_IS_DIRECTORY
  } else { // node yg ditemuin file
    metadata->filesize = 0;
    for (i = 0; i < FS_MAX_NODE; i++) {
      sector = data_fs_buf.datas[node_fs_buf.nodes[found].data_index].sectors[i];
      if (sector == 0x00) {
        break;
      }
      readSector(metadata->buffer + i * SECTOR_SIZE, sector);
      metadata->filesize += SECTOR_SIZE;
    }
    *status = FS_R_SUCCESS;
  }

}

// TODO: 3. Implement fsWrite function
void fsWrite(struct file_metadata* metadata, enum fs_return* status) {
  struct map_fs map_fs_buf;
  struct node_fs node_fs_buf;
  struct data_fs data_fs_buf;

  /**
   * add local variable here
   * ...
  */

  int i,j=0; 
  int empty_node = -1;
  int empty_data = -1;
  int free_block = 0;
  int block_need;

  readSector(&data_fs_buf, FS_DATA_SECTOR_NUMBER);
  readSector(&map_fs_buf, FS_MAP_SECTOR_NUMBER);
  readSector(&(node_fs_buf.nodes[0]), FS_NODE_SECTOR_NUMBER);
  readSector(&(node_fs_buf.nodes[32]), FS_NODE_SECTOR_NUMBER);

  /**
   *  add your code here
   * ...
  */

  for (i = 0; i < FS_MAX_NODE; i++) {
    if (node_fs_buf.nodes[i].node_name[0] != '\0' &&
        strcmp(node_fs_buf.nodes[i].node_name, metadata->node_name) == 0 &&
        node_fs_buf.nodes[i].parent_index == metadata->parent_index) {
      *status = FS_W_NODE_ALREADY_EXISTS;
      return;
    }
  }
  

  // nyari node kosong
  for (i = 0; i < FS_MAX_NODE; i++) {
    if (node_fs_buf.nodes[i].node_name[0] == '\0') {
      empty_node = i;
      break;
    }
  }

  if(empty_node==-1){
    *status = FS_W_NO_FREE_NODE;
    return;
  }

  // nyari data kosong
  for (i=0;i<FS_MAX_DATA;i++) {
    if (data_fs_buf.datas[i].sectors[0] == 0x00) {
      empty_data = i;
      break;
    }
  }

  if(empty_data==-1){
    *status = FS_W_NO_FREE_DATA;
    return;
  }

  // nyari block kosong
  for (i=0;i<FS_MAX_SECTOR;i++) {
      if (!map_fs_buf.is_used[i]) {
          free_block++;
      }
  }

  block_need = metadata->filesize / SECTOR_SIZE;
  if (free_block < block_need) {
      *status = FS_W_NOT_ENOUGH_SPACE;
      return;
  }

  strcpy(node_fs_buf.nodes[empty_node].node_name, metadata->node_name);
  node_fs_buf.nodes[empty_node].parent_index = metadata->parent_index;
  node_fs_buf.nodes[empty_node].data_index = empty_data;

  for(i=0;i<SECTOR_SIZE && j < block_need ; i++){
    if(map_fs_buf.is_used[i] == 0x00){
      data_fs_buf.datas[empty_data].sectors[j] = i;
      writeSector(metadata->buffer + i * SECTOR_SIZE);
      j++;
    }
  }

  writeSector(&data_fs_buf, FS_DATA_SECTOR_NUMBER);
  writeSector(&map_fs_buf, FS_MAP_SECTOR_NUMBER);
  writeSector(&(node_fs_buf.nodes[0]), FS_NODE_SECTOR_NUMBER);
  writeSector(&(node_fs_buf.nodes[32]), FS_NODE_SECTOR_NUMBER);

  *status = FS_W_SUCCESS;
}
