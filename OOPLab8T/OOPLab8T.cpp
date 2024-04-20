#include <iostream>
#include <cstring>

/*Задача 1.3.Написати функцію - шаблон, що переставляє перший
максимальний та перший мінімальний елементи в масиві.Написати
специфікацію функції - шаблон для типу char*/


template<typename T>
void swapFirstMaxMin(T arr[], int size) {
    if (size <= 1) return;

    // Знаходження максимального та мінімального елементів
    T maxElem = arr[0];
    T minElem = arr[0];
    int maxIndex = 0;
    int minIndex = 0;

    for (int i = 1; i < size; ++i) {
        if (arr[i] > maxElem) {
            maxElem = arr[i];
            maxIndex = i;
        }
        else if (arr[i] < minElem) {
            minElem = arr[i];
            minIndex = i;
        }
    }

    // Перестановка максимального та мінімального елементів
    T temp = arr[0];
    arr[0] = arr[minIndex];
    arr[minIndex] = temp;

    temp = arr[size - 1];
    arr[size - 1] = arr[maxIndex];
    arr[maxIndex] = temp;
}

// Специфікація функції-шаблону для типу const char*
template<>
void swapFirstMaxMin<const char*>(const char* arr[], int size) {
    if (size <= 1) return;

    const char* maxElem = arr[0];
    const char* minElem = arr[0];
    int maxIndex = 0;
    int minIndex = 0;

    for (int i = 1; i < size; ++i) {
        if (std::strcmp(arr[i], maxElem) > 0) {
            maxElem = arr[i];
            maxIndex = i;
        }
        else if (std::strcmp(arr[i], minElem) < 0) {
            minElem = arr[i];
            minIndex = i;
        }
    }

    const char* temp = arr[0];
    arr[0] = arr[minIndex];
    arr[minIndex] = temp;

    temp = arr[size - 1];
    arr[size - 1] = arr[maxIndex];
    arr[maxIndex] = temp;
}

int main1() {
    int intArr[] = { 3, 1, 7, 4, 2 };
    const char* charArr[] = { "banana", "apple", "grape", "kiwi", "orange" };

    std::cout << "Before swapping: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << intArr[i] << " ";
    }
    std::cout << std::endl;

    swapFirstMaxMin(intArr, 5);

    std::cout << "After swapping: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << intArr[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Before swapping: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << charArr[i] << " ";
    }
    std::cout << std::endl;

    swapFirstMaxMin(charArr, 5);

    std::cout << "After swapping: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << charArr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

/*Задача 2.3. Написати функцію-шаблон функцію впорядкування методом
«Вставки». Написати специфікацію функції-шаблон для типу char*.*/
#include <iostream>
#include <cstring>

// Функція-шаблон для сортування методом вставки
template<typename T>
void insertionSort(T arr[], int size) {
    for (int i = 1; i < size; ++i) {
        T key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Специфікація функції-шаблону для типу const char*
template<>
void insertionSort<const char*>(const char* arr[], int size) {
    for (int i = 1; i < size; ++i) {
        const char* key = arr[i];
        int j = i - 1;

        while (j >= 0 && std::strcmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main2() {
    // Приклад використання функції-шаблону для сортування чисел
    int intArr[] = { 3, 1, 7, 4, 2 };
    int intSize = sizeof(intArr) / sizeof(intArr[0]);
    insertionSort(intArr, intSize);
    std::cout << "Sorted int array: ";
    for (int i = 0; i < intSize; ++i) {
        std::cout << intArr[i] << " ";
    }
    std::cout << std::endl;

    // Приклад використання функції-шаблону для сортування рядків
    const char* strArr[] = { "banana", "apple", "grape", "kiwi", "orange" };
    int strSize = sizeof(strArr) / sizeof(strArr[0]);
    insertionSort(strArr, strSize);
    std::cout << "Sorted string array: ";
    for (int i = 0; i < strSize; ++i) {
        std::cout << strArr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
/* Задача 3.3. Створити параметризованную черга.*/
#include <iostream>

template<typename T>
class QueueNode {
public:
    T data;
    QueueNode<T>* next;

    QueueNode(const T& newData) : data(newData), next(nullptr) {}
};

template<typename T>
class Queue {
private:
    QueueNode<T>* front;
    QueueNode<T>* rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    int getSize() const {
        return size;
    }

    void enqueue(const T& newData) {
        QueueNode<T>* newNode = new QueueNode<T>(newData);
        if (isEmpty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    T dequeue() {
        if (isEmpty()) {
            std::cerr << "Queue is empty. Cannot dequeue.\n";
            return T(); // Повертаємо значення за замовчуванням для типу T
        }
        T data = front->data;
        QueueNode<T>* temp = front;
        front = front->next;
        delete temp;
        size--;
        if (isEmpty()) {
            rear = nullptr;
        }
        return data;
    }

    T getFront() const {
        if (isEmpty()) {
            std::cerr << "Queue is empty. No front element.\n";
            return T(); // Повертаємо значення за замовчуванням для типу T
        }
        return front->data;
    }
};

int main3() {
    Queue<int> intQueue;

    intQueue.enqueue(10);
    intQueue.enqueue(20);
    intQueue.enqueue(30);

    std::cout << "Front element: " << intQueue.getFront() << std::endl;

    std::cout << "Dequeue: " << intQueue.dequeue() << std::endl;
    std::cout << "Dequeue: " << intQueue.dequeue() << std::endl;

    intQueue.enqueue(40);
    intQueue.enqueue(50);

    std::cout << "Size of the queue: " << intQueue.getSize() << std::endl;

    while (!intQueue.isEmpty()) {
        std::cout << "Dequeue: " << intQueue.dequeue() << std::endl;
    }

    return 0;
}


/*. Побудувати клас, що описує лінійний двох зв’язний список.
Побудувати клас ітератор, що дозволяє проходити список.  */


#include <iostream>

// Клас, що описує вузол двозв'язного списку
template<typename T>
class Node {
public:
    T data;
    Node<T>* prev;
    Node<T>* next;

    Node(const T& newData) : data(newData), prev(nullptr), next(nullptr) {}
};

// Клас, що описує лінійний двозв'язний список
template<typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    // Конструктор за замовчуванням
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Деструктор
    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    // Метод, що перевіряє, чи є список порожнім
    bool isEmpty() const {
        return size == 0;
    }

    // Метод, що повертає розмір списку
    int getSize() const {
        return size;
    }

    // Метод, що додає елемент в кінець списку
    void append(const T& newData) {
        Node<T>* newNode = new Node<T>(newData);
        if (isEmpty()) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    // Клас ітератора для проходження по списку
    class Iterator {
    private:
        Node<T>* current;

    public:
        Iterator(Node<T>* node) : current(node) {}

        // Перевірка наявності наступного елемента
        bool hasNext() const {
            return current != nullptr;
        }

        // Переведення ітератора на наступний елемент
        void next() {
            if (current != nullptr) {
                current = current->next;
            }
        }

        // Отримання даних поточного елемента
        T getData() const {
            if (current != nullptr) {
                return current->data;
            }
            throw std::out_of_range("Iterator is out of range.");
        }
    };

    // Метод, що повертає початковий ітератор списку
    Iterator begin() const {
        return Iterator(head);
    }

    // Метод, що повертає кінцевий ітератор списку
    Iterator end() const {
        return Iterator(nullptr);
    }
};

int main() {
    // Приклад використання класу лінійного двозв'язного списку та класу ітератора
    DoublyLinkedList<int> list;
    list.append(10);
    list.append(20);
    list.append(30);

    // Проходження списку за допомогою ітератора
    std::cout << "List elements: ";
    for (DoublyLinkedList<int>::Iterator it = list.begin(); it.hasNext(); it.next()) {
        std::cout << it.getData() << " ";
    }
    std::cout << std::endl;

    return 0;
}
