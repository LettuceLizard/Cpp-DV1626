#ifndef VECTOR_HPP
#define VECTOR_HPP

template <typename T>
class Vector {
public:
  Vector();
  ~Vector();
  Vector(const Vector&);
  Vector(Vector&&);

  Vector& operator=(const Vector&);
  Vector& operator=(Vector&&);


  const T* data();
  void insert(int index, const T& element);
  void erase(int index);
  T& front() const;
  T& back() const;
  void clear();
  void pop_back();
  int capacity() const;
  bool empty() const;
  int size() const;
  void push_back(const T& element);
  T& at(int index);
  T& operator[](int index);



private:
  void rezise();
  int m_capacity = 20;
  T* m_elements = new T[m_capacity];
  T* temp_ptr = nullptr;
  int m_size = 0;
};

/*
fixme(1): currently there is nothing to stop the user from using insert(index, element)
at an index larger than the current elements. DOES only increases the m_size of the
object

addfeature(): vector.at(index) should return nothing if index is out of range,
vector[index] shoud throw error if index out of range.
*/

template <class T>
Vector<T>::Vector() {}

template <class T>
Vector<T>::~Vector() {
  delete[] m_elements;
  m_elements = nullptr;
}

template <class T>
const T* Vector<T>::data() {
  return m_elements;
}

template <class T>
void Vector<T>::insert(int index, const T& element) { //(1)
  m_size++;
  temp_ptr = m_elements;
  m_elements = new T[m_capacity];
  for (int i = 0; i < m_size; i++) {
    if(index == i) {
       m_elements[index] = element;
       i++;
    }
    m_elements[i] = temp_ptr[i];
  }
  delete[] temp_ptr;
  temp_ptr = nullptr;
}


template <class T>
void Vector<T>::erase(int index) {
  m_size--;
  temp_ptr = m_elements;
  m_elements = new T[m_capacity];
  for (int i = 0; i < m_size; i++) {
    if(index == i) {
      i--;
      continue;
    }
      m_elements[i] = temp_ptr[i];
  }
  delete[] temp_ptr;
  temp_ptr = nullptr;
}

template <class T>
T& Vector<T>::front() const {
    return m_elements[0];
}

template <class T>
T& Vector<T>::back() const{
  return m_elements[m_size];
}

template <class T>
void Vector<T>::clear() {
  m_size = 0;
}

template <class T>
void Vector<T>::pop_back() {
  m_size--;
}

template <class T>
int Vector<T>::capacity() const {
  return m_capacity;
}

template <class T>
bool Vector<T>::empty() const {
  return m_size==0?true:false;
}

template <class T>
int Vector<T>::size() const {
  return m_size;
}

template <class T>
void Vector<T>::push_back(const T& element) {
  m_elements[m_size] = element;
  m_size++;
  if(m_size == m_capacity) {
    this->rezise();
  }
}

template <class T>
T& Vector<T>::operator[](int index) {
  return m_elements[index];
}

template <class T>
T& Vector<T>::at(int index) {
  return m_elements[index];
}

template <class T>
void Vector<T>::rezise() {
    m_capacity = m_capacity + 20;
    temp_ptr = m_elements;

    m_elements = new T[m_capacity];
    for (int i = 0; i < m_size; i++) {
      m_elements[i] = temp_ptr[i];
    }
    delete[] temp_ptr;
    temp_ptr = nullptr;

}

#endif
