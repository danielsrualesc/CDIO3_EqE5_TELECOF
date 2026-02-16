# Plantillas de Carpetas - Guía de Creación

## 🚀 Cómo Usar Este Documento

Este documento proporciona plantillas y ejemplos para crear la estructura completa del repositorio siguiendo el esquema definido.

## 1. Plantilla para 01_Gestion

### Paso 1: Crear la estructura
```bash
mkdir -p 01_Gestion/{Actas,BOM,Cronogramas}
```

### Paso 2: Crear README.md en 01_Gestion
```markdown
# Gestión del Proyecto TELECOF

## Contenido
- **Actas:** Registro de reuniones y decisiones
- **BOM:** Lista de materiales requeridos
- **Cronogramas:** Calendario y hitos del proyecto

## Responsable
[Nombre del Project Manager]

## Últimas Actualizaciones
- [Fecha]: [Descripción del cambio]
```

---

## 2. Plantilla para 02_Hardware

### Paso 1: Crear la estructura
```bash
mkdir -p 02_Hardware/{Datasheets,Mechanical,Source}
mkdir -p 02_Hardware/Source/{KiCad,Altium,Eagle}
mkdir -p 02_Hardware/Mechanical/{STL,DXF,CAD}
```

### Paso 2: Crear README.md en 02_Hardware
```markdown
# Hardware - TELECOF

## Especificaciones Técnicas
- **Tensión de operación:** 5V / 12V
- **Corriente máxima:** [Valor] mA
- **Conectores:** [Especificación]
- **Temperatura de operación:** [Rango]

## Componentes Principales
| Componente | Modelo | Cantidad | Datasheet |
|-----------|--------|----------|-----------|
| MCU | [Modelo] | 1 | [Archivo] |
| Sensor | [Modelo] | 2 | [Archivo] |

## Directorio Datasheets
Todos los PDFs de componentes están aquí. Descargar desde proveedores oficiales.

## Directorio Source
- **KiCad/:** Diseño principal (editable)
- **Altium/:** Alternativa profesional
- **Eagle/:** Alternativa económica

## Directorio Mechanical
- **STL/:** Para impresión 3D
- **DXF/:** Para corte láser
- **CAD/:** Archivos de diseño completo

## Responsable
[Nombre del Ingeniero de Hardware]
```

---

## 3. Plantilla para 03_Firmware

### Paso 1: Crear la estructura
```bash
mkdir -p 03_Firmware/{lib,src,build}
mkdir -p 03_Firmware/lib/{Arduino_libraries,C_libraries,Python_modules}
```

### Paso 2: Crear README.md en 03_Firmware
```markdown
# Firmware - TELECOF

## Requisitos de Compilación
- Arduino IDE v1.8.x o superior
- Librerías instaladas:
  - WiFi.h
  - [Otras librerías]

## Instalación de Librerías
```bash
# Opción 1: Mediante Arduino IDE
# Sketch → Include Library → Manage Libraries → Buscar [nombre]

# Opción 2: Manual
cp lib/Arduino_libraries/* ~/Arduino/libraries/
```

## Compilación

### Método 1: Arduino IDE
1. Abrir `src/main.ino` en Arduino IDE
2. Seleccionar placa: Tools → Board
3. Seleccionar puerto: Tools → Port
4. Click en Upload

### Método 2: Línea de comandos
```bash
arduino --board esp32:esp32:esp32 --port /dev/ttyUSB0 --upload src/main.ino
```

## Estructura del Código
- **main.ino:** Punto de entrada
- **config.h:** Configuraciones globales
- **sensors.ino:** Rutinas de sensores
- **communication.ino:** Protocolo de comunicación

## Responsable
[Nombre del Ingeniero de Software]
```

### Paso 3: Archivo plantilla para src/main.ino
```cpp
/*
 * PROYECTO: TELECOF - CDIO3
 * DESCRIPCIÓN: [Descripción breve]
 * AUTOR: [Tu nombre]
 * FECHA: [YYYY-MM-DD]
 * VERSIÓN: 1.0
 */

#include "config.h"

void setup() {
    Serial.begin(115200);
    delay(100);
    Serial.println("\n\nTELECOF Iniciando...");
    
    // Inicialización de hardware
    inicializar_sensores();
    inicializar_comunicacion();
    
    Serial.println("Sistema listo!");
}

void loop() {
    // Lógica principal
    leer_sensores();
    procesar_datos();
    enviar_datos();
    delay(100);
}
```

---

## 4. Plantilla para 04_Dossier

### Paso 1: Crear la estructura
```bash
mkdir -p 04_Dossier/{Manuales,Validación,Finales}
```

### Paso 2: Crear README.md en 04_Dossier
```markdown
# Documentación Final - TELECOF

## Índice Completo
1. [Manuales](#manuales)
2. [Validación](#validación)
3. [Documentos Finales](#documentos-finales)

## Manuales

### Manual de Usuario
- Instrucciones de instalación
- Operación básica
- Mantenimiento

### Manual Técnico
- Arquitectura del sistema
- Diagramas de bloques
- Especificaciones detalladas

### Guía de Troubleshooting
- Problemas comunes
- Soluciones
- Contacto de soporte

## Validación

### Reportes de Pruebas
- Resultados de pruebas unitarias
- Pruebas de integración
- Validación de requisitos

### Certificaciones
- Conformidad CE (si aplica)
- Certificados de calidad
- Reportes de seguridad

## Documentos Finales
- Resumen ejecutivo
- Conclusiones del proyecto
- Recomendaciones futuras

## Responsable
[Nombre del Responsable de Documentación]
```

---

## 5. Estructura de Directorios Completa (Referencia)

```
CDIO3_EqE5_TELECOF/
├── 01_Gestion/
│   ├── README.md
│   ├── Actas/
│   │   ├── Acta_2026-02-16_Kickoff.md
│   │   └── ...
│   ├── BOM/
│   │   ├── BOM_v1.0.xlsx
│   │   └── ...
│   └── Cronogramas/
│       ├── Gantt_Proyecto.xlsx
│       └── ...
│
├── 02_Hardware/
│   ├── README.md
│   ├── Datasheets/
│   │   └── (PDFs de componentes)
│   ├── Mechanical/
│   │   ├── STL/
│   │   ├── DXF/
│   │   └── CAD/
│   └── Source/
│       ├── KiCad/
│       ├── Altium/
│       └── Eagle/
│
├── 03_Firmware/
│   ├── README.md
│   ├── lib/
│   │   ├── Arduino_libraries/
│   │   ├── C_libraries/
│   │   └── Python_modules/
│   ├── src/
│   │   ├── main.ino
│   │   ├── config.h
│   │   ├── sensors.ino
│   │   └── ...
│   └── build/
│       └── (Archivos compilados)
│
├── 04_Dossier/
│   ├── README.md
│   ├── Manuales/
│   │   ├── Manual_Usuario.pdf
│   │   └── ...
│   ├── Validación/
│   │   ├── Reporte_Pruebas.pdf
│   │   └── ...
│   └── Finales/
│       └── ...
│
├── .gitignore
├── README.md
├── ARCHITECTURE.md
├── STRUCTURE_DIAGRAM.md
└── FOLDER_TEMPLATES.md
```

---

## 6. Checklist de Implementación

- [ ] Crear todos los directorios
- [ ] Crear README.md en cada carpeta principal
- [ ] Llenar información de responsables
- [ ] Actualizar .gitignore con patrones de cada carpeta
- [ ] Crear primeros archivos de cada sección
- [ ] Hacer commit inicial con la estructura
- [ ] Notificar al equipo sobre la nueva estructura
- [ ] Asignar permisos de escritura por módulo

---

## 7. Comandos Rápidos

### Crear todo de una vez
```bash
# En la raíz del repositorio
mkdir -p 01_Gestion/{Actas,BOM,Cronogramas}
mkdir -p 02_Hardware/{Datasheets,Mechanical/STL,Mechanical/DXF,Mechanical/CAD,Source/{KiCad,Altium,Eagle}}
mkdir -p 03_Firmware/{lib/{Arduino_libraries,C_libraries,Python_modules},src,build}
mkdir -p 04_Dossier/{Manuales,Validación,Finales}
```

### Crear archivo .gitignore actualizado
```
# Compilados
*.o
*.hex
*.elf

# IDEs
.vscode/
.idea/
*.swp

# Binarios grandes
*.bin

# Archivos temporales
*~
.DS_Store

# Específico de cada carpeta
03_Firmware/build/*.hex
02_Hardware/Source/*/[Cc]ache/
```

---

## 8. Notas Importantes

- Los README.md son **obligatorios** en cada carpeta principal
- Usar versionado en archivos críticos (v1.0, v1.1, etc.)
- Documentar cambios importantes en los commits
- Mantener la estructura limpia y ordenada
- Revisar regularmente que todo siga el esquema
