# INF8775-tp2
## TODO
Backtrack dynprog
Verif dist
Refine greedy

Verfif que le greedy fait le retour au départ

Dire dans le rapport que l'espace mémoire pour la programmation dynamique peut être optimisée car on a pas besoin de garder toutes les distances. On a besoin que de l'ensemble des distances au niveau $n-1$. Pour des calculs sur des chemins de taille 4, pas besoin des résultats sur ceux de tailles 1 et 2.

### Prim
- Repr graph
- Prim
  - Avoir une liste des voisins de tous les noeuds et leurs distances aux noeuds
  - verifier pas cycle
  - Garder en mémoire quelles arrêtes ont été sélectionées
- Choisir une racine
- Faire le parcours en préordre