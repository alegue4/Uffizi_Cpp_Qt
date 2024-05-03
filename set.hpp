/**
  @file set.hpp

  @brief File header della classe Set templata

  File di dichiarazioni/definizioni della classe Set templata
*/
#ifndef SET_HPP
#define SET_HPP

#include <ostream> // std::ostream
#include <iostream>
#include <iterator> // std::bidirectional_iterator_tag
#include <cstddef>  // std::ptrdiff_t
#include <fstream> // per scrittura su file

typedef unsigned int set_size; ///< Tipo di dato per la dimensione di un Set

/**
 * @brief classe Set di dati

  La classe implementa un generico Set di oggetti T.
  La valutazione se due dati di tipo T sono uguali è realizzata
  tramite un secondo funtore Equal. 
*/
template<typename T, typename Equal>
class Set {
private:
    T* elements; ///< puntatore ai dati ti tipo T
    set_size size; ///< grandezza di un Set dato

    Equal _eql;   ///< funtore per l'uguaglianza tra dati T
public:

    /**
     * @brief Costruttore di default
     * 
     * Costruttore di default di un Set di dati
     * 
     * @post elements == new T[0]
     * @post size == 0
    */
    Set() : elements(new T[0]), size(0) {}

    /**
     * @brief Copy constructor
     * 
     * Crea un nuovo oggetto Set copiando gli elementi da un altro
     * Set di dati passato come parametro
     * 
     * @param other Set di dati da cui copiare gli elementi
    */
    Set(const Set &other) : elements(new T[other.size]), size(other.size) {
        for (set_size i = 0; i < size; ++i) {
            elements[i] = other.elements[i];
        }
    }

    /**
     * @brief Operatore di assegnamento della classe Set
     *
     * Esegue un assegnamento dell'oggetto Set, copiando gli elementi 
     * dall'oggetto Set fornito.
     * 
     * @param other Set di dati da cui copiare gli elementi
     * 
     * @return Reference a *this
    */
    Set& operator=(const Set &other) {
        if (&other != this) {
            // Crea una copia temporanea degli elementi
            T* tmp = new T[other.size];
            for (set_size i = 0; i < other.size; ++i) {
                tmp[i] = other.elements[i];
            }

            // Dealloca la memoria esistente
            delete[] elements;

            // Aggiorna gli elementi e la dimensione con la copia profonda
            elements = tmp;
            size = other.size;
        }
        return *this;
    }

    /**
     * @brief Distruttore della classe Set
     *
     * Libera la memoria allocata per gli elementi della classe Set.
    */
    ~Set() {
        delete[] elements;
        elements = nullptr;
    }

    /**
     * @brief Metodo per restituzione grandezza Set
     * 
     * Restituisce la dimensione corrente del Set, ovvero il numero
     * di elementi che compongono il set
     * 
     * @return Dimensione del Set
    */
    set_size get_size() const {
        return size;
    }

    /**
     * @brief Metodo per aggiunta di un elemento al Set
     * 
     * Aggiunge un elemento al Set solo se questo non è già presente,
     * altrimenti non modifica il Set
     * 
     * @param el elemento da aggiungere al Set di dati
    */
    void add(const T& el) {
        if (contains(el)) {
            return; 
        }

        T* new_elements = new T[size + 1];
        for (size_t i = 0; i < size; ++i) {
            new_elements[i] = elements[i];
        }
        new_elements[size] = el;

        delete[] elements;
        elements = new_elements;
        size++;
    }

    /**
     * @brief Metodo per rimozione di un elemento dal Set
     * 
     * Rimuove un elemento dal Set solo se questo è già presente, 
     * altrimenti non modifica il Set
     * 
     * @param el elemento da rimuovere dal Set di dati
    */
    void remove(const T& el) {
        bool found = false;
        set_size index_found = 0;

        if (!contains(el)) {
            return;
        }

        for (set_size i = 0; i < size; i++) {
            if (_eql(elements[i], el)) {
                index_found = i;
            }    
        }
        
        T* new_elements = new T[size - 1];
    
        if(index_found == (size - 1)) {
            for (set_size i = 0; i < index_found; i++) {
                new_elements[i] = elements[i];
            }
            delete[] elements;
            elements = new_elements;
            size--;
        } else {
            // Copia gli elementi precedenti all'elemento da rimuovere
            for (set_size i = 0; i < index_found; i++) {
                new_elements[i] = elements[i];
            }

            // Copia gli elementi successivi all'elemento da rimuovere
            for (set_size i = index_found + 1; i < size; i++) {
                new_elements[i - 1] = elements[i];
            }

            delete[] elements;
            elements = new_elements;
            size--;
        }  
    }

    /**
     * @brief Operatore di accesso in sola lettura
     * 
     * Operatore di accesso in sola lettura all'i-esimo elemento del Set.
     * Se l'indice passato come parametro è negativo o fuori dalla
     * dimensione del Set viene generata un'asserzione
     * 
     * @param i indice dell'elemento del Set a cui accedere
     * 
     * @pre L'indice deve essere compreso tra 0 e size-1
    */
    const T& operator[](set_size i) const {
        assert(i >= 0 && i < size);
        return elements[i];
    }

    /**
     * @brief Verifica la presenza di un elemento nel Set
     *
     * Verifica se l'elemento specificato è presente o meno nel Set.
     * 
     * @param el elemento da cercare nel Set
     * 
     * @return true se l'elemento è presente, false altrimenti
    */
    bool contains(const T &el) const {
        for (set_size i = 0; i < size; i++) {
            if (_eql(elements[i], el)) {
                return true;
            }
            
        }
        return false;
    }

    /**
     * @brief Costruttore con iteratori
     * 
     * Costruttore di un Set di dati presi da una sequenza di dati
     * identificata da un iteratore di inizio e uno di fine. Gli 
     * iteratori possono essere di qualsiasi tipo
     * 
     * @param begin iteratore di inizio sequenza
     * @param end iteratore di fine sequenza
    */
    template<typename Q>
    Set(Q start, Q end) : elements(nullptr), size(0) {
        while (start != end) {
            add(*start);
            ++start;
        }
    }

    /**
     * @brief Operatore di stream
     * 
     * Funzione globale che implementa l'operatore di stream di un Set.
     * La funzione è templata sul Set ed è messa friend per poter accedere
     * ai dati privati della classe Set
     * 
     * @param os stream di output
     * @param set Set di dati da spedire sullo stream
     * 
     * @return Lo stream di output
    */
    friend std::ostream& operator<<(std::ostream &os, const Set &set) {
        os << set.size << " ";
        for (set_size i = 0; i < set.size; i++) {
            os << "(" << set.elements[i] << ") ";
        }
        
        return os;
    }

    /**
     * @brief Operatore di confronto di uguaglianza tra due Set
     *
     * Verifica se due Set sono uguali confrontando i loro contenuti. 
     * E' presente un controllo iniziale che interrompe il confronto se
     * i due Set sono di lunghezze diverse
     * 
     * @param set Set da confrontare con l'istanza del Set corrente
     * 
     * @return true se i due Set contengono gli stessi elementi, false altrimenti
    */
    bool operator==(const Set &set) {
        if (size != set.size)
            return false;

        for (set_size i = 0; i < size; i++)
        {
            if (!(set.contains(elements[i]))) {
                return false;
            }
        }
        
        return true;
    }   

    /**
     * Gli iteratori devono iterare sui dati inseriti nella classe
     * principale. Siccome nel Set mettiamo dei dati di tipo T,
     * l'iteratore deve iterare sui dati di tipo T.
    */
    class const_iterator {

	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T                               value_type;
		typedef ptrdiff_t                       difference_type;
		typedef const T*                        pointer;
		typedef const T&                        reference;

	
		const_iterator() : _ptr(nullptr) {}
		
		const_iterator(const const_iterator &other) : _ptr(other._ptr) {}

		const_iterator& operator=(const const_iterator &other) {
			if (this != &other) {
                _ptr = other._ptr;
            }
            return *this;
		}

		~const_iterator() {}

        // Ritorna il dato riferito dall'iteratore (dereferenziamento)
        reference operator*() const {
            return *_ptr;
        }

        // Ritorna il puntatore al dato riferito dall'iteratore
        pointer operator->() const {
            return _ptr;
        }
		
		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
			const_iterator tmp = *this;
            ++_ptr;
            return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator &operator++() {
			++_ptr;
            return *this;
		}

		// Operatore di iterazione post-decremento
		const_iterator operator--(int) {
			const_iterator tmp = *this;
            --_ptr;
            return tmp;
		}

		// Operatore di iterazione pre-decremento
		const_iterator &operator--() {
			--_ptr;
            return *this;
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return _ptr == other._ptr;
		}
		
		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return _ptr != other._ptr;
		}

	private:
		//Dati membro
        const T *_ptr;
		// La classe Set deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class Set;

		// Costruttore privato di inizializzazione usato dalla classe Set
		// tipicamente nei metodi begin e end
		const_iterator(const T *ptr) : _ptr(ptr) {}
		
		
	}; // classe const_iterator
	
	// Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const {
		return const_iterator(elements);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	const_iterator end() const {
		return const_iterator(elements + size);
	}
}; // fine della classe Set

/**
 * @brief Funzione che filtra un Set
 * 
 * Funzione globale che stampa a schermo solo i valori di un
 * generico Set di dati solo se questi rispettano un predicato
 * generico di tipo P.
 * 
 * @param set Set di dati sorgente
 * @param pred predicato generico di tipo P
*/
template <typename T, typename Equal, typename P>
void filter_out(const Set<T, Equal> &set, P pred) {
  typename Set<T, Equal>::const_iterator i, ie;

  for(i=set.begin(), ie = set.end(); i != ie; ++i) {
    if (pred(*i)) {
        std::cout << *i << std::endl;
    } 
  }
}

/**
 * @brief Funzione per concatenazione di due Set
 * 
 * Funzione globale che concatena gli elementi presenti in due Set,
 * mantendendo la non duplicità degli elementi di un Set. Viene ritornato
 * un Set contenente la concatenazione.
 * 
 * @param s1 primo Set da concatenare
 * @param s2 secondo Set da concatenare
 * 
 * @return Set risultato della concatenazione tra due Set
*/
template <typename T, typename Equal>
Set<T, Equal> operator+(const Set<T, Equal> &s1, const Set<T, Equal> &s2) {
    Set<T, Equal> tmp(s1);
    for (set_size i = 0; i < s2.get_size(); i++) {
        if (!s1.contains(s2[i]))
        {
            tmp.add(s2[i]);
        }
    }
    return tmp;
}

/**
 * @brief Funzione per intersezione di due Set
 * 
 * Funzione globale che interseca gli elementi presenti in due Set,
 * mantendendo la non duplicità degli elementi di un Set. Viene ritornato
 * un Set contenente la intersecazione.
 * 
 * @param s1 primo Set da intersecare
 * @param s2 secondo Set da intersecare
 * 
 * @return Set risultato della intersezione tra due Set
*/
template <typename T, typename Equal>
Set<T, Equal> operator-(const Set<T, Equal> &s1, const Set<T, Equal> &s2) {
    Set<T, Equal> tmp;
    for (set_size i = 0; i < s2.get_size(); i++) {
        if (s1.contains(s2[i]))
        {
            tmp.add(s2[i]);
        }
    }
    return tmp;
}

/**
 * @brief Funzione per salvare un Set di stringhe in un file
 * 
 * Funzione che permette di salvare un Set di stringhe in un file definito.
 * Ogni elemento del Set viene limitato tra parentesi tonde e separato
 * dagli altri elementi con degli spazi
 * 
 * @param set Set di stringhe da passare al file
 * @param filename file su cui scrivere il Set passato
 * 
 * @throw Eccezioni derivanti dall'errore nell'apertura o la scrittura del file. 
*/
template <typename Equal>
void save(const Set<std::string, Equal> &set, const std::string &filename) {
    try {
        std::ofstream file(filename);
        if (file.is_open()) {
            // file << set.get_size() << " ";
            for (size_t i = 0; i < set.get_size(); ++i) {
                file << "(" << set[i] << ") ";
            }
            file.close();
            // std::cout << "Set saved to " << filename << std::endl;
        } 
    } catch (...) {
        throw;
    }
}

#endif
