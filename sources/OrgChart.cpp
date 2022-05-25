#include "OrgChart.hpp"

using namespace std;

namespace ariel{
    OrgChart& OrgChart::add_root(const std::string &j){
        if(this->root == nullptr){
            string p = j;
            this->root = new Node{p};
		}
        else{
            this->root->pos = j;
        }
        return *this;
    }
    std::string OrgChart::chart_empty() const{
        if(this->root == nullptr){
            throw "chart is empty!";
        }
        return "enpty chart";
    }
    OrgChart& OrgChart::add_sub(const std::string &j,std::string l){
        this->chart_empty();
        Node* p = find(j,this->root);
        if(p !=nullptr){
            (p->child).push_back(new Node(l,p,p->child.size()));
        }
        else{
            throw "employer doesn't exist";
        }
        return *this;
    }
    OrgChart::level_order_iterator OrgChart::begin() const{
        this->chart_empty();
        std::queue<Node*> start_queue;
        for(unsigned long i = 0; i < this->root->child.size(); i++){
            start_queue.push(this->root->child.at(i));
        }
        return level_order_iterator{this->root,start_queue};
    }
    OrgChart::level_order_iterator OrgChart::end() const{
        this->chart_empty();
        std::queue<Node*> start_queue;
        return level_order_iterator{nullptr,start_queue};
    }
    OrgChart::level_order_iterator OrgChart::begin_level_order() const{
        this->chart_empty();
        std::queue<Node*> start_queue;
        for(unsigned long i = 0; i < this->root->child.size(); i++){
            start_queue.push(this->root->child.at(i));
        }
        return level_order_iterator{this->root,start_queue};
    }
    OrgChart::level_order_iterator OrgChart::end_level_order() const{
        this->chart_empty();
        std::queue<Node*> start_queue;
        return level_order_iterator{nullptr,start_queue};
    }
     OrgChart::reverse_order_iterator OrgChart::begin_reverse_order() const{
        this->chart_empty();
        std::queue<Node*> order_traversal = this->level_order_for_reverse(this->root);
        return reverse_order_iterator(order_traversal.front(),order_traversal);
    }
     OrgChart::reverse_order_iterator OrgChart::reverse_order() const{
        this->chart_empty();
        std::queue<Node*> order_traversal;
        return reverse_order_iterator(nullptr,order_traversal);
    }
    OrgChart::pre_order_iterator OrgChart::begin_preorder() const{
        this->chart_empty();
        std::stack<Node*> stack_start;
        std::vector<Node*>::iterator it = this->root->child.end();
        while (it != this->root->child.begin()) {
            it--;
            stack_start.push(*it);
        }
        return pre_order_iterator(this->root,stack_start);
    }
    OrgChart::pre_order_iterator OrgChart::end_preorder()const{
        this->chart_empty();
        std::stack<Node*> stack_start;
        return pre_order_iterator(nullptr,stack_start);
    }
    ostream & operator<<(std::ostream & os, const OrgChart & self){
        self.print_OrgChart(self.root,os);
        return os;
    }
}