# 📝 Laporan Tugas Akhir

**Mata Kuliah**: Sistem Operasi

**Semester**: Genap / Tahun Ajaran 2024–2025

**Nama**: Tyas Nurshika Damaia

**NIM**: 240202887

**Modul yang Dikerjakan**:
Modul 1 – System Call dan Instrumentasi Kernel

---

## 📌 Deskripsi Singkat Tugas
* **Modul 1 – System Call dan Instrumentasi Kernel**:
  Pada modul ini, saya mengimplementasikan dua buah system call baru di sistem operasi xv6-public, yaitu:
1.getpinfo(struct pinfo *ptable) — untuk mendapatkan informasi proses aktif di sistem (PID, ukuran memori, dan nama proses).
2.getreadcount() — untuk menghitung total pemanggilan fungsi read() sejak sistem dijalankan (boot).
Modul ini bertujuan untuk memahami bagaimana kernel mengelola sistem call dan melakukan instrumentasi aktivitas sistem secara manual.

## 🛠️ Rincian Implementasi

Berikut adalah langkah-langkah implementasi yang dilakukan:

* Implementasi dimulai dengan menambahkan struktur pinfo di proc.h untuk menyimpan informasi proses, serta variabel global readcount di sysproc.c untuk mencatat jumlah pemanggilan read(). Dua nomor syscall baru, SYS_getpinfo dan SYS_getreadcount, ditambahkan di syscall.h, lalu didaftarkan handler-nya di syscall.c, dan deklarasinya dimasukkan ke user.h dan usys.S.

* Fungsi sys_getpinfo mengambil data dari ptable dan menyalin ke user, sedangkan sys_getreadcount mengembalikan nilai readcount. Di fungsi sys_read() (sysfile.c), ditambahkan readcount++ untuk mencatat setiap pemanggilan read().

* Untuk pengujian, dibuat program ptest.c (mengakses getpinfo()) dan rtest.c (mengakses getreadcount() sebelum dan sesudah read()). Keduanya ditambahkan ke Makefile agar bisa dijalankan di xv6.

## ✅ Uji Fungsionalitas

* Program ptest – Menguji getpinfo()
Program ini memanggil getpinfo() dan mencetak daftar proses aktif di sistem. Data yang ditampilkan meliputi PID, ukuran memori, dan nama proses. Hasil pengujian menunjukkan informasi proses berhasil ditampilkan dengan benar.
* Program rtest – Menguji getreadcount()
Program ini memanggil getreadcount() sebelum dan sesudah fungsi read() dijalankan. Tujuannya untuk memverifikasi apakah counter readcount meningkat sesuai jumlah pemanggilan read(). Hasilnya, nilai readcount bertambah 1 setelah pemanggilan read(), menandakan counter bekerja dengan benar.


## 📷 Hasil Uji

Lampirkan hasil uji berupa screenshot atau output terminal. Contoh:

### 📍 Contoh Output `ptest`:

```
PID     MEM      NAME
1       12288    init
2       16384    sh
3       12288    ptest
```

### 📍 Contoh Output `rtest`:

```
Read Count Sebelum: 12
hello
Read Count Setelah: 13
```

![Output ptest_rtest](./screenshots/output_ptest_rtest.png)


## ⚠️ Kendala yang Dihadapi

* Variabel readcount tidak dikenali di sys_read() → disebabkan karena belum dideklarasikan sebagai global. Solusi: dipindah ke bagian global sysfile.c atau sysproc.c, dan bila perlu dideklarasikan extern.

* ptable tidak dikenali di sysproc.c → karena belum ditambahkan deklarasi extern struct ptable dari proc.c. Solusi: tambahkan extern di defs.h atau langsung di sysproc.c.

* Typo dan pointer cast di argptr → perlu hati-hati dengan konversi (char**)&....

## 📚 Referensi

* xv6-public GitHub

* MIT xv6 Book

* Dokumentasi praktikum dan diskusi internal:

* Buku xv6 MIT: [https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf](https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf)
* Repositori xv6-public: [https://github.com/mit-pdos/xv6-public](https://github.com/mit-pdos/xv6-public)
* Stack Overflow, GitHub Issues, diskusi praktikum

---
