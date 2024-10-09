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

## 0. Initialisation
À son lancement, un shell exécute et lit ses fichiers de configuration.  
Bon, pour notre mini.s.hell ça n'est pas demandé, mais au moins, 
vous avez l'info.  
Accessoirement, c'est ici que l'on peut être amené à vérifier si l'on dispose
d'un tty ou non.

## 1. L'interprétation
### 1.0 La lecture
> Y'a vraiment besoin d'élaborer ?  
> Bon, s'il y a besoin, voici quelques infos ! En vrai, lire une ligne ça peut  
> paraître simple mais en C c'est une autre paire de manches.    
> Pour les étudiants de 42 ça devrait très vite faire penser à un projet lorsque  
> je parle de *lire des lignes*, suivez mon regard.  
>  Oui oui, je parle de ***get_next_line***
### 1.1 Le parsing
Avant de pouvoir s'amuser à exécuter des commandes, créer des fichiers,
faire des redirections, il faut s'assurer que la ligne de commande.s envoyée
est recevable. On effectue donc une analyse de ladite ligne de commande.

#### 1.1.1 L'analyse lexicale (lexing)
Le lexer va prendre notre chaîne de caractères et la découper en tokens
(c'est-à-dire en mots).

#### 1.1.2 L'analyse syntaxique (parsing)
Le parser va, quant à lui, prendre les tokens que le lexer a créé pour créer
une table de commande selon une grammaire.
### 1.2 L'exécution
Une fois que la string a été parsée, on exécute les commandes avec les options
et/ou arguments qui ont été fournis.
```c
int ms_launch(char **args, char **envp)
{
    pid_t   pid;
    pid_t   wpid;
    int     status;
    
    pid = fork();
    if (pid == 0)
    {
        // Child process
        if (execve(args[0], args, envp) == -1)
        {
            perror("mini.s.hell");
            exit (EXIT_FAILURE);
        }
        else if (pid < 0)
        {
            // Error forking
            perror("mini.s.hell");
        }
        else
        {
            // Parent process
            while (!WIFEXITED(status) && !WIFSIGNALED(status))
                wpid = waitpid(pid, &status, WUNTRACED);
        }
    }
    return (1);
}
```
Bon, certains malandrins noteront que cette fonction s'appelle ms_launch()
et non pas ms_execute(), la raison c'est les ~~protéines~~ **builtins**
#### 1.2.1 Les builtins
Dans un shell on peut soit exécuter des commandes en passant un nom de commande
(qui sera ensuite cherchée dans le PATH), un chemin relatif ou un chemin absolu.  
Mais pour certaines commandes qui sont utilisées souvent, il est d'usage de les
incorporer directement au programme[^1].

> [!tip]
> Dans notre cas voici les builtins qui doivent être inclus:
> - `cd` seulement avec un chemin relatif ou absolu
> - `echo` avec l'option `-n`
> - `env` sans options ni arguments
> - `exit` sans options
> - `export` sans options
> - `pwd` sans options
> - `unset` sans options

Ça peut donc être intéressant d'avoir un tableau  qui répertorie tous
les builtins afin de pouvoir checker si on nous envoie une commande "externe" ou
un builtin ! En parallèle avoir ceci :

```C
int (*builtin_func[]) (char **) = {&ms_cd, &ms_echo, &ms_env};
```
Je sais, je sais... cette ligne est HORRIBLE. Oui, moi aussi, j'ai cru faire un
AVC au début. Pourtant, elle est sensée, je vais la décortiquer rien que pour
vos beaux yeux !

Bon déjà, qu'est-ce que l'on a sous les yeux ?  
↳ Ceci est un *tableau* de pointeurs de fonctions.
> [!warning]
> Oui, c'est bizarre de voir `int` au début de la déclaration, mais je
> vais l'expliquer tout de suite ! :)

- `int` : le type de variable retournée par les fonctions
- `builtin_func[]` : Ça normalement, vous reconnaissez, c'est un tableau !
- `(*builtin_func[])` : Et cette étrangeté bah... ça signifie que chaque élément
du tableau est un pointeur de fonction !
- `(char **)` : Et enfin ça, c'est pour préciser que chaque fonction prend un
tableau de chaînes de caractères.

> [!tip]
> Pour les curieux, un tableau de tableaux de pointeurs de fonction aurait cette
> syntaxe :  
> `int  (*array_of_array[][]) (char **)` (évidemment les types d'arguments
> et de return sont arbitraires ici)

---

Bon avec tout ça on a de quoi écrire une fonction `ms_execute()` !  
Alors, aux fourneaux !

```C
int ms_execute(char **args)
{
    int i;
    
    if (args[0] == NULL)
        return (1);
    while (i < ms_num_builtins())
    {
        if (ft_strcmp(args[0], builtin_str[i]) == 0)
            return (*builtin_func[i](args));
        i++;
    }
    return (ms_launch(args));
}
```
Ce joli petit bout de code vérifie juste si l'on doit utiliser un builtin,
sinon on utilise `ms_launch()` pour exécuter la commande.

---

```c
void    mini.s.hell(void)
{
    char    *line;
    char    **args;
    int     status;
    
    status = 1;
    while (status)
    {
        printf("%s", PROMPT);               // Afficher le prompt
        line = ms_read_line();              // Lire la ligne
        args = ms_split_line();             // Tokenisation
        status = ms_execute(args);          // Exécution de.s commande.s
        free(line);
        free(args);
    }
}
```

## 2. Sortie du programme
Une fois que l'utilisateur a fini d'utiliser le shell et qu'il souhaite le quitter,
le programme exécute ses fonctions pour se finir, libérer la mémoire et se clore.

```c
int main(int argc, char *argv[])
{
    // Charger les fichiers de configuration si besoin.
    
    // Rentrer dans la boucle.
    mini_s_hell();
    
    // Nettoyer avant de quitter.
    
    return (EXIT_SUCCESS);
}
```

# Annexe
## Liste des includes (parce que y'en a une floppée)
```c
# include <curses.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
```
(Normalement la liste est exhaustive, je confirmerai à la fin du projet)
> [!warning]
> `stdio.h` doit être incluse avant `readline/readline.h` & `readline/history.h`
>car FILE est défini dans `stdio.h` ![^2]

# Sources

### Git
- [A successful git branching model](https://nvie.com/posts/a-successful-git-branching-model/)

### Généralités
- [42Docs - minishell](https://harm-smits.github.io/42docs/projects/minishell)
- [Normes POSIX](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/contents.html)
- [Write a shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)

### Lexing / Parsing
- [Writing your own shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [Parsing expressions by precedence climbing](https://eli.thegreenplace.net/2012/08/02/parsing-expressions-by-precedence-climbing)
- [Abstract Syntax Tree - Wikipedia](https://en.wikipedia.org/wiki/Abstract_syntax_tree)

[^1]: ["Any of the standard utilities may be implemented as regular built-in
utilities within the command language interpreter"](https://pubs.opengroup.org/onlinepubs/9799919799/nframe.html)
[^2]: ["if you encountered this error: error: unknown type name 'FILE' FILE *outf;
In your header file! you need to put stdio.h file before readline/readline.h and readline/history.h file
because FILE is defined in stdio.h"](https://github.com/achrafelkhnissi/minishell)
