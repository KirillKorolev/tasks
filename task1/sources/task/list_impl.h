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
<<<<<<< HEAD
    	DLIST_ASSERTXD(u != NULL, "DList::Unit::glue: a NULL address\n");
		
	next_u = u;
	u->prev_u = this;
    }
	
    template <class T> DList<T>::DList():
    l_size(0) {
	head = new Unit;
=======
        DLIST_ASSERTXD(u != NULL, "DList::Unit::glue: a NULL address\n");
	
	next_u = u;
	u->prev_u = this;
    }
	
    template <class T> DList<T>::DList():
    l_size(0) {
        head = new Unit;
>>>>>>> ba65de489f01f9e81a7e22966ceefa35fe6ff196
	tail = new Unit;
	head->u_val = 0;
	tail->u_val = 0;
	head->prev_u = NULL;
	tail->next_u = NULL;
<<<<<<< HEAD
    	head->next_u = tail;
=======
	head->next_u = tail;
>>>>>>> ba65de489f01f9e81a7e22966ceefa35fe6ff196
	tail->prev_u = head;
    }

    template <class T> DList<T>::~DList()
    {
	clear();
	delete head;
	delete tail;
    }

    template <class T> void DList<T>::push_front(const T &val)
    {
<<<<<<< HEAD
        Unit *new_u = new Unit;
=======
	Unit *new_u = new Unit;
>>>>>>> ba65de489f01f9e81a7e22966ceefa35fe6ff196
	new_u->u_val = val;
	new_u->glue(head->next());
	head->glue(new_u);
	l_size++;
    }

    template <class T> void DList<T>::pop_front()
    {
	DLIST_ASSERTXD(size() > 0, "DList::pop_front: the list is empty\n");
		
	Unit *dead = head->next(); //< A unit to remove
	head->glue(dead->next());
	delete dead;
	l_size--;
    }

    template <class T> void DList<T>::push_back(const T &val)
    {
	Unit *new_u = new Unit;
	new_u->u_val = val;
	tail->prev()->glue(new_u);
	new_u->glue(tail);
	l_size++;
    }

    template <class T> void DList<T>::pop_back()
    {
	DLIST_ASSERTXD(size() > 0, "DList::pop_back: the list is empty\n");
		
	Unit *dead = tail->prev(); //< A unit to remove
	dead->prev()->glue(tail);
	delete dead;
	l_size--;
    }

    template <class T> typename DList<T>::Unit *DList<T>::insert(Unit *u, const T &val)
    {
	DLIST_ASSERTXD(u != NULL, "DList::insert: NULL address\n");
	DLIST_ASSERTXD(u != head, "DList::insert: can't insert a unit before the head\n");
		
	Unit *new_u = new Unit;
	new_u->u_val = val;
	u->prev()->glue(new_u);
	new_u->glue(u);
	l_size++;
	
	return new_u;
    }
	
    template <class T> inline typename DList<T>::Unit *DList<T>::first()
    {
<<<<<<< HEAD
    	if (size() > 0) return head->next();
=======
	if (size() > 0) return head->next();
>>>>>>> ba65de489f01f9e81a7e22966ceefa35fe6ff196
        return NULL;
    }

    template <class T> inline typename DList<T>::Unit *DList<T>::last()
    {
	if (size() > 0)	return tail->prev();
        return NULL;
    }

    template <class T> typename DList<T>::Unit *DList<T>::by_num(const int &num)
    {
	DLIST_ASSERTXD(num <= size(), "DList::by_num: there is no unit with curr. number\n");
	DLIST_ASSERTXD(num > 0, "DList::by_num: curr. number is not appropriate\n");	
	
	Unit *curr = head;
	for (int i = 0; i < num; i++)
<<<<<<< HEAD
	    curr = curr->next();
=======
	curr = curr->next();
>>>>>>> ba65de489f01f9e81a7e22966ceefa35fe6ff196
	return curr;
    }

    template <class T> typename DList<T>::Unit *DList<T>::erase(Unit *u)
    {
<<<<<<< HEAD
	DLIST_ASSERTXD(u != NULL, "DList::erase: a NULL address\n");
=======
        DLIST_ASSERTXD(u != NULL, "DList::erase: a NULL address\n");
>>>>>>> ba65de489f01f9e81a7e22966ceefa35fe6ff196
	DLIST_ASSERTXD(u != tail, "DList::erase: can't erase the tail\n");
	DLIST_ASSERTXD(u != head, "DList::erase: can't erase the head\n");
	DLIST_ASSERTXD(size() > 0, "DList::erase: the list is empty\n");
		
	Unit *res = u->next();
	u->prev()->glue(u->next());
	delete u;
	l_size--;

	if (res == tail) return NULL;
	else             return res;
    }

    template <class T> void DList<T>::clear()
    {
<<<<<<< HEAD
	DLIST_ASSERTXD(size() > 0, "DList::clear: the list is already empty\n");
		
	while (head->next() != tail)
            pop_front(); 
=======
        DLIST_ASSERTXD(size() > 0, "DList::clear: the list is already empty\n");
		
	Unit *curr = head->next();
	Unit *next = curr->next();
	while (curr != tail) {
	    delete curr;
	    curr = next;
	    next = curr->next();
	}
>>>>>>> ba65de489f01f9e81a7e22966ceefa35fe6ff196
	l_size = 0;
    }

    template <class T> void DList<T>::reverse()
    {
	DLIST_ASSERTXD(size() > 0, "DList::reverse: the list is empty\n");
<<<<<<< HEAD
		
	Unit *unit1 = head->next(), *unit2 = tail->prev(); //Two units for replacing
        T tmp = 0;
        	
	for (int i = 0; i < size() / 2; i++) {
	    tmp = unit1->val();
            unit1->u_val = unit2->val();
            unit2->u_val = tmp;

            unit1 = unit1->next();
            unit2 = unit2->prev();
=======
		
	Unit *unit1 = head->next(), *unit2 = tail->prev(); //Two units for replacing
	Unit *left_neig = unit2->prev(), *right_neig = unit2->next(); //neighbors of unit2
		
	for (int i = 0; i < size() / 2; i++) {
	    unit1->prev()->glue(unit2); // <--
	    unit2->glue(unit1->next()); // <-- REPLACING 
	    left_neig->glue(unit1);     // <--
	    unit1->glue(right_neig);    // <--
			
	    unit1 = unit2->next();
	    unit2 = left_neig;
>>>>>>> ba65de489f01f9e81a7e22966ceefa35fe6ff196
	}
    }
	
    template <class T> void DList<T>::dump()
    {
	cout << "\nLIST DUMP:\n"
	     << "Size: " << size() << "\n";
<<<<<<< HEAD
		
        if (size() == 0) return;
				
    	cout << "Units: |HEAD|<->";
=======
		
	if (size() == 0) return;
		
	cout << "Units: |HEAD|<->";
>>>>>>> ba65de489f01f9e81a7e22966ceefa35fe6ff196
	Unit *curr = head->next();
	while (curr != tail) {
	    cout << "|" << curr->val() << "|<->";
	    curr = curr->next();
	}
	cout << "|TAIL|\n\n";
    }
};
