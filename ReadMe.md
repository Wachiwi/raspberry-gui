# Projektarbeit Raspberry Pi - I²C-Daten mittels Qt-GUI anzeigen

## Aufgabenteil 2

Der zweite Aufgabenteil hat das Ziel, eine Anwendung mit grafischer Benutzerschnittstelle auf Basis der Qt-Bibliothek zu erstellen, welche eine Widget-Applikation zur Darstellung von Daten des I²C-Slaves, in Form eines SRF02 Ultraschallsensors, zu realisieren. Dabei liegt der Fokus auf der Darstellung, der in der Textdatei fortlaufend geschriebenen Daten des C-Programmes, über eine in C++ geschriebene QT-GUI-Anwendung. Zur Visualisierung soll ein zweidimensionales Diagramm der aufgenommen Werte des Ultraschallsensors mit Hilfe der Bibliothek QCustomPlot erstellt werden.

Die Anwendung soll auf dem ausgegebenen Raspberry Pi lauffähig sein (ARM-Architektur).

### Anforderungen

Um die Problematik der Schreib-/Lese-Synchronisation zu umgehen, wird immer der Wert der vorletzten Zeile der Textdatei visualisiert. Die gelesenen Werte des Ultraschallsensors sollen in der GUI-Anwendung graphisch ausgegeben werden, der neueste Wert zudem wenn möglich auch in einem Textfeld. Zur Visualisierung wird die Bibliothek QCustomPlot verwendet.

### Testprotokoll

- [x] C++: GUI Event-Handling
- [x] C++: Auslesen der Messdaten

### Screenshots

Screenshots sind im Verzeichnis `Screenshots` zu finden. Die Screenshots wurden via x11-Forwarding aufgezeichnet.
Es sollten folgende Dateien existieren:

- *Initial*: Dies Zeigt die Applikation nachdem sie gestartet wurde, im Initialzustand.
- *Selecting File*: Dies zeigt die Applikation, wenn auf "Visualize File" gedrückt wurde und eine Datei ausgewählt wird, die "überwacht" werden soll.
- *Reading File*: Dies zeigt die Applikation, während eine Datei überwacht wird.
