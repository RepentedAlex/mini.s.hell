# Petit précis sur les branches Git
## main
Branche principale, elle ne doit recevoir que du code propre et prêt à l'usage.
Ça ne doit pas être la branche la plus active niveau commits.
Par ailleurs ajouter un "tag" à chaque commit (ex: v1.0, v1.1...) permet de se
repérer plus facilement.
C'est la branche de prod en résumé.
> [!warning]  
> Pour merge sur le main il faut bien penser à `git checkout main` !!!  
> Si vous mergez en étant sur votre branche,
> vous mergerez le main sur votre branche !  
> Donc il faut d'abord checkout sur la branche qui "recevra".
## develop (ici nommées llabonde & apetitco)
Nos branches pour avancer les features sur lesquelles on travaille.
Lorsque la feature sur laquelle on travaille est prête à être incorporée,
on peut merge sur la main.
Par PITIÉ avant de push, faire la Norme :,)
## Pourquoi deux branches ?
- Pour séparer notre travail en cours et les avancées.
- On pourrait avoir une branche "feature" qui émane des "develop" et
- qui merge sur ces mêmes branches mais ça rajouterait de la complexité inutile.

# Bon c'est bien sympa, mais comment on fait un shell ?
Avant de coder son propre shell, il faut savoir comment ça marche à l'intérieur.
Malheureusement on ne peut pas expliquer le fonctionnement d'un shell au
travers de la magie, des protéines ou encore de la matière noire...
donc va falloir lire encore un peu !

## 1. Le parsing
Avant de pouvoir s'amuser à exécuter des commandes, créer des fichiers,
faire des redirections, il faut s'assurer que la ligne de commande.s envoyée
est recevable. On effectue donc une analyse de ladite ligne de commande.

### 1.1 L'analyse lexicale (lexing)
Le lexer va prendre notre chaîne de caractères et la découper en tokens
(c'est-à-dire en mots).

### 1.2 L'analyse syntaxique (parsing)
Le parser va, quant à lui, prendre les tokens que le lexer a créé pour créer
une table de commande selon une grammaire.

# Sources
- [A successful git branching model](https://nvie.com/posts/a-successful-git-branching-model/)
- [Normes POSIX](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/contents.html)

## Lexing / Parsing
- [Writing your own shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [Parsing expressions by precedence climbing](https://eli.thegreenplace.net/2012/08/02/parsing-expressions-by-precedence-climbing)
