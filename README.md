ESP32 | LED-Steuerung
Projektbeschreibung
Dieses Projekt dient dazu, den ESP32 besser zu verstehen und seine vielseitigen Funktionen zu erkunden.
Es ermöglicht die Steuerung einer LED-Diode über ein selbst gehostetes WLAN, ohne dass ein externes Netzwerk benötigt wird.
So können Anfänger und Fortgeschrittene die Grundlagen von Access Points, Webservern und der LED-Steuerung auf dem ESP32 erlernen.
________________________________________
Features
•	Steuerung einer LED über einen Webbrowser. 
•	ESP32 startet als Access Point mit eigener SSID und Passwort. 
•	Einfaches Setup über die Arduino IDE. 
•	Perfekt zum Lernen der Grundlagen von ESP32 WLAN-Programmierung und Webservern. 
•	Keine externe Internetverbindung notwendig. 
________________________________________
Technologien
•	Programmiersprache: C++ 
•	Plattform: Arduino IDE 
•	Libraries: 
o	WiFi.h – Verbindung und Verwaltung von WLAN auf dem ESP32 
o	WebServer.h – Einrichtung eines einfachen Webservers zur Steuerung der LED 
________________________________________
Installation / Setup
1.	Arduino IDE installieren: https://www.arduino.cc/en/software 
2.	ESP32-Bibliothek in der Arduino IDE installieren: 
o	Datei → Voreinstellungen → Zusätzliche Boardverwalter-URLs:
https://dl.espressif.com/dl/package_esp32_index.json 
o	Werkzeuge → Board → Boardverwalter → "ESP32" suchen → Installieren 
3.	Den Projektcode öffnen und auf den ESP32 hochladen. 
________________________________________
Nutzung / Beispiele
1.	Den ESP32 an eine ausreichende Stromquelle anschließen (z. B. USB-Netzteil mit mindestens 500 mA). 
2.	Der ESP32 startet automatisch als Access Point: 
o	SSID: ESP32-LED-AP 
o	Passwort: 12345678 
3.	Mit diesem WLAN verbinden. 
4.	Im Browser die Adresse http://192.168.4.1 eingeben. 
5.	Die LED über die angezeigten Buttons steuern (Ein/Aus). 
Hinweis:
•	Wenn der ESP32 nicht genügend Strom erhält, kann das WLAN instabil sein oder gar nicht starten. 
•	Dieses Setup funktioniert komplett ohne Internetzugang. 
________________________________________
Erweiterungsmöglichkeiten
•	Steuerung mehrerer LEDs über mehrere Buttons. 
•	PWM-Funktion für dimmbare LEDs hinzufügen. 
•	Integration von Sensoren, um LED-Aktionen automatisch auszulösen. 
•	Zugriff auf den Webserver über ein Smartphone oder Tablet. 
________________________________________
Lizenz
Dieses Projekt steht unter der MIT-Lizenz.
Berechtigungen:
•	Nutzung, Kopieren, Modifizieren, Zusammenführen, Veröffentlichen und Verteilen des Codes. 
Bedingung:
•	Der ursprüngliche Autor muss genannt werden. 
Haftungsausschluss:
•	Der Code wird „wie besehen“ bereitgestellt, ohne Garantie jeglicher Art.

