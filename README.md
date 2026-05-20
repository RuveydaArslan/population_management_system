# 🏙️ Hiyerarşik Nüfus Simülasyon Sistemi

Bu proje, **C dili** kullanılarak geliştirilmiş hiyerarşik bir nüfus simülasyon sistemidir. Sistem; şehir, ilçe, mahalle ve kişi yapıları arasında ilişki kurarak dinamik bir yerleşim simülasyonu gerçekleştirmektedir. Projede modüler programlama, dinamik bellek yönetimi ve C dilinde nesne yönelimli programlamaya benzer yapıların kullanımı hedeflenmiştir.

---

## ✨ Özellikler

- 🏙️ **Şehir → İlçe → Mahalle → Kişi** hiyerarşik veri yapısı
- 👥 Dinamik nüfus oluşturma sistemi
- 📈 Tur bazlı nüfus artış simülasyonu
- 🧩 Modüler proje mimarisi
- 🧠 C dilinde OOP benzetimi (struct + pointer tabanlı)
- 💾 Dinamik bellek yönetimi (`malloc`, `realloc`)
- 📂 Dosya tabanlı veri okuma sistemi
- 🎲 Java Faker ile gerçekçi veri üretimi
- 🖥️ Konsol tabanlı kullanıcı arayüzü

---

## 🏗️ Proje Yapısı

```text
project/
│
├── include/        # Header dosyaları (.h)
├── src/            # Kaynak kod dosyaları (.c)
├── data/           # Veri dosyaları
├── lib/            # Object dosyaları (.o)
├── bin/            # Derlenmiş program çıktısı
├── Makefile
└── README.md
```

---

## 🔧 Kullanılan Teknolojiler

| Teknoloji | Açıklama |
|-----------|----------|
| ⚙️ C | Ana simülasyon sistemi |
| ☕ Java | Veri üretimi |
| 🎲 Java Faker | Rastgele gerçekçi veri oluşturma |
| 🧠 Dynamic Memory | `malloc` / `realloc` ile dinamik veri yönetimi |
| 📄 Makefile | Derleme otomasyonu |

---

## 🌳 Hiyerarşik Yapı

```
Sehir
 └── Ilce
       └── Mahalle
             └── Kisi
```

> Projede kalıtım benzetimi için ortak `Yerlesim` yapısı kullanılmıştır.

---

## 📊 Simülasyon Mantığı

1. Kullanıcıdan başlangıç nüfus değerleri alınır.
2. Girilen değerlere göre şehir yapıları oluşturulur.
3. Her tur sonunda:
   - 📈 Nüfus artışı gerçekleşir
   - 👶➡️🧓 Yaş bilgileri güncellenir
   - 🏘️ Yeni yerleşimler oluşabilir

---

## 📂 Veri Dosyaları

Projede **Java Faker** ile üretilmiş aşağıdaki veri dosyaları kullanılmaktadır:

| Dosya | İçerik |
|-------|--------|
| `sehir.txt` | Şehir adları |
| `ilce.txt` | İlçe adları |
| `mahalle.txt` | Mahalle adları |
| `kisiler.txt` | Kişi bilgileri |

---

## 🚀 Derleme ve Çalıştırma

### 🔨 Derleme

```bash
mingw32-make
```

### ▶️ Programı Çalıştırma

```bash
./bin/program
```

---

## 🧠 Kullanılan Programlama Konuları

- Pointer kullanımı
- Dinamik diziler
- Struct yapıları
- Dosya işlemleri
- Bellek yönetimi (`malloc`, `realloc`, `free`)
- Modüler programlama
- Simülasyon sistemleri
- Hiyerarşik veri modelleme

---

## 📸 Örnek Çıktı

```
----- 2. tur sonrasi nufuslar -----
[336]-[810]-[2156]-[2464]
```

---

## 👩‍💻 Geliştirici

Bu proje, **Programlama Dillerinin Prensipleri** dersi kapsamında geliştirilmiştir.
