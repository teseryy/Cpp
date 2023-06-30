#include<iostream>
#include<cassert>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<unordered_map>
#include<memory>
#include<unordered_set>
#include<queue>
#include<list>
#include<sstream>
#include<cstring>

using namespace std;

class CPkg{
public:
    CPkg(const string& name) : name(name){}

    CPkg& addDep(const string& package){
        depend.insert(package);

        return *this;
    }

    bool operator <(const CPkg& other) const{
        return name < other.name;
    }

    string name;
    set<string> depend;

};

class CPkgSys{
public:
    CPkgSys& addPkg(const CPkg& input){
        added.insert(input);

        return *this;
    }

    set<string> install(const list<string>& packs){
        set<string> res;

        map<string, CPkg> packages;
        for (const auto& pack : added){
            packages.insert(make_pair(pack.name, pack));
        }

        set<string> newInstalled;

        list<string> newL = packs;

        queue<string> toVisit;
        toVisit.push(newL.front());
        newL.pop_front();

        while (!toVisit.empty() || !newL.empty()){
            if (toVisit.empty() && !newL.empty()){
                toVisit.push(newL.front());
                newL.pop_front();
            }

            string name = toVisit.front();
            toVisit.pop();

            if (installed.find(name) != installed.end() || newInstalled.find(name) != newInstalled.end()){
                continue;
            }

            if (packages.find(name) == packages.end()){
                throw invalid_argument("Package not found.");
            }

            newInstalled.insert(name);
            res.insert(name);
            for (const auto& elem : packages.find(name)->second.depend){
                toVisit.push(elem);
            }
        }
        for (const auto& str : newInstalled){
            installed.insert(str);
        }

        return res;
    }

    friend ostream& operator <<(ostream& out, const CPkgSys& packages){
        bool isFirst = true;
        for (const auto& package : packages.installed){
            if (isFirst){
                out << package;
                isFirst = false;
            }
            else{
                out << ", " << package;
            }
        }
        return out;
    }
private:
    set<CPkg> added;
    set<string> installed;
};

int main(void) {
    CPkgSys s;
    stringstream ss;
    s.addPkg(CPkg("ssh").addDep("sudo").addDep("apt"))
            .addPkg(CPkg("sudo").addDep("git").addDep("c++"));
    s.addPkg(CPkg("apt"))
            .addPkg(CPkg("c++").addDep("c").addDep("asm").addDep("fortran"));
    s.addPkg(CPkg("git"))
            .addPkg(CPkg("c").addDep("kekw"))
            .addPkg(CPkg("kekw"))
            .addPkg(CPkg("asm"))
            .addPkg(CPkg("fortran"));
    s.addPkg(CPkg("python").addDep("bash").addDep("sadge"))
            .addPkg(CPkg("karel").addDep("python"))
            .addPkg(CPkg("bash").addDep("sadge"))
            .addPkg(CPkg("sadge"))
            .addPkg(CPkg("cython").addDep("dev"));
    s.addPkg(CPkg("perl"));

    ss << s;
    assert(ss.str() == "");
    ss.clear();
    ss.str("");

    set<string> t1 = s.install(list<string>{"sudo"});
    assert(t1 == (set<string>{"asm", "c", "c++", "fortran", "git", "kekw", "sudo"}));
    set<string> t2 = s.install(list<string>{"ssh", "c++"});
    assert(t2 == (set<string>{"apt", "ssh"}));

    ss << s;
    assert(ss.str() == "apt, asm, c, c++, fortran, git, kekw, ssh, sudo");
    ss.clear();
    ss.str("");

    try {
        set<string> e = s.install(list<string>{"karel", "cython"});
        assert("Sem ses nemel dostat debilku" == nullptr);
    }
    catch (const invalid_argument &e) {
        assert(strcmp("Package not found.", e.what()) == 0);
    }
    set<string> t3 = s.install(list<string>{"karel", "fortran", "git"});
    assert(t3 == (set<string>{"bash", "karel", "python", "sadge"}));

    s.addPkg(CPkg("java").addDep("utils"))
            .addPkg(CPkg("utils").addDep("VB"))
            .addPkg(CPkg("VB").addDep("java"));

    set<string> t4 = s.install(list<string>{"java", "perl"});
    assert(t4 == (set<string>{"VB", "java", "perl", "utils"}));

    ss << s;
    assert(ss.str() ==
           "VB, apt, asm, bash, c, c++, fortran, git, java, karel, kekw, perl, python, sadge, ssh, sudo, utils");
    ss.clear();
    ss.str("");

    CPkgSys k;
    k.addPkg(CPkg("ssh").addDep("sudo").addDep("apt"))
            .addPkg(CPkg("sudo").addDep("git"));
    k.addPkg(CPkg("apt"));
    k.addPkg(CPkg("git"))
            .addPkg(CPkg("c").addDep("kekw"))
            .addPkg(CPkg("kekw"))
            .addPkg(CPkg("asm"))
            .addPkg(CPkg("fortran"));
    k.addPkg(CPkg("python").addDep("bash").addDep("sadge"))
            .addPkg(CPkg("karel").addDep("python"))
            .addPkg(CPkg("bash").addDep("sadge"))
            .addPkg(CPkg("sadge"));
    k.addPkg(CPkg("perl").addDep("no"));

    set<string> t5 = k.install(list<string>{"asm"});
    assert(t5 == (set<string>{"asm"}));
    set<string> t6 = k.install(list<string>{"python", "ssh"});
    assert(t6 == (set<string>{"apt", "bash", "git", "python", "sadge", "ssh", "sudo"}));

    try {
        set<string> t7 = k.install(list<string>{"perl", "c"});
        assert("Sem ses nemel dostat debilku" == nullptr);
    }
    catch (const invalid_argument &e) {
        assert(strcmp("Package not found.", e.what()) == 0);
    }
    set<string> t8 = k.install(list<string>{"c", "ssh", "karel"});

    assert(t8 == (set<string>{"c", "karel", "kekw"}));

    ss << k;
    assert(ss.str() == "apt, asm, bash, c, git, karel, kekw, python, sadge, ssh, sudo");
    ss.clear();
    ss.str("");
}