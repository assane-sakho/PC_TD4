###Exercice 1 : Conditions de concurrence et exclusion mutuelle
- Question 1 : Il n'y a pas de section critique lors de l'allocation ou de la libération de ressources disponibles. On modifie de façon incohérente le nombre de ressources disponibles.
- Question 2 : 
    - 1 : **Chaque processus intègre la section critique suivante {request(m), utilisation de m ressources, release(m)}**
        - Avantages : Il n'y a qu'un seul processus qui utilisera la ressource critique donc il n'y a pas d'incohérence.
        - Inconvénients : Cela peut être bloquant pour les autres processus; Section critique importante.
        <pre>
            P(S);  
                request m  
                Utiliser m  
                release m
            V(S);
        </pre>
    - 2 : **Chaque processus fait appel à deux sections critiques séparées : {request(m)} et {release(m)}**
        - Avantages : Plusieurs processus peuvent demander et relâcher la ressource critique; Section critique plus petite
        - Inconvénients : Peut bloquer les autres processus si la ressource demandée n'est pas encore disponible; Création de famine.
            
         <pre>
              P(S);  
                  request m  
              V(S);
          </pre>
              
         <pre>
              P(S);  
                  release m
              V(S);
          </pre>
          
###Exercice 2 : le paradigme du producteur consommateur
<pre>
  P(S);  
      Produire message
      Ecrire message dans le tampon N s'il y a de la place
  V(S);
</pre>
    
<pre>
    P(S);  
        Récupérer message
        Afficher messagew
    V(S);
</pre>
              
                   