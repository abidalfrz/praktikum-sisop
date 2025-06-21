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

a. Implementasikan fungsi printString, readString, dan clearScreen di kernel.c yang akan menampilkan dan membaca string di layar.
printString: Menampilkan string yang diakhiri null menggunakan int 10h dengan AH=0x0E.
readString: Membaca karakter dari keyboard menggunakan int 16h dengan AH=0x00 sampai Enter ditekan. Termasuk penanganan Backspace dasar.
clearScreen: Membersihkan layar dan mengatur kursor ke pojok kiri atas (0, 0) menggunakan int 10h dengan AH=0x06 dan AH=0x02. Buffer video untuk warna karakter akan diubah menjadi putih.

**Answer:**

Menambahkan fungsi printString, readString, dan clearScreen di `kernel.c`.

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

- **Explanation:**
  ```
  void printString(char *str){
      int i = 0;
      while(str[i] != '\0'){
          interrupt(0x10, (0x0E << 8) | str[i], 0, 0, 0);
          i++;
      }
  }
  ```
  Menampilkan string ke layar karakter per karakter menggunakan loop dan interrupt BIOS hingga berhenti ketika user input `ENTER`.
  
  ```
  interrupt(0x10, (0x0E << 8) | str[i], 0, 0, 0)
  ```
    - `0x10` adalah integer interupsi BIOS untuk layar (video service).
    - `AH = 0x0E`: Subfungsi "Teletype Output", BIOS akan menampilkan karakter ke layar dan menggeser kursor satu posisi ke kanan.
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
    - `AX = 0x0000`: AH=0x00, membaca karakter dari keyboard.
    - `ch` variabel yang digunakan untuk menyimpan karakter input dari keyboard.
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
  - `break` untuk keluar dari loop dan menandakan proses input selesai.
 
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


b. Lengkapi implementasi fungsi-fungsi di [`std_lib.h`](./include/std_lib.h) dalam [`std_lib.c`](./src/std_lib.c).
Fungsi-fungsi di atas dapat digunakan untuk menyederhanakan implementasi fungsi `printString`, `readString`, `clearScreen`, dan fungsi-fungsi lebih lanjut yang dijelaskan pada tugas berikutnya.

Fungsi di dalam [`std_lib.c`](./src/std_lib.c)
  - `div` : fungsi pembagian
  - `mod` : fungsi modulo
  - `memcpy` : fungsi untuk menyalin memori  
  - `strlen` : fungsi untuk menghitung panjang string
  - `strcmp` : fungsi untuk membandingkan dua string
  - `strcpy` : fungsi untuk menyalin string
  - `clear` : fungsi untuk mengisi memori dengan nol

**Answer:**

- **Code:**
  ```
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
  ```

- **Explanation:**
  
    ```
    #include "std_lib.h"
    ```
    Include `std_lib.h` untuk mendapatkan/mendefinisikan prototype fungsi.
    
    ```
    unsigned int strlen(char* str){
        int len;
        len = 0;
        while(str[len] != '\0') len++;
        return len;
    }
    ```
    
    Menghitung panjang string menggunakan loop hingga karakter sebelum '\0' dengan variabel `len`, lalu return `len` sebagai hasil.
  
    ```
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
    ```
    Melakukan pembagian bilangan bulat secara manual.
    - Jika `b == 0`, return -999 sebagai tanda error pembagian dengan nol.
    - Menentukan apakah hasilnya negatif menggunakan variabel `neg`. Jika salah satu operand negatif, maka hasilnya negatif (set `neg` menjadi 1).
    - Mengubah operand yang negatif menjadi positif untuk mempermudah perhitungan.
    - Melakukan pengurangan berulang `a -= b` dan menghitung berapa kali pengurangan bisa dilakukan disimpan di variabel `total`.
    - Setelah loop, jika hasil seharusnya negatif `neg`, membalik tanda hasil.
    - return `total` sebagai hasil pembagian.
  
    ```
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
    ```
    Menghitung sisa bagi (modulo) secara manual.
    - Jika `b == 0`, return -999 sebagai tanda error pembagian dengan nol.
    - Menentukan apakah hasilnya negatif menggunakan variabel `neg`. Jika `a` negatif atau kedua operand negatif, maka hasilnya negatif (set `neg` menjadi 1).
    - Mengubah operand yang negatif menjadi positif untuk mempermudah perhitungan.
    - Menghitung modulo dengan rumus `a - b * div(a, b)` dan menyimpannya di variabel `res`.
    - jika hasil seharusnya negatif `neg`, membalik tanda hasil.
    - return `res` sebagai hasil modulo.
  
    ```
    void memcpy(byte* src, byte* dst, unsigned int size){
        unsigned int i;
        for(i = 0; i < size; i++){
            dst[i] = src[i];
        }
    }
    ```
    Menyalin blok memori dari array `src` ke array `dst` sebanyak `size` byte.
    - Melakukan loop sebanyak `size` kali.
    - Tiap iterasi, menyalin satu byte dari `src[i]` ke `dst[i]`.
  
    ```
    bool strcmp(char* str1, char* str2){
        int length, i;
        if(strlen(str1) != strlen(str2)) return 0;
  
        length = strlen(str1);
        for(i = 0; i < length; i++){
            if(str1[i] != str2[i]) return 0;
        }
  
        return 1;
    }
    ```
    Membandingkan dua string,  jika true/1 jika sama, dan 0/false jika berbeda.
    - `if(strlen(str1) != strlen(str2))` cek apakah panjang kedua string sama, jika beda akan return 0.
    - Jika kedua string memiliki panjang yang sama, akan membandingkan menggunakan loop dengan mengiterasi indexnya.
    - Jika ditemukan karakter berbeda, return 0.
    - Jika semua karakter sama, return 1.
  
    ```
    void strcpy(char* src, char* dst){
        int i;
        i = 0;
        while(src[i] != '\0'){
            dst[i] = src[i];
            i+=1;
        }
        dst[i] = '\0';
    }
    ```
    Menyalin string dari `src` ke `dst` hingga menemukan karakter null (`'\0'`).
    - Menggunakan loop hingga hingga karakter sebelum '\0' dan menggunakan variabel `i` untuk iterasi per indexnya.
    - Setiap karakter diindeks `i` dari `src` disalin ke `dst`.
    - Mengakhiri dst dengan nul `\0`.
  
    ```
    void clear(byte* buf, unsigned int size){
        unsigned int i;
        for(i = 0; i < size; i++){
            buf[i] = '\0';
        }
    }
    ```
    Mengosongkan atau menginisialisasi `buf` dengan mengisi elemen sepanjang `size` dengan `\0`.
    

**Code Kernel.c untuk soal c dan d**
```
#include "std_type.h"
#include "std_lib.h"
```
Include `std_type.h` dan `std_lib.h` di dalam `kernel.h` untuk mengakses fungsi dan tipe data dari std_type dan std_lib yang telah dibuat.

```
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
```


c. Implementasikan perintah `echo`
Perintah ini mengambil argumen yang diberikan (karakter keyboard) untuk perintah `echo` dan mencetaknya ke shell.
<br>c. Implementasikan perintah `grep`
Perintah ini mencari baris yang cocok dengan pola dalam inputnya dan mencetak baris yang cocok. `grep` hanya akan mengambil satu argumen menggunakan piping (`|`) dari perintah `echo`. Output harus berupa bagian dari argumen yang di-pipe yang diteruskan ke `grep`. Jika argumen tidak cocok, mengembalikan `NULL`.</br>

**Answer:**

**1. Implementasi Echo**

Di dalam code `kernel.c` untuk membuat echo membutuhkan fungsi `getCommands`, `prefix`, `strcpy` serta variabel tambahan untuk menyimpan hasil input user dan hasil echo dan menggunakan fungsi `printString` untuk mencetak hasilnya.
- **Penjelasan:**
  ```
  #include "kernel.h"
  ```
  Mengakses fungsi yang ada di `kernel.h` beserta headernya.
        
  ```
  int getCommands(char *buf, char commands[][128]);
  int prefix(char *buf, char *comm);
  ```
  Prototipe fungsi yang digunakan untuk membuat echo.

  ```
  char res[128];
  char commands[8][128];
  char buf[128];
  int i, count, x;
  ```
  - `res` untuk menyimpan hasil perintah.
  - `commands` (array of string) untuk menyimpan perintah.
  - `buf` menyimpan hasil input user.
  - variabel tambahan.

  ```
  int prefix(char *buf, char *comms){
    int i, length;
    length = strlen(comms);
    for(i = 0; i < length; i++){
        if(buf[i] != comms[i]) return 0;
    }
    return 1;
  }
  ```
  Fungsi untuk memeriksa apakah sebuah string diawali dengan suatu string.
  - Membandingkan menggunakan loop dengan mengiterasi indexnya. Jika ada karakter yang tidak sama return 0 sepanjang `length`.
  - return 1 jika semua karakter sama sepanjang `length`.

  ```
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
  ```
  Fungsi untuk membagi input pipeline menjadi beberapa command dengan delimiter `|`.
  - setiap ketemu `|` atau di akhir string, menyimpan command ke array `commands` dan mengilangkan spasi berlebih di akhir command.
  - Menggunakan loop untuk memproses `buf` ke dalam array `commands`.
  - return j sebagai jumlah commands yang dipisah menggunakan delimiter `|`.

  ```
  if (strlen(buf) > 0) {
        count = getCommands(buf, commands);
        for(i = 0; i < count; i++){
            if(prefix(commands[i], "echo")){
                strcpy(commands[i] + 5, res);
        }
  ```
  - `count` untuk menyimpan jumlah commands.
  - Melakukan loop sebanyak `count` dan mengiterasi index dari array `commands`.
  - Jika `commands[i]` memiliki prefix "echo" maka array `res` akan menyalin string dari commands[i] dimulai dengan indeks ke 6 yaitu argumen echo.

  ```
  if(strlen(res) > 0 && !prefix(commands[count - 1], "wc")){
      printString(res);
      printString("\n");
  }
  ```
  Setelah loop selesai, jika `res` tidak kosong dan commands terakhir bukan `wc`, akan menampilkan `res` di layar dengan `\n`.


**2. Implementasi Grep**

Di dalam code `kernel.c` untuk membuat grep membutuhkan fungsi `getCommands`, `prefix`, `findPattern`, `strcpy` serta variabel tambahan untuk menyimpan hasil input user dan hasil grep dan menggunakan fungsi `printString` untuk mencetak hasilnya. grep hanya dapat diimplementasikan setelah dipipe dengan echo.

**Penjelasan:**
  ```
  #include "kernel.h"
  ```
  Mengakses fungsi yang ada di `kernel.h` beserta headernya.
        
  ```
  int getCommands(char *buf, char commands[][128]);
  int findPattern(char *buff, char *patt);
  int prefix(char *buf, char *comm);
  ```
  Prototipe fungsi yang digunakan untuk membuat echo.

  ```
  char res[128];
  char commands[8][128];
  char buf[128];
  int i, count, x;
  ```
  - `res` untuk menyimpan hasil perintah.
  - `commands` (array of string) untuk menyimpan perintah.
  - `buf` menyimpan hasil input user.
  - variabel tambahan.

  ```
  int prefix(char *buf, char *comms){
    int i, length;
    length = strlen(comms);
    for(i = 0; i < length; i++){
        if(buf[i] != comms[i]) return 0;
    }
    return 1;
  }
  ```
  Fungsi untuk memeriksa apakah sebuah string diawali dengan suatu string.
  - Membandingkan menggunakan loop dengan mengiterasi indexnya. Jika ada karakter yang tidak sama return 0 sepanjang `length`.
  - return 1 jika semua karakter sama sepanjang `length`.
  
  ```
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

  ```
  Fungsi untuk membagi input pipeline menjadi beberapa command dengan delimiter `|`.
  - setiap ketemu `|` atau di akhir string, menyimpan command ke array `commands` dan mengilangkan spasi berlebih di akhir command.
  - Menggunakan loop untuk memproses `buf` ke dalam array `commands`.
  - return j sebagai jumlah commands yang dipisah menggunakan delimiter `|`.

  ```
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
  ```
  Fungsi untuk mencari pattern berupa substring di string lain.
  
  ```
  if (strlen(buf) > 0) {
      count = getCommands(buf, commands);
      for(i = 0; i < count; i++){
          if(prefix(commands[i], "echo")){
              strcpy(commands[i] + 5, res);
      }
  ```
  - `count` untuk menyimpan jumlah commands.
  - Melakukan loop sebanyak `count` dan mengiterasi index dari array `commands`.
  - Jika `commands[i]` memiliki prefix "echo" maka array `res` akan menyalin string dari commands[i] dimulai dengan indeks ke 6 yaitu argumen echo.

  ```
  if(strlen(res) > 0 && !prefix(commands[count - 1], "wc")){
      printString(res);
      printString("\n");
  }
  ```
  Setelah loop selesai, jika `res` tidak kosong dan commands terakhir bukan `wc`, akan menampilkan `res` di layar dengan `\n`.

  
            
          


  
    
  
 
