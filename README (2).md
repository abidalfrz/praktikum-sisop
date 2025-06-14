[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Ph837wyE)
|    NRP     |           Name           |
| :--------: | :----------------------: |
| 5025221133 | Muhammad Abid Baihaqi A. |
| 5025221150 | Nabila Shafa Rahayu      |
| 5025221153 | Kamal Zaky Adinata       |

# Praktikum Modul 1 _(Module 1 Lab Work)_

</div>

### Daftar Soal _(Task List)_

- [Task 1 - New Jeans Global Teratas _(Top Global New Jeans)_](/task-1/)

- [Task 2 - Liburan Bersama Rudi _(Holiday with Rudi)_](/task-2/)

- [Task 3 - Ignatius Si Cloud Engineer _(Ignatius The Cloud Engineer)_](/task-3/)

- [Task 4 - Proxy Terbaik di New Eridu _(Best Proxy in New Eridu)_](/task-4/)

### Laporan Resmi Praktikum Modul 1 _(Module 1 Lab Work Report)_

### Task 1 - Top Global New Jeans
 
Setelah comeback besar-besaran, NewJeans memecahkan berbagai rekor di chart musik global. Oleh karena itu, muncul lah niat Minji untuk menganalisis performa album mereka selama 2024. Manajer Minji memberikan kepada Minji data streaming dari platform “N” melalui link [newjeans_analysis.zip](https://drive.google.com/file/d/1poxmppuB7zOXOVm9Xn7_FtSRwtC10dbw/view?usp=sharing). Data tersebut mencakup data streamer dan detail album NewJeans. Sebagai penggemar NewJeans dan juga seorang suhu dalam dunia Linux, kamu ditantang oleh Minji untuk memenuhi rasa ingin tahunya. Minji ingin kamu untuk menganalisis data yang diberikan oleh manajernya menggunakan shell scripting dan awk. Sebagai Bunnies yang baik, tentu kamu tidak bisa menolak tantangan ini. Adapun analisis yang diminta oleh Minji adalah sebagai berikut:

a. Minji penasaran dengan nama-nama user yang mendengarkan lagunya pada platform “N”. Berhubung Minji sangat menyukai angka **2** dan ia sangat membenci orang yang membuat username menggunakan **underscore (\_)**, bantulah Minji untuk mendapatkan username yang sesuai dengan kriterianya (**terdapat angka 2 dan tidak terdapat underscore**) dan tampilkan jumlahnya. **Pastikan username yang ditampilkan berurutan berdasarkan ASCII Table (dari kecil ke besar).**

**Rule:** gunakan **`DataStreamer.csv`**

<b>Code<b>
```

#!/bin/bash

awk -F',' '{if ($2 ~ /2/ && $2 !~ /_/) print $2}'  ./newjeans_analysis/DataStreamer.csv | LC_ALL=c  sort | awk '{print $0} {count++} END {print "jumlah username adalah " count}'
```

<b>Output<b>

![OutputA](https://github.com/user-attachments/assets/3afbf50c-94df-4f64-875e-a9e401eb5ab5)

<b>Penjelasan</b>
- `awk` adalah command untuk membaca dan memproses suatu file yang diinput.
-  `-F` digunakan untuk menentukan apa pemisah data pada file, di csv ini pemisahnya adalah koma. maka, kita menggunakan "-F','".
-  `if` digunakan sebagai persyaratan, pada kode terdapat ```if ($2 ~ /2/ && $2 !~ /_/) print $2``` yang berarti jika kolom dua terdapat 2 dan _ maka command setelahnya (print kolom 2) akan dilakukan.
-  `|` digunakan untuk memasukkan output dari perintah atau kode di sebelah kiri sebagai input untuk kode atau perintah di kanan. di kode terdapat 2 pipe, 1 untuk menginput username yang telah difilter untuk disort kemudian pipe kedua digunakan untuk menginput hasil nama ke kode terakhir.
-  `sort` digunakan untuk mengurutkan data berdasarkan aturan tertentu. pada kode sort yang digunakan adalah LC_ALL=c sort, yaitu sort yang didasarkan dengan ascii sehingga usn diurutkan sesuai keinginan soal.
-  `END` digunakan untuk menjalankan kode setelah inputan selesai dibaca sepenuhnya. di kode, end digunakan untuk menjalankan kode print count, sehingga count hanya ter print 1 kali di akhir output.
  
b. Ternyata, Minji tidak hanya menyukai angka 2, tetapi semua angka. Ia ingin mengetahui lagu apa yang paling banyak di-streaming oleh user yang memiliki username berangka. Beri tahu Minji nama lagu tersebut dan jumlah usernya. Jika jumlah user tersebut tidak mencapai 24, maka berikan pesan kepada Minji “Maaf, Minji, total streamingnya tidak sesuai harapan :(“. Jika jumlah user mencapai atau melebihi 24, berikan pesan kepada Minji “Keren, Minji! Kamu hebat <3!”.


<b>Code<b>
```
#!/bin/bash

awk -F',' '{if($2 ~ /[0-9]+/) print $2","$3}' ./newjeans_analysis/DataStreamer.csv |
awk -F',' '
BEGIN{a=-1
        b=""}

{count[$2]++}
END {for(e in count) {if (a < count[e]) 
        {       a = count[e]
                b = e}}
print b":", a
    if(count[b] >= 24) {
        print "Keren, Minji! Kamu hebat <3!"
    } else {
        print "Maaf, Minji, total streamingnya tidak sesuai harapan :("
    }
}'
```

<b>Output<b>

![OutputB](https://drive.google.com/uc?id=1eWDhDuuooeu2BYKZtQ8DgKPfIAf7LSri)

<b>Penjelasan</b>
- `awk -F','` untuk menentukan bahwa koma adalah delimiter file csv tsb.
-  `{if($2 ~ /[0-9]+/) print $2","$3}`
  memfilter hanya usn dengan angka saja yang akan di print dan juga mengeprint kolom ke 3 juga.
-  `BEGIN` digunakan untuk melakukan suatu command sebelum membaca file, di sini digunakan untuk mendeklarasikan variabel yang akan digunakan dalam alogaritma pengurutan.
-  `count[$2]++` digunakan untuk memasukkan kolom 2 (sekarang menjadi judul lagu dan membuatnya menyimpan nilai sebanyak judul lagu itu muncul.
-  `END` digunakan untuk menjalankan kode setelah inputan selesai dibaca sepenuhnya.
```
   END {for(e in count) {if (a < count[e]) 
        {       a = count[e]
                b = e}}
print b":", a
    if(count[b] >= 24) {
        print "Keren, Minji! Kamu hebat <3!"
    } else {
        print "Maaf, Minji, total streamingnya tidak sesuai harapan :("
    }
}'
```
kode ini berfungsi untuk mencari judul lagu dengan jumlah streamingan terbanyak. jika nantinya telah ketemu judul lagu dengan jumlah streamingan terbanyak, maka sistem akan mengecek apakah jumlah streaming di atas 24 ataukah tidak karena jumlah streaming di atas 100 maka terprint keren, minji!

c. Tiba-tiba Minji lupa, di album mana lagu yang paling banyak di-streaming tersebut berada. **Carikan Minji nama album dari lagu yang paling banyak di-streaming di platform tersebut, beserta tahun rilisnya!**

**Rule:** wajib menggunakan **`AlbumDetails.csv`** dan output **tidak menggunakan tanda petik (`" "`)**


<b>Code<b>
```
#!/bin/bash

awk -F',' '
BEGIN{
    a = -1
    b = ""}

{if($2 ~ /[0-9]+/) count[$3]++}


END{
    for (e in count) {
        if (a < count[e]) {
            a = count[e]
            b = e}}
            print b":", a
}' ./newjeans_analysis/DataStreamer.csv

b=$(awk -F',' '
BEGIN{a = -1
    b = ""}
{if($2 ~ /[0-9]+/) count[$3]++}

END{
    for (e in count) {
        if (a < count[e]) {
            a = count[e]
            b = e}}
            print b
}' ./newjeans_analysis/DataStreamer.csv)

awk -F',' -v terbanyak="$b" '{if($2 == terbanyak) print $1, $3}' ./newjeans_analysis/AlbumDetails.csv

```

<b>Output<b>

![OutputC](https://drive.google.com/uc?id=1aN2hVJrFobOH2ucfKGkMYGCsenCfRfC3)

<b>Penjelasan</b>
- `awk -F',' '
BEGIN{
    a = -1
    b = ""}

{if($2 ~ /[0-9]+/) count[$3]++}


END{
    for (e in count) {
        if (a < count[e]) {
            a = count[e]
            b = e}}
            print b":", a
}' ./newjeans_analysis/DataStreamer.csv` 
kode ini sama persis dengan kode task B, karena memang perintahnya sama.
-  `b=$` digunakan untuk mengambil output dari hasil pengolahan data di dalamnya sebagai variabel yaitu b. Kode di dalamnya juga sama dengan kode di atasnya, yaitu mencoba mendapatkan judul lagu dengan jumlah pendengaran terbanyak (cookie) kemudian hasilnya dimasukkan ke dalam variabel b.
-  `if` digunakan sebagai persyaratan, pada kode terdapat `if ($2 ~ /2/ && $2 !~ /_/) print $2` yang berarti jika kolom dua terdapat 2 dan _ maka command setelahnya (print kolom 2) akan dilakukan.
-  `|` digunakan untuk memasukkan output dari perintah atau kode di sebelah kiri sebagai input untuk kode atau perintah di kanan. di kode terdapat 2 pipe, 1 untuk menginput username yang telah difilter untuk disort kemudian pipe kedua digunakan untuk menginput hasil nama ke kode terakhir.
-  `-v` digunakan untuk mengambil variabel shell ke dalam awk, di kode `terbanyak="$b"` yang berarti variabel yang tadi didapatkan dan disimpan pada variabel shell di masukkan ke dalam variabel terbanyak pada awk.
-  `awk -F',' -v terbanyak="$b" '{if($2 == terbanyak) print $1, $3}' ./newjeans_analysis/AlbumDetails.csv` 
line terakhir ini digunakan untuk menyocokkan judul lagu dengan jumlah pendengar terbanyak dengan file AlbumDetails yang kemudian mengoutputkan kolom 1 dan 3 yang berisi nama album dan tahun rilisnya.

d. Minji ingin mengajukan ke agensi untuk membuat campaign iklan supaya lagu-lagu NewJeans lebih dikenal, tapi Minji bingung mau optimasi iklan untuk device apa. Berikut tugas kamu untuk membantu Minji menyusun proposal iklan sebelum diberikan ke CEO ADOR:

1.  **Hitung berapa banyak pengguna** yang menggunakan setiap jenis device (**Tablet, Smart TV, Desktop, Mobile**) untuk streaming lagu NewJeans.
2.  **Hitung total durasi streaming (detik)** untuk setiap device.
3.  **Tentukan:**

    - **Device paling populer** yang punya user terbanyak.
    - **Device menang durasi** yang memiliki total streaming tertinggi.
    - **Device ter-“loyal”** berdasarkan **rasio (total durasi / user) tertinggi**.

<b>Code<b>
```
#!/bin/bash

tr -d '\r' < DataStreamer.csv > cleaned_DataStreamer.csv
awk -F',' 'NR > 1 {yeah[$7]++;waktu[$7]+=$4}
END{for(e in yeah){print e "\nJumlah pengguna:", yeah[e]"\nTotal waktu pendengaran:", waktu[e]}}
BEGIN{a=-1; b=""; c=-1; d=""; g=0; f=""}
END{for(e in yeah) {if (a < yeah[e])
        {       a = yeah[e]
                b = e}}
print"\nDevice paling populer adalah:", b"\nDengan jumlah user sebanyak:", a
        }
END{for(e in waktu) {if (c < waktu[e])
        {       c = waktu[e]
                d = e}}
print"\nDevice dengan waktu penggunaan terlama adalah:", d"\nDengan total waktu  sebanyak:", c"s"
        }
END{for(e in waktu) {if (g < waktu[e]/yeah[e])
        {       g = waktu[e]/yeah[e]
                f = e}}
print"\nDevice dengan rasio terbesar adalah:", f"\nDengan rasio sebesar:", g,": 1"
        }
' cleaned_DataStreamer.csv
```

<b>Output<b>

![OutputD](https://drive.google.com/uc?id=1HvCgx7KNHpdUae7mcU9BsV-wo7RdLNc1)

<b>Penjelasan</b>

- `tr -d '\r' < DataStreamer.csv > cleaned_DataStreamer.csv` 
adalah kode untuk mengubah (tr) khususnya menghapus (-d) sisaan \r yang biasanya terdapat pada pemformatan windows. kode ini menghapus \r pada file dan menyimpan versi "bersih" dari file ke dalam file cleaned_DataStreamer.csv.
-  `awk -F',' 'NR > 1 {yeah[$7]++;waktu[$7]+=$4}` 
kode ini mengiterasi isi file dan menghitung tiap jumlah kemunculan tiap data di kolom 7, menghitung jumlah total waktu pendengaran yang kemudian di masukkan ke dalam array dengan index kolom 7, dan kode NR > 1 bermaksud bahwa kode hanya membaca file pada baris ke 2 dan seterusnya.
-  `END{for(e in yeah){print e "\nJumlah pengguna:", yeah[e]"\nTotal waktu pendengaran:", waktu[e]}}` 
kode ini mengeprint variabel yang terdapat pada array yeah (berisi nama-nama device) dan mengeprint total waktu streaming device dengan mengakses array waktu dengan string pada array yeah karena keduanya memiliki index array yang sama. di kode ini juga menggunakan `for(e in yeah)` yang memiliki arti untuk tiap index di array sehingga nantinya e yang diprint adalah index" string yang tadinya berasal dari kolom ke 7.
-  `BEGIN{a=-1; b=""; c=-1; d=""; g=0; f=""}` 
kode ini menggunakan begin untuk menginisiasi variabel-variabel yang digunakan sebagai algoritma pencari nilai data terbanyak nantinya, ada 3 pasang karena nanti ada 3 kali pencarian.
-  `END{for(e in yeah) {if (a < yeah[e])
        {       a = yeah[e]
                b = e}}
print"\nDevice paling populer adalah:", b"\nDengan jumlah user sebanyak:", a
        }` 
kode ini berisi algoritma untuk mencari device dengan jumlah user terbanyak dengan cara membandingkan jumlah user tiap-tiap device yang sudah disimpan dalam bentuk index array yeah. kemudian kode akan mengeprint hasil pencariannya dengan format yang telah ditentukan.
-  `END{for(e in waktu) {if (c < waktu[e])
        {       c = waktu[e]
                d = e}}
print"\nDevice dengan waktu penggunaan terlama adalah:", d"\nDengan total waktu  sebanyak:", c"s"
        }` 
sama dengan kode di atasnya, bedanya kode ini mencari device dengan total waktu terlama yang disimpan dalam array waktu. kode ini juga nantinya akan mengeprint output berupa nama device dan total waktu device dengan total waktu pendengaran terlama.
-  `END{for(e in waktu) {if (g < waktu[e]/yeah[e])
        {       g = waktu[e]/yeah[e]
                f = e}}
print"\nDevice dengan rasio terbesar adalah:", f"\nDengan rasio sebesar:", g,": 1"
        }
' cleaned_DataStreamer.csv` 
menggunakan algoritma yang sama dengan kedua for loop di atasnya, bedanya for loop yang ini mencari device dengan rasio waktu/pengguna terbanyak. tidak lupa semua kode yang dirun tadi menggunakan cleaned_datastreamer yang sudah dihapus \r nya.

**Sebagai Bunnies sejati dan suhu Linux, tunjukkan kemampuanmu dan bantu Minji!**

🔥🔥🔥


## Task 2 - Liburan Bersama Rudi
Rudi membuat sebuah website untuk personal brandingnya yang sementara berjalan di local pada komputer laboratorium. Rudi yang baru belajar kebingungan karena sering muncul error yang tidak ia pahami. Untuk itu dia meminta ketiga temannya Andi, Budi, dan Caca untuk melakukan pengecekan secara berkala pada website Rudi. Dari pengecekan secara berkala, Rudi mendapatkan sebuah file `access.log` yang berisi catatan akses dari ketiga temannya. Namun, Rudi masih tidak paham cara untuk membaca data pada file tersebut sehingga meminta bantuanmu untuk mencari data yang dibutuhkan Rudi.

### Soal A
Rudi meminta praktikan untuk menampilkan total request yang dibuat oleh setiap IP dan menampilkan jumlah dari setiap status code

<b>Code</b>
```
#!/bin/bash

awk '{iarr[$1]++}{carr[$9]++} END {print "Jumlah request tiap ip:";
for(j in iarr){print j," "iarr[j]};print "\nJumlah request tiap status:";
for(j in carr){print j," "carr[j]}}' access.log
```
<b>Output</b>

![Output A](https://drive.google.com/uc?id=1Z3cCfRhHl4DmLs-LWiHa5kIbbM66SLDu)

<b>Penjelasan</b>
- `awk` adalah command yang digunakan untuk membaca dan memproses file.
- `iarr` adalah array dengan nama iarr untuk menyimpan jumlah kemunculan setiap IP Address. `$1` merepresentasikan kolom pertama dalam `access.log`, yaitu IP Address. Jika IP Address sudah ada dalam array `iarr`, nilainya akan bertambah 1 setiap kali ditemukan lagi.
- `carr` adalah array dengan nama carr untuk menyimpan jumlah kemunculan setiap status code. `$9` merepresentasikan kolom ke sembilan dalam `access.log`, yaitu status code. Jika status code sudah ada dalam array `carr`, nilainya akan bertambah 1 setiap kali ditemukan lagi.
- Setelah semua baris dalam access.log diproses, command `END` dijalankan untuk mencetak hasilnya.
- `for(j in iarr){ print j, iarr[j] }` adalah loop untuk mencetak setiap IP beserta jumlah request yang dibuat.
- `for(j in carr){ print j, carr[j] }` mencetak setiap status code beserta jumlah request yang dibuat.

### Soal B
Karena banyaknya status code error, Rudi ingin tahu siapa yang menemukan error tersebut. Setelah melihat-lihat, ternyata IP komputer selalu sama. Dengan bantuan `peminjaman_komputer.csv`, Rudi meminta kamu untuk membuat sebuah program bash yang akan menerima inputan tanggal dan IP serta menampilkan siapa pengguna dan membuat file backup log aktivitas.

<b>Code</b>
```
#!/bin/bash

echo "Input tanggal (MM/DD/YYYY):"
read tanggal
echo "Input IP address:"
read ip

x=$(echo "$ip" | cut -d'.' -f4)
day=$(echo "$tanggal" | cut -d'/' -f2)
month=$(echo "$tanggal" | cut -d'/' -f1)
year=$(echo "$tanggal" | cut -d'/' -f3)

if [[ $month != "01" || $year != "2025" || ! $ip =~ ^192\.168\.1\. ]]
then
	echo "Data yang kamu cari tidak ada"
else	
	if grep -q "192.168.1.$x" access.log && grep -q "$day/Jan/2025" access.log
	then
		pengguna=$(awk -F',' -v n="$x" -v d="$day" '{if($2 == n && $1 ~ "/"d"/2025") print $3}' peminjaman_computer.csv)
		echo "Pengguna saat itu adalah $pengguna"
		echo "Log Aktivitas $pengguna"

		mkdir -p backup
		filename="${pengguna}_$(echo "$tanggal" | tr -d '/')_$(date +"%H%M%S")"
		awk -v n="$x" -v d="$day" '{gsub("\"", "", $6)}{if($1 == "192.168.1."n && $4 ~ d"/Jan/2025") print $4"]:",$6, "-", $7,"-",$9}' access.log>>./backup/"$filename.log"
	
	else
		echo "Data yang kamu cari tidak ada"
	fi
fi	
```

<b>Output</b>

![Output B](https://drive.google.com/uc?id=1ZEGO2o5QYdKnZZsxB5ZiL_u64-0NuSrH)

<b>Penjelasan</b>
```
echo "Input tanggal (MM/DD/YYYY):"
read tanggal
echo "Input IP address:"
read ip
```
Membaca input dari pengguna untuk tanggal dengan format (MM/DD/YYYY) dan IP Address.
```
x=$(echo "$ip" | cut -d'.' -f4)
day=$(echo "$tanggal" | cut -d'/' -f2)
month=$(echo "$tanggal" | cut -d'/' -f1)
year=$(echo "$tanggal" | cut -d'/' -f3)
```
Mengekstrak hasil input:
- `x`: Mengambil bagian terakhir dari IP.
- `day`: Mengambil hari dari tanggal.
- `month`: Mengambil bulan dari tanggal.
- `year`: Mengambil tahun dari tanggal.
```
if [[ $month != "01" || $year != "2025" || ! $ip =~ ^192\.168\.1\. ]]
then
	echo "Data yang kamu cari tidak ada"
```
Melakukan pengecekan jika `month` tidak bernilai "01" atau `year` tidak bernilai 2025 atau `ip` tidak memiliki pola 192.168.1. akan mengeluarkan output `Data yang kamu cari tidak ada` dan script akan berhenti.
```
if grep -q "192.168.1.$x" access.log && grep -q "$day/Jan/2025" access.log
```
Melakukan pengecekan apakah IP dengan pola 192.168.1.`x` ada di `access.log` jika iya akan menjalankan kondisi ke dua, yaitu melakukan pengecekan apakah tanggal dengan pola `day`/Jan/2025 ada di `access.log`. JIka salah satu dari kondisi tidak terpenuhi, akan mengeluarkan output `Data yang kamu cari tidak ada` dan script akan berhenti.
- `grep -q` mencari pola tanpa menampilkan hasilnya dan mengembalikan exit status.
```
pengguna=$(awk -F',' -v n="$x" -v d="$day" '{if($2 == n && $1 ~ "/"d"/2025") print $3}' peminjaman_computer.csv)
		echo "Pengguna saat itu adalah $pengguna"
		echo "Log Aktivitas $pengguna"
```
Jika kedua kondisi terpenuhi, akan menggunakan `awk` untuk membuat variabel pengguna dari file `peminjaman_computer.csv` berdasarkan `x` dan `day`.
- `awk` adalah command yang digunakan untuk membaca dan memproses file.
- `-F','` menentukan bahwa delimiter dalam file CSV adalah koma.
- `-v n="$x" -v d="$day"` mengambil variabel dari luar awk, yaitu `x` dan `day` untuk digunakan sebagai variabel dalam awk.
- `if($2 == n && $1 ~ "/"d"/2025") print $3` melakukan pengecekan jika kolom ke-2 memiliki nilai sama dengan `n` dan kolom pertama memiliki pola /`d`/2025
  maka akan melakukan print untuk kolom ke-3 (nama pengguna).
```
mkdir -p backup
```
Membuat direktori `backup` di direktori saat ini jika belum ada.
```
filename="${pengguna}_$(echo "$tanggal" | tr -d '/')_$(date +"%H%M%S")"
```
- Variabel `filename` untuk menyimpan nama file backup dengan format `pengguna_MMDDYYY_HHMMSS`
- `tr -d '/'` menghapus karakter / dari tanggal agar sesuai format.
```
awk -v n="$x" -v d="$day" '{gsub("\"", "", $6)}{if($1 == "192.168.1."n && $4 ~ d"/Jan/2025") print $4"]:",$6, "-", $7,"-",$9}' access.log>>./backup/"$filename.log"
```
Menggunakan `awk` untuk mengekstrak `access log`.
- `-v n="$x" -v d="$day"` mengambil variabel dari luar awk, yaitu `x` dan `day` untuk digunakan sebagai variabel dalam awk.
- `gsub("\"", "", $6)` menghapus semua tanda kutip " yang terdapat di kolom ke-6.
- `if($1 == "192.168.1."n && $4 ~ d"/Jan/2025") print $4"]:",$6, "-", $7,"-",$9` melakukan pengecekan jika kolom pertama memiliki nilai sama dengan 192.168.1.`n` dan kolom ke-4 memiliki pola `d`/Jan/2025 maka akan melakukan print $4"]:",$6, "-", $7,"-",$9 yang berarti mencetak log dalam format `[dd/mm/yyyy:hh:mm:ss]: method - endpoint - status_code`
- `>>./backup/"$filename.log"` hasil dari pencetakan log akan disimpan dan diteruskan di `./backup/"filename.log"`

![Output B Log](https://drive.google.com/uc?id=1mN62L_vbODrCt4lkuSCCUQH8RQUNUvm3)

### Soal C
Rudi ingin memberikan hadiah kepada temannya yang sudah membantu. Namun karena dana yang terbatas, Rudi hanya akan memberikan hadiah kepada teman yang berhasil menemukan server error dengan status code 500 terbanyak. Bantu Rudi untuk menemukan siapa dari ketiga temannya yang berhak mendapat hadiah dan tampilkan jumlah status code 500 yang ditemukan.

<b>Code</b>
```
#!/bin/bash

awk '{gsub("\[", "", $4); split($4, arr, ":"); print $1"-"arr[1]","$9}' access.log | awk -F',' '{if($2 == "500") count[$1]++} END {for(e in count) print e,count[e]}' | sort -k2 -nr | awk -F'-' '{print $1, $2}' | awk '{split($1, ip, "."); split($2, date, "/"); print date[1]","ip[4]","$3}'>./extract.csv

awk -F',' '{if(NR==FNR) {data[substr($1, 4, 2)","$2] = $3;} else {if(($1","$2) in data) print data[$1","$2], $3;}}' peminjaman_computer.csv extract.csv | awk '{count[$1] += $2} END {for(e in count) print e, count[e]}' | sort -k2 -nr | head -n 1 | awk '{print "nama:", $1, "\njumlah status code 500 ditemukan:", $2}'
```

<b>Output</b>

![Output C](https://drive.google.com/uc?id=10htLwvw34t49i7DXZQ2GNgCP11ujvhAG)

<b>Penjelasan</b>

```
awk '{gsub("\\[", "", $4); split($4, arr, ":"); print $1"-"arr[1]","$9}' access.log
```
Mengekstrak informasi dari access.log, seperti IP Address, tanggal dari timestamp kolom ke-4, dan status code di kolom ke-9.
- `gsub("\\[", "", $4)` menghapus semua tanda kutip [ yang terdapat di kolom ke-6.
- `split($4, arr, ":")` memisahkan timestamp menggunakan delimiter ":" dan menyimpannya ke dalam array arr.
- `print $1"-"arr[1]","$9` print IP address ($1), elemen pertama dari arr (tanggal), dan status code ($9) dalam format IP-Tanggal,status code.
```
awk -F',' '{if($2 == "500") count[$1]++} END {for(e in count) print e,count[e]}'
```
Menghitung jumlah status code 500 untuk setiap IP-Tanggal.
- `-F','` menentukan bahwa delimiter adalah koma.
- `if($2 == "500") count[$1]++` `count` adalah array dengan nama count untuk menyimpan jumlah kemunculan setiap status code yang bernilai 500. `$1` merepresentasikan kolom pertama (IP-Tanggal) dari hasil awk sebelumnya. Jika status code 500 sudah ada dalam array count, nilainya akan bertambah 1 setiap kali ditemukan lagi.
- Setelah semua baris diproses, command `END` dijalankan untuk mencetak hasilnya.
- `for(e in count) print e,count[e]` adalah loop untuk mencetak setiap IP-Tanggal beserta jumlah status code 500 yang ditemukan.
```
sort -k2 -nr
```
Mengurutkan kolom ke-2.
- `-k2` mengurutkan berdasarkan kolom ke-2 (jumlah status code 500).
- `-nr` mengurutkan dalam urutan numerik secara descending.
```
awk -F'-' '{print $1, $2} | awk '{split($1, ip, "."); split($2, date, "/"); print date[1]","ip[4]","$3}'>./extract.csv'
```
- `awk -F'-' '{print $1, $2}` memisahkan IP dan tanggal dari hasil sebelumnya.
- `split($1, ip, ".")` memisahkan IP menggunakan delimiter "." dan menyimpannya ke dalam array `ip`.
- `split($2, date, "/")` memisahkan tanggal menggunakan delimiter / dan menyimpannya ke dalam array `date`.
- `print date[1]","ip[4]","$3}'>./extract.csv'` print elemen pertama dari array date (hari), elemen ke-4 array ip (angka terakhir IP), dan jumlah status code 500. Hasilnya akan disimpan di file baru, yaitu extract.csv.
  
<b>Tampilan Extract.csv</b>

kolom 1 = Hari, kolom 2 = Angka terakhir IP Address, kolom 3 = Jumlah status code 500

![extract.csv image](https://drive.google.com/uc?id=109aOzUwCSXW1kW9_zgPs_kp_vVsUnqmf)

```
awk -F',' '{if(NR==FNR) {data[substr($1, 4, 2)","$2] = $3;} else {if(($1","$2) in data) print data[$1","$2], $3;}}' peminjaman_computer.csv extract.csv
```
- `-F','` menentukan bahwa delimiter dalam file CSV adalah koma.
- `if(NR==FNR) {data[substr($1, 4, 2)","$2] = $3` kondisi ketika membaca file pertama `peminjaman_computer.csv` membuat array `data` dengan key berupa kombinasi substring dari kolom pertama (tanggal) dimulai dari karakter ke-4 dengan panjang 2 karakter (hari) dan kolom ke-2 (IP komputer). kemudian menyimpan kolom ke-3 (nama nengguna) sebagai nilai.
- `else {if(($1","$2) in data) print data[$1","$2], $3;}}'` kondisi setelah membaca file pertama (melanjutkan ke file ke dua `extract.csv`) melakukan pengecekan apakah kombinasi kolom pertama (hari) dan kolom ke-2 (angka terakhir ip) ada dalam array `data`. Jika ada, akan print `data[$1","$2]` (nama pengguna) sesuai key dan kolom ke-3 (jumlah status code 500).
```
awk '{count[$1] += $2} END {for(e in count) print e, count[e]}'
```
Menghitung jumlah status code 500 untuk setiap nama pengguna.
- `count` adalah array dengan nama count untuk menyimpan jumlah kemunculan setiap status code yang bernilai 500. `$1` merepresentasikan kolom pertama (nama pengguna) dari hasil awk sebelumnya. status code 500 yang ditemukan akan dijumlahkan sesuai dengan nama pengguna.
- Setelah semua baris diproses, command `END` dijalankan untuk mencetak hasilnya.
- `for(e in count) print e, count[e]` adalah loop untuk mencetak setiap nama pengguna beserta jumlah status code 500 yang ditemukan.
```
sort -k2 -nr | head -n 1
```
Mengurutkan berdasarkan kolom ke-2 setelah itu mengambil 1 baris pertama.
- `-k2` mengurutkan berdasarkan kolom ke-2 (jumlah status code 500).
- `-nr` mengurutkan dalam urutan numerik secara descending.
- `head -n 1` mengambil 1 baris pertama dalam suatu file.
```
awk '{print "nama:", $1, "\njumlah status code 500 ditemukan:", $2}'
```
Menampilkan kolom pertama (nama pengguna) dengan kolom ke-2 (jumlah status code 500) terbanyak.

## Task 3 - Ignatius Si Cloud Engineer
Ignatius ingin mengembangkan sebuah sistem Cloud Storage Otomatis untuk mengelola penyimpanan file secara terintegrasi setelah pengguna berhasil login. Sistem ini harus menyediakan mekanisme register dan login untuk memastikan keamanan akses. Serta secara otomatis mengunduh gambar dari internet ketika pengguna berhasil login, tentunya layanan Cloud Storage juga memberikan otomasi backup gambar dalam format terkompresi dengan nama yang disesuaikan berdasarkan waktu pembuatan.

### Soal A
Login dan Register Sistem harus memastikan hanya pengguna terdaftar yang dapat mengakses layanan. Proses registrasi dilakukan melalui script register.sh dan data pengguna yang berhasil didaftarkan disimpan di `/cloud_storage/users.txt`. Proses login dilakukan melalui script `login.sh` dan semua aktivitas login atau register dicatat dalam file `cloud_log.txt`.

<b>Code register.sh</b>
```
#!/bin/bash

mkdir -p cloud_storage
touch cloud_storage/users.txt

echo "input username:"
read username

mapfile -t array < <(awk '{print tolower($1)}' ./cloud_storage/users.txt)

while [ true ]
do
    found=false
    for user in "${array[@]}"
    do
        if [[ "$user" == "${username,,}" ]]
	then
            found=true
            break
        fi
    done

    if $found
    then
        echo "$(date +"%y/%m/%d %T") REGISTER: ERROR User already exists" >> ./cloud_log.txt
        echo "REGISTER: ERROR User already exists"
        echo "input username:"
        read username
    else
        break
    fi
done


while [ true ]
do
	echo "input password:"
	read password

	if [[ ${#password} -lt 8 ]]
	then
		echo "$(date +"%y/%m/%d %T") REGISTER: ERROR must be at least 8 characters">>./cloud_log.txt
		echo "REGISTER: ERROR must be at least 8 characters"
		continue
	fi
	if [[ ! "$password" =~ [A-Z] ]]
	then
		echo "$(date +"%y/%m/%d %T") REGISTER: ERROR must be at least contains one capital letter">>./cloud_log.txt
		echo "REGISTER: ERROR must be at least contains one capital letter"
                continue
	fi
	if [[ ! "$password" =~ [0-9] ]]
        then
                echo "$(date +"%y/%m/%d %T") REGISTER: ERROR must be at least contains one number">>./cloud_log.txt
		echo "REGISTER: ERROR must be at least contains one number"
                continue
        fi
	if [[ ! "$password" =~ [^a-zA-Z0-9] ]]
        then
                echo "$(date +"%y/%m/%d %T") REGISTER: ERROR must be at least contains one special character">>./cloud_log.txt
		echo "REGISTER: ERROR must be at least contains one special character"
                continue
        fi
	if [[ "$password" == "$username" ]]
        then
                echo "$(date +"%y/%m/%d %T") REGISTER: ERROR must not be the same as Username">>./cloud_log.txt
		echo "REGISTER: ERROR must not be the same as Username"
                continue
        fi
	if [[ "$password" =~ [Cc][Ll][Oo][Uu][Dd] || "$password" =~ [Ss][Tt][Oo][Rr][Aa][Gg][Ee] ]]
        then
                echo "$(date +"%y/%m/%d %T") REGISTER: ERROR Must not contain the words 'cloud' or 'storage'">>./cloud_log.txt
		echo "REGISTER: ERROR Must not contain the words 'cloud' or 'storage'"
                continue
        fi
	break
done

echo "$(date +"%y/%m/%d %T") REGISTER: INFO User registered successfully">>./cloud_log.txt
echo "REGISTER: INFO User registered successfully"
echo $username $password >> ./cloud_storage/users.txt
```
<b>Output</b>

![Output Register](https://drive.google.com/uc?id=10-vBqjwzT0CWkGCQuDFZxbht7mCsD6nl)

<b>Tampilan cloud_log.txt</b>

![output log](https://drive.google.com/uc?id=1odHzX0F_ZH77ifWFR9G9mskQnZKl87PO)

<b>Tampilan users.txt di direktori cloud_storage</b>

![output users](https://drive.google.com/uc?id=1e9Ax0pcEKuqlwCmWl0W7ieuMzOISJqVo)

<b>Penjelasan</b>
```
mkdir -p cloud_storage
touch cloud_storage/users.txt
```
Membuat direktori `cloud_storage` dan membuat file `users.txt` di dalamnya.
```
echo "input username:"
read username
```
Membaca input dari pengguna untuk username.
```
mapfile -t array < <(awk '{print tolower($1)}' ./cloud_storage/users.txt)
```
Menggunakan `mapfile` untuk membuat array dengan nama `array` yang elemennya diambil dari setiap baris pada kolom pertama (username) dalam bentuk lowercase `users.txt`.
```
while [ true ]
do
    found=false
    for user in "${array[@]}"
    do
        if [[ "$user" == "${username,,}" ]]
	then
            found=true
            break
        fi
    done
```
Loop untuk melakukan pengecekan jika input username sama dengan username yang telah register terlebih dahulu.
- `found` variabel bertipe boolean yang digunakan sebagai indikator jika username sama.
- `${username,,}` Mengubah input username menjadi huruf kecil.
- Jika input username sama, variabel `found` menjadi true dan for loop berhenti, tetapi jika berbeda, mengecek tiap elemen (username `users.txt`) dalam array hingga selesai.
```
if $found
    then
        echo "$(date +"%y/%m/%d %T") REGISTER: ERROR User already exists" >> ./cloud_log.txt
        echo "REGISTER: ERROR User already exists"
        echo "input username:"
        read username
    else
        break
    fi
```
Melakukan pengecekan jika `found` = true, mengeluarkan log error yang akan disimpan di `cloud_log.txt` dan pengguna akan diminta untuk melakukan input username hingga username berbeda dengan username yang sudah ada.
```
while [ true ]
do
	echo "input password:"
	read password
```
Membaca input dari pengguna untuk password di dalam loop.
```
if [[ ${#password} -lt 8 ]]
	then
		echo "$(date +"%y/%m/%d %T") REGISTER: ERROR must be at least 8 characters">>./cloud_log.txt
		echo "REGISTER: ERROR must be at least 8 characters"
		continue
	fi
```
Melakukan pengecekan terhadap panjang input password. Jika panjang password kurang dari 8 character, mengeluarkan log error yang akan disimpan di `cloud_log.txt` dan pengguna akan diminta untuk melakukan input password hingga memiliki panjang minimal 8 character.
```
if [[ ! "$password" =~ [A-Z] ]]
	then
		echo "$(date +"%y/%m/%d %T") REGISTER: ERROR must be at least contains one capital letter">>./cloud_log.txt
		echo "REGISTER: ERROR must be at least contains one capital letter"
                continue
	fi
```
Melakukan pengecekan apakah input password mengandung huruf kapital. JIka tidak, mengeluarkan log error yang akan disimpan di `cloud_log.txt` dan pengguna akan diminta untuk melakukan input password hingga memiliki minimal 1 character dengan huruf kapital.
```
if [[ ! "$password" =~ [0-9] ]]
        then
                echo "$(date +"%y/%m/%d %T") REGISTER: ERROR must be at least contains one number">>./cloud_log.txt
		echo "REGISTER: ERROR must be at least contains one number"
                continue
        fi
```
Melakukan pengecekan apakah input password mengadung angka. Jika tidak, mengeluarkan log error yang akan disimpan di `cloud_log.txt` dan pengguna akan diminta untuk melakukan input password hingga memiliki minimal 1 character angka.
```
if [[ ! "$password" =~ [^a-zA-Z0-9] ]]
        then
                echo "$(date +"%y/%m/%d %T") REGISTER: ERROR must be at least contains one special character">>./cloud_log.txt
		echo "REGISTER: ERROR must be at least contains one special character"
                continue
        fi
```
Melakukan pengecekan apakah input password mengadung selain charcter alphanumeric `a-zA-Z0-9` (special character). JIka tidak, mengeluarkan log error yang akan disimpan di `cloud_log.txt` dan pengguna akan diminta untuk melakukan input password hingga memiliki minimal 1 special character.
```
if [[ "$password" == "$username" ]]
        then
                echo "$(date +"%y/%m/%d %T") REGISTER: ERROR must not be the same as Username">>./cloud_log.txt
		echo "REGISTER: ERROR must not be the same as Username"
                continue
        fi
```
Melakukan pengecekan apakah input password sama dengan input username. JIka iya, mengeluarkan log error yang akan disimpan di `cloud_log.txt` dan pengguna akan diminta untuk melakukan input password hingga berbeda dengan input username.
```
if [[ "$password" =~ [Cc][Ll][Oo][Uu][Dd] || "$password" =~ [Ss][Tt][Oo][Rr][Aa][Gg][Ee] ]]
        then
                echo "$(date +"%y/%m/%d %T") REGISTER: ERROR Must not contain the words 'cloud' or 'storage'">>./cloud_log.txt
		echo "REGISTER: ERROR Must not contain the words 'cloud' or 'storage'"
                continue
        fi
	break
```
Melakukan pengecekan apakah input password mengandung kata `cloud` atau `storage`. JIka iya, mengeluarkan log error yang akan disimpan di `cloud_log.txt` dan pengguna akan diminta untuk melakukan input password hingga tidak mengandung kedua kata tersebut.
```
echo "$(date +"%y/%m/%d %T") REGISTER: INFO User registered successfully">>./cloud_log.txt
echo "REGISTER: INFO User registered successfully"
echo $username $password >> ./cloud_storage/users.txt
```
Jika input username dan input password telah memenuhi persyaratan, loop berhenti dan mengeluarkan log success untuk register yang akan disimpan di `cloud_log.txt`. Input username dan password disimpan di `./cloud_storage/users.txt` dengan format `username password`.

<b>Output jika error</b>

![reg error](https://drive.google.com/uc?id=1IPXIDNDZNDRe0FdSwTw7TxPjGGXi2ls9)

![error pass8](https://drive.google.com/uc?id=1DpAgBPHk8XXBjTa8AhvvkA2On5226Z8R)

![error passCap](https://drive.google.com/uc?id=1hgFe6Dznjkirq_zq6emCGnYpV13Xgrug)

![error passNum](https://drive.google.com/uc?id=1cUcGiDqqqueKJoO-XfB5Z6Zoa9zyICLU)

![error passSpecial](https://drive.google.com/uc?id=1e-0L2UEKPrs8KO_bZe0MB_D5FEek1YFD)

![error passSame](https://drive.google.com/uc?id=1UY6Z6nKg4g2UshTzbeYcydHvPWAbrC2c)

![error passCloud](https://drive.google.com/uc?id=1JCIlzE46vMtgropP3nNvJQA0fjKzpB5l)

![error passStorage](https://drive.google.com/uc?id=15J8-cvyW32-kYiCFqa7OsoKsVgX10D5A)

<b>Code login.sh</b>
```
#!/bin/bash

if cat cloud_log.txt | grep -v "REGISTER" | tail -n 1 | grep -q 'logged in'
then
	user=$(cat cloud_log.txt | grep -v -E "REGISTER|LOGOUT" | tail -n 1 | grep -oE 'User [a-zA-Z0-9]+' | cut -d' ' -f2)
        echo "Must log out first before login, current user: $user"
	echo "Log out? [y/n]"
	read out
	if [[ "$out" == 'y' ]]
	then
		echo "$(date +"%y/%m/%d %T") LOGOUT: INFO User $user logged out">>./cloud_log.txt
		echo "LOGOUT: INFO User $user logged out"
	fi
else
	echo "Input username: "
	read username
	echo "Input password: "
	read password

	if grep -F -q "$username $password" ./cloud_storage/users.txt
	then
		echo "$(date +"%y/%m/%d %T") LOGIN: INFO User $username logged in">>./cloud_log.txt
		echo "LOGIN: INFO User $username logged in"
	else
		echo "$(date +"%y/%m/%d %T") LOGIN: ERROR Failed login attempt on user $username">>./cloud_log.txt
        	echo "LOGIN: ERROR Failed login attempt on user $username"
	fi
fi
```
<b>Output</b>

![output login](https://drive.google.com/uc?id=15g7li1BjBHay6UrHcFQ7mHZ5TB1tCM2u)

![output logout](https://drive.google.com/uc?id=1y9Bw1ZDiJva2C0df7lXerPOzftWtKYrm)

<b>Tampilan cloud_log.txt</b>

![log login](https://drive.google.com/uc?id=1RXnyegJ5hRq7hw_Y92t2gPwUOP9AqZwB)

<b>Penjelasan</b>
```
if cat cloud_log.txt | grep -v "REGISTER" | tail -n 1 | grep -q 'logged in'
```
Melakukan pengecekan pada satu baris terakhir file `cloud_log.txt` apakah ada kata `logged in` yang berarti ada pengguna yang sedang login.
- `cat cloud_log.txt` membaca file `cloud_log.txt`.
- `grep -v "REGISTER"` mengecualikan baris yang mengandung kata "REGISTER" di file.
- `tail -n 1` mengambil satu baris terakhir dari hasil sebelumnya.
- `grep -q 'logged in'` memeriksa apakah baris terakhir mengandung 'logged in'. `-q` mengembalikan exit status.
```
user=$(cat cloud_log.txt | grep -v -E "REGISTER|LOGOUT" | tail -n 1 | grep -oE 'User [a-zA-Z0-9]+' | cut -d' ' -f2)
```
Jika ada pengguna yang sedang login, membuat variabel user dari hasil berbagai commands untuk menemukan pengguna yang sedang login.
- `cat cloud_log.txt` membaca file `cloud_log.txt`.
- `grep -v "REGISTER|LOGOUT"` mengecualikan baris yang mengandung kata "REGISTER" atau "LOGOUT" di file. `-E` untuk melakukkan regex/pencocokan.
- `tail -n 1` mengambil satu baris terakhir dari hasil sebelumnya.
- `grep -oE 'User [a-zA-Z0-9]+'` mengekstrak kata dalam teks dengan pola 'User [a-zA-Z0-9]+'. `-o` hanya menampilkan bagian teks yang cocok dengan pola.
- `cut -d' ' -f2` mengambil kata kedua dari hasil sebelumnya. `d' '` menentukan bahwa delimiter adalah spasi, `-f2` untuk mengambil kata ke-2.
```
echo "Must log out first before login, current user: $user"
	echo "Log out? [y/n]"
	read out
```
Memberi tahu pengguna bahwa harus logout terlebih dahulu sebelum login dan menampilkan pengguna yang sedang login saat ini.
Membaca input melalui variabel `out` yang ditujukan kepada pengguna yang sedang login apakah ingin log out dengan format input 'y' atau 'n'.
```
if [[ "$out" == 'y' ]]
then
	echo "$(date +"%y/%m/%d %T") LOGOUT: INFO User $user logged out">>./cloud_log.txt
	echo "LOGOUT: INFO User $user logged out"
fi
```
Jka `out` = 'y' yang berarti pengguna saat ini sudah melakukan log out, mengeluarkan log logout yang akan disimpan di `cloud_log.txt`.
```
echo "Input username: "
read username
echo "Input password: "
read password
```
Jika tidak ada pengguna yang sedang login, membaca input untuk username dan password.
```
if grep -F -q "$username $password" ./cloud_storage/users.txt
then
	echo "$(date +"%y/%m/%d %T") LOGIN: INFO User $username logged in">>./cloud_log.txt
	echo "LOGIN: INFO User $username logged in"
else
	echo "$(date +"%y/%m/%d %T") LOGIN: ERROR Failed login attempt on user $username">>./cloud_log.txt
	echo "LOGIN: ERROR Failed login attempt on user $username"
fi
```
Melakukan pengecekan apakah kombinasi input username dan input password tersimpan di file `users.txt` direktori `cloud_storage`. jika tersimpan, mengeluarkan log success login, tetapi jika tidak, mengeluarkan log error login. Log tersebut akan disimpan di `cloud_log.txt`
- `grep -F` mencari teks sebagai string liberal.
- `-q` mencari pola tanpa menampilkan hasilnya dan mengembalikan exit status.

<b>Output jika error</b>

![output error](https://drive.google.com/uc?id=1v5tSrkis3KCRHDmx3easHQSlGPh0K9e3)

### Soal B
Pengunduhan Gambar Otomatis Sistem akan secara berkala memeriksa file log secara berkala untuk mendeteksi apakah ada satu pengguna yang sedang login memanfaatkan script `automation.sh`. Jika terdeteksi, sistem akan menjalankan proses pengunduhan gambar secara otomatis pada script `download.sh`.

<b>Code download.sh</b>
```
#!/bin/bash

API_KEY="3da519b2ab6c61bd90d71237e3354e3859ecf372a8f8f6c4eb3e6198c971a5da"
QUERY="nature"
URL="https://serpapi.com/search?engine=google_images&q=${QUERY}&api_key=${API_KEY}"

mapfile -t IMAGE_URLS < <(curl -s "$URL" | sed -n 's/.*"original":[[:space:]]*"\([^"]*\)".*/\1/p' | head -n 20)

SELECTED_URL=$(printf "%s\n" "${IMAGE_URLS[@]}" | shuf -n 1)
if cat /home/abidalfrz/Documents/sisop1/cloud_log.txt | grep -v "REGISTER" | tail -n -1 | grep -q 'logged in'
then
        user=$(cat /home/abidalfrz/Documents/sisop1/cloud_log.txt | grep -v -E "REGISTER|LOGOUT" | tail -n 1 | grep -oE 'User [a-zA-Z0-9]+' | cut -d' ' -f2)
	mkdir -p "cloud_storage/downloads/$user"

	save_path="/home/abidalfrz/Documents/sisop1/cloud_storage/downloads/$user"
	dateformat=$(date +"%H-%M_%d-%m-%y")

	FILENAME="${save_path}/${dateformat}.jpeg"

	echo "Downloading image from $SELECTED_URL"
	echo "to $FILENAME"
	curl -s "$SELECTED_URL" -o "$FILENAME"

fi
```
<b>Output</b>

Sebelum menjalankan `download.sh`

![before downloads](https://drive.google.com/uc?id=1r0gq1M5fwyz9mJWEUhsPIynVr5BAElbN)

Setelah menjalankan `download.sh`

![after downloads](https://drive.google.com/uc?id=16aACD5UmKrCjSunENp3QPd3AG2dAjUAJ)

<b>Penjelasan</b>
```
API_KEY="3da519b2ab6c61bd90d71237e3354e3859ecf372a8f8f6c4eb3e6198c971a5da"
QUERY="nature"
URL="https://serpapi.com/search?engine=google_images&q=${QUERY}&api_key=${API_KEY}"
```
- `API_KEY` variabel yang berisi SerpAPI authenticationn key.
- `QUERY` variabel dari jenis gambar yang akan diunduh.
- `URL` variabel yang berisi request URL dari SerpAPI dengan engine google images yang digunakan untuk mengunduh gambar.
```
mapfile -t IMAGE_URLS < <(curl -s "$URL" | sed -n 's/.*"original":[[:space:]]*"\([^"]*\)".*/\1/p' | head -n 20)
```
Menggunakan `mapfile` untuk membuat array dengan nama `IMAGE_URLS` yang elemennya diambil dari ekstrak data JSON hasil dari Google Images API sebanyak 20 URL.
- `curl -s "$URL"` curl mengambil data dari `URL`.Kemudian, `URL` berisi API akan mengembalikan hasil pencarian gambar berbentuk JSON. `-s` menonaktifkan output progress.
- `sed -n 's/.*"original":[[:space:]]*"\([^"]*\)".*/\1/p'`
	- `s/.../.../p` substitusi string menggunakan regex, lalu mencetak hasil yang cocok (p).
 	- `.*"original":[[:space:]]*"` mencari bagian JSON yang memiliki "original": di dalamnya (tempat url gambar disimpan).
  	- `\([^"]*\)` menangkap URL gambar yang berada di dalam tanda kutip ganda.
  	- `.*` mengabaikan sisa teks setelah url.
  	- `\1` mengembalikan hanya url gambar.
- `head -n 20` mengambil 20 URL pertama dari daftar url gambar yang diperoleh dari hasil sebelumnya.
```
SELECTED_URL=$(printf "%s\n" "${IMAGE_URLS[@]}" | shuf -n 1)
```
Mengambil 1 dari 20 url gambar secara acak dan menyimpannya di variabel `SELECTED_URL`.
- `printf "%s\n" "${IMAGE_URLS[@]}"` print setiap url gambar per baris.
- `shuf -n 1` mengambil satu url secara acak dari 20 baris url.
```
if cat /home/abidalfrz/Documents/sisop1/cloud_log.txt | grep -v "REGISTER" | tail -n -1 | grep -q 'logged in'
```
Melakukan pengecekan pada satu baris terakhir file `cloud_log.txt` apakah ada kata `logged in` yang berarti ada pengguna yang sedang login.
- `cat cloud_log.txt` membaca file `cloud_log.txt`.
- `grep -v "REGISTER"` mengecualikan baris yang mengandung kata "REGISTER" di file.
- `tail -n 1` mengambil satu baris terakhir dari hasil sebelumnya.
- `grep -q 'logged in'` memeriksa apakah baris terakhir mengandung 'logged in'. `-q` mengembalikan exit status.
```
user=$(cat cloud_log.txt | grep -v -E "REGISTER|LOGOUT" | tail -n 1 | grep -oE 'User [a-zA-Z0-9]+' | cut -d' ' -f2)
```
Jika ada pengguna yang sedang login, membuat variabel user dari hasil berbagai commands untuk menemukan pengguna yang sedang login.
- `cat cloud_log.txt` membaca file `cloud_log.txt`.
- `grep -v "REGISTER|LOGOUT"` mengecualikan baris yang mengandung kata "REGISTER" atau "LOGOUT" di file. `-E` untuk melakukkan regex/pencocokan.
- `tail -n 1` mengambil satu baris terakhir dari hasil sebelumnya.
- `grep -oE 'User [a-zA-Z0-9]+'` mengekstrak kata dalam teks dengan pola 'User [a-zA-Z0-9]+'. `-o` hanya menampilkan bagian teks yang cocok dengan pola.
- `cut -d' ' -f2` mengambil kata kedua dari hasil sebelumnya. `d' '` menentukan bahwa delimiter adalah spasi, `-f2` untuk mengambil kata ke-2.
```
mkdir -p "cloud_storage/downloads/$user"
```
Membuat direktori `downloads` di dalam `cloud_storage` lalu membuat direktori dengan nama `user` di dalam `downloads`.
```
save_path="/home/abidalfrz/Documents/sisop1/cloud_storage/downloads/$user"
dateformat=$(date +"%H-%M_%d-%m-%y")

FILENAME="${save_path}/${dateformat}.jpeg"
```
Membuat path yang akan digunakan sebagai penyimpanan hasil download gambar sesuai dengan format soal dan menyimpannya di variabel `FILENAME`.
```
curl -s "$SELECTED_URL" -o "$FILENAME"
```
Mengunduh gambar dari `SELECTED_URL`, lalu menyimpannya di `FILENAME`.
- `curl -s` menyembunyikan output progress.
- `curl -o` menyimpan hasil unduhan ke dalam file tertentu.

### Soal C
Pengarsipan Gambar: Untuk menjaga kerapihan penyimpanan, setiap gambar yang telah diunduh akan dikumpulkan dan diarsipkan ke dalam file ZIP secara otomatis setiap 2 jam menggunakan script `archive.sh`. Setiap pengguna memiliki folder arsip sendiri.

<b>Code archive.sh</b>
```
#!/bin/bash

if cat /home/abidalfrz/Documents/sisop1/cloud_log.txt | grep -v "REGISTER" | tail -n -1 | grep -q 'logged in'
then
	user=$(cat /home/abidalfrz/Documents/sisop1/cloud_log.txt | grep -v -E "REGISTER|LOGOUT" | tail -n 1 | grep -oE 'User [a-zA-Z0-9]+' | cut -d' ' -f2)
fi
mkdir -p "/home/abidalfrz/Documents/sisop1/cloud_storage/archives/$user"

filename="$(echo "archive")_$(date +"%d-%m-%y")"

path="/home/abidalfrz/Documents/sisop1/cloud_storage/downloads/$user"

cd "$path" && zip -r "$filename.zip" *

cd ../..

mv "/home/abidalfrz/Documents/sisop1/cloud_storage/downloads/$user/$filename.zip" "/home/abidalfrz/Documents/sisop1/cloud_storage/archives/$user"

rm -f "/home/abidalfrz/Documents/sisop1/cloud_storage/downloads/$user"/*

echo "archived completed"
```
<b>Output</b>

Sebelum menjalankan `archive.sh`

![before archive](https://drive.google.com/uc?id=1WVIWJmZwZELjadgqUciCuudIAtKavrME)

Setelah menjalankan `archive.sh`

![after archive](https://drive.google.com/uc?id=1Yorgztuaa_HiQ_IjoCj-1eQeSL1kx-NA)

<b>Penjelasan</b>
```
if cat /home/abidalfrz/Documents/sisop1/cloud_log.txt | grep -v "REGISTER" | tail -n -1 | grep -q 'logged in'
```
Melakukan pengecekan pada satu baris terakhir file `cloud_log.txt` apakah ada kata `logged in` yang berarti ada pengguna yang sedang login.
- `cat cloud_log.txt` membaca file `cloud_log.txt`.
- `grep -v "REGISTER"` mengecualikan baris yang mengandung kata "REGISTER" di file.
- `tail -n 1` mengambil satu baris terakhir dari hasil sebelumnya.
- `grep -q 'logged in'` memeriksa apakah baris terakhir mengandung 'logged in'. `-q` mengembalikan exit status.
```
user=$(cat cloud_log.txt | grep -v -E "REGISTER|LOGOUT" | tail -n 1 | grep -oE 'User [a-zA-Z0-9]+' | cut -d' ' -f2)
```
Jika ada pengguna yang sedang login, membuat variabel user dari hasil berbagai commands untuk menemukan pengguna yang sedang login.
- `cat cloud_log.txt` membaca file `cloud_log.txt`.
- `grep -v "REGISTER|LOGOUT"` mengecualikan baris yang mengandung kata "REGISTER" atau "LOGOUT" di file. `-E` untuk melakukkan regex/pencocokan.
- `tail -n 1` mengambil satu baris terakhir dari hasil sebelumnya.
- `grep -oE 'User [a-zA-Z0-9]+'` mengekstrak kata dalam teks dengan pola 'User [a-zA-Z0-9]+'. `-o` hanya menampilkan bagian teks yang cocok dengan pola.
- `cut -d' ' -f2` mengambil kata kedua dari hasil sebelumnya. `d' '` menentukan bahwa delimiter adalah spasi, `-f2` untuk mengambil kata ke-2.
```
mkdir -p "/home/abidalfrz/Documents/sisop1/cloud_storage/archives/$user"
```
Membuat direktori `archives` di dalam `cloud_storage` lalu membuat direktori dengan nama `user` di dalam `archives`.
```
filename="$(echo "archive")_$(date +"%d-%m-%y")"

path="/home/abidalfrz/Documents/sisop1/cloud_storage/downloads/$user"
```
Membuat variabel `filename` yang akan digunakan sebagai nama zip dan variabel `path` untuk menanadai direktori yang digunakan `user` untuk menyimpan hasil pengunduhan gambar.
```
cd "$path" && zip -r "$filename.zip" *
cd ../..
```
- `cd "$path"` berpindah ke direktori `path`
- `&&` memastikan bahwa perintah setelahnya hanya akan dieksekusi jika `cd "$path"` berhasil.
- `zip -r "$filename.zip" *` melakukan kompresi untuk seluruh file yang ada di direktori saat ini. `-r` digunakan agar semua file dan subdirektori dalam direktori saat ini dimasukkan ke dalam arsip. `*` menandakan untuk semua file di direktori.
- `cd ../..` kembali ke dua tingkat direktori di atas direktori saat ini.
```
mv "/home/abidalfrz/Documents/sisop1/cloud_storage/downloads/$user/$filename.zip" "/home/abidalfrz/Documents/sisop1/cloud_storage/archives/$user"
```
Memindahkan `filename.zip` dari `cloud_storage/downloads/$user/$filename.zip` ke `cloud_storage/archives/user`.
```
rm -f "/home/abidalfrz/Documents/sisop1/cloud_storage/downloads/$user"/*
```
Menghapus semua file yang ada di direktori `cloud_storage/downloads/$user"`
- `rm -f` Memaksa penghapusan file tanpa meminta konfirmasi.
- `*` menandakan untuk semua file di direktori.

### Automation
- Sistem mengecek file log (cloud_log.txt) setiap 2 menit untuk memastikan ada satu pengguna yang login.
- Jika kondisi terpenuhi, proses download gambar dimulai.
- Jika pengguna pengguna logout, proses download dihentikan.
- Download gambar dari Google Images setiap 10 menit bertema alam.
- Frekuensi Pengarsipan: Sistem mengarsipkan gambar setiap 2 jam.
  
<b>Code automation.sh</b>
```
#!/bin/bash

if cat /home/abidalfrz/Documents/sisop1/cloud_log.txt | grep -v "REGISTER" | tail -n 1 | grep -q 'logged in'
then
        if ! crontab -l | grep -q -E "download.sh|archive.sh"
        then
                echo "Download Started.."
                (crontab -l; echo "*/10 * * * * /home/abidalfrz/Documents/sisop1/download.sh") | crontab -
                (crontab -l; echo "* */2 * * * /home/abidalfrz/Documents/sisop1/archive.sh") | crontab -
        fi
elif cat /home/abidalfrz/Documents/sisop1/cloud_log.txt | grep -v "REGISTER" | tail -n 1 | grep -q 'logged out'
then
        crontab -l | grep -v "/home/abidalfrz/Documents/sisop1/download.sh" | crontab -
        crontab -l | grep -v "/home/abidalfrz/Documents/sisop1/archive.sh" | crontab -
        echo "Download cancelled"
fi
```

<b>Output</b>

Sebelum menjalankan `automation.sh`

![before auto](https://drive.google.com/uc?id=1DsAomZwJLC8A0E2zrccMonb0-t9rKRxs)

Setelah 2 menit dan `automation.sh` dijalankan

![after auto](https://drive.google.com/uc?id=1EqGYF_tvwkA0ZcUhaRqIT2W2wYPEArEO)

<b>Penjelasan</b>
```
if cat /home/abidalfrz/Documents/sisop1/cloud_log.txt | grep -v "REGISTER" | tail -n 1 | grep -q 'logged in'
```
Melakukan pengecekan pada satu baris terakhir file `cloud_log.txt` apakah ada kata `logged in` yang berarti ada pengguna yang sedang login.
- `cat cloud_log.txt` membaca file `cloud_log.txt`.
- `grep -v "REGISTER"` mengecualikan baris yang mengandung kata "REGISTER" di file.
- `tail -n 1` mengambil satu baris terakhir dari hasil sebelumnya.
- `grep -q 'logged in'` memeriksa apakah baris terakhir mengandung 'logged in'. `-q` mengembalikan exit status.
```
if ! crontab -l | grep -q -E "download.sh|archive.sh"
then
	echo "Download Started.."
	(crontab -l; echo "*/10 * * * * /home/abidalfrz/Documents/sisop1/download.sh") | crontab -
	(crontab -l; echo "* */2 * * * /home/abidalfrz/Documents/sisop1/archive.sh") | crontab -
fi
```
Melakukan pengecekan apakah `download.sh` atau `archive.sh` ada di list crontab. Jika tidak, menambahkan entri baru untuk menjalankan `download.sh` sesuai path `/home/abidalfrz/Documents/sisop1/download.sh` setiap 10 menit dan entri baru untuk menjalankan `archive.sh` seusai path `/home/abidalfrz/Documents/sisop1/archive.sh` setiap 2 jam.
- `crontab -l` menampilkan cron jobs yang sudah terdaftar.
- `grep -q -E` mencari pola dengan regex`-E` tanpa menampilkan hasilnya dan mengembalikan exit status.
- `crontab -` memasukkan hasil perubahan kembali ke crontab.
```
elif cat /home/abidalfrz/Documents/sisop1/cloud_log.txt | grep -v "REGISTER" | tail -n 1 | grep -q 'logged out'
```
Melakukan pengecekan pada satu baris terakhir file `cloud_log.txt` apakah ada kata `logged out` yang berarti tidak ada pengguna yang sedang login karena pengguna terakhir telah log out.
- `cat cloud_log.txt` membaca file `cloud_log.txt`.
- `grep -v "REGISTER"` mengecualikan baris yang mengandung kata "REGISTER" di file.
- `tail -n 1` mengambil satu baris terakhir dari hasil sebelumnya.
- `grep -q 'logged out'` memeriksa apakah baris terakhir mengandung 'logged in'. `-q` mengembalikan exit status.
```
crontab -l | grep -v "/home/abidalfrz/Documents/sisop1/download.sh" | crontab -
crontab -l | grep -v "/home/abidalfrz/Documents/sisop1/archive.sh" | crontab -
```
Jika tidak ada pengguna yang sedang login, menjalankan script tersebut.
- `crontab -l` menampilkan cron jobs yang sudah terdaftar.
- `grep -v "/home/abidalfrz/Documents/sisop1/download.sh"` mengecualikan baris yang mengandung `/home/abidalfrz/Documents/sisop1/download.sh`. Hasilnya adalah daftar cron jobs tanpa `/home/abidalfrz/Documents/sisop1/download.sh`.
- `grep -v "/home/abidalfrz/Documents/sisop1/archive.sh"` mengecualikan baris yang mengandung `/home/abidalfrz/Documents/sisop1/archive.sh`. Hasilnya adalah daftar cron jobs tanpa `/home/abidalfrz/Documents/sisop1/archive.sh`.
- `crontab -` memasukkan hasil perubahan kembali ke crontab.

<b>Crontab</b>
```
*/2 * * * * /home/abidalfrz/Documents/sisop1/automation.sh

# Dijalankan ketika terdapat pengguna yang sedang login
*/10 * * * * /home/abidalfrz/Documents/sisop1/download.sh
* */2 * * * /home/abidalfrz/Documents/sisop1/archive.sh
```

<b>Penjelasan crontab</b>
- `*/2 * * * * /home/abidalfrz/Documents/sisop1/automation.sh` menjalankan `automation.sh` sesuai path `/home/abidalfrz/Documents/sisop1/automation.sh` setiap 2 menit untuk memastikan ada pengguna yang login.
- `*/10 * * * * /home/abidalfrz/Documents/sisop1/download.sh` menjalankan `download.sh` sesuai path `/home/abidalfrz/Documents/sisop1/download.sh` setiap 10 menit untuk melakukan pengunduhan gambar melalu API.
- `* */2 * * * /home/abidalfrz/Documents/sisop1/archive.sh` menjalankan `archive.sh` sesuai path `/home/abidalfrz/Documents/sisop1/archive.sh` setiap 2 jam untuk melakukan pengarsipan gambar-gambar yang telah diunduh di direktori `/home/abidalfrz/Documents/sisop1/cloud_storage/downloads/$user`.

<b>Kendala</b>
- Sebelum revisi soal b, menjalankan pengunduhan melalui copy paste link google image secara manual di txt hingga setelah praktikum baru menemukan cara untuk melakukan pengunduhan menggunakan API.
- Menjalankan crontab yang pada awalnya menggunakan shortcut path `~` tidak berjalan. Kemudian, diganati menjadi absolut path sehingga crontab dapat dijalankan.

## Task 4 - Proxy Terbaik di New Eridu
Belle dan Wise membuka Toko Video di Sixth Street. Mereka meminta bantuan membuat program monitoring untuk memantau sumber daya pada setiap server.

### File Script 1 (minute5_log.sh)
Script pencatatan metrics setiap 5 menit. Masukkan semua metrics ke dalam sebuah file log bernama `metrics_{YmdHms}.log`. {YmdHms} adalah waktu saat script Bash dijalankan. Contoh: jika dijalankan pada 2025-03-17 19:00:00, maka file log yang akan dibuat adalah `metrics_20250317190000.log`

Code
```
#!/bin/bash

log="$HOME/metrics/metrics_$(date +%Y%m%d%H%M%S).log"
echo "mem_total,mem_used,mem_free,mem_shared,mem_buff,mem_available,swap_total,swap_used,swap_free,path,path_size" > "$log"
mem=$(free -m | awk 'NR==2 {print $2","$3","$4","$5","$6","$7}')
swap=$(free -m | awk 'NR==3 {print $2","$3","$4}')
path_size=$(du -sh | awk '{print $1}')
echo "$mem,$swap,$(pwd),$path_size" >> "$log"
chmod 600 "$log"
```
Output (Berada di folder /{user}/metrics)

![Screenshot from 2025-03-26 07-57-46](https://github.com/user-attachments/assets/eea76a44-a0c1-489b-834e-9d4c0ceb10a8)

Penjelasan
- `log` adalah absolute path untuk file metrics_{YmdHms}.log
- `$(date +%Y%m%d%H%M%S)` adalah command untuk menampilkan Tahun, Bulan, Tanggal, Jam, Menit, Detik secara real time saat code dijalankan.
- `free -m` adalah command untuk menampilkan penggunaan RAM suatu directory.
- `awk` adalah command yang bisa digunakan untuk mengambil catatan/record tertentu dalam sebuah file dan melakukan sebuah/beberapa operasi terhadap catatan/record tersebut.
- `echo "$mem,$swap,$(pwd),$path_size" >> "$log"` menambahkan dan menampilkan data di baris baru ke dalam file log.
- `chmod 600 "$log"` mengubah permission file menjadi privat.

### File Script 2 (agg_5min_to_hour.sh)
Script untuk membuat file aggregasi log setiap 1 jam. Di dalam file aggregasi, terdapat nilai minimum, maximum, dan average dari tiap metrics yang sebelumnya tergenerate setiap 5 menit. File aggregasi ini harus tergenerate setiap 1 jam sekali. File aggregasi ini memiliki format penamaan `metrics_agg_{YmdH}.log`.

Code
```
#!/bin/bash

count=0
declare -a sum max min avg
max_path="" min_path=""
max_size=0 min_size=99999 total_size=0

for log in $HOME/metrics/metrics_*.log; do
    [[ "$log" =~ metrics_agg_[0-9]{10}\.log$ || -f "$HOME/metrics/metrics_agg_$(basename "$log" | cut -d'_' -f2 | cut -c1-10).log" ]] && continue

    name=$(basename "$log" | cut -d'_' -f2 | cut -c1-10)
    agg_log="$HOME/metrics/metrics_agg_$name.log"

    while IFS=',' read -r -a fields; do
        ((count == 0)) && { num_fields=${#fields[@]}; for ((i=0; i<num_fields-2; i++)); do sum[i]=0; max[i]=0; min[i]=99999; done; max_size=0; min_size=99999; total_size=0; }

        for ((i=0; i<num_fields-2; i++)); do
            val=${fields[i]}
            ((sum[i] += val))
            [[ $val -gt ${max[i]} ]] && max[i]=$val
            [[ $val -lt ${min[i]} ]] && min[i]=$val
        done

        path=${fields[num_fields-2]}
        size_val=${fields[num_fields-1]%M}
        ((total_size += size_val))
        
        [[ $size_val -gt $max_size ]] && { max_size=$size_val; max_path=$path; }
        [[ $size_val -lt $min_size ]] && { min_size=$size_val; min_path=$path; }

        ((count++))

        if [[ $count -eq 12 ]]; then
            for ((i=0; i<num_fields-2; i++)); do avg[i]=$((sum[i] / count)); done

            oldIFS="$IFS"
            IFS=','
            echo "type,mem_total,mem_used,mem_free,mem_shared,mem_buff,mem_available,swap_total,swap_used,swap_free,path,path_size" >> "$agg_log"
            echo "minimum:${min[*]},$min_path,${min_size}M" >> "$agg_log"
            echo "maximum:${max[*]},$max_path,${max_size}M" >> "$agg_log"
            echo "average:${avg[*]},$max_path,$((total_size / count))M" >> "$agg_log"
            IFS="$oldIFS"

            count=0; for ((i=0; i<num_fields-2; i++)); do sum[i]=0; max[i]=0; min[i]=99999; done
            max_size=0; min_size=99999; total_size=0
        fi
    done < <(awk -F',' 'FNR==2' "$log")
done
```

Output

![Screenshot from 2025-03-28 13-18-47](https://github.com/user-attachments/assets/4748645c-bc57-457a-8af1-e1b0dd28aa02)


Penjelasan
- `for log in $HOME/metrics/metrics_*.log;` melakukan looping untuk mencari path file log dengan nama metrics_* (* berarti semua karakter) di folder ~/metrics lalu disimpan di variabel log.
- `[[ "$log" =~ metrics_agg_[0-9]{10}\.log$ || -f "$HOME/metrics/metrics_agg_$(basename "$log" | cut -d'_' -f2 | cut -c1-10).log" ]] && continue` melompati file yang berformat nama metrics_agg_{YmdH}.log (karena setiap jam melakukan proses aggregasi), dan melompati file log aggregasi yang sudah ada.
- `name=$(basename "$log" | cut -d'_' -f2 | cut -c1-10)
  agg_log="$HOME/metrics/metrics_agg_$name.log"` mengambil tanggal dari nama file lalu menyimpannya di $name dan digabungkan lagi dengan format dalam $agg_log.
- `while IFS=',' read -r -a fields; do` membaca data dengan separator ','.
- `-gt` operator untuk mengecek apakah {data1} lebih besar dari {data2}.
- `-lt` operator untuk mengecek apakah {data1} lebih kecil dari {data2}.
- `if [[ $count -eq 12 ]];` mengecek apakah nilai count sama dengan 12, karena dalam 1 jam ada 12 file log.
- `echo "minimum:${min[*]},$min_path,${min_size}M" >> "$agg_log"
   echo "maximum:${max[*]},$max_path,${max_size}M" >> "$agg_log"
   echo "average:${avg[*]},$max_path,$((total_size / count))M" >> "$agg_log"` menampilkan minimum, maximum, dan average dalam agg_log.
- `count=0; for ((i=0; i<num_fields-2; i++)); do sum[i]=0; max[i]=0; min[i]=99999; done
   max_size=0; min_size=99999; total_size=0` mereset nilai variabel untuk looping jam selanjutnya.
- `(awk -F',' 'FNR==2' "$log")` hanya membaca baris ke 2 setiap file $log.
- `chmod 600 "$agg_log"` mengubah permission file menjadi privat.

### File Script 3 (uptime_monitor.sh)
Script untuk memantau uptime dan load average server setiap jam dan menyimpannya dalam file log bernama uptime_{YmdH}.log. Uptime harus diambil dari output perintah uptime, sedangkan load average diambil dari cat /proc/loadavg.

Code
```
#!/bin/bash

log="$HOME/metrics/uptime_$(date +%Y%m%d%H).log"
echo "uptime,load_avg_1min,load_avg_5min,load_avg_15min" > "$log"
up_time=$(uptime | awk '{print $1, $2, $3}')
loadavg=$(cat /proc/loadavg | awk '{print $1","$2","$3}')
echo "$up_time,$loadavg" >> "$log"
chmod 600 "$log"
```

Output (Berada di folder /{user}/metrics)

![Screenshot from 2025-03-26 08-32-25](https://github.com/user-attachments/assets/1e20f20e-db62-46ea-ab99-1773dd6d6cef)

Penjelasan
- `log` adalah absolute path untuk file uptime_{YmdHms}.log
- `$(date +%Y%m%d%H)` adalah command untuk menampilkan Tahun, Bulan, Tanggal, Jam secara real time saat code dijalankan.
- `uptime` adalah command untuk mengecek seberapa lama sistem menyala tanpa restart.
- `cat /proc/loadavg` adalah command untuk mengecek beban kerja CPU.
- `awk` adalah command yang bisa digunakan untuk mengambil catatan/record tertentu dalam sebuah file dan melakukan sebuah/beberapa operasi terhadap catatan/record tersebut.
- `echo "$up_time,$loadavg" >> "$log"` menambahkan dan menampilkan data di baris baru ke dalam file log.
- `chmod 600 "$log"` mengubah permission file menjadi privat.

### File Script 4 (cleanup_log.sh)
Script untuk menghapus file log agregasi yang lebih lama dari 12 jam pertama setiap hari. Script ini harus dijalankan setiap hari pada pukul 00:00.

Code
```
#!/bin/bash

for agg_log in $HOME/metrics/metrics_agg_*.log; do
        name=$(basename "$agg_log")
        if [[ $name =~ ^metrics_agg_[0-9]{8}(0[0-9]|1[0-2])\.log$ ]]; then
        rm "$agg_log"
        fi
done
```
Output

Sebelum

![Screenshot from 2025-03-26 08-34-21](https://github.com/user-attachments/assets/ee5cc10a-bbec-4069-a853-cca18a4853e6)

Sesudah

![Screenshot from 2025-03-26 08-34-43](https://github.com/user-attachments/assets/e686cb47-0e61-4373-80d6-1713e40dc38e)

Penjelasan
- `for agg_log in $HOME/metrics/metrics_agg_*.log; do ... done` melakukan looping untuk mencari path file log dengan nama metrics_agg_* (* berarti semua karakter) di folder ~/metrics lalu disimpan di variabel agg_log.
- `basename` adalah perintah untuk mengambil nama file saja, tanpa path.
- `if [[ $name =~ ^metrics_agg_[0-9]{8}(0[0-9]|1[0-2])\.log$ ]]; then ... fi` kondisi jika nama file yang didapat sama dengan format metrics_agg_{YmdH}.log, dengan catatan jam yang bernilai true adalah dari 00-12.
- `rm` adalah command untuk menghapus file, folder.

### Crontab
```
*/5 * * * * /bin/bash /home/ubuntu/minutes5_log.sh
* */1 * * * /bin/bash /home/ubuntu/agg_5min_to_hour.sh
* */1 * * * /bin/bash /home/ubuntu/uptime_monitor.sh
0 0 * * * /bin/bash /home/ubuntu/cleanup_log.sh
```

Penjelasan
- `*/5 * * * * /bin/bash /home/ubuntu/minutes5_log.sh` akan menjalankan minutes5_log.sh per 5 menit setelah dijalankan.
- `* */1 * * * /bin/bash /home/ubuntu/agg_5min_to_hour.sh` akan menjalankan agg_5min_to_hour.sh dan uptime_monitor.sh per 1 jam setelah dijalankan.
- `0 0 * * * /bin/bash /home/ubuntu/cleanup_log.sh` akan menjalankan cleanup_log.sh setiap jam 00.00

Kendala pengerjaan : Script file 2 (agg_5min_to_hour.sh) sempat error hingga batas pengumpulan praktikum.
