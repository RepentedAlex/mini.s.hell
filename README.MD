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
Même si ces lignes sont surtout pour mon acolyte et moi, il est possible qu'éventuellement (et je dis bien *éventuellement*) d'autres yeux curieux viennent parcourir ces dernières. Alors avant de coder son propre shell en C, il faut savoir comment ça marche à l'intérieur (la logique derrière est simple, c'est l'implémentation qui sera le coeur de vos mental breakdowns[^1]).

Malheureusement on ne peut pas expliquer le fonctionnement d'un shell seulement au travers de la magie, des protéines ou de la matière noire... donc il faudra lire encore un peu (beaucoup) !
## 0. Initialisation
À son lancement, un shell lit et exécute ses fichiers de configuration. Bon, pour notre mini.s.hell ça n'est pas demandé, mais au moins, vous avez l'info. Accessoirement, c'est ici que l'on peut aussi être amené à vérifier si l'on dispose d'un TTY ou non.

> [!warning] C'est quoi un TTY ?
> Pour faire très simple, lorsque vous donnez "à la main" vos commande au shell, vous utilisez le mode interactif de celui-ci au travers d'un [TTY](https://fr.wikipedia.org/wiki/Téléscripteur).
> Vous vous demandez donc sûrement dans quel cas on *n'utilise pas* de TTY et bien dans le cas d'un script qui exécute des tâches en arrière plan par exemple ! L'entrée viendra dans ce cas d'un fichier (le script) et non pas d'un TTY qui aurait traité vos entrées au clavier ! Dans d'autres cas il peut y avoir le lancement de notre shell via un pipe ou encore un session SSH sans terminal.

> [!tip]+ Non mais vraiment, c'est quoi un TTY ?
> La confusion autour des TTY vient du fait qu'à la base, les TeleTYpewriter (TTY) étaient des terminaux physiques permettant la communication à distance. Aujourd'hui on utilise des terminaux virtuels pour émuler les TTY, ce qui rend bien plus abstrait leur concept. Mais concrètement si vous disposez d'un port série, vous pouvez recréer un système de TTY physique !

## 1. L'interprétation
### 1.0 La lecture
Y a-t-il vraiment vraiment besoin d'élaborer ? Évidemment, voici donc quelques informations !
En soit, lire une ligne ça peut paraître simple, mais *en C* c'est une autre paire de manches. Pour les étudiants de 42 vous devriez très vite penser à un projet lorsque je parle de *lire des lignes*...

Oui oui, je parle bien de ***get_next_line***. Pourtant même si ça peut être tentant, il y a quelque chose que `readline()` a que `get_next_line()` n'a pas ~~à part les leaks~~, c'est la possibilité d'avoir un historique. Ça tombe bien, c'est une exigence du sujet !
#### 1.0.1 readline() et les fuites
```C
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char *buf = NULL;

	buf = readline("mini.s.hell-> ");
	printf("%s\n", buf);
	free(buf);
	return (0);
}
```
De toute évidence je n'ai pas écrit ce code car il était utile. Enfin, si, il *est* utile dans un sens. Si vous compilez ce programme éminemment basique (vous pourriez même enlever le printf()) et que vous le lancez sous Valgrind, préparez vous.
Mais vraiment, rien que ce simple programme va faire fuire une quantité **astronomique** de mémoire pour le (très) peu qu'il fait. Alors imaginez si vous appelez `readline()` *plusieurs* fois. :)

Vous devrez donc apprendre à faire des [suppression files](https://valgrind.org/docs/manual/manual-core.html#manual-core.suppress) pour Valgrind. <sub><sup>o:) (Oui, c'est un ange).</sup></sub>
> [!tip] Suppression files
> Ces fichiers permettent de demander à Valgrind de ne pas afficher certains warnings en suivant un certain set de règles.

Si `readline()` noie les fuites de mémoires qui seraient de *votre* faute et que, donc, vous ne corrigez pas ces fuites, **la faute sera sur vous**. Alors faites en sorte d'avoir un suppression file carré.
### 1.1 Le parsing
C'est super, vous avez lu la ligne de commande, elle est bien au chaud dans votre `char *buffer`, c'est maintenant que tous vos problèmes vont commencer[^2]. :)

Avant de pouvoir s'amuser à exécuter des commandes, créer des fichiers, faire des redirections... il faut s'assurer que la ligne de commande.s envoyée est recevable. On effectue donc une analyse de ladite ligne de commande.

#### 1.1.1 Petites vérifications de base
##### Bon nombre de guillemets
Dans la [Sainte-Bible](https://docs.google.com/spreadsheets/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/edit?gid=0#gid=0) il y a une teraflopée de tests ou on envoie des commandes avec un nombre impair de guillemets. Et bah bonne nouvelle, vu que nous ne sommes pas censés gérer ce cas (à date du 9/10/2024) et bien si l'on reçoit une ligne de commande qui n'est pas conforme de ce point de vue, c'est ciao !
#### 1.1.2 L'analyse lexicale (lexing)
Avant d'expliquer le fonctionnement de l'analyseur lexical, je vais rapidement définir ce qu'*est* une analyse lexicale.
##### Qu'est-ce que c'est ?
L'analyse lexicale, consiste à prendre une chaîne de caractère pour la convertir en une liste de symboles (tokens). Voilà, c'est juste ça !

Encore une fois, pour les étudiants de 42, si je parle d'une fonction qui prend une chaîne de caractère et qui en ressort une liste de chaînes de caractères, ça devrait faire **TIIILT** dans votre tête (c'est le fameux `ft_split()` qui vous aura fait suer en piscine). Et bien il vous serait utile de ressortir cet outil.
> [!warning]
> Alors `ft_split()` est certes super pratique, en revanche faites attention à pas faire les idiots lorsque vous rentrez dans des `"`ou des `'` !
> Il ne faut pas prendre en compte les espaces qui sont compris dans une paire de guillemets, donc ça serait bête de perdre les espaces contenus dans :
> `  il manque   "des   trucs  la,"    non????"  ` ! :)
> > Normalement vous devriez ressortir avec ces tokens là :
> > - `il`
> > - `manque`
> > - `des   trucs  la,`
> > - `non????`

Pour le programme, lire `|` (un pipe) est aussi anodin que de lire n'importe quoi d'autre. C'est donc à vous de lui expliquer que lorsqu'il tombe sur tel ou tel caractère, il doit créer un nouveau symbole.

Ainsi la ligne de commande :
`$> whereis ls | cat -e | cat -e > /tmp/bonjour`[^3]
Doit être découpée comme suit :
- `whereis`
- `ls`
- `|` -> token PIPE
- `cat`
- `-e`
- `|` -> token PIPE
- `cat`
- `-e`
- `>` -> token REDIR_O
- `/tmp/bonjour`

En guise d'exemple, la première node du lexer devrait ressembler à cela :
- `char *str` = "whereis"
- `t_tokens token` = 0
- `struct s_lexer *prev` = NULL
- - `struct s_lexer *next` = NULL (pointera sur le `ls`)
#### 1.1.3 L'analyse syntaxique (parsing)
C'est super, on a désormais un tableau de `t_tokens` rempli. Maintenant il faut transformer ces nodes en commandes.

L'analyseur syntaxique va donc itérer le long de la liste de symboles et à chaque fois qu'il tombera sur un de ces symboles : `|`, `<`, `<<`, `>`, `>>`, il prendra toutes les nodes précédentes pour créer une node `t_simple_command`

Dans notre cas, la première node de ce type ressemblera à ceci :
- `char **str` = {"whereis", "ls"}
-  `int (*builtin)(t_tools *, struct s_simple_cmds *)` = NULL(sinon un pointeur de fonction sur un builtin si c'est le cas)
- `int num_redir` = 0
- `char *heredoc_filename` = NULL
- `t_lexer *redir` = NULL
- `struct s_simple_commands *prev` = NULL
- `struct s_simple_commands *next` = NULL

Mais évidemment ce n'est pas tout, lors de l'analyse syntaxique, le programme va créer un [arbre de syntaxe abstrait](https://fr.wikipedia.org/wiki/Arbre_de_la_syntaxe_abstraite)

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
incorporer directement au programme[^4].

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
>car FILE est défini dans `stdio.h` ![^5]

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

[^1]: Vous serez sûrement amenés à retravailler souvent des bouts du programme. Parfois ces ravalements vous feront repartir de zéro sur certaines fonctionnalités. Ça sera frustrant mais l'apprentissage veut ça. Alors ne soyez pas durs avec vous-même et faites preuve de compréhension envers vo.tre.s mate.s <3
[^2]: Et encore, je parlais en général, l'implémenter en C en **devant** utiliser une fonction qui fuit autant qu'un pneu crevé c'est tout autre chose, HEIN **readline()** ? >:(
[^3]: Test tiré de la [Sainte-Bible](https://docs.google.com/spreadsheets/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/edit?gid=0#gid=0)
[^4]: ["Any of the standard utilities may be implemented as regular built-in
utilities within the command language interpreter"](https://pubs.opengroup.org/onlinepubs/9799919799/nframe.html)
[^5]: ["if you encountered this error: error: unknown type name 'FILE' FILE *outf;
In your header file! you need to put stdio.h file before readline/readline.h and readline/history.h file
because FILE is defined in stdio.h"](https://github.com/achrafelkhnissi/minishell)
