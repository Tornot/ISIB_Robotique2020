#ifndef GLOBAL_STRUCT
#define GLOBAL_STRUCT

struct Coordinates//coordonees en float //next est la coord que l'on veut atteindre // actual est la coord actuelle, à l'instant où on fait les calculs
{
    float coordX;//On ne peut normalement pas initialiser les structures ici. Logique: On déclare mais on ne défini pas de variable, donc on alloue pas de mémoire donc on ne peut pas donner sa valeur.
    float coordY;
    float coordZ;
};

extern struct Coordinates nextCoordinates;
//struct Coordinates actualCoordinates = {0.0, 0.0, 0.0};
//struct Coordinates tempCoordinates = {0.0, 0.0, 0.0};

#endif
