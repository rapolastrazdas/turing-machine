#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <deque>
#include <conio.h>

using namespace std;

class TuringMachine
{
    private:
        // Tiuringo mašinos lentelės duomenys
        vector<string> prev_state;
        vector<char> prev_symbol_1;
        vector<char> prev_symbol_2;
        vector<char> next_symbol_1;
        vector<char> next_symbol_2;
        vector<char> direction_1;
        vector<char> direction_2;
        vector<string> next_state;

        // Tiuringo mašinos būsena
        string state = "0";

        // Tiuringo mašinų galvučių pozicijos
        int position_1;
        int position_2;

        // Tiuringo mašinos juosta/-os
        int n_tapes;
        bool two_tapes = false;
        deque<char> tape_1;
        deque<char> tape_2;

    public:
        string input_file;
        bool halted = false;

        void read_tape()
        {
            ifstream read(input_file);

            string line, tape, p_state, n_state;
            char p_symbol_1, p_symbol_2, n_symbol_1, n_symbol_2, direct_1, direct_2;

            // Nuskaitomi duomenys apie mašinos juostą/-as
            read >> n_tapes;
            if (n_tapes == 2) two_tapes = true;

            read >> tape;
            for (char symbol : tape) tape_1.push_back(symbol);

            if (two_tapes)
            {
                read >> tape;
                for (char symbol : tape) tape_2.push_back(symbol);
            }

            // Galvutės pozicija koreguojama kad 1-mas simbolis būtų 0-intoje pozicijoje
            read >> position_1; position_1--;
            if(two_tapes) read >> position_2, position_2--;

            // Nuskaitomi mašinos lentelės duomenys ir sukeliami į atitinkamus vektorius
            while (getline(read, line))
            {
                stringstream ss(line);

                if (!two_tapes) ss >> p_state >> p_symbol_1 >> n_symbol_1 >> direct_1 >> n_state;
                else if (two_tapes)  ss >> p_state >> p_symbol_1 >> p_symbol_2 >> n_symbol_1 >> n_symbol_2 >> direct_1 >> direct_2 >> n_state;

                prev_state.push_back(p_state);
                prev_symbol_1.push_back(p_symbol_1);
                prev_symbol_2.push_back(p_symbol_2);
                next_symbol_1.push_back(n_symbol_1);
                next_symbol_2.push_back(n_symbol_2);
                direction_1.push_back(direct_1);
                direction_2.push_back(direct_2);
                next_state.push_back(n_state);
            }
        }
        void take_step()
        {
           
            for (int i = 0; i < prev_state.size(); i++)
            {
                // Juosta/-os pratempiama/-os pagal poreikį
                if(position_1 == -1) tape_1.push_front('_');
                if(position_1 == tape_1.size()) tape_1.push_back('_');
                if(position_2 == -1) tape_2.push_front('_');
                if(position_2 == tape_2.size()) tape_2.push_back('_');

                 // Tikrinama ar yra taisyklės mašinos būsenai ir pirmos juostos simboliui
                if ((state == prev_state[i]) && (tape_1[position_1] == prev_symbol_1[i]))
                {
                    if (!two_tapes)
                    {
                        // Įvykdomos vienjuostės mašinos taisyklės
                        tape_1[position_1] = next_symbol_1[i];

                        if (direction_1[i] == 'L') position_1--;
                        else if (direction_1[i] == 'R') position_1++; 

                        if (next_state[i] == "H"){halted = true; cout << "SUSTABDYTA!" << endl;}
                        state = next_state[i];

                        return;
                    }

                    // Jei mašina dvijuostė papildomai tikrinama ar yra taisyklė ir antros juostos simboliui
                    else if (two_tapes && tape_2[position_2] == prev_symbol_2[i])
                    {
                        // Įvykdomos dvijuostės mašinos taisyklės
                        tape_2[position_2] = next_symbol_2[i];

                        if (direction_2[i] == 'L') position_2--;
                        else if (direction_2[i] == 'R') position_2++;

                        tape_1[position_1] = next_symbol_1[i];

                        if (direction_1[i] == 'L') position_1--;
                        else if (direction_1[i] == 'R') position_1++;

                        if (next_state[i] == "H"){halted = true; cout << "SUSTABDYTA!" << endl;}
                        state = next_state[i];

                        return;
                    }
                }
            }

            // Jei nerasta taisyklė atitinkamai būsenai ir atitinkamoms galvutės pozicijoms mašina sustabdoma 
            halted = true;
            if(state != "H")
            {
                cout << "SUSTABDYTA! Nėra taisyklės būsenai '" << state << "' ir simboliui '" << tape_1[position_1] <<"'";
                if(two_tapes) cout << " ir simboliui '" << tape_2[position_2] <<"'";
                cout << endl;
            }
            else cout << "SUSTABDYTA!" << endl;
        }
        void print_tapes()
        {
            // Juostų išvedimas į ekraną
            cout << "Juosta 1:" << endl;
            if(!tape_1.empty())
            {
                for(int i = 0; i < tape_1.size(); i++) cout << tape_1[i];
            } 
            cout << endl;

            if(two_tapes)
            {
                cout << "Juosta 2:" << endl;
                if(!tape_2.empty())
                {
                    for(int i = 0; i < tape_2.size(); i++) cout << tape_2[i];
                }
                cout << endl;
            }
        }
};

int main()
{
    int n_machines, n_halted = 0;
    string input_file;
    vector<TuringMachine> tu_machines;
    TuringMachine tu_machine;
    bool print;

    // Simuliacijos UI :D
    cout << "Sveiki atvykę į Tiuringo mašinos simuliaciją!" << endl;
    cout << "Jei norėtumėte sustabdyti simuliaciją paspauskite betkurį klavieturos mygtuką." << endl;
    cout << "Kiek tiuringo mašinų norėtumėte paleisti vienu metu?" << endl;
    cin >> n_machines;
    for (int i = 0; i < n_machines; i++)
    {
        cout << "Įveskite failo pavadinimą su " << i+1 <<" mašinos taisyklėmis" << endl;
        cin >> input_file;
        tu_machine.input_file = input_file;
        tu_machines.push_back(tu_machine);
    }
    
    for (int i = 0; i < n_machines; i++) tu_machines[i].read_tape();

    while(n_halted != n_machines)
    {
        n_halted = 0, print = false;
        for (int i = 0; i < n_machines; i++)
        {
            cout << endl;
            cout << "MAŠINA " << i+1 << ":" << endl;
            cout << endl;
            tu_machines[i].print_tapes();
            tu_machines[i].take_step();
        }

        for (int i = 0; i < n_machines; i++)
        {
            if(tu_machines[i].halted == true) n_halted++;
        }

        // Begalinio ciklo stabdis
        if(_kbhit()) n_halted = n_machines;
    }
    if(n_halted == n_machines) cout << endl << "Visos mašinos sustojo!" << endl;
    
    return 0;
}