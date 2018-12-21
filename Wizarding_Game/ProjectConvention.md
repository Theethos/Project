# Convention de nommage
Toutes les variables, fonctions et classes doivent être écrites en anglais.

Les **noms de variables** et de **fonctions** seront en cameUpperCase.

Les **fonctions** _privées_ dans un objet (c'est à dire qui ne doivent pas être appelées en dehors de l'objet) seront précédées d'un \_\_nomDeFonction.

Les **noms de classes** commenceront par une Majuscule.

# Convention de code
Il faut écrire une cartouche pour **chaque fonction** écrite en utilisant le pattern ci-dessous:  
"""  
Description de la fonction  

:param _param1_: description du paramètre attendu  
:type _param1_: type du paramètre attendu  

:param _param2_: description du paramètre attendu  
:type _param2_: type du paramètre attendu  

:return: description de ce qui est retourné par la fonction  
:rtype: type de ce qui est retourné  
"""  
def maFonction(param1, param2):


Il faut egalement écrire une cartouche pour **chaque classe** écrite en utilisant le pattern ci-dessous:    
\# Description rapide de la classe et de ses attributs  
\#  
\# attribut1 : type, description de l'attribut  
\# attribut2 : type, description de l'attribut  
\# attribut3 : type, description de l'attribut  
class MaClasse:

# Convention de gestion du dépôt Git
Pour **chaque tâche**, _une branche_ tirée de _develop_ sera créée et utilisée pour implémenter cette tâche.

Lorsque **la tâche est terminée**, la branche de la tâche doit être **fusionner** avec la branche _develop_.

Si **la tâche est validée** par l'ensemble du groupe et que la branche _develop_ est jugée stable, la branche _develop_ sera fusionnée avec la branche _master_
