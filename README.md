# **Negociation App**

## **Présentation du Projet**
Le projet "NegociationApp" est un projet visant à simuler des négociations entre un acheteur et un ou plusieurs négociateurs. Pour cela, nous avons développé un système qui comprend plusieurs éléments.  

Le projet inclut une interface utilisateur avec quatre différents menus :  
1. **Paramètres** : un menu où il est possible de configurer tous les paramètres d'une négociation.  
2. **Boutique** : un espace où l'on peut sélectionner les produits souhaités.  
3. **Chat** : une section où il est possible de suivre ou relire les négociations.  
4. **Garage** : un espace pour gérer les objets achetés.  
5. **Vente** : une fonction pour revendre les objets déjà achetés.  

Cela permet une expérience complète pour simuler et expérimenter les différentes étapes d'une négociation.

Voici l'énoncé original de S. Aknine:

Nous utiliserons des modèles de négociation automatique pour la mise en place de sites marchands intelligents. Chaque site dit vendeur” propose plusieurs items ou produits avec des indications sur les propriétés des items (ex. prix min,…). Un utilisateur peut spécifier, un site dit “acheteur”, l’item qu’il recherche, ses propriétés ainsi que les contraintes et les préférences associées à cet item. Le site acheteur se chargera alors de mener les négociations automatiques avec les sites vendeurs proposant cet item. Le travail demandé consiste à modéliser les différents comportements de négociation automatique pour la vente et l’achat des items. Nous définirons les protocoles d’interactions et de négociation correspondants. Nous implémenterons et testerons l'ensemble des mécanismes à proposer.

---

## **Tutoriel d'installation**

### **0. Pour executer la version fourni**
```bash
cd build/Desktop_Qt_6_8_0-Debug
./projet-informatique-sa7
```
### **1. Prérequis**
Avant de commencer, assurez-vous que les outils suivants sont installés sur votre système :
- **Qt6** (Widgets, Multimedia)
- **CMake** (version 3.10 ou supérieure)
- **Ninja** (ou un autre générateur compatible CMake)
- Un compilateur C++ prenant en charge le standard C++17 :
  - GCC (Linux)
  - Clang (macOS)
  - MSVC (Windows)

### **2. Installation des librairies nécessaires**
#### **Sous Linux :**
```bash
sudo apt update
sudo apt install build-essential qt6-base-dev qt6-tools-dev-tools cmake ninja-build qt6-multimedia-dev
```

#### **Sous macOS :**
Assurez-vous que **Homebrew** est installé, puis exécutez :
```bash
brew install qt6 cmake ninja
```

#### **Sous Windows :**
1. Installez **Qt6** via le [Qt Online Installer](https://www.qt.io/download-qt-installer).
2. Ajoutez `qmake` et les binaires Qt au `PATH`.
3. Installez **CMake** et **Ninja** depuis [cmake.org](https://cmake.org/) et [Ninja GitHub](https://github.com/ninja-build/ninja/releases).

### **3. Compilation**
1. Clonez le projet depuis le dépôt Git :
   ```bash
   git clone https://github.com/alanlecaps/NegociationApp.git
   cd projet-informatique-sa7
   ```
2. configurez le projet :
   ```bash
   rm -r build
   mkdir build
   cd build
   ```
   Si vous connaisez pas le chemin pour votre installation QT:
   ```bash
   find / -type d -name "gcc_64" 2>/dev/null`
   ```
   Example : /home/loko/Qt/6.8.0/
   ```bash
   cmake .. -G Ninja -DCMAKE_PREFIX_PATH=/home/loko/Qt/6.8.0/
   ```
   
3. Compilez le projet :
   ```bash
   ninja
   ```

### **4. Exécution**
1. Lancez l'exécutable depuis le répertoire `build` :
   ```bash
   ./projet-informatique-sa7
   ```

---

## **Structure du Projet**
Le projet est organisé en deux parties principales : **backend** et **frontend**. Voici une explication de chaque dossier :

### **1. Backend**
Gère la logique métier, les calculs et le traitement des données.
- **`backend/src/`** : Contient les fichiers source C++ pour le backend.
  - Exemples :
    - `BoiteAuLettres.cpp` : Gère la communication entre utilisateurs.
    - `Acheteur.cpp` : Modélise le comportement d’un acheteur.
    - `Threads_var.cpp` : Gère les threads nécessaires pour le traitement asynchrone.
- **`backend/include/`** : Contient les fichiers d'en-tête associés.

### **2. Frontend**
Gère l'interface utilisateur et l'interaction utilisateur.
- **`frontend/src/`** : Contient les fichiers source C++ pour l'interface utilisateur.
  - Exemples :
    - `MainWindow.cpp` : Fenêtre principale de l'application.
    - `Parametres.cpp` : Fenêtre des paramètres utilisateur.
    - `StartScreen.cpp` : Écran d'accueil.
- **`frontend/include/`** : Contient les fichiers d'en-tête pour le frontend.
- **`frontend/ui/`** : Fichiers `.ui` conçus avec **Qt Designer** pour définir les interfaces utilisateur graphiques.

### **3. Fichiers Racine**
- **`main.cpp`** : Point d’entrée principal du programme.
- **`CMakeLists.txt`** : Script de configuration pour CMake.
- **`README.md`** : Documentation du projet.

---

