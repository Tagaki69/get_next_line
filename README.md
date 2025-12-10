# get_next_line 📖

## 🎯 Description

Fonction de lecture ligne par ligne depuis un descripteur de fichier. Utilise des variables statiques pour maintenir l'état entre les appels et gérer efficacement la mémoire avec un buffer configurable. Projet fondamental pour comprendre la gestion de fichiers, les variables statiques et l'allocation mémoire dynamique en C.

## 🚀 Fonctionnalités principales

### 📋 Lecture séquentielle
- **Une ligne par appel** - Retourne la ligne complète incluant le `\n` (sauf EOF)
- **Gestion EOF** - Retourne `NULL` en fin de fichier ou en cas d'erreur
- **Buffer dynamique** - Taille configurable via `-D BUFFER_SIZE=n` (défaut: 42)
- **Optimisation mémoire** - Lit uniquement les données nécessaires

### ⚙️ Version bonus
- **Multi-descripteurs** - Gestion simultanée de plusieurs fd avec tableau statique
- **Variables statiques uniques** - Une seule variable statique pour tous les fd
- **Support jusqu'à 1024 fd** - Limitation système respectée

## 📁 Structure du projet

### 🗂️ Fichiers obligatoires
- **`get_next_line.c`** - Fonction principale et logique de lecture
- **`get_next_line_utils.c`** - Fonctions utilitaires (ft_strlen, ft_strjoin, etc.)
- **`get_next_line.h`** - Prototypes et définitions

### ⭐ Fichiers bonus
- **`get_next_line_bonus.c`** - Version multi-fd avec tableau statique
- **`get_next_line_utils_bonus.c`** - Utilitaires pour la version bonus
- **`get_next_line_bonus.h`** - Header bonus avec MAX_FD = 1024

## 📝 Aperçu des fonctions

### 🎯 Fonction principale
- **`get_next_line(int fd)`** - Point d'entrée, gère la variable statique et orchestre la lecture

### ⚙️ Fonctions auxiliaires
- **`read_and_update_stash()`** - Lit BUFFER_SIZE octets et concatène au stash
- **`extract_line_from_stash()`** - Extrait une ligne complète (jusqu'à '\n') du stash
- **`update_stash_after_extraction()`** - Mise à jour du stash après extraction d'une ligne
- **`ft_free()`** - Fonction de nettoyage et gestion d'erreurs

### 🔧 Utilitaires string
- **`ft_strlen()`** - Calcule la longueur d'une chaîne (NULL-safe)
- **`ft_strdup()`** - Duplique une chaîne de caractères
- **`ft_substr()`** - Extrait une sous-chaîne
- **`ft_strchr()`** - Cherche un caractère dans une chaîne
- **`ft_strjoin()`** - Concatène deux chaînes (gère s1 NULL)

### 🛠️ Compilation
```bash
# Version standard
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c

# Version bonus
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1000 get_next_line_bonus.c get_next_line_utils_bonus.c
```

## 🛠️ Contraintes 42

✅ **≤25 lignes/fonction** ✅ **≤80 colonnes** ✅ **Variables statiques uniquement** ✅ **Gestion mémoire stricte** ✅ **Norme 42**

### ❌ Interdictions
- ❌ **libft interdite** - Réimplémentation des fonctions nécessaires
- ❌ **lseek() interdit** - Lecture séquentielle uniquement
- ❌ **Variables globales** - Variables statiques uniquement

## 📚 Concepts clés appris

**Variables statiques** • **Gestion fichiers** • **Buffers dynamiques** • **Parsing par délimiteurs** • **Gestion multi-fd** • **Optimisation mémoire**

---

## ⚠️ Disclaimer 42

Ce dépôt est rendu public à des fins pédagogiques et pour présenter mon code. Le plagiat étant strictement interdit à 42, vous devez développer votre propre solution et être capable d'expliquer chaque ligne de votre implémentation.

*Projet réalisé dans le cadre du cursus 42* 🎓
