#include <krnl/assert.hpp>

template <typename T>
class list
{
protected:
	template<class U> friend class tree;

	struct node
	{
		T data;
		node* next;

		node(T item)
		{
			data = item;
			next = nullptr;
		}
	};

	node* head;
	node* tail;
	node* please_delete;
	int count;

	virtual bool circular()
	{
		return false;
	}

	struct iterator
	{
		node* m_ptr;
		list* owner;

		iterator(list* _owner, node* start_node)
		{
			owner = _owner;
			m_ptr = start_node;
		}

		T operator*()
		{
			assert(m_ptr);
			return m_ptr->data;
		}

		list<T>::iterator& operator++()
		{
			assert(m_ptr);
			m_ptr = m_ptr->next;
			if (owner->circular() && m_ptr == nullptr) {
				m_ptr = owner->head;
			}
			return *this;
		}

		list<T>::iterator& operator++(int postfix)
		{
			auto temp = *this;
			++(*this);
			return temp;
		}

		bool operator!=(list<T>::iterator first)
		{
			return first.m_ptr != this->m_ptr;
		}
	};

	void flush_deletion()
	{
		if (please_delete != nullptr) {
			delete please_delete;
		}
		please_delete = nullptr;
	}

	void mark_for_deletion(node* n)
	{
		flush_deletion();
		please_delete = n;
	}

public:
	list()
	{
		head = nullptr;
		tail = nullptr;
		count = 0;
		please_delete = nullptr;
	}

	virtual ~list()
	{
		while (count) {
			remove_head();
		}
		flush_deletion();
	}

	node* create_node(T item)
	{
		if (please_delete != nullptr) {
			auto recycled = please_delete;
			please_delete = nullptr;
			recycled->next = nullptr;
			recycled->data = item;
			return recycled;

		} else {
			return new node(item);
		}
	}

	void push_back(T item)
	{
		assert((head && tail) | (!head && !tail));

		++count;

		if (tail == nullptr) {
			tail = create_node(item);
			head = tail;
		} else {
			tail->next = create_node(item);
			tail = tail->next;

			assert(head != tail);
		}

		assert((head && tail) | (!head && !tail));
	}

	T remove_tail()
	{
		assert((head && tail) | (!head && !tail));
		assert(head != nullptr);
		assert(tail != nullptr);

		T ret = tail->data;
		auto to_delete = tail;

		node* current = head;
		while (1) {
			assert(current);

			if (current->next == tail) {
				current->next = nullptr;
				tail = current;
				if (tail == nullptr) {
					head = nullptr;
				}

				--count;

				mark_for_deletion(please_delete);
				return ret;
			}

			current = current->next;
		}
	}

	T remove_head()
	{
		assert((head && tail) | (!head && !tail));
		assert(head != nullptr);
		assert(tail != nullptr);

		T ret = head->data;
		auto please_delete = head;
		head = head->next;
		if (head == nullptr) {
			tail = nullptr;
		}

		assert((head && tail) | (!head && !tail));
		mark_for_deletion(please_delete);

		--count;

		return ret;
	}

	void rotate_item_to_head(T item)
	{
		int rotation_timeout = 0;
		while (head->data != item) {
			auto head = remove_head();
			push_back(head);
			assert(rotation_timeout++ <= count);
		}
	}

	void rotate_item_to_tail(T item)
	{
		int rotation_timeout = 0;
		while (tail->data != item) {
			auto head = remove_head();
			push_back(head);
			assert(rotation_timeout++ <= count);
		}
	}

	T get_item_from_id(int id)
	{
		node* current = head;
		int current_id = 0;
		while (id--) {
			assert(current);
			current = current->next;
		}
		return current->data;
	}

	void rotate_id_to_head(int id)
	{
		rotate_item_to_head(get_item_from_id(id));
	}

	void rotate_id_to_tail(int id)
	{
		rotate_item_to_tail(get_item_from_id(id));
	}

	void rotate_and_remove_item(T item)
	{
		rotate_item_to_head(item);
		remove_head();
	}

	void rotate_and_remove_id(int id)
	{
		rotate_id_to_head(id);
		remove_head();
	}

	int size()
	{
		return count;
	}

	iterator begin()
	{
		return iterator(this, head);
	}

	iterator end()
	{
		return iterator(this, nullptr);
	}
};

template <typename T>
class circular_list : public list<T>
{
protected:
	virtual bool circular() override final
	{
		return true;
	}
};