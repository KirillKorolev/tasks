#include "iface.h"

// Implementation of the task 2 unit testing
namespace Task
{
    struct Node;
    struct Edge;
    typedef Graph<Node, Edge> G;

    struct Node: public G::Node
    {
        int weight;
        Node( G& g): G::Node( g), weight(0){} 
    };

    struct Edge: public G::Edge
    {
        int weight;
        Edge( Node& p, Node& s): G::Edge(p, s), weight(0){} 
    };

    bool uTest( UnitTest *utest_p)
    {
        G graph;
        Node& n1 = graph.create_node();
        Node& n2 = graph.create_node();
        Node& n3 = graph.create_node();

        Edge& e1 = graph.create_edge( n1, n2);

        n1.weight = 10;
        n2.weight = 20;

        UTEST_CHECK(utest_p, &n1 == &e1.pred()); 
        UTEST_CHECK(utest_p, n1.succs_begin() != n1.succs_end());
        UTEST_CHECK(utest_p, n1.preds_begin() == n1.preds_end());
        UTEST_CHECK(utest_p, n2.succs_begin() == n2.succs_end());
        UTEST_CHECK(utest_p, n2.preds_begin() != n2.preds_end());
        UTEST_CHECK(utest_p, n1.uid() != n2.uid());
        UTEST_CHECK(utest_p, n1.uid() != n3.uid());
        UTEST_CHECK(utest_p, n2.uid() != n3.uid());

        graph.remove(e1); // remove the only edge

        UTEST_CHECK(utest_p, n1.succs_begin() == n1.succs_end());
        UTEST_CHECK(utest_p, n1.preds_begin() == n1.preds_end());
        UTEST_CHECK(utest_p, n2.succs_begin() == n2.succs_end());
        UTEST_CHECK(utest_p, n2.preds_begin() == n2.preds_end());

        Edge& e2 = graph.create_edge(n1, n2);
        Edge& e3 = graph.create_edge(n2, n3);
        UTEST_CHECK(utest_p, e2.uid() != e3.uid());
        UTEST_CHECK(utest_p, &n1 == &(n2.first_pred().pred()));
        UTEST_CHECK(utest_p, &n2 == &(n3.first_pred().pred()));
        UTEST_CHECK(utest_p, &n2 == &(n1.first_succ().succ()));
        UTEST_CHECK(utest_p, &n3 == &(n2.first_succ().succ()));
        UTEST_CHECK(utest_p, 0 == n1.num_preds());
        UTEST_CHECK(utest_p, 1 == n1.num_succs());

        UTEST_CHECK(utest_p, 3 == graph.num_nodes());
        UTEST_CHECK(utest_p, 2 == graph.num_edges());

        bool throws_correctly = false;

        try
        {
            n1.first_pred();
        } catch (G::Error e)
        {
            throws_correctly = true; 
        }

        UTEST_CHECK(utest_p, throws_correctly);

        e2.weight = 1;
        e3.weight = 2;
        int sum = 0;
        
        // Iterate through the nodes
        for ( auto n_iter = graph.nodes_begin(), n_end = graph.nodes_end(); 
              n_iter != n_end; ++n_iter)
        {
            sum += (*n_iter).weight;
        }
        // Iterate through the edges
        for ( auto e_iter = graph.edges_begin(), n_end = graph.edges_end();
              e_iter != n_end; ++e_iter)
        {
            sum += (*e_iter).weight;
        }

        UTEST_CHECK(utest_p, sum == 33);
      
        return utest_p->result();
    } 
    
    bool my_uTest(UnitTest *utest_p)
    {
        G graph;
        
        Node &n1 = graph.create_node();
        UTEST_CHECK(utest_p, n1.uid() == 1);
        UTEST_CHECK(utest_p, &(n1.graph()) == &graph);
        UTEST_CHECK(utest_p, graph.nodes_begin() != graph.nodes_end());
        
        Node &n2 = graph.create_node();
        UTEST_CHECK(utest_p, n2.uid() == 2);
        
        Node &n3 = graph.create_node();
        UTEST_CHECK(utest_p, n3.uid() == 3);
        
        Node &n4 = graph.create_node();
        UTEST_CHECK(utest_p, n4.uid() == 4);

        Edge& e1 = graph.create_edge(n1, n2);
        UTEST_CHECK(utest_p, &(e1.graph()) == &graph);
        UTEST_CHECK(utest_p, e1.uid() == 5);
        UTEST_CHECK(utest_p, n1.num_preds() == 0);
        UTEST_CHECK(utest_p, n1.num_succs() == 1);
        UTEST_CHECK(utest_p, graph.edges_begin() != graph.edges_end());
        
        Edge& e2 = graph.create_edge(n1, n2);
        UTEST_CHECK(utest_p, e2.uid() == 6);
        UTEST_CHECK(utest_p, n1.num_preds() == 0);
        UTEST_CHECK(utest_p, n1.num_succs() == 2);
        UTEST_CHECK(utest_p, n1.num_succs() == n2.num_preds());
        UTEST_CHECK(utest_p, n1.num_preds() == n2.num_succs());
        UTEST_CHECK(utest_p, &(n1.first_succ()) == &(n2.first_pred()));
        
        Edge& e3 = graph.create_edge(n2, n3);
        UTEST_CHECK(utest_p, e3.uid() == 7);
        
        Edge& e4 = graph.create_edge(n3, n4);
        UTEST_CHECK(utest_p, e4.uid() == 8);
        
        Edge& e5 = graph.create_edge(n4, n1);
        UTEST_CHECK(utest_p, e5.uid() == 9);
        
        Edge& e6 = graph.create_edge(n2, n4);
        UTEST_CHECK(utest_p, e6.uid() == 10);
        
        Edge& e7 = graph.create_edge(n3, n1);
        UTEST_CHECK(utest_p, e7.uid() == 11);
        
        UTEST_CHECK(utest_p, graph.num_nodes() == 4);
        UTEST_CHECK(utest_p, graph.num_edges() == 7);

        n1.weight = 1;
        n2.weight = 2;
        n3.weight = 3;
        n4.weight = 4;
        
        e1.weight = 1;
        e2.weight = 2;
        e3.weight = 3;
        e4.weight = 4;
        e5.weight = 5;
        e6.weight = 6;
        e7.weight = 7;
       
        UTEST_CHECK(utest_p, *n1.succs_begin() == *n2.preds_begin()); 
        UTEST_CHECK(utest_p, *(--n1.succs_end()) == *(--n2.preds_end()));
        UTEST_CHECK(utest_p, &(e7.succ()) == &(e1.pred()));
        
        graph.remove(e2);
        UTEST_CHECK(utest_p, graph.num_edges() == 6);
        UTEST_CHECK(utest_p, n1.num_succs() == 1);
        
        graph.remove(n1);
        UTEST_CHECK(utest_p, (int) graph.num_nodes() == 3);
        UTEST_CHECK(utest_p, (int) graph.num_edges() == 3);
        UTEST_CHECK(utest_p, (int) n4.num_succs() == 0);

        bool throws_correctly = false;

        try {
            n4.first_succ();
        } catch (G::Error e) {
            throws_correctly = true; 
        }

        UTEST_CHECK(utest_p, throws_correctly);

        int sum = 0;
        
        for (auto n_iter = graph.nodes_begin(), n_end = graph.nodes_end(); n_iter != n_end; ++n_iter)
            sum += (*n_iter).weight;

        for (auto e_iter = graph.edges_begin(), e_end = graph.edges_end(); e_iter != e_end; ++e_iter)
            sum += (*e_iter).weight;
    
        UTEST_CHECK(utest_p, sum == 22);
        
        return utest_p->result();
    }
};
