# 21sh

## Version Francaise

21sh est un projet qui vous fait créer un shell sommaire mais fonctionnel. Il est plus complet que minishell puisque il contient les redirections,
les pipes et d'autres améliorations générales.

### -Fonctionnalitées


###    Raccourci clavier
```
- SIGNAUX :
Ctrl-D : Supprime en arrière lorsque le curseur se situe sur un caractère de l'entrée utilisateur
		 Quitte le shell lorsque l'entrée utilisateur est vide
Ctrl-C : vide l'entrée utilisateur et retourne le prompt

- AFFICHAGE:
Ctrl-A : Déplace le curseur en début de ligne
Ctrl-E : Déplace le curseur en fin de ligne
Ctrl-K : Coupe la ligne
Ctrl-L : Copie la ligne
Ctrl-P : Colle la ligne
Ctrl-B : Déplace le curseur d'un mot vers la gauche
Ctrl-N : Déplace le curseur d'un mot vers la droite
Ctrl-U : Déplace le curseur d'une ligne vers le haut
Ctrl-F : Déplace le curseur d'une ligne vers le bas
Les flèches s'utilisent logiquement.
```

###    Options du shell
```
[--help] Affiche l'aide du shell et quitte
[- l]    Permet de charger le fichier .historique dans le shell s'il existe
```
####    Builtins
- echo [POSIX]
```
[-n] N'imprime pas le '\n' après le dernier argument.
\a
Ecrit un <alert>.
\b
Ecrit un <backspace>.
\f
Ecrit un <form-feed>.
\n
Ecrit un <newline>.
\r
Ecrit un <carriage-return>.
\t
Ecrit un <tab>.
\v
Ecrit un <vertical-tab>.
```
- env [POSIX]
```
[--help] Affiche l'aide et quitte 
[-i]     Permet de passer l'environnement souhaité a un executable
[-v]     Active le mode verbose, avec des infos supplémentaires
[-0]     N'affiche pas de retour ligne lors de l'affichage des variables d'environnement
```
- setenv
```
usage: setenv VAR1=VALUE1 VAR2=VALUE2 ...
```
- unsetenv
```
usage: unsetenv VAR1 VAR2 ...
```
- exit [POSIX]
```
  Lorsqu'un argument numérique valide est spécifié, quitte avec la valeur passée
  Si plusieurs arguments sont spécifiés, un "Too many arguments" sera affiché.
  Si une valeur non numérique est spécifiée comme argument, le code de retour sera fixé à 255 et "Error: Too many arguments" sera affiché.
```
- cd [POSIX]
```
usage: cd chemin...
```
- redirections
```
>	redirige la sortie standard vers un fichier vide
<	redirige le fichier vers l'entrée standard
>>	redirige la sortie standard vers un fichier, en ajoutqnt le contenu a la fin
&>	redirige la sortie standard et la sortie d'erreur vers un fichier vide
j>	redirige le file descriptor j vers un fichier vide
j>>	redirige la sortie standard vers un fichier, en ajoutqnt le contenu a la fin
j>&	redirige le file descriptor j vers la sortie standard
>&k	redirige le ls sortie standard vers le file descriptor k
j>&k	redirige le file descriptor j vers le file descriptor k
j>&-	ferme le file descriptor j
j<&-	ferme le file descriptor j

exemple: cat existing_file non_existing_file > file1 2>&1
```
- pipe
```
exemple: ls | grep Makefile
```

## English Version

21sh is a project that makes you cr21sh is a project that makes you create a summary but functional shell. It is more complete than minishell since it contains the redirections,
pipes and other general improvements.

### -Features

### Keyboard shortcut
```
- SIGNALS:
Ctrl-D: Deletes backwards when the cursor is on a character in my user entry
		Exits the shell when the user entry is empty
Ctrl-C : empties the current buffer of the user entry and returns the prompt

- DISPLAY:
Ctrl-A : Moves the cursor to the beginning of the line
Ctrl-E : Moves the cursor to the end of the line
Ctrl-K : Cuts the line
Ctrl-L : Copies the line
Ctrl-P : Pastes the line
Ctrl-B : Moves the cursor one word to the left
Ctrl-N : Moves the cursor one word to the right
Ctrl-U : Moves the cursor one line up
Ctrl-F : Moves the cursor one line down
The arrows are used logically.
```

###    Shell options
```
[--help] Print shell help and exit
[- l]    Load .history file into the shell if it exist
```

####    Builtins
- echo [POSIX COMPLIANT]
```
[-n] Does not print '\n' after the last argument.

\a
Write an <alert>.
\b
Write a <backspace>.
\f
Write a <form-feed>.
\n
Write a <newline>.
\r
Write a <carriage-return>.
\t
Write a <tab>.
\v
Write a <vertical-tab>.
```
- env [POSIX]
```
[--help] Print help and exit
[-i]     Allow to pass custom environnement variables
[-v]     Activates the verbose mode, which display more informations
[-0]     Does not print new line when printing environnement variables
```
- setenv
```
usage: setenv VAR1=VALUE1 VAR2=VALUE2 ...
```
- unsetenv
```
usage: unsetenv VAR1 VAR2 ...
```
- exit [POSIX COMPLIANT]
```
  When a valid numeric argument is specified, exit with passed value
  If multiple arguments are specified, an too many arguments error will be printed
  If a non-numeric value is specified as argument, return code will be set to 255 and an "invalid arguments" error will be printed
```
- cd [POSIX COMPLIANT]
```
usage: cd path...
```
- redirections
```
>	redirects the standard output to an empty file
< 	redirects the file to the standard input
>> 	redirects the standard output to a file, adding the content at the end
&>	redirects the standard output and error output to an empty file
j> 	redirects the file descriptor j to an empty file
j>> 	redirects the standard output to a file, adding the content at the end
j>& 	redirects the file descriptor j to the standard output
>&k 	redirects the ls standard output to the file descriptor k
j>&k 	redirects the file descriptor j to the file descriptor k
j>&- 	closes the file descriptor j
j<&- 	closes the file descriptor j

example: cat existing_file non_existing_file > file1 2>&1
```
- pipe
```
example: ls | grep Makefile
```
