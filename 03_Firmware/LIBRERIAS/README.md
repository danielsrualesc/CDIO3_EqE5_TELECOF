### Dependencias (Librerías)

Las siguientes librerías son **obligatorias** para compilar correctamente el proyecto **TELESFÉRICO DE CAFÉ**:

1. **LoRa by Sandeep Mistry**  
   (Permite la comunicación inalámbrica LoRa entre el transmisor y receptor).

2. **ESPAsyncWebServer**  
   (Servidor web asíncrono para la interfaz web del sistema).

3. **AsyncTCP**  
   (Manejo de comunicación TCP asíncrona requerida por ESPAsyncWebServer).

4. **WiFi** *(incluida en ESP32)*  
   (Permite la conexión del ESP32 a redes WiFi o hotspot móvil).

5. **SPI** *(incluida en ESP32)*  
   (Comunicación SPI utilizada por el módulo LoRa integrado).

6. **time / NTP** *(incluida en ESP32)*  
   (Permite sincronizar fecha y hora automáticamente para generar reportes).

### Instalación de Librerías
Ve a:

**Arduino IDE → Herramientas → Administrar Librerías**

E instala las siguientes:

```txt
LoRa by Sandeep Mistry
ESPAsyncWebServer
AsyncTCP
```

Las librerías **WiFi**, **SPI** y **time** ya vienen integradas en el paquete de placas **ESP32 by Espressif Systems**, por lo que **no es necesario instalarlas manualmente**.
