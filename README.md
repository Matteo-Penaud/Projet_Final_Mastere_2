# Projet fin d'études Mastere 2 : Kit WATIHOUSE
Le kit domotique WATIHOUSE est un système complet et sécurisé offrant une solution pratique pour la
gestion et le contrôle d'une maison intelligente. Il comprend une centrale de contrôle intégrant à la
fois le Bluetooth et le Wi-Fi, permettant une connectivité sans fil polyvalente, ainsi que différents
modules intelligents et connectés au système

Dans les dossiers `/modules` et `/qt` vous trouverez les codes sources associés aux différents appareils 

# Mise en place d'un module 
- Cloner le dépot sur votre appareil local
- Ouvrir le projet dans un IDE (STM32CubeIDE, IAR...)
- Brancher la STM32L476RG (ou autre carte de ST en vérifiant la configuration matérielle)
- Flasher la carte
-> Le module est prêt à l'emploi !

# Mise en place de la centrale
- Précompiler une cross-toolchain arm32 contenant les bibliothèques Qt :
    - cloner Yocto, avec les layers meta-qt5 et meta-raspberrypi
    - créer une configuration de compilation pour raspberrypi3 ("machine" dans le fichier yocto/conf/local.conf)
    - générer la chaine de cross-compilation (bitbake meta-toolchain-qt5)
    - configurer QtCreator avec cette chaine de compilation
- Cloner ce dépôt sur la machine de compilation
- Ouvrir qt/l'envoyerProjet_Master_Qt.pro dans QtCreator, préalablement configuré
- Compiler l'application et la transférer sur une Raspberry pi3
- Ouvrir l'appication sur la cible

# Manuel d'utilisation

Ce manuel guide l’utilisateur à travers les étapes simples pour la mise en place et l’utilisation du kit
WATIHOUSE. Une fois ces étapes terminées, le kit est prêt à être utilisé.
Note : les manipulations réelles peuvent varier à la suite de mise à jour du système.

## Contenu du kit :
```
- Centrale WATIHOUSE
- Câble d’alimentation de la centrale
- Module QDV
- Câble d’alimentation du module QDV
```

## Préparation du kit
1. Brancher la centrale à l’aide du câble d’alimentation fourni à l’arrière de la centrale
2. Brancher l’autre extrémité du câble d’alimentation à une prise secteur standard
3. Patienter le temps du démarrage du système.
4. L’écran d’accueil s’affiche. La centrale est alors prête à être utilisée  

## Ajout d’une nouvelle pièce
Depuis l’écran d’accueil de la centrale, sélectionner l’option « Nouvelle pièce » pour créer un nouvel espace et choisir un nom pour cette pièce.

![image](https://github.com/Matteo-Penaud/Projet_Final_Mastere_2/assets/72444888/2196e271-39a8-40e3-9734-63361f08471b)

## Ajout d’un module dans une pièce
1.	Accéder à une pièce.
   
![image](https://github.com/Matteo-Penaud/Projet_Final_Mastere_2/assets/72444888/11189f1b-adfd-4a99-a8a6-4f38de1aa8d3)

2.	Choisir l’option « Ajouter un module »
   
![image](https://github.com/Matteo-Penaud/Projet_Final_Mastere_2/assets/72444888/1a9034c5-fa00-4c75-a0e6-625dbbac7928)

![image](https://github.com/Matteo-Penaud/Projet_Final_Mastere_2/assets/72444888/5a687838-b191-456f-8692-7c62ad181344)

3.	Lorsque l’interface le demande, approcher le module de la surface NFC de la centrale jusqu’à que l’appairage soit détecté par la centrale.
   
![image](https://github.com/Matteo-Penaud/Projet_Final_Mastere_2/assets/72444888/76fb595a-944b-4c0f-b643-3eda82c5f5c8)

4.	Une fois que l’appairage est réussi, une notification à l’écran de la centrale apparait. Confirmer l’appairage en sélectionnant « Valider » sur l’écran.
5.	Le module est désormais ajouté.
   
![image](https://github.com/Matteo-Penaud/Projet_Final_Mastere_2/assets/72444888/13255cba-159e-490d-ae54-5a55f08bfe53)

## Personnalisation d’une pièce et de ses modules
1.	Sélectionner une pièce à personnaliser
2.	Cliquer sur le nom de la pièce pour accéder aux différentes options de personnalisation : 
•	Nom de la pièce
•	Ordre des modules
•	Nom des modules
•	Options des modules

## Vue d’ensemble des modules connectés
Cliquer sur le bouton BLE. Les modules connectés au système sont alors affichés.

![image](https://github.com/Matteo-Penaud/Projet_Final_Mastere_2/assets/72444888/ffd73db1-b9ab-4ece-b8a2-89a58f99fc1c)

![image](https://github.com/Matteo-Penaud/Projet_Final_Mastere_2/assets/72444888/b6a5b5bb-15c8-4d26-93b6-454e0a60c2f1)

Ici se trouvent les caractéristiques détaillées de connexion des différents équipements appairés à la centrale en fonction des pièces configurées.

## Consulter les données
1.	Sélectionner une pièce

![image](https://github.com/Matteo-Penaud/Projet_Final_Mastere_2/assets/72444888/807dbfae-1f37-41ab-8904-c4b010846c6e)

2.	Consulter les données du module souhaité

![image](https://github.com/Matteo-Penaud/Projet_Final_Mastere_2/assets/72444888/8b188130-e469-492a-93d3-857c91de467a)

## Paramètres de la centrale
Sélectionner le bouton des paramètres de la centrale 

![image](https://github.com/Matteo-Penaud/Projet_Final_Mastere_2/assets/72444888/8aa9282f-150b-4f55-b41b-ac8207e7a1b7)

Différentes options de personnalisation sont alors disponibles pour la centrale :
- Choix du thème clair/sombre
- Activation/Désactivation du Wi-Fi
- Variation de luminosité
- Mode Ne pas déranger













