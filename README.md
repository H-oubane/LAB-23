# LAB 23 Android – LabJNISecurite

Application Android démontrant l'intégration de contrôles de sécurité natifs via JNI (Java Native Interface) pour détecter les environniments suspects (débogueur, instrumentation).

## Objectif
Comprendre et maîtriser :
- Intégration de code C++ natif avec JNI
- Compilation avec CMake et NDK
- Contrôle anti-debug avec ptrace
- Inspection mémoire via /proc/self/maps
- Journalisation native avec Logcat
- Adaptation de l'interface selon l'état de sécurité

## Fonctionnalités
- Détection de supervision via ptrace
- Inspection des modules suspects (Frida, Xposed, Magisk)
- Blocage conditionnel des fonctions natives
- Logs natifs dans Logcat

## Captures d'écran



### 1. Environnement suspect détecté
<img width="720" height="1600" alt="image" src="https://github.com/user-attachments/assets/8e7904f0-206a-4998-bca9-f0dd5b0d06aa" />


### 2. Logs natifs dans Logcat
<img width="1309" height="353" alt="image" src="https://github.com/user-attachments/assets/36efef53-2d33-4134-ba1c-662c50acb475" />

### 3. Débogage C++ avec point d'arrêt
<img width="1325" height="682" alt="image" src="https://github.com/user-attachments/assets/1a21bbb3-47f5-4a28-8779-45b5abd952bb" />

-Les deux scénarios donnent le même résultat car ptrace() est bloqué systématiquement sur le téléphone non rooté.



## Structure du projet
MonJNIDemo/

└── app/src/main/

    ├── java/com/example/monjnidemo/

       └── MainActivity.java

    ├── cpp/

       └── detection.cpp
   
       └── CMakeLists.txt
   
       └── native-lib.cpp

    ├── res/layout/

       └── activity_main.xml




## Pourquoi ce résultat sur mon téléphone ?

## Cause Explication
**ptrace()** bloqué	Android bloque systématiquement ptrace(PTRACE_TRACEME) sur les appareils non rootés pour des raisons de sécurité. La fonction retourne -1, ce qui est interprété comme une détection.
Sécurité Android	C'est une protection normale du système. Un téléphone rooté pourrait permettre ptrace, un téléphone non rooté le bloque.
**Conclusion** : Le résultat "ENVIRONNEMENT SUSPECT" sur un téléphone non rooté est normal et attendu. 


## Technologies utilisées
- Android Studio
- Java / C++
- JNI / NDK
- CMake / ptrace / Logcat


## Auteur
**H-oubane**
