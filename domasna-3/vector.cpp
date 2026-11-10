
#include<iostream>

class MyVec{
private:
    unsigned int calc_capacity(int size){
        unsigned int capacity = 1;
        while(capacity < size) {capacity = capacity << 1;}
        return capacity;
    }
    unsigned int v_size;
    unsigned v_capacity;
    int *array;
public:
    MyVec(unsigned int size = 0, int value = 0){
        v_size = size;
        int cl = calc_capacity(size);
        v_capacity = ((cl < 8)? 8 : cl);
        array = new int[v_capacity];
        for(int i = 0; i < v_capacity; i++){
            array[i] = value;
        }
    }
    
    int size() {return v_size;}
    
    int capacity() {return v_capacity;}
    
    void info(){
        std::cout << "c:" << capacity() << " s:" << size() << '\n' << "[";
        for(int i = 0; i < v_size; i++){
            std::cout << " " << array[i];
        }
        std::cout << " ]\n";
    }
    
    int &at(unsigned int index){
        return array[index];
    }
    
    int back(){
        return array[size() - 1];
    }
    
    void pop(){
        if(size() >= 1){
            v_size --;
        }
    }
};

int main(){
    
    MyVec v;
    MyVec v1(10);
    MyVec v2(3,8);
    
    v2.info();
    std::cout << v2.at(1);
    v2.at(1) = 7;
    std::cout << v2.at(1);
    v2.info();
    v2.pop();
    v2.info();
    v2.back();
    v2.info();
    
    
    return 0;
}
