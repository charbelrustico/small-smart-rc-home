## **🏠 Projet Domotique Miniature Contrôlé par Bluetooth**

Ce projet utilise une carte Arduino Uno et un module Bluetooth (HC-05/06) pour simuler et contrôler à distance les fonctions de base d'une maison miniature : ventilation, éclairage intérieur et extérieur, et ouverture/fermeture d'une porte (ou fenêtre) via un servomoteur.

### **⚙️ Matériel Requis**

Ce projet nécessite les composants suivants :

* **Microcontrôleur :** Carte Arduino Uno  
* **Communication sans fil :** Module Bluetooth (HC-05 ou HC-06)  
* **Actionneurs :**  
  * 1 x Servomoteur simple (pour la porte/fenêtre)  
  * 1 x Module Relais (pour le ventilateur)  
  * 2 x LEDs (une pour l'intérieur, une pour l'extérieur)  
  * 2 x Résistances (adaptées aux LEDs, ex: 220 Ω)  
* **Alimentation & Gestion :**  
  * Protoboard (pour une gestion efficace des connexions et de l'alimentation)  
  * Batterie 9V avec *jacket* (pour alimenter l'Arduino)  
  * Ventilateur (alimenté par une source 12V externe, contrôlée par le Relais)  
  * Transformateur (pour convertir l'alimentation en 12V pour le ventilateur)

### **🔌 Schéma de Connexion et Broches**

Le code utilise les broches suivantes pour contrôler les différents composants :

| Composant | Broche Arduino | Variable dans le code (domo2.0.ino) | Rôle |
| :---- | :---- | :---- | :---- |
| **Ventilateur (Relais)** | 9 | pinMode(9, OUTPUT) | Contrôle l'activation/désactivation du Relais (et donc du ventilateur). |
| **Porte (Servomoteur)** | 13 | servo.attach(13) | Contrôle l'angle du servomoteur (ouverture/fermeture). |
| **Éclairage Extérieur** | A0 (Analogique) | D2 | Contrôle la LED extérieure (via analogWrite). |
| **Éclairage Intérieur** | A1 (Analogique) | D3 | Contrôle la LED intérieure (via analogWrite). |
| **Bluetooth RX** | 0 | Serial.read() | Réception des commandes du module Bluetooth (croisement obligatoire TX-\>RX). |
| **Bluetooth TX** | 1 | Serial.println() | Envoi de messages de confirmation vers le module Bluetooth (croisement obligatoire RX-\>TX). |

#### **Connexion Bluetooth (Règle TX/RX)**

Comme pour tout projet série, les broches de transmission (TX) et de réception (RX) doivent être croisées :

* **Arduino Broche 1 (TX)** ➡️ **Broche RX** du module HC-05  
* **Arduino Broche 0 (RX)** ➡️ **Broche TX** du module HC-05

### **🧠 Logique du Code et Commandes**

Le code écoute les commandes (caractères uniques) reçues via le port série à un débit de **9600 bauds**.

Le projet utilise un système de commandes en majuscule/minuscule pour activer (MAJUSCULE) ou désactiver (minuscule) chaque fonction.

| Commande | Caractère | Action sur le Système | Fonction dans le code |
| :---- | :---- | :---- | :---- |
| **Ventilation ON** | V | Démarre la ventilation (Relais sur LOW, car le relais est souvent actif LOW). | digitalWrite(9, LOW) |
| **Ventilation OFF** | v | Arrête la ventilation (Relais sur HIGH). | digitalWrite(9, HIGH) |
| **Porte Ouverture** | S | Fait tourner le servomoteur de 0° à 180°. | fermeture() |
| **Porte Fermeture** | s | Fait tourner le servomoteur de 180° à 0°. | ouverture() |
| **Lumière Ext. ON** | L | Allume la LED extérieure (pleine intensité 255). | analogWrite(D2, 255\) |
| **Lumière Ext. OFF** | l | Éteint la LED extérieure. | analogWrite(D2, LOW) |
| **Lumière Int. ON** | I | Allume la LED intérieure (pleine intensité 255). | analogWrite(D3, 255\) |
| **Lumière Int. OFF** | i | Éteint la LED intérieure. | digitalWrite(D3, LOW) |

**Note sur le Servomoteur :** Les fonctions ouverture() et fermeture() utilisent des boucles for avec un delay(25) pour créer une animation fluide du mouvement. L'implémentation actuelle **inverse** les noms : fermeture() ouvre la porte (0 à 180°) et ouverture() la ferme (180 à 0°).

### **🚀 Guide de Démarrage Rapide**

1. **Câblage :** Connectez tous les composants selon la table des broches, en respectant la connexion croisée TX/RX pour le Bluetooth.  
2. **Bibliothèques :** Assurez-vous d'avoir les bibliothèques **Servo.h** et **SoftwareSerial.h** installées (bien que SoftwareSerial.h soit incluse mais non utilisée dans le code actuel, elle est souvent requise pour les projets Bluetooth).  
3. **Téléversement :** Déconnectez le module Bluetooth des broches 0 et 1, puis téléversez le code domo2.0.ino sur votre Arduino Uno.  
4. **Connexion :** Reconnectez le module Bluetooth.  
5. **App Mobile :** Utilisez une application de terminal série Bluetooth (comme l'application **Serial Bluetooth Terminal** si elle permet d'envoyer les caractères spécifiques ci-dessus) pour vous connecter au module et envoyer les commandes.
