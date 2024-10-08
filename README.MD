# Petit précis sur les branches Git
### main
Branche principale, elle ne doit recevoir que du code propre et prêt à l'usage.
Ça ne doit pas être la branche la plus active niveau commits.
Par ailleurs ajouter un "tag" à chaque commit (ex: v1.0, v1.1...) permet de se repérer plus facilement.
C'est la branche de prod en résumé.
### develop (ici nommées llabonde & apetitco)
Nos branches pour avancer les features sur lesquelles on travaille. Lorsque l
Lorsque la feature sur laquelle on travaille est prête à être incorporée, on peut merge sur la main.
### Pourquoi deux branches ?
- Pour séparer notre travail en cours et les avancées.
- On pourrait avoir une branche "feature" qui émane des "develop" et qui merge sur ces mêmes branches mais ça rajouterait de la complexité inutile.


# Sources
https://nvie.com/posts/a-successful-git-branching-model/
https://pubs.opengroup.org/onlinepubs/9699919799/utilities/contents.html
