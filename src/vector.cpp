#include "vector.h"

Vector::Iterator::Iterator() : value_(nullptr) {
}

Vector::Iterator::Iterator(ValueType* pointer) : value_(pointer) {
}

Vector::ValueType& Vector::Iterator::operator*() const {
	return *value_;
}

Vector::ValueType* Vector::Iterator::operator->() const {
	return value_;
}

Vector::Iterator& Vector::Iterator::operator=(Iterator other) {
	value_ = other.value_;
	return *this;
}

Vector::Iterator& Vector::Iterator::operator++() {
	++value_;
	return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
	Vector::Iterator prev_iterator = *this;
	++(*this);
	return prev_iterator;
}

Vector::Iterator& Vector::Iterator::operator--() {
	--value_;
	return *this;
}

Vector::Iterator Vector::Iterator::operator--(int) {
	Vector::Iterator prev_iterator = *this;
	--(*this);
	return prev_iterator;
}

Vector::Iterator Vector::Iterator::operator+(DifferenceType shift) {
	return Vector::Iterator(value_ + shift);
}

Vector::DifferenceType Vector::Iterator::operator-(Iterator other) {
	return value_ - other.value_;
}

Vector::Iterator& Vector::Iterator::operator+=(DifferenceType shift) {
	*this = *this + shift;
	return *this;
}

Vector::Iterator& Vector::Iterator::operator-=(DifferenceType shift) {
	*this = *this + (-shift);
	return *this;
}

bool Vector::Iterator::operator==(const Iterator& other) const {
	return value_ == other.value_;
}

bool Vector::Iterator::operator!=(const Iterator& other) const {
	return value_ != other.value_;
}

std::strong_ordering Vector::Iterator::operator<=>(const Iterator& other) const {
	if (value_ - other.value_ > 0) {
		return std::strong_ordering::greater;
	}
	if (other.value_ - value_ > 0) {
		return std::strong_ordering::less;
	}
	return std::strong_ordering::equivalent;
}

Vector::Vector() : size_(0), capacity_(0), data_(nullptr) {
}

Vector::Vector(size_t size) : size_(size), capacity_(size_), data_(new int[size]) {
	for (SizeType i = 0; i < size_; ++i) {
		data_[i] = 0;
	}
}

Vector::Vector(std::initializer_list<ValueType> list) : Vector(list.size()) {
	SizeType index = 0;
	for (const auto& it : list) {
		data_[index] = it;
		++index;
	}
}

Vector::Vector(const Vector& other) : Vector(other.Size()) {
	for (SizeType i = 0; i < other.Size(); ++i) {
		data_[i] = other.data_[i];
	}
}

Vector& Vector::operator=(const Vector& other) {
	if (data_ == other.data_) {
		return *this;
	}
	delete[] data_;
	size_ = other.Size();
	capacity_ = size_;
	data_ = new int[size_];
	for (SizeType i = 0; i < size_; ++i) {
		data_[i] = other.data_[i];
	}
	return *this;
}

Vector::~Vector() {
	delete[] data_;
}

Vector::SizeType Vector::Size() const {
	return size_;
}

Vector::SizeType Vector::Capacity() const {
	return capacity_;
}

const Vector::ValueType* Vector::Data() const {
	return data_;
}

Vector::ValueType& Vector::operator[](size_t position) {
	return *(data_ + position);
}

Vector::ValueType Vector::operator[](size_t position) const {
	return *(data_ + position);
}

bool Vector::operator==(const Vector& other) const {
	if (size_ != other.size_) {
		return false;
	}
	for (SizeType i = 0; i < size_; ++i) {
		if (data_[i] != other.data_[i]) {
			return false;
		}
	}
	return true;
}

bool Vector::operator!=(const Vector& other) const {
	return !(*this == other);
}

std::strong_ordering Vector::operator<=>(const Vector& other) const {
	for (SizeType i = 0; i < size_ && i < other.size_; ++i) {
		if (data_[i] < other.data_[i]) {
			return std::strong_ordering::less;
		}
		if (data_[i] < other.data_[i]) {
			return std::strong_ordering::greater;
		}
	}
	if (size_ < other.size_) {
		return std::strong_ordering::less;
	}
	if (size_ > other.size_) {
		return std::strong_ordering::greater;
	}
	return std::strong_ordering::equivalent;
}

void Vector::Reserve(SizeType new_capacity) {
	if (new_capacity <= capacity_) {
		return;
	}
	ValueType* new_data = new int[new_capacity];
	for (SizeType i = 0; i < size_; ++i) {
		new_data[i] = data_[i];
	}
	delete[] data_;
	data_ = new_data;
	capacity_ = new_capacity;
}

void Vector::Clear() {
	size_ = 0;
}

void Vector::PushBack(const ValueType& new_element) {
	if (size_ == capacity_) {
		SizeType new_capacity = (size_ == 0 ? 1 : size_ * 2);
		Reserve(new_capacity);
	}
	data_[size_] = new_element;
	++size_;
}

void Vector::PopBack() {
	--size_;
}

void Vector::Swap(Vector& other) {
	std::swap(data_, other.data_);
	std::swap(size_, other.size_);
	std::swap(capacity_, other.capacity_);
}

Vector::Iterator Vector::Begin() {
	return Iterator(data_);
}

Vector::Iterator Vector::End() {
	return Iterator(data_ + size_);
}

Vector::Iterator Vector::begin() {
	return Begin();
}

Vector::Iterator Vector::end() {
	return End();
}