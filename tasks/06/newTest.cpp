#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <typeinfo>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <utility>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <memory>
#include <algorithm>
#include <type_traits>

using namespace std;

class CRect {
public:
    CRect(double x, double y, double w, double h) : m_X(x), m_Y(y), m_W(w), m_H(h) {};

    friend ostream &operator<<(ostream &os, const CRect &x) {
        return os << '(' << x.m_X << ',' << x.m_Y << ',' << x.m_W << ',' << x.m_H << ')';
    }

    double m_X;
    double m_Y;
    double m_W;
    double m_H;
};

#endif /* __PROGTEST__ */

//убрать атрибуты из САйтем, переделать классы в НеймедАйтем, имена сделать атрибутом классов-потомков

class CItem {
protected:
    CRect realPos = CRect(0, 0, 0, 0);
public:

    virtual void print(ostream &out, const string &fPrefix, const string &sPrefix) const = 0;

    virtual ~CItem() = default;

    virtual void setRealPos(const CRect &rPos) = 0;

    virtual CItem *clone(const CRect &realPosition) const = 0;

    friend std::ostream &operator<<(std::ostream &out, const CItem &item) {
        item.print(out, "", "");
        return out;
    }

    virtual CItem * find(int x) const = 0;

    virtual CRect getRelPos() const = 0;

    virtual int getId() const = 0;
};

class CNamedItem : public CItem {
protected:
    int id;
    CRect pos;

public:
    CNamedItem(int id, const CRect &pos) : id(id), pos(pos) {};

};

class CButton : public CNamedItem {
    string content;
public:
    CButton(int id, const CRect &relPos, const string &name) : CNamedItem(id, relPos), content(name) {};

    CItem *clone(const CRect &realPosition) const override {
        auto *newButton = new CButton(id, pos, content);
        newButton->setRealPos(
                CRect(realPosition.m_W * pos.m_X + realPosition.m_X, realPosition.m_H * pos.m_Y + realPosition.m_Y,
                      realPosition.m_W * pos.m_W, realPosition.m_H * pos.m_H));
        return newButton;
    }

    CItem *find(int x) const override {
        return nullptr;
    }

    void setRealPos(const CRect &rPos) override {
        realPos = CRect(rPos.m_X, rPos.m_Y, rPos.m_W, rPos.m_H);
    }

    int getId() const override {
        return id;
    }

    CRect getRelPos() const override {
        return pos;
    }

    void print(ostream &out, const string &fPrefix, const string &sPrefix ) const override {
        out << fPrefix <<"[" << id << "] Button \"" << content << "\" " << realPos << "\n";
    }
};

class CInput : public CNamedItem {
    string content;
public:
    CInput(int id, const CRect &relPos, const string &value) : CNamedItem(id, relPos), content(value) {};

    void setValue(const string &name) {
        content = name;
    }

    CItem *find(int x) const override {
        return nullptr;
    }

    void setRealPos(const CRect &rPos) override {
        realPos = CRect(rPos.m_X, rPos.m_Y, rPos.m_W, rPos.m_H);
    }

    string getValue() {
        return content;
    }

    int getId() const override {
        return id;
    }

    CRect getRelPos() const override {
        return pos;
    }

    CItem *clone(const CRect &realPosition) const override {
        CInput *newInput = new CInput(id, pos, content);
        newInput->setRealPos(
                CRect(realPosition.m_W * pos.m_X + realPosition.m_X, realPosition.m_H * pos.m_Y + realPosition.m_Y,
                      realPosition.m_W * pos.m_W, realPosition.m_H * pos.m_H));
        return newInput;
    }

    void print(ostream &out, const string &fPrefix, const string &sPrefix) const override {
        out << fPrefix << "[" << id << "] Input \"" << content << "\" " << realPos << "\n";
    }
};

class CLabel : public CNamedItem {

    string content;
public:
    CLabel(int id, const CRect &relPos, const string &label) : CNamedItem(id, relPos), content(label) {};

    CItem *clone(const CRect &realPosition) const override {
        CLabel *newLabel = new CLabel(id, pos, content);
        newLabel->setRealPos(
                CRect(realPosition.m_W * pos.m_X + realPosition.m_X, realPosition.m_H * pos.m_Y + realPosition.m_Y,
                      realPosition.m_W * pos.m_W, realPosition.m_H * pos.m_H));
        return newLabel;
    }

    CItem *find(int x) const override {
        return nullptr;
    }

    void setRealPos(const CRect &rPos) override {
        realPos = CRect(rPos.m_X, rPos.m_Y, rPos.m_W, rPos.m_H);
    }

    CRect getRelPos() const override {
        return pos;
    }

    int getId() const override {
        return id;
    }

    void print(ostream &out, const string &fPrefix, const string &sPrefix) const override {
        out << fPrefix << "[" << id << "] Label \"" << content << "\" " << realPos << "\n";
    }
};

class CComboBox : public CNamedItem {
    int idx = 0;
    vector<string> options;

    string content;
public:
    CComboBox(int id, const CRect &relPos) : CNamedItem(id, relPos) {};

    CRect getRelPos() const override {
        return pos;
    }

    CComboBox &add(const string &option) {
        options.push_back(option);
        return *this;
    }

    CItem *find(int x) const override {
        return nullptr;
    }

    void setRealPos(const CRect &rPos) override {
        realPos = CRect(rPos.m_X, rPos.m_Y, rPos.m_W, rPos.m_H);
    }

    void setSelected(int x) {
        idx = x;
    }

    int getSelected() const {
        return idx;
    }

    int getId() const override {
        return id;
    }

    CItem *clone(const CRect &realPosition) const override {
        auto *newBox = new CComboBox(*this);
        newBox->setRealPos(
                CRect(realPosition.m_W * pos.m_X + realPosition.m_X, realPosition.m_H * pos.m_Y + realPosition.m_Y,
                      realPosition.m_W * pos.m_W, realPosition.m_H * pos.m_H));
        return newBox;
    }

    const vector<string> &getOptions() const {
        return options;
    }

    void print(ostream &out, const string &fPrefix, const string &sPrefix) const override {
        out << fPrefix << "[" << id << "] ComboBox " << realPos << "\n";
        size_t len = options.size();
        for (int i = 0; i < int(len); i++) {
            if (i == idx) {
                out << sPrefix << "+->" << options[i] << "<" << "\n";
            } else {
                out << sPrefix << "+- " << options[i] << "\n";
            }
        }
    }
};

class CPanel : public CItem{
    int id;
    CRect pos;

public:
    vector<unique_ptr<CItem>> items;
    CPanel(int id, const CRect &relPos) : id(id), pos(relPos) {}

    CPanel(const CPanel &other) : pos(other.pos) {
        for (auto &item: other.items) {
            add(*item);
        }
        id = other.id;
        realPos = CRect(other.realPos.m_X, other.realPos.m_Y, other.realPos.m_W, other.realPos.m_H);
    }

    CPanel& operator=(const CPanel &other) {
        if (this == &other) return *this;

        CPanel copied(other);
        std::swap(items, copied.items);
        id = other.id;
        pos = CRect(other.pos.m_X, other.pos.m_Y, other.pos.m_W, other.pos.m_H);
        realPos = CRect(other.realPos.m_X, other.realPos.m_Y, other.realPos.m_W, other.realPos.m_H);

        return *this;
    }

    void print(ostream &out, const string &fPrefix, const string &sPrefix) const override {
        out << fPrefix << "[" << id << "] Panel " << realPos << "\n";

        size_t len = items.size();

        for (int i = 0; i < int(len); i++) {
            if (typeid(*items[i]).name() == typeid(CPanel).name() || typeid(*items[i]).name() == typeid(CComboBox).name()) {
                if (i != int(len) - 1) {
                    items[i]->print(out, sPrefix + "+- ", sPrefix + "|  ");
                } else {
                    items[i]->print(out, sPrefix + "+- ", sPrefix + "   ");
                }
            }
            else{
                items[i]->print(out, sPrefix + "+- ", sPrefix + "");
            }
        }
    }


    void setRealPos(const CRect &rPos) override {
        realPos = CRect(rPos.m_X, rPos.m_Y, rPos.m_W, rPos.m_H);

        changePos();
    }

    CPanel* changePos(){
        for (auto & item : items){
            item->setRealPos(CRect(realPos.m_W * item->getRelPos().m_X + realPos.m_X, realPos.m_H * item->getRelPos().m_Y + realPos.m_Y,
                                   realPos.m_W * item->getRelPos().m_W, realPos.m_H * item->getRelPos().m_H));
        }

        return this;
    }

    CItem *clone(const CRect &realPosition) const override {
        auto *newPanel = new CPanel(*this);
        newPanel->setRealPos(
                CRect(realPosition.m_W * pos.m_X + realPosition.m_X, realPosition.m_H * pos.m_Y + realPosition.m_Y,
                      realPosition.m_W * pos.m_W, realPosition.m_H * pos.m_H));

        newPanel->changePos();

        return newPanel;
    }

    CRect getRelPos() const override {
        return pos;
    }

    int getId() const override {
        return id;
    }

    CPanel &add(const CItem &item) {
        items.emplace_back(item.clone(realPos));
        return *this;
    }

    CItem *find(int x) const override {
        for (auto &item : items){
            if (item->getId() == x){
                return item.get();
            }

            if (typeid(*item).name() == typeid(CPanel).name()){
                auto element = item->find(x);
                if (element != nullptr){
                    return element;
                }
            }
        }

        return nullptr;
    }
};

class CWindow : public CItem {
    vector<unique_ptr<CItem>> items;
    int id;
    CRect pos;
    string content;
public:
    CWindow(int id, const string &title, const CRect &absPos) : id(id), pos(absPos), content(title) {};

    CWindow(const CWindow &other) : pos(other.pos) {
        for (auto &item: other.items) {
            add(*item);
        }
        id = other.id;
        content = other.content;
    }

    void setRealPos(const CRect &rPos) override {
        realPos = CRect(rPos.m_X, rPos.m_Y, rPos.m_W, rPos.m_H);
    }

    CWindow &operator=(const CWindow &other) {
        if (this == &other) return *this;

        CWindow copied(other);
        std::swap(items, copied.items);
        id = other.id;
        content = other.content;
        pos = CRect(other.pos.m_X, other.pos.m_Y, other.pos.m_W, other.pos.m_H);

        return *this;
    }

    int getId() const override {
        return id;
    }

    CRect getRelPos() const override {
        return pos;
    }

    CItem *clone(const CRect &realPosition) const override {
        return new CWindow(*this);
    }

    void print(ostream &out, const string &fPrefix, const string &sPrefix) const override {
        out << "[" << id << "] Window \"" << content << "\" " << pos << "\n";

        size_t len = items.size();

        for (int i = 0; i < int(len); i++) {
            if (i != int(len) - 1){
                string str1 = "+- ";
                string str2 = "|  ";
                items[i]->print(out, fPrefix + str1, sPrefix + str2);
            }
            else{
                string str1 = "+- ";
                string str2 = "   ";
                items[i]->print(out, fPrefix + str1, sPrefix + str2);
            }
        }
    }

    CItem *find(int x) const override {
        return nullptr;
    }

    CWindow &add(const CItem &item) {
        items.emplace_back(item.clone(pos));
        return *this;
    }

    CItem *search(int x) {
        for (auto &item: items) {
            if (item->getId() == x) {
                return item.get();
            }

            if (typeid(*item).name() == typeid(CPanel).name()){
                auto element = item->find(x);
                if (element != nullptr){
                    return element;
                }
            }
        }

        return nullptr;
    }

    CWindow &setPosition(const CRect &absPos) {
        pos = absPos;

        for (auto &item: items) {
            (*item).setRealPos(
                    CRect(pos.m_W * item->getRelPos().m_X + pos.m_X, pos.m_H * item->getRelPos().m_Y + pos.m_Y,
                          pos.m_W * item->getRelPos().m_W, pos.m_H * item->getRelPos().m_H));
        }

        return *this;
    }
};

// output operators

#ifndef __PROGTEST__

template<typename T_>
string toString(const T_ &x) {
    ostringstream oss;
    oss << x;
    return oss.str();
}

int main(void) {
    assert (sizeof(CButton) - sizeof(string) < sizeof(CComboBox) - sizeof(vector<string>));
    assert (sizeof(CInput) - sizeof(string) < sizeof(CComboBox) - sizeof(vector<string>));
    assert (sizeof(CLabel) - sizeof(string) < sizeof(CComboBox) - sizeof(vector<string>));
    assert (sizeof(CButton) - sizeof(string) <= sizeof(CPanel) - sizeof(vector<void *>));
    assert (sizeof(CInput) - sizeof(string) <= sizeof(CPanel) - sizeof(vector<void *>));
    assert (sizeof(CLabel) - sizeof(string) <= sizeof(CPanel) - sizeof(vector<void *>));
    CWindow a(0, "Sample window", CRect(10, 10, 600, 480));
    a.add(CButton(1, CRect(0.1, 0.8, 0.3, 0.1), "Ok")).add(CButton(2, CRect(0.6, 0.8, 0.3, 0.1), "Cancel"));
    a.add(CLabel(10, CRect(0.1, 0.1, 0.2, 0.1), "Username:"));
    a.add(CInput(11, CRect(0.4, 0.1, 0.5, 0.1), "chucknorris"));
    a.add(CPanel(12, CRect(0.1, 0.3, 0.8, 0.7)).add(
            CComboBox(20, CRect(0.1, 0.3, 0.8, 0.1)).add("Karate").add("Judo").add("Box").add("Progtest")));
    assert (toString(a) ==
            "[0] Window \"Sample window\" (10,10,600,480)\n"
            "+- [1] Button \"Ok\" (70,394,180,48)\n"
            "+- [2] Button \"Cancel\" (370,394,180,48)\n"
            "+- [10] Label \"Username:\" (70,58,120,48)\n"
            "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
            "+- [12] Panel (70,154,480,336)\n"
            "   +- [20] ComboBox (118,254.8,384,33.6)\n"
            "      +->Karate<\n"
            "      +- Judo\n"
            "      +- Box\n"
            "      +- Progtest\n");
    CWindow b = a;
    assert (toString(*b.search(20)) ==
            "[20] ComboBox (118,254.8,384,33.6)\n"
            "+->Karate<\n"
            "+- Judo\n"
            "+- Box\n"
            "+- Progtest\n");
    assert (dynamic_cast<CComboBox &> ( *b.search(20)).getSelected() == 0);
    dynamic_cast<CComboBox &> ( *b.search(20)).setSelected(3);
    assert (dynamic_cast<CInput &> ( *b.search(11)).getValue() == "chucknorris");
    dynamic_cast<CInput &> ( *b.search(11)).setValue("chucknorris@fit.cvut.cz");
    CPanel &p = dynamic_cast<CPanel &> ( *b.search(12));
    p.add(CComboBox(21, CRect(0.1, 0.5, 0.8, 0.1)).add("PA2").add("OSY").add("Both"));
    assert (toString(b) ==
            "[0] Window \"Sample window\" (10,10,600,480)\n"
            "+- [1] Button \"Ok\" (70,394,180,48)\n"
            "+- [2] Button \"Cancel\" (370,394,180,48)\n"
            "+- [10] Label \"Username:\" (70,58,120,48)\n"
            "+- [11] Input \"chucknorris@fit.cvut.cz\" (250,58,300,48)\n"
            "+- [12] Panel (70,154,480,336)\n"
            "   +- [20] ComboBox (118,254.8,384,33.6)\n"
            "   |  +- Karate\n"
            "   |  +- Judo\n"
            "   |  +- Box\n"
            "   |  +->Progtest<\n"
            "   +- [21] ComboBox (118,322,384,33.6)\n"
            "      +->PA2<\n"
            "      +- OSY\n"
            "      +- Both\n");
    assert (toString(a) ==
            "[0] Window \"Sample window\" (10,10,600,480)\n"
            "+- [1] Button \"Ok\" (70,394,180,48)\n"
            "+- [2] Button \"Cancel\" (370,394,180,48)\n"
            "+- [10] Label \"Username:\" (70,58,120,48)\n"
            "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
            "+- [12] Panel (70,154,480,336)\n"
            "   +- [20] ComboBox (118,254.8,384,33.6)\n"
            "      +->Karate<\n"
            "      +- Judo\n"
            "      +- Box\n"
            "      +- Progtest\n");
    assert (toString(p) ==
            "[12] Panel (70,154,480,336)\n"
            "+- [20] ComboBox (118,254.8,384,33.6)\n"
            "|  +- Karate\n"
            "|  +- Judo\n"
            "|  +- Box\n"
            "|  +->Progtest<\n"
            "+- [21] ComboBox (118,322,384,33.6)\n"
            "   +->PA2<\n"
            "   +- OSY\n"
            "   +- Both\n");
    b.setPosition(CRect(20, 30, 640, 520));
    assert (toString(b) ==
            "[0] Window \"Sample window\" (20,30,640,520)\n"
            "+- [1] Button \"Ok\" (84,446,192,52)\n"
            "+- [2] Button \"Cancel\" (404,446,192,52)\n"
            "+- [10] Label \"Username:\" (84,82,128,52)\n"
            "+- [11] Input \"chucknorris@fit.cvut.cz\" (276,82,320,52)\n"
            "+- [12] Panel (84,186,512,364)\n"
            "   +- [20] ComboBox (135.2,295.2,409.6,36.4)\n"
            "   |  +- Karate\n"
            "   |  +- Judo\n"
            "   |  +- Box\n"
            "   |  +->Progtest<\n"
            "   +- [21] ComboBox (135.2,368,409.6,36.4)\n"
            "      +->PA2<\n"
            "      +- OSY\n"
            "      +- Both\n");
    p.add(p);
    assert (toString(p) ==
            "[12] Panel (84,186,512,364)\n"
            "+- [20] ComboBox (135.2,295.2,409.6,36.4)\n"
            "|  +- Karate\n"
            "|  +- Judo\n"
            "|  +- Box\n"
            "|  +->Progtest<\n"
            "+- [21] ComboBox (135.2,368,409.6,36.4)\n"
            "|  +->PA2<\n"
            "|  +- OSY\n"
            "|  +- Both\n"
            "+- [12] Panel (135.2,295.2,409.6,254.8)\n"
            "   +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
            "   |  +- Karate\n"
            "   |  +- Judo\n"
            "   |  +- Box\n"
            "   |  +->Progtest<\n"
            "   +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
            "      +->PA2<\n"
            "      +- OSY\n"
            "      +- Both\n");
    p.add(p);
    assert (toString(p) ==
            "[12] Panel (84,186,512,364)\n"
            "+- [20] ComboBox (135.2,295.2,409.6,36.4)\n"
            "|  +- Karate\n"
            "|  +- Judo\n"
            "|  +- Box\n"
            "|  +->Progtest<\n"
            "+- [21] ComboBox (135.2,368,409.6,36.4)\n"
            "|  +->PA2<\n"
            "|  +- OSY\n"
            "|  +- Both\n"
            "+- [12] Panel (135.2,295.2,409.6,254.8)\n"
            "|  +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
            "|  |  +- Karate\n"
            "|  |  +- Judo\n"
            "|  |  +- Box\n"
            "|  |  +->Progtest<\n"
            "|  +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
            "|     +->PA2<\n"
            "|     +- OSY\n"
            "|     +- Both\n"
            "+- [12] Panel (135.2,295.2,409.6,254.8)\n"
            "   +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
            "   |  +- Karate\n"
            "   |  +- Judo\n"
            "   |  +- Box\n"
            "   |  +->Progtest<\n"
            "   +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
            "   |  +->PA2<\n"
            "   |  +- OSY\n"
            "   |  +- Both\n"
            "   +- [12] Panel (176.16,371.64,327.68,178.36)\n"
            "      +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
            "      |  +- Karate\n"
            "      |  +- Judo\n"
            "      |  +- Box\n"
            "      |  +->Progtest<\n"
            "      +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
            "         +->PA2<\n"
            "         +- OSY\n"
            "         +- Both\n");
    p.add(p);
    assert (toString(p) ==
            "[12] Panel (84,186,512,364)\n"
            "+- [20] ComboBox (135.2,295.2,409.6,36.4)\n"
            "|  +- Karate\n"
            "|  +- Judo\n"
            "|  +- Box\n"
            "|  +->Progtest<\n"
            "+- [21] ComboBox (135.2,368,409.6,36.4)\n"
            "|  +->PA2<\n"
            "|  +- OSY\n"
            "|  +- Both\n"
            "+- [12] Panel (135.2,295.2,409.6,254.8)\n"
            "|  +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
            "|  |  +- Karate\n"
            "|  |  +- Judo\n"
            "|  |  +- Box\n"
            "|  |  +->Progtest<\n"
            "|  +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
            "|     +->PA2<\n"
            "|     +- OSY\n"
            "|     +- Both\n"
            "+- [12] Panel (135.2,295.2,409.6,254.8)\n"
            "|  +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
            "|  |  +- Karate\n"
            "|  |  +- Judo\n"
            "|  |  +- Box\n"
            "|  |  +->Progtest<\n"
            "|  +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
            "|  |  +->PA2<\n"
            "|  |  +- OSY\n"
            "|  |  +- Both\n"
            "|  +- [12] Panel (176.16,371.64,327.68,178.36)\n"
            "|     +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
            "|     |  +- Karate\n"
            "|     |  +- Judo\n"
            "|     |  +- Box\n"
            "|     |  +->Progtest<\n"
            "|     +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
            "|        +->PA2<\n"
            "|        +- OSY\n"
            "|        +- Both\n"
            "+- [12] Panel (135.2,295.2,409.6,254.8)\n"
            "   +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
            "   |  +- Karate\n"
            "   |  +- Judo\n"
            "   |  +- Box\n"
            "   |  +->Progtest<\n"
            "   +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
            "   |  +->PA2<\n"
            "   |  +- OSY\n"
            "   |  +- Both\n"
            "   +- [12] Panel (176.16,371.64,327.68,178.36)\n"
            "   |  +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
            "   |  |  +- Karate\n"
            "   |  |  +- Judo\n"
            "   |  |  +- Box\n"
            "   |  |  +->Progtest<\n"
            "   |  +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
            "   |     +->PA2<\n"
            "   |     +- OSY\n"
            "   |     +- Both\n"
            "   +- [12] Panel (176.16,371.64,327.68,178.36)\n"
            "      +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
            "      |  +- Karate\n"
            "      |  +- Judo\n"
            "      |  +- Box\n"
            "      |  +->Progtest<\n"
            "      +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
            "      |  +->PA2<\n"
            "      |  +- OSY\n"
            "      |  +- Both\n"
            "      +- [12] Panel (208.928,425.148,262.144,124.852)\n"
            "         +- [20] ComboBox (235.142,462.604,209.715,12.4852)\n"
            "         |  +- Karate\n"
            "         |  +- Judo\n"
            "         |  +- Box\n"
            "         |  +->Progtest<\n"
            "         +- [21] ComboBox (235.142,487.574,209.715,12.4852)\n"
            "            +->PA2<\n"
            "            +- OSY\n"
            "            +- Both\n");
    assert (toString(b) ==
            "[0] Window \"Sample window\" (20,30,640,520)\n"
            "+- [1] Button \"Ok\" (84,446,192,52)\n"
            "+- [2] Button \"Cancel\" (404,446,192,52)\n"
            "+- [10] Label \"Username:\" (84,82,128,52)\n"
            "+- [11] Input \"chucknorris@fit.cvut.cz\" (276,82,320,52)\n"
            "+- [12] Panel (84,186,512,364)\n"
            "   +- [20] ComboBox (135.2,295.2,409.6,36.4)\n"
            "   |  +- Karate\n"
            "   |  +- Judo\n"
            "   |  +- Box\n"
            "   |  +->Progtest<\n"
            "   +- [21] ComboBox (135.2,368,409.6,36.4)\n"
            "   |  +->PA2<\n"
            "   |  +- OSY\n"
            "   |  +- Both\n"
            "   +- [12] Panel (135.2,295.2,409.6,254.8)\n"
            "   |  +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
            "   |  |  +- Karate\n"
            "   |  |  +- Judo\n"
            "   |  |  +- Box\n"
            "   |  |  +->Progtest<\n"
            "   |  +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
            "   |     +->PA2<\n"
            "   |     +- OSY\n"
            "   |     +- Both\n"
            "   +- [12] Panel (135.2,295.2,409.6,254.8)\n"
            "   |  +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
            "   |  |  +- Karate\n"
            "   |  |  +- Judo\n"
            "   |  |  +- Box\n"
            "   |  |  +->Progtest<\n"
            "   |  +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
            "   |  |  +->PA2<\n"
            "   |  |  +- OSY\n"
            "   |  |  +- Both\n"
            "   |  +- [12] Panel (176.16,371.64,327.68,178.36)\n"
            "   |     +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
            "   |     |  +- Karate\n"
            "   |     |  +- Judo\n"
            "   |     |  +- Box\n"
            "   |     |  +->Progtest<\n"
            "   |     +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
            "   |        +->PA2<\n"
            "   |        +- OSY\n"
            "   |        +- Both\n"
            "   +- [12] Panel (135.2,295.2,409.6,254.8)\n"
            "      +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
            "      |  +- Karate\n"
            "      |  +- Judo\n"
            "      |  +- Box\n"
            "      |  +->Progtest<\n"
            "      +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
            "      |  +->PA2<\n"
            "      |  +- OSY\n"
            "      |  +- Both\n"
            "      +- [12] Panel (176.16,371.64,327.68,178.36)\n"
            "      |  +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
            "      |  |  +- Karate\n"
            "      |  |  +- Judo\n"
            "      |  |  +- Box\n"
            "      |  |  +->Progtest<\n"
            "      |  +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
            "      |     +->PA2<\n"
            "      |     +- OSY\n"
            "      |     +- Both\n"
            "      +- [12] Panel (176.16,371.64,327.68,178.36)\n"
            "         +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
            "         |  +- Karate\n"
            "         |  +- Judo\n"
            "         |  +- Box\n"
            "         |  +->Progtest<\n"
            "         +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
            "         |  +->PA2<\n"
            "         |  +- OSY\n"
            "         |  +- Both\n"
            "         +- [12] Panel (208.928,425.148,262.144,124.852)\n"
            "            +- [20] ComboBox (235.142,462.604,209.715,12.4852)\n"
            "            |  +- Karate\n"
            "            |  +- Judo\n"
            "            |  +- Box\n"
            "            |  +->Progtest<\n"
            "            +- [21] ComboBox (235.142,487.574,209.715,12.4852)\n"
            "               +->PA2<\n"
            "               +- OSY\n"
            "               +- Both\n");
    assert (toString(a) ==
            "[0] Window \"Sample window\" (10,10,600,480)\n"
            "+- [1] Button \"Ok\" (70,394,180,48)\n"
            "+- [2] Button \"Cancel\" (370,394,180,48)\n"
            "+- [10] Label \"Username:\" (70,58,120,48)\n"
            "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
            "+- [12] Panel (70,154,480,336)\n"
            "   +- [20] ComboBox (118,254.8,384,33.6)\n"
            "      +->Karate<\n"
            "      +- Judo\n"
            "      +- Box\n"
            "      +- Progtest\n");
    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
