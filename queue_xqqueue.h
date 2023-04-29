#ifndef QUEUE_XQQUEUE_H
#define QUEUE_XQQUEUE_H


#include <iostream>
#include <vector>

using namespace std;

namespace xq {

    const int MAX_QUEUE_SIZE = 50;
    template<typename T>
    class xqQueue {
    private:
        T *base;
        int front;
        int rear;
        int size;
    public:
        xqQueue();

        xqQueue(int);

        bool insert(T);

        bool delete_(T *);

        bool isEmpty();

        void print();

        int print_new2old();

        T getRear();

        int getAll(vector<T> &);
    };

    template<typename T>
    xqQueue<T>::xqQueue() {
        base = new T[MAX_QUEUE_SIZE];
        front = rear = 0;
        size = MAX_QUEUE_SIZE;
    }

    template<typename T>
    xqQueue<T>::xqQueue(int n) {
        base = new T[n];
        front = rear = 0;
        size = n;
    }

    template<typename T>
    bool xqQueue<T>::isEmpty() {
        if (rear == front)
            return true;

        return false;
    }

    template<typename T>
    bool xqQueue<T>::insert(T num) {
        if ((rear + 1) % size == front) {
//            cout << "queue is full!" << endl;
//            return false;
            front = (front + 1) % size;
            base[rear % size] = num;
            rear = (rear + 1) % size;
            return true;
        }

        base[rear % size] = num;
        rear = (rear + 1) % size;
    }

    template<typename T>
    void xqQueue<T>::print() {
        if (isEmpty()) {
            cout << "queue is empty!" << endl;
            return;
        }

        int p = front;
        int q = rear;
        while (p % size != q) {
            cout << base[p] << ' ';
            p = (p+1)%size;
        }
        cout << endl;
    }

    template<typename T>
    bool xqQueue<T>::delete_(T *num) {
        if (isEmpty()) {
            cout << "queue is empty!" << endl;
            return false;
        }

        *num = base[front];
        front = (front + 1) % size;
    }

    template<typename T>
    int xqQueue<T>::print_new2old(){
        if (isEmpty()) {
            cout << "queue is empty!" << endl;
            return -1;      // 队列为空则返回-1表示队空
        }

        int traversal = rear;
        while(traversal % size != front){
            traversal = traversal-1 < 0 ? size-1 : traversal-1;
            cout << base[traversal] << ' ';
        }
        cout << endl;
    }

    template<typename T>
    T xqQueue<T>::getRear(){    // 使用前需手动判断非空
        if (isEmpty()) {
            cout << "queue is empty!" << endl;
        }
        return base[rear-1<0 ? size-1 : rear-1];
    }

    template<typename  T>
    int xqQueue<T>::getAll(vector<T> &results){
        if (isEmpty()) {
            cout << "queue is empty!" << endl;
            return -1;      // 队列为空则返回-1表示队空
        }

        int traversal = rear;
        while(traversal % size != front){
            traversal = traversal-1 < 0 ? size-1 : traversal-1;
            results.push_back(base[traversal]);
        }
        return results.size();
    }
}

#endif // QUEUE_XQQUEUE_H
