#include <iostream>
#include <bits/stdc++.h>

struct CEnvironment {
    bool hasOxygen; ///< true if there is oxygen present in warehouse atmosphere
    int temperature; ///< Temperature in degrees of Celsius
};

class CItem {
public:
    virtual bool canExplode(const CEnvironment & environment) const = 0;
    virtual CItem * clone() const = 0;
    virtual void print(std::ostream & out, int indent) const = 0;
    virtual ~CItem() = default;

    friend std::ostream &operator<<(std::ostream &out, const CItem &item){
        item.print(out, 0);
        return out;
    }
};


class CNamedItem : public CItem {
protected:
    std::string m_Name;
public:
    CNamedItem(const std::string & name) : m_Name(name) {}
};

class CNotExplosive : public CNamedItem {
public:
    explicit CNotExplosive(const std::string &name) : CNamedItem(name) {}

    bool canExplode(const CEnvironment &environment) const override{
        return false;
    }

    CItem *clone() const override{
        return new CNotExplosive(*this);
    }

    void print(std::ostream &out, int indent) const override{
        out << std::string(indent, '\t') << "[N] " << m_Name << std::endl;
    }
};

class COxygenExplosive : public CNamedItem {
public:
    explicit COxygenExplosive(const std::string &name) : CNamedItem(name) {}

    bool canExplode(const CEnvironment &environment) const override{
        return environment.hasOxygen;
    }

    CItem *clone() const override{
        return new COxygenExplosive(*this);
    }

    void print(std::ostream &out, int indent) const override{
        out << std::string(indent, '\t') << "[O] " << m_Name << std::endl;
    }
};

class CTemperatureExplosive : public CNamedItem {
    int m_Temperature;
public:
    CTemperatureExplosive(const std::string &name, int temperature)
            : CNamedItem(name), m_Temperature(temperature) {}

    bool canExplode(const CEnvironment &environment) const override{
        return environment.temperature >= m_Temperature;
    }

    CItem *clone() const override{
        return new CTemperatureExplosive(*this);
    }

    void print(std::ostream &out, int indent) const override{
        out << std::string(indent, '\t') << "[T] " << m_Name << " (" << m_Temperature << "°C)" << std::endl;
    }
};

class CBox : public CItem {
    std::vector<std::unique_ptr<CItem>> m_Items;
public:
    CBox() = default;
    CBox(const CBox & other){
        for(auto & item : other.m_Items) {
            add(*item);
        }
    }
    CBox & operator=(const CBox & other){
        if(this == &other) return *this;

        CBox copied(other);
        std::swap(m_Items, copied.m_Items);

        return *this;
    }

    CBox & add(const CItem & item){
        m_Items.emplace_back(item.clone());
        return *this;
    }

    bool canExplode(const CEnvironment &environment) const override{
        for(auto & item : m_Items) {
            if(item->canExplode(environment)) return true;
        }
        return false;
    }

    CItem *clone() const override{
        return new CBox(*this);
    }

    void print(std::ostream &out, int indent) const override{
        out << std::string(indent, '\t') << "[+] " << m_Items.size() << std::endl;
        for(auto & item : m_Items) {
            item->print(out, indent + 1);
        }
    }
};

int main() {
    CNotExplosive a("teddy");
    COxygenExplosive b("coke_with_mentos");
    CTemperatureExplosive c("chicony_keyboard", 100);
    CBox d;
    std::cout << d.add(CNotExplosive("not_explosive")).add(CTemperatureExplosive("a", 666)).add(CBox().add(COxygenExplosive("anything")));
    std::cout << d.canExplode({ true, 100 }) << std::endl;
    std::cout << d.canExplode({ false, 100 }) << std::endl;
    std::cout << d.canExplode({ true, 1000 }) << std::endl;
    std::cout << d.canExplode({ false, 1000 }) << std::endl;
}