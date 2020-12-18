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

  T& operator[](int);
  int capacity() const;
  bool empty() const;
  int size() const;
  void push_back(const T& element);
  T& at(int index);



private:
  void check_rezise();

  int m_capacity = 20;
  T* m_elements = new T[m_capacity];

  T* temp_ptr = nullptr;

  int m_size = 0;
};

template <class T>
Vector<T>::Vector() {}

template <class T>
Vector<T>::~Vector() {}

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
  this->check_rezise();;
}

template <class T>
T& Vector<T>::at(int index) {
  return m_elements[index];
}

template <class T>
void Vector<T>::check_rezise() {
  if(m_size == m_capacity) {
    m_capacity = m_capacity + 20;
    temp_ptr = m_elements;

    m_elements = new T[m_capacity];
    for (int i = 0; i < m_size; i++) {
      m_elements[i] = temp_ptr[i];
    }
    delete[] temp_ptr;
    temp_ptr = nullptr;
  }
}

#endif
