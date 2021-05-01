
#include <iostream>
#include <map>
#include <cmath>
#include <vector>

using namespace std;

class Fancy {
    enum OpType { NONE = 0, ADD=1, MUL=2};

    struct Op{

        int32_t val_;
        OpType type_ = NONE; 

        explicit Op(OpType type, int val) {
            this->type_ = type;
            this->val_ = val;
        }

        int64_t doOp(int64_t num) {
            int64_t ret = 0;
            if (type_ == ADD) {
                ret = num + val_; 
            } else if (type_ == MUL) {
                ret = num * val_;
            }
            return ret;
        }
    };

    static constexpr int64_t mod = pow(10, 9);

    std::vector<int64_t> elem_;

    std::map<int32_t, std::vector<Op>> ops_;

public:
    Fancy() {

    }

    void printAll() {
        cout << "elem:";
        for (int i = 0; i < this->elem_.size(); i++) {
            cout << this->elem_[i] << ",";
        }
        cout << endl;
    }

    void append(int val) {
        elem_.push_back(val);
    }

    void addAll(int inc) {
        if (not this->elem_.size()) {
            return;
        }
        Op o(OpType::ADD, inc);
        auto iter = ops_.find(this->elem_.size() - 1);
        if (iter == ops_.end()) {
            std::vector<Op> opvec{o};
            ops_.insert({elem_.size() - 1, opvec});
        } else {
            iter->second.push_back(o);
        }
    }

    void multAll(int m) {
        if (not this->elem_.size()) {
            return;
        }
        Op o(OpType::MUL, m);
        auto iter = ops_.find(this->elem_.size() - 1);
        if (iter == ops_.end()) {
            std::vector<Op> opvec{o};
            ops_.insert({elem_.size() - 1, opvec});
        } else {
            iter->second.push_back(o);
        }
    }

    int getIndex(int idx) {
        if (idx >= elem_.size()) {
            return -1;
        }
        int64_t raw_elem = elem_[idx];
        cout << "idx=" << idx << "=" << raw_elem << "B:";
        auto iter = ops_.lower_bound(idx);
        for (; iter != ops_.end(); ++iter) {
            for (auto opiter = iter->second.begin(); opiter != iter->second.end(); ++opiter) {
                raw_elem = opiter->doOp(raw_elem);
                cout << ":op=" << opiter->type_ << "," << opiter->val_ << "=" << raw_elem;
                while (raw_elem >= Fancy::mod) { 
                    raw_elem = raw_elem - Fancy::mod; 
                    cout << ":t=" << raw_elem;
                }
            }
        }
        cout << endl;
        return raw_elem;
    }
};

int main()
{
    Fancy* obj = new Fancy();
  obj->append(12);
  obj->append(8);
  obj->append(12);
  obj->addAll(12);
  obj->append(8);
  obj->append(4);
  obj->append(13);
  obj->append(12);
  obj->append(11);
  obj->append(10);
  obj->multAll(3);
  obj->addAll(1);
  obj->append(14);
  obj->addAll(5);
  obj->multAll(12);
  obj->multAll(12);
  obj->addAll(15);
  obj->addAll(6);
  obj->append(7);
  obj->multAll(8);
  obj->append(13);
  obj->append(15);
  obj->append(15);
  obj->multAll(10);
  obj->multAll(12);
  obj->multAll(12);
  obj->multAll(9);
  obj->addAll(9);
  obj->append(9);
  obj->multAll(4);
  obj->addAll(8);
  obj->addAll(11);
  obj->multAll(15);
  obj->addAll(9);
  obj->addAll(1);
  obj->append(4);
  obj->append(10);
    obj->printAll();
    cout << "ANSWER: " << obj->getIndex(9) << endl;
}

/**

[Fancy,append,append,getIndex,append,getIndex,addAll,append,getIndex,getIndex,append,append,getIndex,append,getIndex,append,getIndex,append,getIndex,multAll,addAll,getIndex,append,addAll,getIndex,multAll,getIndex,multAll,addAll,addAll,append,multAll,append,append,append,multAll,getIndex,multAll,multAll,multAll,getIndex,addAll,append,multAll,addAll,addAll,multAll,addAll,addAll,append,append,getIndex]
[[],[12],[8],[1],[12],[0],[12],[8],[2],[2],[4],[13],[4],[12],[6],[11],[1],[10],[2],[3],[1],[6],[14],[5],[6],[12],[3],[12],[15],[6],[7],[8],[13],[15],[15],[10],[9],[12],[12],[9],[9],[9],[9],[4],[8],[11],[15],[9],[1],[4],[10],[9]]
*/
