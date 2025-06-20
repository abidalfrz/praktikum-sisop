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

## Soal 4
Lilhab sedang ditantang oleh Trabowo (orang yang sama yang dia temui di modul ke-1) untuk membuat kernel sederhana yang memiliki fitur piping menggunakan `echo`, `grep`, dan `wc`. Lilhab merasa kesulitan dan gugup karena dia pikir pekerjaannya tidak akan selesai ketika bertemu dengan deadline. Jadi, dia memutuskan untuk bertanya kepada Grok tentang tantangan tersebut dan AI tersebut memutuskan untuk mengejeknya.

![image](image.png)

Merasa sedih, Lilhab bertekad untuk menyelesaikan pekerjaannya tepat waktu. Dia kemudian menemukan [modul](https://github.com/arsitektur-jaringan-komputer/Modul-Sisop/tree/master/Modul4) ini dan merasa sangat bersyukur. Bantu dia untuk menyelesaikan tantangan tersebut!

> a. Implementasikan fungsi printString, readString, dan clearScreen di kernel.c yang akan menampilkan dan membaca string di layar.
printString: Menampilkan string yang diakhiri null menggunakan int 10h dengan AH=0x0E.
readString: Membaca karakter dari keyboard menggunakan int 16h dengan AH=0x00 sampai Enter ditekan. Termasuk penanganan Backspace dasar.
clearScreen: Membersihkan layar dan mengatur kursor ke pojok kiri atas (0, 0) menggunakan int 10h dengan AH=0x06 dan AH=0x02. Buffer video untuk warna karakter akan diubah menjadi putih.

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
          if(ch == 0x0D){
              buf[idx] = '\0';
              interrupt(0x10, (0x0E << 8) | '\n', 0, 0, 0);
              interrupt(0x10, (0x0E << 8) | '\r', 0, 0, 0);
              break;
          }else if(ch == 0x08){
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
  Menampilkan string ke layar karakter per karakter menggunakan loop dan interrupt.
  Menggunakan loop untuk input dari user dan berhenti ketika user menekan `ENTER`.
  
  ```
  interrupt(0x10, (0x0E << 8) | str[i], 0, 0, 0)
  ```
    - `0x10` adalah integer interupsi BIOS untuk layar (video service).
    - `AH = 0x0E`: Subfungsi "Teletype Output", Menampilkan satu karakter ke layar menggunakan BIOS teletype output. BIOS akan mencetak karakter ke layar dan menggeser           kursor satu posisi ke kanan.
    - `AL = str[i]`: karakter yang akan ditampilkan.
    - Set `BX`, `CX`, `DX` sebagai 0 untuk default.
  
  ```
  void readString(char *buf){
      int idx = 0;
      char ch;
      while(true){
          ch = interrupt(0x16, (0x00 << 8) | 0x00, 0, 0, 0) & 0xFF;
          if(ch == 0x0D){
              buf[idx] = '\0';
              interrupt(0x10, (0x0E << 8) | '\n', 0, 0, 0);
              interrupt(0x10, (0x0E << 8) | '\r', 0, 0, 0);
              break;
          }else if(ch == 0x08){
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
  Membaca input keyboard hingga ENTER ditekan, menyimpan hasil input ke `buf`.
  ```
  ch = interrupt(0x16, (0x00 << 8) | 0x00, 0, 0, 0) & 0xFF
  ```
    - `0x16` adalah integer interupsi BIOS untuk keyboard.
    - `AH = 0x00`: subfungsi `Read Keyboard Input`, akan menunggu sampai user menekan tombol, lalu mengembalikan ASCII di AL.
    - `AX = 0x0000`: AH=0x00, membaca karakter dari keyboard.
    - `ch` digunakan untuk menyimpan karakter input dari keyboard.
    - Set `BX`, `CX`, `DX` sebagai 0 untuk default.
    - `& 0xFF` mengambil byte rendah (AL) dari hasil kembalian.

  ```
  if(ch == 0x0D){
    buf[idx] = '\0';
    interrupt(0x10, (0x0E << 8) | '\n', 0, 0, 0);
    interrupt(0x10, (0x0E << 8) | '\r', 0, 0, 0);
    break;
  }
  ```
  Case ketika user menekan `ENTER`.
  - `0x0D`: Kode ASCII untuk `ENTER`.
  - Menambahkan`\0` ke akhir `buf` sebagai penanda akhir input (string).
  - interrupt pertama `interrupt(0x10, (0x0E << 8) | '\n', 0, 0, 0)` untuk mengeksekusi `\n` di kernel (pindah ke baris setelahnya).
  - interrupt kedua `interrupt(0x10, (0x0E << 8) | '\r', 0, 0, 0)` untuk mengeksekusi `\r` (pindah ke awal baris/kolom 0).
  - `break` yang menandakan keluar dari loop dan input selesai.
 
  ```
  else if(ch == 0x08){
      if(idx > 0){
          idx--;
          interrupt(0x10, (0x0E << 8) | 0x08, 0, 0, 0);
          interrupt(0x10, (0x0E << 8) | ' ', 0, 0, 0);
          interrupt(0x10, (0x0E << 8) | 0x08, 0, 0, 0);
      }
  }
  ```
  Case ketika user menekan `BACKSPACE`.
  - `0x08`: Kode ASCII untuk `BACKSPACE`.
  - Jika input tidak kosong, turunkan indeks `idx--` agar karakter sebelumnya dihapus.
  - interrupt pertama `interrupt(0x10, (0x0E << 8) | 0x08, 0, 0, 0)` untuk menggeser kursor ke kiri `0x08`.
  - interrupt kedua `interrupt(0x10, (0x0E << 8) | ' ', 0, 0, 0)` untuk menampilkan spasi dan menimpa karakter yang dihapus.
  - interrupt ketiga `interrupt(0x10, (0x0E << 8) | 0x08, 0, 0, 0)` untuk menggeser kursor ke kiri lagi agar kembali ke posisi sebelumnya untuk menulis karakter baru.

  ```
  else{
      buf[idx++] = ch;
      interrupt(0x10, (0x0E << 8) | ch, 0, 0, 0);
  }
  ```
  Case ketika user menekan selain `ENTER` dan `BACKSPACE`.
  - Menyimpan `ch` ke `buf` dan increment index `idx` untuk mencetak karakter selanjutnya.
  - interrupt `interrupt(0x10, (0x0E << 8) | ch, 0, 0, 0)` untuk menampilkan `ch` input ke layar.
 
  ```
  buf[idx] = '\0'
  ```
  Ketika loop berakhir menambahkan`\0` ke akhir `buf` sebagai penanda akhir input (string). 

  ```
  void clearScreen(void){
      int i;
  
      interrupt(0x10, (0x06 << 8) | 0x00, 0x0F00, 0x0000, (24 << 8) | 79);
  
      interrupt(0x10, (0x02 << 8) | 0x00, 0, 0, 0);
  
      for(i = 0; i < 80 * 25; i++){
          putInMemory(0xB800, i * 2, ' ');
          putInMemory(0xB800, i * 2 + 1, 0x0F);
      }
  }
  ```
  Membersihkan layar dan mengatur kursor ke pojok kiri atas.
  - interrupt `interrupt(0x10, (0x06 << 8) | 0x00, 0x0F00, 0x0000, (24 << 8) | 79)` untuk scroll up (membersihkan layar).
      - `AX = (0x06 << 8) | 0x00`, AH=0x06 untuk scroll up window, AL=0 (baris yang di-scroll, 0 = semua).
      - `BX = 0x0F00`, BH=0x0F set setiap karakter yang dibersihkan akan diisi dengan spasi warna default (putih, 0x0F).
      - `CX = 0x0000`, CH=0 (row atas), CL=0 (kolom kiri).
      - `DX = (24 << 8) | 79` → DH=24 (row bawah), DL=79 (kolom kanan).
  - interrupt `interrupt(0x10, (0x02 << 8) | 0x00, 0, 0, 0)` memindahkan kursor ke pojok kiri atas (baris 0, kolom 0) layar teks.
      - `AX = (0x02 << 8) | 0x00`, AH=0x02 untuk set posisi kursor
      - `DH=0` dan `DL=0` (DX = 0), baris = 0 dan kolom = 0.
        
  ```
  for(i = 0; i < 80 * 25; i++){
      putInMemory(0xB800, i * 2, ' ');
      putInMemory(0xB800, i * 2 + 1, 0x0F);
  }
  ```
  Loop untuk menghapus karakter satu per satu di video memory langsung.
  `80 * 25 = 2000` lebar layar yang akan diisi dengan dengan spasi putih.
  - putInMemory `putInMemory(0xB800, i * 2, ' ')` untuk menampilkan spasi ke layar.
    - `segment = 0xB800`, segmen memori video text mode.
    - `address = i * 2`, offset karakter.
    - `char = ' '`, mengganti karakter sebelumnya di layar dengan spasi.
  - putInMemory `putInMemory(0xB800, i * 2 + 1, 0x0F)` untuk menampilkan teks (spasi) berwarna putih dengan background hitam.
      - `segment = 0xB800`, segmen memori video text mode.
      - `address = i * 2 + 1`: offset atribut warna.
      - `char = 0x0F`: warna putih untuk foreground `F` dan warna hitam untuk background `0`.
