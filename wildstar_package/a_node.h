#ifndef A_NODE_H
#define A_NODE_H

class ANode
{
public:
    explicit ANode( ANode* parent );

private:
    ANode* parent_;
};

#endif // A_NODE_H
