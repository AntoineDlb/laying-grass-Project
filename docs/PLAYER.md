Fichier: `docs/PLAYER.md`



Courte description : documentation joueur complète en français — instructions simples pour jouer depuis CLion (ou en lançant l'exécutable).



```markdown

\# Guide joueur — Laying Grass



\## Avant de lancer

1\. Ouvrir le projet dans CLion.

2\. Dans la configuration d'exécution : `Run | Edit Configurations` → cocher \*\*Emulate terminal in output console\*\* pour que les saisies clavier fonctionnent depuis CLion.

3\. Vous pouvez aussi lancer directement `cmake-build-debug/laying\_grass\_Project.exe` depuis l'explorateur Windows.



\## Démarrage

\- Au lancement, le jeu demande :

&nbsp; - le nombre de joueurs,

&nbsp; - puis le nom et la couleur de chaque joueur.

\- Suivre les invites affichées en console.



\## Déroulement général

\- Le jeu se joue en rounds (par défaut 9).

\- L'ordre de jeu est tiré au sort au début.

\- À chaque tour, le joueur courant :

&nbsp; - voit la tuile actuelle,

&nbsp; - peut la faire tourner/retourner,

&nbsp; - choisit où la poser (ou utiliser un bonus / coupon).



\## Contrôles / touches (CLI)

\- Tourner la tuile :

&nbsp; - `r` : tourner sens horaire (right).

&nbsp; - `l` : tourner sens antihoraire (left).

&nbsp; - `f` : retourner / flip (si supporté).

\- Positionner la tuile :

&nbsp; - Entrer les coordonnées sous la forme `x y` (ex : `3 2`) pour la case d'ancrage de la tuile.

&nbsp; - Confirmer la pose si demandé par `y` / `n`.

\- Annuler / revenir :

&nbsp; - `c` : annuler la pose en cours (si disponible).

&nbsp; - `q` : quitter un menu (si proposé).



\## Exemples rapides d'entrée

\- Tourner puis poser : `r` puis `3 2` puis `y`

\- Poser sans tourner : `3 2` puis `y`



\## Coordonnées / indexation

\- Les indices sont généralement 0-based (cases 0..N-1). Si l'interface affiche des indices 1-based, suivre l'indication affichée à l'écran.

\- Vérifier toujours les invites avant de saisir.



\## Bonus (comportement et saisies)

\- `EXCHANGE` : +1 coupon d'échange. Pour l'utiliser, répondre `y` quand proposé.

\- `STONE` : place une pierre 1x1 — entrer `x y` quand demandé.

\- `STEAL` : voler une case :

&nbsp; - saisir l'ID du joueur cible,

&nbsp; - puis `x y` de la case à voler.

&nbsp; - Si la capture est valide la case passe sous votre contrôle.

\- Coupons d'échange :

&nbsp; - Si vous avez des coupons, vous pouvez ouvrir le marché (`y`) et choisir une tuile parmi les propositions en entrant son index (ex : `1`, `2`, ...).



\## Placement de tuile

\- L'interface affiche le plateau et la tuile candidate (orientation actuelle).

\- Indiquer `x y` pour l'ancrage. Si la pose est invalide, la pose échoue et la tuile est perdue pour ce tour (selon règles du jeu).

\- Certaines tuile(s) peuvent exiger une orientation particulière — utiliser `r`/`l`/`f` avant de valider.



\## Phase d'achat finale

\- Après la fin des rounds, chaque coupon non utilisé peut être converti en tuile 1x1 (GRASS) et posée immédiatement : répondre `y` / `n`, puis fournir `x y` pour la pose si `y`.



\## Condition de victoire

\- Le gagnant est le joueur ayant le plus grand carré continu de cases à son identifiant.

&nbsp; - Le score affiché correspond à la taille du côté du plus grand carré (ex : un carré de 3×3 donne la valeur `3`) et au nombre total de cases d'herbe.

\- Les égalités sont résolues selon les règles affichées en fin de partie (vérifier la sortie console).



\## Conseils pratiques

\- Si les saisies n'apparaissent pas dans CLion : vérifier `Emulate terminal in output console`.

\- Lire attentivement chaque invite (les menus indiquent les touches valides).

\- Utiliser les coupons au meilleur moment (marché vs achat final).

\- Tester une pose sur une petite grille pour s'entraîner aux orientations et coordonnées.



Fin.

```



