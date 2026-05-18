# TELESFÉRICO DE CAFÉ — Guía de Instalación y Uso
## Sistema Inteligente de Pesaje Cafetero con LoRa y WiFi

**TELESFÉRICO DE CAFÉ** es un sistema diseñado para automatizar el registro de cargas de café y el cálculo de pagos por trabajador en tiempo real. Utiliza comunicación **LoRa** para recibir pesajes inalámbricos y una interfaz web moderna para visualizar datos, gestionar trabajadores y descargar reportes desde cualquier celular o computador conectado a la red.

---

## ¿Qué necesitas?

### Hardware
| Componente | Descripción |
|---|---|
| LilyGO ESP32 LoRa V2 | Microcontrolador principal (Receptor) |
| Módulo LoRa 915 MHz | Comunicación inalámbrica integrada |
| Celular con hotspot WiFi | Para conexión al sistema |
| Cable USB | Programación del ESP32 |
| Fuente USB o Power Bank | Alimentación del sistema |

### Conexiones del hardware
La tarjeta **LilyGO ESP32 LoRa** ya incluye el módulo LoRa integrado, por lo que no requiere conexiones adicionales.

---

## PARTE 1 — Configurar el ESP32 LoRa

### Paso 1 — Instalar Arduino IDE
1. Descarga Arduino IDE desde:  
   https://www.arduino.cc/en/software
2. Instálalo normalmente

### Paso 2 — Agregar soporte ESP32
1. Abre Arduino IDE  
2. Ve a **Archivo → Preferencias**  
3. En **URLs adicionales del Gestor de Placas** pega:

```txt
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

4. Ve a **Herramientas → Placa → Gestor de Placas**
5. Busca `esp32`
6. Instala **ESP32 by Espressif Systems**

### Paso 3 — Instalar librerías
Ve a **Herramientas → Administrar Librerías** e instala:

- `LoRa by Sandeep Mistry`
- `ESPAsyncWebServer`
- `Async TCP`

### Paso 4 — Seleccionar la placa
1. Ve a:

**Herramientas → Placa → ESP32 Arduino → ESP32 Dev Module**

2. Conecta la LilyGO ESP32 LoRa  
3. Selecciona el puerto COM correspondiente

### Paso 5 — Configurar WiFi
En el código cambia estos datos:

```cpp
const char* WIFI_SSID = "Tu WiFi";
const char* WIFI_PASS = "Tu contraseña";
```

También puedes usar el hotspot de tu celular.

### Paso 6 — Subir el firmware
1. Abre el archivo `.ino`
2. Haz clic en **→ Subir**
3. Espera **“Subida completada”**
4. Abre el **Monitor Serial** a **115200 baud**

Deberías ver algo similar:

```txt
Conectando WiFi...
IP: 172.20.10.5

LoRa OK 915MHz
Servidor activo en 172.20.10.5
```

---

## PARTE 2 — Acceder al Sistema

### Iniciar sesión
1. Conecta tu celular o computador al mismo WiFi
2. Abre el navegador
3. Ingresa a:

```txt
http://172.20.10.5
```

4. Inicia sesión con:

```txt
Usuario: admin
Contraseña: 1234
```

---

## PARTE 3 — Gestión de Trabajadores

### Registrar trabajadores
1. Entra al **Panel de Gestión**
2. Escribe el nombre del trabajador
3. Presiona **Agregar**

El sistema guardará automáticamente la lista de trabajadores registrados.

### Eliminar trabajadores
- Presiona **Eliminar**
- El trabajador será removido del sistema

---

## PARTE 4 — Pesaje en Tiempo Real

### Funcionamiento del sistema
Cuando el transmisor envía un pesaje mediante **LoRa**, el sistema:

- Recibe el nombre del trabajador
- Registra automáticamente la carga
- Acumula el peso total
- Calcula el pago automáticamente
- Actualiza la tabla en tiempo real

### Datos registrados

| Dato | Descripción |
|---|---|
| Trabajador | Nombre registrado |
| Cargas | Número de cargas realizadas |
| Peso Total | Peso acumulado |
| Pago Total | Pago generado automáticamente |

Toda la información se actualiza automáticamente en el sistema web.

---

## PARTE 5 — Descargar Reportes

### Generar reporte
Desde el panel principal:

1. Presiona **Descargar Reporte**
2. El sistema descargará automáticamente un archivo `.txt`

El reporte incluye:

- Fecha y hora
- Cantidad de cargas
- Peso total
- Pago individual
- Totales generales

---

## Solución de problemas comunes

| Problema | Solución |
|---|---|
| No conecta al WiFi | Verifica SSID y contraseña |
| No abre la página | Revisa la IP en el Monitor Serial |
| LoRa no funciona | Verifica frecuencia 915 MHz |
| No llegan pesajes | Revisar transmisor LoRa |
| No aparecen trabajadores | Agregarlos desde el panel |

---

## Formato de datos LoRa

El transmisor debe enviar:

```txt
PESAJE,NOMBRE,PESO,PAGO
```

Ejemplo:

```txt
PESAJE,Juan,52.350,62820.000
```

---

## Resumen rápido

```txt
IP del sistema:
172.20.10.5
```

```txt
Usuario:
admin
```

```txt
Contraseña:
1234
```

```txt
Frecuencia LoRa:
915 MHz
```

---

*TELESFÉRICO DE CAFÉ © 2026 — Sistema Inteligente de Pesaje Cafetero*
