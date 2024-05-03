/**
@file main.cpp 
@brief test d'uso della classe Set templata
**/

#include <iostream>
#include <cassert>
#include "set.hpp"

//------------------ FUNTORI ---------------------------------

/**
  @brief Funtore di uguaglianza tra tipi interi

  Valuta l'uglianza tra due interi. 
*/
struct equal_int {
  bool operator()(int a, int b) const {
    return a==b;
  }
};

/**
  @brief Funtore predicato 

  Ritorna true se il valore intero passato è pari 
*/
struct is_even {
  bool operator()(int a) const {
    return (a % 2 ==0);
  }
};

/**
  @brief Funtore per l'uguaglianza tra stringhe.

  Funtore per l'ugagianza tra stringhe. La valutazione e' fatta
  lessicografica.
*/
struct equal_string {
  bool operator()(const std::string &a, const std::string &b) const {
    return (a==b);
  } 
};

// --------------- METODI FONDAMENTALI ----------------------------

/**
  @brief Test dei metodi fondamentali

  Test dei metodi fondamentali
*/
void test_metodi_fondamentali() {
  std::cout<<"TEST METODI FONDAMENTALI DEL DATA SET"<<std::endl;

   Set<int, equal_int> setI;  // ctor default

   setI.add(5);
   setI.add(8);
   setI.add(1);
   setI.add(4);

   std::cout << setI << std::endl;

   Set<int, equal_int> new_set(setI);  // copy constructor

   std::cout << new_set << std::endl;

   Set<int, equal_int> new_set2;

   new_set2 = setI; // operator=

   std::cout << new_set2 << std::endl;

} // ~Set()

// -------------------- TEST DEI TIPI -------------------------------
/**
  @brief Test del Set di dati istanziato su interi

  Test del Set di dati istanziato su interi
*/
void test_interi() {
    std::cout << "TEST PER AGGIUNTA E RIMOZIONE INTERI" << std::endl;

    Set<int, equal_int> setI;

    setI.add(5);
    setI.add(2);
    setI.add(8);

    std::cout << setI << std::endl; // usa operator<<

    setI.add(5); // Non dovrebbe essere aggiunto perché già presente
    setI.add(10);

    std::cout << setI << std::endl; // usa operator<<

    setI.remove(2);
    setI.remove(10);

    std::cout << setI << std::endl; // usa operator<<

    setI.remove(10);

    std::cout << setI << std::endl; // usa operator<<
}

/**
  @brief Test del Set di dati istanziato su stringhe

  Test del Set di dati istanziato su stringhe
*/
void test_stringhe() {
    std::cout << "TEST PER AGGIUNTA E RIMOZIONE STRINGHE" << std::endl;

    Set<std::string, equal_string> setS;

    setS.add("apple");
    setS.add("banana");
    setS.add("orange");

    std::cout << setS << std::endl; // usa operator<<
    
    setS.add("apple"); // Non dovrebbe essere aggiunto perché già presente
    setS.add("grapes");

    std::cout << setS << std::endl; // usa operator<<
    
    setS.remove("banana");
    setS.remove("grapes");

    std::cout << setS << std::endl; // usa operator<<

    setS.remove("grapes");

    std::cout << setS << std::endl; // usa operator<<
    
}

/**
  @brief Test del Set di dati di prova generale

  Test del Set di dati di prova generale
*/
void test_prova() {
    std::cout << "TEST PER PROVA GENERALE DEL SET" << std::endl;

    Set<int, equal_int> set1;

    set1.add(1);
    set1.add(2);
    set1.add(3);

    std::cout << set1 << std::endl;
    assert(set1.contains(2));
    // assert(set1.contains(4));

    assert(set1[0] == 1);
    // assert(set1[1] == 1);

    Set<int, equal_int> set2;
    set2.add(2);
    set2.add(3);
    set2.add(1);

    assert(set1 == set2);
}

//---------------- TEST PER TIPO CUSTOM -----------------------------
/**
  Struct person che implementa una persona.

  @brief Struct person che implementa una persona con nome e età.
*/
struct person {
  std::string name; ///< stringa che rappresenta il nome
  int age; ///< intero che rappresenta l'età

  person() : name(" "), age(0) {}

  person(std::string n, int a) : name(n), age(a) {}
};

/**
  Ridefinizione dell'operatore di stream << per una persona.
  Necessario per l'operatore di stream della classe Set.
*/
std::ostream &operator<<(std::ostream &os, const person &p) {
  std::cout << "(" << p.name << ", " << p.age <<")";
  return os;
}

/**
  @brief Funtore per il confronto di due persone.

  Funtore per l'uguaglianza di due persone. Due persone sono uguali
  se hanno lo stesso nome e la stessa età.

  Ritorna true se p1.name == p2.name e p1.age==p2.age
*/
struct equal_person {
  bool operator()(const person &p1, const person &p2) const {
    return (p1.name==p2.name) && (p1.age==p2.age);
  } 
};

/**
  @brief Test del Set di dati istanziato su oggetti person

  Test del Set di dati istanziato su oggetti person
*/
void test_person() {
    std::cout << "TEST PER AGGIUNTA E RIMOZIONE DI PERSONE" << std::endl;

    Set<person, equal_person> setP;

    setP.add(person("Alessandro", 22));
    setP.add(person("Nicola", 29));
    setP.add(person("Elena", 26));

    std::cout << setP << std::endl; // usa operator<<

    setP.add(person("Alessandro", 22)); // Non dovrebbe essere aggiunto perché già presente
    setP.add(person("Alessandro", 29));

    std::cout << setP << std::endl; // usa operator<<

    setP.remove(person("Alessandro", 29));
    setP.remove(person("Elena", 26));

    std::cout << setP << std::endl; // usa operator<<

    setP.remove(person("Elena", 26));

    std::cout << setP << std::endl; // usa operator<<

    Set<person, equal_person>::const_iterator i,ie;

    for(i = setP.begin(), ie=setP.end(); i!=ie; ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
}

// -------------------- TEST ITERATORI --------------------------

/**
 * @brief Test per la stampa degli iteratori del Set
 * 
 * Questa funzione testa la stampa degli iteratori all'interno di un Set
 * di interi.
*/
void test_iteratori() {
    std::cout << "TEST PER ITERATORI E METODI" << std::endl;

    Set<int, equal_int> set_iter;

    set_iter.add(1);
    set_iter.add(2);
    set_iter.add(3);

    Set<int, equal_int>::const_iterator i, ie;
    std::cout << "Stampa dei valori tramite iteratori:" << std::endl;
    for (i = set_iter.begin(), ie = set_iter.end(); i != ie; ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    i = set_iter.begin();
    i++;
    std::cout << "Dopo incremento: " << *i << std::endl;
    i--;
    std::cout << "Dopo decremento: " << *i << std::endl;

    Set<int, equal_int>::const_iterator i2;
    i2 = set_iter.begin();
    assert(i == i2);

    i2++;
    assert(i != i2);
    
}

// ------------------- TEST FUNZIONI GLOBALI -----------------------

/**
 * @brief Test della funzione filter_out con un funtore personalizzato
 *
 * Questa funzione testa la funzione filter_out, che filtra gli elementi di un Set
 * utilizzando un predicato (funtore) specifico. In questo caso viene 
 * utilizzato il funtore is_even.
 */
void test_filter_out() {
    std::cout<<"TEST DELLA FUNZIONE FILTER_OUT"<<std::endl;
    int array[7] = {5, 8, 4, 9, 2, 3, 6};

    Set<int, equal_int> set1(array, array + 7);

    std::cout<< set1 << std::endl; // usa operator<<
    is_even ie;

    std::cout<<"Chiamata filter_out con funtore is_even"<<std::endl;
    filter_out(set1, ie);
}

/**
 * @brief Test dell'operatore di concatenazione di due Set
 *
 * Questa funzione testa l'operatore di concatenazione (operator+) 
 * per i Set. Viene stampato a schermo un Set contenente la concatenazione
 * dei valori di due Set creati in precedenza
 */
void test_operator_concatenazione() {
    std::cout<<"TEST DELLA FUNZIONE OPERATOR+"<<std::endl;
    Set<int, equal_int> set1;
    set1.add(1);
    set1.add(2);
    set1.add(3);

    Set<int, equal_int> set2;
    set2.add(5);
    set2.add(3);
    set2.add(4);

    Set<int, equal_int> concat = set1 + set2;

    std::cout << concat << std::endl;
}

/**
 * @brief Test dell'operatore di intersezione di due Set
 *
 * Questa funzione testa l'operatore di intersezione (operator-) 
 * per i Set. Viene stampato a schermo un Set contenente l'intersezione
 * dei valori di due Set creati in precedenza
 */
void test_operator_intersezione() {
    std::cout<<"TEST DELLA FUNZIONE OPERATOR-"<<std::endl;
    Set<int, equal_int> set1;
    set1.add(1);
    set1.add(2);
    set1.add(3);

    Set<int, equal_int> set2;
    set2.add(5);
    set2.add(3);
    set2.add(4);

    Set<int, equal_int> intersec = set1 - set2;

    std::cout << intersec << std::endl;
}

/**
 * @brief Test della funzione di salvataggio di un Set in un file testuale
 *
 * Questa funzione testa la funzione di salvataggio `save`, che prende un Set di stringhe
 * e salva il suo contenuto in un file testuale. Viene creato un Set di stringhe di esempio
 * con alcune parole, quindi viene chiamata la funzione `save` per salvare il contenuto del
 * Set nel file "save_file.txt".
 */
void test_save() {
    std::cout << "TEST DELLA FUNZIONE SAVE" << std::endl;

    Set<std::string, equal_string> setS;

    setS.add("apple");
    setS.add("banana");
    setS.add("orange");
    setS.add("grapes");
    setS.add("watermelon");
    setS.add("cherry");

    save(setS, "save_file.txt");
    
}

//---------------------- MAIN ------------------------------
/**
 * @brief Funzione main del programma
 *
 * La funzione main esegue i vari test sulla classe Set, chiamando le 
 * funzioni di test specifiche. Le chiamate ai test sono attualmente
 * commentate per eseguirli uno alla volta.
 */
int main() {
    test_metodi_fondamentali();
    
    // test_interi();

    // test_stringhe();

    // test_prova();

    // test_person();

    // test_iteratori();

    // test_filter_out();

    // test_operator_concatenazione();

    // test_operator_intersezione();

    // test_save();

    return 0;
}
