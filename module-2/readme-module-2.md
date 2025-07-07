# praktikum-sisop-modul2

[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/9LcL5VTQ)
|    NRP     |      Name      |
| :--------: | :------------: |
| 5025241133 | Muhammad Abid Baihaqi Al Faridzi |
| 5025241150 | Nabila Shafa Rahayu |
| 5025241153 | Kamal Zaki Adinata |

# Praktikum Modul 2 _(Module 2 Lab Work)_

</div>


### Daftar Soal _(Task List)_

- [Task 1 - Trabowo & Peddy Movie Night](/task-1/)

- [Task 2 - Organize and Analyze Anthony's Favorite Films](/task-2/)

- [Task 3 - Cella’s Manhwa](/task-3/)

- [Task 4 - Pipip's Load Balancer](/task-4/)

### Laporan Resmi Praktikum Modul 2 _(Module 2 Lab Work Report)_

## Task 1 - Trabowo & Peddy Movie Night
Trabowo dan sahabatnya, Peddy, sedang menikmati malam minggu di rumah sambil mencari film seru untuk ditonton. Mereka menemukan sebuah file ZIP yang berisi gambar-gambar poster film yang sangat menarik. File tersebut dapat diunduh dari **[Google Drive](https://drive.google.com/file/d/1nP5kjCi9ReDk5ILgnM7UCnrQwFH67Z9B/view?usp=sharing)**. Karena penasaran dengan film-film tersebut, mereka memutuskan untuk membuat sistem otomatis guna mengelola semua file tersebut secara terstruktur dan efisien. Berikut adalah tugas yang harus dikerjakan untuk mewujudkan sistem tersebut:

### **a. Ekstraksi File ZIP**

Trabowo langsung mendownload file ZIP tersebut dan menyimpannya di penyimpanan lokal komputernya. Namun, karena file tersebut dalam bentuk ZIP, Trabowo perlu melakukan unzip agar dapat melihat daftar film-film seru yang ada di dalamnya.

<b>Code</b>
```
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t child_pid = fork();

    if(child_pid == 0){
        execlp("sh", "sh", "-c", "wget -q -O film.zip \"https://drive.usercontent.google.com/u/0/uc?id=1nP5kjCi9ReDk5ILgnM7UCnrQwFH67Z9B&export=download\" && unzip -q film.zip && rm film.zip", NULL);
        exit(1);
    }

    int status;
    waitpid(child_pid, &status, 0);

    return 0;
}
```

<b>Output</b>

<b>Sebelum</b>

![sebelum a](https://drive.google.com/uc?id=19DrAUOqnLNpDs_U_UJsijcbZrK3JYWuK)

<b>Sesudah</b>

![sesudah a](https://drive.google.com/uc?id=1uyQPUTP7zGDG-uiFR_jaKySGJ_X2uxTY)

![film](https://drive.google.com/uc?id=17VEzwGV1VgkHPfzp5Xm7RbVOYtDyrOtQ)

<b>Penjelasan</b>
```
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
```
- `stdio.h`: Mengakses fungsi input/output standar.
- `unistd.h`: Mengakses fungsi-fungsi POSIX seperti `fork()` dan `execlp()`.
- `sys/types.h`: Untuk tipe data `pid_t`.
- `sys/wait.h`: Mengakses fungsi `waitpid()`.
- `stdlib.h`: Mengakses fungsi seperti `exit()`.

```
pid_t child_pid = fork();
```
Membuat proses baru (child process), `child_pid` menyimpan PID dari child process pada parent process dan akan bernilai 0 untuk child process.

```
if(child_pid == 0){
        execlp("sh", "sh", "-c", "wget -q -O film.zip \"https://drive.usercontent.google.com/u/0/uc?id=1nP5kjCi9ReDk5ILgnM7UCnrQwFH67Z9B&export=download\" && unzip -q film.zip && rm film.zip", NULL);
        exit(1);
    }
```
Melakukan pengondisian/pengecekan apakah proses ini termasuk child process (child_pid == 0), jika ya maka akan menjalankan blok kode di bawahnya.
- `execlp()` akan menggantikan child process dengan proses baru (`sh`), sehingga kode setelahnya tidak akan dijalankan kecuali terjadi error.
- Menggunakan parameter `sh` untuk menjalankan shell dan `-c` untuk mengeksekusi string command.
- `wget -q -O film.zip "url"`: Mengunduh file dari URL Google Drive dari soal dengan menggunakan nama `film.zip` secara silent.
- `unzip -q film.zip`: Mengekstrak file `film.zip` secara silent.
- `rm film.zip`: Menghapus file zip setelah diekstrak.
- `exit(1)`: Jika `execlp()` gagal, maka child process keluar dengan kode error 1.

```
int status;
waitpid(child_pid, &status, 0);
```
- Membuat variabel `status` di parent process untuk menyimpan exit status dari child process.
- `waitpid(child_pid, &status, 0)` akan membuat parent process menunggu hingga child process dengan id `child_pid` selesai dieksekusi.

### **b. Pemilihan Film Secara Acak**
Setelah berhasil melakukan unzip, Trabowo iseng melakukan pemilihan secara acak/random pada gambar-gambar film tersebut untuk menentukan film pertama yang akan dia tonton malam ini.

<b>Code</b>
```
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t child_pid = fork();

    if(child_pid == 0) {
        execlp("sh", "sh", "-c" ,"echo \"Film for Trabowo & Peddy: ‘$(ls film | shuf -n 1)’\"", NULL);
        exit(1);
    }

    int status;
    waitpid(child_pid, &status, 0);

    return 0;
}
```

<b>Output</b>

![output b](https://drive.google.com/uc?id=1q6ubIeVMtngJ4C0dai8S6uzACY4bq88b)

<b>Penjelasan</b>
```
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
```
- `stdio.h`: Mengakses fungsi input/output standar.
- `unistd.h`: Mengakses fungsi-fungsi POSIX seperti `fork()` dan `execlp()`.
- `sys/types.h`: Untuk tipe data `pid_t`.
- `sys/wait.h`: Mengakses fungsi `waitpid()`.
- `stdlib.h`: Mengakses fungsi seperti `exit()`.

```
pid_t child_pid = fork();
```
Membuat proses baru (child process), `child_pid` menyimpan PID dari child process pada parent process dan akan bernilai 0 untuk child process.

```
if(child_pid == 0) {
        execlp("sh", "sh", "-c" ,"echo \"Film for Trabowo & Peddy: ‘$(ls film | shuf -n 1)’\"", NULL);
        exit(1);
    }
```
Melakukan pengondisian/pengecekan apakah proses ini termasuk child process (child_pid == 0), jika ya maka akan menjalankan blok kode di bawahnya.
- `execlp()` akan menggantikan child process dengan proses baru (`sh`), sehingga kode setelahnya tidak akan dijalankan kecuali terjadi error.
- Menggunakan parameter `sh` untuk menjalankan shell dan `-c` untuk mengeksekusi string command.
- `ls film`: Menampilkan seluruh file yang ada di direktori `film`.
- `shuf -n 1`: Mengambil 1 file secara acak untuk ditampilkan dari `ls film`.
- `exit(1)`: Jika `execlp()` gagal, maka child process keluar dengan kode error 1.

```
int status;
waitpid(child_pid, &status, 0);
```
- Membuat variabel `status` di parent process untuk menyimpan exit status dari child process.
- `waitpid(child_pid, &status, 0)` akan membuat parent process menunggu hingga child process dengan id `child_pid` selesai dieksekusi.

### **c. Memilah Film Berdasarkan Genre**
Karena Trabowo sangat perfeksionis dan ingin semuanya tertata rapi, dia memutuskan untuk mengorganisir film-film tersebut berdasarkan genre. Dia membuat 3 direktori utama di dalam folder ~/film, yaitu:
- **FilmHorror**
- **FilmAnimasi**
- **FilmDrama**

Setelah itu, dia mulai memindahkan gambar-gambar film ke dalam folder yang sesuai dengan genrenya. Tetapi Trabowo terlalu tua untuk melakukannya sendiri, sehingga ia meminta bantuan Peddy untuk memindahkannya. Mereka membagi tugas secara efisien dengan mengerjakannya secara bersamaan (overlapping) dan membaginya sama banyak. Trabowo akan mengerjakan dari awal, sementara Peddy dari akhir. Misalnya, jika ada 10 gambar, Trabowo akan memulai dari gambar pertama, gambar kedua, dst dan Peddy akan memulai dari gambar kesepuluh, gambar kesembilan, dst. Lalu buatlah file “recap.txt” yang menyimpan log setiap kali mereka selesai melakukan task.
Setelah memindahkan semua film, Trabowo dan Peddy juga perlu menghitung jumlah film dalam setiap kategori dan menuliskannya dalam file **`total.txt`**.

<b>Code</b>
```
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t child_pid = fork();

    if(child_pid == 0) {
        execlp("sh", "sh", "-c" ,"mkdir ./film/FilmHorror && mkdir ./film/FilmAnimasi && mkdir ./film/FilmDrama", NULL);
        exit(1);
    }

    int status;
    waitpid(child_pid, &status, 0);

    pid_t t_pid = fork();
    if(t_pid == 0){
        execlp("bash", "bash", "-c",
            "arrfile=($(ls film | grep jpg | sort -h)) && "
            "mid=$((${#arrfile[@]} / 2)) && "
            "for ((i=0; i<mid; i++)); do "
                "temp=${arrfile[$i]};"
                "genre=$(echo $temp | cut -d'_' -f3 | cut -d'.' -f1);"
                "mv \"./film/$temp\" \"./film/Film${genre^}\"; "
                "echo \"[$(date +'%d-%m-%Y %H-%M-%S')] Trabowo: $temp telah dipindahkan ke Film${genre^}\">>recap.txt; "
                "done", NULL
            );
        
        exit(1);

    }

    pid_t p_pid = fork();
    if(p_pid == 0){
        execlp("bash", "bash", "-c",
            "arrfile=($(ls film | grep jpg | sort -h)) && "
            "mid=$((${#arrfile[@]} / 2)) && "
            "for ((i=${#arrfile[@]}-1; i>=mid; i--)); do "
                "temp=${arrfile[$i]};"
                "genre=$(echo $temp | cut -d'_' -f3 | cut -d'.' -f1);"
                "mv \"./film/$temp\" \"./film/Film${genre^}\"; "
                "echo \"[$(date +'%d-%m-%Y %H-%M-%S')] Peddy: $temp telah dipindahkan ke Film${genre^}\">>recap.txt; "
                "done", NULL
            );
        
        exit(1);

    }

    int tstatus, pstatus;
    waitpid(t_pid, &tstatus, 0);
    waitpid(p_pid, &pstatus, 0);

    pid_t most_pid = fork();
    if(most_pid == 0){
        execlp("bash", "bash", "-c",
            "horror=$(ls ./film/FilmHorror | awk \'{count++} END {print count}\') && "
            "animasi=$(ls ./film/FilmAnimasi | awk \'{count++} END {print count}\') && "
            "drama=$(ls ./film/FilmDrama | awk \'{count++} END {print count}\') && "
            "arrtotal=($horror $animasi $drama) && "
            "arrjenis=(\'horror\' \'animasi\' \'drama\') && "
            "max=${arrtotal[0]} && "
            "most=${arrjenis[0]} &&"
            "for ((i=1; i < ${#arrtotal[@]}; i++)); do "
                "if [[ ${arrtotal[$i]} > $max ]]; then "
                    "max=${arrtotal[$i]}; "
                    "most=${arrjenis[$i]}; fi "
            "done && "
            "echo \"Jumlah film horror: \"$horror >> total.txt && "
            "echo \"Jumlah film animasi: \"$animasi >> total.txt && "
            "echo \"Jumlah film drama: \"$drama >> total.txt && "
            "echo \"Genre dengan jumlah film terbanyak: \"$most >> total.txt", NULL);
        
        exit(1);

    }

    int statusmost;
    waitpid(most_pid, &statusmost, 0);

    return 0;
}
```

<b>Output</b>

<b>Tampilan recap.txt</b>

![recap](https://drive.google.com/uc?id=1kU5W2jmtO4VQ7hqIPthGrSHzUrT-dsTY)

<b>Tampilan total.txt</b>

![total](https://drive.google.com/uc?id=1ikH0dHVR193YX4sq4HocDh44QYLb195E)

<b>Penjelasan</b>
```
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
```
- `stdio.h`: Mengakses fungsi input/output standar.
- `unistd.h`: Mengakses fungsi-fungsi POSIX seperti `fork()` dan `execlp()`.
- `sys/types.h`: Untuk tipe data `pid_t`.
- `sys/wait.h`: Mengakses fungsi `waitpid()`.
- `stdlib.h`: Mengakses fungsi seperti `exit()`.
```
pid_t child_pid = fork();
```
Membuat proses baru (child process pertama), `child_pid` menyimpan PID dari child process pada parent process dan akan bernilai 0 untuk child process.

```
if(child_pid == 0) {
        execlp("sh", "sh", "-c" ,"mkdir ./film/FilmHorror && mkdir ./film/FilmAnimasi && mkdir ./film/FilmDrama", NULL);
        exit(1);
    }
```
Melakukan pengondisian/pengecekan apakah proses ini termasuk child process (child_pid == 0), jika ya maka akan menjalankan blok kode di bawahnya.
- `execlp()` akan menggantikan child process dengan proses baru (`sh`), sehingga kode setelahnya tidak akan dijalankan kecuali terjadi error.
- Menggunakan parameter `sh` untuk menjalankan shell dan `-c` untuk mengeksekusi string command.
- Membuat direktori `FilmHorror`, `FilmAnimasi`, dan `FilmDrama` di dalam direktori `film` menggunakan `mkdir`.
- `exit(1)`: Jika `execlp()` gagal, maka child process keluar dengan kode error 1.

```
int status;
waitpid(child_pid, &status, 0);
```
- Membuat variabel `status` di parent process untuk menyimpan exit status dari child process.
- `waitpid(child_pid, &status, 0)` akan membuat parent process menunggu hingga child process dengan id `child_pid` selesai dieksekusi.

```
pid_t t_pid = fork();
```
Membuat proses baru (child process kedua), `t_pid` menyimpan PID dari child process pada parent process dan akan bernilai 0 untuk child process.

```
if(t_pid == 0){
        execlp("bash", "bash", "-c",
            "arrfile=($(ls film | grep jpg | sort -h)) && "
            "mid=$((${#arrfile[@]} / 2)) && "
            "for ((i=0; i<mid; i++)); do "
                "temp=${arrfile[$i]};"
                "genre=$(echo $temp | cut -d'_' -f3 | cut -d'.' -f1);"
                "mv \"./film/$temp\" \"./film/Film${genre^}\"; "
                "echo \"[$(date +'%d-%m-%Y %H-%M-%S')] Trabowo: $temp telah dipindahkan ke Film${genre^}\">>recap.txt; "
                "done", NULL
            );
        
        exit(1);

    }
```
Melakukan pengondisian/pengecekan apakah proses ini termasuk child process (t_pid == 0), jika ya maka akan menjalankan blok kode di bawahnya.
- `execlp()` akan menggantikan child process dengan proses baru (`bash`), sehingga kode setelahnya tidak akan dijalankan kecuali terjadi error.
- Menggunakan parameter `bash` untuk menjalankan bash dan `-c` untuk mengeksekusi string command.
- `arrfile=($(ls film | grep jpg | sort -h))`: Membaca semua file di direktori `film` yang mengandung `jpg` pada namanya, lalu mengurutkannya secara numerik (`sort -h`) dan menyimpannya sebagai array `arrfile`.
- `mid=$((${#arrfile[@]} / 2))`: Menghitung indeks tengah dari array `arrfile` yang merupakan setengah dari jumlah total file.
```
"for ((i=0; i<mid; i++)); do "
        "temp=${arrfile[$i]};"
        "genre=$(echo $temp | cut -d'_' -f3 | cut -d'.' -f1);"
        "mv \"./film/$temp\" \"./film/Film${genre^}\"; "
        "echo \"[$(date +'%d-%m-%Y %H-%M-%S')] Trabowo: $temp telah dipindahkan ke Film${genre^}\">>recap.txt; "
        "done", NULL
    );
```
Loop dari indeks 0 sampai sebelum `mid`.
- `temp=${arrfile[$i]}`: Mengambil nama file pada indeks ke-i.
- `genre=$(echo $temp | cut -d'_' -f3 | cut -d'.' -f1)`: Mengambil bagian ketiga nama file sebagai genre, lalu mengambil bagian pertama untuk menghapus ekstensi `.jpg`.
- `mv "./film/$temp" "./film/Film${genre^}"`: Memindahkan file ke direktori genre yang sesuai. `${genre^}` mengubah huruf depan menjadi kapital.
- `echo "[$(date +'%d-%m-%Y %H-%M-%S')] Trabowo: $temp telah dipindahkan ke Film${genre^}">>recap.txt`: Mencatat output ke file `recap.txt` dengan format sesuai soal. 

- `exit(1)`: Jika `execlp()` gagal, maka child process keluar dengan kode error 1.

```
pid_t p_pid = fork();
```
Membuat proses baru (child process ketiga), `p_pid` menyimpan PID dari child process pada parent process dan akan bernilai 0 untuk child process. Proses ini akan dijalankan secara overlapping dengan proses kedua.

```
if(p_pid == 0){
        execlp("bash", "bash", "-c",
            "arrfile=($(ls film | grep jpg | sort -h)) && "
            "mid=$((${#arrfile[@]} / 2)) && "
            "for ((i=${#arrfile[@]}-1; i>=mid; i--)); do "
                "temp=${arrfile[$i]};"
                "genre=$(echo $temp | cut -d'_' -f3 | cut -d'.' -f1);"
                "mv \"./film/$temp\" \"./film/Film${genre^}\"; "
                "echo \"[$(date +'%d-%m-%Y %H-%M-%S')] Peddy: $temp telah dipindahkan ke Film${genre^}\">>recap.txt; "
                "done", NULL
            );
        
        exit(1);

    }
```
Melakukan pengondisian/pengecekan apakah proses ini termasuk child process (p_pid == 0), jika ya maka akan menjalankan blok kode di bawahnya.
- `execlp()` akan menggantikan child process dengan proses baru (`bash`), sehingga kode setelahnya tidak akan dijalankan kecuali terjadi error.
- Menggunakan parameter `bash` untuk menjalankan bash dan `-c` untuk mengeksekusi string command.
- `arrfile=($(ls film | grep jpg | sort -h))`: Membaca semua file di direktori `film` yang mengandung `jpg` pada namanya, lalu mengurutkannya secara numerik (`sort -h`) dan menyimpannya sebagai array `arrfile`.
- `mid=$((${#arrfile[@]} / 2))`: Menghitung indeks tengah dari array `arrfile` yang merupakan setengah dari jumlah total file.
```
"for ((i=${#arrfile[@]}-1; i>=mid; i--)); do "
        "temp=${arrfile[$i]};"
        "genre=$(echo $temp | cut -d'_' -f3 | cut -d'.' -f1);"
        "mv \"./film/$temp\" \"./film/Film${genre^}\"; "
        "echo \"[$(date +'%d-%m-%Y %H-%M-%S')] Peddy: $temp telah dipindahkan ke Film${genre^}\">>recap.txt; "
        "done", NULL
    );
```
Loop dari indeks terakhir sampai `mid`.
- `temp=${arrfile[$i]}`: Mengambil nama file pada indeks ke-i.
- `genre=$(echo $temp | cut -d'_' -f3 | cut -d'.' -f1)`: Mengambil bagian ketiga nama file sebagai genre, lalu mengambil bagian pertama untuk menghapus ekstensi `.jpg`.
- `mv "./film/$temp" "./film/Film${genre^}"`: Memindahkan file ke direktori genre yang sesuai. `${genre^}` mengubah huruf depan menjadi kapital.
- `echo "[$(date +'%d-%m-%Y %H-%M-%S')] Peddy: $temp telah dipindahkan ke Film${genre^}">>recap.txt`: Mencatat output ke file `recap.txt` dengan format sesuai soal. 

- `exit(1)`: Jika `execlp()` gagal, maka child process keluar dengan kode error 1.

```
int tstatus, pstatus;
waitpid(t_pid, &tstatus, 0);
waitpid(p_pid, &pstatus, 0);
```
- Membuat variabel `tstatus` dan `pstatus` di parent process untuk menyimpan exit status dari child process.
- `waitpid(t_pid, &tstatus, 0)` dan `waitpid(p_pid, &pstatus, 0)` akan membuat parent process menunggu hingga child process kedua dan ketiga selesai dieksekusi.

```
pid_t most_pid = fork();
```
Membuat proses baru (child process keempat), `most_pid` menyimpan PID dari child process pada parent process dan akan bernilai 0 untuk child process.
```
if(most_pid == 0){
        execlp("bash", "bash", "-c",
            "horror=$(ls ./film/FilmHorror | awk \'{count++} END {print count}\') && "
            "animasi=$(ls ./film/FilmAnimasi | awk \'{count++} END {print count}\') && "
            "drama=$(ls ./film/FilmDrama | awk \'{count++} END {print count}\') && "
            "arrtotal=($horror $animasi $drama) && "
            "arrjenis=(\'horror\' \'animasi\' \'drama\') && "
            "max=${arrtotal[0]} && "
            "most=${arrjenis[0]} &&"
            "for ((i=1; i < ${#arrtotal[@]}; i++)); do "
                "if [[ ${arrtotal[$i]} > $max ]]; then "
                    "max=${arrtotal[$i]}; "
                    "most=${arrjenis[$i]}; fi "
            "done && "
            "echo \"Jumlah film horror: \"$horror >> total.txt && "
            "echo \"Jumlah film animasi: \"$animasi >> total.txt && "
            "echo \"Jumlah film drama: \"$drama >> total.txt && "
            "echo \"Genre dengan jumlah film terbanyak: \"$most >> total.txt", NULL);
        
        exit(1);

    }
```
Melakukan pengondisian/pengecekan apakah proses ini termasuk child process (most_pid == 0), jika ya maka akan menjalankan blok kode di bawahnya.
- `execlp()` akan menggantikan child process dengan proses baru (`bash`), sehingga kode setelahnya tidak akan dijalankan kecuali terjadi error.
- Menggunakan parameter `bash` untuk menjalankan bash dan `-c` untuk mengeksekusi string command.
- `horror=$(ls ./film/FilmHorror | awk '{count++} END {print count}')`: Menampilkan file yang berada di direktori `FilmHorror` dengan `ls` lalu menghitung jumlah filenya menggunakan `awk`. Proses ini juga digunakan pada variabel `animasi` untuk menghitung jumlah file yang berada di direktori `FilmAnimasi` dan variabel `drama` untuk menghitung jumlah file yang berada di direktori `FilmDrama`.
- `arrtotal=($horror $animasi $drama)`: Menyimpan jumlah file setiap genre dalam array `arrtotal`.
- `arrjenis=('horror' 'animasi' 'drama')`: Menyimpan setiap nama genre dalam array `arrjenis`.
- `max=${arrtotal[0]}` dan `most=${arrjenis[0]}`: Inisialisasi `max` dengan jumlah file genre pertama dan `most` dengan nama genre pertama.

```
for ((i=1; i < ${#arrtotal[@]}; i++)); do "
        "if [[ ${arrtotal[$i]} > $max ]]; then "
            "max=${arrtotal[$i]}; "
            "most=${arrjenis[$i]}; fi "
    "done
```
Loop dari indeks 1 sampai indeks terakhir `arrtotal` untuk mencari genre dengan jumlah terbanyak.
- Jika elemen ke-i pada `arrtotal` lebih besar dari `max`, update `max` dan `most`, hingga mendapat elemen dengan jumlah terbesar.

```
"echo \"Jumlah film horror: \"$horror >> total.txt && "
"echo \"Jumlah film animasi: \"$animasi >> total.txt && "
"echo \"Jumlah film drama: \"$drama >> total.txt && "
"echo \"Genre dengan jumlah film terbanyak: \"$most >> total.txt"
```
Mencatat jumlah film untuk setiap genre dan genre dengan jumlah terbanyak di `total.txt` dengan format sesuai soal.

- `exit(1)`: Jika `execlp()` gagal, maka child process keluar dengan kode error 1.

```
int statusmost;
waitpid(most_pid, &statusmost, 0);
```
- Membuat variabel `statusmost` di parent process untuk menyimpan exit status dari child process.
- `waitpid(most_pid, &statusmost, 0)` akan membuat parent process menunggu hingga child process dengan id `most_pid` selesai dieksekusi.

### **d. Pengarsipan Film**
Setelah semua film tertata dengan rapi dan dikelompokkan dalam direktori masing-masing berdasarkan genre, Trabowo ingin mengarsipkan ketiga direktori tersebut ke dalam format ZIP agar tidak memakan terlalu banyak ruang di komputernya.

<b>Code</b>
```
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t child_pid = fork();
    if(child_pid == 0){
        execlp("sh", "sh", "-c", "zip -rq film.zip ./film/*Film* && rm -rf film", NULL);
        exit(1);
    }

    int status;
    waitpid(child_pid, &status, 0);

    return 0;
}
```

<b>Output</b>

![output d](https://drive.google.com/uc?id=1hSEsHZBbR3oQ2l5dVVwInv7oQ3EXeScY)

<b>Penjelasan</b>
```
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
```
- `stdio.h`: Mengakses fungsi input/output standar.
- `unistd.h`: Mengakses fungsi-fungsi POSIX seperti `fork()` dan `execlp()`.
- `sys/types.h`: Untuk tipe data `pid_t`.
- `sys/wait.h`: Mengakses fungsi `waitpid()`.
- `stdlib.h`: Mengakses fungsi seperti `exit()`.

```
pid_t child_pid = fork();
```
Membuat proses baru (child process), `child_pid` menyimpan PID dari child process pada parent process dan akan bernilai 0 untuk child process.

```
if(child_pid == 0) {
        execlp("sh", "sh", "-c", "zip -rq film.zip ./film/\*Film\* && rm -rf film", NULL);
        exit(1);
    }
```
Melakukan pengondisian/pengecekan apakah proses ini termasuk child process (child_pid == 0), jika ya maka akan menjalankan blok kode di bawahnya.
- `execlp()` akan menggantikan child process dengan proses baru (`sh`), sehingga kode setelahnya tidak akan dijalankan kecuali terjadi error.
- `zip -rq film.zip ./film/*Film*`: Melakukan zip untuk setiap direktori yang mengandung nama `Film` di dalam direktori `film` secara rekursif dan silent.
- `rm -rf film`: Menghapus direktori `film` beserta isinya setelah proses zip selesai.
- `exit(1)`: Jika `execlp()` gagal, maka child process keluar dengan kode error 1.

```
int status;
waitpid(child_pid, &status, 0);
```
- Membuat variabel `status` di parent process untuk menyimpan exit status dari child process.
- `waitpid(child_pid, &status, 0)` akan membuat parent process menunggu hingga child process dengan id `child_pid` selesai dieksekusi.

## Task 2 - Organize and Analyze Anthony's Favorite Films

Anthony sedang asyik menonton film favoritnya dari Netflix, namun seiring berjalannya waktu, koleksi filmnya semakin menumpuk. Ia pun memutuskan untuk membuat sistem agar film-film favoritnya bisa lebih terorganisir dan mudah diakses. Anthony ingin melakukan beberapa hal dengan lebih efisien dan serba otomatis.

> Film-film yang dimaksud adalah film-film yang ada di dalam file ZIP yang bisa diunduh dari **[Google Drive](https://drive.google.com/file/d/12GWsZbSH858h2HExP3x4DfWZB1jLdV-J/view?usp=drive_link)**.

Berikut adalah serangkaian tugas yang Anthony ingin capai untuk membuat pengalaman menonton filmnya jadi lebih menyenangkan:

### **a. One Click and Done!**

Pernahkah kamu merasa malas untuk mengelola file ZIP yang penuh dengan data film? Anthony merasa hal yang sama, jadi dia ingin semuanya serba instan dengan hanya satu perintah. Dengan satu perintah saja, Anthony bisa:

- Mendownload file ZIP yang berisi data film-film Netflix favoritnya.
- Mengekstrak file ZIP tersebut ke dalam folder yang sudah terorganisir.
- Menghapus file ZIP yang sudah tidak diperlukan lagi, supaya tidak memenuhi penyimpanan.

Buatlah skrip yang akan mengotomatiskan proses ini sehingga Anthony hanya perlu menjalankan satu perintah untuk mengunduh, mengekstrak, dan menghapus file ZIP.

<b>Code</b>
```
void downloadextract(){
    int i;
    pid_t pid;
    for (i = 0; i < 3; i++)
    {
        pid = fork();
        
        if (pid == 0)
        {
        if (i == 0)
        {
            char *argv[]={"wget","wget","-q","-p","https://docs.google.com/uc?export=download&id=12GWsZbSH858h2HExP3x4DfWZB1jLdV-J","-O","/home/pardofelis/Downloads/netflixData.zip", NULL};
            execv("/bin/wget", argv);
            exit (0);
        } else if (i == 1)
        {
            char *argv[]={"unzip","-n","-q","/home/pardofelis/Downloads/netflixData.zip","-d","/home/pardofelis/Downloads/NetflixTask2", NULL};
            execv("/bin/unzip", argv);
            exit (0);
        } else if (i == 2)
        {
            char *argv[]={"rm","/home/pardofelis/Downloads/netflixData.zip", NULL};
            execv("/bin/rm", argv);
            exit (0);
        }
    }   else {
        wait(NULL);}
    }
}
```
<b>Output</b>

![gambar1](https://drive.google.com/uc?id=1-hM7jL7z50q7RcXC1gcnNeHwU0YQBAac)

<b>Penjelasan</b>
- `int i;
    pid_t pid;`

  inisialisasi untuk memulai proses fork
- `for (i = 0; i < 3; i++)
    {
        pid = fork();
        
        if (pid == 0)
        {
        if (i == 0)
        {
            char *argv[]={"wget","wget","-q","-p","https://docs.google.com/uc?export=download&id=12GWsZbSH858h2HExP3x4DfWZB1jLdV-J","-O","/home/pardofelis/Downloads/netflixData.zip", NULL};
            execv("/bin/wget", argv);
            exit (0);
        } else if (i == 1)
        {
            char *argv[]={"unzip","-n","-q","/home/pardofelis/Downloads/netflixData.zip","-d","/home/pardofelis/Downloads/NetflixTask2", NULL};
            execv("/bin/unzip", argv);
            exit (0);
        } else if (i == 2)
        {
            char *argv[]={"rm","/home/pardofelis/Downloads/netflixData.zip", NULL};
            execv("/bin/rm", argv);
            exit (0);
        }
    }   else {
        wait(NULL);}
    }`

    Jadi untuk melakukan 3 task secara berurutan diperlukan fork 3 kali, saya menggunakan for loop sebagai struktur pengulangan untuk fork 3 kali. untuk melakukan fork, assign fork() ke dalam pid yang sebelumnya telah diinisiasi di luar pengulangan for loop. Di dalam for loop, terdapat if else untuk membedakan tugas dari parent dan children berupa 'if (pid == 0) {} else {}'. kemudian, di dalam if else ini, ada if else lagi yang memetakan tugas tugas yang harus dikerjakan tiap children. dengan i == 0, menandakan bahwa pada iterasi 1 (karena loop dimulai dari i == 0) children akan mendownload file dari link yang telah disediakan dan menaruhnya di path yang sudah  di-assign dengan menggunakan -o, program ini bisa berjalan dengan menggunakan execv dan exit(0) (exit(0) digunakan agar program tidak mennjalankan program lain selain yang diassign pada execv). di if i -- 0, file yang tadi telah didownload kemudian di unzip dan hasil unzipnya ditempatkan di tempat dan folder yang diinginkan (di sini aku menaruhnya di folder baru yaitu NetflixTask2) sama seperti di i == o aku juga menggunakan exit(0) di sini. terakhir, pada i == 2 aku menghapus file sisa zip yang tadinya didownload menggunakan perintah rm.

### **b. Sorting Like a Pro**

Koleksi film Anthony semakin banyak dan dia mulai bingung mencari cara yang cepat untuk mengelompokkannya. Nah, Anthony ingin mengelompokkan film-filmnya dengan dua cara yang sangat mudah:

1. Berdasarkan huruf pertama dari judul film.
2. Berdasarkan tahun rilis (release year).

Namun, karena Anthony sudah mempelajari **multiprocessing**, dia ingin mengelompokkan di for kedua kategori ini secara paralel untuk menghemat waktu.

**Struktur Output:**

- **Berdasarkan Huruf Pertama Judul Film:**

  - Folder: `judul/`
  - Setiap file dinamai dengan huruf abjad atau angka, seperti `A.txt`, `B.txt`, atau `1.txt`.
  - Jika judul film tidak dimulai dengan huruf atau angka, film tersebut disimpan di file `#.txt`.

- **Berdasarkan Tahun Rilis:**
  - Folder: `tahun/`
  - Setiap file dinamai sesuai tahun rilis film, seperti `1999.txt`, `2021.txt`, dst.

Format penulisan dalam setiap file :

```
Judul Film - Tahun Rilis - Sutradara
```

Setiap proses yang berjalan akan mencatat aktivitasnya ke dalam satu file bernama **`log.txt`** dengan format:

```
[jam:menit:detik] Proses mengelompokkan berdasarkan [Abjad/Tahun]: sedang mengelompokkan untuk film [judul_film]
```

**Contoh Log:**

```
[14:23:45] Proses mengelompokkan berdasarkan Abjad: sedang mengelompokkan untuk film Avengers: Infinity War
[14:23:46] Proses mengelompokkan berdasarkan Tahun: sedang mengelompokkan untuk film Kung Fu Panda
```
<b>Code</b>
```
void organizefile(){
    int i;
    pid_t pid;
    for (i = 0; i < 2; i++)
    {
        pid = fork();
        
        if (pid == 0)
        {
        if (i == 0)
        {
            char *argv[]={"mkdir","-p","/home/pardofelis/Downloads/NetflixTask2/Judul", NULL};
            execv("/bin/mkdir", argv);
            exit(0);
        } else if (i == 1)
        {
            char *argv[]={"mkdir","-p","/home/pardofelis/Downloads/NetflixTask2/Tahun", NULL};
            execv("/bin/mkdir", argv);
            exit(0);
        }}
    }

    for ( i = 0; i < 2; i++)
    {

        pid = fork();
        if (pid == 0)
        {
            char baris[1024];
            Film film;
            FILE *file = fopen("/home/pardofelis/Downloads/NetflixTask2/netflixData.csv", "r");

            if (i == 0)
            {

    fgets(baris, sizeof(baris), file);

    while (fgets(baris, sizeof(baris), file))
    {
        char temp[2];
        sscanf(baris, "%1s", temp);
        if ((temp[0] < 'a' || temp[0] > 'z') && (temp[0] < 'A' || temp[0] > 'Z') && (temp[0] < '0' || temp[0] > '9')) {
            temp[0] = '#';
        }
        sscanf(baris, "%255[^,],%255[^,],%255[^,],%d", film.Judul, film.director, film.negara, &film.tahun);
        char namafile[300];
        snprintf(namafile, sizeof(namafile), "/home/pardofelis/Downloads/NetflixTask2/Judul/%s.txt", temp);
        FILE *filekeluar = fopen(namafile, "a");
        fprintf(filekeluar, "%s - %s - %d\n", film.Judul, film.director, film.tahun);
        
        int logpipe[2];
        pipe(logpipe);
        pid_t logger = fork();
        if (logger == 0) {
            close(logpipe[0]);
            dup2(logpipe[1], STDOUT_FILENO); 
            close(logpipe[1]); 
    
            char *argv[] = {"date","+%H:%M:%S", NULL};
            execv("/bin/date", argv);
            exit(1);
        } else {
            close(logpipe[1]); 
            wait(NULL); 
    
            char buffer[512];
            int len = read(logpipe[0], buffer, sizeof(buffer)-1); 
            buffer[len] = '\0';
            buffer[len-1] = '\0';
            FILE *logging = fopen("/home/pardofelis/Downloads/NetflixTask2/log.txt", "a");
            fprintf(logging, "[%s] Proses mengelompokkan berdasarkan Abjad: sedang mengelompokkan untuk film %s\n", buffer, film.Judul);
            close(logpipe[0]);
            fclose(filekeluar);
        }
    }
    exit(0);
    }   else if (i == 1)
    {
    char baris[1024];
    Film film;
    FILE *file = fopen("/home/pardofelis/Downloads/NetflixTask2/netflixData.csv", "r");

    fgets(baris, sizeof(baris), file);

    while (fgets(baris, sizeof(baris), file))
    {
        sscanf(baris, "%255[^,],%255[^,],%255[^,],%d", film.Judul, film.director, film.negara, &film.tahun);
        char namafile[300];
        snprintf(namafile, sizeof(namafile), "/home/pardofelis/Downloads/NetflixTask2/Tahun/%d.txt", film.tahun);
        FILE *filekeluar = fopen(namafile, "a");
        fprintf(filekeluar, "%s - %s - %d\n", film.Judul, film.director, film.tahun);

        int logpipe[2];
        pipe(logpipe);
        pid_t logger = fork();
        if (logger == 0) {
            close(logpipe[0]);
            dup2(logpipe[1], STDOUT_FILENO); 
            close(logpipe[1]); 
    
            char *argv[] = {"date","+%H:%M:%S", NULL};
            execv("/bin/date", argv);
            exit(1);
        } else {
            close(logpipe[1]); 
            wait(NULL); 
    
            char buffer[512];
            int len = read(logpipe[0], buffer, sizeof(buffer)-1); 
            buffer[len] = '\0';
            buffer[len-1] = '\0';
            FILE *logging = fopen("/home/pardofelis/Downloads/NetflixTask2/log.txt", "a");
            fprintf(logging, "[%s] Proses mengelompokkan berdasarkan Tahun: sedang mengelompokkan untuk film %s\n", buffer, film.Judul);
            close(logpipe[0]);
            fclose(filekeluar);
        }
    }
    exit(0);
            }
            fclose(file);
        }
    }
}
```
<b>Output</b>

![gambar2](https://drive.google.com/uc?id=1EeIlkSv4kVGsneT6u1Uab4dAJKUZiCra)

![gambar3](https://drive.google.com/uc?id=1AgcM1H6_xY_JYVmv1M2yHAt3RaEgNfJj)

![gambar4](https://drive.google.com/uc?id=1dk-eJcQZkqPf49R7r2pQF6VERnAIrNAZ)

![gambar5](https://drive.google.com/uc?id=1SCP59WhysSr07JiUUvlM2xjx0Re4gt3m)

![gambar6](https://drive.google.com/uc?id=1wd_0s7qNnmJYx83AfHzIVjAJSnA_WqhE)

<b>Penjelasan</b>
-`nt i;
    pid_t pid;
    for (i = 0; i < 2; i++)
    {
        pid = fork();
        
        if (pid == 0)
        {
        if (i == 0)
        {
            char *argv[]={"mkdir","-p","/home/pardofelis/Downloads/NetflixTask2/Judul", NULL};
            execv("/bin/mkdir", argv);
            exit(0);
        } else if (i == 1)
        {
            char *argv[]={"mkdir","-p","/home/pardofelis/Downloads/NetflixTask2/Tahun", NULL};
            execv("/bin/mkdir", argv);
            exit(0);
        }}
    }`

    sama seperti point A, saya menggunakan for loop untuk menugaskan 2 children untuk membuat 2 folder menggunakan perintah mkdir dengan execv
    
-`pid = fork();
        if (pid == 0)
        {
            char baris[1024];
            Film film;
            FILE *file = fopen("/home/pardofelis/Downloads/NetflixTask2/netflixData.csv", "r");

            if (i == 0)
            {

    fgets(baris, sizeof(baris), file);

    while (fgets(baris, sizeof(baris), file))
    {
        char temp[2];
        sscanf(baris, "%1s", temp);
        if ((temp[0] < 'a' || temp[0] > 'z') && (temp[0] < 'A' || temp[0] > 'Z') && (temp[0] < '0' || temp[0] > '9')) {
            temp[0] = '#';
        }
        sscanf(baris, "%255[^,],%255[^,],%255[^,],%d", film.Judul, film.director, film.negara, &film.tahun);
        char namafile[300];
        snprintf(namafile, sizeof(namafile), "/home/pardofelis/Downloads/NetflixTask2/Judul/%s.txt", temp);
        FILE *filekeluar = fopen(namafile, "a");
        fprintf(filekeluar, "%s - %s - %d\n", film.Judul, film.director, film.tahun);
        
        int logpipe[2];
        pipe(logpipe);
        pid_t logger = fork();
        if (logger == 0) {
            close(logpipe[0]);
            dup2(logpipe[1], STDOUT_FILENO); 
            close(logpipe[1]); 
    
            char *argv[] = {"date","+%H:%M:%S", NULL};
            execv("/bin/date", argv);
            exit(1);
        } else {
            close(logpipe[1]); 
            wait(NULL); 
    
            char buffer[512];
            int len = read(logpipe[0], buffer, sizeof(buffer)-1); 
            buffer[len] = '\0';
            buffer[len-1] = '\0';
            FILE *logging = fopen("/home/pardofelis/Downloads/NetflixTask2/log.txt", "a");
            fprintf(logging, "[%s] Proses mengelompokkan berdasarkan Abjad: sedang mengelompokkan untuk film %s\n", buffer, film.Judul);
            close(logpipe[0]);
            fclose(filekeluar);
        }
    }
    exit(0);
    }   else if (i == 1)
    {
    char baris[1024];
    Film film;
    FILE *file = fopen("/home/pardofelis/Downloads/NetflixTask2/netflixData.csv", "r");

    fgets(baris, sizeof(baris), file);

    while (fgets(baris, sizeof(baris), file))
    {
        sscanf(baris, "%255[^,],%255[^,],%255[^,],%d", film.Judul, film.director, film.negara, &film.tahun);
        char namafile[300];
        snprintf(namafile, sizeof(namafile), "/home/pardofelis/Downloads/NetflixTask2/Tahun/%d.txt", film.tahun);
        FILE *filekeluar = fopen(namafile, "a");
        fprintf(filekeluar, "%s - %s - %d\n", film.Judul, film.director, film.tahun);

        int logpipe[2];
        pipe(logpipe);
        pid_t logger = fork();
        if (logger == 0) {
            close(logpipe[0]);
            dup2(logpipe[1], STDOUT_FILENO); 
            close(logpipe[1]); 
    
            char *argv[] = {"date","+%H:%M:%S", NULL};
            execv("/bin/date", argv);
            exit(1);
        } else {
            close(logpipe[1]); 
            wait(NULL); 
    
            char buffer[512];
            int len = read(logpipe[0], buffer, sizeof(buffer)-1); 
            buffer[len] = '\0';
            buffer[len-1] = '\0';
            FILE *logging = fopen("/home/pardofelis/Downloads/NetflixTask2/log.txt", "a");
            fprintf(logging, "[%s] Proses mengelompokkan berdasarkan Tahun: sedang mengelompokkan untuk film %s\n", buffer, film.Judul);
            close(logpipe[0]);
            fclose(filekeluar);
        }
    }
    exit(0);
            }
            fclose(file);
        }
    }
}`

Pada potongan kode ini, sama seperti penyelesaian sebelumnya saya menggunakan for loop untuk memberi perintah ke pada 2 children:

- children pertama ditugaskan untuk menganalisa file dan menulis kembali judul film yang ada di file csv ke dalam file.txt yang dikelompokkan berdasarkan abjad. untuk mengolah isi file csv, aku melakukan loop pembacaan file menggunakan while (sebelum loop terdapat fgets untuk mengambil line paling atas karena bagian atas adalah header file). loop dengan while ini membaca seluruh line dari file, isi dari line yang diambil ini kemuadian diolah menggunakan sscanf yang membedakan judul, asal negara, sutradara, dan tahun terbit dengan pemisahan berdasarkan delimiter koma. Untuk menentukan abjad apa yang memulai judul film, aku menggunakan sscanf untuk membaca line yang telah disimpan ke dalam variabel baris dan membaca huruf pertama (kebetulan format csv diawali dengan judul film). untuk membuat file dengan nama abjad awal film, snprintf digunakan untuk membuat path yang nanti digunakan dalam fopen. setelah itu, menggunakan fopen untuk membuat file dan menambahkan baris dengan mode a (append) sehingga list tidak tumpang tindih jika melakukan fprintf berkali kali. karena soal meminta untuk membuat log yang disertai dengan waktu hingga detik, maka aku membuat struktur pipe. di struktur pipe ini aku mengambil hasil execv dari date +%H:%M:%S ke dalam variabel buffer. kemudian dengan fopen mode append, aku menambahkan log dari tiap-tiap proses yang sudah diberi waktu yang disimpan pada variabel buffer

- children kedua ditugaskan untuk menganalisa file dan menulis kembali judul film yang ada di file csv ke dalam file.txt yang dikelompokkan berdasarkna abjad. sistematikanya sama seperti pada children pertama, namun pada task kedua ini bisa lebih mudah karena bisa dibandingkan langsung karena kolom ke empat pasti berisi tahun terbit dan tahun terbitnya merupakan integer. sisanya sama seperti children pertama untuk membuat file dengan nama tahun terbit film, snprintf digunakan untuk membuat path yang nanti digunakan dalam fopen. setelah itu, menggunakan fopen untuk membuat file dan menambahkan baris dengan mode a (append) sehingga list tidak tumpang tindih jika melakukan fprintf berkali kali. karena soal meminta untuk membuat log yang disertai dengan waktu hingga detik, maka aku membuat struktur pipe. di struktur pipe ini aku mengambil hasil execv dari date +%H:%M:%S ke dalam variabel buffer. kemudian dengan fopen mode append, aku menambahkan log dari tiap-tiap proses yang sudah diberi waktu yang disimpan pada variabel buffer


### **c. The Ultimate Movie Report**

Sebagai penggemar film yang juga suka menganalisis, Anthony ingin mengetahui statistik lebih mendalam tentang film-film yang dia koleksi. Misalnya, dia ingin tahu berapa banyak film yang dirilis **sebelum tahun 2000** dan **setelah tahun 2000**.

Agar laporan tersebut mudah dibaca, Anthony ingin hasilnya disimpan dalam file **`report_ddmmyyyy.txt`**.

**Format Output dalam Laporan:**

```
i. Negara: <nama_negara>
Film sebelum 2000: <jumlah>
Film setelah 2000: <jumlah>

...
i+n. Negara: <nama_negara>
Film sebelum 2000: <jumlah>
Film setelah 2000: <jumlah>
```

Agar penggunaannya semakin mudah, Anthony ingin bisa menjalankan semua proses di atas melalui sebuah antarmuka terminal interaktif dengan pilihan menu seperti berikut:
1. Download File
2. Mengelompokkan Film
3. Membuat Report

Catatan:
- Dilarang menggunakan `system`
- Harap menggunakan thread dalam pengerjaan soal C

<b>Code</b>
```
void *kerjaanthread(void *arg) {
    char listnegara[256][100] = {{0}};
    int jumlahpernegara[256][2] = {{0}};
    int totalnegara = 0;
    Film film;
    char baris[1024];

    FILE *file = fopen("/home/pardofelis/Downloads/NetflixTask2/netflixData.csv", "r");

    fgets(baris, sizeof(baris), file);

    while (fgets(baris, sizeof(baris), file)) {
        if (strlen(baris) < 5) continue;

        if (sscanf(baris, "%255[^,],%255[^,],%255[^,],%d", film.Judul, film.director, film.negara, &film.tahun) != 4) {
            continue; 
        }
        int index = -1;
        for (int i = 0; i < totalnegara; i++) {
            if (strcmp(listnegara[i], film.negara) == 0) {
                index = i;
                break;
            }
        }

        if (index == -1 && totalnegara < 256) {
            strncpy(listnegara[totalnegara], film.negara, sizeof(listnegara[0]) - 1);
            index = totalnegara;
            totalnegara++;
        }

        if (index != -1) {
            if (film.tahun < 2000) {
                jumlahpernegara[index][0]++;
            } else {
                jumlahpernegara[index][1]++;
            }
        }
    }
    fclose(file);

    int logpipe[2];
    char buffer[512];
        pipe(logpipe);
        pid_t logger = fork();
        if (logger == 0) {
            close(logpipe[0]);
            dup2(logpipe[1], STDOUT_FILENO); 
            close(logpipe[1]); 
    
            char *argv[] = {"date","+%d%m%y", NULL};
            execv("/bin/date", argv);
            exit(1);
        } else {
            close(logpipe[1]); 
            wait(NULL); 
    
            int len = read(logpipe[0], buffer, sizeof(buffer)-1); 
            buffer[len] = '\0';
            buffer[len-1] = '\0';
            close(logpipe[0]);
        }
    
    char namareport[600];
    snprintf(namareport, sizeof(namareport), "/home/pardofelis/Downloads/NetflixTask2/report_%s.txt", buffer);
    FILE *fileout = fopen(namareport, "a");

    for (int i = 0; i < totalnegara; i++) {
        fprintf(fileout, "%d. Negara: %s\n", i+1, listnegara[i]);
        fprintf(fileout, "Film sebelum 2000: %d\n", jumlahpernegara[i][0]);
        fprintf(fileout, "Film setelah 2000: %d\n", jumlahpernegara[i][1]);
    }
    fclose(fileout);

    return NULL;
}

int main(){
    pthread_t t1;
    int pilihan;
    
    do {
        printf("Menu \n");
        printf("1. Download File\n");
        printf("2. Mengelompokkan Film\n");
        printf("3. Membuat Report\n");
        printf("4. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);
        
        switch(pilihan) {
            case 1:
                downloadextract();
                printf("\nDownload dan extract sukses\n\n");
                break;
            case 2:
                organizefile();
                printf("\nFile sudah diorganisir bub\n\n");
                break;
            case 3:
                pthread_create(&t1, NULL, &kerjaanthread, NULL);
                pthread_join(t1, NULL);
                printf("\nreport sudah jadi sayangg\n\n");
                break;
            case 4:
                printf("\nKOK... yaudah dehh keluar dari program... :(((((\n\n");
                break;
            default:
                printf("\nyang bener dong nginputnya hmphhh\n\n");
        }
    } while (pilihan != 4);

    return 0;
}
```

<b>Output</b>

![gambar7](https://drive.google.com/uc?id=100r-iQLhY39t_R5gwzAGFZLUpyHgo851)

![gambar8](https://drive.google.com/uc?id=1rdI0sNxVlZZVmaRcahOk3J3atm7XzUMj)

<b>Penjelasan</b>

- Ada 3 proses utama pada subtask 3 ini: yang pertama adalah membuat fungsi untuk thread dan membaca file sambil memasukkan data statistik, yang kedua adalah melakukan pipe agar nama file bisa memiliki tanggal, dan yang terakhir adalah membuat menu serta menjalankan perintah thread di main.

- Pada bagian kode pertama, aku mengimplementasikan proses multithreading untuk mengolah file csv menjadi suatu file statistik. pertama tama, aku membuat fungsi untuk proses threading. di fungsi ini, sama seperti proses pada subtask 2, aku juga melakukan loop while untuk membaca satu per satu baris pada file yang sebelumnya sudah aku fgets satu kali untuk melewati header file csv. karena aku diminta membuat statistik per-negara tentang berapa banyak film yang dibuat setelah dan sebelum tahun 2000 maka aku perlu memasukkan data negara terlebih dahulu. karena tidak mungkin memasukkan satu per satu daftar negara, maka aku membuat for loop lagi di dalam fungsi while, sebelumnya di awal aku menginisiasi beberapa variabel seperti listnegara untuk menyimpan nama nama negara, jumlahpernegara untuk menyimpan banyak film sesudah dan sebelum tahun 200, dan totalnegara untuk menyimpan nilai banyak negara yang telah dimasukkan ke dalam statistik. nah, pada for loop di dalam while loop ini aku mengecek negara film pada judul film yang sedang dicek, apabila terdapat nama negara yang sama maka loop akan berhenti dan mengasign variabel index yang diinisiasi di luar for loop (sebelumnya diinisasi dengan nilai -1). kemudian ada if yang mengecek jika index masih bernilai -1 (berarti masih belum ada nama negara di dalam list) dan jumlah negara kurang dari 256 (karena jumlah negara di dunia kurang dari 256) maka nama negara kemudian di assign ke array 2 dimensi listnegara. jika index tidak sama dengan -1 yang berarti terdapat nama negara yang sama di list dan baris maka kita akan men increment isi array jumlahpernegara index 0 jika tahun terbit kurang dari 2000 dan index 1 jika lebih dari 2000.

- Pada bagian kode kedua, aku melakukan pipe agar dapat menamai file statistik dengan format yang ditambahi dengan tanggal dari dibuatnya file. sama seperti yang dilakukan saat pipe di subtask 2, bedanya kali ini pipe digunakkan untuk menamai file. jadi, setelah tanggal sudah didapatkan dan disimpan ke dalam variabel buffer, aku menggunakan ssnprintf untuk memodifikasi variabel judul agar bisa membuat absolute path dan judul dari file statistik ini. setelah variabel sudah dibuat, aku menggunakan fopen mode append agar tidak menghapus negara yang sudah di print out dan sisanya tinggal mengeprint data data statistik yang sudah didapatkan dengan fprintf.

- Pada bagian kode terakhir yaitu fungsi main, kode mendeklarasikan thread dan pilihan yang kemudian digunakan untuk membuat tab menu dengan do while. di do while, terdapat switch-case yang menjalankan perintah sesuai inputan. khusus pada proses ke tiga yaitu threading. perlu command yaitu pthreadcreate untuk menjalankan fungsi khusus thread dan pthreadjoin untuk menunggu hingga thread selesai dijalankan.

---

# Organize and Analyze Anthony's Favorite Films

Anthony is enjoying watching his favorite movies on Netflix, but over time, his movie collection has grown significantly. He decided to create a system to make his favorite movies more organized and easily accessible. Anthony wants to achieve several tasks more efficiently and automatically.

> The movies in question are the ones contained in a ZIP file that can be downloaded from **[Google Drive](https://drive.google.com/file/d/12GWsZbSH858h2HExP3x4DfWZB1jLdV-J/view?usp=drive_link)**.

Here are the tasks Anthony wants to accomplish to make his movie-watching experience more enjoyable:

### **a. One Click and Done!**

Have you ever felt lazy managing ZIP files full of movie data? Anthony feels the same way, so he wants everything to be instant with just one command. With a single command, Anthony can:

- Download a ZIP file containing his favorite Netflix movie data.
- Extract the ZIP file into an organized folder.
- Delete the unnecessary ZIP file to save storage space.

Create a script that automates this process so Anthony only needs to run one command to download, extract, and delete the ZIP file.

### **b. Sorting Like a Pro**

Anthony's movie collection is growing, and he's starting to get confused about how to quickly organize it. Anthony wants to group his movies in two very simple ways:

1. By the first letter of the movie title.
2. By release year.

However, since Anthony has learned about **multiprocessing**, he wants to group these two categories in parallel to save time.

**Output Structure:**

- **By First Letter of Movie Title:**

  - Folder: `judul/`
  - Each file is named with an alphabet letter or number, such as `A.txt`, `B.txt`, or `1.txt`.
  - If the movie title does not start with a letter or number, the movie is stored in the file `#.txt`.

- **By Release Year:**
  - Folder: `tahun/`
  - Each file is named according to the movie's release year, such as `1999.txt`, `2021.txt`, etc.

The format for each file:

```
Movie Title - Release Year - Director
```

Each running process will log its activity into a single file named **`log.txt`** in the following format:

```
[hour:minute:second] Grouping process by [Alphabet/Year]: currently grouping movie [movie_title]
```

**Example Log:**

```
[14:23:45] Grouping process by Alphabet: currently grouping movie Avengers: Infinity War
[14:23:46] Grouping process by Year: currently grouping movie Kung Fu Panda
```

### **c. The Ultimate Movie Report**

As a movie enthusiast who also loves analysis, Anthony wants to gain deeper insights into his movie collection. For example, he wants to know how many movies were released **before the year 2000** and **after the year 2000**.

To make the report easy to read, Anthony wants the results saved in a file named **`report_ddmmyyyy.txt`**.

**Output Format in the Report:**

```
i. Country: <country_name>
Movies before 2000: <count>
Movies after 2000: <count>

...
i+n. Country: <country_name>
Movies before 2000: <count>
Movies after 2000: <count>
```

To make it even easier to use, Anthony wants to be able to run all of the above processes through an interactive terminal interface with menu options like the following:
1. Download File
2. Categorize Movies
3. Create Report

Notes:
- It is forbidden to use `system`
- Please use threads in working with question C.

## Task 3 - Cella's Manhwa

Membantu Cella untuk mengumpulkan informasi dan foto dari berbagai manhwa favoritnya dengan skrip otomatis.

Daftar Manhwa :

|    No     |      Manhwa      |
| :--------: | :------------: |
| 1 | Mistaken as the Monster Duke's Wife |
| 2 | The Villainess Lives Again |
| 3 | No, I Only Charmed the Princess! |
| 4 | Darling, Why Can't We Divorce? |

Library yang digunakan :

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>
#include <ctype.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>  
#include <wait.h> 
```

### **a. Summoning the Manhwa Stats**

Mengambil data detail dari manhwa menggunakan API Jikan

- Judul
- Status
- Tanggal rilis
- Genre
- Tema
- Author

Lalu disimpan dalam file .txt dengan format nama file tanpa karakter khusus dan spasi diganti dengan underscore. File disimpan dalam folder `Manhwa`.


### **b. Seal the Scrolls**

Setiap file .txt kemudian di-zip dan disimpan ke dalam folder `Archive`. Format nama file zip adalah inisial judul manhwa tanpa character.

**Code a & b :**
```
struct string {
    char *ptr;
    size_t len;
};

void init_string(struct string *s) {
    s->len = 0;
    s->ptr = malloc(1);
    if (s->ptr == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr + s->len, ptr, size * nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size * nmemb;
}

void make_directory(const char *dir_path) {
    pid_t pid = fork();
    if (pid == 0) {
        execlp("mkdir", "mkdir", "-p", dir_path, (char *)NULL);
        perror("execlp failed");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);  
    }
}

char *filename(const char *title) {
    char *filename = malloc(strlen(title) * 2);
    int j = 0;
    for (int i = 0; title[i]; i++) {
        if (isalnum(title[i])) {
            filename[j++] = title[i];
        } else if (isspace(title[i])) {
            filename[j++] = '_';
        }
    }
    filename[j] = '\0';
    return filename;
}

char *initial_filename(const char *filename) {
    char *initial = malloc(16);
    int j = 0;
    if (isalpha(filename[0])) {
        initial[j++] = toupper(filename[0]);
    }
    for (int i = 1; filename[i]; i++) {
        if (filename[i - 1] == '_' && isalpha(filename[i])) {
            initial[j++] = toupper(filename[i]);
        }
    }
    initial[j] = '\0';
    return initial;
}

void txt_zip(const char *filename, const char *content) {
    make_directory("Manhwa"); 
    char path[256];
    snprintf(path, sizeof(path), "Manhwa/%s.txt", filename);

    FILE *f = fopen(path, "w");
    if (!f) {
        perror("fopen");
        return;
    }
    fprintf(f, "%s", content);
    fclose(f);

    make_directory("Archive"); 
    char *zip_name = initial_filename(filename);
    char zip_path[256];
    snprintf(zip_path, sizeof(zip_path), "Archive/%s.zip", zip_name);

    pid_t pid = fork();
    if (pid == 0) {
        execlp("zip", "zip", "-j", zip_path, path, (char *)NULL);
        perror("execlp failed");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);  
    }
    printf("%s.zip is completed!\n", zip_name);
    free(zip_name);
}

void manhwa_info(int id, struct Heroine *h) {
    CURL *curl;
    CURLcode res;
    struct string s;
    char url[128];

    sprintf(url, "https://api.jikan.moe/v4/manga/%d", id);

    curl = curl_easy_init();
    if (curl) {
        init_string(&s);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            json_error_t error;
            json_t *root = json_loads(s.ptr, 0, &error);
            if (root) {
                json_t *data = json_object_get(root, "data");
                const char *title = json_string_value(json_object_get(data, "title_english"));
                const char *status = json_string_value(json_object_get(data, "status"));
                const char *release_raw = json_string_value(json_object_get(json_object_get(data, "published"), "from"));

                char release[11];
                strncpy(release, release_raw, 10);
                release[10] = '\0';

                json_t *genres = json_object_get(data, "genres");
                char genre_list[256] = "";
                for (size_t i = 0; i < json_array_size(genres); i++) {
                    json_t *g = json_array_get(genres, i);
                    strcat(genre_list, json_string_value(json_object_get(g, "name")));
                    if (i != json_array_size(genres) - 1) strcat(genre_list, ", ");
                }

                json_t *themes = json_object_get(data, "themes");
                char theme_list[256] = "";
                for (size_t i = 0; i < json_array_size(themes); i++) {
                    json_t *t = json_array_get(themes, i);
                    strcat(theme_list, json_string_value(json_object_get(t, "name")));
                    if (i != json_array_size(themes) - 1) strcat(theme_list, ", ");
                }

                json_t *authors = json_object_get(data, "authors");
                char author_list[256] = "";
                for (size_t i = 0; i < json_array_size(authors); i++) {
                    json_t *a = json_array_get(authors, i);
                    strcat(author_list, json_string_value(json_object_get(a, "name")));
                    if (i != json_array_size(authors) - 1) strcat(author_list, ", ");
                }

                h->manhwa_filename = strdup(filename(title));

                char content[1024];
                snprintf(content, sizeof(content),
                         "Title: %s\nStatus: %s\nRelease: %s\nGenre: %s\nTheme: %s\nAuthor: %s\n",
                         title, status, release, genre_list, theme_list, author_list);

                txt_zip(h->manhwa_filename, content);
                json_decref(root);
            } else {
                fprintf(stderr, "JSON parse error: %s\n", error.text);
            }
        }
        curl_easy_cleanup(curl);
        free(s.ptr);
    }
}

int main() {
    int id[] = {168827, 147205, 169731, 175521}; 

    struct Heroine heroines[] = {
        {"Lia", 3, "https://i.pinimg.com/736x/11/d9/ad/11d9ad85a47892f5fd979a0209162377.jpg"},
        {"Artezia", 6, "https://i.pinimg.com/736x/cf/ab/a7/cfab73765912c97bc16865df4a9b3455.jpg"},
        {"Adelia", 4, "https://i.pinimg.com/736x/fd/26/a7/fd26a75cbc439e66ed6b55bbd5c904f2.jpg"},
        {"Ophelia", 10, "https://i.pinimg.com/736x/ba/a7/c7/baa7c7b496cc61848d17b471a0000cbd.jpg"}
    };
    
    for (int i = 0; i < 4; i++) {
        manhwa_info(id[i], &heroines[i]);
    }

    pthread_t threads[4];

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, download_images, &heroines[i]);
        pthread_join(threads[i], NULL);
    }

    cleanup_images();
}
```

**Output :**

Terminal :

![Screenshot from 2025-04-30 14-49-50](https://drive.google.com/uc?id=18x3hT0JKENKflQcfVK2E5nCHEqKWSmGk)

a. Summoning the Manhwa Stats

Folder :

![Screenshot from 2025-04-30 14-55-14](https://drive.google.com/uc?id=1rrfNr7YSjeAuOY30Jc0J5dvCJf6r5g-0)

Isi folder :

![Screenshot from 2025-04-30 14-55-24](https://drive.google.com/uc?id=1zkvdr8r8zFzNajOJaJZEM9IIvxm8bSk1)

Isi txt (Mistaken_as_the_Monster_Dukes_Wife.txt):

![Screenshot from 2025-04-30 15-04-01](https://drive.google.com/uc?id=1glStLIMhev2-xA7f1DUBl3qqttcsryB2)

Isi txt (The_Villainess_Lives_Again.txt):

![Screenshot from 2025-04-30 15-30-44](https://drive.google.com/uc?id=1XLStLEdpRRllKTV_Y7RP9E-t1oNqeaEf)

Isi txt (No_I_Only_Charmed_the_Princess.txt):

![Screenshot from 2025-04-30 15-30-47](https://drive.google.com/uc?id=1d9Rn0wpXlH1pAzJZiEubMr8c3n_Llq6-)

Isi txt (Darling_Why_Cant_We_Divorce.txt):

![Screenshot from 2025-04-30 15-30-49](https://drive.google.com/uc?id=1NF8yjw3JXOtuxFLtsBxAWZgqD_OxuPID)


b. Seal the Scrolls

Folder :

![Screenshot from 2025-04-30 14-55-06](https://drive.google.com/uc?id=176r7mF4c_XYkPaq9JNqPfHi6VWYNWjvO)

Isi folder :

![Screenshot from 2025-04-30 14-55-39](https://drive.google.com/uc?id=1WCpZtfvc4S1uN95u6TZPCnkF1KHqq7s7)


**Penjelasan :**

Function :

`struct string` :
- Menyimpan semua konten API melalui `curl_easy_perform` (dari function `manhwa_info`) sebagai string dinamis.

`void init_string(struct string *s)` :
- Inisialisasi struct string jadi string kosong dinamis.
- `malloc(1)` nyiapin 1 byte awal.
- Di-terminate dengan '\0' supaya menjadi string valid.

`size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)` :
- Fungsi callback supaya libcurl dapat menaruh data ke memori.
- Realloc ukuran baru `(s->len + size * nmemb)`. Salin data baru ke `s->ptr`. Update `s->len`.

`void make_directory(const char *dir_path)` :
- Membuat folder dengan fork + execlp.

`char *filename(const char *title)` :
- Mengonversi judul manhwa jadi nama file valid. Nama file tanpa karakter khusus dan spasi diganti dengan underscore.

`char *initial_filename(const char *filename)` :
- Mengambil huruf pertama dan setiap huruf setelah `_` untuk nama zip.

`void txt_zip(const char *filename, const char *content)` :
- Membuat direktori `Manhwa` dan `Archive`
- Menyimpan informasi manhwa ke dalam txt.
- Membuat file .zip dari file .txt.

`void manhwa_info(int id, struct Heroine *h)` :
- Mengambil informasi manhwa via Jikan API berdasarkan id dari array `id` di `main`.
- Menggabungkan informasi ke dalam array lalu memanggil `txt_zip` untuk diubah menjadi txt dan zip.

Main :
- `int id[]` : array untuk menyimpan id masing-masing manhwa.
- `for (int i = 0; i < 4; i++) manhwa_info(id[i], &heroines[i]);` : melakukan loop untuk mengambil informasi dari manhwa.


### **c. Making the Waifu Gallery**

Mengunduh gambar heroine dari internet dengan jumlah unduhan sesuai dengan bulan rilis manhwa. Gambar disimpan ke dalam subfolder Heroines/(nama heroine).

**Code :**
```
struct Heroine {
    const char *name;
    int count;
    int month;
    const char *img_url;
    char *manhwa_filename;
}

void make_directory(const char *dir_path) {
    pid_t pid = fork();
    if (pid == 0) {
        execlp("mkdir", "mkdir", "-p", dir_path, (char *)NULL);
        perror("execlp failed");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);  
    }
}

void *download_images(void *arg) {
    struct Heroine *h = (struct Heroine *)arg;

    char dir_path[512];
    snprintf(dir_path, sizeof(dir_path), "Heroines/%s", h->name);
    make_directory("Heroines");
    make_directory(dir_path);

    for (int i = 0; i < h->count; i++) {
        char filename[100];
        snprintf(filename, sizeof(filename), "%s/%s_%d.jpg", dir_path, h->name, i + 1);

        char cmd[1024];
        snprintf(cmd, sizeof(cmd), "wget -q -O \"%s\" \"%s\"", filename, h->img_url);
        system(cmd); 
    }

    archive_images(h->manhwa_filename, h->name);

    pthread_exit(NULL);
}

int main() {
    int id[] = {168827, 147205, 169731, 175521}; 

    struct Heroine heroines[] = {
        {"Lia", 3, "https://i.pinimg.com/736x/11/d9/ad/11d9ad85a47892f5fd979a0209162377.jpg"},
        {"Artezia", 6, "https://i.pinimg.com/736x/cf/ab/a7/cfab73765912c97bc16865df4a9b3455.jpg"},
        {"Adelia", 4, "https://i.pinimg.com/736x/fd/26/a7/fd26a75cbc439e66ed6b55bbd5c904f2.jpg"},
        {"Ophelia", 10, "https://i.pinimg.com/736x/ba/a7/c7/baa7c7b496cc61848d17b471a0000cbd.jpg"}
    };
    
    for (int i = 0; i < 4; i++) {
        manhwa_info(id[i], &heroines[i]);
    }

    pthread_t threads[4];

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, download_images, &heroines[i]);
        pthread_join(threads[i], NULL);
    }

    cleanup_images();
};
```

**Output :**

Terminal :

![Screenshot from 2025-04-30 15-36-12](https://drive.google.com/uc?id=1mkUhvGtPHb-X_qayxGPqjXjyLJajJLbW)

Folder :

![Screenshot from 2025-04-30 15-09-05](https://drive.google.com/uc?id=1ew1MbntzBu3lVK1Y3BY6lD2L2dd2Dtr4)

Isi folder Heroines :

![Screenshot from 2025-04-30 15-09-15](https://drive.google.com/uc?id=1al-GFYNW2KTm780VTC15wOI51xIquHW3)

Isi subfolder Adelia :

![Screenshot from 2025-04-30 15-09-24](https://drive.google.com/uc?id=1aD7JVupSFOyl9z8zuFTiAaghD6XgGOlW)

Isi subfolder Artezia :

![Screenshot from 2025-04-30 15-21-38](https://drive.google.com/uc?id=18dVdc6E0rgHj2Pbug2jZ-1SGWszxTKHv)

Isi subfolder Lia :

![Screenshot from 2025-04-30 15-14-50](https://drive.google.com/uc?id=1O81RkvPkw4wLPj__I5BidNix2QcZVzxa)

Isi subfolder Ophelia :

![Screenshot from 2025-04-30 15-15-05](https://drive.google.com/uc?id=1Bta0nJPasWn8_l4quw6JuptsWRRgWb2q)

**Penjelasan :**

Function :

`struct Heroine` :
- Menyimpan data heroine: nama, jumlah gambar, bulan rilis, URL gambar, dan nama file manhwa.

`void make_directory(const char *dir_path)` :
- Membuat folder dengan fork + execlp.

`void *download_images(void *arg)` :
- Fungsi thread untuk mendownload gambar heroine melalui link yang sudah diset di `struct Heroine` yang sudah didefinisikan di `main`
- Membuat folder `Heroines/(nama heroine)`
- Menyimpan gambar dengan `wget`.
- Memanggil fungsi zip gambar heroine (untuk soal d).

Main :
- `struct Heroine heroines[]` : Inisialisasi struct Heroine di main lalu mengisinya dengan data.
- `{"Lia", 3, "https://i.pinimg.com/736x/11/d9/ad/11d9ad85a47892f5fd979a0209162377.jpg"}`. `Lia` : nama heroine, `3` : bulan rilis, `"https://i.pinimg.com/736x/11/d9/ad/11d9ad85a47892f5fd979a0209162377.jpg"` : link gambar.
- `pthread_t threads[4]` : membuat array untuk 4 thread.
- ```
  for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, download_images, &heroines[i]);
        pthread_join(threads[i], NULL);
    }
  ```
  Melakukan looping membuat thread baru per heroine untuk memanggil fungsi `download_images`. Satu thread dibuat hingga selesai baru lanjut ke thread selanjutnya.


### **d. Zip. Save. Goodbye**

Mengarsipkan semua gambar heroine, lalu menyimpan ke dalam folder Archive/Images. Sedangkan gambar heroine di folder Heroine/(nama heroine) dihapus sesuai urutan abjad.

**Code :**
```
struct Heroine {
    const char *name;
    int count;
    int month;
    const char *img_url;
    char *manhwa_filename;
}

void make_directory(const char *dir_path) {
    pid_t pid = fork();
    if (pid == 0) {
        execlp("mkdir", "mkdir", "-p", dir_path, (char *)NULL);
        perror("execlp failed");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);  
    }
}

char *initial_filename(const char *filename) {
    char *initial = malloc(16);
    int j = 0;
    if (isalpha(filename[0])) {
        initial[j++] = toupper(filename[0]);
    }
    for (int i = 1; filename[i]; i++) {
        if (filename[i - 1] == '_' && isalpha(filename[i])) {
            initial[j++] = toupper(filename[i]);
        }
    }
    initial[j] = '\0';
    return initial;
}

void archive_images(const char *manhwa_filename, const char *heroine_name);

void *download_images(void *arg) {
...
    archive_images(h->manhwa_filename, h->name);
...
}

void archive_images(const char *manhwa_filename, const char *heroine_name) {
    make_directory("Archive/Images");
    char *zip_name = initial_filename(manhwa_filename);

    char zip_path_images[512];
    snprintf(zip_path_images, sizeof(zip_path_images), "Archive/Images/%s_%s.zip", zip_name, heroine_name);

    char source_folder[512];
    snprintf(source_folder, sizeof(source_folder), "Heroines/%s", heroine_name);

    char *args[] = {"zip", "-r", "-j", zip_path_images, source_folder, NULL};

    pid_t pid = fork();
    if (pid == 0) {
        execvp("zip", args);
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(NULL);
        printf("%s_%s.zip is completed!\n", zip_name, heroine_name);
    } else {
        perror("fork failed");
    }
}

void cleanup_images() {
    DIR *dir;
    struct dirent *entry;
    char *folders[100];
    int count = 0;

    dir = opendir("Heroines");
    if (!dir) {
        perror("opendir failed");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                folders[count++] = strdup(entry->d_name);
            }
        }
    }
    closedir(dir);

    for (int i=0; i<count-1; i++) {
        for (int j=i+1; j<count; j++) {
            if (strcmp(folders[i], folders[j]) > 0) {
                char *tmp = folders[i];
                folders[i] = folders[j];
                folders[j] = tmp;
            }
        }
    }

    for (int i = 0; i < count; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            char folder_path[512];
            snprintf(folder_path, sizeof(folder_path), "Heroines/%s", folders[i]);
            execlp("find", "find", folder_path, "-type", "f", "-name", "*.jpg", "-delete", (char *)NULL);
            perror("execlp find failed");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            wait(NULL);
            printf("%s images in Heroines/%s deleted successfully!\n", folders[i], folders[i]);
        } else {
            perror("fork failed");
        }
        free(folders[i]);
    }
}

int main() {
    int id[] = {168827, 147205, 169731, 175521}; 

    struct Heroine heroines[] = {
        {"Lia", 3, "https://i.pinimg.com/736x/11/d9/ad/11d9ad85a47892f5fd979a0209162377.jpg"},
        {"Artezia", 6, "https://i.pinimg.com/736x/cf/ab/a7/cfab73765912c97bc16865df4a9b3455.jpg"},
        {"Adelia", 4, "https://i.pinimg.com/736x/fd/26/a7/fd26a75cbc439e66ed6b55bbd5c904f2.jpg"},
        {"Ophelia", 10, "https://i.pinimg.com/736x/ba/a7/c7/baa7c7b496cc61848d17b471a0000cbd.jpg"}
    };
    
    for (int i = 0; i < 4; i++) {
        manhwa_info(id[i], &heroines[i]);
    }

    pthread_t threads[4];

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, download_images, &heroines[i]);
        pthread_join(threads[i], NULL);
    }

    cleanup_images();
};
```

**Output :**

Terminal :

![Screenshot from 2025-04-30 15-37-13](https://drive.google.com/uc?id=1zS02JiBBzCUfoo9h7GE8W0kWAw79P4Qr)

Isi folder Heroines :

![Screenshot from 2025-04-30 15-09-15](https://drive.google.com/uc?id=1al-GFYNW2KTm780VTC15wOI51xIquHW3)

Isi subfolder Adelia :

![Subfolder adelia](https://drive.google.com/uc?id=1KMURpvjY_ZqPD0sIYZjHZzEaZ4uGw8r3)

Isi subfolder Artezia :

![Subfolder adelia](https://drive.google.com/uc?id=1k_1utpsjO7PighPW2uz8ev8uwvGsBcKv)

Isi subfolder Lia :

![Subfolder adelia](https://drive.google.com/uc?id=1NP_6tIfyWDLTbusjfX6zTrw-n17OrHk9)

Isi subfolder Ophelia :

![Subfolder adelia](https://drive.google.com/uc?id=16aBFyeHbibxZD5wws8IufP7jlwjDqAds)

Isi folder Archive/Images :

![Screenshot from 2025-04-30 15-39-59](https://drive.google.com/uc?id=1ljnDE_63Bym4-GFwA2xf9afwRvYnRzFA)


**Penjelasan :**

Function :

`struct Heroine` :
- Menyimpan data heroine: nama, jumlah gambar, bulan rilis, URL gambar, dan nama file manhwa.

`void make_directory(const char *dir_path)` :
- Membuat folder dengan fork + execlp.

`void *download_images(void *arg)` :
- Memanggil fungsi zip gambar heroine.

`void archive_images(const char *manhwa_filename, const char *heroine_name)`:
- Membuat directory `Archive/Images`.
- Mengambil nama zip dengan memanggil `initial_filename(manhwa_filename)` lalu menyimpannya ke dalam `zip_name`
- Menyusun path untuk menyimpan file zip dan source folder.
- Melakukan zip dengan fork dan exec.

`void cleanup_images()` :
- Membuka folder `Heroines`, membaca isinya lalu disimpan ke dalam array `folders` , lalu menutup foldernya.
- Mengurutkan nama file yang akan dihapus dengan bubble sort.
- Melakukan loop menghapus file dengan fork() dan exec().

Main :
- `cleanup_images();` : memanggil fungsi `cleanup_images` untuk menghapus gambar heroine urut sesuai abjad.

Kendala pengerjaan :
- Soal c sempat bermasalah pada download (yang terdownload terkadang random).
- Soal d sempat bermasalah pada urutan hapus.


## Task 4 - Pipip's Load Balancer
Pipip, seorang pengembang perangkat lunak yang tengah mengerjakan proyek distribusi pesan dengan sistem load balancing, memutuskan untuk merancang sebuah sistem yang memungkinkan pesan dari client bisa disalurkan secara efisien ke beberapa worker. Dengan menggunakan komunikasi antar-proses (IPC), Pipip ingin memastikan bahwa proses pengiriman pesan berjalan mulus dan terorganisir dengan baik, melalui sistem log yang tercatat dengan rapi.

### **a. Client Mengirimkan Pesan ke Load Balancer**
Pipip ingin agar proses `client.c` dapat mengirimkan pesan ke `loadbalancer.c` menggunakan IPC dengan metode **shared memory**.

<b>Code</b>
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define MAX 100
#define SHM_KEY 1234

typedef struct SharedMem{
    char message[MAX];
    int count;
}sm;

int main(){
    int shmid = shmget(SHM_KEY, sizeof(sm), 0666 | IPC_CREAT);
    sm *data = (sm *)shmat(shmid, NULL, 0);
    
    FILE *file = fopen("sistem.log", "a");
    char buff[MAX], *word, *num_str;
    int num;

    fgets(buff, MAX, stdin);

    word = strtok(buff, ";");
    num_str = strtok(NULL, ";");
    num = (num_str != NULL) ? atoi(num_str) : 1;

    strcpy(data->message, word);
    data->count = num;

    fprintf(file, "Message from client: %s\nMessage count: %d\n", word, num);
    fflush(file);

    shmdt(data);
    fclose(file);
    return 0;
}
```

<b>Output</b>

input = `Halo A;10`

![output client](https://drive.google.com/uc?id=1JJfRaTscVIJ4CImaoVWLqQk6FhPLoqvL)


<b>Penjelasan</b>

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
```
- `stdio.h`: Mengakses fungsi input/output standar seperti `printf()`, `fgets()`, dan `fprintf()`.
- `stdlib.h`: Mengakses fungsi utilitas seperti `atoi()`, `exit()`, dan alokasi memori.
- `string.h`: Mengakses fungsi manipulasi string seperti `strcpy()` dan `strtok()`.
- `sys/ipc.h`: Mengakses fungsi untuk membuat kunci (key) IPC.
- `sys/shm.h`: Mengakses fungsi untuk shared memory seperti `shmget()` dan `shmat()`.
- `unistd.h`: Mengakses fungsi sistem POSIX seperti `semop()`.

```
#define MAX 100
#define SHM_KEY 1234
```
Inisialisasi untuk `MAX` (panjang pesan) dan `SHM_KEY` (shared memory key).

```
typedef struct SharedMem{
    char message[MAX];
    int count;
}sm;
```
Mendefinisikan struktur data `SharedMem`:
- `message`: Menyimpan pesan berupa string (maksimal 100 karakter).
- `count`: Menyimpan jumlah pesan.

```
int shmid = shmget(SHM_KEY, sizeof(sm), 0666 | IPC_CREAT);
sm *data = (sm *)shmat(shmid, NULL, 0);
```
- `shmget()`: Membuat atau mengambil shared memory dengan ukuran `sizeof(sm)` dan kunci `SHM_KEY`.
- `shmat()`: Melampirkan (attach) shared memory ke proses saat ini dengan pointer bertipe `sm`.

```
FILE *file = fopen("sistem.log", "a");
```
Membuka file log `sistem.log` dengan mode append untuk mencatat pesan dan jumlah yang diterima.
```
fgets(buff, MAX, stdin);

word = strtok(buff, ";");
num_str = strtok(NULL, ";");
num = (num_str != NULL) ? atoi(num_str) : 1;

strcpy(data->message, word);
data->count = num;

fprintf(file, "Message from client: %s\nMessage count: %d\n", word, num);
fflush(file);

```
- Membaca input dari user menggunakan `fgets()` dengan format: `pesan;angka`.
- Memisahkan input menjadi `word` (pesan) dan `num` (angka) menggunakan `strtok()` dan `atoi()`.
- `fprintf(file, "Message from client: %s\nMessage count: %d\n", word, num)`: Menulis message ke file log.
- `fflush(file)`: Memastikan semua data yang telah ditulis ke buffer file segera dikirim ke file.
- Menulis pesan dan angka ke shared memory `data->message`, `data->count`.
  
```
shmdt(data);
fclose(file);
```
- `shmdt(data)`: Melepaskan shared memory dari proses.
- `fclose(file)`: Menutup file log.

### **b. Load Balancer Mendistribusikan Pesan ke Worker Secara Round-Robin**

Setelah menerima pesan dari client, tugas `loadbalancer.c` adalah mendistribusikan pesan-pesan tersebut ke beberapa **worker** menggunakan metode **round-robin**. Sebelum mendistribusikan pesan, `loadbalancer.c` terlebih dahulu mencatat informasi ke dalam **`sistem.log`**.

<b>Code</b>
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX 100
#define SHM_KEY 1234
#define MSGQ_KEY 9999

typedef struct SharedMem{
    char message[MAX];
    int count;
}sm;

typedef struct msg_buffer{
    long mtype;
    char mtext[MAX];
}msgb;

int main(){
    int worker;
    printf("Jumlah worker: ");
    scanf("%d", &worker);

    int shmid = shmget(SHM_KEY, sizeof(sm), 0666 | IPC_CREAT);
    int msgid = msgget(MSGQ_KEY, 0666 | IPC_CREAT);

    sm *data = (sm *)shmat(shmid, NULL, 0);

    FILE *logfile = fopen("sistem.log", "a");

    msgb msg;
    int round = 1;
    for (int i = 0; i < data->count; i++){
        fprintf(logfile, "Received at lb: %s (#message%d)\n", data->message, i + 1);
        fflush(logfile);

        msg.mtype = round;

        msgsnd(msgid, &msg, sizeof(msg.mtext), 0);
        round++;
        if (round > worker) round = 1;
    }

    fclose(logfile);
    shmdt(data);

    return 0;
}
```

<b>Output</b>

<b>Run Program</b>
```
gcc client.c -o client
gcc loadbalancer.c -o loadbalancer

./client
input pesan

./loadbalancer
input worker
```

![output lb](https://drive.google.com/uc?id=1Eve3fEvm3WxEKWZnWt_k8nCBsRzMs6kW)

<b>Penjelasan</b>
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <unistd.h>
```
- `stdio.h`: Mengakses fungsi input/output standar seperti `printf()`, `fprintf()`, dan `scanf()`.
- `stdlib.h`: Mengakses fungsi utilitas seperti `exit()`, `malloc()`, dan `atoi()`.
- `string.h`: Mengakses fungsi manipulasi string seperti `strncpy()` dan `strtok()`.
- `sys/ipc.h`: Mengakses fungsi untuk membuat kunci (key) IPC.
- `sys/shm.h`: Mengakses fungsi untuk shared memory seperti `shmget()` dan `shmat()`.
- `sys/msg.h`: Mengakses fungsi message queue seperti `msgget()` dan `msgsnd()`.
- `unistd.h`: Mengakses fungsi sistem POSIX seperti `semop()`.

```
#define MAX 100
#define SHM_KEY 1234
#define MSGQ_KEY 9999
```
Inisialisasi untuk `MAX` (panjang pesan), `SHM_KEY` (shared memory key), dan `MSGQ_KEY` (message queue key).

```
typedef struct SharedMem{
    char message[MAX];
    int count;
}sm;
```
Mendefinisikan struktur data `SharedMem`:
- `message`: Menyimpan pesan berupa string (maksimal 100 karakter).
- `count`: Menyimpan jumlah pesan .

```
typedef struct msg_buffer{
    long mtype;
    char mtext[MAX];
}msgb;
```
Mendefinisikan struktur data `msg_buffer` untuk message queue:
- `mtype`: Tipe pesan yang menentukan worker tujuan.
- `mtext`: Menyimpan isi pesan.

```
int shmid = shmget(SHM_KEY, sizeof(sm), 0666 | IPC_CREAT);
sm *data = (sm *)shmat(shmid, NULL, 0);
```
- `shmget()`: Membuat atau mengambil shared memory dengan ukuran `sizeof(sm)` dan key `SHM_KEY`.
- `shmat()`: Melampirkan (attach) shared memory ke proses saat ini dengan pointer bertipe `sm`.

```
int msgid = msgget(MSGQ_KEY, 0666 | IPC_CREAT);
```
Membuat message queue dengan key `MSGQ_KEY`.

```
FILE *file = fopen("sistem.log", "a");
```
Membuka file log `sistem.log` dengan mode append untuk mencatat pesan yang diterima.

```
msgb msg;
int round = 1;
```
Inisialisasi `msg` untuk message queue dan variabel `round` untuk metode distribusi pesan berbasis round-robin.

```
for(int i = 0; i < data->count; i++){
    fprintf(file, "Received at lb: %s (#message%d)\n", data->message, i + 1);
    fflush(file);

    msg.mtype = round;

    msgsnd(msgid, &msg, sizeof(msg.mtext), 0);
    round++;
    if (round > n) round = 1;
}

```
`for loop` untuk membaca pesan dari `client.c` dan mengirim pesan ke worker:
   - `fprintf(file, "Received at lb: %s (#message%d)\n", data->message, i + 1)`: Mencatat message dari `client.c` ke file log.
   - `fflush(file)`: Memastikan semua data yang telah ditulis ke buffer file segera dikirim ke file.
   - Iterasi sebanyak jumlah pesan `data->count`.
   - Mencatat pesan ke file log `sistem.log`.
   - Membuat buffer pesan `msgb` dan mengatur tipe pesan `mtype` untuk worker.
   - Mengirim pesan message queue menggunakan `msgsnd()` untuk worker.
   - Mengatur worker tujuan secara round-robin dengan variabel `round` yang selalu diincrement, lalu jika lebih dari jumlah worker akan direset menjadi 1.

```
fclose(file);
shmdt(data);
```
- `fclose(file)`: Menutup file log.
- `shmdt(data)`: Melepaskan shared memory dari proses.

### **c. Worker Mencatat Pesan yang Diterima**

Setiap worker yang menerima pesan dari `loadbalancer.c` harus mencatat pesan yang diterima ke dalam **`sistem.log`** dengan format log sebagai berikut:

### **d. Catat Total Pesan yang Diterima Setiap Worker di Akhir Eksekusi**

Setelah proses selesai (semua pesan sudah diproses), setiap worker akan mencatat jumlah total pesan yang mereka terima ke bagian akhir file **`sistem.log`**.

<b>Bagian c dan d menggunakan source code yang sama</b>

<b>Code</b>
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 100
#define MSGQ_KEY 9999

typedef struct msg_buffer{
    long mtype;
    char mtext[MAX];
} msgb;

pthread_mutex_t lock;
pthread_cond_t cond;

int msgid;
int total_worker;
int current_worker = 1;
int msg_count[1000] = {0};

void* worker_thread(void* arg) {
    long id = *(long*)arg;
    FILE *file = fopen("sistem.log", "a");

    msgb msg;
    int received = 0;
    while(1) {
        pthread_mutex_lock(&lock);
        
        while (current_worker != id) {
            pthread_cond_wait(&cond, &lock);
        }
        
        if(msgrcv(msgid, &msg, sizeof(msg.mtext), id, IPC_NOWAIT) > 0){
            fprintf(file, "Worker%ld: message received\n", id);
            fflush(file);
            msg_count[current_worker]++;
            received++;
        }else{
            break;
        }
    
        current_worker++;
        if(current_worker > total_worker) current_worker = 1;

        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);

    }

    for(int i =  1; i <= total_worker;i++){
        fprintf(file, "Worker %d: %d messages\n", i, msg_count[i]);
        fflush(file);
    }

    fclose(file);

}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <jumlah_worker>\n", argv[0]);
        exit(1);

    }
    
    total_worker = atoi(argv[1]);
    msgid = msgget(MSGQ_KEY, 0666 | IPC_CREAT);

    pthread_t workers[total_worker];
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    for (int i = 1; i <= total_worker; i++) {
        long *id = (long *)malloc(sizeof(long));
        *id = i;
        pthread_create(&workers[i], NULL, worker_thread, id);
    }

    for (int i = 0; i < total_worker; i++) {
        pthread_join(workers[i], NULL);
    }

    
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
```

<b>Output</b>

<b>Run Program</b>
```
gcc client.c -o client
gcc loadbalancer.c -o loadbalancer
gcc worker.c -o worker

./client
input pesan

./loadbalancer
input worker

./worker <input worker>
```

![output cd](https://drive.google.com/uc?id=1yOSQ9-pr55c5bPtaRVo2XwkoZ1VHetUX)

<b>Penjelasan</b>
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>
```
- `stdio.h`: Mengakses fungsi input/output standar seperti `printf()` dan `fprintf()`.
- `stdlib.h`: Mengakses fungsi utilitas seperti `malloc()`, `atoi()`, dan `exit()`.
- `string.h`: Mengakses fungsi manipulasi string seperti `strncpy()` dan `strtok()`.
- `pthread.h`: Mengakses fungsi threading seperti `pthread_create()` dan `pthread_join()`.
- `sys/ipc.h`: Mengakses fungsi untuk membuat kunci (key) IPC.
- `sys/msg.h`: Mengakses fungsi message queue seperti `msgget()` dan `msgrcv()`.
- `unistd.h`: Mengakses fungsi sistem POSIX seperti `usleep()`.
- `sys/wait.h`: Mengakses fungsi wait dengan `wait()`.

```
#define MAX 100
#define MSGQ_KEY 9999
```
Inisialisasi untuk `MAX` (panjang pesan) dan `MSGQ_KEY` (message queue key).

```
typedef struct msg_buffer{
    long mtype;
    char mtext[MAX];
} msgb;
```
Mendefinisikan struktur data `msg_buffer` untuk message queue:
- `mtype`: Tipe pesan yang menentukan worker tujuan.
- `mtext`: Menyimpan isi pesan.

```
pthread_mutex_t lock;
pthread_cond_t cond;
```
- `lock`: inisialisasi variabel dari `pthread_mutex_t` untuk mengatur akses thread ke resource bersama.
- `cond`: inisialisasi variabel dari `pthread_cond_t` untuk sinkronisasi antar thread.

```
int msgid;
int total_worker;
int current_worker = 1;
int msg_count[1000] = {0};
```
Inisialisasi beberapa variabel di global.
- `msgid`: ID untuk message queue.
- `total_worker`: Jumlah worker yang akan dibuat.
- `current_worker`: Worker yang saat ini diproses (untuk round-robin) (dimulai dari 1).
- `msg_count`: Array untuk menyimpan jumlah pesan yang diterima setiap worker.

```
void* worker_thread(void* arg) {
    long id = *(long*)arg;
    FILE *file = fopen("sistem.log", "a");

    msgb msg;
    int received = 0;
    while(1) {
        pthread_mutex_lock(&lock);
        
        while (current_worker != id) {
            pthread_cond_wait(&cond, &lock);
        }
        
        if(msgrcv(msgid, &msg, sizeof(msg.mtext), id, IPC_NOWAIT) > 0){
            fprintf(file, "Worker%ld: message received\n", id);
            fflush(file);
            msg_count[current_worker]++;
            received++;
        }else{
            break;
        }
    
        current_worker++;
        if(current_worker > total_worker) current_worker = 1;

        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);

    }

    for(int i =  1; i <= total_worker;i++){
        fprintf(file, "Worker %d: %d messages\n", i, msg_count[i]);
        fflush(file);
    }

    fclose(file);

}
```
- Fungsi `worker_thread` menangani eksekusi pesan untuk setiap worker.
- `pthread_mutex_lock()`: Mengunci akses ke resource bersama.
- `pthread_cond_wait()`: Menunggu worker lain selesai sebelum worker dijalankan.
- `msgrcv()`: Menerima pesan dari message queue `loadbalancer.c`.
- `msg_count[current_worker]++`: Menambah jumlah pesan yang diterima oleh worker.
- `fprintf(file, ...)`: Menyimpan log pesan ke file `sistem.log`.

```
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <jumlah_worker>\n", argv[0]);
        exit(1);
    }
```
Memvalidasi input jumlah worker dari argumen command line. Jika input tidak sesuai, program akan keluar.

```
total_worker = atoi(argv[1]);
msgid = msgget(MSGQ_KEY, 0666 | IPC_CREAT);
```
- `atoi(argv[1])`: Mengonversi jumlah worker dari string ke integer.
- `msgget(MSGQ_KEY, 0666 | IPC_CREAT)`: Membuat atau mengambil message queue dengan key `MSGQ_KEY`.

```
pthread_t workers[total_worker];
pthread_mutex_init(&lock, NULL);
pthread_cond_init(&cond, NULL);
```
- `pthread_t workers[total_worker]`: Array thread untuk worker.
- `pthread_mutex_init(&lock, NULL)`: Inisialisasi mutex `lock`.
- `pthread_cond_init(&cond, NULL)`: Inisialisasi kondisi `cond`.

```
for (int i = 1; i <= total_worker; i++) {
    long *id = (long *)malloc(sizeof(long));
    *id = i;
    pthread_create(&workers[i], NULL, worker_thread, id);
}
```
`pthread_create(&workers[i], NULL, worker_thread, id)`: Membuat thread untuk setiap worker dan menjalankan di fungsi `worker_thread` dengan parameter `id`.

```
for (int i = 0; i < total_worker; i++) {
    pthread_join(workers[i], NULL);
}
```
`pthread_join` untuk menunggu semua thread selesai.

```
pthread_mutex_destroy(&lock);
pthread_cond_destroy(&cond);
msgctl(msgid, IPC_RMID, NULL);
```
- `pthread_mutex_destroy()`: Menghapus mutex.
- `pthread_cond_destroy()`: Menghapus cond.
- `msgctl(msgid, IPC_RMID, NULL)`: Menghapus message queue.

<b>Kendala</b>
- Melakukan penjumlahan message per worker.



