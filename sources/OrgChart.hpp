#ifndef ORGCHART_
#define ORGCHART_

// #include <iostream>
#include <vector>
#include <bits/stdc++.h>
namespace ariel
{
    class OrgChart
    {
    public:
        OrgChart() = default;
        OrgChart(OrgChart & org) = default;
        OrgChart(OrgChart && org) = default;
        OrgChart & operator=(OrgChart && ) = default;
        OrgChart& operator=(const OrgChart & org) = default;
        struct Node{
            Node *parent = nullptr;   //parent node
            std::vector<Node *> child; 
            std::string pos; // possition or name or job
            unsigned long child_num; 
            Node(std::string &po, Node *p = nullptr,unsigned long cn=0) : pos(po), parent(p), child_num(cn){}
        };
        Node * root =nullptr;
        Node* find(const std::string & pos, Node* node){
				Node* ans = nullptr;
				if(node != nullptr){
                    if(node->pos == pos){ return node;}
                    for(unsigned long i = 0 ; i < node->child.size(); i++){
                       ans = find(pos, node->child.at(i));
                       if(ans!=nullptr) {return ans;}
                    }
				}
				return ans;
		}
        std::queue<Node*> level_order_for_reverse(Node* root) const // BFS iteration with improvement
                {
                    std::vector<std::vector<Node*>> level_order;
                    std::queue<Node*> main_queue;
                    std::queue<Node*> queue_reverse;
                    main_queue.push(this->root); //put the first node. In first this the root at level 0.
                    std::vector<Node*> temp_level;
                    int size_of_level = 0;
                    while (!main_queue.empty()) {
                        size_of_level = main_queue.size(); 
                        for (int i = 0; i < size_of_level; i++) { //move out every node from that level
                            Node* current = main_queue.front();
                            main_queue.pop();
                            temp_level.push_back(current);
                            for (Node* child_i : current->child){ //put the next level
                                main_queue.push(child_i);
                            }
                        }
                        level_order.push_back(temp_level); // put every level in her place.
                        temp_level.clear();
                    }
                    for(unsigned long i = level_order.size(); i > 0; i--){
                            for(unsigned long j = 0; j < level_order.at(i-1).size(); j++){
                                queue_reverse.push(level_order.at(i-1).at(j));
                            }
                    }
                    return queue_reverse;
        }
        void print_OrgChart(Node *node, std::ostream& os , int spaces=0) const{ 
				if (node != nullptr){
                    spaces += 1;
                    for (int i = 1; i < spaces; i++){
                            os << "    "; 
                    } 
                    os << node->pos << '\n';
                    for(unsigned long i = 0; i < node->child.size(); i++){ 
                        print_OrgChart(node->child.at(i), os, spaces); 
			    	} 
                }
			}
        class level_order_iterator{
            private:
                std::string *str = new std::string[1];
                Node *current_node = nullptr;
                std::queue <Node*> order;
            public:
                level_order_iterator(Node* ptr,std::queue<Node*> &order)  {
                    this->order = order;
                    this->current_node = ptr;
                }
                level_order_iterator(const level_order_iterator &other) : current_node(other.current_node) , order(other.order){}
                level_order_iterator(level_order_iterator &&other) noexcept{ 
                    current_node = other.current_node; 
                    other.current_node = nullptr;
                    order = other.order;
                    while (!other.order.empty())
                    {
                        other.order.pop();
                    }
                }
                // level_order_iterator& operator= (const level_order_iterator &other){ 
                //     if(*this != other){
                //         current_node = other.current_node;
                //         order = other.order;
                //     }
                //     return *this;
                // }
                level_order_iterator& operator= (const level_order_iterator &other) = default;
                level_order_iterator& operator= (level_order_iterator &&other) noexcept{ 
                    current_node = other.current_node;
                    other.current_node = nullptr;
                    order = other.order;
                    while (!other.order.empty())
                    {
                        other.order.pop();
                    }
                    return *this;
                }
                std::string operator*() const {
                    return current_node->pos;
                }
                std::string *operator->() const {
                    *str = current_node->pos;
                    return str;
                }
                level_order_iterator& operator++() {
                    if(!this->order.empty()){
                        this->current_node = order.front();
                        for(unsigned long i = 0; i < this->current_node->child.size(); i++){
                            order.push(this->current_node->child.at(i));
                        }
                        order.pop();
                    }
                    else{
                            this->current_node = nullptr;
                    }
                    return *this;
                }
                level_order_iterator operator++(int dummy) {
                    level_order_iterator tmp = *this;
                    ++*this;
                    return tmp;
                }
                bool operator==(const level_order_iterator& other) const {

                    return current_node == other.current_node && order == other.order;
                }
                bool operator!=(const level_order_iterator& other) const {
                    return !(*this == other);
                }
                ~level_order_iterator(){
                    delete [] str;
                }
        };
        class reverse_order_iterator{ 
            private:
                std::string *str = new std::string[1];
                Node *current_node = nullptr; 
                std::queue<Node*> order;
            public:
                reverse_order_iterator(Node* ptr,std::queue<Node*> &order)  {
                    this->order = order;
                    this->current_node = ptr;
                }
                reverse_order_iterator(const reverse_order_iterator &other) : current_node(other.current_node) , order(other.order){} 
                reverse_order_iterator(reverse_order_iterator &&other) noexcept{
                    current_node = other.current_node; 
                    other.current_node = nullptr;
                    order = other.order;
                    while (!other.order.empty())
                    {
                        other.order.pop();
                    }
                }
                // reverse_order_iterator& operator= (const reverse_order_iterator &other){
                //     if(*this != other){
                //         current_node = other.current_node;
                //         order = other.order;
                //     }
                //     return *this;
                // }
                reverse_order_iterator& operator= (const reverse_order_iterator &other) = default;
                reverse_order_iterator& operator= (reverse_order_iterator &&other) noexcept{
                    current_node = other.current_node;
                    other.current_node = nullptr;
                    order = other.order;
                    while (!other.order.empty())
                    {
                        other.order.pop();
                    }
                    return *this;
                }
                std::string operator*() const {
                    return current_node->pos;
                }
                std::string *operator->() const {
                    *str = current_node->pos;
                    return str;
                }

                reverse_order_iterator& operator++() {
                    this->order.pop();
                    if(!this->order.empty()){
                            this->current_node =this->order.front();        
                    }
                    else{
                            this->current_node = nullptr;
                    }
                    return *this;
                }
                reverse_order_iterator operator++(int dummy) {
                    reverse_order_iterator tmp = *this;
                    ++*this;
                    return tmp;
                }
                bool operator==(const reverse_order_iterator& other) const {
                    return current_node == other.current_node;
                }
                bool operator!=(const reverse_order_iterator& other) const {
                    return !(*this == other);
                }
                ~reverse_order_iterator(){
                    delete [] str;
                }
        };
        class pre_order_iterator{
            private:
                std::string *str = new std::string[1];
                Node *current_node = nullptr;
                std::stack<Node*> order;
            public:
                pre_order_iterator(Node* ptr,std::stack<Node*> &order)  {
                    this->order = order;
                    this->current_node = ptr;
                }
                pre_order_iterator(const pre_order_iterator &other) : current_node(other.current_node){}
                pre_order_iterator(pre_order_iterator &&other) noexcept{
                    current_node = other.current_node; 
                    other.current_node = nullptr;
                    order = other.order;
                    while (!other.order.empty())
                    {
                        other.order.pop();
                    }
                }
                // pre_order_iterator& operator= (const pre_order_iterator &other){ 
                //     if(*this != other){
                //         current_node = other.current_node;
                //         order = other.order;
                //     }
                //     return *this;
                // }
                pre_order_iterator& operator= (const pre_order_iterator &other) = default;
                pre_order_iterator& operator= (pre_order_iterator &&other) noexcept{ 
                    current_node = other.current_node;
                    other.current_node = nullptr;
                    order = other.order;
                    while (!other.order.empty())
                    {
                        other.order.pop();
                    }
                    return *this;
                }
                std::string operator*() const {
                    return current_node->pos;
                }
                std::string *operator->() const {
                    *str = current_node->pos;
                    return str;
                }
                pre_order_iterator& operator++() {
                    this->current_node = nullptr;
                    if(!order.empty()){
                        this->current_node = order.top();
                        order.pop();
                        if(this->current_node != nullptr)
                        {
                            std::vector<Node*>::iterator it = this->current_node->child.end();
                            while (it != this->current_node->child.begin()) {
                                it--;
                                order.push(*it);
                            }
                        }
                    }
                    return *this;
                }
                pre_order_iterator operator++(int dummy) {
                    pre_order_iterator tmp = *this;
                    ++*this;
                    return tmp;
                }
                bool operator==(const pre_order_iterator& other) const {
                    return current_node == other.current_node;
                }
                bool operator!=(const pre_order_iterator& other) const {
                    return !(*this == other);
                }
                ~pre_order_iterator(){
                    delete [] str;
                }
        };
        OrgChart &add_root(const std::string &j);
        std::string chart_empty() const;
        OrgChart &add_sub(const std::string &j,std::string l);
        level_order_iterator begin() const;
        level_order_iterator end() const;
        level_order_iterator begin_level_order() const;
        level_order_iterator end_level_order() const;
        reverse_order_iterator begin_reverse_order() const;
        reverse_order_iterator reverse_order() const;
        pre_order_iterator begin_preorder()const;
        pre_order_iterator end_preorder()const;
        friend std::ostream & operator<<(std::ostream & os, const OrgChart & self);
        void clear(Node* node){
            if(node != nullptr){
                for(unsigned long i = 0; i < node->child.size(); i++){
                    clear(node->child.at(i));
                }
                delete node;
            }
        }
        ~OrgChart(){
            clear(root);   //before deconstructing delete all nodes
        }

    };
    
}
#endif