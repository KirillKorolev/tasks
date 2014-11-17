/***********************************************************

    Implementation of Graph class.

    @file: task/iface.h
    @date: October 27, 2014
    @author: Kirill Korolev <kirill.korolef@gmail.com>
    @vertion: 1.0 (October 27, 2014) 

***********************************************************/

namespace Task {
    
    //NODE  <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
    
    template <class NodeT, class EdgeT> EdgeT &Graph<NodeT, EdgeT>::Node::first_pred()
    {
        if (_preds.size())
            return *_preds.front();
        else {
            Error err;
            err.type = EMPTY;
            throw err;
        }
    }
    
    template <class NodeT, class EdgeT> EdgeT &Graph<NodeT, EdgeT>::Node::first_succ()
    {
        if (_succs.size())
            return *_succs.front();
        else {
            Error err;
            err.type = EMPTY;
            throw err;
        }
    }
    
    template <class NodeT, class EdgeT> Graph<NodeT, EdgeT>::Node::Node(Graph<NodeT, EdgeT> &g):
    _graph(g) {
        GRAPH_ASSERTXD(g._free_id.size(), "Node constructor: no free id values/n");
        _id = g._free_id.back();
        g._free_id.pop_back();
        if (g._free_id.empty())
            g._free_id.push_back(_id + 1);
    }
    
    //EDGE  <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
    
    template <class NodeT, class EdgeT> Graph<NodeT, EdgeT>::Edge::Edge(NodeT &p, NodeT &s):
    _graph(p._graph), _pred(p), _succ(s) {
        GRAPH_ASSERTXD(_graph._free_id.size(), "Edge constructor: no free id values/n");
        GRAPH_ASSERTXD(&p._graph == &s._graph, "Edge constructor: nodes from differnt graphs/n");
        _id = _graph._free_id.back();
        _graph._free_id.pop_back();
        if (_graph._free_id.empty())
            _graph._free_id.push_back(_id + 1);
    }
    
    //GRAPH <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
    
    template <class NodeT, class EdgeT> NodeT &Graph<NodeT, EdgeT>::create_node()
    {
        _nodes.emplace_back(*this);
        NodeT &res = _nodes.back();
        res._iter = --_nodes.end();
        return res;
    }

    template <class NodeT, class EdgeT> EdgeT &Graph<NodeT, EdgeT>::create_edge(NodeT& pred, NodeT& succ)
    {
        _edges.emplace_back(pred, succ);
        EdgeT &res = _edges.back();
        res._iter = --_edges.end();
        pred._succs.push_back(res._iter);
        succ._preds.push_back(res._iter);
        res._pred_iter = --pred._succs.end();
        res._succ_iter = --succ._preds.end();
        return res;
    }
    
    template <class NodeT, class EdgeT> void Graph<NodeT, EdgeT>::remove(NodeT &node)
    {
        int num = (int) node.num_preds();
        for (int i = 0; i < num; i++)
                remove(*node._preds.front());
        for (int i = 0; i < (int) node.num_succs(); i++)
                remove(*node._succs.front());
        _free_id.push_back(node._id);
        _nodes.erase(node._iter);
    }
    
    template <class NodeT, class EdgeT> void Graph<NodeT, EdgeT>::remove(EdgeT &edge)
    {
        edge._pred._succs.erase(edge._pred_iter);
        edge._succ._preds.erase(edge._succ_iter);
        _free_id.push_back(edge._id);
        _edges.erase(edge._iter);
    }
    
    //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

}; // namespace Task
