DECHAUX
HENO

# Commentaire général
Bon résultat malgré la petite équipe. Attention à certaines lacunes à compenser (détail dans NOTES.md sur le git).

## Programmation orientée objet
### Héritage $$3.5
Héritage appliqué correctement.

### Encapsulation $$1.5
Attention: Encapsulation quasiment pas utilisée !

### Fonctions virtuelles $$ 3.5
Les différents comportements des tours sont bien override par rapport à la classe de base.

### Utilisation de références et pas de copies inutiles $$3.5
Game est passé par référence. Mais peu d'utilisation des refs.

## Clarté du code
### Niveau d'abstraction cohérent $$3.25
A part la fonction `Game::UpdateAndDraw()` qui est assez haut niveau, le reste est très complexe à lire. Par exemple, la fonction `DrawGame` aurait mérité un découpage en sous-fonctions.
### Clarté des nommages (fonctions/variables) $$3.5
Nommage des variables plutôt correct.
Attention aux noms de certaines fonctions qui ne sont pas clairs. Une fonction doit commencer quasiment toujours par un verbe (Draw, Get, Update).
### Découpage des fichiers cohérent $$3
game.cpp est un peu le fourre-tout.

## Fonctionnalités
### Qualité du rendu $$3.75
Le résultat final est très bon, surtout sachant que vous n'étiez que 2.

### Absence de warning à la compilation $$5
OK
### Memory leaks $$4.5
Pas de leaks
### Crash $$3.5
Crash potentiel ligne 103, posTile peut être égal à 0, donc map.tile[posTile-1] est en dehors des limites.

## Présentation
### Commentaires $$3.5
Commentaires souvent utilisés
### Readme $$3.5
Correct mais un screenshot aurait été apprécié
### Norme de code $$4
OK, mais attention aux majuscules/minuscules pas cohérent sur certaines fonctions/variables.

## Bonus $$3
### Sons $$5
### Format de donnée (niveau, score) $$0
### Editeur de niveau $$0

## Git
### Qualité des messages $$4
Bonne qualité de message, mais certains sont trop abstraits (clean code, fix bug), il faut préciser de quoi il s'agit !
### Régularité des commits $$4
Commits assez constants

## Gestion de projet
### Utilisation des tâches GitLab $$4.5
Utilisées, 
### Bonne répartition des tâches $$3
Déséquilibrée ou non représentative

## Code review (divers)
Dans main.cpp, les `PlayMusicStream` sont appelés à chaque frame alors qu'ils devraient être appelés que ponctuellement.

