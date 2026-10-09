#pragma once //usamos #pragma once para evitar inclusiones múltiples del mismo archivo
//Aquí nombramos los métodos a utilizar, como si fuera una clase dedicada solo a lista simple.
//¿Por qué su uso en un .h y no en un cpp? Ahorro de código y permite llamar desde archivos distintos
//Es decir estamos mencionando las declaraciones de la clase ListaSimple y su respectivo struct NodoSimple
template <typename T> //Template es una clase perteneciente a C++, clase plantilla
struct NodoSimple { //Hacamos un struct con el Nodo perteneciente a la clase ListaSimple
    //Que es la que contiene los datos y el puntero al siguiente nodo
    T dato; //El dato es de tipo T, que es un tipo genérico definido por la clase plantilla
    //Ser tipo T hace que se le pueda pasar cualquier tipo de dato, como int, float, string, etc.
    //Opte por esto ya que agiliza el tener una lista de cualquier tipo de dato, sin necesidad de crear una clase para cada tipo de dato.
    NodoSimple<T>* siguiente; //El puntero siguiente apunta al siguiente nodo de la lista, que es de tipo NodoSimple<T>
    //Ahora el NodoSimple se usa normal para hacer el puntero, pero debe escribirse como <T> antes de este
    //El porque de esto se debe a que el NodoSimple es una clase plantilla, y al serlo, se debe especificar el tipo de dato que va a contener
    // Inicializa el dato del nodo y deja vacío el enlace siguiente.
    NodoSimple(const T& valor)  //Creación del constructor del NodoSimple, que recibe un valor de tipo T y lo asigna al dato del nodo
    //usamos const T& para recibir el valor sin copiarlo y sin permitir modificarlo, lo que mejora el rendimiento y la seguridad del código
        : dato(valor), siguiente(nullptr) {} //Para hacer el constructor primero usamos el nombre usado en el Struct
        //Es decir el NodoSimple, ya que trabajamos con Template, debemos pasar T y valor es el valor que se le pasa al constructor, que es de tipo T
        //Los dos puntos indican que estamos inicializando los miembros del struct, en este caso dato y siguiente
        //Hacemos dato(valor) para asignar el valor recibido al dato del nodo
        //siguiente(nullptr) para inicializar el puntero siguiente a nullptr, ya que al crear un nodo nuevo, este no apunta a ningún otro nodo
        //Los {} indican el final del constructor, y el ; indica el final de la declaración del struct
};

template <typename T> //No es código repetido, es una clase plantilla que permite definir clases y funciones genéricas, 
//En este caso la clase ListaSimple
class ListaSimple { //Class para definir la clase y ListaSimple es su nombre.
protected: //Protected es un modificador de acceso que permite que los miembros de la clase sean accesibles desde la propia clase y desde las clases derivadas, pero no desde fuera de ellas.
    NodoSimple<T>* primero; //El puntero se sigue formando como primero, lo único que al usar template, debemos añadir <T> antes del *
    //Hacemos un método para insertar al final de la lista.
    // Agrega un elemento al final recorriendo la lista hasta su último nodo.
    void insertarAlFinal(const T& elemento) { 
        NodoSimple<T>* nuevo = new NodoSimple<T>(elemento);

        if (primero == nullptr) {
            primero = nuevo;
            return;
        }

        NodoSimple<T>* actual = primero;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }

        actual->siguiente = nuevo;
    }

public:
//Este es el constructor de la clase ListaSimple, que inicializa el puntero primero a nullptr, indicando que la lista está vacía al inicio.
    // Crea una lista simple inicialmente vacía.
    ListaSimple()
        : primero(nullptr) {}

    // Permite que reportes y consultas recorran la lista sin duplicar su implementacion.
    // Expone el primer nodo para consultas y reportes.
    NodoSimple<T>* inicio() const {
        return primero;
    }

    //El destructor de la clase ListaSimple se encarga de liberar la memoria ocupada por los nodos de la lista al destruir el objeto, evitando fugas de memoria.
    // Libera todos los nodos enlazados al destruir la lista.
    virtual ~ListaSimple() {
        while (primero != nullptr) {
            NodoSimple<T>* siguiente = primero->siguiente;
            delete primero;
            primero = siguiente;
        }
    }

    // La plantilla hace que T cambie dinamicamente segun la clase que hereda:
    // puede ser NodoInvestigador, NodoProyecto, NodoRevista, etc.
    // Inserta usando el comportamiento genérico al final de la lista.
    virtual void insertar(const T& elemento) {
        insertarAlFinal(elemento);
    }

    virtual void imprimir() const = 0;
};
//Al final se define un método insertar que recibe un elemento genérico de tipo T.
//Internamente llama a insertarAlFinal(elemento), que ya implementaste para añadir un nodo al final de la lista.
//ES Virtual porque permite que las clases derivadas puedan redefinir este método con su propia implementación.
//Significa que las clases que hereden de ListaSimple pueden sobreescribir este método con su propia lógica.
