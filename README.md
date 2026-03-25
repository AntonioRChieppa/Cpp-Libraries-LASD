# Algoritmi e Strutture Dati - Librerie in C++

Questo repository contiene l'implementazione da zero di diverse strutture dati fondamentali e algoritmi avanzati in C++. Il progetto è stato sviluppato come prova d'esame per il corso universitario di "Laboratorio di Algoritmi e Strutture Dati" (LASD).

**Autore:** Antonio Renato Chieppa  
**Matricola:** N86005121  
**Votazione conseguita:** 28/30  

---

## 🎯 Obiettivo del Progetto
Il progetto mira a costruire una libreria personalizzata e robusta, sfruttando appieno le potenzialità del C++ moderno. L'intera architettura è basata sulla **programmazione generica (Template)** e fa un uso estensivo della **Move Semantics** per ottimizzare le prestazioni e la gestione dinamica della memoria, evitando memory leak e copie inutili (es. *Copy-and-Swap idiom*).

Il lavoro è suddiviso in due librerie principali (Esercizio 1 ed Esercizio 2), strutturate a partire da classi puramente astratte (interfacce) fino ad arrivare alle implementazioni concrete.

---

## 📁 Struttura del Progetto

### Esercizio 1: Contenitori di Base e Strutture dati
La prima parte si concentra sulle strutture dati lineari e sui set, partendo da una solida gerarchia di classi astratte (`Container`, `Traversable`, `Mappable`, ecc.) che definiscono i comportamenti standard (come `Map`, `Traverse`, `PreOrder`, `PostOrder`).

| Struttura Dati | Descrizione e Dettagli Implementativi |
| :--- | :--- |
| **Vector** | Implementazione di un array dinamico ridimensionabile con accesso random in $O(1)$. |
| **List** | Implementazione di una lista concatenata singola (Singly Linked List) con puntatori a `head` e `tail` per ottimizzare gli inserimenti. |
| **SetVec** | Implementazione di un Set basato su un **Array Circolare**. Gestisce espansione/contrazione dinamica e utilizza la ricerca binaria in $O(\log n)$ per le operazioni di ricerca, inserimento e determinazione di successori/predecessori. |
| **SetLst** | Implementazione di un Set basato su lista concatenata, mantenuta ordinata. Particolarità dell'implementazione è la **simulazione di una ricerca binaria** sfruttando i **puntatori a puntatore** (`Node**`), che ottimizzano le logiche di inserimento e rimozione permettendo la modifica diretta dei collegamenti. |

### Esercizio 2: Heap e PQHeap (Code con priorità)
La seconda parte estende le strutture lineari per creare alberi e code di priorità basate su Heap.

| Struttura Dati | Descrizione e Dettagli Implementativi |
| :--- | :--- |
| **HeapVec** | Implementazione di un Max-Heap basato su `Vector`. Include funzioni per il ripristino delle proprietà dell'heap (`Heapify`) e l'algoritmo di ordinamento in-place **HeapSort** in $O(n \log n)$. |
| **PQHeap** | Coda di priorità (Priority Queue) implementata estendendo `HeapVec`. Permette inserimenti, estrazione del massimo (`TipNRemove`) e variazione di priorità (`Change`) mantenendo le performance tipiche dell'heap logico. |

---

## ⚙️ Dettagli Tecnici Rilevanti
* **C++ Moderno:** Uso di `std::move`, riferimenti r-value (`&&`) e qualificatori `noexcept` per costruttori e assegnamenti di spostamento.
* **Ricerca Binaria con Puntatori a Puntatore:** Implementazione di una logica di ricerca avanzata all'interno delle liste (`SetLst`) avvalendosi di puntatori doppi per manipolare agilmente i nodi senza variabili d'appoggio superflue.
* **Memoria Dinamica:** Gestione rigorosa dei distruttori e dell'allocazione tramite `new` e `delete[]`.
* **Compilazione:** Gestione tramite `Makefile` personalizzato per l'automazione dei processi di build e test.

---
