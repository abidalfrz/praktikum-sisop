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

## Soal 1
# FUSecure

Yuadi adalah seorang developer brilian yang sedang mengerjakan proyek top-secret. Sayangnya, temannya Irwandi yang terlalu penasaran memiliki kebiasaan buruk menyalin jawaban praktikum sistem operasi Yuadi tanpa izin setiap kali deadline mendekat. Meskipun sudah diperingatkan berkali-kali dan bahkan ditegur oleh asisten dosen karena sering ketahuan plagiat, Irwandi tetap tidak bisa menahan diri untuk mengintip dan menyalin jawaban praktikum Yuadi. Merasa kesal karena prestasinya terus-menerus dicuri dan integritasnya dipertaruhkan, Yuadi yang merupakan ahli keamanan data memutuskan untuk mengambil tindakan sendiri dengan membuat FUSecure, sebuah file system berbasis FUSE yang menerapkan akses read-only dan membatasi visibilitas file berdasarkan permission user.

## Deskripsi Tugas

Setelah frustrasi dengan kebiasaan plagiat Irwandi yang merugikan prestasi akademiknya, Yuadi memutuskan untuk merancang sistem keamanan yang sophisticated. Dia akan membuat sistem file khusus yang memungkinkan mereka berdua berbagi materi umum, namun tetap menjaga kerahasiaan jawaban praktikum masing-masing.

Library yang digunakan :
```
#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h> 
```

Struct FUSE :
```
static struct fuse_operations fs_oper = {
    .readdir = fs_readdir,
    .getattr = fs_getattr,
    .mkdir   = fs_mkdir,
    .rmdir   = fs_rmdir,
    .create  = fs_create,
    .unlink  = fs_unlink,
    .write   = fs_write,
    .rename  = fs_rename,
    .truncate= fs_truncate,
    .open    = fs_open,
    .read    = fs_read
};
```

### a. Setup Direktori dan Pembuatan User

Langkah pertama dalam rencana Yuadi adalah mempersiapkan infrastruktur dasar sistem keamanannya.

1. Buat sebuah "source directory" di sistem Anda (contoh: `/home/shared_files`). Ini akan menjadi tempat penyimpanan utama semua file.

2. Di dalam source directory ini, buat 3 subdirektori: `public`, `private_yuadi`, `private_irwandi`. Buat 2 Linux users: `yuadi` dan `irwandi`. Anda dapat memilih password mereka.
   | User | Private Folder |
   | ------- | --------------- |
   | yuadi | private_yuadi |
   | irwandi | private_irwandi |

Yuadi dengan bijak merancang struktur ini: folder `public` untuk berbagi materi kuliah dan referensi yang boleh diakses siapa saja, sementara setiap orang memiliki folder private untuk menyimpan jawaban praktikum mereka masing-masing.

**Answer:**

- **Code:**
  
  Terminal :
  ```
  mkdir shared_files
  cd shared_files

  mkdir public
  mkdir private_yuadi
  mkdir private_irwandi

  sudo useradd -m yuadi
  sudo passwd yuadi
  sudo useradd -m irwandi
  sudo passwd irwandi

  sudo chown yuadi:yuadi private_yuadi
  sudo chown irwandi:irwandi private_irwandi

  sudo chmod 755 public
  sudo chmod 700 private_yuadi
  sudo chmod 700 private_irwandi
  ```

- **Penjelasan:**
  ```
  mkdir shared_files
  cd shared_files
  ```
  Membuat direktori dan berpindah ke direktori `shared_files`

  ```
  mkdir public
  mkdir private_yuadi
  mkdir private_irwandi
  ```
  Membuat sub-direktori `public`, `private_yuadi`, `private_irwandi`

  ```
  sudo useradd -m yuadi
  sudo passwd yuadi
  sudo useradd -m irwandi
  sudo passwd irwandi
  ```
  Membuat user dan password untuk user `yuadi` dan user `irwandi`

  ```
  sudo chown yuadi:yuadi private_yuadi
  sudo chown irwandi:irwandi private_irwandi
  ```
  Memberikan hak kepemilikan direktori `private_yuadi` untuk grup `yuadi` dan user `yuadi`, serta direktori `private_irwandi` untuk grup `irwandi` dan user `irwandi`

  ```
  sudo chmod 755 public
  sudo chmod 700 private_yuadi
  sudo chmod 700 private_irwandi
  ```
  - Mengubah permission direktori `public` menjadi baca, tulis, eksekusi untuk owner, serta baca, eksekusi untuk group/user lain
  - Mengubah permission direktori `private_yuadi` menjadi baca, tulis, eksekusi untuk owner, serta tidak bisa akses untuk group/user lain
  - Mengubah permission direktori `private_irwandi` menjadi baca, tulis, eksekusi untuk owner, serta tidak bisa akses untuk group/user lain

- **Screenshot:**
  

### b. Akses Mount Point

Selanjutnya, Yuadi ingin memastikan sistem filenya mudah diakses namun tetap terkontrol.

FUSE mount point Anda (contoh: `/mnt/secure_fs`) harus menampilkan konten dari `source directory` secara langsung. Jadi, jika Anda menjalankan `ls /mnt/secure_fs`, Anda akan melihat `public/`, `private_yuadi/`, dan `private_irwandi/`.

**Answer:**

- **Code:**
  ```
  const char *source_dir = "/home/nabila/shared_files";

  static void full_path(char fpath[PATH_MAX], const char *path) {
    snprintf(fpath, PATH_MAX, "%s%s", source_dir, path);
  }

  static int fs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    filler(buf, "public", NULL, 0);
    filler(buf, "private_yuadi", NULL, 0);
    filler(buf, "private_irwandi", NULL, 0);
    return 0;
  }

  static int fs_getattr(const char *path, struct stat *stbuf) {
    char fpath[PATH_MAX];
    full_path(fpath, path);
    int res = lstat(fpath, stbuf);
    if (res == -1) return -errno;
    return 0;
  }

  int main(int argc, char *argv[]) {
    umask(0);
    return fuse_main(argc, argv, &fs_oper, NULL);
  }
  ```
  
- **Penjelasan:**
  ```
  const char *source_dir = "/home/nabila/shared_files";
  ```
  `source_dir` adalah pointer bertipe `const char*` yang menunjuk ke alamat awal dari string `"/home/nabila/shared_files"`. Sebagai tempat menyimpan path `source directory`

  ```
  static void full_path(char fpath[PATH_MAX], const char *path) {
    snprintf(fpath, PATH_MAX, "%s%s", source_dir, path);
  }
  ```
  Menggabungkan `source_dir` dengan `path` dari FUSE agar mendapatkan path absolut dari file yang diminta

  ```
  static int fs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    filler(buf, "public", NULL, 0);
    filler(buf, "private_yuadi", NULL, 0);
    filler(buf, "private_irwandi", NULL, 0);
    return 0;
  }
  ```
  Menampilkan direktori `public`, `private_yuadi`, `private_irwandi` setiap kali user melakukan command `ls` untuk direktori di mount point.

  ```
  static int fs_getattr(const char *path, struct stat *stbuf) {
    char fpath[PATH_MAX];
    full_path(fpath, path);
    int res = lstat(fpath, stbuf);
    if (res == -1) return -errno;
    return 0;
  }
  ```
  Mengambil informasi tentang file atau folder di mount point.

  ```
  int main(int argc, char *argv[]) {
    umask(0);
    return fuse_main(argc, argv, &fs_oper, NULL);
  }
  ```
  - `umask(0)` untuk menentukan default permission file/folder yang dibuat oleh proses.
  - Inisialisasi FUSE dan mulai operasi file system.

- **Screenshot:**


### c. Read-Only untuk Semua User

Yuadi sangat kesal dengan kebiasaan Irwandi yang suka mengubah atau bahkan menghapus file jawaban setelah menyalinnya untuk menghilangkan jejak plagiat. Untuk mencegah hal ini, dia memutuskan untuk membuat seluruh sistem menjadi read-only.

1. Jadikan seluruh FUSE mount point **read-only untuk semua user**.
2. Ini berarti tidak ada user (termasuk `root`) yang dapat membuat, memodifikasi, atau menghapus file atau folder apapun di dalam `/mnt/secure_fs`. Command seperti `mkdir`, `rmdir`, `touch`, `rm`, `cp`, `mv` harus gagal semua.

"Sekarang Irwandi tidak bisa lagi menghapus jejak plagiatnya atau mengubah file jawabanku," pikir Yuadi puas.

**Answer:**

- **Code:**
  ```
  static int fs_mkdir(const char *path, mode_t mode) {
    return -EROFS;
  }

  static int fs_rmdir(const char *path) {
    return -EROFS;
  }

  static int fs_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
    return -EROFS;
  }

  static int fs_unlink(const char *path) {
    return -EROFS;
  }

  static int fs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    return -EROFS;
  }

  static int fs_rename(const char *from, const char *to) {
    return -EROFS;
  }

  static int fs_truncate(const char *path, off_t size) {
    return -EROFS;
  }

  int main(int argc, char *argv[]) {
    umask(0);
    return fuse_main(argc, argv, &fs_oper, NULL);
  }
  ```

- **Penjelasan:**
  ```
  static int fs_mkdir(const char *path, mode_t mode) {
    return -EROFS;
  }
  ```
  Ketika user ingin membuat direktori (`mkdir`) di mount point, akan menampilkan Error: Read-Only File System

  ```
  static int fs_rmdir(const char *path) {
    return -EROFS;
  }
  ```
  Ketika user ingin menghapus direktori (`rmdir`) di mount point, akan menampilkan Error: Read-Only File System

  ```
  static int fs_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
    return -EROFS;
  }
  ```
  Ketika user ingin membuat file (`touch`, `nano`, dll) di mount point, akan menampilkan Error: Read-Only File System

  ```
  static int fs_unlink(const char *path) {
    return -EROFS;
  }
  ```
  Ketika user ingin menghapus file (`rm`) di mount point, akan menampilkan Error: Read-Only File System

  ```
  static int fs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    return -EROFS;
  }
  ```
  Ketika user ingin menulis ke file (`echo`, `vim`, `nano`, `cp`) di mount point, akan menampilkan Error: Read-Only File System

  ```
  static int fs_rename(const char *from, const char *to) {
    return -EROFS;
  }
  ```
  Ketika user ingin rename file, memindahkan file (`mv`) di mount point, akan menampilkan Error: Read-Only File System

  ```
  static int fs_truncate(const char *path, off_t size) {
    return -EROFS;
  }
  ```
  Ketika user ingin resize file (`truncate`) di mount point, akan menampilkan Error: Read-Only File System

  ```
  int main(int argc, char *argv[]) {
    umask(0);
    return fuse_main(argc, argv, &fs_oper, NULL);
  }
  ```
  - `umask(0)` untuk menentukan default permission file/folder yang dibuat oleh proses.
  - Inisialisasi FUSE dan mulai operasi file system.

- **Screenshot:**
  

### d. Akses Public Folder

Meski ingin melindungi jawaban praktikumnya, Yuadi tetap ingin berbagi materi kuliah dan referensi dengan Irwandi dan teman-teman lainnya.

Setiap user (termasuk `yuadi`, `irwandi`, atau lainnya) harus dapat **membaca** konten dari file apapun di dalam folder `public`. Misalnya, `cat /mnt/secure_fs/public/materi_kuliah.txt` harus berfungsi untuk `yuadi` dan `irwandi`.

**Answer:**

- **Code:**
  ```
  static int fs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    filler(buf, "public", NULL, 0);
    filler(buf, "private_yuadi", NULL, 0);
    filler(buf, "private_irwandi", NULL, 0);
    return 0;
  }

  static int fs_getattr(const char *path, struct stat *stbuf) {
    char fpath[PATH_MAX];
    full_path(fpath, path);
    int res = lstat(fpath, stbuf);
    if (res == -1) return -errno;
    return 0;
  }

  static int fs_open(const char *path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    full_path(fpath, path);

    if (strncmp(path, "/private_yuadi/", 15) == 0 && fuse_get_context()->uid != getpwnam("yuadi")->pw_uid) {
        return -EACCES;
    }

    if (strncmp(path, "/private_irwandi/", 17) == 0 && fuse_get_context()->uid != getpwnam("irwandi")->pw_uid) {
        return -EACCES;
    }

    int fd = open(fpath, O_RDONLY);
    if (fd == -1) return -errno;

    close(fd);
    return 0;
  }

  static int fs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    full_path(fpath, path);

    int fd = open(fpath, O_RDONLY);
    if (fd == -1) return -errno;

    int res = pread(fd, buf, size, offset);
    if (res == -1) res = -errno;

    close(fd);
    return res;
  }

  int main(int argc, char *argv[]) {
    umask(0);
    return fuse_main(argc, argv, &fs_oper, NULL);
  }
  ```

- **Penjelasan:**
  ```
  static int fs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    filler(buf, "public", NULL, 0);
    filler(buf, "private_yuadi", NULL, 0);
    filler(buf, "private_irwandi", NULL, 0);
    return 0;
  }
  ```
  Memberi tahu FUSE bahwa ada direktori `public`, `private_yuadi`, `private_irwandi` setiap kali user melakukan command `ls` untuk direktori di mount point.

  ```
  static int fs_getattr(const char *path, struct stat *stbuf) {
    char fpath[PATH_MAX];
    full_path(fpath, path);
    int res = lstat(fpath, stbuf);
    if (res == -1) return -errno;
    return 0;
  }
  ```
  Mengambil informasi tentang file atau folder di mount point.

  ```
  static int fs_open(const char *path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    full_path(fpath, path);

    if (strncmp(path, "/private_yuadi/", 15) == 0 && fuse_get_context()->uid != getpwnam("yuadi")->pw_uid) {
        return -EACCES;
    }

    if (strncmp(path, "/private_irwandi/", 17) == 0 && fuse_get_context()->uid != getpwnam("irwandi")->pw_uid) {
        return -EACCES;
    }

    int fd = open(fpath, O_RDONLY);
    if (fd == -1) return -errno;

    close(fd);
    return 0;
  }
  ```
  Menjamin siapa saja dan direktori apa yang dapat dibuka

  ```
  static int fs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    full_path(fpath, path);

    int fd = open(fpath, O_RDONLY);
    if (fd == -1) return -errno;

    int res = pread(fd, buf, size, offset);
    if (res == -1) res = -errno;

    close(fd);
    return res;
  }
  ```
  Mengambil isi file dan menampilkan ke user.

  ```
  int main(int argc, char *argv[]) {
    umask(0);
    return fuse_main(argc, argv, &fs_oper, NULL);
  }
  ```
  - `umask(0)` untuk menentukan default permission file/folder yang dibuat oleh proses.
  - Inisialisasi FUSE dan mulai operasi file system.

### e. Akses Private Folder yang Terbatas

Inilah bagian paling penting dari rencana Yuadi - memastikan jawaban praktikum benar-benar terlindungi dari plagiat.

1. File di dalam `private_yuadi` **hanya dapat dibaca oleh user `yuadi`**. Jika `irwandi` mencoba membaca file jawaban praktikum di `private_yuadi`, harus gagal (contoh: permission denied).
2. Demikian pula, file di dalam `private_irwandi` **hanya dapat dibaca oleh user `irwandi`**. Jika `yuadi` mencoba membaca file di `private_irwandi`, harus gagal.

"Akhirnya," senyum Yuadi, "Irwandi tidak bisa lagi menyalin jawaban praktikumku, tapi dia tetap bisa mengakses materi kuliah yang memang kubuat untuk dibagi."

**Answer:**

- **Code:**
  ```
  const char *source_dir = "/home/nabila/shared_files";

  static void full_path(char fpath[PATH_MAX], const char *path) {
    snprintf(fpath, PATH_MAX, "%s%s", source_dir, path);
  }

  static int fs_open(const char *path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    full_path(fpath, path);

    if (strncmp(path, "/private_yuadi/", 15) == 0 && fuse_get_context()->uid != getpwnam("yuadi")->pw_uid) {
        return -EACCES;
    }

    if (strncmp(path, "/private_irwandi/", 17) == 0 && fuse_get_context()->uid != getpwnam("irwandi")->pw_uid) {
        return -EACCES;
    }

    int fd = open(fpath, O_RDONLY);
    if (fd == -1) return -errno;

    close(fd);
    return 0;
  }
  ```

- **Penjelasan:**
  ```
  const char *source_dir = "/home/nabila/shared_files";
  ```
  `source_dir` adalah pointer bertipe `const char*` yang menunjuk ke alamat awal dari string `"/home/nabila/shared_files"`. Sebagai tempat menyimpan path `source directory`

  ```
  static void full_path(char fpath[PATH_MAX], const char *path) {
    snprintf(fpath, PATH_MAX, "%s%s", source_dir, path);
  }
  ```
  Menggabungkan `source_dir` dengan `path` dari FUSE agar mendapatkan path absolut dari file yang diminta

  ```
  static int fs_open(const char *path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    full_path(fpath, path);

    if (strncmp(path, "/private_yuadi/", 15) == 0 && fuse_get_context()->uid != getpwnam("yuadi")->pw_uid) {
        return -EACCES;
    }

    if (strncmp(path, "/private_irwandi/", 17) == 0 && fuse_get_context()->uid != getpwnam("irwandi")->pw_uid) {
        return -EACCES;
    }

    int fd = open(fpath, O_RDONLY);
    if (fd == -1) return -errno;

    close(fd);
    return 0;
  }
  ```
  Mengecek siapakah yang sedang mengakses direktori. Apabila yang mengakses direktorinya adalah user selain owner, maka akan gagal dan menampilkan `Permission Denied`

- **Screenshot:**

## Contoh Skenario

Setelah sistem selesai, beginilah cara kerja FUSecure dalam kehidupan akademik sehari-hari:

- **User `yuadi` login:**

  - `cat /mnt/secure_fs/public/materi_algoritma.txt` (Berhasil - materi kuliah bisa dibaca)
  - `cat /mnt/secure_fs/private_yuadi/jawaban_praktikum1.c` (Berhasil - jawaban praktikumnya sendiri)
  - `cat /mnt/secure_fs/private_irwandi/tugas_sisop.c` (Gagal dengan "Permission denied" - tidak bisa baca jawaban praktikum Irwandi)
  - `touch /mnt/secure_fs/public/new_file.txt` (Gagal dengan "Permission denied" - sistem read-only)

- **User `irwandi` login:**
  - `cat /mnt/secure_fs/public/materi_algoritma.txt` (Berhasil - materi kuliah bisa dibaca)
  - `cat /mnt/secure_fs/private_irwandi/tugas_sisop.c` (Berhasil - jawaban praktikumnya sendiri)
  - `cat /mnt/secure_fs/private_yuadi/jawaban_praktikum1.c` (Gagal dengan "Permission denied" - tidak bisa baca jawaban praktikum Yuadi)
  - `mkdir /mnt/secure_fs/new_folder` (Gagal dengan "Permission denied" - sistem read-only)

Dengan sistem ini, kedua mahasiswa akhirnya bisa belajar dengan tenang. Yuadi bisa menyimpan jawaban praktikumnya tanpa khawatir diplagiat Irwandi, sementara Irwandi terpaksa harus mengerjakan tugasnya sendiri namun masih bisa mengakses materi kuliah yang dibagikan Yuadi di folder public.

## Catatan

- Anda dapat memilih nama apapun untuk FUSE mount point Anda.
- Ingat untuk menggunakan argument `-o allow_other` saat mounting FUSE file system Anda agar user lain dapat mengaksesnya.
- Fokus pada implementasi operasi FUSE yang berkaitan dengan **membaca** dan **menolak** operasi write/modify. Anda perlu memeriksa **UID** dari user yang mengakses di dalam operasi FUSE Anda untuk menerapkan pembatasan private folder.

**Screenshot Skenario:**

## Soal 4
Lilhab sedang ditantang oleh Trabowo (orang yang sama yang dia temui di modul ke-1) untuk membuat kernel sederhana yang memiliki fitur piping menggunakan `echo`, `grep`, dan `wc`. Lilhab merasa kesulitan dan gugup karena dia pikir pekerjaannya tidak akan selesai ketika bertemu dengan deadline. Jadi, dia memutuskan untuk bertanya kepada Grok tentang tantangan tersebut dan AI tersebut memutuskan untuk mengejeknya.

![image](image.png)

Merasa sedih, Lilhab bertekad untuk menyelesaikan pekerjaannya tepat waktu. Dia kemudian menemukan [modul](https://github.com/arsitektur-jaringan-komputer/Modul-Sisop/tree/master/Modul4) ini dan merasa sangat bersyukur. Bantu dia untuk menyelesaikan tantangan tersebut!

<b>a. Implementasikan fungsi printString, readString, dan clearScreen di kernel.c yang akan menampilkan dan membaca string di layar.
printString: Menampilkan string yang diakhiri null menggunakan int 10h dengan AH=0x0E.
readString: Membaca karakter dari keyboard menggunakan int 16h dengan AH=0x00 sampai Enter ditekan. Termasuk penanganan Backspace dasar.
clearScreen: Membersihkan layar dan mengatur kursor ke pojok kiri atas (0, 0) menggunakan int 10h dengan AH=0x06 dan AH=0x02. Buffer video untuk warna karakter akan diubah menjadi putih.</b>

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


<b>b. Lengkapi implementasi fungsi-fungsi di [`std_lib.h`](./include/std_lib.h) dalam [`std_lib.c`](./src/std_lib.c).
Fungsi-fungsi di atas dapat digunakan untuk menyederhanakan implementasi fungsi `printString`, `readString`, `clearScreen`, dan fungsi-fungsi lebih lanjut yang dijelaskan pada tugas berikutnya.</b>

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

- **Penjelasan:**
  
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
```


<b>c. Implementasikan perintah `echo`
Perintah ini mengambil argumen yang diberikan (karakter keyboard) untuk perintah `echo` dan mencetaknya ke shell.
<br>c. Implementasikan perintah `grep`
Perintah ini mencari baris yang cocok dengan pola dalam inputnya dan mencetak baris yang cocok. `grep` hanya akan mengambil satu argumen menggunakan piping (`|`) dari perintah `echo`. Output harus berupa bagian dari argumen yang di-pipe yang diteruskan ke `grep`. Jika argumen tidak cocok, mengembalikan null.</br></b>

**Answer:**

**1. Implementasi Echo**

Di dalam code `kernel.c`, untuk membuat echo membutuhkan fungsi `getCommands`, `prefix`, `strcpy` serta variabel tambahan untuk menyimpan hasil input user dan hasil echo dan menggunakan fungsi `printString` untuk mencetak hasilnya.
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
  - setiap ketemu `|` atau di akhir string, menyimpan command ke array `commands` dan mengilangkan ekstra spasi di akhir command.
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
  - Jika `commands[i]` memiliki prefix "echo" maka array `res` akan menyalin string dari commands[i] dimulai dengan indeks ke-6 yaitu argumen echo.

  ```
  if(strlen(res) > 0 && !prefix(commands[count - 1], "wc")){
      printString(res);
      printString("\n");
  }
  ```
  Setelah loop selesai, jika `res` tidak kosong dan commands terakhir bukan `wc`, akan menampilkan `res` di layar dengan `\n`.


**2. Implementasi Grep**

Di dalam code `kernel.c`, untuk membuat grep membutuhkan fungsi `getCommands`, `prefix`, `findPattern`, `strcpy` serta variabel tambahan untuk menyimpan hasil input user dan hasil grep dan menggunakan fungsi `printString` untuk mencetak hasilnya. grep hanya dapat diimplementasikan setelah dipipe dengan echo.

- **Penjelasan:**
  ```
  #include "kernel.h"
  ```
  Mengakses fungsi yang ada di `kernel.h` beserta headernya.
        
  ```
  int getCommands(char *buf, char commands[][128]);
  int findPattern(char *buff, char *patt);
  int prefix(char *buf, char *comm);
  ```
  Prototipe fungsi yang digunakan untuk membuat grep.

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
  - setiap ketemu `|` atau di akhir string, menyimpan command ke array `commands` dan mengilangkan ekstra spasi di akhir command.
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
  - Jika panjang pattern 0 (`len_patt == 0`), akan return 0.
  - Melakukan loop utama dari `i = 0` hingga `i <= len_buf - len_patt` untuk memastikan pattern tidak melewati batas akhir buffer.  
     - Pada setiap posisi `i`, diasumsikan pattern dimulai dari indeks tersebut.
     - Untuk setiap posisi `i`, melakukan loop kedua untuk setiap karakter pattern.
     - Bandingkan `buf[i + j]` dengan `patt[j]`:
       - Jika tidak sama, keluar dari loop (break).
       - Jika seluruh karakter pattern cocok (`j == len_patt` setelah loop), berarti pattern ditemukan di posisi `i` dan return index `i`.
     - return -1 jika tidak pernah ditemukan hingga akhir buffer.
  
  ```
  else if(prefix(commands[i], "grep")){
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
  }
  ```
  - `pattern` untuk menyimpan argumen dari grep yang dimulai dari indeks ke-6
  - Jika array `res` kosong maka loop berhenti dan grep return null.
  - Setelah menggunakan fungsi `findPattern`, jika return -1 yang berarti `pattern` tidak ditemukan, `res` akan dikosongkan dan keluar dari loop.
  - Jika `pattern` ditemukan, akan mengosongkan `res` dan menyalin `pattern` ke `res`.

  ```
  if(strlen(res) > 0 && !prefix(commands[count - 1], "wc")){
      printString(res);
      printString("\n");
  }
  ```
  Setelah loop selesai, jika `res` tidak kosong dan commands terakhir bukan `wc`, akan menampilkan `res` di layar dengan `\n`.

- **Screenshot:**

  **1. Echo**
  
  ![echoimg](https://drive.google.com/uc?id=1XpHCYmyVkR91A3jYnQ6J2Gmj6pLVDfG9)

  **2. Grep**

  ![grepimg](https://drive.google.com/uc?id=174FGeuOHAM9FJ-Mji9wouzK2wUDHFbNd)


<b>d. Implementasikan perintah `wc`
Perintah ini menghitung baris, kata, dan karakter dalam inputnya. `wc` tidak memerlukan argumen karena mendapat input dari pipe (`|`) dari perintah sebelumnya. Output harus berupa hitungan akhir dari argumen yang di-pipe yang diteruskan ke `wc`. Jika argumen tidak cocok, mengembalikan `NULL` atau `0`</b>

**Answer:**

Contoh penggunaan:

```bash
$> echo <argument> | wc
$> echo <argument> | grep <argument> | wc
```

Di dalam code `kernel.c`, untuk membuat wc membutuhkan fungsi `getCommands`, `prefix`, `toChar`, `strlen` serta serta variabel tambahan untuk menyimpan hasil input user dan menggunakan fungsi `printString` untuk mencetak hasilnya.

- **Penjelasan:**
  ```
  #include "kernel.h"
  ```
  Mengakses fungsi yang ada di `kernel.h` beserta headernya.
        
  ```
  int getCommands(char *buf, char commands[][128]);
  int findPattern(char *buff, char *patt);
  int prefix(char *buf, char *comm);
  ```
  Prototipe fungsi yang digunakan untuk membuat grep.

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
  - setiap ketemu `|` atau di akhir string, menyimpan command ke array `commands` dan mengilangkan ekstra spasi di akhir command.
  - Menggunakan loop untuk memproses `buf` ke dalam array `commands`.
  - return j sebagai jumlah commands yang dipisah menggunakan delimiter `|`.

  ```
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
  Fungsi untuk mengonversi integer positif menjadi char lalu me-reverse hasil dari konversi.
  - Jika `num` = 0, mengisi `val[0]` dengan 0, tutup string dengan `'\0'` lalu keluar dari fungsi.
  - Jika `num` > 0:
     - Menggunakan while loop `num > 0`, ambil digit paling belakang dengan `mod(num, 10)` dan menambahkan nilai ASCII '0' agar menjadi karakter digit lalu disimpan ke `val[i]`. Mengiterasi `i` untuk indeks selanjutnya.
     - Membagi `num` dengan 10 untuk memproses digit berikutnya.
  - Setelah loop selesai, menambahkan karakter null `\0` di akhir string.
  - Selanjutnya, melakukan loop untuk me-reverse urutan digit dari `val`.

  ```
  else if(prefix(commands[i], "wc")){
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
  ```
  - `row`, `length`, `words` untuk menyimpan baris, kata, dan karakter.
  - Jika array `res` kosong, `words` dan `row` diisi 0. Mengisi `length` dengan `strlen`.
  - Jika `res` tidak kosong:
    - `row` dan `words` diisi dengan 1.
    - Melakukan iterasi karakter per karakter dari `res` dengan `j` sebagai variabel indeks. Jika `res[j] == \n`, `row` diincrement, Jika `res[j] == ' ' && res[j+1] != '\0' && res[j+1] != ' '`, `words` diincrement.
  - Selanjutnya mengonversi `row`, `length`, `words` ke char dan menggunakan `printString` untuk menampilkannya menggunakan delimiter `\t`. Mencetak `\n` di akhir hasil.

  ```
  clear(buf, 128);
  clear(res, 128);
  for(i=0; i < count;i++){
      clear(commands[i], 128);
  }
  ```
  Jika semua perintah commands sudah dieksekusi, mengosongkan array `commands` sebanyak total perintah dari input.

- **Screenshot:**

  ![wcimg](https://drive.google.com/uc?id=1sBOxoe-G7TAdNZBTjZJ5Uzjftfls-v0F)

  
<b>e. Buat otomatisasi untuk mengompilasi dengan melengkapi file [`makefile`](./makefile).
Untuk mengompilasi program, perintah `make build` akan digunakan. Semua hasil program yang dikompilasi akan disimpan di direktori [`bin/`](./bin). Untuk menjalankan program, perintah `make run` akan digunakan.</b>

**Answer:**

- **makefile:**
```
prepare:
	dd if=/dev/zero of=bin/floppy.img bs=512 count=2880

bootloader:
	nasm -f bin src/bootloader.asm -o bin/bootloader.bin

stdlib:
	bcc -ansi -c -Iinclude src/std_lib.c -o bin/std_lib.o

kernel:
	nasm -f as86 src/kernel.asm -o bin/kernel-asm.o
	bcc -ansi -c -Iinclude src/kernel.c -o bin/kernel.o

link:
	dd if=bin/bootloader.bin of=bin/floppy.img bs=512 count=1 conv=notrunc
	ld86 -o bin/kernel.bin -d bin/kernel.o bin/kernel-asm.o bin/std_lib.o	
	dd if=bin/kernel.bin of=bin/floppy.img bs=512 seek=1 conv=notrunc

build: prepare bootloader stdlib kernel link

run: 
	bochs -f bochsrc.txt
```

- **Penjelasan:**
  1. prepare:
     
     Membuat image disk baru `floppy.img` di direktori `bin/` dengan ukuran 1.44 MB.
     
  2. bootloader:
     
     Mengompilasi file `bootloader.asm` di dalam `src/` yang menghasilkan `booloader.bin` dan disimpan di direktori `bin/`.
     
  3. stdlib:
     
     Mengompilasi file `std_lib.c` di dalam `src/` yang menghasilkan object file `std_lib.o` dan disimpan di direktori `bin/`. Menggunakan `-Iinclude` karena file `std_lib.c` menggunakan header.
     
  4. kernel:
     
     - Mengompilasi file `kernel.asm` di dalam `src/` yang menghasilkan object file `kernel-asm.o` dan disimpan di direktori `bin/`.
     - Mengompilasi file `kernel.c` di dalam `src/` yang menghasilkan object file `kernel.o` dan disimpan di direktori `bin/`. Menggunakan `-Iinclude` karena file `kernel.c` menggunakan header.
       
  5. link:
      
     - Menulis file `bootloader.bin` di dalam `bin/` ke sektor pertama `floopy.img`.
     - Menggabungkan file `bootloader.bin`, `kernel.o`, `kernel_asm.o`, dan `std_lib.o` dalam `bin/` menjadi executable (satu binary kernel).
     - Menulis file `kernel.bin` di dalam `bin/` pada blok ke-1 `seek=1` setelah bootloader.
       
  6. build:
     
      Menjalankan tahapan `prepare`, `bootloader`, `stdlib`, `kernel`, dan `link` secara berurutan.
     
  7. run:
     
     Menjalankan `floopy.img` hasil build menggunakan `bochs` dan menggunakan file configurasi `bochsrc.txt`.

- **Screenshot:**

  **make build**

  ![buildimg](https://drive.google.com/uc?id=1aCc4jFOImP0lPeDvgcSgy6M9T4gcwS_2)

  **make run**

  ![runimg](https://drive.google.com/uc?id=10qeMZ_bBnKO49bM_qhjBXxUHEPR-aXt7)

  **Tampilan bochs**

  ![bochsimg](https://drive.google.com/uc?id=1Co2w_y-OgUlX3pIUjzrXUaKA-NoKaK2y)
