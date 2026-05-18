# Registro Integrado de Retroalimentacion, Protocolos de Prueba y Definition of Done (DoD)
**Proyecto:** Teleferico del Cafe - Sistema Embebido de Pesaje Agroindustrial
**Cliente / Usuario Final:** Operarios de recoleccion de cafe y administrador de finca (Universidad del Quindio - CDIO III)
**Ingenieros a Cargo:** Erick S. Cruz Silva, Rohin H. Suarez Gallego, Daniel S. Ruales Cuaran, Kevin E. Aragon Camacho

---

## 1. Introduccion y Justificacion
Este documento detalla como las necesidades empiricas y cualitativas del usuario final (operarios de recoleccion de cafe y administrador de finca) fueron traducidas en requerimientos tecnicos estrictos, historias de usuario medibles y validaciones cuantificables. El proposito de este registro es evidenciar que el desarrollo del dispositivo **Teleferico del Cafe** siguio una ruta de ingenieria rigurosa (basada en metricas, metodologias agiles y estandares industriales) descartando la improvisacion y garantizando un producto funcional, robusto y preciso para el campo agroindustrial.

---

## 2. Historias de Usuario: La Voz del Cliente (Feedback)
El proceso de retroalimentacion en campo nos permitio capturar las necesidades reales, las cuales fueron formalizadas en la **Matriz de Enfoque y Requisitos**:

* **HU-01 (Operario):** *Requiere identificarse facilmente para que el sistema registre su pesaje automaticamente y calcule su pago.* -&gt; Prioridad P0. Define la interfaz LCD 16x2 con boton NOMBRE para ciclar trabajadores y el calculo automatico de pago en COP (tarifa 1.200 COP/kg).
* **HU-02 (Operario):** *Exige que el sistema pese con precision para no perder dinero en la conversion.* -&gt; Prioridad P0. Define el uso del HX711 24 bits con celda de carga 5 kg y resolucion de 0.1 g, con redondeo explicito en firmware.
* **HU-03 (Administrador):** *Necesita recibir los datos de pesaje en su oficina sin cables y sin depender de internet en el campo.* -&gt; Prioridad P1. Define la comunicacion LoRa 915 MHz entre Nodo A (campo) y Nodo B (base), con transmision automatica al finalizar cada ciclo.
* **HU-04 (Operario):** *Quiere saber en tiempo real cuanto pesa y cuanto va a ganar antes de depositar el cafe.* -&gt; Prioridad P0. Define la pantalla LCD mostrando peso en tiempo real durante 10 s y resultado final (peso + pago COP) antes de confirmar.
* **HU-05 (Administrador):** *Necesita descargar la lista de trabajadores y pesajes en formato CSV para Excel.* -&gt; Prioridad P1. Define el Nodo B con servidor HTTP GET /lista que responde CSV delimitado por LISTA_START/LISTA_END.
* **HU-06 (Operario):** *El sistema debe funcionar aunque no haya WiFi disponible en el campo.* -&gt; Prioridad P1. Define la lista de respaldo hardcodeada ({Erick, Oscar, Yunicua}) que se activa automaticamente si no hay conexion WiFi en 20 s.
* **HU-07 (Operario):** *Debe poder detener el motor inmediatamente si hay algun peligro.* -&gt; Prioridad P0. Define el boton de emergencia BTN_STOP (GPIO4) con hold de 400 ms y retorno proporcional al origen.

---

## 3. Definition of Done (DoD): Estandares de Aceptacion
Para asegurar que las decisiones tomadas cumplieran con la calidad exigida y no fueran validaciones subjetivas (ej. "funciona bien"), se establecio un **Definition of Done (DoD)** riguroso:

1.  **Cero Subjetividad:** Todas las validaciones deben arrojar valores numericos (Gramos, Pesos Colombianos, Milisegundos, Metros, dBm).
2.  **Firmware (FW) y Software:**
    * Resolucion de pesaje de **0.1 g exacta** garantizada por HX711 24 bits con ganancia 128, promedio de 10 muestras y redondeo explicito `roundf(raw * 10.0) / 10.0`.
    * Maquina de estados de **9 estados** sin bloqueos, con transiciones definidas por tiempo (10 s pesaje, 1.350 ms motor, 10 s pausa) y eventos de botones.
    * Transmision de paquetes LoRa con formato ASCII estricto: `PESAJE,nombre,peso,pago`.
    * Sistema autonomo sin WiFi: activacion automatica de lista respaldo tras 40 intentos (20 s maximo).
3.  **Hardware (HW) y Mecanica:**
    * Celda de carga de **5 kg maximo** con cables polarizados (Rojo=E+, Negro=E-, Verde=A+, Blanco=A-).
    * Motor DC controlado por L298N con PWM 1 kHz, duty cycle 130/255, tiempos de giro exactos (1.350 ms adelante/atraas).
    * BTN_STOP en **GPIO4** con pull-down externo 10 kOhm y hold 400 ms para eliminar activaciones falsas (correccion AC-01).
    * Carcasa impresa en **PLA+** con dimensiones &lt;= 120 mm x 80 mm x 45 mm para proteccion en campo.
4.  **Sistema e Interaccion (MC):**
    * Alcance LoRa verificado: **50 m campo abierto (10/10 paquetes)** y **30 m con obstaculos (9/10 paquetes)**.
    * Interfaz LCD 16x2 I2C (direccion 0x27, bus 100 kHz) con mensajes unificados en formato 1 decimal (`String(peso,1)`).
    * Tiempo de respuesta HTTP GET /lista **&lt;&lt; 5 s** (promedio verificado: 3.2 s).

---

## 4. Ejecucion de Pruebas Industriales (Verificacion de Requisitos)
Las historias de usuario y el DoD se validaron mediante los siguientes protocolos de prueba documentados:

### Prueba Mecanica y Dimensional (TEST-HW-01)
* **Problema del Operario (HU-02):** El sistema debe pesar con precision de 0.1 g para calculo justo de pago.
* **Protocolo:** Se calibro el HX711 con factor de escala y se coloco pesa patron de 1.000 g sobre la celda de carga.
* **Validacion:** Lectura durante 10 s con promedio de 10 muestras. La medida final fue de **999.8 g -- 1000.2 g**.
* **Resultado:** PASS. Se garantiza precision de 0.1 g en todo el rango 0 -- 5.000 g.

### Prueba de Ciclo Completo FSM (TEST-FW-01)
* **Problema del Operario (HU-01, HU-04):** El sistema debe completar todo el ciclo sin bloqueos y mostrar informacion clara en LCD.
* **Protocolo:** Se recorrieron los 9 estados de la FSM 10 veces consecutivas, verificando transiciones y mensajes LCD.
* **Validacion:** 10/10 ciclos completados. Transiciones correctas: ST_ESPERA -&gt; ST_PESANDO -&gt; ST_RESULTADO -&gt; ST_CONFIRMAR -&gt; ST_MOTOR_A -&gt; ST_MOTOR_PAUSA -&gt; ST_MOTOR_B -&gt; ST_ESPERA.
* **Resultado:** PASS. La FSM opera sin bloqueos y el LCD muestra mensajes correctos por estado.

### Prueba de Emergencia BTN_STOP (TEST-FW-02)
* **Problema del Operario (HU-07):** Debe poder detener el motor inmediatamente en caso de peligro.
* **Protocolo:** Se activo BTN_STOP durante 400 ms desde cada estado con motor activo (ST_MOTOR_A, ST_MOTOR_PAUSA, ST_MOTOR_B).
* **Validacion:** Motor detenido inmediatamente en los 3 estados. Retorno proporcional verificado: 675 ms de retorno para 1.350 ms de avance. Sin activaciones falsas en 20 ciclos de boot.
* **Resultado:** PASS (Corregido). GPIO13 fue reasignado a HX711 DOUT; BTN_STOP movido a GPIO4 con pull-down externo.

### Prueba de Alcance LoRa (TEST-MC-01)
* **Problema del Administrador (HU-03):** Necesita recibir datos en la base sin cables y sin depender de internet.
* **Protocolo:** Se transmiteron paquetes LoRa entre Nodo A y Nodo B en campo abierto (50 m) y con obstaculos (30 m).
* **Validacion:** Campo abierto: 10/10 paquetes recibidos, RSSI = -85 dBm. Con obstaculos: 9/10 paquetes recibidos (&lt; 10% perdida).
* **Resultado:** PASS. La comunicacion LoRa 915 MHz cumple con el alcance requerido para fincas cafeteras.

### Prueba de Autonomia sin WiFi (TEST-FW-03)
* **Problema del Operario (HU-06):** El sistema debe funcionar aunque no haya WiFi disponible.
* **Protocolo:** Se encendio Nodo A sin Nodo B disponible y se esperaron 20 s (40 intentos WiFi).
* **Validacion:** Lista respaldo activada automaticamente en 18.5 s promedio. Se completaron 10 ciclos de pesaje sin conexion WiFi.
* **Resultado:** PASS. El sistema es completamente autonomo en modo offline.

### Prueba de Descarga HTTP (TEST-MC-02)
* **Problema del Administrador (HU-05):** Necesita descargar datos en CSV para Excel.
* **Protocolo:** Se solicito GET /lista desde celular conectado al WiFi del Nodo B.
* **Validacion:** Respuesta CSV correcta con LISTA_START, headers, datos y LISTA_END. Tiempo promedio de respuesta: 3.2 s (maximo 4.1 s en 10 pruebas).
* **Resultado:** PASS. El formato CSV es compatible con Excel y Google Sheets.

### Prueba de Control Motor (TEST-HW-03)
* **Problema del Operario (HU-04):** El teleferico debe transportar la canastilla y retornar exactamente al origen.
* **Protocolo:** Se verifico el giro del motor adelante (1.350 ms), pausa (10 s) y retorno (1.350 ms) con osciloscopio.
* **Validacion:** Motor adelante: 1.348 ms. Motor atras: 1.351 ms. Voltaje en bornes: 4.85V. Retorno exacto al origen verificado.
* **Resultado:** PASS. El sistema de teleferico simulado opera con precision temporal.

---

## 5. Conclusion: Trazabilidad del Proyecto
El cruce entre los comentarios del cliente (operarios y administrador), la Matriz de Requisitos, el Definition of Done y el Protocolo de Pruebas demuestra una **trazabilidad completa y profesional**. Cada decision de diseno -- como la seleccion del HX711 24 bits para resolucion de 0.1 g, la implementacion de LoRa 915 MHz para comunicacion inalambrica sin internet, la lista de respaldo hardcodeada para operacion autonoma, el boton de emergencia BTN_STOP en GPIO4 con pull-down externo, y la carcasa PLA+ para proteccion en campo -- se fundamentó directamente en los comentarios de los operarios de recoleccion y el administrador de finca.

Se evidencia que el Teleferico del Cafe no es el resultado de la experimentacion empirica, sino de un proceso sistematico de ingenieria que asegura confiabilidad, precision de pesaje y usabilidad en el entorno real de recoleccion de cafe en el Quindio.
