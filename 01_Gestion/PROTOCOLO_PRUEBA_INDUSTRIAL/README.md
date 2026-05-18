# Protocolo de Pruebas Industrial -- Proyecto Teleferico del Cafe
**Version:** 1.0 | **Fecha de actualizacion:** 2026-05-18
**Equipo:** Erick S. Cruz Silva / Rohin H. Suarez Gallego / Daniel S. Ruales Cuaran / Kevin E. Aragon Camacho

&gt; Este protocolo ha sido diligenciado y ejecutado. Los resultados definitivos se encuentran registrados en `Bitacora_Trazabilidad.csv`.

---

## TEST-HW-01 -- Validacion Dimensional PCB (KiCad)
**Prioridad:** P1 Alto | **Requisito:** REQ-HW-01 | **Estado:** PASS

| Campo | Detalle |
|---|---|
| Objetivo | Validar que las dimensiones de la PCB del Nodo A permitan encaje dentro de la carcasa PLA+ |
| Setup | Software KiCad 7.0, Diseno 3D de la carcasa en PLA+ |
| Pasos | 1. Trazar bordes de corte (Edge.Cuts) / 2. Medir ancho y largo maximo en KiCad / 3. Comparar con dimensiones internas de la carcasa |
| Input | Ancho max objetivo: &lt;= 120mm / Largo max objetivo: &lt;= 80mm |
| Resultado Esperado | PCB virtual &lt;= 120mm x 80mm |
| Resultado Obtenido | **118mm x 78mm** |
| Responsable | Rohin Suarez |

---

## TEST-HW-02 -- Validacion Conexion Celda de Carga (HX711)
**Prioridad:** P0 Critico | **Requisito:** REQ-HW-02 | **Estado:** PASS

| Campo | Detalle |
|---|---|
| Objetivo | Validar lectura estable del HX711 con celda de carga de 5 kg en condicion estatica |
| Setup | LilyGo TTGO LoRa32 V2.1, HX711, Celda de carga 5 kg, Monitor Serial 115200 baud, Pesa patron 1 kg |
| Pasos | 1. Flashear firmware v23 / 2. Colocar pesa patron de 1 kg sobre celda / 3. Registrar lectura durante 10 s / 4. Verificar estabilidad |
| Input | Pesa patron: 1000.0 g exactos / Ganancia: 128 / Muestras: 10 promedio |
| Resultado Esperado | Lectura en Monitor Serial: 1000.0 g +/- 0.5 g |
| Resultado Obtenido | **999.8 g -- 1000.2 g** |
| Responsable | Erick Cruz |

---

## TEST-FW-01 -- Validacion FSM 9 Estados
**Prioridad:** P0 Critico | **Requisito:** REQ-FW-01 | **Estado:** PASS

| Campo | Detalle |
|---|---|
| Objetivo | Validar transicion correcta entre los 9 estados de la maquina de estados sin bloqueos |
| Setup | Firmware v23 completo, LCD 16x2 I2C, 3 botones, Motor DC + L298N |
| Pasos | 1. Iniciar en ST_ESPERA / 2. Presionar BTN_NOMBRE para ciclar trabajadores / 3. Presionar BTN_OK para iniciar pesaje / 4. Esperar 10 s (ST_PESANDO) / 5. Confirmar resultado (ST_RESULTADO) / 6. Confirmar motor (ST_CONFIRMAR) / 7. Verificar secuencia motor adelante / pausa / atras / 8. Repetir 10 ciclos completos |
| Input | Lista trabajadores: {Erick, Oscar, Yunicua} / tiempoMotor: 1350 ms / tiempoPausa: 10 s |
| Resultado Esperado | 10 ciclos completos sin bloqueo, LCD muestra mensajes correctos por estado |
| Resultado Obtenido | **10/10 ciclos completados sin bloqueos. Transiciones ST_ESPERA -&gt; ST_PESANDO -&gt; ST_RESULTADO -&gt; ST_CONFIRMAR -&gt; ST_MOTOR_A -&gt; ST_MOTOR_PAUSA -&gt; ST_MOTOR_B -&gt; ST_ESPERA correctas** |
| Responsable | Daniel Ruales |

---

## TEST-HW-03 -- Validacion Control Motor DC (L298N)
**Prioridad:** P1 Alto | **Requisito:** REQ-HW-03 | **Estado:** PASS

| Campo | Detalle |
|---|---|
| Objetivo | Validar control de direccion y velocidad del motor DC mediante L298N |
| Setup | LilyGo TTGO, L298N, Motor DC 5V, Fuente 5V externa, Osciloscopio |
| Pasos | 1. Configurar PWM en ENA (GPIO25) / 2. Activar IN1 (GPIO15) + IN2 LOW para adelante / 3. Medir voltaje en bornes motor / 4. Invertir IN1/IN2 para atras / 5. Verificar tiempo de giro 1350 ms |
| Input | PWM duty cycle: 130/255 / Voltaje motor: 5V / Tiempo adelante: 1350 ms |
| Resultado Esperado | Motor gira adelante 1350 ms, detiene, gira atras 1350 ms. Voltaje motor ~4.8V |
| Resultado Obtenido | **Motor adelante: 1348 ms / Motor atras: 1351 ms / Voltaje: 4.85V. Retorno exacto al origen verificado** |
| Responsable | Rohin Suarez |

---

## TEST-MC-01 -- Validacion Alcance LoRa 915 MHz
**Prioridad:** P0 Critico | **Requisito:** REQ-MC-01 | **Estado:** PASS

| Campo | Detalle |
|---|---|
| Objetivo | Validar transmision y recepcion de paquetes LoRa entre Nodo A y Nodo B en campo abierto y con obstaculos |
| Setup | Nodo A (Transmisor) + Nodo B (Receptor), antenas SMA 915 MHz, Campo de pruebas Universidad del Quindio |
| Pasos | 1. Encender ambos nodos / 2. Realizar pesaje completo en Nodo A / 3. Verificar recepcion en Nodo B / 4. Medir distancia maxima campo abierto / 5. Medir distancia con obstaculos (edificios) / 6. Registrar RSSI |
| Input | Frecuencia: 915 MHz / SF: 7 / BW: 125 kHz / CR: 4/5 / TX Power: +20 dBm |
| Resultado Esperado | Campo abierto: &gt;= 50 m (10/10 paquetes) / Con obstaculos: &gt;= 30 m (&gt;= 9/10 paquetes) |
| Resultado Obtenido | **Campo abierto: 50 m -- 10/10 paquetes recibidos, RSSI = -85 dBm / Con obstaculos: 30 m -- 9/10 paquetes recibidos, &lt; 10% perdida** |
| Responsable | Kevin Aragon |

---

## TEST-FW-02 -- Validacion Emergencia BTN_STOP
**Prioridad:** P0 Critico | **Requisito:** REQ-FW-02 | **Estado:** PASS (Corregido)

| Campo | Detalle |
|---|---|
| Objetivo | Validar detencion de emergencia y retorno proporcional al origen desde cualquier estado motor activo |
| Setup | Firmware v23, BTN_STOP en GPIO4 con pull-down 10kOhm, Motor DC + L298N |
| Pasos | 1. Iniciar ciclo normal hasta ST_MOTOR_A / 2. Durante giro adelante, mantener BTN_STOP 400 ms / 3. Verificar detencion inmediata / 4. Esperar 3 s (ST_EMERGENCIA_ESPERA) / 5. Verificar retorno proporcional a tiempoGirado / 6. Repetir desde ST_MOTOR_PAUSA y ST_MOTOR_B |
| Input | Hold minimo BTN_STOP: 400 ms / tiempoGirado: registrado en ST_MOTOR_A |
| Resultado Esperado | Motor detiene inmediatamente. Retorna proporcional al tiempo girado. No activacion falsa en boot. |
| Resultado Obtenido | **Detencion inmediata en 3 estados probados. Retorno proporcional verificado: 675 ms retorno para 1350 ms adelante. Sin activaciones falsas en 20 ciclos de boot** |
| Responsable | Erick Cruz |

---

## TEST-HW-04 -- Validacion LCD 16x2 I2C
**Prioridad:** P1 Alto | **Requisito:** REQ-HW-04 | **Estado:** PASS

| Campo | Detalle |
|---|---|
| Objetivo | Validar visualizacion correcta de mensajes en LCD 16x2 I2C por cada estado de la FSM |
| Setup | LCD 16x2 PCF8574, direccion I2C 0x27, bus 100 kHz |
| Pasos | 1. Verificar direccion I2C con scanner / 2. Flashear firmware v23 / 3. Recorrer todos los estados de la FSM / 4. Verificar mensaje Linea 1 y Linea 2 por estado / 5. Confirmar formato 1 decimal (String(peso,1)) |
| Input | Direccion I2C: 0x27 / Frecuencia: 100 kHz / Estados: 9 |
| Resultado Esperado | LCD muestra mensajes correctos en todos los estados. Formato 1 decimal unificado. |
| Resultado Obtenido | **9/9 estados con mensajes correctos. Formato 1 decimal verificado en LCD, Serial y LoRa. Sin caracteres corruptos** |
| Responsable | Daniel Ruales |

---

## TEST-MC-02 -- Validacion WiFi HTTP Nodo B
**Prioridad:** P1 Alto | **Requisito:** REQ-MC-02 | **Estado:** PASS

| Campo | Detalle |
|---|---|
| Objetivo | Validar descarga de lista de trabajadores via HTTP GET /lista desde Nodo B |
| Setup | Nodo B con AsyncWebServer, Access Point WiFi, Celular como cliente |
| Pasos | 1. Encender Nodo B / 2. Conectar celular a WiFi del Nodo B / 3. Abrir navegador e ingresar IP / 4. Solicitar GET /lista / 5. Verificar formato CSV / 6. Medir tiempo de respuesta |
| Input | SSID: configurable / IP tipica: 192.168.4.1 / Endpoint: /lista |
| Resultado Esperado | Respuesta CSV con LISTA_START/LISTA_END. Tiempo respuesta &lt; 5 s. |
| Resultado Obtenido | **Respuesta CSV correcta: LISTA_START, headers, datos, LISTA_END. Tiempo promedio: 3.2 s (10 pruebas). Maximo: 4.1 s** |
| Responsable | Kevin Aragon |

---

## TEST-FW-03 -- Validacion Modo Autonomo (Sin WiFi)
**Prioridad:** P1 Alto | **Requisito:** REQ-FW-03 | **Estado:** PASS

| Campo | Detalle |
|---|---|
| Objetivo | Validar operacion completa del Nodo A sin conexion WiFi usando lista de respaldo hardcodeada |
| Setup | Nodo A aislado (sin Nodo B encendido), firmware v23 |
| Pasos | 1. Encender Nodo A sin Nodo B disponible / 2. Esperar 20 s (40 intentos WiFi) / 3. Verificar activacion automatica de lista respaldo / 4. Realizar ciclo completo de pesaje / 5. Verificar transmision LoRa (sin receptor) / 6. Repetir 10 ciclos |
| Input | Max intentos WiFi: 40 / Tiempo max espera: 20 s / Lista respaldo: {Erick, Oscar, Yunicua} |
| Resultado Esperado | Lista respaldo activa automaticamente. Sistema funciona autonomo. 10 ciclos sin fallos. |
| Resultado Obtenido | **Lista respaldo activada en 18.5 s promedio. 10/10 ciclos completos sin WiFi. LCD muestra nombres correctos. LoRa transmite sin receptor (paquetes en cola)** |
| Responsable | Erick Cruz |

---

## TEST-HW-05 -- Validacion Resolucion HX711 (0.1 g)
**Prioridad:** P0 Critico | **Requisito:** REQ-HW-05 | **Estado:** PASS

| Campo | Detalle |
|---|---|
| Objetivo | Validar resolucion de 0.1 g del sistema de pesaje con HX711 y celda de carga 5 kg |
| Setup | HX711, Celda 5 kg, Pesas patron (100 g, 500 g, 1000 g, 2000 g, 5000 g) |
| Pasos | 1. Calibrar HX711 con factor de escala / 2. Colocar pesa patron / 3. Registrar lectura durante 10 s / 4. Verificar resolucion (incrementos de 0.1 g) / 5. Repetir con 5 pesas diferentes |
| Input | Pesas: 100 g, 500 g, 1000 g, 2000 g, 5000 g / Resolucion esperada: 0.1 g |
| Resultado Esperado | Lectura con resolucion 0.1 g estable en todo el rango 0 -- 5000 g |
| Resultado Obtenido | **Resolucion 0.1 g confirmada en todo el rango. Desviacion maxima: +/- 0.2 g en 5000 g. Estabilidad verificada con promedio 10 muestras** |
| Responsable | Rohin Suarez |

---

## TEST-MC-03 -- Validacion Persistencia Nodo B (RAM)
**Prioridad:** P2 Medio | **Requisito:** REQ-MC-03 | **Estado:** PARCIAL

| Campo | Detalle |
|---|---|
| Objetivo | Validar almacenamiento de registros en RAM del Nodo B y limite de 50 pesajes |
| Setup | Nodo B receptor, 50 ciclos de pesaje simulados desde Nodo A |
| Pasos | 1. Encender Nodo B / 2. Simular 50 recepciones LoRa / 3. Verificar almacenamiento en RAM / 4. Solicitar GET /lista / 5. Verificar 50 registros / 6. Intentar registro 51 |
| Input | Max registros RAM: 50 / Formato: id,nombre,peso_g,pago_COP |
| Resultado Esperado | 50 registros almacenados correctamente. Registro 51 rechazado o sobrescribe el primero. |
| Resultado Obtenido | **50/50 registros almacenados correctamente. Registro 51 rechazado con mensaje de error. Persistencia en flash PENDIENTE (solo RAM actualmente)** |
| Responsable | Kevin Aragon |
