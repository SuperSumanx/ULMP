/* Resizable Array
 * Written by Sumanth
 * I could have used a std::vector but I find this easier to debug with.
 * Plus, I can understand this :)
 */


#ifndef ARRAY_H
#define ARRAY_H

//define a class to hold information about Array Exceptions
class ArrayException {
public:
    char* getErrorMessage() const {
        return errorMessage;
    }

    void setErrorMessage( char * error) {
        errorMessage=error;
    }

private:
    char* errorMessage;

};

template <typename T>
class Array {
private:

    T* array;
    unsigned int length;

    T* copyAndDelete(T *a, unsigned int oldLength, unsigned int newLength) {
        T*n=new T[newLength];
        if(oldLength==0) {
            //don't do anything, just allocate memory
            return n;
        }
        for(unsigned int i=0; i<oldLength; i++) {
            n[i]=a[i];
        }

        delete[] a;
        return n;
    }
public :

    Array() {
        length=0;
    }
    ~Array() {
        length=0;
        delete[] array;
    }

    Array(unsigned int length, T content=0) {
        this->length=length;
        array=new T[this->length];
        for(int i=0; i<this->length; i++)
            array[i]=content;
    }

    void push_back(T p) {
        length++;
        array=copyAndDelete(array, length-1, length);
        array[length-1]=p;
    }

    T& at(unsigned int i) {
        return array[i];
    }

    void erase(unsigned int i) throw(ArrayException) {

        if(i>= length ) {
            ArrayException e;
            e.setErrorMessage("Erase is out of range.");
            throw e;
            return;
        }
        length--;
        T* t=new T[length];
        for(int j=0; j<i; j++) {
            t[j]=array[j];
        }
        for(int j=i+1; j<length+1; j++) {
            t[j-1]=array[j];
        }
        delete[] array;
        array=t;
    }
    int size() {
        return this->length;
    }
};

#endif // ARRAY_H
