# FactSemiprime
An algorithm for semiprimes factorization.

Algoritmo per la fattorizzazione di semiprimi.
L'algoritmo prende in input (da file o da stdin) un intero semiprimo (prodotto di due numeri primi *p* e *q*) di dimensione arbitraria e ne restituisce (in un file di output e in stdout) la fattorizzazione.

**ATTENZIONE**: l'algoritmo impiega un tempo ragionevole SE E SOLO SE *p* e *q* sono vicini, poichè esegue esattamente ![Iterazioni](https://latex.codecogs.com/gif.latex?%28p&plus;q%29/2-%5Cleft%20%5Clceil%20%5Csqrt%7Bp*q%7D%20%5Cright%20%5Crceil)  iterazioni! Quindi per ![pqlontani](https://latex.codecogs.com/gif.latex?%5Cleft%20%7C%20p-q%20%5Cright%20%7C%5Cgg%200) l'algoritmo itererà per giorni/mesi/anni. 

Utilizza la libreria esterna GMP per la gestione dei numeri di dimensione arbitraria.
