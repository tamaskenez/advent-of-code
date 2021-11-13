#include "common.h"

struct Inst
{
    string mne;
    int num;
};

struct Machine
{
    int pc = 0;
    int acc = 0;
};

Inst line_to_inst(string s)
{
    auto vs = split(s, " ");
    assert(~vs == 2);
    assert(~vs[0] == 3);
    assert(!vs[1].empty());
    assert(vs[1][0] == '+' || vs[1][0] == '-');
    int num = atoi(vs[1].c_str());
    return Inst{vs[0], num};
}

void execute_next(Machine& m, const vector<Inst>& insts)
{
    auto& i = insts.at(m.pc);
    if (i.mne == "acc") {
        m.acc += i.num;
        m.pc++;
    } else if (i.mne == "jmp") {
        m.pc += i.num;
    } else if (i.mne == "nop") {
        m.pc++;
    }
}

struct FindTermination
{
    vector<Inst> insts;

    FindTermination(vector<Inst> insts) : insts(std::move(insts)) {}

    Machine m;
    maybe<int> next_step()
    {
        execute_next(m, insts);
        if (m.pc == ~insts) {
            return m.acc;
        }
        return nullopt;
    }
};

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d8_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    vector<Inst> insts;
    for (auto l : lines) {
        insts.PB(line_to_inst(l));
    }
    Machine m;
    unordered_set<int> executed;
    for (;;) {
        if (executed.count(m.pc) > 0) {
            printf("P1: %d\n", m.acc);
            break;
        }
        executed.insert(m.pc);
        execute_next(m, insts);
    }

    vector<FindTermination> finders;
    FOR (i, 0, < ~insts) {
        auto instsmod = insts;
        auto& im = instsmod[i];
        if (im.mne == "jmp") {
            im.mne = "nop";
        } else if (im.mne == "nop") {
            im.mne = "jmp";
        } else {
            continue;
        }
        finders.emplace_back(move(instsmod));
    }

    bool done = false;
    for (; !done;) {
        for (auto& f : finders) {
            auto r = f.next_step();
            if (r) {
                done = true;
                printf("P2: %d\n", *r);
                break;
            }
        }
    }

    return 0;
}

// 13.31
