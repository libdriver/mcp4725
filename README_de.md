[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MCP4725

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mcp4725/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der MCP4725 ist ein stromsparender, hochgenauer, einkanaliger, gepufferter 12-Bit-Digital-Analog-Wandler (DAC) mit Spannungsausgang und nichtflüchtigem Speicher (EEPROM). Sein integrierter Präzisions-Ausgangsverstärker ermöglicht es ihm, einen analogen Ausgangshub von Schiene zu Schiene zu erreichen.
Die DAC-Eingangs- und Konfigurationsdaten können vom Benutzer mithilfe des I2C-Schnittstellenbefehls in den nichtflüchtigen Speicher (EEPROM) programmiert werden. Die nichtflüchtige Speicherfunktion ermöglicht es dem DAC-Gerät, den DAC-Eingangscode während der Abschaltzeit zu halten, und der DAC-Ausgang ist sofort nach dem Einschalten verfügbar. Diese Funktion ist sehr nützlich, wenn das DAC-Gerät als unterstützendes Gerät für andere Geräte im Netzwerk verwendet wird. Das Gerät enthält eine Power-On-Reset (POR)-Schaltung, um ein zuverlässiges Einschalten zu gewährleisten, und eine integrierte Ladungspumpe für die EEPROM-Programmierspannung. Die DAC-Referenz wird direkt von VDD getrieben. Im Powerdown
Modus kann der Ausgangsverstärker so konfiguriert werden, dass er eine bekannte Ausgangslast mit niedrigem, mittlerem oder hohem Widerstand darstellt. Der MCP4725 verfügt über einen externen A0-Adressbit-Auswahlstift. Dieser A0-Pin kann mit VDD oder VSS der Anwendungsplatine des Benutzers verbunden werden. Der MCP4725 verfügt über einen zweiadrigen I2C. kompatible serielle Schnittstelle für Standard- (100 kHz), schnellen (400 kHz) oder Hochgeschwindigkeitsmodus (3,4 MHz). Der MCP4725 ist ein ideales DAC-Gerät, wenn Designeinfachheit und geringer Platzbedarf erwünscht sind, und für Anwendungen, bei denen die Einstellungen des DAC-Geräts während der Abschaltzeit gespeichert werden müssen. Das Gerät ist in einem kleinen 6-Pin-SOT-23-Gehäuse erhältlich. MCP4725 wird in der Sensorkalibrierung, Servosteuerung mit geschlossenem Regelkreis, tragbaren Instrumenten mit geringem Stromverbrauch, PC-Peripheriegeräten und Datenerfassungssystemen verwendet.

LibDriver MCP4725 ist ein MCP4725-Treiber mit vollem Funktionsumfang, der von LibDriver gestartet wurde. Er bietet eine DAC-Ausgabe und eine Lesefunktion für DAC-Ausgabewerte. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver MCP4725-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver MCP4725 IIC.

/test enthält den Testcode des LibDriver MCP4725-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver MCP4725-Beispielcode.

/doc enthält das LibDriver MCP4725-Offlinedokument.

/Datenblatt enthält MCP4725-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

#### example basic

```C
#include "driver_mcp4725_basic.h"

uint8_t res;

res = mcp4725_basic_init(MCP4725_ADDR_A0_GND);
if (res != 0)
{
    return 1;
}

...

res = mcp4725_basic_write(1.2f);
if (res != 0)
{
    mcp4725_interface_debug_print("mcp4725: write failed.\n");
    (void)mcp4725_basic_deinit();

    ...
    
    return 1;
}

...

(void)mcp4725_basic_deinit();

return 0;
```

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/mcp4725/index.html](https://www.libdriver.com/docs/mcp4725/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.