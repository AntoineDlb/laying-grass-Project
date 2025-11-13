# Guide joueur — Laying Grass

Ce document explique comment lancer et jouer à Laying Grass (interface CLI), avec les commandes principales et quelques conseils pratiques.

## Avant de lancer

1. Ouvrez le projet dans CLion ou compilez via CMake (voir `CMakeLists.txt`).
2. Si vous jouez depuis CLion : dans *Run | Edit Configurations*, cochez *Emulate terminal in output console* pour que les saisies fonctionnent correctement.
3. Vous pouvez aussi lancer l'exécutable depuis le dossier de build (ex. `cmake-build-debug/laying_grass_Project.exe` ou `build\laying_grass_Project.exe`).

## Démarrage

Au lancement, suivez les invites : nombre de joueurs, puis pour chaque joueur son nom et sa couleur.

## Déroulement d'une partie

- Le jeu se déroule en rounds (par défaut 9) avec un ordre de jeu tiré au sort.
- À chaque tour le joueur voit la tuile courante, peut la faire tourner/retourner, puis choisit où la poser ou utiliser un bonus.

## Commandes (interface CLI)

- Flèches directionnelles (← ↑ → ↓) : déplacer la tuile candidate sur le plateau
- Espace : valider la pose courante
- r : tourner la tuile sens horaire (right)
- l : tourner la tuile sens antihoraire (left)
- f : retourner la tuile (flip), si supporté
- y / n : confirmer ou refuser certaines actions (marché, conversions)
- c : annuler l'opération courante (si disponible)
- q : quitter un menu (si proposé)

Exemples rapides :
- Positionner la tuile puis valider : (←/→/↑/↓) pour déplacer → `Espace` pour confirmer
- Tourner avant de valider : `r` → utiliser les flèches → `Espace`

## Coordonnées

La plupart des placements de tuiles s'effectuent via les flèches et la touche `Espace` (pas de saisie `x y`).
Certaines actions (par ex. `STONE`, `STEAL` ou conversions finales) demandent encore des coordonnées sous la forme `x y` ; dans ce cas les indices sont généralement 0-based (cases 0..N-1).

## Bonus (utilisation)

- EXCHANGE : donne un coupon d'échange; répondez `y` pour ouvrir le marché et choisissez une tuile par son index.
- STONE : place une pierre 1×1 — saisissez `x y` quand demandé.
- STEAL : voler une case — saisissez l'ID du joueur cible puis `x y` de la case à voler.

## Placement de tuiles

- L'interface affiche la tuile candidate avec son orientation courante.
- Déplacez la tuile candidate sur la grille à l'aide des flèches directionnelles (← ↑ → ↓).
- Utilisez `r` / `l` / `f` pour ajuster l'orientation de la tuile avant validation.
- Appuyez sur `Espace` pour valider définitivement la pose ; si la pose est invalide, la tentative échoue et la tuile peut être perdue pour ce tour selon les règles.

Remarque : si une action particulière demande explicitement des coordonnées (ex. pierre 1×1 ou vol), saisissez `x y` lorsque l'invite l'exige.

## Phase d'achat finale

Après la fin des rounds, chaque coupon non utilisé peut être converti en tuile GRASS 1×1 et posée immédiatement en répondant `y` puis en fournissant `x y`.

## Condition de victoire

Le gagnant est le joueur ayant le plus grand carré continu de cases à son identifiant (la valeur affichée correspond à la taille du côté du plus grand carré et au total des cases d'herbe).

## Conseils & dépannage

- Si les saisies n'apparaissent pas dans CLion : vérifiez *Emulate terminal in output console*.
- Lisez toujours les invites : elles précisent les touches valides et le format attendu.
- Utilisez les coupons avec parcimonie (marché vs achat final) et entraînez-vous sur une petite grille pour maîtriser les orientations.

---

Si tu veux, je peux :
- formater ce guide en sections imprimables, ajouter des captures d'écran ou une version en anglais,
- ou générer un court tutoriel interactif (exemples pas à pas) dans `docs/TUTORIAL.md`.


\- Tourner puis poser : `r` puis `3 2` puis `y`



