# TP1 Réseau et Sécurité

Author : François SUZEAU, bachelor's degree graduaded in computer science.

## How to use it
This project is only for Windows Environnement. The executable file is in the ``build/debug`` or ``build/release`` directory.
You have a Makefile at you disposal in the ``src`` directory. You can compile it with a debug option (``DEBUG=1``) or a release option (``DEBUG=0``).
+ At the launch a text is already use to encrypt (for now it is a french text). You have the possibility to use an english text or to enter your own text that you want to encrypt.

+ After that you have to enter a key

All special characters are taken into account. The ``é``, ``è``, ``ç``, ``à`` and the ``ù`` are transformed into ``e, e, c, a, ù`` respectively. All other are deleted from the message.
All letters in upper case are transformed into lower case and there is no space.

+ After calculation your message is shown encrypted.


<!-- Réponse aux questions 9 et 10 de la partie 2 sur le test de Friedman 

9) Puisque nous avons un texte Tr composé seulement de lettres miniscules il y a donc 26 lettres possible.
    Obtenir une lettre donnée est de 1/26 donc obtenir une pair idendique est égale à 26 * (1/26)^2 = 1/26 = 0.0385


10) On obtient des résultats différent pour l'anglais car la ditributions des lettres n'est pas les mêmes que pour le Francais par exemple.
    A noter aussi que cette probabilité peut varier aussi selon la source du texte (ex : La Disparition de Georges Perec)

-->

English random text : 
``During this last day, however, little by little the gangways were cleared, the scaffoldings were taken down, the fly-wheel cranes disappeared, the fixing of the engines was accomplished, the last screws and nails were driven in, the reservoirs filled with oil, and the last slab rested on its metal mortise. This day the chief engineer tried the boilers.``

French random text :
``Internet n’est pas le seul réseau. Il existe un autre réseau plus performant. Je ne t’apprendrais rien en te disant qu’Internet a été crée par l’armée Américaine dans un but militaire. Internet n’était que le prototype. Un autre réseau a été créé pour les militaires. Complètement indépendant d’Internet. Tirant des leçons du premier réseau, le petit frère d’Internet est devenue un grand frère.``

+ We first calculate the size of the key by the most common divisor method (if it is pair we let the user to choose his length among all the divisor previously find)

+ The Friedman method is called and also calculate a key length

+ We let the choice to the user which key length he want to use

+ We ask to the user to specified in which language the original text is written

+ Then the frequency analysis begin : at each iteration the program shows the selection of letter of each subsequence at each position and then it shows the frequency appearance and then the frequency appearance in a certain language.

+ You choose wicht letter in the subsequence and then which letter in the frequency appearance language table.

+ The program does his calculation and show to you the result

+ When the frequency analysis is done we use the key you create and test it to the encrypted text. If the decrypted text is the same as the original a surprise may come in ..

+ Then we start the Baeries method (with the key length previously choose) : You have to choose a likely word strictly greater than the key

+ The program shows you at each iteration the word he find with this method and let you the choice to continue or to stop

+ Then it shows to you the substring containing the key you might be think it is ...