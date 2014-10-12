/******************************************************
	Interface of a double connected list and its unit.

	@file: task/iface.h
	@date: October 7, 2014
	@author: Kirill Korolev <kirill.korolef@gmail.com>
	@vertion: 1.0 (October 7, 2014) 

******************************************************/

#include "../Utils/utils_iface.h"

/* namespaces import */
using namespace Utils;

//Debug assert with diagnostic info
#if !defined(DLIST_ASSERTXD)
#    define DLIST_ASSERTXD(cond, what) ASSERT_XD(cond, "DList", what)
#endif

//Simple debug assert
#if !defined(DLIST_ASSERTD)
#    define DLIST_ASSERTD(cond) ASSERT_XD(cond, "DList", "")
#endif

namespace Task //< A namespace of the task
{
    template <class T> class DList //< Doubly connected list
    {
    public:
        class Unit //< List unit class
        {
			friend class DList; //The only one that can change Unit class data

        public: //INTERFACE <****************************************************************>	
			inline Unit *next() { return next_u; } //< Gets the next unit in list             
            inline Unit *prev() { return prev_u; } //< Gets the previous unit in list        
            inline T &val() { return u_val; }      //< Gets the reference to the unit's value		
		private:
			Unit(): next_u(NULL), prev_u(NULL), u_val(0) {}; //<
			Unit(const Unit &orig);                          //< Can't use these
            Unit &operator= (const Unit &orig);              //<
			void glue(Unit *u); //< Connects doubly u unit to the current one from right
			// <*****************************************************************************>

			//DATA <*************************************************************************>
        	Unit *next_u; //< A pointer on a next unit in the list (u = unit)               | 
            Unit *prev_u; //< A pointer on a previous unit in the list                      |
			T u_val; //< A value of the current unit                                        |
			// <*****************************************************************************>
        };

		//INTERFACE <************************************************************************>
		DList(); //< A basic constructor: construct an empty list
        ~DList(); //< A basic destructor
        
        void push_front(const T &val);       //< Inserts one unit with given value at front        
        void pop_front();                    //< Removes one unit at front of the list
        void push_back(const T &val);        //< Inserts one unit with given value to back
        void pop_back();                     //< Removes one unit from the back of the list
        Unit *insert(Unit *u, const T &val); //< Inserts one unit before the given one  

        Unit *first(); //< Gets first unit
        Unit *last();  //< Gets last unit
		// Gets a unit with num number from a head if it exists
		Unit *by_num(const int &num);
        
        Unit *erase(Unit *u);               //< Removes given unit, return next unit or null  
        void clear();                       //< Removes all units
        inline bool empty() { return size() ? false : true; } //< Check if list is empty
        inline unsigned size() { return l_size; } //< Gets the number of units in the list
        void reverse();                     //< Reverses the order of units in the list
		void dump();                        //< Prints all units from the list
		// <**********************************************************************************>

	private: //DATA <*************************************************************************>
		Unit *head; //< An empty unit which points on the first unit                         |
		Unit *tail; //< An empty unit which points on the last unit                          |
		unsigned l_size; //< Number of units in the list without a head and a tail (l =list) |
		// <**********************************************************************************>
    };

    bool uTest(UnitTest *utest_p); //< A basic unit test prototype
};

#include "list_impl.h" //< A implementation of the interface
