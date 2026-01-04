# projet_borne

## Documentation

Ce projet utilise Doxygen pour générer automatiquement la documentation à partir des commentaires dans le code.

### Prérequis
```bash
sudo apt-get install doxygen graphviz texlive-latex-base texlive-latex-extra
```

### Génération de la documentation

#### Méthode 1 : Script automatique
```bash
chmod +x generate_docs.sh
./generate_docs.sh
```

#### Méthode 2 : Makefile
```bash
make docs
```

#### Méthode 3 : Commande directe
```bash
doxygen Doxyfile
cd docs/latex && make
```

### Fichiers générés
- **PDF** : `docs/Documentation_Projet_Borne.pdf`
- **HTML** : `docs/html/index.html`

## Structure de la documentation

La documentation inclut :
- Description complète de toutes les fonctions
- Paramètres et valeurs de retour
- Diagrammes de dépendances (si Graphviz installé)
- Structure des fichiers et modules
- Liste des auteurs et dates
