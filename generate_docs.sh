#!/bin/bash
# Script de génération de la documentation

echo "🔍 Génération de la documentation avec Doxygen..."

# Vérifier que Doxygen est installé
if ! command -v doxygen &> /dev/null; then
    echo "❌ Erreur : Doxygen n'est pas installé"
    echo "Installation : sudo apt-get install doxygen texlive-latex-base texlive-latex-extra"
    exit 1
fi

# Générer la documentation
doxygen Doxyfile

# Générer le PDF depuis LaTeX
if [ -d "docs/latex" ]; then
    echo "📄 Génération du PDF..."
    cd docs/latex
    make
    if [ -f "refman.pdf" ]; then
        cp refman.pdf ../Documentation_Projet_Borne.pdf
        echo "✅ PDF généré avec succès : docs/Documentation_Projet_Borne.pdf"
    else
        echo "⚠️  Erreur lors de la génération du PDF"
    fi
    cd ../..
fi

echo "✅ Documentation HTML disponible dans : docs/html/index.html"
