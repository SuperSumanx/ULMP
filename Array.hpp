#ifndef ARRAY_HPP
#define ARRAY_HPP
template <typename T>
class Array {
public:
    //*****************************
    //Constructors and Destructors
    Array() : len(0),maxLen(1) {
        array=new T[maxLen];
        allocated=true;
    }
    Array(unsigned length, T&content=0) : len(length),maxLen(length*2) {
        array=new T[maxLen];
        allocated=true;
        for(unsigned int i=0; i<len; i++) {
            array[i]=content;
        }
    }
    ~Array() {
        delete[] array;
    }
    //**************************************
    //capacity related functions
    unsigned int size() {
        return len;
    }
    unsigned int capacity() {
        return maxLen;
    }

    void resize(unsigned int newSize, const T& content=0) {
        if(newSize==len) {
            return;
        }
        T* temp= new T[newSize];
        if(newSize>len) { //if newSize is more than len, then copy the previous array, and append content to the array
            int oldLen=len;
            len=newSize;
            checkMax();
            for(unsigned int i=0; i<oldLen; i++) {
                temp[i]=array[i];
            }
            for(unsigned int i=oldLen; i<newSize; i++) {
                temp[i]=content;
            }
        }
        if(newSize<len) { // if newSize is less than len, then just copy the previous array till the length
            for(unsigned int i=0; i<newSize; i++) {
                temp[i]=array[i];
            }
        }
        delete[] array;
        array=temp;
        len=newSize;
    }
    bool empty() const {
        return len==0;
    }
    void reserve(unsigned int newCapacity) {
        if(newCapacity>maxLen) {
            maxLen=newCapacity;
            T * temp = new T[maxLen];
            for(unsigned int i=0; i< maxLen; i++) {
                temp[i]=array[i];
            }
            delete [] array;
            array=temp;
        }
    }
    void shrink_to_fit() {
        maxLen=len;
        T*temp = new T[len];
        for(unsigned int i=0; i<len; i++) {
            temp[i]=array[i];
        }
        delete[] array;
        array=temp;

    }
    //********************************************
    //Element Access
    T& operator[](unsigned int i) {
        return array[i];
    }
    T& at(unsigned int index) {
        return array[index];
    }
    const T& front() {
        return array[0];
    }
    const T& back() {
        return array[len-1];
    }
    T* data() {
        return array;
    }
    //**********************************************
    //Modifiers
    void push_back(const T& content) {
        checkMax();
        array[len]=content;
        len++;
    }

    void pop_back() {
        len--;
        array[len]=0;
    }

    void erase(unsigned int index, unsigned int length=1) {
        T*temp=new T[len-length];
        for(unsigned int i=0; i<index; i++) {
            temp[i]=array[i];
        }
        for(unsigned int i=index+length; i<len; i++) {
            temp[i-length]=array[i];
        }
        delete[] array;
        array=temp;
        len=len-length;

        if(maxLen>len*2) {
            maxLen=len*2;
            temp=new T[len*2];
            for(unsigned int i=0; i<len; i++) {
                temp[i]=array[i];
            }
            delete[] array;
            array=temp;
        }
    }
    //*******************************************
private:
    T* array;
    unsigned int len;
    unsigned int maxLen;
    bool allocated;

    void checkMax() {
        if(len==maxLen) {
            //allocate more memory for the array
            maxLen*=2;
            T*temp=new T[maxLen];
            for(unsigned int i=0; i<len; i++) {
                temp[i]=array[i];
            }
            delete [] array;
            array=temp;
        }
    }
};

#endif // ARRAY_HPP
