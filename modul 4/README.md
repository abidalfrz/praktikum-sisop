[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/V7fOtAk7)
|    NRP     |      Name      |
| :--------: | :------------: |
| 5025241133 | Muhammad Abid Baihaqi Al Faridzi |
| 5025241150 | Nabila Shafa Rahayu |
| 5025241153 | Kamal Zaki Adinata |

# Praktikum Modul 4 _(Module 4 Lab Work)_

</div>

### Daftar Soal _(Task List)_

- [Task 1 - FUSecure](/task-1/)

- [Task 2 - LawakFS++](/task-2/)

- [Task 3 - Drama Troll](/task-3/)

- [Task 4 - LilHabOS](/task-4/)

### Laporan Resmi Praktikum Modul 4 _(Module 4 Lab Work Report)_

Tulis laporan resmi di sini!

_Write your lab work report here!_

<<<<<<< HEAD
## Soal 4
> Lilhab sedang ditantang oleh Trabowo (orang yang sama yang dia temui di modul ke-1) untuk membuat kernel sederhana yang memiliki fitur piping menggunakan `echo`, `grep`, dan `wc`. Lilhab merasa kesulitan dan gugup karena dia pikir pekerjaannya tidak akan selesai ketika bertemu dengan deadline. Jadi, dia memutuskan untuk bertanya kepada Grok tentang tantangan tersebut dan AI tersebut memutuskan untuk mengejeknya.

![image](image.png)

> Merasa sedih, Lilhab bertekad untuk menyelesaikan pekerjaannya tepat waktu. Dia kemudian menemukan [modul](https://github.com/arsitektur-jaringan-komputer/Modul-Sisop/tree/master/Modul4) ini dan merasa sangat bersyukur. Bantu dia untuk menyelesaikan tantangan tersebut!

**Answer:**

- **Code:**
  ```
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
  ```

- **Penjelasan:**
  ```
  void printString(char *str){
      int i = 0;
      while(str[i] != '\0'){
          interrupt(0x10, (0x0E << 8) | str[i], 0, 0, 0);
          i++;
      }
  }
  ```
  - Menampilkan string ke layar karakter per karakter.
  - Menggunakan BIOS interrupt `0x10` (layar/teks), fungsi AH=0x0E (teletype output).
  - Parameter pada `interrupt`:
      - `number = 0x10`: Layanan video BIOS.
      - `AX = (0x0E << 8) | str[i]`: AH=0x0E (teletype), AL=karakter yang ingin ditampilkan.
      - `BX, CX, DX = 0`: Tidak digunakan pada mode dasar ini.
  - Pengaruh:
      - Menampilkan tiap karakter pada layar sesuai urutan string.

  ```
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
  ```
  - Membaca input keyboard hingga ENTER ditekan, menyimpan ke `buf`.
  - `interrupt(0x16, (0x00 << 8) | 0x00, 0, 0, 0)`:
      - `number = 0x16`: Layanan keyboard BIOS.
      - `AX = 0x0000`: AH=0x00 (membaca karakter dari keyboard).
      - `BX, CX, DX = 0`: Tidak digunakan.
      - Return value: karakter dari keyboard (AL).
  - Untuk output karakter:
      - Sama seperti printString: `interrupt(0x10, (0x0E << 8) | ch, 0, 0, 0);`
  - Untuk efek backspace:
      - `0x08` menampilkan backspace, `' '` menimpa karakter, lalu backspace lagi.
  - Pengaruh:
      - User bisa menginput, menghapus, dan menekan enter seperti di terminal.

  ```
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
  ```
  - Membersihkan layar dan mengatur kursor ke pojok kiri atas.
  - Pertama: `interrupt` untuk scroll up (membersihkan layar):
      - `number = 0x10`
      - `AX = (0x06 << 8) | 0x00` → AH=0x06 (scroll up window), AL=0 (baris yang di-scroll, 0 = semua).
      - `BX = 0x0F00` → BH=0x0F (warna atribut putih).
      - `CX = 0x0000` → CH=0 (row atas), CL=0 (kolom kiri).
      - `DX = (24 << 8) | 79` → DH=24 (row bawah), DL=79 (kolom kanan).
  - Kedua: `interrupt` untuk mengatur kursor:
      - `AX = (0x02 << 8) | 0x00` → AH=0x02 (set cursor), DL/DH tidak perlu diatur jika ingin ke kiri atas.
      - Lainnya 0.
  - Ketiga: `putInMemory` untuk menulis spasi dan warna putih langsung ke video memory seluruh layar:
      - `putInMemory(0xB800, i * 2, ' ');`
          - `segment = 0xB800`: segmen memori video text mode.
          - `address = i * 2`: offset karakter.
          - `character = ' '`: karakter spasi.
      - `putInMemory(0xB800, i * 2 + 1, 0x0F);`
          - `address = i * 2 + 1`: offset atribut warna.
          - `character = 0x0F`: warna putih terang.
  - Pengaruh:
      - Layar bersih, seluruh karakter menjadi spasi berwarna putih, kursor di pojok kiri atas.
=======
>>>>>>> 4e4e823 (test)
