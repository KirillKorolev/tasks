/***********************************************************

    Interface of Graph class.

    @file: task/iface.h
    @date: October 27, 2014
    @author: Kirill Korolev <kirill.korolef@gmail.com>
    @vertion: 1.0 (October 27, 2014) 

***********************************************************/

#include "../Utils/utils_iface.h"
#include <unordered_set>
#include <list>
#include <iterator>
#include <exception>

/* namespaces import */
using namespace Utils;
using namespace std;

//Debug assert with diagnostic info
#if !defined(GRAPH_ASSERTXD)
#    define GRAPH_ASSERTXD(cond, what) ASSERT_XD(cond, "Graph", what)
#endif

// Simple debug assert
#if !defined(GRAPH_ASSERTD)
#    define GRAPH_ASSERTD(cond) ASSERT_XD(cond, "Graph", "")
#endif

enum ErrType
{
    UNEXP, //< Unexpected error
    BADDR, //< Bad address
    EMPTY, //< Accsess to an empty list
};
    
namespace Task //< Namespace for the programming task
{
 /* CLASS : GRAPH
    @param NodeT class representing nodes of graph, should be inherited from Graph::Node
    @param EdgeT class representing edges of graph, should be inherited from Graph::Edge */
    template <class NodeT, class EdgeT> class Graph
    {
    public:
        typedef UInt32 UId; //< Unique id type for node and edge
        typedef typename list<EdgeT>::iterator EdIterT;
        typedef typename list<NodeT>::iterator NoIterT;
        static const UId INVALID_UID = (UId) (-1);
        
        
        //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
        

        class Error: public exception
        {
        public:
            inline virtual const char *what() const throw() { return "Graph exception happened"; }
            ErrType type;
        };

        
        //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
        
        
        class Node
        {
            friend class Graph;
            
        public:
            //Iterator's type for:
            class pred_iterator // node's predecessor edges
            {
                typename list<EdgeT>::iterator _iter;
        
            public:
                inline pred_iterator(const typename list<EdgeT>::iterator &basic): _iter(basic) {}
        
                inline pred_iterator &operator++()                         { ++_iter; return *this;     }
                inline bool           operator==(const pred_iterator &rhs) { return _iter == rhs._iter; }
                inline bool           operator!=(const pred_iterator &rhs) { return _iter != rhs._iter; }
                inline EdgeT&         operator* ()                         { return *_iter;             }
            };
    
            class succ_iterator // node's successor edges
            {
                typename list<EdgeT>::iterator _iter;
        
            public:
                inline succ_iterator(const typename list<EdgeT>::iterator &basic): _iter(basic) {}
        
                inline succ_iterator &operator++()                         { ++_iter; return *this;     }
                inline bool           operator==(const succ_iterator &rhs) { return _iter == rhs._iter; }
                inline bool           operator!=(const succ_iterator &rhs) { return _iter != rhs._iter; }
                inline EdgeT&         operator* ()                         { return *_iter;             }
            };
            
            // INTERFACE ----------------------------------------------------------------------------------//
            // Get the iterator to:                                                                       //
            inline pred_iterator preds_begin() { return *_preds.begin(); } // the first predecessing edge                                  //
            inline pred_iterator preds_end()   { return *_preds.end();   } // the last predecessing edge                                  //
            inline succ_iterator succs_begin() { return *_succs.begin(); } // the first successing edge                                  //
            inline succ_iterator succs_end()   { return *_succs.end();   } // the last successing edge                                  //
                                                                                                     //
            inline Graph& graph() { return _graph; }  // Get the graph reference                    //
            inline UId uid() const { return _id; }    // Get the node's unique id                  //
                                                                                                  //
            //Convinience routine returns:                                                       //
            EdgeT &first_pred(); // first predecessor edge (else throws an exception)           //
            EdgeT &first_succ(); // first successor edge (else throws an exception)            //
                                                                                              //
            // Get the number of:                                                            //
            inline UInt32 num_preds() const { return _preds.size(); } // predecessors       //
            inline UInt32 num_succs() const { return _succs.size(); } // successors        //
                                                                                          //
        protected:                                                                     //
            Node(Graph &g); // Constructor of the node              //
            virtual ~Node() {};                                                        //
                                                                                      //
        private:                                                                   //
            Node();               //<--TURNED------                                 //
       //   Node(const Node &n);  //<---------OFF--                                //
            //--------------------------------------------------------------------//
            
            // DATA ------------------------------------------------------------//
            UId _id;                                                           //
            // The iterator for _graph._nodes:                                //
            NoIterT _iter;                                                   //
            Graph &_graph;                                                  //
            list<pred_iterator> _preds;                                          //
            list<succ_iterator> _succs;                                         //
            //-----------------------------------------------------------//
            
        };

        
        //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
        
        
        class Edge
        {
            friend class Graph;
            
        public: // INTERFACE -----------------------------------------------------------------//
            inline NodeT &pred() { return _pred; } // Get edge predecessor                   //
            inline NodeT &succ() { return _succ; } // Get edge successor                    //
                                                                                           //
            inline Graph &graph() { return _graph; } // Get the graph                     //
            inline UId uid() const { return _id; }// Get the edge's unique id            //
                                                                                        //
        protected:                                                                   //
            Edge(NodeT &p, NodeT &s); // Construct an edge between given nodes    //
            virtual ~Edge() {};                                                      //
                                                                                    //
        private:                                                                 //
            Edge();               //<--TURNED------                               //
           //Edge(const Edge &e);  //<---------OFF--                              //
            //------------------------------------------------------------------//
        
            // DATA ----------------------------------------------------------//
            UId _id;                                                         //
            // The iterator for _graph._edges:                              //
            EdIterT _iter;                                                 //
            Graph &_graph;                                                //
            NodeT &_pred;                                                //
            NodeT &_succ;                                               //
            //---------------------------------------------------------//
        };

        
        //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
 
        
    public: 
        // Iterator's type for:
        class node_iterator // the graph's nodes
        {
            typename list<NodeT>::iterator _iter;
        
        public:
            inline node_iterator(const typename list<NodeT>::iterator &basic): _iter(basic) {}
        
            inline node_iterator &operator++()                         { ++_iter; return *this;     }
            inline bool           operator==(const node_iterator &rhs) { return _iter == rhs._iter; }
            inline bool           operator!=(const node_iterator &rhs) { return _iter != rhs._iter; }
            inline NodeT         &operator* ()                         { return *_iter;             }
        };
    
        class edge_iterator // the graph's edges
        {
            typename list<EdgeT>::iterator _iter;
        
        public:
            inline edge_iterator(const typename list<EdgeT>::iterator &basic): _iter(basic) {}
        
            inline edge_iterator &operator++()                         { ++_iter; return *this;     }
            inline bool           operator==(const edge_iterator &rhs) { return _iter == rhs._iter; }
            inline bool           operator!=(const edge_iterator &rhs) { return _iter != rhs._iter; }
            inline EdgeT         &operator* ()                         { return *_iter;             }
        };
        
        // INTERFACE ---------------------------------------------------------------------------------------------//
        // Get the iterator to:                                                                                  //
        inline node_iterator nodes_begin() { return _nodes.begin(); } // the first node                                                          //
        inline node_iterator nodes_end()   { return _nodes.end();   } // the last node                                                          //
        inline edge_iterator edges_begin() { return _edges.begin(); } // the first edge                                                        //
        inline edge_iterator edges_end()   { return _edges.end();   } // the last edge                                                        //
                                                                                                            //
        inline UInt32 num_nodes() const { return _nodes.size(); } // Get the number of nodes               //
        inline UInt32 num_edges() const { return _edges.size(); } // Get the number of edges              //
                                                                                                         //
        NodeT &create_node(); // Create a new node and return reference to it                           //
        EdgeT &create_edge(NodeT &pred, NodeT &succ); // Create a new edge between given nodes         //
                                                                                                      //
        void remove(NodeT &node); // Remove and delete node                                          //
        void remove(EdgeT &edge); // Remove and delete edge                                         //
                                                                                                   //
        inline Graph() { _free_id.push_back(1); }
        virtual ~Graph() {} // Destructor, deletes all nodes and edges by list destructor        //
        //---------------------------------------------------------------------------------------//
        
        // DATA -------------------------------------------------------------------------------//
        list<UId> _free_id;                                                                   //
    private:                                                                               //
        list<NodeT> _nodes;                                                                 //
        list<EdgeT> _edges;                                                                //
        //--------------------------------------------------------------------------------//
        
    };
    
    
    //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
    

    bool uTest( UnitTest *utest_p); //< Basic function for unit testing
}; 

#include "graph_impl.h"
