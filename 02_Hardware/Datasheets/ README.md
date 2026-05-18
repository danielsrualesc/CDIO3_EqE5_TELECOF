# 📑 Datasheets y Documentación Técnica

Esta carpeta contiene la documentación técnica oficial de los componentes utilizados en el sistema **TELESFÉRICO DE CAFÉ**.

Todos los documentos aquí almacenados corresponden a **datasheets oficiales de fabricante**, especificaciones técnicas y documentación necesaria para el correcto diseño electrónico, programación del firmware y configuración del sistema de comunicación **LoRa + WiFi**.

---

## 🔧 Microcontrolador

💿 **LilyGO ESP32 LoRa V2**  
Tarjeta principal utilizada como receptor del sistema. Incluye conectividad **WiFi**, **Bluetooth** y módulo **LoRa SX1276 integrado**, ideal para aplicaciones IoT y telemetría de largo alcance.

Información oficial y guía de uso:

:contentReference[oaicite:0]{index=0}

---

## 📡 Comunicación Inalámbrica LoRa

📶 **SX1276 / SX1278 LoRa Transceiver**  
Módulo encargado de la transmisión y recepción inalámbrica de datos de pesaje entre nodos.

Datasheet oficial:

:contentReference[oaicite:1]{index=1}

---

## 🌐 Comunicación WiFi ESP32

📡 **ESP32 WiFi/Bluetooth SoC**  
Microcontrolador utilizado para gestionar el servidor web, autenticación de usuarios y visualización de datos en tiempo real.

Documentación oficial:

:contentReference[oaicite:2]{index=2}

---

## ⚙️ Librerías Utilizadas

Las siguientes librerías son necesarias para el funcionamiento del sistema:

- **LoRa by Sandeep Mistry** → Comunicación LoRa
- **ESPAsyncWebServer** → Interfaz web asíncrona
- **AsyncTCP** → Comunicación TCP asíncrona
- **WiFi.h** → Conectividad WiFi
- **SPI.h** → Comunicación SPI con LoRa
- **time.h** → Sincronización de fecha y hora (NTP)

---

*TELESFÉRICO DE CAFÉ © 2026 — Sistema Inteligente de Pesaje Cafetero*
