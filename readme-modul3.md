[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Eu-CByJh)
|    NRP     |      Name      |
| :--------: | :------------: |
| 5025241133 | Muhammad Abid Baihaqi Al Faridzi |
| 5025241150 | Nabila Shafa Rahayu |
| 5025241153 | Kamal Zaki Adinata |

# Praktikum Modul 3 _(Module 3 Lab Work)_

### Laporan Resmi Praktikum Modul 3 _(Module 3 Lab Work Report)_

Di suatu pagi hari yang cerah, Budiman salah satu mahasiswa Informatika ditugaskan oleh dosennya untuk membuat suatu sistem operasi sederhana. Akan tetapi karena Budiman memiliki keterbatasan, Ia meminta tolong kepadamu untuk membantunya dalam mengerjakan tugasnya. Bantulah Budiman untuk membuat sistem operasi sederhana!

_One sunny morning, Budiman, an Informatics student, was assigned by his lecturer to create a simple operating system. However, due to Budiman's limitations, he asks for your help to assist him in completing his assignment. Help Budiman create a simple operating system!_

### Soal 1

> Sebelum membuat sistem operasi, Budiman diberitahu dosennya bahwa Ia harus melakukan beberapa tahap terlebih dahulu. Tahap-tahapan yang dimaksud adalah untuk **mempersiapkan seluruh prasyarat** dan **melakukan instalasi-instalasi** sebelum membuat sistem operasi. Lakukan seluruh tahapan prasyarat hingga [perintah ini](https://github.com/arsitektur-jaringan-komputer/Modul-Sisop/blob/master/Modul3/README-ID.md#:~:text=sudo%20apt%20install%20%2Dy%20busybox%2Dstatic) pada modul!

> _Before creating the OS, Budiman was informed by his lecturer that he must complete several steps first. The steps include **preparing all prerequisites** and **installing** before creating the OS. Complete all the prerequisite steps up to [this command](https://github.com/arsitektur-jaringan-komputer/Modul-Sisop/blob/master/Modul3/README-ID.md#:~:text=sudo%20apt%20install%20%2Dy%20busybox%2Dstatic) in the module!_

**Answer:**

- **Code:**
  
  ```
  sudo apt -y update
  sudo apt -y install qemu-system build-essential bison flex libelf-dev libssl-dev bc grub-common grub-pc libncurses-dev libssl-dev mtools grub-pc-bin  xorriso tmux
  ```
  ```
  mkdir -p osboot
  cd osboot
  ```
  ```
  wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.1.1.tar.xz
  tar -xvf linux-6.1.1.tar.xz
  cd linux-6.1.1
  ```
  ```
  make tinyconfig
  ```
  ```
  make menuconfig
  64-Bit Kernel
  General Setup > Configure standard kernel features > Enable support for printk
  General Setup > Configure standard kernel features > Enable futex support
  General Setup > Initial RAM filesystem and RAM disk (initramfs/initrd) support
  General Setup > Control Group Support
  Enable the block layer > Legacy autoloading support
  Enable the block layer > Partition type > Advanced Partition Selection
  Device Drivers > Character devices > Enable TTY
  Device Drivers > Character devices > Virtio console
  Device Drivers > Character devices > /dev/mem virtual device support
  Device Drivers > Network device support > Virtio Network Driver
  Device Drivers > Serial Ata / Paralel ATA
  Device Drivers > Block Devices > Virtio block driver
  Device Drivers > Block Devices > loopback device support
  Device Drivers > Block Devices > RAM block device support
  Device Drivers > Virtio drivers
  Device Drivers > Virtualization Drivers
  Device Drivers > Generic  Driver Options > Maintain a devtmpfs at filesystems
  Device Drivers > Generic Driver Options > Automount devtmpfs at /dev
  Executable file formats > Kernel Support for ELF binaries
  Executable file formats > Kernel Support scripts starting with #!
  File Systems > FUSE support
  File Systems > The extended 3 filesystem
  File Systems > The extended 4 filesystem
  File Systems > Second extended fs support
  File Systems > Virtio Filesystem
  File Systems > Kernel automounter support
  File Systems > Pseudo File Systems > /proc file system support
  File Systems > Pseudo File Systems > sysctl support
  File Systems > Pseudo File Systems > sysfs file system support
  Networking Support > Networking options > Unix domain sockets
  Networking Support > Networking options > TCP/IP Networking
  ```
  ```
  make -j$(nproc)
  ```
  ```
  cp arch/x86/boot/bzImage ..
  ```
  ```
  sudo apt install -y busybox-static
  ```
  ```
  whereis busybox
  ```

- **Explanation:**

  ```
  sudo apt -y update
  sudo apt -y install qemu-system build-essential bison flex libelf-dev libssl-dev bc grub-common grub-pc libncurses-dev libssl-dev mtools grub-pc-bin  xorriso tmux
  ```
  Memastikan sistem telah diperbarui.
  Menginstal tools qemu, build-essential, bison, flex, libelf-dev, libssl-dev, bc, grub-common, grub-pc, grub-pc-bin, libncurses-dev, mtools, xorriso, tmux.
  ```
  mkdir -p osboot
  cd osboot
  ```
  Membuat direktori osboot, lalu berpindah ke dalam direktori osboot.
  ```
  wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.1.1.tar.xz
  tar -xvf linux-6.1.1.tar.xz
  cd linux-6.1.1
  ```
  Menginstall kode sumber kernel Linux versi 6.1.1 lalu diekstrak ke dalam direktori `linux-6.1.1`.
  ```
  make tinyconfig
  ```
  Membuat konfigurasi minimal.
  ```
  make menuconfig
  64-Bit Kernel
  General Setup > Configure standard kernel features > Enable support for printk
  General Setup > Configure standard kernel features > Enable futex support
  General Setup > Initial RAM filesystem and RAM disk (initramfs/initrd) support
  General Setup > Control Group Support
  Enable the block layer > Legacy autoloading support
  Enable the block layer > Partition type > Advanced Partition Selection
  Device Drivers > Character devices > Enable TTY
  Device Drivers > Character devices > Virtio console
  Device Drivers > Character devices > /dev/mem virtual device support
  Device Drivers > Network device support > Virtio Network Driver
  Device Drivers > Serial Ata / Paralel ATA
  Device Drivers > Block Devices > Virtio block driver
  Device Drivers > Block Devices > loopback device support
  Device Drivers > Block Devices > RAM block device support
  Device Drivers > Virtio drivers
  Device Drivers > Virtualization Drivers
  Device Drivers > Generic  Driver Options > Maintain a devtmpfs at filesystems
  Device Drivers > Generic Driver Options > Automount devtmpfs at /dev
  Executable file formats > Kernel Support for ELF binaries
  Executable file formats > Kernel Support scripts starting with #!
  File Systems > FUSE support
  File Systems > The extended 3 filesystem
  File Systems > The extended 4 filesystem
  File Systems > Second extended fs support
  File Systems > Virtio Filesystem
  File Systems > Kernel automounter support
  File Systems > Pseudo File Systems > /proc file system support
  File Systems > Pseudo File Systems > sysctl support
  File Systems > Pseudo File Systems > sysfs file system support
  Networking Support > Networking options > Unix domain sockets
  Networking Support > Networking options > TCP/IP Networking
  ```
  Menyesuaikan konfigurasi lebih lanjut untuk mengaktifkan fitur-fitur, seperti dukungan untuk virtualisasi, file systems, driver perangkat, serta jaringan.
  Simpan hasil konfigurasi pada `.config`.
  ```
  make -j$(nproc)
  ```
  Mengkompilasi kernel menggunakan seluruh inti CPU yang tersedia pada sistem.
  Menghasilkan file `bzImage` di dalam direktori `arch/x86/boot/`
  ```
  cp arch/x86/boot/bzImage ..
  ```
  Menyalin file `bzImage` ke dalam direktori `osboot`
  ```
  sudo apt install -y busybox-static
  ```
  Menginstall BusyBox.
  ```
  whereis busybox
  ```
  Mengecek apakah BusyBox sudah terinstall.

- **Screenshot:**

  `put your answer here`

### Soal 2

> Setelah seluruh prasyarat siap, Budiman siap untuk membuat sistem operasinya. Dosen meminta untuk sistem operasi Budiman harus memiliki directory **bin, dev, proc, sys, tmp, home** dan **sisop**. Lagi-lagi Budiman meminta bantuanmu. Bantulah Ia dalam membuat directory tersebut!

> _Once all prerequisites are ready, Budiman is ready to create his OS. The lecturer asks that the OS should contain the directories **bin, dev, proc, sys, tmp,** and **sisop**. Help Budiman create these directories!_

**Answer:**

- **Code:**

  ```
  sudo bash
  cd osboot
  ```
  ```
  mkdir -p myramdisk/{bin,dev,proc,sys,etc,tmp,home}
  ```
  ```
  cp -a /dev/null myramdisk/dev
  cp -a /dev/tty* myramdisk/dev
  cp -a /dev/zero myramdisk/dev
  cp -a /dev/console myramdisk/dev
  ```
  ```
  cp /usr/bin/busybox myramdisk/bin
  cd myramdisk/bin
  ./busybox --install .
  ```

- **Explanation:**

  `put your answer here`

- **Screenshot:**

  `put your answer here`

### Soal 3

> Budiman lupa, Ia harus membuat sistem operasi ini dengan sistem **Multi User** sesuai permintaan Dosennya. Ia meminta kembali kepadamu untuk membantunya membuat beberapa user beserta directory tiap usernya dibawah directory `home`. Buat pula password tiap user-usernya dan aplikasikan dalam sistem operasi tersebut!

> _Budiman forgot that he needs to create a **Multi User** system as requested by the lecturer. He asks your help again to create several users and their corresponding home directories under the `home` directory. Also set each user's password and apply them in the OS!_

**Format:** `user:pass`

```
root:Iniroot
Budiman:PassBudi
guest:guest
praktikan1:praktikan1
praktikan2:praktikan2
```

**Answer:**

- **Code:**
  
  ```
  sudo bash
  cd myramdisk
  ```
  ```
  mkdir root
  mkdir -p home/{Budiman,guest,praktikan1,praktikan2}
  ```
  ```
  cd etc
  openssl passwd -1 Iniroot
  openssl passwd -1 PassBudi
  openssl passwd -1 guest
  openssl passwd -1 praktikan1
  openssl passwd -1 praktikan2
  ```
  ```
  root:<<hasilgeneratorrootpassword>>:0:0:root:/root:/bin/sh
  user1:<<hasilgeneratorrootpassword>>:1001:100:user1:/home/user1:/bin/sh
  ```
  ```
  root:x:0:
  bin:x:1:root
  sys:x:2:root
  tty:x:5:root,user1
  disk:x:6:root
  wheel:x:10:root,user1
  users:x:100:user1
  ```
  ```
  cd myramdisk
  nano init
  chmod +x init
  ```
  ```
  #!/bin/sh
  /bin/mount -t proc none /proc
  /bin/mount -t sysfs none /sys

  while true
  do
      /bin/getty -L tty1 115200 vt100
      sleep 1
  done
  ```
  ```
  find . | cpio -oHnewc | gzip > ../myramdisk.gz
  ```

- **Explanation:**

  `put your answer here`

- **Screenshot:**

  `put your answer here`

### Soal 4

> Dosen meminta Budiman membuat sistem operasi ini memilki **superuser** layaknya sistem operasi pada umumnya. User root yang sudah kamu buat sebelumnya akan digunakan sebagai superuser dalam sistem operasi milik Budiman. Superuser yang dimaksud adalah user dengan otoritas penuh yang dapat mengakses seluruhnya. Akan tetapi user lain tidak boleh memiliki otoritas yang sama. Dengan begitu user-user selain root tidak boleh mengakses `./root`. Buatlah sehingga tiap user selain superuser tidak dapat mengakses `./root`!

> _The lecturer requests that the OS must have a **superuser** just like other operating systems. The root user created earlier will serve as the superuser in Budiman's OS. The superuser should have full authority to access everything. However, other users should not have the same authority. Therefore, users other than root should not be able to access `./root`. Implement this so that non-superuser accounts cannot access `./root`!_

**Answer:**

- **Code:**

  ```
  sudo bash
  cd myramdisk
  ```
  ```
  chown 0:0 root
  ```
  ```
  chmod 700 root
  ```
  ```
  find . | cpio -oHnewc | gzip > ../myramdisk.gz
  ```

- **Explanation:**

  `put your answer here`

- **Screenshot:**

  `put your answer here`

### Soal 5

> Setiap user rencananya akan digunakan oleh satu orang tertentu. **Privasi dan otoritas tiap user** merupakan hal penting. Oleh karena itu, Budiman ingin membuat setiap user hanya bisa mengakses dirinya sendiri dan tidak bisa mengakses user lain. Buatlah sehingga sistem operasi Budiman dalam melakukan hal tersebut!

> _Each user is intended for an individual. **Privacy and authority** for each user are important. Therefore, Budiman wants to ensure that each user can only access their own files and not those of others. Implement this in Budiman's OS!_

**Answer:**

- **Code:**

  ```
  sudo bash
  ```
  ```
  mkdir -p myramdisk/etc
  nano myramdisk/etc/group
  ```
  ```
  root:x:0:
  bin:x:1:root
  sys:x:2:root
  tty:x:5:root
  disk:x:6:root
  wheel:x:10:root
  Budiman:x:<<GID>>:
  guest:x:<<GID>>:
  praktikan1:x:<<GID>>:
  praktikan2:x:<<GID>>:
  users:x:100:Budiman,guest,praktikan1,praktikan2
  ```
  ```
  cd myramdisk/home
  ```
  ```
  chown <<UIDBudiman>>:<<GIDBudiman>> Budiman
  chown <<UIDguest>>:<<GIDguest>> guest
  chown <<UIDpraktikan1>>:<<GIDpraktikan1>> praktikan1
  chown <<UIDpraktikan2>>:<<GIDpraktikan2>> praktikan2
  ```
  ```
  chmod 700 Budiman
  chmod 700 guest
  chmod 700 praktikan1
  chmod 700 praktikan2
  ```
  ```
  cd .. && find . | cpio -oHnewc | gzip > ../myramdisk.gz
  ```

- **Explanation:**

  ```
  sudo bash
  ```
  Berpindah ke superuser (root) untuk melakukan perubahan.
  
  ```
  mkdir -p myramdisk/etc
  nano myramdisk/etc/group
  ```
  Membuat direktori `etc` di dalam direktori `myramdisk`.
  Setelah itu, jika file `group` belum dibuat, membuat file `group` di dalam `myramdisk/etc/` dan mengisi file tersebut dengan:
  ```
  root:x:0:
  bin:x:1:root
  sys:x:2:root
  tty:x:5:root
  disk:x:6:root
  wheel:x:10:root
  Budiman:x:<<GID>>:
  guest:x:<<GID>>:
  praktikan1:x:<<GID>>:
  praktikan2:x:<<GID>>:
  users:x:100:Budiman,guest,praktikan1,praktikan2
  ```
  Jika `group` sudah ada di dalam `myramdisk/etc/`, cukup menambahkan
  ```
  Budiman:x:<<GID>>:
  guest:x:<<GID>>:
  praktikan1:x:<<GID>>:
  praktikan2:x:<<GID>>:
  ```
  di dalam file tersebut.
  
  ```
  cd myramdisk/home
  ```
  Berpindah ke `/home` untuk melakukan perubahan akses untuk tiap direktori user.
  ```
  chown <<UIDBudiman>>:<<GIDBudiman>> Budiman
  chown <<UIDguest>>:<<GIDguest>> guest
  chown <<UIDpraktikan1>>:<<GIDpraktikan1>> praktikan1
  chown <<UIDpraktikan2>>:<<GIDpraktikan2>> praktikan2
  ```
  Mengubah ownership untuk tiap direktori user sesuai dengan UID dan GID yang dimiliki oleh user.
  
  <b>catatan: UID dapat dilihat di `passwd`</b>
  
  ```
  chmod 700 Budiman
  chmod 700 guest
  chmod 700 praktikan1
  chmod 700 praktikan2
  ```
  Mengubah izin akses untuk tiap direktori user agar hanya owner yang dapat mengakses.

  ```
  cd .. && find . | cpio -oHnewc | gzip > ../myramdisk.gz
  ```
  Berpindah ke direktori `myramdisk` menggunakan utilitas cpio lalu mengompresnya dengan gzip untuk membuat/memperbarui `myramdisk.gz`.
  
- **Screenshot:**
  
  Tampilan `passwd` untuk melihat UID tiap user
  ![UID](https://drive.google.com/uc?id=1KokEZxyb5dq6s87EAouNEFKfJuxniXSZ)

  Tampilan izin akses tiap direktori user sebelum diubah

  ![access](https://drive.google.com/uc?id=1lXd_pWEPL4KFKQPBOHlfJrHyNLGH-U-M)

  
  Tampilan izin akses tiap direktori user setelah diubah:

  - VM

    ![noaccess](https://drive.google.com/uc?id=1zedGQJ8uqGyWwqG_RIHGNhNkiKuUPzTI)

  - QEMU
 
    ![noaccess](https://drive.google.com/uc?id=1roCqLRl_I87B9MzIVjbS-H0ylNlhow3U)

  Implementasi login menggunakan user `Budiman`
  
  ![implement](https://drive.google.com/uc?id=1zCUHogCb20hDOA5_lBiFKIDES4t_6-Li)
    


  
### Soal 6

> Dosen Budiman menginginkan sistem operasi yang **stylish**. Budiman memiliki ide untuk membuat sistem operasinya menjadi stylish. Ia meminta kamu untuk menambahkan tampilan sebuah banner yang ditampilkan setelah suatu user login ke dalam sistem operasi Budiman. Banner yang diinginkan Budiman adalah tulisan `"Welcome to OS'25"` dalam bentuk **ASCII Art**. Buatkanlah banner tersebut supaya Budiman senang! (Hint: gunakan text to ASCII Art Generator)

> _Budiman wants a **stylish** operating system. Budiman has an idea to make his OS stylish. He asks you to add a banner that appears after a user logs in. The banner should say `"Welcome to OS'25"` in **ASCII Art**. Use a text to ASCII Art generator to make Budiman happy!_ (Hint: use a text to ASCII Art generator)

**Answer:**

- **Code:**

  ```
  sudo bash
  ```
  ```
  cd myramdisk
  nano etc/motd
  ```
  ```
  '##:::::'##:'########:'##::::::::'######:::'#######::'##::::'##:'########:
   ##:'##: ##: ##.....:: ##:::::::'##... ##:'##.... ##: ###::'###: ##.....::
   ##: ##: ##: ##::::::: ##::::::: ##:::..:: ##:::: ##: ####'####: ##:::::::
   ##: ##: ##: ######::: ##::::::: ##::::::: ##:::: ##: ## ### ##: ######:::
   ##: ##: ##: ##...:::: ##::::::: ##::::::: ##:::: ##: ##. #: ##: ##...::::
   ##: ##: ##: ##::::::: ##::::::: ##::: ##: ##:::: ##: ##:.:: ##: ##:::::::
  . ###. ###:: ########: ########:. ######::. #######:: ##:::: ##: ########:
  :...::...:::........::........:::......::::.......:::..:::::..::........::
  '########::'#######::::::'#######:::'######::'####::'#######::'########:  
  ... ##..::'##.... ##::::'##.... ##:'##... ##: ####:'##.... ##: ##.....::  
  ::: ##:::: ##:::: ##:::: ##:::: ##: ##:::..::. ##::..::::: ##: ##:::::::  
  ::: ##:::: ##:::: ##:::: ##:::: ##:. ######::'##::::'#######:: #######::  
  ::: ##:::: ##:::: ##:::: ##:::: ##::..... ##:..::::'##::::::::...... ##:  
  ::: ##:::: ##:::: ##:::: ##:::: ##:'##::: ##::::::: ##::::::::'##::: ##:  
  ::: ##::::. #######:::::. #######::. ######:::::::: #########:. ######::  
  :::..::::::.......:::::::.......::::......:::::::::.........:::......:::  
  ```
  ```
  find . | cpio -oHnewc | gzip > ../myramdisk.gz
  ```
  
- **Explanation:**

  ```
  sudo bash
  ```
  Berpindah ke superuser (root) untuk melakukan perubahan.
  
  ```
  cd myramdisk
  nano etc/motd
  ```
  Berpindah ke direktori `myramdisk` lalu membuat file `motd` di dalam direktori `etc`.
  <br>`motd`: "Message of The Day", file yang isinya akan ditampilkan secara otomatis di terminal setalah user berhasil login.</br>
  
  ```
  '##:::::'##:'########:'##::::::::'######:::'#######::'##::::'##:'########:
   ##:'##: ##: ##.....:: ##:::::::'##... ##:'##.... ##: ###::'###: ##.....::
   ##: ##: ##: ##::::::: ##::::::: ##:::..:: ##:::: ##: ####'####: ##:::::::
   ##: ##: ##: ######::: ##::::::: ##::::::: ##:::: ##: ## ### ##: ######:::
   ##: ##: ##: ##...:::: ##::::::: ##::::::: ##:::: ##: ##. #: ##: ##...::::
   ##: ##: ##: ##::::::: ##::::::: ##::: ##: ##:::: ##: ##:.:: ##: ##:::::::
  . ###. ###:: ########: ########:. ######::. #######:: ##:::: ##: ########:
  :...::...:::........::........:::......::::.......:::..:::::..::........::
  '########::'#######::::::'#######:::'######::'####::'#######::'########:  
  ... ##..::'##.... ##::::'##.... ##:'##... ##: ####:'##.... ##: ##.....::  
  ::: ##:::: ##:::: ##:::: ##:::: ##: ##:::..::. ##::..::::: ##: ##:::::::  
  ::: ##:::: ##:::: ##:::: ##:::: ##:. ######::'##::::'#######:: #######::  
  ::: ##:::: ##:::: ##:::: ##:::: ##::..... ##:..::::'##::::::::...... ##:  
  ::: ##:::: ##:::: ##:::: ##:::: ##:'##::: ##::::::: ##::::::::'##::: ##:  
  ::: ##::::. #######:::::. #######::. ######:::::::: #########:. ######::  
  :::..::::::.......:::::::.......::::......:::::::::.........:::......:::  
  ```
  Mengisi file `motd` dengan teks **ASCII Art** tersebut.

  ```
  find . | cpio -oHnewc | gzip > ../myramdisk.gz
  ```
  Menggunakan utilitas cpio lalu mengompresnya dengan gzip untuk membuat/memperbarui `myramdisk.gz`.
  

- **Screenshot:**

  Tampilan sebelum menambahkan banner
  
  ![before](https://drive.google.com/uc?id=1d2G8F-MhL7YpaVtFoYOKrpkLecg-MMne)

  Tampilan setelah menambahkan banner


  ![after](https://drive.google.com/uc?id=13K_ELy9gVwjjvr1sn8e6SdELrlkJw1GR)

### Soal 7

> Melihat perkembangan sistem operasi milik Budiman, Dosen kagum dengan adanya banner yang telah kamu buat sebelumnya. Kemudian Dosen juga menginginkan sistem operasi Budiman untuk dapat menampilkan **kata sambutan** dengan menyebut nama user yang login. Sambutan yang dimaksud berupa kalimat `"Helloo %USER"` dengan `%USER` merupakan nama user yang sedang menggunakan sistem operasi. Kalimat sambutan ini ditampilkan setelah user login dan setelah banner. Budiman kembali lagi meminta bantuanmu dalam menambahkan fitur ini.

> _Seeing the progress of Budiman's OS, the lecturer is impressed with the banner you created. The lecturer also wants the OS to display a **greeting message** that includes the name of the user who logs in. The greeting should say `"Helloo %USER"` where `%USER` is the name of the user currently using the OS. This greeting should be displayed after user login and after the banner. Budiman asks for your help again to add this feature._

**Answer:**

- **Code:**

  ```
  sudo bash
  ```
  ```
  cd myramdisk
  nano etc/profile
  ```
  ```
  #!/bin/bash

  echo "Heloo $USER"
  ```
  ```
  find . | cpio -oHnewc | gzip > ../myramdisk.gz
  ```
  
- **Explanation:**

  ```
  sudo bash
  ```
  Berpindah ke superuser (root) untuk melakukan perubahan.
  
  ```
  cd myramdisk
  nano etc/motd
  ```
  Berpindah ke direktori `myramdisk` lalu membuat file `profile` di dalam direktori `etc`.
  <br>`profile`: file yang digunakan untuk mengatur konfigurasi awal terminal untuk semua user ketika login dengan menjalankan isi dari file tersebut.</br>

  ```
  #!/bin/bash

  echo "Heloo $USER"
  ```
  Mengisi file `profile` dengan skrip tersebut untuk memberikan greeting dan menggunakan `$USER` untuk mengakses nama user yang login.

  ```
  find . | cpio -oHnewc | gzip > ../myramdisk.gz
  ```
  Menggunakan utilitas cpio lalu mengompresnya dengan gzip untuk membuat/memperbarui `myramdisk.gz`.

- **Screenshot:**

  Tampilan sebelum menambahkan greeting message

  ![before](https://drive.google.com/uc?id=13K_ELy9gVwjjvr1sn8e6SdELrlkJw1GR)

  Tampilan setelah menambahkan greeting message

  ![after](https://drive.google.com/uc?id=1DKodvljyR-yYjDq6CqQxtaW3MvOZU90m)

  

### Soal 8

> Dosen Budiman sudah tua sekali, sehingga beliau memiliki kesulitan untuk melihat tampilan terminal default. Budiman menginisiatif untuk membuat tampilan sistem operasi menjadi seperti terminal milikmu. Modifikasilah sistem operasi Budiman menjadi menggunakan tampilan terminal kalian.

> _Budiman's lecturer is quite old and has difficulty seeing the default terminal display. Budiman takes the initiative to make the OS look like your terminal. Modify Budiman's OS to use your terminal appearance!_

**Answer:**

- **Code:**

Dengan menggunakan perintah `make menuconfig` kita mengubah beberapa settingan ui input terminal agar sama dengan terminal input linux utama kita:
```
-> Device Drivers > Character devices > Serial drivers > 8250/16550 and compatible serial support
```
```
-> Device Drivers > Character devices > Serial drivers > 8250/16550 and compatible serial support > Support 8250_core.* kernel options (DEPRECATED)
```
```
-> Device Drivers > Character devices > Serial drivers > 8250/16550 and compatible serial support > Console on 8250/16550 and compatible serial port 
```

setelah itu, kita menjalankan qemu dengan pengaturan:
```qemu-system-x86_64 -smp 2 -m 256 -display curses -vga std -kernel bzImage -initrd myramdisk.gz -nographic -append "console=ttyS0"```

- **Explanation:**

*config explanation:*

Fungsi `-> Device Drivers > Character devices > Serial drivers > 8250/16550 and compatible serial support` adalah: 
Mengaktifkan dukungan untuk UART serial driver 8250/16550 (seri chipset yang umum dipakai di sistem x86 dan embedded). sehingga, Kernel mampu mengakses dan menggunakan port serial yang menggunakan chip ini (misalnya /dev/ttyS0, /dev/ttyS1, dll).

Fungsi `-> Device Drivers > Character devices > Serial drivers > 8250/16550 and compatible serial support > Support 8250_core.* kernel options (DEPRECATED)` adalah:
Kernel bisa pakai 8250_core.nr_uarts=* untuk membuat ttyS0 dan seterusnya.

Fungsi `-> Device Drivers > Character devices > Serial drivers > 8250/16550 and compatible serial support > Console on 8250/16550 and compatible serial port` adalah:

*qemu setting explanation:*

Dengan settingan -nographic, semuanya dipindah ke serial console (/dev/ttyS0) secara langsung. sedangkan, console=ttyS0 memberi tahu kernel untuk menggunakan ttyS0 (port serial pertama) sebagai console utama.

- **Screenshot:**

![after](https://drive.google.com/uc?id=1E5FAwG1OWip4shd1FY4hdu-QfrFmQyyO)

### Soal 9

> Ketika mencoba sistem operasi buatanmu, Budiman tidak bisa mengubah text file menggunakan text editor. Budiman pun menyadari bahwa dalam sistem operasi yang kamu buat tidak memiliki text editor. Budimanpun menyuruhmu untuk menambahkan **binary** yang telah disiapkan sebelumnya ke dalam sistem operasinya. Buatlah sehingga sistem operasi Budiman memiliki **binary text editor** yang telah disiapkan!

> _When trying your OS, Budiman cannot edit text files using a text editor. He realizes that the OS you created does not have a text editor. Budiman asks you to add the prepared **binary** into his OS. Make sure Budiman's OS has the prepared **text editor binary**!_

**Answer:**

- **Code:**

  ```
  cp /bin/nano myramdisk/bin/
  ```

  ```
  mkdir -p myramdisk/{lib,lib64}
  ```

  ```
  mkdir -p myramdisk/lib/x86_64-linux-gnu
cp /lib/x86_64-linux-gnu/libncursesw.so.6 myramdisk/lib/x86_64-linux-gnu/
cp /lib/x86_64-linux-gnu/libtinfo.so.6 myramdisk/lib/x86_64-linux-gnu/
cp /lib/x86_64-linux-gnu/libc.so.6 myramdisk/lib/x86_64-linux-gnu/
cp /lib64/ld-linux-x86-64.so.2 myramdisk/lib64/
  ```

  ```
mkdir -p myramdisk/lib/terminfo/v
cp /lib/terminfo/v/vt100 myramdisk/lib/terminfo/v/
  ```

  ```
chmod +x myramdisk/bin/nano
  ```

  ```
cd myramdisk 
find . | cpio -oHnewc | gzip > ../myramdisk.gz
  ```

- **Explanation:**

**Copy nano dari linux ke mini linux**:
```
cp /bin/nano myramdisk/bin/
```

**Membuat folder lib dan lib64 yang nanti akan dimasukki oleh dpendensi dari nano**:

```
mkdir -p myramdisk/{lib,lib64}
```
**Mengkopi dependensi dari nano ke dalam kedua folder tadi**:
```
mkdir -p myramdisk/lib/x86_64-linux-gnu
cp /lib/x86_64-linux-gnu/libncursesw.so.6 myramdisk/lib/x86_64-linux-gnu/
cp /lib/x86_64-linux-gnu/libtinfo.so.6 myramdisk/lib/x86_64-linux-gnu/
cp /lib/x86_64-linux-gnu/libc.so.6 myramdisk/lib/x86_64-linux-gnu/
cp /lib64/ld-linux-x86-64.so.2 myramdisk/lib64/
```
Note: dependensi ini dapat dicari dengan syntax
```
ldd /bin/nano
```

**copy vt100 ke dalam myramdisk karena nano butuh ini untuk bekerja**:
```
mkdir -p myramdisk/lib/terminfo/v
cp /lib/terminfo/v/vt100 myramdisk/lib/terminfo/v/
```
Note: mencari vt100 bisa menggunakan `find /lib/terminfo -name "vt100"`

**Mengubah izin nano agar bisa mengedit file**:
```
chmod +x myramdisk/bin/nano
```

**Rebuild iniramfs**:
```
cd myramdisk 
find . | cpio -oHnewc | gzip > ../myramdisk.gz
```

**Jalankan qemu dengan settingan nomor 8 agar menampilkan tampilan terminal**:
```
qemu-system-x86_64 \
-smp 2 \
-m 256 \
-nographic \
-kernel bzImage \
-initrd myramdisk.gz \
-nographic \
-append "console=ttyS0"
```
- **Screenshot:**

![after](https://drive.google.com/uc?id=1O9aVx8s66tKJBSjWje3eoNk47H7uq8So)
![after](https://drive.google.com/uc?id=1O9aVx8s66tKJBSjWje3eoNk47H7uq8So)
![after](https://drive.google.com/uc?id=19CAAg3DDb9U2NG7WFh4qWrhm_8MDhvzo)

### Soal 10

> Setelah seluruh fitur yang diminta Dosen dipenuhi dalam sistem operasi Budiman, sudah waktunya Budiman mengumpulkan tugasnya ini ke Dosen. Akan tetapi, Dosen Budiman tidak mau menerima pengumpulan selain dalam bentuk **.iso**. Untuk terakhir kalinya, Budiman meminta tolong kepadamu untuk mengubah seluruh konfigurasi sistem operasi yang telah kamu buat menjadi sebuah **file .iso**.

> After all the features requested by the lecturer have been implemented in Budiman's OS, it's time for Budiman to submit his assignment. However, Budiman's lecturer only accepts submissions in the form of **.iso** files. For the last time, Budiman asks for your help to convert the entire configuration of the OS you created into a **.iso file**.

**Answer:**

- **Code:**
   ```bash
   cd osboot
   ```
   
   ```bash
   mkdir -p mylinuxiso/boot/grub
   ```

   ```bash
   cp bzImage mylinuxiso/boot
   cp myramdisk.gz mylinuxiso/boot
   ```

   ```cfg
   set timeout=5
   set default=0

   menuentry "MyLinux" {
     linux /boot/bzImage
     initrd /boot/myramdisk.gz
   }
   ```

   ```bash
   grub-mkrescue -o mylinux.iso mylinuxiso
   ```

```qemu-system-x86_64   -smp 2   -m 256   -display curses   -vga std   -cdrom mylinux.iso -nographic 
```
- **Explanation:**
**Masuk ke direktori `osboot`**:
   ```bash
   cd osboot
   ```
**Buat struktur direktori ISO**:
   ```bash
   mkdir -p mylinuxiso/boot/grub
   ```
**Salin file kernel dan root filesystem**:
   ```bash
   cp bzImage mylinuxiso/boot
   cp myramdisk.gz mylinuxiso/boot
   ```
**Buat file konfigurasi GRUB**:
  Buat file `grub.cfg` di `mylinuxiso/boot/grub` dengan isi:
     ```cfg
   set timeout=5
   set default=0

   menuentry "MyLinux" {
     linux /boot/bzImage
     initrd /boot/myramdisk.gz
   }
   ```
     > File ini akan membuat menu GRUB yang menampilkan pilihan boot bernama "MyLinux", dan mengarahkan sistem untuk menggunakan kernel dan initrd yang sudah kita sediakan.
**Buat file ISO bootable**:
 
   ```bash
   grub-mkrescue -o mylinux.iso mylinuxiso
   ```
**Boot iso dengan menggunakan qemu dengan settingan agar seperti terminal linux utama**:
``` qemu-system-x86_64   -smp 2   -m 256   -display curses   -vga std   -cdrom mylinux.iso -nographic```
- **Screenshot:**
![after](https://drive.google.com/uc?id=1__qyQXhE5viz55ltgGDaeNJomVmbE4te)
![after](https://drive.google.com/uc?id=1uJ51gOgxJSzsVC0xwWIg8NsCRAY0LSLj)
---

Pada akhirnya sistem operasi Budiman yang telah kamu buat dengan susah payah dikumpulkan ke Dosen mengatasnamakan Budiman. Kamu tidak diberikan credit apapun. Budiman pun tidak memberikan kata terimakasih kepadamu. Kamupun kecewa tetapi setidaknya kamu telah belajar untuk menjadi pembuat sistem operasi sederhana yang andal. Selamat!

_At last, the OS you painstakingly created was submitted to the lecturer under Budiman's name. You received no credit. Budiman didn't even thank you. You feel disappointed, but at least you've learned to become a reliable creator of simple operating systems. Congratulations!_
