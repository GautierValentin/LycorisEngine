#pragma once

// This class is meant to have NO ownership
template <typename T>
class LinkPtr
{
public:
	LinkPtr(T* ref, LinkPtr* prev, LinkPtr* next) : _ref(ref), _prev(prev), _next(next) {

	}

	~LinkPtr() {
		if (_prev != nullptr && _next != nullptr) {
			LinkPtr* prev = _prev;
			LinkPtr* next = _next;

			next->_prev = prev;
			prev->_prev = next;
		}
		else {
			if (_prev != nullptr) {
				_prev->_next = nullptr;
			}
			if (_next != nullptr) {
				_next->_prev = nullptr;
			}
		}
	}

private:
	T* _ref;
	LinkPtr* _prev;
	LinkPtr* _next;

public:
	T operator*() {
		return *_ref;
	}

public:
	bool Contains(T* ref) {
		if (_ref == ref)
			return true;

		if (_next != nullptr)
			return _next->Contains(ref);

		return false;
	}

	void DeleteList() {
		if (_next != nullptr)
			_next->DeleteList();

		delete this;
	}

	void Add(T* ref) {
		if (_ref == nullptr) {
			_ref = ref;
		}
		else if (_next == nullptr) {
			_next = new LinkPtr(ref, this, nullptr);
		}
		else {
			_next->Add(ref);
		}
	}
};

