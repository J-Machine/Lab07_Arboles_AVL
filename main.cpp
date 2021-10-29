#include <bits/stdc++.h>
using namespace std;

template <class T>
class Nodo
{
public:
    T dato;
    Nodo<T> *hijo[2];

    Nodo(T d)
    {
        dato = d;
        hijo[0] = 0;
        hijo[1] = 0;
    }
};

template <class T>
class ArbolBinarioBusqueda
{
public:
    Nodo<T> *raiz;

public:
    /////////////////////CONSTRUCTOR//////////////////////////////////
    ArbolBinarioBusqueda() : raiz(0){};

    /////////////////////INSERTAR//////////////////////////////////
    void insert(const T &d, Nodo<T> *&p)
    {
        if (p == nullptr)
        {
            p = new Nodo<T>(d);
        }
        if (p->dato == d)
            return;
        return insert(d, p->hijo[p->dato < d]);
    }

    void insert(const T &d)
    {
        insert(d, raiz);
    }

    //////////////////////BUSCAR//////////////////////////////////
    bool find(const T &d, Nodo<T> *p)
    {
        if (p == nullptr)
            return false;
        if (p->dato == d)
            return true;
        else if (p->dato > d)
            return find(d, p->hijo[0]);
        else if (p->dato < d)
            return find(d, p->hijo[1]);
    }

    bool find(const T &d)
    {
        return find(d, raiz);
    }

    Nodo<T> *findMin(Nodo<T> *t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->hijo[0] == nullptr)
            return t;
        return findMin(t->hijo[0]);
    }

    //////////////////////ELIMINAR//////////////////////////////////
    void remove(const T &x, Nodo<T> *&t)
    {
        if (t == nullptr)
            return;
        if (x < t->dato)
            remove(x, t->hijo[0]);
        else if (t->dato < x)
            remove(x, t->hijo[1]);
        else if (t->hijo[0] != nullptr && t->hijo[1] != nullptr)
        {
            t->dato = findMin(t->hijo[1])->dato;
            remove(t->dato, t->hijo[1]);
        }
        else
        {
            Nodo<T> *aux = t;
            t = (t->hijo[0] != nullptr) ? t->hijo[0] : t->hijo[1];
            delete aux;
        }
    }

    bool eliminar(const T &x)
    {
        if (find(x))
        {
            remove(x, raiz);
            return true;
        }
        else
        {
            return false;
        }
    }

    ///////////////////////// CLEAR TREE /////////////////////////
    void clearNodes(Nodo<T> *_node)
    {
        if (_node == nullptr)
            return;
        clearNodes(_node->hijo[0]);
        clearNodes(_node->hijo[1]);
        cout << "\n Eliminando nodo: " << _node->dato;
        if (_node == raiz)
            raiz = 0;
        else
            delete _node;
    }

    void clear()
    {
        clearNodes(raiz);
    }

    //////////////////////INORDER//////////////////////////////////
    void inorder(Nodo<T> *tmp, string &cadena) // F. Aux.
    {
        if (!tmp)
            return;
        inorder(tmp->hijo[0], cadena);
        cadena.append(to_string(tmp->dato)).append(" ");
        inorder(tmp->hijo[1], cadena);
    }
    string inOrder()
    {
        string cad;
        inorder(raiz, cad);
        return cad;
    }

    //////////////////////PREORDER//////////////////////////////////
    void preorder(Nodo<T> *tmp, string &cadena) // F. Aux.
    {
        if (!tmp)
        {
            return;
        }
        cadena.append(to_string(tmp->dato)).append(" ");
        preorder(tmp->hijo[0], cadena);
        preorder(tmp->hijo[1], cadena);
    }

    string preOrder()
    {
        string cad;
        preorder(raiz, cad);
        return cad;
    }

    //////////////////////POSTORDER//////////////////////////////////
    void postorder(Nodo<T> *tmp, string &cadena) // F. Aux.
    {
        if (!tmp)
        {
            return;
        }
        postorder(tmp->hijo[0], cadena);
        postorder(tmp->hijo[1], cadena);
        cadena.append(to_string(tmp->dato)).append(" ");
    }

    string postOrder()
    {
        string cad;
        postorder(raiz, cad);
        return cad;
    }

    /////////////////////GRAFICAR//////////////////////////////////
    void escribirdot(ofstream &archivo, Nodo<T> *ARBOL, int i)
    {
        if (ARBOL)
        {
            escribirdot(archivo, ARBOL->hijo[0], i); // recorrer por la izquierda
            if (ARBOL->hijo[0])
            {
                i++;
                archivo << ARBOL->dato << " -> " << ARBOL->hijo[0]->dato << "\n";
            }
            else
            {
                archivo << "izq" << i << " [style=invis]"
                        << "\n";
                archivo << ARBOL->dato << " -> izq" << i << " [style=invis]"
                        << "\n";
            }

            if (ARBOL->hijo[1])
            {
                archivo << ARBOL->dato << " -> " << ARBOL->hijo[1]->dato << "\n";
            }
            else
            {
                i++;
                archivo << "der" << i << " [style=invis]"
                        << "\n";
                archivo << ARBOL->dato << " -> der" << i << " [style=invis]"
                        << "\n";
            }
            escribirdot(archivo, ARBOL->hijo[1], i); // recorrer por la derecha
        }
    }

    
    /*
    string ToDot(Nodo<T> *NodoActual, string resultado)
    {
        if(NodoActual!= nullptr){
            if(!NodoActual->hijo[0]){
                resultado = resultado + "\n" + to_string(NodoActual->dato) + " -> " + to_string(NodoActual->hijo[0]->dato) + ";";
            }
            if(!NodoActual->hijo[1]){
                resultado = resultado + "\n" + to_string(NodoActual->dato) + " -> " + to_string(NodoActual->hijo[1]->dato) + ";";
            }
            ToDot(NodoActual->hijo[0], resultado);
            ToDot(NodoActual->hijo[1], resultado);
            return resultado;
        }
    }
    */
    void ToDot(Nodo<T> *NodoActual, string& resultado)
    {
        if(NodoActual->hijo[0]!= nullptr){
            resultado.append(to_string(NodoActual->dato)).append(" -> ").append(to_string(NodoActual->hijo[0]->dato)).append(";\n");
            ToDot(NodoActual->hijo[0], resultado);
        }
        if(NodoActual->hijo[1]!= nullptr){
            resultado.append(to_string(NodoActual->dato)).append(" -> ").append(to_string(NodoActual->hijo[1]->dato)).append(";\n");
            ToDot(NodoActual->hijo[1], resultado);
        }
    }
    

    void graficar()
    {
        ofstream archivo;
        archivo.open("./arbolito.dot");
        string Resultado ="";
        ToDot(this->raiz, Resultado);
        if (archivo.is_open())
        {
            archivo << "digraph Figura { \n";
            // escribirdot(archivo, raiz, 0);
            archivo << Resultado;
            archivo << "}\n";
            archivo.close();
            system("dot -Tpng ./arbolito.dot -o ./arbolito.png ");
        }
        else
        {
            cout << "error al crear archivo";
        }
    }
};

int main()
{
    ArbolBinarioBusqueda<int> A;

    cout << "\nEJEMPLO DE ARBOL BINARIO";
    A.insert(6);
    A.insert(2);
    A.insert(8);
    A.insert(1);
    A.insert(4);
    A.insert(3);
   cout << endl;

    // Imprimir los elementos del arbol
    cout << "Arbol en InOrden: "
         << A.inOrder() << endl;
    cout << "Arbol en PostOrden: "
         << A.postOrder() << endl;
    cout << "Arbol en PreOrden: "
         << A.preOrder() << endl;

    // Prueba de busqueda y eliminación
    cout << "\nBuscar elemento 7 en el arbol binario: \n"
         << (A.find(7) ? "Encontrado" : "No encontrado") << endl;

    cout << "\nEliminar elemento 7 del arbol binario: \n";
    cout << (A.eliminar(7) ? "Eliminado" : "No eliminado, no se encuentra") << endl;

    cout << "\nBuscar elemento 7 en el arbol binario: \n"
         << (A.find(7) ? "Encontrado" : "No encontrado") << endl;
    cout << endl;

    // Imprimir los elementos del arbol sin el 7
    cout << "Arbol en InOrden: "
         << A.inOrder() << endl;
    cout << "Arbol en PostOrden: "
         << A.postOrder() << endl;
    cout << "Arbol en PreOrden: "
         << A.preOrder() << endl;
    cout << endl;
    
    // Graficar el arbol
    cout << "Generando gráfico del arbol";
    A.graficar();
    // system("/arbolito.png");
    cout << endl;
    return 0;
}