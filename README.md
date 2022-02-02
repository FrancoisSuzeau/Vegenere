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