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
        State nodeState_;

    public:
        Node() {
            nodeState_ = CANDIDATE;
        }

        ~Node() {
        }

        Node(const Node &) = delete;
        Node &operator=(const Node &) = delete;
        Node(Node &&) = delete;
        Node &operator=(Node &&) = delete;

        State nodeState() {
            return nodeState_;
        }
    };
}


#endif //ROTR_NODE_H
