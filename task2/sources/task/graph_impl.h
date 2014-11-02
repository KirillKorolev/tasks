/***********************************************************

    Implementation of Graph class.

    @file: task/iface.h
    @date: October 27, 2014
    @author: Kirill Korolev <kirill.korolef@gmail.com>
    @vertion: 1.0 (October 27, 2014) 

***********************************************************/

//#include "iface.h"

namespace Task {
    
    //NODE  <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
    
   
    template <class NodeT, class EdgeT> class Graph<NodeT, EdgeT>::Node::pred_iterator
    {
        typedef typename list<EdgeT>::iterator EdIterT;
        EdIterT _iter;
        
    public:
        inline pred_iterator(const EdIterT &basic): _iter(basic) {}
        
        inline pred_iterator &operator++()                         { ++_iter; return *this;     }
        inline bool           operator==(const pred_iterator &rhs) { return _iter == rhs._iter; }
        inline bool           operator!=(const pred_iterator &rhs) { return _iter != rhs._iter; }
        inline EdgeT&         operator* ()                         { return *_iter;             }
    };
    
    template <class NodeT, class EdgeT> class Graph<NodeT, EdgeT>::Node::succ_iterator
    {
        typedef typename list<EdgeT>::iterator EdIterT;
        EdIterT _iter;
        
    public:
        inline succ_iterator(const EdIterT &basic): _iter(basic) {}
        
        inline succ_iterator &operator++()                         { ++_iter; return *this;     }
        inline bool           operator==(const succ_iterator &rhs) { return _iter == rhs._iter; }
        inline bool           operator!=(const succ_iterator &rhs) { return _iter != rhs._iter; }
        inline EdgeT&         operator* ()                         { return *_iter;             }
    };
    
    template <class NodeT, class EdgeT> typename Graph<NodeT, EdgeT>::Node::pred_iterator Graph<NodeT, EdgeT>::Node::preds_begin()
    {
        GRAPH_ASSERTXD(_preds.size(), "Node: preds_begin: no predecessing edges/n");
        return *_preds.begin();
    }
    
    template <class NodeT, class EdgeT> typename Graph<NodeT, EdgeT>::Node::pred_iterator Graph<NodeT, EdgeT>::Node::preds_end()
    {
        GRAPH_ASSERTXD(_preds.size(), "Node: preds_end: no predecessing edges/n");
        return *_preds.end();
    }
    
    template <class NodeT, class EdgeT> typename Graph<NodeT, EdgeT>::Node::succ_iterator Graph<NodeT, EdgeT>::Node::succs_begin()
    {
        GRAPH_ASSERTXD(_succs.size(), "Node: succs_begin: no successing edges/n");
        return *_succs.begin();
    }
    
    template <class NodeT, class EdgeT> typename Graph<NodeT, EdgeT>::Node::succ_iterator Graph<NodeT, EdgeT>::Node::succs_end()
    {
        GRAPH_ASSERTXD(_succs.size(), "Node: succs_end: no successing edges/n");
        return *_succs.end();
    }
    
    template <class NodeT, class EdgeT> EdgeT &Graph<NodeT, EdgeT>::Node::first_pred()
    {
        if (_preds.size())
            return **_preds.begin();
        else {
            Error err;
            err.type = EMPTY;
            throw err;
            //return;
        }
    }
    
    template <class NodeT, class EdgeT> EdgeT &Graph<NodeT, EdgeT>::Node::first_succ()
    {
        if (_succs.size())
            return **_succs.begin();
        else {
            Error err;
            err.type = EMPTY;
            throw err;
           // return 0;
        }
    }
    
    template <class NodeT, class EdgeT> Graph<NodeT, EdgeT>::Node::Node(Graph &g):
    _graph(g) {
        GRAPH_ASSERTXD(g._free_id.size(), "Node constructor: no free id values/n");
        
        _id = *g._free_id.end();
        g._free_id.pop_back();
        if (g._free_id.empty())
            g._free_id.push_back(_id + 1);
    }
    
    //EDGE  <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
    
    template <class NodeT, class EdgeT> Graph<NodeT, EdgeT>::Edge::Edge(NodeT &p, NodeT &s):
    _graph(p._graph), _pred(p), _succ(s) {
        GRAPH_ASSERTXD(_graph._free_id.size(), "Edge constructor: no free id values/n");
        GRAPH_ASSERTXD(_graph == s._graph, "Edge constructor: nodes from differnt graphs/n");
        
        _id = *_graph._free_id.end();
        _graph._free_id.pop_back();
        if (_graph._free_id.empty())
            _graph._free_id.push_back(_id + 1);
    }
    
    //GRAPH <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
    
    template <class NodeT, class EdgeT> class Graph<NodeT, EdgeT>::node_iterator
    {
        typedef typename list<NodeT>::iterator NoIterT;
        NoIterT _iter;
        
    public:
        inline node_iterator(const NoIterT &basic): _iter(basic) {}
        
        inline node_iterator &operator++()                         { ++_iter; return *this;     }
        inline bool           operator==(const node_iterator &rhs) { return _iter == rhs._iter; }
        inline bool           operator!=(const node_iterator &rhs) { return _iter != rhs._iter; }
        inline NodeT          operator* ()                         { return *_iter;             }
    };
    
    template <class NodeT, class EdgeT> class Graph<NodeT, EdgeT>::edge_iterator
    {
        typedef typename list<EdgeT>::iterator EdIterT;
        EdIterT _iter;
        
    public:
        inline edge_iterator(const EdIterT &basic): _iter(basic) {}
        
        inline edge_iterator &operator++()                         { ++_iter; return *this;     }
        inline bool           operator==(const edge_iterator &rhs) { return _iter == rhs._iter; }
        inline bool           operator!=(const edge_iterator &rhs) { return _iter != rhs._iter; }
        inline EdgeT          operator* ()                         { return *_iter;             }
    };
    
    
    template <class NodeT, class EdgeT> typename Graph<NodeT, EdgeT>::node_iterator Graph<NodeT, EdgeT>::nodes_begin()
    {
        GRAPH_ASSERTXD(_succs.size(), "Graph: nodes_begin: no nodes in the graph/n");
        return _nodes.begin();
    }
    
    template <class NodeT, class EdgeT> typename Graph<NodeT, EdgeT>::node_iterator Graph<NodeT, EdgeT>::nodes_end()
    {
        GRAPH_ASSERTXD(_succs.size(), "Graph: nodes_end: no nodes in the graph/n");
        return _nodes.end();
    }
    
    template <class NodeT, class EdgeT> typename Graph<NodeT, EdgeT>::edge_iterator Graph<NodeT, EdgeT>::edges_begin()
    {
        GRAPH_ASSERTXD(_succs.size(), "Graph: edges_begin: no edges in the graph/n");
        return _edges.begin();
    }
    
    template <class NodeT, class EdgeT> typename Graph<NodeT, EdgeT>::edge_iterator Graph<NodeT, EdgeT>::edges_end()
    {
        GRAPH_ASSERTXD(_succs.size(), "Graph: edges_end: no edges in the graph/n");
        return _edges.end();
    }
    
    template <class NodeT, class EdgeT> NodeT &Graph<NodeT, EdgeT>::create_node()
    {
        NodeT* res = new NodeT(*this);
        
        _nodes.push_back(*res);
        res->_iter = _nodes.end();
        return *res;
    }

    template <class NodeT, class EdgeT> EdgeT &Graph<NodeT, EdgeT>::create_edge(NodeT& pred, NodeT& succ)
    {
        EdgeT* res = new EdgeT(pred, succ);
        
        _edges.push_back(*res);
        res->_iter = _edges.end();
        pred._succs.push_back(res->_iter);
        succ._preds.push_back(res->_iter);
        return *res;
    }
    
    template <class NodeT, class EdgeT> void Graph<NodeT, EdgeT>::remove(NodeT &node)
    {
        for (NoIterT i = node._preds.begin(); i != node._preds.end(); ++i)
            remove(*i);
        for (NoIterT i = node._succs.begin(); i != node._succs.end(); ++i)
            remove(*i);
        _free_id.push_back(node._id);
        _nodes.erase(node._iter);
    }
    
    template <class NodeT, class EdgeT> void Graph<NodeT, EdgeT>::remove(EdgeT &edge)
    {
        _free_id.push_back(edge._id);
        _edges.erase(edge._iter);
    }
    
    //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
        

}; // namespace Task
