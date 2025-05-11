# Goofy Gobblets

**Goofy Gobblets** est une réinterprétation stratégique et amusante du jeu classique de gobblets, où des pièces de tailles différentes peuvent en manger d'autres. Il y a 3 modes de jeu disponible, joueur contre joueur, joueur contre ia et ia contre ia !

---

##  Introduction

Le plateau est une grille 4x4, chaque joueur possède des pièces de différentes tailles qu'il peut poser à son tour. L'objectif est d'aligner 4 pièces d'une meme couleur avant l'adversaire.

---

## 🎮 Modes de jeu

Lorsque vous lancez le jeu, un menu principal s’affiche pour choisir le mode :

1. **Joueur vs Joueur**
2. **Joueur vs Goofybot (IA)**
3. **Goofybot vs Goofybot**

---

## 🕹️ Contrôles

- Le plateau est numéroté pour suivre le placement de vos pieces.
- Lors de votre tour, suivez les instructions dans le terminal :
  - Sélectionnez le type de coup à jouer
  - Sélectionnez la pièce à jouer
  - Indiquez la position souhaitée selon la numérotation affichée.

---

## IA et niveaux de difficulté

Le mode Goofybot propose trois niveaux d’intelligence :

-  **Facile** : Réagit au placement et au controle du terrain.
-  **Moyen** :  Réagit au controle du terrain mais également aux menaces possibles.
-  **Difficile** : Réagit au controle du terrain, aux menaces possibles, aux fourchettes possible et affine le score    de position des pieces.

---

##  Compilation et Exécution

### Compilation :
```bash
make
```
Un exécutable `GOOFY_GOBBLERS` sera généré.

### Lancement :
```bash
./GOOFY_GOBBLERS
```

### Nettoyage :
```bash
make clean   # Supprime les objets compilés
make fclean  # Supprime les objets + l'exécutable
make re      # Recompile tout
```

---

## 📂 Structure du projet

```
includes/         → Fichiers headers
srcs/             → Code source principal
main.cpp          → Point d’entrée
Makefile          → Compilation
README.md         → Ce fichier
```

---

## 👥 Auteurs

- 👨‍💻 Développement : Martin Trullard && Ismaël Bouarfa
- 🤖 IA & stratégie : Martin Trullard && Ismaël Bouarfa
