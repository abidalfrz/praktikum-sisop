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
  

  int i, j;
  int get = 0; 
  int node_idx = -1; 
  byte data_idx;


  readSector(&(node_fs_buf.nodes[0]), FS_NODE_SECTOR_NUMBER);        
  readSector(&(node_fs_buf.nodes[32]), FS_NODE_SECTOR_NUMBER + 1);   
  readSector(&data_fs_buf, FS_DATA_SECTOR_NUMBER);                   

  for (i = 0; i < FS_MAX_NODE; i++) {
    struct node_item* node = &node_fs_buf.nodes[i];
    if (node->parent_index == metadata->parent_index &&
        strncmp(node->node_name, metadata->node_name, MAX_FILENAME) == true) {
      get = 1;
      node_idx = i;
      break;
    }
  }

  if (!get) {
    *status = FS_R_NODE_NOT_FOUND;
    return;
  }

  if (node_fs_buf.nodes[node_idx].data_index == FS_NODE_D_DIR) {
    *status = FS_R_TYPE_IS_DIRECTORY;
    return;
  }

  metadata->filesize = 0;
  data_idx = node_fs_buf.nodes[node_idx].data_index;

  for (i = 0; i < FS_MAX_SECTOR; i++) {
    byte sector_number = data_fs_buf.datas[data_idx].sectors[i];
    if (sector_number == 0x00) break;
    readSector(metadata->buffer + i * SECTOR_SIZE, sector_number);
    metadata->filesize += SECTOR_SIZE;
  }

  *status = FS_SUCCESS;
}


// TODO: 3. Implement fsWrite function
void fsWrite(struct file_metadata* file, enum fs_return* result) {
  struct map_fs map;
  struct node_fs node_fs_buf;
  struct data_fs datas;
  int i, j;
  int node_slot = -1, data_slot = -1, free_blocks = 0;
  int sector_needed;

  readSector(&map, FS_MAP_SECTOR_NUMBER);
  readSector(&node_fs_buf.nodes[0], FS_NODE_SECTOR_NUMBER);
  readSector(&node_fs_buf.nodes[32], FS_NODE_SECTOR_NUMBER + 1);
  readSector(&datas, FS_DATA_SECTOR_NUMBER);

  // Cek duplikasi nama file
  for (i = 0; i < FS_MAX_NODE; i++) {
    if (node_fs_buf.nodes[i].parent_index == file->parent_index &&
        strncmp(node_fs_buf.nodes[i].node_name, file->node_name, MAX_FILENAME) == 0) {
      *result = FS_W_NODE_ALREADY_EXISTS;
      return;
    }
  }

  // Temukan slot kosong untuk node
  for (i = 0; i < FS_MAX_NODE && node_slot == -1; i++) {
    if (node_fs_buf.nodes[i].node_name[0] == '\0') node_slot = i;
  }
  if (node_slot == -1) {
    *result = FS_W_NO_FREE_NODE;
    return;
  }

  // Temukan slot data kosong
  for (i = 0; i < FS_MAX_DATA && data_slot == -1; i++) {
    if (datas.datas[i].sectors[0] == 0x00) data_slot = i;
  }
  if (data_slot == -1) {
    *result = FS_W_NO_FREE_DATA;
    return;
  }

  // Hitung kebutuhan blok dan cek blok kosong
  sector_needed = (file->filesize + SECTOR_SIZE - 1) / SECTOR_SIZE;
  for (i = 16; i < 256; i++) if (!map.is_used[i]) free_blocks++;
  if (free_blocks < sector_needed) {
    *result = FS_W_NOT_ENOUGH_SPACE;
    return;
  }

  // Tulis node
  strcpy(node_fs_buf.nodes[node_slot].node_name, file->node_name);
  node_fs_buf.nodes[node_slot].parent_index = file->parent_index;
  node_fs_buf.nodes[node_slot].data_index = (file->filesize == 0) ? FS_NODE_D_DIR : data_slot;

  // Tulis data jika file
  if (file->filesize > 0) {
    j = 0;
    for (i = 16; j < sector_needed && i < 256; i++) {
      if (!map.is_used[i]) {
        map.is_used[i] = true;
        datas.datas[data_slot].sectors[j] = (byte)i;
        writeSector(file->buffer + j * SECTOR_SIZE, i);
        j++;
      }
    }
  }

  // Simpan kembali ke sektor
  writeSector(&map, FS_MAP_SECTOR_NUMBER);
  writeSector(&node_fs_buf.nodes[0], FS_NODE_SECTOR_NUMBER);
  writeSector(&node_fs_buf.nodes[32], FS_NODE_SECTOR_NUMBER + 1);
  writeSector(&datas, FS_DATA_SECTOR_NUMBER);

  *result = FS_W_SUCCESS;
}
