# 21sh

## Version Francaise

21sh est un projet qui vous fait créer un shell sommaire mais fonctionnel. Il est plus complet que minishell puisque il contient les redirections,
les pipes et d'autres améliorations générales.

### -Fonctionnalitées

####    Builtins
- echo [POSIX]
- env
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

## English Version

21sh is a project that makes you cr21sh is a project that makes you create a summary but functional shell. It is more complete than minishell since it contains the redirections,
pipes and other general improvements.

### -Features

####    Builtins
- echo [POSIX COMPLIANT]
- env
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
