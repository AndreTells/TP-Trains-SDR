# TP Trains
groupe:
 - André Silva Telles
 - Gabriel Sousa Fontenele
 
# Pour compiler le code
make server
make train

obs: il faut changer les ips dans les defines du fichier train.c
 
# Pour éxecuter le code

./bin/server --ip << votre ip >>
./bin/train

obs: les programmes peuvent donner un output plus detaillée si le flag -v est
utilisé, ex:

./bin/server --ip << votre ip >> -v
./bin/train -v
