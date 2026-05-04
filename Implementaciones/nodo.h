#ifndef NODO_H_
#define NODO_H_
#ifndef NULL
#define NULL 0
#endif

template <class T>
class nodo {
    private:
        T info;
        nodo<T> *sig;
    public:
        nodo(T x, nodo<T> *p = 0){
            info = x;
            sig = p;
        };   
        T getInfo(){
            return info;
        };
        nodo<T> *getSig(){
            return sig;
        };
        void setInfo(T i){
            info = i;
        };
        void setSig(nodo<T> *n){
            sig = n;
        };
};

#endif