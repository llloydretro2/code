#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "hash_table.hpp"

/**
 * Implementation of a priority queue that supports the
 * extended API discussed during lecture. This priority
 * queue maps unsigned values to instances of ValueType.
 * You are required to use a hash table to efficiently
 * support the operations of the extended API.
 *
 * As with the hash table, any use of the term "element" here
 * refers to a key-value pair.
 *
 * As with the hash table (see the block comment right before the
 * definition of class HahsTable), any mention of "constant time" in
 * double quotes means "amortized constant time on average",
 * i.e. you should use hashing / the required hash table
 * to speed things up and not iterate through the entire underlying
 * binary heap array unnecessarily.
 *
 * The priority queue's underlying implementation is
 * required to be a binary min heap and the hash table
 * that you implement in the first part of this assignment.
 */
template <typename ValueType>
struct Node {
    unsigned key;
    ValueType value;
    bool state = false;
};

template <typename ValueType>
class PriorityQueue
{
public:
    /**
     * Creates a priority queue that can have at most @maxSize elements.
     *
     * Throws std::runtime_error if @maxSize is 0.
     */
    explicit PriorityQueue(unsigned maxSize) {
        this->priorityqueue = new Node<ValueType>[maxSize];
        maxsize = maxSize;
    }

    ~PriorityQueue() {
        delete[] priorityqueue;
    }

    /**
     * Makes the underlying implementation details (including the max size) look
     * exactly the same as that of @rhs.
     */
    PriorityQueue(const PriorityQueue& rhs) : hashTable(std::move(rhs.hashTable)) {
        priorityqueue = new Node<ValueType>[rhs.maxSize()];
        maxsize = rhs.maxsize;
        elementnum = rhs.elementnum;
        for (unsigned i = 0; i < elementnum; ++i) {
            priorityqueue[i] = rhs.priorityqueue[i];
        }
    }
    PriorityQueue& operator=(const PriorityQueue& rhs) {
        hashTable = rhs.hashTable;
        priorityqueue = new Node<ValueType>[rhs.maxSize()];
        maxsize = rhs.maxsize;
        elementnum = rhs.elementnum;
        for (unsigned i = 0; i < maxsize; ++i) {
            priorityqueue[i] = rhs.priorityqueue[i];
        }
        return *this;
    }

    /**
     * Takes the underlying implementation details of @rhs
     * and gives them to "this" object.
     * After this, @rhs should be in a "moved from" state.
     */
    PriorityQueue(PriorityQueue&& rhs) noexcept: hashTable(std::move(rhs.hashTable)){
        priorityqueue = rhs.priorityqueue;
        maxsize = rhs.maxsize;
        elementnum = rhs.elementnum;

        rhs.priorityqueue = NULL;
        rhs.elementnum = 0;
        rhs.maxsize = 0;
    }
    PriorityQueue& operator=(PriorityQueue&& rhs) noexcept{
        priorityqueue = rhs.priorityqueue;
        maxsize = rhs.maxsize;
        elementnum = rhs.elementnum;
        rhs.priorityqueue = NULL;
        rhs.hashTable = NULL;
        rhs.elementnum = 0;
        rhs.maxsize = 0;
        return *this;
    }

    /**
     * Both of these must run in constant time.
     */
    unsigned numElements() const {
        return elementnum;
    }
    unsigned maxSize() const {
        return maxsize;
    }

    /**
     * Print the underlying heap level-by-level.
     * See prog_hw4.pdf for how exactly this should look.
     */
    friend std::ostream& operator<<(
        std::ostream& os,
        const PriorityQueue<ValueType>& pq)
    {
        // TODO: Implement this method.

        unsigned layerLimit = 1;
        unsigned total = 1;
        unsigned elementCount = 0;
        for (unsigned i = 0; i < pq.numElements(); ++i) {
            elementCount++;
            os << "(" << pq.priorityqueue[i].key << "," << pq.priorityqueue[i].value << ")";
            if (elementCount == total) {
                os << std::endl;
                total = total + layerLimit*2;
                layerLimit = layerLimit *2;

            }
            else{
                if (i == pq.numElements()-1){
                    os << std::endl;
                }
                else{
                    os << " ";
                }
            }
        }
        
        return os;
    }

    /**
     * Inserts a key-value pair mapping @key to @value into
     * the priority queue.
     *
     * Returns true if success.
     * In this case, must run in logarithmic time.
     *
     * Returns false if @key is already in the priority queue
     * or if max size would be exceeded.
     * (In either of these cases, the insertion is not performed.)
     * In this case, must run in "constant time".
     */
    bool insert(unsigned key, const ValueType& value) {
        if (hashTable->get(key)) {
            return false;
        }
        if ((elementnum+1) > maxsize){
            return false;
        }
        unsigned position = elementnum;
        Node<ValueType> tempNode;

        priorityqueue[position].value = value;
        priorityqueue[position].key = key;
        priorityqueue[position].state = true;
        if (position == 0) {
            hashTable->insert(key, position);
            elementnum++;
            return true;
        }
        while (priorityqueue[(position-1)/2].key > priorityqueue[position].key){
            switchHash(priorityqueue[(position-1)/2].key, (position-1)/2, priorityqueue[position].key, position);
            tempNode = priorityqueue[(position-1)/2];
            priorityqueue[(position-1)/2] = priorityqueue[position];
            priorityqueue[position] = tempNode;
            position = (position-1)/2;
            if (position == 0){
                break;
            }
        }
        hashTable->insert(key, position);
        elementnum++;

        return true;
    }

    void switchHash(unsigned key1, unsigned value1, unsigned key2, unsigned value2){
        hashTable->update(key1, value2);
        hashTable->update(key2, value1);

    }


    /**
     * Returns key of the smallest element in the priority queue
     * or null pointer if empty.
     *
     * This function must run in constant time.
     *
     * The pointer may be invalidated if the priority queue is modified.
     */
    const unsigned* getMinKey() const
    {
        if (elementnum == 0){
            return NULL;
        }
        return &priorityqueue[0].key;
    }

    /**
     * Returns value of the smallest element in the priority queue
     * or null pointer if empty.
     *
     * This function must run in constant time.
     *
     * The pointer may be invalidated if the priority queue is modified.
     */
    const ValueType* getMinValue() const{
        if (elementnum == 0){
            return NULL;
        }
        return &priorityqueue[0].value;
    }

    /**
     * Removes the root of the priority queue.
     *
     * This function must run in logarithmic time.
     *
     * Returns true if success.
     * Returns false if priority queue is empty, i.e. nothing to delete.
     */
    bool deleteMin() {
        if (elementnum == 0){
            return false;
        }
        hashTable->remove(*getMinKey());
        elementnum--;
        hashTable->update(priorityqueue[elementnum].key, 0);
        priorityqueue[0] = priorityqueue[elementnum];
        Node<ValueType> emptyNode;
        priorityqueue[elementnum] = emptyNode;
        Node<ValueType> tempNode;

        unsigned position = 0;
        unsigned left = 1;
        unsigned right = 2;
        unsigned compareLeft;
        unsigned compareRight;

        while(true){
//            std::cout << *hashTable;
//            std::cout << "SELF: " << priorityqueue[position].key << std::endl;
//            std::cout << "LEFT: " << priorityqueue[left].key << std::endl;
//            std::cout << "RIGHT: " << priorityqueue[right].key << std::endl;
            compareLeft = 0;
            compareRight = 0;
            if (priorityqueue[left].state == false && priorityqueue[right].state == false){
                return true;
            }

            if (priorityqueue[left].state == true){
                if (priorityqueue[left].key < priorityqueue[position].key) {
                    compareLeft = priorityqueue[position].key - priorityqueue[left].key;
                }

            }
            else {
                compareLeft = 0;
            }

            if (priorityqueue[right].state == true){
                if (priorityqueue[right].key < priorityqueue[position].key) {
                    compareRight = priorityqueue[position].key - priorityqueue[right].key;
                }
            }
            else{
                compareRight = 0;
            }

            if (compareLeft == 0 && compareRight == 0) {
                return true;
            }

            if (compareLeft > compareRight) {
                switchHash(priorityqueue[position].key, position, priorityqueue[left].key, left);
                tempNode = priorityqueue[position];
                priorityqueue[position] = priorityqueue[left];
                priorityqueue[left] = tempNode;
                position = left;
            }
            else {
                switchHash(priorityqueue[position].key, position, priorityqueue[right].key, right);
                tempNode = priorityqueue[position];
                priorityqueue[position] = priorityqueue[right];
                priorityqueue[right] = tempNode;
                position = right;
            }
            left = position * 2 + 1;
            right = position * 2 + 2;

        }
    }

    /**
     * Returns address of the value that @key is mapped to in the priority queue.
     *
     * These functions must run in "constant time".
     *
     * Returns null pointer if @key is not in the table.
     */
    ValueType* get(unsigned key){
        if (hashTable->get(key) == nullptr) {
            return nullptr;
        }
        unsigned position = *hashTable->get(key);
        return &priorityqueue[position].value;
    }
    const ValueType* get(unsigned key) const{
        if (hashTable->get(key) == nullptr) {
            return nullptr;
        }
        unsigned position = *hashTable->get(key);
//        for (unsigned i = 0; i < elementnum; ++i) {
//            if (priorityqueue[i].key == key){
//                return priorityqueue[i].value;
//            }
//        }
        return &priorityqueue[position].value;    }

    /**
     * Subtracts/adds @change from/to the key of
     * the element that has key @key.
     *
     * These functions must run in "constant time" + logarithmic time.
     * This means you must use the required hash table to find the
     * location of @key in the underlying binary heap array.
     *
     * Returns true if success.
     * Returns false if any of the following:
     * - @change is 0.
     * - @key not found.
     * - If the change would lead to a duplicate key.
     *
     * The function does not do anything about  overflow/underflow.
     * For example, an operation like decreaseKey(2, 10)
     * has an undefined effect.
     */
    bool decreaseKey(unsigned key, unsigned change){
        if (!hashTable->get(key)){
            return false;
        }
        if (hashTable->get(key-change)){
            return false;
        }
        unsigned position = *hashTable->get(key);
        hashTable->remove(key);
        hashTable->insert(key-change, position);
        Node<ValueType> tempNode;
        priorityqueue[position].key -= change;

        while (priorityqueue[(position-1)/2].key > priorityqueue[position].key){
            switchHash(priorityqueue[(position-1)/2].key, (position-1)/2, priorityqueue[position].key, position);
            tempNode = priorityqueue[(position-1)/2];
            priorityqueue[(position-1)/2] = priorityqueue[position];
            priorityqueue[position] = tempNode;
            position = (position-1)/2;
            if (position == 0){
                break;
            }
        }
        return true;

    }
    bool increaseKey(unsigned key, unsigned change){

        if (!hashTable->get(key)){
            return false;
        }
        if (hashTable->get(key+change)){
            return false;
        }
        unsigned position = *hashTable->get(key);
        hashTable->remove(key);
        hashTable->insert(key+change, position);
        Node<ValueType> tempNode;
        priorityqueue[position].key += change;

        unsigned left = position * 2 + 1;
        unsigned right = position * 2 + 2;
        unsigned compareLeft;
        unsigned compareRight;

        while(true){
//            std::cout << *hashTable;
//            std::cout << "SELF: " << priorityqueue[position].key << std::endl;
//            std::cout << "LEFT: " << priorityqueue[left].key << std::endl;
//            std::cout << "RIGHT: " << priorityqueue[right].key << std::endl;
            compareLeft = 0;
            compareRight = 0;
            if (priorityqueue[left].state == false && priorityqueue[right].state == false){
                return true;
            }

            if (priorityqueue[left].state == true){
                if (priorityqueue[left].key < priorityqueue[position].key) {
                    compareLeft = priorityqueue[position].key - priorityqueue[left].key;
                }

            }
            else {
                compareLeft = 0;
            }

            if (priorityqueue[right].state == true){
                if (priorityqueue[right].key < priorityqueue[position].key) {
                    compareRight = priorityqueue[position].key - priorityqueue[right].key;
                }
            }
            else{
                compareRight = 0;
            }

            if (compareLeft == 0 && compareRight == 0) {
                return true;
            }

            if (compareLeft > compareRight) {
                switchHash(priorityqueue[position].key, position, priorityqueue[left].key, left);
                tempNode = priorityqueue[position];
                priorityqueue[position] = priorityqueue[left];
                priorityqueue[left] = tempNode;
                position = left;
            }
            else {
                switchHash(priorityqueue[position].key, position, priorityqueue[right].key, right);
                tempNode = priorityqueue[position];
                priorityqueue[position] = priorityqueue[right];
                priorityqueue[right] = tempNode;
                position = right;
            }
            left = position * 2 + 1;
            right = position * 2 + 2;

        }


    }

    /**
     * Removes element that has key @key.
     *
     * These functions must run in "constant time" + logarithmic time.
     * This means you must use the required hash table to find the
     * location of @key in the underlying binary heap array.
     *
     * Returns true if success.
     * Returns false if @key not found.
     */
    bool remove(unsigned key){
        if (hashTable->get(key) == NULL){
            return false;
        }
        if (hashTable->get(key) == 0){
            this->deleteMin();

            return true;
        }

        unsigned position = *hashTable->get(key);
        hashTable->update(priorityqueue[elementnum-1].key, position);
        hashTable->remove(key);
        Node<ValueType> tempNode;

        priorityqueue[position] = priorityqueue[elementnum-1];
        Node<ValueType> emptyNode;
        priorityqueue[elementnum-1] = emptyNode;

        elementnum--;

        unsigned left = position * 2 + 1;
        unsigned right = position * 2 + 2;
        unsigned compareLeft;
        unsigned compareRight;


        while(true){
//            std::cout << *hashTable;
//            std::cout << "SELF: " << priorityqueue[position].key << std::endl;
//            std::cout << "LEFT: " << priorityqueue[left].key << std::endl;
//            std::cout << "RIGHT: " << priorityqueue[right].key << std::endl;
            compareLeft = 0;
            compareRight = 0;
            if (priorityqueue[left].state == false && priorityqueue[right].state == false){
                return true;
            }

            if (priorityqueue[left].state == true){
                if (priorityqueue[left].key < priorityqueue[position].key) {
                    compareLeft = priorityqueue[position].key - priorityqueue[left].key;
                }

            }
            else {
                compareLeft = 0;
            }

            if (priorityqueue[right].state == true){
                if (priorityqueue[right].key < priorityqueue[position].key) {
                    compareRight = priorityqueue[position].key - priorityqueue[right].key;
                }
            }
            else{
                compareRight = 0;
            }

            if (compareLeft == 0 && compareRight == 0) {
                return true;
            }

            if (compareLeft > compareRight) {
                switchHash(priorityqueue[position].key, position, priorityqueue[left].key, left);
                tempNode = priorityqueue[position];
                priorityqueue[position] = priorityqueue[left];
                priorityqueue[left] = tempNode;
                position = left;
            }
            else {
                switchHash(priorityqueue[position].key, position, priorityqueue[right].key, right);
                tempNode = priorityqueue[position];
                priorityqueue[position] = priorityqueue[right];
                priorityqueue[right] = tempNode;
                position = right;
            }
            left = position * 2 + 1;
            right = position * 2 + 2;

        }
    }

private:
    // TODO: Your members here.
    Node<ValueType> *priorityqueue;
    unsigned maxsize;
    unsigned elementnum = 0;
    HashTable<unsigned > *hashTable = new HashTable<unsigned >(17);
};

#include "priority_queue.inl"
#endif  // PRIORITY_QUEUE_HPP
