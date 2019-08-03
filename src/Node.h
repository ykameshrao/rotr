//
// Created by ykameshrao on 03/08/19.
//

#ifndef ROTR_NODE_H
#define ROTR_NODE_H

namespace rotr {
    class Node {
        enum State {
            CANDIDATE, FOLLOWER, LEADER
        };

    private:
        State _nodeState;

    public:
        Node() {
            _nodeState = CANDIDATE;
        }

        ~Node() {
        }

        Node(const Node &) = delete;
        Node &operator=(const Node &) = delete;
        Node(Node &&) = delete;
        Node &operator=(Node &&) = delete;

        State nodeState() {
            return _nodeState;
        }
    };
}


#endif //ROTR_NODE_H
