## Documentation technique — laying-grass-Project

## Aperçu

Le projet est une application C++ (C++20) organisée selon une architecture MVC légère :
- Models : représentation des entités du jeu (Board, Tile, Player, Cell, Position...)
- Controllers : logique du jeu (flow des tours, règles, bonus)
- Views : interfaces utilisateur (CLI et Qt)
- Utils : utilitaires réutilisables (validation, calculs, random)

Le binaire principal est `laying_grass_Project` (généré par CMake). Le point d'entrée est `src/main.cpp` qui crée et exécute `Controllers::Game`.

## Arborescence importante

- `CMakeLists.txt` : configuration de compilation (C++20). Utilise `FetchContent` pour `nlohmann/json`.
- `include/` : fichiers d'en-têtes publics (controllers, models, utils, views).
- `src/` : implémentations correspondantes (.cpp).
- `tests/` : tests unitaires (fichiers `tests/test_*.cpp`) — CMake génère une cible `tests` si des tests sont détectés.
- `asserts/Tiles.json` : fichier de données copié dans le répertoire de build via `configure_file`.

## Points-clés d'implémentation

- `Controllers::Game` (`include/controllers/Game.h` / `src/controllers/Game.cpp`)
  - Responsable du cycle de vie du jeu : `start()`, `run()`, `end()`.
  - Méthodes internes : initialisation des joueurs, du plateau et de la pioche, génération de l'ordre de jeu, boucle des rounds, gestion des tours et application des bonus.

- `Models::Board` (`include/models/Board.h` / `src/models/Board.cpp`)
  - Représente la grille de jeu (`std::vector<std::vector<Cell>>`) et propose les méthodes de validation et de placement (`canPlaceTile`, `placeTile`, `checkBonusAcquisition`, etc.).

- `Models::Tile`, `Models::TileQueue`, `Models::Player`, `Models::Cell`, `Models::Position`
  - Structures centrales pour la représentation des tuiles, files de tuiles, joueurs, cellules et positions.

- `Views::UI_Cli` / `Views::UI_Qt`
  - UI_Cli expose les méthodes d'affichage et de saisie (affichage du plateau, du marché, demande de placement, etc.) ; elle est utilisée par le contrôleur pour toutes les interactions textuelles.

- `Utils` : `InputValidator`, `SquareCalculator`, `Random`, `KeyboardInput`
  - Fonctions d'aide : validations d'input, calcul de surfaces, génération pseudo-aléatoire, etc.

## Flux d'exécution (haut niveau)

1. `main()` crée une instance `Controllers::Game` et appelle `start()`, `run()`, `end()`.
2. `start()` appelle les routines d'initialisation : joueurs, plateau, pioche de tuiles, ordre de jeu.
3. `run()` boucle sur les rounds jusqu'à `maxRounds` ou condition de fin (`isGameOver()`), gère les tours et applique règles/bonus.
4. `end()` calcule les scores et détermine le gagnant.

## Compilation (Windows / PowerShell)

Le projet utilise CMake. Exemple minimal pour compiler en local :

```powershell
# depuis la racine du dépôt
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

Ensuite, lancer l'exécutable depuis le répertoire `build` :

```powershell
# si l'exécutable est placé à la racine du build
.\laying_grass_Project.exe
```

Notes :
- CMake configure `asserts/Tiles.json` pour être copié dans le répertoire de build (fichier de ressources).
- La dépendance `nlohmann/json` est récupérée via `FetchContent` (aucune action manuelle normalement requise).

## Tests

Si des fichiers `tests/test_*.cpp` sont présents, CMake crée la cible `tests` et active les tests via `enable_testing()`.

Exécution des tests (depuis `build`) :

```powershell
ctest --output-on-failure
```

Ou lancer l'exécutable `tests` généré directement :

```powershell
.\tests.exe
```

## Format des données & configuration

- `asserts/Tiles.json` contient la configuration des tuiles. Le fichier est copié dans le répertoire de build au moment de la configuration CMake.

## Points d'extension recommandés

- Ajout d'une IA : créer un module `ai/` avec une interface `IAgent` et implémenter des stratégies (greedy, minimax simplifié, heuristiques).
- Nouvelles UI : `Views::UI_Web` (HTTP/REST ou WebSocket) ou amélioration de `UI_Qt`.
- Persistences / Replays : sérialiser l'état des rounds (JSON) dans `saves/` pour relecture.

## Contrat rapide (API publique & attentes)

- Entrées/Sorties principales : `Controllers::Game::run()` exécute la logique; `Views::UI_Cli` fournit les interactions; `Models::Board::placeTile` valide et place des tuiles.
- Forme des données : `Tile`, `Player`, `Position` sont passés par référence/pointeur selon les responsabilités. Les méthodes retournent `bool` ou listes de `Position` pour indiquer les bonus acquis.

## Cas limites et conseils de test

- Entrées invalides : vérifier `InputValidator` pour empêcher valeurs hors bornes et couleurs dupliquées.
- Plateau hors-bords : `Board::isInsideBoard` doit être utilisé avant `getCell`.
- Concurrence : actuellement mono-thread — si vous parallélisez (p. ex. IA asynchrone), protéger l'accès à la pioche et au plateau.

## Documentation générée (optionnel)

- Pour documenter l'API C++, vous pouvez ajouter un `Doxyfile` et exécuter Doxygen pour générer de la doc HTML à partir des en-têtes `include/`.

## Ressources utiles

- Fichier CMake principal : `CMakeLists.txt`
- Entrée : `src/main.cpp`
- En-têtes principaux : `include/controllers/Game.h`, `include/models/Board.h`, `include/views/UI_Cli.h`

## Checklist avant PR

- [ ] Les modifications sont compilables localement (C++20)
- [ ] Les tests restent verts (si présents)
- [ ] Ajouter des tests unitaires pour toute nouvelle logique métier

---

Si vous voulez, je peux :
- générer une version Doxygen de la doc,
- ajouter des diagrammes d'architecture (PlantUML) dans `docs/`,
- créer des exemples d'exécution (scripts PowerShell) pour la CI.
