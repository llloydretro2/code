#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include "iostream"

/**
 * Implementation of a hash table that stores key-value
 * pairs mapping unsigned integers to instances of
 * ValueType.
 *
 * Hash function: key % tableSize
 * Collision resolution: quadratic probing.
 * Non-unique keys are not supported.
 *
 * Any use of the term "element" refers to a key-value pair.
 *
 * Some functions have runtime requirements.
 * During lecture, I mentioned that when talking about hash
 * tables, people tend to talk as if common hash table
 * operations take constant time, even though this is false.
 * Here, any mention of "constant time" in double quotes means
 * "amortized constant time on average", i.e. you should
 * use hashing to speed things up and not iterate through
 * all the buckets, ignoring the hash function. For instance,
 * it is required that you implement delete() in "constant
 * time", so you cannot take the inefficient approach of
 * searching for the relevant key by iterating 
 * bucket-by-bucket.
 *
 * The table rehashes whenever the insertion of a new
 * element would put the load factor at at least 1/2.
 * (The rehashing is done before the element would've been inserted.)
 * Upon a rehash, the table size (let's call it m) should
 * be increased to the lowest prime number that is greater
 * than or equal to 2m. Elements are then transferred
 * from the "old table" to the "new/larger table" in the
 * order in which they appear in the old table, and then
 * the new element is finally inserted.
 */

template <typename ValueType>
struct Pair {
    unsigned key;
    ValueType value;
    bool existence = false;
};


template <typename ValueType>
class HashTable
{
public:
    /**
     * Creates a hash table with the given number of
     * buckets/slots.
     *
     * Throws std::runtime_error if @tableSize is 0 or not
     * prime.
     */
    explicit HashTable(unsigned tableSize){
        if(tableSize == 0 || tableSize == 1){
            throw std::runtime_error("Not prime");
        }
        for (unsigned i = 2; i < tableSize; ++i) {
            if (tableSize % i == 0){
                throw std::runtime_error("Not prime");
            }
        }
        this->hashtable = new Pair<ValueType>[tableSize];
        this->tablesize = tableSize;
    }

    ~HashTable(){
        delete[] hashtable;
    }

    /**
     * Makes the underlying hash table of this object look
     * exactly the same as that of @rhs.
     */
    HashTable(const HashTable& rhs){
        hashtable = new Pair<ValueType>[rhs.tablesize];
        tablesize = rhs.tablesize;
        elementnum = rhs.elementnum;
        for (unsigned i = 0; i < tablesize; ++i) {
            hashtable[i] = rhs.hashtable[i];
        }
    }
    HashTable& operator=(const HashTable& rhs){
        hashtable = new Pair<ValueType>[rhs.tablesize];
        tablesize = rhs.tablesize;
        elementnum = rhs.elementnum;
        for (unsigned i = 0; i < tablesize; ++i) {
            hashtable[i] = rhs.hashtable[i];
        }
        return *this;
    }

    /**
     * Takes the underlying implementation details of @rhs
     * and gives them to "this" object.
     * After this, @rhs should be in a "moved from" state.
     */
    HashTable(HashTable&& rhs) noexcept{
        tablesize = rhs.tablesize;
        elementnum = rhs.elementnum;
        hashtable = rhs.hashtable;
        rhs.tablesize = 0;
        rhs.elementnum = 0;
        rhs.hashtable = NULL;
    }
    HashTable& operator=(HashTable&& rhs) noexcept{
        tablesize = rhs.tablesize;
        elementnum = rhs.elementnum;
        hashtable = rhs.hashtable;
        rhs.tablesize = 0;
        rhs.elementnum = 0;
        rhs.hashtable = NULL;
        return *this;
    }

    /**
     * Both of these must run in constant time.
     */
    unsigned tableSize() const
    {
        return this->tablesize;
    }
    unsigned numElements() const
    {
        return this->elementnum;
    }

    /**
     * Prints each bucket in the hash table.
     * See prog_hw4.pdf for how exactly this should look.
     *
     * I don't think that a friend of a templated class can
     * be defined outside of the class. If you can figure
     * out how to do that in a way that works on the CSIF,
     * go for it.
     */
    friend std::ostream& operator<<(std::ostream& os,
                                    const HashTable<ValueType>& ht)
    {
        // TODO: Implement this method.
        for (unsigned i = 0; i < ht.tableSize(); ++i) {
            os << "Bucket " << i << ": ";
            if (ht.hashtable[i].existence == false){
                os << "(empty)" << std::endl;
            }
            else {
                os << ht.hashtable[i].key << " -> " << ht.hashtable[i].value << std::endl;
            }
        }
        return os;
    }

    /**
     * Inserts a key-value pair mapping @key to @value into
     * the table.
     *
     * This function must run in "constant time".
     *
     * Returns true if success.
     * Returns false if @key is already in the table
     * (in which case, the insertion is not performed).
     */
    bool insert(unsigned key, const ValueType& value){
        if (get(key) != nullptr){
            return false;
        }
        unsigned insertPostion = key % tablesize;
        unsigned tempInsertPosition;
        if (hashtable[insertPostion].existence != false){
            for (unsigned i = 1; i < 5; ++i){
                tempInsertPosition = insertPostion + i*i;
                if (tempInsertPosition > (tablesize - 1)) {
                    tempInsertPosition -= tablesize;
                }
                if (hashtable[tempInsertPosition].existence == false){
                    hashtable[tempInsertPosition].key = key;
                    hashtable[tempInsertPosition].value = value;
                    hashtable[tempInsertPosition].existence = true;
                    elementnum++;
                    if (loadFactor()){
//                        std::cout << "TRUE: " << elementnum << "     " << tablesize << std::endl;
                        reHash();
                    }
//                    std::cout << key << " -> " << value << std::endl;
                    return true;
                }
            }
        }
        else{
            hashtable[insertPostion].key = key;
            hashtable[insertPostion].value = value;
            hashtable[insertPostion].existence = true;
            elementnum++;
            if (loadFactor()) {
//                std::cout << "TRUE: " << elementnum << "     " << tablesize << std::endl;
                reHash();
            }
//            std::cout << key << " ->" << value << std::endl;
            return true;
        }
        return false;
    }

    bool loadFactor(){
        float floatTableSize = tablesize;
        if (elementnum > (floatTableSize /2)){
            return true;
        }
        return false;
    }

    unsigned getNewTableSize(unsigned tableSize){
        unsigned newTableSize = tableSize * 2;
        while (true) {
            unsigned upperLimit = newTableSize;
            for (unsigned i = 2; i <upperLimit; ++i) {
                if (newTableSize % i == 0){
                    newTableSize++;
                    continue;
                }
            }
            return newTableSize;
        }
    }

    void reHash() {
        unsigned newTableSize = getNewTableSize(tablesize);
        Pair<ValueType> *returnHashTable = new Pair<ValueType>[newTableSize];
        Pair<ValueType> *newHashTable = new Pair<ValueType>[tablesize];
        for (unsigned i = 0; i < tablesize; ++i) {
            if (hashtable[i].existence == true){
                newHashTable[i] = hashtable[i];
            }
        }
        tablesize = newTableSize;
        elementnum = 0;
        hashtable = returnHashTable;
        for (unsigned i = 0; i < tablesize; ++i) {
            if (newHashTable[i].existence == true){
                this->insert(newHashTable[i].key, newHashTable[i].value);
            }
        }
    }

    /**
     * Finds the value corresponding to the given key
     * and returns its address.
     *
     * This function must run in "constant time".
     *
     * Returns null pointer if @key is not in the table.
     */
    ValueType* get(unsigned key){
        unsigned position = key % tablesize;
        unsigned tempPosition;
        if (hashtable[position].key == key && hashtable[position].existence == true){
            return &hashtable[position].value;
        }
        else{
            for (unsigned i = 1; i < 5; ++i) {
                tempPosition = position + i*i;
                if (tempPosition > (tablesize -1)) {
                    tempPosition -= tablesize;
                }
                if (hashtable[tempPosition].key == key){
                    if (hashtable[tempPosition].existence == true){
                        return &hashtable[tempPosition].value;
                    }
                }
            }
        }

        return NULL;
    }
    const ValueType* get(unsigned key) const{
        unsigned position = key % tablesize;
        unsigned tempPosition;
        if (hashtable[position].key == key && hashtable[position].existence == true){
            return &hashtable[position].value;
        }
        else{
            for (unsigned i = 1; i < 5; ++i) {
                tempPosition = position + i*i;
                if (tempPosition > (tablesize -1)) {
                    tempPosition -= tablesize;
                }
                if (hashtable[tempPosition].key == key){
                    if (hashtable[tempPosition].existence == true){
                        return &hashtable[tempPosition].value;
                    }
                }
            }
        }

        return nullptr;
    }

    /**
     * Updates the key-value pair with key @key to be
     * mapped to @newValue.
     *
     * This function must run in "constant time".
     *
     * Returns true if success.
     * Returns false if @key is not in the table.
     */
    bool update(unsigned key, const ValueType& newValue){
        unsigned position = key % tablesize;
        unsigned tempPosition;
        if (hashtable[position].key != key){
            for (unsigned i = 1; i < 5; ++i) {
                tempPosition = position + i*i;
                if (tempPosition > (tablesize-1)){
                    tempPosition -= tablesize;
                }
                if (hashtable[tempPosition].key == key){
                    if (hashtable[tempPosition].existence == true){
                        hashtable[tempPosition].value = newValue;
                        return true;
                    }
                }
            }
        } else{
            if (hashtable[position].existence == true){
                hashtable[position].value = newValue;
                return true;
            }
        }
        return false;
    }

    /**
     * Deletes the element that has the given key.
     *
     * This function must run in "constant time".
     *
     * Returns true if success.
     * Returns false if @key not found.
     */
    bool remove(unsigned key){

        unsigned position = key % tablesize;
        unsigned tempPosition;
        if (hashtable[position].key != key || hashtable[position].existence != true){
            for (unsigned i = 1; i < 5; ++i) {
                tempPosition = position + i*i;
                if (hashtable[tempPosition].key == key){
                    if (hashtable[tempPosition].existence == true){
                        hashtable[tempPosition].existence = false;
                        elementnum--;
                        return true;
                    }
                }
            }
        } else{
            if (hashtable[position].existence == true){
                hashtable[position].existence = false;
                elementnum--;
                return true;
            }
        }
        return false;
    }

    /**
     * Deletes all elements that have the given value.
     *
     * Returns the number of elements deleted.
     */
    unsigned removeAllByValue(const ValueType& value){
        unsigned deletionCount = 0;
        for (unsigned i = 0; i < tablesize; ++i) {
            if (hashtable[i].value == value and hashtable[i].existence == true){
                hashtable[i].existence = false;
                deletionCount++;
                elementnum--;
            }
        }
        return deletionCount;
    }

    /**
     * Two instances of HashTable<ValueType> are considered 
     * equal if they contain the same elements, even if those
     * elements are in different buckets (i.e. even if the
     * hash tables have different sizes).
     */
    bool operator==(const HashTable& rhs) const{
        if (elementnum != rhs.elementnum){
            return false;
        }
        bool existState;
        for (unsigned i = 0; i < tablesize; ++i) {
            if (hashtable[i].existence == true) {
                existState = false;
                for (unsigned j = 0; j < rhs.tablesize; ++j) {
                    if ((hashtable[i].value == rhs.hashtable[j].value) && (hashtable[i].key == rhs.hashtable[j].key) && rhs.hashtable[j].existence == true) {
                        existState = true;
                    }

                }
                if (!existState){
                    return false;
                }
            }
        }
        return true;
    }
    bool operator!=(const HashTable& rhs) const{
        if (elementnum != rhs.elementnum){
            return true;
        }
        for (unsigned i = 0; i < tablesize; ++i) {
            for (unsigned j = 0; j < rhs.tablesize; ++j) {
                if ((hashtable[i].value != rhs.hashtable[j].value) && (hashtable[i].key == rhs.hashtable[j].key)) {
                    if (hashtable[i].existence == true && rhs.hashtable[i].existence == true){
                        return true;
                    }
                }
            }
        }
        return false;
    }

    /**
     * Returns a newly constructed hash table that is the hash table
     * that would result from inserting each element from @rhs
     * (in the order that they appear in the buckets)
     * into this (i.e. *this) hash table.
     */
    HashTable operator+(const HashTable& rhs) const{
        HashTable<ValueType> newHashtable(*this);
        for (unsigned i = 0; i < rhs.tablesize; ++i) {
            if (rhs.hashtable[i].existence == true) {
                newHashtable.insert(rhs.hashtable[i].key, rhs.hashtable[i].value);
            }
        }
        return newHashtable;
    }

private:
    // TODO: Your members here.
    Pair<ValueType> *hashtable;
    unsigned tablesize = 0;
    unsigned elementnum = 0;
};

#include "hash_table.inl"
#endif  // HASH_TABLE_HPP
