# TP1 Réseau et Sécurité

Author : François SUZEAU, bachelor's degree graduaded in computer science.

## How to use it
This project is only for Windows Environnement. The executable file is in the ``build/debug`` or ``build/release`` directory.
You have a Makefile at you disposal in the ``src`` directory. You can compile it with a debug option (``DEBUG=1``) or a release option (``DEBUG=0``).
+ At the launch a first demand is made. You have to enter the text that you want to encrypt.
+ After that you have to enter a key

All special characters are taken into account. The ``é``, ``è``, ``ç``, ``à`` and the ``ù`` are transformed into ``e, e, c, a, ù`` respectively. All other are deleted from the message.
All letters in upper case are transformed into lower case and there is no space.

+ After calculation your message is shown encrypted and then decrypted.


<!-- Réponse aux questions 9 et 10 de la partie 2 sur le test de Friedman 

9) Puisque nous avons un texte Tr composé seulement de lettres miniscules il y a donc 26 lettres possible.
    Obtenir une lettre donnée est de 1/26 donc obtenir une pair idendique est égale à 26 * (1/26)^2 = 1/26 = 0.0385


10) On obtient des résultats différent pour l'anglais car la ditributions des lettres n'est pas les mêmes que pour le Francais par exemple.
    A noter aussi que cette probabilité peut varier aussi selon la source du texte (ex : La Disparition de Georges Perec)

-->

English random text : 
``During this last day, however, little by little the gangways were cleared, the scaffoldings were taken down, the fly-wheel cranes disappeared, the fixing of the engines was accomplished, the last screws and nails were driven in, the reservoirs filled with oil, and the last slab rested on its metal mortise. This day the chief engineer tried the boilers.``