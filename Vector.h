#include <stdexcept>

template <typename T> class Vector {
public:
  Vector() : data_{nullptr}, capacity_{0}, size_{0} {}

  Vector(std::initializer_list<T> init)
      : size_{init.size()}, capacity_{init.size()} {
    data_ = new T[capacity_];
    size_t cnt = 0;
    for (auto &val : init) {
      data_[cnt] = val;
      ++cnt;
    }
  }

  Vector(size_t size) : size_{size}, capacity_{size} {
    data_ = new T[capacity_];
  }

  Vector(size_t size, const T &value) : size_{size}, capacity_{size} {
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = value;
    }
  }

  Vector(const Vector &other) : size_{other.size_}, capacity_{other.capacity_} {
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = other[i];
    }
  }

  Vector(Vector &&other) noexcept
      : data_{other.data_}, capacity_{other.capacity_}, size_{other.size_} {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  Vector &operator=(const Vector &other) {
    if (this != &other) {
      delete[] data_;
      size_ = other.size_;
      capacity_ = other.capacity_;
      data_ = new T[capacity_];
      for (size_t i = 0; i < size_; ++i) {
        data_[i] = other[i];
      }
    }
    return *this;
  }

  Vector &operator=(Vector &&other) noexcept {
    if (this != &other) {
      delete[] data_;
      data_ = other.data_;
      capacity_ = other.capacity_;
      size_ = other.size_;
      other.data_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }
    return *this;
  }

  bool operator==(const Vector &other) const {
    if (size_ != other.size_)
      return false;
    for (size_t i = 0; i < size_; ++i) {
      if (data_[i] != other.data_[i])
        return false;
    }
    return true;
  }
  bool operator!=(const Vector &other) const { return !(*this == other); }

  ~Vector() { delete[] data_; }

  void Resize(size_t size) {
    T *new_data = new T[size];
    for (size_t i = 0; i < std::min(size_, size); ++i) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    size_ = size;
    capacity_ = size;
  }

  void Swap(Vector &other) {
    std::swap(data_, other.data_);
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
  }

  void PushBack(const T &value) {
    if (size_ == capacity_) {
      ResizePrivate(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_] = value;
    ++size_;
  }

  void PopBack() {
    if (size_ == 0) {
      throw std::out_of_range(
          "What are you doing?! Vector is empty!!!!!!!!!!!!!!");
    }
    --size_;
  }

  void Clear() { size_ = 0; }

  T &operator[](size_t index) {
    if (index >= size_) {
      throw std::out_of_range("What are you doing?! Index out of range!!!");
    }
    return data_[index];
  }

  const T &operator[](size_t index) const {
    if (index >= size_) {
      throw std::out_of_range("What are you doing?! Index out of range!!!!");
    }
    return data_[index];
  }

  T &Front() {
    if (size_ == 0) {
      throw std::out_of_range(
          "What are you doing?! I think that vector is empty)");
    }
    return data_[0];
  }

  T &Back() {
    if (size_ == 0) {
      throw std::out_of_range(
          "What are you doing?! I think that vector is empty)");
    }
    return data_[size_ - 1];
  }

  void Reverse() {
    for (size_t i = 0; i < size_ / 2; ++i) {
      std::swap(data_[i], data_[size_ - 1 - i]);
    }
  }

  size_t GetSize() const { return size_; }

  size_t GetCapacity() const { return capacity_; }

  bool Empty() const { return size_ == 0; }

private:
  T *data_;
  size_t capacity_;
  size_t size_;
  void ResizePrivate(size_t new_capacity) {
    T *new_data = new T[new_capacity];
    for (size_t i = 0; i < size_; ++i) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
  }
};
