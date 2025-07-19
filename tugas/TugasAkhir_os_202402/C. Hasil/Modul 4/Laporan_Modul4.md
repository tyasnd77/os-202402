# 📝 Laporan Tugas Akhir

**Mata Kuliah**: Sistem Operasi

**Semester**: Genap / Tahun Ajaran 2024–2025

**Nama**: Tyas Nurshika Damaia

**NIM**: 240202887

**Modul yang Dikerjakan**:
 Modul 4 – Subsistem Kernel Alternatif (xv6-public)

---

## 📌 Deskripsi Singkat Tugas

Modul ini mencakup pengembangan dua fitur subsistem kernel pada xv6:

  1. System call `chmod(path, mode)` untuk mengatur mode file (`read-only`      atau `read-write`) secara sederhana.

  2. Pseudo-device `/dev/random` yang menghasilkan byte acak ketika             dibaca, menyerupai fungsionalitas `/dev/random` di sistem UNIX/Linux.

---

## 🛠️ Rincian Implementasi

* System Call `chmod(path, mode)` *
* Menambahkan field `mode` pada `struct inode` di `fs.h` (bersifat volatile, hanya di memori).

* Menambahkan syscall `chmod()` di:

  * `sysfile.c` (`sys_chmod`)

  * `syscall.h`, `syscall.c`, `user.h`, `usys.S`

* Modifikasi `filewrite()` di `file.c` untuk mencegah penulisan ke file dengan mode `read-only`.

* Program uji: `chmodtest.c`

🔹 Device `/dev/random`
Menambahkan file `random.c` sebagai driver sederhana penghasil angka acak.

Registrasi device di `file.c` melalui `devsw[]` dengan major number `3`.

Menambahkan entri `/dev/random` via `mknod()` di `init.c`.

Program uji: `randomtest.c`

---

## ✅ Uji Fungsionalitas

Program uji yang digunakan:

* `chmodtest`: menguji sistem file agar menolak penulisan ke file `read-only`

* `randomtest`: membaca 8 byte acak dari `/dev/random`

---

## 📷 Hasil Uji

### 📍 Contoh Output `chmodtest`:

```
Write blocked as expected
```
### 📍 Contoh Output `randomtest`:

```
241 6 82 99 12 201 44 73
```

Jika ada screenshot:

```
![hasil cowtest](./screenshots/cowtest_output.png)
```

---

## ⚠️ Kendala yang Dihadapi

* Lupa memvalidasi `mode` pada `sys_chmod()` → bisa menyebabkan mode tidak valid diset.

* Salah index `devsw[]` menyebabkan `randomread()` tidak terhubung ke `/dev/random`.

* Masalah pada `filewrite()` ketika pointer `f->ip` belum valid → sempat menyebabkan panic.

---

## 📚 Referensi

Tuliskan sumber referensi yang Anda gunakan, misalnya:

* Buku xv6 MIT: [https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf](https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf)
* Repositori xv6-public: [https://github.com/mit-pdos/xv6-public](https://github.com/mit-pdos/xv6-public)
* Stack Overflow, GitHub Issues, diskusi praktikum

---
