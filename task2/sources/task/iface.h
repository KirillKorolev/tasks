/*******************************************************

    Interface of Graph class.

    @file: task/iface.h
    @date: October 27, 2014
    @author: Kirill Korolev <kirill.korolef@gmail.com>
    @vertion: 1.0 (October 27, 2014) 

*******************************************************/

#include "../Utils/utils_iface.h"
#include <unordered_set>
#include <vector>

/* namespaces import */
using namespace Utils;

//Debug assert with diagnostic info
#if !defined(GRAPH_ASSERTXD)
#    define GRAPH_ASSERTXD(cond, what) ASSERT_XD(cond, "Graph", what)
#endif

// Simple debug assert
#if !defined(GRAPH_ASSERTD)
#    define GRAPH_ASSERTD(cond) ASSERT_XD(cond, "Graph", "")
#endif

namespace Task //< Namespace for the programming task
{
 /* CLASS : GRAPH ================================================================================>
    @param NodeT class representing nodes of graph, should be inherited from Graph::Node
    @param EdgeT class representing edges of graph, should be inherited from Graph::Edge */
    template <class NodeT, class EdgeT> class Graph
    {
    public:
        typedef UInt32 UId; //< Unique id type for node and edge
        static const UId INVALID_UID = (UId) (-1);

        class Error: public std::exception {};

        class Node //CLASS: NODE *****************************************************************>
        {
        public:
            //Iterator's type for:
            class pred_iterator: public std::random_access_iterator_tag;// node's predecessor edges 
            class succ_iterator: public std::random_access_iterator_tag;// node's successor edges 
            
            // NODE: INTERFACE ------------------------------------------------------------------->
            pred_iterator preds_begin(); // Get iterator to the first predecessor edge
            pred_iterator preds_end();   // Get end iterator for the predecessors

            succ_iterator succs_begin(); // Get iterator to the first successor edge
            succ_iterator succs_end();   // Get end iterator for the successors

            Graph& graph();  // Get the graph reference
            UId uid() const; // Get the node's unique id 

            EdgeT& first_pred(); // Convinience routine returns first predecessor edge or throws an exception
            EdgeT& first_succ(); // Convinience routine returns first successor edge or throws an exception
            
            UInt32 num_preds() const; // Get the number of predecessors
            UInt32 num_succs() const; // Get the number of successors

        protected:
            Node( Graph& g); // Constructor of the node
            virtual ~Node(); 
            
        private:
            Node();               //<--TURNED------
            Node(const Node &n);  //<---------OFF--
            //------------------------------------------------------------------------------------<
            
            // NODE: DATA ------------------------------------------------------------------------>
            UId id;
            Graph &curr_gr;
            NodeT curr;
            EdgeT *&edges;
            //------------------------------------------------------------------------------------<
            
        }; //*************************************************************************************<

        class Edge // CLASS: EDGE ****************************************************************>
        {
        public: // EDGE: INTERFACE --------------------------------------------------------------->
            inline NodeT &pred() { return pred_n; }; // Get edge predecessor
            inline NodeT &succ() { return succ_n; }; // Get edge successor

            Graph& graph(); // Get the graph
            inline UId uid() const { return id; };// Get the edge's unique id

        protected:
            Edge( NodeT& p, NodeT& s); // Construct an edge between given nodes
            virtual ~Edge();
            
        private:
            Edge();               //<--TURNED------
            Edge( const Edge &e); //<---------OFF--
            //------------------------------------------------------------------------------------<
        
            // EDGE: DATA ------------------------------------------------------------------------>
            UId id;
            Graph &curr_gr;
            EdgeT curr;
            NodeT &pred_n;
            NodeT &succ_n;
            //------------------------------------------------------------------------------------<
        
        }; //*************************************************************************************<

    public: 
        // Iterator's type for:
        class node_iterator { std::random_access_iterator_tag iter; }; // the graph's nodes
        class edge_iterator { std::random_access_iterator_tag iter; }; // the graph's edges
        
        // GRAPH: INTERFACE ---------------------------------------------------------------------->
        node_iterator nodes_begin(); // Get the iterator to the first node
        node_iterator nodes_end();   // Get the end iterator for the nodes

        edge_iterator edges_begin(); // Get the iterator to the first edge
        edge_iterator edges_end();   // Get the end iterator for the edges

        inline UInt32 num_nodes() const { return nodes.size(); }; // Get the number of nodes
        inline UInt32 num_edges() const { return edges.size(); }; // Get the number of edges

        NodeT &create_node();                   // Create a new node and return reference to it
        EdgeT &create_edge( NodeT& pred, NodeT& succ); // Create a new edge between given nodes
    
        void remove( NodeT& node); // Remove and delete node
        void remove( EdgeT& edge); // Remove and delete edge

        virtual ~Graph(); // Destructor, deletes all nodes and edges
        //----------------------------------------------------------------------------------------<
        
    private:
        // GRAPH: DATA --------------------------------------------------------------------------->
        vector<NodeT> nodes;
        vector<EdgeT> edges;
        //----------------------------------------------------------------------------------------<
        
    };//==========================================================================================<

    bool uTest( UnitTest *utest_p); //< Basic function for unit testing
}; 

#include "graph_impl.h"
