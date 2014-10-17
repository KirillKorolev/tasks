/******************************************************
    Implementation for DList and Unit classes

    @file: task/iface.h
    @date: October 8, 2014
    @author: Kirill Korolev <kirill.korolef@gmail.com>
    @vertion: 1.0 (October 8, 2014) 

******************************************************/

namespace Task
{
	template <class T> void DList<T>::Unit::glue(Unit *u)
	{
		DLIST_ASSERTXD(u != NULL, "DList::Unit::glue: a NULL address\n");
		next_u = u;
		u->prev_u = this;
	}

	template <class T> void DList<T>::push_front(const T &val)
	{
		Unit *new_u = new Unit;
		new_u->u_val = val;
                if (!size()) {
                        head = new_u;
                        tail = new_u;
                } else {
                        new_u->glue(head);
                        head = new_u;
                }
                l_size++;
	}

	template <class T> void DList<T>::pop_front()
	{
		DLIST_ASSERTXD(size() > 0, "DList::pop_front: the list is empty\n");
		Unit *dead = head; //< A unit to remove
		if (size() == 1)
                        tail = NULL;
                head = dead->next();
                if (head)
                        head->prev_u = NULL;
		delete dead;
		l_size--;
	}

	template <class T> void DList<T>::push_back(const T &val)
	{
		Unit *new_u = new Unit;
		new_u->u_val = val;
                if (!size()) {
                        head = new_u;
                        tail = new_u;
                } else {
                        tail->glue(new_u);
                        tail = new_u;
                }
		l_size++;
	}

	template <class T> void DList<T>::pop_back()
	{
		DLIST_ASSERTXD(size() > 0, "DList::pop_back: the list is empty\n");
		Unit *dead = tail; //< A unit to remove
		if (size() == 1)
                        head = NULL;
                tail = dead->prev();
                if (tail)
                        tail->next_u = NULL;
		delete dead;
		l_size--;
	}

	template <class T> typename DList<T>::Unit *DList<T>::insert(Unit *u, const T &val)
	{
		DLIST_ASSERTXD(u != NULL, "DList::insert: NULL address\n");
                DLIST_ASSERTXD(size(), "DList::insert: the list is empty\n");
                
                if (u == head) {
                        push_front(val);
                        return first();
                }
                
		Unit *new_u = new Unit;
		new_u->u_val = val;
		u->prev()->glue(new_u);
		new_u->glue(u);
		l_size++;
	
		return new_u;
	}

	template <class T> typename DList<T>::Unit *DList<T>::by_num(const int &num)
	{
		if (num > size() || num <= 0)
                        return NULL;

		Unit *curr = head;
		for (int i = 0; i < num - 1; i++)
			curr = curr->next();

		return curr;
	}

	template <class T> typename DList<T>::Unit *DList<T>::erase(Unit *u)
	{
		DLIST_ASSERTXD(u != NULL, "DList::erase: a NULL address\n");
		DLIST_ASSERTXD(size() > 0, "DList::erase: the list is empty\n");
                
                Unit *res = u->next();
                
                if (u == head)
                        pop_front();
                else if (u == tail)
                        pop_back();
                else {
                        u->prev()->glue(u->next());
                        delete u;
                        l_size--;
                }

		return res;
	}

	template <class T> void DList<T>::reverse()
	{
		Unit **point = new Unit*[size()];
                Unit *curr = tail;
                
                for (int i = 0; i < size(); i++) {
                        point[i] = curr;
                        curr = curr->prev();
                }
                
                for (int i = 0; i < size() - 1; i++)
                        point[i]->glue(point[i + 1]);
                head = point[0];
                tail = point[size() - 1];
                head->prev_u = NULL;
                tail->next_u = NULL;
                
                delete [] point;
	}
	
	template <class T> void DList<T>::dump()
	{
		cout << "\nLIST DUMP:" << endl
                     << "Size: " << size() << endl;
		
		if (!size()) return;
                
		cout << "Units: |HEAD|<->";
		Unit *curr = head;
		for (int i = 0; i < size(); i++) {
			cout << "|" << curr->val() << "|<->";
			curr = curr->next();
		}
		cout << "|TAIL|\n" << endl;
	}
};
